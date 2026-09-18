/*
 * Startui.h -- declarations recovered from the official
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

#ifndef AKARI_STARTUI_H_
#define AKARI_STARTUI_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). --------
 *
 * Audit 2026-09-16 (crosscheck, real WinCE clang):
 * Startup_DestroyDialogCallback and Startup_WantStartupScreen were
 * declared here as plain prototypes AND again below in the canonical
 * AKARI_CE_IMPORT form from the ee5xxxxx page family, which Clang
 * rejects (-Wdll-attribute-on-redeclaration).  The plain duplicates
 * are removed; the ms919626/ms919641 generation those prints stated
 * is carried onto the surviving twins below, whose ee pages state
 * none.  Startup_Initialize and Startup_PowerOnNotification have no
 * import-form twin and are left exactly as they were. ------------ */

/* ms919633: page-printed prototype (Windows CE 2.10 and later.). */
void Startup_Initialize(HINSTANCE hinst);

/* ms919638: page-printed prototype (Windows CE 2.10 and later.). */
void Startup_PowerOnNotification(HWND hwndDlg);


/* ms940352 Startup_DlgProc: print `BOOL Startup_DlgProc( HWND hDlg,UINT message,WPARAMwParam,LPARAM lParam);`
 * (Windows CE 2.10 and later.; Link Library: not stated) */
/* ee502285: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT BOOL Startup_DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(Startup_DlgProc);


/* ee501481 Startup_WantStartupScreen: print `BOOL Startup_WantStartupScreen(void);`
 * (ee page states no generation; the ms919641 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and
 * later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL Startup_WantStartupScreen(void) AKARI_CE_NAME(Startup_WantStartupScreen);

/* ee503134 Startup_DestroyDialogCallback: print `void Startup_DestroyDialogCallback(void);`
 * (ee page states no generation; the ms919626 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and
 * later.; Link Library: not stated) */
AKARI_CE_IMPORT void Startup_DestroyDialogCallback(void) AKARI_CE_NAME(Startup_DestroyDialogCallback);

#endif /* AKARI_STARTUI_H_ */
