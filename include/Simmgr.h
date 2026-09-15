/*
 * Simmgr.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: simmgr.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_SIMMGR_H
#define AKARI_SIMMGR_H

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


/* ee497103 SIMLOCKINGPWDLENGTH: page print
 * typedef struct simlockingpwdlength { DWORD dwFacility; DWORD dwPasswordLength; } SIMLOCKINGPWDLENGTH, FAR *LPSIMLOCKINGPWDLENGTH;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simlockingpwdlength {
    DWORD dwFacility;
    DWORD dwPasswordLength;
} SIMLOCKINGPWDLENGTH, FAR *LPSIMLOCKINGPWDLENGTH;

/* ee497361 SIMPBECHANGE: page print
 * typedef struct simpbechange_tag { DWORD dwEntry; DWORD dwStorage; } SIMPBECHANGE, FAR *LPSIMPBECHANGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simpbechange_tag {
    DWORD dwEntry;
    DWORD dwStorage;
} SIMPBECHANGE, FAR *LPSIMPBECHANGE;

/* ee497628 SIMPHONEBOOKCAPS: page print
 * typedef struct simphonebookcaps_tag { DWORD cbSize; DWORD dwParams; DWORD dwStorages; DWORD dwMinIndex; DWORD dwMaxIndex; DWORD dwMaxAddressLength; DW
 * (generation not stated) */
typedef struct simphonebookcaps_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwStorages;
    DWORD dwMinIndex;
    DWORD dwMaxIndex;
    DWORD dwMaxAddressLength;
    DWORD dwMaxTextLength;
    DWORD dwMaxSecondNameLength;
    DWORD dwMaxAdditionalNumberLength;
    DWORD dwMaxEmailAddressLength;
    DWORD dwMaxGroupTagLength;
    DWORD dwMaxAdditionalNumberTagLength;
    DWORD dwAdditionalNumberCount;
    DWORD dwEmailAddressCount;
    DWORD dwMaxGroupTags;
    DWORD dwMaxAdditionalNumberTags;
    BOOL fHidden;
    BOOL fUid;
    DWORD dwMaxGroupIdCount;
} SIMPHONEBOOKCAPS, FAR *LPPHONEBOOKSIMCAPS;

/* ee497860 SIMMESSAGECHANGE: page print
 * typedef struct simmessagechange_tag { DWORD dwEntry; DWORD dwStorage; } SIMMESSAGECHANGE, FAR *LPSIMMESSAGECHANGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct simmessagechange_tag {
    DWORD dwEntry;
    DWORD dwStorage;
} SIMMESSAGECHANGE, FAR *LPSIMMESSAGECHANGE;

/* ee498275 SIMRECORDINFO: page print
 * typedef struct simrecordinfo_tag { DWORD cbSize; DWORD dwParams; DWORD dwRecordType; DWORD dwItemCount; DWORD dwSize; } SIMRECORDINFO, FAR *LPSIMRECOR
 * (Windows Embedded CE 6.0 and later) */
typedef struct simrecordinfo_tag {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwRecordType;
    DWORD dwItemCount;
    DWORD dwSize;
} SIMRECORDINFO, FAR *LPSIMRECORDINFO;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_SIMMGR_H */
