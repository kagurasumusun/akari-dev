#!/usr/bin/env python3
"""const-cite.py -- attach inline page citations to #define constants
whose value the corpus verifiably prints.

Input: docs/const-audit-2026-09-18.tsv (gap rows) and the corpus-wide
print index from tools/const-index.py.  A citation is only attached
when some page prints the SAME numeric value (32-bit canonical) --
never to "fix" a citation onto a differing value; those are reported
for manual triage instead.

Usage:
    python3 tools/const-cite.py [--dry]
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUDIT = "docs/const-audit-2026-09-18.tsv"
INDEX = "build/const-page-index.tsv"
DEF = re.compile(r"^(#define\s+([A-Z_][A-Z0-9_]*)\s+"
                 r"(0[xX][0-9A-Fa-f]+|[0-9]+)\s*[LlUu]*\s*)"
                 r"(?:/\*(.*?)\*/)?\s*$")
GAPS = ("no-pageid", "name-not-on-page", "name-no-value-on-page")


def parse_value(s):
    try:
        return int(s, 0)
    except ValueError:
        try:
            return int(s, 16)          # bare hex cell
        except ValueError:
            return None


def main():
    dry = "--dry" in sys.argv
    # gap list: (header, name)
    gaps = set()
    for line in open(os.path.join(ROOT, AUDIT), encoding="utf-8"):
        f = line.rstrip("\n").split("\t")
        if len(f) >= 4 and f[3] in GAPS:
            gaps.add((f[0], f[1]))
    # index: name -> [(pid, value)]
    idx = {}
    for line in open(os.path.join(ROOT, INDEX), encoding="utf-8"):
        if line.startswith("#"):
            continue
        f = line.rstrip("\n").split("\t")
        if len(f) < 4:
            continue
        v = parse_value(f[2].rstrip("LlUu"))
        if v is not None:
            idx.setdefault(f[0], []).append((f[1], v, f[3]))
    cited = differs = noprint = already = 0
    per_file = {}
    report = []
    by_hdr = {}
    for hdr, name in gaps:
        by_hdr.setdefault(hdr, set()).add(name)
    for hdr in sorted(by_hdr):
        path = os.path.join(ROOT, hdr)
        lines = open(path, encoding="utf-8").read().splitlines(keepends=True)
        changed = False
        for i, line in enumerate(lines):
            m = DEF.match(line.rstrip("\n"))
            if not m or m.group(2) not in by_hdr[hdr]:
                continue
            name = m.group(2)
            val = parse_value(m.group(3))
            entries = idx.get(name, [])
            same = [(p, v, fm) for p, v, fm in entries
                    if (v & 0xFFFFFFFF) == (val & 0xFFFFFFFF)]
            if same:
                pid = same[0][0]
                if m.group(4) and pid in m.group(4):
                    already += 1
                    by_hdr[hdr].discard(name)
                    continue
                if m.group(4):
                    lines[i] = "%s/* %s %s */\n" % (
                        m.group(1), pid, m.group(4).strip())
                else:
                    lines[i] = "%s/* %s */\n" % (m.group(1), pid)
                changed = True
                cited += 1
                per_file[hdr] = per_file.get(hdr, 0) + 1
                by_hdr[hdr].discard(name)
            elif entries:
                differs += 1
                report.append("%s\t%s\thdr=%s\t%s" % (
                    hdr, name, m.group(3),
                    "; ".join("%s:%s" % (p, hex(v)) for p, v, _ in entries)))
                by_hdr[hdr].discard(name)
        if changed and not dry:
            open(path, "w", encoding="utf-8").writelines(lines)
    noprint = sum(len(v) for v in by_hdr.values())
    print(("DRY " if dry else "") +
          "cited=%d differs=%d no-print-anywhere=%d already=%d"
          % (cited, differs, noprint, already))
    for hdr, n in sorted(per_file.items()):
        print("  %-28s +%d citations" % (hdr, n))
    if report:
        rp = os.path.join(ROOT, "docs/const-cite-conflicts.tsv")
        with open(rp, "w") as f:
            f.write("\n".join(report) + "\n")
        print("conflicts ->", rp)


if __name__ == "__main__":
    main()
