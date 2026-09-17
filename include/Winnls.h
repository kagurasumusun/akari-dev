/*
 * Winnls.h -- National Language Support API for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs); per-page Requirements rows (OS Versions / Header /
 * Link Library) are transcribed in docs/inventory.md.  Header Winnls.h
 * is the Header row the CE pages themselves name for these functions.
 */

#ifndef AKARI_WINNLS_H
#define AKARI_WINNLS_H

#include "Windef.h"
#include "Winbase.h"   /* SYSTEMTIME for the date/time formatters */

#ifdef __cplusplus
extern "C" {
#endif

/* Code pages accepted by the conversion functions.  Names per the CE
 * MultiByteToWideChar / WideCharToMultiByte pages (ms886760,
 * aa450989), which mark CP_MACCP, CP_SYMBOL and CP_THREAD_ACP as "Not
 * supported" on Windows CE; values are the fixed Win32 ABI values. */
#define CP_ACP        0     /* ANSI code page */
#define CP_OEMCP      1     /* OEM code page */
#define CP_MACCP      2     /* not supported on Windows CE */
#define CP_THREAD_ACP 3     /* not supported on Windows CE */
#define CP_SYMBOL     42    /* not supported on Windows CE */
#define CP_UTF7       65000 /* UTF-7 code page */
#define CP_UTF8       65001 /* UTF-8 code page */

/* MultiByteToWideChar dwFlags (names per ms886760; values are the
 * fixed Win32 ABI values). */
#define MB_PRECOMPOSED        0x0001u
#define MB_COMPOSITE          0x0002u
#define MB_USEGLYPHCHARS      0x0004u
#define MB_ERR_INVALID_CHARS  0x0008u

/* WideCharToMultiByte dwFlags (names per aa450989; values are the
 * fixed Win32 ABI values; WC_NO_BEST_FIT_CHARS is not published by
 * the CE page so it is not defined here). */
#define WC_COMPOSITECHECK  0x0200u
#define WC_DISCARDNS       0x0010u
#define WC_SEPCHARS        0x0020u
#define WC_DEFAULTCHAR     0x0040u

/* ms886760 "MultiByteToWideChar (Windows CE 5.0)":
 * int MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int).
 * CE 1.01+; Winnls.h; Coredll.lib.  Maps a (not necessarily
 * multibyte) character string to a wide-character string. */
AKARI_CE_IMPORT int MultiByteToWideChar(UINT CodePage, DWORD dwFlags,
                        LPCSTR lpMultiByteStr, int cbMultiByte,
                        LPWSTR lpWideCharStr, int cchWideChar) AKARI_CE_NAME(MultiByteToWideChar);

/* aa450989 "WideCharToMultiByte (Windows CE 5.0)":
 * int WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR, int,
 * LPCSTR, LPBOOL).  CE 1.01+; Winnls.h; Coredll.lib.  Maps a wide
 * string to the given code page. */
AKARI_CE_IMPORT int WideCharToMultiByte(UINT CodePage, DWORD dwFlags,
                        LPCWSTR lpWideCharStr, int cchWideChar,
                        LPSTR lpMultiByteStr, int cbMultiByte,
                        LPCSTR lpDefaultChar,
                        LPBOOL lpUsedDefaultChar) AKARI_CE_NAME(WideCharToMultiByte);

/* ms886515 "IsDBCSLeadByte (Windows CE 5.0)":
 * BOOL IsDBCSLeadByte(BYTE).  CE 1.01+; Winnls.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL IsDBCSLeadByte(BYTE TestChar) AKARI_CE_NAME(IsDBCSLeadByte);

/* ms886608 "IsDBCSLeadByteEx (Windows CE 5.0)":
 * BOOL IsDBCSLeadByteEx(UINT, BYTE).  CE 1.01+; Winnls.h;
 * Coredll.lib. */
AKARI_CE_IMPORT BOOL IsDBCSLeadByteEx(UINT CodePage, BYTE TestChar) AKARI_CE_NAME(IsDBCSLeadByteEx);

/* ------------------------------------------------------------------ */
/* M16: locale/code-page functions (official NLS Reference pages).    */
/* The NLS pages list Link Library Coreloc.lib except where noted.    */
/* ------------------------------------------------------------------ */

/* Character-type flag groups for GetStringTypeW/GetStringTypeEx
 * (ms905272/ms905283 name CT_CTYPE1/2/3; the values 1/2/4 are the
 * fixed Win32 ABI values). */
#define CT_CTYPE1 0x00000001u
#define CT_CTYPE2 0x00000002u
#define CT_CTYPE3 0x00000004u

/* Validity-test flags for IsValidLocale (ms906219). */
#define LCID_INSTALLED   0x00000001u
#define LCID_SUPPORTED   0x00000002u

/* String comparison results of CompareString (ms904713). */
#define CSTR_LESS_THAN    1
#define CSTR_EQUAL        2
#define CSTR_GREATER_THAN 3

/* CPINFO array sizes (names from the CPINFO page ms904717; values are
 * the fixed Win32 NLS-ABI sizes MAX_DEFAULTCHAR/MAX_LEADBYTES). */
#define MAX_DEFAULTCHAR 2
#define MAX_LEADBYTES   12

/* ms904717 "CPINFO (Windows CE 5.0)": code-page information filled by
 * GetCPInfo.  CE .NET 4.0+; Winnls.h. */
typedef struct _cpinfo {
    UINT MaxCharSize;              /* max length, in bytes, of a char */
    BYTE DefaultChar[MAX_DEFAULTCHAR]; /* default character */
    BYTE LeadByte[MAX_LEADBYTES];  /* lead-byte ranges, zero-terminated */
} CPINFO, *LPCPINFO;

/* ms905215 "GetACP (Windows CE 5.0)": UINT GetACP(VOID).  Returns the
 * current ANSI code-page identifier for the system.  CE .NET 4.0+;
 * Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT UINT GetACP(void) AKARI_CE_NAME(GetACP);

/* ms905256 "GetOEMCP (Windows CE 5.0)": UINT GetOEMCP(void).  Returns
 * the current OEM code-page identifier.  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT UINT GetOEMCP(void) AKARI_CE_NAME(GetOEMCP);

/* ms905298 "GetSystemDefaultLCID (Windows CE 5.0)":
 * LCID GetSystemDefaultLCID(void).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LCID GetSystemDefaultLCID(void) AKARI_CE_NAME(GetSystemDefaultLCID);

/* ms905323 "GetUserDefaultLCID (Windows CE 5.0)":
 * LCID GetUserDefaultLCID(void).  CE .NET 4.0+; Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT LCID GetUserDefaultLCID(void) AKARI_CE_NAME(GetUserDefaultLCID);

/* ms905289 "GetSystemDefaultLangID (Windows CE 5.0)":
 * LANGID GetSystemDefaultLangID(void).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LANGID GetSystemDefaultLangID(void) AKARI_CE_NAME(GetSystemDefaultLangID);

/* ms905315 "GetUserDefaultLangID (Windows CE 5.0)":
 * LANGID GetUserDefaultLangID(void).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LANGID GetUserDefaultLangID(void) AKARI_CE_NAME(GetUserDefaultLangID);

/* ms906218 "IsValidCodePage (Windows CE 5.0)":
 * BOOL IsValidCodePage(UINT).  CE .NET 4.0+; Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT BOOL IsValidCodePage(UINT CodePage) AKARI_CE_NAME(IsValidCodePage);

/* ms906219 "IsValidLocale (Windows CE 5.0)":
 * BOOL IsValidLocale(LCID, DWORD).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib.  dwFlags = LCID_INSTALLED and/or LCID_SUPPORTED; CE
 * cannot download code pages to a device (page note). */
AKARI_CE_IMPORT BOOL IsValidLocale(LCID Locale, DWORD dwFlags) AKARI_CE_NAME(IsValidLocale);

/* ms904713 "CompareString (Windows CE 5.0)":
 * int CompareString(LCID, DWORD, LPCTSTR, int, LPCTSTR, int).
 * CE 1.0+; Winnls.h; Coreloc.lib.  Compares two strings under the
 * locale; returns CSTR_LESS_THAN/EQUAL/GREATER_THAN (0 on failure).
 * cchCount -1 means null-terminated.  Fastest at dwCmpFlags 0 or
 * NORM_IGNORECASE with -1 counts (page note). */
AKARI_CE_IMPORT int CompareStringW(LCID Locale, DWORD dwCmpFlags,
                   LPCWSTR lpString1, int cchCount1,
                   LPCWSTR lpString2, int cchCount2) AKARI_CE_NAME(CompareStringW);
#define CompareString CompareStringW

/* ms904716 "ConvertDefaultLocale (Windows CE 5.0)":
 * LCID ConvertDefaultLocale(LCID).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LCID ConvertDefaultLocale(LCID Locale) AKARI_CE_NAME(ConvertDefaultLocale);

/* ms905221 "GetCPInfo (Windows CE 5.0)":
 * BOOL GetCPInfo(UINT, LPCPINFO).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib.  Fills the code-page info structure. */
AKARI_CE_IMPORT BOOL GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo) AKARI_CE_NAME(GetCPInfo);

