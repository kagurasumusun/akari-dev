/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SHTYPES_H
#define WCE_SHTYPES_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSHITEMID { USHORT cb; BYTE abID[ 1 ]; } SHITEMID, *PSHITEMID, *LPSHITEMID;
typedef struct tagITEMIDLIST { SHITEMID mkid; } ITEMIDLIST, *PITEMIDLIST, *LPITEMIDLIST;


#ifdef __cplusplus
}
#endif
#endif

