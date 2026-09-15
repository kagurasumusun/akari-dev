#!/usr/bin/env python3
"""placement-audit.py -- regenerate the header-placement audit from the corpus.

The preserved official-page corpus (tools/ce-corpus.py import) carries the
Requirements block of every CE reference page:

    <h4 id="requirements">Requirements</h4>
    <p><strong>OS Versions:</strong> Windows CE 1.01 and later.<br>
       <strong>Header:</strong> Windbase.h.</p>

That block is the only admissible evidence for where a name belongs.  The
previous docs/header-placement-audit.md was assembled ad hoc and carried
false positives -- it claimed the CEPROPVAL/CEVALUNION/CERECORDINFO/
CEFILEINFO/CEDIRINFO group was documented in winbase.h, when every one of
those pages (aa517227, aa517283, aa517237, aa517101, aa517001) prints
"Header: Windbase.h.".  This tool rebuilds the audit from the pages so the
work list is evidence-backed.

Output: a group per (documented header, declaring header) pair, with the
names, whether including the documented header reaches the declaring one,
and a machine-readable JSON twin.
"""
import argparse
import collections
import glob
import html
import json
import os
import re
import sys

ROOT = "include"
CACHE = "build/page-requirements.tsv"

REQ = re.compile(r'<h4 id="requirements">.*?</p>', re.S | re.I)
FIELD = re.compile(r'<strong>\s*([^<:]{2,24}?)\s*:?\s*</strong>\s*(.*?)(?=<br\s*/?>|<strong>|$)',
                   re.S | re.I)
TITLE = re.compile(r"<title>(.*?)</title>", re.S | re.I)
HDR_NAME = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\.h(?:xx)?", re.I)
API_TITLE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*(?:\([^)]*\))?\s*$")


def clean(seg):
    t = re.sub(r"<[^>]+>", " ", seg)
    return re.sub(r"\s+", " ", html.unescape(t)).strip()


def parse_page(path):
    """Return (api, os_versions, headers, libraries) or None."""
    try:
        s = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return None
    m = REQ.search(s)
    if not m:
        return None
    fields = {}
    for k, v in FIELD.findall(m.group(0)):
        fields[k.strip().lower().rstrip(":")] = clean(v)
    hdrs = sorted({h for h in HDR_NAME.findall(fields.get("header", ""))})
    libs = sorted({h for h in re.findall(r"[A-Za-z_][A-Za-z0-9_]*\.lib",
                                         fields.get("library", "") + " " +
                                         fields.get("libraries", ""), re.I)})
    api = None
    t = TITLE.search(s)
    if t:
        title = clean(t.group(1))
        title = re.sub(r"\s*\|.*$", "", title)
        mm = API_TITLE.match(title)
        if mm:
            api = mm.group(1)
    return api, fields.get("os versions", ""), hdrs, libs


def build_cache(dirs, force=False):
    if os.path.exists(CACHE) and not force:
        rows = []
        for line in open(CACHE, encoding="utf-8"):
            f = line.rstrip("\n").split("\t")
            if len(f) >= 5:
                rows.append((f[0], f[1], f[2], f[3].split(";"), f[4].split(";")))
        return [r for r in rows if r[0]]
    rows = []
    files = []
    for d in dirs:
        files.extend(sorted(glob.glob(os.path.join(d, "*.html"))))
    for i, p in enumerate(files, 1):
        if i % 2000 == 0:
            print("  parsed %d/%d" % (i, len(files)), file=sys.stderr)
        r = parse_page(p)
        if not r:
            continue
        api, osv, hdrs, libs = r
        rows.append((api or "", osv, os.path.basename(p), hdrs, libs))
    os.makedirs(os.path.dirname(CACHE), exist_ok=True)
    with open(CACHE, "w", encoding="utf-8") as fh:
        for api, osv, pid, hdrs, libs in rows:
            fh.write("\t".join([api, osv, pid, ";".join(hdrs), ";".join(libs)]) + "\n")
    return rows


