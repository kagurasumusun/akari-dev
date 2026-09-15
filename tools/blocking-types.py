#!/usr/bin/env python3
"""blocking-types.py -- which undeclared type blocks which documented names.

The tree's audits answer "is this name declared?".  They cannot answer the
question that actually decides coverage: when a name is *not* declared, is
that because its page prints nothing, or because one type it mentions is
missing and that one type is holding a whole API family hostage?

WinInet is the worked example.  include/Wininet.h declares 38 names and
records 47 more as "held", every one of them because HINTERNET, GROUPID or
INTERNET_PORT is not declared.  InternetOpen's page (ms918368) prints
"HINTERNET WINAPI InternetOpen(...)" and InternetCloseHandle (ms918348)
prints "BOOL WINAPI InternetCloseHandle(HINTERNET hInternet)" -- so HINTERNET
is the documented return type of a documented, exported function and is
closed by a documented CloseHandle, i.e. it is a handle.  No CE page prints a
typedef for it (145 pages mention it, 0 define it), and the hold policy
therefore removed the entire area: 0 of the 11 basic WinInet functions were
declared.

This tool measures the cascade instead of guessing at it: it offers every
documented name to the transcribers and tallies the skip reasons, so a type
that blocks 40 functions is visible next to one that blocks 1.

Usage:
    tools/blocking-types.py [--corpus DIR] [--top N] [--json OUT]
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
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

spec = importlib.util.spec_from_file_location("dfp", os.path.join(HERE, "decl-from-pages.py"))
dfp = importlib.util.module_from_spec(spec)
spec.loader.exec_module(dfp)
spec2 = importlib.util.spec_from_file_location("ca", os.path.join(HERE, "coverage-audit.py"))
ca = importlib.util.module_from_spec(spec2)
spec2.loader.exec_module(ca)

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


def scan(corpus, shipped, declared, OEM):
    """(name, header, lib, page) for every documented name in a shipped header."""
    out = {}
    dirs = [os.path.join(corpus, d) for d in sorted(os.listdir(corpus))
            if os.path.isdir(os.path.join(corpus, d)) and d not in ("catalogs", ".git")]
    for d in dirs:
        for f in os.listdir(d):
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
            t = re.search(r"<title>(.*?)</title>", raw, re.S)
            title = html.unescape(t.group(1)).split(" (Windows")[0].strip() if t else f[:-5]
            k = KIND.match(title)
            name = k.group(1).strip() if k else title
            if not IDENT.match(name) or name in declared:
                continue
            out.setdefault((name, hdr), {"name": name, "page": f[:-5],
                                         "os": "", "lib": (lib or ""), "target": tgt})
    return list(out.values())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--corpus", default=os.environ.get(
        "WINCE_CORPUS", "/home/user/wince-docs-corpus"))
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--json", default="build/blocking-types.json")
    a = ap.parse_args()

    shipped = ca.shipped_headers()
    declared = dfp.declared_in_tree()
    jobs = scan(a.corpus, shipped, declared, ca.OEM)
    print("documented names in a shipped header, not declared: %d" % len(jobs),
          file=sys.stderr)

    by_hdr = collections.defaultdict(list)
    for j in jobs:
        by_hdr[j["target"]].append(j)

    reasons = collections.Counter()
    blocked_by = collections.defaultdict(set)     # type -> {name}
    tmpdir = os.path.join(ROOT, "build", "blocking")
    os.makedirs(tmpdir, exist_ok=True)
    for f in os.listdir(tmpdir):
        os.remove(os.path.join(tmpdir, f))
    for tgt, js in sorted(by_hdr.items()):
        p = os.path.join(tmpdir, os.path.basename(tgt).replace(".", "_") + ".json")
        json.dump(js, open(p, "w", encoding="utf-8"), indent=1)
        for tool in ("decl-types-from-pages", "decl-from-pages"):
            r = subprocess.run([sys.executable, os.path.join(HERE, tool + ".py"),
                                "--list", p, "--cache", os.path.join(ROOT, "build", "allpages")],
                               capture_output=True, text=True)
            for line in r.stdout.splitlines():
                if not line.startswith("SKIP"):
                    continue
                parts = line.split(None, 2)
                if len(parts) < 3:
                    continue
                name, why = parts[1], parts[2]
                key = re.sub(r'"[^"]*"', '"X"', why)
                reasons[key[:70]] += 1
                for m in re.finditer(r'type "([^"]+)"', why):
                    blocked_by[m.group(1)].add(name)
                m = re.match(r'value uses "([^"]+)"', why)
                if m:
                    blocked_by[m.group(1)].add(name)

    print("\n%-40s %s" % ("skip reason", "count"))
    for k, n in reasons.most_common(12):
        print("%-40s %d" % (k, n))
    print("\ntypes blocking the most documented names:")
    print("%-38s %6s  %s" % ("type", "blocks", "examples"))
    top = sorted(blocked_by.items(), key=lambda kv: -len(kv[1]))
    for t, names in top[:a.top]:
        print("%-38s %6d  %s" % (t, len(names), ", ".join(sorted(names)[:5])))
    js = a.json if os.path.isabs(a.json) else os.path.join(ROOT, a.json)
    os.makedirs(os.path.dirname(js), exist_ok=True)
    json.dump({"jobs": len(jobs),
               "reasons": dict(reasons),
               "blocked_by": {k: sorted(v) for k, v in blocked_by.items()}},
              open(js, "w", encoding="utf-8"), indent=1)
    print("\nwrote %s" % js, file=sys.stderr)


if __name__ == "__main__":
    main()
