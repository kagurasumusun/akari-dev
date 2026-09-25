/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_HTTPFILT_H
#define WCE_HTTPFILT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagHTTP_FILTER_RAW_DATA { PVOID pvInData; DWORD cbInData; DWORD cbInBuffer; DWORD dwReserved; } HTTP_FILTER_RAW_DATA, *PHTTP_FILTER_RAW_DATA, *LPHTTP_FILTER_RAW_DATA;
typedef struct tagHTTP_FILTER_AUTHENT { CHAR * pszUser; DWORD cbUserBuff; CHAR * pszPassword; DWORD cbPasswordBuff; } HTTP_FILTER_AUTHENT, *PHTTP_FILTER_AUTHENT, *LPHTTP_FILTER_AUTHENT;
typedef struct tagHTTP_FILTER_URL_MAP { const CHAR * pszURL; CHAR * pszPhysicalPath; DWORD cbPathBuff; } HTTP_FILTER_URL_MAP, *PHTTP_FILTER_URL_MAP, *LPHTTP_FILTER_URL_MAP;
typedef struct tagHTTP_FILTER_ACCESS_DENIED { const CHAR * pszURL; const CHAR * pszPhysicalPath; DWORD dwReason; } HTTP_FILTER_ACCESS_DENIED, *PHTTP_FILTER_ACCESS_DENIED, *LPHTTP_FILTER_ACCESS_DENIED;
typedef struct tagHTTP_FILTER_LOG { const CHAR * pszClientHostName; const CHAR * pszClientUserName; const CHAR * pszServerName; const CHAR * pszOperation; const CHAR * pszTarget; const CHAR * pszParameters; DWORD dwHttpStatus; DWORD dwWin32Status; DWORD dwBytesSent; DWORD dwBytesRecvd; DWORD msTimeForProcessing; } HTTP_FILTER_LOG, *PHTTP_FILTER_LOG, *LPHTTP_FILTER_LOG;

WCE_IMPORT BOOL WINAPI TerminateFilter(DWORD dwFlags) WCE_LINK(TerminateFilter);

#ifdef __cplusplus
}
#endif
#endif

