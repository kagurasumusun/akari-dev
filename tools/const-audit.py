#!/usr/bin/env python3
"""const-audit.py -- value-level cross-check of numeric #define
constants in include/ against the corpus pages cited for them.

For every `#define NAME <integer literal>` the governing citation is
either a page id on the same line (/* ms931795 */) or the nearest
preceding comment block carrying page ids, provided only #define /
comment / blank lines sit between (i.e. the block heads a constants
table).  The page is then searched for the printed name: tables print
"NAME = 0xVALUE" or put the name and the value in adjacent cells.
Values are compared numerically (32-bit two's-complement aware).

Usage:
    python3 tools/const-audit.py <corpus-clone> [--out docs/const-audit.tsv]
"""
import html
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEF = re.compile(r"^#define\s+([A-Z_][A-Z0-9_]*)\s+"
                 r"(0[xX][0-9A-Fa-f]+|[0-9]+)\s*[LlUu]*\s*(?:/\*(.*?)\*/)?\s*$")
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")
INT_RE = re.compile(r"^(0[xX][0-9A-Fa-f]+|[0-9]+)[LlUu]*$")


def parse_value(s):
    try:
        return int(s, 0)
    except ValueError:
        return None


def canon32(v):
    return v & 0xFFFFFFFF


def page_text_cache(pages):
    cache = {}

    def get(pid):
        if pid not in cache:
            p = pages.get(pid)
            if p:
                h = open(p, encoding="utf-8", errors="replace").read()
                txt = html.unescape(re.sub(r"<[^>]+>", " ", h))
                cache[pid] = (h, re.sub(r"\s+", " ", txt))
            else:
                cache[pid] = None
        return cache[pid]
    return get


NUM = r"(0[xX][0-9A-Fa-f]+|\d+)"



def strip_comments(s):
    """Blank out C comments/strings, preserving offsets (so citations can
    still be located in the original text)."""
    out = list(s)
    i = 0
    n = len(s)
    while i < n:
        if s[i:i + 2] == "/*":
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif s[i:i + 2] == "//":
            j = s.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif s[i] == '"':
            j = i + 1
            while j < n and s[j] != '"':
                j += 2 if s[j] == "\\" else 1
            j = min(j + 1, n)
            for k in range(i + 1, j - 1):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        else:
            i += 1
    return "".join(out)


def find_printed_value(raw, txt, name):
    """Return (status, value...).  status in found/name-only/absent."""
    if not txt:
        return ("absent",)
    esc = re.escape(name)
    cands = []
    # S1: explicit "NAME = 0xVALUE" (constants tables, e.g. RTC/Tapi)
    for m in re.finditer(r"\b%s\s*=\s*%s" % (esc, NUM), txt):
        v = parse_value(m.group(1))
        if v is not None:
            cands.append(v)
    # S2: table rows -- the name occupies a whole cell; the value is
    # another numeric cell of the same row (prefer 0x form, then a
    # bare 8-digit hex, then a lone integer cell)
    if not cands:
        for tr in re.findall(r"<tr[^>]*>(.*?)</tr>", raw, re.S):
            cells = [re.sub(r"\s+", " ",
                            html.unescape(re.sub(r"<[^>]+>", "", c))).strip()
                     for c in re.findall(r"<t[dh][^>]*>(.*?)</t[dh]>", tr, re.S)]
            if not any(c == name for c in cells):
                continue
            hexes = [c for c in cells if re.fullmatch(r"0[xX][0-9A-Fa-f]+", c)]
            bare8 = [c for c in cells if re.fullmatch(r"[0-9A-Fa-f]{8}", c)]
            ints = [c for c in cells if re.fullmatch(r"\d+", c)]
            pick = hexes[:1] or bare8[:1] or (ints[:1] if len(ints) == 1 else [])
            if pick:
                try:
                    # bare 8-digit cells are hex without the 0x prefix
                    v = int(pick[0], 16) if pick[0] in bare8 \
                        else parse_value(pick[0])
                except ValueError:
                    v = None
                if v is not None:
                    cands.append(v)
            break
    # S3: adjacent "NAME VALUE" in the flow text
    if not cands:
        for m in re.finditer(r"\b%s\s+%s\b" % (esc, NUM), txt):
            v = parse_value(m.group(1))
            if v is not None:
                cands.append(v)
    if not cands:
        if re.search(r"\b%s\b" % esc, txt):
            return ("name-only",)
        return ("absent",)
    vals = {canon32(v) for v in cands}
    if len(vals) > 1:
        return ("ambiguous", cands[0], cands[-1])
    return ("found", cands[0])


