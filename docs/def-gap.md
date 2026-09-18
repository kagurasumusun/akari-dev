# Link libraries documented by the corpus, and the .def situation

Generated 2026-09-19 (after the def restructure; per-name ledger in
`docs/def-restructure-2026-09-19.tsv`).

Full-corpus scan: 95288 pages name **283**
distinct `Link Library:` / `Library:` / `Link to:` values.
**70** import libraries are shipped in `def/`.

## Scope note (owner ruling 2026-09-19)

Akari-dev carries the **minimum** Windows CE API surface needed to build CE
applications (the "-dev package" of the CE SDK).  OAK / BSP / driver / kernel
import libraries are **out of scope** and intentionally have no `.def`.

## Shipped (70)

`acmdwrap.lib`, `autodial.lib`, `aygshell.lib`, `btagsvc.lib`, `btagsvc_network.lib`, `btagsvc_phoneext.lib`, `btd.lib`, `btdrt.lib`, `cellcore.lib`, `ceshell.lib`, `ceutil.lib`, `chsime03.lib`, `commctrl.lib`, `commdlg.lib`, `coredll.lib`, `crypt32.lib`, `ctblt.lib`, `d3dm.lib`, `ddraw.lib`, `dnsapi.lib`, `dsound.lib`, `fwapi.lib`, `gpsapi.lib`, `hwxcht.lib`, `hwxjpn.lib`, `hwxkor.lib`, `hwxusa.lib`, `imejpp.lib`, `iphlpapi.lib`, `ipsec_api.lib`, `mlang.lib`, `msdmo.lib`, `msmqrt.lib`, `mstsax.lib`, `ndis.lib`, `netapi32.lib`, `netui.lib`, `ntlmssp.lib`, `ole32.lib`, `oleaut32.lib`, `p2p.lib`, `phcommon.lib`, `pimstore.lib`, `rapi.lib`, `sapilib.lib`, `schedlog.lib`, `sdcardlib.lib`, `secur32.lib`, `serial.lib`, `shellcb.lib`, `sideshowapi.lib`, `smbconfig.lib`, `sms.lib`, `snmp.lib`, `snmpapi.lib`, `splusa.lib`, `storeapi.lib`, `strsafe.lib`, `toolhelp.lib`, `touchgesture.lib`, `upnpcapi.lib`, `urlmon.lib`, `uspce.lib`, `wap.lib`, `wininet.lib`, `winscard.lib`, `wldap32.lib`, `ws2.lib`, `wsdapi.lib`, `wzcsapi.lib`

## No .def, by category (213)

### coredll/gwes components -- covered by coredll-doc.def (58)

Documented as static components of coredll.dll (Module pages ms923451,
aa448387, ee482607, ee482579, plus dual "Coredll.lib, <Component>.lib"
rows such as Ole232.lib / Mmtimer.lib).  The SDK shipped separate
import libraries for these components, but the exports live in
coredll.dll, so coredll-doc.def carries them (DOC-COMPONENT class,
grouped by component library).

| `coreimm.lib` | 223 |
| `coreloc.lib` | 162 |
| `imgctl.lib` | 96 |
| `ole232.lib` | 87 |
| `winmgr.lib` | 57 |
| `dlgmgr.lib` | 54 |
| `cursor.lib` | 53 |
| `mcursor.lib` | 53 |
| `menu.lib` | 51 |
| `serdev.lib` | 48 |
| `clipbd.lib` | 42 |
| `caret.lib` | 36 |
| `rectapi.lib` | 35 |
| `mgprint.lib` | 26 |
| `icon.lib` | 24 |
| `kbdui.lib` | 23 |
| `mgdraw.lib` | 20 |
| `coremain.lib` | 19 |
| `mmtimer.lib` | 18 |
| `msgque.lib` | 17 |
| `accel.lib` | 17 |
| `mgrgn.lib` | 14 |
| `mgbase.lib` | 14 |
| `wmgr_c.lib` | 14 |
| `foregnd.lib` | 12 |
| `sbcmn.lib` | 12 |
| `iconcurs.lib` | 12 |
| `lmem.lib` | 12 |
| `coresip.lib` | 10 |
| `notify.lib` | 9 |
| `mgtt.lib` | 8 |
| `uibase.lib` | 8 |
| `mgpal.lib` | 7 |
| `mgrast.lib` | 6 |
| `fileopen.lib` | 6 |
| `accel_c.lib` | 5 |
| `shmisc.lib` | 4 |
| `mgdc.lib` | 4 |
| `wmbase.lib` | 4 |
| `nclient.lib` | 3 |
| `drawmbar.lib` | 3 |
| `mgrast2.lib` | 3 |
| `mgblt2.lib` | 3 |
| `hotkey.lib` | 3 |
| `fmtmsg.lib` | 3 |
| `loadbmp.lib` | 3 |
| `loadimg.lib` | 3 |
| `loadstr.lib` | 3 |
| `msgbeep.lib` | 3 |
| `msgbox.lib` | 3 |
| `shortcut.lib` | 2 |
| `locusa.lib` | 2 |
| `mgbitmap.lib` | 2 |
| `mgdi_c.lib` | 2 |
| `mgblt.lib` | 1 |
| `mgdibsec.lib` | 1 |
| `mgdrwtxt.lib` | 1 |
| `mgwinmgr.lib` | 1 |

