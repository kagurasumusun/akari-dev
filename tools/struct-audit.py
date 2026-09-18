#!/usr/bin/env python3
"""struct-audit.py -- member-layout cross-check of struct/union
typedefs in include/ against the corpus pages cited for them.

For every `typedef struct {...} NAME;` (no function-pointer members)
the governing citation is the nearest preceding comment carrying a
page id (only comments/blank lines between).  The page is searched for
a printed `typedef struct ... NAME` prototype; member names are
extracted from both sides (the archive glues type+name tokens, so the
proto-audit lexicon/unglue is reused) and compared in order.

Usage:
    python3 tools/struct-audit.py <corpus-clone> [--out docs/struct-audit.tsv]
"""
import html
import importlib.util
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
spec = importlib.util.spec_from_file_location(
    "proto_audit", os.path.join(ROOT, "tools/proto-audit.py"))
pa = importlib.util.module_from_spec(spec)
sys.modules["proto_audit"] = pa
spec.loader.exec_module(pa)
unglue = pa.unglue
LEX = pa.LEX
BUILTIN = pa.BUILTIN

TS = re.compile(r"typedef\s+(struct|union)\s*(\w+)?\s*\{(.*?)\}\s*"
                r"([A-Za-z_]\w*)(?:\s*,\s*\*?\s*[A-Za-z_]\w*)*\s*;",
                re.S)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")
PRE = re.compile(r"<pre[^>]*>(.*?)</pre>", re.S)



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

_NOUND = None


def nound_map():
    global _NOUND
    if _NOUND is None:
        m = {}
        for w in LEX:
            k = w.lower().replace("_", "")
            if len(k) >= 4 and (k not in m or len(w) > len(m[k])):
                m[k] = w
        _NOUND = sorted(m, key=len, reverse=True)
    return _NOUND


KW = {"struct", "union", "enum", "const", "unsigned", "signed", "short",
      "long", "volatile", "__cdecl", "__fastcall", "near", "far"}
BASE_LOW = {"u_char", "u_short", "u_int", "uint", "uchar", "ushort",
            "short", "long", "int", "char", "float", "double",
            "unsigned", "signed"}
DECOR = {"UNICODE", "ANSI", "IN", "OUT", "OPTIONAL", "__in", "__out",
         "__inout", "CONST"}


def peel_type(tok):
    """Split a GLUED type+name token (archive prints like
    'CRYPT_OBJID_BLOBParameters', 'SdpAttributeRangepRange',
    'uintipr_size').  Returns the name part, or None when the token is
    purely a type word / cannot be split safely."""
    if tok in LEX or tok in BUILTIN:
        return None
    # case-sensitive: only all-caps type words or lowercase primitives,
    # so a clean member name like 'DCBlength' or 'hold_mode_max' is
    # never mistaken for a glued type+name
    cands = [w for w in LEX
             if len(w) >= 3 and tok.startswith(w)
             and re.fullmatch(r"[A-Z][A-Z0-9_]*", w)]
    cands += [w for w in BASE_LOW | BUILTIN | LEX if len(w) >= 3
              and tok.startswith(w)
              and re.fullmatch(r"[a-z][a-z0-9_]*", w)]
    for w in sorted(cands, key=len, reverse=True):
        rest = tok[len(w):]
        if not rest or not re.match(r"^[A-Za-z_]\w*$", rest):
            continue
        prim = not re.fullmatch(r"[A-Z][A-Z0-9_]*", w)
        if prim:
            # lowercase primitive prefixes ('int', 'short') only peel
            # when the rest looks like a member name (digit, '_', a
            # case hump or an uppercase start) -- 'interval' stays whole
            if not re.search(r"[0-9_]|[a-z][A-Z]", rest) \
                    and not rest[0].isupper():
                continue
        return rest, prim
    # case-insensitive (archive case/underscore mangling, e.g.
    # 'SdpAttributeRangepRange'): the prefix must cover most of the
    # token, so small fragments ('hconn' of 'hConnection') never fire
    if "_" not in tok:
        low = tok.lower()
        for k in nound_map():
            if (len(k) >= 5 and low.startswith(k)
                    and len(k) * 2 >= len(low)):
                rest = tok[len(k):]
                if rest and re.match(r"^[a-z_]\w*$", rest):
                    return rest, False
    return None


