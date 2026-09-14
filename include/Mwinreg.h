/*
 * Mwinreg.h -- declarations recovered from the official
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

#ifndef AKARI_MWINREG_H_
#define AKARI_MWINREG_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms919603: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT BOOL SetCurrentUser(LPCWSTR lpszUserName, LPBYTE lpbUserSecret, DWORD dwDataSize, BOOL bCreateIfNew) AKARI_CE_NAME(SetCurrentUser);

#endif /* AKARI_MWINREG_H_ */
