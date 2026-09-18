#!/usr/bin/env python3
"""
surface-audit.py -- honest coverage audit for the Akari API tree.

Classifies every documented API name into DECLARED (live code in
include/), COMMENT-ONLY (mentioned only inside comments, e.g. held
records) or ABSENT, cross-references the committed doc defs and the
device-dump-audited coredll export surface of the sysroot (corpus
coredll/*.def, clean-room.md section 3 tier 2), and writes:

    docs/surface-audit.tsv   name, trees, decl, doc_def, surface
    docs/surface-audit.md    summary counts + the three defect lists

No content of any third-party tree is read; the export-surface names
are the observable-fact tier allowed by docs/clean-room.md.

Usage:  python3 tools/surface-audit.py <corpus-dir>
"""

import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDENT = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]{2,}\b")


# Two physical layers, one C namespace for a CE compile (the Makefile
# compiles with -I include -I include/oak):
#
#   include/       application -dev layer (what a user-mode CE program
#                  includes)
#   include/oak/   OAK/DDK/driver layer (OEM-BSP scope, kept in the
#                  tree but outside the application -dev set)
#
# The audit therefore measures BOTH: a name declared in include/oak/ is
# carried (it compiles), but it is not part of the application layer,
# and the two counts are reported separately so the -dev set can never
# be claimed complete on the strength of an OAK declaration.
LAYERS = (("app", "include"), ("oak", "include/oak"))


def load_headers(incdir=None):
    """returns (live_all, whole_all, live_by_layer, whole_by_layer)."""
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    live, whole = set(), set()
    live_l, whole_l = {}, {}
    for tag, rel in LAYERS:
        d = os.path.join(root, rel)
        ll, ww = set(), set()
        if os.path.isdir(d):
            for fn in sorted(os.listdir(d)):
                if not fn.endswith((".h", ".hxx", ".hpp")):
                    continue
                text = open(os.path.join(d, fn), encoding="utf-8",
                            errors="replace").read()
                ww.update(IDENT.findall(text))
                code = re.sub(r"(?s)/\*.*?\*/", " ", text)
                code = re.sub(r"//[^\n]*", " ", code)
                ll.update(IDENT.findall(code))
        live_l[tag], whole_l[tag] = ll, ww
        live |= ll
        whole |= ww
    return live, whole, live_l, whole_l


def strip_comments(text):
    text = re.sub(r"(?s)/\*.*?\*/", "\n", text)
    return re.sub(r"//[^\n]*", "\n", text)


def def_names(path):
    names = set()
    exports = False
    for ln in open(path, encoding="utf-8", errors="replace"):
        s = ln.strip()
        if s.upper() == "EXPORTS":
            exports = True
            continue
        if not exports or not s or s.startswith((";", "#")):
            continue
        names.add(s.split()[0])
    return names


def surface_names(corpus):
    out = {}
    for fn, tag in (("coredll4.def", "ce4"), ("coredll.def", "ce5"),
                    ("coredll6.def", "ce6"), ("coredll6-x86.def", "ce6-x86")):
        p = os.path.join(corpus, "coredll", fn)
        if os.path.exists(p):
            out[tag] = def_names(p)
    return out


