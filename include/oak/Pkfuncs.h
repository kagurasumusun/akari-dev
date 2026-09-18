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
#include "Winreg.h"   /* HKEY, REGSAM, PHKEY (NKReg* declarations) */
#include "Dbgapi.h"    /* LPDBGPARAM (SetDbgZone) */
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
/* ee482858: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT VOID CacheSync(int flags) AKARI_CE_NAME(CacheSync);

/* _wcepb_ForcePageout: page-printed prototype (Windows CE OS). */
/* ee483002: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT VOID ForcePageout(void) AKARI_CE_NAME(ForcePageout);

/* ms905534: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT BOOL FreeIntChainHandler(HANDLE hInstance) AKARI_CE_NAME(FreeIntChainHandler);

/* _wcepb_GetCurrentPermissions: page-printed prototype (Windows CE OS). */
/* ee483152: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD GetCurrentPermissions(void) AKARI_CE_NAME(GetCurrentPermissions);

/* _wcepb_GetOwnerProcess: page-printed prototype (Windows CE OS). */
/* ee483052: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT HANDLE GetOwnerProcess(void) AKARI_CE_NAME(GetOwnerProcess);

/* _wcepb_InterruptDisable: page-printed prototype (Windows CE OS). */
/* ee482866: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT VOID InterruptDisable(DWORD idInt) AKARI_CE_NAME(InterruptDisable);

/* _wcepb_InterruptDone: page-printed prototype (Windows CE OS). */
/* ee482745: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT VOID InterruptDone(DWORD idInt) AKARI_CE_NAME(InterruptDone);

/* _wcepb_InterruptInitialize: page-printed prototype (Windows CE OS). */
/* ee482998: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL InterruptInitialize(DWORD idInt, HANDLE hEvent, LPVOID pvData, DWORD cbData) AKARI_CE_NAME(InterruptInitialize);

/* _wcepb_KernelIoControl: page-printed prototype (Windows CE OS). */
/* ee488646: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL KernelIoControl(DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned) AKARI_CE_NAME(KernelIoControl);

/* _wcepb_LoadDriver: page-printed prototype (Windows CE OS). */
/* ee482944: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT HINSTANCE LoadDriver(LPCWSTR lpszFileName) AKARI_CE_NAME(LoadDriver);

/* ms903212: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT HANDLE LoadKernelLibrary(LPCWSTR lpszFileName) AKARI_CE_NAME(LoadKernelLibrary);

/* _wcepb_LockPages: page-printed prototype (Windows CE OS). */
/* ee482989: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL LockPages(LPVOID lpvAddress, DWORD cbSize, PDWORD pPFNs, int fOptions) AKARI_CE_NAME(LockPages);

/* _wcepb_MapPtrToProcess: page-printed prototype (Windows CE OS). */
/* ee482835: param-list verified against this page (proto-cite) */
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
/* ee482868: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL SetKMode(BOOL fMode) AKARI_CE_NAME(SetKMode);

/* ms919612: page-printed prototype (Windows CE 3.0 and later.; coredll.lib). */
AKARI_CE_IMPORT void SetOOMEvent(HANDLE hEvent, DWORD cpLow, DWORD cpCritical, DWORD cpLowBlockSize, DWORD cpCriticalBlockSize) AKARI_CE_NAME(SetOOMEvent);

/* _wcepb_SetProcPermissions: page-printed prototype (Windows CE OS). */
/* ee482959: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD SetProcPermissions(DWORD newperms) AKARI_CE_NAME(SetProcPermissions);

/* _wcepb_SetStoreQueueBase: page-printed prototype (Windows CE OS). */
LPVOID SetStoreQueueBase(DWORD dwPhysPage);

/* _wcepb_UnMapPtr: page-printed prototype (Windows CE OS). */
LPVOID UnMapPtr(LPVOID lpv);

/* _wcepb_UnlockPages: page-printed prototype (Windows CE OS). */
/* ee483160: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL UnlockPages(LPVOID lpvAddress, DWORD cbSize) AKARI_CE_NAME(UnlockPages);

/* _wcepb_VirtualCopy: page-printed prototype (Windows CE OS). */
/* ee483154: param-list verified against this page (proto-cite) */
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

#if _WIN32_WCE >= 0x0420   /* CacheInfo / CeGetCacheInfo: documented from CE .NET 4.2 (docs/generation-audit.md) */
/* aa450786 "CacheInfo" (CE 5.0; CE 6.0 twin ee483008): page-printed
 * definition verbatim (OS Versions: Windows CE .NET 4.2 and later.;
 * Header: Pkfuncs.h). */
