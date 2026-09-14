#!/usr/bin/env python3
"""
decl-retest.py -- re-test every "record-only / held" print carried in
include/ comment blocks.  When the types that blocked a recorded
prototype/definition are now declared live, declare it in place,
citing the same page.  Nothing is invented: only the prints already
recorded verbatim in the tree are used.

Dry-run:  python3 tools/decl-retest.py <corpus> --dry
Apply:    python3 tools/decl-retest.py <corpus>
"""

import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import importlib

d1 = importlib.import_module("decl-d1") if False else None


def _load(modname):
    import importlib.util
    here = os.path.dirname(os.path.abspath(__file__))
    spec = importlib.util.spec_from_file_location(
        modname, os.path.join(here, modname + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


PRINT_RE = re.compile(
    r"/\*\s*([A-Za-z0-9_.]+)\s+([A-Za-z_][A-Za-z0-9_]*)\s*:\s*print\s+"
    r"`([^`]*)`", re.S)
PRINT_RE2 = re.compile(
    r"/\*\s*\"([A-Za-z_][A-Za-z0-9_]*)\"\s*\(([A-Za-z0-9_.]+)\)\s*:\s*"
    r"`([^`]*)`", re.S)


def main():
    d1 = _load("decl-d1")
    dt = _load("decl-types")
    corpus = sys.argv[1]
    apply = "--dry" not in sys.argv
    incdir = os.path.join(d1.ROOT, "include")
    live = d1.load_live(incdir)
    res = d1.Resolver(live, d1.load_types(incdir))
    ctx = dt.Ctx(dt.load_code(incdir))
    surf = set()
    for fn in ("coredll4.def", "coredll.def", "coredll6.def",
               "coredll6-x86.def"):
        p = os.path.join(corpus, "coredll", fn)
        if os.path.exists(p):
            surf |= d1.def_names(p)
    libmap = {}
    for fn in ("rows.json", "rows4.json", "rows3.json"):
        p = os.path.join(corpus, fn)
        if not os.path.exists(p):
            continue
        for r in json.load(open(p, encoding="utf-8")):
            libmap.setdefault(r.get("title", "").strip(),
                              (r.get("lib") or ""))

    stats = {"retested": 0, "now-live": 0, "declared": 0,
             "still-blocked": 0}
    for fn in sorted(os.listdir(incdir)):
        if not fn.endswith((".h", ".hxx", ".hpp")):
            continue
        path = os.path.join(incdir, fn)
        text = open(path, encoding="utf-8").read()
        inserts = []   # (offset_after_comment, decl_lines)
        seen_spans = set()
        for rex, swap in ((PRINT_RE, False), (PRINT_RE2, True)):
            for m in rex.finditer(text):
                if swap:
                    name, cite, sig = m.group(1), m.group(2), m.group(3)
                else:
                    cite, name, sig = m.group(1), m.group(2), m.group(3)
                if m.span() in seen_spans:
                    continue
                seen_spans.add(m.span())
                if name in live:
                    stats["now-live"] += 1
                    continue
                # don't double-declare on a later pass
                end = text.find("*/", m.end())
                if end < 0:
                    continue
                after = text[end + 2:end + 400]
                if re.search(r"\b" + re.escape(name) + r"\s*\(", after.split("/*")[0]) \
                        and "AKARI_CE_NAME(" + name in after.split("/*")[0]:
                    continue
                stats["retested"] += 1
                s = dt.clean(sig)
                decl = None
                if s.startswith("typedef"):
                    r3 = (dt.try_simple_typedef(s, ctx)
                          or dt.try_enum(s, ctx) or dt.try_struct(s, ctx))
                    if r3 and r3[2] == name:
                        decl = r3[1]
                elif s.startswith("#define"):
                    r3 = dt.try_define(s, ctx)
                    if r3 and r3[2] == name:
                        decl = r3[1]
                else:
                    p = d1.parse_sig(sig, res)
                    if p and p[1] == name:
                        ret, _, params = p
                        plist = ", ".join(t + ((" " + a) if a else "")
                                          for t, a in params) if params else "void"
                        lib = libmap.get(name, "").lower()
                        core = ("coredll" in lib) or (name in surf) \
                            or (name + "W" in surf)
                        if core:
                            decl = (f"AKARI_CE_IMPORT {ret} {name}({plist}) "
                                    f"AKARI_CE_NAME({name});")
                        else:
                            decl = f"{ret} {name}({plist});"
                if not decl:
                    stats["still-blocked"] += 1
                    continue
                stats["declared"] += 1
                note = (f"/* {cite} {name}: declared from the recorded print "
                        f"(tools/decl-retest.py); the former blocker type is "
                        f"now live. */\n")
                inserts.append((end + 2, note + decl + "\n"))
        if inserts and apply:
            for off, chunk in sorted(inserts, reverse=True):
                text = text[:off] + "\n" + chunk + text[off:]
            open(path, "w", encoding="utf-8").write(text)
        if inserts:
            print(f"{fn}: +{len(inserts)}")
    print(f"TOTAL: {stats}")


if __name__ == "__main__":
    main()
