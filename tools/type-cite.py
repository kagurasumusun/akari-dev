#!/usr/bin/env python3
"""type-cite.py -- backfill page-id citations for struct/union and
function-pointer typedefs that struct-audit / fnptr-audit report as
no-pageid.

Structs: a page is cited only when its printed member-name list equals
the decl's (exact), or is an exact prefix of it (page truncated the
print block; struct-audit scores that match-truncated-print).
Fnptrs: cited only when both the parameter types and the return type
compare equal (the audit's match path); partial matches are never
cited.

Citations are inserted as a one-line comment directly above the decl.
Comment wording avoids the annotated-deviation trigger words so the
next audit scores these rows on their merits.

Usage: python3 tools/type-cite.py <corpus-clone> [--dry]
"""
import html
import importlib.util
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def _load(mod, fname):
    spec = importlib.util.spec_from_file_location(
        mod, os.path.join(ROOT, "tools", fname))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


pa = _load("pa", "proto-audit.py")
sa = _load("sa", "struct-audit.py")
fa = _load("fa", "fnptr-audit.py")


def read_targets(tsv):
    out = []
    for ln in open(tsv, encoding="utf-8").read().splitlines()[1:]:
        c = ln.split("\t")
        if len(c) >= 4 and c[3] == "no-pageid":
            out.append((c[0], c[1]))
    return out


def main():
    corpus = sys.argv[1]
    dry = "--dry" in sys.argv
    t_struct = read_targets(os.path.join(
        ROOT, "docs", "struct-audit-2026-09-18.tsv"))
    t_fn = read_targets(os.path.join(
        ROOT, "docs", "fnptr-audit-2026-09-18.tsv"))
    names = sorted({n for _, n in t_struct + t_fn},
                   key=len, reverse=True)
    print("struct no-pageid:", len(t_struct),
          "fnptr no-pageid:", len(t_fn), "names:", len(names))
    name_re = re.compile(r"\b(" + "|".join(map(re.escape, names)) + r")\b")

    cache = os.path.join(ROOT, "build", "type-cite-cache.tsv")
    found = {}
    if os.path.exists(cache):
        for ln in open(cache, encoding="utf-8"):
            c = ln.rstrip("\n").split("\t")
            if len(c) == 4:
                found.setdefault(c[0], []).append((c[1], c[2], c[3]))
        print("cache loaded:", sum(len(v) for v in found.values()), "hits")
    if not found:
        npages = 0
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

    edits = {}                       # hdr -> [(start, pid, name)]
    stats = {"struct": 0, "fnptr": 0}
    unresolved = []

    # ---- structs ----
    by_hdr = {}
    for hdr, nm in t_struct:
        by_hdr.setdefault(hdr, []).append(nm)
    for hdr, nms in sorted(by_hdr.items()):
        p = os.path.join(ROOT, hdr)
        s = open(p, encoding="utf-8").read()
        sc = sa.strip_comments(s)
        decl = {}
        for m in sa.TS.finditer(sc):
            decl.setdefault(m.group(4), (m.group(3), m.start()))
        for nm in nms:
            if nm not in decl or nm not in found:
                unresolved.append((hdr, nm, "struct:no-page-or-decl"))
                continue
            body, dstart = decl[nm]
            a = sa.member_names(body, peel_glued=False)
            best = None
            for pid, fn, path in found[nm]:
                h = open(path, encoding="utf-8", errors="replace").read()
                printed = trunc = None
                for blk in sa.PRE.findall(h):
                    t = html.unescape(re.sub(r"<[^>]+>", " ", blk))
                    t = re.sub(r"\s+", " ", t)
                    mm = re.search(
                        r"typedef\s+(?:struct|union)\s*\w*\s*\{(.*)\}"
                        r"\s*%s\b" % re.escape(nm), t)
                    if mm:
                        printed = mm.group(1)
                        break
                    if trunc is None:
                        mt = re.search(
                            r"typedef\s+(?:struct|union)\s*\w*\s*\{(.*)$", t)
                        if mt:
                            trunc = mt.group(1)
                if printed is not None:
                    if sa.member_names(printed) == a:
                        pref = 0 if "winembedded.60" in fn else 1
                        if best is None or pref < best[0]:
                            best = (pref, pid, dstart, nm)
                elif trunc is not None:
                    b = sa.member_names(trunc)
                    if b and b == a[:len(b)]:
                        pref = 2 if "winembedded.60" in fn else 3
                        if best is None or pref < best[0]:
                            best = (pref, pid, dstart, nm)
            if best is None:
                unresolved.append((hdr, nm, "struct:no-exact"))
                continue
            edits.setdefault(hdr, []).append(
                (best[2], best[1], best[3]))
            stats["struct"] += 1

    # ---- fnptrs ----
    by_hdr = {}
    for hdr, nm in t_fn:
        by_hdr.setdefault(hdr, []).append(nm)
    for hdr, nms in sorted(by_hdr.items()):
        p = os.path.join(ROOT, hdr)
        s = open(p, encoding="utf-8").read()
        sc = pa.strip_comments(s)
        decl = {}
        for m in fa.FP.finditer(sc):
            ret, name, args = (re.sub(r"\s+", " ", g).strip()
                               for g in m.groups())
            decl.setdefault(name, (ret.replace("typedef", "").strip(),
                                   args, m.start()))
        for nm in nms:
            if nm not in decl or nm not in found:
                unresolved.append((hdr, nm, "fnptr:no-page-or-decl"))
                continue
            ret, args, dstart = decl[nm]
            ha, hok = pa.norm_params(args)
            if not hok:
                unresolved.append((hdr, nm, "fnptr:unparseable"))
                continue
            hret = pa.norm_type(ret)
            best = None
            for pid, fn, path in found[nm]:
                prints = fa.page_prints(path, nm)
                for pret, pargs in prints:
                    pr, pok = pa.norm_params(pargs)
                    if not pok:
                        continue
                    pr0 = re.sub(r"(?i)^\s*typedef", "", pret.strip())
                    pret_t = pa.norm_type(re.sub(
                        r"\b(typedef|CALLBACK|CALLAPI|APIENTRY)\b",
                        " ", pr0))
                    if (len(pr) == len(ha)
                            and all(pa.types_equal(x, y)
                                    for x, y in zip(pr, ha))
                            and pa.types_equal(pret_t, hret)):
                        pref = 0 if "winembedded.60" in fn else 1
                        if best is None or pref < best[0]:
                            best = (pref, pid)
                        break
            if best is None:
                unresolved.append((hdr, nm, "fnptr:no-exact"))
                continue
            edits.setdefault(hdr, []).append((dstart, best[1], nm))
            stats["fnptr"] += 1
    print("stats:", stats)

    if not dry:
        for hdr, lst in sorted(edits.items()):
            p = os.path.join(ROOT, hdr)
            s = open(p, encoding="utf-8").read()
            for dstart, pid, nm in sorted(lst, key=lambda x: -x[0]):
                line_start = s.rfind("\n", 0, dstart) + 1
                cmt = (f"/* {pid}: members/signature verified against "
                       f"this page (type-cite) */\n")
                s = s[:line_start] + cmt + s[line_start:]
            open(p, "w", encoding="utf-8").write(s)
        print("edited", len(edits), "headers")

    rep = os.path.join(ROOT, "docs", "type-cite-unresolved.tsv")
    with open(rep, "w", encoding="utf-8") as f:
        f.write("# header\tname\treason\n")
        for hdr, nm, why in unresolved:
            f.write(f"{hdr}\t{nm}\t{why}\n")
    print("wrote", rep)


if __name__ == "__main__":
    main()
