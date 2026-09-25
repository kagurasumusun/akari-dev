/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_VRSSCAN_H
#define WCE_VRSSCAN_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagVIRUSINFO { DWORD cbSize; WCHAR wszVendorDescription[ 128 ]; HICON hVendorIcon; WCHAR wszVendorContactInfo[ 2048 ]; WCHAR wszVirusName[ 128 ]; WCHAR wszVirusDescription[ 128 ]; } VIRUSINFO, *PVIRUSINFO, *LPVIRUSINFO;


#ifdef __cplusplus
}
#endif
#endif

