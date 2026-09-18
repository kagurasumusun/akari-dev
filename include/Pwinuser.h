/*
 * Pwinuser.h -- OEM keyboard / foreground-target layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The Keyboard Reference book of the CE 5.0 GWES documentation is
 * the source book; these leaves were deferred from the M26 window-manager
 * harvest because their Header rows name Pwinuser.h and they depend on
 * the OEM keybd types (KEY_STATE_FLAGS, keybd.h, M52).
 *
 * Requirement rows (per page):
 *   GetAsyncShiftFlags (aa453955): Pwinuser.h / Kbdui.lib, CE .NET 4.2+.
 *   GetForegroundInfo (ms929241): Pwinuser.h / "Linked during platform
 *     build", CE .NET 4.2+ -- only available to OEMs; no import library
 *     row, so no def entry (documented).
 *   GetForegroundKeyboardLayoutHandle (ms929242): Pwinuser.h / "Linked
 *     during build", CE .NET 4.2+ -- OEMs only, no def entry.
 *   GetForegroundKeyboardTarget (ms929243): Pwinuser.h / "Linked during
 *     build", CE .NET 4.2+ -- OEMs only, no def entry.
 *   KeybdGetDeviceInfo (aa453246): Pwinuser.h / Coredll.lib, CE 1.0+.
 *   GET_FOREGROUND_INFO (aa453186): Pwinuser.h, CE .NET 4.2+.
 *
 * The iIndex identifiers of KeybdGetDeviceInfo are published as names
 * only (KBDI_VKEY_TO_UNICODE_INFO_ID, KBDI_AUTOREPEAT_INFO_ID,
 * KBDI_AUTOREPEAT_SELECTIONS_INFO_ID, KBDI_KEYBOARD_STATUS_ID, and the
 * status bits KBDI_KEYBOARD_PRESENT / KBDI_KEYBOARD_ENABLED /
 * KBDI_KEYBOARD_ENTER_ESC / KBDI_KEYBOARD_ALPHA_NUM); no official source
 * publishes their values (checked CE 5.0 / WM 6.5), so they are held as
 * gaps in docs/inventory.md rather than defined here.
 */

#ifndef AKARI_PWINUSER_H
#define AKARI_PWINUSER_H

#include "Windows.h"   /* HWND, BOOL, DWORD, HKL */
#include "oak/Keybd.h"     /* KEY_STATE_FLAGS (GetAsyncShiftFlags return) */
#include "oak/Nled.h"  /* NLedGetDeviceInfo/NLedSetDevice: the CE 6.0 pages
                        * (ee482640, ee484693) print "Header: nled.h" while the
                        * CE 4.x pages (ms905318, ms905321) print Pwinuser.h, so
                        * the declarations live in oak/Nled.h -- which already
                        * carried the NLED_*_INFO structures -- and this header,
                        * the one CE 4.x names, reaches them (M134). */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453186 "GET_FOREGROUND_INFO" (Windows CE .NET 4.2 and later;
 * Pwinuser.h).  Information about the current foreground thread, filled
 * by GetForegroundInfo.  "This structure is only available to OEMs."
 * Tag as printed (tagGetForegroundInfo).  The IME members carry the
 * foreground thread's conversion / sentence / open state and composition
 * string length. */
typedef struct tagGetForegroundInfo {
    HWND  hwndActive;           /* current active window of the foreground thread */
    HWND  hwndFocus;            /* current focus window (can be NULL) */
    HWND  hwndMenu;             /* current menu window (can be NULL) */
    HWND  hwndKeyboardDest;     /* current destination window for keystrokes */
    DWORD fdwConversion;        /* IME conversion mode */
    DWORD fdwSentence;          /* IME sentence mode */
    BOOL  fOpen;                /* IME open state */
    DWORD dwCompStrLen;         /* IME composition string length */
    HKL   KeyboardLayoutHandle; /* current keyboard layout handle */
} GET_FOREGROUND_INFO;

/* ms929241 "GetForegroundInfo" (CE .NET 4.2+; Pwinuser.h; Linked during
 * platform build).  Retrieves the GET_FOREGROUND_INFO of the current
 * foreground thread; used by the more specialized functions below (and
 * ImmGetConversionStatusForeground).  OEMs only. */
AKARI_CE_IMPORT BOOL GetForegroundInfo(GET_FOREGROUND_INFO *pgfi) AKARI_CE_NAME(GetForegroundInfo);

