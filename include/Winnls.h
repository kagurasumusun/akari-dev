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
#define CP_ACP        0     /* ms906416 ANSI code page */
#define CP_OEMCP      1     /* ms906416 OEM code page */
#define CP_MACCP      2     /* ms906416 not supported on Windows CE */
#define CP_THREAD_ACP 3     /* ms906416 not supported on Windows CE */
#define CP_SYMBOL     42    /* ms906416 not supported on Windows CE */
#define CP_UTF7       65000 /* ms906416 UTF-7 code page */
#define CP_UTF8       65001 /* ms906416 UTF-8 code page */

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
/* ms906223 table); the full 102-constant table with confirmed values  */
/* is transcribed below (re-verification record of 2026-09-18).  The   */
/* DATE_ and TIME_ flag names are                                  */
/* documented by the GetDateFormat/GetTimeFormat pages; numeric values */
/* are not republished there (fixed-ABI follow-on, recorded).          */
/* dwFlags=0 gives                                                 */
/* the default locale format for every function here.  CE is           */
/* Unicode-only: exports are the W spellings.                          */
/* ------------------------------------------------------------------ */

typedef DWORD LCTYPE;   /* LCTYPE constant space (UINT-sized) */

/* ------------------------------------------------------------------ */
/* LCTYPE constants (GetLocaleInfo/SetLocaleInfo LCType values).      */
/*                                                                     */
/* NAME SET: exactly the 102 constants printed by the official LCTYPE */
/* Constants pages -- CE .NET 4.2 ms921463, CE 5.0 ms906223, CE 6.0   */
/* ee491958 (identical sets across the three generations; order below */
/* follows the CE 5.0 table).  VALUES: each confirmed against the     */
/* CeGCC-lineage w32api reference R1 (value confirmation only -- the  */
/* policy exception; the pages print names+descriptions, no numbers). */
/* See the re-verification record above.                              */
/* ------------------------------------------------------------------ */
#define LOCALE_ILANGUAGE             0x0001
#define LOCALE_SLANGUAGE             0x0002
#define LOCALE_SENGLANGUAGE          0x1001
#define LOCALE_SABBREVLANGNAME       0x0003
#define LOCALE_SNATIVELANGNAME       0x0004
#define LOCALE_ICOUNTRY              0x0005
#define LOCALE_SCOUNTRY              0x0006
#define LOCALE_SNATIVECTRYNAME       0x0008
#define LOCALE_SENGCOUNTRY           0x1002
#define LOCALE_SABBREVCTRYNAME       0x0007
#define LOCALE_IDEFAULTLANGUAGE      0x0009
#define LOCALE_IDEFAULTCOUNTRY       0x000A
#define LOCALE_IDEFAULTANSICODEPAGE  0x1004
#define LOCALE_IDEFAULTCODEPAGE      0x000B
#define LOCALE_SLIST                 0x000C
#define LOCALE_IMEASURE              0x000D
#define LOCALE_SDECIMAL              0x000E
#define LOCALE_STHOUSAND             0x000F
#define LOCALE_SGROUPING             0x0010
#define LOCALE_IDIGITS               0x0011
#define LOCALE_IDIGITSUBSTITUTION    0x1014
#define LOCALE_SNATIVEDIGITS         0x0013
#define LOCALE_ILZERO                0x0012
#define LOCALE_INEGNUMBER            0x1010
#define LOCALE_SCURRENCY             0x0014
#define LOCALE_SINTLSYMBOL           0x0015
#define LOCALE_SMONDECIMALSEP        0x0016
#define LOCALE_SMONTHOUSANDSEP       0x0017
#define LOCALE_SMONGROUPING          0x0018
#define LOCALE_ICURRDIGITS           0x0019
#define LOCALE_IINTLCURRDIGITS       0x001A
#define LOCALE_ICURRENCY             0x001B
#define LOCALE_INEGCURR              0x001C
#define LOCALE_SDATE                 0x001D
#define LOCALE_STIME                 0x001E
#define LOCALE_STIMEFORMAT           0x1003
#define LOCALE_SYEARMONTH            0x1006
#define LOCALE_SSHORTDATE            0x001F
#define LOCALE_SLONGDATE             0x0020
#define LOCALE_IDATE                 0x0021
#define LOCALE_ILDATE                0x0022
#define LOCALE_ITIME                 0x0023
#define LOCALE_ICENTURY              0x0024
#define LOCALE_ITLZERO               0x0025
#define LOCALE_IDAYLZERO             0x0026
#define LOCALE_IMONLZERO             0x0027
#define LOCALE_S1159                 0x0028
#define LOCALE_S2359                 0x0029
#define LOCALE_ICALENDARTYPE         0x1009
#define LOCALE_IOPTIONALCALENDAR     0x100B
#define LOCALE_IFIRSTDAYOFWEEK       0x100C
#define LOCALE_SDAYNAME1             0x002A
#define LOCALE_SDAYNAME2             0x002B
#define LOCALE_SDAYNAME3             0x002C
#define LOCALE_SDAYNAME4             0x002D
#define LOCALE_SDAYNAME5             0x002E
#define LOCALE_SDAYNAME6             0x002F
#define LOCALE_SDAYNAME7             0x0030
#define LOCALE_IFIRSTWEEKOFYEAR      0x100D
#define LOCALE_SABBREVDAYNAME1       0x0031
#define LOCALE_SABBREVDAYNAME2       0x0032
#define LOCALE_SABBREVDAYNAME3       0x0033
#define LOCALE_SABBREVDAYNAME4       0x0034
#define LOCALE_SABBREVDAYNAME5       0x0035
#define LOCALE_SABBREVDAYNAME6       0x0036
#define LOCALE_SABBREVDAYNAME7       0x0037
#define LOCALE_SMONTHNAME1           0x0038
#define LOCALE_SMONTHNAME2           0x0039
#define LOCALE_SMONTHNAME3           0x003A
#define LOCALE_SMONTHNAME4           0x003B
#define LOCALE_SMONTHNAME5           0x003C
#define LOCALE_SMONTHNAME6           0x003D
#define LOCALE_SMONTHNAME7           0x003E
#define LOCALE_SMONTHNAME8           0x003F
#define LOCALE_SMONTHNAME9           0x0040
#define LOCALE_SMONTHNAME10          0x0041
#define LOCALE_SMONTHNAME11          0x0042
#define LOCALE_SMONTHNAME12          0x0043
#define LOCALE_SMONTHNAME13          0x100E
#define LOCALE_SABBREVMONTHNAME1     0x0044
#define LOCALE_SABBREVMONTHNAME2     0x0045
#define LOCALE_SABBREVMONTHNAME3     0x0046
#define LOCALE_SABBREVMONTHNAME4     0x0047
#define LOCALE_SABBREVMONTHNAME5     0x0048
#define LOCALE_SABBREVMONTHNAME6     0x0049
#define LOCALE_SABBREVMONTHNAME7     0x004A
#define LOCALE_SABBREVMONTHNAME8     0x004B
#define LOCALE_SABBREVMONTHNAME9     0x004C
#define LOCALE_SABBREVMONTHNAME10    0x004D
#define LOCALE_SABBREVMONTHNAME11    0x004E
#define LOCALE_SABBREVMONTHNAME12    0x004F
#define LOCALE_SABBREVMONTHNAME13    0x100F
#define LOCALE_SPOSITIVESIGN         0x0050
#define LOCALE_SNEGATIVESIGN         0x0051
#define LOCALE_IPOSSIGNPOSN          0x0052
#define LOCALE_INEGSIGNPOSN          0x0053
#define LOCALE_IPOSSYMPRECEDES       0x0054
#define LOCALE_IPOSSEPBYSPACE        0x0055
#define LOCALE_INEGSYMPRECEDES       0x0056
#define LOCALE_INEGSEPBYSPACE        0x0057
#define LOCALE_IPAPERSIZE            0x100A
#define LOCALE_NOUSEROVERRIDE        0x80000000

