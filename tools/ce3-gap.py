#!/usr/bin/env python3
"""
ce3-gap.py -- cross-reference the official CE 1/2/3 API surface
(docs/ce3-versions.tsv, from the Windows CE 3.0 documentation archive)
against the headers currently shipped in include/, and emit a gap table.

For every CE 3.0 page that carries a "Versions: N and later" row we take
the bare API name (page title minus the "(Windows CE ...)" / "(RAPI)" /
"(Windows Sockets)" disambiguation suffix) and test whether that
identifier is declared in any include/ header.  Result columns:

    name, min_ce, versions, header, lib, in_include (0/1), where (headers)

This is the implementation-side gap report for "collect CE 1/2/3
exhaustively": it shows which CE 1.0/2.x/3.0 APIs are already carried by
the tree and which are not yet implemented.

Usage:  python3 tools/ce3-gap.py docs/ce3-versions.tsv docs/ce3-gap.tsv
"""

import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def bare_name(title):
    t = title.strip()
    # strip trailing parenthetical disambiguations
    t = re.sub(r"\s*\([^)]*\)\s*$", "", t)
    t = t.strip()
    if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", t):
        return ""
    return t


def load_headers(incdir):
    text = ""
    for fn in sorted(os.listdir(incdir)):
        p = os.path.join(incdir, fn)
        if os.path.isfile(p):
            with open(p, encoding="utf-8", errors="replace") as fh:
                text += "\n" + fh.read()
    # one pass: identifier set (membership heuristic, not the authoritative
    # inventory -- that lives in docs/inventory.md + per-header citations)
    return set(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]{2,}\b", text))


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    src, dst = sys.argv[1], sys.argv[2]
    incdir = os.path.join(ROOT, "include")
    idents = load_headers(incdir)
    rows = []
    with open(src, encoding="utf-8") as fh:
        lines = fh.read().splitlines()
    for line in lines[1:]:
        if not line.strip():
            continue
        parts = line.split("\t")
        if len(parts) < 5:
            continue
        cid, title, min_ce, versions, header, lib = parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]
        os_ = parts[6] if len(parts) > 6 else ""
        name = bare_name(title)
        if not name:
            continue
        found = name in idents
        rows.append((name, min_ce, versions, header, lib, found))

    covered = sum(1 for r in rows if r[5])
    missing = [r for r in rows if not r[5]]
    with open(dst, "w", encoding="utf-8") as fh:
        fh.write("name\tmin_ce\tversions\theader\tlib\tin_include\n")
        for name, mc, v, h, l, found in sorted(rows, key=lambda r: (r[0].lower(), r[1])):
            fh.write(f"{name}\t{mc}\t{v}\t{h}\t{l}\t{1 if found else 0}\n")

    print(f"rows (named, with Versions): {len(rows)}")
    print(f"covered in include/: {covered}")
    print(f"missing from include/: {len(missing)}")
    from collections import Counter
    print("missing by min_ce:", dict(Counter(r[1] for r in missing)))
    print("missing by header (top 20):")
    for h, c in Counter(r[3] for r in missing).most_common(20):
        print(f"   {c:5d}  {h}")


if __name__ == "__main__":
    main()
