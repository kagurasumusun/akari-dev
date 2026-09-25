/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WININET_H
#define WCE_WININET_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagINTERNET_ASYNC_RESULT { DWORD_PTR dwResult; DWORD dwError; } INTERNET_ASYNC_RESULT, *PINTERNET_ASYNC_RESULT, *LPINTERNET_ASYNC_RESULT;
typedef struct tagINTERNET_PROXY_INFO { DWORD dwAccessType; LPCTSTR lpszProxy; LPCTSTR lpszProxyBypass; } INTERNET_PROXY_INFO, *PINTERNET_PROXY_INFO, *LPINTERNET_PROXY_INFO;
typedef struct tagINTERNET_VERSION_INFO { DWORD dwMajorVersion; DWORD dwMinorVersion; } INTERNET_VERSION_INFO, *PINTERNET_VERSION_INFO, *LPINTERNET_VERSION_INFO;
typedef struct tagHTTP_VERSION_INFO { DWORD dwMajorVersion; DWORD dwMinorVersion; } HTTP_VERSION_INFO, *PHTTP_VERSION_INFO, *LPHTTP_VERSION_INFO;
typedef struct tagINTERNET_CONNECTED_INFO { DWORD dwConnectedState; DWORD dwFlags; } INTERNET_CONNECTED_INFO, *PINTERNET_CONNECTED_INFO, *LPINTERNET_CONNECTED_INFO;
typedef struct tagINTERNET_CERTIFICATE_INFO { FILETIME ftExpiry; FILETIME ftStart; LPTSTR lpszSubjectInfo; LPTSTR lpszIssuerInfo; LPTSTR lpszProtocolName; LPTSTR lpszSignatureAlgName; LPTSTR lpszEncryptionAlgName; DWORD dwKeySize; } INTERNET_CERTIFICATE_INFO, *PINTERNET_CERTIFICATE_INFO, *LPINTERNET_CERTIFICATE_INFO;
typedef struct tagIncomingCookieState { int cSession; int cPersistent; int cAccepted; int cLeashed; int cDowngraded; int cBlocked; const char *pszLocation; } IncomingCookieState, *PIncomingCookieState, *LPIncomingCookieState;
typedef struct tagOutgoingCookieState { int cSent; int cSuppressed; const char *pszLocation; } OutgoingCookieState, *POutgoingCookieState, *LPOutgoingCookieState;
typedef struct tagInternetCookieHistory { BOOL fAccepted; BOOL fLeashed; BOOL fDowngraded; BOOL fRejected; } InternetCookieHistory, *PInternetCookieHistory, *LPInternetCookieHistory;
typedef struct tagCookieDecision { DWORD dwCookieState; BOOL fAllowSession; } CookieDecision, *PCookieDecision, *LPCookieDecision;
typedef struct tagGOPHER_ADMIN_ATTRIBUTE_TYPE { LPCTSTR Comment; LPCTSTR EmailAddress; } GOPHER_ADMIN_ATTRIBUTE_TYPE, *PGOPHER_ADMIN_ATTRIBUTE_TYPE, *LPGOPHER_ADMIN_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_MOD_DATE_ATTRIBUTE_TYPE { FILETIME DateAndTime; } GOPHER_MOD_DATE_ATTRIBUTE_TYPE, *PGOPHER_MOD_DATE_ATTRIBUTE_TYPE, *LPGOPHER_MOD_DATE_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_TTL_ATTRIBUTE_TYPE { DWORD Ttl; } GOPHER_TTL_ATTRIBUTE_TYPE, *PGOPHER_TTL_ATTRIBUTE_TYPE, *LPGOPHER_TTL_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_SCORE_ATTRIBUTE_TYPE { INT Score; } GOPHER_SCORE_ATTRIBUTE_TYPE, *PGOPHER_SCORE_ATTRIBUTE_TYPE, *LPGOPHER_SCORE_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_SCORE_RANGE_ATTRIBUTE_TYPE { INT LowerBound; INT UpperBound; } GOPHER_SCORE_RANGE_ATTRIBUTE_TYPE, *PGOPHER_SCORE_RANGE_ATTRIBUTE_TYPE, *LPGOPHER_SCORE_RANGE_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_SITE_ATTRIBUTE_TYPE { LPCTSTR Site; } GOPHER_SITE_ATTRIBUTE_TYPE, *PGOPHER_SITE_ATTRIBUTE_TYPE, *LPGOPHER_SITE_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_ORGANIZATION_ATTRIBUTE_TYPE { LPCTSTR Organization; } GOPHER_ORGANIZATION_ATTRIBUTE_TYPE, *PGOPHER_ORGANIZATION_ATTRIBUTE_TYPE, *LPGOPHER_ORGANIZATION_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_LOCATION_ATTRIBUTE_TYPE { LPCTSTR Location; } GOPHER_LOCATION_ATTRIBUTE_TYPE, *PGOPHER_LOCATION_ATTRIBUTE_TYPE, *LPGOPHER_LOCATION_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE { INT DegreesNorth; INT MinutesNorth; INT SecondsNorth; INT DegreesEast; INT MinutesEast; INT SecondsEast; } GOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE, *PGOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE, *LPGOPHER_GEOGRAPHICAL_LOCATION_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_TIMEZONE_ATTRIBUTE_TYPE { INT Zone; } GOPHER_TIMEZONE_ATTRIBUTE_TYPE, *PGOPHER_TIMEZONE_ATTRIBUTE_TYPE, *LPGOPHER_TIMEZONE_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_PROVIDER_ATTRIBUTE_TYPE { LPCTSTR Provider; } GOPHER_PROVIDER_ATTRIBUTE_TYPE, *PGOPHER_PROVIDER_ATTRIBUTE_TYPE, *LPGOPHER_PROVIDER_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_VERSION_ATTRIBUTE_TYPE { LPCTSTR Version; } GOPHER_VERSION_ATTRIBUTE_TYPE, *PGOPHER_VERSION_ATTRIBUTE_TYPE, *LPGOPHER_VERSION_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_ABSTRACT_ATTRIBUTE_TYPE { LPCTSTR ShortAbstract; LPCTSTR AbstractFile; } GOPHER_ABSTRACT_ATTRIBUTE_TYPE, *PGOPHER_ABSTRACT_ATTRIBUTE_TYPE, *LPGOPHER_ABSTRACT_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_VIEW_ATTRIBUTE_TYPE { LPCTSTR ContentType; LPCTSTR Language; DWORD Size; } GOPHER_VIEW_ATTRIBUTE_TYPE, *PGOPHER_VIEW_ATTRIBUTE_TYPE, *LPGOPHER_VIEW_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_VERONICA_ATTRIBUTE_TYPE { BOOL TreeWalk; } GOPHER_VERONICA_ATTRIBUTE_TYPE, *PGOPHER_VERONICA_ATTRIBUTE_TYPE, *LPGOPHER_VERONICA_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_ASK_ATTRIBUTE_TYPE { LPCTSTR QuestionType; LPCTSTR QuestionText; } GOPHER_ASK_ATTRIBUTE_TYPE, *PGOPHER_ASK_ATTRIBUTE_TYPE, *LPGOPHER_ASK_ATTRIBUTE_TYPE;
typedef struct tagGOPHER_UNKNOWN_ATTRIBUTE_TYPE { LPCTSTR Text; } GOPHER_UNKNOWN_ATTRIBUTE_TYPE, *PGOPHER_UNKNOWN_ATTRIBUTE_TYPE, *LPGOPHER_UNKNOWN_ATTRIBUTE_TYPE;

