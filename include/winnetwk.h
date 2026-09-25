/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINNETWK_H
#define WCE_WINNETWK_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagNETRESOURCEA { DWORD dwScope; DWORD dwType; DWORD dwDisplayType; DWORD dwUsage; LPSTR lpLocalName; LPSTR lpRemoteName; LPSTR lpComment; LPSTR lpProvider; } NETRESOURCEA, *PNETRESOURCEA, *LPNETRESOURCEA;
typedef struct tagNETRESOURCEW { DWORD dwScope; DWORD dwType; DWORD dwDisplayType; DWORD dwUsage; LPWSTR lpLocalName; LPWSTR lpRemoteName; LPWSTR lpComment; LPWSTR lpProvider; } NETRESOURCEW, *PNETRESOURCEW, *LPNETRESOURCEW;
typedef struct tagCONNECTDLGSTRUCTA { DWORD cbStructure; HWND hwndOwner; LPNETRESOURCEA lpConnRes; DWORD dwFlags; DWORD dwDevNum; } CONNECTDLGSTRUCTA, *PCONNECTDLGSTRUCTA, *LPCONNECTDLGSTRUCTA;
typedef struct tagCONNECTDLGSTRUCTW { DWORD cbStructure; HWND hwndOwner; LPNETRESOURCEW lpConnRes; DWORD dwFlags; DWORD dwDevNum; } CONNECTDLGSTRUCTW, *PCONNECTDLGSTRUCTW, *LPCONNECTDLGSTRUCTW;
typedef struct tagDISCDLGSTRUCTA { DWORD cbStructure; HWND hwndOwner; LPSTR lpLocalName; LPSTR lpRemoteName; DWORD dwFlags; } DISCDLGSTRUCTA, *PDISCDLGSTRUCTA, *LPDISCDLGSTRUCTA;
typedef struct tagDISCDLGSTRUCTW { DWORD cbStructure; HWND hwndOwner; LPWSTR lpLocalName; LPWSTR lpRemoteName; DWORD dwFlags; } DISCDLGSTRUCTW, *PDISCDLGSTRUCTW, *LPDISCDLGSTRUCTW;
typedef struct tagUNIVERSAL_NAME_INFOA { LPSTR lpUniversalName; } UNIVERSAL_NAME_INFOA, *PUNIVERSAL_NAME_INFOA, *LPUNIVERSAL_NAME_INFOA;
typedef struct tagUNIVERSAL_NAME_INFOW { LPWSTR lpUniversalName; } UNIVERSAL_NAME_INFOW, *PUNIVERSAL_NAME_INFOW, *LPUNIVERSAL_NAME_INFOW;
typedef struct tagREMOTE_NAME_INFOA { LPSTR lpUniversalName; LPSTR lpConnectionName; LPSTR lpRemainingPath; } REMOTE_NAME_INFOA, *PREMOTE_NAME_INFOA, *LPREMOTE_NAME_INFOA;
typedef struct tagREMOTE_NAME_INFOW { LPWSTR lpUniversalName; LPWSTR lpConnectionName; LPWSTR lpRemainingPath; } REMOTE_NAME_INFOW, *PREMOTE_NAME_INFOW, *LPREMOTE_NAME_INFOW;

