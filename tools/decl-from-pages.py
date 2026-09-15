#!/usr/bin/env python3
"""Declare app-layer functions from their official Windows CE pages.

The corpus rows carry a `sig` field that cannot be used to transcribe a
prototype: only 10 of the 357 documented-but-undeclared names had a `sig`
that parsed at all, and none of those was usable (one was the page's
example call, one had a parameter glued to its type, eight were SNDMSG
macros rather than exports).

The reason is in the archive itself.  The prototype is served as a single
text node with the space between each parameter type and its name lost --
ms904713's source is literally

    <pre><code>intCompareString(LCIDLocale, DWORDdwCmpFlags, ...

with no markup between the tokens, so no parser recovers the spacing.
What the page *does* still print intact is its Parameters section, which
names every parameter.  So the reconstruction is: take each parameter
name from the Parameters section, and the type is whatever prefixes it in
the print -- which must be a type this tree already declares.  Anything
that does not resolve that way is reported, never guessed.

Usage:
    tools/decl-from-pages.py --list jobs.json [--write] [--header include/X.h]

`jobs.json` is a list of {"name","page","lib","os"} where `page` is the
archive page id (`ms904713` or `ms904713(v=msdn.10)`).  Without --write
the tool only reports; with --write it inserts the declarations before
the final #endif of --header.  Pages are cached under --cache so a rerun
costs no requests.
"""
import argparse
import html
import json
import os
import re
import sys
import time
import urllib.request

UA = "Mozilla/5.0 (Akari API surface transcription; contact: repo maintainer)"
BASE = "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/"

# Types that need no lookup because they are built into the transcription
# language rather than declared by a header.
PRIMITIVE = {
    "int", "void", "char", "short", "long", "float", "double", "unsigned",
    "signed", "BOOL", "BYTE", "WORD", "DWORD", "LONG", "ULONG", "UINT",
    "HRESULT", "LCID", "LCTYPE", "CALID", "CALTYPE", "HANDLE", "HWND",
    "HFONT", "HINSTANCE", "HMODULE", "HKEY", "LPARAM", "WPARAM", "LRESULT",
    "SIZE_T", "ULONG_PTR", "DWORD_PTR", "INT_PTR", "UINT_PTR",
    # M134: the archive prints C's multi-word spellings verbatim on the CE 6.0
    # pages (BthSetCODInquiryFilter prints "unsigned int cod"), and those are
    # language types, not header-declared ones.
    "unsigned int", "unsigned long", "unsigned short", "unsigned char",
    "signed int", "signed long", "long long", "unsigned long long",
    "long double", "__int64", "__int32", "__int16", "__int8",
}


CONV_CHAIN = {"WINAPI", "WINAPIV", "CALLBACK", "__cdecl", "__stdcall"}
# Shape filter: only linkage/calling-convention and parameter-annotation
# macros are stripped.  Every one of these is defined empty (or as WINAPI)
# in this tree, and none carries type information on Windows CE.
CONV_SHAPE = re.compile(r"^(?:.*(?:API|ENTRY|CALLTYPE)$"
                        r"|WINAPI|WINAPIV|CALLBACK|VCAPITYPE|FAR|NEAR"
                        r"|IN|OUT|OPTIONAL|UNALIGNED|__cdecl|__stdcall)$")


def convention_macros(include_dirs):
    """Names this tree defines as an empty (or convention-only) macro.

    The archive prints prototypes with the linkage/calling-convention macro
    still attached -- ms911790 prints 'int MapWindowPoints(' but the
    CreatePartition page prints 'BOOL WINAPI CreatePartition('.  On Windows
    CE these carry no type: windef.h defines WINAPI empty, and CALLBACK,
    WINAPIV, VCAPITYPE, WINGDIAPI, WINUSERAPI and WSAAPI all reduce to it.
    Collecting the list from the tree rather than hardcoding it keeps the
    strip grounded in what this SDK actually defines.
    """
    empty = set()
    pat = re.compile(r"^\s*#\s*define\s+([A-Za-z_]\w*)\s*(.*)$")
    for d in include_dirs:
        for dirpath, _, files in os.walk(d):
            for f in files:
                if not f.endswith((".h", ".hxx", ".hpp")):
                    continue      # WINGDIAPI/WINUSERAPI live in the .hpp set
                for line in open(os.path.join(dirpath, f),
                                 encoding="utf-8", errors="replace"):
                    m = pat.match(line)
                    if not m:
                        continue
                    name, val = m.group(1), m.group(2)
                    val = re.sub(r"/\*.*?\*/", " ", val)
                    val = re.sub(r"//.*$", "", val).strip()
                    if (val == "" or val in CONV_CHAIN) and CONV_SHAPE.match(name):
                        empty.add(name)
    return empty


