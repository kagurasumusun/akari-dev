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


def load_headers(incdir):
    live, whole = set(), set()
    for fn in sorted(os.listdir(incdir)):
        p = os.path.join(incdir, fn)
        if not fn.endswith(".h"):
            continue
        text = open(p, encoding="utf-8", errors="replace").read()
        whole.update(IDENT.findall(text))
        code = re.sub(r"(?s)/\*.*?\*/", " ", text)
        code = re.sub(r"//[^\n]*", " ", code)
        live.update(IDENT.findall(code))
    return live, whole


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
    live, whole = load_headers(os.path.join(ROOT, "include"))

    # documented rows from every harvested official tree
    rows = {}
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
                                    "sig": False, "os": ""})
            e["trees"].add(tag)
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

    recs = []
    for name, e in sorted(rows.items(), key=lambda kv: kv[0].lower()):
        if name in live:
            decl = "declared"
        elif name in whole:
            decl = "comment-only"
        else:
            decl = "absent"
        recs.append((name, "+".join(sorted(e["trees"])), decl,
                     "1" if in_set(name, alldoc) else "0",
                     "1" if in_set(name, s_all) else "0",
                     "1" if e["sig"] else "0", e["lib"]))

    with open(os.path.join(ROOT, "docs", "surface-audit.tsv"), "w",
              encoding="utf-8") as fh:
        fh.write("name\ttrees\tdecl\tin_any_doc_def\tin_coredll_surface\thas_sig\tlib\n")
        for r in recs:
            fh.write("\t".join(r) + "\n")

    # defect lists
    d1 = [r for r in recs if r[2] == "comment-only" and r[5] == "1"]
    d2 = [r for r in recs if r[2] == "declared" and "coredll" in r[6].lower()
          and r[3] == "0"]
    d3 = sorted(n for n in unmangled if n in live
                and n not in docdef)
    d4 = sorted(n for n in unmangled if n not in whole)

    md = []
    md.append("# Surface audit (generated by tools/surface-audit.py)\n")
    md.append("Measured state -- replaces all earlier \"complete\" claims.\n")
    md.append(f"* documented API-like rows: {len(recs)}")
    for st in ("declared", "comment-only", "absent"):
        md.append(f"* {st}: {sum(1 for r in recs if r[2] == st)}")
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
    md.append(f"\n## D4 -- verified coredll surface names not carried anywhere in include/ ({len(d4)})")
    md.append("Candidate surface gaps (may include CRT-provider names).")
    for n in d4[:800]:
        md.append(f"* `{n}`")
    open(os.path.join(ROOT, "docs", "surface-audit.md"), "w",
         encoding="utf-8").write("\n".join(md) + "\n")

    print(f"rows={len(recs)} declared={sum(1 for r in recs if r[2]=='declared')} "
          f"comment-only={sum(1 for r in recs if r[2]=='comment-only')} "
          f"absent={sum(1 for r in recs if r[2]=='absent')}")
    print(f"D1={len(d1)} D2={len(d2)} D3={len(d3)} D4={len(d4)}")
    print(f"coredll-doc.def={len(docdef)} surface-unmangled={len(unmangled)}")


if __name__ == "__main__":
    main()
