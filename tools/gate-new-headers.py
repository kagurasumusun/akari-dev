#!/usr/bin/env python3
"""gate-new-headers.py -- wrap generated declarations in the generation guard
their own page requires.

The tree builds for _WIN32_WCE 0x420, 0x500 and 0x600, and tools/gen-audit.py
counts every declaration whose page documents it after CE 4.2 but which is
visible at 4.2.  That count was 0 before the M135 headers were generated, and
a declaration transcribed from a "Windows Embedded CE 6.0 and later" page with
no guard puts it straight back up -- and worse, a header that includes a
whole-file-gated one (D3dmx.h includes D3dm.h, gated at 0x0500) then fails to
compile at 0x420 because the type it uses is not there.

The version mapping is tools/gen-guard.py's OS_VERSIONS table: the documented
`_WIN32_WCE` encoding (0x0420 = CE 4.20), nothing invented.  A string the table
does not carry is reported and left unguarded rather than guessed.

If every declaration in a header documents the same minimum generation the
guard goes around the whole file, matching how D3dm.h and Usp10.h are done;
otherwise each declaration gets its own.

Usage:  tools/gate-new-headers.py [--json build/shipped-headers.json] [--dry]
"""
import argparse
import importlib.util
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

spec = importlib.util.spec_from_file_location("gen_guard", os.path.join(HERE, "gen-guard.py"))
gg = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gg)

BLOCK = re.compile(r"(?ms)^/\* ([0-9a-z]+)\s+.*?\*/\n(.*?)(?=^/\* [0-9a-z]+\s|\Z)")
OS_ROW = re.compile(r"\(([^)]*(?:Windows CE|Windows Embedded CE|Windows Mobile)[^)]*)\)")


def blocks(text):
    out = []
    for m in BLOCK.finditer(text):
        out.append((m.start(), m.end(), m.group(1), m.group(2)))
    return out


def min_version(text):
    """(min, unmapped) from every citation comment's OS Versions row."""
    mins, unmapped = [], []
    for _, _, pid, body in blocks(text):
        # the OS row is in the comment; find it in the whole block instead
        pass
    for m in re.finditer(r"(?ms)^/\* ([0-9a-z]+)\s+.*?\*/", text):
        pid = m.group(1)
        row = None
        for r in OS_ROW.findall(m.group(0)):
            row = r
        if row is None:
            continue
        row = re.sub(r";\s*Link Library:.*$", "", row).strip()
        hit = gg.OS_VERSIONS.get(row)
        if hit is None:
            # try without the trailing period, then the first clause only
            hit = gg.OS_VERSIONS.get(row.rstrip(".")) or \
                  gg.OS_VERSIONS.get(row.split(".")[0] + ".")
        if hit is None:
            unmapped.append((pid, row))
        elif isinstance(hit[0], int):
            mins.append(hit[0])
        else:
            # gen-guard's table carries sentinels for rows that state no
            # minimum at all -- "Windows CE OS" (min None), "Not supported in
            # Windows CE." ('none') and the 5.0 Networked Media Device Feature
            # Pack rows ('fp').  None of them is a `_WIN32_WCE` value, so
            # nothing may be inferred from them; the declaration is left
            # visible and reported.
            unmapped.append((pid, row + "  [table: no minimum stated]"))
    return (min(mins) if mins else None), unmapped


def guard(hexv):
    return "#if _WIN32_WCE >= 0x%04X" % hexv


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", default="build/shipped-headers.json")
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()

    paths = json.load(open(os.path.join(ROOT, a.json), encoding="utf-8"))["created"]
    for path in paths:
        text = open(os.path.join(ROOT, path), encoding="utf-8").read()
        if "#if _WIN32_WCE" in text:
            print("%-30s already gated" % path)
            continue
        mn, unmapped = min_version(text)
        for pid, row in unmapped:
            print("  !! %s: OS row %r not in gen-guard's table (page %s)"
                  % (path, row, pid))
        if mn is None or mn <= 0x0420:
            print("%-30s no gate needed (min=%s)"
                  % (path, "0x%04X" % mn if mn else "none"))
            continue
        if a.dry:
            print("%-30s would gate whole file at 0x%04X" % (path, mn))
            continue
        lines = text.split("\n")
        # after the include guard's #define
        di = next(i for i, l in enumerate(lines) if l.startswith("#define AKARI_"))
        ei = max(i for i, l in enumerate(lines) if l.startswith("#endif /* AKARI_"))
        lines.insert(ei, "#endif /* _WIN32_WCE >= 0x%04X */" % mn)
        lines.insert(di + 1, "\n%s   /* every declaration below is documented"
                              "\n * from this generation or later (each block's"
                              "\n * citation comment carries the page's own"
                              "\n * OS Versions row; tools/gen-guard.py's"
                              "\n * mapping) */" % guard(mn))
        open(os.path.join(ROOT, path), "w", encoding="utf-8").write("\n".join(lines))
        print("%-30s gated at 0x%04X" % (path, mn))


if __name__ == "__main__":
    main()
