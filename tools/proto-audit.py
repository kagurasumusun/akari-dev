#!/usr/bin/env python3
"""proto-audit.py -- prototype-level cross-check of include/ against the corpus.

For every AKARI_CE_IMPORT declaration in include/, finds the official
page cited in the preceding comment, extracts the page-printed
prototype, and compares (function name, return type, parameter type
sequence).  The archive's prototypes glue type and parameter-name
tokens ("DWORDdwExitCode"); the comparison unglues them with a lexicon
built from the tree's own typedefs plus C builtins, so a mismatch
means a real divergence, not an artifact.

Usage:
    python3 tools/proto-audit.py <corpus-clone> [--out docs/proto-audit.tsv]
"""
import html
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DECL = re.compile(r"AKARI_CE_IMPORT\s+(.+?)\s+([A-Za-z_]\w*)\s*\(([^;]*?)\)\s*"
                  r"AKARI_CE_NAME\(\2\)\s*;", re.S)
PAGEID = re.compile(r"\b([a-z]{2}\d{6})\b")
PRE = re.compile(r"<pre[^>]*>(.*?)</pre>", re.S)

BUILTIN = {"int", "void", "char", "short", "long", "float", "double",
           "signed", "unsigned", "const", "struct", "enum", "union",
           "VOID", "INT", "UINT", "BOOL", "DWORD", "WORD", "BYTE",
           "HRESULT", "ULONG", "USHORT", "UCHAR", "SIZE_T", "LRESULT",
           "PROC", "FARPROC", "SNMPAPI", "LONG", "USHORT"}

# page-print typos (verbatim page text vs. the evidently intended type;
# each occurrence is annotated page-typo in the audit output)
PAGE_TYPO = {"HESULT": "HRESULT", "SAFEARRRAYBOUND": "SAFEARRAYBOUND",
             "CURRENTY": "CURRENCY", "LPwSTR": "LPWSTR",
             "ItypeInfo": "ITypeInfo", "IerrorInfo": "IErrorInfo",
             "LHANDLE": "HANDLE", "LPCSCARD_I0_REQUEST": "LPCSCARD_IO_REQUEST",
             "BOOLAPI": "BOOL", "voidWINAPI": "void WINAPI",
             "CONST": "const", "PTCHAR": "LPTSTR"}


def build_lexicon():
    lex = set(BUILTIN)
    pat = re.compile(r"^\s*(?:typedef\s+.*?\s)?\b([A-Z][A-Za-z0-9_]{1,})\s*(?:,|\*|\[|;)",
                     re.M)
    for dirpath in ("include", "include/oak"):
        d = os.path.join(ROOT, dirpath)
        for fn in os.listdir(d):
            if not fn.endswith((".h", ".hpp")):
                continue
            s = open(os.path.join(d, fn), encoding="utf-8", errors="replace").read()
            lex |= set(re.findall(r"}\s*([A-Z][A-Za-z0-9_]*)\s*(?:,|;)", s))
            lex |= set(re.findall(r"typedef\s+[A-Za-z0-9_ \t\*]+?\b([A-Z][A-Za-z0-9_]*)\s*(?:,|;|\[)", s))
            # struct/union/enum typedef names: '} NAME,' / '} NAME;'
            lex |= set(re.findall(r"\}\s*([A-Z_][A-Za-z0-9_]{2,})\s*[,;]", s))
            # struct/union/enum TAG names (struct _X {, union Y {)
            lex |= set(re.findall(r"\b(?:struct|union|enum)\s+(_?[A-Za-z]\w*)\s*[\{;,\)]", s))
            # lowercase typedef names (u_char, u_long, ...) -- needed to
            # unglue prints like "u_charirdaDeviceID"
            lex |= set(re.findall(r"typedef\s+[A-Za-z0-9_ \t\*]+?\b([a-z_][A-Za-z0-9_]*)\s*(?:,|;|\[)", s))
            lex |= set(re.findall(r"^\s*#define\s+([A-Z][A-Z0-9_]*)", s, re.M))
            lex |= set(re.findall(r"\b(L?PC?[A-Z][A-Z0-9_]*|HANDLE|H[A-Z][A-Z0-9]{1,})\b", s))
            # function-pointer typedefs:  typedef ... (*PFN_X)(...)
            lex |= set(re.findall(
                r"typedef[^;]*\(\s*(?:[A-Z][A-Z_]*\s+)*\*\s*([A-Za-z_]\w*)\s*\)", s))
            # callback typedefs:  typedef RET (CALLBACK *NAME)(params);
            lex |= set(re.findall(
                r"typedef\s+\w[\w \t]*\(\s*(?:[A-Z][A-Z_]*\s+)*\*\s*"
                r"([A-Za-z_]\w*)\s*\)\s*\(", s))
            # struct/union tag lists:  } TAG, *PTAG;  /  } VTableProvStruc, *PVTableProvStruc;
            for tail in re.findall(r"}\s*([A-Za-z_][\w, \t\*\n]*);", s):
                for nm in tail.split(","):
                    nm = nm.strip().lstrip("*").strip()
                    if re.fullmatch(r"[A-Za-z_]\w*", nm):
                        lex.add(nm)
    return {t for t in lex if len(t) >= 2}


