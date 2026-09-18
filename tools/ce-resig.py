#!/usr/bin/env python3
"""
ce-resig.py -- backfill rows*.json `sig` fields that the original
harvest left empty although the saved official page DOES print a
signature (inside its <pre><code> syntax block).

Local-only: reads the corpus pages already saved.  Updates the rows
files in place and reports how many prints were recovered.

Usage: python3 tools/ce-resig.py <corpus> [--dry]
"""

import glob
import html
import json
import os
import re
import sys


def page_path(corpus, pid):
    for d in ("pages3", "pages4", "pages5", "pages6", "pagesw", "pageswm",
              "pagesnet", "pagesmag", "pages42"):
        p = os.path.join(corpus, d, pid + ".html")
        if os.path.exists(p):
            return p
    hit = glob.glob(os.path.join(corpus, "pages*", pid + ".html"))
    return hit[0] if hit else None


def code_blocks(text):
    out = []
    for m in re.finditer(r"(?s)<pre[^>]*>\s*<code[^>]*>(.*?)</code>\s*</pre>",
                         text):
        b = m.group(1)
        b = re.sub(r"<br\s*/?>", "\n", b)
        b = re.sub(r"<[^>]+>", "", b)
        b = html.unescape(b)
        b = b.replace("\r", "")
        lines = [re.sub(r"[ \t]+", " ", ln).strip()
                 for ln in b.split("\n")]
        b = "\n".join(ln for ln in lines if ln)
        if b:
            out.append(b)
    for m in re.finditer(r"(?s)<pre[^>]*>(.*?)</pre>", text):
        b = m.group(1)
        if "<code" in b:
            continue
        b = re.sub(r"<[^>]+>", "", b)
        b = html.unescape(b)
        b = b.replace("\r", "")
        lines = [re.sub(r"[ \t]+", " ", ln).strip()
                 for ln in b.split("\n")]
        b = "\n".join(ln for ln in lines if ln)
        if b:
            out.append(b)
    return out


def looks_like_sig(b, title):
    first = b.split("\n")[0]
    if re.match(r"^\s*(typedef|#define)\b", b):
        return 3
    if title and re.search(re.escape(title) + r"\s*\(", b):
        return 2
    if re.match(r"^\s*[A-Za-z_][\w\s\*]*\b[A-Za-z_]\w*\s*\(", first) \
            and ")" in b and len(b) < 2000:
        return 1
    return 0


def main():
    corpus = sys.argv[1]
    dry = "--dry" in sys.argv
    total = fixed = nopage = noblock = 0
    for fn in ("rows.json", "rows4.json", "rows3.json"):
        path = os.path.join(corpus, fn)
        rows = json.load(open(path, encoding="utf-8"))
        changed = False
        for r in rows:
            if (r.get("sig") or "").strip():
                continue
            title = r.get("title", "").strip()
            mo = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)\s*(?:\(.*\))?$",
                          title)
            if not mo:
                continue
            total += 1
            pid = r.get("id", "").split("(")[0].strip()
            p = page_path(corpus, pid)
            if not p:
                nopage += 1
                continue
            text = open(p, encoding="utf-8", errors="replace").read()
            cands = [(looks_like_sig(b, mo.group(1)), b)
                     for b in code_blocks(text)]
            cands = [(s, b) for s, b in cands if s]
            if not cands:
                noblock += 1
                continue
            cands.sort(key=lambda x: -x[0])
            r["sig"] = cands[0][1]
            fixed += 1
            changed = True
        if changed and not dry:
            json.dump(rows, open(path, "w", encoding="utf-8"),
                      ensure_ascii=False, indent=1)
        print(f"{fn}: {fixed} backfilled so far "
              f"(empty-sig identifier rows seen: {total}, "
              f"no page: {nopage}, page without print: {noblock})")
    print(f"TOTAL backfilled: {fixed}")


if __name__ == "__main__":
    main()
