/*
 * Kernel.h -- declarations recovered from the official
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

#ifndef AKARI_KERNEL_H_
#define AKARI_KERNEL_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Winbase.h"   /* FILETIME/LPFILETIME -- the FILETIME page
                        * (ms885586) prints Header: Winbase.h */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms902902: page-printed prototype (Windows CE .NET 4.0 and later.; nk.lib). */
void FlushDCache(void);

/* ms902910: page-printed prototype (Windows CE .NET 4.0 and later.; nk.lib). */
void FlushICache(void);

/* ms903218: page-printed prototype (Windows CE .NET 4.2 and later.; not applicable). */
void OEMCacheRangeFlush(LPVOID pAddr, DWORD dwLength, DWORD dwFlags);

/* ms903551: page-printed prototype (Windows CE .NET 4.0 and later.; nk.lib). */
DWORD SC_GetTickCount(void);


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms903211: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
BOOL KLocalFileTimeToFileTime(const FILETIME* lpft, LPFILETIME lpst);


/* ee478340 FlushDCache: print `void FlushDCache(void);`
 * (generation not stated; Link Library: nk.lib) */
AKARI_CE_IMPORT void FlushDCache(void) AKARI_CE_NAME(FlushDCache);

/* ee478614 SC_GetTickCount: print `DWORD SC_GetTickCount(void);`
 * (generation not stated; Link Library: nkstub.lib) */
AKARI_CE_IMPORT DWORD SC_GetTickCount(void) AKARI_CE_NAME(SC_GetTickCount);

/* ee479199 FlushICache: print `void FlushICache(void);`
 * (generation not stated; Link Library: nk.lib) */
AKARI_CE_IMPORT void FlushICache(void) AKARI_CE_NAME(FlushICache);

/* ee479202 KLocalFileTimeToFileTime: print `BOOL KLocalFileTimeToFileTime(
const FILETIME* lpft,
LPFILETIME lpst
);`
 * (generation not stated; Link Library: nk.lib) */
AKARI_CE_IMPORT BOOL KLocalFileTimeToFileTime(const FILETIME *lpft, LPFILETIME lpst) AKARI_CE_NAME(KLocalFileTimeToFileTime);

#endif /* AKARI_KERNEL_H_ */
