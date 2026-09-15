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

#endif /* AKARI_PWINREG_H_ */
