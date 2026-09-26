/* User notifications. Original text. Exported by coredll.dll.
 *
 * The surface is the same on Windows CE .NET 4.2, CE 5.0 and CE 6.0. The two
 * structures below are what the run time actually reads; the older
 * CeSetUserNotification / CeRunAppAtTime / CeRunAppAtEvent calls are still
 * exported for compatibility but only cover the time based trigger.
 */
#ifndef AKARI_WCE_NOTIFY_H
#define AKARI_WCE_NOTIFY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"
#include "tchar.h"

/* CeRunAppAtEvent trigger events. */
#define NOTIFICATION_EVENT_NONE            0
#define NOTIFICATION_EVENT_TIME_CHANGE     1
#define NOTIFICATION_EVENT_SYNC_END        2
#define NOTIFICATION_EVENT_ON_ACPOWER      3
#define NOTIFICATION_EVENT_OFF_ACPOWER     4
#define NOTIFICATION_EVENT_RESTORE_END     10

/* Command lines the shell runs when one of those events arrives. */
#define APP_RUN_AT_TIME                    TEXT("AppRunAtTime")
#define APP_RUN_AFTER_TIME_CHANGE          TEXT("AppRunAfterTimeChange")
#define APP_RUN_AFTER_SYNC                 TEXT("AppRunAfterSync")
#define APP_RUN_AFTER_WAKEUP               TEXT("AppRunAfterWakeUp")
#define APP_RUN_AFTER_RESTORE              TEXT("AppRunAfterRestore")

/* What a notification does when it fires. */
#define PUN_LED       1
#define PUN_VIBRATE   2
#define PUN_DIALOG    4
#define PUN_SOUND     8
#define PUN_REPEAT    16
#define PUN_PRIVATE   32

/* What kind of trigger a notification uses. */
#define CNT_EVENT        1
#define CNT_TIME         2
#define CNT_PERIOD       3
#define CNT_CLASSICTIME  4

#define CNS_SIGNALLED    1

#define NAMED_EVENT_PREFIX_TEXT \
    TEXT("\\\\.\\Notifications\\NamedEvents\\")
#define NAMED_EVENT_PREFIX_LEN \
    (sizeof(NAMED_EVENT_PREFIX_TEXT) / sizeof(TCHAR) - 1)

#define NOTIFICATION_EVENTNAME_API_SET_READY \
    L"system/events/notify/APIReady"

typedef struct akari_CE_USER_NOTIFICATION {
    DWORD ActionFlags;
    LPTSTR pwszDialogTitle;
    LPTSTR pwszDialogText;
    LPTSTR pwszSound;
    DWORD nMaxSound;
    union {
        DWORD dwReserved;
        void *pExpansion;
    };
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

typedef struct akari_CE_NOTIFICATION_TRIGGER {
    DWORD dwSize;
    DWORD dwType;
    DWORD dwEvent;
    LPTSTR lpszApplication;
    LPTSTR lpszArguments;
    SYSTEMTIME stStartTime;
    SYSTEMTIME stEndTime;
} CE_NOTIFICATION_TRIGGER, *PCE_NOTIFICATION_TRIGGER;

typedef struct akari_CE_NOTIFICATION_INFO_HEADER {
    HANDLE hNotification;
    DWORD dwStatus;
    CE_NOTIFICATION_TRIGGER *pcent;
    CE_USER_NOTIFICATION *pceun;
} CE_NOTIFICATION_INFO_HEADER, *PCE_NOTIFICATION_INFO_HEADER;

NOTIFYAPI BOOL WINAPI CeGetUserNotificationPreferences(HWND hWndParent,
    PCE_USER_NOTIFICATION lpNotification);
NOTIFYAPI HANDLE WINAPI CeSetUserNotificationEx(HANDLE hNotification,
    PCE_NOTIFICATION_TRIGGER pcnt, PCE_USER_NOTIFICATION pceun);
NOTIFYAPI BOOL WINAPI CeClearUserNotification(HANDLE hNotification);
NOTIFYAPI BOOL WINAPI CeGetUserNotification(HANDLE hNotification,
    DWORD cBufferSize, LPDWORD pcBytesNeeded, LPBYTE pBuffer);
NOTIFYAPI BOOL WINAPI CeGetUserNotificationHandles(HANDLE *rghNotifications,
    DWORD cHandles, LPDWORD pcHandlesNeeded);

/* Compatibility forms. They only describe a time based trigger. */
NOTIFYAPI HANDLE WINAPI CeSetUserNotification(HANDLE hNotification,
    LPTSTR pwszAppName, LPSYSTEMTIME lpTime, PCE_USER_NOTIFICATION lpUserNotification);
NOTIFYAPI BOOL WINAPI CeRunAppAtTime(LPTSTR pwszAppName, LPSYSTEMTIME lpTime);
NOTIFYAPI BOOL WINAPI CeRunAppAtEvent(LPTSTR pwszAppName, LONG lWhichEvent);
NOTIFYAPI BOOL WINAPI CeHandleAppNotifications(LPTSTR pwszAppName);

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_NOTIFY_H */
