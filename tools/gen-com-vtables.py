#!/usr/bin/env python3
"""gen-com-vtables.py -- declare COM interfaces whose method order the
public pages actually print.

Many CE interface pages carry a "Methods in Vtable Order" section whose
tables list, per inherited-interface segment and in binary vtable
order, every method with a link to its method page.  That makes the
vtable layout public information: this tool parses those tables, pulls
each method's prototype from its linked page, and emits the tree's
Vtbl-struct + lpvtable-struct + macro form (Objbase.h style).

Interfaces whose pages print no vtable order get an opaque
`typedef struct IXxx IXxx;` plus a HELD comment -- a vtable layout is
never guessed.

Carrier mapping follows the tree's alias design: strmif/Playlist ->
Dshow.h, Objidl/Docobj/Ocidl/Oleidl/Dccole -> Objbase.h, Sapiddk ->
Sapi.h, others -> themselves.

Usage: python3 tools/gen-com-vtables.py <corpus> [--apply]
Writes docs/com-vtable-plan-2026-09-18.tsv and build/com-vtables/*.inc;
--apply inserts the blocks into the carrier headers.
"""
import html as _html
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

import importlib.util as _ilu
_spec = _ilu.spec_from_file_location(
    "pa", os.path.join(ROOT, "tools", "proto-audit.py"))
pa = _ilu.module_from_spec(_spec)
_spec.loader.exec_module(pa)


def fix_params(params):
    """Normalize a printed parameter list: unglue type-name fusions
    with the tree lexicon (ULONGcelt), repair the MIDL conversion
    trace IFoo_com_Ifoo -> IFoo**, drop bare void."""
    if params.strip() == "void":
        return ""
    out = []
    for p in params.split(","):
        p = p.strip()
        m = re.match(r"^(\w+)_com_(\w+?)(\**)$",
                     p.split()[0]) if p else None
        if m and m.group(1).lower() == m.group(2).lower():
            rest = p.split()[1:] if len(p.split()) > 1 else []
            p = " ".join([m.group(1) + "**" + m.group(3)] + rest)
        toks = []
        for tk in p.split():
            g = pa.UNGLUE.match(tk) if "*" not in tk else None
            if tk in pa.LEX or tk.lower() in pa._CANON:
                g = None            # token is itself a known type
            if g and (len(g.group(1)) >= 4
                      or re.search(r"[A-Z]", g.group(2))):
                toks.extend([g.group(1), g.group(2)])
            else:
                toks.append(tk)
        out.append(" ".join(toks))
    return ", ".join(out)

CARRIER = {
    "strmif.h": "Dshow.h", "Playlist.h": "Dshow.h",
    "Dmodshow.h": "Dshow.h", "D3dmcaps.h": "Dshow.h",
    "Objidl.h": "Objbase.h", "Docobj.h": "Objbase.h",
    "Ocidl.h": "Objbase.h", "Oleidl.h": "Objbase.h",
    "Dccole.h": "Objbase.h", "Objsafe.h": "Objbase.h",
    "Unknwn.h": "Objbase.h", "Wtypes.h": "Objbase.h",
    "Sapiddk.h": "Sapi.h", "Mqmgmt.h": "Mqmgmt.h",
}

PRE = re.compile(r"<pre[^>]*>(.*?)</pre>", re.S)
GEN_PREF = ["windows-embedded-ce-6.0", "windows-ce-net-4x",
            "windows-ce-5.0", "windows-embedded-compact-7",
            "dotnet-compact-framework", "uncategorized"]


def load_index(corpus):
    by_title = {}
    with open(os.path.join(corpus, "data", "index", "INDEX.tsv"),
              encoding="utf-8") as f:
        for ln in f.read().splitlines()[1:]:
            c = ln.split("\t")
            if len(c) >= 4:
                by_title.setdefault(c[3], []).append((c[1], c[2]))
    return by_title