/* ms929242 "GetForegroundKeyboardLayoutHandle" (CE .NET 4.2+;
 * Pwinuser.h; Linked during build).  Returns the keyboard layout handle
 * of the current foreground thread (low word = language identifier,
 * high word = device handle of the physical layout).  OEMs only. */
AKARI_CE_IMPORT HKL GetForegroundKeyboardLayoutHandle(void) AKARI_CE_NAME(GetForegroundKeyboardLayoutHandle);

/* ms929243 "GetForegroundKeyboardTarget" (CE .NET 4.2+; Pwinuser.h;
 * Linked during build).  Returns the window currently receiving keyboard
 * input (NULL on failure).  OEMs only. */
AKARI_CE_IMPORT HWND GetForegroundKeyboardTarget(void) AKARI_CE_NAME(GetForegroundKeyboardTarget);

/* aa453955 "GetAsyncShiftFlags" (CE .NET 4.2+; Pwinuser.h; Kbdui.lib ->
 * def/kbdui-doc.def).  Asynchronous state of a virtual key: low-order
 * bits carry the key state, high-order bits the SHIFT state (the
 * KEY_STATE_FLAGS layout, keybd.h).  An invalid virtual-key code returns
 * 0 and sets ERROR_INVALID_PARAMETER -- clear the last error before the
 * call to distinguish that from a genuine 0. */
AKARI_CE_IMPORT KEY_STATE_FLAGS GetAsyncShiftFlags(UINT VKey) AKARI_CE_NAME(GetAsyncShiftFlags);

/* aa453246 "KeybdGetDeviceInfo" (CE 1.0+; Pwinuser.h; Coredll.lib ->
 * def/coredll-doc.def).  Returns information about the keyboard and its
 * driver.  iIndex takes the KBDI_* identifiers (names held): for
 * KBDI_KEYBOARD_STATUS_ID the routine fills lpOutput with a DWORD
 * combining KBDI_KEYBOARD_PRESENT / KBDI_KEYBOARD_ENABLED /
 * KBDI_KEYBOARD_ENTER_ESC / KBDI_KEYBOARD_ALPHA_NUM; any other index is
 * passed to the driver's PFN_KEYBD_DRIVER_GET_INFO. */
AKARI_CE_IMPORT BOOL KeybdGetDeviceInfo(INT iIndex, LPVOID lpOutput) AKARI_CE_NAME(KeybdGetDeviceInfo);

/* ------------------------------------------------------------------
 * Book surface: drivers-nled (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms905318 NLedGetDeviceInfo: print `BOOL WINAPI NLedGetDeviceInfo(UINT nInfoId,void* pOutput);` */
/* (record-only: parameter or return type unpublished) */
/* ms905321 NLedSetDevice: print `BOOL WINAPI NLedSetDevice(UINT nDeviceId,void* pInput);` */
/* (record-only: parameter or return type unpublished) */

/* ------------------------------------------------------------------
 * Book surface: drivers-battery (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms896132 BatteryGetLifeTimeInfo: print `void BatteryGetLifeTimeInfo(LPSYSTEMTIMEpstLastChange,DWORD* pcmsCpuUsage,DWORD* pcmsPreviousCpuUsage );` */
AKARI_CE_IMPORT void BatteryGetLifeTimeInfo(LPSYSTEMTIME pstLastChange, DWORD* pcmsCpuUsage, DWORD* pcmsPreviousCpuUsage)
    AKARI_CE_NAME(BatteryGetLifeTimeInfo);
/* ms896134 BatteryNotifyOfTimeChange: print `void WINAPI BatteryNotifyOfTimeChange( BOOL fForward, FILETIME *pftDelta);` */
AKARI_CE_IMPORT void WINAPI BatteryNotifyOfTimeChange(BOOL fForward, FILETIME* pftDelta)
    AKARI_CE_NAME(BatteryNotifyOfTimeChange);

/* ------------------------------------------------------------------
 * Book surface: drivers-touch (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa448196 TouchCalibrate: print `BOOL WINAPI TouchCalibrate(void);` */
AKARI_CE_IMPORT BOOL WINAPI TouchCalibrate(void)
    AKARI_CE_NAME(TouchCalibrate);

#ifdef __cplusplus
}
#endif


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms902923: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT void GwesPowerOffSystem(void) AKARI_CE_NAME(GwesPowerOffSystem);

