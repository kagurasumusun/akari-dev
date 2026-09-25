/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ADDRSTOR_H
#define WCE_ADDRSTOR_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT int WINAPI GetPropertyDataStruct(int fFlag, ULONG uValue, PropertyDataStruct *ppds) WCE_LINK(GetPropertyDataStruct);
WCE_IMPORT void WINAPI CloseAddressBook() WCE_LINK(CloseAddressBook);
WCE_IMPORT void WINAPI RecountCards() WCE_LINK(RecountCards);
WCE_IMPORT int WINAPI GetNumberOfAddressCards() WCE_LINK(GetNumberOfAddressCards);

#ifdef __cplusplus
}
#endif
#endif

