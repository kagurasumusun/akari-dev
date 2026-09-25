/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_NMPIPE_H
#define WCE_NMPIPE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT BOOL WINAPI CreatePipe(OUT PHANDLE phReadPipe, OUT PHANDLE phWritePipe, IN LPSECURITY_ATTRIBUTES lpPipeAttributes, IN DWORD nSize) WCE_LINK(CreatePipe);
WCE_IMPORT BOOL WINAPI ConnectNamedPipe(IN HANDLE hNamedPipe, IN LPOVERLAPPED lpOverlapped) WCE_LINK(ConnectNamedPipe);
WCE_IMPORT BOOL WINAPI DisconnectNamedPipe(IN HANDLE hNamedPipe) WCE_LINK(DisconnectNamedPipe);
WCE_IMPORT BOOL WINAPI SetNamedPipeHandleState(IN HANDLE hNamedPipe, IN LPDWORD lpMode, IN LPDWORD lpMaxCollectionCount, IN LPDWORD lpCollectDataTimeout) WCE_LINK(SetNamedPipeHandleState);
WCE_IMPORT BOOL WINAPI GetNamedPipeInfo(IN HANDLE hNamedPipe, IN LPDWORD lpFlags, OUT LPDWORD lpOutBufferSize, OUT LPDWORD lpInBufferSize, OUT LPDWORD lpMaxInstances) WCE_LINK(GetNamedPipeInfo);
WCE_IMPORT BOOL WINAPI PeekNamedPipe(IN HANDLE hNamedPipe, OUT LPVOID lpBuffer, IN DWORD nBufferSize, OUT LPDWORD lpBytesRead, OUT LPDWORD lpTotalBytesAvail, OUT LPDWORD lpBytesLeftThisMessage) WCE_LINK(PeekNamedPipe);
WCE_IMPORT BOOL WINAPI TransactNamedPipe(IN HANDLE hNamedPipe, IN LPVOID lpInBuffer, IN DWORD nInBufferSize, OUT LPVOID lpOutBuffer, IN DWORD nOutBufferSize, OUT LPDWORD lpBytesRead, IN LPOVERLAPPED lpOverlapped) WCE_LINK(TransactNamedPipe);
WCE_IMPORT HANDLE WINAPI CreateNamedPipeW(IN LPCWSTR lpName, IN DWORD dwOpenMode, IN DWORD dwPipeMode, IN DWORD nMaxInstances, IN DWORD nOutBufferSize, IN DWORD nInBufferSize, IN DWORD nDefaultTimeOut, IN LPSECURITY_ATTRIBUTES lpSecurityAttributes) WCE_LINK(CreateNamedPipeW);
WCE_IMPORT BOOL WINAPI GetNamedPipeHandleStateW(IN HANDLE hNamedPipe, OUT LPDWORD lpState, OUT LPDWORD lpCurInstances, OUT LPDWORD lpMaxCollectionCount, OUT LPDWORD lpCollectDataTimeout, OUT LPWSTR lpUserName, IN DWORD nMaxUserNameSize) WCE_LINK(GetNamedPipeHandleStateW);
WCE_IMPORT BOOL WINAPI CallNamedPipeW(IN LPCWSTR lpPipeName, IN LPVOID lpInBuffer, IN DWORD nInBufferSize, OUT LPVOID lpOutBuffer, IN DWORD nOutBufferSize, OUT LPDWORD lpBytesRead, IN DWORD nTimeOut) WCE_LINK(CallNamedPipeW);
WCE_IMPORT BOOL WINAPI WaitNamedPipeW(IN LPCWSTR lpNamedPipeName, IN DWORD nTimeOut) WCE_LINK(WaitNamedPipeW);
WCE_IMPORT BOOL WINAPI ReadNamedPipe(IN HANDLE hNamedPipe, IN LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, OUT LPOVERLAPPED lpOverlapped) WCE_LINK(ReadNamedPipe);
WCE_IMPORT BOOL WINAPI WriteNamedPipe(IN HANDLE hNamedPipe, IN LPCVOID lpBuffer, IN DWORD nNumberOfBytesToWrite, OUT LPDWORD lpNumberOfBytesWritten, OUT LPOVERLAPPED lpOverlapped) WCE_LINK(WriteNamedPipe);
WCE_IMPORT BOOL WINAPI CloseNamedPipe(IN HANDLE hPipe) WCE_LINK(CloseNamedPipe);
WCE_IMPORT BOOL WINAPI QuerySessionKeyOfBinding(IN LPWSTR lpPipeName, OUT LPVOID lpSessionKey, IN DWORD nSessionKeySize) WCE_LINK(QuerySessionKeyOfBinding);

#define CreateNamedPipe CreateNamedPipeW
#define GetNamedPipeHandleState GetNamedPipeHandleStateW
#define CallNamedPipe CallNamedPipeW
#define WaitNamedPipe WaitNamedPipeW
#ifdef __cplusplus
}
#endif
#endif

