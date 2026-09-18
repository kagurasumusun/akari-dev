#!/usr/bin/env python3
"""fnptr-audit.py -- callback (function-pointer typedef) cross-check.

For every `typedef RET (CALL *NAME)(ARGS);` in include/ the governing
citation is the nearest preceding comment carrying a page id.  The
cited page is searched for the callback's printed syntax -- either the
typedef form `RET (*NAME)(ARGS)` or the procedure form
`RET [CALLBACK] NAME(ARGS)` -- and the parameter/return types are
compared with proto-audit's normalizer (handles the archive's glued
print tokens).

Usage:
    python3 tools/fnptr-audit.py <corpus-clone> [--out docs/fnptr-audit.tsv]
"""
import html
import importlib.util
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_spec = importlib.util.spec_from_file_location(
    "proto_audit", os.path.join(ROOT, "tools/proto-audit.py"))
pa = importlib.util.module_from_spec(_spec)
sys.modules["proto_audit"] = pa
_spec.loader.exec_module(pa)

FP = re.compile(r"typedef\s+([^;{}()]*?)\(\s*(?:\w+\s+)*\*\s*"
                r"([A-Za-z_]\w*)\s*\)\s*\(([^;]*?)\)\s*;", re.S)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")
PRE = re.compile(r"<pre[^>]*>(.*?)</pre>", re.S)


def name_variants(name):
    """The typedef name plus the procedure-style names a page may
    print (LP/PFN/PF/P pointer prefixes dropped); matched
    case-insensitively because the archive re-cases freely."""
    vs = [name]
    for p in ("LP", "PFN", "PF", "P"):
        if name.startswith(p) and len(name) - len(p) >= 4:
            vs.append(name[len(p):])
            break
    return vs


def page_prints(path, name):
    """[(ret, args)] printed for NAME on the page."""
    h = open(path, encoding="utf-8", errors="replace").read()
    out = []
    for blk in PRE.findall(h):
        blk = re.sub(r"(?i)<br\s*/?>", "\n", blk)
        t = html.unescape(re.sub(r"<[^>]+>", " ", blk))
        t = re.sub(r"[ \t]+", " ", t)
        for nm in name_variants(name):
            en = re.escape(nm)
            # typedef form (the 'typedef' keyword may be missing or
            # glued: 'typedefVOID (*NDIS_PROC) (...)')
            for m in re.finditer(
                    r"(?:typedef\s*)?([^;{}()]*?)\(\s*\*?\s*" + en +
                    r"\s*\)\s*\(([^)]*)\)", t, re.I):
                out.append((m.group(1), m.group(2)))
            # procedure form: RET [CALLBACK] NAME(args) -- decorations
            # may be glued to the name ('UINTCALLBACKPageSetupHook(')
            for m in re.finditer(
                    r"([A-Za-z_][\w \t\*]*?)(?:CALLBACK|CALLAPI|"
                    r"APIENTRY)?\s*" + en +
                    r"\s*\(([^)]*?)(?:\)\s*(?:[;{]|$)|$)",
                    t, re.I):
                out.append((m.group(1), m.group(2)))
    return out


def main():
    corpus = sys.argv[1]
    out = "docs/fnptr-audit-2026-09-18.tsv"
    for a in sys.argv:
        if a.startswith("--out="):
            out = a.split("=", 1)[1]
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
    rows = []
    counts = {}

    def bump(st):
        counts[st] = counts.get(st, 0) + 1

    for dirpath in ("include", "include/oak"):
        d = os.path.join(ROOT, dirpath)
        for fn in sorted(os.listdir(d)):
            if not fn.endswith((".h", ".hpp", ".hxx")):
                continue
            s = open(os.path.join(d, fn), encoding="utf-8",
                     errors="replace").read()
            sc = pa.strip_comments(s)
            for m in FP.finditer(sc):
                ret, name, args = (re.sub(r"\s+", " ", g).strip()
                                   for g in m.groups())
                ret = ret.replace("typedef", "").strip()
                hdr = os.path.join(dirpath, fn)
                back = s[max(0, m.start() - 1500):m.start()]
                cm = back.rfind("/*")
                gov = back[cm:] if cm >= 0 else ""
                ids = PAGEID.findall(gov)
                if not ids:
                    bump("no-pageid")
                    rows.append((hdr, name, "", "no-pageid", ""))
                    continue
                pid = ids[0]
                pg = pages.get(pid)
                if not pg:
                    bump("page-not-in-corpus")
                    rows.append((hdr, name, pid, "page-not-in-corpus", ""))
                    continue
                prints = page_prints(pg, name)
                if not prints:
                    bump("no-print-on-page")
                    rows.append((hdr, name, pid, "no-print-on-page", ""))
                    continue
                ha, hok = pa.norm_params(args)
                if not hok:
                    bump("unparseable-header")
                    rows.append((hdr, name, pid, "unparseable-header", ""))
                    continue
                hret = pa.norm_type(ret)
                ok = False
                detail = ""
                for pret, pargs in prints:
                    pr, pok = pa.norm_params(pargs)
                    if not pok:
                        continue
                    pr0 = re.sub(r"(?i)^\s*typedef", "", pret.strip())
                    pret_t = pa.norm_type(re.sub(
                        r"\b(typedef|CALLBACK|CALLAPI|APIENTRY)\b",
                        " ", pr0))
                    same_args = (len(pr) == len(ha) and all(
                        pa.types_equal(x, y) for x, y in zip(pr, ha)))
                    same_ret = pa.types_equal(pret_t, hret)
                    if same_args and same_ret:
                        ok = True
                        break
                    detail = "page-ret=%r hdr-ret=%r page-args=%d hdr-args=%d" % (
                        pret_t, hret, len(pr), len(ha))
                if ok:
                    bump("match")
                    rows.append((hdr, name, pid, "match", ""))
                elif re.search(r"(?i)artifact|page print|omits|typo", gov):
                    bump("annotated-deviation")
                    rows.append((hdr, name, pid, "annotated-deviation",
                                 detail))
                else:
                    bump("MISMATCH")
                    rows.append((hdr, name, pid, "MISMATCH", detail))
    outp = os.path.join(ROOT, out)
    with open(outp, "w") as f:
        f.write("# header\tname\tpage\tstatus\tdetail\n")
        for r in rows:
            f.write("\t".join(r) + "\n")
    print("status counts:", dict(sorted(counts.items())))
    print("wrote", outp, len(rows), "rows")


if __name__ == "__main__":
    main()
