/*
 * objidl.h -- COM interface method tables for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * The method order and signatures are the application-facing COM surface;
 * IUnknown's three methods come first in every vtable, as the ABI requires.
 */
#ifndef AKARI_WCE_OBJIDL_H
#define AKARI_WCE_OBJIDL_H

#include <unknwn.h>

#ifndef _OBJIDL_H
#define _OBJIDL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Bind options, used by IBindCtx and the moniker entry points. */
typedef struct akari_BIND_OPTS {
    DWORD  cbStruct;
    DWORD  grfFlags;
    DWORD  grfMode;
    DWORD  dwTickCountDeadline;
} BIND_OPTS, *LPBIND_OPTS;

#define BIND_MAYBOTHERUSER     1
#define BIND_JUSTTESTEXISTENCE 2

/* ------------------------------------------------------------ ISequentialStream */

#undef  INTERFACE
#define INTERFACE ISequentialStream

DECLARE_INTERFACE_(ISequentialStream, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(Read)(THIS_ void *pv, ULONG cb, ULONG *pcbRead) PURE;
    STDMETHOD(Write)(THIS_ const void *pv, ULONG cb, ULONG *pcbWritten) PURE;
};

typedef ISequentialStream *LPSEQUENTIALSTREAM;

/* ------------------------------------------------------------ IStream */

#undef  INTERFACE
#define INTERFACE IStream

DECLARE_INTERFACE_(IStream, ISequentialStream)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(Read)(THIS_ void *pv, ULONG cb, ULONG *pcbRead) PURE;
    STDMETHOD(Write)(THIS_ const void *pv, ULONG cb, ULONG *pcbWritten) PURE;
    STDMETHOD(Seek)(THIS_ LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition) PURE;
    STDMETHOD(SetSize)(THIS_ ULARGE_INTEGER libNewSize) PURE;
    STDMETHOD(CopyTo)(THIS_ IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten) PURE;
    STDMETHOD(Commit)(THIS_ DWORD grfCommitFlags) PURE;
    STDMETHOD(Revert)(THIS) PURE;
    STDMETHOD(LockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) PURE;
    STDMETHOD(UnlockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) PURE;
    STDMETHOD(Stat)(THIS_ STATSTG *pstatstg, DWORD grfStatFlag) PURE;
    STDMETHOD(Clone)(THIS_ IStream * *ppstm) PURE;
};

typedef IStream *LPSTREAM;

/* ------------------------------------------------------------ IEnumSTATSTG */

#undef  INTERFACE
#define INTERFACE IEnumSTATSTG

DECLARE_INTERFACE_(IEnumSTATSTG, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(Next)(THIS_ ULONG celt, STATSTG *rgelt, ULONG *pceltFetched) PURE;
    STDMETHOD(Skip)(THIS_ ULONG celt) PURE;
    STDMETHOD(Reset)(THIS) PURE;
    STDMETHOD(Clone)(THIS_ IEnumSTATSTG * *ppenum) PURE;
};

typedef IEnumSTATSTG *LPENUMSTATSTG;

/* ------------------------------------------------------------ IStorage */

#undef  INTERFACE
#define INTERFACE IStorage

DECLARE_INTERFACE_(IStorage, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(CreateStream)(THIS_ const OLECHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream * *ppstm) PURE;
    STDMETHOD(OpenStream)(THIS_ const OLECHAR *pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream * *ppstm) PURE;
    STDMETHOD(CreateStorage)(THIS_ const OLECHAR *pwcsName, DWORD grfMode, DWORD dwStgFmt, DWORD reserved2, IStorage * *ppstg) PURE;
    STDMETHOD(OpenStorage)(THIS_ const OLECHAR *pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage * *ppstg) PURE;
    STDMETHOD(CopyTo)(THIS_ DWORD ciidExclude, const IID *rgiidExclude, SNB snbExclude, IStorage *pstgDest) PURE;
    STDMETHOD(MoveElementTo)(THIS_ const OLECHAR *pwcsName, IStorage *pstgDest, const OLECHAR *pwcsNewName, DWORD grfFlags) PURE;
    STDMETHOD(Commit)(THIS_ DWORD grfCommitFlags) PURE;
    STDMETHOD(Revert)(THIS) PURE;
    STDMETHOD(EnumElements)(THIS_ DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG * *ppenum) PURE;
    STDMETHOD(DestroyElement)(THIS_ const OLECHAR *pwcsName) PURE;
    STDMETHOD(RenameElement)(THIS_ const OLECHAR *pwcsOldName, const OLECHAR *pwcsNewName) PURE;
    STDMETHOD(SetElementTimes)(THIS_ const OLECHAR *pwcsName, const FILETIME *pctime, const FILETIME *patime, const FILETIME *pmtime) PURE;
    STDMETHOD(SetClass)(THIS_ REFCLSID clsid) PURE;
    STDMETHOD(SetStateBits)(THIS_ DWORD grfStateBits, DWORD grfMask) PURE;
    STDMETHOD(Stat)(THIS_ STATSTG *pstatstg, DWORD grfStatFlag) PURE;
};

typedef IStorage *LPSTORAGE;

