/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_OLECTL_H
#define WCE_OLECTL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFONTDESC { UINT cbSizeofstruct; LPOLESTR lpstrName; CY cySize; SHORT sWeight; SHORT sCharset; BOOL fItalic; BOOL fUnderline; BOOL fStrikethrough; } FONTDESC, *PFONTDESC, *LPFONTDESC;

WCE_IMPORT HRESULT WINAPI DllRegisterServer(void) WCE_LINK(DllRegisterServer);
WCE_IMPORT HRESULT WINAPI DllUnregisterServer(void) WCE_LINK(DllUnregisterServer);

#ifdef __cplusplus
}
#endif
#endif

