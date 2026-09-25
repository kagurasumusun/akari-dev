/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_FSCICLNT_H
#define WCE_FSCICLNT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCI_STATE { DWORD cbStruct; DWORD cWordList; DWORD cPersistentIndex; DWORD cQueries; DWORD cDocuments; DWORD cFreshTest; DWORD dwMergeProgress; DWORD eState; DWORD cFilteredDocuments; DWORD cTotalDocuments; DWORD cPendingScans; DWORD dwIndexSize; DWORD cUniqueKeys; DWORD cSecQDocuments; DWORD dwPropCacheSize; } CI_STATE, *PCI_STATE, *LPCI_STATE;


#ifdef __cplusplus
}
#endif
#endif