/* Predefined LCID values (named on the GetLocaleInfo/SetLocaleInfo
 * pages ms905243/ms906277 without numbers; values R1-confirmed --
 * see the record above).  LOCALE_NEUTRAL is an alias of
 * LOCALE_USER_DEFAULT per the official NLS statement. */
#define LOCALE_USER_DEFAULT          0x0400
#define LOCALE_SYSTEM_DEFAULT        0x0800
#define LOCALE_NEUTRAL               LOCALE_USER_DEFAULT

/* Audit 2026-09-17 (evidence retraction): the 20 numeric LOCALE_*
 * values added on 2026-09-16 (the 18 LCTYPE constants LOCALE_SDECIMAL
 * 0x000E .. LOCALE_INEGSEPBYSPACE 0x0057 plus the LCIDs
 * LOCALE_USER_DEFAULT 0x0400 and LOCALE_SYSTEM_DEFAULT 0x0800) were
 * WITHDRAWN because their grounding cited excluded sources
 * (desktop-Win32 analogy and cross-checks against trees the evidence
 * policy absolutely excludes).  Nothing was restored speculatively.
 *
 * RESOLUTION (re-verification record, 2026-09-18, policy v3 =
 * wince-docs-corpus AGENTS.md): official pages searched first, per
 * the policy order; the whole LCTYPE surface is now GROUNDED:
 *  - NAMES: the LCTYPE Constants pages print every constant name
 *    with its description -- CE .NET 4.2 ms921463, CE 5.0 ms906223,
 *    CE 6.0 ee491958 (all three stored in wince-docs-corpus; the
 *    three generations print the same 102-name set; corpus-verified
 *    2026-09-18, zero numeric values printed on any of them; same
 *    for the CE 3.0 _wcesdk_LCTYPE_Constants page);
 *  - VALUES: every one of the 102 values below was confirmed
 *    value-for-value against the CeGCC-lineage w32api reference
 *    (R1 -- the single exception the policy permits, for value
 *    confirmation only; R1 is never a source of declarations, text
 *    or name sets);
 *  - LCIDs: LOCALE_USER_DEFAULT / LOCALE_SYSTEM_DEFAULT are named on
 *    the GetLocaleInfo / SetLocaleInfo pages (ms905243 / ms906277
 *    and twins) without numbers; the values 0x0400 / 0x0800 are
 *    R1-confirmed.  LOCALE_NEUTRAL is declared as an alias of
 *    LOCALE_USER_DEFAULT per the official statement in "Specifying
 *    Locales with NLS" (_wcesdk_Specifying_Locales_with_NLS /
 *    ms904358: "LOCALE_NEUTRAL is the same identifier as
 *    LOCALE_USER_DEFAULT"); R1 does not carry a LOCALE_NEUTRAL
 *    define, so the alias form -- not a second literal -- is used.
 *  - The LCID special-identifier rows printed by the official
 *    "Language Identifiers and Locales" tables (ms903928 / ms921461
 *    / ee491651: 0x0000 "Language-Neutral", 0x0400 "Process Default
 *    Language") remain the only officially printed numbers on this
 *    surface and are consistent with the R1-confirmed 0x0400.
 * Register: docs/unpublished-constants.tsv (recreated).
 *
 * Downstream note (verified 2026-09-18 against
 * kagurasumusun/llvm-project@LLVM-WinCE,
 * libcxx/src/support/wince/locale_wince.cpp): the former consumer of
 * 19 withdrawn values has since been reworked and no longer
 * references these constants directly -- the blocker recorded on
 * 2026-09-17 (task D) is closed. */

/* ms904720: members/signature verified against this page (type-cite) */
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

/* ms906228: members/signature verified against this page (type-cite) */
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