WCE_IMPORT DWORD WINAPI WNetAddConnection3A(HWND hwndOwner, LPNETRESOURCEA lpNetResource, LPCSTR lpPassword, LPCSTR lpUserName, DWORD dwFlags) WCE_LINK(WNetAddConnection3A);
WCE_IMPORT DWORD WINAPI WNetAddConnection3W(HWND hwndOwner, LPNETRESOURCEW lpNetResource, LPCWSTR lpPassword, LPCWSTR lpUserName, DWORD dwFlags) WCE_LINK(WNetAddConnection3W);
WCE_IMPORT DWORD WINAPI WNetCancelConnection2A(LPCSTR lpName, DWORD dwFlags, BOOL fForce) WCE_LINK(WNetCancelConnection2A);
WCE_IMPORT DWORD WINAPI WNetCancelConnection2W(LPCWSTR lpName, DWORD dwFlags, BOOL fForce) WCE_LINK(WNetCancelConnection2W);
WCE_IMPORT DWORD WINAPI WNetGetConnectionA(LPCSTR lpLocalName, LPSTR lpRemoteName, LPDWORD lpnLength) WCE_LINK(WNetGetConnectionA);
WCE_IMPORT DWORD WINAPI WNetGetConnectionW(LPCWSTR lpLocalName, LPWSTR lpRemoteName, LPDWORD lpnLength) WCE_LINK(WNetGetConnectionW);
WCE_IMPORT DWORD WINAPI WNetDisconnectDialog(HWND hwnd, DWORD dwType) WCE_LINK(WNetDisconnectDialog);
WCE_IMPORT DWORD WINAPI WNetConnectionDialog1A(LPCONNECTDLGSTRUCTA lpConnDlgStruct) WCE_LINK(WNetConnectionDialog1A);
WCE_IMPORT DWORD WINAPI WNetConnectionDialog1W(LPCONNECTDLGSTRUCTW lpConnDlgStruct) WCE_LINK(WNetConnectionDialog1W);
WCE_IMPORT DWORD WINAPI WNetDisconnectDialog1A(LPDISCDLGSTRUCTA lpConnDlgStruct) WCE_LINK(WNetDisconnectDialog1A);
WCE_IMPORT DWORD WINAPI WNetDisconnectDialog1W(LPDISCDLGSTRUCTW lpConnDlgStruct) WCE_LINK(WNetDisconnectDialog1W);
WCE_IMPORT DWORD WINAPI WNetOpenEnumA(DWORD dwScope, DWORD dwType, DWORD dwUsage, LPNETRESOURCEA lpNetResource, LPHANDLE lphEnum) WCE_LINK(WNetOpenEnumA);
WCE_IMPORT DWORD WINAPI WNetOpenEnumW(DWORD dwScope, DWORD dwType, DWORD dwUsage, LPNETRESOURCEW lpNetResource, LPHANDLE lphEnum) WCE_LINK(WNetOpenEnumW);
WCE_IMPORT DWORD WINAPI WNetEnumResourceA(HANDLE hEnum, LPDWORD lpcCount, LPVOID lpBuffer, LPDWORD lpBufferSize) WCE_LINK(WNetEnumResourceA);
WCE_IMPORT DWORD WINAPI WNetEnumResourceW(HANDLE hEnum, LPDWORD lpcCount, LPVOID lpBuffer, LPDWORD lpBufferSize) WCE_LINK(WNetEnumResourceW);
WCE_IMPORT DWORD WINAPI WNetCloseEnum(HANDLE hEnum) WCE_LINK(WNetCloseEnum);
WCE_IMPORT DWORD WINAPI WNetGetUniversalNameA(LPCSTR lpLocalPath, DWORD dwInfoLevel, LPVOID lpBuffer, LPDWORD lpBufferSize) WCE_LINK(WNetGetUniversalNameA);
WCE_IMPORT DWORD WINAPI WNetGetUniversalNameW(LPCWSTR lpLocalPath, DWORD dwInfoLevel, LPVOID lpBuffer, LPDWORD lpBufferSize) WCE_LINK(WNetGetUniversalNameW);
WCE_IMPORT DWORD WINAPI WNetGetUserA(LPCSTR lpName, LPSTR lpUserName, LPDWORD lpnLength) WCE_LINK(WNetGetUserA);
WCE_IMPORT DWORD WINAPI WNetGetUserW(LPCWSTR lpName, LPWSTR lpUserName, LPDWORD lpnLength) WCE_LINK(WNetGetUserW);

#define WNetAddConnection3 WNetAddConnection3W
#define WNetCancelConnection2 WNetCancelConnection2W
#define WNetGetConnection WNetGetConnectionW
#define WNetConnectionDialog1 WNetConnectionDialog1W
#define WNetDisconnectDialog1 WNetDisconnectDialog1W
#define WNetOpenEnum WNetOpenEnumW
#define WNetEnumResource WNetEnumResourceW
#define WNetGetUniversalName WNetGetUniversalNameW
#define WNetGetUser WNetGetUserW
#ifdef __cplusplus
}
#endif
#endif

