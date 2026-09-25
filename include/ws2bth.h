/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WS2BTH_H
#define WCE_WS2BTH_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagBTH_LOCAL_VERSION { unsigned char hci_version; unsigned short hci_revision; unsigned char lmp_version; unsigned short lmp_subversion; unsigned short manufacturer; unsigned char lmp_features[8]; } BTH_LOCAL_VERSION, *PBTH_LOCAL_VERSION, *LPBTH_LOCAL_VERSION;
typedef struct tagBTH_REMOTE_VERSION { unsigned char lmp_version; unsigned short lmp_subversion; unsigned short manufacturer; unsigned char lmp_features[8]; } BTH_REMOTE_VERSION, *PBTH_REMOTE_VERSION, *LPBTH_REMOTE_VERSION;
typedef struct tagBTH_HOLD_MODE { unsigned short hold_mode_max; unsigned short hold_mode_min; unsigned short interval; } BTH_HOLD_MODE, *PBTH_HOLD_MODE, *LPBTH_HOLD_MODE;
typedef struct tagBTH_SNIFF_MODE { unsigned short sniff_mode_max; unsigned short sniff_mode_min; unsigned short sniff_attempt; unsigned short sniff_timeout; unsigned short interval; } BTH_SNIFF_MODE, *PBTH_SNIFF_MODE, *LPBTH_SNIFF_MODE;
typedef struct tagBTH_PARK_MODE { unsigned short beacon_max; unsigned short beacon_min; unsigned short interval; } BTH_PARK_MODE, *PBTH_PARK_MODE, *LPBTH_PARK_MODE;


#ifdef __cplusplus
}
#endif
#endif

