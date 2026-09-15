/*
 * Rapitypes2.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: rapitypes2.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_RAPITYPES2_H
#define AKARI_RAPITYPES2_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Rapitypes.h"   /* RAPI_CONNECTIONTYPE (ee497483) and RAPI_DEVICESTATUS (ee496793) are documented under rapitypes2.h */
#include "Objbase.h"   /* BSTR */



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee496442 RAPIDEVICEID: page print
 * typedef GUID RAPIDEVICEID;
 * (Windows Embedded CE 6.0 and later) */
typedef GUID RAPIDEVICEID;

/* ee496614 RAPI_DEVICEINFO: page print
 * typedef struct { RAPIDEVICEID DeviceId; DWORD dwOsVersionMajor; DWORD dwOsVersionMinor; BSTR bstrName; BSTR bstrPlatform; } RAPI_DEVICEINFO;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    RAPIDEVICEID DeviceId;
    DWORD dwOsVersionMajor;
    DWORD dwOsVersionMinor;
    BSTR bstrName;
    BSTR bstrPlatform;
} RAPI_DEVICEINFO;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_RAPITYPES2_H */