typedef struct _CacheInfo {
    DWORD dwL1Flags;
    DWORD dwL1ICacheSize;
    DWORD dwL1ICacheLineSize;
    DWORD dwL1ICacheNumWays;
    DWORD dwL1DCacheSize;
    DWORD dwL1DCacheLineSize;
    DWORD dwL1DCacheNumWays;
    DWORD dwL2Flags;
    DWORD dwL2ICacheSize;
    DWORD dwL2ICacheLineSize;
    DWORD dwL2ICacheNumWays;
    DWORD dwL2DCacheSize;
    DWORD dwL2DCacheLineSize;
    DWORD dwL2DCacheNumWays;
} CacheInfo, *PCacheInfo;

/* aa450791 "CeGetCacheInfo (Windows CE 5.0)": page-printed prototype
 * `BOOL CeGetCacheInfo(DWORD cbSize, PCacheInfo pCacheInfo);` (glued
 * tokens split).  CE .NET 4.2+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL CeGetCacheInfo(DWORD cbSize, PCacheInfo pCacheInfo) AKARI_CE_NAME(CeGetCacheInfo);

#endif /* _WIN32_WCE >= 0x0420 (CacheInfo / CeGetCacheInfo) */

/* aa450982 "VirtualSetAttributes (Windows CE 5.0)": page-printed
 * prototype `BOOL VirtualSetAttributes(LPVOIDlpvAddress,DWORDcbSize,
 * DWORDdwNewFlags,DWORDdwMask,LPDWORDlpdwOldFlags);` (glued tokens
 * split); identical print on the CE 6.0 twin ee482857.  CE .NET 4.1+;
 * Pkfuncs.h; Coredll.lib.  (The VirtualSetAttributesEx page ee488757
 * reprints this same prototype -- archive artifact, recorded in
 * Mkfuncs.h.) */
AKARI_CE_IMPORT BOOL VirtualSetAttributes(LPVOID lpvAddress, DWORD cbSize,
                    DWORD dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags)
                    AKARI_CE_NAME(VirtualSetAttributes);

#if _WIN32_WCE >= 0x0500   /* CeSetMemoryAttributes / DrWatson*: documented from CE 5.0 (docs/generation-audit.md) */
/* ms885152 "CeSetMemoryAttributes (Windows CE 5.0)": page-printed
 * prototype `BOOL CeSetMemoryAttributes(LPVOID pVirtualAddr, LPVOID
 * pShiftedPhysAddr, DWORD cbSize, DWORD dwAttributes);` (glued tokens
 * split).  CE 5.0+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL CeSetMemoryAttributes(LPVOID pVirtualAddr,
                    LPVOID pShiftedPhysAddr, DWORD cbSize, DWORD dwAttributes)
                    AKARI_CE_NAME(CeSetMemoryAttributes);

/* ms885203 "DrWatsonClear (Windows CE 5.0)": page-printed prototype
 * `BOOL DrWatsonClear(void);`.  CE 5.0+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL DrWatsonClear(void) AKARI_CE_NAME(DrWatsonClear);

/* ms885204 "DrWatsonFlush (Windows CE 5.0)": page-printed prototype
 * `BOOL DrWatsonFlush(void);`.  CE 5.0+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL DrWatsonFlush(void) AKARI_CE_NAME(DrWatsonFlush);

/* ms885205 "DrWatsonGetSize (Windows CE 5.0)": page-printed prototype
 * `DWORD DrWatsonGetSize(void);`.  CE 5.0+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT DWORD DrWatsonGetSize(void) AKARI_CE_NAME(DrWatsonGetSize);

/* ms885206 "DrWatsonReadData (Windows CE 5.0)": page-printed
 * prototype `DWORD DrWatsonReadData(DWORD dwOffset, LPVOID pData,
 * DWORD cbSize);`.  CE 5.0+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT DWORD DrWatsonReadData(DWORD dwOffset, LPVOID pData,
                    DWORD cbSize) AKARI_CE_NAME(DrWatsonReadData);

/* ms885207 "DrWatsonWriteData (Windows CE 5.0)": page-printed
 * prototype `DWORD DrWatsonWriteData(DWORD dwOffset, LPVOID pData,
 * DWORD cbSize);`.  CE 5.0+; Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT DWORD DrWatsonWriteData(DWORD dwOffset, LPVOID pData,
                    DWORD cbSize) AKARI_CE_NAME(DrWatsonWriteData);

/* ee478212 "NKVirtualSetAttributes (Windows Embedded CE 6.0)" and
 * ms904874 (CE 5.0): page-printed prototype `BOOL
 * NKVirtualSetAttributes( LPVOID lpvAddress, DWORD cbSize, DWORD
 * dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags );`.  CE 5.0+;
 * Pkfuncs.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL NKVirtualSetAttributes(LPVOID lpvAddress, DWORD cbSize,
                    DWORD dwNewFlags, DWORD dwMask, LPDWORD lpdwOldFlags)
                    AKARI_CE_NAME(NKVirtualSetAttributes);

/* Record-only: "NKSetDataAbortHandler" (ms904873; CE 5.0+; Pkfuncs.h)
 * prints `PFNVOID NKSetDataAbortHandler(PFNVOIDpfnDataAbortHandler);`
 * -- PFNVOID is printed by no CE page's typedef (see Mkfuncs.h note),
 * so the declaration stays recorded, not shipped. */

