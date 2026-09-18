#!/usr/bin/env python3
"""const-index.py -- index constant prints across the whole corpus.

Scans every page and records NAME -> (page, value) for the two print
forms the CE archive uses:  "NAME = 0xVALUE" (constants tables) and
table rows where the NAME occupies one cell and another cell carries
the value (0x form, bare 8-digit hex, or a lone integer).

Only names listed in --names (a file with one constant name per line)
are recorded, which keeps the index small and the scan fast.

Usage:
    python3 tools/const-index.py <corpus> --names /tmp/names.txt \
        [--out build/const-page-index.tsv]
"""
import html
import os
import re
import sys

ASSIGN = None          # compiled per run
CELLNAME = re.compile(r"^[A-Z_][A-Z0-9_]{1,63}$")


def scan_page(path, names, out):
    pid = re.sub(r"\(v=[a-z0-9.]+\)$", "", os.path.basename(path)[:-5])
    try:
        raw = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return
    txt = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", raw)))
    seen = set()
    for m in ASSIGN.finditer(txt):
        n, v = m.group(1), m.group(2)
        if n in names and (n, pid) not in seen:
            seen.add((n, pid))
            out.append((n, pid, v, "assign"))
    for tr in re.findall(r"<tr[^>]*>(.*?)</tr>", raw, re.S):
        cells = [re.sub(r"\s+", " ", html.unescape(
            re.sub(r"<[^>]+>", "", c))).strip()
            for c in re.findall(r"<t[dh][^>]*>(.*?)</t[dh]>", tr, re.S)]
        cellnames = [c for c in cells if c in names]
        if not cellnames:
            continue
        hexes = [c for c in cells if re.fullmatch(r"0[xX][0-9A-Fa-f]+", c)]
        bare8 = [c for c in cells if re.fullmatch(r"[0-9A-Fa-f]{8}", c)]
        ints = [c for c in cells if re.fullmatch(r"\d+", c)]
        if hexes:
            v, form = hexes[0], "cell-hex"
        elif bare8:
            v, form = bare8[0], "cell-bare8"
        elif len(ints) == 1:
            v, form = ints[0], "cell-int"
        else:
            continue
        for n in cellnames:
            if (n, pid) not in seen:
                seen.add((n, pid))
                out.append((n, pid, v, form))


def main():
    corpus = sys.argv[1]
    names = set()
    out = "build/const-page-index.tsv"
    a = sys.argv[2:]
    while a:
        if a[0] == "--names":
            names = {l.strip() for l in open(a[1]) if l.strip()}
            a = a[2:]
        elif a[0] == "--out":
            out = a[1]
            a = a[2:]
        else:
            a = a[1:]
    global ASSIGN
    ASSIGN = re.compile(
        r"\b([A-Z_][A-Z0-9_]{1,63})\s*=\s*(0[xX][0-9A-Fa-f]+[LlUu]*|\d+[LlUu]*)"
        r"(?![A-Za-z0-9_])")
    rows = []
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
                scan_page(os.path.join(d, fn), names, rows)
    os.makedirs(os.path.dirname(os.path.join(os.getcwd(), out)) or ".",
                exist_ok=True)
    with open(out, "w") as f:
        f.write("# name\tpage\tvalue\tform\n")
        for r in sorted(rows):
            f.write("\t".join(r) + "\n")
    covered = len({r[0] for r in rows})
    print("scanned", npages, "pages;", len(rows), "prints;",
          covered, "of", len(names), "names covered ->", out)


if __name__ == "__main__":
    main()