# ---------------------------------------------------------------- tree side
def strip_comments(s):
    """Blank comment bodies but keep line structure and string literals."""
    out = []
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if c == "/" and i + 1 < n and s[i + 1] == "*":
            j = s.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r"[^\n]", " ", s[i:j]))
            i = j
        elif c == "/" and i + 1 < n and s[i + 1] == "/":
            j = s.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n:
                if s[j] == "\\":
                    j += 2
                    continue
                if s[j] == c or s[j] == "\n":
                    j += 1
                    break
                j += 1
            out.append(s[i:j])
            i = j
        else:
            out.append(c)
            i += 1
    return "".join(out)


IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
KEYWORDS = {
    "if", "else", "for", "while", "do", "return", "switch", "case", "break",
    "continue", "sizeof", "typedef", "struct", "union", "enum", "const",
    "static", "extern", "inline", "void", "char", "short", "int", "long",
    "float", "double", "signed", "unsigned", "defined", "include", "define",
    "ifdef", "ifndef", "endif", "elif", "pragma", "error", "undef",
}


def tree_index():
    """name -> sorted list of (header, line) where a declaration-like use is."""
    idx = collections.defaultdict(list)
    for dirpath, _, files in os.walk(ROOT):
        for f in sorted(files):
            if not f.endswith((".h", ".hxx")):
                continue
            p = os.path.normpath(os.path.join(dirpath, f))
            txt = strip_comments(open(p, encoding="utf-8", errors="replace").read())
            for ln, line in enumerate(txt.split("\n"), 1):
                st = line.strip()
                if not st:
                    continue
                if st.startswith("#"):
                    mdef = re.match(r"#\s*define\s+([A-Za-z_]\w*)", st)
                    if mdef:
                        idx[mdef.group(1)].append((p, ln))
                    continue
                for m in IDENT.finditer(line):
                    w = m.group(0)
                    if w in KEYWORDS:
                        continue
                    # A declaration site puts the name where a declarator
                    # belongs: immediately before ';', ',', '(', '=', '{',
                    # '[' or end of line.  Parameter names inside a prototype
                    # are followed by ',' too, which is harmless noise; uses
                    # such as 'p->field', 'a.b' or 'f(x)' are not recorded.
                    rest = line[m.end():]
                    nxt = rest.lstrip(" \t")
                    if not nxt or nxt[0] in ";,([{=":
                        idx[w].append((p, ln))
    return idx


def includes():
    inc = collections.defaultdict(set)
    pat = re.compile(r'^\s*#\s*include\s+"([^"]+)"')
    bylow = {}
    for dirpath, _, files in os.walk(ROOT):
        for f in files:
            if f.endswith((".h", ".hxx")):
                bylow.setdefault(f.lower(), os.path.normpath(os.path.join(dirpath, f)))
    for src, targets in list(inc.items()):
        pass
    for dirpath, _, files in os.walk(ROOT):
        for f in files:
            if not f.endswith((".h", ".hxx")):
                continue
            p = os.path.normpath(os.path.join(dirpath, f))
            for line in open(p, encoding="utf-8", errors="replace"):
                m = pat.match(line)
                if not m:
                    continue
                t = m.group(1).lower()
                tgt = bylow.get(t) or bylow.get(os.path.basename(t))
                if tgt:
                    inc[p].add(tgt)
    return inc, bylow


