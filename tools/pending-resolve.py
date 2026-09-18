#!/usr/bin/env python3
"""pending-resolve.py -- resolve PENDING-REGROUNDING entries in
def/coredll-doc.def against the harvested corpus.

Policy (def header comment, docs/clean-room.md v3): a pending entry is
the exact title of a page in the official TOC catalogs whose
Requirements row had not been read yet.  Now that the pages are in the
corpus, read each page's Requirements row / APILocation metadata:
  * some page of the function confirms Coredll  -> keep (doc-derived)
  * pages exist, none names Coredll             -> drop (ledgered)
  * page still missing from the corpus          -> stays pending

Usage:
    python3 tools/pending-resolve.py <corpus> [--dry] [--out docs/pending-resolution.tsv]
"""
import html
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUDIT = "docs/def-audit-coredll-2026-09-18.tsv"


def pending_names():
    names = []
    with open(os.path.join(ROOT, AUDIT), encoding="utf-8") as f:
        for line in f:
            f_ = line.rstrip("\n").split("\t")
            if len(f_) >= 2 and f_[0] == "pending":
                names.append(f_[1])
    return names


def load_index(corpus):
    by_title = {}
    with open(os.path.join(corpus, "data/index/INDEX.tsv"),
              encoding="utf-8") as f:
        for line in f:
            f_ = line.rstrip("\n").split("\t")
            if len(f_) < 4:
                continue
            pid, book, path, title = f_[:4]
            by_title.setdefault(title, []).append((pid, book, path))
    return by_title


def title_hits(by_title, name):
    """Pages whose title is exactly this function's name."""
    out = []
    pats = (re.compile(r"^%s$" % re.escape(name)),
            re.compile(r"^%s (?:Function )?\(" % re.escape(name)),
            # Unicode-only export: the generic (unsuffixed) page
            re.compile(r"^%s (?:Function )?\(" % re.escape(name[:-1]))
            if name.endswith("W") else None)
    for title, pages in by_title.items():
        for p in pats:
            if p and p.match(title):
                out.extend(pages)
                break
    return out


REQ = re.compile(r"Requirements(.{0,1500}?)(?:See Also|Community|Feedback|$)",
                 re.S | re.I)


def page_requirements(corpus, relpath):
    h = open(os.path.join(corpus, relpath), encoding="utf-8",
             errors="replace").read()
    text, meta = "", []
    m = REQ.search(h)
    if m:
        text = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ",
                                                        m.group(1))))
    for mm in re.finditer(r'<meta[^>]+>', h):
        tag = mm.group(0)
        if re.search(r"APILocation|APIName|APIMinOS", tag, re.I):
            meta.append(re.sub(r"\s+", " ", tag))
    return text, meta


COREDLL = re.compile(r"coredll", re.I)


def main():
    corpus = sys.argv[1]
    dry = "--dry" in sys.argv
    out = "docs/pending-resolution-2026-09-18.tsv"
    for a in sys.argv:
        if a.startswith("--out="):
            out = a.split("=", 1)[1]
    names = pending_names()
    by_title = load_index(corpus)
    rows = []
    stats = {"confirm": 0, "drop": 0, "still-pending": 0}
    for name in names:
        cands = title_hits(by_title, name)
        if not cands:
            stats["still-pending"] += 1
            rows.append((name, "pending", "", "page not harvested yet"))
            continue
        conf, libs = None, []
        for pid, book, rel in cands:
            text, meta = page_requirements(corpus, "docs/mslearn/" + rel
                                           if not rel.startswith("docs/")
                                           else rel)
            blob = text + " " + " ".join(meta)
            lm = re.search(r"(?:Link Library|Library)[:\s]+([A-Za-z0-9_.]+)",
                           text)
            lib = lm.group(1) if lm else ""
            libs.append((pid, lib or "?"))
            if COREDLL.search(blob):
                conf = (pid, lib)
                break
        if conf:
            stats["confirm"] += 1
            rows.append((name, "confirm", conf[0],
                         "Requirements name Coredll (%s)" %
                         (conf[1] or "meta")))
        else:
            stats["drop"] += 1
            rows.append((name, "drop", libs[0][0],
                         "Requirements name %s" %
                         ", ".join(sorted({l for _, l in libs}))))
    outp = os.path.join(ROOT, out)
    with open(outp, "w") as f:
        f.write("# name\taction\tpage\tnote\n")
        for r in rows:
            f.write("\t".join(r) + "\n")
    print("stats:", stats, "-> ", outp)
    if dry:
        return

    # apply: audit tsv + def file
    act = {r[0]: r for r in rows}
    lines = open(os.path.join(ROOT, AUDIT), encoding="utf-8").read().splitlines()
    with open(os.path.join(ROOT, AUDIT), "w", encoding="utf-8") as f:
        for line in lines:
            f_ = line.split("\t")
            if len(f_) >= 2 and f_[0] == "pending" and f_[1] in act:
                r = act[f_[1]]
                if r[1] == "confirm":
                    f.write("keep\t%s\tdoc-derived (%s)\n" % (f_[1], r[2]))
                elif r[1] == "drop":
                    f.write("drop\t%s\t%s\n" % (f_[1], r[3]))
                else:
                    f.write(line + "\n")
            else:
                f.write(line + "\n")
    drops = {r[0] for r in rows if r[1] == "drop"}
    defp = os.path.join(ROOT, "def/coredll-doc.def")
    kept = []
    for line in open(defp, encoding="utf-8"):
        s = line.strip()
        if s in drops:
            continue
        kept.append(line)
    with open(defp, "w", encoding="utf-8") as f:
        f.writelines(kept)
    print("def entries dropped:", len(drops),
          "def size now:", sum(1 for l in kept
                               if l.strip() and not l.startswith(";")
                               and l.strip().upper() not in
                               ("LIBRARY COREDLL.DLL", "EXPORTS")))


if __name__ == "__main__":
    main()
