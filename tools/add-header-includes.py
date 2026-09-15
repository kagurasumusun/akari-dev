#!/usr/bin/env python3
"""add-header-includes.py -- give a generated header the #include lines its
own declarations need.

tools/ship-missing-headers.py creates a header with only Windef.h and
Winnt.h, because at that point nothing is known about what the pages will
transcribe.  The declarations that follow use types from all over the tree
-- D3dmx.h uses D3DMFORMAT from D3dm.h, Sms.h uses FILETIME from Winbase.h,
Extapi.h uses HLINE from Tapi.h -- and a header that does not include the
header declaring them does not compile.

Three rules keep this from making things worse:

  * a name the header already reaches transitively needs no include.  TCHAR
    and LPTSTR come from Windef.h, and Tchar.h is the !UNICODE spelling of
    the same names -- including it produced "conflicting types for TCHAR".
    The reachability set is read from the headers themselves, not from the
    name index, because the index keeps only the first header that declares
    a name and Tchar.h sorts before Windef.h.
  * nothing under include/oak is added: an app-layer header must not pull in
    a driver header.
  * a header is never made to include itself or something that already
    reaches it, so no cycle is introduced.

Usage:  tools/add-header-includes.py include/X.h [include/Y.h ...]
        tools/add-header-includes.py --all-new build/shipped-headers.json
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Names that are not declarations of another header: the generation macro and
# this tree's own include guards.
IGNORE = re.compile(r"^(?:_WIN32_WCE|AKARI_[A-Z0-9_]+|__cplusplus"
                    r"|APIENTRY|CALLBACK|FAR|NEAR|STDMETHODCALLTYPE|STDAPI"
                    r"|WINAPI|WINAPIV|WSAAPI"
                    r"|const|struct|enum|union|unsigned|signed|void)$")


# Placement relations the compiler cannot see.  tools/placement-audit.py
# reports a group "unreachable" when the header the pages name does not reach
# the header this tree declares the names in.  Rapitypes2.h is such a case:
# ee497483 (RAPI_CONNECTIONTYPE) and ee496793 (RAPI_DEVICESTATUS) print
# "Header: rapitypes2.h", the tree declares both in Rapitypes.h, and nothing in
# Rapitypes2.h *uses* them -- so the include is not a compile dependency and
# only this table can supply it.
PLACEMENT_INCLUDES = {
    "include/Rapitypes2.h": ("Rapitypes.h",
                             "RAPI_CONNECTIONTYPE (ee497483) and RAPI_DEVICESTATUS "
                             "(ee496793) are documented under rapitypes2.h"),
}


def strip_comments(s):
    s = re.sub(r"(?s)/\*.*?\*/", " ", s)
    return re.sub(r"//[^\n]*", " ", s)


# A name is a *used type* when it is followed by a declarator: `ULONG
# FormatSize;`, `CALLER_ID_OPTIONS cidoOptions;`, `D3DMFORMAT fmt)`.  Reading
# every identifier in the file instead pulled in parameter names -- a Dshow.h
# prototype's `pCaps`, a Winnt.h one's `pv` -- and each of those is also a
# typedef somewhere else in the tree, so Winnt.h grew an #include of
# Shellcb.h and the build deadlocked on an include cycle.
# `const` sits outside the capture group: with it inside, `const SYSTEMTIME
# *ptsCurrentTime,` in Sms.h yielded the single token "const SYSTEMTIME",
# which no header declares, so Sms.h never got its Winbase.h include.
USE = re.compile(r"(?<![A-Za-z0-9_])(?:const\s+)?([A-Za-z_]\w*)\s+\**\s*"
                 r"[A-Za-z_]\w*\s*(?:\[[^\]]*\]\s*)*[;,)=]")
# ...and in return position, which USE cannot see: the declarator of
# `AKARI_CE_IMPORT COLORREF PHGetColor(PH_COLOR Id)` is terminated by `(`, so
# Controldefinitions.h never learned it needed Wingdi.h for COLORREF.
RET = re.compile(r"(?<![A-Za-z0-9_])([A-Za-z_]\w*)\s+\**\s*[A-Za-z_]\w*\s*\(")


def names_in(path):
    r"""Every name this header declares -- types, tags, macros, functions.

    Only real declarations count.  An earlier version also ran
    a `^\s*typedef\s+([^;{\n]*);` pattern over function-pointer typedefs, whose
    parameter list is full of names that are not types (`DWORD dwSize`,
    `PBYTE pBuffer`), and indexed those as if the header declared them.
    """
    s = strip_comments(open(os.path.join(ROOT, path), encoding="utf-8",
                            errors="replace").read())
    names = set(re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)", s, re.M))
    names |= set(re.findall(r"^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*[\{;]", s, re.M))
    names |= set(re.findall(r"AKARI_CE_NAME\(([A-Za-z_]\w*)\)", s))
    # `} NAME, *PNAME;` declarator lists.  Reject a capture holding `(` so a
    # function-pointer typedef's parameter list is never read as names, and
    # reject `#` so the `}` closing `extern "C" {` cannot run across #endif.
    for m in re.finditer(r"\}\s*([^;{}()#]*);", s):
        for part in m.group(1).split(","):
            if "(" in part:
                continue
            ids = re.findall(r"[A-Za-z_]\w*", part)
            if ids:
                names.add(ids[-1])
    # Plain `typedef X NAME, *PNAME;` on one line -- this is what makes
    # `typedef HANDLE HLINE;` indexable, which an earlier `$`-anchored
    # pattern missed and so left Extapi.h without its Tapi.h include.
    for m in re.finditer(r"^\s*typedef\s+([^;{\n(]*);", s, re.M):
        for part in m.group(1).split(","):
            ids = re.findall(r"[A-Za-z_]\w*", part)
            if ids:
                names.add(ids[-1])
    # The name of a function-pointer typedef lives inside the parentheses:
    # `typedef DWORD (APIENTRY *PFNRASSENDBUFFER)(...);`
    names |= set(re.findall(r"\(\s*(?:APIENTRY|WINAPI|CALLBACK|STDMETHODCALLTYPE)?\s*"
                            r"\*\s*([A-Za-z_]\w*)\s*\)\s*\(", s))
    return names


def all_headers():
    for dp, _, fs in os.walk(os.path.join(ROOT, "include")):
        for f in fs:
            if f.endswith((".h", ".hpp", ".hxx")):
                yield os.path.relpath(os.path.join(dp, f), ROOT)


def index():
    """identifier -> header path (first header that declares it)."""
    out = {}
    for p in sorted(all_headers()):
        for n in names_in(p):
            out.setdefault(n, p)
    return out


def resolve(inc):
    base = os.path.basename(inc)
    for cand in (os.path.join("include", base), os.path.join("include", "oak", base),
                 os.path.join("include", inc), os.path.join("include", "oak", inc)):
        cand = os.path.normpath(cand)
        if os.path.exists(os.path.join(ROOT, cand)):
            return cand
    return None


def includes_of(path):
    s = open(os.path.join(ROOT, path), encoding="utf-8", errors="replace").read()
    return set(re.findall(r'^\s*#\s*include\s+["<]([^">]+)[">]', s, re.M))


def closure(paths):
    """(files, names) reachable from `paths` through their includes."""
    files, todo, seen = set(), list(paths), set()
    while todo:
        p = os.path.normpath(todo.pop())
        if p in seen or not os.path.exists(os.path.join(ROOT, p)):
            continue
        seen.add(p)
        files.add(p)
        for inc in includes_of(p):
            r = resolve(inc)
            if r:
                todo.append(r)
    names = set()
    for f in files:
        names |= names_in(f)
    return files, names


def main():
    args = sys.argv[1:]
    if args and args[0] == "--all-new":
        d = json.load(open(os.path.join(ROOT, args[1]), encoding="utf-8"))
        args = d["created"]
    if not args:
        sys.exit("usage: add-header-includes.py [--all-new build/shipped-headers.json]")

    idx = index()
    for path in args:
        s = open(os.path.join(ROOT, path), encoding="utf-8").read()
        code = strip_comments(s)
        used = {t for t in USE.findall(code) if not IGNORE.match(t)}
        used |= {t for t in RET.findall(code) if not IGNORE.match(t)}
        already, base_names = closure([path])
        need = {}
        for u in sorted(used):
            src = idx.get(u)
            if not src:
                continue
            src = os.path.normpath(src)
            if src in already or u in base_names:
                continue
            if src.startswith("include" + os.sep + "oak"):
                continue                      # never pull in a driver header
            need.setdefault(src, []).append(u)
        if not need and os.path.normpath(path) not in PLACEMENT_INCLUDES:
            continue
        extra = PLACEMENT_INCLUDES.get(os.path.normpath(path))
        if extra and extra[0] not in s:
            add = ['#include "%s"   /* %s */' % (extra[0], extra[1])]
        else:
            add = []
        add += ['#include "%s"   /* %s */'
                % (src[len("include/"):] if src.startswith("include/") else src,
                   ", ".join(sorted(need[src])[:5]))
                for src in sorted(need)]
        # Most headers open an extern "C" block, which is the natural place
        # for the includes.  A few (include/Gwebypasscoredllthunk.hpp) have
        # none, so fall back to the include guard's own #endif rather than
        # asserting -- a header that cannot take its includes silently keeps
        # the unknown types that made them necessary.
        anchor = '#ifdef __cplusplus\nextern "C" {'
        block = "\n".join(add)
        if anchor in s:
            s = s.replace(anchor, block + "\n\n" + anchor, 1)
        else:
            ends = [i for i, l in enumerate(s.split("\n")) if l.startswith("#endif")]
            assert ends, path
            L = s.split("\n")
            L[max(ends):max(ends)] = ["", block, ""]
            s = "\n".join(L)
        open(os.path.join(ROOT, path), "w", encoding="utf-8").write(s)
        print("%-30s +%d includes (%s)"
              % (path, len(add), ", ".join(os.path.basename(x) for x in sorted(need)[:5])))


if __name__ == "__main__":
    main()
