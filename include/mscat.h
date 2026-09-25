/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MSCAT_H
#define WCE_MSCAT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagCRYPTCATATTRIBUTE { DWORD cbStruct; LPWSTR pwszReferenceTag; DWORD dwAttrTypeAndAction; DWORD cbValue; BYTE *pbValue; DWORD dwReserved; } CRYPTCATATTRIBUTE, *PCRYPTCATATTRIBUTE, *LPCRYPTCATATTRIBUTE;
typedef struct tagCRYPTCATCDF { DWORD cbStruct; HANDLE hFile; DWORD dwCurFilePos; DWORD dwLastMemberOffset; BOOL fEOF; LPWSTR pwszResultDir; HANDLE hCATStore; } CRYPTCATCDF, *PCRYPTCATCDF, *LPCRYPTCATCDF;

WCE_IMPORT BOOL WINAPI CryptCATClose(IN HANDLE hCatalog) WCE_LINK(CryptCATClose);
WCE_IMPORT BOOL WINAPI CryptCATPersistStore(IN HANDLE hCatalog) WCE_LINK(CryptCATPersistStore);
WCE_IMPORT CRYPTCATATTRIBUTE* WINAPI CryptCATGetCatAttrInfo(IN HANDLE hCatalog, IN LPWSTR pwszReferenceTag) WCE_LINK(CryptCATGetCatAttrInfo);
WCE_IMPORT CRYPTCATATTRIBUTE* WINAPI CryptCATPutCatAttrInfo(IN HANDLE hCatalog, IN LPWSTR pwszReferenceTag, IN DWORD dwAttrTypeAndAction, IN DWORD cbData, IN BYTE *pbData) WCE_LINK(CryptCATPutCatAttrInfo);
WCE_IMPORT CRYPTCATATTRIBUTE* WINAPI CryptCATEnumerateCatAttr(IN HANDLE hCatalog, IN CRYPTCATATTRIBUTE *pPrevAttr) WCE_LINK(CryptCATEnumerateCatAttr);
WCE_IMPORT CRYPTCATCDF* WINAPI CryptCATCDFOpen(IN LPWSTR pwszFilePath, IN OPTIONAL PFN_CDF_PARSE_ERROR_CALLBACK pfnParseError) WCE_LINK(CryptCATCDFOpen);
WCE_IMPORT BOOL WINAPI CryptCATCDFClose(IN CRYPTCATCDF *pCDF) WCE_LINK(CryptCATCDFClose);
WCE_IMPORT CRYPTCATATTRIBUTE* WINAPI CryptCATCDFEnumCatAttributes(CRYPTCATCDF *pCDF, CRYPTCATATTRIBUTE *pPrevAttr, PFN_CDF_PARSE_ERROR_CALLBACK pfnParseError) WCE_LINK(CryptCATCDFEnumCatAttributes);
WCE_IMPORT BOOL WINAPI IsCatalogFile(IN OPTIONAL HANDLE hFile, IN OPTIONAL WCHAR *pwszFileName) WCE_LINK(IsCatalogFile);
WCE_IMPORT BOOL WINAPI CryptCATAdminCalcHashFromFileHandle(IN HANDLE hFile, IN OUT DWORD *pcbHash, OUT OPTIONAL BYTE *pbHash, IN DWORD dwFlags) WCE_LINK(CryptCATAdminCalcHashFromFileHandle);

#ifdef __cplusplus
}
#endif
#endif

