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
 * prints a header for it; it is a common intrinsic, not a MIPS one.
 *
 * Audit 2026-09-14 (crosscheck-lc regression sweep, real WinCE clang):
 * discovered that `make crosscheck` already failed on this header on
 * both arm-pc-wince* and i386-pc-wince* targets, independent of any
 * case-aliasing work -- Clang/GCC provide `_ReturnAddress` as a
 * builtin returning `void *`, which conflicts with the page's `void`
 * return type. Guarding the redeclaration under those compilers (the
 * page's own printed type is still the one declared for any other
 * compiler) is the standard fix for an intrinsic that became a
 * compiler builtin after the CE-era page was written; it does not
 * change what is recorded as documented on the page. */
#if !defined(__GNUC__) && !defined(__clang__)
void _ReturnAddress(void);
#endif

#endif /* AKARI_CMNINTRIN_H_ */
