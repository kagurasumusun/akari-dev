#!/usr/bin/env python3
"""area-audit.py -- coverage per functional area, from the pages themselves.

Every other audit in this tree buckets by "is the documented header shipped
here".  That answers a question about files, not about the surface: it cannot
say whether the Telephony, IrDA or Notifications area is covered, because it
never groups by area.  This tool does, and it groups by the only objective
signal the archive gives -- the `Header:` row of each page's Requirements
block -- so an area's coverage is whatever its own pages say, not a guess
from a filename.

It scans every harvested page directory in the corpus plus the two fetched
this milestone (build/pagesgap2, build/pagesmember), because a page that was
never harvested is invisible to every audit that reads the corpus.

Usage:
    tools/area-audit.py [--corpus /home/user/wince-docs-corpus]
                        [--md docs/area-coverage.md]
                        [--json build/area-audit.json]
"""
import argparse
import collections
import html
import importlib.util
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

spec = importlib.util.spec_from_file_location("dfp", os.path.join(HERE, "decl-from-pages.py"))
dfp = importlib.util.module_from_spec(spec)
spec.loader.exec_module(dfp)
spec2 = importlib.util.spec_from_file_location("ca", os.path.join(HERE, "coverage-audit.py"))
ca = importlib.util.module_from_spec(spec2)
spec2.loader.exec_module(ca)

# Functional areas, keyed by the header the pages name.  A header appears in
# exactly one area; where a header spans two (windows.h carries both User and
# Kernel declarations) the area is chosen by what the header is for, and the
# per-name report below still lists every name so nothing is hidden by the
# choice.
AREAS = collections.OrderedDict([
    ("Process / Thread / Module", {
        "winbase.h", "winbase.h,", "tlhelp32.h", "psapi.h", "kfuncs.h",
        "toolhelp.h", "windev.h", "aygshell.h"}),
    ("Virtual Memory / Memory Manager", {
        "winbase.h", "heapapi.h", "memoryapi.h", "winnt.h"}),
    ("File System", {
        "winbase.h", "winioctl.h", "extfile.h", "storemgr.h", "fatutil.h",
        "fsdmgr.h", "winfile.h", "scard.h", "pfile.h"}),
    ("Storage Manager", {
        "storemgr.h", "storeapi.h", "partition.h", "fatutil.h", "diskio.h",
        "scandisk.h", "formatdisk.h", "defragdisk.h", "fatfs.h", "pstore.h"}),
    ("Device Manager / Notifications", {
        "windev.h", "notify.h", "notifext.hxx", "notifext.cxx", "pwinbase.h",
        "aygshell.h", "msgqueue.h", "pm.h"}),
    ("Registry", {
        "winreg.h", "regext.h", "pwinreg.h", "ceguid.h"}),
    ("Synchronization", {
        "winbase.h", "winnt.h", "syncapi.h"}),
    ("Kernel / System Information", {
        "winnt.h", "windows.h", "kernel.h", "cecap.h", "sysinfo.h",
        "profiler.h", "nkfuncs.h", "winperf.h"}),
    ("Power Management", {
        "pm.h", "pwinbase.h", "batmgr.h", "gx.h", "powerstatus.h"}),
    ("Winsock", {
        "winsock.h", "winsock2.h", "ws2tcpip.h", "iphlpapi.h", "ws2spi.h",
        "nspapi.h", "af_irda.h", "wspiapi.h", "connmgr.h", "connmgr_status.h",
        "autoras.h", "lt2pcfg.h", "wzcsapi.h", "netui.h", "ppp.h"}),
    ("WinInet / URLMon", {
        "wininet.h", "urlmon.h", "shlwapi.h", "mshtml.h", "mshtmhst.h",
        "mshtmcid.h", "shdocvw.h", "exdisp.h"}),
    ("User / Window Manager", {
        "winuser.h", "windowsx.h", "commctrl.h", "pcommctrl.h", "wingdi.h",
        "pwinuser.h", "gdi.hpp", "scrollview.hpp", "nclientview.hpp",
        "buttonview.hpp", "toolbarview.hpp", "statctlview.hpp",
        "gwebypasscoredllthunk.hpp", "imm.h", "winuserp.h", "kato.h",
        "aygshell.h", "winmgr.h"}),
    ("COM / OLE", {
        "objbase.h", "objidl.h", "ole2.h", "oleauto.h", "unknwn.h", "objbase.h,",
        "combase.h", "olectl.h", "oleidl.h", "propidl.h", "shobjidl.h",
        "servprov.h", "wtypes.h", "rpc.h", "rpcndr.h", "uuid.h", "cccommon.idl"}),
    ("Multimedia", {
        "mmsystem.h", "dsound.h", "dshow.h", "dmusics.h", "mediaqueryengine.hpp",
        "wmdrm10nd.h", "drmoutputleveltypes.h", "wfmtmidi.h", "ddkmapi.h",
        "vfw.h", "mmisc.h", "waveform.h"}),
    ("Shell", {
        "shlobj.h", "shellcb.h", "aygshell.h", "shlobj.h,", "startui.h",
        "ceshell.h", "netui.h", "tileproxy.h", "controldefinitions.h"}),
    ("Bluetooth", {
        "bthapi.h", "bt_api.h", "bthutil.h", "bt_hcip.h", "bt_buffer.h",
        "btdrt.h", "bt_sdp.h", "ws2bth.h", "bthdef.h", "bt_ddi.h"}),
    ("IrDA", {
        "af_irda.h", "irda.h", "winsock2.h"}),
    ("Telephony", {
        "tapi.h", "tsp.h", "unimodem.h", "extapi.h", "astdtapi.h", "phoneapi.h",
        "sms.h", "simtkit.h", "simmgr.h", "ccdatastore.h", "ril.h"}),
    ("RAS", {
        "ras.h", "raserror.h", "raseapif.h", "autoras.h", "lt2pcfg.h",
        "ppp.h", "rasdlg.h"}),
    ("DirectDraw / DDraw", {
        "ddraw.h", "ddrawi.h", "d3dm.h", "d3dmx.h", "d3dmtypes.h", "ddkmapi.h",
        "d3dmddk.h"}),
    ("XAML (Silverlight for CE)", {
        "xamlruntime.h", "xrplatform.h", "xrcompositor.h"}),
    ("RTC / VoIP", {
        "rtccore.h", "rtcapi.h", "voip.h", "voipinterfaces.h",
        "voiperrorcodes.h", "sdpdiscovery.h"}),
    ("PIM / Pocket Outlook", {
        "pimstore.h", "pimmgr.h", "poutlook.h", "iexchangeclient.h",
        "ccdatastore.h", "cesync.h", "rapi.h", "rapi2.h", "rapitypes.h",
        "rapitypes2.h"}),
    ("Web Services for Devices (WSD)", {
        "wsdapi.h", "wsdattachment.h", "wsdbase.h", "wsdxml.h"}),
    ("Crypto", {
        "wincrypt.h", "certmod.h", "cecertmod.h", "crypt32.h", "wintrust.h",
        "loadauth.h"}),
    ("UPnP / SOAP / XML", {
        "upnp.h", "av_upnp.h", "mssoap.h", "msxml2.h", "mstsax.h", "msxmldom.h",
        "snmp.h", "winldap.h", "mlang.h"}),
    ("Multimedia (DirectShow / DVD / DMO)", {
        "dvdata.h", "dvdnav.h", "dvddrvr.idl", "dmo.h", "amvideo.h", "strmif.h",
        "uuids.h", "edevdefs.h", "il21dec.h", "vpconfig.h"}),
    ("Message Queue", {
        "mq.h", "mqoai.h", "msgqueue.h"}),
    ("IME / Uniscribe / Imaging", {
        "msime.h", "imjpskin.h", "usp10.h", "imaging.h", "imm.h", "coreimm.h",
        "wingdi.h"}),
    ("Wireless / 802.11", {
        "windot11.h", "wzcsapi.h", "eapol.h", "ndistapi.h", "ntddndis.h"}),
    ("Device Drivers (DDI, user-mode side)", {
        "winddi.h", "usbdi.h", "ddgpe.h", "ddstream.h", "d3dmddk.h",
        "nkintr.h", "pnp.h", "usbfntypes.h"}),
    ("Strings / Safe CRT wrappers", {
        "strsafe.h", "sphelper.h", "sapilib.h", "sapi.h", "sapiddk.h"}),
])

