/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_OBJBASE_H
#define WCE_OBJBASE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI CoInitialize(LPVOID pvReserved) WCE_LINK(CoInitialize);
WCE_IMPORT HRESULT WINAPI CoGetMalloc(DWORD dwMemContext, LPMALLOC FAR* ppMalloc) WCE_LINK(CoGetMalloc);
WCE_IMPORT HRESULT WINAPI CoRegisterMallocSpy(LPMALLOCSPY pMallocSpy) WCE_LINK(CoRegisterMallocSpy);
WCE_IMPORT HRESULT WINAPI CoRevokeMallocSpy(void) WCE_LINK(CoRevokeMallocSpy);
WCE_IMPORT HRESULT WINAPI CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit) WCE_LINK(CoInitializeEx);
WCE_IMPORT HRESULT WINAPI CoRegisterClassObject(REFCLSID rclsid, LPUNKNOWN pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister) WCE_LINK(CoRegisterClassObject);
WCE_IMPORT HRESULT WINAPI CoRevokeClassObject(DWORD dwRegister) WCE_LINK(CoRevokeClassObject);
WCE_IMPORT HRESULT WINAPI CoResumeClassObjects(void) WCE_LINK(CoResumeClassObjects);
WCE_IMPORT HRESULT WINAPI CoSuspendClassObjects(void) WCE_LINK(CoSuspendClassObjects);
WCE_IMPORT HRESULT WINAPI CoGetPSClsid(REFIID riid, CLSID *pClsid) WCE_LINK(CoGetPSClsid);
WCE_IMPORT HRESULT WINAPI CoRegisterPSClsid(REFIID riid, REFCLSID rclsid) WCE_LINK(CoRegisterPSClsid);
WCE_IMPORT HRESULT WINAPI CoRegisterSurrogate(LPSURROGATE pSurrogate) WCE_LINK(CoRegisterSurrogate);
WCE_IMPORT HRESULT WINAPI CoGetMarshalSizeMax(ULONG *pulSize, REFIID riid, LPUNKNOWN pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags) WCE_LINK(CoGetMarshalSizeMax);
WCE_IMPORT HRESULT WINAPI CoMarshalInterface(LPSTREAM pStm, REFIID riid, LPUNKNOWN pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags) WCE_LINK(CoMarshalInterface);
WCE_IMPORT HRESULT WINAPI CoUnmarshalInterface(LPSTREAM pStm, REFIID riid, LPVOID FAR* ppv) WCE_LINK(CoUnmarshalInterface);
WCE_IMPORT HRESULT WINAPI CoMarshalHresult(LPSTREAM pstm, HRESULT hresult) WCE_LINK(CoMarshalHresult);
WCE_IMPORT HRESULT WINAPI CoUnmarshalHresult(LPSTREAM pstm, HRESULT FAR * phresult) WCE_LINK(CoUnmarshalHresult);
WCE_IMPORT HRESULT WINAPI CoReleaseMarshalData(LPSTREAM pStm) WCE_LINK(CoReleaseMarshalData);
WCE_IMPORT HRESULT WINAPI CoDisconnectObject(LPUNKNOWN pUnk, DWORD dwReserved) WCE_LINK(CoDisconnectObject);
WCE_IMPORT HRESULT WINAPI CoLockObjectExternal(LPUNKNOWN pUnk, BOOL fLock, BOOL fLastUnlockReleases) WCE_LINK(CoLockObjectExternal);
WCE_IMPORT HRESULT WINAPI CoGetStandardMarshal(REFIID riid, LPUNKNOWN pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags, LPMARSHAL FAR* ppMarshal) WCE_LINK(CoGetStandardMarshal);
WCE_IMPORT HRESULT WINAPI CoMarshalInterThreadInterfaceInStream(REFIID riid, LPUNKNOWN pUnk, LPSTREAM *ppStm) WCE_LINK(CoMarshalInterThreadInterfaceInStream);
WCE_IMPORT HRESULT WINAPI CoGetInterfaceAndReleaseStream(LPSTREAM pStm, REFIID iid, LPVOID FAR* ppv) WCE_LINK(CoGetInterfaceAndReleaseStream);
WCE_IMPORT HRESULT WINAPI CoCreateFreeThreadedMarshaler(LPUNKNOWN punkOuter, LPUNKNOWN *ppunkMarshal) WCE_LINK(CoCreateFreeThreadedMarshaler);
WCE_IMPORT HRESULT WINAPI CoGetCallContext(REFIID riid, void **ppInterface) WCE_LINK(CoGetCallContext);
WCE_IMPORT HRESULT WINAPI CoImpersonateClient() WCE_LINK(CoImpersonateClient);
WCE_IMPORT HRESULT WINAPI CoRevertToSelf() WCE_LINK(CoRevertToSelf);
WCE_IMPORT HRESULT WINAPI CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID FAR* ppv) WCE_LINK(CoCreateInstance);
WCE_IMPORT HRESULT WINAPI CoGetClassObject(REFCLSID rclsid, DWORD dwClsContext, LPVOID pvReserved, REFIID riid, LPVOID FAR* ppv) WCE_LINK(CoGetClassObject);
WCE_IMPORT HRESULT WINAPI StringFromCLSID(REFCLSID rclsid, LPOLESTR FAR* lplpsz) WCE_LINK(StringFromCLSID);
WCE_IMPORT HRESULT WINAPI CLSIDFromString(LPOLESTR lpsz, LPCLSID pclsid) WCE_LINK(CLSIDFromString);
WCE_IMPORT HRESULT WINAPI StringFromIID(REFIID rclsid, LPOLESTR FAR* lplpsz) WCE_LINK(StringFromIID);
WCE_IMPORT HRESULT WINAPI IIDFromString(LPOLESTR lpsz, LPIID lpiid) WCE_LINK(IIDFromString);
WCE_IMPORT HRESULT WINAPI ProgIDFromCLSID(REFCLSID clsid, LPOLESTR FAR* lplpszProgID) WCE_LINK(ProgIDFromCLSID);
WCE_IMPORT HRESULT WINAPI CLSIDFromProgID(LPCOLESTR lpszProgID, LPCLSID lpclsid) WCE_LINK(CLSIDFromProgID);
WCE_IMPORT HRESULT WINAPI CoCreateGuid(GUID FAR *pguid) WCE_LINK(CoCreateGuid);
WCE_IMPORT HRESULT WINAPI CoFileTimeNow(FILETIME FAR* lpFileTime) WCE_LINK(CoFileTimeNow);
WCE_IMPORT HRESULT WINAPI CoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter, LPMESSAGEFILTER FAR* lplpMessageFilter) WCE_LINK(CoRegisterMessageFilter);
WCE_IMPORT HRESULT WINAPI CoGetTreatAsClass(REFCLSID clsidOld, LPCLSID pClsidNew) WCE_LINK(CoGetTreatAsClass);
WCE_IMPORT HRESULT WINAPI CoTreatAsClass(REFCLSID clsidOld, REFCLSID clsidNew) WCE_LINK(CoTreatAsClass);
WCE_IMPORT HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv) WCE_LINK(DllGetClassObject);
WCE_IMPORT HRESULT WINAPI DllCanUnloadNow(void) WCE_LINK(DllCanUnloadNow);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI CreateDataAdviseHolder(LPDATAADVISEHOLDER FAR* ppDAHolder) WCE_LINK(CreateDataAdviseHolder);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI CreateDataCache(LPUNKNOWN pUnkOuter, REFCLSID rclsid, REFIID iid, LPVOID FAR* ppv) WCE_LINK(CreateDataCache);
#endif
WCE_IMPORT HRESULT WINAPI BindMoniker(LPMONIKER pmk, DWORD grfOpt, REFIID iidResult, LPVOID FAR* ppvResult) WCE_LINK(BindMoniker);
WCE_IMPORT HRESULT WINAPI MkParseDisplayName(LPBC pbc, LPCOLESTR szUserName, ULONG FAR * pchEaten, LPMONIKER FAR * ppmk) WCE_LINK(MkParseDisplayName);
WCE_IMPORT HRESULT WINAPI MonikerRelativePathTo(LPMONIKER pmkSrc, LPMONIKER pmkDest, LPMONIKER FAR* ppmkRelPath, BOOL dwReserved) WCE_LINK(MonikerRelativePathTo);
WCE_IMPORT HRESULT WINAPI MonikerCommonPrefixWith(LPMONIKER pmkThis, LPMONIKER pmkOther, LPMONIKER FAR* ppmkCommon) WCE_LINK(MonikerCommonPrefixWith);
WCE_IMPORT HRESULT WINAPI CreateBindCtx(DWORD reserved, LPBC FAR* ppbc) WCE_LINK(CreateBindCtx);
WCE_IMPORT HRESULT WINAPI CreateGenericComposite(LPMONIKER pmkFirst, LPMONIKER pmkRest, LPMONIKER FAR* ppmkComposite) WCE_LINK(CreateGenericComposite);
WCE_IMPORT HRESULT WINAPI GetClassFile(LPCOLESTR szFilename, CLSID FAR* pclsid) WCE_LINK(GetClassFile);
WCE_IMPORT HRESULT WINAPI CreateClassMoniker(REFCLSID rclsid, LPMONIKER FAR* ppmk) WCE_LINK(CreateClassMoniker);
WCE_IMPORT HRESULT WINAPI CreateFileMoniker(LPCOLESTR lpszPathName, LPMONIKER FAR* ppmk) WCE_LINK(CreateFileMoniker);
WCE_IMPORT HRESULT WINAPI CreateItemMoniker(LPCOLESTR lpszDelim, LPCOLESTR lpszItem, LPMONIKER FAR* ppmk) WCE_LINK(CreateItemMoniker);
WCE_IMPORT HRESULT WINAPI CreateAntiMoniker(LPMONIKER FAR* ppmk) WCE_LINK(CreateAntiMoniker);
WCE_IMPORT HRESULT WINAPI CreatePointerMoniker(LPUNKNOWN punk, LPMONIKER FAR* ppmk) WCE_LINK(CreatePointerMoniker);
WCE_IMPORT HRESULT WINAPI GetRunningObjectTable(DWORD reserved, LPRUNNINGOBJECTTABLE FAR* pprot) WCE_LINK(GetRunningObjectTable);

#ifdef __cplusplus
}
#endif
#endif

