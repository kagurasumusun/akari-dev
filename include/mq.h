/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MQ_H
#define WCE_MQ_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI MQDeleteQueue(IN LPCWSTR lpwcsFormatName) WCE_LINK(MQDeleteQueue);
WCE_IMPORT HRESULT WINAPI MQLocateEnd(IN HANDLE hEnum) WCE_LINK(MQLocateEnd);
WCE_IMPORT HRESULT WINAPI MQCloseCursor(IN HANDLE hCursor) WCE_LINK(MQCloseCursor);
WCE_IMPORT HRESULT WINAPI MQCloseQueue(IN HANDLE hQueue) WCE_LINK(MQCloseQueue);
WCE_IMPORT HRESULT WINAPI MQPathNameToFormatName(IN LPCWSTR lpwcsPathName, OUT LPWSTR lpwcsFormatName, IN OUT LPDWORD lpdwFormatNameLength) WCE_LINK(MQPathNameToFormatName);
WCE_IMPORT HRESULT WINAPI MQInstanceToFormatName(IN GUID* pGuid, OUT LPWSTR lpwcsFormatName, IN OUT LPDWORD lpdwFormatNameLength) WCE_LINK(MQInstanceToFormatName);
WCE_IMPORT void WINAPI MQFreeMemory(IN PVOID pvMemory) WCE_LINK(MQFreeMemory);
WCE_IMPORT HRESULT WINAPI MQGetSecurityContext(IN PVOID lpCertBuffer, IN DWORD dwCertBufferLength, OUT HANDLE* hSecurityContext) WCE_LINK(MQGetSecurityContext);
WCE_IMPORT void WINAPI MQFreeSecurityContext(IN HANDLE hSecurityContext) WCE_LINK(MQFreeSecurityContext);

#ifdef __cplusplus
}
#endif
#endif