/* ms905272 "GetStringTypeW (Windows CE 5.0)":
 * BOOL GetStringTypeW(DWORD, LPCWSTR, int, LPWORD).  CE 1.0+;
 * Winnls.h; **Coredll.lib** (page row).  Sets one or more CT_* bits
 * per source character in the output WORD array. */
AKARI_CE_IMPORT BOOL GetStringTypeW(DWORD dwInfoType, LPCWSTR lpSrcStr, int cchSrc,
                    LPWORD lpCharType) AKARI_CE_NAME(GetStringTypeW);

/* ms905283 "GetStringTypeEx (Windows CE 5.0)":
 * BOOL GetStringTypeEx(LCID, DWORD, LPCTSTR, int, LPWORD).  CE 1.0+;
 * Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT BOOL GetStringTypeExW(LCID Locale, DWORD dwInfoType,
                      LPCWSTR lpSrcStr, int cchSrc,
                      LPWORD lpCharType) AKARI_CE_NAME(GetStringTypeExW);
#define GetStringTypeEx GetStringTypeExW

/* ------------------------------------------------------------------ */
/* M32: NLS formatting / locale-info functions (Coreloc.lib; Winnls.h).*/
/*                                                                     */
/* All pages below print Header Winnls.h and Link Library Coreloc.lib, */
/* OS Versions Windows CE .NET 4.0 and later, except where noted.      */
/* The CURRENCYFMT / NUMBERFMT member lists are transcribed verbatim   */
/* from their structure pages (ms904720 / ms906228); the LPTSTR format */
/* fields are per the pages.  LCType takes the LCTYPE constants (the   */
/* ms906223 table); their values are not yet transcribed (recorded),   */
/* so GetLocaleInfoW/SetLocaleInfoW are declared and the LCTYPE table  */
/* is a recorded follow-on.  The DATE_ and TIME_ flag names are        */
/* documented by the GetDateFormat/GetTimeFormat pages; numeric values */
/* are not republished there (fixed-ABI follow-on, recorded).          */
/* republished there (fixed-ABI follow-on, recorded).  dwFlags=0 gives */
/* the default locale format for every function here.  CE is           */
/* Unicode-only: exports are the W spellings.                          */
/* ------------------------------------------------------------------ */