WCE_IMPORT BOOL WINAPI InternetTimeFromSystemTimeA(IN CONST SYSTEMTIME *pst, IN DWORD dwRFC, OUT LPSTR lpszTime, IN DWORD cbTime) WCE_LINK(InternetTimeFromSystemTimeA);
WCE_IMPORT BOOL WINAPI InternetTimeFromSystemTimeW(IN CONST SYSTEMTIME *pst, IN DWORD dwRFC, OUT LPWSTR lpszTime, IN DWORD cbTime) WCE_LINK(InternetTimeFromSystemTimeW);
WCE_IMPORT BOOL WINAPI InternetTimeFromSystemTime(IN CONST SYSTEMTIME *pst, IN DWORD dwRFC, OUT LPSTR lpszTime, IN DWORD cbTime) WCE_LINK(InternetTimeFromSystemTime);
WCE_IMPORT BOOL WINAPI InternetTimeToSystemTimeA(IN LPCSTR lpszTime, OUT SYSTEMTIME *pst, IN DWORD dwReserved) WCE_LINK(InternetTimeToSystemTimeA);
WCE_IMPORT BOOL WINAPI InternetTimeToSystemTimeW(IN LPCWSTR lpszTime, OUT SYSTEMTIME *pst, IN DWORD dwReserved) WCE_LINK(InternetTimeToSystemTimeW);
WCE_IMPORT BOOL WINAPI InternetTimeToSystemTime(IN LPCSTR lpszTime, OUT SYSTEMTIME *pst, IN DWORD dwReserved) WCE_LINK(InternetTimeToSystemTime);
WCE_IMPORT BOOL WINAPI InternetCrackUrlA(IN LPCSTR lpszUrl, IN DWORD dwUrlLength, IN DWORD dwFlags, IN OUT LPURL_COMPONENTSA lpUrlComponents) WCE_LINK(InternetCrackUrlA);
WCE_IMPORT BOOL WINAPI InternetCrackUrlW(IN LPCWSTR lpszUrl, IN DWORD dwUrlLength, IN DWORD dwFlags, IN OUT LPURL_COMPONENTSW lpUrlComponents) WCE_LINK(InternetCrackUrlW);
WCE_IMPORT BOOL WINAPI InternetCreateUrlA(IN LPURL_COMPONENTSA lpUrlComponents, IN DWORD dwFlags, OUT LPSTR lpszUrl, IN OUT LPDWORD lpdwUrlLength) WCE_LINK(InternetCreateUrlA);
WCE_IMPORT BOOL WINAPI InternetCreateUrlW(IN LPURL_COMPONENTSW lpUrlComponents, IN DWORD dwFlags, OUT LPWSTR lpszUrl, IN OUT LPDWORD lpdwUrlLength) WCE_LINK(InternetCreateUrlW);
WCE_IMPORT BOOL WINAPI InternetCanonicalizeUrlA(IN LPCSTR lpszUrl, OUT LPSTR lpszBuffer, IN OUT LPDWORD lpdwBufferLength, IN DWORD dwFlags) WCE_LINK(InternetCanonicalizeUrlA);
WCE_IMPORT BOOL WINAPI InternetCanonicalizeUrlW(IN LPCWSTR lpszUrl, OUT LPWSTR lpszBuffer, IN OUT LPDWORD lpdwBufferLength, IN DWORD dwFlags) WCE_LINK(InternetCanonicalizeUrlW);
WCE_IMPORT BOOL WINAPI InternetCombineUrlA(IN LPCSTR lpszBaseUrl, IN LPCSTR lpszRelativeUrl, OUT LPSTR lpszBuffer, IN OUT LPDWORD lpdwBufferLength, IN DWORD dwFlags) WCE_LINK(InternetCombineUrlA);
WCE_IMPORT BOOL WINAPI InternetCombineUrlW(IN LPCWSTR lpszBaseUrl, IN LPCWSTR lpszRelativeUrl, OUT LPWSTR lpszBuffer, IN OUT LPDWORD lpdwBufferLength, IN DWORD dwFlags) WCE_LINK(InternetCombineUrlW);
WCE_IMPORT BOOL WINAPI InternetUnlockRequestFile(IN HANDLE hLockRequestInfo) WCE_LINK(InternetUnlockRequestFile);
WCE_IMPORT BOOL WINAPI InternetGetLastResponseInfoA(OUT LPDWORD lpdwError, OUT LPSTR lpszBuffer OPTIONAL, IN OUT LPDWORD lpdwBufferLength) WCE_LINK(InternetGetLastResponseInfoA);
WCE_IMPORT BOOL WINAPI InternetGetLastResponseInfoW(OUT LPDWORD lpdwError, OUT LPWSTR lpszBuffer OPTIONAL, IN OUT LPDWORD lpdwBufferLength) WCE_LINK(InternetGetLastResponseInfoW);
WCE_IMPORT BOOL WINAPI GopherGetLocatorTypeA(IN LPCSTR lpszLocator, OUT LPDWORD lpdwGopherType) WCE_LINK(GopherGetLocatorTypeA);
WCE_IMPORT BOOL WINAPI GopherGetLocatorTypeW(IN LPCWSTR lpszLocator, OUT LPDWORD lpdwGopherType) WCE_LINK(GopherGetLocatorTypeW);

#define InternetCrackUrl InternetCrackUrlW
#define InternetCreateUrl InternetCreateUrlW
#define InternetCanonicalizeUrl InternetCanonicalizeUrlW
#define InternetCombineUrl InternetCombineUrlW
#define InternetGetLastResponseInfo InternetGetLastResponseInfoW
#define GopherGetLocatorType GopherGetLocatorTypeW
#ifdef __cplusplus
}
#endif
#endif

