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
 * from the official pages (tools/decl-d1.py). --------
 *
 * Audit 2026-09-16 (crosscheck, real WinCE clang): this block
 * originally re-declared DestroyIcon_I, GetForegroundWindow_I,
 * SendMessageW_I, SetForegroundWindow_I and CreateIconIndirect_I as
 * plain `RET WINAPI name(...)` prototypes.  Every one of those five
 * is declared again below by the later pass in the tree's canonical
 * form (AKARI_CE_IMPORT + AKARI_CE_NAME), from a different page id
 * for the same function -- the two passes harvested the same
 * function from the ms9xxxxx and aa4xxxxx page families and neither
 * de-duplicated against the other.  Clang rejects the pair outright
 * (-Wdll-attribute-on-redeclaration: a redeclaration may not add
 * dllimport), so `make crosscheck` failed on this header for all six
 * CE targets.  The duplicate plain prototypes are removed here
 * rather than the import-attributed ones: the latter carry the
 * AKARI_CE_NAME import spelling every other header in this tree
 * uses, and dropping them would silently change how the name is
 * resolved against coredll at link time.  No declaration is lost --
 * the page ids the removed prints came from (ms905519, ms906086,
 * ms919599, ms919607, ms905514) are recorded alongside their
 * surviving twins below. ---------------------------- */

/* aa452939 DestroyIcon_I (duplicate print of the same function also harvested as
 * ms905519 by the M104 pass; that duplicate removed 2026-09-16, see
 * block comment above): print `BOOL WINAPI DestroyIcon_I(HICON hicon);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
/* ee504624: param-list verified against this page (proto-cite) */
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

/* ms908176 CreateIconIndirect_I (duplicate print of the same function also harvested as
 * ms905514 by the M104 pass; that duplicate removed 2026-09-16, see
 * block comment above): print `HICON WINAPI CreateIconIndirect_I(PICONINFO pii);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT HICON CreateIconIndirect_I(PICONINFO pii) AKARI_CE_NAME(CreateIconIndirect_I);

/* ms929245 GetForegroundWindow_I (duplicate print of the same function also harvested as
 * ms906086 by the M104 pass; that duplicate removed 2026-09-16, see
 * block comment above): print `HWND WINAPI GetForegroundWindow_I(void);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT HWND GetForegroundWindow_I(void) AKARI_CE_NAME(GetForegroundWindow_I);

/* ms939982 SendMessageW_I (duplicate print of the same function also harvested as
 * ms919599 by the M104 pass; that duplicate removed 2026-09-16, see
 * block comment above): print `LRESULT WINAPI SendMessageW_I(HWND hWnd,UINT uMsg,WPARAMwParam,LPARAM lParam);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT LRESULT SendMessageW_I(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(SendMessageW_I);

/* ms940025 SetForegroundWindow_I (duplicate print of the same function also harvested as
 * ms919607 by the M104 pass; that duplicate removed 2026-09-16, see
 * block comment above): print `BOOL WINAPI SetForegroundWindow_I( HWND hwnd);`
 * (Windows CE .NET 4.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT BOOL SetForegroundWindow_I(HWND hwnd) AKARI_CE_NAME(SetForegroundWindow_I);

#endif /* AKARI_GWEBYPASSCOREDLLTHUNK_HPP_ */