def main():
    corpus = sys.argv[1]
    out = "docs/const-audit-2026-09-18.tsv"
    for a in sys.argv:
        if a.startswith("--out="):
            out = a.split("=", 1)[1]
    # page index
    pages = {}
    for base in ("docs/mslearn", "docs/chm", "docs/wayback-msdn"):
        d0 = os.path.join(corpus, base)
        if not os.path.isdir(d0):
            continue
        for sub in os.listdir(d0):
            d = os.path.join(d0, sub)
            if not os.path.isdir(d):
                continue
            for fn in os.listdir(d):
                if fn.endswith(".html"):
                    pid = re.sub(r"\(v=[a-z0-9.]+\)$", "", fn[:-5])
                    pages.setdefault(pid, os.path.join(d, fn))
    get = page_text_cache(pages)
    rows = []
    counts = {}

    def bump(st):
        counts[st] = counts.get(st, 0) + 1

    for dirpath in ("include", "include/oak"):
        d = os.path.join(ROOT, dirpath)
        for fn in sorted(os.listdir(d)):
            if not fn.endswith((".h", ".hpp", ".hxx")):
                continue
            lines = open(os.path.join(d, fn), encoding="utf-8",
                         errors="replace").read().splitlines()
            block_ids = []          # page ids of the governing table comment
            block_txt = ""          # its text (for deviation annotations)
            since_code = False
            for line in lines:
                s = line.strip()
                m = DEF.match(line)
                if m:
                    name, raw, cmt = m.group(1), m.group(2), m.group(3) or ""
                    inline_ids = PAGEID.findall(cmt)
                    ids = inline_ids or block_ids
                    gov = cmt if inline_ids else block_txt
                    hdr = os.path.join(dirpath, fn)
                    if not ids:
                        bump("no-pageid")
                        rows.append((hdr, name, "", "no-pageid", ""))
                        continue
                    val = parse_value(raw)
                    pid = ids[0]
                    if pid not in pages:
                        bump("page-not-in-corpus")
                        rows.append((hdr, name, pid, "page-not-in-corpus", ""))
                        continue
                    pg = get(pid)
                    res = find_printed_value(pg[0], pg[1], name) if pg \
                        else ("absent",)
                    annotated = bool(re.search(
                        r"\bR1\b|artifact|not printed|no numbers|"
                        r"value confirmation|values? (?:are )?confirmed",
                        gov, re.I))
                    if res[0] == "absent":
                        bump("name-not-on-page")
                        rows.append((hdr, name, pid, "name-not-on-page", ""))
                    elif res[0] == "name-only":
                        bump("name-no-value-on-page")
                        rows.append((hdr, name, pid, "name-no-value-on-page",
                                     "value R1/derived" if annotated else ""))
                    elif res[0] == "ambiguous":
                        bump("ambiguous-on-page")
                        rows.append((hdr, name, pid, "ambiguous-on-page",
                                     "page prints %s and %s" %
                                     (hex(res[1]), hex(res[2]))))
                    elif canon32(res[1]) == canon32(val):
                        bump("match")
                        rows.append((hdr, name, pid, "match", ""))
                    elif annotated:
                        bump("annotated-deviation")
                        rows.append((hdr, name, pid, "annotated-deviation",
                                     "hdr=%s page=%s" % (raw, hex(res[1]))))
                    else:
                        bump("MISMATCH")
                        rows.append((hdr, name, pid, "MISMATCH",
                                     "hdr=%s page=%s" % (raw, hex(res[1]))))
                    continue
                if s.startswith("/*") or s.startswith("*") or \
                   s.startswith("//") or not s:
                    ids = PAGEID.findall(line)
                    if ids:
                        block_ids = ids
                        block_txt = line
                        since_code = False
                    elif block_ids:
                        block_txt += " " + line
                    continue
                # any other line (code) ends the governed table block
                if not since_code:
                    since_code = True
                block_ids = []
    outp = os.path.join(ROOT, out)
    os.makedirs(os.path.dirname(outp), exist_ok=True)
    with open(outp, "w") as f:
        f.write("# header\tname\tpage\tstatus\tdetail\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")
    print("status counts:", dict(sorted(counts.items())))
    print("wrote", outp, len(rows), "rows")


if __name__ == "__main__":
    main()
