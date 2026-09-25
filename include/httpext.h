/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_HTTPEXT_H
#define WCE_HTTPEXT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagHSE_SEND_HEADER_EX_INFO { LPCSTR pszStatus; LPCSTR pszHeader; DWORD cchStatus; DWORD cchHeader; BOOL fKeepConn; } HSE_SEND_HEADER_EX_INFO, *PHSE_SEND_HEADER_EX_INFO, *LPHSE_SEND_HEADER_EX_INFO;

WCE_IMPORT BOOL WINAPI TerminateExtension(DWORD dwFlags) WCE_LINK(TerminateExtension);

#ifdef __cplusplus
}
#endif
#endif

