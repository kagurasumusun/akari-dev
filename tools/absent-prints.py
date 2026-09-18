#!/usr/bin/env python3
"""Regenerate the absent-funcprints ledger against the current corpus.

Reads docs/surface-audit.tsv (run surface-audit.py first), takes every
`absent` name, scans all corpus pages' <pre> blocks for a function
print of that name, and writes docs/absent-funcprints-<date>.tsv with
columns: name, page, lib, header, print.

`lib` is filled when some def/*-doc.def exports the name (basename of
the def file); `header` is filled from a "Header:" requirements row on
the page when present.

Usage: python3 tools/absent-prints.py <corpus-clone>
"""
import html
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PRE = re.compile(r"<pre[^>]*>(.*?)</pre>", re.S)


def main():
    corpus = sys.argv[1]
    # absent names
    absent = set()
    with open(os.path.join(ROOT, "docs", "surface-audit.tsv"),
              encoding="utf-8") as f:
        rd = f.read().splitlines()
    for ln in rd[1:]:
        c = ln.split("\t")
        if len(c) > 2 and c[2] == "absent":
            absent.add(c[0])
    print("absent names:", len(absent))

    # def exports: name -> lib
    lib_of = {}
    defdir = os.path.join(ROOT, "def")
    for fn in os.listdir(defdir):
        if not fn.endswith("-doc.def"):
            continue
        lib = fn[:-8]
        for ln in open(os.path.join(defdir, fn), encoding="utf-8",
                       errors="replace"):
            ln = ln.strip()
            if not ln or ln.startswith(";") or "=" in ln:
                continue
            nm = ln.split()[0].strip()
            lib_of.setdefault(nm, lib)

    names = sorted(absent, key=len, reverse=True)
    name_re = re.compile(
        r"\b(" + "|".join(re.escape(n) for n in names) + r")\s*\(")

    out = {}
    pages = 0
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
                pages += 1
                path = os.path.join(d, fn)
                try:
                    h = open(path, encoding="utf-8",
                             errors="replace").read()
                except OSError:
                    continue
                if not name_re.search(h):
                    continue
                hdr = ""
                mh = re.search(r"Header:</[^>]+>\s*<[^>]+>([\w.]+\.h)", h)
                if mh:
                    hdr = mh.group(1)
                pid = re.sub(r"\(v=[a-z0-9.]+\)$", "", fn[:-5])
                for blk in PRE.findall(h):
                    t = html.unescape(re.sub(r"<[^>]+>", " ", blk))
                    t = re.sub(r"\s+", " ", t).strip()
                    if len(t) > 500 or "(" not in t:
                        continue
                    for m in name_re.finditer(t):
                        nm = m.group(1)
                        if nm in out:
                            continue
                        # statement = after previous ';' up to next ';'
                        st = t.rfind(";", 0, m.start()) + 1
                        en = t.find(";", m.end())
                        seg = t[st:en if en >= 0 else len(t)]
                        seg = seg.strip().rstrip(";").strip()
                        pre = t[st:m.start()].strip()
                        if not seg or not re.match(
                                r"^[A-Za-z_][\w \t\*]*$", pre):
                            continue
                        page = (pid + "(" + fn[len(pid):-5] + ")"
                                if fn[:-5] != pid else pid)
                        out[nm] = (page, lib_of.get(nm, "-"),
                                   hdr or "-", seg)
    print("pages scanned:", pages, "prints found:", len(out))

    date = "2026-09-18"
    dest = os.path.join(ROOT, "docs", f"absent-funcprints-{date}.tsv")
    with open(dest, "w", encoding="utf-8") as f:
        f.write("# name\tpage\tlib\theader\tprint\n")
        for nm in sorted(out):
            pg, lib, hdr, seg = out[nm]
            f.write(f"{nm}\t{pg}\t{lib}\t{hdr}\t{seg}\n")
    print("wrote", dest)


if __name__ == "__main__":
    main()
