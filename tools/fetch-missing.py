#!/usr/bin/env python3
"""fetch-missing.py -- fetch the TOC pages the corpus does not hold.

The corpus is the input every audit in this tree measures against, so a page
that was never harvested is invisible to gen-audit.py, placement-audit.py,
undeclared-audit.py and coverage-audit.py alike.  Measured against all four
CE catalogs (tools/catalogs/catalog-*.tsv, 61,926 page ids), 14,219 TOC pages
are absent from the corpus, and 1,330 of those carry a reference-page title --
real API pages, including ADDCONNECT_DLGPARAMS (ee493238), BD_ADDR
(ee495641) and AllocPhysMem (ee482808).  ADDCONNECT_DLGPARAMS was reported in
M135 as "no printed definition on the page"; the page had simply never been
fetched.  That is the failure this tool exists to prevent.

Two details the archive forces:

  * The URL must keep the catalog's version suffix.  `ms905342(v=msdn.10)`
    returns 200; the bare `ms905342` returns 404.
  * 12 concurrent workers draw mass HTTP 429.  3 workers with exponential
    backoff (6*n s) completes with zero failures.

Usage:
    tools/fetch-missing.py --out build/pagesgap2 [--jobs build/missing-toc.json]
                           [--ref-only] [--limit N] [--workers 3]
"""
import argparse
import concurrent.futures as cf
import json
import os
import re
import sys
import time
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
URL = "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/"
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/120.0 Safari/537.36")

IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
KIND = re.compile(r"^[A-Za-z_][A-Za-z0-9_:\. ]{0,40}?\s+(Function|Functions|"
                  r"Structure|Structures|Constants?|Messages?|Macro|Macros|"
                  r"Enumeration|Values|Callback Function|Method|Methods|"
                  r"Interface|Interfaces)$")


def is_ref(title):
    return bool(IDENT.match(title) or KIND.match(title))


def fetch_one(pid, outdir):
    dest = os.path.join(outdir, pid + ".html")
    if os.path.exists(dest) and os.path.getsize(dest) > 2000:
        return pid, "cached"
    for n in range(1, 6):
        try:
            req = urllib.request.Request(URL + pid, headers={"User-Agent": UA})
            with urllib.request.urlopen(req, timeout=60) as r:
                body = r.read()
            if len(body) < 2000:
                return pid, "too-small:%d" % len(body)
            tmp = dest + ".part"
            with open(tmp, "wb") as fh:
                fh.write(body)
            os.replace(tmp, dest)
            return pid, "ok"
        except Exception as e:                                   # noqa: BLE001
            code = getattr(e, "code", None)
            if code == 404:
                return pid, "404"
            time.sleep(6 * n)
    return pid, "failed"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default="build/pagesgap2")
    ap.add_argument("--jobs", default="build/missing-toc.json")
    ap.add_argument("--ref-only", action="store_true",
                    help="only pages whose title looks like an API reference page")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--workers", type=int, default=3)
    a = ap.parse_args()

    jobs = json.load(open(os.path.join(ROOT, a.jobs), encoding="utf-8"))
    todo = []
    for base, (cat, title, pid) in jobs.items():
        if a.ref_only and not is_ref(title):
            continue
        todo.append(pid)
    todo = sorted(set(todo))
    if a.limit:
        todo = todo[:a.limit]
    outdir = a.out if os.path.isabs(a.out) else os.path.join(ROOT, a.out)
    os.makedirs(outdir, exist_ok=True)
    print("fetching %d pages into %s with %d workers" % (len(todo), outdir, a.workers),
          flush=True)

    counts = {}
    done = 0
    t0 = time.time()
    with cf.ThreadPoolExecutor(max_workers=a.workers) as ex:
        for pid, st in ex.map(lambda p: fetch_one(p, outdir), todo):
            counts[st] = counts.get(st, 0) + 1
            done += 1
            if done % 100 == 0:
                print("  %d/%d  %s  (%.0fs)" % (done, len(todo), counts,
                                                time.time() - t0), flush=True)
    print("done: %s" % counts, flush=True)


if __name__ == "__main__":
    main()