/* ms906006: page-printed prototype (Windows CE .NET 4.2 and later.; linked during platform build). */
BOOL WINAPI ImmGetConversionStatusForeground(DWORD* pfdwConversion, DWORD* pfdwSentence);

/* _wcepb_NotifyWinUserSystem: page-printed prototype (Windows CE OS). */
/* ee478253: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT void NotifyWinUserSystem(UINT uEvent) AKARI_CE_NAME(NotifyWinUserSystem);

/* ms919550: page-printed prototype (Windows CE 2.10 and later.). */
AKARI_CE_IMPORT BOOL RegisterTaskBar(HWND hwndTaskbar) AKARI_CE_NAME(RegisterTaskBar);


/* --- absent-surface pass 2026-09-18: touch-gesture surface
 * (def/touchgesture-doc.def; pages print "Link Library:
 * touchgesture.lib", Header: pwinuser.h). -------------------- */

/* ee503892 GESTUREINFO: page print
 * typedef struct tagGESTUREINFO { UINT cbSize; DWORD dwFlags; DWORD dwID;
 * HWND hwndTarget; POINTS ptsLocation; DWORD dwInstanceID;
 * DWORD dwSequenceID; ULONGLONG ullArguments; UINT cbExtraArguments;
 * } GESTUREINFO, *PGESTUREINFO; */
typedef struct tagGESTUREINFO {
    UINT      cbSize;
    DWORD     dwFlags;
    DWORD     dwID;
    HWND      hwndTarget;
    POINTS    ptsLocation;
    DWORD     dwInstanceID;
    DWORD     dwSequenceID;
    ULONGLONG ullArguments;
    UINT      cbExtraArguments;
} GESTUREINFO, *PGESTUREINFO;

/* HGESTUREINFO: no CE page prints the typedef (corpus-wide search
 * 2026-09-18); the gesture pages pass it as an opaque handle, so it
 * ships as the tree's handle convention (cf. HWAVEIN, Mmsystem.h). */
typedef void *HGESTUREINFO;

/* ee504292 CloseGestureInfoHandle: print `BOOL CloseGestureInfoHandle ( HGESTUREINFO hGestureInfo );` (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL CloseGestureInfoHandle(HGESTUREINFO hGestureInfo) AKARI_CE_NAME(CloseGestureInfoHandle);

/* ee504053 DisableGestures: print `BOOL DisableGestures( HWND hwnd, ULONGLONG ullFlags, UINT uScope );` (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL DisableGestures(HWND hwnd, ULONGLONG ullFlags, UINT uScope) AKARI_CE_NAME(DisableGestures);

/* ee499762 EnableGestures: print `BOOL EnableGestures( HWND hwnd, ULONGLONG ullFlags, UINT uScope );` (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL EnableGestures(HWND hwnd, ULONGLONG ullFlags, UINT uScope) AKARI_CE_NAME(EnableGestures);

/* ee505235 GetGestureExtraArguments: print `BOOL GetGestureExtraArguments ( HGESTUREINFO hGestureInfo, UNIT cbExtraArguments, PBYTE pbExtraArguments );`
 * -- the page prints "UNIT" for the evidently intended UINT (page
 * typo, same class as proto-audit's PAGE_TYPO records).
 * (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL GetGestureExtraArguments(HGESTUREINFO hGestureInfo, UINT cbExtraArguments, PBYTE pbExtraArguments) AKARI_CE_NAME(GetGestureExtraArguments);

/* ee503217 GetGestureInfo: print `BOOL GetGestureInfo( HGESTUREINFO hGestureInfo PGESTUREINFO pGestureInfo );`
 * -- the print drops the comma between the parameters (page print
 * artifact; boundary restored).  (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL GetGestureInfo(HGESTUREINFO hGestureInfo, PGESTUREINFO pGestureInfo) AKARI_CE_NAME(GetGestureInfo);

/* ee503597 QueryGestures: print `BOOL QueryGestures ( HWND hwnd, UINT uScope, PULONGLONG pullFlags );` (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL QueryGestures(HWND hwnd, UINT uScope, PULONGLONG pullFlags) AKARI_CE_NAME(QueryGestures);

/* ee505707 RegisterGesture: print `BOOL RegisterGesture ( LPCWSTR pszName, PDWORD_PTR pdwID );` (Link Library: touchgesture.lib) */
AKARI_CE_IMPORT BOOL RegisterGesture(LPCWSTR pszName, PDWORD_PTR pdwID) AKARI_CE_NAME(RegisterGesture);

#endif /* AKARI_PWINUSER_H */
