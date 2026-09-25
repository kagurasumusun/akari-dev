/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SIMMGR_H
#define WCE_SIMMGR_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSIMLOCKINGPWDLENGTH { DWORD dwFacility; DWORD dwPasswordLength; } SIMLOCKINGPWDLENGTH, *PSIMLOCKINGPWDLENGTH, *LPSIMLOCKINGPWDLENGTH;
typedef struct tagSIMRECORDINFO { DWORD cbSize; DWORD dwParams; DWORD dwRecordType; DWORD dwItemCount; DWORD dwSize; } SIMRECORDINFO, *PSIMRECORDINFO, *LPSIMRECORDINFO;
typedef struct tagSIMPBECHANGE { DWORD dwEntry; DWORD dwStorage; } SIMPBECHANGE, *PSIMPBECHANGE, *LPSIMPBECHANGE;
typedef struct tagSIMMESSAGECHANGE { DWORD dwEntry; DWORD dwStorage; } SIMMESSAGECHANGE, *PSIMMESSAGECHANGE, *LPSIMMESSAGECHANGE;


#ifdef __cplusplus
}
#endif
#endif

