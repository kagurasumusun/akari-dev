/*
 * Pwinreg.h -- declarations recovered from the official
 * page prints (tools/decl-d1.py, M105 header creation).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own
 * print (page id cited).  Prints whose types include/
 * cannot yet resolve are recorded verbatim in the
 * header comment blocks by later passes; nothing is
 * dropped or invented.
 */

#ifndef AKARI_PWINREG_H_
#define AKARI_PWINREG_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Winreg.h"    /* HKEY (RegReplaceKey / RegSaveKey) */
#include "Mwinreg.h"   /* SetCurrentUser: pwinreg.h (ee490214, ms891903) is the
                        * documented header, this tree declares it in the
                        * multiple-user registry header (M134) */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_RegCopyFile: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL RegCopyFile(LPCWSTR lpszFile) AKARI_CE_NAME(RegCopyFile);

/* _wcepb_RegRestoreFile: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL RegRestoreFile(LPCWSTR lpszFile) AKARI_CE_NAME(RegRestoreFile);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms903018: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef struct HiveRAMRegion {
    LPVOID lpStart;
    DWORD dwLength;
    DWORD dwVirtCopyFlags;
} HiveRAMRegion;

/* ms903548: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef struct RegSecureKey {
    WORD wRoots;
    WORD wLen;
    LPWSTR pName;
} RegSecureKey;


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms903012: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef struct HiveRAMInfo {
    WORD wVersion;
    WORD wFlags;
    HiveRAMRegion SystemRegion;
} HiveRAMInfo;

/* ms903549: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef struct RegSecureKeyList {
    DWORD dwNumKeys;
    RegSecureKey* pList;
} RegSecureKeyList;

/* ee489789 "RegReplaceKey (Windows Embedded CE 6.0)": page-printed
 * prototype; Header pwinreg.h, Library coredll.lib, CE .NET 4.0 and
 * later; verified coredll export on all four device dumps. */
AKARI_CE_IMPORT LONG RegReplaceKey(HKEY hKey, LPCTSTR lpSubKey,
    LPCTSTR lpNewFile, LPCTSTR lpOldFile) AKARI_CE_NAME(RegReplaceKey);

/* ee489766 "RegSaveKey (Windows Embedded CE 6.0)": page-printed
 * prototype; Header pwinreg.h, Library coredll.lib, CE .NET 4.0 and
 * later; verified coredll export on all four device dumps. */
AKARI_CE_IMPORT LONG RegSaveKey(HKEY hKey, LPCTSTR lpFile,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes) AKARI_CE_NAME(RegSaveKey);


/* --- absent-surface pass 2026-09-18: coredll-exported functions
 * whose pages print "Header: Pwinreg.h" + "Link Library: Coredll.lib"
 * (docs/absent-funcprints-2026-09-18.tsv). --------------------- */

/* ms891226(v=msdn.10) GetUserDirectory: page print `BOOL GetUserDirectory( LPWSTRlpszBuffer, LPDWORDlpdwSize);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL GetUserDirectory(LPWSTR lpszBuffer, LPDWORD lpdwSize) AKARI_CE_NAME(GetUserDirectory);

/* ms891446(v=msdn.10) ReadGenericData: page print `BOOL ReadGenericData(WORDdwId,DWORDdwIndex,DWORDdwFlags, LPBYTE pBuf,DWORD dwLength,DWORD pdwBytesReturned);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL ReadGenericData(WORD dwId, DWORD dwIndex, DWORD dwFlags, LPBYTE pBuf, DWORD dwLength, DWORD pdwBytesReturned) AKARI_CE_NAME(ReadGenericData);

/* ms891447(v=msdn.10) ReadRegData: page print `DWORD ReadRegData(DWORDdwFlags,LPBYTEpBuf,DWORDlen );`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT DWORD ReadRegData(DWORD dwFlags, LPBYTE pBuf, DWORD len) AKARI_CE_NAME(ReadRegData);

/* ms891457(v=msdn.10) RegistryOperation: page print `BOOL RegistryOperation(DWORDdwOp);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL RegistryOperation(DWORD dwOp) AKARI_CE_NAME(RegistryOperation);

/* ms892382(v=msdn.10) WriteRegData: page print `BOOL WriteRegData( DWORDdwFlags,LPBYTElpBuf,DWORDlen );`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT BOOL WriteRegData(DWORD dwFlags, LPBYTE lpBuf, DWORD len) AKARI_CE_NAME(WriteRegData);

#endif /* AKARI_PWINREG_H_ */
