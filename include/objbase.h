/*
 * objbase.h -- COM library, structured storage and moniker entry points.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * The prototypes below cover the application-facing surface of ole32.dll.
 */
#ifndef AKARI_WCE_OBJBASE_H
#define AKARI_WCE_OBJBASE_H

#include <wtypes.h>
#include <unknwn.h>
#include <objidl.h>

#ifndef _OBJBASE_H
#define _OBJBASE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINOLEAPI
#ifdef _OLE32_
#define WINOLEAPI        extern "C" HRESULT STDMETHODCALLTYPE
#define WINOLEAPI_(type) extern "C" type STDMETHODCALLTYPE
#else
#define WINOLEAPI        __declspec(dllimport) HRESULT STDMETHODCALLTYPE
#define WINOLEAPI_(type) __declspec(dllimport) type STDMETHODCALLTYPE
#endif
#endif

/* ------------------------------------------------- structures */

typedef struct akari_COSERVERINFO {
    DWORD             dwReserved1;
    LPWSTR            pwszName;
    void             *pAuthInfo;
    DWORD             dwReserved2;
} COSERVERINFO, *LPCOSERVERINFO;

typedef struct akari_MULTI_QI {
    const IID *pIID;
    IUnknown  *pItf;
    HRESULT    hr;
} MULTI_QI, *LPMULTI_QI;

typedef struct akari_SOLE_AUTHENTICATION_SERVICE {
    DWORD   dwAuthnSvc;
    DWORD   dwAuthzSvc;
    OLECHAR *pPrincipalName;
    HRESULT hr;
} SOLE_AUTHENTICATION_SERVICE;

typedef struct akari_RPC_AUTH_IDENTITY_HANDLE__ *RPC_AUTH_IDENTITY_HANDLE;
typedef struct akari_RPC_AUTHZ_HANDLE__ *RPC_AUTHZ_HANDLE;

/* ------------------------------------------------- prototypes */

WINOLEAPI BindMoniker(LPMONIKER pmk, DWORD grfOpt, REFIID iidResult, LPVOID * ppvResult);
WINOLEAPI CLSIDFromProgID(LPCOLESTR lpszProgID, LPCLSID lpclsid);
WINOLEAPI CLSIDFromString(LPOLESTR lpsz, LPCLSID pclsid);
WINOLEAPI_(ULONG) CoAddRefServerProcess(void);
WINOLEAPI_(DWORD) CoBuildVersion(VOID);
WINOLEAPI CoCopyProxy(IUnknown *pProxy, IUnknown **ppCopy);
WINOLEAPI CoCreateFreeThreadedMarshaler(LPUNKNOWN punkOuter, LPUNKNOWN *ppunkMarshal);
WINOLEAPI CoCreateGuid(GUID *pguid);
WINOLEAPI CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID * ppv);
WINOLEAPI CoCreateInstanceEx(REFCLSID Clsid, IUnknown * punkOuter, DWORD dwClsCtx,
    COSERVERINFO * pServerInfo, DWORD dwCount, MULTI_QI * pResults);
WINOLEAPI CoDisconnectObject(LPUNKNOWN pUnk, DWORD dwReserved);
WINOLEAPI CoFileTimeNow(FILETIME * lpFileTime);
WINOLEAPI_(void) CoFreeAllLibraries(void);
WINOLEAPI_(void) CoFreeLibrary(HINSTANCE hInst);
WINOLEAPI_(void) CoFreeUnusedLibraries(void);
WINOLEAPI_(void) CoFreeUnusedLibrariesEx(DWORD dwUnloadDelay, DWORD dwReserved);
WINOLEAPI CoGetCallContext(REFIID riid, void **ppInterface);
WINOLEAPI CoGetClassObject(REFCLSID rclsid, DWORD dwClsContext, LPVOID pvReserved, REFIID riid, LPVOID * ppv);
WINOLEAPI_(DWORD) CoGetCurrentProcess(void);
WINOLEAPI CoGetInstanceFromFile(COSERVERINFO * pServerInfo, CLSID * pClsid,
    IUnknown * punkOuter, DWORD dwClsCtx, DWORD grfMode, OLECHAR * pwszName,
    DWORD dwCount, MULTI_QI * pResults);
