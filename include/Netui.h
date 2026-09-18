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
/* ee495072: param-list verified against this page (proto-cite) */
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


/* --- absent-surface pass 2026-09-18: HELD Netui dialog surface.
 * Eight functions (ConnectionDialog ms908147, GetDriverName ms929238,
 * GetNewPassword aa453143, GetNewPasswordEx aa453144,
 * GetResourcePassword aa453158, GetUsernamePassword aa453176,
 * GetUsernamePasswordEx aa453177, LineConfigEdit aa453295) are in
 * netui-doc.def and print full prototypes, but every one takes a
 * parameter struct whose array-size macros are not published anywhere
 * in the corpus (corpus-wide value search 2026-09-18 found no print
 * for RMLEN, PWLEN, UNLEN, DNLEN, DRIVER_NAME_LEN or
 * NETUI_LCD_DIAL_MOD_LEN).  Shipping the structs would require
 * inventing those values, so the prints are recorded, not shipped:
 *
 * aa452847:  typedef struct ADDCONNECT_DLGPARAMS {WCHAR LocalName[RMLEN + 10];WCHAR RemoteName[RMLEN];BOOL bReadOnly;} ADDCONNECT_DLGPARAMS, *PADDCONNECT_DLGPARAMS;
 * ms929239:  typedef struct _GETDRIVERNAMEPARMS {WCHAR DriverName[DRIVER_NAME_LEN];DWORD Socket;DWORD PCCardType;} GETDRIVERNAMEPARMS, *PGETDRIVERNAMEPARMS;
 * ms931467:  typedef struct _NETUI_NEWPWD { TCHAR szNewPassword[PWLEN+1];} NETUI_NEWPWD, *PNETUI_NEWPWD;
 * ms931465:  typedef struct _NETUI_RESPWD {TCHAR szPassword[PWLEN +1];TCHAR szResourceName[RMLEN];} NETUI_RESPWD, *PNETUI_RESPWD;
 * ms931466:  typedef struct _NETUI_USERPWD {TCHAR szUserName[UNLEN + 1];TCHAR szPassword[PWLEN + 1];TCHAR szDomain[DNLEN +1];DWORD dwFlags;TCHAR szResourceName[RMLEN];} NETUI_USERPWD, *PNETUI_USERPWD;
 * aa453294:  typedef struct _LINECONFIGDATA {DWORD dwVersion;DWORD dwBaudRate;DWORD dwSettableBaud;BYTE bByteSize;BYTE bParity;BYTE bStopBits;BYTE bReserved;WORD wSettableData;WORD wWaitBong;DWORD dwCallSetupFailTimer;DWORD dwModemOptions;DWORD dwTermOptions;DWORD dwDdevCapFlags;DWORD dwModMaxLen;TCHAR szDialModifier[NETUI_LCD_DIAL_MOD_LEN + 1];WORD wSettableStopParity;} LINECONFIGDATA, *PLINECONFIGDATA;
 *
 * ms908147:  BOOL ConnectionDialog(HWND hParent,PADDCONNECT_DLGPARAMS pDlgParams);
 * ms929238:  BOOL GetDriverName(HWND hParent,PGETDRIVERNAMEPARMS pDriverParms);
 * aa453143:  BOOL WINAPI GetNewPassword ( HWND hParent, OUT PNETUI_NEWPWD pNewPwd);
 * aa453144:  BOOL WINAPI GetNewPasswordEx ( HWND hParent, OUT PNETUI_NEWPWD pNewPwd, OUT OPTIONAL HWND* phDlg);
 * aa453158:  BOOL GetResourcePassword(HWND hParent, PNETUI_RESPWD pResPwd);
 * aa453176:  BOOL GetUsernamePassword(HWND hParent, PNETUI_USERPWD pUserPwd);
 * aa453177:  BOOL GetUsernamePasswordEx ( HWND hParent, PNETUI_USERPWD pUserPwd, OPTIONAL HWND* phDlg);
 * aa453295:  BOOL LineConfigEdit(HWND hParent,PLINECONFIGDATA pLineConfigData);
 */

#endif /* AKARI_NETUI_H_ */
