/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_IMM_H
#define WCE_IMM_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCOMPOSITIONFORM { DWORD dwStyle; POINT ptCurrentPos; RECT rcArea; } COMPOSITIONFORM, *PCOMPOSITIONFORM, *LPCOMPOSITIONFORM;
typedef struct tagCANDIDATEFORM { DWORD dwIndex; DWORD dwStyle; POINT ptCurrentPos; RECT rcArea; } CANDIDATEFORM, *PCANDIDATEFORM, *LPCANDIDATEFORM;
typedef struct tagCANDIDATELIST { DWORD dwSize; DWORD dwStyle; DWORD dwCount; DWORD dwSelection; DWORD dwPageStart; DWORD dwPageSize; DWORD dwOffset[1]; } CANDIDATELIST, *PCANDIDATELIST, *LPCANDIDATELIST;
typedef struct tagREGISTERWORDA { LPSTR lpReading; LPSTR lpWord; } REGISTERWORDA, *PREGISTERWORDA, *LPREGISTERWORDA;
typedef struct tagREGISTERWORDW { LPWSTR lpReading; LPWSTR lpWord; } REGISTERWORDW, *PREGISTERWORDW, *LPREGISTERWORDW;
typedef struct tagIMECHARPOSITION { DWORD dwSize; DWORD dwCharPos; POINT pt; UINT cLineHeight; RECT rcDocument; } IMECHARPOSITION, *PIMECHARPOSITION, *LPIMECHARPOSITION;
typedef struct tagCOMPOSITIONSTRING { DWORD dwSize; DWORD dwCompReadAttrLen; DWORD dwCompReadAttrOffset; DWORD dwCompReadClauseLen; DWORD dwCompReadClauseOffset; DWORD dwCompReadStrLen; DWORD dwCompReadStrOffset; DWORD dwCompAttrLen; DWORD dwCompAttrOffset; DWORD dwCompClauseLen; DWORD dwCompClauseOffset; DWORD dwCompStrLen; DWORD dwCompStrOffset; DWORD dwCursorPos; DWORD dwDeltaStart; DWORD dwResultReadClauseLen; DWORD dwResultReadClauseOffset; DWORD dwResultReadStrLen; DWORD dwResultReadStrOffset; DWORD dwResultClauseLen; DWORD dwResultClauseOffset; DWORD dwResultStrLen; DWORD dwResultStrOffset; DWORD dwPrivateSize; DWORD dwPrivateOffset; } COMPOSITIONSTRING, *PCOMPOSITIONSTRING, *LPCOMPOSITIONSTRING;
typedef struct tagGUIDELINE { DWORD dwSize; DWORD dwLevel; DWORD dwIndex; DWORD dwStrLen; DWORD dwStrOffset; DWORD dwPrivateSize; DWORD dwPrivateOffset; } GUIDELINE, *PGUIDELINE, *LPGUIDELINE;
typedef struct tagRECONVERTSTRING { DWORD dwSize; DWORD dwVersion; DWORD dwStrLen; DWORD dwStrOffset; DWORD dwCompStrLen; DWORD dwCompStrOffset; DWORD dwTargetStrLen; DWORD dwTargetStrOffset; } RECONVERTSTRING, *PRECONVERTSTRING, *LPRECONVERTSTRING;
typedef struct tagCANDIDATEINFO { DWORD dwSize; DWORD dwCount; DWORD dwOffset[32]; DWORD dwPrivateSize; DWORD dwPrivateOffset; } CANDIDATEINFO, *PCANDIDATEINFO, *LPCANDIDATEINFO;
typedef struct tagIMEINFO { DWORD dwPrivateDataSize; DWORD fdwProperty; DWORD fdwConversionCaps; DWORD fdwSentenceCaps; DWORD fdwUICaps; DWORD fdwSCSCaps; DWORD fdwSelectCaps; } IMEINFO, *PIMEINFO, *LPIMEINFO;
typedef struct tagSOFTKBDDATA { UINT uCount; WORD wCode[1][256]; } SOFTKBDDATA, *PSOFTKBDDATA, *LPSOFTKBDDATA;

WCE_IMPORT HWND WINAPI ImmGetDefaultIMEWnd(HWND) WCE_LINK(ImmGetDefaultIMEWnd);
WCE_IMPORT BOOL WINAPI ImmSimulateHotKey(HWND, DWORD) WCE_LINK(ImmSimulateHotKey);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI ImmSendNotification(void) WCE_LINK(ImmSendNotification);
#endif
WCE_IMPORT BOOL WINAPI ImmIsUIMessageW(HWND, UINT, WPARAM, LPARAM) WCE_LINK(ImmIsUIMessageW);
WCE_IMPORT UINT WINAPI ImmGetVirtualKey(HWND) WCE_LINK(ImmGetVirtualKey);
WCE_IMPORT BOOL WINAPI ImmDisableIME(DWORD) WCE_LINK(ImmDisableIME);
WCE_IMPORT BOOL WINAPI ImmGetHotKey(DWORD, LPUINT lpuModifiers, LPUINT lpuVKey, LPHKL) WCE_LINK(ImmGetHotKey);
WCE_IMPORT BOOL WINAPI ImmDestroySoftKeyboard(HWND) WCE_LINK(ImmDestroySoftKeyboard);
WCE_IMPORT BOOL WINAPI ImmShowSoftKeyboard(HWND, int) WCE_LINK(ImmShowSoftKeyboard);
WCE_IMPORT BOOL WINAPI ImeInquire(LPIMEINFO, LPWSTR lpszUIClass, DWORD dwSystemInfoFlags) WCE_LINK(ImeInquire);
WCE_IMPORT BOOL WINAPI ImeDestroy(UINT) WCE_LINK(ImeDestroy);
WCE_IMPORT BOOL WINAPI ImeRegisterWord(LPCWSTR, DWORD, LPCWSTR) WCE_LINK(ImeRegisterWord);
WCE_IMPORT BOOL WINAPI ImeUnregisterWord(LPCWSTR, DWORD, LPCWSTR) WCE_LINK(ImeUnregisterWord);
WCE_IMPORT UINT WINAPI ImeGetRegisterWordStyle(UINT nItem, LPSTYLEBUF) WCE_LINK(ImeGetRegisterWordStyle);
WCE_IMPORT BOOL WINAPI ImmSIPanelState(UINT dwCmd, LPVOID pValue) WCE_LINK(ImmSIPanelState);

#define ImmIsUIMessage ImmIsUIMessageW
#ifdef __cplusplus
}
#endif
#endif

