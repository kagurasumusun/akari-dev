#!/usr/bin/env python3
"""proto-cite.py -- backfill page-id citations for function decls that
proto-audit reports as no-pageid.

For every (header, name) row with status `no-pageid` in the proto-audit
TSV, scan the corpus for pages printing a prototype of that name and
verify the print's parameter list equals the decl's (norm_params).
Only exact param matches are cited; pages whose print differs are never
cited (that would manufacture a MISMATCH).  The page id is inserted as
a one-line comment directly above the decl, which is where proto-audit
looks for citations.

Decls are located in comment-stripped text (strip_comments preserves
offsets), so DECL-shaped examples inside documentation comments are
never touched.  The pass-1 corpus scan is cached in
build/proto-cite-cache.tsv (delete it to force a rescan).

Usage: python3 tools/proto-cite.py <corpus-clone> [--dry]
"""
import importlib.util
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_spec = importlib.util.spec_from_file_location(
    "pa", os.path.join(ROOT, "tools", "proto-audit.py"))
pa = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(pa)


def main():
    corpus = sys.argv[1]
    dry = "--dry" in sys.argv
    audit = os.path.join(ROOT, "docs", "proto-audit-2026-09-18.tsv")
    targets = []
    for ln in open(audit, encoding="utf-8").read().splitlines()[1:]:
        c = ln.split("\t")
        if len(c) >= 4 and c[3] == "no-pageid":
            targets.append((c[0], c[1]))
    names = sorted({n for _, n in targets}, key=len, reverse=True)
    print("no-pageid decls:", len(targets), "names:", len(names))
    name_re = re.compile(
        r"\b(" + "|".join(map(re.escape, names)) + r")\s*\(")

    # pass 1: which pages mention a candidate name at all (cached)
    cache = os.path.join(ROOT, "build", "proto-cite-cache.tsv")
    found = {}                       # name -> [(pid, fn, path)]
    npages = 0
    if os.path.exists(cache):
        for ln in open(cache, encoding="utf-8"):
            c = ln.rstrip("\n").split("\t")
            if len(c) == 4:
                found.setdefault(c[0], []).append((c[1], c[2], c[3]))
        print("cache loaded:", sum(len(v) for v in found.values()),
              "hits for", len(found), "names")
    if not found:
        for base in ("docs/mslearn", "docs/chm", "docs/wayback-msdn"):
            d0 = os.path.join(corpus, base)
            if not os.path.isdir(d0):
                continue
            for sub in sorted(os.listdir(d0)):
                d = os.path.join(d0, sub)
                if not os.path.isdir(d):
                    continue
                for fn in sorted(os.listdir(d)):
                    if not fn.endswith(".html"):
                        continue
                    npages += 1
                    path = os.path.join(d, fn)
                    try:
                        h = open(path, encoding="utf-8",
                                 errors="replace").read()
                    except OSError:
                        continue
                    cand = set(name_re.findall(h))
                    if not cand:
                        continue
                    pid = re.sub(r"\(v=[a-z0-9.]+\)$", "", fn[:-5])
                    for nm in cand:
                        found.setdefault(nm, []).append((pid, fn, path))
        print("pages scanned:", npages, "names with pages:", len(found))
        os.makedirs(os.path.dirname(cache), exist_ok=True)
        with open(cache, "w", encoding="utf-8") as f:
            for nm, lst in sorted(found.items()):
                for pid, fn, path in lst:
                    f.write(f"{nm}\t{pid}\t{fn}\t{path}\n")

    by_hdr = {}
    for hdr, nm in targets:
        by_hdr.setdefault(hdr, []).append(nm)

    edits = {}                       # hdr -> [(name, pid)]
    stats = {"cited": 0, "no-page": 0, "no-exact": 0, "decl-in-comment": 0}
    unresolved = []
    for hdr, nms in sorted(by_hdr.items()):
        p = os.path.join(ROOT, hdr)
        s = open(p, encoding="utf-8").read()
        stripped = pa.strip_comments(s)   # offsets preserved
        decl = {}                          # name -> (params_raw, start)
        for m in pa.DECL.finditer(stripped):
            decl.setdefault(m.group(2), (m.group(3), m.start()))
        for nm in nms:
            pages = found.get(nm)
            if not pages:
                stats["no-page"] += 1
                unresolved.append((hdr, nm, "no-page"))
                continue
            if nm not in decl:
                stats["decl-in-comment"] += 1
                unresolved.append((hdr, nm, "decl-only-in-comment"))
                continue
            praw, dstart = decl[nm]
            dparams, ok = pa.norm_params(praw)
            if not ok:
                stats["no-exact"] += 1
                unresolved.append((hdr, nm, "complex-decl"))
                continue
            best = None
            for pid, fn, path in pages:
                cands = pa.page_protos(path, nm)
                if not cands:
                    bn = nm[:-1] if nm.endswith(("W", "A")) else nm
                    cands = pa.page_protos(path, bn)
                if not cands:
                    continue
                for _ret, _cn, params in cands:
                    if params == dparams:
                        pref = (0 if "winembedded.60" in fn else
                                1 if "msdn.10" in fn else 2)
                        if best is None or pref < best[0]:
                            best = (pref, pid)
            if best is None:
                stats["no-exact"] += 1
                unresolved.append((hdr, nm, "print-differs"))
                continue
            edits.setdefault(hdr, []).append((nm, best[1], dstart))
            stats["cited"] += 1
    print("stats:", stats)

    if not dry:
        for hdr, lst in sorted(edits.items()):
            p = os.path.join(ROOT, hdr)
            s = open(p, encoding="utf-8").read()
            # insert bottom-up so earlier offsets stay valid
            for nm, pid, dstart in sorted(lst, key=lambda x: -x[2]):
                line_start = s.rfind("\n", 0, dstart) + 1
                cmt = f"/* {pid}: page print verified (proto-cite) */\n"
                s = s[:line_start] + cmt + s[line_start:]
            open(p, "w", encoding="utf-8").write(s)
        print("edited", len(edits), "headers")

    rep = os.path.join(ROOT, "docs", "proto-cite-unresolved.tsv")
    with open(rep, "w", encoding="utf-8") as f:
        f.write("# header\tname\treason\n")
        for hdr, nm, why in unresolved:
            f.write(f"{hdr}\t{nm}\t{why}\n")
    print("wrote", rep)


if __name__ == "__main__":
    main()
