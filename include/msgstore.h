/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSGSTORE_H
#define WCE_MSGSTORE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagMailAtt { UINT uiAttachmentNumber; DWORD dwFlags; ULONG ulCharacterPosition; ULONG ulSize; LPWSTR szOriginalName; LPWSTR szLocalName; } MailAtt, *PMailAtt, *LPMailAtt;

WCE_IMPORT int WINAPI MailError(HANDLE hMail) WCE_LINK(MailError);
WCE_IMPORT int WINAPI MailErrorMsg(HANDLE hMail, LPWSTR szBuf, int iBufLen, int* piSrcLine) WCE_LINK(MailErrorMsg);
WCE_IMPORT BOOL WINAPI MailOpen(HANDLE* phMail, BOOL fAllowCreate) WCE_LINK(MailOpen);
WCE_IMPORT BOOL WINAPI MailOpenNotify(HANDLE* phMail, BOOL fAllowCreate, HWND hwndNotify) WCE_LINK(MailOpenNotify);
WCE_IMPORT BOOL WINAPI MailPutFolder(HANDLE hMail, BYTE bId, LPWSTR szName) WCE_LINK(MailPutFolder);
WCE_IMPORT BOOL WINAPI MailGetFolderName(HANDLE hMail, int* piId, int* piLen, LPWSTR szName) WCE_LINK(MailGetFolderName);
WCE_IMPORT BOOL WINAPI MailGetFolderId(HANDLE hMail, BYTE* pbId, LPWSTR szName) WCE_LINK(MailGetFolderId);
WCE_IMPORT BOOL WINAPI MailClose(HANDLE hMail) WCE_LINK(MailClose);
WCE_IMPORT BOOL WINAPI MailGetSort(HANDLE hMail, PMAILSORTINFO pInfo) WCE_LINK(MailGetSort);
WCE_IMPORT LONG WINAPI MailRegOpenKeyExW(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) WCE_LINK(MailRegOpenKeyExW);
WCE_IMPORT LONG WINAPI MailRegEnumKeyExW(HKEY hKey, DWORD dwIndex, LPWSTR lpName, LPDWORD lpcbName, LPDWORD lpReserved, LPWSTR lpClass, LPDWORD lpcbClass, PFILETIME lpftLastWriteTime) WCE_LINK(MailRegEnumKeyExW);
WCE_IMPORT LONG WINAPI MailRegCloseKey(HKEY hKey) WCE_LINK(MailRegCloseKey);

#define MailRegOpenKeyEx MailRegOpenKeyExW
#define MailRegEnumKeyEx MailRegEnumKeyExW
#ifdef __cplusplus
}
#endif
#endif

