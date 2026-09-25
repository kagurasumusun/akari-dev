/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SPLAPI_H
#define WCE_SPLAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSPLSUGGEST { WCHAR *pwsz; DWORD nScore; } SPLSUGGEST, *PSPLSUGGEST, *LPSPLSUGGEST;
typedef struct tagSPLBUFFER { const WCHAR *pwszIn; WCHAR *pwszOut; SPLSUGGEST aspl[8]; DWORD iwcIn; DWORD cwcIn; DWORD dwMode; DWORD cwcOut; DWORD cwcUsed; DWORD dwErr; DWORD iwcErr; DWORD cwcErr; DWORD cspl; } SPLBUFFER, *PSPLBUFFER, *LPSPLBUFFER;


#ifdef __cplusplus
}
#endif
#endif

