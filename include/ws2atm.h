/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WS2ATM_H
#define WCE_WS2ATM_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagAALUSER_PARAMETERS { ULONG UserDefined; } AALUSER_PARAMETERS, *PAALUSER_PARAMETERS, *LPAALUSER_PARAMETERS;
typedef struct tagATM_TD { ULONG PeakCellRate_CLP0; ULONG PeakCellRate_CLP01; ULONG SustainableCellRate_CLP0; ULONG SustainableCellRate_CLP01; ULONG MaxBurstSize_CLP0; ULONG MaxBurstSize_CLP01; BOOL Tagging; } ATM_TD, *PATM_TD, *LPATM_TD;
typedef struct tagATM_TRAFFIC_DESCRIPTOR_IE { ATM_TD Forward; ATM_TD Backward; BOOL BestEffort; } ATM_TRAFFIC_DESCRIPTOR_IE, *PATM_TRAFFIC_DESCRIPTOR_IE, *LPATM_TRAFFIC_DESCRIPTOR_IE;
typedef struct tagATM_CONNECTION_ID { DWORD DeviceNumber; DWORD VPI; DWORD VCI; } ATM_CONNECTION_ID, *PATM_CONNECTION_ID, *LPATM_CONNECTION_ID;


#ifdef __cplusplus
}
#endif
#endif

