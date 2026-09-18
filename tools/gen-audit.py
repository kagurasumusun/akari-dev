#!/usr/bin/env python3
"""Audit each declaration's effective CE generation against its official one.

For every name in docs/generation-map.tsv the audit computes the
*effective* minimum generation -- the strongest `#if _WIN32_WCE >= 0xNNNN`
condition enclosing the declaration in the shipped header -- and compares
it with the generation the page's `OS Versions:` row states.

The comparison only means something against the lowest target this tree
builds, CE 4.2 (0x0420).  A name documented from CE 1.0 needs no guard
and is not a violation; an unguarded name documented from CE 5.0 is one,
because a 4.2 build sees it.  Conversely a name documented from CE 4.0
that sits behind `>= 0x0500` is hidden from a 4.2 build the pages say
should have it -- unless a type in its prototype does not exist at 4.2,
which is a dependency hold rather than a generation claim (M117).

Usage:
    tools/gen-audit.py            # report both directions
    tools/gen-audit.py --json OUT # also write the per-name detail
"""
import argparse
import collections
import csv
import json
import os
import re

LOWEST = 0x0420          # the lowest _WIN32_WCE this tree builds


def strip_keep_lines(s):
    """Blank comment text, keep line structure and string literals.

    Line structure so that `#if` tracking lines up with the original file;
    strings because blanking them destroys the target of every
    `#include "X.h"` and silently empties any include graph built from the
    result (M122).
    """
    out = []
    i, n = 0, len(s)
    while i < n:
        if s.startswith("/*", i):
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r"[^\n]", " ", s[i:j]))
            i = j
            continue
        if s.startswith("//", i):
            j = s.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * len(s[i:j]))
            i = j
            continue
        if s[i] in "\"'":
            q = s[i]
            j = i + 1
            while j < n and s[j] != q:
                j += 2 if s[j] == "\\" else 1
            j = min(j + 1, n)
            out.append(s[i:j])
            i = j
            continue
        out.append(s[i])
        i += 1
    return "".join(out)


COND = re.compile(r"_WIN32_WCE\s*(?:>=|==)\s*(0[xX][0-9A-Fa-f]+|\d+)")


def effective_min(path):
    """Per-line effective minimum _WIN32_WCE, from #if nesting."""
    lines = strip_keep_lines(
        open(path, encoding="utf-8", errors="replace").read()).split("\n")
    stack, res = [], []
    for ln in lines:
        t = ln.strip()
        if re.match(r"#\s*if(n?def)?\b", t):
            m = COND.search(t)
            stack.append(int(m.group(1), 0) if m else 0)
        elif re.match(r"#\s*(else|elif)\b", t):
            m = COND.search(t)
            if stack:
                stack[-1] = int(m.group(1), 0) if m else 0
        elif re.match(r"#\s*endif\b", t):
            if stack:
                stack.pop()
        res.append(max(stack) if stack else 0)
    return res, lines


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--map", default="docs/generation-map.tsv")
    ap.add_argument("--json")
    ap.add_argument("--exceptions", default="docs/generation-exceptions.tsv",
                    help="header<TAB>name<TAB>reason rows that a documented "
                         "4.2 API legitimately needs, so the name stays visible")
    a = ap.parse_args()

    # Rows the corpus parser mis-recorded: the "name" is the keyword that
    # introduced the construct, not a declared identifier.  There is no
    # declaration to gate, so they are counted apart from real violations.
    ARTIFACTS = {"enum", "struct", "union"}
    exc = set()
    if os.path.exists(a.exceptions):
        for r in csv.DictReader(open(a.exceptions, encoding="utf-8"), delimiter="\t"):
            if r.get("header") and r.get("name"):
                exc.add((r["header"], r["name"]))

    cache = {}
    artifacts, held = [], []
    early, late = [], []
    rows = list(csv.DictReader(open(a.map, encoding="utf-8"), delimiter="\t"))
    for r in rows:
        h, name, mn = r["header"], r["name"], r.get("min") or ""
        if not h or not name or not mn or not os.path.exists(h):
            continue
        try:
            dmin = int(mn, 0)
        except ValueError:
            continue
        if name in ARTIFACTS:
            artifacts.append((h, name, r.get("page", "")))
            continue
        if h not in cache:
            cache[h] = effective_min(h)
        eff, lines = cache[h]
        pat = re.compile(r"\b" + re.escape(name) + r"\b")
        hit = next((i for i, l in enumerate(lines)
                    if pat.search(l) and not l.strip().startswith("*")), None)
        if hit is None:
            continue
        e = eff[hit]
        rec = (h, name, dmin, e, r.get("page", ""), hit + 1)
        # A guard is only needed when the documented generation is above the
        # lowest target built; below it every supported build has the name.
        if dmin > LOWEST and e < dmin:
            if (h, name) in exc:
                held.append(rec)
            else:
                early.append(rec)
        elif e > max(dmin, LOWEST):
            late.append(rec)

    byh = collections.Counter(x[0] for x in early)
    print("documented after CE 4.2 but visible at 4.2 (unguarded): %d names in %d headers"
          % (len(early), len(byh)))
    for h, c in byh.most_common(20):
        gens = sorted({x[2] for x in early if x[0] == h})
        print("   %-28s %4d   documented from %s"
              % (h, c, ", ".join("0x%04X" % g for g in gens)))
    if artifacts:
        ah = collections.Counter(x[0] for x in artifacts)
        print("\ncorpus artifacts skipped (name is literally enum/struct/union): "
              "%d rows in %d headers" % (len(artifacts), len(ah)))
        for h, c in ah.most_common(10):
            print("   %-28s %4d" % (h, c))
    if held:
        print("\ndeliberately visible at 4.2 (docs/generation-exceptions.tsv): "
              "%d names" % len(held))
        for h, n, d, e, p, ln in held:
            print("   %s:%d %s doc>=0x%04X (%s)" % (h, ln, n, d, p))
    print("\nvisible later than documented (over-guarded): %d names" % len(late))
    for h, n, d, e, p, ln in late:
        print("   %s:%d %s doc>=0x%04X effective=0x%04X (%s)" % (h, ln, n, d, e, p))
    if a.json:
        json.dump({"early": early, "late": late,
                   "artifacts": artifacts, "held": held}, open(a.json, "w"), indent=1)
        print("\nwrote", a.json)


if __name__ == "__main__":
    main()
