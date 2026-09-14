/*
 * Kitltran.h -- declarations recovered from the official
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

#ifndef AKARI_KITLTRAN_H_
#define AKARI_KITLTRAN_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms920052: page-printed prototype (Windows CE .NET 4.0 and later.; not applicable). */
BOOL TranDeInitLibrary(void);

/* ms920064: page-printed prototype (Windows CE .NET 4.0 and later.; not applicable). */
BOOL TranInitLibrary(LPCWSTR pszRegKeyRoot);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms919247: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef BOOL (*PFN_EnumProc)(LPCWSTR pszDevName, LPVOID pData);


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms920056: page-printed prototype (Windows CE .NET 4.0 and later.; not applicable). */
BOOL TranEnumKnownDevice(PFN_EnumProc pfnCB, LPVOID pUserData);

#endif /* AKARI_KITLTRAN_H_ */
