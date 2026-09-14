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


def compiles_at(path, wince, tu=False):
    """standalone compile of one header (or of the shipped consumer TU)
    at one CE generation, exactly as the Makefile compiles it."""
    import subprocess
    inc = os.path.join(ROOT, "include")
    cmd = ["cc", "-std=c11", "-ffreestanding", "-Werror",
           f"-D_WIN32_WCE={wince}", "-I", inc,
           "-I", os.path.join(inc, "oak")]
    if tu:
        cmd += ["-fsyntax-only", os.path.join(ROOT, "tests", "host",
                                              "tu_compile.c")]
    else:
        cmd += ["-include", path, "-fsyntax-only", "-x", "c", os.devnull]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
    except OSError:
        return True, ""
    if r.returncode == 0:
        return True, ""
    for lne in (r.stderr or "").splitlines():
        if "error:" in lne:
            # keep the "file:line:" prefix: the caller needs to know
            # which file lost a declaration
            return False, lne.strip()
    return False, "compile failed"


TU = os.path.join(ROOT, "tests", "host", "tu_compile.c")


def guard_consumer_sites(guarded):
    """wrap the consumer TU's uses of now-guarded APIs in the same
    condition.  A CE 4.2 program cannot call a CE 5.0 API; the shipped
    consumer check has to say so exactly like a real consumer would.
    `guarded` maps name -> condition."""
    text = open(TU, encoding="utf-8", errors="replace").read()
    lines = text.splitlines()
    hits = []
    for i, ln in enumerate(lines):
        s = ln.strip()
        if not s or s.startswith(("#", "/*", "*", "//")):
            continue
        for name, cond in guarded.items():
            if re.search(r"\b" + re.escape(name) + r"\b", ln):
                # extend to the end of the statement
                j = i
                while j < len(lines) and not lines[j].rstrip().endswith(";") \
                        and not lines[j].rstrip().endswith("}") \
                        and j - i < 40:
                    j += 1
                hits.append((i, j, cond, name))
                break
    # merge overlapping/adjacent ranges with the same condition
    merged = []
    for a, b, cond, name in sorted(hits):
        if merged and merged[-1][2] == cond and a <= merged[-1][1] + 1:
            merged[-1][1] = max(merged[-1][1], b)
            merged[-1][3].add(name)
        else:
            merged.append([a, b, cond, {name}])
    for a, b, cond, names in sorted(merged, reverse=True):
        note = ", ".join(sorted(names)[:3]) + ("..." if len(names) > 3 else "")
        lines.insert(b + 1, f"#endif /* {cond} */")
        lines.insert(a, f"#if {cond}   /* consumer: {note} */")
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
    # Cross-header uses: a name another header's code refers to cannot be
    # hidden from a generation that header still compiles for (CEDDK.h
    # prints `PDEVMGR_DEVICE_INFORMATION` in a prototype while the
    # typedef is Winbase.h's).  Such units are skipped and reported, not
    # guarded -- resolving them needs the *using* declaration's own page
    # row, which is a separate attribution question.
    code_of = {}
    for rel, _got in per_file.items():
        code_of[rel] = strip_comments(
            open(os.path.join(ROOT, rel), encoding="utf-8",
                 errors="replace").read())
    byfile = {}
    crossheader = []
    for rel, got in per_file.items():
        for ln, name, cite, osr, lo, hi, g in got:
            if not g or "<=" in g:
                continue
            # every identifier the unit introduces, not just its primary
            # name: a typedef's pointer tail (`} DEVMGR_DEVICE_INFORMATION,
            # *PDEVMGR_DEVICE_INFORMATION;`) is what other headers use.
            span = stmt_span(open(os.path.join(ROOT, rel),
                                  encoding="utf-8",
                                  errors="replace").read().splitlines(), ln)
            unit_lines = open(os.path.join(ROOT, rel), encoding="utf-8",
                              errors="replace").read().splitlines()
            first, last = span if span else (ln, ln)
            names = {name} | {t for t in IDENT_ALL.findall(
                strip_comments("\n".join(unit_lines[first:last + 1])))
                if len(t) > 2}
            users = None
            for nm in names:
                for r2, c2 in code_of.items():
                    if r2 != rel and re.search(r"\b" + re.escape(nm)
                                               + r"\b", c2):
                        users = (nm, r2)
                        break
                if users:
                    break
            if users:
                crossheader.append((rel, users[0], g, users[1]))
                continue
            byfile.setdefault(rel, []).append((ln, name, cite, osr, g))
    applied = rolled = skipped = 0
    for rel, items in sorted(byfile.items()):
        path = os.path.join(ROOT, rel)
        text = open(path, encoding="utf-8", errors="replace").read()
        orig = text
        snap = path + ".preguard"
        if not os.path.exists(snap):
            open(snap, "w", encoding="utf-8").write(orig)
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
            # A page's constants/declarations are usually printed as one
            # block under one citation comment.  Extend the unit over the
            # consecutive declarations that share that comment, so a
            # documented set is never split (guarding REG_NOTIFY_CHANGE_
            # NAME but not REG_NOTIFY_CHANGE_LAST_SET would publish half
            # a page's table at one generation and half at another).
            merged = any(e[0] == cstart and e[1] == first - 1 for e in edits)
            if merged:
                for i, e in enumerate(edits):
                    if e[0] == cstart:
                        edits[i] = (e[0], last, e[2], e[3], e[4])
                        break
                continue
            if any(not (e[1] < first or e[0] > last) for e in edits):
                skipped += 1     # overlapping unit
                continue
            edits.append((cstart, last, g, cite, osr))
        # only the last declaration of a merged run may extend it
        edits.sort()
        if not edits:
            continue
        # merge units that are contiguous (blank lines between them are
        # part of the same printed block) and carry the same condition
        merged = []
        for e in sorted(edits):
            if merged and merged[-1][2] == e[2] \
                    and all(not t.strip() or t.strip().startswith(("*", "/*", "//"))
                            for t in lines[merged[-1][1] + 1:e[0]]):
                merged[-1] = (merged[-1][0], e[1], e[2], e[3], e[4])
            else:
                merged.append(list(e))
        edits = [tuple(e) for e in merged]
        for cstart, last, g, cite, osr in sorted(edits, reverse=True):
            lines.insert(last + 1, f"#endif /* {g} */")
            lines.insert(cstart, f"#if {g}   /* {osr} ({cite}) */")
        open(path, "w", encoding="utf-8").write("\n".join(lines) + "\n")
        bad = None
        for w in (0x420, 0x500, 0x600):
            ok, err = compiles_at(path, w)
            if not ok:
                bad = f"header _WIN32_WCE=0x{w:04x}: {err}"
                break
        if bad:
            open(path, "w", encoding="utf-8").write(orig)
            rolled += 1
            print(f"  !! {rel}: rolled back ({len(edits)} guards) -- {bad}")
        else:
            applied += len(edits)
            print(f"  {rel}: +{len(edits)} generation guards")
    print(f"guards applied: {applied}; headers rolled back: {rolled}; "
          f"units skipped (nested/overlapping/unbounded): {skipped}")
    if crossheader:
        print(f"units held (name also used by another header's code): "
              f"{len(crossheader)}")
        for rel, name, g, user in crossheader[:15]:
            print(f"  {rel}: {name} [{g}] -- also in {user}")

    # ---- consumer TU: same conditions on the uses, then the full gate --
    guarded = {}
    for rel, got in per_file.items():
        for ln, name, cite, osr, lo, hi, g in got:
            if g and "<=" not in g:
                guarded.setdefault(name, g)
    n = guard_consumer_sites(guarded)
    print(f"consumer TU: {n} guarded regions")
    # the shipped TU must compile at all three generations; a header
    # whose guard breaks it (a cross-header dependency on a type the
    # guard hides) is rolled back and reported.
    # name -> header that guards its declaration, so a cross-header
    # failure can be traced to the guard that hid the declaration (the
    # file named by the compiler is only the *user* of the name).
    guarded_in = {}
    decl_owner = {}
    for rel, got in per_file.items():
        for ln, name, cite, osr, lo, hi, g in got:
            decl_owner.setdefault(name, rel)
            if g and "<=" not in g:
                guarded_in.setdefault(name, rel)
    done = set()

    def rollback(rel, why):
        nonlocal rolled
        path = os.path.join(ROOT, rel)
        snap = path + ".preguard"
        if not os.path.exists(snap):
            print(f"  !! {rel}: no pre-guard snapshot; left as is")
            return False
        import shutil
        shutil.copyfile(snap, path)
        rolled += 1
        done.add(rel)
        print(f"  !! {rel}: rolled back to its pre-guard state ({why})")
        return True

    for _round in range(20):
        bad_rel = None
        for w in (0x420, 0x500, 0x600):
            ok, err = compiles_at(None, w, tu=True)
            if ok:
                continue
            print(f"  !! TU at 0x{w:04x}: {err}")
            # the compiler quotes the missing name in typographic quotes
            m = re.search(r"(?:unknown type name|undeclared)[^A-Za-z_]*"
                          "([A-Za-z_][A-Za-z0-9_]*)", err)
            name = m.group(1) if m else None
            # the guard that hid it lives in the header that declares it,
            # not in the file the compiler names (that one only uses it).
            # Find it by diffing every guarded header against its
            # pre-guard snapshot: the header whose snapshot mentions the
            # name and whose current text does not is the one that hid it
            # (a typedef tail such as `*PDEVMGR_DEVICE_INFORMATION` is not
            # a declaration name, so the attribution table cannot see it).
            bad_rel = None
            if name:
                for rel2, _got in per_file.items():
                    snap = os.path.join(ROOT, rel2) + ".preguard"
                    cur = os.path.join(ROOT, rel2)
                    if not os.path.exists(snap):
                        continue
                    pat = re.compile(r"\b" + re.escape(name) + r"\b")
                    a = strip_comments(open(snap, encoding="utf-8",
                                            errors="replace").read())
                    b = strip_comments(open(cur, encoding="utf-8",
                                            errors="replace").read())
                    if pat.search(a) and not pat.search(b):
                        bad_rel = rel2
                        break
            if not bad_rel and name:
                bad_rel = guarded_in.get(name)
            if not bad_rel:
                m2 = re.search(r"(include/[A-Za-z0-9_./-]+\.h)", err)
                bad_rel = m2.group(1) if m2 else None
            if bad_rel in done:
                print(f"  !! {bad_rel}: already rolled back; stopping")
                bad_rel = None
            break
        if not bad_rel:
            break
        if not rollback(bad_rel, f"hides a declaration another header uses"):
            break
    for w in (0x420, 0x500, 0x600):
        ok, err = compiles_at(None, w, tu=True)
        print(f"  consumer TU at 0x{w:04x}: "
              + ("OK" if ok else f"FAIL -- {err}"))


if __name__ == "__main__":
    main()
