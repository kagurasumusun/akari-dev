/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_BT_API_H
#define WCE_BT_API_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagBTEVENT { DWORD dwEventId; DWORD dwReserved; BYTE baEventData[64]; } BTEVENT, *PBTEVENT, *LPBTEVENT;
typedef struct tagBT_PAN_NUM_CONNECTIONS { DWORD dwSize; DWORD NumConnections; } BT_PAN_NUM_CONNECTIONS, *PBT_PAN_NUM_CONNECTIONS, *LPBT_PAN_NUM_CONNECTIONS;

WCE_IMPORT int WINAPI BthWriteScanEnableMask(unsigned char mask) WCE_LINK(BthWriteScanEnableMask);
WCE_IMPORT int WINAPI BthReadScanEnableMask(unsigned char *pmask) WCE_LINK(BthReadScanEnableMask);
WCE_IMPORT int WINAPI BthWritePageTimeout(unsigned short timeout) WCE_LINK(BthWritePageTimeout);
WCE_IMPORT int WINAPI BthReadPageTimeout(unsigned short *ptimeout) WCE_LINK(BthReadPageTimeout);
WCE_IMPORT int WINAPI BthWriteCOD(unsigned int cod) WCE_LINK(BthWriteCOD);
WCE_IMPORT int WINAPI BthReadCOD(unsigned int *pcod) WCE_LINK(BthReadCOD);
WCE_IMPORT int WINAPI BthWriteAuthenticationEnable(unsigned char ae) WCE_LINK(BthWriteAuthenticationEnable);
WCE_IMPORT int WINAPI BthReadAuthenticationEnable(unsigned char *pae) WCE_LINK(BthReadAuthenticationEnable);
WCE_IMPORT int WINAPI BthGetBasebandHandles(int cHandles, unsigned short *pHandles, int *pcHandlesReturned) WCE_LINK(BthGetBasebandHandles);
WCE_IMPORT int WINAPI BthGetHardwareStatus(int *pistatus) WCE_LINK(BthGetHardwareStatus);
WCE_IMPORT int WINAPI BthReadLocalVersion(unsigned char *phci_version, unsigned short *phci_revision, unsigned char *plmp_version, unsigned short *plmp_subversion, unsigned short *pmanufacturer, unsigned char *plmp_features) WCE_LINK(BthReadLocalVersion);
WCE_IMPORT int WINAPI BthCancelInquiry(void) WCE_LINK(BthCancelInquiry);
WCE_IMPORT int WINAPI BthTerminateIdleConnections(void) WCE_LINK(BthTerminateIdleConnections);
WCE_IMPORT int WINAPI BthClearInquiryFilter(void) WCE_LINK(BthClearInquiryFilter);
WCE_IMPORT int WINAPI BthSetSecurityUI(HANDLE hEvent, DWORD dwStoreTimeout, DWORD dwProcTimeout) WCE_LINK(BthSetSecurityUI);
WCE_IMPORT int WINAPI BthCloseConnection(unsigned short handle) WCE_LINK(BthCloseConnection);
WCE_IMPORT int WINAPI BthAcceptSCOConnections(BOOL fAccept) WCE_LINK(BthAcceptSCOConnections);
WCE_IMPORT int WINAPI BthNsLookupServiceBegin(LPWSAQUERYSET pQuerySet, DWORD dwFlags, LPHANDLE lphLookup) WCE_LINK(BthNsLookupServiceBegin);
WCE_IMPORT int WINAPI BthNsLookupServiceNext(HANDLE hLookup, DWORD dwFlags, LPDWORD lpdwBufferLength, LPWSAQUERYSET pResults) WCE_LINK(BthNsLookupServiceNext);
WCE_IMPORT int WINAPI BthNsLookupServiceEnd(HANDLE hLookup) WCE_LINK(BthNsLookupServiceEnd);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI RegisterBluetoothCOMPort(LPCWSTR lpszType, DWORD dwIndex, PORTEMUPortParams* pParams) WCE_LINK(RegisterBluetoothCOMPort);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI DeregisterBluetoothCOMPort(HANDLE hDevice) WCE_LINK(DeregisterBluetoothCOMPort);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HANDLE WINAPI RequestBluetoothNotifications(DWORD dwClass, HANDLE hMsgQ) WCE_LINK(RequestBluetoothNotifications);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI StopBluetoothNotifications(HANDLE h) WCE_LINK(StopBluetoothNotifications);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT int WINAPI BthActivatePAN(BOOL fActivate) WCE_LINK(BthActivatePAN);
#endif

#ifdef __cplusplus
}
#endif
#endif

