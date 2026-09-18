#!/usr/bin/env python3
"""gen-app-defs.py -- generate def/<lib>-doc.def for app-layer link
libraries that the corpus documents but the tree has not shipped.

Evidence rule (same policy as gen-doc-def.py / touchgesture-doc.def):
a name enters a def only when (a) an official corpus page's
Requirements row names that link library AND the page's title is that
function name, and (b) this tree declares the function with
AKARI_CE_IMPORT.  Unicode near-misses (page "Foo", tree "FooW") are
reported, never auto-adopted.

Usage: python3 tools/gen-app-defs.py <corpus-clone> [--libs a,b,c]
       [--dry]
"""
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


dc = _load("dc", "declare-from-corpus.py")
pa = _load("pa", "proto-audit.py")

APPS = ["av_upnp", "cellcore", "commctrlview", "gpsapi", "imaging",
        "mqelib", "mqoa", "owaexchangeclient", "shdocvw", "sms",
        "wap", "wsdapi"]

TITLE = re.compile(r"<title>(.*?)\s*\(", re.S)


def main():
    corpus = sys.argv[1]
    dry = "--dry" in sys.argv
    libs = APPS
    for a in sys.argv:
        if a.startswith("--libs="):
            libs = a.split("=", 1)[1].split(",")
    libset = {l.lower() for l in libs}

    # declared function names in the tree
    declared = set()
    for dirpath in ("include",):
        d = os.path.join(ROOT, dirpath)
        for fn in sorted(os.listdir(d)):
            if not fn.endswith((".h", ".hpp", ".hxx")):
                continue
            s = open(os.path.join(d, fn), encoding="utf-8",
                     errors="replace").read()
            for m in pa.DECL.finditer(pa.strip_comments(s)):
                declared.add(m.group(2))
    print("declared functions:", len(declared))

    # pass: page title -> libs named in Requirements
    per_lib = {l: {} for l in libset}          # lib -> name -> pid
    npages = 0
    for p, dirs, files in os.walk(os.path.join(corpus, "docs")):
        dirs[:] = [x for x in dirs if x != ".git"]
        for fn in sorted(files):
            if not fn.endswith(".html"):
                continue
            npages += 1
            path = os.path.join(p, fn)
            try:
                raw = open(path, encoding="utf-8",
                           errors="replace").read()
            except OSError:
                continue
            _, lib = dc.requirements(raw)
            if not lib:
                continue
            toks = {re.sub(r"\.lib$", "", t.strip().strip(".").lower())
                    for t in re.split(r"[,;]| and ", lib)}
            hit = toks & libset
            if not hit:
                continue
            mt = TITLE.search(raw)
            if not mt:
                continue
            name = mt.group(1).strip()
            if not re.fullmatch(r"[A-Za-z_]\w*", name):
                continue
            pid = re.sub(r"\(v=[a-z0-9.]+\)$", "", fn[:-5])
            for l in hit:
                per_lib[l].setdefault(name, pid)
    print("pages scanned:", npages)

    total = 0
    for l in sorted(libset):
        names = per_lib[l]
        exports = sorted(n for n in names if n in declared)
        near = sorted(n for n in names
                      if n not in declared and (n + "W") in declared)
        print(f"{l}: documented {len(names)}, declared+documented "
              f"{len(exports)}, unicode near-miss {len(near)}")
        if near:
            print("   near:", ", ".join(near[:8]))
        if not exports:
            continue
        total += len(exports)
        if dry:
            continue
        dest = os.path.join(ROOT, "def", f"{l}-doc.def")
        with open(dest, "w", encoding="utf-8") as f:
            f.write(f"; {l}-doc.def -- {l}.lib export surface for "
                    f"Windows CE.\n;\n"
                    "; Copyright (c) 2026 Akari API contributors\n"
                    "; SPDX-License-Identifier: MIT\n;\n"
                    "; Derived exclusively from the official Microsoft CE\n"
                    "; documentation pages: each name below appears as a\n"
                    "; page title whose Requirements row names this link\n"
                    "; library (wince-docs-corpus) and is declared with\n"
                    "; AKARI_CE_IMPORT by this tree's headers.  No\n"
                    "; shared-source/device-dump/VS/PB-derived name is\n"
                    "; used.  Ordinals are not published; entries are\n"
                    "; name-only.\n"
                    f"LIBRARY {l}.dll\nEXPORTS\n")
            for n in exports:
                f.write(f"  {n}\n")
        print("   wrote", dest)
    print("total exports:", total)


if __name__ == "__main__":
    main()
