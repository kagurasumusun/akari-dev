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
 * from the official pages (tools/decl-d1.py). -------- */

/* ms919626: page-printed prototype (Windows CE 2.10 and later.). */
void Startup_DestroyDialogCallback(void);

/* ms919633: page-printed prototype (Windows CE 2.10 and later.). */
void Startup_Initialize(HINSTANCE hinst);

/* ms919638: page-printed prototype (Windows CE 2.10 and later.). */
void Startup_PowerOnNotification(HWND hwndDlg);

/* ms919641: page-printed prototype (Windows CE 2.10 and later.). */
BOOL Startup_WantStartupScreen(void);


/* ms940352 Startup_DlgProc: print `BOOL Startup_DlgProc( HWND hDlg,UINT message,WPARAMwParam,LPARAM lParam);`
 * (Windows CE 2.10 and later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL Startup_DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(Startup_DlgProc);


/* ee501481 Startup_WantStartupScreen: print `BOOL Startup_WantStartupScreen(void);`
 * (generation not stated; Link Library: not stated) */
AKARI_CE_IMPORT BOOL Startup_WantStartupScreen(void) AKARI_CE_NAME(Startup_WantStartupScreen);

/* ee503134 Startup_DestroyDialogCallback: print `void Startup_DestroyDialogCallback(void);`
 * (generation not stated; Link Library: not stated) */
AKARI_CE_IMPORT void Startup_DestroyDialogCallback(void) AKARI_CE_NAME(Startup_DestroyDialogCallback);

#endif /* AKARI_STARTUI_H_ */