#endif /* _WIN32_WCE >= 0x0500 (CeSetMemoryAttributes / DrWatson*) */


/* --- absent-surface pass 2026-09-18: coredll-exported functions
 * whose pages print "Link Library: Coredll.lib" (docs/absent-funcprints
 * -2026-09-18.tsv). ------------------------------------------- */

/* aa450785(v=msdn.10) AllocPhysMem: page print `LPVOID AllocPhysMem(DWORD cbSize,DWORD fdwProtect,DWORD dwAlignmentMask,DWORD dwFlags,PULONG pPhysicalAddress);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LPVOID AllocPhysMem(DWORD cbSize, DWORD fdwProtect, DWORD dwAlignmentMask, DWORD dwFlags, PULONG pPhysicalAddress) AKARI_CE_NAME(AllocPhysMem);

/* aa450787(v=msdn.10) CacheRangeFlush: page print `void CacheRangeFlush(LPVOIDpAddr,DWORDdwLength,DWORDdwFlags );`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT void CacheRangeFlush(LPVOID pAddr, DWORD dwLength, DWORD dwFlags) AKARI_CE_NAME(CacheRangeFlush);

/* ms885185(v=msdn.10) CreateStaticMapping: page print `LPVOID CreateStaticMapping(DWORDdwPhysBase,DWORDdwSize);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LPVOID CreateStaticMapping(DWORD dwPhysBase, DWORD dwSize) AKARI_CE_NAME(CreateStaticMapping);

/* ms885603(v=msdn.10) FreePhysMem: page print `BOOL FreePhysMem(LPVOID lpvAddress);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL FreePhysMem(LPVOID lpvAddress) AKARI_CE_NAME(FreePhysMem);

/* ms885637(v=msdn.10) GetStdioPathW: page print `BOOL GetStdioPathW(DWORDid,PWSTRpwszBuf,LPDWORDlpdwLen );`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL GetStdioPathW(DWORD id, PWSTR pwszBuf, LPDWORD lpdwLen) AKARI_CE_NAME(GetStdioPathW);

/* ms885678(v=msdn.10) InterruptMask: page print `VOID InterruptMask(DWORD idInt, BOOL fDisable);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT VOID InterruptMask(DWORD idInt, BOOL fDisable) AKARI_CE_NAME(InterruptMask);

/* ms886725(v=msdn.10) IsNamedEventSignaled: page print `BOOL IsNamedEventSignaled( LPCWSTR pszName, DWORD dwFlags);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL IsNamedEventSignaled(LPCWSTR pszName, DWORD dwFlags) AKARI_CE_NAME(IsNamedEventSignaled);

/* ms904841(v=msdn.10) KLibAllocShareMem: page print `BOOL KLibAllocShareMem(DWORD nPages,BOOL fNoCache,LPVOID* pVa,LPVOID* pPa);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL KLibAllocShareMem(DWORD nPages, BOOL fNoCache, LPVOID*pVa, LPVOID*pPa) AKARI_CE_NAME(KLibAllocShareMem);

/* ms904850(v=msdn.10) KLibFreeShareMem: page print `BOOL KLibFreeShareMem(DWORD nPages,LPVOID pVa,LPVOID pPa);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL KLibFreeShareMem(DWORD nPages, LPVOID pVa, LPVOID pPa) AKARI_CE_NAME(KLibFreeShareMem);

/* ms886730(v=msdn.10) KernelLibIoControl: page print `BOOL KernelLibIoControl(HANDLEhModule,DWORDdwIoControlCode,LPVOIDlpInBuf,DWORDnInBufSize,LPVOIDlpOutBuf,DWORDnOutBufSize,LPDWORDlpBytesReturned);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL KernelLibIoControl(HANDLE hModule, DWORD dwIoControlCode, LPVOID lpInBuf, DWORD nInBufSize, LPVOID lpOutBuf, DWORD nOutBufSize, LPDWORD lpBytesReturned) AKARI_CE_NAME(KernelLibIoControl);

/* ms904854(v=msdn.10) LoadIntChainHandler: page print `HANDLE LoadIntChainHandler(LPCWSTR lpFilename,LPCWSTR lpszFunctionName,BYTE bIRQ);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT HANDLE LoadIntChainHandler(LPCWSTR lpFilename, LPCWSTR lpszFunctionName, BYTE bIRQ) AKARI_CE_NAME(LoadIntChainHandler);

/* ms886749(v=msdn.10) MapCallerPtr: page print `LPVOID MapCallerPtr( LPVOID ptr, DWORD dwLen);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LPVOID MapCallerPtr(LPVOID ptr, DWORD dwLen) AKARI_CE_NAME(MapCallerPtr);

/* ms904868(v=msdn.10) NKRegCloseKey: page print `LONG NKRegCloseKey(HKEYhKey);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LONG NKRegCloseKey(HKEY hKey) AKARI_CE_NAME(NKRegCloseKey);

/* ms904869(v=msdn.10) NKRegCreateKeyEx: page print `LONG NKRegCreateKeyEx(HKEYhKey,LPCWSTRlpSubKey, DWORDReserved,LPWSTRlpClass,DWORDdwOptions, REGSAMsamDesired,LPSECURITY_ATTRIBUTESlpSecurityAttributes,PHKEYphkResult, LPDWORDlpdwDisposition);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LONG NKRegCreateKeyEx(HKEY hKey, LPCWSTR lpSubKey, DWORD Reserved, LPWSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition) AKARI_CE_NAME(NKRegCreateKeyEx);

/* ms904870(v=msdn.10) NKRegOpenKeyEx: page print `LONG NKRegOpenKeyEx(HKEYhKey,LPCWSTRlpSubKey, DWORDulOptions, REGSAMsamDesired,PHKEYphkResult);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LONG NKRegOpenKeyEx(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) AKARI_CE_NAME(NKRegOpenKeyEx);

/* ms904871(v=msdn.10) NKRegQueryValueEx: page print `LONG NKRegQueryValueEx(HKEYhKey,LPCWSTRlpValueName, LPDWORDlpReserved,LPDWORDlpType,LPBYTElpData, LPDWORDlpcbData);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LONG NKRegQueryValueEx(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) AKARI_CE_NAME(NKRegQueryValueEx);

/* ms904872(v=msdn.10) NKRegSetValueEx: page print `LONG NKRegSetValueEx(HKEYhKey,LPCWSTRlpValueName, DWORDdwReserved,DWORDdwType,LPBYTElpData, DWORDcbData);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT LONG NKRegSetValueEx(HKEY hKey, LPCWSTR lpValueName, DWORD dwReserved, DWORD dwType, LPBYTE lpData, DWORD cbData) AKARI_CE_NAME(NKRegSetValueEx);

/* ms886771(v=msdn.10) PageOutModule: page print `BOOL PageOutModule(HANDLEhModule,DWORDdwFlags);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL PageOutModule(HANDLE hModule, DWORD dwFlags) AKARI_CE_NAME(PageOutModule);

/* ms886809(v=msdn.10) SetDbgZone: page print `BOOL SetDbgZone(DWORDdwProcid,LPVOIDlpvMod, LPVOIDbaseptr,DWORDzone,LPDBGPARAMlpdbgTgt);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL SetDbgZone(DWORD dwProcid, LPVOID lpvMod, LPVOID baseptr, DWORD zone, LPDBGPARAM lpdbgTgt) AKARI_CE_NAME(SetDbgZone);

/* ms886820(v=msdn.10) SetStdioPathW: page print `BOOL SetStdioPathW(DWORDid,PWSTRpwszPath );`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL SetStdioPathW(DWORD id, PWSTR pwszPath) AKARI_CE_NAME(SetStdioPathW);

/* aa450901(v=msdn.10) SleepTillTick: page print `void SleepTillTick();`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT void SleepTillTick(void) AKARI_CE_NAME(SleepTillTick);

#endif /* AKARI_PKFUNCS_H */
