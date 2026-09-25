/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RASDLG_H
#define WCE_RASDLG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT BOOL WINAPI RasPhonebookDlgA(LPSTR lpszPhonebook, LPSTR lpszEntry, LPRASPBDLGA lpInfo) WCE_LINK(RasPhonebookDlgA);
WCE_IMPORT BOOL WINAPI RasPhonebookDlgW(LPWSTR lpszPhonebook, LPWSTR lpszEntry, LPRASPBDLGW lpInfo) WCE_LINK(RasPhonebookDlgW);
WCE_IMPORT BOOL WINAPI RasEntryDlgA(LPSTR lpszPhonebook, LPSTR lpszEntry, LPRASENTRYDLGA lpInfo) WCE_LINK(RasEntryDlgA);
WCE_IMPORT BOOL WINAPI RasEntryDlgW(LPWSTR lpszPhonebook, LPWSTR lpszEntry, LPRASENTRYDLGW lpInfo) WCE_LINK(RasEntryDlgW);
WCE_IMPORT BOOL WINAPI RasDialDlgA(LPSTR lpszPhonebook, LPSTR lpszEntry, LPSTR lpszPhoneNumber, LPRASDIALDLG lpInfo) WCE_LINK(RasDialDlgA);
WCE_IMPORT BOOL WINAPI RasDialDlgW(LPWSTR lpszPhonebook, LPWSTR lpszEntry, LPWSTR lpszPhoneNumber, LPRASDIALDLG lpInfo) WCE_LINK(RasDialDlgW);
WCE_IMPORT BOOL WINAPI RasMonitorDlgA(LPSTR lpszDeviceName, LPRASMONITORDLG lpInfo) WCE_LINK(RasMonitorDlgA);
WCE_IMPORT BOOL WINAPI RasMonitorDlgW(LPWSTR lpszDeviceName, LPRASMONITORDLG lpInfo) WCE_LINK(RasMonitorDlgW);

#define RasPhonebookDlg RasPhonebookDlgW
#define RasEntryDlg RasEntryDlgW
#define RasDialDlg RasDialDlgW
#define RasMonitorDlg RasMonitorDlgW
#ifdef __cplusplus
}
#endif
#endif

