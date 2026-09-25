/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINSCARD_H
#define WCE_WINSCARD_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSCARD_READERSTATEA { LPCSTR szReader; LPVOID pvUserData; DWORD dwCurrentState; DWORD dwEventState; DWORD cbAtr; BYTE rgbAtr[36]; } SCARD_READERSTATEA, *PSCARD_READERSTATEA, *LPSCARD_READERSTATEA;
typedef struct tagSCARD_READERSTATEW { LPCWSTR szReader; LPVOID pvUserData; DWORD dwCurrentState; DWORD dwEventState; DWORD cbAtr; BYTE rgbAtr[36]; } SCARD_READERSTATEW, *PSCARD_READERSTATEW, *LPSCARD_READERSTATEW;
typedef struct tagSCARD_ATRMASK { DWORD cbAtr; BYTE rgbAtr[36]; BYTE rgbMask[36]; } SCARD_ATRMASK, *PSCARD_ATRMASK, *LPSCARD_ATRMASK;

WCE_IMPORT LONG WINAPI SCardEstablishContext(IN DWORD dwScope, IN LPCVOID pvReserved1, IN LPCVOID pvReserved2, OUT LPSCARDCONTEXT phContext) WCE_LINK(SCardEstablishContext);
WCE_IMPORT LONG WINAPI GetOpenCardNameA(LPOPENCARDNAMEA) WCE_LINK(GetOpenCardNameA);
WCE_IMPORT LONG WINAPI GetOpenCardNameW(LPOPENCARDNAMEW) WCE_LINK(GetOpenCardNameW);
WCE_IMPORT LONG WINAPI SCardDlgExtendedError(void) WCE_LINK(SCardDlgExtendedError);

#define GetOpenCardName GetOpenCardNameW
#ifdef __cplusplus
}
#endif
#endif

