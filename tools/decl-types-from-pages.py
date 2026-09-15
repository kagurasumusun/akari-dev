#!/usr/bin/env python3
"""decl-types-from-pages.py -- declare printed typedef/struct/enum/#define
definitions from their official Windows CE pages.

tools/decl-from-pages.py transcribes *function* prototypes.  It reports
"page has no prototype block" for the pages that define a type, which is
most of what the coverage audit's "header not shipped here" bucket holds:
of the 1,217 records in that bucket plus the app-layer gap list, 288 print
a `typedef struct/union/enum`, 85 print a bare tag definition, 22 print a
`#define` and 1 prints a typedef alias.

The archive serves those prints with the space lost between a member type
and its name -- aa456345 prints

    typedef struct __tagDRM_MINIMUM_OUTPUT_PROTECTION_LEVELS{
    DRM_WORDwCompressedDigitalVideo;DRM_WORDwUncompressedDigitalVideo; ... }

so the reconstruction is the same one decl-from-pages.py uses for
parameters: the type is whatever known type prefixes the token, and the
rest is the declarator.  Anything whose type is not already live in the
tree is reported, never guessed, so the tool is meant to be run to a
fixpoint -- each pass's new types unblock the next.

Usage:
    tools/decl-types-from-pages.py --list jobs.json --cache build/pagecache
        [--write --header include/X.h]

`jobs.json` is a list of {"name","page"} (plus any extra keys, which are
carried into the citation comment).
"""
import argparse
import html
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))


