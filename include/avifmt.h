/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_AVIFMT_H
#define WCE_AVIFMT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagMainAVIHeader { DWORD dwMicroSecPerFrame; DWORD dwMaxBytesPerSec; DWORD dwPaddingGranularity; DWORD dwFlags; DWORD dwTotalFrames; DWORD dwInitialFrames; DWORD dwStreams; DWORD dwSuggestedBufferSize; DWORD dwWidth; DWORD dwHeight; DWORD dwReserved[4]; } MainAVIHeader, *PMainAVIHeader, *LPMainAVIHeader;
typedef struct tagAVIINDEXENTRY { DWORD ckid; DWORD dwFlags; DWORD dwChunkOffset; DWORD dwChunkLength; } AVIINDEXENTRY, *PAVIINDEXENTRY, *LPAVIINDEXENTRY;
typedef struct tagAVIPALCHANGE { BYTE bFirstEntry; BYTE bNumEntries; WORD wFlags; PALETTEENTRY peNew[]; } AVIPALCHANGE, *PAVIPALCHANGE, *LPAVIPALCHANGE;


#ifdef __cplusplus
}
#endif
#endif

