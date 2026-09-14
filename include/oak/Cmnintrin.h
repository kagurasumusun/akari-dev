/*
 * Cmnintrin.h -- declarations recovered from the official
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

#ifndef AKARI_CMNINTRIN_H_
#define AKARI_CMNINTRIN_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms879734: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _disable(void);

/* ms879741: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _enable(void);

#endif /* AKARI_CMNINTRIN_H_ */
