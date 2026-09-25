/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_FATUTIL_H
#define WCE_FATUTIL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFORMAT_OPTIONS { DWORD dwClusSize; DWORD dwRootEntries; DWORD dwFatVersion; DWORD dwNumFats; DWORD dwFlags; } FORMAT_OPTIONS, *PFORMAT_OPTIONS, *LPFORMAT_OPTIONS;
typedef struct tagFORMAT_RESULTS { DWORD dwSectorsPerFat; DWORD dwReservedSectors; DWORD dwSectorsPerCluster; DWORD dwRootSectors; DWORD dwTotalSectors; DWORD dwNumFats; DWORD dwFatVersion; } FORMAT_RESULTS, *PFORMAT_RESULTS, *LPFORMAT_RESULTS;
typedef struct tagSCAN_OPTIONS { DWORD dwFlags; DWORD dwFatToUse; } SCAN_OPTIONS, *PSCAN_OPTIONS, *LPSCAN_OPTIONS;
typedef struct tagSCAN_RESULTS { DWORD dwLostClusters; DWORD dwInvalidClusters; DWORD dwLostChains; DWORD dwInvalidDirs; DWORD dwInvalidFiles; DWORD dwTotalErrors; DWORD dwPercentFrag; BOOL fConsistentFats; BOOL fErrorNotFixed; } SCAN_RESULTS, *PSCAN_RESULTS, *LPSCAN_RESULTS;
typedef struct tagDEFRAG_OPTIONS { DWORD dwFatToUse; DWORD dwFlags; } DEFRAG_OPTIONS, *PDEFRAG_OPTIONS, *LPDEFRAG_OPTIONS;
typedef struct tagDEFRAG_RESULTS { SCAN_RESULTS sr; } DEFRAG_RESULTS, *PDEFRAG_RESULTS, *LPDEFRAG_RESULTS;


#ifdef __cplusplus
}
#endif
#endif

