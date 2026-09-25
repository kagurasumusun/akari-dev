/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINNLS_H
#define WCE_WINNLS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagNUMBERFMTA { UINT NumDigits; UINT LeadingZero; UINT Grouping; LPSTR lpDecimalSep; LPSTR lpThousandSep; UINT NegativeOrder; } NUMBERFMTA, *PNUMBERFMTA, *LPNUMBERFMTA;
typedef struct tagNUMBERFMTW { UINT NumDigits; UINT LeadingZero; UINT Grouping; LPWSTR lpDecimalSep; LPWSTR lpThousandSep; UINT NegativeOrder; } NUMBERFMTW, *PNUMBERFMTW, *LPNUMBERFMTW;
typedef struct tagCURRENCYFMTA { UINT NumDigits; UINT LeadingZero; UINT Grouping; LPSTR lpDecimalSep; LPSTR lpThousandSep; UINT NegativeOrder; UINT PositiveOrder; LPSTR lpCurrencySymbol; } CURRENCYFMTA, *PCURRENCYFMTA, *LPCURRENCYFMTA;
typedef struct tagCURRENCYFMTW { UINT NumDigits; UINT LeadingZero; UINT Grouping; LPWSTR lpDecimalSep; LPWSTR lpThousandSep; UINT NegativeOrder; UINT PositiveOrder; LPWSTR lpCurrencySymbol; } CURRENCYFMTW, *PCURRENCYFMTW, *LPCURRENCYFMTW;

