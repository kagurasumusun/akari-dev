#!/usr/bin/env python3
"""coverage-audit.py -- what the corpus does not cover, and what that hides.

Every audit in this tree measures the SDK against the preserved corpus.  That
is sound only if the corpus is complete, and it was not: cross-checking the
preserved pages against the official table of contents showed the harvest
covered 66% of the CE 5.0 TOC, 58% of the CE 6.0 TOC and 100% of CE .NET.
A name whose page was never harvested is invisible to gen-audit.py,
placement-audit.py and undeclared-audit.py alike -- the gap the audits could
not report was a gap in their own input.

This tool closes that.  It takes the official TOC (tools/catalogs/*.tsv, the
page-id/title index of the MSDN archive books) as the universe, subtracts the
preserved pages, filters what is left to reference-page titles, and -- for
pages that have been fetched under build/pagesgap -- reads each page's
Requirements block to say whether the name is declared, is OEM/BSP, or is a
real app-layer gap.

Stages, so the report is honest about what is measured and what is not:

  TOC            every page id in the CE catalogs
  harvested      present in build/pages*
  reference-like title is a bare identifier or 'X Function/Structure/
                 Constants/Messages/Macro/Enumeration/Values/Callback
                 Function/Method/Interface'
  fetched        present under build/pagesgap (this tool does not fetch;
                 /tmp/fetch2.py did, keeping the catalog's own version
                 suffix -- the archive URL needs 'ms905342(v=msdn.10)',
                 not 'ms905342')
  classified     has a Requirements block, so header and link library are
                 known and the name can be judged

Usage:
    tools/coverage-audit.py [--json build/coverage.json] [--tsv OUT]
"""
import argparse
import collections
import glob
import importlib.util
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

CATALOGS = ["catalog-windows-ce-net.tsv", "catalog-windows-ce-50.tsv",
            "catalog-windows-embedded-ce-60.tsv"]
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
KIND = re.compile(
    r"^(?P<n>[A-Za-z_][A-Za-z0-9_:\. ]{0,40}?)\s+"
    r"(Function|Functions|Structure|Structures|Constants?|Messages?|Macro|"
    r"Macros|Enumeration|Values|Callback Function|Method|Methods|Interface|"
    r"Interfaces)$")

# Platform Builder, OAL, BSP and driver-development headers.  The project's
# standing constraint puts the OEM/BSP layer out of scope, so a gap whose
# documented header is one of these is reported apart from the work list.
OEM = {
    "atapi2.h", "armintr.h", "blcommon.h", "busenum.h", "bt_ddi.h", "calibrui.h",
    "cardserv.h", "cardsv2.h", "ceddk.h", "celog.h", "cmnintr.h", "cmnintrin.h",
    "ddhal.h", "ddkreg.h", "ddstream.h", "devload.h", "diskio.h", "ethdbg.h",
    "externs.h", "fmd.h", "fsdmgr.h", "giisr.h", "gpe.h", "halether.h",
    "hcdddsi.h", "hcdi.h", "hiddi.h", "hidpddi.h", "hidparse.h", "hidpi.h",
    "kfuncs.h", "keybddr.h", "kitl.h", "kitltran.h", "mmddk.h", "mipsintr.h",
    "ndis.h", "nkintr.h", "nleddrv.h", "ntddndis.h", "oalintr.h", "oemwake.h",
    "ohcdddsi.h", "partdrv.h", "pcibus.h", "pcireg.h", "pcmcia.h", "pkfuncs.h",
    "pm.h", "pwindbas.h", "pwindbase.h", "pwinddi.h", "pwinreg.h", "pwinuser.h",
    "pcommctr.h", "profiler.h", "rndismini.h", "romldr.h", "sdcardddk.h",
    "sdmem.h", "serdev.h", "shintr.h", "streams.h", "tchddi.h", "tchddsi.h",
    "tchmdd.h", "usbd.h", "waveapi.h", "waveddsi.h", "wavemdd.h", "wdm.h",
    "nclient.h", "oomui.h", "nkarm.h", "pegdserr.h",
}


