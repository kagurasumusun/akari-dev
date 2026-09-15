/*
 * Cfgmgrapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: cfgmgrapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CFGMGRAPI_H
#define AKARI_CFGMGRAPI_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee497867 DMProcessConfigXML: print `HRESULT DMProcessConfigXML(
LPCWSTR pszWXMLin,
DWORD dwFlags,
LPWSTR* ppszwXMLout
);`
 * (generation not stated; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT DMProcessConfigXML(LPCWSTR pszWXMLin, DWORD dwFlags, LPWSTR *ppszwXMLout) AKARI_CE_NAME(DMProcessConfigXML);

#endif /* AKARI_CFGMGRAPI_H */