typedef DWORD LCTYPE;   /* LCTYPE constant space (UINT-sized) */

/* Audit 2026-09-17 (evidence retraction; supersedes the 2026-09-16
 * audit addition of commit 051ee54): the 20 numeric LOCALE_* values
 * that commit added here -- the 18 LCTYPE constants LOCALE_SDECIMAL
 * 0x000E .. LOCALE_INEGSEPBYSPACE 0x0057 plus the LCIDs
 * LOCALE_USER_DEFAULT 0x0400 and LOCALE_SYSTEM_DEFAULT 0x0800 -- are
 * WITHDRAWN.  The constants return to the held state recorded since
 * M32: names documented, values not confirmable from official CE
 * material ("公式資料で確認できない").
 *
 * Corpus-verified evidence status, all four documented generations:
 *  - the LCTYPE Constants pages print the constant NAMES and their
 *    per-item descriptions, never numeric values: CE 3.0
 *    _wcesdk_LCTYPE_Constants, CE .NET 4.2 ms921463, CE 5.0 ms906223,
 *    CE 6.0 ee491958;
 *  - GetLocaleInfo / SetLocaleInfo name LOCALE_SYSTEM_DEFAULT,
 *    LOCALE_USER_DEFAULT and LOCALE_NEUTRAL as predefined Locale
 *    values without printing numbers (ms905243 / ms906277 and their
 *    CE 4.2 / CE 6.0 twins, CE 3.0 _wcesdk_Win32_GetLocaleInfo);
 *  - the only numeric anchors printed anywhere on this surface are
 *    the "Language Identifiers and Locales" LCID tables (ms903928 /
 *    ms921461 / ee491651 / _wcesdk_Language_Identifiers_and_Locales),
 *    whose special-identifier rows read 0x0000 "Language-Neutral" and
 *    0x0400 "Process Default Language"; no CE page ties 0x0400 to the
 *    NAME LOCALE_USER_DEFAULT, and no CE page prints 0x0800 in an
 *    LCID context at all;
 *  - "Specifying Locales with NLS" (_wcesdk_Specifying_Locales_with_NLS
 *    / ms904358) prints the LCID and LANGID bit layouts and states
 *    LOCALE_NEUTRAL is the same identifier as LOCALE_USER_DEFAULT --
 *    still without values.
 *
 * The withdrawn definitions were grounded in a Wine / ReactOS
 * cross-check and a Win32-ABI-stability argument.  Wine and ReactOS
 * are absolutely excluded sources under the evidence policy v2
 * (docs/clean-room.md, 2026-09-17: no reference, no investigation),
 * and desktop-Win32 analogy is no CE evidence (v2 1.3), so that
 * grounding does not hold and the values are removed rather than kept
 * on the assumption that they are correct.  Record:
 * docs/CHANGELOG-audit-2026-09-17.md; register:
 * docs/unpublished-constants.tsv.  Under v2 these constants are
 * re-verification candidates: the official pages print their names
 * only (corpus-verified above), so a CeGCC-lineage value confirmation
 * (v2 1.2 -- reference/comparison/value-check only, never copying)
 * can ground them.  Until that confirmation is run and recorded here,
 * the values stay withdrawn; nothing is restored speculatively, and
 * the withdrawn numbers are not a starting point.
 *
 * Downstream note: llvm-project libcxx/src/support/wince/
 * locale_wince.cpp consumes 19 of the withdrawn values (the 18
 * LCTYPE constants + LOCALE_USER_DEFAULT) and no longer compiles
 * against this header until that consumer is reworked (task D). */