def strip_conventions(text, macros):
    """Drop linkage/calling-convention macros from a type expression."""
    toks = [t for t in re.split(r"\s+", text.strip()) if t]
    kept = [t for t in toks if t not in macros]
    return " ".join(kept) if kept else " ".join(toks)


# M134: CE 6.0 pages print SAL parameter annotations inside the prototype
# (`LONG CeRegGetInfo(__in HKEY hKey, __inout PCE_REGISTRY_INFO pInfo)`).
# SAL is an annotation language, not a type language -- __in/__out/__inout
# and their _In_/_Out_ spellings carry no type and are not defined by any
# CE header, so they must be dropped before the type is resolved.  Without
# this the parser reported the type of hKey as "__in HKEY" and refused the
# declaration, which is how three winreg.h exports stayed undeclared.
SAL_BASE = re.compile(r"^_+(?:deref_)?(?:opt_)?(?:in|out|inout|opt|reserved"
                      r"|success|checkReturn|field_|struct_|callback|post"
                      r"|pre|format_string)(?![A-Za-z0-9])", re.I)


def strip_sal(text):
    """Drop SAL parameter annotations, which are not types.

    Handled token-wise so the sized forms survive: the archive prints
    `__inout_bcount(nBufferLength)`, `__in_bcount(cbOldData) __opt` and the
    `_In_`/`_Out_` spellings alike, and a keyword-prefix regex alone leaves
    a trailing `out_bcount(nBufferLength)` behind.  The `\b` after the
    keyword is what keeps real identifiers safe -- `_outp`, `_inp` and
    `_interlockedincrement` all start with a SAL keyword plus a letter and
    are left alone.
    """
    kept = []
    for tok in re.split(r"\s+", text.strip()):
        if tok and SAL_BASE.match(tok.split("(")[0]):
            continue
        kept.append(tok)
    return " ".join(kept)


def norm_page(pid):
    """`ms904713` and `ms904713(v=msdn.10)` both name one archive page."""
    m = re.match(r"^([A-Za-z0-9_]+)(\(v=[^)]+\))?$", pid.strip())
    if not m:
        return None
    return m.group(1) + (m.group(2) or "(v=msdn.10)")


def cache_path(cache, page):
    return os.path.join(cache, re.sub(r"[^A-Za-z0-9_]", "_", page) + ".html")


def fetch(page, cache, sleep=0.4):
    p = cache_path(cache, page)
    if os.path.exists(p):
        return open(p, encoding="utf-8", errors="replace").read()
    req = urllib.request.Request(BASE + page, headers={"User-Agent": UA})
    raw = urllib.request.urlopen(req, timeout=45).read().decode("utf-8", "replace")
    os.makedirs(cache, exist_ok=True)
    open(p, "w", encoding="utf-8").write(raw)
    time.sleep(sleep)
    return raw


def text_of(fragment):
    """HTML to text, turning a tag boundary into a space.

    The prototype tokens are glued together in the source, so this cannot
    unglue them; it only stops inline markup from gluing tokens that the
    page did separate.
    """
    s = re.sub(r"</?(?:span|b|i|em|strong|a|code|pre|br|div|p)\b[^>]*>", " ", fragment)
    s = re.sub(r"<[^>]+>", "", s)
    s = html.unescape(s).replace("\xa0", " ")
    s = re.sub(r"[ \t]+", " ", s)
    return re.sub(r" ?\n ?", "\n", s).strip()