WINOLEAPI CoGetInstanceFromIStorage(COSERVERINFO * pServerInfo, CLSID * pClsid,
    IUnknown * punkOuter, DWORD dwClsCtx, struct IStorage * pstg, DWORD dwCount,
    MULTI_QI * pResults);
WINOLEAPI CoGetInterfaceAndReleaseStream(LPSTREAM pStm, REFIID iid, LPVOID * ppv);
WINOLEAPI CoGetMalloc(DWORD dwMemContext, LPMALLOC * ppMalloc);
WINOLEAPI CoGetMarshalSizeMax(ULONG *pulSize, REFIID riid, LPUNKNOWN pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags);
WINOLEAPI CoGetObject(LPCWSTR pszName, BIND_OPTS *pBindOptions, REFIID riid, void **ppv);
WINOLEAPI CoGetPSClsid(REFIID riid, CLSID *pClsid);
WINOLEAPI CoGetStandardMarshal(REFIID riid, LPUNKNOWN pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags, LPMARSHAL * ppMarshal);
WINOLEAPI CoGetTreatAsClass(REFCLSID clsidOld, LPCLSID pClsidNew);
WINOLEAPI CoImpersonateClient(void);
WINOLEAPI CoInitialize(LPVOID pvReserved);
WINOLEAPI CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit);
WINOLEAPI CoInitializeSecurity(PSECURITY_DESCRIPTOR pSecDesc, LONG cAuthSvc, SOLE_AUTHENTICATION_SERVICE *asAuthSvc, void *pReserved1, DWORD dwAuthnLevel, DWORD dwImpLevel, void *pReserved2, DWORD dwCapabilities, void *pReserved3);
WINOLEAPI_(BOOL) CoIsHandlerConnected(LPUNKNOWN pUnk);
WINOLEAPI_(BOOL) CoIsOle1Class(REFCLSID rclsid);
WINOLEAPI_(HINSTANCE) CoLoadLibrary(LPOLESTR lpszLibName, BOOL bAutoFree);
WINOLEAPI CoLockObjectExternal(LPUNKNOWN pUnk, BOOL fLock, BOOL fLastUnlockReleases);
WINOLEAPI CoMarshalHresult(LPSTREAM pstm, HRESULT hresult);
WINOLEAPI CoMarshalInterface(LPSTREAM pStm, REFIID riid, LPUNKNOWN pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags);
WINOLEAPI CoMarshalInterThreadInterfaceInStream(REFIID riid, LPUNKNOWN pUnk, LPSTREAM *ppStm);
WINOLEAPI CoQueryAuthenticationServices(DWORD *pcAuthSvc, SOLE_AUTHENTICATION_SERVICE **asAuthSvc);
WINOLEAPI CoQueryClientBlanket(DWORD *pAuthnSvc, DWORD *pAuthzSvc, OLECHAR **pServerPrincName, DWORD *pAuthnLevel, DWORD *pImpLevel, RPC_AUTHZ_HANDLE *pPrivs, DWORD *pCapabilities);
WINOLEAPI CoQueryProxyBlanket(IUnknown *pProxy, DWORD *pwAuthnSvc, DWORD *pAuthzSvc, OLECHAR **pServerPrincName, DWORD *pAuthnLevel, DWORD *pImpLevel, RPC_AUTH_IDENTITY_HANDLE *pAuthInfo, DWORD *pCapabilites);
WINOLEAPI CoRegisterChannelHook(REFGUID ExtensionUuid, IChannelHook *pChannelHook);
WINOLEAPI CoRegisterClassObject(REFCLSID rclsid, LPUNKNOWN pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister);
WINOLEAPI CoRegisterMallocSpy(LPMALLOCSPY pMallocSpy);
WINOLEAPI CoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter, LPMESSAGEFILTER * lplpMessageFilter);
WINOLEAPI CoRegisterPSClsid(REFIID riid, REFCLSID rclsid);
WINOLEAPI CoRegisterSurrogate(LPSURROGATE pSurrogate);
WINOLEAPI CoReleaseMarshalData(LPSTREAM pStm);
WINOLEAPI_(ULONG) CoReleaseServerProcess(void);
WINOLEAPI CoResumeClassObjects(void);
WINOLEAPI CoRevertToSelf(void);
WINOLEAPI CoRevokeClassObject(DWORD dwRegister);
WINOLEAPI CoRevokeMallocSpy(void);
WINOLEAPI CoSetProxyBlanket(IUnknown *pProxy, DWORD dwAuthnSvc, DWORD dwAuthzSvc, OLECHAR *pServerPrincName, DWORD dwAuthnLevel, DWORD dwImpLevel, RPC_AUTH_IDENTITY_HANDLE pAuthInfo, DWORD dwCapabilities);
WINOLEAPI CoSuspendClassObjects(void);
WINOLEAPI CoSwitchCallContext(IUnknown *pNewObject, IUnknown **ppOldObject);
WINOLEAPI_(LPVOID) CoTaskMemAlloc(ULONG cb);
WINOLEAPI_(void) CoTaskMemFree(LPVOID pv);
WINOLEAPI_(LPVOID) CoTaskMemRealloc(LPVOID pv, ULONG cb);
WINOLEAPI_(UINT) CoTaskMemSize(LPVOID pv);
WINOLEAPI CoTreatAsClass(REFCLSID clsidOld, REFCLSID clsidNew);
WINOLEAPI_(void) CoUninitialize(void);
WINOLEAPI CoUnmarshalHresult(LPSTREAM pstm, HRESULT * phresult);
WINOLEAPI CoUnmarshalInterface(LPSTREAM pStm, REFIID riid, LPVOID * ppv);
WINOLEAPI CreateAntiMoniker(LPMONIKER * ppmk);
WINOLEAPI CreateBindCtx(DWORD reserved, LPBC * ppbc);
WINOLEAPI CreateClassMoniker(REFCLSID rclsid, LPMONIKER * ppmk);
WINOLEAPI CreateFileMoniker(LPCOLESTR lpszPathName, LPMONIKER * ppmk);
WINOLEAPI CreateGenericComposite(LPMONIKER pmkFirst, LPMONIKER pmkRest, LPMONIKER * ppmkComposite);
WINOLEAPI CreateItemMoniker(LPCOLESTR lpszDelim, LPCOLESTR lpszItem, LPMONIKER * ppmk);