LEX = build_lexicon()
# doc-decoration words that appear inside page prints (never in headers)
LEX |= {"UNICODE", "ANSI", "IN", "OUT", "OPTIONAL"}
# longest-first alternation for greedy prefix match
LEX_ALT = "|".join(sorted((re.escape(t) for t in LEX), key=len, reverse=True))
UNGLUE = re.compile(r"^(%s)([A-Za-z_][A-Za-z0-9_]*)$" % LEX_ALT)
_CANON = {t.lower(): t for t in LEX}
LEX_ALT_CI = "|".join(sorted((re.escape(t.lower()) for t in LEX),
                             key=len, reverse=True))
UNGLUE_CI = re.compile(r"^(%s)([a-z_][a-z0-9_]*)$" % LEX_ALT_CI)


def unglue(tok):
    """Split glued type+name tokens; recursive for multi-glue strings
    like 'constLPVOIDlpValue'.  The case-insensitive fallback (for page
    case typos like 'AsnTimetickspTimeStamp') requires a >=5-char
    prefix so that short builtin words ('int') cannot eat the front
    of ordinary identifiers ('InterfaceHandle')."""
    out, frontier = [], [tok]
    for _ in range(4):
        nxt = []
        for t in frontier:
            if t in LEX:
                out.append(t); continue
            m = UNGLUE.match(t)
            if m and len(m.group(1)) < len(t):
                rest = m.group(2)
                # an all-caps remainder that is not itself a lexicon
                # word is part of the type name (PNDIS_TIMER_FUNCTION),
                # not a glued parameter name (DWORDLCID -> DWORD+LCID)
                if len(rest) >= 2 and rest.isupper() and rest not in LEX:
                    out.append(t); continue
                nxt.extend((m.group(1), rest)); continue
            low = t.lower()
            m = UNGLUE_CI.match(low)
            # the case-insensitive fallback is for archive case typos in
            # GLUED tokens; a clean single word ('Parameters') must not
            # be split just because it starts with a lexicon word
            clean = re.fullmatch(r"[A-Za-z][a-z0-9_]*|[A-Z0-9_]+", t)
            if m and not clean and 5 <= len(m.group(1)) < len(low):
                nxt.extend((_CANON[m.group(1)], t[len(m.group(1)):])); continue
            out.append(t)
        if not nxt:
            return out
        frontier = nxt
    return out + frontier


def norm_params(raw):
    """Parameter list -> (types, ok).  ok=False when unparseable."""
    raw = raw.strip()
    if raw in ("", "void", "VOID"):
        return [], True
    out = []
    raw = re.sub(r"=[^,]*", " ", raw)          # default arguments
    raw = raw.replace("[", " ").replace("]", " ")
    raw = re.sub(r"\b__(in|out|inout|reserved|deref|checkReturn)\b", " ", raw)
    for p in raw.split(","):
        p = re.sub(r"\s+", " ", p).strip()
        if not p or p in ("argument", "..."):
            continue
        toks = []
        for t in p.split():
            t = t.replace("*", " * ").replace("(", " ( ").replace(")", " ) ")
            toks.extend(x for x in re.split(r"\s+", t) if x)
        # unglue type+name fusions
        ex = []
        for t in toks:
            ex.extend(unglue(t))
        toks = ex
        if "(" in toks:
            return None, False          # function pointer / callback: skip
        # keep type tokens only: drop parameter-name identifiers (any
        # casing) that are not known type words
        star = toks.count("*")
        toks = [PAGE_TYPO.get(t, t) for t in toks]
        # doc-only decoration tokens
        toks = [t for t in toks if t not in
                ("IN", "OUT", "OPTIONAL", "UNICODE", "ANSI")]
        types = [t for t in toks if t == "*" or t in LEX or t in BUILTIN
                 or (len(t) > 3 and t.isupper() and "_" in t)]
        if not types:
            types = [toks[0]] if toks else ["?"]
        types = [t for t in types if t != "*"]
        # trailing parameter name that is itself a known type word
        # ("DWORD LCID"): drop the last token when a full type precedes
        # it and it is not a builtin scalar / qualifier
        if len(types) >= 2 and types[-1] in LEX \
           and types[-1] not in BUILTIN \
           and types[-2] not in ("const", "struct", "enum", "unsigned",
                                 "signed"):
            types = types[:-1]
        t = " ".join(types) + "*" * star
        out.append(re.sub(r"\s*\*\s*", "*", t).replace("const ", "const ").strip())
    return out, True


