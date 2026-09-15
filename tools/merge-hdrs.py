#!/usr/bin/env python3
"""merge-hdrs.py -- keep Makefile's HDRS exactly equal to include/'s contents.

A header that is not in HDRS is compiled by neither `hostcheck` nor
`crosscheck`, so `make check` stays green while the header is broken -- the
failure mode that let the 33 M135 headers sit uncompilable for a whole run.
The invariant is mechanical, so enforce it mechanically: HDRS is the set of
top-level headers in include/, sorted.  include/oak/ is OAK_HDRS's business
(the OEM/BSP layer, out of scope) and is left alone.

Usage: tools/merge-hdrs.py [--check]
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    path = os.path.join(ROOT, "Makefile")
    lines = open(path, encoding="utf-8").read().split("\n")
    start = next(i for i, l in enumerate(lines) if l.startswith("HDRS = "))
    end = start
    while lines[end].rstrip().endswith("\\"):
        end += 1
    entries = []
    for l in lines[start:end + 1]:
        s = l.rstrip()
        cont = s.endswith("\\")
        s = s[:-1] if cont else s
        entries += [x for x in re.sub(r"^\s*HDRS\s*=\s*", "", s).split() if x]

    inc = os.path.join(ROOT, "include")
    disk = sorted("include/" + f for f in os.listdir(inc)
                  if f.endswith((".h", ".hpp", ".hxx")))
    added = sorted(set(disk) - set(entries))
    dropped = sorted(set(entries) - set(disk))
    if added or dropped:
        print("HDRS +%d -%d -> %d" % (len(added), len(dropped), len(disk)))
        for a in added:
            print("  +", a)
        for d in dropped:
            print("  -", d)
    else:
        print("HDRS already matches include/ (%d headers)" % len(disk))
    if "--check" in sys.argv:
        sys.exit(1 if (added or dropped) else 0)

    block = ["HDRS = \\"] + [e + (" \\" if i < len(disk) - 1 else "")
                             for i, e in enumerate(disk)]
    lines[start:end + 1] = block
    open(path, "w", encoding="utf-8").write("\n".join(lines))


if __name__ == "__main__":
    main()
