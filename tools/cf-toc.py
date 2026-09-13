#!/usr/bin/env python3
"""
cf-toc.py -- snapshot the official .NET Framework 3.5 (v=vs.90) doc-tree
catalog from its Learn toc.json, for the CE 4/5/6 .NET (Compact) Framework
collection (M102b).

The .NET Compact Framework library reference lives inside the .NET
Framework 3.5 class library (see docs/plan-ce-net.md): Learn serves the
vs.90 documentation tree at

    https://learn.microsoft.com/en-us/previous-versions/dotnet/netframework-3.5/toc.json

Two parts make the CF API surface:
  1. the CF-specific managed namespaces (Microsoft.WindowsCE.Forms,
     Microsoft.WindowsMobile.*, ...) -- under the "Additional Managed
     Reference Topics" book (ms229434);
  2. the CF-supported subset of the desktop System.* class library,
     marked per member by a ".NET Compact Framework -> Supported in: N"
     Version Information row (the desktop class-library subtree itself
     is not enumerated in this toc.json -- it was migrated to the
     modern API browser, which drops the CF rows; see the plan).

This tool writes a 4-column catalog:

    <page-id>(v=vs.90)   <title>   <book>   <full path>

where <book> is the second-level section (e.g. "Additional Managed
Reference Topics", "General Reference for the .NET Framework") and
<full path> is the slash-joined breadcrumb, so the harvest can select
the CF-specific subtrees directly.

Usage:
    python3 tools/cf-toc.py fx35-toc.json tools/catalogs/catalog-netfx-35.tsv
"""

import json
import sys


def walk(node, path, out):
    if isinstance(node, list):
        for c in node:
            walk(c, path, out)
        return
    if not isinstance(node, dict):
        return
    title = node.get("toc_title") or node.get("title") or ""
    href = node.get("href") or ""
    children = node.get("children") or []
    newpath = path + [title] if title else path
    if href:
        book = newpath[1] if len(newpath) > 1 else (newpath[0] if newpath else "")
        out.append((href, title, book, "/".join(newpath)))
    for c in children:
        walk(c, newpath, out)


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    src, dst = sys.argv[1], sys.argv[2]
    data = json.load(open(src, encoding="utf-8"))
    items = data.get("items", data)
    out = []
    walk(items, [], out)
    out.sort()
    with open(dst, "w", encoding="utf-8") as fh:
        for href, title, book, path in out:
            fh.write(f"{href}\t{title}\t{book}\t{path}\n")
    from collections import Counter
    print(f"leaves: {len(out)}")
    print("by book:")
    for sec, c in Counter(x[2] for x in out).most_common(20):
        print(f"   {c:6d}  {sec}")


if __name__ == "__main__":
    main()