typedef struct _currencyfmt {
    UINT   NumDigits;
    UINT   LeadingZero;
    UINT   Grouping;
    LPTSTR lpDecimalSep;
    LPTSTR lpThousandSep;
    UINT   NegativeOrder;
    UINT   PositiveOrder;
    LPTSTR lpCurrencySymbol;
} CURRENCYFMT;

typedef struct _numberfmt {
    UINT   NumDigits;
    UINT   LeadingZero;
    UINT   Grouping;
    LPTSTR lpDecimalSep;
    LPTSTR lpThousandSep;
    UINT   NegativeOrder;
} NUMBERFMT;

AKARI_CE_IMPORT int GetCurrencyFormatW(LCID Locale, DWORD dwFlags, LPCWSTR lpValue,
                       const CURRENCYFMT *lpFormat,
                       LPWSTR lpCurrencyStr, int cchCurrency) AKARI_CE_NAME(GetCurrencyFormatW);
#define GetCurrencyFormat GetCurrencyFormatW
AKARI_CE_IMPORT int GetNumberFormatW(LCID Locale, DWORD dwFlags, LPCWSTR lpValue,
                     const NUMBERFMT *lpFormat,
                     LPWSTR lpNumberStr, int cchNumber) AKARI_CE_NAME(GetNumberFormatW);
