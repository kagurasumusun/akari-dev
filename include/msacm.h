/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSACM_H
#define WCE_MSACM_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagACMSTREAMHEADER { DWORD cbStruct; DWORD fdwStatus; DWORD dwUser; LPBYTE pbSrc; DWORD cbSrcLength; DWORD cbSrcLengthUsed; DWORD dwSrcUser; LPBYTE pbDst; DWORD cbDstLength; DWORD cbDstLengthUsed; DWORD dwDstUser; DWORD dwReservedDriver[10]; } ACMSTREAMHEADER, *PACMSTREAMHEADER, *LPACMSTREAMHEADER;


#ifdef __cplusplus
}
#endif
#endif

