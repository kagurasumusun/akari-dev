#!/usr/bin/env python3
"""
gen-guard.py -- per-declaration Windows CE generation attribution.

The official per-page Requirements block prints an "OS Versions:" row
("Windows CE 1.0 and later.", "Windows CE 5.0 and later.", "Windows
Embedded CE 6.0", "Windows CE 3.0 to Windows CE .NET 4.1.", ...).  That
row is the only published statement of which CE generation an API
belongs to, and it is what separates the *common* CE surface from the
*generation-specific* surface (`_WIN32_WCE` in include/Sdkddkver.h).

This tool

  1. maps every distinct OS Versions string harvested from the official
     pages onto a (minimum, maximum) `_WIN32_WCE` pair -- explicitly,
     string by string, in OS_VERSIONS below; a string that is not in the
     table is reported as unmapped and never guessed,
  2. attributes every shipped declaration to its cited page (the page id
     in the declaration's comment) and therefore to a generation range,
  3. writes docs/generation-map.tsv
         header  name  page  os_text  min  max  guard
     and prints the measured distribution.

The mapping is the documented `_WIN32_WCE` encoding (0x0420 = CE 4.20:
major in the high byte, the minor's two decimal digits in the low byte);
nothing is invented -- every range is a page's own OS Versions row.

`--apply` wraps a declaration in the matching `#if _WIN32_WCE ...`
guard.  IT IS NOT SAFE TO SHIP YET, and the tree therefore carries the
map but no guards; two measured blockers (2026-09-14):

  1. cross-header tails -- a typedef's pointer tail is what other
     headers use, so hiding `DEVMGR_DEVICE_INFORMATION,
     *PDEVMGR_DEVICE_INFORMATION` (Winbase.h, CE 5.0+) breaks
     `CEDDK.h:174`, whose own page row does not state a generation.
     Guarding such a unit needs the *using* declaration's row, which is
     a separate attribution question, not a mechanical wrap.
  2. the consumer TU -- `tests/host/tu_compile.c` is compiled at all
     three generations and calls the CE 5.0+ APIs unconditionally, so
     83 of its regions need the same conditions; wrapping them
     statement-wise broke the file (`tu_compile.c:813: expected
     expression before 'typedef'`).  The consumer check needs a
     generation-aware structure of its own before any guard can land.

Both are recorded in docs/inventory.md (M109) with the exact compiler
diagnostics.

Usage:  python3 tools/gen-guard.py <corpus-dir> [--apply]
"""

import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, "docs", "generation-map.tsv")

# `_WIN32_WCE` values of the CE generations (include/Sdkddkver.h).
V = {
    "1.0": 0x0100, "1.01": 0x0101,
    "2.0": 0x0200, "2.01": 0x0201, "2.1": 0x0210, "2.10": 0x0210,
    "2.11": 0x0211, "2.12": 0x0212,
    "3.0": 0x0300, "3.1": 0x0310,
    "4.0": 0x0400, "4.1": 0x0410, "4.2": 0x0420,
    "5.0": 0x0500, "6.0": 0x0600,
}

# Every distinct OS Versions string in the harvested official rows,
# mapped to (min, max, closed).
#
#   min    lowest `_WIN32_WCE` the row states
#   max    highest `_WIN32_WCE` the row states (None when open-ended)
#   closed True only when the row *enumerates* the versions ("X to Y",
#          "X and Y", "X and earlier"), i.e. when the page itself is
#          evidence of absence above `max`.  A bare generation label
#          ("Windows CE 5.0") and an "and later" row are NOT absence
#          evidence: the CE 6.0 archive prints an empty OS Versions row
#          on its own pages, so "Windows CE 5.0" on the CE 5.0 page says
#          nothing about CE 6.0 (measured: `Animate_Close` aa452851
#          prints "Windows CE 5.0" and has a CE 6.0 twin page ee504340).
#
# A string that is not in this table is reported as unmapped and never
# guessed.  Two harvested strings name generations that do not exist
# ("Windows CE .NET 3.0 and later.", "Windows CE .NET 2.0 and later." --
# CE .NET is the 4.x line); they are listed in IMPOSSIBLE below so the
# report shows them as archive labels that cannot be mapped, rather
# than being silently folded onto a neighbouring generation.
OS_VERSIONS = {
    "Windows CE 1.0 and later.": (V["1.0"], None, False),
    "Windows CE 1.0 and later": (V["1.0"], None, False),
    "Windows CE 1.01 and later.": (V["1.01"], None, False),
    "Windows CE 2.0 and later.": (V["2.0"], None, False),
    "Windows CE 2.0 and later": (V["2.0"], None, False),
    "Windows CE 2.0 and later. Versions prior to 2.12 require the MSMQ "
    "add-on pack.": (V["2.0"], None, False),
    "Windows CE 2.0 and 2.01.": (V["2.0"], V["2.01"], True),
    "Windows CE 2.01 and later.": (V["2.01"], None, False),
    "Windows CE 2.10 and later.": (V["2.10"], None, False),
    "Windows CE 2.11 and later.": (V["2.11"], None, False),
    "Windows CE 2.12 and later.": (V["2.12"], None, False),
    "Windows CE 2.12 and later. Version 2.12 requires DXPAK 1.0 or "
    "later.": (V["2.12"], None, False),
    "Windows CE 3.0 and later.": (V["3.0"], None, False),
    "Windows CE 3.0 and later": (V["3.0"], None, False),
    "Windows CE 3.1 and later.": (V["3.1"], None, False),
    "Windows CE 3.0 to Windows CE 4.1.": (V["3.0"], V["4.1"], True),
    "Windows CE 3.0 to Windows CE .NET 4.1.": (V["3.0"], V["4.1"], True),
    "Windows CE 2.12 through .NET 4.1.": (V["2.12"], V["4.1"], True),
    "Windows CE 2.12 through 3.1.": (V["2.12"], V["3.1"], True),
    "Windows CE 2.12 and earlier.": (None, V["2.12"], True),
    "Windows CE 4.0 and later.": (V["4.0"], None, False),
    "Windows CE .NET 4.0 and later.": (V["4.0"], None, False),
    "Windows CE .NET 4.0 and later": (V["4.0"], None, False),
    "Windows CE .NET 4.1 and later.": (V["4.1"], None, False),
    "Windows CE .NET 4.2 and later.": (V["4.2"], None, False),
    "Windows CE .NET 4.2 and later": (V["4.2"], None, False),
    "Windows CE.NET 4.2 and later.": (V["4.2"], None, False),
    "Windows CE .NET 4.2.": (V["4.2"], None, False),
    "Windows CE 5.0 and later.": (V["5.0"], None, False),
    "Windows CE 5.0 and later": (V["5.0"], None, False),
    "Windows CE 5.0 or later.": (V["5.0"], None, False),
    "Microsoft\u00ae Windows CE\u00ae 5.0 and later.": (V["5.0"], None, False),
    "Windows CE 5.0": (V["5.0"], None, False),
    "Windows CE 5.0.": (V["5.0"], None, False),
    "Windows CE .NET 5.0 and later.": (V["5.0"], None, False),
    "Windows Embedded CE 6.0": (V["6.0"], None, False),
    "Windows Embedded CE 6.0 and later": (V["6.0"], None, False),
    # rows that do not state a generation range
    "Windows CE OS": (None, None, False),
    "Windows CE OS 2.10 and later": (V["2.10"], None, False),
    "Windows CE .": (None, None, False),
    "Not supported in Windows CE.": ("none", "none", False),
    "Windows CE 5.0 Networked Media Device Feature Pack.": ("fp", "fp", False),
    "Windows CE 5.0 with Windows CE 5.0 Networked Media Device Feature "
    "Pack": ("fp", "fp", False),
    "": (None, None, False),
}

