# Makefile for the Akari API (wince-api)
#
# Copyright (c) 2026 Akari API contributors
# SPDX-License-Identifier: MIT

CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -Wshadow -Wstrict-prototypes
STD      = -std=c11
INCLUDES = -Iinclude

# CE deployment versions checked on the host (types/syntax only; the
# 32-bit pointer model is verified with the CE toolchain, see
# docs/verification.md).
CE_VERSIONS = 0x420 0x500 0x600

HDRS = \
include/Acmdrv.h \
include/Advbacklight.h \
include/Af_irda.h \
include/Autodial.h \
include/Autoras.h \
include/Av_upnp.h \
include/Avc_stream.h \
include/Avc_unit.h \
include/Avc_vcr.h \
include/Avc_vvcr.h \
include/aygshell.h \
include/Bt_api.h \
include/bt_ddi.h \
include/Bt_hcip.h \
include/Btagnetwork.h \
include/Btagpub.h \
include/Bthapi.h \
include/Bthid.h \
include/Bthsdpdef.h \
include/Calibrui.h \
include/Cchannel.h \
include/Cdioctl.h \
include/Ce_setup.h \
include/CEDDK.h \
include/Celog.h \
include/Cesync.h \
include/Ceutil.h \
include/Comcat.h \
include/Commctrl.h \
include/Commdlg.h \
include/Console.h \
include/Cpl.h \
include/Cred.h \
include/Cred_prov.h \
include/Credmgr.h \
include/Ctblt.h \
include/D3dm.h \
include/D3dmcaps.h \
include/D3dmddk.h \
include/D3dmtypes.h \
include/Dccole.h \
include/Ddraw.h \
include/Ddvdata.h \
include/Devmgmt.h \
include/Dinput.h \
include/Discodlg.h \
include/Diskio.h \
include/Dmo.h \
include/Dmodshow.h \
include/Dmoimpl.h \
include/Dmoreg.h \
include/Docobj.h \
include/Dsgetdc.h \
include/Dshow.h \
include/Dsound.h \
include/Dvdata.h \
include/dvdcss.h \
include/Dvddata.h \
include/dvddrvr.h \
include/Dvdioctl.h \
include/dvdmedia.h \
include/Dvdnav.h \
include/Dvp.h \
include/ErrorRep.h \
include/Excpt.h \
include/Externs.h \
include/Extfile.h \
include/Fatui.h \
include/Fwapi.h \
include/getdeviceuniqueid.h \
include/Gwebypasscoredllthunk.hpp \
include/Htmlctrl.h \
include/Httpext.h \
include/Httpfilt.h \
include/IAccess.h \
include/Icmpapi.h \
include/IExchangeClient.h \
include/Iltiming.h \
include/Imaging.h \
include/Imjpskin.h \
include/Imm.h \
include/Interned.h \
include/Ipexport.h \
include/Iphlpapi.h \
include/Iprtrmib.h \
include/Ipsec_api.h \
include/Iptypes.h \
include/Kernel.h \
include/Kfuncs.h \
include/Koreanimeui.h \
include/Lap.h \
include/Lass.h \
include/Loadauth.h \
include/Mlang.h \
include/Mmsystem.h \
include/Mq.h \
include/Mqmgmt.h \
include/Mqoai.h \
include/Msacmdrv.h \
include/Msgqueue.h \
include/Mshtmhst.h \
include/Mshtml.h \
include/Msime.h \
include/Msimeui.h \
include/Mspyime.h \
include/Mssoap.h \
include/Msxml2.h \
include/Mwinreg.h \
include/Natedit.h \
include/Netui.h \
include/newmenu.h \
include/Nkarm.h \
include/Notify.h \
include/Ntlmssp.h \
include/Nuiouser.h \
include/Oaidl.h \
include/Obex.h \
include/Objbase.h \
include/Objidl.h \
include/Objsafe.h \
include/Ocidl.h \
include/Oleauto.h \
include/Olectl.h \
include/Oleidl.h \
include/Oomui.h \
include/p2p.h \
include/Pcommctr.h \
include/Pcommctrl.h \
include/Pegdser.h \
include/Pimstore.h \
include/Playlist.h \
include/pm.h \
include/pnrpdef.h \
include/pnrpns.h \
include/Prnport.h \
include/Proxy.h \
include/Prsht.h \
include/Psapi.h \
include/Pwinbase.h \
include/Pwindbas.h \
include/Pwingdi.h \
include/Pwinreg.h \
include/Pwinuser.h \
include/Rapi.h \
include/Rapitypes.h \
include/Ras.h \
include/Raseapif.h \
include/Recog.h \
include/Remoteui.h \
include/Replfilt.h \
include/Routprot.h \
include/Rpcdce.h \
include/Rules.h \
include/Sapi.h \
include/Sapiddk.h \
include/Schnlsp.h \
include/Sdcard.h \
include/Sdkddkver.h \
include/Service.h \
include/Shellapi.h \
include/Shellcb.h \
include/shellsdk.h \
include/Shelwapi.h \
include/shintr.h \
include/Shlobj.h \
include/Shobjidl.h \
include/Shtypes.h \
include/sideshow.h \
include/Sip.h \
include/Sipapi.h \
include/Smbconfig.h \
include/Smcce.h \
include/Smclib.h \
include/Snmp.h \
include/Snmpapi.h \
include/Snmpexts.h \
include/Sockserv.h \
include/Socksv2.h \
include/Sphelper.h \
include/Splapi.h \
include/Sspi.h \
include/Startui.h \
include/Storemgr.h \
include/Streams.h \
include/strmif.h \
include/Tapi.h \
include/Tapicomn.h \
include/Tchar.h \
include/Tchaud.h \
include/Tlhelp32.h \
include/Tuple.h \
include/Tvout.h \
include/Unimodem.h \
include/Unknwn.h \
include/Upnp.h \
include/Upnpdevapi.h \
include/Upnphost.h \
include/Urlmon.h \
include/Urlmonui.h \
include/Usb100.h \
include/Usbclient.h \
include/Usbmsc.h \
include/Usbtypes.h \
include/Usp10.h \
include/Uxtheme.h \
include/Voipconfigurationdatastore.h \
include/Voiperrorcodes.h \
include/Voiplap.h \
include/Voipmanager.h \
include/Webproxy.h \
include/webvw.h \
include/Winbase.h \
include/Winber.h \
include/Wincrypt.h \
include/Windbase.h \
include/Windef.h \
include/Windev.h \
include/Windns.h \
include/Windot11.h \
include/Windows.h \
include/Windowsx.h \
include/winerror.h \
include/Wingdi.h \
include/Wininet.h \
include/Wininetui.h \
include/Winldap.h \
include/Winnetwk.h \
include/Winnls.h \
include/Winnt.h \
include/Winreg.h \
include/Winscard.h \
include/Winsmcrd.h \
include/Winsock2.h \
include/Winuser.h \
include/Winver.h \
include/Ws2bth.h \
include/Ws2spi.h \
include/Ws2tcpip.h \
include/Wtypes.h \
include/Wzcsapi.h