def title_of(raw):
    m = re.search(r"<title>(.*?)</title>", raw, re.S)
    return html.unescape(m.group(1)).strip() if m else "?"


def prints(raw):
    """Every <pre>/<code> block, longest last, that looks like a prototype."""
    out = []
    for blk in re.findall(r"<(?:pre|code)[^>]*>(.*?)</(?:pre|code)>", raw, re.S):
        t = text_of(blk)
        if "(" in t and len(t) < 900:
            out.append(t)
    return out


def param_names(raw):
    """Parameter names from the Parameters section, in page order.

    The archive renders that section two ways: `<li><p><em>n</em>` and,
    on the majority of pages, `<li><em>n</em><br>` with no <p> wrapper.
    Only matching the first is why an earlier pass recovered no names for
    FoldString, the Enum* family and SetLocaleInfo.
    """
    i = raw.find('id="parameters"')
    if i < 0:
        return []
    j = raw.find('id="return', i)
    seg = raw[i:j if j > 0 else i + 40000]
    # stop at the next section so a following <ul> cannot contribute
    cut = re.search(r"<h[234]\b", seg[20:])
    if cut:
        seg = seg[: cut.start() + 20]
    names = re.findall(r"<li>\s*(?:<p>)?\s*<em>(.*?)</em>", seg)
    if not names:
        # M134: Windows Embedded CE 6.0 renders Parameters as a two-column
        # table instead of a list --
        #   <tr><td><p><em>dwProcessId</em></p></td><td><p>A process ...</p></td></tr>
        # -- so every CE 6.0 page reported "no Parameters section this parser
        # recognises".  Take the <em> of the first cell of each body row; the
        # second cell is prose and must not contribute names.
        for tr in re.findall(r"<tr\b.*?</tr>", seg, re.S):
            if re.search(r"<th\b", tr, re.I):
                continue                      # the "Parameter|Description" head
            cells = re.findall(r"<td\b[^>]*>(.*?)</td>", tr, re.S)
            if not cells:
                continue
            em = re.search(r"<em>(.*?)</em>", cells[0], re.S)
            if em:
                names.append(html.unescape(em.group(1)).strip())
    if not names:
        # M134: a third shape omits the <em> too -- CheckRemoteDebuggerPresent
        # (ee488625) prints `<li>hProcess<br> [in] Handle to the process.</li>`.
        # The name is the bare identifier before the <br>.
        names = re.findall(r"<li>\s*([A-Za-z_]\w*)\s*<br", seg)
    return [html.unescape(n).strip() for n in names]


def known_types(include_dirs):
    """Every type name this tree declares, so a recovered type can be checked."""
    found = set(PRIMITIVE)
    for d in include_dirs:
        if not os.path.isdir(d):
            continue
        for f in sorted(os.listdir(d)):
            if not f.endswith((".h", ".hpp", ".hxx")):
                continue
            s = open(os.path.join(d, f), encoding="utf-8", errors="replace").read()
            s = re.sub(r"(?s)/\*.*?\*/", " ", s)          # comments name types too
            # M134: a typedef can name several types at once, and the archive
            # then uses the later names in its prototypes.  Winbase.h:429 is
            # `} FILETIME, *PFILETIME, *LPFILETIME;` and Bt_api.h:47 is
            # `typedef ULONGLONG bt_addr, *pbt_addr, BT_ADDR, *PBT_ADDR;`.
            # The old patterns captured only the first declarator, so
            # GetSystemTimeAsFileTime was rejected for an "undeclared"
            # LPFILETIME and BthReadRSSI for BT_ADDR.  Collect them all: in a
            # declarator list every name is the last identifier of its part.
            for m in re.finditer(r"(?:typedef\b|\})\s*([^;{}]*);", s):
                for part in m.group(1).split(","):
                    ids = re.findall(r"[A-Za-z_]\w*", part)
                    if ids:
                        found.add(ids[-1])
            found |= set(re.findall(r"\}\s*(\w+)\s*(?:,[^;]*)?;", s))
            found |= set(re.findall(r"typedef\s+struct\s+(\w+)", s))
            found |= set(re.findall(r"^\s*(?:struct|union|enum)\s+(\w+)\b", s, re.M))
            found |= set(re.findall(r"#define\s+(\w+)", s, re.M))
    return found


