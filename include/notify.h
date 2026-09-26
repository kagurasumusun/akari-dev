/* User notifications. Original text. Exported by coredll.dll. */
#ifndef AKARI_WCE_NOTIFY_H
#define AKARI_WCE_NOTIFY_H

#include "winbase.h"

#define CNT_EVENT        1
#define CNT_TIME         2
#define CNT_PERIODIC     3
#define CNT_NAMED_TIMER  4

#define CNF_DIALOG       0x00000001
#define CNF_SOUND        0x00000002
#define CNF_REPEAT       0x00000004
#define CNF_LANDESCAPE   0x00000008
#define CNF_INTELLIMIRROR 0x00000010

typedef struct akari_USER_NOTIFICATION {
    DWORD Type;
    DWORD Event;
    DWORD DialogTemplate;
    LPWSTR pwszSound;
    WORD wRepeatCount;
    DWORD dwReserved;
} USER_NOTIFICATION, *PUSER_NOTIFICATION;

typedef struct akari_USER_NOTIFICATIONEVENT {
    HANDLE hNotification;
    WORD wYear; WORD wMonth; WORD wDay; WORD wHour; WORD wMinute; WORD wSecond;
    DWORD dwCookie;
} USER_NOTIFICATIONEVENT, *PUSER_NOTIFICATIONEVENT;

#define NAMED_EVENT 0x00000001
#define NAMED_TIMER 0x00000002

NOTIFYAPI BOOL WINAPI CeSetUserNotificationEx(PUSER_NOTIFICATION lpNotify,
    PSYSTEMTIME lpTime, HANDLE *phNotification);
NOTIFYAPI BOOL WINAPI CeClearUserNotification(HANDLE hNotification);
NOTIFYAPI BOOL WINAPI CeRunAppAtTime(LPCWSTR pwszAppName, LPSYSTEMTIME lpTime);
NOTIFYAPI BOOL WINAPI CeRunAppAtEvent(LPCWSTR pwszAppName, DWORD dwEvent);
NOTIFYAPI BOOL WINAPI CeGetUserNotification(PUSER_NOTIFICATION lpNotify,
    HANDLE *phNotification);
NOTIFYAPI BOOL WINAPI CeGetUserNotificationPreferences(HWND hWndParent,
    PUSER_NOTIFICATION lpNotify);

/*
 * CeGetUserNotificationEx, CeGetNextUserNotification, CeFindNextNotification and
 * CeHandleAppTimedEvent are not exports on any supported release, so they are
 * not declared here.
 */

#endif /* AKARI_WCE_NOTIFY_H */
