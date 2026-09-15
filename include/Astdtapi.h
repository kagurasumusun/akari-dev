/*
 * Astdtapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: astdtapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_ASTDTAPI_H
#define AKARI_ASTDTAPI_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee497280 tapiRequestMakeCall: print `LONG tapiRequestMakeCall (
LPCTSTR lpszDestAddress,
LPCTSTR lpszAppName,
LPCTSTR lpszCalledParty,
LPCTSTR lpszComment
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG tapiRequestMakeCall(LPCTSTR lpszDestAddress, LPCTSTR lpszAppName, LPCTSTR lpszCalledParty, LPCTSTR lpszComment) AKARI_CE_NAME(tapiRequestMakeCall);

#endif /* AKARI_ASTDTAPI_H */
