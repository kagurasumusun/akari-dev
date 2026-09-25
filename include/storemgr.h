/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_STOREMGR_H
#define WCE_STOREMGR_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI OpenStore(LPCTSTR szDeviceName) WCE_LINK(OpenStore);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI DismountStore(HANDLE hStore) WCE_LINK(DismountStore);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FormatStore(HANDLE hStore) WCE_LINK(FormatStore);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI FindFirstStore(PSTOREINFO pStoreInfo) WCE_LINK(FindFirstStore);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FindNextStore(HANDLE hSearch, PSTOREINFO pStoreInfo) WCE_LINK(FindNextStore);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FindCloseStore(HANDLE hSearch) WCE_LINK(FindCloseStore);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI GetStoreInfo(HANDLE hStore, PSTOREINFO pStoreInfo) WCE_LINK(GetStoreInfo);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI DeletePartition(HANDLE hStore, LPCTSTR szPartitionName) WCE_LINK(DeletePartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI OpenPartition(HANDLE hStore, LPCTSTR szPartitionName) WCE_LINK(OpenPartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI MountPartition(HANDLE hPartition) WCE_LINK(MountPartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI DismountPartition(HANDLE hPartition) WCE_LINK(DismountPartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI RenamePartition(HANDLE hPartition, LPCTSTR szNewName) WCE_LINK(RenamePartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI SetPartitionAttributes(HANDLE hPartition, DWORD dwAttrs) WCE_LINK(SetPartitionAttributes);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI GetPartitionInfo(HANDLE hPartition, PPARTINFO pPartInfo) WCE_LINK(GetPartitionInfo);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FormatPartition(HANDLE hPartition) WCE_LINK(FormatPartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FormatPartitionEx(HANDLE hPartition, BYTE bPartType, BOOL bAuto) WCE_LINK(FormatPartitionEx);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HANDLE WINAPI FindFirstPartition(HANDLE hStore, PPARTINFO pPartInfo) WCE_LINK(FindFirstPartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FindNextPartition(HANDLE hSearch, PPARTINFO pPartInfo) WCE_LINK(FindNextPartition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT BOOL WINAPI FindClosePartition(HANDLE hSearch) WCE_LINK(FindClosePartition);
#endif

#ifdef __cplusplus
}
#endif
#endif

