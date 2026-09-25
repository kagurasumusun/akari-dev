/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MQMGMT_H
#define WCE_MQMGMT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI MQMgmtAction(IN LPCWSTR pMachineName, IN LPCWSTR pObjectName, IN LPCWSTR pAction) WCE_LINK(MQMgmtAction);
WCE_IMPORT HRESULT WINAPI MQPurgeQueue(IN HANDLE hQueue) WCE_LINK(MQPurgeQueue);

#ifdef __cplusplus
}
#endif
#endif

