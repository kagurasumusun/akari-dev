/*
 * Tsp.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: tsp.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_TSP_H
#define AKARI_TSP_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee497030 CALLER_ID_OPTIONS: page print
 * enum CALLER_ID_OPTIONS { CALLER_ID_DEFAULT, CALLER_ID_BLOCK, CALLER_ID_PRESENT, };
 * (Windows Embedded CE 6.0 and later) */
typedef enum CALLER_ID_OPTIONS {
    CALLER_ID_DEFAULT,
    CALLER_ID_BLOCK,
    CALLER_ID_PRESENT
} CALLER_ID_OPTIONS;

/* ee497055 CELLBEARERINFO: page print
 * typedef struct cellbearerinfo_tag { DWORD dwSpeed; DWORD dwService; DWORD dwConnectionElement; } CELLBEARERINFO, *LPCELLBEARERINFO;
 * (Windows CE 3.0 and later) */
typedef struct cellbearerinfo_tag {
    DWORD dwSpeed;
    DWORD dwService;
    DWORD dwConnectionElement;
} CELLBEARERINFO, *LPCELLBEARERINFO;

/* ee497177 LINECALLPARAMSDEVSPECIFIC: page print
 * typedef struct linecallparamsdevspecific_tag { CALLER_ID_OPTIONS cidoOptions; } LINECALLPARAMSDEVSPECIFIC, *LPLINECALLPARAMSDEVSPECIFIC;
 * (Windows CE 3.0 and later) */
typedef struct linecallparamsdevspecific_tag {
    CALLER_ID_OPTIONS cidoOptions;
} LINECALLPARAMSDEVSPECIFIC, *LPLINECALLPARAMSDEVSPECIFIC;

/* ee497225 CELLDATACOMPINFO: page print
 * typedef struct celldatacompinfo_tag { DWORD dwDirection; BOOL dwRequired; DWORD dwMaxDictEntries; DWORD dwMaxStringLength; } CELLDATACOMPINFO, *LPCELL
 * (Windows CE 3.0 and later) */
typedef struct celldatacompinfo_tag {
    DWORD dwDirection;
    BOOL dwRequired;
    DWORD dwMaxDictEntries;
    DWORD dwMaxStringLength;
} CELLDATACOMPINFO, *LPCELLDATACOMPINFO;

/* ee497635 CELLRADIOLINKINFO: page print
 * typedef struct cellradiolinkinfo_tag { DWORD dwVersion; DWORD dwIws; DWORD dwMws; DWORD dwAckTimer; DWORD dwRetransmitAttempts; DWORD dwResequenceTime
 * (Windows CE 3.0 and later) */
typedef struct cellradiolinkinfo_tag {
    DWORD dwVersion;
    DWORD dwIws;
    DWORD dwMws;
    DWORD dwAckTimer;
    DWORD dwRetransmitAttempts;
    DWORD dwResequenceTimer;
} CELLRADIOLINKINFO, *LPCELLRADIOLINKINFO;

/* ee497892 CELLGPRSQOSSETTINGS: page print
 * typedef struct cellgprsqossettings_tag { DWORD dwPrecedenceClass; DWORD dwDelayClass; DWORD dwReliabilityClass; DWORD dwPeakThruClass; DWORD dwMeanThr
 * (Windows CE 3.0 and later) */
typedef struct cellgprsqossettings_tag {
    DWORD dwPrecedenceClass;
    DWORD dwDelayClass;
    DWORD dwReliabilityClass;
    DWORD dwPeakThruClass;
    DWORD dwMeanThruClass;
} CELLGPRSQOSSETTINGS, *LPCELLGPRSQOSSETTINGS;

#endif /* AKARI_TSP_H */