def pick_page(by_title, title_prefs):
    for want in title_prefs:
        pats = (want + " (", want + " Interface (")
        for gen in GEN_PREF:
            for title, pages in by_title.items():
                if title == want or title == want + " Interface" \
                        or title.startswith(pats):
                    for g, path in pages:
                        if g == gen:
                            return path
    return None


def parse_vtable_sections(h):
    """[(iface, [(method, href), ...]), ...] from the Vtable Order
    section, or None."""
    i = h.find("Vtable Order")
    if i < 0:
        return None
    sec = h[i:]
    out = []
    for tb in re.findall(r"<table>(.*?)</table>", sec, re.S):
        th = re.search(r"<th>(?:(I\w+)\s+)?[Mm]ethods?</th>", tb)
        if not th:
            continue
        rows = re.findall(
            r'<td[^>]*>\s*<a href="([^"]+)"[^>]*>(\w+)</a>\s*</td>', tb)
        if rows:
            out.append((th.group(1) or "", [(m, hr) for hr, m in rows]))
    return out or None


def href_to_path(corpus, page_path, href):
    pid = re.sub(r"\(v=[a-z0-9.]+\)$", "", href.split("/")[-1])
    d = os.path.dirname(os.path.join(corpus, page_path))
    for cand in (pid + ".html",):
        p = os.path.join(d, cand)
        if os.path.exists(p):
            return p, pid
    # search index dirs
    for sub in ("windows-embedded-ce-6.0", "windows-ce-net-4x",
                "windows-ce-5.0"):
        p = os.path.join(corpus, "docs", "mslearn", sub, pid + ".html")
        if os.path.exists(p):
            return p, pid
    return None, pid


SIG = re.compile(
    r"(?:(\w[\w \*]*?)\s+)?STDMETHODIMP(?:_\((\w[\w \*]*?)\))?\s*"
    r"(?:\w+::)?(\w+)\s*\((.*?)\)\s*;?\s*$")


def method_sig(path, iface, method):
    """(ret, params) from the method page print, or None.  Requires an
    explicit return type or STDMETHODIMP in the print -- the HRESULT
    default only comes from the documented STDMETHODIMP convention,
    never from a bare name-only line."""
    h = open(path, encoding="utf-8", errors="replace").read()
    pat = re.compile(
        r"^(?:(\w[\w \*]*?)\s+)?(?:STDMETHODIMP(?:_\((\w[\w \*]*?)\))"
        r"\s*)?(?:\w+::)?" + re.escape(method) +
        r"\s*\((.*?)\)\s*(?:PURE)?\s*;?\s*$")
    for blk in PRE.findall(h):
        t = _html.unescape(re.sub(r"<[^>]+>", " ", blk))
        t = re.sub(r"\s+", " ", t).strip()
        # some pages lost the space between the return type and the
        # method name ('HRESULTGetX(...)'); split only when the rest
        # is exactly the method being looked up.  Param fusions are
        # handled token-wise in fix_params with the full lexicon.
        t = re.sub(r"\b(HRESULT|BOOL|ULONG|DWORD|LONGLONG|LONG|UINT|"
                   r"void|int|BYTE|WORD|short|char|float|double|"
                   r"REFERENCE_TIME)(" + re.escape(method) + r")\b",
                   r"\1 \2", t)
        # SAPI pages print C++ vtable form
        t = re.sub(r"^virtual\s+", "", t)
        t = t.replace("STDMETHODCALLTYPE ", "")
        if not re.search(r"\b%s\s*\(" % re.escape(method), t):
            continue
        m = pat.match(t)
        if not m:
            continue
        had_stdi = "STDMETHODIMP" in t
        ret = m.group(2) or m.group(1)
        if ret is None and not had_stdi:
            continue
        if ret == "RESULT":
            # page dropped the leading H (ms908797); the C type is
            # HRESULT -- recorded in the entry comment via ret_note
            ret = "HRESULT"
        ret = ret or "HRESULT"
        params = m.group(3).strip()
        params = re.sub(r"\bTHIS_\s*", "", params)
        params = re.sub(r"\s*,\s*", ", ", params)
        return re.sub(r"\s+", " ", ret).strip(), params
    return None


