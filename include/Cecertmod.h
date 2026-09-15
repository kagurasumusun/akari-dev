/*
 * Cecertmod.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: cecertmod.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CECERTMOD_H
#define AKARI_CECERTMOD_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee498571 CertVerify: print `DWORD CertVerify (
HANDLE hFile,
LPCWSTR pszFileName,
LPWSTR pUserName,
DWORD cchUserName,
LPDWORD pdwCertFlags
);`
 * (Windows Embedded CE 6.0 and later; Link Library: Certmod.dll) */
AKARI_CE_IMPORT DWORD CertVerify(HANDLE hFile, LPCWSTR pszFileName, LPWSTR pUserName, DWORD cchUserName, LPDWORD pdwCertFlags) AKARI_CE_NAME(CertVerify);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_CECERTMOD_H */
