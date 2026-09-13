#!/usr/bin/env python3
"""
cf-harvest.py -- harvest the official .NET Framework 3.5 (v=vs.90) class
library pages that carry a ".NET Compact Framework" Version Information row,
and emit the CF API-surface table (M102b/M102c).

Source (official): learn.microsoft.com
    https://learn.microsoft.com/en-us/previous-versions/dotnet/netframework-3.5/<id>(v=vs.90)

Microsoft's CF roadmap (dn197949(v=winembedded.80)) states the CF library
reference is the .NET 3.5 class library, where a member's CF support is
marked by the "Version Information -> .NET Compact Framework -> Supported
in: N" row (or the CF member icon).  A page WITHOUT that row is desktop-only
and is not part of the CE surface.  This tool records only pages WITH a CF
row (plus their namespace/assembly/platform facts), so the CE surface stays
a documented constrained subset -- never desktop .NET by assumption.

Outputs (per run):
    build/pagesnet/<id>.html   raw official HTML (preservation copy)
    <surface.tsv>              id, title, kind, namespace, assembly,
                               platforms, cf_supported, path

Usage:
    python3 tools/cf-harvest.py tools/catalogs/catalog-netfx-35.tsv \
        build/cf-surface.tsv [namespace-substring ...]
    (an empty namespace-substring list harvests every catalog leaf)

The catalog is produced by tools/cf-toc.py from the official toc.json.
"""

import html
import os
import re
import sys
import time
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE = "https://learn.microsoft.com/en-us/previous-versions/dotnet/netframework-3.5/{}(v=vs.90)"
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/120 Safari/537.36")
PAGES = os.path.join(ROOT, "build", "pagesnet")


def fetch(root):
    path = os.path.join(PAGES, root + ".html")
    if os.path.exists(path) and os.path.getsize(path) > 4000:
        return path
    url = BASE.format(root)
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    data = None
    for attempt in range(4):
        try:
            with urllib.request.urlopen(req, timeout=60) as resp:
                data = resp.read()
            break
        except urllib.error.HTTPError as exc:
            if exc.code == 404 and attempt < 3:
                time.sleep(15 * (attempt + 1))
                continue
            raise
        except Exception:
            if attempt == 3:
                raise
            time.sleep(2 * (attempt + 1))
    os.makedirs(PAGES, exist_ok=True)
    tmp = path + ".tmp"
    with open(tmp, "wb") as fh:
        fh.write(data)
    os.replace(tmp, path)
    time.sleep(0.15)
    return path


def strip_tags(seg):
    return html.unescape(re.sub(r"<[^>]+>", "", seg))


def parse(path, title, tpath):
    raw = open(path, encoding="utf-8", errors="replace").read()
    flat = html.unescape(re.sub(r"<[^>]+>", " ", raw))
    flat = re.sub(r"\s+", " ", flat)

    # namespace: "Namespace:  <link>" right after the heading
    ns = ""
    m = re.search(r"Namespace:\s*([A-Za-z_][\w.]*)", flat)
    if m:
        ns = m.group(1)

    # assembly: "Assembly:  Foo (in Foo.dll)"
    asm = ""
    m = re.search(r"Assembly:\s*([A-Za-z0-9_.]+(?:\s*\(in\s*[A-Za-z0-9_.]+\.dll\))?)", flat)
    if m:
        asm = re.sub(r"\s+", " ", m.group(1))

    # platforms: "Platforms" section lists "Windows CE, ..." or specific OSes
    platforms = ""
    m = re.search(r"Platforms\s+(.*?)(?:Version Information|\.NET Framework Security|See Also|$)",
                  flat)
    if m:
        platforms = " ".join(m.group(1).split())[:160]

    # CF support: "Version Information ... .NET Compact Framework ... Supported in: X"
    cf = ""
    m = re.search(r"\.NET Compact Framework\s+Supported in:\s*"
                  r"([0-9]+\.[0-9]+(?:\s*,\s*[0-9]+\.[0-9]+)*)",
                  flat)
    if m:
        cf = re.sub(r"\s+", "", m.group(1))

    # kind from the TOC path tail ("... Foo Class" / "... Bar Method " etc.)
    kind = ""
    segs = [s.strip() for s in tpath.split("/") if s.strip()]
    tail = segs[-1] if segs else title
    m = re.search(r"\b(Namespace|Class|Structure|Interface|Delegate|Enumeration|Method|Property|Field|Event|Constructor|Operator|Members)$", tail)
    if m:
        kind = m.group(1)
    return ns, asm, platforms, cf, kind


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    catalog, surface = sys.argv[1], sys.argv[2]
    filters = sys.argv[3:]

    rows = []
    with open(catalog, encoding="utf-8") as fh:
        for line in fh:
            parts = line.rstrip("\n").split("\t")
            if len(parts) < 4:
                continue
            pid, title, book, path = parts[0], parts[1], parts[2], parts[3]
            if filters and not any(f.lower() in path.lower() for f in filters):
                continue
            rows.append((pid, title, path))

    print(f"harvesting {len(rows)} leaves -> {PAGES}")
    out = []
    for pid, title, path in rows:
        root = pid.split("(")[0]
        try:
            p = fetch(root)
            ns, asm, platforms, cf, kind = parse(p, title, path)
        except Exception as exc:  # noqa: BLE001
            print(f"!! {pid} {title}: {exc}", file=sys.stderr)
            out.append((pid, title, "", "", "", "", "ERROR:" + str(exc), path))
            continue
        out.append((pid, title, kind, ns, asm, platforms, cf, path))
        flag = "CF" if cf else "-"
        print(f"  {flag:2} {title[:44]:46} {ns or '-':34} {cf or ''}")

    with open(surface, "w", encoding="utf-8") as fh:
        fh.write("id\ttitle\tkind\tnamespace\tassembly\tplatforms\tcf_supported\tpath\n")
        for pid, title, kind, ns, asm, platforms, cf, path in sorted(out):
            fh.write(f"{pid}\t{title}\t{kind}\t{ns}\t{asm}\t{platforms}\t{cf}\t{path}\n")

    withcf = [r for r in out if r[6] and not r[6].startswith("ERROR")]
    print(f"pages: {len(out)}; with a .NET Compact Framework row: {len(withcf)}")
    print(f"wrote: {surface}")


if __name__ == "__main__":
    main()
