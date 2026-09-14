#!/usr/bin/env python3
"""
decl-types.py -- declare printed typedef / struct / enum / constant
definitions that include/ does not yet carry, so that printed
function prototypes blocked on those types can be declared.

Every emitted declaration is an official page's own print (page id
cited).  A definition is skipped outright when any constituent type
or constant is not already live in the tree -- nothing invented.
Run to fixpoint: each pass's new types unblock later rows.

Dry-run:  python3 tools/decl-types.py <corpus> --dry
Apply:    python3 tools/decl-types.py <corpus>
"""

import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDENT = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")

C_KEYWORDS = {"void", "const", "unsigned", "signed", "struct", "enum",
              "union", "char", "short", "int", "long", "float", "double"}


def load_code(incdir):
    code_all = ""
    for fn in sorted(os.listdir(incdir)):
        if not fn.endswith((".h", ".hxx", ".hpp")):
            continue
        text = open(os.path.join(incdir, fn), encoding="utf-8",
                    errors="replace").read()
        text = re.sub(r"(?s)/\*.*?\*/", " ", text)
        text = re.sub(r"//[^\n]*", " ", text)
        code_all += text + "\n"
    return code_all


def load_live(code):
    return set(IDENT.findall(code))


def load_types(code):
    types = set()
    for m in re.finditer(r"\btypedef\b", code):
        end = code.find(";", m.end())
        if end < 0:
            continue
        stmt = code[m.end():end]
        stmt = re.sub(r"\([^()]*\)", " ", stmt)
        names = re.sub(r"^.*?[}\]]\s*", "", stmt, flags=re.S)
        for part in names.split(","):
            part = part.strip().replace("*", " ").strip()
            toks = part.split()
            if toks:
                types.add(toks[-1])
    for m in re.finditer(r"\b(?:struct|union|enum)\s+([A-Za-z_][A-Za-z0-9_]*)",
                         code):
        types.add(m.group(1))
    return types | C_KEYWORDS


def load_consts(code):
    consts = set()
    for m in re.finditer(r"#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+"
                         r"(?:0[Xx][0-9A-Fa-f]+|-?\d+|[\dLUlu]+)\b", code):
        consts.add(m.group(1))
    for m in re.finditer(r"\benum\b[^{};]*\{([^{}]*)\}", code):
        for item in m.group(1).split(","):
            nm = item.split("=")[0].strip()
            if re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", nm):
                consts.add(nm)
    return consts


def norm_header(hdr):
    hdr = (hdr or "").strip().rstrip(".").strip()
    if hdr.startswith("Include:"):
        hdr = hdr[8:].strip()
    if "," in hdr:
        cand = [h.strip() for h in hdr.split(",")
                if h.strip().endswith((".h", ".hxx", ".hpp"))]
        hdr = cand[0] if cand else hdr
    if hdr.endswith(".Se"):
        hdr = hdr[:-3]
    hdr = hdr.split()[0] if hdr.split() else ""
    return {"Kfuncs.h": "Winbase.h", "Cesync.h": "Objbase.h"}.get(hdr, hdr)


def resolve(incdir, hdr):
    """existing file (case-insensitive), or hdr itself to create"""
    if not hdr or not re.match(r"^[A-Za-z0-9_]+\.(h|hxx|hpp)$", hdr):
        return None
    if os.path.exists(os.path.join(incdir, hdr)):
        return hdr
    hit = next((fn for fn in os.listdir(incdir)
                if fn.lower() == hdr.lower()), None)
    return hit or hdr


def clean(sig):
    s = sig.replace("\n", " ")
    s = re.sub(r"//[^\n]*", " ", s)
    s = re.sub(r"\s+", " ", s).strip()
    return s.rstrip(";").strip()


NUM = r"(?:0[Xx][0-9A-Fa-f]+|-?\d+)[ULul]*"


def value_ok(tok, live):
    tok = tok.strip()
    if not tok:
        return False
    atoms = re.split(r"[+\-*/() ]+", tok)
    if not all(atoms):
        return False
    for a in atoms:
        if re.fullmatch(NUM, a):
            continue
        if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", a) and a in live:
            continue
        return False
    # balanced parens only
    if tok.count("(") != tok.count(")"):
        return False
    return True


