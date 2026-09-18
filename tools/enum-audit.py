#!/usr/bin/env python3
"""enum-audit.py -- enumerator cross-check of typedef enums in include/
against the corpus pages cited for them.

For every `typedef enum {...} NAME;` the governing citation is the
nearest preceding comment carrying a page id.  The page is searched
for a printed `typedef enum ... NAME` block; enumerator names are
compared in order, and every value the page prints explicitly is
compared against the header's effective value (explicit or sequential).
Enums whose body contains preprocessor gates are recorded, not
compared (the page prints one variant only).

Usage:
    python3 tools/enum-audit.py <corpus-clone> [--out docs/enum-audit.tsv]
"""
import importlib.util
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_spec = importlib.util.spec_from_file_location(
    "struct_audit", os.path.join(ROOT, "tools/struct-audit.py"))
_sa = importlib.util.module_from_spec(_spec)
sys.modules["struct_audit"] = _sa
_spec.loader.exec_module(_sa)
strip_comments = _sa.strip_comments
PAGEID = _sa.PAGEID
PRE = _sa.PRE

TE = re.compile(r"typedef\s+enum\s*(\w+)?\s*\{(.*?)\}\s*"
                r"([A-Za-z_]\w*)(?:\s*,\s*\*?\s*[A-Za-z_]\w*)*\s*;",
                re.S)


def enum_members(body):
    """[(name, explicit_value_or_None)] from an enum body."""
    body = re.sub(r"/\*.*?\*/", " ", body, flags=re.S)
    # single-line prints with embedded // comments: the comment runs
    # until the next enumerator assignment resumes
    body = re.sub(r"//.*?(?=\s+[A-Za-z_]\w*\s*=|\s*$)", " ", body)
    body = re.sub(r"//[^\n]*", " ", body)
    out = []
    for part in body.split(","):
        part = part.strip()
        if not part:
            continue
        m = re.match(r"^([A-Za-z_]\w*)\s*(?:=\s*([^,]+))?$", part)
        if not m:
            # print lost a comma between bare enumerators
            toks = part.split()
            if len(toks) > 1 and all(
                    re.fullmatch(r"[A-Za-z_]\w*", t) for t in toks):
                out.extend((t, None) for t in toks)
                continue
            return None            # unparseable body
        val = (m.group(2) or "").strip() or None
        out.append((m.group(1), val))
    return out


def eff_value(v):
    try:
        return int(v, 0)
    except (TypeError, ValueError):
        return None


def main():
    corpus = sys.argv[1]
    out = "docs/enum-audit-2026-09-18.tsv"
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
            if not fn.endswith((".h", ".hpp")):
                continue
            s = open(os.path.join(d, fn), encoding="utf-8",
                     errors="replace").read()
            sc = strip_comments(s)
            for m in TE.finditer(sc):
                tag, body, name = m.groups()
                hdr = os.path.join(dirpath, fn)
                back = s[max(0, m.start() - 1500):m.start()]
                cm = back.rfind("/*")
                gov = back[cm:] if cm >= 0 else ""
                ids = PAGEID.findall(gov)
                if re.search(r"^\s*#", body, re.M):
                    bump("gated")
                    rows.append((hdr, name, "", "gated", ""))
                    continue
                a = enum_members(body)
                if a is None:
                    bump("unparseable")
                    rows.append((hdr, name, "", "unparseable", ""))
                    continue
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
                h = open(pg, encoding="utf-8", errors="replace").read()
                printed = None
                ptag = ""
                import html as _html
                for blk in PRE.findall(h):
                    blk = re.sub(r"(?i)<br\s*/?>", "\n", blk)
                    t = _html.unescape(re.sub(r"<[^>]+>", " ", blk))
                    t = re.sub(r"[ \t]+", " ", t)
                    mm = re.search(
                        r"typedef\s+enum\s*(\w*)\s*\{(.*?)\}\s*%s\b"
                        % re.escape(name), t, re.S)
                    if mm:
                        ptag, printed = mm.group(1), mm.group(2)
                        break
                if printed is None:
                    bump("no-print-on-page")
                    rows.append((hdr, name, pid, "no-print-on-page", ""))
                    continue
                if ptag and tag and ptag != tag:
                    bump("MISMATCH-tag")
                    rows.append((hdr, name, pid, "MISMATCH-tag",
                                 "hdr=%s page=%s" % (tag, ptag)))
                    continue
                if "," not in printed and \
                        len(re.findall(r"[A-Za-z_]\w*\s*=", printed)) > 1:
                    # print lost its commas ('A = 0 B = 1')
                    printed = re.sub(r"\s+(?=[A-Za-z_]\w*\s*=)",
                                     ", ", printed)
                b = enum_members(printed)
                if b is None:
                    bump("page-unparseable")
                    rows.append((hdr, name, pid, "page-unparseable",
                                 re.sub(r"\s+", " ", printed)[:160]))
                    continue
                an = [x[0] for x in a]
                bn = [x[0] for x in b]
                if an != bn:
                    if re.search(r"(?i)artifact|page print|omits", gov):
                        bump("annotated-deviation")
                        rows.append((hdr, name, pid, "annotated-deviation",
                                     "hdr=%s page=%s"
                                     % (",".join(an), ",".join(bn))))
                    else:
                        bump("MISMATCH-names")
                        rows.append((hdr, name, pid, "MISMATCH-names",
                                     "hdr=%s page=%s"
                                     % (",".join(an), ",".join(bn))))
                    continue
                # effective values: header side
                hv = {}
                nxt = 0
                for nm, v in a:
                    if v is not None:
                        e = eff_value(v)
                        nxt = e + 1 if e is not None else nxt
                        hv[nm] = e if e is not None else v
                    else:
                        hv[nm] = nxt
                        nxt += 1
                bad = []
                nxt = 0
                for nm, v in b:
                    if v is not None:
                        e = eff_value(v)
                        if e is not None:
                            nxt = e
                        if isinstance(hv.get(nm), int) and e is not None \
                                and hv[nm] != e:
                            bad.append("%s: hdr=%d page=%d" % (nm, hv[nm], e))
                        nxt += 1
                    else:
                        nxt += 1
                if bad:
                    bump("MISMATCH-value")
                    rows.append((hdr, name, pid, "MISMATCH-value",
                                 "; ".join(bad[:6])))
                else:
                    bump("match")
                    rows.append((hdr, name, pid, "match", ""))
    outp = os.path.join(ROOT, out)
    with open(outp, "w") as f:
        f.write("# header\tname\tpage\tstatus\tdetail\n")
        for r in rows:
            f.write("\t".join(r) + "\n")
    print("status counts:", dict(sorted(counts.items())))
    print("wrote", outp, len(rows), "rows")


if __name__ == "__main__":
    main()
