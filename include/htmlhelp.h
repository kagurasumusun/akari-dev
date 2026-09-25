/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_HTMLHELP_H
#define WCE_HTMLHELP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagHHN_NOTIFY { NMHDR hdr; PCSTR pszUrl; } HHN_NOTIFY, *PHHN_NOTIFY, *LPHHN_NOTIFY;
typedef struct tagHH_POPUP { int cbStruct; HINSTANCE hinst; UINT idString; LPCTSTR pszText; POINT pt; COLORREF clrForeground; COLORREF clrBackground; RECT rcMargins; LPCTSTR pszFont; } HH_POPUP, *PHH_POPUP, *LPHH_POPUP;
typedef struct tagHH_AKLINK { int cbStruct; BOOL fReserved; LPCTSTR pszKeywords; LPCTSTR pszUrl; LPCTSTR pszMsgText; LPCTSTR pszMsgTitle; LPCTSTR pszWindow; BOOL fIndexOnFail; } HH_AKLINK, *PHH_AKLINK, *LPHH_AKLINK;
typedef struct tagHH_ENUM_IT { int cbStruct; int iType; LPCSTR pszCatName; LPCSTR pszITName; LPCSTR pszITDescription; } HH_ENUM_IT, *PHH_ENUM_IT, *LPHH_ENUM_IT;
typedef struct tagHH_ENUM_CAT { int cbStruct; LPCSTR pszCatName; LPCSTR pszCatDescription; } HH_ENUM_CAT, *PHH_ENUM_CAT, *LPHH_ENUM_CAT;
typedef struct tagHH_SET_INFOTYPE { int cbStruct; LPCSTR pszCatName; LPCSTR pszInfoTypeName; } HH_SET_INFOTYPE, *PHH_SET_INFOTYPE, *LPHH_SET_INFOTYPE;
typedef struct tagHH_FTS_QUERY { int cbStruct; BOOL fUniCodeStrings; LPCTSTR pszSearchQuery; LONG iProximity; BOOL fStemmedSearch; BOOL fTitleOnly; BOOL fExecute; LPCTSTR pszWindow; } HH_FTS_QUERY, *PHH_FTS_QUERY, *LPHH_FTS_QUERY;

WCE_IMPORT HWND WINAPI HtmlHelpA(HWND hwndCaller, LPCSTR pszFile, UINT uCommand, ULONG_PTR dwData) WCE_LINK(HtmlHelpA);
WCE_IMPORT HWND WINAPI HtmlHelpW(HWND hwndCaller, LPCWSTR pszFile, UINT uCommand, ULONG_PTR dwData) WCE_LINK(HtmlHelpW);

#define HtmlHelp HtmlHelpW
#ifdef __cplusplus
}
#endif
#endif

