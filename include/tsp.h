/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_TSP_H
#define WCE_TSP_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCELLBEARERINFO { DWORD dwSpeed; DWORD dwService; DWORD dwConnectionElement; } CELLBEARERINFO, *PCELLBEARERINFO, *LPCELLBEARERINFO;
typedef struct tagCELLDATACOMPINFO { DWORD dwDirection; BOOL dwRequired; DWORD dwMaxDictEntries; DWORD dwMaxStringLength; } CELLDATACOMPINFO, *PCELLDATACOMPINFO, *LPCELLDATACOMPINFO;
typedef struct tagCELLRADIOLINKINFO { DWORD dwVersion; DWORD dwIws; DWORD dwMws; DWORD dwAckTimer; DWORD dwRetransmitAttempts; DWORD dwResequenceTimer; } CELLRADIOLINKINFO, *PCELLRADIOLINKINFO, *LPCELLRADIOLINKINFO;
typedef struct tagCELLGPRSQOSSETTINGS { DWORD dwPrecedenceClass; DWORD dwDelayClass; DWORD dwReliabilityClass; DWORD dwPeakThruClass; DWORD dwMeanThruClass; } CELLGPRSQOSSETTINGS, *PCELLGPRSQOSSETTINGS, *LPCELLGPRSQOSSETTINGS;


#ifdef __cplusplus
}
#endif
#endif

