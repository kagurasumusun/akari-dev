/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DMOREG_H
#define WCE_DMOREG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDMO_PARTIAL_MEDIATYPE { GUID type; GUID subtype; } DMO_PARTIAL_MEDIATYPE, *PDMO_PARTIAL_MEDIATYPE, *LPDMO_PARTIAL_MEDIATYPE;

WCE_IMPORT HRESULT WINAPI DMORegister(LPCWSTR szName, REFCLSID clsidDMO, REFGUID guidCategory, DWORD dwFlags, DWORD cInTypes, const DMO_PARTIAL_MEDIATYPE *pInTypes, DWORD cOutTypes, const DMO_PARTIAL_MEDIATYPE *pOutTypes) WCE_LINK(DMORegister);
WCE_IMPORT HRESULT WINAPI DMORegisterFilter(LPCWSTR szName, REFCLSID clsidDMO, REFGUID guidCategory, REFCLSID clsidAutoWrap, DWORD dwFlags, unsigned long ulInTypes, const DMO_PARTIAL_MEDIATYPE *pInTypes, unsigned long ulOutTypes, const DMO_PARTIAL_MEDIATYPE *pOutTypes) WCE_LINK(DMORegisterFilter);
WCE_IMPORT HRESULT WINAPI DMOUnregister(REFCLSID clsidDMO, REFGUID guidCategory) WCE_LINK(DMOUnregister);
WCE_IMPORT HRESULT WINAPI DMOUnregisterFilter(REFCLSID clsidAutoWrap) WCE_LINK(DMOUnregisterFilter);
WCE_IMPORT HRESULT WINAPI DMOGetTypes(REFCLSID clsidDMO, unsigned long ulInputTypesRequested, unsigned long *pulInputTypesSupplied, DMO_PARTIAL_MEDIATYPE *pInputTypes, unsigned long ulOutputTypesRequested, unsigned long *pulOutputTypesSupplied, DMO_PARTIAL_MEDIATYPE *pOutputTypes) WCE_LINK(DMOGetTypes);
WCE_IMPORT HRESULT WINAPI DMOGetName(REFCLSID clsidDMO, WCHAR szName[80]) WCE_LINK(DMOGetName);

#ifdef __cplusplus
}
#endif
#endif

