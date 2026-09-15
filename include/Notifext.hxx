/*
 * Notifext.hxx -- declarations recovered from the official
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

#ifndef AKARI_NOTIFEXT_HXX_
#define AKARI_NOTIFEXT_HXX_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
/* M134: this header had never been compiled -- Makefile's HDRS is an
 * explicit list and Notifext.hxx was missing from it, so `make check`
 * passed over a file that does not build.  The declarations below use
 * CEOID (Windbase.h, which also brings FILETIME through Winbase.h) and
 * CE_USER_NOTIFICATION (Notify.h); nothing includes this header, so
 * neither include can close a cycle. */
#include "Windbase.h"  /* CEOID, FILETIME */
#include "Notify.h"    /* CE_USER_NOTIFICATION */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms905402: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPrivate_ClearUserAlarm(void);

/* ms905403: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPrivate_DeleteNotification(CEOID oid);

/* ms905404: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPrivate_FilterType(unsigned int uiFlag);

/* ms905405: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPrivate_Lock(void);

/* ms905406: page-printed prototype (Windows CE 2.10 and later.). */
int CeNotifyPrivate_Reschedule(CEOID oid, int iDelaySeconds);

/* ms905409: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPrivate_Unlock(void);

/* ms905411: page-printed prototype (Windows CE 2.10 and later.). */
int CeNotifyPublic_FilterEvent(DWORD dwEvent);

/* ms905413: page-printed prototype (Windows CE 2.10 and later.). */
int CeNotifyPublic_Initialize(HINSTANCE hInst, HWND hwndUI);

/* ms905414: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPublic_NewPacket(CEOID oidRecord);

/* ms905417: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPublic_UserAlarmSignalled(void);


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms905407: page-printed prototype (Windows CE 2.10 and later.). */
void CeNotifyPrivate_SetUserAlarm(FILETIME* ftWhen);

/* ms905412: page-printed prototype (Windows CE 2.10 and later.). */
int CeNotifyPublic_FilterUserNotification(CE_USER_NOTIFICATION* pceun);

/* ms905415: page-printed prototype (Windows CE 2.10 and later.). */
int CeNotifyPublic_PresentSettingsBox(HWND hWnd, CE_USER_NOTIFICATION* pceun, TCHAR* lpszSoundBuffer, void* pExpansion);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms919617: page-printed definition (Windows CE 2.10 and later.). */
typedef struct tagSettingsDialogData {
    PCE_USER_NOTIFICATION UserNotification;
    TCHAR* MappedSoundBuffer;
    void* pvExtension;
    HWND hParentWindow;
    HWND hLedWindow;
    HWND hVibrateWindow;
    HWND hDialogWindow;
    HWND hSoundWindow;
    HWND hComboWindow;
    HWND hRepeatWindow;
    HICON hIcon;
    BOOL SaveData;
} SettingsDialogData;


/* ms908098 CeNotifyPublic_UIWndProc: print `LRESULT CALLBACK CeNotifyPublic_UIWndProc(HWNDhWnd,UINTmessage,WPARAMwParam,LPARAMlParam);`
 * (Windows CE 2.10 and later.; Link Library: not stated) */
LRESULT CALLBACK CeNotifyPublic_UIWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/* ms908100 CeNotifyPublic_InitializeUI: print `int CeNotifyPublic_InitializeUI(HINSTANCE hInst,HWNDhwndUI);`
 * (Windows CE 5.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT int CeNotifyPublic_InitializeUI(HINSTANCE hInst, HWND hwndUI) AKARI_CE_NAME(CeNotifyPublic_InitializeUI);

/* ms908101 CeNotifyPublic_Uninitialize: print `void CeNotifyPublic_Uninitialize(void);`
 * (Windows CE 5.0 and later.; Link Library: not stated) */
AKARI_CE_IMPORT void CeNotifyPublic_Uninitialize(void) AKARI_CE_NAME(CeNotifyPublic_Uninitialize);

#endif /* AKARI_NOTIFEXT_HXX_ */