def load_placement():
    spec = importlib.util.spec_from_file_location(
        "placement_audit", os.path.join(HERE, "placement-audit.py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def shipped_headers():
    out = {}
    for dp, _, fs in os.walk(os.path.join(ROOT, "include")):
        for f in fs:
            if f.endswith((".h", ".hxx", ".hpp")):
                out.setdefault(f.lower(), os.path.normpath(os.path.join(dp, f)))
    return out


def norm(pid):
    return re.sub(r"\(v=[^)]*\)", "", pid).strip().lower()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--catalogs", nargs="*", default=CATALOGS)
    ap.add_argument("--gap-pages", default="build/pagesgap")
    ap.add_argument("--json", default="build/coverage.json")
    ap.add_argument("--tsv", default="docs/coverage-gaps.tsv")
    a = ap.parse_args()

    pa = load_placement()
    bylow = shipped_headers()
    declared = set(pa.tree_index())

    harvested = set()
    for d in glob.glob(os.path.join(ROOT, "build", "pages*")):
        for f in os.listdir(d):
            if f.endswith(".html"):
                harvested.add(f[:-5].lower())

    toc = {}
    for cat in a.catalogs:
        p = os.path.join(ROOT, "tools", "catalogs", cat)
        if not os.path.exists(p):
            continue
        for line in open(p, encoding="utf-8"):
            f = line.rstrip("\n").split("\t")
            if len(f) >= 2 and f[0]:
                toc.setdefault(norm(f[0]), {"raw": f[0].strip(),
                                            "title": f[1].strip(),
                                            "catalog": cat})
    missing = {k: v for k, v in toc.items() if k not in harvested}
    refl = {}
    for k, v in missing.items():
        t = v["title"]
        m = KIND.match(t)
        if IDENT.match(t) or m:
            v = dict(v, api=(t if IDENT.match(t) else m.group("n")))
            refl[k] = v

    st = collections.Counter(toc=0, harvested=0)
    st["toc"] = len(toc)
    st["harvested"] = len(harvested)
    st["missing"] = len(missing)
    st["reference_like"] = len(refl)

    gaps, oem, not_shipped, no_req = [], [], [], []
    fetched = 0
    for k, v in sorted(refl.items()):
        p = os.path.join(ROOT, a.gap_pages, v["raw"] + ".html")
        if not os.path.exists(p):
            continue
        fetched += 1
        r = pa.parse_page(p)
        if not r:
            no_req.append(v)
            continue
        api, osv, hdrs, libs = r
        api = api or v["api"]
        sh = [h for h in hdrs if h.lower() in bylow]
        rec = {"api": api, "page": v["raw"], "title": v["title"],
               "os": osv, "header": sh[0] if sh else "",
               "all_headers": sh, "lib": ",".join(libs),
               "catalog": v["catalog"]}
        if not sh:
            rec["header"] = (hdrs[0] if hdrs else "")
            not_shipped.append(rec)
        elif api in declared:
            st["already_declared"] += 1
        elif sh[0].lower() in OEM:
            oem.append(rec)
        else:
            gaps.append(rec)
    st["fetched_for_classification"] = fetched
    st["no_requirements_block"] = len(no_req)
    st["header_not_shipped"] = len(not_shipped)
    st["oem_or_bsp"] = len(oem)
    st["app_layer_gaps"] = len(gaps)

    print("official TOC pages (CE .NET + 5.0 + 6.0): %d" % st["toc"])
    print("  harvested into build/pages*:           %d" % st["harvested"])
    print("  not harvested:                         %d" % st["missing"])
    print("    reference-like titles:               %d" % st["reference_like"])
    print("      fetched for classification:        %d" % fetched)
    print("        no Requirements block:           %d" % st["no_requirements_block"])
    print("        header not shipped here:         %d" % st["header_not_shipped"])
    print("        already declared:                %d" % st["already_declared"])
    print("        OEM/BSP (out of scope):          %d" % st["oem_or_bsp"])
    print("        APP-LAYER GAPS:                  %d" % st["app_layer_gaps"])

    byh = collections.Counter(g["header"] for g in gaps)
    print("\napp-layer gaps by documented header:")
    for h, c in byh.most_common(30):
        print("   %-24s %4d" % (h, c))

    os.makedirs(os.path.dirname(a.json) or ".", exist_ok=True)
    json.dump({"stats": dict(st), "app_layer_gaps": gaps,
               "oem_or_bsp": oem, "header_not_shipped": not_shipped,
               "no_requirements_block": no_req},
              open(a.json, "w", encoding="utf-8"), indent=1)
    with open(a.tsv, "w", encoding="utf-8") as fh:
        fh.write("name\tpage\tos_versions\theader\tlink_library\tcatalog\n")
        for g in sorted(gaps, key=lambda g: (g["header"], g["api"])):
            fh.write("\t".join([g["api"], g["page"], g["os"], g["header"],
                                g["lib"], g["catalog"]]) + "\n")
    print("\nwrote %s and %s" % (a.json, a.tsv))


if __name__ == "__main__":
    main()
