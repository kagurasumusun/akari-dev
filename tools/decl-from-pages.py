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
    # M136: ee479349 prints "unsigned __int64 __cdecl __emulu( int int1, int
    # int2 );" -- the signed/unsigned qualifier in front of the MSVC spelling.
    "unsigned __int64", "signed __int64",
    # Freestanding types the compiler's own <stddef.h> provides; Windef.h
    # already includes it for NULL and size_t, so a prototype using one of
    # these compiles even though no header in include/ declares the name.
    "size_t", "ptrdiff_t", "wchar_t", "intptr_t", "uintptr_t", "va_list",
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


def find_cached(cache, page):
    """The cached file for a page id, whatever spelling the corpus used.

    M137: cache_path() rewrites every character outside [A-Za-z0-9_] to `_`,
    so `ee491797(v=winembedded.60)` was looked up as
    `ee491797_v_winembedded_60_.html` while the corpus stores
    `ee491797(v=winembedded.60).html` -- and pages6/ stores the bare
    `ee491797.html`.  Neither matched, so every run silently fell through to
    the network and drew HTTP 429s instead of reading the 52,461 pages that
    were sitting in the cache.  Try the real spellings first.
    """
    base = re.sub(r"\(v=[^)]*\)$", "", page).strip()
    for cand in (page + ".html", base + ".html"):
        p = os.path.join(cache, cand)
        if os.path.exists(p):
            return p
    for f in os.listdir(cache) if os.path.isdir(cache) else ():
        if f.startswith(base + "(v=") and f.endswith(".html"):
            return os.path.join(cache, f)
    p = cache_path(cache, page)
    return p if os.path.exists(p) else None


def fetch(page, cache, sleep=0.4):
    p = find_cached(cache, page)
    if p:
        return open(p, encoding="utf-8", errors="replace").read()
    p = cache_path(cache, page)
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


_DECLARED = None


def declared_in_tree(include_dirs=("include", "include/oak")):
    """name -> the header that already declares it, so a rerun is idempotent.

    Running the transcribers twice over the same job list writes every
    declaration once per pass: the second run of the M135 gap pass added a
    second IMAGE_DATA_DIRECTORY to Winnt.h and a second COMPOSITIONSTRING to
    Imm.h, and `make check` reported both as redefinitions.  A pass has to
    subtract what the tree already declares, not only what it emitted in
    this run.
    """
    global _DECLARED
    if _DECLARED is None:
        _DECLARED = {}
        for d in include_dirs:
            if not os.path.isdir(d):
                continue
            for f in sorted(os.listdir(d)):
                if not f.endswith((".h", ".hpp", ".hxx")):
                    continue
                rel = os.path.join(d, f)
                t = open(rel, encoding="utf-8", errors="replace").read()
                t = re.sub(r"(?s)/\*.*?\*/", " ", t)
                names = set(re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)", t, re.M))
                names |= set(re.findall(r"^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*[\{;]", t, re.M))
                # M136: `typedef struct TAG { ... } NAME;` -- the tag is a
                # declared name too (reachable as `struct TAG`), and this
                # pattern set missed it because the line starts with
                # `typedef` and the closing-declarator scan only sees NAME.
                # include/Af_irda.h:130 already carried
                # `typedef struct IRDA_DEVICE_INFO { ... } _IRDA_DEVICE_INFO;`
                # and the gap pass wrote a second identical copy of it.
                names |= set(re.findall(r"^\s*typedef\s+(?:struct|union|enum)\s+"
                                        r"([A-Za-z_]\w*)\s*\{", t, re.M))
                names |= set(re.findall(r"AKARI_CE_NAME\(([A-Za-z_]\w*)\)", t))
                for m in re.finditer(r"\}\s*([^;{}()#]*);", t):
                    for part in m.group(1).split(","):
                        if "(" in part:
                            continue
                        ids = re.findall(r"[A-Za-z_]\w*", part)
                        if ids:
                            names.add(ids[-1])
                # M137: the scan above was single-line (`[^;{\n(]*`), so a
                # typedef wrapped across two lines was invisible and got
                # written a second time.  include/Wzcsapi.h:77 carries
                # `typedef struct _WZC_802_11_CONFIG_LIST WZC_802_11_CONFIG_LIST,\n
                #     *PWZC_802_11_CONFIG_LIST;` and the corpus pass emitted a
                # second definition of the same names, which is a duplicate
                # member set because WZC_WLAN_CONFIG is held opaque.  Newlines
                # are allowed now; `(` still excludes the function-pointer
                # typedefs the next scan owns.
                for m in re.finditer(r"^\s*typedef\s+([^;{()]*);", t, re.M):
                    for part in m.group(1).split(","):
                        ids = re.findall(r"[A-Za-z_]\w*", part)
                        if ids:
                            names.add(ids[-1])
                for m in re.finditer(r"\(\s*(?:APIENTRY|WINAPI|CALLBACK|STDMETHODCALLTYPE)?"
                                     r"\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(", t):
                    names.add(m.group(1))
                # M136: plain prototypes.  Not every declaration in this tree
                # carries AKARI_CE_NAME -- include/Notifext.hxx:55 is a bare
                # `int CeNotifyPublic_Initialize(HINSTANCE hInst, HWND hwndUI);`
                # from an earlier milestone, and because this index only read
                # AKARI_CE_NAME(...) the gap pass added a second
                # CeNotifyPublic_Initialize with the CE 6.0 page's `void`
                # parameter list, which make check reported as conflicting
                # types.  The identifier immediately before `(` is the name.
                for m in re.finditer(r"^\s*(?:AKARI_CE_IMPORT\s+)?"
                                     r"(?:[A-Za-z_]\w*\s+)+?([A-Za-z_]\w*)\s*\(", t, re.M):
                    names.add(m.group(1))
                for n in names:
                    _DECLARED.setdefault(n, rel)
    return _DECLARED


