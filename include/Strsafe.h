/*
 * Strsafe.h -- safe string functions for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive).  Every page in this
 * book prints "Header: strsafe.h", "Link Library: strsafe.lib" and
 * "OS Versions: Windows CE 5.0 and later."
 *
 * This header did not exist in the tree until M134, which is why the
 * whole StringCch... and StringCb... family sat in the coverage audit's
 * "header not shipped here" bucket: the audit could name the gap but
 * nothing in include/ corresponded to the header the pages cite.
 * (The family names are spelled without a trailing asterisk here because
 * a star-slash inside a C comment ends it.)
 *
 * Not declared here: StringCbGetsEx (ms860404).  Its page prints
 * "Link Library: none." -- not a missing row, an explicit none -- so
 * marking it AKARI_CE_IMPORT would promise a symbol nothing provides.
 */

#ifndef AKARI_STRSAFE_H
#define AKARI_STRSAFE_H

#include "Windef.h"    /* LPTSTR, LPCTSTR, HRESULT, DWORD, size_t (<stddef.h>) */
#include <stdarg.h>    /* va_list: StringCbVPrintf ms860415, StringCbVPrintfEx
                        * ms860416, StringCchVPrintf ms860480, StringCchVPrintfEx
                        * ms860481 all take one as their last parameter */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* M134: declared from the official Windows CE pages cited on each
 *  prototype.  Every page prints Header: strsafe.h, Link Library: strsafe.lib
 *  and OS Versions: Windows CE 5.0 and later. */

/* ms860394 StringCbCat: print `HRESULT StringCbCat( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
/* ee480128: param-list verified against this page (proto-cite) */
/* ee480128: page print verified (proto-cite) */
AKARI_CE_IMPORT HRESULT StringCbCat(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc) AKARI_CE_NAME(StringCbCat);

