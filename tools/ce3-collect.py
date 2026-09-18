#!/usr/bin/env python3
"""
ce3-collect.py -- harvest the official "Windows CE 3.0 Technical Documentation"
archive (Microsoft Download Center, id=41197) into the wince-docs-corpus.

Source (official):
    https://www.microsoft.com/en-us/download/details.aspx?id=41197
    https://download.microsoft.com/download/1/3/d/13d0b628-4758-4b87-a9f2-6e98c940e6a9/WindowsCE3.0_DocumentationArchive.zip
    (zip contains WindowsCE3.0_DocumentationArchive.chm)

Pipeline
--------
1.  curl -L -o ce30.zip "<the download URL above>"
2.  unzip ce30.zip                                   # -> .chm + Important_ReadMe.txt
3.  7z x -o<chmdir> WindowsCE3.0_DocumentationArchive.chm   # p7zip; see README note
4.  python3 tools/ce3-collect.py <chmdir>/html <outdir> <rows.json> <catalog.tsv> <versions.tsv>

Outputs
-------
* <outdir>/pages3/<id>.html     raw official HTML, one file per page (corpus)
* <rows.json>                   harvested rows: id/title/sig/os/versions/header/lib
* <catalog.tsv>                 id <TAB> title  (full page catalog)
* <versions.tsv>                id/title/min_ce/versions/header/lib/os  (API surface table)

Why this matters: CE 1.x/2.x documentation is not published on Learn. The CE 3.0
archive is the only complete official reference for the CE 1/2/3 API surface,
because every reference page carries a "Versions: N and later" Requirements row
(e.g. "1.0 and later", "2.10 and later", "3.0 and later"). Those rows give the
minimum Windows CE version for each API, so the CE 1.0 / 2.x / 3.0 surfaces can
be reconstructed exactly from official statements (no desktop-Win32 assumption).
"""

import html as _html
import json
import os
import re
import shutil
import sys

ID_TOKEN = re.compile(r"(?:ms|aa|ee)\d{5,}")


def strip_tags(raw: str) -> str:
    raw = re.sub(r"<script[\s\S]*?</script>", " ", raw, flags=re.I)
    raw = re.sub(r"<style[\s\S]*?</style>", " ", raw, flags=re.I)
    t = re.sub(r"<[^>]+>", " ", raw)
    t = _html.unescape(t)
    t = t.replace("\xa0", " ").replace("\u200b", "")
    t = re.sub(r"[ \t]+", " ", t)
    t = re.sub(r"[ \t]*\n[ \t]*", "\n", t)
    return t.strip()


def parse_syntax(raw: str) -> str:
    m = re.search(r'<pre[^>]*class="syntax"[^>]*>([\s\S]*?)</pre>', raw, re.I)
    if not m:
        m = re.search(r"<pre[^>]*>([\s\S]*?)</pre>", raw, re.I)
    if not m:
        return ""
    return " ".join(strip_tags(m.group(1)).split())


def parse_requirements(raw: str):
    """Return (runs_on, versions, defined_in, include, link_to)."""
    i = raw.lower().find("requirements")
    if i < 0:
        return "", "", "", "", ""
    seg = raw[i:i + 6000]
    tbm = re.search(r"<table[^>]*>([\s\S]*?)</table>", seg, re.I)
    if not tbm:
        return "", "", "", "", ""
    tbl = tbm.group(1)
    ths = [strip_tags(x).strip().lower()
           for x in re.findall(r"<th[^>]*>([\s\S]*?)</th>", tbl, re.I)]
    tds = [strip_tags(x).strip()
           for x in re.findall(r"<td[^>]*>([\s\S]*?)</td>", tbl, re.I)]
    if len(tds) < len(ths):
        return "", "", "", "", ""
    row = dict(zip(ths, tds))
    return (row.get("runs on", ""), row.get("versions", ""),
            row.get("defined in", ""), row.get("include", ""),
            row.get("link to", ""))


def min_ce(versions: str):
    """Canonicalize a raw Versions string into a minimum CE generation tag."""
    v = versions.strip().lower().replace("\n", " ")
    v = re.sub(r"\s+", " ", v)
    if not v:
        return ""
    if v.startswith("4."):
        return "4.0"
    if v.startswith("3."):
        return "3.0"
    if v.startswith("2.12"):
        return "2.12"
    if v.startswith("2.11"):
        return "2.11"
    if v.startswith("2.10"):
        return "2.10"
    if v.startswith("2.1"):
        return "2.1"
    if v.startswith("2.01"):
        return "2.01"
    if v.startswith("2.0"):
        return "2.0"
    if v.startswith("1.02"):
        return "1.02"
    if v.startswith("1.01"):
        return "1.01"
    if v.startswith("1.9"):
        return "1.9"
    if v.startswith("1."):
        return "1.0"
    if "japanese version 1.0" in v:
        return "1.0-jp"
    if "japanese version 2.0" in v:
        return "2.0-jp"
    return v[:24]


def main():
    if len(sys.argv) != 6:
        print(__doc__)
        sys.exit(2)
    src, outdir, rows_path, catalog_path, versions_path = sys.argv[1:6]

    pagesdir = os.path.join(outdir, "pages3")
    os.makedirs(pagesdir, exist_ok=True)

    catalog = []      # (id, title)
    rows = []
    vers_rows = []

    for fn in sorted(os.listdir(src)):
        if not fn.lower().endswith((".htm", ".html")):
            continue
        cid = re.sub(r"\.html?$", "", fn)
        raw = open(os.path.join(src, fn), encoding="utf-8",
                   errors="replace").read()

        t = re.search(r"<title>(.*?)</title>", raw, re.S | re.I)
        title = _html.unescape(t.group(1)).strip() if t else cid

        runs_on, versions, defined_in, include, link_to = parse_requirements(raw)
        header = defined_in if defined_in else include
        sig = parse_syntax(raw)

        # corpus: raw official HTML (preservation copy)
        shutil.copyfile(os.path.join(src, fn),
                        os.path.join(pagesdir, cid + ".html"))

        catalog.append((cid, title))
        rows.append({
            "id": cid,
            "title": title,
            "sig": sig,
            "os": runs_on,
            "versions": versions,
            "header": header,
            "lib": link_to,
            "params": [],
            "notes": [],
        })
        mc = min_ce(versions)
        if versions:
            vers_rows.append((cid, title, mc, versions, header, link_to, runs_on))

    catalog.sort()
    with open(catalog_path, "w", encoding="utf-8") as fh:
        for cid, title in catalog:
            fh.write(f"{cid}\t{title}\n")

    with open(rows_path, "w", encoding="utf-8") as fh:
        json.dump(rows, fh, ensure_ascii=False, indent=1)

    with open(versions_path, "w", encoding="utf-8") as fh:
        fh.write("id\ttitle\tmin_ce\tversions\theader\tlib\tos\n")
        for cid, title, mc, v, h, l, o in sorted(vers_rows, key=lambda x: x[0]):
            fh.write(f"{cid}\t{title}\t{mc}\t{v}\t{h}\t{l}\t{o}\n")

    nver = len(vers_rows)
    print(f"pages: {len(catalog)}; with Versions row: {nver}")
    print(f"wrote: {rows_path}, {catalog_path}, {versions_path}, pages3/*.html")


if __name__ == "__main__":
    main()
