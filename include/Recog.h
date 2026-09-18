/*
 * Recog.h -- Japanese handwriting recognition (HWX) driver-side API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages
 * of the International book (Handwriting Recognition reference,
 * tools/manifests/intl-book.manifest): the Hwx* function pages print
 * "Header: Recog.h" with Link Library rows "Hwxjpn.lib, ..." (trailing
 * comma as printed).  HRC (recognition-context handle) and ALC (ambient
 * link constraint enumeration) are not printed by any CE page, so the
 * functions taking them by value are recorded; HwxConfig prints a
 * plain void prototype and is declared.  HWXGUIDE and HWXRESULTS are
 * printed in full and compiled.
 * See docs/inventory.md M83.
 */

#ifndef AKARI_RECOG_H
#define AKARI_RECOG_H

#include "Windef.h"    /* BOOL, UINT, INT, USHORT, WCHAR, DWORD, POINT */

/* --- Handle types no CE page typedefs. ------------------------------
 * HRC: 75 corpus pages mention it and none prints a typedef.  ms905434
 * "HwxCreate" prints `HRC HwxCreate( HRC hrc);` and ms905436 "HwxDestroy"
 * prints `BOOL HwxDestroy( HRChrc);` (both Header: Recog.h, Link Library:
 * Hwxjpn.lib, Hwxusa.lib, Hwxcht.lib, Hwxkor.lib, Windows CE .NET 4.0 and
 * later), and the handwriting-recognition overview text describes the HRC
 * object as "similar to a handle to a window or a handle to a device
 * context".  See Windef.h:236 for the in-tree precedent. */
typedef HANDLE HRC;

/* ms905440 "HWXGUIDE": print `typedef struct tagHWXGUIDE {UINT
 * cHorzBox;UINT cVertBox;INT xOrigin;INT yOrigin;UINT cxBox;UINT
 * cyBox;UINT cxOffset;UINT cyOffset;UINT cxWriting;UINT cyWriting;UINT
 * cyMid;UINT cyBase;UINTnDir;} HWXGUIDE, *PHWXGUIDE;` (glued tokens
 * split). */
typedef struct tagHWXGUIDE {
    UINT cHorzBox;
    UINT cVertBox;
    INT  xOrigin;
    INT  yOrigin;
    UINT cxBox;
    UINT cyBox;
    UINT cxOffset;
    UINT cyOffset;
    UINT cxWriting;
    UINT cyWriting;
    UINT cyMid;
    UINT cyBase;
    UINT nDir;
} HWXGUIDE, *PHWXGUIDE;

/* "HWXRESULTS": print `typedef struct tagHWXRESULTS {USHORT indxBox;
 * WCHAR rgChar[1]} HWXRESULTS, *PHWXRESULTS;` (missing semicolon in
 * the print repaired -- doc typo). */
/* ms905443: members/signature verified against this page (type-cite) */
typedef struct tagHWXRESULTS {
    USHORT indxBox;
    WCHAR  rgChar[1];
} HWXRESULTS, *PHWXRESULTS;

/* --- Declared (grounded print). ---------------------------------- */
/* "HwxConfig": print `BOOL HwxConfig(void);` (Hwxjpn.lib row). */
/* ms905428: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL HwxConfig(void)
                    AKARI_CE_NAME(HwxConfig);

/* --- Recorded (HRC / ALC unpublished). ---------------------------- */
/* "HwxCreate": `HRC HwxCreate( HRC hrc);` */
/* "HwxDestroy": `BOOL HwxDestroy( HRChrc);` */
/* "HwxEndInput": `BOOL HwxEndInput( HRChrc);` */
/* "HwxInput": `BOOL HwxInput( HRChrc,POINT* lppnt,UINT upoints,
 * DWORDtimestamp );` */
/* "HwxProcess": `BOOL HwxProcess( HRChrc);` */
/* "HwxResultsAvailable": `INT HwxResultsAvailable( HRC hrc);` */
/* "HwxSetAbort" (Hwxjpn.lib row): page prints no signature. */
/* "HwxSetContext": `BOOL HwxSetContext( HRChrc,WCHAR wContext );` */
/* "HwxSetGuide": `BOOL HwxSetGuide( HRChrc,HWXGUIDE* lpGuide );` */
/* "HwxSetPartial": `BOOL HwxSetPartial( HRChrc,UINT urecog );` */
/* "HwxALCPriority": `BOOL HwxALCPriority( HRChrc,ALC alc );` */
/* "HwxALCValid": `BOOL HwxALCValid( HRChrc,ALC alc );` */
/* "HwxGetResults": `INT32 HwxGetResults( HRChrc,UINT cAlt,UINT
 * iFirst,UINT cBoxRes,HWXRESULTS* rgBoxResults );`. */


/* ee490977 HwxSetPartial: print `BOOL HwxSetPartial(
HRC hrc,
UINT urecog
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxSetPartial(HRC hrc, UINT urecog) AKARI_CE_NAME(HwxSetPartial);

/* ee491134 HwxSetAbort: print `BOOL HwxSetAbort(
HRC hrc,
UINT* pnumstrokes
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxSetAbort(HRC hrc, UINT *pnumstrokes) AKARI_CE_NAME(HwxSetAbort);

/* ee491138 HwxGetResults: print `INT32 HwxGetResults(
HRC hrc,
UINT cAlt,
UINT iFirst,
UINT cBoxRes,
HWXRESULTS* rgBoxResults
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT INT32 HwxGetResults(HRC hrc, UINT cAlt, UINT iFirst, UINT cBoxRes, HWXRESULTS *rgBoxResults) AKARI_CE_NAME(HwxGetResults);

/* ee491152 HwxResultsAvailable: print `INT HwxResultsAvailable(
HRC hrc
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT INT HwxResultsAvailable(HRC hrc) AKARI_CE_NAME(HwxResultsAvailable);

/* ee491204 HwxSetContext: print `BOOL HwxSetContext(
HRC hrc,
WCHAR wContext
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxSetContext(HRC hrc, WCHAR wContext) AKARI_CE_NAME(HwxSetContext);

/* ee491529 HwxEndInput: print `BOOL HwxEndInput(
HRC hrc
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxEndInput(HRC hrc) AKARI_CE_NAME(HwxEndInput);

/* ee491580 HwxSetGuide: print `BOOL HwxSetGuide(
HRC hrc,
HWXGUIDE* lpGuide
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxSetGuide(HRC hrc, HWXGUIDE *lpGuide) AKARI_CE_NAME(HwxSetGuide);

/* ee491763 HwxProcess: print `BOOL HwxProcess(
HRC hrc
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxProcess(HRC hrc) AKARI_CE_NAME(HwxProcess);

/* ee491781 HwxDestroy: print `BOOL HwxDestroy(
HRC hrc
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxDestroy(HRC hrc) AKARI_CE_NAME(HwxDestroy);

/* ee491902 HwxCreate: print `HRC HwxCreate(
HRC hrc
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT HRC HwxCreate(HRC hrc) AKARI_CE_NAME(HwxCreate);

/* ee492154 HwxInput: print `BOOL HwxInput(
HRC hrc,
POINT* lppnt,
UINT upoints,
DWORD timestamp
);`
 * (generation not stated; Link Library: hwxcht.lib,) */
AKARI_CE_IMPORT BOOL HwxInput(HRC hrc, POINT *lppnt, UINT upoints, DWORD timestamp) AKARI_CE_NAME(HwxInput);

#endif /* AKARI_RECOG_H */