/* ------------------------------------------------------------ ILockBytes */

#undef  INTERFACE
#define INTERFACE ILockBytes

DECLARE_INTERFACE_(ILockBytes, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(ReadAt)(THIS_ ULARGE_INTEGER ulOffset, void *pv, ULONG cb, ULONG *pcbRead) PURE;
    STDMETHOD(WriteAt)(THIS_ ULARGE_INTEGER ulOffset, const void *pv, ULONG cb, ULONG *pcbWritten) PURE;
    STDMETHOD(Flush)(THIS) PURE;
    STDMETHOD(SetSize)(THIS_ ULARGE_INTEGER cb) PURE;
    STDMETHOD(LockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) PURE;
    STDMETHOD(UnlockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType) PURE;
    STDMETHOD(Stat)(THIS_ STATSTG *pstatstg, DWORD grfStatFlag) PURE;
};

typedef ILockBytes *LPLOCKBYTES;

/* ------------------------------------------------------------ IMalloc */

#undef  INTERFACE
#define INTERFACE IMalloc

DECLARE_INTERFACE_(IMalloc, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD_(void *, Alloc)(THIS_ ULONG cb) PURE;
    STDMETHOD_(void *, Realloc)(THIS_ void *pv, ULONG cb) PURE;
    STDMETHOD_(void, Free)(THIS_ void *pv) PURE;
    STDMETHOD_(ULONG, GetSize)(THIS_ void *pv) PURE;
    STDMETHOD_(int, DidAlloc)(THIS_ void *pv) PURE;
    STDMETHOD_(void, HeapMinimize)(THIS) PURE;
};

typedef IMalloc *LPMALLOC;

/* ------------------------------------------------------------ IMarshal */

#undef  INTERFACE
#define INTERFACE IMarshal

DECLARE_INTERFACE_(IMarshal, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(GetUnmarshalClass)(THIS_ REFIID riid, void *pv, DWORD dwDestContext, void *pvDestContext, DWORD mshlflags, CLSID *pCid) PURE;
    STDMETHOD(GetMarshalSizeMax)(THIS_ REFIID riid, void *pv, DWORD dwDestContext, void *pvDestContext, DWORD mshlflags, DWORD *pSize) PURE;
    STDMETHOD(MarshalInterface)(THIS_ IStream *pStm, REFIID riid, void *pv, DWORD dwDestContext, void *pvDestContext, DWORD mshlflags) PURE;
    STDMETHOD(UnmarshalInterface)(THIS_ IStream *pStm, REFIID riid, void * *ppv) PURE;
    STDMETHOD(ReleaseMarshalData)(THIS_ IStream *pStm) PURE;
    STDMETHOD(DisconnectObject)(THIS_ DWORD dwReserved) PURE;
};

typedef IMarshal *LPMARSHAL;

/* ------------------------------------------------------------ IMessageFilter */

#undef  INTERFACE
#define INTERFACE IMessageFilter

DECLARE_INTERFACE_(IMessageFilter, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD_(DWORD, HandleInComingCall)(THIS_ DWORD dwCallType, HTASK htaskCaller, DWORD dwTickCount, LPINTERFACEINFO lpInterfaceInfo) PURE;
    STDMETHOD_(DWORD, RetryRejectedCall)(THIS_ HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType) PURE;
    STDMETHOD_(DWORD, MessagePending)(THIS_ HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType) PURE;
};

typedef IMessageFilter *LPMESSAGEFILTER;

/* ------------------------------------------------------------ IMallocSpy */

#undef  INTERFACE
#define INTERFACE IMallocSpy

DECLARE_INTERFACE_(IMallocSpy, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD_(ULONG, PreAlloc)(THIS_ ULONG cbRequest) PURE;
    STDMETHOD_(void *, PostAlloc)(THIS_ void *pActual) PURE;
    STDMETHOD_(void *, PreFree)(THIS_ void *pRequest, BOOL fSpyed) PURE;
    STDMETHOD_(void, PostFree)(THIS_ BOOL fSpyed) PURE;
    STDMETHOD_(ULONG, PreRealloc)(THIS_ void *pRequest, ULONG cbRequest, void * *ppNewRequest, BOOL fSpyed) PURE;
    STDMETHOD_(void *, PostRealloc)(THIS_ void *pActual, BOOL fSpyed) PURE;
    STDMETHOD_(void *, PreGetSize)(THIS_ void *pRequest, BOOL fSpyed) PURE;
    STDMETHOD_(ULONG, PostGetSize)(THIS_ ULONG cbActual, BOOL fSpyed) PURE;
    STDMETHOD_(void *, PreDidAlloc)(THIS_ void *pRequest, BOOL fSpyed) PURE;
    STDMETHOD_(int, PostDidAlloc)(THIS_ void *pRequest, BOOL fSpyed, int fActual) PURE;
    STDMETHOD_(void, PreHeapMinimize)(THIS) PURE;
    STDMETHOD_(void, PostHeapMinimize)(THIS) PURE;
};

typedef IMallocSpy *LPMALLOCSPY;

/* ------------------------------------------------------------ ISurrogate */

