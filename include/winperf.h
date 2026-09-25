/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINPERF_H
#define WCE_WINPERF_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPERF_INSTANCE_DEFINITION { DWORD ByteLength; DWORD ParentObjectTitleIndex; DWORD ParentObjectInstance; LONG UniqueID; DWORD NameOffset; DWORD NameLength; } PERF_INSTANCE_DEFINITION, *PPERF_INSTANCE_DEFINITION, *LPPERF_INSTANCE_DEFINITION;
typedef struct tagPERF_COUNTER_BLOCK { DWORD ByteLength; } PERF_COUNTER_BLOCK, *PPERF_COUNTER_BLOCK, *LPPERF_COUNTER_BLOCK;


#ifdef __cplusplus
}
#endif
#endif

