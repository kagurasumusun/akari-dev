/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RASEAPIF_H
#define WCE_RASEAPIF_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPPP_EAP_PACKET { BYTE Code; BYTE Id; BYTE Length[2]; BYTE Data[1]; } PPP_EAP_PACKET, *PPPP_EAP_PACKET, *LPPPP_EAP_PACKET;

WCE_IMPORT DWORD WINAPI RasEapGetInfo(IN DWORD dwEapTypeId, OUT PPP_EAP_INFO* pEapInfo) WCE_LINK(RasEapGetInfo);
WCE_IMPORT DWORD WINAPI RasEapFreeMemory(IN BYTE* pMemory) WCE_LINK(RasEapFreeMemory);
WCE_IMPORT DWORD WINAPI RasEapInvokeInteractiveUI(IN DWORD dwEapTypeId, IN HWND hwndParent, IN BYTE* pUIContextData, IN DWORD dwSizeOfUIContextData, OUT BYTE** ppDataFromInteractiveUI, OUT DWORD* pdwSizeOfDataFromInteractiveUI) WCE_LINK(RasEapInvokeInteractiveUI);
WCE_IMPORT DWORD WINAPI RasEapInvokeConfigUI(IN DWORD dwEapTypeId, IN HWND hwndParent, IN DWORD dwFlags, IN BYTE* pConnectionDataIn, IN DWORD dwSizeOfConnectionDataIn, OUT BYTE** ppConnectionDataOut, OUT DWORD* pdwSizeOfConnectionDataOut) WCE_LINK(RasEapInvokeConfigUI);
WCE_IMPORT DWORD WINAPI RasEapGetIdentity(IN DWORD dwEapTypeId, IN HWND hwndParent, IN DWORD dwFlags, IN const WCHAR* pwszPhonebook, IN const WCHAR* pwszEntry, IN BYTE* pConnectionDataIn, IN DWORD dwSizeOfConnectionDataIn, IN BYTE* pUserDataIn, IN DWORD dwSizeOfUserDataIn, OUT BYTE** ppUserDataOut, OUT DWORD* pdwSizeOfUserDataOut, OUT WCHAR** ppwszIdentity) WCE_LINK(RasEapGetIdentity);

#ifdef __cplusplus
}
#endif
#endif

