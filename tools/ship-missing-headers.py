#!/usr/bin/env python3
"""ship-missing-headers.py -- create the headers the CE pages name but this
tree does not ship, and fill them from those pages.

tools/coverage-audit.py reports a "header not shipped here" bucket: pages
whose Requirements row names a header that include/ does not contain.  The
audit can name the gap but nothing acted on it, because declaring a name
needs a file to declare it in.  This closes that loop.

For every documented header that is app-layer (not in coverage-audit's OEM
set and not a C runtime header), it

  1. creates include/<Header>.h with the tree's usual banner and guard if
     the file does not exist,
  2. runs tools/decl-types-from-pages.py over the group's type pages, then
     tools/decl-from-pages.py over the group's function pages -- types
     first, so a function whose parameter is a struct from the same header
     resolves in the same pass,
  3. repeats until nothing new is declared, and
  4. deletes any header it created that ended up empty.

Nothing is transcribed that the two declaration tools accept; the tools
report and skip anything whose constituent types the tree does not already
declare, so a fixpoint pass is what unblocks the dependent definitions.

Usage:  tools/ship-missing-headers.py [--json build/coverage.json]
                                      [--passes 3] [--dry]
"""
import argparse
import collections
import importlib.util
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def load(name):
    spec = importlib.util.spec_from_file_location(name, os.path.join(HERE, name + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


BANNER = """/*
 * {file} -- {title}
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: {doc}".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef {guard}
#define {guard}

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {{
#endif

#ifdef __cplusplus
}}
#endif

#endif /* {guard} */
"""


def declared_in(path):
    """Identifiers the header already declares, so a pass cannot repeat them."""
    try:
        s = open(os.path.join(ROOT, path), encoding="utf-8").read()
    except OSError:
        return set()
    out = set()
    for m in re.finditer(r"\}\s*([^;{}()]*);", s):
        for part in m.group(1).split(","):
            ids = re.findall(r"[A-Za-z_]\w*", part)
            if ids:
                out.add(ids[-1])
    out |= set(re.findall(r"^#define\s+([A-Za-z_]\w*)", s, re.M))
    out |= set(re.findall(r"AKARI_CE_NAME\(([A-Za-z_]\w*)\)", s))
    out |= set(re.findall(r"^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*\{", s, re.M))
    return out


def duplicates_in(path):
    """Names the header declares more than once."""
    s = open(os.path.join(ROOT, path), encoding="utf-8").read()
    s = re.sub(r"(?s)/\*.*?\*/", " ", s)          # citation comments name things too
    names = []
    names += re.findall(r"AKARI_CE_NAME\(([A-Za-z_]\w*)\)", s)
    names += re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)", s, re.M)
    names += re.findall(r"^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*\{", s, re.M)
    for m in re.finditer(r"\}\s*([^;{}()]*);", s):
        # the `}` that closes `extern "C" {` is followed by #endif and then
        # the first declaration, and this scan read that as a declarator list
        # (it reported RAPIDEVICEID twice).  A real declarator list never
        # contains a preprocessor directive.
        if "#" in m.group(1):
            continue
        for part in m.group(1).split(","):
            ids = re.findall(r"[A-Za-z_]\w*", part)
            if ids:
                names.append(ids[-1])
    # only single-line typedef aliases; a multi-line pattern matched member
    # lines as well and reported RAPIDEVICEID (a struct member) as a
    # duplicate of its own typedef.
    for line in s.split("\n"):
        m = re.match(r"^\s*typedef\s+[^;{}()]*?\b([A-Za-z_]\w*)\s*;", line)
        if m:
            names.append(m.group(1))
    seen, dup = set(), set()
    for n in names:
        if n in seen:
            dup.add(n)
        seen.add(n)
    return dup


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", default="build/coverage.json")
    ap.add_argument("--passes", type=int, default=3)
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()

    ca = load("coverage-audit")
    cov = json.load(open(os.path.join(ROOT, a.json), encoding="utf-8"))
    recs = cov["header_not_shipped"] + cov["app_layer_gaps"]

    shipped = ca.shipped_headers()
    groups = collections.defaultdict(list)
    for r in recs:
        h = (r.get("header") or "").strip()
        if not h:
            continue
        low = h.lower()
        if low in ca.OEM or low in ca.CRT:
            continue
        if low in shipped:
            continue
        if not re.match(r"^[A-Za-z_]\w*\.h(xx|pp)?$", h):
            continue
        groups[h].append(r)

    print("app-layer documented headers not shipped: %d (%d pages)"
          % (len(groups), sum(len(v) for v in groups.values())))

    os.makedirs(os.path.join(ROOT, "build", "shipped"), exist_ok=True)
    created, filled, empty = [], {}, []
    for doc, rs in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        base = os.path.basename(doc)
        stem = re.sub(r"\.h(xx|pp)?$", "", base)
        fname = stem[:1].upper() + stem[1:] + ".h"
        path = os.path.join("include", fname)
        made = False
        if not os.path.exists(os.path.join(ROOT, path)):
            if a.dry:
                print("  [dry] would create %s (%d pages)" % (path, len(rs)))
                continue
            guard = "AKARI_" + re.sub(r"[^A-Za-z0-9]", "_", stem).upper() + "_H"
            open(os.path.join(ROOT, path), "w", encoding="utf-8").write(
                BANNER.format(file=fname, doc=doc, guard=guard,
                              title="Windows CE book-surface header of record (Akari API)"))
            created.append(path)
            made = True

        tj = os.path.join(ROOT, "build", "shipped", stem + "-types.json")
        fj = os.path.join(ROOT, "build", "shipped", stem + "-funcs.json")
        # M135: every page goes to both transcribers.  Splitting them by
        # "does the page print a Link Library" sent the sms.h and tsp.h
        # enum pages -- which do print one -- to the function transcriber,
        # where they were rejected as "page has no prototype block", and the
        # headers that use those enums then failed to compile.  Each tool
        # rejects what it cannot handle, so offering both costs nothing.
        allj = [{"name": r["api"], "page": r["page"], "os": r["os"],
                 "lib": r.get("lib", "")} for r in rs]
        types = funcs = allj
        json.dump(types, open(tj, "w"), indent=1)
        json.dump(funcs, open(fj, "w"), indent=1)

        total = 0
        tjobs, fjobs = types, funcs
        for _ in range(a.passes):
            if a.dry:
                break
            # M135: a fixpoint pass must not re-declare what the previous
            # pass already wrote.  Re-running the same job list produced
            # three copies of every definition (Extapi.h came out with each
            # name three times), so each pass starts by dropping the names
            # the header already carries.
            have = declared_in(path)
            tjobs = [j for j in tjobs if j["name"] not in have]
            fjobs = [j for j in fjobs if j["name"] not in have]
            before = total
            for jobs, jpath, tool in ((tjobs, tj, "decl-types-from-pages"),
                                      (fjobs, fj, "decl-from-pages")):
                if not jobs:
                    continue
                json.dump(jobs, open(jpath, "w"), indent=1)
                r = subprocess.run([sys.executable, os.path.join(HERE, tool + ".py"),
                                    "--list", jpath, "--cache", "build/pagecache",
                                    "--write", "--header", path],
                                   capture_output=True, text=True, cwd=ROOT)
                m = re.search(r"^(\d+) declared", r.stdout, re.M)
                if m:
                    total += int(m.group(1))
                if r.returncode != 0:
                    print("  !! %s on %s: %s" % (tool, path, r.stdout[-200:]))
            if total == before:
                break
        dup = duplicates_in(path)
        if dup:
            print("  !! %s still has %d duplicated names: %s"
                  % (path, len(dup), ", ".join(sorted(dup)[:4])))
        filled[path] = total
        if made and total == 0:
            os.remove(os.path.join(ROOT, path))
            empty.append(path)
            created.remove(path)

    print("\ncreated %d headers, removed %d that stayed empty" % (len(created), len(empty)))
    for p, n in sorted(filled.items(), key=lambda kv: -kv[1]):
        if n:
            print("  %-30s %3d declarations" % (p, n))
    print("total declarations written: %d" % sum(filled.values()))
    json.dump({"created": created, "filled": filled, "removed": empty},
              open(os.path.join(ROOT, "build", "shipped-headers.json"), "w"), indent=1)


if __name__ == "__main__":
    main()
