/*
 * Cs.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: cs.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CS_H
#define AKARI_CS_H

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


/* ee481240 CSPROPERTY_CONNECTION: page print
 * typedef enum { CSPROPERTY_CONNECTION_STATE, CSPROPERTY_CONNECTION_DATAFORMAT, CSPROPERTY_CONNECTION_ALLOCATORFRAMING, CSPROPERTY_CONNECTION_PROPOSEDAT
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    CSPROPERTY_CONNECTION_STATE,
    CSPROPERTY_CONNECTION_DATAFORMAT,
    CSPROPERTY_CONNECTION_ALLOCATORFRAMING,
    CSPROPERTY_CONNECTION_PROPOSEDATAFORMAT,
    CSPROPERTY_CONNECTION_ALLOCATORFRAMING_EX
} CSPROPERTY_CONNECTION;

/* ee483400 CSDATAFORMAT: page print
 * typedef struct { ULONG FormatSize; ULONG Flags; ULONG SampleSize; ULONG Reserved; GUID MajorFormat; GUID SubFormat; GUID Specifier; } CSDATAFORMAT, *P
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG FormatSize;
    ULONG Flags;
    ULONG SampleSize;
    ULONG Reserved;
    GUID MajorFormat;
    GUID SubFormat;
    GUID Specifier;
} CSDATAFORMAT, *PCSDATAFORMAT, CSDATARANGE, *PCSDATARANGE;

/* ee483433 CSTIME: page print
 * typedef struct { LONGLONG Time; ULONG Numerator; ULONG Denominator; } CSTIME, *PCSTIME;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    LONGLONG Time;
    ULONG Numerator;
    ULONG Denominator;
} CSTIME, *PCSTIME;

/* ee484198 CSPIN_CINSTANCES: page print
 * typedef struct { ULONG PossibleCount; ULONG CurrentCount; } CSPIN_CINSTANCES, *PCSPIN_CINSTANCES;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG PossibleCount;
    ULONG CurrentCount;
} CSPIN_CINSTANCES, *PCSPIN_CINSTANCES;

/* ee484262 CSMULTIPLE_ITEM: page print
 * typedef struct { ULONG Size; ULONG Count; } CSMULTIPLE_ITEM, *PCSMULTIPLE_ITEM;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG Size;
    ULONG Count;
} CSMULTIPLE_ITEM, *PCSMULTIPLE_ITEM;

/* ee484413 CSSTATE: page print
 * typedef enum { CSSTATE_STOP, CSSTATE_PAUSE, CSSTATE_RUN } CSSTATE, *PCSSTATE;
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    CSSTATE_STOP,
    CSSTATE_PAUSE,
    CSSTATE_RUN
} CSSTATE, *PCSSTATE;

/* ee484426 CSPROPERTY_MEMBERSHEADER: page print
 * typedef struct { ULONG MembersFlags; ULONG MembersSize; ULONG MembersCount; ULONG Flags; } CSPROPERTY_MEMBERSHEADER, *PCSPROPERTY_MEMBERSHEADER;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG MembersFlags;
    ULONG MembersSize;
    ULONG MembersCount;
    ULONG Flags;
} CSPROPERTY_MEMBERSHEADER, *PCSPROPERTY_MEMBERSHEADER;

/* ee485040 CS_COMPRESSION: page print
 * typedef struct { ULONG RatioNumerator; ULONG RatioDenominator; ULONG RatioConstantMargin; } CS_COMPRESSION, *PCS_COMPRESSION;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG RatioNumerator;
    ULONG RatioDenominator;
    ULONG RatioConstantMargin;
} CS_COMPRESSION, *PCS_COMPRESSION;

/* ee485486 CS_FRAMING_RANGE: page print
 * typedef struct { ULONG MinFrameSize; ULONG MaxFrameSize; ULONG Stepping; } CS_FRAMING_RANGE, *PCS_FRAMING_RANGE;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG MinFrameSize;
    ULONG MaxFrameSize;
    ULONG Stepping;
} CS_FRAMING_RANGE, *PCS_FRAMING_RANGE;

/* ee486638 CSPROPERTY_PIN: page print
 * typedef enum { CSPROPERTY_PIN_CINSTANCES = 0, CSPROPERTY_PIN_CTYPES, CSPROPERTY_PIN_DATARANGES, CSPROPERTY_PIN_DATAINTERSECTION, CSPROPERTY_PIN_CATEGO
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    CSPROPERTY_PIN_CINSTANCES = 0,
    CSPROPERTY_PIN_CTYPES,
    CSPROPERTY_PIN_DATARANGES,
    CSPROPERTY_PIN_DATAINTERSECTION,
    CSPROPERTY_PIN_CATEGORY,
    CSPROPERTY_PIN_NAME
} CSPROPERTY_PIN;


/* ee481459 CSPROPERTY_MEMBERSLIST: page print
 * typedef struct { CSPROPERTY_MEMBERSHEADER MembersHeader; const VOID* Members; } CSPROPERTY_MEMBERSLIST, *PCSPROPERTY_MEMBERSLIST;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    CSPROPERTY_MEMBERSHEADER MembersHeader;
    const VOID *Members;
} CSPROPERTY_MEMBERSLIST, *PCSPROPERTY_MEMBERSLIST;

/* ee482468 CS_FRAMING_RANGE_WEIGHTED: page print
 * typedef struct { CS_FRAMING_RANGE Range; ULONG InPlaceWeight; ULONG NotInPlaceWeight; } CS_FRAMING_RANGE_WEIGHTED, *PCS_FRAMING_RANGE_WEIGHTED;
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    CS_FRAMING_RANGE Range;
    ULONG InPlaceWeight;
    ULONG NotInPlaceWeight;
} CS_FRAMING_RANGE_WEIGHTED, *PCS_FRAMING_RANGE_WEIGHTED;

/* ee483430 CSSTREAM_HEADER: page print
 * typedef struct { ULONG Size; ULONG TypeSpecificFlags; CSTIME PresentationTime; LONGLONG Duration; ULONG FrameExtent; ULONG DataUsed; PVOID Data; ULONG
 * (Windows Embedded CE 6.0 and later) */
typedef struct {
    ULONG Size;
    ULONG TypeSpecificFlags;
    CSTIME PresentationTime;
    LONGLONG Duration;
    ULONG FrameExtent;
    ULONG DataUsed;
    PVOID Data;
    ULONG OptionsFlags;
} CSSTREAM_HEADER, *PCSSTREAM_HEADER;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_CS_H */
