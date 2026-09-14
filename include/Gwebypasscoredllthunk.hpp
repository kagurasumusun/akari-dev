/*
 * Gwebypasscoredllthunk.hpp -- declarations recovered from the official
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

#ifndef AKARI_GWEBYPASSCOREDLLTHUNK_HPP_
#define AKARI_GWEBYPASSCOREDLLTHUNK_HPP_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Winuser.h"   /* HWND, WPARAM, LPARAM, HICON, PICONINFO (ICONINFO) */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms905519: page-printed prototype (Windows CE .NET 4.0 and later.). */
BOOL WINAPI DestroyIcon_I(HICON hicon);

/* ms906086: page-printed prototype (Windows CE .NET 4.0 and later.). */
HWND WINAPI GetForegroundWindow_I(void);

/* ms919599: page-printed prototype (Windows CE .NET 4.0 and later.). */
LRESULT WINAPI SendMessageW_I(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* ms919607: page-printed prototype (Windows CE .NET 4.0 and later.). */
BOOL WINAPI SetForegroundWindow_I(HWND hwnd);


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms905514: page-printed prototype (Windows CE .NET 4.0 and later.). */
HICON WINAPI CreateIconIndirect_I(PICONINFO pii);

#endif /* AKARI_GWEBYPASSCOREDLLTHUNK_HPP_ */