/* ms860396 StringCbCatEx: print `HRESULT StringCbCatEx( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc,
LPTSTR *ppszDestEnd,
size_t *pcbRemaining,
DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCatEx(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc, LPTSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCbCatEx);

/* ms860397 StringCbCatN: print `HRESULT StringCbCatN( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc,
size_t cbMaxAppend
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCatN(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc, size_t cbMaxAppend) AKARI_CE_NAME(StringCbCatN);

/* ms860398 StringCbCatNEx: print `HRESULT StringCbCatNEx( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc,
size_t cbMaxAppend,
LPTSTR *ppszDestEnd,
size_t *pcbRemaining,
DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCatNEx(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc, size_t cbMaxAppend, LPTSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCbCatNEx);

/* ms860399 StringCbCopy: print `HRESULT StringCbCopy( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCopy(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc) AKARI_CE_NAME(StringCbCopy);

/* ms860400 StringCbCopyEx: print `HRESULT StringCbCopyEx( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc,
LPTSTR *ppszDestEnd,
size_t *pcbRemaining,
DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCopyEx(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc, LPTSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCbCopyEx);

/* ms860401 StringCbCopyN: print `HRESULT StringCbCopyN( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc,
size_t cbSrc
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCopyN(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc, size_t cbSrc) AKARI_CE_NAME(StringCbCopyN);

/* ms860402 StringCbCopyNEx: print `HRESULT StringCbCopyNEx( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszSrc,
size_t cbSrc,
LPTSTR *ppszDestEnd,
size_t *pcbRemaining,
DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbCopyNEx(LPTSTR pszDest, size_t cbDest, LPCTSTR pszSrc, size_t cbSrc, LPTSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCbCopyNEx);

/* ms860403 StringCbGets: print `HRESULT StringCbGets( LPTSTR pszDest,
size_t cbDest
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbGets(LPTSTR pszDest, size_t cbDest) AKARI_CE_NAME(StringCbGets);

/* ms860405 StringCbLength: print `HRESULT StringCbLength( LPCTSTR psz,
size_t cbMax,
size_t *pcb
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbLength(LPCTSTR psz, size_t cbMax, size_t *pcb) AKARI_CE_NAME(StringCbLength);

/* ms860406 StringCbPrintf: print `HRESULT StringCbPrintf( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszFormat,
...
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbPrintf(LPTSTR pszDest, size_t cbDest, LPCTSTR pszFormat, ...) AKARI_CE_NAME(StringCbPrintf);

/* ms860407 StringCbPrintfEx: print `HRESULT StringCbPrintfEx( LPTSTR pszDest,
size_t cbDest,
LPTSTR *ppszDestEnd,
size_t *pcbRemaining,
DWORD dwFlags,
LPCTSTR pszFormat,
...
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbPrintfEx(LPTSTR pszDest, size_t cbDest, LPTSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags, LPCTSTR pszFormat, ...) AKARI_CE_NAME(StringCbPrintfEx);

/* ms860408 StringCbVPrintf: print `HRESULT StringCbVPrintf( LPTSTR pszDest,
size_t cbDest,
LPCTSTR pszFormat,
va_list argList);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbVPrintf(LPTSTR pszDest, size_t cbDest, LPCTSTR pszFormat, va_list argList) AKARI_CE_NAME(StringCbVPrintf);

/* ms860409 StringCbVPrintfEx: print `HRESULT StringCbVPrintfEx( LPTSTR pszDest,
size_t cbDest,
LPTSTR *ppszDestEnd,
size_t *pcbRemaining,
DWORD dwFlags,
LPCTSTR pszFormat,
va_list argList);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCbVPrintfEx(LPTSTR pszDest, size_t cbDest, LPTSTR *ppszDestEnd, size_t *pcbRemaining, DWORD dwFlags, LPCTSTR pszFormat, va_list argList) AKARI_CE_NAME(StringCbVPrintfEx);

/* ms860410 StringCchCat: print `HRESULT StringCchCat(
LPTSTR pszDest,
size_t cchDest,
LPCTSTR pszSrc
);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCat(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc) AKARI_CE_NAME(StringCchCat);

/* ms860411 StringCchCatEx: print `HRESULT StringCchCatEx( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCatEx(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCchCatEx);

/* ms860413 StringCchCatN: print `HRESULT StringCchCatN( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchMaxAppend);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCatN(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchMaxAppend) AKARI_CE_NAME(StringCchCatN);

/* ms860415 StringCchCatNEx: print `HRESULT StringCchCatNEx( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchMaxAppend, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCatNEx(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchMaxAppend, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCchCatNEx);

/* ms860418 StringCchCopy: print `HRESULT StringCchCopy( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCopy(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc) AKARI_CE_NAME(StringCchCopy);

/* ms860420 StringCchCopyEx: print `HRESULT StringCchCopyEx( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCopyEx(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCchCopyEx);

/* ms860422 StringCchCopyN: print `HRESULT StringCchCopyN( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchSrc);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCopyN(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchSrc) AKARI_CE_NAME(StringCchCopyN);

/* ms860424 StringCchCopyNEx: print `HRESULT StringCchCopyNEx( LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchSrc, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchCopyNEx(LPTSTR pszDest, size_t cchDest, LPCTSTR pszSrc, size_t cchSrc, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCchCopyNEx);

/* ms860427 StringCchGets: print `HRESULT StringCchGets( LPTSTR pszDest, size_t cchDest);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchGets(LPTSTR pszDest, size_t cchDest) AKARI_CE_NAME(StringCchGets);

/* ms860429 StringCchGetsEx: print `HRESULT StringCchGetsEx( LPTSTR pszDest, size_t cchDest, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchGetsEx(LPTSTR pszDest, size_t cchDest, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags) AKARI_CE_NAME(StringCchGetsEx);

/* ms860431 StringCchLength: print `HRESULT StringCchLength( LPCTSTR psz, size_t cchMax, size_t *pcch);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchLength(LPCTSTR psz, size_t cchMax, size_t *pcch) AKARI_CE_NAME(StringCchLength);

/* ms860433 StringCchPrintf: print `HRESULT StringCchPrintf( LPTSTR pszDest, size_t cchDest, LPCTSTR pszFormat, ...);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchPrintf(LPTSTR pszDest, size_t cchDest, LPCTSTR pszFormat, ...) AKARI_CE_NAME(StringCchPrintf);

/* ms860435 StringCchPrintfEx: print `HRESULT StringCchPrintfEx( LPTSTR pszDest, size_t cchDest, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags, LPCTSTR pszFormat, ...);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchPrintfEx(LPTSTR pszDest, size_t cchDest, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags, LPCTSTR pszFormat, ...) AKARI_CE_NAME(StringCchPrintfEx);

/* ms860438 StringCchVPrintf: print `HRESULT StringCchVPrintf( LPTSTR pszDest, size_t cchDest, LPCTSTR pszFormat, va_list argList);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchVPrintf(LPTSTR pszDest, size_t cchDest, LPCTSTR pszFormat, va_list argList) AKARI_CE_NAME(StringCchVPrintf);

/* ms860440 StringCchVPrintfEx: print `HRESULT StringCchVPrintfEx( LPTSTR pszDest, size_t cchDest, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags, LPCTSTR pszFormat, va_list argList);`
 * (Windows CE 5.0 and later.; Link Library: strsafe.lib) */
AKARI_CE_IMPORT HRESULT StringCchVPrintfEx(LPTSTR pszDest, size_t cchDest, LPTSTR *ppszDestEnd, size_t *pcchRemaining, DWORD dwFlags, LPCTSTR pszFormat, va_list argList) AKARI_CE_NAME(StringCchVPrintfEx);

#endif /* AKARI_STRSAFE_H */
