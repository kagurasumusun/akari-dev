/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINDBASE_EDB_H
#define WCE_WINDBASE_EDB_H
#include "windef.h"
#include "winnt.h"
#include "windbase.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HANDLE WINAPI CeCreateSession(IN CEGUID* pGuid) WCE_LINK(CeCreateSession);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeSetSessionOption(IN HANDLE hSession, IN ULONG ulOptionId, IN DWORD dwValue) WCE_LINK(CeSetSessionOption);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HANDLE WINAPI CeGetDatabaseSession(IN HANDLE hDatabase) WCE_LINK(CeGetDatabaseSession);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeEndTransaction(IN HANDLE hSession, IN BOOL fCommit) WCE_LINK(CeEndTransaction);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeStreamRead(IN HANDLE hStream, OUT BYTE* prgbBuffer, IN DWORD cbRead, OUT DWORD* pcbRead) WCE_LINK(CeStreamRead);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeStreamWrite(IN HANDLE hStream, IN BYTE* prgbBuffer, IN DWORD cbWrite, OUT DWORD* pcbWritten) WCE_LINK(CeStreamWrite);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeStreamSaveChanges(IN HANDLE hStream) WCE_LINK(CeStreamSaveChanges);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeStreamSeek(IN HANDLE hStream, IN DWORD cbMove, IN DWORD dwOrigin, OUT DWORD* pcbNewOffset) WCE_LINK(CeStreamSeek);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeStreamSetSize(IN HANDLE hStream, IN DWORD cbSize) WCE_LINK(CeStreamSetSize);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeAddSyncPartner(IN PCEGUID pVolGuid, IN PCEGUID pSyncPartnerGuid, IN LPCWSTR pwszFriendlyName, IN LPCWSTR pwszFullName) WCE_LINK(CeAddSyncPartner);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeRemoveSyncPartner(IN PCEGUID pVolGuid, IN PCEGUID pSyncPartnerGuid) WCE_LINK(CeRemoveSyncPartner);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CeEndSyncSession(IN HANDLE hSession, IN DWORD dwOutcome) WCE_LINK(CeEndSyncSession);
#endif
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT BOOL WINAPI CePurgeTrackingData(IN PCEGUID pVolGuid, IN PCEGUID pSyncPartnerGuid, IN SYSTEMTIME* pstThreshold) WCE_LINK(CePurgeTrackingData);
#endif

#ifdef __cplusplus
}
#endif
#endif

