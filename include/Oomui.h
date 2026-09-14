/*
 * Oomui.h -- declarations recovered from the official
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

#ifndef AKARI_OOMUI_H_
#define AKARI_OOMUI_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms919144: page-printed prototype (Windows CE 2.10 and later.). */
BOOL OomUICallback_IsCritical(void);

/* ms919151: page-printed prototype (Windows CE 2.10 and later.). */
VOID OomUICallback_NonClientPaint(HWND hwnd);

/* ms919160: page-printed prototype (Windows CE 2.10 and later.). */
HWND OomUI_CreateNotRespondingWindow(void);

/* ms919172: page-printed prototype (Windows CE 2.10 and later.). */
HWND OomUI_CreateOomWindow(void);

/* ms919181: page-printed prototype (Windows CE 2.10 and later.). */
BOOL OomUI_FShowOomWindow(void);

/* ms919190: page-printed prototype (Windows CE 2.10 and later.). */
VOID OomUI_Initialize(HINSTANCE hinst);

/* ms919210: page-printed prototype (Windows CE 2.10 and later.). */
VOID OomUI_OnShow(void);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms920087: page-printed definition (Windows CE 2.10 and later.). */
typedef struct _WINDOWINFO {
    HWND hwnd;
    LPCTSTR szWindowName;
    UINT32 fToBeClosed;
    UINT32 fToBeTerminated;
} WINDOWINFO;


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms919135: page-printed prototype (Windows CE 2.10 and later.). */
BOOL OomUICallback_CloseWindow(WINDOWINFO* pwi);

/* ms919227: page-printed prototype (Windows CE 2.10 and later.). */
VOID OomUI_SetWindowsInfo(INT cWindows, WINDOWINFO* rgwi);

#endif /* AKARI_OOMUI_H_ */