def member_names(body, peel_glued=True):
    """Ordered member-name list from a C struct/union body, flattening
    nested struct/union blocks."""
    body = re.sub(r"/\*.*?\*/", " ", body, flags=re.S)
    body = re.sub(r"//[^;]*", " ", body)
    names = []
    while True:
        m = re.search(r"\{([^{}]*)\}", body)
        if not m:
            break
        body = body[:m.start()] + " " + m.group(1) + " ; " + body[m.end():]
    body = body.replace("{", " ").replace("}", " ")
    for seg in body.split(";"):
        seg = seg.strip().strip(".").strip()
        seg = re.sub(r"\[[^\]]*\]", " ", seg)
        seg = re.sub(r":\s*\d+", " ", seg)
        if not seg:
            continue
        parts = [p.strip() for p in seg.replace("*", " * ").split(",")]
        for pi, part in enumerate(parts):
            toks = [t for t in part.split() if t not in ("*",)]
            toks = [t.strip(".()") for t in toks]
            toks = [t for t in toks if t and t not in KW
                    and t not in DECOR and t not in
                    ("__RPC_FAR", "RPC_FAR", "_RPC_FAR", "_FAR", "FAR")]
            if not toks:
                continue
            if len(toks) == 1:
                # either a bare name or a glued type+name print
                t = toks[0]
                if t in LEX or t in BUILTIN:
                    names.append(t)      # member named like a type word
                    continue
                if peel_glued:
                    for _ in range(3):   # 'unsignedshortunused1' peels
                        r = peel_type(t)  # in layers, but only through
                        if not r:         # chained lowercase primitives
                            break
                        t, prim = r
                        if not prim:
                            break
                names.append(t)
            else:
                # space-separated: the last token is the clean name
                names.append(toks[-1])
    return names


def main():
    corpus = sys.argv[1]
    out = "docs/struct-audit-2026-09-18.tsv"
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
            sc = strip_comments(s)
            for m in TS.finditer(sc):
                kind, tag, body, name = m.groups()
                hdr = os.path.join(dirpath, fn)
                if "(" in body:
                    bump("skip-fnptr")
                    rows.append((hdr, name, "", "skip-fnptr", ""))
                    continue
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
                h = open(pg, encoding="utf-8", errors="replace").read()
                printed = None
                for blk in PRE.findall(h):
                    t = html.unescape(re.sub(r"<[^>]+>", " ", blk))
                    t = re.sub(r"\s+", " ", t)
                    mm = re.search(
                        r"typedef\s+(?:struct|union)\s*\w*\s*\{(.*)\}\s*%s\b"
                        % re.escape(name), t)
                    if mm:
                        printed = mm.group(1)
                        break
                if printed is None:
                    bump("no-print-on-page")
                    rows.append((hdr, name, pid, "no-print-on-page", ""))
                    continue
                if "WINAPI" in printed or "(*" in printed:
                    bump("fnptr-print")
                    rows.append((hdr, name, pid, "fnptr-print", ""))
                    continue
                if "__cplusplus" in printed or "operator" in printed:
                    bump("cpp-print")
                    rows.append((hdr, name, pid, "cpp-print", ""))
                    continue
                a = member_names(body, peel_glued=False)
                b = member_names(printed)
                if a == b:
                    bump("match")
                    rows.append((hdr, name, pid, "match", ""))
                elif re.search(r"(?i)artifact|missing space|glues|"
                               r"page print", gov):
                    # the governing comment already records the print
                    # defect and how the header was derived from it
                    bump("annotated-deviation")
                    rows.append((hdr, name, pid, "annotated-deviation",
                                 "hdr=%s page=%s"
                                 % (",".join(a), ",".join(b))))
                else:
                    bump("MISMATCH")
                    rows.append((hdr, name, pid, "MISMATCH",
                                 "hdr=%s page=%s" % (",".join(a), ",".join(b))))
    outp = os.path.join(ROOT, out)
    with open(outp, "w") as f:
        f.write("# header\tname\tpage\tstatus\tdetail\n")
        for r in rows:
            f.write("\t".join(r) + "\n")
    print("status counts:", dict(sorted(counts.items())))
    print("wrote", outp, len(rows), "rows")


if __name__ == "__main__":
    main()