#define GetNumberFormat GetNumberFormatW
AKARI_CE_IMPORT int GetDateFormatW(LCID Locale, DWORD dwFlags,
                   const SYSTEMTIME *lpDate, LPCWSTR lpFormat,
                   LPWSTR lpDateStr, int cchDate) AKARI_CE_NAME(GetDateFormatW);
#define GetDateFormat GetDateFormatW
AKARI_CE_IMPORT int GetTimeFormatW(LCID Locale, DWORD dwFlags,
                   const SYSTEMTIME *lpTime, LPCWSTR lpFormat,
                   LPWSTR lpTimeStr, int cchTime) AKARI_CE_NAME(GetTimeFormatW);
#define GetTimeFormat GetTimeFormatW
AKARI_CE_IMPORT int GetLocaleInfoW(LCID Locale, LCTYPE LCType,
                   LPWSTR lpLCData, int cchData) AKARI_CE_NAME(GetLocaleInfoW);
#define GetLocaleInfo GetLocaleInfoW
AKARI_CE_IMPORT BOOL SetLocaleInfoW(LCID Locale, LCTYPE LCType, LPCWSTR lpLCData) AKARI_CE_NAME(SetLocaleInfoW);
#define SetLocaleInfo SetLocaleInfoW

/* ------------------------------------------------------------------ */
/* String mapping (FoldString / LCMapString) and code-page enumeration */
/* (EnumSystemCodePages).  Page family: FoldString ms905209 (CE 1.0+), */
/* LCMapString ms906221 (CE .NET 4.0+), EnumSystemCodePages ms905062   */
/* (CE .NET 4.0+); Header rows all Winnls.h; Link Library rows all     */
/* Coreloc.lib.  CE 6.0 twins ee491930 / ee491201 / ee491962 confirm   */
/* the prototypes and the (v=winembedded.60) requirement rows.         */
/*                                                                     */
/* Windows CE is Unicode-only: the CE .NET/CE 5.0 LCMapString page     */
/* states "Even though Windows CE supports only the Unicode version    */
/* of this function...", so the exports are the wide spellings         */
/* (gen-doc-def.py UNICODE_ONLY).                                     */

/* CODEPAGE_ENUMPROC -- pointer to the application-defined callback
 * that EnumSystemCodePages calls for each code page.  The official
 * EnumCodePagesProc page (ms904723, CE .NET 4.0+; Winnls.h;
 * Coreloc.lib) documents "BOOL CALLBACK EnumCodePagesProc(LPTSTR
 * lpCodePageString)" and states "The CODEPAGE_ENUMPROC type defines a
 * pointer to this callback function."; the EnumSystemCodePages
 * parameter is typed CODEPAGE_ENUMPROC.  CE 6.0 twins ee491122 /
 * ee491962 restate both. */
typedef BOOL (CALLBACK *CODEPAGE_ENUMPROC)(LPWSTR lpCodePageString);

/* ms905209 "FoldString (Windows CE 5.0)": int FoldString(DWORD, LPCTSTR,
 * int, LPTSTR, int).  OS CE 1.0+; Winnls.h; Coreloc.lib.  dwMapFlags
 * combines the MAP_* mapping flags (names and CE support notes are on
 * the page; the CE page does not publish the flag values, so no
 * MAP_* constants are shipped -- recorded). */
AKARI_CE_IMPORT int FoldStringW(DWORD dwMapFlags, LPCWSTR lpSrcStr, int cchSrc,
                LPWSTR lpDestStr, int cchDest) AKARI_CE_NAME(FoldStringW);
#define FoldString FoldStringW

