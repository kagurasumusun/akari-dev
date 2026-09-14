/* Winnetwk.h -- Windows Networking (WNet) API (Windows CE).
 * Pages: tools/manifests/netgen.manifest; Link Library rows print
 * Coredll.lib (def/coredll-doc.def).  See docs/inventory.md M77b. */

#ifndef AKARI_WINNETWK_H
#define AKARI_WINNETWK_H

#include "Windef.h"    /* DWORD, BOOL, HWND, HANDLE, LPHANDLE,
                        * LPTSTR, LPCTSTR, LPVOID, LPDWORD */

/* NETRESOURCE (title, print `typedef struct _NETRESOURCE {DWORD dwScope;
 * DWORD dwType; DWORD dwDisplayType; DWORD dwUsage; LPTSTR lpLocalName;
 * LPTSTR lpRemoteName; LPTSTR lpComment; LPTSTR lpProvider; }`). */
typedef struct _NETRESOURCE {
    DWORD  dwScope;
    DWORD  dwType;
    DWORD  dwDisplayType;
    DWORD  dwUsage;
    LPTSTR lpLocalName;
    LPTSTR lpRemoteName;
    LPTSTR lpComment;
    LPTSTR lpProvider;
} NETRESOURCE, *LPNETRESOURCE;

/* CONNECTDLGSTRUCT (tagless print; tag closed on typedef name). */
typedef struct CONNECTDLGSTRUCT {
    DWORD          cbStructure;
    HWND           hwndOwner;
    LPNETRESOURCE  lpConnRes;
    DWORD          dwFlags;
    DWORD          dwDevNum;
} CONNECTDLGSTRUCT, *LPCONNECTDLGSTRUCT;

/* DISCDLGSTRUCT: print `typedef struct _wcesdk_win32_DISCDLGSTRUCT_str
 * {DWORD cbStructure;HWND hwndOwner;LPTSTR lpLocalName;
 * LPTSTR lpRemoteName;DWORD dwFlags;} DISCDLGSTRUCT;` (wcesdk tag). */
typedef struct _wcesdk_win32_DISCDLGSTRUCT_str {
    DWORD  cbStructure;
    HWND   hwndOwner;
    LPTSTR lpLocalName;
    LPTSTR lpRemoteName;
    DWORD  dwFlags;
} DISCDLGSTRUCT, *LPDISCDLGSTRUCT;

typedef struct _REMOTE_NAME_INFO {
    LPTSTR lpUniversalName;
    LPTSTR lpConnectionName;
    LPTSTR lpRemainingPath;
} REMOTE_NAME_INFO, *LPREMOTE_NAME_INFO;

typedef struct _UNIVERSAL_NAME_INFO {
    LPTSTR lpUniversalName;
} UNIVERSAL_NAME_INFO, *LPUNIVERSAL_NAME_INFO;


/* ms898713 "WNetOpenEnum" */
AKARI_CE_IMPORT DWORD WNetOpenEnumW(DWORD dwScope, DWORD dwType, DWORD dwUsage,
                    LPNETRESOURCE lpNetResource, LPHANDLE lphEnum)
                    AKARI_CE_NAME(WNetOpenEnumW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetOpenEnum WNetOpenEnumW

/* ms898709 "WNetEnumResource" */
AKARI_CE_IMPORT DWORD WNetEnumResourceW(HANDLE hEnum, LPDWORD lpcCount, LPVOID lpBuffer,
                    LPDWORD lpBufferSize)
                    AKARI_CE_NAME(WNetEnumResourceW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetEnumResource WNetEnumResourceW

/* ms898606 "WNetCloseEnum" */
AKARI_CE_IMPORT DWORD WNetCloseEnum(HANDLE hEnum)
                    AKARI_CE_NAME(WNetCloseEnum);

/* ms898589 "WNetAddConnection3" */
AKARI_CE_IMPORT DWORD WNetAddConnection3W(HWND hwndOwner, LPNETRESOURCE lpNetResource,
                    LPTSTR lpPassword, LPTSTR lpUserName,
                    DWORD dwFlags)
                    AKARI_CE_NAME(WNetAddConnection3W);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetAddConnection3 WNetAddConnection3W

/* ms898597 "WNetCancelConnection2" */
AKARI_CE_IMPORT DWORD WNetCancelConnection2W(LPTSTR lpName, DWORD dwFlags, BOOL fForce)
                    AKARI_CE_NAME(WNetCancelConnection2W);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetCancelConnection2 WNetCancelConnection2W

/* ms898611 "WNetConnectionDialog1" */
AKARI_CE_IMPORT DWORD WNetConnectionDialog1W(LPCONNECTDLGSTRUCT lpConnectDlgStruct)
                    AKARI_CE_NAME(WNetConnectionDialog1W);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetConnectionDialog1 WNetConnectionDialog1W

/* ms898697 "WNetDisconnectDialog" */
AKARI_CE_IMPORT DWORD WNetDisconnectDialog(HWND hwnd, DWORD dwType)
                    AKARI_CE_NAME(WNetDisconnectDialog);

/* ms898705 "WNetDisconnectDialog1" */
AKARI_CE_IMPORT DWORD WNetDisconnectDialog1W(LPDISCDLGSTRUCT lpDiscDlgStruct)
                    AKARI_CE_NAME(WNetDisconnectDialog1W);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetDisconnectDialog1 WNetDisconnectDialog1W

/* ms898710 "WNetGetConnection" */
AKARI_CE_IMPORT DWORD WNetGetConnectionW(LPCTSTR lpLocalName, LPTSTR lpRemoteName,
                    LPDWORD lpnLength)
                    AKARI_CE_NAME(WNetGetConnectionW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetGetConnection WNetGetConnectionW

/* ms898711 "WNetGetUniversalName" */
AKARI_CE_IMPORT DWORD WNetGetUniversalNameW(LPCTSTR lpLocalPath, DWORD dwInfoLevel,
                    LPVOID lpBuffer, LPDWORD lpBufferSize)
                    AKARI_CE_NAME(WNetGetUniversalNameW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetGetUniversalName WNetGetUniversalNameW

/* ms898712 "WNetGetUser" */
AKARI_CE_IMPORT DWORD WNetGetUserW(LPCTSTR lpName, LPTSTR lpUserName, LPDWORD lpnLength)
                    AKARI_CE_NAME(WNetGetUserW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define WNetGetUser WNetGetUserW

#endif /* AKARI_WINNETWK_H */
