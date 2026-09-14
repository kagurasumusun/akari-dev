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

#endif /* AKARI_NETUI_H_ */