_HELD = None


def held_in_tree(include_dirs=("include", "include/oak")):
    """name -> the header that deliberately holds it, so a rerun is a no-op.

    declared_in_tree() strips every comment before it scans, which is right
    for finding declarations and wrong for finding records: a name whose
    only appearance in the tree is a recorded hold ("HELD --", "record-only",
    "recorded verbatim") then reads as undeclared, and the next pass writes a
    real definition over the record.  M137 hit this seven times and every one
    of them broke `make check` -- WZC_802_11_CONFIG_LIST (embeds the held
    WZC_WLAN_CONFIG), QUERYCLIENTCERT (PSecPkgContext_IssuerListInfoEx has no
    CE page), SD_DEBUG_INSTANTIATE_ZONES (a duplicate of the ms920430
    record), DDGPEStandardHeader (a `#define` whose body is a struct),
    DEFINE_CSPROPERTY_SET (continuations inside the parameter list),
    CEDB_FIND_DATA (embeds CEDBASEINFO by value) and
    _MINIDUMP_MEMORY_DESCRIPTOR (embeds the held location descriptor).

    Only comments carrying an explicit hold marker count, and only names the
    tree does not actually declare are consulted, so this cannot hide a real
    declaration -- it can only keep a documented hold documented.
    """
    global _HELD
    if _HELD is None:
        _HELD = {}
        marker = re.compile(r"HELD\b|record-only|recorded verbatim|\bheld\b")
        for d in include_dirs:
            if not os.path.isdir(d):
                continue
            for f in sorted(os.listdir(d)):
                if not f.endswith((".h", ".hpp", ".hxx")):
                    continue
                rel = os.path.join(d, f)
                t = open(rel, encoding="utf-8", errors="replace").read()
                for c in re.findall(r"(?s)/\*.*?\*/", t):
                    if not marker.search(c):
                        continue
                    for n in re.findall(r"[A-Za-z_][A-Za-z0-9_]{2,}", c):
                        _HELD.setdefault(n, rel)
    return _HELD



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


