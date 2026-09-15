/*
 * Pkfuncs.h -- Windows CE public kernel functions.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE page
 * ms939622 "CaptureDumpFileOnDevice" (Error Report Generator
 * Functions, CE-era MSDN archive): Requirements row prints
 * "Header: Pkfuncs.h / Link Library: Coredll.lib / OS Versions:
 * Windows Embedded CE 6.0".  (The ZeroPtr macro named by the
 * CeZeroPointer page ms885158 is OEM-side and stays recorded in
 * Winbase.h -- see docs/inventory.md.)
 *
 * See docs/inventory.md M82.
 */

#ifndef AKARI_PKFUNCS_H
#define AKARI_PKFUNCS_H

#include "Windef.h"    /* BOOL, DWORD, LPCWSTR */
#include "Windbase.h"   /* 1 declaration(s) whose official pages print
                    * "Header: Pkfuncs.h" are carried there, so including it
                    * makes <Pkfuncs.h> provide them as those pages promise
                    * (docs/header-placement-audit.md). */

#if _WIN32_WCE >= 0x0500   /* CaptureDumpFileOnDevice: documented from CE 5.0 (docs/generation-audit.md) */
/* ms939622 "CaptureDumpFileOnDevice": print
 * `BOOL CaptureDumpFileOnDevice(DWORDdwProcessId,DWORDdwThreadId,
 * LPCWSTRpwzExtraFilesPath);` (glued tokens split).  Generates an
 * error-report dump file for the given process and thread. */
AKARI_CE_IMPORT BOOL CaptureDumpFileOnDevice(DWORD dwProcessId,
                    DWORD dwThreadId, LPCWSTR pwzExtraFilesPath)
                    AKARI_CE_NAME(CaptureDumpFileOnDevice);

#endif /* _WIN32_WCE >= 0x0500 (CaptureDumpFileOnDevice) */
/* ------------------------------------------------------------------
 * Book surface: drivers-pci (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms898290 DEVICE_LOCATION -- HELD (page print; member types unpublished):
 *   typedef struct _DEVICE_LOCATION { ... } DEVICE_LOCATION, *PDEVICE_LOCATION; */

/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_CacheSync: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT VOID CacheSync(int flags) AKARI_CE_NAME(CacheSync);

/* _wcepb_ForcePageout: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT VOID ForcePageout(void) AKARI_CE_NAME(ForcePageout);

/* ms905534: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT BOOL FreeIntChainHandler(HANDLE hInstance) AKARI_CE_NAME(FreeIntChainHandler);

/* _wcepb_GetCurrentPermissions: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT DWORD GetCurrentPermissions(void) AKARI_CE_NAME(GetCurrentPermissions);

/* _wcepb_GetOwnerProcess: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT HANDLE GetOwnerProcess(void) AKARI_CE_NAME(GetOwnerProcess);

/* _wcepb_InterruptDisable: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT VOID InterruptDisable(DWORD idInt) AKARI_CE_NAME(InterruptDisable);

/* _wcepb_InterruptDone: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT VOID InterruptDone(DWORD idInt) AKARI_CE_NAME(InterruptDone);

/* _wcepb_InterruptInitialize: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL InterruptInitialize(DWORD idInt, HANDLE hEvent, LPVOID pvData, DWORD cbData) AKARI_CE_NAME(InterruptInitialize);

/* _wcepb_KernelIoControl: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL KernelIoControl(DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned) AKARI_CE_NAME(KernelIoControl);

/* _wcepb_LoadDriver: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT HINSTANCE LoadDriver(LPCWSTR lpszFileName) AKARI_CE_NAME(LoadDriver);

/* ms903212: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT HANDLE LoadKernelLibrary(LPCWSTR lpszFileName) AKARI_CE_NAME(LoadKernelLibrary);

/* _wcepb_LockPages: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL LockPages(LPVOID lpvAddress, DWORD cbSize, PDWORD pPFNs, int fOptions) AKARI_CE_NAME(LockPages);

/* _wcepb_MapPtrToProcess: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT LPVOID MapPtrToProcess(LPVOID lpv, HANDLE hProc) AKARI_CE_NAME(MapPtrToProcess);

/* ms903215: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT LPVOID NKCreateStaticMapping(DWORD dwPhysBase, DWORD dwSize) AKARI_CE_NAME(NKCreateStaticMapping);

/* ms903216: page-printed prototype (Windows CE .NET 4.2 and later.; coredll.lib). */
AKARI_CE_IMPORT VOID NKForceCleanBoot(void) AKARI_CE_NAME(NKForceCleanBoot);

/* ms918905: page-printed prototype (Windows CE 3.0 and later.; nk.lib). */
BOOL OEMKDIoControl(DWORD dwIoControlCode, LPVOID lpBuf, DWORD nBufSize);

/* ms903546: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT void PowerOffSystem(void) AKARI_CE_NAME(PowerOffSystem);

/* ms919353: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
AKARI_CE_IMPORT DWORD ReadRegistryFromOEM(DWORD dwFlags, LPBYTE lpData, DWORD cbData) AKARI_CE_NAME(ReadRegistryFromOEM);

/* ms903552: page-printed prototype (Windows CE 2.10 and later.; coredll.lib). */
AKARI_CE_IMPORT void SetCleanRebootFlag(void) AKARI_CE_NAME(SetCleanRebootFlag);