/* ms906221 "LCMapString (Windows CE 5.0)": int LCMapString(LCID, DWORD,
 * LPCTSTR, int, LPTSTR, int).  OS CE .NET 4.0+; Winnls.h; Coreloc.lib.
 * dwMapFlags combines the LCMAP_* and NORM_* flags (the page names
 * them per supported-flag groups; numeric values are not published by
 * the CE page -> no LCMAP_* or NORM_* constants shipped -- recorded). */
AKARI_CE_IMPORT int LCMapStringW(LCID Locale, DWORD dwMapFlags, LPCWSTR lpSrcStr,
                 int cchSrc, LPWSTR lpDestStr, int cchDest) AKARI_CE_NAME(LCMapStringW);
#define LCMapString LCMapStringW

/* ms905062 "EnumSystemCodePages (Windows CE 5.0)":
 * BOOL EnumSystemCodePages(CODEPAGE_ENUMPROC, DWORD).  OS CE .NET 4.0+;
 * Winnls.h; Coreloc.lib.  Enumerates the code pages installed on (or,
 * with CP_INSTALLED unset, supported by) the system; enumeration stops
 * when the callback returns FALSE. */
AKARI_CE_IMPORT BOOL EnumSystemCodePagesW(CODEPAGE_ENUMPROC lpCodePageEnumProc,
                          DWORD dwFlags) AKARI_CE_NAME(EnumSystemCodePagesW);
#define EnumSystemCodePages EnumSystemCodePagesW

/* ------------------------------------------------------------------ */
/* Locale / date / time enumeration (M139, 2026-09-17).  The four     */
/* Enum* function pages print full prototypes -- the "print `` (no    */
/* compiled prototype)" record the intl-book harvest left on them     */
/* was a ce-fetch.py extraction failure, not a property of the pages  */
/* (see the corrected Book surface records below).                    */
/* Page family (CE 5.0): EnumSystemLocales ms905070, EnumDateFormats  */
/* ms904724, EnumTimeFormats ms905077, EnumCalendarInfo ms904721;     */
/* CE .NET 4.2 twins ms919238 / ms919196 / ms919245 / ms919176 and    */
/* CE 6.0 twins ee491192 / ee491363 / ee491332 / ee491359 print the   */
/* same prototypes; every one of these pages carries the requirement  */
/* rows Header Winnls.h, Link Library Coreloc.lib, CE .NET 4.0+.      */
/*                                                                    */
/* Callback pointer typedefs: each function page prints its           */
/* *_ENUMPROC parameter type name and describes that parameter as a   */
/* pointer to the application-defined callback of the sibling         */
/* Enum*Proc page; the callback pages (EnumLocalesProc ms904848,      */
/* EnumDateFormatsProc ms904740, EnumTimeFormatsProc ms905083,        */
/* EnumCalendarInfoProc ms904722) print                               */
/* "BOOL CALLBACK Enum*Proc(LPWSTR lp*String);" and state "Windows    */
/* CE supports only the Unicode version of this function."  The       */
/* typedefs compose exactly those two prints -- the same derivation   */
/* the CODEPAGE_ENUMPROC typedef above (ms904723 + ms905062) uses.    */
/* The exports are the W spellings per that Unicode-only statement,   */
/* matching the sibling NLS exports (GetLocaleInfoW, LCMapStringW,    */
/* EnumSystemCodePagesW).                                             */

typedef BOOL (CALLBACK *LOCALE_ENUMPROC)(LPWSTR lpLocaleString);
typedef BOOL (CALLBACK *DATEFMT_ENUMPROC)(LPWSTR lpDateFormatString);
typedef BOOL (CALLBACK *TIMEFMT_ENUMPROC)(LPWSTR lpTimeFormatString);
typedef BOOL (CALLBACK *CALINFO_ENUMPROC)(LPWSTR lpCalendarInfoString);

/* ms905070 "EnumSystemLocales (Windows CE 5.0)":
 * BOOL EnumSystemLocales(LOCALE_ENUMPROC, DWORD).  CE .NET 4.0+;
 * Winnls.h; Coreloc.lib.  Enumerates the locales installed on (or,
 * with LCID_SUPPORTED, supported by) the system; dwFlags takes
 * LCID_INSTALLED or LCID_SUPPORTED (mutually exclusive, page
 * Remarks). */
