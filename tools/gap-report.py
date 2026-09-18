#!/usr/bin/env python3
"""
gap-report.py -- classify the application-layer (-dev) gap by blocker.

Input: the harvested official-page records (wince-docs-corpus
rows.json / rows4.json / rows3.json) and the shipped headers.

A row is in the gap when the official page's Header row resolves to a
file in `include/` (the application -dev layer) but the page's
identifier is not declared live in `include/` -- i.e. a user-mode CE
program that includes the documented header cannot obtain the
declaration from this tree (docs/surface-audit.md, class D5).

Every gap row is classified by *why* it is not declared yet, using
only what the page itself prints:

    macro        the page prints a `#define ...` body
    prototype    the page prints a function prototype that parses
                 against the tree's type universe -> declarable now
    unres-type   prototype print, but at least one type token is not
                 declared anywhere in the tree (the blocking tokens
                 are listed, so the type can be harvested next)
    callback     prototype print of a user-implemented callback
    variadic     prototype print with `...`
    no-print     the page carries no printed signature at all (name
                 only) -- nothing to declare without inventing

Nothing is written; this is a measurement tool.

Usage:  python3 tools/gap-report.py <corpus-dir> [--limit N]
"""

import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import importlib.util


def _load(modname):
    spec = importlib.util.spec_from_file_location(
        modname, os.path.join(HERE, modname + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


d1 = _load("decl-d1")
ROOT = d1.ROOT
IDENT = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")


def layer_idents(rel):
    """(live, whole) identifier sets of one layer."""
    d = os.path.join(ROOT, rel)
    live, whole = set(), set()
    if not os.path.isdir(d):
        return live, whole
    for fn in sorted(os.listdir(d)):
        if not fn.endswith((".h", ".hxx", ".hpp")):
            continue
        text = open(os.path.join(d, fn), encoding="utf-8",
                    errors="replace").read()
        whole.update(IDENT.findall(text))
        code = re.sub(r"(?s)/\*.*?\*/", " ", text)
        code = re.sub(r"//[^\n]*", " ", code)
        live.update(IDENT.findall(code))
    return live, whole


def header_layer():
    m = {}
    for rel, tag in (("include", "app"), ("include/oak", "oak")):
        d = os.path.join(ROOT, rel)
        if os.path.isdir(d):
            for fn in os.listdir(d):
                m.setdefault(fn.lower(), tag)
    return m


def norm_header(h):
    h = (h or "").strip().rstrip(".").strip()
    if h.startswith("Include:"):
        h = h[8:].strip()
    if "," in h:
        cand = [x.strip() for x in h.split(",")
                if x.strip().endswith((".h", ".hxx", ".hpp"))]
        h = cand[0] if cand else h
    if h.endswith(".Se"):
        h = h[:-3]
    return h.split()[0] if h.split() else ""


def main():
    corpus = sys.argv[1]
    limit = None
    if "--limit" in sys.argv:
        limit = int(sys.argv[sys.argv.index("--limit") + 1])

    app_live, app_whole = layer_idents("include")
    oak_live, oak_whole = layer_idents("include/oak")
    live = app_live | oak_live          # one C namespace for a CE build
    res = d1.Resolver(live, d1.load_types())
    hl = header_layer()

    # best page record per identifier, CE5/CE6 first (same precedence
    # as the declaration tools)
    rows = {}
    for fn, tag in (("rows.json", "ce5+ce6"), ("rows4.json", "ce4"),
                    ("rows3.json", "ce3")):
        p = os.path.join(corpus, fn)
        if not os.path.exists(p):
            continue
        for r in json.load(open(p, encoding="utf-8")):
            t = r.get("title", "").strip()
            if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", t):
                continue
            rows.setdefault(t, []).append((tag, r))

    cls = {}
    detail = {}
    for name, entries in sorted(rows.items()):
        if name in app_live:
            continue                      # already in the -dev layer
        hdrs = [norm_header(r.get("header")) for _t, r in entries]
        if not any(hl.get(h.lower()) == "app" for h in hdrs if h):
            continue                      # OAK-only or no header row
        entries.sort(key=lambda e: {"ce5+ce6": 0, "ce4": 1, "ce3": 2}[e[0]])
        sig = ""
        for _t, r in entries:
            if (r.get("sig") or "").strip():
                sig = r["sig"]
                break
        if not sig.strip():
            k = "no-print"
        elif sig.lstrip().startswith("#define"):
            k = "macro"
        else:
            s = d1.clean_sig(sig)
            parsed = d1.parse_sig(sig, res)
            if parsed and parsed[1] == name:
                k = "prototype"
            elif "..." in s:
                k = "variadic"
            elif "CALLBACK" in s.split("(")[0].split():
                k = "callback"
            elif re.match(r"^[A-Z0-9_]+$", name):
                k = "all-caps-name"
            elif "(" not in s:
                k = "not-a-prototype"
            else:
                k = "unres-type"
                # a token counts as a blocker only when the resolver
                # cannot resolve it either directly or by splitting a
                # migration-glued print ("HWNDhwnd" -> HWND + hwnd)
                miss = set()
                for t in IDENT.findall(s):
                    if not t[0].isupper() or t in live \
                            or t in d1.DECOR or t in d1.C_KEYWORDS:
                        continue
                    if res.is_type(t) or res.split_glued(t):
                        continue
                    miss.add(t)
                detail[name] = sorted(miss)
        cls.setdefault(k, []).append(name)

    total = sum(len(v) for v in cls.values())
    print(f"application-layer (-dev) gap rows: {total}")
    for k in sorted(cls, key=lambda k: -len(cls[k])):
        print(f"  {k:16s} {len(cls[k])}")
    print()
    # the blocking type tokens, most frequent first: these are the
    # types whose official pages must be harvested next to unblock the
    # largest number of prototypes.
    from collections import Counter
    c = Counter()
    for miss in detail.values():
        c.update(miss)
    print("most frequent unresolved type tokens (blockers):")
    for tok, n in c.most_common(40):
        print(f"  {tok:32s} {n}")
    if limit:
        for k in sorted(cls):
            print(f"\n== {k} ({len(cls[k])}) ==")
            for n in cls[k][:limit]:
                extra = ("  blocked on: " + ",".join(detail[n][:6])
                         if n in detail else "")
                print(f"  {n}{extra}")


if __name__ == "__main__":
    main()