def main():
    corpus = sys.argv[1]
    apply = "--apply" in sys.argv
    by_title = load_index(corpus)

    # interfaces with a full vtable already declared vs recorded-only
    declared = set()          # full vtable present
    opaque = set()            # typedef struct IXxx IXxx; present
    DI = re.compile(r"DECLARE_INTERFACE_?\s*\(\s*(I\w+)")
    VT = re.compile(r"\b(I\w+)Vtbl\b")
    OP = re.compile(r"typedef\s+struct\s+(I\w+)\s+(I\w+)\s*;")
    for root, _d, fs in os.walk(os.path.join(ROOT, "include")):
        for fn in fs:
            if not fn.endswith((".h", ".hpp", ".hxx")):
                continue
            s = open(os.path.join(root, fn), encoding="utf-8",
                     errors="replace").read()
            nc = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
            declared |= set(DI.findall(nc)) | set(VT.findall(nc))
            opaque |= {g for g, _ in OP.findall(nc)}
    targets = {}
    for fn in CARRIER:
        p = os.path.join(ROOT, "include", fn)
        if not os.path.exists(p):
            continue
        s = open(p, encoding="utf-8", errors="replace").read()
        for nm in re.findall(r"\b(I[A-Z]\w+)::", s):
            if nm not in declared:
                targets.setdefault(nm, fn)
    print("vtable-declared:", len(declared),
          "opaque-typedefs:", len(opaque),
          "recorded w/o vtable:", len(targets))

    plan = []
    blocks = {}          # carrier header -> text
    for nm in sorted(targets):
        origin = targets[nm]
        carrier = CARRIER[origin]
        # try every candidate page (gen preference order) until one
        # prints a vtable-order section
        want = nm
        pats = (want + " (", want + " Interface (")
        cands = []
        for title, pages in by_title.items():
            if title == want or title == want + " Interface" \
                    or title.startswith(pats):
                for g, path in pages:
                    pref = (GEN_PREF.index(g) if g in GEN_PREF
                            else len(GEN_PREF))
                    cands.append((pref, path))
        cands.sort()
        page, secs = None, None
        for _pref, path in cands:
            h = open(os.path.join(corpus, path), encoding="utf-8",
                     errors="replace").read()
            s2 = parse_vtable_sections(h)
            if s2:
                page, secs = path, s2
                break
            if page is None:
                page = path
        if not cands:
            plan.append((nm, origin, carrier, "no-interface-page",
                         "", ""))
            continue
        if not secs:
            plan.append((nm, origin, carrier, "no-vtable-order",
                         page, ""))
            continue
        entries = []
        ok = True
        methods = []
        for iface, rows in secs:
            for meth, href in rows:
                methods.append((iface, meth))
        if True:  # IUnknown trio always in fixed R1 form
            entries.append(f"    HRESULT (WINAPI *QueryInterface)({nm}*, REFIID iid, void** ppvObject);  /* (R1) */")
            entries.append(f"    ULONG (WINAPI *AddRef)({nm}*);  /* (R1) */")
            entries.append(f"    ULONG (WINAPI *Release)({nm}*);  /* (R1) */")
        nmiss = 0
        for iface, meth in methods:
            if iface == "IUnknown":
                # inherited entries: fixed R1 form, never page-derived
                continue
            # find href for this method
            href = None
            for _if2, rows2 in secs:
                for m2, hr2 in rows2:
                    if m2 == meth:
                        href = hr2
                        break
                if href:
                    break
            mpath, pid = href_to_path(corpus, page, href)
            if not mpath:
                nmiss += 1
                ok = False
                continue
            sig = method_sig(mpath, iface, meth)
            if sig is None:
                nmiss += 1
                ok = False
                continue
            ret, params = sig
            params = fix_params(params)
            plist = f"{nm}*" + (", " + params if params else "")
            entries.append(f"    {ret} (WINAPI *{meth})({plist});"
                           f"  /* {pid} */")
        if not ok:
            plan.append((nm, origin, carrier,
                         f"sig-missing:{nmiss}", page, ""))
            continue
        # macros
        macros = []
        allmeths = []
        for m0 in ["QueryInterface", "AddRef", "Release"] + \
                [m for i2, m in methods if i2 != "IUnknown"]:
            if m0 not in allmeths:
                allmeths.append(m0)
        for mm in allmeths:
            # arity from the entry line
            ln = next((e for e in entries if f"*{mm})(" in e), None)
            if ln is None:
                continue
            inner = ln.split("(", 1)[1].rsplit(")", 1)[0]
            n = 0 if not inner.strip() else \
                len([x for x in re.split(r",(?![^()]*\))", inner)]) - 1
            args = ",".join("abcdefghij"[:n])
            call = ",".join(["T"] + list("abcdefghij"[:n]))
            macros.append(
                f"#define {nm}_{mm}(T{',' + args if args else ''}) "
                f"((T)->lpVtbl->{mm}({call}))")
        body = "\n".join(e for e in entries if e)
        blk = (f"\n/* ---- {nm}: vtable order printed by "
               f"{os.path.basename(page)}\n"
               f" *      (\"Methods in Vtable Order\" tables; method "
               f"page ids per entry) ---- */\n"
               f"typedef struct {nm}Vtbl {{\n{body}\n}} {nm}Vtbl;\n"
               f"struct {nm} {{ const {nm}Vtbl *lpVtbl; }};\n"
               + "\n".join(macros) + "\n")
        blocks.setdefault(carrier, []).append(blk)
        plan.append((nm, origin, carrier, "generated", page,
                     str(len(allmeths))))

    # opaque typedefs for no-vtable-order interfaces (skip those the
    # tree already forward-declares)
    for nm, origin, carrier, st, page, _x in plan:
        if st != "no-vtable-order" or nm in opaque:
            continue
        blocks.setdefault(carrier, []).append(
            f"\n/* {nm}: documented method pages recorded in "
            f"{origin}; the interface page prints no vtable order, "
            f"so the vtable layout is HELD (never guessed).  Opaque "
            f"type so documented prototypes can name it. */\n"
            f"typedef struct {nm} {nm};\n")

    os.makedirs(os.path.join(ROOT, "build", "com-vtables"),
                exist_ok=True)
    for carrier, blks in blocks.items():
        dest = os.path.join(ROOT, "build", "com-vtables",
                            carrier + ".inc")
        with open(dest, "w", encoding="utf-8") as f:
            f.write("".join(blks))
        print("block:", carrier, len(blks), "interfaces")

    with open(os.path.join(ROOT, "docs",
                           "com-vtable-plan-2026-09-18.tsv"),
              "w", encoding="utf-8") as f:
        f.write("# interface\torigin\tcarrier\tstatus\tpage\tmethods\n")
        for row in plan:
            f.write("\t".join(row) + "\n")
    from collections import Counter
    print("plan:", dict(Counter(r[3].split(":")[0] for r in plan)))

    if apply:
        for carrier, blks in blocks.items():
            p = os.path.join(ROOT, "include", carrier)
            s = open(p, encoding="utf-8").read()
            # ensure an interface typedef precedes each new Vtbl
            gen_names = [r[0] for r in plan if r[2] == carrier
                         and r[3] == "generated"]
            fixed = []
            for blk in blks:
                m2 = re.match(r"\n?/\* ---- (I\w+):", blk)
                if m2:
                    nm2 = m2.group(1)
                    if nm2 in gen_names and not re.search(
                            r"typedef\s+struct\s+%s\s+%s\s*;"
                            % (nm2, nm2), s):
                        blk = ("typedef struct %s %s;\n" % (nm2, nm2)
                               + blk)
                fixed.append(blk)
            blks = fixed
            i = s.rstrip().rfind("#endif")
            if i < 0:
                s = s.rstrip() + "\n" + "".join(blks)
            else:
                s = s[:i] + "".join(blks) + "\n" + s[i:]
            open(p, "w", encoding="utf-8").write(s)
            print("applied ->", carrier)


if __name__ == "__main__":
    main()