def _load(name):
    import importlib.util
    spec = importlib.util.spec_from_file_location(
        name, os.path.join(HERE, name + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


dfp = _load("decl-from-pages")
fetch, cache_path = dfp.fetch, dfp.cache_path
norm_page = dfp.norm_page
PRIMITIVE = dfp.PRIMITIVE

# A member declarator: optional pointer stars, a name, optional [array] and
# optional bit-field width.
DECLARATOR = re.compile(r"^(\**)\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*(?::\s*(\S+))?$")


def prints(raw):
    """Every <pre> block's text, whitespace-normalised."""
    out = []
    for x in re.findall(r"<pre[^>]*>(.*?)</pre>", raw, re.S):
        t = re.sub(r"<[^>]+>", "", x)
        t = html.unescape(t)
        out.append(re.sub(r"\s+", " ", t).strip())
    return out


def split_glued(tok, known):
    """'DRM_WORDwCompressedDigitalVideo' -> ('DRM_WORD', 'wCompressedDigitalVideo').

    Returns (type_text, declarator_text) or None.  A space-separated token
    is returned unchanged; a glued one is split at the longest prefix that
    is a type this tree declares, which is the only non-guessing split
    available (the archive lost the space, not a character).
    """
    tok = tok.strip()
    if not tok:
        return None
    if " " in tok:
        head, rest = tok.rsplit(" ", 1)
        return head.strip(), rest.strip()
    best = None
    for t in known:
        if len(t) >= 2 and tok.startswith(t) and len(tok) > len(t):
            rest = tok[len(t):]
            # the remainder must be a declarator: an identifier that does
            # not start with a digit.  The longest known type wins, so
            # LONGLONG is not split into LONG + LONG when both are known.
            # No case rule here -- CE prints members whose names start with
            # an upper-case letter (aa450429 prints DWORDByteLength), and a
            # case heuristic silently dropped those members.
            if re.match(r"^[A-Za-z_]\w*$", rest):
                if best is None or len(t) > len(best):
                    best = t
    if best is None:
        return None
    return best, tok[len(best):]


def render_members(body, known):
    """Transcribe a struct/union body.  Returns (text, [unknown types])."""
    out, unknown = [], []
    for raw in body.split(";"):
        raw = raw.strip()
        if not raw:
            continue
        # a nested anonymous struct/enum is not something this tool invents
        if "{" in raw or "}" in raw:
            return None, ["nested definition"]
        parts = split_glued(raw, known)
        if parts is None:
            unknown.append(raw)
            continue
        ttext, decl = parts
        m = DECLARATOR.match(decl)
        if not m:
            unknown.append(raw)
            continue
        stars, name, arr, bits = m.group(1), m.group(2), m.group(3) or "", m.group(4)
        # the type may itself be 'const X' or carry its own stars
        const = ""
        cm = re.match(r"^(?:const|CONST)\s+(.*)$", ttext)
        if cm:
            const, ttext = "const ", cm.group(1).strip()
        tstars = ""
        while ttext.endswith("*"):
            tstars += "*"
            ttext = ttext[:-1].strip()
        base = ttext
        if base not in known and base not in PRIMITIVE:
            unknown.append(base)
            continue
        if bits is not None and not re.match(r"^\d+$", bits):
            unknown.append("bit-field width " + bits)
            continue
        if arr:
            inner = arr[1:-1].strip()
            if not re.match(r"^\d+$", inner) and inner not in known:
                unknown.append("array size " + inner)
                continue
        line = "%s%s %s%s%s%s" % (const, base, tstars + stars, name, arr,
                                  (":" + bits) if bits else "")
        out.append("    " + re.sub(r"\s+", " ", line).strip() + ";")
    if unknown or not out:
        return None, unknown
    return "\n".join(out), []


def insertion_point(L, ends):
    """The line a new declaration goes before, innermost region first.

    Precedence is the generation gate, then the `__cplusplus` region, then
    the include guard.  A header that keeps its declarations inside
    `#ifdef __cplusplus` (include/Scrollview.hpp and the other CE .NET view
    headers) got its new block after `#endif /* __cplusplus */`, so
    ScrollBarInfoInternal landed where the enum SCROLL_STATE at line 35 was
    no longer in scope.  The generation gate outranks both: a block inserted
    after the gate's #endif compiles with the gated includes switched off,
    which is how Cs.h lost ULONG and GUID.
    """
    if not ends:
        return len(L) - 1
    gated = [i for i in ends if "_WIN32_WCE" in L[i]]
    if gated:
        return max(gated)
    cxx = [i for i in ends if "__cplusplus" in L[i]]
    return max(cxx or ends)


_MACROS = None


def known_macros():
    """Every #define name this tree already ships."""
    global _MACROS
    if _MACROS is None:
        _MACROS = set()
        for d in ("include", "include/oak"):
            if not os.path.isdir(d):
                continue
            for f in sorted(os.listdir(d)):
                if not f.endswith((".h", ".hpp", ".hxx")):
                    continue
                t = open(os.path.join(d, f), encoding="utf-8",
                         errors="replace").read()
                t = re.sub(r"(?s)/\*.*?\*/", " ", t)
                _MACROS |= set(re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)", t, re.M))
    return _MACROS


def enumerators(body, known):
    out, unknown = [], []
    depth = 0
    cur = ""
    for ch in body:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    lines = []
    for e in out:
        e = e.strip()
        if not e:
            continue
        if "=" in e:
            nm, val = e.split("=", 1)
            nm, val = nm.strip(), val.strip()
            for tok in identifiers(val):
                if tok not in known and tok not in PRIMITIVE:
                    unknown.append(tok)
            lines.append("    %s = %s," % (nm, val))
        else:
            if not re.match(r"^[A-Za-z_]\w*$", e):
                unknown.append(e)
                continue
            lines.append("    %s," % e)
    if unknown or not lines:
        return None, unknown
    if lines[-1].endswith(","):
        lines[-1] = lines[-1][:-1]
    return "\n".join(lines), []


def identifiers(expr):
    """The identifiers an expression depends on.

    String and character literals and numeric literals are removed first:
    the archive prints `L"string"` and `0x0001`, and a bare identifier scan
    reads those as a type named `L` and one named `x0001`, which is how
    eleven correct definitions were reported as blocked on an undeclared
    type.
    """
    e = re.sub(r'"(?:[^"\\]|\\.)*"', '""', expr)
    e = re.sub(r"'(?:[^'\\]|\\.)*'", "''", e)
    e = re.sub(r"\b(?:0[xX][0-9A-Fa-f]+|0[0-7]*|[0-9]+)[uUlL]*\b", "0", e)
    e = re.sub(r"\bL(?=\")", "", e)
    return re.findall(r"[A-Za-z_]\w*", e)


def build(job, raw, known):
    """Return (declaration, note) or (None, reason)."""
    name = job["name"]
    if not re.match(r"^[A-Za-z_]\w*$", name):
        return None, "not an identifier"
    cands = prints(raw)
    if not cands:
        return None, "page has no <pre> block"
    esc = re.escape(name)

    # typedef struct/union [tag] { ... } NAME [, *PNAME]...;
    for t in cands:
        m = re.match(r"^typedef\s+(struct|union)\s+([A-Za-z_]\w*)?\s*\{(.*?)\}\s*"
                     r"([^;]*\b" + esc + r"\b[^;]*);$", t, re.S)
        if not m:
            continue
        kind, tag, body, names = m.group(1), m.group(2), m.group(3), m.group(4)
        text, unk = render_members(body, known)
        if text is None:
            return None, "member type not declared here: %s" % ", ".join(sorted(set(unk))[:4])
        tail = ", ".join(n.strip() for n in names.split(","))
        if name not in [x.strip().lstrip("*") for x in names.split(",")]:
            continue
        # `typedef` is part of the definition: the print is
        # `typedef struct { ... } DEVDETAIL, *PDEVDETAIL;` and without the
        # keyword the emitted text declares two *variables* called DEVDETAIL
        # and PDEVDETAIL instead of a type, which is silently accepted by a
        # syntax-only check and only fails where the type is used.
        head = "typedef %s%s" % (kind, " " + tag if tag else "")
        return ("%s {\n%s\n} %s;" % (head, text, tail), t)

    # typedef enum [tag] { ... } NAME...;
    for t in cands:
        m = re.match(r"^typedef\s+enum\s+([A-Za-z_]\w*)?\s*\{(.*?)\}\s*"
                     r"([^;]*\b" + esc + r"\b[^;]*);$", t, re.S)
        if not m:
            continue
        tag, body, names = m.group(1), m.group(2), m.group(3)
        text, unk = enumerators(body, known)
        if text is None:
            return None, "enumerator value not declared here: %s" % ", ".join(sorted(set(unk))[:4])
        tail = ", ".join(n.strip() for n in names.split(","))
        return ("typedef enum%s {\n%s\n} %s;" % (" " + tag if tag else "", text, tail), t)

    # typedef <type> NAME [, *PNAME]...;   (alias)
    for t in cands:
        m = re.match(r"^typedef\s+([^;{}()]*?\b" + esc + r"\b[^;{}()]*);$", t, re.S)
        if not m:
            continue
        body = m.group(1)
        parts = split_glued(body if " " not in body else body, known)
        decls = [d.strip() for d in body.split(",")]
        head = None
        rendered = []
        for d in decls:
            p = split_glued(d, known)
            if p is None:
                return None, "cannot split typedef declarator \"%s\"" % d
            tt, dd = p
            if head is None:
                head = tt
            elif tt != head and dd != name:
                pass
            m2 = DECLARATOR.match(dd)
            if not m2:
                return None, "cannot read typedef declarator \"%s\"" % dd
            base = tt
            if base not in known and base not in PRIMITIVE:
                return None, 'type "%s" is not declared by this tree' % base
            rendered.append("%s%s" % (m2.group(1), m2.group(2)))
        if head is None or not rendered:
            continue
        if name not in [r.lstrip("*") for r in rendered]:
            continue
        return ("typedef %s %s;" % (head, ", ".join(rendered)), t)

    # #define NAME value
    for t in cands:
        m = re.match(r"^#define\s+" + esc + r"\s+(.*)$", t)
        if not m:
            continue
        val = m.group(1).strip()
        for tok in identifiers(val):
            if tok not in known and tok not in PRIMITIVE:
                return None, 'value uses "%s", which this tree does not declare' % tok
        return ("#define %s %s" % (name, val), t)

    # struct/union/enum NAME { ... };   (bare tag definition)
    for t in cands:
        m = re.match(r"^(struct|union|enum)\s+" + esc + r"\s*\{(.*?)\};$", t, re.S)
        if not m:
            continue
        kind, body = m.group(1), m.group(2)
        if kind == "enum":
            text, unk = enumerators(body, known)
            if text is None:
                return None, "enumerator value not declared here: %s" % ", ".join(sorted(set(unk))[:4])
            # An enumerator cannot share a name with a macro the tree already
            # ships: `#define olNormal 0` (Pimstore.h, transcribed from
            # aa513746) turns `olNormal = 0,` inside `enum OlSensitivity`
            # (ee483685) into `0 = 0,`, which is a syntax error.  The same
            # constants reach this tree in two official spellings -- aa513746
            # prints a macro table and the CE 6.0 pages print enums -- so the
            # spelling already shipped wins and the enum is held, recorded
            # with both page IDs in docs/coverage-blocked.tsv.
            clash = sorted({re.sub(r"\s*=.*$", "", e).strip() for e in body.split(",")}
                           & known_macros())
            if clash:
                return None, ("enumerator%s %s already defined as a macro in "
                              "this tree" % ("" if len(clash) == 1 else "s",
                                             ", ".join(clash[:4])))
        else:
            text, unk = render_members(body, known)
            if text is None:
                return None, "member type not declared here: %s" % ", ".join(sorted(set(unk))[:4])
        if kind == "enum":
            # A bare `enum X { ... };` declares only a tag, so `X` cannot be
            # used as a type -- yet the pages that consume these enums do
            # exactly that: ee497177 prints
            # `typedef struct linecallparamsdevspecific_tag {
            #   CALLER_ID_OPTIONS cidoOptions; }` for the enum ee497030
            # defines as `enum CALLER_ID_OPTIONS { ... };`.  Declaring the tag
            # and a typedef of the same name is what makes the documented use
            # compile, and invents nothing: both spellings are the pages'.
            return ("typedef enum %s {\n%s\n} %s;" % (name, text, name), t)
        return ("%s %s {\n%s\n};" % (kind, name, text), t)

    return None, "no printed definition of this name on the page"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--list", required=True)
    ap.add_argument("--cache", default="build/pagecache")
    ap.add_argument("--include", action="append", default=["include", "include/oak"])
    ap.add_argument("--header")
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()

    jobs = json.load(open(a.list, encoding="utf-8"))
    known = dfp.known_types(a.include)
    declared = dfp.declared_in_tree(a.include)
    emitted = set()
    ok, bad, err = [], [], []
    for job in jobs:
        # Two pages can print one typedef: ee483400 (CSDATAFORMAT) and
        # ee484862 (CSDATARANGE) both print
        # `} CSDATAFORMAT, *PCSDATAFORMAT, CSDATARANGE, *PCSDATARANGE;`.
        # Transcribing both writes the same definition twice, so a name an
        # earlier job in this run already emitted is skipped.
        if job["name"] in declared:
            bad.append((job["name"], norm_page(job["page"]) or job["page"],
                        "already declared in " + declared[job["name"]]))
            continue
        if job["name"] in emitted:
            bad.append((job["name"], norm_page(job["page"]) or job["page"],
                        "already emitted by another page's print of the same typedef"))
            continue
        page = norm_page(job["page"])
        if not page:
            err.append((job["name"], "unparseable page id " + job["page"]))
            continue
        try:
            raw = fetch(page, a.cache)
        except Exception as e:                                     # noqa: BLE001
            err.append((job["name"], "fetch failed: %s" % e))
            continue
        decl, why = build(job, raw, known)
        if decl is None:
            bad.append((job["name"], page, why))
        else:
            ok.append((job["name"], page, why, decl, job.get("os"), job.get("lib")))
            # a definition makes its own names known to later jobs in this run
            for n in re.findall(r"[A-Za-z_]\w*", decl):
                known.add(n)
                emitted.add(n)

    for n, p, pr, d, osv, lib in ok:
        print("DECLARE %-32s %s" % (n, d.splitlines()[0][:70]))
    for n, p, why in bad:
        print("SKIP    %-32s %s" % (n, why))
    for n, why in err:
        print("ERROR   %-32s %s" % (n, why))
    print("\n%d declared, %d skipped, %d errors" % (len(ok), len(bad), len(err)))

    if a.write and ok:
        if not a.header:
            sys.exit("--write needs --header")
        L = open(a.header, encoding="utf-8").read().split("\n")
        ends = [i for i, l in enumerate(L) if l.startswith("#endif")]
        # M135: a whole-file generation gate ends with
        # `#endif /* _WIN32_WCE >= 0xNNNN */` BEFORE the include guard's own
        # #endif.  Inserting before the last #endif put new declarations
        # outside the gate, so at a lower generation they compiled with the
        # gated includes switched off -- Cs.h lost ULONG and GUID.  Prefer
        # the gate when the file has one.
        ei = insertion_point(L, ends)
        blk = [""]
        for n, pg, pr, d, osv, lib in ok:
            blk.append("/* %s %s: page print" % (pg.split("(")[0], n))
            blk.append(" * %s" % pr[:150])
            blk.append(" * (%s%s) */" % (osv or "generation not stated",
                                          "; Link Library: " + lib if lib else ""))
            blk.extend(d.split("\n"))
            blk.append("")
        L[ei:ei] = blk
        open(a.header, "w", encoding="utf-8").write("\n".join(L))
        print("inserted %d definitions into %s" % (len(ok), a.header))


if __name__ == "__main__":
    main()