# A header can serve several areas: winbase.h carries Process, Virtual
# Memory, Synchronization and Power declarations, and attributing it to one
# area made the other three report zero.  So a name counts in every area
# whose set names its header.  The column totals are therefore not a
# partition of the corpus -- the per-name list under each area is what to
# read, and a name that belongs to two areas appears in both on purpose.
HDR2AREAS = collections.defaultdict(list)
for _area, _hs in AREAS.items():
    for _h in _hs:
        if _area not in HDR2AREAS[_h.rstrip(",")]:
            HDR2AREAS[_h.rstrip(",")].append(_area)


def requirements(raw):
    """(header, library, os_versions) from a page's Requirements block."""
    m = re.search(r'id="requirements"(.*?)(?:</table>|</p>)', raw, re.S)
    if not m:
        return None, None, None
    t = re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", m.group(1))))
    def g(k):
        mm = re.search(k + r"\s+([^ ]+)", t)
        return mm.group(1).strip(".") if mm else None
    osv = re.search(r"(Windows (?:Embedded )?CE[^A-Z]{0,60})", t)
    return (g("Header"), g("Library"), osv.group(1).strip() if osv else None)


KIND = re.compile(r"^(?P<n>.+?)\s+(Function|Functions|Structure|Structures|"
                  r"Constants?|Messages?|Macro|Macros|Enumeration|Values|"
                  r"Callback Function|Method|Methods|Interface|Interfaces)$")


