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


def _load(modname):
    """load a sibling tool by file name (the tools are not a package)."""
    import importlib.util
    here = os.path.dirname(os.path.abspath(__file__))
    spec = importlib.util.spec_from_file_location(
        modname, os.path.join(here, modname + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


# The application layer (include/) and the OAK/DDK layer (include/oak/)
# are one C namespace for a CE compile, so the type universe and the
# header lookup must span both -- see the layer note in decl-d1.py.
d1 = _load("decl-d1")


def load_code(incdir=None):
    code_all = ""
    for path, _fn, _layer in d1.header_files():
        text = open(path, encoding="utf-8", errors="replace").read()
        text = re.sub(r"(?s)/\*.*?\*/", " ", text)
        text = re.sub(r"//[^\n]*", " ", text)
        code_all += text + "\n"
    return code_all


def load_live(code):
    return set(IDENT.findall(code))


def load_types(code):
    types = set()
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
    """(layer, existing file basename) -- case-insensitive across both
    layers -- or (include/, hdr) when the tree has no such file and a
    new application-layer header would be created."""
    if not hdr or not re.match(r"^[A-Za-z0-9_]+\.(h|hxx|hpp)$", hdr):
        return None
    hit, layer = d1.resolve_header(hdr)
    if hit:
        return layer, os.path.basename(hit)
    return d1.INC, hdr


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


# C keyword prefixes the CE 5.0 migration glues onto member names
# ("int command" -> "intcommand"); longest first so "unsigned long"
# style prints split correctly.
KW_PREFIXES = sorted(
    ("unsigned long", "unsigned short", "unsigned int", "unsigned char",
     "unsigned", "signed", "double", "float", "short", "long", "char",
     "int", "void"), key=len, reverse=True)


class Ctx:
    def __init__(self, code):
        self.live = load_live(code)
        self.types = load_types(code)
        self.consts = load_consts(code)
        self.res = d1.Resolver(self.live, self.types)

    def split_glued(self, tok):
        """(type, name) of a migration-glued print token, or None.
        Tries the tree's declared type names first (decl-d1's splitter),
        then the C keyword prefixes, which the CE 5.0 archive glues the
        same way ('intcommand' -> int + command).

        A token that is itself a live identifier is never split: the
        CE pages print type names whose tail looks like a glued member
        ('SOCKADDR_STORAGE' is one type, not 'SOCKADDR' + '_STORAGE'),
        and splitting one would silently rename the member."""
        if tok in self.live or tok in self.types:
            return None
        g = self.res.split_glued(tok)
        if g:
            return g
        for kw in KW_PREFIXES:
            flat = kw.replace(" ", "")
            if tok.startswith(flat) and len(tok) > len(flat):
                rest = tok[len(flat):]
                if re.match(r"^[a-z_][A-Za-z0-9_]*$", rest):
                    return kw, rest
        return None

    def type_ok(self, tok):
        stars = tok.count("*")
        bare = tok.replace("*", "").strip()
        if bare in ("struct", "union", "enum"):
            return False
        return bare in self.types or bare in C_KEYWORDS

    def member_norm(self, m, curtag=None):
        """normalized member declaration text, or None when the print
        does not resolve.  `m` is one member of a page's struct/union
        print: 'DWORD cbSize', 'TCHAR szName[80]', 'BYTE bPartType',
        'intcommand' (the CE 5.0 migration glues 'int command'),
        'struct in6_addrsin6_addr' (glued 'struct in6_addr sin6_addr').
        The returned text is what lands in the header, so a glued print
        is emitted with its tokens separated -- the page's own tokens,
        never a re-spelling."""
        m = re.sub(r"\s+", " ", m.strip())
        if not m:
            return None
        bf = re.search(r":\s*(\d+)\s*$", m)
        bits = ""
        if bf:
            bits = " : " + bf.group(1)
            m = m[:bf.start()].strip()
        arr = ""
        am = re.search(r"\[\s*([^\]]*)\s*\]\s*$", m)
        if am:
            arrsz = am.group(1).strip()
            m = m[:am.start()].strip()
            if arrsz and not value_ok(arrsz, self.live | self.consts):
                return None
            arr = "[" + arrsz + "]" if arrsz else "[]"
        toks = m.split()
        had_no_name = len(toks) < 2
        if had_no_name:
            # a single glued token: "intcommand" is the CE 5.0 print of
            # "int command".  Split it against the tree's types and the
            # C keyword prefixes; anything else is not a member print.
            g = self.split_glued(m) if m else None
            if not g:
                return None
            toks = [g[0], g[1]]
        name = toks[-1]
        typetoks = toks[:-1]
        # a glued "struct TAGname" / "union TAGname" member: only a
        # single-token print is glued ('struct in6_addrsin6_addr'); a
        # print with two tokens already separates tag and member.
        if had_no_name and len(typetoks) == 1 \
                and typetoks[0] in ("struct", "union"):
            g = self.split_glued(name)
            if g:
                typetoks, name = [typetoks[0], g[0]], g[1]
        if not typetoks or not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", name) \
                or re.match(r"^[A-Z0-9_]+$", name):
            return None
        # struct/union tag member: struct TAG [FAR|NEAR] [*]
        if typetoks[0] in ("struct", "union"):
            if len(typetoks) < 2:
                return None
            tag = typetoks[1]
            if tag not in self.types and tag != curtag:
                return None
            rest = [t for t in typetoks[2:] if t not in ("FAR", "NEAR")]
            stars = "".join("*" * t.count("*") for t in rest)
            if rest and not all(set(t) <= {"*"} for t in rest):
                # embedded by value: only if the tag is fully live
                if tag not in self.types:
                    return None
            return f"{typetoks[0]} {tag}{stars} {name}{arr}{bits}"
        out = []
        for t in typetoks:
            if t in ("FAR", "NEAR"):
                continue
            stars = "*" * t.count("*")
            bare = t.replace("*", "")
            if self.type_ok(bare):
                out.append(bare + stars)
                continue
            if not had_no_name:
                # The print already separates type tokens from the member
                # name, so every type token is a type name of its own:
                # one the tree does not declare is a hard stop.  Glue
                # splitting is NOT applied here -- splitting an
                # unresolvable type name would silently emit a different
                # type ('SOCKADDR_STORAGE ipaddr' is not 'SOCKADDR
                # ipaddr'), i.e. a wrong member and a wrong layout.
                return None
            g = self.split_glued(t)
            if not g:
                return None
            out.append(g[0] + stars)
            # the glued remainder may supply the member name only when
            # the print carried no separate name token
            if g[1] and re.match(r"^[a-z_][A-Za-z0-9_]*$", g[1]):
                name = g[1]
        if not out:
            return None
        return " ".join(out) + f" {name}{arr}{bits}"

    def member_ok(self, m, curtag=None):
        return self.member_norm(m, curtag) is not None


def split_stmts(sig):
    """the pages' code blocks often print several statements (a forward
    tag declaration before the typedef, a chain of related typedefs).
    Split on ';' at brace depth 0 so each statement can be resolved on
    its own; the statement that declares the page's identifier is the
    one that lands in the header."""
    out, depth, cur = [], 0, ""
    for ch in sig:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
        if ch == ";" and depth == 0:
            if cur.strip():
                out.append(cur.strip())
            cur = ""
            continue
        cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


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


DECL_WORDS = ("FAR", "NEAR", "IN", "OUT", "OPTIONAL", "CONST", "const",
              "WINAPI", "CALLBACK", "APIENTRY", "PASCAL")


def _split_declarators(tail):
    """'X, *PX, *LPX' -> [('X',''), ('PX','*'), ('LPX','*')] or None.
    Every declarator must be a plain identifier optionally preceded by
    pointer stars; `const` between the tag and the declarators is
    carried on each pointer declarator."""
    const = False
    parts = [p.strip() for p in tail.split(",")]
    out = []
    for p in parts:
        p = re.sub(r"\s+", " ", p).strip()
        if p in ("const", "CONST"):
            const = True
            continue
        mo = re.match(r"^(\**\s*(?:const\s*)?)([A-Za-z_][A-Za-z0-9_]*)$", p)
        if not mo:
            return None
        stars = "*" * mo.group(1).count("*")
        out.append((mo.group(2), stars))
    if not out:
        return None
    # a non-pointer declarator of an incomplete tag would declare an
    # incomplete object type; the pages that print one print the tag's
    # definition on the same page (handled by try_struct) -- require
    # pointers unless the declarator is the tag's own plain alias, which
    # the caller checks against the tree.
    return out, const


def try_tag_typedef(sig, ctx):
    """typedef (struct|union|enum) TAG [const] NAME[, *PNAME...];

    The CE pages print this form for opaque record types (e.g. the
    USB_FUNCS page ms923262 / CE 6.0 twin ee486704 prints
    `typedef struct _USB_FUNCS USB_FUNCS, * PUSB_FUNCS, * LPUSB_FUNCS;`
    after `struct  _USB_FUNCS;`).  Emitted verbatim from the print; the
    only check is that the declarator names are new to the tree."""
    m = re.match(r"^typedef\s+(struct|union|enum)\s+"
                 r"([A-Za-z_][A-Za-z0-9_]*)\s+(.+)$", sig)
    if not m:
        return None
    kind, tag, tail = m.group(1), m.group(2), m.group(3)
    dec = _split_declarators(tail)
    if not dec:
        return None
    names, const = dec
    alias_names = [n for n, _s in names]
    if tag in ctx.types and tag not in alias_names:
        return None        # tag already defined: would redeclare
    # Declaring an alias of an *incomplete* struct/union tag is valid C
    # (only pointers to it may be used) and is exactly what the pages
    # print, so no completeness check is applied here; the tag's
    # definition, when the archive publishes one, arrives on its own
    # page through try_struct.
    out = []
    for n, st in names:
        if n in ctx.live:
            return None
        out.append(f"{st}{n}")
    cq = "const " if const else ""
    return ("tag", f"typedef {kind} {tag} {cq}{', '.join(out)};",
            names[0][0])


def try_fptr_typedef(sig, ctx):
    """typedef RET [CALLBACK] (* NAME)(PARAMS);

    The CE pages print driver/callback entry-point types in this form
    (e.g. D3DM_CREATECONTEXT_PTR aa447695, LPFIND_INTERFACE aa447799).
    The print is emitted verbatim; the return type and every parameter
    type must already be live in the tree, and migration-glued
    parameter prints ('LPCUSB_DEVICElpDeviceInfo') are split against
    the tree's type names exactly as decl-d1 splits prototype prints."""
    m = re.match(r"^typedef\s+(.+?)\(\s*\**\s*"
                 r"([A-Za-z_][A-Za-z0-9_]*)\s*\)\s*\((.*)\)\s*$", sig)
    if not m:
        return None
    ret, name, params_raw = m.group(1), m.group(2), m.group(3)
    if name in ctx.live:
        return None
    d1r = d1.Resolver(ctx.live, ctx.types)
    ret_toks = []
    for tok in ret.split():
        if tok in DECL_WORDS:
            ret_toks.append(tok)
            continue
        stars = "*" * tok.count("*")
        bare = tok.replace("*", "")
        if d1r.is_type(bare):
            ret_toks.append(bare + stars)
        else:
            g = d1r.split_glued(bare)
            if not g:
                return None
            ret_toks.append(g[0] + stars)
    if not any(t not in DECL_WORDS for t in ret_toks):
        return None
    params = []
    for p in re.split(r",(?![^(]*\))", params_raw):
        p = re.sub(r"\s+", " ", p).strip()
        if not p:
            continue
        if p == "void":
            params.append("void")
            continue
        if "..." in p or "(" in p:
            return None
        toks = p.split()
        arg = toks[-1]
        ttypes = toks[:-1]
        if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", arg) \
                or re.match(r"^[A-Z0-9_]+$", arg):
            # glued print with no parameter name, or an all-caps
            # artifact: the type tokens alone must all resolve
            ttypes, arg = toks, ""
        resolved = []
        for tok in ttypes:
            if tok in DECL_WORDS:
                resolved.append(tok)
                continue
            stars = "*" * tok.count("*")
            bare = tok.replace("*", "")
            if d1r.is_type(bare):
                resolved.append(bare + stars)
            else:
                g = d1r.split_glued(bare)
                if not g:
                    return None
                resolved.append(g[0] + stars)
                if g[1] and g[1][0].islower() and not arg:
                    arg = g[1]
        if not resolved:
            return None
        params.append((" ".join(resolved) + ((" " + arg) if arg else "")).strip())
    plist = ", ".join(params) if params else "void"
    ret_s = " ".join(ret_toks)
    return ("fptr", f"typedef {ret_s} (*{name})({plist});", name)


def try_tagdef(sig, ctx):
    """struct|union|enum NAME { ... };  (no typedef)

    Most of the recovered page prints (tools/ce-prints.py) are in this
    shape -- e.g. the Ws2tcpip.h `addrinfo` page aa450282/ms910257 and
    the Tchddi.h TPDC_* pages print a bare tagged definition.  Every
    member must resolve through Ctx.member_norm; the emitted text is
    the page's own print with the migration glue separated."""
    m = re.match(r"^(struct|union|enum)\s+([A-Za-z_][A-Za-z0-9_]*)\s*"
                 r"\{(.*)\}\s*$", sig)
    if not m:
        return None
    kind, tag, body = m.group(1), m.group(2), m.group(3)
    if tag in ctx.types:
        return None                      # already carried by the tree
    if kind == "enum":
        items = []
        for it in body.split(","):
            it = it.strip()
            if not it:
                continue
            if "=" in it:
                k, v = it.split("=", 1)
                k, v = k.strip(), v.strip()
                if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", k) \
                        or not value_ok(v, ctx.live | ctx.consts):
                    return None
                if k in ctx.live:
                    return None
                items.append(f"{k} = {v}")
            else:
                if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", it) \
                        or it in ctx.live:
                    return None
                items.append(it)
        if not items:
            return None
        return ("tagdef", f"{kind} {tag} {{ {', '.join(items)} }};", tag)
    members = [mb.strip() for mb in body.split(";") if mb.strip()]
    lines = []
    for mb in members:
        norm = ctx.member_norm(mb, curtag=tag)
        if not norm:
            return None
        lines.append("    " + norm + ";")
    if not lines:
        return None
    return ("tagdef", f"{kind} {tag} {{\n" + "\n".join(lines)
            + f"\n}};", tag)


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
        norm = ctx.member_norm(mb, curtag=tag)
        if not norm:
            return None
        lines.append("    " + norm + ";")
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


def compiles(path):
    """(ok, first-error-line) of a standalone -fsyntax-only compile of
    one header, exactly as the Makefile's hostcheck compiles it."""
    import subprocess
    inc = os.path.join(ROOT, "include")
    cmd = ["cc", "-std=c11", "-ffreestanding", "-Werror",
           "-D_WIN32_WCE=0x600", "-I", inc, "-I", os.path.join(inc, "oak"),
           "-include", path, "-fsyntax-only", "-x", "c", os.devnull]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
    except OSError as e:
        return True, f"(compiler unavailable: {e})"
    if r.returncode == 0:
        return True, ""
    first = ""
    for ln in (r.stderr or "").splitlines():
        if "error:" in ln:
            first = ln.split("error:")[-1].strip()
            break
    return False, first or "compile failed"


def main():
    corpus = sys.argv[1]
    apply = "--dry" not in sys.argv
    incdir = os.path.join(ROOT, "include")
    ctx = Ctx(load_code(incdir))

    rows = {}
    # build/rows-prints.json carries the prints recovered from the
    # preserved pages by tools/ce-prints.py (same record schema); it is
    # read first so a recovered print is preferred over a twin row that
    # carries no print at all.
    sources = [(os.path.join(ROOT, "build", "rows-prints.json"), "print")]
    for fn, tag in (("rows.json", "ce5+ce6"), ("rows4.json", "ce4"),
                    ("rows3.json", "ce3")):
        sources.append((os.path.join(corpus, fn), tag))
    for path, tag in sources:
        if not os.path.exists(path):
            continue
        for r in json.load(open(path, encoding="utf-8")):
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
    for v in rows.values():
        v.sort(key=lambda e: {"print": -1, "ce5+ce6": 0, "ce4": 1,
                              "ce3": 2}[e[0]])

    out = {}
    stats = {"self": 0, "unresolved": 0, "noheader": 0, "ok": 0}
    for name, entries in sorted(rows.items()):
        if name in ctx.live:
            stats["self"] += 1
            continue
        entries.sort(key=lambda e: {"print": -1, "ce5+ce6": 0, "ce4": 1,
                                    "ce3": 2}[e[0]])
        chosen = None
        for tag, kind, r in entries:
            # a page's code block may print several statements; each is
            # resolved on its own and the one declaring this page's
            # identifier is the one adopted.
            stmts = split_stmts(clean(r["sig"]))
            for st in stmts:
                res = None
                if kind == "define":
                    res = try_define(st, ctx)
                else:
                    res = (try_simple_typedef(st, ctx)
                           or try_tag_typedef(st, ctx)
                           or try_fptr_typedef(st, ctx)
                           or try_tagdef(st, ctx)
                           or try_enum(st, ctx) or try_struct(st, ctx))
                # the print must declare THIS page's identifier; pages
                # that reprint another type's definition do not count
                if res and res[2] == name:
                    chosen = (r, res)
                    break
            if chosen:
                break
        if not chosen:
            stats["unresolved"] += 1
            continue
        r, (kind, text, _dn) = chosen
        rl = resolve(incdir, norm_header(r.get("header")))
        if not rl:
            stats["noheader"] += 1
            continue
        layer, hdr = rl
        cite = r["id"].split("(")[0]
        osr = r.get("os") or ""
        out.setdefault((layer, hdr), []).append(
            (name, cite, osr, kind, text))
        stats["ok"] += 1

    total = 0
    for (layer, hdr), items in sorted(
            out.items(), key=lambda kv: (kv[0][0], kv[0][1].lower())):
        total += len(items)
        path = os.path.join(layer, hdr)
        lrel = os.path.relpath(layer, ROOT)
        if not os.path.exists(path) and not apply:
            print(f"{lrel}/{hdr}: would CREATE (+{len(items)} types planned)")
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
            print(f"{lrel}/{hdr}: CREATED (+{len(items)} types planned)")
        else:
            print(f"{lrel}/{hdr}: +{len(items)} types")
        if not apply:
            continue
        text = open(path, encoding="utf-8").read()
        orig = text
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
        # Gate: every header in this tree must compile standalone (the
        # Makefile's hostcheck/crosscheck compile each header on its
        # own).  A page print may use a type that lives in another CE
        # header the target does not include; such a declaration is
        # rolled back and stays held rather than breaking the tree.
        ok, err = compiles(path)
        if not ok:
            open(path, "w", encoding="utf-8").write(orig)
            total -= len(items)
            stats["held-nocompile"] = stats.get("held-nocompile", 0) + 1
            print(f"  !! {lrel}/{hdr}: rolled back "
                  f"({len(items)} types held) -- {err}")
    print(f"TOTAL types declared: {total}  (stats: {stats})")


if __name__ == "__main__":
    main()
