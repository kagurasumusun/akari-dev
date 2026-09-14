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

#endif /* AKARI_PWINREG_H_ */
