#!/usr/bin/env python3
"""
tools/gen-case-vfs.py -- generate a Clang VFS overlay that resolves
lowercase #include spellings (e.g. "windows.h") to the documented-case
header files this tree actually ships (e.g. "Windows.h"), for use on
case-sensitive build hosts (Linux/etc.), WITHOUT committing any
duplicate-cased files to the repository.

Why this exists (see docs/inventory.md M76a)
---------------------------------------------
cellvm-sdk's header filenames follow the case Microsoft's own CE
documentation prints for each header (this project's stated policy).
Real-world Windows CE application source -- and eVC-era source in
particular -- was almost universally written and only ever compiled
on Windows, where NTFS/FAT are case-preserving but case-INSENSITIVE.
As a result such source freely mixes spelling, e.g. `#include
<windows.h>`, `#include <Windows.h>`, `#include <WINDOWS.H>` all doing
the same thing on a Windows box, with no way to tell from the source
alone which spelling "wins".

This repository previously (M69a-M76) tried shipping one physical
file per spelling actually seen. That broke in the other direction:
a case-INSENSITIVE checkout (an ordinary `git clone` on Windows or
macOS, i.e. exactly the platforms real CE developers use) silently
collides `windows.h` and `Windows.h` into a single file, corrupting
the tree. M76a therefore settled on exactly one committed file per
header, spelled as Microsoft's documentation prints it -- correct for
git portability, but by itself insufficient for cross-compiling real
CE application source from a case-sensitive Linux host, which is
cellvm-sdk's whole reason to exist alongside kagurasumusun/llvm-project.

This script closes that gap without reopening the M76a problem: the
mapping lives in a single generated YAML file (a Clang "VFS overlay",
-ivfsoverlay), not as files in the tree. It is regenerated from
include/ on demand and is NOT meant to be committed (see
build/.gitignore); nothing about the checkout changes, so nothing new
can collide on a case-insensitive filesystem.

Usage
-----
    python3 tools/gen-case-vfs.py [--dir include] [--dir include/oak] \\
        -o build/case-overlay.yaml

    clang -target armv5te-pc-wince6.0 -ivfsoverlay build/case-overlay.yaml \\
        -Iinclude -Iinclude/oak -c app.c

Only headers whose documented-case spelling is NOT already all-lowercase
get an alias entry (an all-lowercase header needs no alias: the
lowercase spelling a real-world #include would use already matches the
one committed file exactly, on any filesystem).

The overlay intentionally does not set "case-sensitive": false, and
does not attempt to alias every possible casing (WINDOWS.H, WinDows.H,
...) -- only the fully-lowercase spelling, since that is the
overwhelmingly dominant convention in real CE/eVC application source
and in cegcc-targeting code. A collision check aborts generation if
two committed headers under the same --dir would ever lower-case to
the same alias name (would mean the tree regressed a M76a invariant).
"""
import argparse
import json
import os
import sys

HEADER_EXTS = (".h", ".hpp", ".hxx")


def collect(dirs):
    """Return {alias_lowercase_name: absolute_real_path} across all dirs,
    aborting on any lowercase collision (within or across dirs)."""
    aliases = {}
    owners = {}
    for d in dirs:
        if not os.path.isdir(d):
            continue
        for name in sorted(os.listdir(d)):
            real_path = os.path.join(d, name)
            if not os.path.isfile(real_path):
                continue
            if not name.endswith(HEADER_EXTS):
                continue
            lower = name.lower()
            if lower == name:
                continue  # already lowercase: no alias needed
            if lower in owners and owners[lower] != real_path:
                raise SystemExit(
                    "gen-case-vfs: lowercase collision: %r and %r both "
                    "fold to %r -- this would also break a case-"
                    "insensitive checkout (M76a); refusing to generate"
                    % (owners[lower], real_path, lower)
                )
            owners[lower] = real_path
            aliases[lower] = os.path.abspath(real_path)
    return aliases


def build_overlay(dirs, aliases):
    """Group alias entries by (abs) parent directory, one VFS "root" per
    directory, matching how -I / -Iinclude/oak search paths are used."""
    by_dir = {}
    for lower, real_abs in aliases.items():
        parent = os.path.dirname(real_abs)
        by_dir.setdefault(parent, []).append((lower, real_abs))

    roots = []
    for parent in sorted(by_dir):
        contents = [
            {"name": lower, "type": "file", "external-contents": real_abs}
            for lower, real_abs in sorted(by_dir[parent])
        ]
        roots.append({"name": parent, "type": "directory", "contents": contents})

    return {
        "version": 0,
        "use-external-names": True,
        "roots": roots,
    }


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--dir", action="append", dest="dirs", default=[],
                     help="header directory to scan (repeatable); "
                          "default: include, include/oak")
    ap.add_argument("-o", "--output", default="build/case-overlay.yaml")
    args = ap.parse_args()
    dirs = args.dirs or ["include", "include/oak"]

    aliases = collect(dirs)
    overlay = build_overlay(dirs, aliases)

    os.makedirs(os.path.dirname(args.output) or ".", exist_ok=True)
    with open(args.output, "w") as f:
        # Plain JSON is valid YAML and is what Clang's VFS overlay
        # parser actually expects in practice; avoids a YAML dep.
        json.dump(overlay, f, indent=2)
        f.write("\n")

    print("gen-case-vfs: %d lowercase aliases across %d directories -> %s"
          % (len(aliases), len(dirs), args.output), file=sys.stderr)


if __name__ == "__main__":
    main()
