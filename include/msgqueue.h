/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSGQUEUE_H
#define WCE_MSGQUEUE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HANDLE WINAPI CreateMsgQueue(LPCWSTR lpName, LPMSGQUEUEOPTIONS lpOptions) WCE_LINK(CreateMsgQueue);
WCE_IMPORT HANDLE WINAPI OpenMsgQueue(HANDLE hSrcProc, HANDLE hMsgQ, LPMSGQUEUEOPTIONS lpOptions) WCE_LINK(OpenMsgQueue);
WCE_IMPORT BOOL WINAPI ReadMsgQueue(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbBufferSize, LPDWORD lpNumberOfBytesRead, DWORD dwTimeout, DWORD *pdwFlags) WCE_LINK(ReadMsgQueue);
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI ReadMsgQueueEx(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbBufferSize, LPDWORD lpNumberOfBytesRead, DWORD dwTimeout, DWORD *pdwFlags, PHANDLE phTok) WCE_LINK(ReadMsgQueueEx);
#endif
WCE_IMPORT BOOL WINAPI WriteMsgQueue(HANDLE hMsgQ, LPVOID lpBuffer, DWORD cbDataSize, DWORD dwTimeout, DWORD dwFlags) WCE_LINK(WriteMsgQueue);
WCE_IMPORT BOOL WINAPI GetMsgQueueInfo(HANDLE hMsgQ, LPMSGQUEUEINFO lpInfo) WCE_LINK(GetMsgQueueInfo);
WCE_IMPORT BOOL WINAPI CloseMsgQueue(HANDLE hMsgQ) WCE_LINK(CloseMsgQueue);

#ifdef __cplusplus
}
#endif
#endif

