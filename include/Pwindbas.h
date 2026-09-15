/*
 * Pwindbas.h -- declarations recovered from the official
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

#ifndef AKARI_PWINDBAS_H_
#define AKARI_PWINDBAS_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Windbase.h"   /* 1 declaration(s) whose official pages print
                    * "Header: Pwindbas.h" are carried there, so including it
                    * makes <Pwindbas.h> provide them as those pages promise
                    * (docs/header-placement-audit.md). */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_GetSystemMemoryDivision: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL GetSystemMemoryDivision(LPDWORD lpdwStorePages, LPDWORD lpdwRamPages, LPDWORD lpdwPageSize) AKARI_CE_NAME(GetSystemMemoryDivision);

/* _wcepb_SetSystemMemoryDivision: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT DWORD SetSystemMemoryDivision(DWORD dwStorePages) AKARI_CE_NAME(SetSystemMemoryDivision);

#endif /* AKARI_PWINDBAS_H_ */
