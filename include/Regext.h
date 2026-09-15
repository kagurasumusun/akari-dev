/*
 * Regext.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: regext.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_REGEXT_H
#define AKARI_REGEXT_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Winreg.h"   /* HKEY */

/* --- Handle types no CE page typedefs. ------------------------------
 * HREGNOTIFY: 7 corpus pages mention it and none prints a typedef, but
 * ee488922 "RegistryCloseNotification" prints
 *   `HRESULT WINAPI RegistryCloseNotification( HREGNOTIFY hNotify );`
 * (Header: regext.h, Link Library: aygshell.lib, Windows Embedded CE 6.0),
 * and the notification callbacks take it as `HREGNOTIFY hNotify`.  A value
 * the registry hands out and the documented closer consumes is a handle;
 * see Windef.h:236 for the in-tree precedent. */
typedef HANDLE HREGNOTIFY;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee488568 REG_COMPARISONTYPE: page print
 * typedef enum tagREG_COMPARISONTYPE { REG_CT_ANYCHANGE, REG_CT_EQUAL, REG_CT_NOT_EQUAL, REG_CT_GREATER, REG_CT_GREATER_OR_EQUAL, REG_CT_LESS, REG_CT_LE
 * (Windows Embedded CE 6.0 and later) */
typedef enum tagREG_COMPARISONTYPE {
    REG_CT_ANYCHANGE,
    REG_CT_EQUAL,
    REG_CT_NOT_EQUAL,
    REG_CT_GREATER,
    REG_CT_GREATER_OR_EQUAL,
    REG_CT_LESS,
    REG_CT_LESS_OR_EQUAL,
    REG_CT_CONTAINS,
    REG_CT_STARTS_WITH,
    REG_CT_ENDS_WITH
} REG_COMPARISONTYPE;


/* ee488186 RegistryTestExchangeDWORD: print `HRESULT WINAPI RegistryTestExchangeDWORD(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
DWORD dwOldValue,
DWORD dwNewValue
);`
 * (Windows Embedded CE 6.0 and later; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryTestExchangeDWORD(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwOldValue, DWORD dwNewValue) AKARI_CE_NAME(RegistryTestExchangeDWORD);

/* ee488205 RegistryStopNotification: print `HRESULT WINAPI RegistryStopNotification(
LPCTSTR pszName
);`
 * (Windows Embedded CE 6.0 and later; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryStopNotification(LPCTSTR pszName) AKARI_CE_NAME(RegistryStopNotification);

/* ee488582 RegistryGetDWORD: print `HRESULT WINAPI RegistryGetDWORD(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
DWORD* pdwData
);`
 * (Windows Embedded CE 6.0 and later; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryGetDWORD(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD *pdwData) AKARI_CE_NAME(RegistryGetDWORD);

/* ee488611 RegistrySetString: print `HRESULT WINAPI RegistrySetString(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
LPCTSTR pszData
);`
 * (Windows Embedded CE 6.0 and later; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistrySetString(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszData) AKARI_CE_NAME(RegistrySetString);

/* ee488764 RegistrySetDWORD: print `HRESULT WINAPI RegistrySetDWORD(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
DWORD dwData
);`
 * (Windows Embedded CE 6.0 and later; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistrySetDWORD(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwData) AKARI_CE_NAME(RegistrySetDWORD);

/* ee488928 RegistryGetString: print `HRESULT WINAPI RegistryGetString(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
LPTSTR pszData,
UINT cchData
);`
 * (Windows Embedded CE 6.0 and later; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryGetString(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPTSTR pszData, UINT cchData) AKARI_CE_NAME(RegistryGetString);


/* ee488645 NOTIFICATIONCONDITION: page print
 * typedef struct tagNOTIFICATIONCONDITION { REG_COMPARISONTYPE ctComparisonType; DWORD dwMask; union TargetValue { LPCTSTR psz; DWORD dw; }; } NOTIFICAT
 * (generation not stated) */
typedef struct tagNOTIFICATIONCONDITION {
    REG_COMPARISONTYPE ctComparisonType;
    DWORD dwMask;
    union {
        LPCTSTR psz;
        DWORD dw;
    };
} NOTIFICATIONCONDITION;


/* ee488776 RegistryNotifyApp: print `HRESULT WINAPI RegistryNotifyApp(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
LPCTSTR pszName,
LPCTSTR pszApp,
LPCTSTR pszClass,
LPCTSTR pszWindow,
UINT msg,
DWORD dwFlags,
NOTIFICATIONCONDITION* pCondition
);`
 * (generation not stated; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryNotifyApp(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszName, LPCTSTR pszApp, LPCTSTR pszClass, LPCTSTR pszWindow, UINT msg, DWORD dwFlags, NOTIFICATIONCONDITION *pCondition) AKARI_CE_NAME(RegistryNotifyApp);


/* ee488220 NOTIFYMSGQUEUEPACKET: page print
 * typedef struct tagNOTIFYMSGQUEUEPACKET { HREGNOTIFY hNotify; DWORD dwUserData; UINT cbData; BYTE rgData[1]; } NOTIFYMSGQUEUEPACKET;
 * (generation not stated) */
typedef struct tagNOTIFYMSGQUEUEPACKET {
    HREGNOTIFY hNotify;
    DWORD dwUserData;
    UINT cbData;
    BYTE rgData[1];
} NOTIFYMSGQUEUEPACKET;


/* ee488231 RegistryNotifyWindow: print `HRESULT WINAPI RegistryNotifyWindow(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
HWND hWnd,
UINT msg,
DWORD dwUserData,
NOTIFICATIONCONDITION* pCondition,
HREGNOTIFY* phNotify
);`
 * (generation not stated; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryNotifyWindow(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, HWND hWnd, UINT msg, DWORD dwUserData, NOTIFICATIONCONDITION *pCondition, HREGNOTIFY *phNotify) AKARI_CE_NAME(RegistryNotifyWindow);

/* ee488614 RegistryNotifyMsgQueue: print `HRESULT WINAPI RegistryNotifyMsgQueue(
HKEY hKey,
LPCTSTR pszSubKey,
LPCTSTR pszValueName,
LPCTSTR pszMsgQueue,
DWORD dwUserData,
NOTIFICATIONCONDITION* pCondition,
HREGNOTIFY* phNotify
);`
 * (generation not stated; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryNotifyMsgQueue(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszMsgQueue, DWORD dwUserData, NOTIFICATIONCONDITION *pCondition, HREGNOTIFY *phNotify) AKARI_CE_NAME(RegistryNotifyMsgQueue);

/* ee488922 RegistryCloseNotification: print `HRESULT WINAPI RegistryCloseNotification(
HREGNOTIFY hNotify
);`
 * (generation not stated; Link Library: aygshell.lib) */
AKARI_CE_IMPORT HRESULT RegistryCloseNotification(HREGNOTIFY hNotify) AKARI_CE_NAME(RegistryCloseNotification);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_REGEXT_H */