def norm_type(t):
    t = re.sub(r"\s+", " ", t).strip()
    t = PAGE_TYPO.get(t, t)
    t = re.sub(r"(?<![A-Za-z_])(%s)(?![A-Za-z_])" % "|".join(
        map(re.escape, PAGE_TYPO)), lambda m: PAGE_TYPO[m.group(1)], t)
    # glued macro suffixes ("voidWINAPI")
    t = re.sub(r"(?<=[a-z])(WINAPI|APIENTRY|PASCAL|CALLBACK)\b", r" \1", t)
    # calling-convention / decoration macros: expand-to-nothing on CE
    # declaration macros that name a type (expand FIRST)
    t = re.sub(r"\b(STDAPI|WINOLEAPI|WINOLEAUTAPI)\b", "HRESULT", t)
    # calling-convention / decoration macros: expand-to-nothing on CE
    t = re.sub(r"\b(WINAPI|WINAPIV|WINGDIAPI|WINUSERAPI|WINSHELLAPI|FAR|"
               r"CALLBACK|NEAR|HUGEP|PASCAL|APIENTRY|WSAAPI|__inline|"
               r"__stdcall|__cdecl|CRYPTFUNC|IN|OUT|OPTIONAL|"
               r"COMMCTRLAPI|IMGAPI|D3DMAPI|URLMONAPI|SHSTDAPI_|SHSTDAPI|"
               r"OLESTDAPI|NDSAPI|LDAPAPI_)\b", " ", t)
    # generic-text resolution FIRST (CE is Unicode-only: T -> W), so
    # LPCTSTR and LPCWSTR normalize to the same spelling
    t = re.sub(r"\bLPCTSTR\b", "LPCWSTR", t)
    t = re.sub(r"\bLPTSTR\b", "LPWSTR", t)
    t = re.sub(r"\bTCHAR\b", "WCHAR", t)
    t = t.strip()
    # pointer-spelling aliases: LP<T> == <T>*, LPC<T>/PC<T> == const <T>*,
    # P<T> == <T>* -- only when <T> is a known type word (so LPARAM,
    # PWSTR &c. stay as-is), keeping the C (const) marker distinct
    m = re.match(r"^(PP|LPC|PC|LP|P)([A-Z][A-Z0-9_]+?)(\*+)$", t) \
        or re.match(r"^(PP|LPC|PC|LP|P)([A-Z][A-Z0-9_]+)$", t)
    if m and (m.group(2) in LEX or m.group(2) in BUILTIN):
        stars = m.group(3) if m.lastindex >= 3 else \
            ("**" if m.group(1) == "PP" else "*")
        t = ("const " if m.group(1) in ("LPC", "PC") else "") \
            + m.group(2) + stars
    t = re.sub(r"\s*\*\s*", "*", t)
    t = re.sub(r"\s+", "", t)
    return t.lower()


def norm_type_strict(t):
    """Like norm_type but keeps const/volatile qualifiers (fidelity view)."""
    return norm_type(t)


def types_equal(a, b):
    """Equality modulo const qualifiers (recorded separately as a note)."""
    return norm_type(a).replace("const", "") == norm_type(b).replace("const", "")


def page_protos(path, name):
    """Return list of normalized candidate prototypes for `name` on page."""
    h = open(path, encoding="utf-8", errors="replace").read()
    cands = []
    for blk in PRE.findall(h):
        t = html.unescape(re.sub(r"<[^>]+>", "", blk))
        t = re.sub(r"//[^\n]*", " ", t)
        t = re.sub(r"\s+", " ", t).strip()
        if not re.match(r"^[A-Za-z_][A-Za-z0-9_ \t\*]*?\b%s\s*\(" % re.escape(name), t):
            continue
        m = re.match(r"^(.*?)\b(%s)\s*\((.*?)\)\s*;?\s*$" % re.escape(name), t)
        if not m:
            continue
        ret = re.sub(r"\s+", " ", m.group(1)).strip()
        params, ok = norm_params(m.group(3))
        if not ok:
            return None                 # complex: signal skip
        cands.append((ret, name, params))
    return cands



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