/* _wcepb_SetKMode: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL SetKMode(BOOL fMode) AKARI_CE_NAME(SetKMode);

/* ms919612: page-printed prototype (Windows CE 3.0 and later.; coredll.lib). */
AKARI_CE_IMPORT void SetOOMEvent(HANDLE hEvent, DWORD cpLow, DWORD cpCritical, DWORD cpLowBlockSize, DWORD cpCriticalBlockSize) AKARI_CE_NAME(SetOOMEvent);

/* _wcepb_SetProcPermissions: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT DWORD SetProcPermissions(DWORD newperms) AKARI_CE_NAME(SetProcPermissions);

/* _wcepb_SetStoreQueueBase: page-printed prototype (Windows CE OS). */
LPVOID SetStoreQueueBase(DWORD dwPhysPage);

/* _wcepb_UnMapPtr: page-printed prototype (Windows CE OS). */
LPVOID UnMapPtr(LPVOID lpv);

/* _wcepb_UnlockPages: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL UnlockPages(LPVOID lpvAddress, DWORD cbSize) AKARI_CE_NAME(UnlockPages);

/* _wcepb_VirtualCopy: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL VirtualCopy(LPVOID lpvDest, LPVOID lpvSrc, DWORD cbSize, DWORD fdwProtect) AKARI_CE_NAME(VirtualCopy);

/* ms920084: page-printed prototype (Windows CE 3.0 and later.; coredll.lib). */
AKARI_CE_IMPORT BOOL VirtualSetPageFlags(LPVOID lpvAddress, DWORD cbSize, DWORD dwFlags, LPDWORD lpdwOldFlags) AKARI_CE_NAME(VirtualSetPageFlags);

/* ms920093: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
AKARI_CE_IMPORT BOOL WriteRegistryToOEM(DWORD dwFlags, LPBYTE lpData, DWORD cbData) AKARI_CE_NAME(WriteRegistryToOEM);


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

#if _WIN32_WCE >= 0x0600   /* CeCloseCallerBuffer: documented from CE 6.0 (docs/generation-audit.md) */
/* ee488934: page-printed prototype (Windows Embedded CE 6.0; coredll.lib). */
AKARI_CE_IMPORT HRESULT CeCloseCallerBuffer(PVOID pDestMarshalled, PVOID pSrcUnmarshalled, DWORD cbSrc, DWORD ArgumentDescriptor) AKARI_CE_NAME(CeCloseCallerBuffer);

#endif /* _WIN32_WCE >= 0x0600 (CeCloseCallerBuffer) */
#if _WIN32_WCE >= 0x0600   /* CeOpenCallerBuffer: documented from CE 6.0 (docs/generation-audit.md) */
/* ee488382 CeOpenCallerBuffer (Windows Embedded CE 6.0; coredll.lib):
 * the page prints the five parameters exactly as below but drops the
 * comma between ArgumentDescriptor and ForceDuplicate (print:
 * `...DWORD cbSrc, DWORD ArgumentDescriptor BOOL ForceDuplicate);`).
 * The comma is restored; nothing else is changed. */
AKARI_CE_IMPORT HRESULT CeOpenCallerBuffer(PVOID* ppDestMarshalled, PVOID pSrcUnmarshalled, DWORD cbSrc, DWORD ArgumentDescriptor, BOOL ForceDuplicate) AKARI_CE_NAME(CeOpenCallerBuffer);

#endif /* _WIN32_WCE >= 0x0600 (CeOpenCallerBuffer) */
#if _WIN32_WCE >= 0x0600   /* GetCallerVMProcessId: documented from CE 6.0 (docs/generation-audit.md) */
/* ee482772: page-printed prototype (Windows Embedded CE 6.0; coredll.lib). */
AKARI_CE_IMPORT DWORD GetCallerVMProcessId(void) AKARI_CE_NAME(GetCallerVMProcessId);

#endif /* _WIN32_WCE >= 0x0600 (GetCallerVMProcessId) */
#if _WIN32_WCE >= 0x0600   /* GetDirectCallerProcessId: documented from CE 6.0 (docs/generation-audit.md) */
/* ee482980: page-printed prototype (Windows Embedded CE 6.0; coredll.lib). */
AKARI_CE_IMPORT DWORD GetDirectCallerProcessId(void) AKARI_CE_NAME(GetDirectCallerProcessId);

#endif /* _WIN32_WCE >= 0x0600 (GetDirectCallerProcessId) */
#if _WIN32_WCE >= 0x0600   /* SetEventData: documented from CE 6.0 (docs/generation-audit.md) */
/* ee482792: page-printed prototype (Windows Embedded CE 6.0; coredll.lib). */
AKARI_CE_IMPORT BOOL SetEventData(HANDLE hEvent, DWORD dwData) AKARI_CE_NAME(SetEventData);

#endif /* _WIN32_WCE >= 0x0600 (SetEventData) */
#if _WIN32_WCE >= 0x0600   /* VirtualAllocCopyEx: documented from CE 6.0 (docs/generation-audit.md) */
/* ee488184: page-printed prototype (Windows Embedded CE 6.0; coredll.lib). */
AKARI_CE_IMPORT LPVOID VirtualAllocCopyEx(HANDLE hSrcProc, HANDLE hDstProc, LPVOID pAddr, DWORD cbSize, DWORD dwProtect) AKARI_CE_NAME(VirtualAllocCopyEx);


#endif /* _WIN32_WCE >= 0x0600 (VirtualAllocCopyEx) */
/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms919253: page-printed definition (Windows CE 3.0 and later.). */
typedef struct _PHYSICAL_BASIC_INFORMATION {
    PVOID lpBaseAddress;
    DWORD dwRegionSize;
    DWORD dwType;
} PHYSICAL_BASIC_INFORMATION;

#endif /* AKARI_PKFUNCS_H */
