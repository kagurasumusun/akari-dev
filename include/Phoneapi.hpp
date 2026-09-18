/*
 * Phoneapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: phoneapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_PHONEAPI_H
#define AKARI_PHONEAPI_H

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


/* ee500412 PHProcessProvisionXML: print `HRESULT PHProcessProvisionXML(
const WCHAR* pInputBuffer,
WCHAR** ppOutputBuffer
);`
 * (Windows Embedded CE 6.0; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHProcessProvisionXML(const WCHAR *pInputBuffer, WCHAR **ppOutputBuffer) AKARI_CE_NAME(PHProcessProvisionXML);

/* ee500691 PHOnHookDialing: print `HRESULT PHOnHookDialing(
const WCHAR CurrentChar
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHOnHookDialing(const WCHAR CurrentChar) AKARI_CE_NAME(PHOnHookDialing);

/* ee501635 PHValidateProvisionXML: print `HRESULT PHValidateProvisionXML(
const WCHAR* pInputBuffer
);`
 * (Windows Embedded CE 6.0; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHValidateProvisionXML(const WCHAR *pInputBuffer) AKARI_CE_NAME(PHValidateProvisionXML);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_PHONEAPI_H */