class Ctx:
    def __init__(self, code):
        self.live = load_live(code)
        self.types = load_types(code)
        self.consts = load_consts(code)

    def type_ok(self, tok):
        stars = tok.count("*")
        bare = tok.replace("*", "").strip()
        if bare in ("struct", "union", "enum"):
            return False
        return bare in self.types or bare in C_KEYWORDS

    def member_ok(self, m, curtag=None):
        """m like 'DWORD cbSize', 'TCHAR szName[80]', 'BYTE bPartType'"""
        m = m.strip()
        if not m:
            return False
        bf = re.search(r":\s*\d+\s*$", m)
        if bf:
            m = m[:bf.start()].strip()
        arr = re.search(r"\[\s*([^\]]*)\s*\]\s*$", m)
        if arr:
            arrsz = arr.group(1).strip()
            m = m[:arr.start()].strip()
            if arrsz and not value_ok(arrsz, self.live | self.consts):
                return False
        toks = m.split()
        if len(toks) < 2:
            return False
        name = toks[-1]
        if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name) \
                or re.match(r"^[A-Z0-9_]+$", name):
            return False
        typetoks = toks[:-1]
        # struct/union tag member: struct TAG [FAR|NEAR] [*]
        if typetoks[0] in ("struct", "union"):
            if len(typetoks) < 2:
                return False
            tag = typetoks[1]
            if tag not in self.types and tag != curtag:
                return False
            rest = [t for t in typetoks[2:] if t not in ("FAR", "NEAR")]
            if rest and not all(t == "*" or set(t) == {"*"} for t in rest):
                # embedded by value: only if the tag is fully live
                if rest or tag not in self.types:
                    return False
            return True
        for t in typetoks:
            if t in ("FAR", "NEAR"):
                continue
            if not self.type_ok(t):
                return False
        return True


def try_simple_typedef(sig, ctx):
    """typedef <type> NAME / typedef <type> *NAME[, *P2...]"""
    m = re.match(r"^typedef\s+(.+)$", sig)
    if not m:
        return None
    body = m.group(1).strip()
    # opaque struct pointer: typedef struct tagX X; / typedef struct X *PX;
    mo = re.match(r"^(struct|union)\s+([A-Za-z_][A-Za-z0-9_]*)\s*$", body)
    if mo:
        return ("opaque", f"typedef {mo.group(1)} {mo.group(2)} "
                f"{mo.group(2)};", mo.group(2))
    mo = re.match(r"^(struct|union)\s+([A-Za-z_][A-Za-z0-9_]*)\s*"
                  r"(\*+)\s*([A-Za-z_][A-Za-z0-9_]*)$", body)
    if mo:
        return ("opaqueptr", f"typedef {mo.group(1)} {mo.group(2)} "
                f"{mo.group(3)}{mo.group(4)};", mo.group(4))
    parts = [p.strip() for p in body.split(",")]
    base_toks = None
    out_names = []
    for i, p in enumerate(parts):
        toks = p.split()
        if i == 0:
            name = toks[-1]
            if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name):
                return None
            base_toks = toks[:-1]
            stars = name.count("*")
            if stars:
                base_toks = base_toks + ["*" * stars]
                name = name.replace("*", "")
            out_names.append((name, ""))
        else:
            nm = p.replace("*", "").strip()
            if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", nm):
                return None
            out_names.append((nm, "*" * p.count("*")))
    for t in base_toks:
        if not ctx.type_ok(t):
            return None
    declared = " ".join(base_toks)
    names = ", ".join(s + n for n, s in out_names)
    return ("simple", f"typedef {declared} {names};", out_names[0][0])


def try_enum(sig, ctx):
    m = re.match(r"^typedef\s+enum\s*(?:[A-Za-z_][A-Za-z0-9_]*)?\s*"
                 r"\{(.*)\}\s*([A-Za-z_][A-Za-z0-9_]*)\s*"
                 r"(?:,\s*\*?\s*([A-Za-z_][A-Za-z0-9_]*))?$", sig)
    if not m:
        return None
    body, name, ptr = m.group(1), m.group(2), m.group(3)
    items = []
    for it in body.split(","):
        it = it.strip()
        if not it:
            continue
        if "=" in it:
            k, v = it.split("=", 1)
            k, v = k.strip(), v.strip()
            if not value_ok(v, ctx.live | ctx.consts):
                return None
            items.append((k, v))
        else:
            items.append((it, None))
    for k, _ in items:
        if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", k):
            return None
        if k in ctx.live and k != name:
            return None
    body_s = ", ".join((f"{k} = {v}" if v else k) for k, v in items)
    tail = f", *{ptr}" if ptr else ""
    return ("enum", f"typedef enum {name.lower()}_tag {{ {body_s} }} "
            f"{name}{tail};", name)


def try_struct(sig, ctx):
    m = re.match(r"^typedef\s+struct\s*([A-Za-z_][A-Za-z0-9_]*)?\s*"
                 r"\{(.*)\}\s*([A-Za-z_][A-Za-z0-9_]*)\s*(.*)$", sig)
    if not m:
        return None
    tag, body, name, tail = (m.group(1), m.group(2), m.group(3),
                             m.group(4).strip())
    ptrs = []
    if tail:
        for p in tail.split(","):
            p = p.strip()
            mo = re.match(r"^\*+\s*([A-Za-z_][A-Za-z0-9_]*)$", p)
            if not mo or not p.startswith("*"):
                return None
            ptrs.append(mo.group(1))
    members = [mb.strip() for mb in body.split(";") if mb.strip()]
    lines = []
    for mb in members:
        if not ctx.member_ok(mb, curtag=tag):
            return None
        # normalize glue spacing inside array sizes / bitfields
        mb = re.sub(r"\s+", " ", mb)
        lines.append("    " + mb + ";")
    if not lines:
        return None
    if tag and tag in ctx.live and tag != name:
        return None       # would collide with an existing tag
    use_tag = tag or ("_" + name)
    tail_s = (", " + ", ".join("*" + p for p in ptrs)) if ptrs else ""
    body_s = "\n".join(lines)
    return ("struct", f"typedef struct {use_tag} {{\n{body_s}\n}} "
            f"{name}{tail_s};", name)


