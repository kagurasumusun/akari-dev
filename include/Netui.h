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
 * from the official pages (tools/decl-d1.py). --------
 *
 * Audit 2026-09-16 (crosscheck, real WinCE clang): six of the seven
 * prototypes in this block (AdapterIPProperties, CreateScanDevice,
 * DisconnectDialog, GetIPAddress, GetNetString, NetMsgBox) were also
 * declared below in the canonical AKARI_CE_IMPORT form, harvested
 * from the ee49xxxx page family for the same six functions.  Clang
 * rejects the pair (-Wdll-attribute-on-redeclaration), which broke
 * `make crosscheck` on this header for all six CE targets.  The
 * plain duplicates are removed and the generation each ms921xxx page
 * stated -- which the surviving ee pages do not state -- is carried
 * onto the twins below.  LineTranslateDialog has no import-form twin
 * and is left exactly as it was. --------------------- */

/* ms921405: page-printed prototype (Windows CE 2.10 and later.; netui.lib). */
DWORD LineTranslateDialog(HWND hParent, HWND* pDialogWnd);


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
 * (ee page states no generation; the ms921399 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and later.;
 * Link Library: netui.lib) */
AKARI_CE_IMPORT int GetNetString(UINT uID, LPTSTR lpBuffer, int cchBufferMax) AKARI_CE_NAME(GetNetString);

/* ee493233 NetMsgBox: print `BOOL NetMsgBox(
HWND hParent,
DWORD dwFlags,
TCHAR* szStr
);`
 * (ee page states no generation; the ms921406 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and later.;
 * Link Library: netui.lib) */
AKARI_CE_IMPORT BOOL NetMsgBox(HWND hParent, DWORD dwFlags, TCHAR *szStr) AKARI_CE_NAME(NetMsgBox);

/* ee493629 CreateScanDevice: print `int CreateScanDevice(
HINSTANCE hInstance,
HWND hWnd
);`
 * (ee page states no generation; the ms921391 print of the same
 * function, removed as a duplicate above, stated Windows CE .NET 4.0 and later.;
 * Link Library: netui.lib) */
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
 * (ee page states no generation; the ms921395 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and later.;
 * Link Library: netui.lib) */
AKARI_CE_IMPORT BOOL DisconnectDialog(HWND hParent, DWORD dwType) AKARI_CE_NAME(DisconnectDialog);

/* ee493896 GetIPAddress: print `DWORD GetIPAddress(
HWND hParent
);`
 * (ee page states no generation; the ms921398 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and later.;
 * Link Library: netui.lib) */
AKARI_CE_IMPORT DWORD GetIPAddress(HWND hParent) AKARI_CE_NAME(GetIPAddress);

/* ee494642 AdapterIPProperties: print `BOOL AdapterIPProperties(
HWND hWndOwner,
LPTSTR szAdapterName
);`
 * (ee page states no generation; the ms921392 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and later.;
 * Link Library: netui.lib) */
AKARI_CE_IMPORT BOOL AdapterIPProperties(HWND hWndOwner, LPTSTR szAdapterName) AKARI_CE_NAME(AdapterIPProperties);

#endif /* AKARI_NETUI_H_ */
