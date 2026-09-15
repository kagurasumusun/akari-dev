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

/* _disable and _enable were declared here until M134.  The CE 5.0 pages
 * (ms933241, ms933277) print "Header: winnt.h" for both, and this header
 * includes Winnt.h, so the declarations moved there and are still
 * reachable from cmnintrin.h. */

/* ms933599 _ReturnAddress: print `void _ReturnAddress(void);`
 * (Windows CE .NET 4.0 and later; Header: cmnintrin.h).  Declared in
 * oak/Mipsintr.h until M134, which contradicted the only page that
 * prints a header for it; it is a common intrinsic, not a MIPS one. */
void _ReturnAddress(void);

#endif /* AKARI_CMNINTRIN_H_ */
