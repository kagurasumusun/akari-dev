#!/usr/bin/env python3
"""twin-fnptr-scan.py CORPUS_ROOT

Verification axis for function-pointer typedefs whose cited page lacks
the print (fnptr-audit status no-print-on-page): find title pages in
any corpus section, extract `typedef ... (*NAME)(...)` prints, compare
parameter/return types against the header declaration.  Read-only;
writes docs/twin-fnptr-scan-2026-09-18.tsv.
"""
import glob
import html
import os
import re
import sys
import collections
import importlib.util

spec = importlib.util.spec_from_file_location(
    "pa", os.path.join(os.path.dirname(os.path.abspath(__file__)), "proto-audit.py"))
pa = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pa)

TSV = "docs/fnptr-audit-2026-09-18.tsv"
TITLE = re.compile(r"<title>([^<]*)", re.I)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")
# typedef RET (WINAPI *NAME)(params);
FNDECL = re.compile(
    r"typedef\s+([\w\s\*]+?)\s*\(\s*\w*\s*\*\s*(\w+)\s*\)\s*\(([^;]*)\)\s*;", re.S)


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
    print("no-print fnptrs:", len(names))

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
        cand = re.sub(r"\s+(Callback|Function)$", "", cand)
        k = cand.lower()
        if k in want:
            title_map.setdefault(want[k], []).append(f)
    print("with twin-title pages:", len(title_map))

    decl_cache = {}

    def header_fn(path, name):
        if path not in decl_cache:
            s = open(path, encoding="utf-8", errors="replace").read()
            d = {}
            for m in FNDECL.finditer(s):
                d[m.group(2)] = (re.sub(r"\s+", " ", m.group(1)).strip(), m.group(3))
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
                for m in FNDECL.finditer(t):
                    if m.group(2) == name:
                        twin = (f, re.sub(r"\s+", " ", m.group(1)).strip(), m.group(3))
                        break
                if twin:
                    break
            if twin:
                break
        if not twin:
            out.append((name, hdr, pid, cands[0], "", "no-print-in-twin", ""))
            continue
        tf, tret, tpraw = twin
        mm = PAGEID.search(os.path.basename(tf))
        tpid = mm.group(1) if mm else ""
        hd = header_fn(hdr, name)
        if hd is None:
            out.append((name, hdr, pid, tf, tpid, "no-header-decl", ""))
            continue
        hret, hpraw = hd
        hp, ok1 = pa.norm_params(hpraw)
        tp, ok2 = pa.norm_params(tpraw)
        if not (ok1 and ok2):
            out.append((name, hdr, pid, tf, tpid, "complex", ""))
            continue
        d = []
        if hret.replace("STDAPI", "").strip() != tret.replace("STDAPI", "").strip():
            d.append("ret hdr='%s' twin='%s'" % (hret, tret))
        if len(hp) != len(tp):
            d.append("argc %d vs %d" % (len(hp), len(tp)))
        else:
            for i, (a, b) in enumerate(zip(hp, tp)):
                if not pa.types_equal(a, b):
                    d.append("arg%d %s vs %s" % (i + 1, a, b))
        out.append((name, hdr, pid, tf, tpid,
                    "twin-match" if not d else "twin-diff", "; ".join(d)[:180]))
    path = "docs/twin-fnptr-scan-2026-09-18.tsv"
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("name\thdr\tcited-pid\ttwin-path\ttwin-pid\tstatus\tdiffs\n")
        for r in out:
            fh.write("\t".join(r) + "\n")
    print(collections.Counter(r[5] for r in out))
    print("wrote", path)


if __name__ == "__main__":
    main()
