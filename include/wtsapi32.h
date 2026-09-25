/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WTSAPI32_H
#define WCE_WTSAPI32_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWTSSESSION_NOTIFICATION { DWORD cbSize; DWORD dwSessionId; } WTSSESSION_NOTIFICATION, *PWTSSESSION_NOTIFICATION, *LPWTSSESSION_NOTIFICATION;
typedef struct tagWTS_SERVER_INFOW { LPWSTR pServerName; } WTS_SERVER_INFOW, *PWTS_SERVER_INFOW, *LPWTS_SERVER_INFOW;
typedef struct tagWTS_SERVER_INFOA { LPSTR pServerName; } WTS_SERVER_INFOA, *PWTS_SERVER_INFOA, *LPWTS_SERVER_INFOA;
typedef struct tagWTS_PROCESS_INFOW { DWORD SessionId; DWORD ProcessId; LPWSTR pProcessName; PSID pUserSid; } WTS_PROCESS_INFOW, *PWTS_PROCESS_INFOW, *LPWTS_PROCESS_INFOW;
typedef struct tagWTS_PROCESS_INFOA { DWORD SessionId; DWORD ProcessId; LPSTR pProcessName; PSID pUserSid; } WTS_PROCESS_INFOA, *PWTS_PROCESS_INFOA, *LPWTS_PROCESS_INFOA;
typedef struct tagWTS_CLIENT_ADDRESS { DWORD AddressFamily; BYTE Address[20]; } WTS_CLIENT_ADDRESS, *PWTS_CLIENT_ADDRESS, *LPWTS_CLIENT_ADDRESS;
typedef struct tagWTS_CLIENT_DISPLAY { DWORD HorizontalResolution; DWORD VerticalResolution; DWORD ColorDepth; } WTS_CLIENT_DISPLAY, *PWTS_CLIENT_DISPLAY, *LPWTS_CLIENT_DISPLAY;

