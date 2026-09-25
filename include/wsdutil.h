/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WSDUTIL_H
#define WCE_WSDUTIL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI WSDSetConfigurationOption(DWORD dwOption, LPVOID pVoid, DWORD cbInBuffer) WCE_LINK(WSDSetConfigurationOption);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI WSDGetConfigurationOption(DWORD dwOption, LPVOID pVoid, DWORD cbOutBuffer) WCE_LINK(WSDGetConfigurationOption);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT void WINAPI WSDFreeLinkedMemory(void *pVoid) WCE_LINK(WSDFreeLinkedMemory);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT void WINAPI WSDAttachLinkedMemory(void* pParent, void* pChild) WCE_LINK(WSDAttachLinkedMemory);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT void WINAPI WSDDetachLinkedMemory(void* pVoid) WCE_LINK(WSDDetachLinkedMemory);
#endif

#ifdef __cplusplus
}
#endif
#endif

