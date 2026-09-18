#!/usr/bin/env python3
"""enum-cite.py -- backfill page-id citations for typedef enums that
enum-audit reports as no-pageid.

A page is cited only when it prints `typedef enum ... } NAME` with the
same tag (when both have one), the same enumerator-name list (with the
audit's lost-comma recovery) and equal effective values -- i.e. only
when the next enum-audit will score the row `match`.  Comment wording
avoids the annotated-deviation trigger words (artifact|page print|
omits) so rows are scored on their merits.

Usage: python3 tools/enum-cite.py <corpus-clone> [--dry]
"""
import html as _html
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


ea = _load("ea", "enum-audit.py")
sa = _load("sa", "struct-audit.py")


def compares_equal(tag, a, ptag, b):
    if ptag and tag and ptag != tag:
        return False
    if "," not in b and len(re.findall(r"[A-Za-z_]\w*\s*=", b)) > 1:
        b = re.sub(r"\s+(?=[A-Za-z_]\w*\s*=)", ", ", b)
    bl = ea.enum_members(b)
    if bl is None:
        return False
    if [x[0] for x in a] != [x[0] for x in bl]:
        return False
    hv = {}
    nxt = 0
    for nm, v in a:
        if v is not None:
            e = ea.eff_value(v)
            nxt = e + 1 if e is not None else nxt
            hv[nm] = e if e is not None else v
        else:
            hv[nm] = nxt
            nxt += 1
    for nm, v in bl:
        if v is not None:
            e = ea.eff_value(v)
            if isinstance(hv.get(nm), int) and e is not None \
                    and hv[nm] != e:
                return False
    return True


def main():
    corpus = sys.argv[1]
    dry = "--dry" in sys.argv
    tsv = os.path.join(ROOT, "docs", "enum-audit-2026-09-18.tsv")
    targets = []
    for ln in open(tsv, encoding="utf-8").read().splitlines()[1:]:
        c = ln.split("\t")
        if len(c) >= 4 and c[3] == "no-pageid":
            targets.append((c[0], c[1]))
    names = sorted({n for _, n in targets}, key=len, reverse=True)
    print("enum no-pageid:", len(targets), "names:", len(names))
    name_re = re.compile(r"\b(" + "|".join(map(re.escape, names)) + r")\b")

    cache = os.path.join(ROOT, "build", "enum-cite-cache.tsv")
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

    by_hdr = {}
    for hdr, nm in targets:
        by_hdr.setdefault(hdr, []).append(nm)
    edits = {}
    cited = 0
    unresolved = []
    for hdr, nms in sorted(by_hdr.items()):
        p = os.path.join(ROOT, hdr)
        s = open(p, encoding="utf-8").read()
        sc = sa.strip_comments(s)
        decl = {}
        for m in ea.TE.finditer(sc):
            tag, body, name = m.groups()
            decl.setdefault(name, (tag, body, m.start()))
        for nm in nms:
            if nm not in decl or nm not in found:
                unresolved.append((hdr, nm, "no-page-or-decl"))
                continue
            tag, body, dstart = decl[nm]
            a = ea.enum_members(body)
            if a is None:
                unresolved.append((hdr, nm, "unparseable"))
                continue
            best = None
            for pid, fn, path in found[nm]:
                h = open(path, encoding="utf-8",
                         errors="replace").read()
                for blk in ea.PRE.findall(h):
                    blk = re.sub(r"(?i)<br\s*/?>", "\n", blk)
                    t = _html.unescape(re.sub(r"<[^>]+>", " ", blk))
                    t = re.sub(r"[ \t]+", " ", t)
                    mm = re.search(
                        r"typedef\s+enum\s*(\w*)\s*\{(.*?)\}\s*%s\b"
                        % re.escape(nm), t, re.S)
                    if mm and compares_equal(tag, a, mm.group(1),
                                             mm.group(2)):
                        pref = 0 if "winembedded.60" in fn else 1
                        if best is None or pref < best[0]:
                            best = (pref, pid)
                        break
            if best is None:
                unresolved.append((hdr, nm, "no-equal-print"))
                continue
            edits.setdefault(hdr, []).append((dstart, best[1], nm))
            cited += 1
    print("cited:", cited)

    if not dry:
        for hdr, lst in sorted(edits.items()):
            p = os.path.join(ROOT, hdr)
            s = open(p, encoding="utf-8").read()
            for dstart, pid, nm in sorted(lst, key=lambda x: -x[0]):
                line_start = s.rfind("\n", 0, dstart) + 1
                cmt = (f"/* {pid}: enumerators verified against this "
                       f"page (enum-cite) */\n")
                s = s[:line_start] + cmt + s[line_start:]
            open(p, "w", encoding="utf-8").write(s)
        print("edited", len(edits), "headers")

    rep = os.path.join(ROOT, "docs", "enum-cite-unresolved.tsv")
    with open(rep, "w", encoding="utf-8") as f:
        f.write("# header\tname\treason\n")
        for hdr, nm, why in unresolved:
            f.write(f"{hdr}\t{nm}\t{why}\n")
    print("wrote", rep)


if __name__ == "__main__":
    main()