# OAK/DDK layer (2026-09-14 split): OEM Adaptation Kit / driver-level
# headers (interrupt/OAL, display/DirectDraw driver internals, storage
# and bus drivers, HID/keyboard PDD, NDIS miniport, audio drivers, power
# manager driver hooks, kernel/KITL). These are NOT part of the
# application "-dev" surface (see docs audit 2026-09-14) and are kept
# out of HDRS/the default install so that a plain app-developer sysroot
# never needs -Iinclude/oak. A small, documented set of app-facing
# headers still reach into this layer for leaked driver-domain types
# (Winuser.h/Pwinuser.h -> oak/Keybd.h for KEY_STATE_FLAGS;
# Externs.h/Nuiouser.h -> oak/Ndis.h for NDIS_HANDLE/NDIS_STATUS/NDIS_OID;
# Voipmanager.h -> oak/Rtccore.h for RTCSS_* session states); those three
# oak/ headers are therefore always installed even when OAK_HDRS itself
# is not requested. TODO: wire OAK_HDRS into check/e2e once a BSP/driver
# consumer exists to validate against (tracked in the 2026-09-14 audit).
OAK_HDRS = \
include/oak/Armintr.h \
include/oak/Atapi2.h \
include/oak/Battery.h \
include/oak/Battimpl.h \
include/oak/Blcommon.h \
include/oak/Cardserv.h \
include/oak/Cardsv2.h \
include/oak/Cmnintr.h \
include/oak/Cmnintrin.h \
include/oak/Dbgapi.h \
include/oak/Ddgpe.h \
include/oak/Ddhal.h \
include/oak/Ddkreg.h \
include/oak/Ddrawi.h \
include/oak/Ddrawip.h \
include/oak/Devload.h \
include/oak/DwCeDump.h \
include/oak/Ethdbg.h \
include/oak/Fmd.h \
include/oak/Fsdmgr.h \
include/oak/Giisr.h \
include/oak/Gpe.h \
include/oak/Halether.h \
include/oak/Hcdddsi.h \
include/oak/Hiddi.h \
include/oak/Hidparse.h \
include/oak/Hidpddi.h \
include/oak/Hidpi.h \
include/oak/Keybd.h \
include/oak/Keybddr.h \
include/oak/Keybdpdd.h \
include/oak/Kitl.h \
include/oak/Kitltran.h \
include/oak/Led_drvr.h \
include/oak/Lockmgr.h \
include/oak/Lockmgrhelp.h \
include/oak/Lockmgrtypes.h \
include/oak/Mipsintr.h \
include/oak/Mmddk.h \
include/oak/Ndis.h \
include/oak/Ndistapi.h \
include/oak/Nkintr.h \
include/oak/Nled.h \
include/oak/Ntcompat.h \
include/oak/Ntddndis.h \
include/oak/Oalintr.h \
include/oak/Oemwake.h \
include/oak/Partdrv.h \
include/oak/PCIbus.h \
include/oak/PCIReg.h \
include/oak/PCIrsrc.h \
include/oak/Pkfuncs.h \
include/oak/Pmimpl.h \
include/oak/Pmpolicy.h \
include/oak/Profiler.h \
include/oak/Rndis.h \
include/oak/Rndismini.h \
include/oak/Romldr.h \
include/oak/Rtccore.h \
include/oak/Schedlog.h \
include/oak/Sdcardddk.h \
include/oak/Sdmem.h \
include/oak/Serhw.h \
include/oak/Tchddi.h \
include/oak/Tchddsi.h \
include/oak/Usbdi.h \
include/oak/Usbfntypes.h \
include/oak/Waveddsi.h \
include/oak/Wavedev.h \
include/oak/Wavemdd.h \
include/oak/Wdm.h \
include/oak/Winddi.h