AKARI_CE_IMPORT BOOL EnumSystemLocalesW(LOCALE_ENUMPROC lpLocaleEnumProc,
                        DWORD dwFlags) AKARI_CE_NAME(EnumSystemLocalesW);
#define EnumSystemLocales EnumSystemLocalesW

/* ms904724 "EnumDateFormats (Windows CE 5.0)":
 * BOOL EnumDateFormats(DATEFMT_ENUMPROC, LCID, DWORD).  CE .NET 4.0+;
 * Winnls.h; Coreloc.lib.  Enumerates the long or short date formats
 * available for a locale; dwFlags takes DATE_SHORTDATE /
 * DATE_LONGDATE (names printed by the page; their numeric values are
 * not published by any CE page -> the two constants stay held). */
AKARI_CE_IMPORT BOOL EnumDateFormatsW(DATEFMT_ENUMPROC lpDateFmtEnumProc,
                      LCID Locale, DWORD dwFlags) AKARI_CE_NAME(EnumDateFormatsW);
#define EnumDateFormats EnumDateFormatsW

/* ms905077 "EnumTimeFormats (Windows CE 5.0)":
 * BOOL EnumTimeFormats(TIMEFMT_ENUMPROC, LCID, DWORD).  CE .NET 4.0+;
 * Winnls.h; Coreloc.lib.  Enumerates the time formats available for
 * a locale; dwFlags is currently unused, set to zero (page). */
AKARI_CE_IMPORT BOOL EnumTimeFormatsW(TIMEFMT_ENUMPROC lpTimeFmtEnumProc,
                      LCID Locale, DWORD dwFlags) AKARI_CE_NAME(EnumTimeFormatsW);
#define EnumTimeFormats EnumTimeFormatsW

/* ms904721 "EnumCalendarInfo (Windows CE 5.0)":
 * BOOL EnumCalendarInfo(CALINFO_ENUMPROC, LCID, CALID, CALTYPE).
 * CE .NET 4.0+; Winnls.h; Coreloc.lib.  HELD, not declared: the page
 * prints the parameter type names CALID and CALTYPE, but no CE page
 * of any documented generation defines either type (catalog-verified
 * across CE 3.0/4.x/5.0/6.0; the CAL_* calendar identifiers of the
 * Calendar table and the CALTYPE constants of the Remarks are also
 * printed name-only, with no values).  Declaring the function would
 * require inventing the CALID/CALTYPE definitions from the desktop
 * Win32 analogy, which the evidence policy forbids.  Recorded in
 * docs/undeclared-blocked.tsv.  CALINFO_ENUMPROC above IS declared:
 * both prints it composes exist (ms904721 parameter row + ms904722
 * prototype); only the CALID/CALTYPE parameters block the function. */

/* ------------------------------------------------------------------
 * Book surface: intl-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* 2026-09-17 correction (M139): the four records below formerly read
 * "print `` -- recorded verbatim (no compiled prototype)".  That was
 * WRONG -- a ce-fetch.py extraction failure, not a page property: all
 * four pages print full prototypes (verified against the preserved
 * corpus pages).  EnumSystemLocales / EnumDateFormats / EnumTimeFormats
 * are declared in the M139 block above; EnumCalendarInfo stays held
 * on its undocumented CALID / CALTYPE parameter types. */
/* ms904721 EnumCalendarInfo: prototype printed -- HELD (CALID/CALTYPE undefined; see above) */
/* ms904724 EnumDateFormats: prototype printed -- declared (M139) */
/* ms905070 EnumSystemLocales: prototype printed -- declared (M139) */
/* ms905077 EnumTimeFormats: prototype printed -- declared (M139) */

/* ------------------------------------------------------------------
 * Book surface: core-nls-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms904722 EnumCalendarInfoProc: documented name-only (no value published; held) */
