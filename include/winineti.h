/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WININETI_H
#define WCE_WININETI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagINTERNET_PREFETCH_STATUS { DWORD dwStatus; DWORD dwSize; } INTERNET_PREFETCH_STATUS, *PINTERNET_PREFETCH_STATUS, *LPINTERNET_PREFETCH_STATUS;
typedef struct tagINTERNET_DIAGNOSTIC_SOCKET_INFO { DWORD_PTR Socket; DWORD SourcePort; DWORD DestPort; DWORD Flags; } INTERNET_DIAGNOSTIC_SOCKET_INFO, *PINTERNET_DIAGNOSTIC_SOCKET_INFO, *LPINTERNET_DIAGNOSTIC_SOCKET_INFO;
typedef struct tagINTERNET_COOKIE { DWORD cbSize; LPSTR pszName; LPSTR pszData; LPSTR pszDomain; LPSTR pszPath; FILETIME *pftExpires; DWORD dwFlags; LPSTR pszUrl; LPSTR pszP3PPolicy; } INTERNET_COOKIE, *PINTERNET_COOKIE, *LPINTERNET_COOKIE;
typedef struct tagINTERNET_CACHE_CONTAINER_INFOA { DWORD dwCacheVersion; LPSTR lpszName; LPSTR lpszCachePrefix; LPSTR lpszVolumeLabel; LPSTR lpszVolumeTitle; } INTERNET_CACHE_CONTAINER_INFOA, *PINTERNET_CACHE_CONTAINER_INFOA, *LPINTERNET_CACHE_CONTAINER_INFOA;
typedef struct tagINTERNET_CACHE_CONTAINER_INFOW { DWORD dwCacheVersion; LPWSTR lpszName; LPWSTR lpszCachePrefix; LPWSTR lpszVolumeLabel; LPWSTR lpszVolumeTitle; } INTERNET_CACHE_CONTAINER_INFOW, *PINTERNET_CACHE_CONTAINER_INFOW, *LPINTERNET_CACHE_CONTAINER_INFOW;