def main():
    corpus = sys.argv[1]
    out = "docs/proto-audit-2026-09-18.tsv"
    for a in sys.argv[2:]:
        if a.startswith("--out="):
            out = a.split("=", 1)[1]
    # corpus page index
    pages = {}
    for base in ("docs/mslearn", "docs/chm"):
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
    for dirpath in ("include", "include/oak"):
        d = os.path.join(ROOT, dirpath)
        for fn in sorted(os.listdir(d)):
            if not fn.endswith((".h", ".hpp")):
                continue
            s = open(os.path.join(d, fn), encoding="utf-8", errors="replace").read()
            for m in DECL.finditer(s):
                ret = re.sub(r"\s+", " ", m.group(1)).strip()
                name, praw = m.group(2), m.group(3)
                if "*" in praw and "(" in praw:
                    st = "skip-callback"; counts[st] = counts.get(st, 0) + 1
                    rows.append((fn, name, "", st, "")); continue
                params, ok = norm_params(praw)
                if not ok:
                    st = "skip-complex"; counts[st] = counts.get(st, 0) + 1
                    rows.append((fn, name, "", st, "")); continue
                # page id from preceding comment
                back = s[max(0, m.start() - 900):m.start()]
                cm = back.rfind("/*")
                cmt = back[cm:] if cm >= 0 else ""
                ids = PAGEID.findall(cmt)
                annotated = bool(re.search(
                    r"artifact|print shows|prints a|printed|the print|"
                    r"print `|\bprint\b|missing comma|dropped|typo", cmt, re.I))
                pid = ids[0] if ids else ""
                hdr = os.path.join(dirpath, fn)
                if not pid:
                    st = "no-pageid"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, "", st, "")); continue
                pg = pages.get(pid)
                if not pg:
                    st = "page-not-in-corpus"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, "")); continue
                base = name[:-1] if name.endswith(("W", "A")) else name
                cands = page_protos(pg, name) or page_protos(pg, base)
                if cands is None:
                    st = "skip-complex-page"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, "")); continue
                if not cands:
                    st = "no-print-on-page"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, "")); continue
                # compare against best candidate; preference order:
                # clean match > const-only diff > page-drops-star >
                # fewest real diffs
                best = None              # (cret, cparams)
                bestdiff = None          # real diffs of the chosen cand
                bestconst = 0
                beststar = []
                for cret, cname, cparams in cands:
                    diffs = []
                    nconst = 0
                    star_drops = []
                    na, nb = norm_type(cret), norm_type(ret)
                    if na != nb:
                        if types_equal(cret, ret):
                            nconst += 1
                        elif "*" in nb and na == nb.replace("*", ""):
                            star_drops.append(-1)
                        else:
                            diffs.append(f"ret: page={cret!r} hdr={ret!r}")
                    if len(cparams) != len(params):
                        diffs.append(f"argc: page={len(cparams)} hdr={len(params)}")
                    else:
                        for i, (a, b) in enumerate(zip(cparams, params)):
                            x, y = norm_type(a), norm_type(b)
                            if x != y:
                                if types_equal(a, b):
                                    nconst += 1
                                elif "*" in y and x == y.replace("*", ""):
                                    star_drops.append(i)
                                else:
                                    diffs.append(f"arg{i}: page={a!r} hdr={b!r}")
                    if not diffs:
                        if not star_drops and nconst == 0:
                            best, bestdiff, bestconst, beststar = \
                                (cret, cparams), [], 0, []
                            break
                        rank = (1 if star_drops else 0, nconst)
                        cur = (1 if beststar else 0, bestconst) \
                            if bestdiff == [] else None
                        if bestdiff != [] or cur is None or rank < cur:
                            best, bestdiff, bestconst, beststar = \
                                (cret, cparams), [], nconst, star_drops
                    elif bestdiff is None or (bestdiff != []
                                              and len(diffs) < len(bestdiff)):
                        best, bestdiff, bestconst, beststar = \
                            (cret, cparams), diffs, nconst, star_drops
                if bestdiff == [] and not beststar:
                    st = "match" if bestconst == 0 else "match-const-diff"
                    counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, ""))
                elif bestdiff == []:
                    st = "page-drops-star"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st,
                                 "args %s: page print omits pointer" % beststar))
                elif annotated:
                    st = "annotated-deviation"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, "; ".join(bestdiff)))
                elif len(bestdiff) == 1 and bestdiff[0].startswith("argc:"):
                    pa = int(re.search(r"page=(\d+)", bestdiff[0]).group(1))
                    ha = int(re.search(r"hdr=(\d+)", bestdiff[0]).group(1))
                    st = "argc-page-short" if pa < ha else "argc-hdr-short"
                    counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, bestdiff[0] +
                                 (" (page print missing comma?)" if pa < ha else "")))
                else:
                    st = "MISMATCH"; counts[st] = counts.get(st, 0) + 1
                    rows.append((hdr, name, pid, st, "; ".join(bestdiff)))
    outp = os.path.join(ROOT, out)
    os.makedirs(os.path.dirname(outp), exist_ok=True)
    with open(outp, "w") as f:
        f.write("# header\tname\tpage\tstatus\tdetail\n")
        for r in rows:
            f.write("\t".join(r) + "\n")
    print("status counts:", dict(sorted(counts.items())))
    print("wrote", outp, len(rows), "rows")


if __name__ == "__main__":
    main()
