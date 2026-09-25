/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_UXTHEME_H
#define WCE_UXTHEME_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagMARGINS { int cxLeftWidth; int cxRightWidth; int cyTopHeight; int cyBottomHeight; } MARGINS, *PMARGINS, *LPMARGINS;
typedef struct tagTHEMEPROPERTYVALUEHDR { HRESULT hrValue; int iType; int cbValue; BYTE pbValue[1]; } THEMEPROPERTYVALUEHDR, *PTHEMEPROPERTYVALUEHDR, *LPTHEMEPROPERTYVALUEHDR;
typedef struct tagDTBGOPTS { DWORD dwSize; DWORD dwFlags; RECT rcClip; } DTBGOPTS, *PDTBGOPTS, *LPDTBGOPTS;


#ifdef __cplusplus
}
#endif
#endif