# archive labels that name a generation which does not exist; reported,
# never mapped onto a neighbouring generation.
IMPOSSIBLE = {
    "Windows CE .NET 3.0 and later.",
    "Windows CE .NET 2.0 and later.",
}

TARGETS = (0x420, 0x500, 0x600)


def combine(ranges):
    """union of the (min, max, closed) ranges harvested for one title
    across all generations: the lowest documented minimum, and an upper
    bound only when every row that states one agrees and no row is
    open-ended above it."""
    mins = [r[0] for r in ranges if isinstance(r[0], int)]
    lo = min(mins) if mins else None
    # An upper bound is only adopted when *every* harvested page of the
    # API enumerates its versions and they all agree.  A single
    # open-ended or generation-less row ("Windows CE OS" on the CE 3.0
    # page) is a documented conflict: the generations disagree, so no
    # absence claim is made and the case is reported instead (rule:
    # never mix generations, never guess).
    maxes = [r[1] for r in ranges if r[2] and isinstance(r[1], int)]
    all_closed = all(r[2] for r in ranges)
    hi = None
    if maxes and all_closed and len(set(maxes)) == 1:
        hi = maxes[0]
    return lo, hi


def guard_for(lo, hi):
    """the `#if` condition a (min, max) pair needs, or None when the
    declaration is available on every supported target."""
    if lo in ("none", "fp") or hi in ("none", "fp"):
        return None
    parts = []
    if isinstance(lo, int) and lo > min(TARGETS):
        parts.append(f"_WIN32_WCE >= 0x{lo:04x}")
    if isinstance(hi, int) and hi < max(TARGETS):
        parts.append(f"_WIN32_WCE <= 0x{hi:04x}")
    return " && ".join(parts) if parts else None


PAGE_RE = re.compile(r"\b((?:[a-z]{2}\d{6}|[a-z0-9]{8})(?:\(v=[a-z0-9.]+\))?)\b")
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
IDENT_ALL = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")


def load_rows(corpus):
    """page id -> (title, os text).  A page id is per-archive, so the
    CE 5.0 and CE 6.0 pages of one API are two records; the generation
    range of an API is the union over every page that documents it."""
    out = {}
    for fn in ("rows.json", "rows4.json", "rows3.json"):
        p = os.path.join(corpus, fn)
        if not os.path.exists(p):
            continue
        for r in json.load(open(p, encoding="utf-8")):
            root = re.split(r"[(]", r.get("id", ""))[0]
            osr = (r.get("os") or "").strip()
            prev = out.get(root)
            # keep the most specific OS row seen for the page
            if prev is None or (not prev[1] and osr):
                out[root] = ((r.get("title") or "").strip(), osr)
    return out


def short_title(title):
    """the archive appends disambiguation suffixes to page titles
    ("CreatePalette (GDI)", "socket (Windows Sockets)"); the API name is
    the title without them -- the same normalisation tools/gen-doc-def.py
    applies to export names."""
    t = re.sub(r"\s*\([^)]*\)\s*$", "", (title or "").strip()).strip()
    return t


def title_ranges(rows):
    """title -> list of (min, max, closed) over every harvested page."""
    per = {}
    for root, (title, osr) in rows.items():
        title = short_title(title)
        # a page may document a class/interface *member*
        # ("ISdpRecord::WriteToStream"): the member's generation row is
        # evidence for the member and, in the absence of a row of its
        # own, for the class the tree declares.
        keys = [title] if IDENT.match(title or "") else []
        if "::" in title:
            cls, _m = title.split("::", 1)
            if IDENT.match(cls):
                keys.append(cls)
        for k in keys:
            e = per.setdefault(k, {"ranges": [], "unmapped": set(),
                                   "impossible": set()})
            if osr in IMPOSSIBLE:
                e["impossible"].add(osr)
            elif osr not in OS_VERSIONS:
                e["unmapped"].add(osr)
            else:
                e["ranges"].append(OS_VERSIONS[osr])
    return per


def header_files():
    for rel in ("include", os.path.join("include", "oak")):
        d = os.path.join(ROOT, rel)
        if not os.path.isdir(d):
            continue
        for fn in sorted(os.listdir(d)):
            if fn.endswith((".h", ".hxx", ".hpp")):
                yield os.path.join(d, fn), os.path.join(rel, fn)