def try_define(sig, ctx):
    m = re.match(r"^#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.+)$", sig)
    if not m:
        return None
    name, val = m.group(1), m.group(2).strip()
    if not value_ok(val, ctx.live | ctx.consts):
        return None
    return ("define", f"#define {name} {val}", name)


def main():
    corpus = sys.argv[1]
    apply = "--dry" not in sys.argv
    incdir = os.path.join(ROOT, "include")
    ctx = Ctx(load_code(incdir))

    rows = {}
    for fn, tag in (("rows.json", "ce5+ce6"), ("rows4.json", "ce4"),
                    ("rows3.json", "ce3")):
        for r in json.load(open(os.path.join(corpus, fn),
                                encoding="utf-8")):
            sig = (r.get("sig") or "").strip()
            if not sig:
                continue
            s = clean(sig)
            kind = None
            if s.startswith("typedef"):
                kind = "typedef"
            elif s.startswith("#define"):
                kind = "define"
            if not kind:
                continue
            t = r.get("title", "").strip()
            mo = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)\s*(?:\(.*\))?$", t)
            if not mo:
                continue
            e = rows.setdefault(mo.group(1), [])
            e.append((tag, kind, r))

    out = {}
    stats = {"self": 0, "unresolved": 0, "noheader": 0, "ok": 0}
    for name, entries in sorted(rows.items()):
        if name in ctx.live:
            stats["self"] += 1
            continue
        entries.sort(key=lambda e: {"ce5+ce6": 0, "ce4": 1,
                                    "ce3": 2}[e[0]])
        chosen = None
        for tag, kind, r in entries:
            s = clean(r["sig"])
            res = None
            if kind == "define":
                res = try_define(s, ctx)
            else:
                res = (try_simple_typedef(s, ctx) or try_enum(s, ctx)
                       or try_struct(s, ctx))
            # the print must declare THIS page's identifier; pages
            # that reprint another type's definition do not count
            if res and res[2] == name:
                chosen = (r, res)
                break
        if not chosen:
            stats["unresolved"] += 1
            continue
        r, (kind, text, _dn) = chosen
        hdr = resolve(incdir, norm_header(r.get("header")))
        if not hdr:
            stats["noheader"] += 1
            continue
        cite = r["id"].split("(")[0]
        osr = r.get("os") or ""
        out.setdefault(hdr, []).append((name, cite, osr, kind, text))
        stats["ok"] += 1

    total = 0
    for hdr, items in sorted(out.items(), key=lambda kv: kv[0].lower()):
        total += len(items)
        path = os.path.join(incdir, hdr)
        if not os.path.exists(path) and not apply:
            print(f"{hdr}: would CREATE (+{len(items)} types planned)")
            continue
        if not os.path.exists(path):
            guard = "AKARI_" + re.sub(r"[^A-Z0-9]+", "_", hdr.upper()) + "_"
            text = (
                "/*\n"
                f" * {hdr} -- type definitions recovered from the official\n"
                " * page prints (tools/decl-types.py).\n"
                " *\n"
                " * Copyright (c) 2026 Akari API contributors\n"
                " * SPDX-License-Identifier: MIT\n"
                " */\n"
                "\n"
                f"#ifndef {guard}\n"
                f"#define {guard}\n"
                "\n"
                "#include \"Windef.h\"    /* base Win32 types */\n"
                "#include \"Winnt.h\"     /* HRESULT, LARGE_INTEGER, ... */\n"
                f"\n#endif /* {guard} */\n")
            open(path, "w", encoding="utf-8").write(text)
            print(f"{hdr}: CREATED (+{len(items)} types planned)")
        else:
            print(f"{hdr}: +{len(items)} types")
        if not apply:
            continue
        text = open(path, encoding="utf-8").read()
        m = re.search(r"\n#endif /\* [A-Za-z_][A-Za-z0-9_]* \*/\s*$", text)
        if not m:
            print(f"  !! no footer in {hdr}, skipped writing")
            continue
        block = ["", "/* --- type definitions from official page prints",
                 " * (tools/decl-types.py). ----------------------------- */",
                 ""]
        for name, cite, osr, kind, decl in items:
            where = f"{osr + '; ' if osr else ''}"
            block.append(f"/* {cite}: page-printed definition "
                         f"({where.rstrip('; ')}). */")
            block.append(decl)
            block.append("")
        text = text[:m.start()] + "\n" + "\n".join(block) + text[m.start():]
        open(path, "w", encoding="utf-8").write(text)
    print(f"TOTAL types declared: {total}  (stats: {stats})")


if __name__ == "__main__":
    main()
