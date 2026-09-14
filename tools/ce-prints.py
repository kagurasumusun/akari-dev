#!/usr/bin/env python3
"""
ce-prints.py -- recover the code prints that the Requirement-row
harvest (tools/ce-fetch.py) does not record.

ce-fetch.py records a page's code block as `sig` only when the block
contains a *call-shaped* print (`NAME(`).  That is right for function
pages, but it silently drops the pages whose print is a plain typedef,
a struct/union/enum definition or a `#define` -- exactly the prints
that the declaration tools need in order to stop holding a type.

This tool re-reads the *preserved official pages* in the corpus clone
(no network, no re-derivation) and, for every harvested row whose
`sig` is empty, extracts the code block that declares the page's own
identifier:

    typedef   `typedef ... NAME ...;`
    tagdef    `struct|union|enum NAME { ... }`  /  `typedef struct {...} NAME`
    define    `#define NAME value`
    proto     `RET NAME(...)`   (call-shaped, but on a page whose row
                                 lost it for another reason)

Output: build/rows-prints.json -- the same record schema as rows.json,
with `sig` filled from the page's own print and `print_kind` naming the
shape that matched.  tools/decl-types.py and tools/decl-d1.py read it
alongside the corpus rows*.json, so a recovered print immediately
unblocks the declarations that cite it.  Nothing is invented: when a
page prints no code block that declares its title, the row is left out
and stays held.

Measured yield over the whole preserved corpus (2026-09-14): of 3,474
rows with an empty `sig` whose page is in the corpus, 77 pages print a
declaration of their own title (75 tagdef, 2 typedef); the remaining
3,397 pages print no such block -- those names stay held, which is the
measured confirmation of the existing hold policy.

Usage:  python3 tools/ce-prints.py <corpus-dir>
"""

import json
import os
import re
import html
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "build", "rows-prints.json")

# corpus trees, in the order the declaration tools prefer them
TREES = ("pages5", "pages6", "pages4", "pages3", "pageswm")
ROWS = (("rows.json", "ce5+ce6"), ("rows4.json", "ce4"),
        ("rows3.json", "ce3"))
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def index_pages(corpus):
    idx = {}
    for t in TREES:
        d = os.path.join(corpus, t)
        if not os.path.isdir(d):
            continue
        for fn in sorted(os.listdir(d)):
            if fn.endswith(".html"):
                idx.setdefault(fn[:-5], os.path.join(d, fn))
    return idx


def strip_tags(seg):
    return html.unescape(re.sub(r"<[^>]+>", "", seg))


def code_blocks(raw):
    out = []
    for b in re.findall(r"<(?:pre|code)[^>]*>(.*?)</(?:pre|code)>", raw,
                        flags=re.S | re.I):
        c = re.sub(r"\s+", " ", strip_tags(b)).strip()
        if c:
            out.append(c)
    return out


def find_print(title, blocks):
    """(kind, print) of the first block that declares `title`."""
    esc = re.escape(title)
    for c in blocks:
        if len(c) > 4000:
            continue
        if re.search(r"\btypedef\b[^;{]*\b" + esc + r"\b", c):
            return "typedef", c
        if re.search(r"\b(?:struct|union|enum)\s+" + esc + r"\s*\{", c):
            return "tagdef", c
        if re.search(r"\btypedef\s+(?:struct|union|enum)\s*"
                     r"(?:[A-Za-z_][A-Za-z0-9_]*)?\s*\{[^}]*\}\s*"
                     + esc + r"\b", c):
            return "tagdef", c
        if re.search(r"#define\s+" + esc + r"\b", c):
            return "define", c
        if re.search(r"\b" + esc + r"\s*\(", c):
            return "proto", c
    return None, None


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    corpus = sys.argv[1]
    idx = index_pages(corpus)

    recs, seen = [], set()
    stats = {"rows": 0, "empty-sig": 0, "page-missing": 0,
             "no-print": 0, "recovered": 0}
    kinds = {}
    for fn, tag in ROWS:
        p = os.path.join(corpus, fn)
        if not os.path.exists(p):
            continue
        for r in json.load(open(p, encoding="utf-8")):
            stats["rows"] += 1
            t = (r.get("title") or "").strip()
            if not IDENT.match(t):
                continue
            if (r.get("sig") or "").strip():
                continue
            stats["empty-sig"] += 1
            root = re.split(r"[(]", r["id"])[0]
            page = idx.get(root)
            if not page:
                stats["page-missing"] += 1
                continue
            raw = open(page, encoding="utf-8", errors="replace").read()
            kind, pr = find_print(t, code_blocks(raw))
            if not pr:
                stats["no-print"] += 1
                continue
            key = (root, t)
            if key in seen:
                continue
            seen.add(key)
            out = dict(r)
            out["sig"] = pr
            out["print_kind"] = kind
            out["print_tree"] = os.path.basename(os.path.dirname(page))
            out["source_row"] = fn
            recs.append(out)
            kinds[kind] = kinds.get(kind, 0) + 1
            stats["recovered"] += 1

    recs.sort(key=lambda r: (r["id"], r["title"]))
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(recs, fh, ensure_ascii=False, indent=1)
    print(f"rows scanned: {stats['rows']}  empty-sig: {stats['empty-sig']}")
    print(f"  page not in corpus: {stats['page-missing']}")
    print(f"  page prints no declaration of its title: {stats['no-print']}")
    print(f"  recovered prints: {stats['recovered']} {kinds}")
    print(f"wrote {OUT}")


if __name__ == "__main__":
    main()
