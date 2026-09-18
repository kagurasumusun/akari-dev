#!/usr/bin/env python3
"""twin-struct-scan.py CORPUS_ROOT [--tsv docs/enum-audit-2026-09-18.tsv]

Verification axis for struct declarations whose cited page lacks the
print (status no-print-on-page): find pages in other corpus sections
whose <title> is the struct name, extract the `typedef struct ... }
NAME` print, normalize the member list, and compare against the
header's own declaration.  Read-only; writes
docs/twin-enum-scan-2026-09-18.tsv with statuses twin-match /
twin-diff / no-twin-page / no-print-in-twin.
"""
import glob
import html
import os
import re
import sys
import collections

TSV = "docs/enum-audit-2026-09-18.tsv"
if "--tsv" in sys.argv:
    TSV = sys.argv[sys.argv.index("--tsv") + 1]

TITLE = re.compile(r"<title>([^<]*)", re.I)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")
# header decl: } NAME [, *P...] ; preceded by typedef struct ...
DECL_CLOSE = re.compile(
    r"typedef\s+(?:struct|union|enum)\s*(\w*)\s*\{(.*?)\}\s*([A-Z_]\w*)\s*(?:,[^;]*)?;", re.S)


def members_of(body):
    out = []
    for m in re.split(r";", body):
        m = re.sub(r"/\*.*?\*/", " ", m, flags=re.S)
        m = re.sub(r"\s+", " ", m).strip()
        if not m:
            continue
        # drop bitfield widths and array sizes for comparison
        m = re.sub(r"\[[^\]]*\]", "", m)
        m = re.sub(r":\s*\d+", "", m)
        toks = [t for t in m.split() if t not in ("const",)]
        if not toks:
            continue
        # keep type words only (drop trailing lowercase member name)
        while len(toks) > 1 and re.match(r"^[a-z_]\w*$", toks[-1]) and \
              not toks[-1].isupper():
            toks = toks[:-1]
        t = " ".join(toks)
        t = re.sub(r"\s*\*\s*", "*", t)
        out.append(t)
    return out


def main():
    root = sys.argv[1]
    rows = []
    for line in open(TSV, encoding="utf-8").read().splitlines()[1:]:
        if line.startswith("#"):
            continue
        f = line.split("\t")
        if len(f) >= 4 and f[3] == "no-print-on-page":
            rows.append((f[1], f[0], f[2]))
    names = sorted({r[0] for r in rows})
    print("no-print structs:", len(names))

    want = {n.lower(): n for n in names}
    title_map = {}
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
        cand = re.sub(r"\s+(Structure|Union)$", "", cand)
        k = cand.lower()
        if k in want:
            title_map.setdefault(want[k], []).append(f)
    print("with twin-title pages:", len(title_map))

    decl_cache = {}

    def header_members(path, name):
        if path not in decl_cache:
            s = open(path, encoding="utf-8", errors="replace").read()
            d = {}
            for m in DECL_CLOSE.finditer(s):
                d[m.group(3)] = members_of(m.group(2))
            decl_cache[path] = d
        return decl_cache[path].get(name)

    out = []
    for name, hdr, pid in sorted(rows):
        cands = title_map.get(name, [])
        if not cands:
            out.append((name, hdr, pid, "", "", "no-twin-page", ""))
            continue
        twin = None
        for f in cands:
            h = open(f, encoding="utf-8", errors="replace").read()
            for b in re.findall(r"<pre[^>]*>(.*?)</pre>", h, re.S):
                t = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", "", b))).strip()
                m = re.search(r"typedef\s+(?:struct|union|enum)\s*(\w*)\s*\{(.*?)\}\s*" +
                              re.escape(name) + r"\s*(?:,[^;]*)?;", t)
                if m:
                    twin = (f, members_of(m.group(2)))
                    break
            if twin:
                break
        if not twin:
            out.append((name, hdr, pid, cands[0], "", "no-print-in-twin", ""))
            continue
        tf, tmembers = twin
        mm = PAGEID.search(os.path.basename(tf))
        tpid = mm.group(1) if mm else ""
        hm = header_members(hdr, name)
        if hm is None:
            out.append((name, hdr, pid, tf, tpid, "no-header-decl", ""))
            continue
        diffs = []
        if len(hm) != len(tmembers):
            diffs.append("membercount hdr=%d twin=%d" % (len(hm), len(tmembers)))
        else:
            for i, (a, b) in enumerate(zip(hm, tmembers)):
                if a.replace(" ", "") != b.replace(" ", ""):
                    diffs.append("m%d hdr='%s' twin='%s'" % (i + 1, a, b))
        st = "twin-match" if not diffs else "twin-diff"
        out.append((name, hdr, pid, tf, tpid, st, "; ".join(diffs)[:200]))
    path = "docs/twin-enum-scan-2026-09-18.tsv"
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("name\thdr\tcited-pid\ttwin-path\ttwin-pid\tstatus\tdiffs\n")
        for r in out:
            fh.write("\t".join(r) + "\n")
    print(collections.Counter(r[5] for r in out))
    print("wrote", path)


if __name__ == "__main__":
    main()