WCE_IMPORT BOOL WINAPI IsValidCodePage(IN UINT CodePage) WCE_LINK(IsValidCodePage);
WCE_IMPORT UINT WINAPI GetACP(void) WCE_LINK(GetACP);
WCE_IMPORT UINT WINAPI GetOEMCP(void) WCE_LINK(GetOEMCP);
WCE_IMPORT BOOL WINAPI GetCPInfo(IN UINT CodePage, OUT LPCPINFO lpCPInfo) WCE_LINK(GetCPInfo);
WCE_IMPORT BOOL WINAPI IsDBCSLeadByte(IN BYTE TestChar) WCE_LINK(IsDBCSLeadByte);
WCE_IMPORT BOOL WINAPI IsDBCSLeadByteEx(IN UINT CodePage, IN BYTE TestChar) WCE_LINK(IsDBCSLeadByteEx);
WCE_IMPORT int WINAPI MultiByteToWideChar(IN UINT CodePage, IN DWORD dwFlags, IN LPCSTR lpMultiByteStr, IN int cbMultiByte, OUT LPWSTR lpWideCharStr, IN int cchWideChar) WCE_LINK(MultiByteToWideChar);
WCE_IMPORT int WINAPI WideCharToMultiByte(IN UINT CodePage, IN DWORD dwFlags, IN LPCWSTR lpWideCharStr, IN int cchWideChar, OUT LPSTR lpMultiByteStr, IN int cbMultiByte, IN LPCSTR lpDefaultChar, OUT LPBOOL lpUsedDefaultChar) WCE_LINK(WideCharToMultiByte);
WCE_IMPORT int WINAPI CompareStringA(IN LCID Locale, IN DWORD dwCmpFlags, IN LPCSTR lpString1, IN int cchCount1, IN LPCSTR lpString2, IN int cchCount2) WCE_LINK(CompareStringA);
WCE_IMPORT int WINAPI CompareStringW(IN LCID Locale, IN DWORD dwCmpFlags, IN LPCWSTR lpString1, IN int cchCount1, IN LPCWSTR lpString2, IN int cchCount2) WCE_LINK(CompareStringW);
WCE_IMPORT int WINAPI LCMapStringA(IN LCID Locale, IN DWORD dwMapFlags, IN LPCSTR lpSrcStr, IN int cchSrc, OUT LPSTR lpDestStr, IN int cchDest) WCE_LINK(LCMapStringA);
WCE_IMPORT int WINAPI LCMapStringW(IN LCID Locale, IN DWORD dwMapFlags, IN LPCWSTR lpSrcStr, IN int cchSrc, OUT LPWSTR lpDestStr, IN int cchDest) WCE_LINK(LCMapStringW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT int WINAPI GetTimeFormatA(IN LCID Locale, IN DWORD dwFlags, IN CONST SYSTEMTIME *lpTime, IN LPCSTR lpFormat, OUT LPSTR lpTimeStr, IN int cchTime) WCE_LINK(GetTimeFormatA);
#endif
WCE_IMPORT int WINAPI GetTimeFormatW(IN LCID Locale, IN DWORD dwFlags, IN CONST SYSTEMTIME *lpTime, IN LPCWSTR lpFormat, OUT LPWSTR lpTimeStr, IN int cchTime) WCE_LINK(GetTimeFormatW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT int WINAPI GetDateFormatA(IN LCID Locale, IN DWORD dwFlags, IN CONST SYSTEMTIME *lpDate, IN LPCSTR lpFormat, OUT LPSTR lpDateStr, IN int cchDate) WCE_LINK(GetDateFormatA);
#endif
WCE_IMPORT int WINAPI GetDateFormatW(IN LCID Locale, IN DWORD dwFlags, IN CONST SYSTEMTIME *lpDate, IN LPCWSTR lpFormat, OUT LPWSTR lpDateStr, IN int cchDate) WCE_LINK(GetDateFormatW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT int WINAPI GetNumberFormatA(IN LCID Locale, IN DWORD dwFlags, IN LPCSTR lpValue, IN CONST NUMBERFMTA *lpFormat, OUT LPSTR lpNumberStr, IN int cchNumber) WCE_LINK(GetNumberFormatA);
#endif
WCE_IMPORT int WINAPI GetNumberFormatW(IN LCID Locale, IN DWORD dwFlags, IN LPCWSTR lpValue, IN CONST NUMBERFMTW *lpFormat, OUT LPWSTR lpNumberStr, IN int cchNumber) WCE_LINK(GetNumberFormatW);
WCE_IMPORT int WINAPI GetCurrencyFormatA(IN LCID Locale, IN DWORD dwFlags, IN LPCSTR lpValue, IN CONST CURRENCYFMTA *lpFormat, OUT LPSTR lpCurrencyStr, IN int cchCurrency) WCE_LINK(GetCurrencyFormatA);
WCE_IMPORT int WINAPI GetCurrencyFormatW(IN LCID Locale, IN DWORD dwFlags, IN LPCWSTR lpValue, IN CONST CURRENCYFMTW *lpFormat, OUT LPWSTR lpCurrencyStr, IN int cchCurrency) WCE_LINK(GetCurrencyFormatW);
WCE_IMPORT BOOL WINAPI IsValidLocale(IN LCID Locale, IN DWORD dwFlags) WCE_LINK(IsValidLocale);
WCE_IMPORT LCID WINAPI ConvertDefaultLocale(IN OUT LCID Locale) WCE_LINK(ConvertDefaultLocale);
WCE_IMPORT LANGID WINAPI GetSystemDefaultLangID(void) WCE_LINK(GetSystemDefaultLangID);
WCE_IMPORT LANGID WINAPI GetUserDefaultLangID(void) WCE_LINK(GetUserDefaultLangID);
WCE_IMPORT BOOL WINAPI SetUserDefaultUILanguage(LANGID langid) WCE_LINK(SetUserDefaultUILanguage);
WCE_IMPORT LCID WINAPI GetSystemDefaultLCID(void) WCE_LINK(GetSystemDefaultLCID);
WCE_IMPORT LCID WINAPI GetUserDefaultLCID(void) WCE_LINK(GetUserDefaultLCID);
WCE_IMPORT BOOL WINAPI GetStringTypeExA(IN LCID Locale, IN DWORD dwInfoType, IN LPCSTR lpSrcStr, IN int cchSrc, OUT LPWORD lpCharType) WCE_LINK(GetStringTypeExA);
WCE_IMPORT BOOL WINAPI GetStringTypeExW(IN LCID Locale, IN DWORD dwInfoType, IN LPCWSTR lpSrcStr, IN int cchSrc, OUT LPWORD lpCharType) WCE_LINK(GetStringTypeExW);
WCE_IMPORT BOOL WINAPI GetStringTypeA(IN LCID Locale, IN DWORD dwInfoType, IN LPCSTR lpSrcStr, IN int cchSrc, OUT LPWORD lpCharType) WCE_LINK(GetStringTypeA);
WCE_IMPORT BOOL WINAPI GetStringTypeW(IN DWORD dwInfoType, IN LPCWSTR lpSrcStr, IN int cchSrc, OUT LPWORD lpCharType) WCE_LINK(GetStringTypeW);
WCE_IMPORT int WINAPI FoldStringA(IN DWORD dwMapFlags, IN LPCSTR lpSrcStr, IN int cchSrc, OUT LPSTR lpDestStr, IN int cchDest) WCE_LINK(FoldStringA);
WCE_IMPORT int WINAPI FoldStringW(IN DWORD dwMapFlags, IN LPCWSTR lpSrcStr, IN int cchSrc, OUT LPWSTR lpDestStr, IN int cchDest) WCE_LINK(FoldStringW);
WCE_IMPORT LANGID WINAPI GetSystemDefaultUILanguage(VOID) WCE_LINK(GetSystemDefaultUILanguage);
WCE_IMPORT LANGID WINAPI GetUserDefaultUILanguage(VOID) WCE_LINK(GetUserDefaultUILanguage);
WCE_IMPORT BOOL WINAPI SetSystemDefaultLCID(LCID Locale) WCE_LINK(SetSystemDefaultLCID);
WCE_IMPORT BOOL WINAPI SetOEMCP(UINT oemcp) WCE_LINK(SetOEMCP);
WCE_IMPORT BOOL WINAPI SetACP(UINT acp) WCE_LINK(SetACP);
WCE_IMPORT BOOL WINAPI SetUserDefaultLCID(LCID Locale) WCE_LINK(SetUserDefaultLCID);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI GetNlsTables(LPVOID *lplpTable, DWORD dwFlags, LPDWORD lpOffset, LPDWORD lpSize) WCE_LINK(GetNlsTables);
#endif

#define CompareString CompareStringW
#define LCMapString LCMapStringW
#define GetTimeFormat GetTimeFormatW
#define GetDateFormat GetDateFormatW
#define GetNumberFormat GetNumberFormatW
#define GetCurrencyFormat GetCurrencyFormatW
#define GetStringTypeEx GetStringTypeExW
#define GetStringType GetStringTypeW
#define FoldString FoldStringW
#ifdef __cplusplus
}
#endif
#endif

