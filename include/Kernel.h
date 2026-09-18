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
 * from the official pages (tools/decl-d1.py). --------
 *
 * Audit 2026-09-16 (crosscheck, real WinCE clang): FlushDCache,
 * FlushICache, SC_GetTickCount and KLocalFileTimeToFileTime were
 * declared here as plain prototypes AND again below in the tree's
 * canonical AKARI_CE_IMPORT + AKARI_CE_NAME form, harvested from the
 * ee4xxxxx page family for the same four functions.  Clang rejects
 * the pair (-Wdll-attribute-on-redeclaration), which broke
 * `make crosscheck` on this header for all six CE targets.  The
 * plain duplicates are removed and the import-attributed twins kept
 * (they carry the coredll/nk import spelling; dropping them would
 * change link-time name resolution).  The ms9xxxxx pages the removed
 * prints came from stated a generation where the surviving ee4xxxxx
 * pages do not, so that information is carried onto the twins below
 * rather than lost.  OEMCacheRangeFlush has no import-form twin and
 * is left exactly as it was. ------------------------ */

/* ms903218: page-printed prototype (Windows CE .NET 4.2 and later.; not applicable). */
void OEMCacheRangeFlush(LPVOID pAddr, DWORD dwLength, DWORD dwFlags);


/* ee478340 FlushDCache: print `void FlushDCache(void);`
 * (ee page states no generation; the ms902902 print of the same
 * function, removed as a duplicate above, stated Windows CE .NET 4.0
 * and later.; Link Library: nk.lib) */
/* ee478340: param-list verified against this page (proto-cite) */
/* ee478340: page print verified (proto-cite) */
AKARI_CE_IMPORT void FlushDCache(void) AKARI_CE_NAME(FlushDCache);

/* ee478614 SC_GetTickCount: print `DWORD SC_GetTickCount(void);`
 * (ee page states no generation; the ms903551 print of the same
 * function, removed as a duplicate above, stated Windows CE .NET 4.0
 * and later.; Link Library: nkstub.lib) */
AKARI_CE_IMPORT DWORD SC_GetTickCount(void) AKARI_CE_NAME(SC_GetTickCount);

/* ee479199 FlushICache: print `void FlushICache(void);`
 * (ee page states no generation; the ms902910 print of the same
 * function, removed as a duplicate above, stated Windows CE .NET 4.0
 * and later.; Link Library: nk.lib) */
AKARI_CE_IMPORT void FlushICache(void) AKARI_CE_NAME(FlushICache);

/* ee479202 KLocalFileTimeToFileTime: print `BOOL KLocalFileTimeToFileTime(
const FILETIME* lpft,
LPFILETIME lpst
);`
 * (ee page states no generation; the ms903211 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and
 * later. -- the earliest generation of the four; Link Library: nk.lib) */
AKARI_CE_IMPORT BOOL KLocalFileTimeToFileTime(const FILETIME *lpft, LPFILETIME lpst) AKARI_CE_NAME(KLocalFileTimeToFileTime);

#endif /* AKARI_KERNEL_H_ */