/* ms904740 EnumDateFormatsProc: documented name-only (no value published; held) */
/* ms904848 EnumLocalesProc: documented name-only (no value published; held) */
/* ms905083 EnumTimeFormatsProc: documented name-only (no value published; held) */

/* ------------------------------------------------------------------
 * Book surface: core-nls-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms903783 Code Pages */
/* ms903928 Language Identifiers and Locales */
/* ms906223 LCTYPE Constants */
/* ms904415 National Language Support (NLS) Functions */
/* ms906224 National Language support (NLS) Locale Identifiers */
/* ms904406 National Language Support (NLS) Macros */
/* ms904614 National Language Support (NLS) Structures */

/* ------------------------------------------------------------------
 * Book surface: core-unicode-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450778 Unicode Functions */
/* aa450779 Unicode Macros */
/* aa450781 Unicode Structures */

#ifdef __cplusplus
}
#endif


/* ms919323 "GetStringType": same export as ms905272 (GetStringTypeW,
 * declared above); the generic-name page is aliased exactly like the
 * GetStringTypeEx precedent. */
#define GetStringType GetStringTypeW


/* M121: the five winnls.h application-defined callbacks, declared with
 *  tools/decl-from-pages.py from their own pages.  They were not declared
 *  before -- the tree only mentioned them in comments (the CODEPAGE_ENUMPROC
 *  note at ms904723 and the core-nls-reference value records, which hold
 *  those names for want of a published *value*, a different axis from a
 *  prototype).  Being application-implemented, they carry no
 *  AKARI_CE_IMPORT.  Status update (M139, 2026-09-17): this block
 *  formerly recorded the five Enum* functions as undeclared because
 *  none of the five *_ENUMPROC pointer typedefs existed.  All five
 *  typedefs are now declared (CODEPAGE_ENUMPROC since the
 *  EnumSystemCodePages block above; CALINFO_/DATEFMT_/LOCALE_/
 *  TIMEFMT_ENUMPROC in the M139 block), and four of the five Enum*
 *  functions are declared (EnumSystemCodePagesW earlier;
 *  EnumSystemLocalesW, EnumDateFormatsW, EnumTimeFormatsW in M139).
 *  Only EnumCalendarInfo stays held, on its undocumented CALID /
 *  CALTYPE parameter types (see the M139 block). */

/* ms904722 EnumCalendarInfoProc: print `BOOLCALLBACKEnumCalendarInfoProc(LPWSTRlpCalendarInfoString);`
 * (Windows CE .NET 4.0 and later.; Link Library: Coreloc.lib.) */
BOOL CALLBACK EnumCalendarInfoProc(LPWSTR lpCalendarInfoString);

/* ms904723 EnumCodePagesProc: print `BOOLCALLBACKEnumCodePagesProc(LPTSTRlpCodePageString);`
 * (Windows CE .NET 4.0 and later.; Link Library: Coreloc.lib.) */
BOOL CALLBACK EnumCodePagesProc(LPTSTR lpCodePageString);

/* ms904740 EnumDateFormatsProc: print `BOOLCALLBACKEnumDateFormatsProc(LPWSTRlpDateFormatString);`
 * (Windows CE .NET 4.0 and later.; Link Library: Coreloc.lib.) */
BOOL CALLBACK EnumDateFormatsProc(LPWSTR lpDateFormatString);

/* ms904848 EnumLocalesProc: print `BOOLCALLBACKEnumLocalesProc(LPWSTRlpLocaleString);`
 * (Windows CE .NET 4.0 and later.; Link Library: Coreloc.lib.) */
BOOL CALLBACK EnumLocalesProc(LPWSTR lpLocaleString);

/* ms905083 EnumTimeFormatsProc: print `BOOLCALLBACKEnumTimeFormatsProc(LPWSTRlpTimeFormatString );`
 * (Windows CE .NET 4.0 and later.; Link Library: Coreloc.lib.) */
BOOL CALLBACK EnumTimeFormatsProc(LPWSTR lpTimeFormatString);

#endif /* AKARI_WINNLS_H */