WINOLEAPI CreatePointerMoniker(LPUNKNOWN punk, LPMONIKER * ppmk);

WINOLEAPI GetClassFile(LPCOLESTR szFilename, CLSID * pclsid);

WINOLEAPI GetRunningObjectTable(DWORD reserved, LPRUNNINGOBJECTTABLE * pprot);
WINOLEAPI IIDFromString(LPOLESTR lpsz, LPIID lpiid);
WINOLEAPI MkParseDisplayName(LPBC pbc, LPCOLESTR szUserName, ULONG * pchEaten, LPMONIKER * ppmk);
WINOLEAPI MonikerCommonPrefixWith(LPMONIKER pmkThis, LPMONIKER pmkOther, LPMONIKER * ppmkCommon);
WINOLEAPI MonikerRelativePathTo(LPMONIKER pmkSrc, LPMONIKER pmkDest, LPMONIKER * ppmkRelPath, BOOL dwReserved);


WINOLEAPI_(BOOL) OleIsRunning(LPOLEOBJECT pObject);






WINOLEAPI ProgIDFromCLSID(REFCLSID clsid, LPOLESTR * lplpszProgID);


WINOLEAPI_(void) ReleaseStgMedium(LPSTGMEDIUM);
WINOLEAPI StgCreateDocfile(const OLECHAR * pwcsName, DWORD grfMode, DWORD reserved, IStorage * *ppstgOpen);
WINOLEAPI StgCreateDocfileOnILockBytes(ILockBytes *plkbyt, DWORD grfMode, DWORD reserved, IStorage * *ppstgOpen);
WINOLEAPI StgOpenStorage(const OLECHAR * pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage * *ppstgOpen);
WINOLEAPI StgOpenStorageOnILockBytes(ILockBytes *plkbyt, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage * *ppstgOpen);
WINOLEAPI StringFromCLSID(REFCLSID rclsid, LPOLESTR * lplpsz);
WINOLEAPI_(int) StringFromGUID2(REFGUID rguid, LPOLESTR lpsz, int cbMax);
WINOLEAPI StringFromIID(REFIID rclsid, LPOLESTR * lplpsz);
WINOLEAPI_(void) UpdateDCOMSettings(void);


#ifdef __cplusplus
}
#endif

#endif /* _OBJBASE_H */
#endif /* AKARI_WCE_OBJBASE_H */
