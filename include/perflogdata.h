/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_PERFLOGDATA_H
#define WCE_PERFLOGDATA_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPERFLOG_PACKET_INFO { DWORD dwEvent; PVOID pPacket; LONGLONG msCurrentTime; LONGLONG msPresentationTime; DWORD msPacketDuration; DWORD dwNBytes; DWORD dwElapsed; } PERFLOG_PACKET_INFO, *PPERFLOG_PACKET_INFO, *LPPERFLOG_PACKET_INFO;
typedef struct tagPERFLOG_OBJECT_INFO { DWORD dwEvent; PVOID pObject; DWORD dwStreamID; DWORD dwObjectID; LONGLONG msCurrentTime; LONGLONG msPresentationTime; DWORD dwNBytes; BOOL bIsKeyFrame; DWORD dwElapsed; } PERFLOG_OBJECT_INFO, *PPERFLOG_OBJECT_INFO, *LPPERFLOG_OBJECT_INFO;


#ifdef __cplusplus
}
#endif
#endif