def split_type(tok, known):
    """`constCURRENCYFMT*` -> ('const ', 'CURRENCYFMT', '*')."""
    t = tok.strip()
    const = ""
    m = re.match(r"^(?:const|CONST)\s*(.*)$", t)
    if m:
        const, t = "const ", m.group(1).strip()
    stars = ""
    while t.endswith("*"):
        stars += "*"
        t = t[:-1].strip()
    return const, t, stars


def build(job, raw, known, known_conv=frozenset()):
    """Return (declaration, note) or (None, reason)."""
    name = job["name"]
    cands = prints(raw)
    if not cands:
        return None, "page has no prototype block"
    # No \b before the name: the archive glues the return type to it, so the
    # prototype reads `BOOLEnumCalendarInfo(` and a word boundary never fires.
    print_str = None
    for c in cands:
        if re.search(re.escape(name) + r"\s*\(", c):
            print_str = c
            break
    if print_str is None:
        return None, "no prototype block names this function"
    m = re.match(r"^(.*?)" + re.escape(name) + r"\s*\((.*)\)\s*;?\s*$", print_str, re.S)
    if not m:
        return None, "prototype does not parse: " + print_str[:80]
    head, body = m.group(1).strip(), m.group(2).strip()
    callback = ""
    if head.endswith("CALLBACK"):
        head, callback = head[:-8].strip(), "CALLBACK "
    # 'BOOL WINAPI', 'WINUSERAPI HCURSOR WINAPI', 'int WSAAPI' -- the
    # convention macro is part of the printed head but not of the type.
    head = strip_conventions(head, known_conv)
    head = strip_sal(head)
    # The archive loses the space between a type and the convention macro
    # that follows it, so IcmpSendEcho's page prints 'DWORDWINAPI'.  When the
    # single token ends with a macro this tree defines empty, split it.
    if head in known_conv:
        return None, 'prototype prints only a convention macro: "%s"' % head
    if " " not in head:
        for cm in sorted(known_conv, key=len, reverse=True):
            if len(head) > len(cm) and head.endswith(cm):
                head = head[:-len(cm)]
                break
    # 'inline HRESULT SpBindToFile(...)' -- Sphelper.h publishes these as
    # header-inline helpers, so the declaration is a bare prototype and must
    # not be marked AKARI_CE_IMPORT: there is nothing to import.
    # 'inline HRESULT SpClearEvent(...)' -- Sphelper.h publishes these as
    # header-inline helpers.  The archive prints the signature but never the
    # body, and no def exports the name (the page's "Link Library:
    # Sapilib.lib" names the library the helper calls into, not a symbol of
    # this name).  Emitting a bare prototype would promise a symbol nothing
    # provides, and an 'inline' prototype with no body is itself a -Werror
    # failure, so these are reported as blocked rather than declared.
    if re.match(r"^inline\s", head):
        return None, ('page prints an inline helper whose body the archive '
                      'does not publish; nothing to declare')
    ret = head
    if ret not in known:
        return None, 'return type "%s" is not a type this tree declares' % ret

    toks = [t.strip() for t in body.split(",") if t.strip()]
    # the same macros appear inside the parameter list ('LPVOID WINAPI x')
    toks = [strip_sal(strip_conventions(t, known_conv)) for t in toks]
    if len(toks) == 1 and toks[0].lower() == "void":
        if callback or re.search(r"Developer\s+implemented", raw, re.I):
            return (f"{ret} {callback}{name}(void)", print_str)
        return (f"AKARI_CE_IMPORT {ret} {name}(void) AKARI_CE_NAME({name});",
                print_str)

    names = param_names(raw)
    if not names:
        return None, "page prints no Parameters section this parser recognises"
    if len(names) != len(toks):
        return None, "%d prototype tokens vs %d documented parameters" % (
            len(toks), len(names))

    args, rendered = [], []
    for tok, pn in zip(toks, names):
        if not (tok.endswith(pn) and len(tok) > len(pn)):
            return None, 'parameter "%s" does not end token "%s"' % (pn, tok)
        const, base, stars = split_type(tok[: -len(pn)], known)
        if base not in known:
            return None, 'type "%s" (before parameter "%s") is not declared by this tree' % (
                base, pn)
        args.append((const, base, stars, pn))
        rendered.append(f"{const}{base} {'*' * len(stars)}{pn}".replace("* ", "*"))
    sig = f"{ret} {callback}{name}({', '.join(rendered)})"
    # The page's own Requirements row is the authority on whether the name is
    # something this image imports or something the developer implements.
    # ms883928 (DllMain) prints "Link Library: Developer implemented."; so
    # does ms902159 (Lock).  Asserting dllimport for those is wrong, and the
    # e2e DLL, which defines its own DllMain, fails to compile on it.
    devimpl = re.search(r"Developer\s+implemented", raw, re.I) is not None
    if callback or devimpl:
        # an app-implemented callback or a header-inline helper: the page
        # prints no import, so none is asserted here
        return sig + ";", print_str
    return (f"AKARI_CE_IMPORT {ret} {name}({', '.join(rendered)}) "
            f"AKARI_CE_NAME({name});"), print_str


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--list", required=True)
    ap.add_argument("--cache", default="build/pages")
    ap.add_argument("--include", action="append", default=["include", "include/oak"])
    ap.add_argument("--header")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--banner", default="")
    a = ap.parse_args()

    jobs = json.load(open(a.list, encoding="utf-8"))
    known = known_types(a.include)
    known_conv = frozenset(convention_macros(a.include))
    print("convention macros stripped (defined empty in this tree): %s"
          % " ".join(sorted(known_conv)))
    ok, bad, skipped = [], [], []
    for job in jobs:
        page = norm_page(job["page"])
        if not page:
            skipped.append((job["name"], "unparseable page id " + job["page"]))
            continue
        try:
            raw = fetch(page, a.cache)
        except Exception as e:                                    # noqa: BLE001
            skipped.append((job["name"], "fetch failed: %s" % e))
            continue
        decl, why = build(job, raw, known, known_conv)
        if decl is None:
            bad.append((job["name"], page, why))
        else:
            ok.append((job["name"], page, why, decl, title_of(raw),
                       job.get("lib"), job.get("os")))

    for n, p, pr, d, t, lib, osv in ok:
        print("DECLARE %-26s %s" % (n, d[:96]))
    for n, p, why in bad:
        print("SKIP    %-26s %s" % (n, why))
    for n, why in skipped:
        print("ERROR   %-26s %s" % (n, why))
    print("\n%d declared, %d skipped, %d errors" % (len(ok), len(bad), len(skipped)))

    if a.write and ok:
        if not a.header:
            sys.exit("--write needs --header")
        L = open(a.header, encoding="utf-8").read().split("\n")
        ends = [i2 for i2, l in enumerate(L) if l.startswith("#endif")]
        if ends:
            ei = max(ends)
        else:
            # An alias stub (include/Sphelper.h) carries no include guard,
            # so there is no #endif to insert before; append at end of file.
            ei = len(L) - 1
        blk = [""]
        if a.banner:
            lines = a.banner.rstrip("\n").split("\n")
            blk.append("/* " + lines[0])
            for l in lines[1:]:
                blk.append(" * " + l)
            blk[-1] += " */"
            blk.append("")
        for n, pg, pr, d, t, lib, osv in ok:
            blk.append("/* %s %s: print `%s`" % (pg.split("(")[0], n, pr))
            blk.append(" * (%s; Link Library: %s) */"
                       % (osv or "generation not stated", lib or "not stated"))
            blk.append(d)
            blk.append("")
        L[ei:ei] = blk
        open(a.header, "w", encoding="utf-8").write("\n".join(L))
        print("inserted %d declarations into %s" % (len(ok), a.header))


if __name__ == "__main__":
    main()
