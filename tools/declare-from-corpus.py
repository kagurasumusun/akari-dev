#!/usr/bin/env python3
"""declare-from-corpus.py -- transcribe every documented name the corpus holds.

The per-area passes run from a hand-built job list, which is how WinInet went
unnoticed: its 47 held functions were recorded in a header comment, so no job
list ever named them, and nothing re-offered them to the transcribers.  This
driver builds the job list from the corpus itself -- every page with a
`Header:` row naming a header this tree ships -- and offers each name to both
transcribers, so coverage is a function of the archive and not of what someone
remembered to ask for.

It is idempotent: both transcribers skip a name the tree already declares
(decl-from-pages.py:declared_in_tree), so a rerun after declaring a blocking
type picks up exactly what that type unblocked and nothing else.  That is how
HINTERNET was verified -- one typedef, then 32 WinInet functions.

Usage:
    tools/declare-from-corpus.py [--corpus DIR] [--cache build/allpages]
                                 [--write] [--only Header.h ...] [--dry]
"""
import argparse
import collections
import html
import importlib.util
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

spec = importlib.util.spec_from_file_location("ca", os.path.join(HERE, "coverage-audit.py"))
ca = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ca)

IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
KIND = re.compile(r"^(?P<n>.+?)\s+(Function|Functions|Structure|Structures|"
                  r"Constants?|Messages?|Macro|Macros|Enumeration|Values|"
                  r"Callback Function|Method|Methods|Interface|Interfaces)$")


def requirements(raw):
    m = re.search(r'id="requirements"(.*?)(?:</table>|</p>)', raw, re.S)
    if not m:
        return None, None
    t = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", m.group(1))))
    def g(k):
        mm = re.search(k + r"\s+([^ ]+)", t)
        return mm.group(1).strip(".") if mm else None
    return g("Header"), g("Library")


def build_jobs(corpus, shipped, OEM, only):
    jobs = collections.defaultdict(dict)
    dirs = [os.path.join(corpus, d) for d in sorted(os.listdir(corpus))
            if os.path.isdir(os.path.join(corpus, d)) and d not in ("catalogs", ".git")]
    for d in dirs:
        for f in sorted(os.listdir(d)):
            if not f.endswith(".html"):
                continue
            raw = open(os.path.join(d, f), encoding="utf-8", errors="replace").read()
            hdr, lib = requirements(raw)
            if not hdr:
                continue
            hdr = hdr.lower().rstrip(",")
            if hdr in OEM or hdr == "developer":
                continue
            tgt = shipped.get(hdr)
            if not tgt or tgt.startswith("include" + os.sep + "oak"):
                continue
            if only and os.path.basename(tgt) not in only:
                continue
            t = re.search(r"<title>(.*?)</title>", raw, re.S)
            title = html.unescape(t.group(1)).split(" (Windows")[0].strip() if t else f[:-5]
            k = KIND.match(title)
            name = k.group(1).strip() if k else title
            if not IDENT.match(name):
                continue
            jobs[tgt].setdefault(name, {"name": name, "page": f[:-5], "os": "",
                                        "lib": (lib or "")})
    return {k: list(v.values()) for k, v in jobs.items()}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--corpus", default=os.environ.get(
        "WINCE_CORPUS", "/home/user/wince-docs-corpus"))
    ap.add_argument("--cache", default=os.path.join(ROOT, "build", "allpages"))
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--only", nargs="*")
    ap.add_argument("--jobs-dir", default=os.path.join(ROOT, "build", "corpusjobs"))
    a = ap.parse_args()

    shipped = ca.shipped_headers()
    jobs = build_jobs(a.corpus, shipped, ca.OEM, set(a.only) if a.only else None)
    print("documented names with a shipped header: %d across %d headers"
          % (sum(len(v) for v in jobs.values()), len(jobs)), file=sys.stderr)

    os.makedirs(a.jobs_dir, exist_ok=True)
    for f in os.listdir(a.jobs_dir):
        os.remove(os.path.join(a.jobs_dir, f))
    total = 0
    for tgt, js in sorted(jobs.items(), key=lambda kv: -len(kv[1])):
        p = os.path.join(a.jobs_dir, os.path.basename(tgt).replace(".", "_") + ".json")
        json.dump(js, open(p, "w", encoding="utf-8"), indent=1)
        for tool in ("decl-types-from-pages", "decl-from-pages"):
            cmd = [sys.executable, os.path.join(HERE, tool + ".py"),
                   "--list", p, "--cache", a.cache]
            if a.write:
                cmd += ["--write", "--header", tgt]
            r = subprocess.run(cmd, capture_output=True, text=True)
            m = re.search(r"^(\d+) declared", r.stdout, re.M)
            n = int(m.group(1)) if m else 0
            err = re.search(r"(\d+) errors", r.stdout)
            if r.returncode != 0:
                print("  !! %-26s %s exited %d: %s"
                      % (os.path.basename(tgt), tool, r.returncode,
                         r.stderr.strip().splitlines()[-1][:90] if r.stderr else ""))
            if n:
                print("  %-28s %-24s +%d" % (os.path.basename(tgt), tool, n))
                total += n
    print("%s: %d" % ("would declare" if not a.write else "declared", total))


if __name__ == "__main__":
    main()
