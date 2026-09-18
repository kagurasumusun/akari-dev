/*
 * Profiler.h -- declarations recovered from the official
 * page prints (tools/decl-d1.py, M105 header creation).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own
 * print (page id cited).  Prints whose types include/
 * cannot yet resolve are recorded verbatim in the
 * header comment blocks by later passes; nothing is
 * dropped or invented.
 */

#ifndef AKARI_PROFILER_H_
#define AKARI_PROFILER_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms919031: page-printed prototype (Windows CE 2.10 and later.; nkprof.lib). */
void OEMProfileTimerDisable(void);

/* ms919045: page-printed prototype (Windows CE 2.10 and later.; nkprof.lib). */
void OEMProfileTimerEnable(DWORD dwUSecInterval);

/* _wcepb_ProfileStart: page-printed prototype (Windows CE OS). */
/* ee482995: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT VOID ProfileStart(DWORD dwUSecInterval, DWORD dwOptions) AKARI_CE_NAME(ProfileStart);

/* _wcepb_ProfileStop: page-printed prototype (Windows CE OS). */
/* ee482806: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT VOID ProfileStop(void) AKARI_CE_NAME(ProfileStop);


/* --- absent-surface pass 2026-09-18: coredll-exported functions
 * whose pages print "Link Library: Coredll.lib" (docs/absent-funcprints
 * -2026-09-18.tsv). ------------------------------------------- */

/* ms886778 ProfilerControl: page print
 * typedef struct ProfilerControl {DWORD dwVersion;DWORD dwOptions;
 * DWORD dwReserved; union { struct { DWORD dwUSecInterval; } Kernel;
 * struct { DWORD dwProcessorType; DWORD dwControlSize;
 * BYTE bHardwareSpecificSettings[0]; } OEM; };} ProfilerControl; */
typedef struct ProfilerControl {
    DWORD dwVersion;
    DWORD dwOptions;
    DWORD dwReserved;
    union {
        struct {
            DWORD dwUSecInterval;
        } Kernel;
        struct {
            DWORD dwProcessorType;
            DWORD dwControlSize;
            BYTE  bHardwareSpecificSettings[0];
        } OEM;
    };
} ProfilerControl;

/* ms886763 OEMProfilerData: page print
 * typedef struct OEMProfilerData {DWORD ra;DWORD dwBufSize;
 * BYTE buf[0];} OEMProfilerData; */
typedef struct OEMProfilerData {
    DWORD ra;
    DWORD dwBufSize;
    BYTE  buf[0];
} OEMProfilerData;

/* ms886776(v=msdn.10) ProfileCaptureStatus: page print `VOID ProfileCaptureStatus();`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT VOID ProfileCaptureStatus(void) AKARI_CE_NAME(ProfileCaptureStatus);

/* ms886782(v=msdn.10) ProfileStartEx: page print `VOID ProfileStartEx( ProfilerControl* pControl );`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT VOID ProfileStartEx(ProfilerControl*pControl) AKARI_CE_NAME(ProfileStartEx);

/* ms886780(v=msdn.10) ProfilerHitEx: page print `VOID ProfilerHitEx( OEMProfilerData* pData);`
 * (Link Library: Coredll.lib) */
AKARI_CE_IMPORT VOID ProfilerHitEx(OEMProfilerData*pData) AKARI_CE_NAME(ProfilerHitEx);

#endif /* AKARI_PROFILER_H_ */