#undef  INTERFACE
#define INTERFACE ISurrogate

DECLARE_INTERFACE_(ISurrogate, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(LoadDllServer)(THIS_ REFCLSID Clsid) PURE;
    STDMETHOD(FreeSurrogate)(THIS) PURE;
};

typedef ISurrogate *LPSURROGATE;

/* ------------------------------------------------------------ IChannelHook */

#undef  INTERFACE
#define INTERFACE IChannelHook

DECLARE_INTERFACE_(IChannelHook, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD_(void, ClientGetSize)(THIS_ REFGUID uExtent, REFIID riid, ULONG *pDataSize) PURE;
    STDMETHOD_(void, ClientFillBuffer)(THIS_ REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer) PURE;
    STDMETHOD_(void, ClientNotify)(THIS_ REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep, HRESULT hrFault) PURE;
    STDMETHOD_(void, ServerNotify)(THIS_ REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep) PURE;
    STDMETHOD_(void, ServerGetSize)(THIS_ REFGUID uExtent, REFIID riid, HRESULT hrFault, ULONG *pDataSize) PURE;
    STDMETHOD_(void, ServerFillBuffer)(THIS_ REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer, HRESULT hrFault) PURE;
};

typedef IChannelHook *LPCHANNELHOOK;

/* ------------------------------------------------------------ IRunningObjectTable */

#undef  INTERFACE
#define INTERFACE IRunningObjectTable

DECLARE_INTERFACE_(IRunningObjectTable, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(Register)(THIS_ DWORD grfFlags, IUnknown *punkObject, IMoniker *pmkObjectName, DWORD *pdwRegister) PURE;
    STDMETHOD(Revoke)(THIS_ DWORD dwRegister) PURE;
    STDMETHOD(IsRunning)(THIS_ IMoniker *pmkObjectName) PURE;
    STDMETHOD(GetObject)(THIS_ IMoniker *pmkObjectName, IUnknown * *ppunkObject) PURE;
    STDMETHOD(NoteChangeTime)(THIS_ DWORD dwRegister, FILETIME *pfiletime) PURE;
    STDMETHOD(GetTimeOfLastChange)(THIS_ IMoniker *pmkObjectName, FILETIME *pfiletime) PURE;
    STDMETHOD(EnumRunning)(THIS_ IEnumMoniker * *ppenumMoniker) PURE;
};

typedef IRunningObjectTable *LPRUNNINGOBJECTTABLE;

/* ------------------------------------------------------------ IBindCtx */

#undef  INTERFACE
#define INTERFACE IBindCtx

DECLARE_INTERFACE_(IBindCtx, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(RegisterObjectBound)(THIS_ IUnknown *punk) PURE;
    STDMETHOD(RevokeObjectBound)(THIS_ IUnknown *punk) PURE;
    STDMETHOD(ReleaseBoundObjects)(THIS) PURE;
    STDMETHOD(SetBindOptions)(THIS_ BIND_OPTS *pbindopts) PURE;
    STDMETHOD(GetBindOptions)(THIS_ BIND_OPTS *pbindopts) PURE;
    STDMETHOD(GetRunningObjectTable)(THIS_ IRunningObjectTable * *pprot) PURE;
    STDMETHOD(RegisterObjectParam)(THIS_ LPOLESTR pszKey, IUnknown *punk) PURE;
    STDMETHOD(GetObjectParam)(THIS_ LPOLESTR pszKey, IUnknown * *ppunk) PURE;
    STDMETHOD(EnumObjectParam)(THIS_ IEnumString * *ppenum) PURE;
    STDMETHOD(RevokeObjectParam)(THIS_ LPOLESTR pszKey) PURE;
};

typedef IBindCtx *LPBC;

/* ------------------------------------------------------------ IPersistStorage */

#undef  INTERFACE
#define INTERFACE IPersistStorage

DECLARE_INTERFACE_(IPersistStorage, IPersist)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID *pClassID) PURE;
    STDMETHOD(IsDirty)(THIS) PURE;
    STDMETHOD(InitNew)(THIS_ IStorage *pStg) PURE;
    STDMETHOD(Load)(THIS_ IStorage *pStg) PURE;
    STDMETHOD(Save)(THIS_ IStorage *pStgSave, BOOL fSameAsLoad) PURE;
    STDMETHOD(SaveCompleted)(THIS_ IStorage *pStgNew) PURE;
    STDMETHOD(HandsOffStorage)(THIS) PURE;
};

typedef IPersistStorage *LPPERSISTSTORAGE;

/* ------------------------------------------------------------ IPersistStream */

#undef  INTERFACE
#define INTERFACE IPersistStream

DECLARE_INTERFACE_(IPersistStream, IPersist)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID *pClassID) PURE;
    STDMETHOD(IsDirty)(THIS) PURE;
    STDMETHOD(Load)(THIS_ IStream *pStm) PURE;
    STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty) PURE;
    STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize) PURE;
};

typedef IPersistStream *LPPERSISTSTREAM;

#ifdef __cplusplus
}
#endif

#endif /* _OBJIDL_H */
#endif /* AKARI_WCE_OBJIDL_H */
