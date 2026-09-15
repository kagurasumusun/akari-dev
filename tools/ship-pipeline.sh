#!/bin/sh
# ship-pipeline.sh -- the M135 declaration pipeline, in order.
#
# Every step here has an ordering dependency on the one before it, and the
# ordering is not obvious from the tools themselves:
#
#   0. coverage-audit.py        classifies the official pages against the
#      surface as it stands.  It has to run BEFORE step 1: ship-missing-headers
#      reads the audit's "header not shipped here" bucket, and a stale
#      coverage.json still says a header that was just deleted is covered, so
#      the run ships nothing (measured: 1 header instead of 36).
#   1. ship-missing-headers.py  creates include/<Documented>.h for headers the
#      official pages name but include/ did not have, and transcribes what
#      their pages print.  --passes is a fixpoint: a type declared in pass 1
#      unblocks the declarations that use it in pass 2.
#   2. add-header-includes.py   adds the includes the transcribed code needs.
#      It must run before the gate so the includes sit outside it -- a header
#      gated at 0x0600 still has to be self-consistent when included at 0x420.
#   3. gate-new-headers.py      wraps a new header's declarations in
#      `#if _WIN32_WCE >= 0xNNNN` from its own OS Versions rows.  A
#      whole-file-gated header silently breaks includers at a lower generation
#      (D3dm.h at 0x0500 is why D3dmx.h lost D3DMFORMAT at 0x420).
#   4. coverage-audit.py        re-runs the audit, because step 1 moved ~750
#      records out of "header not shipped here" and into the buckets below it;
#      the residue is what step 5 works on.
#   5. the gap pass             offers every remaining app-layer gap whose
#      header now exists to both transcribers.  They insert before the
#      generation gate's #endif, which is why step 3 has to have run first.
#   6. add-header-includes.py   again, for the declarations step 5 added.
#   7. Makefile HDRS            a header absent from HDRS is compiled by
#      neither hostcheck nor crosscheck, so make check stays green while the
#      header is broken.
#
# Usage: sh tools/ship-pipeline.sh
set -e
cd "$(dirname "$0")/.."

# 0. start from the committed surface so a rerun is idempotent
for f in $(git status --porcelain include/ | awk '$1=="??"{print $2}'); do rm -f "$f"; done
git checkout include/

echo "--- 0. coverage-audit (classify what the committed surface covers) ---"
python3 tools/coverage-audit.py --gap-pages build/pagesgap \
    --json build/coverage.json --tsv docs/coverage-gaps.tsv

echo "--- 1. ship-missing-headers ---"
python3 tools/ship-missing-headers.py --passes 3

echo "--- 2. add-header-includes (new headers) ---"
python3 tools/add-header-includes.py --all-new build/shipped-headers.json

echo "--- 3. gate-new-headers ---"
python3 tools/gate-new-headers.py

echo "--- 4. coverage-audit ---"
python3 tools/coverage-audit.py --gap-pages build/pagesgap \
    --json build/coverage.json --tsv docs/coverage-gaps.tsv

echo "--- 5. gap pass over the remaining app-layer gaps ---"
python3 tools/gap-pass.py

echo "--- 6. add-header-includes (gap-pass declarations) ---"
python3 tools/add-header-includes.py $(python3 - <<'PY'
import json, subprocess
new = json.load(open('build/shipped-headers.json'))['created']
mod = subprocess.run(['git', 'status', '--porcelain', 'include/'],
                     capture_output=True, text=True).stdout
touched = [l.split()[-1] for l in mod.splitlines() if l.endswith(('.h', '.hpp', '.hxx'))]
print(' '.join(sorted(set(new) | set(touched))))
PY
) || true

echo "--- 7. Makefile HDRS ---"
python3 tools/merge-hdrs.py

echo "--- 8. make check ---"
make check
