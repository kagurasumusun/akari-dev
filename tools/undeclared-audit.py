#!/usr/bin/env python3
"""undeclared-audit.py -- documented app-layer exports this tree does not declare.

The old "357 undeclared" figure could not be rebuilt from repo data: it was
measured against an app-layer export list, and docs/generation-map.tsv has no
Library column, so "app-layer export" was undefinable.  Three attempts gave
1,277, 746 and 132 -- none of them the 357 -- and the population was declared
blocked pending a corpus re-fetch.

That fetch has happened (tools/ce-corpus.py import), and the Requirements
block of every preserved page carries both the header and the link library.
So the population is now derived from two independent primary sources that
have to agree:

  1. the page's Requirements block -- `Header:` names a header this tree
     ships, and `Link Library:` names a library (a name with no link library
     is a type, a constant or a developer-implemented callback, not an
     import the tree owes);
  2. def/*-doc.def -- the doc-derived export lists, which are what a CE
     image actually exports.  A name exported there but declared nowhere is
     a link that can succeed while no consumer can call it.

Only names in both are reported.  Output is a TSV work list plus a summary.

Usage:
    tools/undeclared-audit.py [--map docs/page-requirements.tsv]
                              [--json build/undeclared.json] [--tsv OUT]
"""
import argparse
import collections
import glob
import importlib.util
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def load_placement():
    spec = importlib.util.spec_from_file_location(
        "placement_audit", os.path.join(HERE, "placement-audit.py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def bylow_headers():
    out = {}
    for dp, _, fs in os.walk(os.path.join(ROOT, "include")):
        for f in fs:
            if f.endswith((".h", ".hxx")):
                out.setdefault(f.lower(), os.path.normpath(os.path.join(dp, f)))
    return out


def def_exports():
    """name -> sorted list of def files that export it."""
    out = collections.defaultdict(set)
    for p in sorted(glob.glob(os.path.join(ROOT, "def", "*.def"))):
        base = os.path.basename(p)
        for line in open(p, encoding="utf-8", errors="replace"):
            s = line.strip()
            if not s or s.startswith((";", "#", "LIBRARY", "EXPORTS", "VERSION")):
                continue
            m = re.match(r"([A-Za-z_][A-Za-z0-9_]*)\b", s)
            if m:
                out[m.group(1)].add(base)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--map", default="docs/page-requirements.tsv")
    ap.add_argument("--json", default="build/undeclared.json")
    ap.add_argument("--tsv", default="docs/undeclared-exports.tsv")
    ap.add_argument("--skip-types", action="store_true", default=True,
                    help="require a Link Library (default on)")
    a = ap.parse_args()

    pa = load_placement()
    idx = pa.tree_index()
    bylow = bylow_headers()
    defs = def_exports()
    declared = set(idx)

    rows = []
    seen = set()
    for line in open(a.map, encoding="utf-8"):
        f = line.rstrip("\n").split("\t")
        if len(f) < 5:
            continue
        api, osv, page, hdrs, libs = f[0], f[1], f[2], f[3], f[4]
        if not api or api in seen:
            continue
        seen.add(api)
        if api in declared:
            continue                        # the tree declares it
        if a.skip_types and not libs.strip(";"):
            continue                        # type / constant / callback
        hlist = [h for h in hdrs.split(";") if h]
        shipped = [h for h in hlist if h.lower() in bylow]
        if not shipped:
            continue                        # documented in a header we do not ship
        inexp = sorted(defs.get(api, ()))
        rows.append({
            "name": api, "page": page.replace(".html", ""),
            "os": osv, "header": shipped[0],
            "all_headers": shipped, "lib": libs, "exported_by": inexp,
        })

    both = [r for r in rows if r["exported_by"]]
    only_page = [r for r in rows if not r["exported_by"]]

    byh = collections.Counter(r["header"] for r in both)
    print("documented with a link library, header shipped, not declared: %d"
          % len(rows))
    print("  ...of those, also exported by a def/*-doc.def: %d  <-- work list"
          % len(both))
    print("  ...documented but exported by no def: %d (reported, not actioned)"
          % len(only_page))
    print("\nwork list by documented header:")
    for h, c in byh.most_common(30):
        print("   %-28s %4d" % (h, c))

    os.makedirs(os.path.dirname(a.json) or ".", exist_ok=True)
    json.dump({"work": both, "documented_only": only_page},
              open(a.json, "w", encoding="utf-8"), indent=1)
    with open(a.tsv, "w", encoding="utf-8") as fh:
        fh.write("name\tpage\tos_versions\theader\tlink_library\texported_by\n")
        for r in sorted(both, key=lambda r: (r["header"], r["name"])):
            fh.write("\t".join([r["name"], r["page"], r["os"], r["header"],
                                r["lib"], ",".join(r["exported_by"])]) + "\n")
    print("\nwrote %s and %s" % (a.json, a.tsv))


if __name__ == "__main__":
    main()