def api_like(title):
    return bool(re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", title.strip()))


def main():
    corpus = sys.argv[1] if len(sys.argv) > 1 else os.path.join(
        os.path.dirname(ROOT), "wince-docs-corpus")
    live, whole, live_l, whole_l = load_headers()

    # documented rows from every harvested official tree
    rows = {}
    if not any(os.path.exists(os.path.join(corpus, f)) for f in
               ("rows.json", "rows4.json", "rows3.json")):
        # reorganized corpus: derive documented names from the page
        # index titles ("CeGetDeviceId Function (Ceutil.h)", "NAME
        # (Windows CE 5.0)"); single capitalized English words
        # (Error/Warning/Method...) are prose pages, not APIs
        BOOKTAG = {"windows-ce-5.0": "ce5", "windows-embedded-ce-6.0":
                   "ce6", "chm-windows-ce-3.0": "ce3",
                   "windows-ce-net-4x": "ce4",
                   "windows-embedded-compact-7": "ce7",
                   "wayback-msdn-2010": "wayback"}
        idx = os.path.join(corpus, "data", "index", "INDEX.tsv")
        titlere = re.compile(
            r"^([A-Za-z_]\w+)\s*(?:\((?:Windows|RAPI)\b|\b(?:Function|"
            r"Structure|Enumeration|Macro|Constant|Notification|Message)\b)")
        for ln in open(idx, encoding="utf-8", errors="replace"):
            f = ln.rstrip("\n").split("\t")
            if len(f) < 4 or f[0].startswith("#"):
                continue
            tag = BOOKTAG.get(f[1])
            if not tag:
                continue
            m = titlere.match(f[3].strip())
            if not m:
                continue
            nm = m.group(1)
            if re.fullmatch(r"[A-Z][a-z]+", nm):
                continue
            e = rows.setdefault(nm, {"trees": set(), "lib": "",
                                     "sig": False, "os": "",
                                     "hdr": set()})
            e["trees"].add(tag)
    for fn, tag in (("rows.json", "ce5+ce6"), ("rows4.json", "ce4"),
                    ("rows3.json", "ce3")):
        p = os.path.join(corpus, fn)
        if not os.path.exists(p):
            continue
        for r in json.load(open(p, encoding="utf-8")):
            t = r.get("title", "").strip()
            if not api_like(t):
                continue
            e = rows.setdefault(t, {"trees": set(), "lib": "",
                                    "sig": False, "os": "",
                                    "hdr": set()})
            e["trees"].add(tag)
            h = (r.get("header") or "").strip().rstrip(".").strip()
            if h.startswith("Include:"):
                h = h[8:].strip()
            for tok in re.split(r"[,;]", h):
                tok = tok.strip().split()[0] if tok.strip() else ""
                if re.match(r"^[A-Za-z0-9_]+\.(h|hxx|hpp)$", tok):
                    e["hdr"].add(tok)
            if r.get("sig"):
                e["sig"] = True
            if r.get("lib"):
                e["lib"] = (e["lib"] + "; " + r["lib"]).strip("; ")
            if r.get("os"):
                e["os"] = r["os"]

    docdef = def_names(os.path.join(ROOT, "def", "coredll-doc.def"))
    surf = surface_names(corpus)
    s_all = set()
    for v in surf.values():
        s_all |= v
    unmangled = {n for n in s_all if not n.startswith(("?", "_?", "@"))}

    # all def/*-doc.def combined
    alldoc = set()
    dd = os.path.join(ROOT, "def")
    for fn in os.listdir(dd):
        if fn.endswith("-doc.def"):
            alldoc |= def_names(os.path.join(dd, fn))

    def in_set(name, s):
        # the CE export spelling is the W form for string-taking APIs;
        # the doc pages title the plain (macro) name.
        return name in s or (name + "W") in s

    # which layer carries a header token, so the -dev (application)
    # layer can be measured on its own
    hdr_layer = {}
    root = ROOT
    for tag, rel in LAYERS:
        d = os.path.join(root, rel)
        if os.path.isdir(d):
            for fn in os.listdir(d):
                hdr_layer.setdefault(fn.lower(), tag)

    recs = []
    for name, e in sorted(rows.items(), key=lambda kv: kv[0].lower()):
        if name in live_l["app"]:
            decl, layer = "declared", "app"
        elif name in live_l["oak"]:
            decl, layer = "declared", "oak"
        elif name in whole_l["app"]:
            decl, layer = "comment-only", "app"
        elif name in whole_l["oak"]:
            decl, layer = "comment-only", "oak"
        else:
            decl, layer = "absent", "-"
        recs.append((name, "+".join(sorted(e["trees"])), decl,
                     "1" if in_set(name, alldoc) else "0",
                     "1" if in_set(name, s_all) else "0",
                     "1" if e["sig"] else "0", e["lib"], layer,
                     ",".join(sorted(e["hdr"]))))

    with open(os.path.join(ROOT, "docs", "surface-audit.tsv"), "w",
              encoding="utf-8") as fh:
        fh.write("name\ttrees\tdecl\tin_any_doc_def\t"
                 "in_coredll_surface\thas_sig\tlib\tlayer\theaders\n")
        for r in recs:
            fh.write("\t".join(r) + "\n")

    # defect lists
    d1 = [r for r in recs if r[2] == "comment-only" and r[5] == "1"]
    d2 = [r for r in recs if r[2] == "declared" and "coredll" in r[6].lower()
          and r[3] == "0"]
    d3 = sorted(n for n in unmangled if n in live
                and n not in docdef)
    d4 = sorted(n for n in unmangled if n not in whole)
    # D5: the application -dev gap.  The official page names an
    # application-layer header (the Header row resolves to a file in
    # include/) but the name is not declared live in include/ -- i.e. a
    # user-mode CE program that includes the documented header cannot
    # get the declaration from this tree.  Names whose Header row
    # resolves to include/oak/ (or to no shipped file) are excluded:
    # those are OAK/DDK scope, not the -dev set.
    def names_app_header(hstr):
        return any(hdr_layer.get(h.lower()) == "app"
                   for h in hstr.split(",") if h)

    d5 = [r for r in recs
          if names_app_header(r[8]) and not (r[7] == "app"
                                             and r[2] == "declared")]
    d5_live_oak = [r for r in d5 if r[7] == "oak"]

    md = []
    md.append("# Surface audit (generated by tools/surface-audit.py)\n")
    md.append("Measured state -- replaces all earlier \"complete\" claims.\n")
    md.append(f"* documented API-like rows: {len(recs)}")
    for st in ("declared", "comment-only", "absent"):
        md.append(f"* {st}: {sum(1 for r in recs if r[2] == st)}")
    md.append("")
    md.append("Per layer (both layers compile together; `-I include "
              "-I include/oak`):")
    md.append("")
    md.append("| measure | include/ (app -dev) | include/oak/ (OAK-DDK) |")
    md.append("|---|---|---|")
    for st in ("declared", "comment-only"):
        a = sum(1 for r in recs if r[2] == st and r[7] == "app")
        o = sum(1 for r in recs if r[2] == st and r[7] == "oak")
        md.append(f"| {st} | {a} | {o} |")
    md.append(f"| absent (neither layer) | {sum(1 for r in recs if r[2] == 'absent')} "
              f"| - |")
    md.append("")
    md.append(f"* coredll doc-def entries: {len(docdef)}")
    md.append(f"* verified coredll surface (unmangled): {len(unmangled)}\n")
    md.append(f"## D1 -- printed signature, comment-only in include/ ({len(d1)})")
    md.append("Name printed a full prototype/struct on an official page but")
    md.append("carried only as a comment record.  These must be declared.\n")
    for r in d1[:400]:
        md.append(f"* `{r[0]}` [{r[1]}] lib: {r[6] or '-'}")
    md.append(f"\n## D2 -- declared, page says Coredll.lib, missing from coredll-doc.def ({len(d2)})")
    for r in d2[:400]:
        md.append(f"* `{r[0]}` [{r[1]}]")
    md.append(f"\n## D3 -- declared in include/, exported by verified coredll surface, missing from coredll-doc.def ({len(d3)})")
    md.append("Export existence grounded on the device-dump-audited sysroot")
    md.append("surface (clean-room.md 3.2); prototypes grounded on the pages.")
    for n in d3[:600]:
        md.append(f"* `{n}`")
    md.append(f"\n## D5 -- application -dev gap: page names an include/ header, "
              f"name not declared there ({len(d5)})")
    md.append("The official page's Header row resolves to a shipped file in")
    md.append("`include/` (application layer), but the name is not declared")
    md.append("live in `include/`.  These are the real user-mode -dev gaps;")
    md.append("OAK/DDK-header rows are excluded (out of the -dev scope).\n")
    for r in d5[:400]:
        md.append(f"* `{r[0]}` [{r[1]}] now: {r[2]}/{r[7]} "
                  f"sig={r[5]} hdr: {r[8] or '-'} lib: {r[6] or '-'}")
    md.append(f"\n## D4 -- verified coredll surface names not carried anywhere in include/ ({len(d4)})")
    md.append("Candidate surface gaps (may include CRT-provider names).")
    for n in d4[:800]:
        md.append(f"* `{n}`")
    open(os.path.join(ROOT, "docs", "surface-audit.md"), "w",
         encoding="utf-8").write("\n".join(md) + "\n")

    print(f"rows={len(recs)} declared={sum(1 for r in recs if r[2]=='declared')} "
          f"comment-only={sum(1 for r in recs if r[2]=='comment-only')} "
          f"absent={sum(1 for r in recs if r[2]=='absent')}")
    print(f"D1={len(d1)} D2={len(d2)} D3={len(d3)} D4={len(d4)} "
          f"D5={len(d5)} (of which declared in oak: {len(d5_live_oak)})")
    for tag in ("app", "oak"):
        print(f"  layer {tag}: declared="
              f"{sum(1 for r in recs if r[2] == 'declared' and r[7] == tag)} "
              f"comment-only="
              f"{sum(1 for r in recs if r[2] == 'comment-only' and r[7] == tag)}")
    print(f"coredll-doc.def={len(docdef)} surface-unmangled={len(unmangled)}")


if __name__ == "__main__":
    main()
