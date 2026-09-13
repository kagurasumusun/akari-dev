#!/usr/bin/env python3
"""ce-twins.py -- resolve official CE 6.0 / CE .NET twin page ids.

The Learn previous-versions archive republishes the same API corpus
under separate per-version trees with independent page ids (CE 5.0
`(v=msdn.10)`, CE 6.0 `(v=winembedded.60)`, CE .NET `(v=msdn.10)`).
This tool maps every harvested CE 5.0 leaf (the union of
`tools/manifests/*.manifest` titles) to its twin id in another tree by
exact title match against the committed official TOC catalogs
(`tools/catalogs/catalog-*.tsv`), and reports the coverage.

The CE 5.0 leaf set is built from the manifest rows that are CE 5.0
pages: a bare id or an id tagged `(v=msdn.10)`.  Rows tagged
`(v=winembedded.60)` belong to the CE 6.0 *twin* manifests
(`*-ce60.manifest`, `m5x-ce60.manifest`, `stdshell6.manifest`, the
`-dep.manifest` dependency stubs, …) and are skipped so the twin id is
never mistaken for a CE 5.0 id.  Twin ids are reported bare (the
`(v=...)` tag is stripped) to match the committed `docs/ce6-twins.tsv`
format.

Usage:
    python3 tools/ce-twins.py --tree windows-embedded-ce-60
    python3 tools/ce-twins.py --tree windows-ce-net --out /tmp/newnet.json

Output (default stdout, TSV):  <ce5-title>\\t<ce5-id>\\t<twin-id>
Titles that exist in multiple trees are matched exactly; the CE5 id
shown is the manifest page (first manifest that lists the title).
"""

import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CAT = os.path.join(ROOT, "tools", "catalogs")


def split_tag(pid):
    """Return (bare_id, tag) from a possibly tagged page id."""
    pid = pid.strip()
    m = re.search(r'\((v=[a-z0-9.]+)\)$', pid)
    if m:
        return pid[:m.start()].strip(), m.group(0)
    return pid, ""


def catalog_ids(tree):
    """Return {title: [bare ids]} from the committed catalog for `tree`."""
    path = os.path.join(CAT, f"catalog-{tree}.tsv")
    if not os.path.exists(path):
        sys.exit(f"no catalog for tree {tree!r}: {path}")
    out = {}
    for line in open(path, encoding="utf-8"):
        line = line.rstrip("\n")
        if not line or "\t" not in line:
            continue
        pid, title = line.split("\t", 1)
        bare, _ = split_tag(pid)
        out.setdefault(title.strip(), []).append(bare)
    return out


def manifest_leaves():
    """{title: CE5 bare id} from the CE 5.0 manifest rows only.

    Skips rows whose id is tagged `(v=winembedded.*)` -- those are the
    CE 6.0 twin manifests, not CE 5.0 leaves.  `(v=msdn.10)` tags are
    stripped; bare ids pass through unchanged."""
    leaves = {}
    for mf in sorted(glob.glob(os.path.join(ROOT, "tools", "manifests", "*.manifest"))):
        for line in open(mf, encoding="utf-8"):
            line = line.rstrip("\n")
            if not line or "\t" not in line:
                continue
            pid, title = line.split("\t", 1)
            bare, tag = split_tag(pid)
            if tag.startswith("(v=winembedded"):
                continue
            leaves.setdefault(title.strip(), bare)
    return leaves


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tree", default="windows-embedded-ce-60",
                    help="twin catalog: windows-embedded-ce-60 or windows-ce-net")
    ap.add_argument("--out", default=None, help="write TSV to a file")
    a = ap.parse_args()

    leaves = manifest_leaves()
    twins = catalog_ids(a.tree)
    out = []
    matched = missing = 0
    for title in sorted(leaves):
        ce5 = leaves[title]
        if title in twins:
            matched += 1
            for tid in twins[title][:1]:
                out.append(f"{title}\t{ce5}\t{tid}")
        else:
            missing += 1
            out.append(f"{title}\t{ce5}\t-")
    text = "\n".join(out) + "\n"
    if a.out:
        with open(a.out, "w", encoding="utf-8") as fh:
            fh.write(text)
    else:
        sys.stdout.write(text)
    print(f"[ce-twins] {matched} matched, {missing} no twin in {a.tree}",
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
