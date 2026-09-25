/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_APPMGMT_H
#define WCE_APPMGMT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLOCALMANAGEDAPPLICATION { LPWSTR pszDeploymentName; LPWSTR pszPolicyName; LPWSTR pszProductId; DWORD dwState; } LOCALMANAGEDAPPLICATION, *PLOCALMANAGEDAPPLICATION, *LPLOCALMANAGEDAPPLICATION;
typedef struct tagMANAGEDAPPLICATION { LPWSTR pszPackageName; LPWSTR pszPublisher; DWORD dwVersionHi; DWORD dwVersionLo; DWORD dwRevision; GUID GpoId; LPWSTR pszPolicyName; GUID ProductId; LANGID Language; LPWSTR pszOwner; LPWSTR pszCompany; LPWSTR pszComments; LPWSTR pszContact; LPWSTR pszSupportUrl; DWORD dwPathType; BOOL bInstalled; } MANAGEDAPPLICATION, *PMANAGEDAPPLICATION, *LPMANAGEDAPPLICATION;
typedef struct tagAPPCATEGORYINFO { LCID Locale; LPWSTR pszDescription; GUID AppCategoryId; } APPCATEGORYINFO, *PAPPCATEGORYINFO, *LPAPPCATEGORYINFO;

WCE_IMPORT DWORD WINAPI InstallApplication(PINSTALLDATA pInstallInfo) WCE_LINK(InstallApplication);
WCE_IMPORT DWORD WINAPI UninstallApplication(WCHAR * ProductCode) WCE_LINK(UninstallApplication);
WCE_IMPORT DWORD WINAPI CommandLineFromMsiDescriptor(WCHAR * Descriptor, WCHAR * CommandLine, DWORD * CommandLineLength) WCE_LINK(CommandLineFromMsiDescriptor);
WCE_IMPORT DWORD WINAPI GetManagedApplications(GUID * pCategory, DWORD dwQueryFlags, DWORD dwInfoLevel, LPDWORD pdwApps, PMANAGEDAPPLICATION* prgManagedApps) WCE_LINK(GetManagedApplications);
WCE_IMPORT DWORD WINAPI GetLocalManagedApplications(BOOL bUserApps, LPDWORD pdwApps, PLOCALMANAGEDAPPLICATION* prgLocalApps) WCE_LINK(GetLocalManagedApplications);

#ifdef __cplusplus
}
#endif
#endif