def params_from_print(toks):
    """[(type_prefix, name)] taken from the prototype print itself, or None.

    None means at least one token is not `<type> <name>` -- the archive's
    glued form (`DWORDdwCmpFlags`) or a bare `void` -- so the caller must
    fall back to the Parameters section.  `...` is passed through.
    """
    out = []
    for tok in toks:
        t = tok.strip()
        if t == "...":
            out.append((None, "..."))
            continue
        m = re.match(r"^(.*?)\s+(\**\s*)?([A-Za-z_]\w*)$", t)
        if not m or not m.group(1).strip():
            return None
        out.append((m.group(1).strip() + " " + (m.group(2) or ""), m.group(3)))
    return out or None


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
    # M136: __cdecl and __stdcall are compiler keywords, not #defines in
    # include/, so convention_macros() never puts them in known_conv and
    # strip_conventions() leaves them attached.  __ll_lshift's page (ee479245)
    # prints "__int64 __cdecl __ll_lshift( int64 Mask, int nBit );" and the
    # head arrived here as the single token "__int64 __cdecl".  Drop the
    # calling-convention tokens, then judge what is left.
    kept = [t for t in head.split() if t not in CONV_CHAIN]
    if kept:
        head = " ".join(kept)
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

    # M134: the prototype print is itself a complete parameter list whenever
    # every comma-separated token reads as `<type> <name>` with the type and
    # the name separated by a space.  Plenty of CE pages document fewer
    # parameters in their Parameters section than the prototype has --
    # StringCbCopyNEx (ms860408) prints seven tokens against five documented
    # parameters -- and refusing those lost the whole StringCch*/StringCb*
    # "Ex"/"N" family.  Reading the names off the print is not a guess: they
    # are the page's own prototype.  The glued case the Parameters-section
    # reconstruction exists for (`DWORDdwCmpFlags`, no space to split on)
    # still returns None here and falls through unchanged.
    pairs = params_from_print(toks)
    if pairs is None:
        names = param_names(raw)
        if not names:
            return None, "page prints no Parameters section this parser recognises"
        if len(names) != len(toks):
            return None, "%d prototype tokens vs %d documented parameters" % (
                len(toks), len(names))
        pairs = []
        for tok, pn in zip(toks, names):
            if not (tok.endswith(pn) and len(tok) > len(pn)):
                return None, 'parameter "%s" does not end token "%s"' % (pn, tok)
            pairs.append((tok[: -len(pn)], pn))

    args, rendered = [], []
    for prefix, pn in pairs:
        if pn == "...":
            rendered.append("...")
            continue
        const, base, stars = split_type(prefix, known)
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
    # M135: some pages print "Link Library: none." -- not a missing row, an
    # explicit none (ms860404, StringCbGetsEx, whose 29 siblings all print
    # strsafe.lib).  There is no library to import the name from, so marking
    # it AKARI_CE_IMPORT would promise a symbol nothing provides and no
    # def/*-doc.def may export it either.  Report, do not declare.
    if re.search(r"Link\s+Library\s*:?\s*(?:</\w+>\s*)?none\b",
                 re.sub(r"<[^>]+>", " ", raw), re.I):
        return None, ('page prints "Link Library: none." -- nothing exports '
                      'this name, so no import declaration is admissible')
    # M136: a page with no Link Library row at all is in the same position as
    # one that prints an explicit none -- there is no module to import the
    # name from.  ee479764 (__emul) and ee479349 (__emulu) print
    # "Architecture: MIPS 32, MIPS IV, ... / Header: winnt.h / Routine: __emul"
    # and no Library row: they are compiler helper routines for 64-bit
    # multiplication on a 32-bit target, not coredll exports, and their
    # prototypes are spelled in __int64, which the host compiler make check
    # runs does not even have.  Marking them AKARI_CE_IMPORT promised symbols
    # nothing provides.
    plain = re.sub(r"<[^>]+>", " ", raw)
    reqm = re.search(r"id=[\"']requirements[\"'](.*?)(?:</table>|</p>)", raw, re.S)
    if reqm and not re.search(r"\bLibrary\b", re.sub(r"<[^>]+>", " ", reqm.group(1)), re.I):
        return None, ("page prints no Link Library row -- no module exports "
                      "this name, so no import declaration is admissible")
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
    declared = declared_in_tree(a.include)
    held = held_in_tree(a.include)
    for job in jobs:
        # Idempotency: a name the tree already declares is a no-op, whether
        # an earlier pass of this tool wrote it or it was hand-written.
        if job["name"] in declared:
            # `bad` is the skip list (3-tuples, reported as SKIP); `skipped`
            # is the error list (2-tuples, reported as ERROR).  M136 put this
            # 3-tuple in `skipped`, so the report loop's
            # `for n, why in skipped` raised ValueError -- and because that
            # happens after the transcribing loop but before the write, every
            # --write run over a list containing an already-declared name
            # crashed having declared everything and written nothing.
            bad.append((job["name"], norm_page(job["page"]) or job["page"],
                        "already declared in " + declared[job["name"]]))
            continue
        # M137: a name the tree *holds* on purpose reads as undeclared
        # above because the record lives in a comment, and a pass that
        # cannot see it writes a definition over the record.
        if job["name"] in held:
            bad.append((job["name"], norm_page(job["page"]) or job["page"],
                        "deliberately held in " + held[job["name"]]))
            continue
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
        # M135: prefer the generation gate's #endif over the include guard's
        # -- see the same note in tools/decl-types-from-pages.py.
        gated = [i2 for i2 in ends if "_WIN32_WCE" in L[i2]]
        cxx = [i2 for i2 in ends if "__cplusplus" in L[i2]]
        if ends:
            # Same precedence as tools/decl-types-from-pages.py's
            # insertion_point(): the generation gate first, then the
            # __cplusplus region, then the include guard.
            ei = max(gated or cxx or ends)
            # M137: an `#ifdef __cplusplus` / `}` / `#endif` region is the
            # extern "C" *closer*, so inserting before its #endif lands the
            # new block after the closing brace and outside extern "C".  If
            # the only thing above that #endif is the brace, go before the
            # #ifdef.  Mirrors insertion_point() in the types transcriber.
            j = ei - 1
            while j >= 0:
                t2 = L[j].strip()
                if not t2 or t2.startswith(("/*", "*", "//")) or t2 == "}":
                    j -= 1
                    continue
                if t2.startswith("#ifdef __cplusplus") or \
                        t2.startswith("#if defined(__cplusplus)"):
                    ei = j
                break
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
