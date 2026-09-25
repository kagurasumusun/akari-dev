/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINCRUI_H
#define WCE_WINCRUI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCREDUI_BALLOONA { DWORD dwVersion; INT iControl; INT iIcon; PSTR pszTitleText; PSTR pszMessageText; } CREDUI_BALLOONA, *PCREDUI_BALLOONA, *LPCREDUI_BALLOONA;
typedef struct tagCREDUI_BALLOONW { DWORD dwVersion; INT iControl; INT iIcon; PWSTR pszTitleText; PWSTR pszMessageText; } CREDUI_BALLOONW, *PCREDUI_BALLOONW, *LPCREDUI_BALLOONW;

WCE_IMPORT BOOL WINAPI CredUIInitControls() WCE_LINK(CredUIInitControls);
WCE_IMPORT DWORD WINAPI CredUIStoreSSOCredW(PCWSTR pszRealm, PCWSTR pszUsername, PCWSTR pszPassword, BOOL bPersist) WCE_LINK(CredUIStoreSSOCredW);
WCE_IMPORT DWORD WINAPI CredUIStoreSSOCredA(PWSTR pszRealm, PWSTR pszUsername, PWSTR pszPassword, BOOL bPersist) WCE_LINK(CredUIStoreSSOCredA);
WCE_IMPORT DWORD WINAPI CredUIReadSSOCredW(PCWSTR pszRealm, PWSTR* ppszUsername) WCE_LINK(CredUIReadSSOCredW);
WCE_IMPORT DWORD WINAPI CredUIReadSSOCredA(PCSTR pszRealm, PSTR* ppszUsername) WCE_LINK(CredUIReadSSOCredA);

#define CredUIStoreSSOCred CredUIStoreSSOCredW
#define CredUIReadSSOCred CredUIReadSSOCredW
#ifdef __cplusplus
}
#endif
#endif