WCE_IMPORT BOOL WINAPI WTSEnumerateServersW(IN LPWSTR pDomainName, IN DWORD Reserved, IN DWORD Version, OUT PWTS_SERVER_INFOW * ppServerInfo, OUT DWORD * pCount) WCE_LINK(WTSEnumerateServersW);
WCE_IMPORT BOOL WINAPI WTSEnumerateServersA(IN LPSTR pDomainName, IN DWORD Reserved, IN DWORD Version, OUT PWTS_SERVER_INFOA * ppServerInfo, OUT DWORD * pCount) WCE_LINK(WTSEnumerateServersA);
WCE_IMPORT HANDLE WINAPI WTSOpenServerW(IN LPWSTR pServerName) WCE_LINK(WTSOpenServerW);
WCE_IMPORT HANDLE WINAPI WTSOpenServerA(IN LPSTR pServerName) WCE_LINK(WTSOpenServerA);
WCE_IMPORT VOID WINAPI WTSCloseServer(IN HANDLE hServer) WCE_LINK(WTSCloseServer);
WCE_IMPORT BOOL WINAPI WTSEnumerateSessionsW(IN HANDLE hServer, IN DWORD Reserved, IN DWORD Version, OUT PWTS_SESSION_INFOW * ppSessionInfo, OUT DWORD * pCount) WCE_LINK(WTSEnumerateSessionsW);
WCE_IMPORT BOOL WINAPI WTSEnumerateSessionsA(IN HANDLE hServer, IN DWORD Reserved, IN DWORD Version, OUT PWTS_SESSION_INFOA * ppSessionInfo, OUT DWORD * pCount) WCE_LINK(WTSEnumerateSessionsA);
WCE_IMPORT BOOL WINAPI WTSEnumerateProcessesW(IN HANDLE hServer, IN DWORD Reserved, IN DWORD Version, OUT PWTS_PROCESS_INFOW * ppProcessInfo, OUT DWORD * pCount) WCE_LINK(WTSEnumerateProcessesW);
WCE_IMPORT BOOL WINAPI WTSEnumerateProcessesA(IN HANDLE hServer, IN DWORD Reserved, IN DWORD Version, OUT PWTS_PROCESS_INFOA * ppProcessInfo, OUT DWORD * pCount) WCE_LINK(WTSEnumerateProcessesA);
WCE_IMPORT BOOL WINAPI WTSTerminateProcess(IN HANDLE hServer, IN DWORD ProcessId, IN DWORD ExitCode) WCE_LINK(WTSTerminateProcess);
WCE_IMPORT BOOL WINAPI WTSSendMessageW(IN HANDLE hServer, IN DWORD SessionId, IN LPWSTR pTitle, IN DWORD TitleLength, IN LPWSTR pMessage, IN DWORD MessageLength, IN DWORD Style, IN DWORD Timeout, OUT DWORD * pResponse, IN BOOL bWait) WCE_LINK(WTSSendMessageW);
WCE_IMPORT BOOL WINAPI WTSSendMessageA(IN HANDLE hServer, IN DWORD SessionId, IN LPSTR pTitle, IN DWORD TitleLength, IN LPSTR pMessage, IN DWORD MessageLength, IN DWORD Style, IN DWORD Timeout, OUT DWORD * pResponse, IN BOOL bWait) WCE_LINK(WTSSendMessageA);
WCE_IMPORT BOOL WINAPI WTSDisconnectSession(IN HANDLE hServer, IN DWORD SessionId, IN BOOL bWait) WCE_LINK(WTSDisconnectSession);
WCE_IMPORT BOOL WINAPI WTSLogoffSession(IN HANDLE hServer, IN DWORD SessionId, IN BOOL bWait) WCE_LINK(WTSLogoffSession);
WCE_IMPORT BOOL WINAPI WTSShutdownSystem(IN HANDLE hServer, IN DWORD ShutdownFlag) WCE_LINK(WTSShutdownSystem);
WCE_IMPORT BOOL WINAPI WTSWaitSystemEvent(IN HANDLE hServer, IN DWORD EventMask, OUT DWORD * pEventFlags) WCE_LINK(WTSWaitSystemEvent);
WCE_IMPORT HANDLE WINAPI WTSVirtualChannelOpen(IN HANDLE hServer, IN DWORD SessionId, IN LPSTR pVirtualName) WCE_LINK(WTSVirtualChannelOpen);
WCE_IMPORT BOOL WINAPI WTSVirtualChannelClose(IN HANDLE hChannelHandle) WCE_LINK(WTSVirtualChannelClose);
WCE_IMPORT BOOL WINAPI WTSVirtualChannelRead(IN HANDLE hChannelHandle, IN ULONG TimeOut, OUT PCHAR Buffer, IN ULONG BufferSize, OUT PULONG pBytesRead) WCE_LINK(WTSVirtualChannelRead);
WCE_IMPORT BOOL WINAPI WTSVirtualChannelWrite(IN HANDLE hChannelHandle, IN PCHAR Buffer, IN ULONG Length, OUT PULONG pBytesWritten) WCE_LINK(WTSVirtualChannelWrite);
WCE_IMPORT BOOL WINAPI WTSVirtualChannelPurgeInput(IN HANDLE hChannelHandle) WCE_LINK(WTSVirtualChannelPurgeInput);
WCE_IMPORT BOOL WINAPI WTSVirtualChannelPurgeOutput(IN HANDLE hChannelHandle) WCE_LINK(WTSVirtualChannelPurgeOutput);
WCE_IMPORT VOID WINAPI WTSFreeMemory(IN PVOID pMemory) WCE_LINK(WTSFreeMemory);
WCE_IMPORT BOOL WINAPI WTSRegisterSessionNotification(HWND hWnd, DWORD dwFlags) WCE_LINK(WTSRegisterSessionNotification);
WCE_IMPORT BOOL WINAPI WTSUnRegisterSessionNotification(HWND hWnd) WCE_LINK(WTSUnRegisterSessionNotification);
WCE_IMPORT BOOL WINAPI WTSQueryUserToken(ULONG SessionId, PHANDLE phToken) WCE_LINK(WTSQueryUserToken);

#define WTSEnumerateServers WTSEnumerateServersW
#define WTSOpenServer WTSOpenServerW
#define WTSEnumerateSessions WTSEnumerateSessionsW
#define WTSEnumerateProcesses WTSEnumerateProcessesW
#define WTSSendMessage WTSSendMessageW
#ifdef __cplusplus
}
#endif
#endif

