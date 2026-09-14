/*
 * Profiler.h -- declarations recovered from the official
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

#ifndef AKARI_PROFILER_H_
#define AKARI_PROFILER_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms919031: page-printed prototype (Windows CE 2.10 and later.; nkprof.lib). */
void OEMProfileTimerDisable(void);

/* ms919045: page-printed prototype (Windows CE 2.10 and later.; nkprof.lib). */
void OEMProfileTimerEnable(DWORD dwUSecInterval);

/* _wcepb_ProfileStart: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT VOID ProfileStart(DWORD dwUSecInterval, DWORD dwOptions) AKARI_CE_NAME(ProfileStart);

/* _wcepb_ProfileStop: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT VOID ProfileStop(void) AKARI_CE_NAME(ProfileStop);

#endif /* AKARI_PROFILER_H_ */
