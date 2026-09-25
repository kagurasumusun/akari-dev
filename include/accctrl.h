/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ACCCTRL_H
#define WCE_ACCCTRL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagACTRL_OVERLAPPED { ULONG Reserved1; ULONG Reserved2; HANDLE hEvent; } ACTRL_OVERLAPPED, *PACTRL_OVERLAPPED, *LPACTRL_OVERLAPPED;
typedef struct tagACTRL_ACCESS_INFOA { ULONG fAccessPermission; LPSTR lpAccessPermissionName; } ACTRL_ACCESS_INFOA, *PACTRL_ACCESS_INFOA, *LPACTRL_ACCESS_INFOA;
typedef struct tagACTRL_ACCESS_INFOW { ULONG fAccessPermission; LPWSTR lpAccessPermissionName; } ACTRL_ACCESS_INFOW, *PACTRL_ACCESS_INFOW, *LPACTRL_ACCESS_INFOW;
typedef struct tagACTRL_CONTROL_INFOA { LPSTR lpControlId; LPSTR lpControlName; } ACTRL_CONTROL_INFOA, *PACTRL_CONTROL_INFOA, *LPACTRL_CONTROL_INFOA;
typedef struct tagACTRL_CONTROL_INFOW { LPWSTR lpControlId; LPWSTR lpControlName; } ACTRL_CONTROL_INFOW, *PACTRL_CONTROL_INFOW, *LPACTRL_CONTROL_INFOW;


#ifdef __cplusplus
}
#endif
#endif