WCE_IMPORT BOOL WINAPI InternetDebugGetLocalTime(OUT SYSTEMTIME * pstLocalTime, OUT DWORD * pdwReserved) WCE_LINK(InternetDebugGetLocalTime);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI HttpCheckDavComplianceA(IN LPCSTR lpszUrl, IN LPCSTR lpszComplianceToken, IN OUT LPBOOL lpfFound, IN HWND hWnd, IN LPVOID lpvReserved) WCE_LINK(HttpCheckDavComplianceA);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI HttpCheckDavComplianceW(IN LPCWSTR lpszUrl, IN LPCWSTR lpszComplianceToken, IN OUT LPBOOL lpfFound, IN HWND hWnd, IN LPVOID lpvReserved) WCE_LINK(HttpCheckDavComplianceW);
#endif
WCE_IMPORT BOOL WINAPI HttpCheckCachedDavStatusA(IN LPCSTR lpszUrl, IN OUT LPDWORD lpdwStatus) WCE_LINK(HttpCheckCachedDavStatusA);
WCE_IMPORT BOOL WINAPI HttpCheckCachedDavStatusW(IN LPCWSTR lpszUrl, IN OUT LPDWORD lpdwStatus) WCE_LINK(HttpCheckCachedDavStatusW);
WCE_IMPORT BOOL WINAPI HttpCheckDavCollectionA(IN LPCSTR lpszUrl, IN OUT LPBOOL lpfFound, IN HWND hWnd, IN LPVOID lpvReserved) WCE_LINK(HttpCheckDavCollectionA);
WCE_IMPORT BOOL WINAPI HttpCheckDavCollectionW(IN LPCWSTR lpszUrl, IN OUT LPBOOL lpfFound, IN HWND hWnd, IN LPVOID lpvReserved) WCE_LINK(HttpCheckDavCollectionW);
WCE_IMPORT BOOL WINAPI IsUrlCacheEntryExpiredA(IN LPCSTR lpszUrlName, IN DWORD dwFlags, IN OUT FILETIME* pftLastModified) WCE_LINK(IsUrlCacheEntryExpiredA);
WCE_IMPORT BOOL WINAPI IsUrlCacheEntryExpiredW(IN LPCWSTR lpszUrlName, IN DWORD dwFlags, IN OUT FILETIME* pftLastModified) WCE_LINK(IsUrlCacheEntryExpiredW);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI CreateUrlCacheContainerA(IN LPCSTR Name, IN LPCSTR lpCachePrefix, LPCSTR lpszCachePath, IN DWORD KBCacheLimit, IN DWORD dwContainerType, IN DWORD dwOptions, IN OUT LPVOID pvBuffer, IN OUT LPDWORD cbBuffer) WCE_LINK(CreateUrlCacheContainerA);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI CreateUrlCacheContainerW(IN LPCWSTR Name, IN LPCWSTR lpCachePrefix, LPCWSTR lpszCachePath, IN DWORD KBCacheLimit, IN DWORD dwContainerType, IN DWORD dwOptions, IN OUT LPVOID pvBuffer, IN OUT LPDWORD cbBuffer) WCE_LINK(CreateUrlCacheContainerW);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI DeleteUrlCacheContainerA(IN LPCSTR Name, IN DWORD dwOptions) WCE_LINK(DeleteUrlCacheContainerA);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI DeleteUrlCacheContainerW(IN LPCWSTR Name, IN DWORD dwOptions) WCE_LINK(DeleteUrlCacheContainerW);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI FindNextUrlCacheContainerA(IN HANDLE hEnumHandle, OUT LPINTERNET_CACHE_CONTAINER_INFOA lpContainerInfo, IN OUT LPDWORD lpdwContainerInfoBufferSize) WCE_LINK(FindNextUrlCacheContainerA);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI FindNextUrlCacheContainerW(IN HANDLE hEnumHandle, OUT LPINTERNET_CACHE_CONTAINER_INFOW lpContainerInfo, IN OUT LPDWORD lpdwContainerInfoBufferSize) WCE_LINK(FindNextUrlCacheContainerW);
#endif
WCE_IMPORT BOOL WINAPI FreeUrlCacheSpaceA(IN LPCSTR lpszCachePath, IN DWORD dwSize, IN DWORD dwFilter) WCE_LINK(FreeUrlCacheSpaceA);
WCE_IMPORT BOOL WINAPI FreeUrlCacheSpaceW(IN LPCWSTR lpszCachePath, IN DWORD dwSize, IN DWORD dwFilter) WCE_LINK(FreeUrlCacheSpaceW);
WCE_IMPORT BOOL WINAPI GetUrlCacheConfigInfoA(OUT LPINTERNET_CACHE_CONFIG_INFOA lpCacheConfigInfo, IN OUT LPDWORD lpdwCacheConfigInfoBufferSize, IN DWORD dwFieldControl) WCE_LINK(GetUrlCacheConfigInfoA);
WCE_IMPORT BOOL WINAPI GetUrlCacheConfigInfoW(OUT LPINTERNET_CACHE_CONFIG_INFOW lpCacheConfigInfo, IN OUT LPDWORD lpdwCacheConfigInfoBufferSize, IN DWORD dwFieldControl) WCE_LINK(GetUrlCacheConfigInfoW);
WCE_IMPORT BOOL WINAPI SetUrlCacheConfigInfoA(IN LPINTERNET_CACHE_CONFIG_INFOA lpCacheConfigInfo, IN DWORD dwFieldControl) WCE_LINK(SetUrlCacheConfigInfoA);
WCE_IMPORT BOOL WINAPI SetUrlCacheConfigInfoW(IN LPINTERNET_CACHE_CONFIG_INFOW lpCacheConfigInfo, IN DWORD dwFieldControl) WCE_LINK(SetUrlCacheConfigInfoW);
WCE_IMPORT BOOL WINAPI UpdateUrlCacheContentPath(LPSTR szNewPath) WCE_LINK(UpdateUrlCacheContentPath);
WCE_IMPORT BOOL WINAPI ImportCookieFileA(IN LPCSTR szFilename) WCE_LINK(ImportCookieFileA);
WCE_IMPORT BOOL WINAPI ImportCookieFileW(IN LPCWSTR szFilename) WCE_LINK(ImportCookieFileW);
WCE_IMPORT BOOL WINAPI ExportCookieFileA(IN LPCSTR szFilename, BOOL fAppend) WCE_LINK(ExportCookieFileA);
WCE_IMPORT BOOL WINAPI ExportCookieFileW(IN LPCWSTR szFilename, BOOL fAppend) WCE_LINK(ExportCookieFileW);
WCE_IMPORT BOOL WINAPI IsDomainLegalCookieDomainA(IN LPCSTR pchDomain, IN LPCSTR pchFullDomain) WCE_LINK(IsDomainLegalCookieDomainA);
WCE_IMPORT BOOL WINAPI IsDomainLegalCookieDomainW(IN LPCWSTR pchDomain, IN LPCWSTR pchFullDomain) WCE_LINK(IsDomainLegalCookieDomainW);
WCE_IMPORT BOOL WINAPI GetUrlCacheHeaderData(IN DWORD nIdx, OUT LPDWORD lpdwData) WCE_LINK(GetUrlCacheHeaderData);
WCE_IMPORT BOOL WINAPI SetUrlCacheHeaderData(IN DWORD nIdx, IN DWORD dwData) WCE_LINK(SetUrlCacheHeaderData);
WCE_IMPORT BOOL WINAPI IncrementUrlCacheHeaderData(IN DWORD nIdx, OUT LPDWORD lpdwData) WCE_LINK(IncrementUrlCacheHeaderData);
WCE_IMPORT BOOL WINAPI LoadUrlCacheContent() WCE_LINK(LoadUrlCacheContent);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI DoConnectoidsExist(void) WCE_LINK(DoConnectoidsExist);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x500)
WCE_IMPORT BOOL WINAPI GetDiskInfoA(IN PSTR pszPath, IN OUT PDWORD pdwClusterSize, IN OUT PDWORDLONG pdlAvail, IN OUT PDWORDLONG pdlTotal) WCE_LINK(GetDiskInfoA);
#endif

#define HttpCheckCachedDavStatus HttpCheckCachedDavStatusW
#define HttpCheckDavCollection HttpCheckDavCollectionW
#define IsUrlCacheEntryExpired IsUrlCacheEntryExpiredW
#define CreateUrlCacheContainer CreateUrlCacheContainerW
#define DeleteUrlCacheContainer DeleteUrlCacheContainerW
#define FindNextUrlCacheContainer FindNextUrlCacheContainerW
#define FreeUrlCacheSpace FreeUrlCacheSpaceW
#define GetUrlCacheConfigInfo GetUrlCacheConfigInfoW
#define SetUrlCacheConfigInfo SetUrlCacheConfigInfoW
#define ImportCookieFile ImportCookieFileW
#define ExportCookieFile ExportCookieFileW
#define IsDomainLegalCookieDomain IsDomainLegalCookieDomainW
#ifdef __cplusplus
}
#endif
#endif

