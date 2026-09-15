/*
 * Lt2pcfg.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: Lt2pcfg.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_LT2PCFG_H
#define AKARI_LT2PCFG_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ms893321 L2TP_CONFIG_DATA: page print
 * typedef struct _L2TP_CONFIG_DATA{ DWORDdwVersion;DWORDdwAuthType;DWORDdwFlags;DWORDcbKey;DWORDdwOffsetKey;DWORDcMyCerts;DWORDcRootCerts;DWORDdwOffsetC
 * (Windows CE .NET 4.2 and later.) */
typedef struct _L2TP_CONFIG_DATA {
    DWORD dwVersion;
    DWORD dwAuthType;
    DWORD dwFlags;
    DWORD cbKey;
    DWORD dwOffsetKey;
    DWORD cMyCerts;
    DWORD cRootCerts;
    DWORD dwOffsetCertHashes;
} L2TP_CONFIG_DATA, *PL2TP_CONFIG_DATA;

#endif /* AKARI_LT2PCFG_H */
