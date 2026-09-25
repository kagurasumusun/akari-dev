/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_CONNMGR_H
#define WCE_CONNMGR_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCONNMGR_CONNECTIONINFO { DWORD cbSize; DWORD dwParams; DWORD dwFlags; DWORD dwPriority; BOOL bExclusive; BOOL bDisabled; GUID guidDestNet; HWND hWnd; UINT uMsg; LPARAM lParam; ULONG ulMaxCost; ULONG ulMinRcvBw; ULONG ulMaxConnLatency; } CONNMGR_CONNECTIONINFO, *PCONNMGR_CONNECTIONINFO, *LPCONNMGR_CONNECTIONINFO;

#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrEstablishConnection(CONNMGR_CONNECTIONINFO *pConnInfo, HANDLE *phConnection) WCE_LINK(ConnMgrEstablishConnection);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrEstablishConnectionSync(CONNMGR_CONNECTIONINFO *pConnInfo, HANDLE *phConnection, DWORD dwTimeout, DWORD *pdwStatus) WCE_LINK(ConnMgrEstablishConnectionSync);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrConnectionStatus(HANDLE hConnection, DWORD *pdwStatus) WCE_LINK(ConnMgrConnectionStatus);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrReleaseConnection(HANDLE hConnection, LONG lCache) WCE_LINK(ConnMgrReleaseConnection);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrSetConnectionPriority(HANDLE hConnection, DWORD dwPriority) WCE_LINK(ConnMgrSetConnectionPriority);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrProviderMessage(HANDLE hConnection, const GUID *pguidProvider, DWORD *pdwIndex, DWORD dwMsg1, DWORD dwMsg2, PBYTE pParams, ULONG cbParamSize) WCE_LINK(ConnMgrProviderMessage);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrUnregisterScheduledConnection(LPCTSTR pwszToken) WCE_LINK(ConnMgrUnregisterScheduledConnection);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ConnMgrMapURL(LPCTSTR pwszURL, GUID *pguid, DWORD *pdwIndex) WCE_LINK(ConnMgrMapURL);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI ConnMgrApiReadyEvent() WCE_LINK(ConnMgrApiReadyEvent);
#endif

#ifdef __cplusplus
}
#endif
#endif