### OAK / BSP / driver / kernel / system stack -- out of scope by policy (78)

| library | pages citing |
| --- | --- |
| `ddvdids.lib` | 707 |
| `ril.lib` | 322 |
| `osaxsc.lib` | 305 |
| `nk.lib` | 274 |
| `ndislib.lib` | 213 |
| `fsdmgr.lib` | 191 |
| `kato.lib` | 165 |
| `ceddk.lib` | 164 |
| `ddgpe.lib` | 156 |
| `ddi_gx_lib.lib` | 107 |
| `ddi_ati_lib.lib` | 107 |
| `ddi_nop_lib.lib` | 107 |
| `ddi_flat_lib.lib` | 107 |
| `ddi_rgx_lib.lib` | 107 |
| `ddi_rflat_lib.lib` | 107 |
| `ddi_tvia5_lib.lib` | 107 |
| `ddi_mq200_lib.lib` | 107 |
| `oemmain.lib` | 97 |
| `oemmain_statickitl.lib` | 97 |
| `blcommon.lib` | 80 |
| `pcc_serv.lib` | 80 |
| `hidparse_lib.lib` | 78 |
| `kitl.lib` | 64 |
| `nkstub.lib` | 61 |
| `rtcdll.lib` | 58 |
| `hal.lib` | 57 |
| `cardserv.lib` | 53 |
| `stressutils.lib` | 50 |
| `gpe_lib.lib` | 41 |
| `ppp.lib` | 40 |
| `layoutmanager.lib` | 40 |
| `wavelib.lib` | 37 |
| `fsdbase.lib` | 30 |
| `kitldll.lib` | 28 |
| `fatutil.lib` | 27 |
| `ddi_perm3_lib.lib` | 27 |
| `tchmdd.lib` | 24 |
| `lfapi.lib` | 24 |
| `tlkitl.lib` | 22 |
| `tlcesrv.lib` | 22 |
| `tcpip.lib` | 22 |
| `sdhclib.lib` | 22 |
| `bootpart.lib` | 21 |
| `tchmain.lib` | 20 |
| `rts.lib` | 20 |
| `loadauth.lib` | 20 |
| `fsmain.lib` | 16 |
| `gdcfg.lib` | 15 |
| `kbdhid_lib.lib` | 12 |
| `mouhid_lib.lib` | 12 |
| `conshid_lib.lib` | 12 |
| `nleddrv.lib` | 12 |
| `dwdmptxt.lib` | 12 |
| `fsreg.lib` | 11 |
| `redir.lib` | 11 |
| `nkprof.lib` | 10 |
| `device.lib` | 9 |
| `ddvduuid.lib` | 8 |
| `tileenginerenderplugin.lib` | 8 |
| `ethdbg.lib` | 6 |
| `avc_unit.lib` | 6 |
| `pcireg.lib` | 6 |
| `dwconn.lib` | 6 |
| `edbg.lib` | 5 |
| `cefnk.lib` | 5 |
| `3c90xdbg.lib` | 5 |
| `devmain.lib` | 4 |
| `drm_nd_oem.lib` | 4 |
| `pmstub.lib` | 4 |
| `tch_cal.lib` | 3 |
| `nkmain.lib` | 2 |
| `corelibc.lib` | 2 |
| `dmamdd.lib` | 2 |
| `fspass.lib` | 1 |
| `afd.lib` | 1 |
| `ipsecsvc.lib` | 1 |
| `usbd_lib.lib` | 1 |
| `usbd.lib` | 1 |

