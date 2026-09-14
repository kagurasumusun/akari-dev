#!/usr/bin/env python3
"""
decl-d1.py -- declare printed-signature functions that the tree
carries only as comments (audit class D1) or not at all.

For every harvested official page that prints a function prototype
(rows*.json `sig`), if the function is not yet declared live in
include/ and every parameter/return type resolves to a type already
declared live in this tree, the prototype is declared in the header
named by the page's Header row, with the page cited.  Nothing is
invented: prototypes are the pages' own prints (spacing restored on
glued tokens by greedy matching against live identifiers), and a
function is skipped outright when any type is unresolved.

Declaration decoration follows the documented evidence: coredll
import when the page's Link Library row names Coredll.lib or the
name is verified on the device-dump-audited coredll surface
(clean-room.md 3.2); otherwise a plain prototype.

Dry-run:  python3 tools/decl-d1.py <corpus> --dry
Apply:    python3 tools/decl-d1.py <corpus>
"""

import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDENT = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")


def _load(modname):
    import importlib.util
    here = os.path.dirname(os.path.abspath(__file__))
    spec = importlib.util.spec_from_file_location(
        modname, os.path.join(here, modname + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod

# The tree is physically split in two layers (docs/CHANGELOG-audit-
# 2026-09-14.md item 4):
#
#   include/       the application -dev layer (the headers an
#                  user-mode CE program includes)
#   include/oak/   the OAL/DDK/driver layer (OEM/BSP scope; kept in
#                  the tree, compiled by `make check`, but outside the
#                  application -dev set)
#
# Both layers are one C namespace for a CE build (the Makefile passes
# -I include -I include/oak), so every scanner must see both: a
# prototype printed on an official page whose parameter types are
# declared in the OAK layer is resolvable, and a page whose Header row
# names a header that lives in include/oak/ must be declared there --
# never re-created in include/.
INC = os.path.join(ROOT, "include")
OAK = os.path.join(ROOT, "include", "oak")
LAYERS = (INC, OAK)


def header_files():
    """(absolute path, header basename, layer dir) of every shipped
    header, both layers, basename-sorted."""
    for d in LAYERS:
        if not os.path.isdir(d):
            continue
        for fn in sorted(os.listdir(d)):
            if fn.endswith((".h", ".hxx", ".hpp")):
                yield os.path.join(d, fn), fn, d


# Header-row tokens that belong to the OAK/DDK layer (OEM/BSP scope,
# out of the user-mode -dev set).  A page whose Header row names one
# of these and for which the tree has no file is recorded as skipped
# ("oakonly") instead of creating a new header in the application
# layer.  Empty today: every such token already has a file in
# include/oak/ (verified by the dry run of this tool).
OAK_ONLY_HEADERS = set()


def resolve_header(name):
    """case-insensitive basename lookup across both layers; returns
    (absolute path, layer dir) or (None, None).  include/ wins when a
    basename exists in both layers (it never does today; asserted by
    `make defcheck`-time duplicate scan)."""
    low = name.lower()
    for d in (INC, OAK):
        if not os.path.isdir(d):
            continue
        for fn in os.listdir(d):
            if fn.lower() == low:
                return os.path.join(d, fn), d
    return None, None


C_KEYWORDS = {"void", "const", "unsigned", "signed", "struct", "enum",
              "union", "char", "short", "int", "long", "float", "double"}
DECOR = {"IN", "OUT", "OPTIONAL", "WINAPI", "CALLBACK", "FAR", "NEAR",
         "PASCAL", "APIENTRY", "CONST", "EXTERN_C"}
# COM-interface method prints documented as standalone pages; never
# free functions of the Win32 surface.
GENERIC_METHODS = {"Add", "AddRef", "Count", "Event", "Get", "Next",
                   "Query", "Read", "Release", "Remove", "Reset", "Set",
                   "Skip", "Write", "Lock", "Unlock"}


def load_live(incdir=None):
    """identifiers live in code (comments stripped) across BOTH
    layers; `incdir` is accepted for callers that still pass it and is
    ignored -- a symbol declared in include/oak/ is as live as one in
    include/ for a CE compile."""
    live = set()
    for path, _fn, _d in header_files():
        text = open(path, encoding="utf-8", errors="replace").read()
        code = re.sub(r"(?s)/\*.*?\*/", " ", text)
        code = re.sub(r"//[^\n]*", " ", code)
        live.update(IDENT.findall(code))
    return live


def load_types(incdir=None):
    """the real type universe: typedef names and struct/union/enum
    tags actually defined in the shipped headers, both layers."""
    types = set()
    for path, _fn, _d in header_files():
        text = open(path, encoding="utf-8", errors="replace").read()
        code = re.sub(r"(?s)/\*.*?\*/", " ", text)
        code = re.sub(r"//[^\n]*", " ", code)
        for m in re.finditer(r"\btypedef\b", code):
            i, depth = m.end(), 0
            end = -1
            while i < len(code):
                c = code[i]
                if c == "{":
                    depth += 1
                elif c == "}":
                    depth -= 1
                elif c == ";" and depth == 0:
                    end = i
                    break
                i += 1
            if end < 0:
                continue
            stmt = code[m.end():end]
            # function-pointer typedefs carry their alias inside the
            # parameter list: `typedef void (*PF_X)(int);` -> PF_X
            for fp in re.finditer(r"\(\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)",
                                  stmt):
                types.add(fp.group(1))
            stmt = re.sub(r"\([^()]*\)", " ", stmt)   # drop fn params
            names = re.sub(r"^.*?[}\]]\s*", "", stmt, flags=re.S)
            for part in names.split(","):
                part = part.strip().replace("*", " ").strip()
                toks = part.split()
                if not toks:
                    continue
                # M107a guard: a function-pointer typedef whose base type
                # cannot be resolved collapses to a single token here
                # (params dropped above), e.g. `typedef STATUS (*FN)(...)`
                # -> `STATUS`.  Adding that token would invent a type
                # definition that does not exist in the tree, which then
                # let later passes declare prototypes using it.  A real
                # alias always leaves at least two tokens (base + name).
                if len(toks) < 2:
                    continue
                types.add(toks[-1])
        for m in re.finditer(r"\b(?:struct|union|enum)\s+([A-Za-z_][A-Za-z0-9_]*)",
                             code):
            types.add(m.group(1))
    return types | C_KEYWORDS


def def_names(path):
    names, exports = set(), False
    for ln in open(path, encoding="utf-8", errors="replace"):
        s = ln.strip()
        if s.upper() == "EXPORTS":
            exports = True
            continue
        if exports and s and not s.startswith((";", "#")):
            names.add(s.split()[0])
    return names


def clean_sig(sig):
    s = sig.replace("\n", " ")
    s = re.sub(r"//[^\n]*", " ", s)           # CE3 inline param comments
    s = re.sub(r"\s+", " ", s).strip()
    # normalize separated pointer stars: "PVOID * p" -> "PVOID* p"
    s = re.sub(r"\s+\*\s+", "* ", s)
    s = re.sub(r"\s+\*(?=[A-Za-z_])", "*", s)
    s = s.rstrip(";").strip()
    return s


class Resolver:
    def __init__(self, live, types):
        self.live = live
        self.types = types
        self.by_prefix = sorted((t for t in types if t[0].isupper()),
                                key=len, reverse=True)

    def is_type(self, tok):
        return tok in self.types or tok in DECOR

    def split_glued(self, tok):
        """split 'HDChdc' -> ('HDC','hdc') using the longest defined
        type prefix; the remainder must look like a parameter name
        (lower-case initial)."""
        for t in self.by_prefix:
            if tok.startswith(t) and len(tok) > len(t):
                rest = tok[len(t):]
                if re.match(r"^[a-z_][A-Za-z0-9_]*$", rest):
                    return t, rest
                # glue right after a _PTR type keeps the CamelCase name
                # ("ULONG_PTRCancelId"); otherwise an upper-case
                # remainder signals a wrong short-prefix pick.
                if t.endswith("_PTR") and \
                        re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", rest):
                    return t, rest
        return None


def parse_sig(sig, res):
    """returns (ret, name, [(type, arg)...]) or None"""
    s = clean_sig(sig)
    if "(" not in s or ")" not in s or "::" in s or "<" in s or ">" in s:
        return None
    head, _, rest = s.partition("(")
    params_raw, _, tail = rest.rpartition(")")
    head_toks = head.split()
    if len(head_toks) < 2:
        return None
    name = head_toks[-1]
    if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name):
        return None
    # function-like macros (all caps) and entry points/callback docs
    if re.match(r"^[A-Z0-9_]+$", name) or name.endswith("Proc") \
            or name.endswith("CallbackFunc") \
            or name in ("DllMain", "WinMain", "wWinMain", "main") \
            or name in GENERIC_METHODS:
        return None
    ret = " ".join(head_toks[:-1])
    if "CALLBACK" in ret.split():
        # callback-prototype page (user implements it), not an import
        return None
    if ret.replace("*", " ").split():
        parts = []
        for tok in ret.split():
            stars = tok.count("*")
            bare = tok.replace("*", "")
            if res.is_type(bare):
                parts.append(bare + "*" * stars)
            else:
                g = res.split_glued(bare)
                if g:
                    parts.append(g[0] + "*" * stars)
                else:
                    return None
        ret = " ".join(parts)
    params = []
    for p in re.split(r",(?![^(]*\))", params_raw):
        p = p.strip()
        if not p:
            continue
        if p == "void":
            continue
        if "..." in p:
            return None
        toks = p.split()
        if len(toks) == 1:
            bare = toks[0].replace("*", "")
            stars = "*" * toks[0].count("*")
            if res.is_type(bare):
                params.append((bare + stars, ""))
                continue
            g = res.split_glued(bare)
            if g:
                params.append((g[0] + stars, g[1]))
                continue
            return None
        arg = toks[-1]
        typetoks = toks[:-1]
        if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", arg):
            return None
        if re.match(r"^[A-Z0-9_]+$", arg):
            # glued-type artifact, not a parameter name
            return None
        resolved = []
        for tok in typetoks:
            stars = tok.count("*")
            bare = tok.replace("*", "")
            if res.is_type(bare):
                resolved.append(bare + "*" * stars)
            else:
                g = res.split_glued(bare)
                if g:
                    resolved.append(g[0] + "*" * stars)
                    if g[1] and g[1][0].islower():
                        arg = g[1]
                else:
                    return None
        params.append((" ".join(resolved), arg))
    return ret, name, params


def main():
    corpus = sys.argv[1]
    apply = "--dry" not in sys.argv
    incdir = os.path.join(ROOT, "include")
    live = load_live(incdir)
    res = Resolver(live, load_types(incdir))
    surf = set()
    for fn in ("coredll4.def", "coredll.def", "coredll6.def",
               "coredll6-x86.def"):
        p = os.path.join(corpus, "coredll", fn)
        if os.path.exists(p):
            surf |= def_names(p)

    rows = {}
    for fn, tag in (("rows.json", "ce5+ce6"), ("rows4.json", "ce4"),
                    ("rows3.json", "ce3")):
        p = os.path.join(corpus, fn)
        for r in json.load(open(p, encoding="utf-8")):
            t = r.get("title", "").strip()
            if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", t):
                continue
            if not r.get("sig"):
                continue
            e = rows.setdefault(t, [])
            e.append((tag, r))

    out = {}
    skipped = {"self": 0, "types": 0, "noheader": 0, "parsed": 0}
    for name, entries in sorted(rows.items()):
        if name in live:
            skipped["self"] += 1
            continue
        # prefer ce5+ce6 rows, then ce4, then ce3; take first parseable
        entries.sort(key=lambda e: {"ce5+ce6": 0, "ce4": 1, "ce3": 2}[e[0]])
        chosen = None
        for tag, r in entries:
            parsed = parse_sig(r["sig"], res)
            if parsed and parsed[1] == name:
                chosen = (tag, r, parsed)
                break
        if not chosen:
            skipped["types"] += 1
            continue
        tag, r, (ret, fname, params) = chosen
        hdr = (r.get("header") or "").strip().rstrip(".").strip()
        if hdr.startswith("Include:"):
            hdr = hdr[8:].strip()
        if "," in hdr:  # "Urlmon.h, Urlmon.idl" -> first header token
            cand = [h.strip() for h in hdr.split(",")
                    if h.strip().endswith((".h", ".hxx", ".hpp"))]
            hdr = cand[0] if cand else hdr
        if hdr.endswith(".Se"):   # extraction artifact ("Commctrl.h.Se")
            hdr = hdr[:-3]
        hdr = hdr.split()[0] if hdr.split() else ""
        # alias headers: the tree carries the base header instead
        hdr = {"Kfuncs.h": "Winbase.h", "Cesync.h": "Objbase.h"}.get(hdr, hdr)
        if not hdr or not re.match(r"^[A-Za-z0-9_]+\.(h|hxx|hpp)$", hdr):
            skipped["noheader"] += 1
            continue
        # case-insensitive resolution against the shipped tree, BOTH
        # layers (include/ and include/oak/).  The layer that already
        # carries the header decides where the declaration lands, so a
        # page whose Header row names an OAK/DDK header is declared in
        # include/oak/ and never re-created in the application layer.
        hit_path, hit_layer = resolve_header(hdr)
        if hit_path:
            hdr = os.path.basename(hit_path)
            layer = hit_layer
        else:
            hit_path, layer = None, INC   # new app-layer header
            if hdr.lower() in OAK_ONLY_HEADERS:
                # The tree has no file for this Header row and the row
                # belongs to the OAK/DDK layer, which is out of the
                # user-mode -dev scope: recorded, not created.
                skipped["oakonly"] = skipped.get("oakonly", 0) + 1
                continue
        lib = (r.get("lib") or "").lower()
        coredll = ("coredll" in lib) or (name in surf) or (name + "W" in surf)
        plist = ", ".join((t + ((" " + a) if a else "")) for t, a in params) \
            if params else "void"
        if coredll:
            decl = (f"AKARI_CE_IMPORT {ret} {fname}({plist}) "
                    f"AKARI_CE_NAME({fname});")
        else:
            decl = f"{ret} {fname}({plist});"
        osr = r.get("os") or r.get("versions") or ""
        cite = r["id"].split("(")[0]
        out.setdefault((layer, hdr), []).append(
            (name, cite, osr, lib.strip(" ."), decl))
        skipped["parsed"] += 1

    # merge case-variant spellings of the same header inside one layer
    merged = {}
    for (layer, hdr), items in sorted(
            out.items(), key=lambda kv: (kv[0][0], kv[0][1].lower())):
        key = (layer, hdr.lower())
        if key in merged:
            tgt = merged[key][0]
            print(f"(merge {hdr} -> {tgt})")
            merged[key][1].extend(items)
        else:
            merged[key] = [hdr, items]
    out = {}
    for (layer, _low), (hdr, items) in merged.items():
        out[(layer, hdr)] = items

    total = 0
    for (layer, hdr), items in sorted(
            out.items(), key=lambda kv: (kv[0][0], kv[0][1].lower())):
        total += len(items)
        where = os.path.relpath(layer, ROOT)
        path = os.path.join(layer, hdr)
        if not os.path.exists(path) and not apply:
            print(f"{where}/{hdr}: would CREATE (+{len(items)} planned)")
            continue
        if not os.path.exists(path):
            guard = "AKARI_" + re.sub(r"[^A-Z0-9]+", "_", hdr.upper()) + "_"
            text = (
                "/*\n"
                f" * {hdr} -- declarations recovered from the official\n"
                " * page prints (tools/decl-d1.py, M105 header creation).\n"
                " *\n"
                " * Copyright (c) 2026 Akari API contributors\n"
                " * SPDX-License-Identifier: MIT\n"
                " *\n"
                " * Every declaration below is an official page's own\n"
                " * print (page id cited).  Prints whose types include/\n"
                " * cannot yet resolve are recorded verbatim in the\n"
                " * header comment blocks by later passes; nothing is\n"
                " * dropped or invented.\n"
                " */\n"
                "\n"
                f"#ifndef {guard}\n"
                f"#define {guard}\n"
                "\n"
                "#include \"Windef.h\"    /* base Win32 types */\n"
                "#include \"Winnt.h\"     /* HRESULT, LARGE_INTEGER, ... */\n"
                f"\n#endif /* {guard} */\n")
            open(path, "w", encoding="utf-8").write(text)
            print(f"{hdr}: CREATED (+{len(items)} planned)")
        else:
            print(f"{hdr}: +{len(items)}")
        if not apply:
            continue
        text = open(path, encoding="utf-8").read()
        orig = text
        m = re.search(r"\n#endif /\* [A-Za-z_][A-Za-z0-9_]* \*/\s*$", text)
        if not m:
            print(f"  !! no footer in {hdr}, skipped writing")
            continue
        block = ["", "/* --- M104 declarations: printed prototypes recovered",
                 " * from the official pages (tools/decl-d1.py). -------- */", ""]
        for name, cite, osr, lib, decl in items:
            where = f"{osr + '; ' if osr else ''}{lib}"
            block.append(f"/* {cite}: page-printed prototype "
                         f"({where.rstrip('; ')}). */")
            block.append(decl)
            block.append("")
        text = text[:m.start()] + "\n" + "\n".join(block) + text[m.start():]
        open(path, "w", encoding="utf-8").write(text)
        # Gate: the header must still compile standalone (Makefile
        # hostcheck/crosscheck compile every header on its own).  A
        # prototype whose types come from a header the target does not
        # include is rolled back and stays held.
        ok, err = _load("decl-types").compiles(path)
        if not ok:
            open(path, "w", encoding="utf-8").write(orig)
            total -= len(items)
            skipped["held-nocompile"] = skipped.get("held-nocompile", 0) + 1
            print(f"  !! {where}/{hdr}: rolled back "
                  f"({len(items)} declarations held) -- {err}")
    print(f"TOTAL declared: {total}  "
          f"(skipped: {skipped})")


if __name__ == "__main__":
    main()
