/*
 * Oemwake.h -- declarations recovered from the official
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

#ifndef AKARI_OEMWAKE_H_
#define AKARI_OEMWAKE_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms903220: page-printed prototype (Windows CE .NET 4.1 and later.; platform oal). */
void OEMClearIntSources(void);

/* ms903228: page-printed prototype (Windows CE .NET 4.1 and later.; platform oal). */
DWORD OEMGetWakeupSource(void);

/* ms903230: page-printed prototype (Windows CE .NET 4.1 and later.; platform oal). */
void OEMIndicateIntSource(DWORD dwSources);

/* ms903237: page-printed prototype (Windows CE .NET 4.1 and later.; platform oal). */
DWORD OEMPowerManagerInit(void);

/* ms903294: page-printed prototype (Windows CE .NET 4.1 and later.; platform oal). */
DWORD OEMResetWakeupSource(DWORD dwSources);

/* ms903523: page-printed prototype (Windows CE .NET 4.1 and later.; platform oal). */
DWORD OEMSetWakeupSource(DWORD dwSources);

#endif /* AKARI_OEMWAKE_H_ */