### CRT debug/release variants -- covered by the coredll CRT component (6)

Pages cite these for debug-build links; the CRT itself is a documented
coredll component (Ccrtrtti.lib / Fullcrt.lib / Lmem.lib).

| `msvcrt.lib` | 2 |
| `libcmt.lib` | 2 |
| `libcmtd.lib` | 2 |
| `libcd.lib` | 2 |
| `msvcrtd.lib` | 2 |
| `libc.lib` | 2 |

### GUID-only (pages print IIDs, not function exports; a .def would be wrong) (8)

| library | pages citing |
| --- | --- |
| `uuid.lib` | 3485 |
| `voipguid.lib` | 250 |
| `d3dmguid.lib` | 210 |
| `rapiuuid.lib` | 192 |
| `dmoguid.lib` | 126 |
| `wvuuid.lib` | 68 |
| `dmoguids.lib` | 3 |
| `strmiids.lib` | 2 |

### COM / vtable / engine (interface method tables, no plain-C export set;
pending a COM-surface decision -- out of the minimum-app-scope for now) (12)

| library | pages citing |
| --- | --- |
| `av_upnp.lib` | 284 |
| `mqelib.lib` | 186 |
| `mqoa.lib` | 140 |
| `dmusic.lib` | 134 |
| `shdocvw.lib` | 132 |
| `d3d8.lib` | 131 |
| `imaging.lib` | 130 |
| `d3dmx.lib` | 96 |
| `owaexchangeclient.lib` | 73 |
| `tileengine.lib` | 44 |
| `d3dx8.lib` | 38 |
| `mshtml.lib` | 37 |

### Small CE DLLs with documented plain exports -- no .def yet (51)

The only in-scope-and-missing category: real, app-linkable system DLLs.
`icmplib.lib` is covered -- its 5 Icmp* exports were merged into
iphlpapi-doc.def (documented Icmplib.lib in CE5, Iphlpapi.lib in CE6).
Add a `.def` for the rest when an application target actually links one
(same doc-derivation rules as the shipped set).

| library | pages citing |
| --- | --- |
| `cecap.lib` | 32 |
| `cryptapi.lib` | 31 |
| `commctl.lib` | 22 |
| `pspubsubce.lib` | 20 |
| `cardea_wince.lib` | 18 |
| `schannel.lib` | 16 |
| `wmdrm10nd.lib` | 16 |
| `devshl.lib` | 14 |
| `icmplib.lib` | 12 |
| `mixerapi.lib` | 10 |
| `httpfilt.lib` | 8 |
| `dwui.lib` | 8 |
| `ietheme.lib` | 8 |
| `wininetui.lib` | 6 |
| `user32.lib` | 5 |
| `com.lib` | 5 |
| `aspcolct.lib` | 5 |
| `strmbase.lib` | 5 |
| `commctrlview.lib` | 5 |
| `ufnclientlibbase.lib` | 4 |
| `bthns.lib` | 4 |
| `cefobj.lib` | 4 |
| `d3dhook.lib` | 4 |
| `acmobj.lib` | 4 |
| `msimeuic.lib` | 4 |
| `msdxm.lib` | 4 |
| `acmwrap.lib` | 4 |
| `aygutils.lib` | 4 |
| `addrstor.lib` | 4 |
| `bthutil.lib` | 4 |
| `certmod.lib` | 4 |
| `quartz.lib` | 3 |
| `urlmonui.lib` | 3 |
| `getpower.lib` | 2 |
| `httpextn.lib` | 2 |
| `multibox.lib` | 2 |
| `mskana.lib` | 2 |
| `ddbtn.lib` | 2 |
| `ptt.lib` | 2 |
| `stub_ce.lib` | 2 |
| `ptv.lib` | 2 |
| `ptlv.lib` | 2 |
| `imeskdic.lib` | 2 |
| `msradlist.lib` | 2 |
| `plv.lib` | 2 |
| `autoshape.lib` | 2 |
| `waveapi.lib` | 1 |
| `httpasp.lib` | 1 |
| `wapiwave.lib` | 1 |
| `imap4.lib` | 1 |
| `asform.lib` | 1 |
