/*
 * Calibrui.h -- declarations recovered from the official
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

#ifndef AKARI_CALIBRUI_H_
#define AKARI_CALIBRUI_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms920024: page-printed prototype (Windows CE 2.10 and later.). */
void TouchCalibrateUI_DrawConfirmationScreen(HDC hdc);

/* ms920026: page-printed prototype (Windows CE 2.10 and later.). */
void TouchCalibrateUI_DrawMainScreen(HDC hdc);

/* ms920028: page-printed prototype (Windows CE 2.10 and later.). */
void TouchCalibrateUI_HandleUserInputMessage(UINT Message, UINT wParam, UINT lParam);

/* ms920033: page-printed prototype (Windows CE 2.10 and later.). */
void TouchCalibrateUI_WaitForConfirmation(HANDLE hevt, HDC hdc);

#endif /* AKARI_CALIBRUI_H_ */