def api_name(title):
    m = KIND.match(title)
    return m.group(1).strip() if m else title


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--corpus", default="/home/user/wince-docs-corpus")
    ap.add_argument("--md", default="docs/area-coverage.md")
    ap.add_argument("--json", default="build/area-audit.json")
    a = ap.parse_args()

    dirs = []
    if os.path.isdir(a.corpus):
        for d in sorted(os.listdir(a.corpus)):
            p = os.path.join(a.corpus, d)
            if os.path.isdir(p) and d not in ("catalogs", ".git"):
                dirs.append(p)
    for d in ("build/pagesgap2", "build/pagesmember"):
        p = os.path.join(ROOT, d)
        if os.path.isdir(p):
            dirs.append(p)

    declared = dfp.declared_in_tree()
    OEM = ca.OEM
    per = collections.defaultdict(lambda: {"documented": 0, "declared": 0,
                                           "undeclared": [], "headers": collections.Counter()})
    unmapped = collections.Counter()
    unmapped_names = collections.defaultdict(list)
    seen = set()
    scanned = 0
    for d in dirs:
        for f in sorted(os.listdir(d)):
            if not f.endswith(".html"):
                continue
            scanned += 1
            raw = open(os.path.join(d, f), encoding="utf-8", errors="replace").read()
            hdr, lib, osv = requirements(raw)
            if not hdr:
                continue
            hdr = hdr.lower().rstrip(",")
            if hdr in OEM or hdr == "developer":
                continue
            t = re.search(r"<title>(.*?)</title>", raw, re.S)
            title = html.unescape(t.group(1)).split(" (Windows")[0].strip() if t else f[:-5]
            name = api_name(title)
            key = (name, hdr)
            if key in seen:
                continue
            seen.add(key)
            areas = HDR2AREAS.get(hdr)
            if not areas:
                if hdr.strip(":"):
                    unmapped[hdr] += 1
                    unmapped_names[hdr].append(name)
                continue
            for area in areas:
                b = per[area]
                b["documented"] += 1
                b["headers"][hdr] += 1
                if name in declared:
                    b["declared"] += 1
                else:
                    b["undeclared"].append({"name": name, "header": hdr,
                                            "lib": (lib or ""), "page": f[:-5]})

    print("pages scanned: %d | areas: %d" % (scanned, len(per)))
    print("headers not mapped to any area: %d (%d names)"
          % (len(unmapped), sum(unmapped.values())))

    lines = ["# Area coverage -- what each functional area's own pages say",
             "",
             "Generated by `tools/area-audit.py`.  Areas are keyed by the",
             "`Header:` row of each page's Requirements block, not by filename,",
             "so an area's numbers come from the archive itself.  A header that",
             "serves several areas (winbase.h serves Process, Virtual Memory,",
             "Synchronization and Power) is counted in each of them, so the",
             "columns are not a partition.  OEM, BSP,",
             "OAL and driver headers are excluded by the project's standing",
             "scope rule.  A name counts as declared when `include/` declares",
             "it (`decl-from-pages.py:declared_in_tree`).",
             "",
             "| area | documented | declared | undeclared |",
             "|---|---|---|---|"]
    for area in AREAS:
        b = per.get(area)
        if not b:
            lines.append("| %s | 0 | 0 | 0 |" % area)
            continue
        lines.append("| %s | %d | %d | %d |"
                     % (area, b["documented"], b["declared"], len(b["undeclared"])))
    lines += ["", "## Undeclared names by area", ""]
    for area in AREAS:
        b = per.get(area)
        if not b or not b["undeclared"]:
            continue
        lines.append("### %s (%d)" % (area, len(b["undeclared"])))
        lines.append("")
        for u in sorted(b["undeclared"], key=lambda x: (x["header"], x["name"])):
            lines.append("- `%s` -- %s%s (page %s)"
                         % (u["name"], u["header"],
                            ", " + u["lib"] if u["lib"] else "", u["page"]))
        lines.append("")
    if unmapped:
        lines += ["## Headers not mapped to any area", "",
                  "These carry documented names this report does not place.  "
                  "Add them to `AREAS` rather than leaving them uncounted.", ""]
        for h, n in unmapped.most_common():
            lines.append("- `%s` -- %d names, e.g. %s"
                         % (h, n, ", ".join(unmapped_names[h][:6])))
        lines.append("")

    md = a.md if os.path.isabs(a.md) else os.path.join(ROOT, a.md)
    open(md, "w", encoding="utf-8").write("\n".join(lines))
    js = a.json if os.path.isabs(a.json) else os.path.join(ROOT, a.json)
    os.makedirs(os.path.dirname(js), exist_ok=True)
    json.dump({"areas": {k: {"documented": v["documented"], "declared": v["declared"],
                             "undeclared": v["undeclared"]} for k, v in per.items()},
               "unmapped": dict(unmapped)},
              open(js, "w", encoding="utf-8"), indent=1)
    print("wrote %s and %s" % (md, js))


if __name__ == "__main__":
    main()
