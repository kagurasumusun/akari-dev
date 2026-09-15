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


/* aa452939 DestroyIcon_I: print `BOOL WINAPI DestroyIcon_I(HICON hicon);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL DestroyIcon_I(HICON hicon) AKARI_CE_NAME(DestroyIcon_I);

/* aa452973 DrawIconEx_I: print `BOOL WINAPI DrawIconEx_I(HDC hdc,int X,int Y,HICON hicon,int cx,int cy,UINT istepIfAniCur,HBRUSH hbrFlickerFreeDraw,UINT diFlags);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL DrawIconEx_I(HDC hdc, int X, int Y, HICON hicon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) AKARI_CE_NAME(DrawIconEx_I);

/* aa453249 KillTimer_I: print `BOOL WINAPI KillTimer_I(HWND hwnd,UINT uIDEvent);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL KillTimer_I(HWND hwnd, UINT uIDEvent) AKARI_CE_NAME(KillTimer_I);

/* aa453412 LoadIconW_I: print `HICON WINAPI LoadIconW_I(HINSTANCE hinst,PCTSTR pszIcon);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT HICON LoadIconW_I(HINSTANCE hinst, PCTSTR pszIcon) AKARI_CE_NAME(LoadIconW_I);

/* ms908176 CreateIconIndirect_I: print `HICON WINAPI CreateIconIndirect_I(PICONINFO pii);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT HICON CreateIconIndirect_I(PICONINFO pii) AKARI_CE_NAME(CreateIconIndirect_I);

/* ms929245 GetForegroundWindow_I: print `HWND WINAPI GetForegroundWindow_I(void);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT HWND GetForegroundWindow_I(void) AKARI_CE_NAME(GetForegroundWindow_I);

/* ms939982 SendMessageW_I: print `LRESULT WINAPI SendMessageW_I(HWND hWnd,UINT uMsg,WPARAMwParam,LPARAM lParam);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT LRESULT SendMessageW_I(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(SendMessageW_I);

/* ms940025 SetForegroundWindow_I: print `BOOL WINAPI SetForegroundWindow_I( HWND hwnd);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL SetForegroundWindow_I(HWND hwnd) AKARI_CE_NAME(SetForegroundWindow_I);

#endif /* AKARI_GWEBYPASSCOREDLLTHUNK_HPP_ */
