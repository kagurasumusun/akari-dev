#!/usr/bin/env python3
"""absent-types-scan.py CORPUS_ROOT

D-axis: for every surface-audit 'absent' name, find title pages in
any corpus section and classify what they print: typedef struct/enum
(the name as the typedef target), constant value assignments, or a
prototype.  The earlier absent-prints scan covered function
prototypes; this pass catches struct/enum/const surfaces.
Writes docs/absent-types-scan-2026-09-18.tsv.
"""
import glob
import html
import os
import re
import sys
import collections

TITLE = re.compile(r"<title>([^<]*)", re.I)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")


def main():
    root = sys.argv[1]
    names = set()
    for line in open("/tmp/absent-names.txt", encoding="utf-8"):
        n = line.strip()
        if n and re.match(r"^[A-Za-z_]\w*$", n):
            names.add(n)
    print("absent names:", len(names))
    want = {n.lower(): n for n in names}

    out = []
    seen = 0
    for f in glob.glob(os.path.join(root, "docs", "**", "*.html"), recursive=True):
        try:
            with open(f, encoding="utf-8", errors="replace") as fh:
                head = fh.read(4000)
        except OSError:
            continue
        m = TITLE.search(head)
        if not m:
            continue
        cand = re.split(r"\s*\(", m.group(1))[0].strip()
        cand = re.sub(r"\s+(Structure|Constant|Enumeration|Function|Union)$", "", cand)
        k = cand.lower()
        if k not in want:
            continue
        name = want[k]
        seen += 1
        try:
            h = open(f, encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        h = re.sub(r"<script.*?</script>", "", h, flags=re.S)
        text = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", h)))
        pid = PAGEID.search(os.path.basename(f))
        pid = pid.group(1) if pid else os.path.basename(f)[:28]
        kind = None
        excerpt = ""
        # typedef print with the name as target
        tm = re.search(r"typedef\s+(struct|enum|union)\b[^;]{0,2000}?\}\s*" +
                       re.escape(name) + r"\s*[,;]", text)
        if tm:
            kind = "typedef-" + tm.group(1)
            excerpt = tm.group(0)[:260]
        else:
            cm = re.search(re.escape(name) + r"\s*(?:=|is)\s*\(?(0[xX][0-9a-fA-F]+|\d+)\)?", text)
            if cm:
                kind = "const"
                excerpt = cm.group(0)[:120]
            else:
                pm = re.search(r"[\w \*]{1,60}\b" + re.escape(name) + r"\s*\([^;)]{0,400}\)\s*;", text)
                if pm:
                    kind = "proto"
                    excerpt = pm.group(0)[:260]
        if kind:
            # Link Library hint
            lm = re.search(r"(?:Link Library|Library)[:\s]+([A-Za-z0-9_,\. ]{2,60}?)(?:\s+(?:Windows|OS Versions|See Also|Requirements)|$)", text)
            lib = lm.group(1).strip() if lm else ""
            out.append((name, kind, pid, lib, excerpt.replace("\t", " ")))
    print("title pages seen:", seen, "with prints:", len(out))
    print(collections.Counter(r[1] for r in out))
    path = "docs/absent-types-scan-2026-09-18.tsv"
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("name\tkind\tpage\tlib\tprint\n")
        for r in sorted(out):
            fh.write("\t".join(r) + "\n")
    print("wrote", path)


if __name__ == "__main__":
    main()