def reach(start, inc):
    seen, st = set(), [start]
    while st:
        for m in inc.get(st.pop(), ()):
            if m not in seen:
                seen.add(m)
                st.append(m)
    return seen


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pages", nargs="*",
                    default=["build/pages", "build/pages4", "build/pages6",
                             "build/pagesnet", "build/pagesw", "build/pageswm",
                             "build/pagesmag"])
    ap.add_argument("--refresh-cache", action="store_true")
    ap.add_argument("--out", default="docs/header-placement-audit.md")
    ap.add_argument("--json", default="build/placement-audit.json")
    a = ap.parse_args()

    rows = build_cache(a.pages, a.refresh_cache)
    print("corpus rows with a Requirements block: %d" % len(rows), file=sys.stderr)

    # documented header per API name (a name may appear on several pages)
    doc = collections.defaultdict(lambda: collections.defaultdict(set))
    pages_of = collections.defaultdict(set)
    for api, osv, pid, hdrs, libs in rows:
        if not api or not hdrs:
            continue
        for h in hdrs:
            doc[api][h.lower()].add(pid)
            pages_of[api].add(pid)

    idx = tree_index()
    inc, bylow = includes()
    rc = {}

    groups = collections.defaultdict(list)
    for api, per in sorted(doc.items()):
        sites = idx.get(api)
        if not sites:
            continue
        declared = {p for p, _ in sites}
        for dh, pids in per.items():
            dpath = bylow.get(dh)
            if dpath is None:
                continue                      # header not shipped in this tree
            if dpath in declared:
                continue        # the documented header declares it, so a
                                # consumer following the page compiles; a
                                # second declaration elsewhere is a separate
                                # (duplicate-declaration) question, not a
                                # placement one
            wrong = sorted(declared - {dpath})
            if not wrong:
                continue                      # declared where documented
            for w in wrong:
                groups[(dh, w)].append((api, sorted(pids)))

    out = []
    out.append("# Header placement audit\n")
    out.append("Regenerated by `tools/placement-audit.py` from the preserved\n"
               "official-page corpus (`tools/ce-corpus.py import`).  A group\n"
               "exists when a page's Requirements block prints a header that\n"
               "differs from the header that actually declares the name.\n")
    out.append("Reachable means including the documented header transitively\n"
               "includes the declaring one, so a consumer following the\n"
               "documentation still compiles.\n")
    out.append("## Groups\n")
    out.append("| page says | actually in | names | reachable |")
    out.append("|---|---|---|---|")
    order = sorted(groups.items(), key=lambda kv: -len(kv[1]))
    nreach = nnames = 0
    detail = []
    for (dh, wh), names in order:
        dpath = bylow.get(dh)
        if dpath not in rc:
            rc[dpath] = reach(dpath, inc)
        ok = wh in rc[dpath]
        nreach += ok
        nnames += len(names)
        out.append("| `%s` | `%s` | %d | %s |" % (dh, wh, len(names), "yes" if ok else "**no**"))
        detail.append(((dh, wh), names, ok))
    out.append("")
    out.append("Totals: %d groups, %d name-placements, %d groups unreachable.\n"
               % (len(groups), nnames, len(groups) - nreach))
    out.append("## Per-name lists\n")
    out.append("Only the unreachable groups are itemised; those are the work\n"
               "list.  `name (page id, ...)`.\n")
    for (dh, wh), names, ok in detail:
        if ok:
            continue
        out.append("### `%s` -> `%s` (%d)\n" % (dh, wh, len(names)))
        out.append("```")
        line = "  "
        for api, pids in sorted(names):
            item = "%s (%s)" % (api, ", ".join(pids[:3]))
            if len(line) + len(item) > 96:
                out.append(line)
                line = "  "
            line += item + "  "
        if line.strip():
            out.append(line)
        out.append("```\n")
    open(a.out, "w", encoding="utf-8").write("\n".join(out) + "\n")
    json.dump([{"documented": dh, "actual": wh,
                "reachable": ok,
                "names": [{"name": n, "pages": p} for n, p in sorted(v)]}
               for (dh, wh), v, ok in detail],
              open(a.json, "w", encoding="utf-8"), indent=1)
    print("wrote %s and %s" % (a.out, a.json))
    print("groups=%d names=%d unreachable_groups=%d"
          % (len(groups), nnames, len(groups) - nreach))


if __name__ == "__main__":
    main()
