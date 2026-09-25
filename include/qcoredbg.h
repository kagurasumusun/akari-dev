/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_QCOREDBG_H
#define WCE_QCOREDBG_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT DWORD WINAPI DbgExGetVersion() WCE_LINK(DbgExGetVersion);
WCE_IMPORT BOOL WINAPI DbgExIsFullDebug() WCE_LINK(DbgExIsFullDebug);
WCE_IMPORT void WINAPI DbgExDoTracePointsDialog(BOOL fWait) WCE_LINK(DbgExDoTracePointsDialog);
WCE_IMPORT void WINAPI DbgExRestoreDefaultDebugState() WCE_LINK(DbgExRestoreDefaultDebugState);
WCE_IMPORT BOOL WINAPI DbgExAssertImpl(char const * szFile, int iLine, char const * szMessage) WCE_LINK(DbgExAssertImpl);
WCE_IMPORT void WINAPI DbgExAssertThreadDisable(BOOL fDisable) WCE_LINK(DbgExAssertThreadDisable);
WCE_IMPORT void* WINAPI DbgExPostAlloc(void *pv) WCE_LINK(DbgExPostAlloc);
WCE_IMPORT void* WINAPI DbgExPreFree(void *pv) WCE_LINK(DbgExPreFree);
WCE_IMPORT void WINAPI DbgExPostFree() WCE_LINK(DbgExPostFree);
WCE_IMPORT void* WINAPI DbgExPostRealloc(void *pv) WCE_LINK(DbgExPostRealloc);
WCE_IMPORT void* WINAPI DbgExPreGetSize(void *pvRequest) WCE_LINK(DbgExPreGetSize);
WCE_IMPORT void* WINAPI DbgExPreDidAlloc(void *pvRequest) WCE_LINK(DbgExPreDidAlloc);
WCE_IMPORT BOOL WINAPI DbgExPostDidAlloc(void *pvRequest, BOOL fActual) WCE_LINK(DbgExPostDidAlloc);
WCE_IMPORT void WINAPI DbgExMemoryTrackDisable(BOOL fDisable) WCE_LINK(DbgExMemoryTrackDisable);
WCE_IMPORT void WINAPI DbgExCoMemoryTrackDisable(BOOL fDisable) WCE_LINK(DbgExCoMemoryTrackDisable);
WCE_IMPORT void WINAPI DbgExMemoryBlockTrackDisable(void * pv) WCE_LINK(DbgExMemoryBlockTrackDisable);
WCE_IMPORT void* WINAPI DbgExGetMallocSpy() WCE_LINK(DbgExGetMallocSpy);
WCE_IMPORT void WINAPI DbgExTraceMemoryLeaks() WCE_LINK(DbgExTraceMemoryLeaks);
WCE_IMPORT BOOL WINAPI DbgExValidateInternalHeap() WCE_LINK(DbgExValidateInternalHeap);
WCE_IMPORT LONG_PTR WINAPI DbgExTraceFailL(LONG_PTR errExpr, LONG_PTR errTest, BOOL fIgnore, LPSTR pstrExpr, LPSTR pstrFile, int line) WCE_LINK(DbgExTraceFailL);
WCE_IMPORT LONG_PTR WINAPI DbgExTraceWin32L(LONG_PTR errExpr, LONG_PTR errTest, BOOL fIgnore, LPSTR pstrExpr, LPSTR pstrFile, int line) WCE_LINK(DbgExTraceWin32L);
WCE_IMPORT HRESULT WINAPI DbgExTraceHR(HRESULT hrTest, BOOL fIgnore, LPSTR pstrExpr, LPSTR pstrFile, int line) WCE_LINK(DbgExTraceHR);
WCE_IMPORT HRESULT WINAPI DbgExTraceOLE(HRESULT hrTest, BOOL fIgnore, LPSTR pstrExpr, LPSTR pstrFile, int line, LPVOID lpsite) WCE_LINK(DbgExTraceOLE);
WCE_IMPORT void WINAPI DbgExTraceEnter(LPSTR pstrExpr, LPSTR pstrFile, int line) WCE_LINK(DbgExTraceEnter);
WCE_IMPORT void WINAPI DbgExTraceExit(LPSTR pstrExpr, LPSTR pstrFile, int line) WCE_LINK(DbgExTraceExit);
WCE_IMPORT void WINAPI DbgExSetSimFailCounts(int firstFailure, int cInterval) WCE_LINK(DbgExSetSimFailCounts);
WCE_IMPORT void WINAPI DbgExShowSimFailDlg() WCE_LINK(DbgExShowSimFailDlg);
WCE_IMPORT BOOL WINAPI DbgExFFail() WCE_LINK(DbgExFFail);
WCE_IMPORT int WINAPI DbgExGetFailCount() WCE_LINK(DbgExGetFailCount);
WCE_IMPORT void WINAPI DbgExTrackItf(REFIID iid, char * pch, BOOL fTrackOnQI, void **ppv) WCE_LINK(DbgExTrackItf);
WCE_IMPORT void WINAPI DbgExOpenMemoryMonitor() WCE_LINK(DbgExOpenMemoryMonitor);
WCE_IMPORT void WINAPI DbgExOpenLogFile(LPCSTR szFName) WCE_LINK(DbgExOpenLogFile);
WCE_IMPORT char* WINAPI DbgExMemGetName(void *pvRequest) WCE_LINK(DbgExMemGetName);
WCE_IMPORT HRESULT WINAPI DbgExWsClear(HANDLE hProcess) WCE_LINK(DbgExWsClear);
WCE_IMPORT HRESULT WINAPI DbgExWsTakeSnapshot(HANDLE hProcess) WCE_LINK(DbgExWsTakeSnapshot);
WCE_IMPORT long WINAPI DbgExWsSize(long row) WCE_LINK(DbgExWsSize);
WCE_IMPORT long WINAPI DbgExWsCount() WCE_LINK(DbgExWsCount);
WCE_IMPORT long WINAPI DbgExWsTotal() WCE_LINK(DbgExWsTotal);
WCE_IMPORT HRESULT WINAPI DbgExWsStartDelta(HANDLE hProcess) WCE_LINK(DbgExWsStartDelta);
WCE_IMPORT long WINAPI DbgExWsEndDelta(HANDLE hProcess) WCE_LINK(DbgExWsEndDelta);
WCE_IMPORT void WINAPI DbgExDumpProcessHeaps() WCE_LINK(DbgExDumpProcessHeaps);
WCE_IMPORT PERFTAG WINAPI DbgExPerfRegister(char * szTag, char * szOwner, char * szDescrip) WCE_LINK(DbgExPerfRegister);
WCE_IMPORT void WINAPI DbgExPerfDump() WCE_LINK(DbgExPerfDump);
WCE_IMPORT void WINAPI DbgExPerfClear() WCE_LINK(DbgExPerfClear);
WCE_IMPORT void WINAPI DbgExPerfTags() WCE_LINK(DbgExPerfTags);
WCE_IMPORT char* WINAPI DbgExDecodeMessage(UINT msg) WCE_LINK(DbgExDecodeMessage);
WCE_IMPORT PERFMETERTAG WINAPI DbgExMtRegister(char * szTag, char * szOwner, char * szDescrip) WCE_LINK(DbgExMtRegister);
WCE_IMPORT void WINAPI DbgExMtAdd(PERFMETERTAG mt, LONG lCnt, LONG lVal) WCE_LINK(DbgExMtAdd);
WCE_IMPORT void WINAPI DbgExMtSet(PERFMETERTAG mt, LONG lCnt, LONG lVal) WCE_LINK(DbgExMtSet);
WCE_IMPORT char* WINAPI DbgExMtGetName(PERFMETERTAG mt) WCE_LINK(DbgExMtGetName);
WCE_IMPORT char* WINAPI DbgExMtGetDesc(PERFMETERTAG mt) WCE_LINK(DbgExMtGetDesc);
WCE_IMPORT BOOL WINAPI DbgExMtSimulateOutOfMemory(PERFMETERTAG mt, LONG lNewValue) WCE_LINK(DbgExMtSimulateOutOfMemory);
WCE_IMPORT void WINAPI DbgExMtOpenMonitor() WCE_LINK(DbgExMtOpenMonitor);
WCE_IMPORT void WINAPI DbgExMtLogDump(LPSTR pchFile) WCE_LINK(DbgExMtLogDump);
WCE_IMPORT void WINAPI DbgExSetTopUrl(LPWSTR pstrUrl) WCE_LINK(DbgExSetTopUrl);
WCE_IMPORT void WINAPI DbgExGetSymbolFromAddress(void * pvAddr, char * pszBuf, DWORD cchBuf) WCE_LINK(DbgExGetSymbolFromAddress);
WCE_IMPORT BOOL WINAPI DbgExGetChkStkFill(DWORD * pdwFill) WCE_LINK(DbgExGetChkStkFill);

#ifdef __cplusplus
}
#endif
#endif