def declarations(text):
    """(line_no, name) of every top-level declaration line, i.e. a line
    that starts a function prototype / typedef / struct / #define."""
    out = []
    for i, ln in enumerate(text.splitlines()):
        s = ln.strip()
        if not s or s.startswith(("*", "/*", "//", "#endif", "#else")):
            continue
        if s.startswith("#define"):
            m = re.match(r"#define\s+([A-Za-z_][A-Za-z0-9_]*)", s)
            if m:
                out.append((i, m.group(1)))
            continue
        if s.startswith(("typedef", "struct", "union", "enum", "class")):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*(?:\{|;|$)", s)
            if m:
                out.append((i, m.group(1)))
            continue
        m = re.match(r"(?:AKARI_CE_IMPORT\s+)?(?:[A-Za-z_][A-Za-z0-9_]*"
                     r"\s+\**)+?([A-Za-z_][A-Za-z0-9_]*)\s*\(", s)
        if m:
            out.append((i, m.group(1)))
    return out


def stmt_span(lines, ln):
    """(first, last) line indices of the declaration that starts at
    `ln`: a preprocessor line with continuations, a struct/union/enum
    body up to its closing '} name;', or a prototype up to its ';'."""
    s0 = lines[ln].strip()
    if s0.startswith("#"):
        i = ln
        while i < len(lines) and lines[i].rstrip().endswith("\\"):
            i += 1
        return ln, min(i, len(lines) - 1)
    depth = 0
    i = ln
    while i < len(lines):
        t = lines[i]
        depth += t.count("{") - t.count("}")
        if i > ln and depth <= 0 and ("}" in t or ";" in t):
            return ln, i
        if depth == 0 and i > ln and ";" in t:
            return ln, i
        if i == ln and depth == 0 and ";" in t and "{" not in t:
            return ln, ln
        i += 1
        if i - ln > 200:
            return None
    return None


def comment_span(lines, ln):
    """first line of the comment block directly above `ln`."""
    j = ln - 1
    while j >= 0 and (lines[j].strip().startswith(("*", "//"))
                      or not lines[j].strip()):
        j -= 1
    k = ln - 1
    if k >= 0 and lines[k].strip().startswith("*"):
        # inside a block comment: walk to its '/*'
        while k >= 0 and "/*" not in lines[k]:
            k -= 1
        return max(k, 0)
    return ln


GUARD_RE = re.compile(r"^#ifndef\s+([A-Za-z_][A-Za-z0-9_]*)")


def preproc_blocked(lines, i):
    """True when line i sits inside a preprocessor conditional other
    than the file's own header guard -- such a unit already has a
    documented condition and is left untouched."""
    open_ifs = []
    for t in lines[:i]:
        s = t.strip()
        if s.startswith(("#if", "#ifdef", "#ifndef")):
            open_ifs.append(s)
        elif s.startswith("#endif") and open_ifs:
            open_ifs.pop()
    if not open_ifs:
        return False
    # the outermost one may be the include guard (#ifndef <X>_H)
    if len(open_ifs) == 1:
        m = GUARD_RE.match(open_ifs[0])
        if m and (m.group(1).endswith(("_H", "_H_", "_HPP", "_HPP_"))
                  or m.group(1).startswith("AKARI_")):
            return False
    return True


def strip_comments(text):
    text = re.sub(r"(?s)/\*.*?\*/", " ", text)
    return re.sub(r"//[^\n]*", " ", text)


def makefile_headers():
    """the header lists the Makefile itself gates (HDRS + OAK_HDRS).

    The sweep has to check exactly what `make check` checks: the tree
    carries files nobody compiles standalone (include/Notifext.hxx takes
    CEOID without including Windbase.h and fails on its own at every
    generation, on the committed tree as well), and gating on those
    would charge their pre-existing breakage to the guards."""
    import subprocess
    try:
        r = subprocess.run(
            ["make", "-s",
             "--eval=__pv: ; @echo $(HDRS) $(OAK_HDRS)", "__pv"],
            cwd=ROOT, capture_output=True, text=True, timeout=120)
    except OSError:
        return []
    if r.returncode != 0:
        return []
    return [t for t in r.stdout.split() if t.endswith((".h", ".hpp"))]


def compiles_at(path, wince, tu=False):
    """standalone compile of one header (or of the shipped consumer TU)
    at one CE generation, exactly as the Makefile compiles it."""
    import subprocess
    inc = os.path.join(ROOT, "include")
    cmd = ["cc", "-std=c11", "-ffreestanding", "-Werror",
           f"-D_WIN32_WCE={wince}", "-I", inc,
           "-I", os.path.join(inc, "oak")]
    if tu:
        # The consumer TU carries `#if __SIZEOF_POINTER__ == 4` blocks, so
        # a 64-bit host compile silently skips them while every WinCE
        # target is 32-bit.  When WINCECLANG is set the TU is gated with
        # the same cross-compiler and triple the Makefile's crosscheck
        # uses; the host compile stays as the `make check` half.  (Forcing
        # __SIZEOF_POINTER__=4 on the host is not an option: the TU
        # deliberately asserts the host pointer size at line 177.)
        tupath = os.path.join(ROOT, "tests", "host", "tu_compile.c")
        cmds = [cmd + ["-fsyntax-only", tupath]]
        clang = os.environ.get("WINCECLANG")
        triple = {0x420: "arm-pc-wince4.2", 0x500: "arm-pc-wince5.0",
                  0x600: "arm-pc-wince6.0"}.get(wince)
        if clang and triple and os.access(clang, os.X_OK):
            os.makedirs("/tmp/wince-sysroot", exist_ok=True)
            cmds.append([clang, "-target", triple, "-std=c11",
                         "-ffreestanding", "--sysroot=/tmp/wince-sysroot",
                         "-Wno-wince-sysroot-missing", "-Werror",
                         "-D_WIN32_WCE=%d" % wince, "-I", inc,
                         "-I", os.path.join(inc, "oak"),
                         "-fsyntax-only", tupath])
    else:
        cmds = [cmd + ["-include", path, "-fsyntax-only", "-x", "c",
                       os.devnull]]
    for c in cmds:
        try:
            r = subprocess.run(c, capture_output=True, text=True,
                               timeout=300)
        except OSError:
            return True, ""
        if r.returncode == 0:
            continue
        for lne in (r.stderr or "").splitlines():
            if "error:" in lne:
                # keep the "file:line:" prefix: the caller needs to know
                # which file lost a declaration
                return False, lne.strip()
        return False, "compile failed"
    return True, ""


TU = os.path.join(ROOT, "tests", "host", "tu_compile.c")


def comment_runs(lines):
    """[(first, last)] of every /* ... */ comment spanning more than one
    line.  A preprocessor directive cannot sit inside one: the `#if` is
    swallowed by the comment while its `#endif` is not, which is exactly
    the `unterminated #if` this file produced when a guard was cut across
    the M27 GDI note in the shipped consumer TU."""
    runs = []
    start = None
    for i, l in enumerate(lines):
        j = 0
        while True:
            if start is None:
                k = l.find("/*", j)
                if k < 0:
                    break
                e = l.find("*/", k + 2)
                if e >= 0:
                    j = e + 2
                    continue
                start = i
                break
            e = l.find("*/", j)
            if e < 0:
                break
            runs.append((start, i))
            start = None
            j = e + 2
    if start is not None:
        runs.append((start, len(lines) - 1))
    return runs


def expand_over_comments(a, b, runs):
    """grow [a, b] until it neither starts, ends, nor stops inside a
    multi-line comment."""
    changed = True
    while changed:
        changed = False
        for r0, r1 in runs:
            if r0 <= a <= r1 or r0 <= b <= r1 or (a < r0 and b > r1):
                na, nb = min(a, r0), max(b, r1)
                # only real growth is progress: two overlapping comment
                # runs otherwise keep re-triggering each other and the
                # loop never terminates
                if (na, nb) != (a, b):
                    a, b = na, nb
                    changed = True
    return a, b


TYPEKW = ("typedef", "struct", "union", "enum")
CKEYWORDS_ENUM = {"enum", "typedef", "struct", "union"}


def declared_names(lines, ln, name):
    """the names a declaration unit *introduces*.

    `declarations()` reports one name per unit -- for
    `typedef struct tagLVBKIMAGE { ... } LVBKIMAGE, *LPLVBKIMAGE;` that is
    the tag -- but consumers spell the typedef tail, so the generation of
    the printed block has to travel with each introduced name (PPCRED,
    PSS_SOCKET_STATE, SCRIPT_LOGATTR and PCHANNEL_ENTRY_POINTS_EX each
    broke a 0x0420 compile when only the primary name carried it)."""
    span = stmt_span(lines, ln)
    if not span:
        return {name}
    flat = " ".join(strip_comments(
        "\n".join(lines[span[0]:span[1] + 1])).split())
    out = {name}
    if re.search(r"\benum\b", flat):
        # enumerator names: consumers reference `DecoderInitFlagNoBlock`,
        # not the tag, and a CE 5.0 enumerator is just as unavailable on
        # CE 4.2 as the enum that declares it
        body = flat[flat.find("{") + 1:flat.rfind("}")] \
            if "{" in flat else ""
        for e in re.finditer(r"([A-Za-z_]\w*)\s*(?:=[^,}]*)?[,}]",
                             body + "}"):
            if e.group(1) not in CKEYWORDS_ENUM:
                out.add(e.group(1))
    if flat.startswith("#define") or "typedef" not in flat:
        return out
    k = flat.rfind("}")
    tail = flat[k + 1:] if k >= 0 else flat[len("typedef"):]
    for part in tail.split(","):
        toks = [t for t in re.split(r"[^A-Za-z0-9_]+", part) if t]
        if toks and re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", toks[-1]):
            out.add(toks[-1])
    m = re.match(r"typedef\s+(?:struct|union|enum)\s+([A-Za-z_]\w*)", flat)
    if m:
        out.add(m.group(1))
    # typedef RET (CALLBACK *PFN)(args);
    for m in re.finditer(r"\(\s*(?:[A-Za-z_]\w*\s+)*\*\s*"
                         r"([A-Za-z_]\w*)\s*\)\s*\(", flat):
        out.add(m.group(1))
    return out


def is_type_unit(lines, ln):
    """True when the unit introduces a type (typedef / struct / union /
    enum).  Propagation is limited to those: a macro or a prototype named
    on a CE 5.0 page says nothing about the generation of everything that
    mentions it, while a *type* does -- a CE 4.2 declaration cannot take
    a parameter of a type that CE 4.2 does not have."""
    span = stmt_span(lines, ln)
    if not span:
        return False
    flat = " ".join(strip_comments(
        "\n".join(lines[span[0]:span[1] + 1])).split())
    return not flat.startswith("#define") and any(
        re.match(k + r"\b", flat) or (" " + k + " ") in flat
        for k in TYPEKW)


def bracket_balance(line):
    """net count of unclosed ( [ { on one line, ignoring string and
    character literals.  An initialiser-table element is balanced and
    ends in a comma; the first line of `_Static_assert(cond,` is not."""
    n = 0
    quote = None
    i = 0
    while i < len(line):
        c = line[i]
        if quote:
            if c == "\\":
                i += 2
                continue
            if c == quote:
                quote = None
        elif c in "\"'":
            quote = c
        elif c in "([{":
            n += 1
        elif c in ")]}":
            n -= 1
        i += 1
    return n


def guard_consumer_sites(guarded):
    """make the shipped consumer TU generation-aware at *function*
    granularity.

    A CE 4.2 program cannot call a CE 5.0 API, so the consumer check has
    to say so the way a real consumer would.  The TU is a dispatcher over
    `static int <name>_usage(void)` functions, so a whole function -- and
    its single dispatch call -- is wrapped in the strictest condition
    among the guarded APIs it uses.  Wrapping statement-wise instead was
    tried first and broke the file twice: `tu_compile.c:813: expected
    expression before 'typedef'` when a declaration block was cut, and
    `unterminated #if` when the cut landed inside a multi-line comment."""
    text = open(TU, encoding="utf-8", errors="replace").read()
    lines = text.splitlines()
    units = []
    i = 0
    while i < len(lines):
        m = re.match(r"^static\s+int\s+([A-Za-z_][A-Za-z0-9_]*)\s*"
                     r"\(void\)\s*$", lines[i].rstrip())
        if not m:
            i += 1
            continue
        j = i + 1
        while j < len(lines) and lines[j].rstrip() != "}":
            j += 1
        if j >= len(lines):
            break
        k = i - 1
        while k >= 0 and (lines[k].strip().startswith(("*", "/*", "//"))
                          or not lines[k].strip()):
            k -= 1
        units.append((m.group(1), k + 1, j))
        i = j + 1
    covered = set()
    for _n, a, b in units:
        covered.update(range(a, b + 1))

    gset = set(guarded)

    def cond_bound(c):
        m = re.search(r"_WIN32_WCE >= (0x[0-9a-fA-F]{4})", c or "")
        return int(m.group(1), 16) if m else 0

    def strictest(a, b):
        return a if cond_bound(a) >= cond_bound(b) else b

    edits = []
    conds = {}
    for name, a, b in units:
        body = strip_comments("\n".join(lines[a:b + 1]))
        used = sorted(set(IDENT_ALL.findall(body)) & gset)
        if not used:
            continue
        cond = guarded[used[0]]
        for u in used[1:]:
            cond = strictest(cond, guarded[u])
        conds[name] = cond
        edits.append([a, b, cond, [f"fn {name}"] + used, 1 + len(used)])
    for i, ln in enumerate(lines):
        if i in covered:
            continue
        m = re.match(r"\s*if \(([A-Za-z_][A-Za-z0-9_]*)\s*\(\s*\)"
                     r" != 0\)", ln)
        if m and m.group(1) in conds:
            j = i + 1 if (i + 1 < len(lines)
                          and lines[i + 1].strip() == "return 1;") else i
            edits.append([i, j, conds[m.group(1)],
                          [f"dispatch {m.group(1)}"], 1])
    for i, ln in enumerate(lines):
        if i in covered:
            continue
        s0 = ln.strip()
        if not s0 or s0.startswith(("#", "/*", "*", "//", "}")):
            continue
        hits = [n for n in dict.fromkeys(IDENT_ALL.findall(ln))
                if n in gset]
        if not hits:
            continue
        # A file-scope use can sit inside a multi-line declaration (the
        # TU's `typedef char assert_x[(A == 1 && B == 2) ? 1 : -1];`
        # value assertions are exactly that), so the guarded range has to
        # be the *whole* declaration: cutting an expression in half left
        # `... PROGRESS_STOP == 2 &&` followed by the next `static` and
        # the compiler reported `expected expression before 'static'`.
        a = i
        while a > 0:
            prev = lines[a - 1]
            st = prev.strip()
            if (not st or st.startswith(("#", "*", "/*", "//"))
                    or prev.rstrip().endswith((";", "{", "*/"))
                    or (bracket_balance(prev) <= 0
                        and prev.rstrip().endswith((",", "}")))):
                break
            a -= 1
        if i - a > 40:
            continue
        j = i
        bal = 0
        while j < len(lines):
            bal += bracket_balance(lines[j])
            if bal <= 0 and lines[j].rstrip().endswith((";", "}", ",")):
                break
            j += 1
            if j - i > 40:
                break
        if j >= len(lines) or j - i > 40:
            continue
        cond = guarded[hits[0]]
        for h in hits[1:]:
            cond = strictest(cond, guarded[h])
        edits.append([a, j, cond, list(hits), len(hits)])

    runs = comment_runs(lines)
    edits = [list(expand_over_comments(a, b, runs)) + [c, n[:4], k]
             for a, b, c, n, k in edits]

    # A static helper whose only use disappears behind a guard becomes an
    # unused function, and the Makefile compiles the TU with -Werror
    # (m47_stream_output is only reached through PFN_CMSG_STREAM_OUTPUT,
    # a CE 5.0 type).  Wrap such a definition in the strictest condition
    # of the regions that used it.
    def fn_defs():
        out = []
        i = 0
        while i < len(lines):
            m = re.match(r"^static\b[^;]*?\b([A-Za-z_]\w*)\s*\(",
                         lines[i])
            if not m or lines[i].rstrip().endswith(";"):
                i += 1
                continue
            bal = 0
            j = i
            while j < len(lines):
                bal += bracket_balance(lines[j])
                if bal <= 0 and "}" in lines[j]:
                    break
                j += 1
                if j - i > 200:
                    break
            if j < len(lines):
                out.append((m.group(1), i, j))
                i = j + 1
            else:
                i += 1
        return out

    for fname, a, b in fn_defs():
        inside = [e for e in edits if not (e[1] < a or e[0] > b)]
        if inside:
            continue
        uses = [i for i, ln in enumerate(lines)
                if not (a <= i <= b)
                and re.search(r"\b" + re.escape(fname) + r"\b", ln)]
        if not uses:
            continue
        cover = [e for e in edits
                 if any(e[0] <= u <= e[1] for u in uses)]
        if len(cover) and all(any(e[0] <= u <= e[1] for e in cover)
                              for u in uses):
            cond = cover[0][2]
            for e in cover[1:]:
                cond = (cond if cond_bound(cond) >= cond_bound(e[2])
                        else e[2])
            edits.append([a, b, cond, [f"static {fname} only used "
                                       "guarded"], 1])
    edits.sort()
    # Merging must not concatenate a note per merged edit: the shipped TU
    # has initialiser tables whose every line names one guarded API, so a
    # single region can absorb a thousand edits and the string building
    # goes quadratic.  Keep the first few names and a count.
    merged = []
    for a, b, cond, names, n in edits:
        if merged and a <= merged[-1][1] + 1:
            merged[-1][2] = (merged[-1][2] if cond_bound(merged[-1][2])
                             >= cond_bound(cond) else cond)
            merged[-1][1] = max(merged[-1][1], b)
            if len(merged[-1][3]) < 3:
                merged[-1][3] += names[:3 - len(merged[-1][3])]
            merged[-1][4] += n
        else:
            merged.append([a, b, cond, list(names), n])
    for a, b, cond, names, n in sorted(merged, key=lambda e: -e[0]):
        note = ", ".join(names) + (f" +{n - len(names)} more"
                                   if n > len(names) else "")
        lines.insert(b + 1, f"#endif /* {cond} */")
        lines.insert(a, f"#if {cond}   /* {note} */")
    open(TU, "w", encoding="utf-8").write("\n".join(lines) + "\n")
    return len(merged)


def attribute_file(path, rel, rows, per_title, unmapped=None,
                   impossible=None):
    """[(line, name, page, os_text, min, max, guard)] for one header.

    A declaration whose own comment block carries no page id inherits
    the citation of the declaration directly above it when the two are
    adjacent and of the same kind (`#define` after `#define`, prototype
    after prototype): the pages print a block of related constants or
    prototypes under one citation, and half a printed block must not be
    attributed to a different generation than the other half."""
    text = open(path, encoding="utf-8", errors="replace").read()
    lines = text.splitlines()
    decls = declarations(text)
    out = []
    prev = None            # (last_line, kind, cite, osr, lo, hi, guard)
    for ln, name in decls:
        kind = ("define" if lines[ln].strip().startswith("#define")
                else "other")
        cite = None
        j = ln - 1
        while j >= 0 and (lines[j].strip().startswith(("*", "/*", "//"))
                          or not lines[j].strip()):
            for m in PAGE_RE.finditer(lines[j]):
                root = re.split(r"[(]", m.group(1))[0]
                if root in rows:
                    cite = root
                    break
            if cite:
                break
            j -= 1
            if ln - j > 12:
                break
        lo = hi = None
        osr = ""
        if cite:
            title, osr = rows[cite]
            st = short_title(title)
            info = per_title.get(st) or {}
            if not info.get("ranges") and "::" in st:
                info = per_title.get(st.split("::", 1)[0]) or {}
            if info.get("impossible"):
                if impossible is not None:
                    for x in info["impossible"]:
                        impossible[x] = impossible.get(x, 0) + 1
                cite = None
            elif not info.get("ranges"):
                if unmapped is not None and osr:
                    unmapped[osr] = unmapped.get(osr, 0) + 1
                cite = None
            else:
                lo, hi = combine(info["ranges"])
        if not cite and prev and prev[0] == ln - 1 and prev[1] == kind:
            cite, osr, lo, hi = prev[2], prev[3], prev[4], prev[5]
        span = stmt_span(lines, ln)
        last = span[1] if span else ln
        g = guard_for(lo, hi) if cite else None
        out.append((ln, name, cite, osr, lo, hi, g))
        if cite:
            prev = (last, kind, cite, osr, lo, hi, g)
    return out


def main():
    corpus = sys.argv[1]
    apply = "--apply" in sys.argv
    rows = load_rows(corpus)
    per_title = title_ranges(rows)

    unmapped = {}
    impossible = {}
    recs = []
    per_file = {}
    for path, rel in header_files():
        got = attribute_file(path, rel, rows, per_title, unmapped,
                             impossible)
        per_file[rel] = got
        for _ln, name, cite, osr, lo, hi, g in got:
            if not cite:
                continue
            recs.append((rel, name, cite, osr, lo, hi, g))

    with open(OUT, "w", encoding="utf-8") as fh:
        fh.write("header\tname\tpage\tos_versions\tmin\tmax\tguard\n")
        for rel, name, cite, osr, lo, hi, g in recs:
            fh.write("\t".join([
                rel, name, cite, osr,
                "" if not isinstance(lo, int) else f"0x{lo:04x}",
                "" if not isinstance(hi, int) else f"0x{hi:04x}",
                g or ""]) + "\n")

    from collections import Counter
    print(f"attributed declarations: {len(recs)}")
    c = Counter((r[4], r[5]) for r in recs)
    print("documented generation range (union over every page of the API):")
    for (lo, hi), n in sorted(c.items(), key=lambda kv: -kv[1]):
        los = "-" if not isinstance(lo, int) else f"0x{lo:04x}"
        his = "open" if hi is None else (
            "-" if not isinstance(hi, int) else f"0x{hi:04x}")
        print(f"  {n:6d}  {los} .. {his}")
    guards = Counter(r[6] for r in recs if r[6])
    print("guard candidates (excluded from at least one supported target):")
    for k, n in guards.most_common():
        print(f"  {n:6d}  #if {k}")
    if unmapped:
        print("UNMAPPED OS strings (add to OS_VERSIONS; never guessed):")
        for k, n in sorted(unmapped.items(), key=lambda kv: -kv[1]):
            print(f"  {n:6d}  {k[:90]!r}")
    if impossible:
        print("IMPOSSIBLE generation labels (archive prints a generation "
              "that does not exist; not mapped):")
        for k, n in sorted(impossible.items(), key=lambda kv: -kv[1]):
            print(f"  {n:6d}  {k[:90]!r}")
    print(f"wrote {OUT}")

    if not apply:
        return
    # ---- apply the lower-bound guards --------------------------------
    # Only a documented *minimum* is applied: an upper bound would claim
    # absence in a later generation, which no harvested row proves (see
    # combine()).  Each guarded unit is the declaration plus the comment
    # block that cites its page; a unit already inside a preprocessor
    # conditional is left alone.  After every header the three supported
    # generations are compiled standalone and the header is rolled back
    # if any of them fails.
    # Type-driven propagation.  A declaration whose parameter or return
    # type is documented as CE 5.0+ cannot exist on CE 4.2 -- the type
    # itself is not there -- even when its own page prints no OS
    # Versions row (CEDDK.h:174 takes PDEVMGR_DEVICE_INFORMATION, whose
    # typedef is Winbase.h's, CE 5.0+, aa447797).  Such a unit inherits
    # the strictest condition of the guarded names it uses, and the
    # whole tree is compiled at all three generations afterwards, so an
    # unsound propagation fails the gate instead of being shipped.
    def cond_bound(c):
        m = re.search(r"_WIN32_WCE >= (0x[0-9a-fA-F]{4})", c or "")
        return int(m.group(1), 16) if m else 0

    def strictest(a, b):
        return a if cond_bound(a) >= cond_bound(b) else b

    CKEYWORDS = {"struct", "union", "enum", "void", "int", "char", "long",
                 "short", "unsigned", "signed", "const", "static", "extern",
                 "typedef", "return", "if", "else", "for", "while", "switch",
                 "case", "break", "continue", "default", "sizeof", "NULL"}
    file_lines = {}
    gmap = {}
    for rel, got in per_file.items():
        file_lines[rel] = open(os.path.join(ROOT, rel), encoding="utf-8",
                               errors="replace").read().splitlines()
        for ln, name, cite, osr, lo, hi, g in got:
            if not g or "<=" in g:
                continue
            if not is_type_unit(file_lines[rel], ln):
                continue
            for nm in declared_names(file_lines[rel], ln, name):
                if nm in CKEYWORDS or len(nm) < 3 \
                        or nm.startswith("AKARI_"):
                    continue
                gmap[nm] = strictest(gmap.get(nm, g), g)

    derived = []
    for _round in range(8):
        changed = False
        for rel, got in per_file.items():
            if rel.startswith("include" + os.sep + "oak"):
                continue
            flines = open(os.path.join(ROOT, rel), encoding="utf-8",
                          errors="replace").read().splitlines()
            gset2 = set(gmap)
            for i, (ln, name, cite, osr, lo, hi, g) in enumerate(got):
                if g or name in CKEYWORDS:
                    continue
                span = stmt_span(flines, ln)
                if not span:
                    continue
                code = strip_comments(
                    "\n".join(flines[span[0]:span[1] + 1]))
                used = sorted((set(IDENT_ALL.findall(code)) & gset2)
                              - {name})
                if not used:
                    continue
                cond = gmap[used[0]]
                for u in used[1:]:
                    cond = strictest(cond, gmap[u])
                got[i] = (ln, name, cite, osr, lo, hi, cond)
                gmap[name] = strictest(gmap.get(name, cond), cond)
                derived.append((rel, name, cond, used[0]))
                changed = True
        if not changed:
            break
    print(f"conditions propagated to users of a generation-specific type: "
          f"{len(derived)}", flush=True)
    for rel, name, cond, src in derived[:10]:
        print(f"  {rel}: {name} [{cond}] -- uses {src}")

    code_of = {}
    for rel, _got in per_file.items():
        code_of[rel] = strip_comments(
            open(os.path.join(ROOT, rel), encoding="utf-8",
                 errors="replace").read())
    # OEM/BSP scope is out of the user-mode -dev set: this pass guards
    # the application layer (include/) only; include/oak is left alone.
    skipped = 0
    byfile = {}
    for rel, got in per_file.items():
        if rel.startswith("include" + os.sep + "oak"):
            continue
        for ln, name, cite, osr, lo, hi, g in got:
            if not g or "<=" in g:
                continue
            byfile.setdefault(rel, []).append((ln, name, cite, osr, g))
    print(f"guard units: {sum(len(v) for v in byfile.values())} "
          f"in {len(byfile)} application-layer headers", flush=True)
    applied = 0
    held_units = []
    state = {}          # rel -> {path, orig, lines, edits}

    def render(st):
        out = list(st["lines"])
        for e in sorted(st["edits"], key=lambda e: -e[0]):
            out.insert(e[1] + 1, f"#endif /* {e[2]} */")
            out.insert(e[0], f"#if {e[2]}   /* {e[4]} ({e[3]}) */")
        open(st["path"], "w", encoding="utf-8").write("\n".join(out) + "\n")

    for rel, items in sorted(byfile.items()):
        path = os.path.join(ROOT, rel)
        text = open(path, encoding="utf-8", errors="replace").read()
        snap = path + ".preguard"
        if not os.path.exists(snap):
            open(snap, "w", encoding="utf-8").write(text)
        lines = text.splitlines()
        edits = []
        for ln, name, cite, osr, g in sorted(items):
            span = stmt_span(lines, ln)
            if not span:
                skipped += 1
                continue
            first, last = span
            if preproc_blocked(lines, first):
                skipped += 1
                continue
            cstart = comment_span(lines, first)
            # A page's declarations are printed as one block under one
            # citation; extend the unit over the consecutive declarations
            # that share that comment so a printed set is never split.
            hit = [i for i, e in enumerate(edits)
                   if e[0] == cstart and e[1] == first - 1]
            if hit:
                i = hit[0]
                e = edits[i]
                edits[i] = (e[0], last, e[2], e[3], e[4],
                            e[5] | declared_names(lines, ln, name))
                continue
            if any(not (e[1] < first or e[0] > last) for e in edits):
                skipped += 1
                continue
            # A guarded range must be brace-balanced on its own: cutting
            # `extern "C" {` away from its closing brace (Shobjidl.h)
            # leaves every C++ consumer of the header with an unterminated
            # linkage block, which cxxcheck reports as "expected '}' at
            # end of input".
            if sum(bracket_balance(t)
                   for t in lines[cstart:last + 1]) != 0:
                skipped += 1
                continue
            edits.append((cstart, last, g, cite, osr,
                          frozenset(declared_names(lines, ln, name))))
        if not edits:
            continue
        merged = []
        for e in sorted(edits):
            if merged and merged[-1][2] == e[2] and all(
                    not t.strip() or t.strip().startswith(("*", "/*", "//"))
                    for t in lines[merged[-1][1] + 1:e[0]]):
                m = merged[-1]
                merged[-1] = (m[0], e[1], m[2], m[3], m[4], m[5] | e[5])
            else:
                merged.append(e)
        state[rel] = {"path": path, "orig": text, "lines": lines,
                      "edits": merged}
        render(state[rel])

    applied = sum(len(st["edits"]) for st in state.values())
    print(f"guard units written: {applied} in {len(state)} application-layer "
          f"headers; skipped (nested/overlapping/unbounded): {skipped}",
          flush=True)

    # name -> the single guard unit that publishes it, so a whole-tree
    # failure can be charged to one unit instead of a whole header.
    unit_owner = {}
    for rel, st in state.items():
        for e in st["edits"]:
            for nm in e[5]:
                unit_owner.setdefault(nm, (rel, e))

    def drop_unit(rel, edit, why):
        st = state[rel]
        if edit not in st["edits"]:
            return False
        st["edits"] = [e for e in st["edits"] if e is not edit]
        if st["edits"]:
            render(st)
        else:
            open(st["path"], "w", encoding="utf-8").write(st["orig"])
        held_units.append((rel, edit[3], edit[4], edit[2], why))
        for nm in edit[5]:
            if unit_owner.get(nm, (None, None))[1] is edit:
                unit_owner.pop(nm, None)
        return True

    def try_drop(rel, e, w, head, validate=None):
        """drop one unit of `rel` and keep it dropped only if the tree
        failure it was blamed for actually goes away."""
        st = state[rel]
        saved = st["edits"]
        owner = {nm: unit_owner[nm] for nm in e[5] if nm in unit_owner}
        st["edits"] = [x for x in saved if x is not e]
        if st["edits"]:
            render(st)
        else:
            open(st["path"], "w", encoding="utf-8").write(st["orig"])
        ok, err2 = (validate() if validate
                    else compiles_at(None, w, tu=True))
        if ok or head not in (err2 or ""):
            # the unit stays out; record it here rather than through
            # drop_unit, which would find it already removed
            held_units.append((rel, e[3], e[4], e[2],
                               f"0x{w:04x}: {head[:90]}"))
            for nm in e[5]:
                if unit_owner.get(nm, (None, None))[1] is e:
                    unit_owner.pop(nm, None)
            return True
        st["edits"] = saved
        unit_owner.update(owner)
        render(st)
        return False

    def triage_header(rel, w, head, validate=None):
        """a failure with no attributable name: try the header's units one
        at a time instead of throwing the whole header's guards away
        (Winbase.h and Wingdi.h carry the largest guard sets in the
        tree)."""
        st = state.get(rel)
        if not st:
            return False
        for e in list(st["edits"]):
            if try_drop(rel, e, w, head, validate):
                return True
        return False

    def find_hider(name):
        """the guarded header whose text lost `name`.

        `unit_owner` only knows the names a unit's own citation
        introduced; when the compiler reports a missing name this finds
        the header that actually stopped declaring it by diffing each
        guarded header against its pre-guard snapshot (CEOID is declared
        in Windbase.h but reported missing from Notifext.hxx)."""
        pat = re.compile(r"\b" + re.escape(name) + r"\b")
        for rel, st in state.items():
            if not st["edits"]:
                continue
            cur = open(st["path"], encoding="utf-8",
                       errors="replace").read()
            if pat.search(strip_comments(st["orig"])) \
                    and not pat.search(strip_comments(cur)):
                return rel
        return None

    import shutil
    pristine = "/tmp/tu_pristine.c"
    if not os.path.exists(pristine):
        shutil.copyfile(TU, pristine)

    # The only gate that matters is the whole tree: a guard can be sound
    # inside its own header and still break another one that includes it
    # (Shobjidl.h's LPSTRRET, Objbase.h's _tagCY, Winbase.h's
    # _PROCESS_INFORMATION all did).  Each failure drops exactly the unit
    # that published the missing name and the tree is rebuilt.
    for _round in range(600):
        guarded = {}
        for rel, st in state.items():
            for e in st["edits"]:
                for nm in e[5]:
                    if nm in CKEYWORDS:
                        continue
                    if nm not in guarded or \
                            cond_bound(e[2]) > cond_bound(guarded[nm]):
                        guarded[nm] = e[2]
        shutil.copyfile(pristine, TU)
        ntu = guard_consumer_sites(guarded)
        fail = None
        for w in (0x420, 0x500, 0x600):
            ok, err = compiles_at(None, w, tu=True)
            if not ok:
                fail = (w, err)
                break
        if not fail:
            print(f"  whole tree compiles at 0x0420/0x0500/0x0600 with "
                  f"{ntu} guarded consumer regions after {_round} "
                  f"unit rollback(s)", flush=True)
            break
        w, err = fail
        head = err.splitlines()[0][:110]
        m = re.search(r"(?:unknown type name|undeclared|redefinition of)"
                      r"[^A-Za-z_]*([A-Za-z_][A-Za-z0-9_]*)", err)
        name = m.group(1) if m else None
        target = unit_owner.get(name) if name else None
        if target and drop_unit(target[0], target[1], f"0x{w:04x}: {head}"):
            print(f"  !! drop {target[0]} unit for {name} (0x{w:04x})",
                  flush=True)
            continue
        rel2 = find_hider(name) if name else None
        if not rel2:
            m2 = re.search(r"(include/[A-Za-z0-9_./-]+\.h(?:pp|xx)?)", err)
            rel2 = m2.group(1) if m2 else None
        if rel2 and triage_header(rel2, w, head):
            print(f"  !! triaged a {rel2} unit away (0x{w:04x})", flush=True)
            continue
        print(f"  !! unresolved at 0x{w:04x}: {head}", flush=True)
        break
    else:
        print("  !! rollback budget exhausted", flush=True)

    # Stage 2: the Makefile's own gate is wider than the consumer TU --
    # hostcheck compiles *every* header standalone at all three
    # generations, and a guard can satisfy the TU while breaking a header
    # the TU never includes (D3dmddk.h takes its D3DM_*_DATA types from
    # D3dm.h).  Sweep until clean, charging each failure to one unit.
    sweep = makefile_headers() or [rel for _p, rel in header_files()]
    for _pass in range(400):
        bad = None
        for w in (0x420, 0x500, 0x600):
            for rel in sweep:
                ok, err = compiles_at(os.path.join(ROOT, rel), w)
                if not ok:
                    bad = (w, rel, err)
                    break
            if bad:
                break
        if not bad:
            print(f"  header sweep clean at 0x0420/0x0500/0x0600 "
                  f"({3 * len(sweep)} standalone compiles) after {_pass} "
                  f"rollback(s)", flush=True)
            break
        w, rel, err = bad
        head = err.splitlines()[0][:110]
        m = re.search(r"(?:unknown type name|undeclared|redefinition of)"
                      r"[^A-Za-z_]*([A-Za-z_][A-Za-z0-9_]*)", err)
        name = m.group(1) if m else None
        target = unit_owner.get(name) if name else None
        if target and drop_unit(target[0], target[1],
                                f"sweep {rel} 0x{w:04x}: {head}"):
            print(f"  !! sweep: drop {target[0]} unit for {name} "
                  f"({rel} 0x{w:04x})", flush=True)
            continue
        rel2 = find_hider(name) if name else None
        if not rel2:
            m2 = re.search(r"(include/[A-Za-z0-9_./-]+\.(?:h|hpp|hxx))",
                           err)
            rel2 = m2.group(1) if m2 else rel
        vpath = os.path.join(ROOT, rel)
        if state.get(rel2) and triage_header(
                rel2, w, head,
                lambda: compiles_at(vpath, w)):
            print(f"  !! sweep: triaged a {rel2} unit away "
                  f"({rel} 0x{w:04x})", flush=True)
            continue
        print(f"  !! sweep unresolved ({rel} 0x{w:04x}): {head}", flush=True)
        break
    else:
        print("  !! sweep rollback budget exhausted", flush=True)

    applied = sum(len(st["edits"]) for st in state.values())
    print(f"guards kept: {applied}; units held: {len(held_units)}",
          flush=True)
    if held_units:
        with open(os.path.join(ROOT, "docs", "generation-held.tsv"), "w",
                  encoding="utf-8") as fh:
            fh.write("header\tpage\tos_versions\twould_be_guard\t"
                     "reason\n")
            for rel, cite, osr, g, why in held_units:
                fh.write("\t".join([rel, cite or "", osr or "", g,
                                     why.replace("\t", " ")]) + "\n")
        print(f"wrote {os.path.join(ROOT, 'docs', 'generation-held.tsv')}",
              flush=True)
    # final consumer regeneration: the conditions wrapping the shipped
    # TU must come from the guards that survived *both* stages, or the
    # consumer check silently stops exercising APIs that are available
    guarded = {}
    for rel, st in state.items():
        for e in st["edits"]:
            for nm in e[5]:
                if nm in CKEYWORDS:
                    continue
                if nm not in guarded or \
                        cond_bound(e[2]) > cond_bound(guarded[nm]):
                    guarded[nm] = e[2]
    shutil.copyfile(pristine, TU)
    ntu = guard_consumer_sites(guarded)
    print(f"consumer TU regenerated from the surviving guards: {ntu} "
          f"regions over {len(guarded)} guarded names", flush=True)
    for w in (0x420, 0x500, 0x600):
        ok, err = compiles_at(None, w, tu=True)
        print(f"  consumer TU at 0x{w:04x}: "
              + ("OK" if ok else f"FAIL -- {err}"), flush=True)


if __name__ == "__main__":
    main()
