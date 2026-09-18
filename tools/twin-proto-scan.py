#!/usr/bin/env python3
"""twin-proto-scan.py CORPUS_ROOT [--tsv docs/proto-audit-2026-09-18.tsv]

For every proto-audit row with status no-print-on-page, look for pages
in OTHER generation directories whose <title> names the same function
("NAME (Windows ..." / "NAME Function") and try to extract the
prototype print there (proto-audit's own page_protos).  Output TSV:
name  hdr  cited-pid  twin-path  twin-pid  status(match-print|no-print-in-twin)  print-text

Read-only against the corpus; no declaration is changed.  A
match-print row means the declaration now has sibling-generation
print evidence (verification); disagreements are left for manual
review (the print text is included).
"""
import glob
import importlib.util
import os
import re
import sys

spec = importlib.util.spec_from_file_location(
    "pa", os.path.join(os.path.dirname(os.path.abspath(__file__)), "proto-audit.py"))
pa = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pa)

TITLE = re.compile(r"<title>([^<]*)", re.I)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")


def gen_of(path):
    parts = path.split(os.sep)
    for p in parts:
        if p in ("docs",):
            i = parts.index(p)
            return "/".join(parts[i + 1:-1]) if i + 1 < len(parts) - 1 else ""
    return ""


def main():
    root = sys.argv[1]
    tsv = "docs/proto-audit-2026-09-18.tsv"
    if "--tsv" in sys.argv:
        tsv = sys.argv[sys.argv.index("--tsv") + 1]
    rows = []
    for line in open(tsv, encoding="utf-8").read().splitlines()[1:]:
        f = line.split("\t")
        if len(f) >= 3 and f[3] == "no-print-on-page":
            rows.append((f[1], f[0], f[2]))
    names = sorted({r[0] for r in rows})
    print("no-print names:", len(names))

    # single pass title index
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
        t = m.group(1)
        # "NAME (Windows Embedded CE 6.0)" / "NAME Function" / bare NAME
        cand = re.split(r"\s*\(", t)[0].strip()
        cand = re.sub(r"\s+(Function|Method|Structure|Constant)$", "", cand)
        k = cand.lower()
        if k in want:
            title_map.setdefault(want[k], []).append(f)
    print("names with twin-title pages:", len(title_map))

    decl_cache = {}

    def header_decl(path, name):
        if path not in decl_cache:
            txt = open(path, encoding="utf-8", errors="replace").read()
            decl_cache[path] = {m.group(2): (m.group(1), m.group(3))
                                for m in pa.DECL.finditer(txt)}
        return decl_cache[path].get(name)

    out = []
    for name, hdr, pid in sorted(rows):
        cands = title_map.get(name, [])
        if not cands:
            out.append((name, hdr, pid, "", "", "no-twin-page", ""))
            continue
        found = None
        for f in cands:
            protos = pa.page_protos(f, name)
            if protos:
                twinpid = ""
                mm = PAGEID.search(os.path.basename(f))
                twinpid = mm.group(1) if mm else ""
                found = (f, twinpid, protos[0])
                break
        if not found:
            out.append((name, hdr, pid, cands[0], "", "no-print-in-twin", ""))
            continue
        tf, tpid, (tret, tname, tparams) = found
        tret = re.sub(r"\s+", " ", tret).strip()
        hd = header_decl(hdr, name)
        if hd is None:
            out.append((name, hdr, pid, tf, tpid, "no-header-decl", ""))
            continue
        hret, hpraw = hd
        hret = re.sub(r"\s+", " ", hret).strip()
        hparams, ok = pa.norm_params(hpraw)
        if not ok:
            out.append((name, hdr, pid, tf, tpid, "hdr-complex", ""))
            continue
        diffs = []
        if hret.replace("STDAPI", "").strip() != tret.replace("STDAPI", "").strip():
            diffs.append("ret: hdr='%s' twin='%s'" % (hret, tret))
        if len(hparams) != len(tparams):
            diffs.append("argc: hdr=%d twin=%d" % (len(hparams), len(tparams)))
        else:
            for i, (a, b) in enumerate(zip(hparams, tparams)):
                if not pa.types_equal(a, b):
                    diffs.append("arg%d: hdr='%s' twin='%s'" % (i + 1, a, b))
        ptxt = "%s %s(%s)" % (tret, tname, ", ".join(tparams))
        st = "twin-match" if not diffs else "twin-diff"
        out.append((name, hdr, pid, tf, tpid, st,
                    ("; ".join(diffs) if diffs else "") + " | " + ptxt[:160]))
    path = "docs/twin-proto-scan-2026-09-18.tsv"
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("name\thdr\tcited-pid\ttwin-path\ttwin-pid\tstatus\tprint\n")
        for r in out:
            fh.write("\t".join(r) + "\n")
    import collections
    print(collections.Counter(r[5] for r in out))
    print("wrote", path)


if __name__ == "__main__":
    main()