.PHONY: check hostcheck defcheck defdoc e2e clean

check: hostcheck defcheck

# defdoc regenerates def/*-doc.def from build/rows.json, the record set
# harvested from the official CE documentation pages by tools/ce-fetch.py
# (Requirement rows of the (v=msdn.10) archive).  tools/gen-doc-def.py
# only lists names that both (a) appear on a harvested page whose
# documented Link Library row names the DLL and (b) are declared as
# exports by these headers.  No shared-source, device-dump, VS or
# Platform Builder material is an input.
defdoc:
	@test -f build/rows.json || { echo "build/rows.json missing: run \
tools/ce-fetch.py on tools/manifests/core-*.manifest first" >&2; exit 1; }
	python3 tools/gen-doc-def.py

# defcheck validates the committed doc-derived defs (one per documented
# Link Library token, e.g. coredll-doc.def, coreloc-doc.def,
# toolhelp-doc.def, lmem-doc.def, loadstr-doc.def).
defcheck:
	@ok=1; found=0; \
	for f in def/*-doc.def; do \
	  [ -e "$$f" ] || continue; found=1; \
	  n=$$(awk '/^EXPORTS/{e=1;next} e && NF && $$0 !~ /^[;#]/' "$$f" | wc -l); \
	  echo "[defcheck] $$f: $$n exports"; \
	  [ $$n -gt 0 ] || { echo "def $$f looks empty" >&2; ok=0; }; \
	done; \
	if [ $$found -eq 0 ]; then \
	  echo "[defcheck] missing def/*-doc.def (run 'make defdoc')" >&2; \
	  exit 1; \
	fi; \
	[ $$ok -eq 1 ]

# Cross checks with the real Windows CE LLVM/Clang toolchain
# (kagurasumusun/llvm-project, branch LLVM-WinCE).  The driver is
# selected with WINCECLANG, e.g.:
#   make crosscheck WINCECLANG=/path/to/wince-clang/bin/clang
# Compilation is freestanding against an empty sysroot so that only
# these headers (never host or CeGCC libc headers) are exercised.
WINCECLANG ?=
CE_TRIPLES = arm-pc-wince4.2 arm-pc-wince5.0 arm-pc-wince6.0 \
             i386-pc-wince4.2 i386-pc-wince5.0 i386-pc-wince6.0

# Headers the freestanding crosscheck cannot compile by design.  Both
# are excluded explicitly (never silently) and are still compiled by
# `make hostcheck`, where the host's own headers/targets make them
# well-formed:
#   * include/Tchar.h -- tchar.h is the C run-time library's
#     generic-text header, not a Windows CE SDK header: no official CE
#     page carries "Header: Tchar.h" in its Requirements row.  Its
#     documented content (_tcslen/_tcscpy/... and the TCHAR mapping)
#     needs <wchar.h>/<string.h>, which are the CRT provider's
#     responsibility (see README "Scope" and the wince-crt split).
#   * include/oak/Mipsintr.h -- MIPS-only intrinsics: the page prints
#     declare the MIPS `_ReturnAddress`/`__ReturnAddress`, which clash
#     with the compiler builtin of the same name on ARM/x86.
CROSSCHECK_SKIP = include/Tchar.h include/oak/Mipsintr.h
CROSSCHECK_HDRS = $(filter-out $(CROSSCHECK_SKIP),$(HDRS))
CROSSCHECK_OAK  = $(filter-out $(CROSSCHECK_SKIP),$(OAK_HDRS))

crosscheck: $(HDRS) $(OAK_HDRS)
	@if [ -z "$(WINCECLANG)" ]; then \
	  echo "[crosscheck] set WINCECLANG to the WinCE clang binary" >&2; \
	  exit 2; \
	fi; \
	tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for t in $(CE_TRIPLES); do \
	  echo "[crosscheck] $$t skipping (documented): $(CROSSCHECK_SKIP)"; \
	  for h in $(CROSSCHECK_HDRS); do \
	    echo "[crosscheck] $$t standalone: $$h"; \
	    "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	      --sysroot=$$tmp -Wno-wince-sysroot-missing \
	      $(CFLAGS) -Werror -I include -I include/oak -include $$h \
	      -fsyntax-only -x c /dev/null || exit 1; \
	  done; \
	  for h in $(CROSSCHECK_OAK); do \
	    echo "[crosscheck] $$t standalone (oak): $$h"; \
	    "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	      --sysroot=$$tmp -Wno-wince-sysroot-missing \
	      $(CFLAGS) -Werror -I include -I include/oak -include $$h \
	      -fsyntax-only -x c /dev/null || exit 1; \
	  done; \
	  echo "[crosscheck] $$t TU"; \
	  "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	    --sysroot=$$tmp -Wno-wince-sysroot-missing \
	    $(CFLAGS) -Werror -I include -I include/oak -fsyntax-only \
	    tests/host/tu_compile.c || exit 1; \
	done; \
	echo "[crosscheck] OK -- $(words $(CE_TRIPLES)) WinCE targets"

hostcheck: $(HDRS) $(OAK_HDRS)
	@for v in $(CE_VERSIONS); do \
	  echo "[hostcheck] headers + TU under _WIN32_WCE=$$v"; \
	  cc $(STD) $(CFLAGS) -Werror -D_WIN32_WCE=$$v $(INCLUDES) -fsyntax-only \
	    tests/host/tu_compile.c || exit 1; \
	  for h in $(HDRS); do \
	    echo "  standalone: $$h"; \
	    cc $(STD) $(CFLAGS) -Werror -D_WIN32_WCE=$$v $(INCLUDES) \
	      -include $$h -fsyntax-only -x c /dev/null || exit 1; \
	  done; \
	  for h in $(OAK_HDRS); do \
	    echo "  standalone (oak): $$h"; \
	    cc $(STD) $(CFLAGS) -Werror -D_WIN32_WCE=$$v $(INCLUDES) \
	      -include $$h -fsyntax-only -x c /dev/null || exit 1; \
	  done; \
	done
	@echo "[hostcheck] OK -- headers compile warning-free for CE $(CE_VERSIONS)"

clean:
	rm -rf build

# End-to-end link checks: the doc-derived def files are turned into
# import libraries with llvm-dlltool (armwince for ARM, i386
# --no-leading-underscore for x86 -- the CE coredll x86 export
# surface is undecorated, the headers are pinned to it, see
# windef.h), and the tests/e2e consumers are linked with lld-link
# -wince against the Akari CRT (wince-crt) startup objects into PE
# images (main app / WinMain app / DLL).  The images' machine type,
# CE subsystem and coredll import names are asserted with
# llvm-readobj.
#   make e2e WINCECLANG=/path/to/clang CRTDIR=/path/to/wince-crt
#
# Toolchain adaptation (2026-09-10 LLVM-WinCE artifact, wince-llvm-
# 01c51ef / 10134447081; superseded 2026-09-11 by 5b8f2fb / artifact
# 10176580836 "[WinCE][ToolDrivers] Name a CE machine by its target,
# not an invented machine", b2851a3d): llvm-dlltool no longer knows the
# invented machine name "armwince" -- a CE machine is named by its
# target triple ("-m arm-pc-wince"; the machine-name table is i386/
# arm/arm64/... where "arm" means ARMNT).  The clang driver still
# answers a bare *-pc-wince ARM triple with the generic default CPU
# arm7tdmi (ARMv4T) -- the core is asked for by option (71f4db8c/
# 0583ffe45).  The ARM e2e objects are therefore pinned to
# -march=armv5tej to match the wince-crt build (its WCE_ARCHFLAGS)
# and keep the pipeline on the link-verified ARMv5TE codegen.
CRTDIR    ?= $(abspath $(CURDIR)/../wince-crt)

# M39 note: the M39 ws2 import assertions below resolve through ws2.dll (Ws2.lib
# per the official CE pages).
e2e:
	@if [ -z "$(WINCECLANG)" ]; then \
	  echo "[e2e] set WINCECLANG to the WinCE clang binary" >&2; \
	  exit 2; \
	fi; \
	if [ ! -f "$(CRTDIR)/src/crt/crt0.c" ]; then \
	  echo "[e2e] set CRTDIR to a wince-crt checkout (got $(CRTDIR))" >&2; \
	  exit 2; \
	fi; \
	bin=$$(dirname "$(WINCECLANG)"); \
	tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for t in $(CE_TRIPLES); do \
	  case $$t in arm*) dtf="-m arm-pc-wince"; march="-march=armv5tej"; mchk="IMAGE_FILE_MACHINE_ARM";; \
	             *)    dtf="-m i386 --no-leading-underscore"; march=""; mchk="IMAGE_FILE_MACHINE_I386";; \
	  esac; \
	  d=build/e2e/$$t; mkdir -p $$d; \
	  for f in def/*-doc.def; do \
	    b=$$(basename $$f .def); \
	    "$$bin/llvm-dlltool" $$dtf -d $$f -l $$d/$$b.lib >/dev/null || exit 1; \
	  done; \
  case $$t in arm*) crtarch="ARCHFLAGS=-march=armv5tej";; \
                   *)    crtarch="";; esac; \
  (cd "$(CRTDIR)" && make clean >/dev/null 2>&1 \
     && make TARGET=$$t CC=$$bin/clang AR=$$bin/llvm-ar $$crtarch >/dev/null 2>&1) || { \
    echo "[e2e] wince-crt build failed for $$t" >&2; exit 1; }; \
	  for s in e2e_console e2e_winmain e2e_module; do \
	    echo "[e2e] $$t compile: $$s"; \
	    "$(WINCECLANG)" -target $$t -std=c11 -ffreestanding \
	      --sysroot=$$tmp -Wno-wince-sysroot-missing $$march \
	      $(CFLAGS) -Werror -I include -I include/oak -c tests/e2e/$$s.c \
	        -o $$d/$$s.o || exit 1; \
	  done; \
	  echo "[e2e] $$t link: main app / WinMain app / DLL"; \
	  "$$bin/lld-link" -wince /subsystem:windowsce /entry:mainACRTStartup \
	    /base:0x10000 /fixed $$d/e2e_console.o \
	    "$(CRTDIR)/build/akari_crt0.o" "$(CRTDIR)/build/libakari.a" \
	    $$d/*.lib /out:$$d/e2e_console.exe 2>/dev/null || exit 1; \
	  "$$bin/lld-link" -wince /subsystem:windowsce /entry:WinMainCRTStartup \
	    /base:0x10000 /fixed $$d/e2e_winmain.o \
	    "$(CRTDIR)/build/akari_crt0.o" "$(CRTDIR)/build/libakari.a" \
	    $$d/*.lib /out:$$d/e2e_winmain.exe 2>/dev/null || exit 1; \
	  "$$bin/lld-link" -wince /dll /entry:DllMainCRTStartup /base:0x10000 \
	    /export:E2EDemo $$d/e2e_module.o \
	    "$(CRTDIR)/build/akari_dllcrt.o" "$(CRTDIR)/build/libakari.a" \
	    $$d/*.lib /out:$$d/e2e_module.dll 2>/dev/null || exit 1; \
	  "$$bin/llvm-readobj" -h $$d/e2e_console.exe | grep -q "$$mchk" || exit 1; \
	  "$$bin/llvm-readobj" -h $$d/e2e_console.exe \
	    | grep -q "IMAGE_SUBSYSTEM_WINDOWS_CE_GUI" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Name: coredll.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CopyFileExW" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ws2.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSAStartup" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: socket" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: getaddrinfo" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CeWriteRecordProps" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CeOidGetInfo" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: msdmo.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DMOEnum" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: oleaut32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SysAllocString" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSAEnumNameSpaceProviders" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSALookupServiceBegin" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSASetService" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CommandBar_Create" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CommandBands_Create" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: GetOpenFileName" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ldap_init" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ber_alloc_t" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WSPStartup" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: NSPSetService" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: TSPI_lineOpen" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: TSPI_phoneGetDevCaps" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ole32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CoCreateGuid" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CreateFileMoniker" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: StgCreateDocfile" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: oleaut32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SysAllocString" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: VariantInit" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: LoadTypeLib" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: lineInitializeEx" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: lineOpen (" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: lineForward (" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: phoneOpen" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: TSPI_lineForward" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: coreimm.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ImmGetContext" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ImmSIPanelState" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptAcquireContext" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptMsgClose" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptProtectData" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: crypt32.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CertOpenStore" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CryptEncodeObjectEx" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: PFXImportCertStore" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: winscard.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SCardEstablishContext" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SCardTransmit" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: aygshell.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHCreateMenuBar" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHHandleWMActivate" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHInitDialog" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHGetAutoRunPath" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SipGetInfo" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SipShowIM" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SHSipPreference" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: kbdui.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: PostKeybdMessage" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: GetAsyncShiftFlags" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: KeybdGetDeviceInfo" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Name: ceshell.dll" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHBrowseForFolder" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHGetSpecialFolderLocation" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: StrRetToBuf" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Name: shmisc.dll" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHShowOutOfMemory" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: ShellExecuteEx" || exit 1; \
	  "$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	    | grep -q "Symbol: SHGetSpecialFolderPath" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btdrt.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthReadLocalAddr" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthPerformInquiry" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthNsLookupServiceBegin" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: snmpapi.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpUtilOidCmp" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpUtilMemAlloc" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpTfxOpen" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: snmp.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: SnmpExtensionQuery" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ceddk.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: HalAllocateCommonBuffer" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: READ_PORT_ULONG" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: MmMapIoSpace" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btagsvc_phoneext.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthAGPhoneExtInit" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btagsvc_network.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthAGNetworkDropCall" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: btagsvc.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: BthAGOnNetworkEvent" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: ddraw.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawCreate" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawCreateClipper" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawEnumerate" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: DirectDrawEnumerateEx" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: urlmon.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CoInternetGetSession" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CoInternetGetSecurityUrl" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: CreateURLMoniker" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: RegisterMediaTypes" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: IsLoggingEnabledW" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: URLDownloadToFileW" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: WriteHitLogging" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Name: mlang.dll" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: ConvertINetString" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: LcidToRfc1766" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_console.exe \
	  | grep -q "Symbol: Rfc1766ToLcid" || exit 1; \
	"$$bin/llvm-readobj" --coff-imports $$d/e2e_winmain.exe \
    | grep -q "Symbol: MessageBoxW" || exit 1; \
	  echo "[e2e] $$t OK (machine/subsystem/imports)"; \
	done; \
	echo "[e2e] OK -- $(words $(CE_TRIPLES)) WinCE targets linked against the doc-derived import libraries"
