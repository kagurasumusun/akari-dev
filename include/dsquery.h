/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DSQUERY_H
#define WCE_DSQUERY_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDSQUERYINITPARAMS { DWORD cbStruct; DWORD dwFlags; LPWSTR pDefaultScope; LPWSTR pDefaultSaveLocation; LPWSTR pUserName; LPWSTR pPassword; LPWSTR pServer; } DSQUERYINITPARAMS, *PDSQUERYINITPARAMS, *LPDSQUERYINITPARAMS;
typedef struct tagDSCOLUMN { DWORD dwFlags; INT fmt; INT cx; INT idsName; LONG offsetProperty; DWORD dwReserved; } DSCOLUMN, *PDSCOLUMN, *LPDSCOLUMN;
typedef struct tagDSQUERYPARAMS { DWORD cbStruct; DWORD dwFlags; HINSTANCE hInstance; LONG offsetQuery; LONG iColumns; DWORD dwReserved; DSCOLUMN aColumns[1]; } DSQUERYPARAMS, *PDSQUERYPARAMS, *LPDSQUERYPARAMS;
typedef struct tagDSQUERYCLASSLIST { DWORD cbStruct; LONG cClasses; DWORD offsetClass[1]; } DSQUERYCLASSLIST, *PDSQUERYCLASSLIST, *LPDSQUERYCLASSLIST;


#ifdef __cplusplus
}
#endif
#endif

