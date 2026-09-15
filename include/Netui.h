/*
 * Netui.h -- declarations recovered from the official
 * page prints (tools/decl-d1.py, M105 header creation).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own
 * print (page id cited).  Prints whose types include/
 * cannot yet resolve are recorded verbatim in the
 * header comment blocks by later passes; nothing is
 * dropped or invented.
 */

#ifndef AKARI_NETUI_H_
#define AKARI_NETUI_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms921392: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
BOOL AdapterIPProperties(HWND hWndOwner, LPTSTR szAdapterName);

/* ms921391: page-printed prototype (Windows CE .NET 4.0 and later.; netui.lib). */
int CreateScanDevice(HINSTANCE hInstance, HWND hWnd);

/* ms921395: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
BOOL DisconnectDialog(HWND hParent, DWORD dwType);

/* ms921398: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
DWORD GetIPAddress(HWND hParent);

/* ms921399: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
int GetNetString(UINT uID, LPTSTR lpBuffer, int cchBufferMax);

/* ms921405: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
DWORD LineTranslateDialog(HWND hParent, HWND* pDialogWnd);

/* ms921406: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
BOOL NetMsgBox(HWND hParent, DWORD dwFlags, TCHAR* szStr);


/* M134: declared from the official Windows CE page cited on
 *  each prototype (tools/coverage-audit.py app-layer gap list). */

/* ms913115 RegisterIPClass: print `void RegisterIPClass( HINSTANCE hInst);`
 * (Windows CE 5.0 and later.; Link Library: Netui.lib) */
AKARI_CE_IMPORT void RegisterIPClass(HINSTANCE hInst) AKARI_CE_NAME(RegisterIPClass);

/* ms928587 CloseUsernamePasswordDialog: print `BOOL CloseUsernamePasswordDialog(
HWND hDlg);`
 * (Windows CE 5.0 and later.; Link Library: Netui.lib) */
AKARI_CE_IMPORT BOOL CloseUsernamePasswordDialog(HWND hDlg) AKARI_CE_NAME(CloseUsernamePasswordDialog);


/* ee493082 GetNetString: print `int GetNetString(
UINT uID,
LPTSTR lpBuffer,
int cchBufferMax
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT int GetNetString(UINT uID, LPTSTR lpBuffer, int cchBufferMax) AKARI_CE_NAME(GetNetString);

/* ee493233 NetMsgBox: print `BOOL NetMsgBox(
HWND hParent,
DWORD dwFlags,
TCHAR* szStr
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT BOOL NetMsgBox(HWND hParent, DWORD dwFlags, TCHAR *szStr) AKARI_CE_NAME(NetMsgBox);

/* ee493629 CreateScanDevice: print `int CreateScanDevice(
HINSTANCE hInstance,
HWND hWnd
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT int CreateScanDevice(HINSTANCE hInstance, HWND hWnd) AKARI_CE_NAME(CreateScanDevice);

/* ee493662 UnregisterIPClass: print `void UnregisterIPClass(
HINSTANCE hInst
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT void UnregisterIPClass(HINSTANCE hInst) AKARI_CE_NAME(UnregisterIPClass);

/* ee493832 DisconnectDialog: print `BOOL DisconnectDialog(
HWND hParent,
DWORD dwType
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT BOOL DisconnectDialog(HWND hParent, DWORD dwType) AKARI_CE_NAME(DisconnectDialog);

/* ee493896 GetIPAddress: print `DWORD GetIPAddress(
HWND hParent
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT DWORD GetIPAddress(HWND hParent) AKARI_CE_NAME(GetIPAddress);

/* ee494642 AdapterIPProperties: print `BOOL AdapterIPProperties(
HWND hWndOwner,
LPTSTR szAdapterName
);`
 * (generation not stated; Link Library: netui.lib) */
AKARI_CE_IMPORT BOOL AdapterIPProperties(HWND hWndOwner, LPTSTR szAdapterName) AKARI_CE_NAME(AdapterIPProperties);

#endif /* AKARI_NETUI_H_ */
