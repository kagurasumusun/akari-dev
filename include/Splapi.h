/*
 * Splapi.h -- Windows CE book-surface header of record (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  Source book(s): the Speech UI
 * (Splapi.h) pages of the CE 5.0 archive plus their Windows CE SDK
 * reference twins.  Signatures are the pages' own prints; glued print
 * artifacts are split for compilation and the verbatim prints are
 * recorded in the per-row comments.
 *
 * This header is the missing Splapi.h of the M107 census: it is named
 * as the Header row by 32 official pages and carried no content
 * anywhere in the tree before (the M100 bridge removal had left it
 * out; it is not a bridge -- every row here is new).
 */

#ifndef AKARI_SPLAPI_H
#define AKARI_SPLAPI_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------
 * Book surface: Speech UI (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */

/* HSPL: referenced by every Spl* prototype; no page prints a layout or
 * a typedef for it (the Splapi.h pages name the type only), so it is
 * carried as an opaque handle type. */
typedef struct HSPL HSPL;

/* SPLSUGGEST -- page print (ms907067, Windows CE 5.0; Header:
 * Splapi.h.; twin _wcesdk_SPLSUGGEST_str, same layout):
 *   typedef struct tagSPLSUGGEST{
 *       WCHAR* pwsz;
 *       DWORD nScore;
 *   } SPLSUGGEST, *PSPLSUGGEST; */
typedef struct tagSPLSUGGEST {
    WCHAR* pwsz;
    DWORD  nScore;
} SPLSUGGEST, *PSPLSUGGEST;

/* SPLBUFFER -- page print (ms926850, Windows CE 5.0; Header: Splapi.h.;
 * twin _wcesdk_SPLBUFFER_str, same layout):
 *   typedef struct tagSPLBUFFER{
 *       const WCHAR* pwszIn;
 *       WCHAR* pwszOut;
 *       SPLSUGGEST aspl[8];
 *       DWORD iwcIn;
 *       DWORD cwcIn;
 *       DWORD dwMode;
 *       DWORD cwcOut;
 *       DWORD cwcUsed;
 *       DWORD dwErr;
 *       DWORD iwcErr;
 *       DWORD cwcErr;
 *       DWORD cspl;
 *   } SPLBUFFER, *PSPLBUFFER; */
typedef struct tagSPLBUFFER {
    const WCHAR* pwszIn;
    WCHAR*       pwszOut;
    SPLSUGGEST   aspl[8];
    DWORD        iwcIn;
    DWORD        cwcIn;
    DWORD        dwMode;
    DWORD        cwcOut;
    DWORD        cwcUsed;
    DWORD        dwErr;
    DWORD        iwcErr;
    DWORD        cwcErr;
    DWORD        cspl;
} SPLBUFFER, *PSPLBUFFER;

/* _wcesdk_SplAddUserDict SplAddUserDict: print `int SplAddUserDict( HSPL hspl , int nID, const WCHAR * pwszAdd , const WCHAR * pwszChange );`  [twin page(s): ms926842] */
AKARI_CE_IMPORT int SplAddUserDict(HSPL hspl, int nID, const WCHAR* pwszAdd, const WCHAR* pwszChange)
    AKARI_CE_NAME(SplAddUserDict);
/* _wcesdk_SplCheck SplCheck: print `int SplCheck( HSPL hspl , SPLBUFFER * psb );`  [twin page(s): ms926858] */
AKARI_CE_IMPORT int SplCheck(HSPL hspl, SPLBUFFER* psb)
    AKARI_CE_NAME(SplCheck);
/* _wcesdk_SplClrUserDict SplClrUserDict: print `int SplClrUserDict( HSPL hspl , int nID );`  [twin page(s): ms926865] */
AKARI_CE_IMPORT int SplClrUserDict(HSPL hspl, int nID)
    AKARI_CE_NAME(SplClrUserDict);
/* _wcesdk_SplEnumUserDict SplEnumUserDict: print `int SplEnumUserDict( HSPL hspl , int nID , DWORD nIndex , SPLBUFFER * psb );`  [twin page(s): ms926873] */
AKARI_CE_IMPORT int SplEnumUserDict(HSPL hspl, int nID, DWORD nIndex, SPLBUFFER* psb)
    AKARI_CE_NAME(SplEnumUserDict);
/* _wcesdk_SplInit SplInit: print `int SplInit( HSPL * phspl , int clex , WCHAR ** ppwsz );`  [twin page(s): ms926880] */
AKARI_CE_IMPORT int SplInit(HSPL* phspl, int clex, WCHAR** ppwsz)
    AKARI_CE_NAME(SplInit);
/* _wcesdk_SplLimitGet SplLimitGet: print `int SplLimitGet( HSPL hspl , DWORD * pdw );`  [twin page(s): ms926886] */
AKARI_CE_IMPORT int SplLimitGet(HSPL hspl, DWORD* pdw)
    AKARI_CE_NAME(SplLimitGet);
/* _wcesdk_SplLimitSet SplLimitSet: print `int SplLimitSet ( HSPL hspl , DWORD dw );`  [twin page(s): ms926893] */
AKARI_CE_IMPORT int SplLimitSet(HSPL hspl, DWORD dw)
    AKARI_CE_NAME(SplLimitSet);
/* _wcesdk_SplOptionGet SplOptionGet: print `int SplOptionGet( HSPL hspl , DWORD * pdw );`  [twin page(s): ms926898] */
AKARI_CE_IMPORT int SplOptionGet(HSPL hspl, DWORD* pdw)
    AKARI_CE_NAME(SplOptionGet);
/* _wcesdk_SplOptionSet SplOptionSet: print `int SplOptionSet ( HSPL hspl , DWORD dw );`  [twin page(s): ms926904] */
AKARI_CE_IMPORT int SplOptionSet(HSPL hspl, DWORD dw)
    AKARI_CE_NAME(SplOptionSet);
/* _wcesdk_SplQuit SplQuit: print `int SplQuit ( HSPL hspl );`  [twin page(s): ms926914] */
AKARI_CE_IMPORT int SplQuit(HSPL hspl)
    AKARI_CE_NAME(SplQuit);
/* _wcesdk_SplRemUserDict SplRemUserDict: print `int SplRemUserDict ( HSPL hspl , int nID, const WCHAR * pwsz );`  [twin page(s): ms926921] */
AKARI_CE_IMPORT int SplRemUserDict(HSPL hspl, int nID, const WCHAR* pwsz)
    AKARI_CE_NAME(SplRemUserDict);
/* _wcesdk_SplReplace SplReplace: print `int SplReplace( HSPL hspl , SPLBUFFER * psb );`  [twin page(s): ms926925] */
AKARI_CE_IMPORT int SplReplace(HSPL hspl, SPLBUFFER* psb)
    AKARI_CE_NAME(SplReplace);
/* _wcesdk_SplSizeUserDict SplSizeUserDict: print `int SplSizeUserDict( HSPL hspl , int nID , DWORD * pdw );`  [twin page(s): ms926932] */
AKARI_CE_IMPORT int SplSizeUserDict(HSPL hspl, int nID, DWORD* pdw)
    AKARI_CE_NAME(SplSizeUserDict);
/* _wcesdk_SplSuggest SplSuggest: print `int SplSuggest( HSPL hspl , SPLBUFFER * psb );`  [twin page(s): ms907061] */
AKARI_CE_IMPORT int SplSuggest(HSPL hspl, SPLBUFFER* psb)
    AKARI_CE_NAME(SplSuggest);

/* Setting Up the SPLBUFFER Structure (_wcesdk_Setting_Up_the_SPLBUFFER_Structure):
 * concept page of the same book; no declaration. */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SPLAPI_H */
