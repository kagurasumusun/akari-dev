#!/usr/bin/env python3
"""gap-pass.py -- offer every remaining app-layer gap to both transcribers.

tools/coverage-audit.py buckets the official pages it classifies; the
"app-layer gaps" bucket is the ones that are in scope, cite a header this tree
ships, and are still not declared.  Most of them are there because the page
prints nothing this tree can transcribe, but a few become transcribable once a
type declared elsewhere in the same run exists -- so the pass is worth running
after tools/ship-missing-headers.py, not before it.

Both transcribers are offered every page.  Splitting them by "does the page
print a Link Library" sends the sms.h and tsp.h enum pages -- which do print
one -- to the function transcriber, where they are rejected as "page has no
prototype block".  Each tool rejects what it cannot handle, so offering both
costs nothing.

The tools insert before the generation gate's #endif, so tools/gate-new-headers.py
must have run first or new declarations land outside the gate and compile with
their own includes switched off.

Usage: tools/gap-pass.py [--dry]
"""
import collections
import importlib.util
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

spec = importlib.util.spec_from_file_location("ca", "tools/coverage-audit.py")
ca = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ca)


def main():
    dry = "--dry" in sys.argv
    shipped = ca.shipped_headers()
    cov = json.load(open("build/coverage.json", encoding="utf-8"))
    by = collections.defaultdict(list)
    for r in cov["app_layer_gaps"]:
        low = (r.get("header") or "").lower()
        target = shipped.get(low)
        # include/oak is the OEM/BSP layer, which is out of scope, so a gap
        # that cites an oak header is not this pass's business.
        if target and not target.startswith("include" + os.sep + "oak"):
            by[target].append({"name": r["api"], "page": r["page"],
                               "os": r["os"], "lib": r.get("lib", "")})
    os.makedirs("build/gaps", exist_ok=True)
    for f in os.listdir("build/gaps"):
        os.remove(os.path.join("build/gaps", f))

    total = 0
    for hdr, jobs in sorted(by.items(), key=lambda kv: -len(kv[1])):
        p = "build/gaps/%s.json" % os.path.basename(hdr).replace(".", "_")
        json.dump(jobs, open(p, "w", encoding="utf-8"), indent=1)
        for tool in ("decl-types-from-pages", "decl-from-pages"):
            cmd = [sys.executable, "tools/%s.py" % tool, "--list", p,
                   "--cache", "build/pagecache"]
            if not dry:
                cmd += ["--write", "--header", hdr]
            r = subprocess.run(cmd, capture_output=True, text=True)
            m = re.search(r"^(\d+) declared", r.stdout, re.M)
            n = int(m.group(1)) if m else 0
            if n:
                print("  %-28s %-24s +%d" % (os.path.basename(hdr), tool, n))
                total += n
    print("gaps considered: %d across %d headers, %s: %d"
          % (sum(len(v) for v in by.values()), len(by),
             "would declare" if dry else "declared", total))


if __name__ == "__main__":
    main()
