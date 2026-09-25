/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_OLE2_H
#define WCE_OLE2_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI CreateDataAdviseHolder(LPDATAADVISEHOLDER FAR* ppDAHolder) WCE_LINK(CreateDataAdviseHolder);
#endif
WCE_IMPORT HRESULT WINAPI ReadClassStg(LPSTORAGE pStg, CLSID FAR* pclsid) WCE_LINK(ReadClassStg);
WCE_IMPORT HRESULT WINAPI WriteClassStg(LPSTORAGE pStg, REFCLSID rclsid) WCE_LINK(WriteClassStg);
WCE_IMPORT HRESULT WINAPI ReadClassStm(LPSTREAM pStm, CLSID FAR* pclsid) WCE_LINK(ReadClassStm);
WCE_IMPORT HRESULT WINAPI WriteClassStm(LPSTREAM pStm, REFCLSID rclsid) WCE_LINK(WriteClassStm);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI OleInitialize(LPVOID pvReserved) WCE_LINK(OleInitialize);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI OleQueryLinkFromData(LPDATAOBJECT pSrcDataObject) WCE_LINK(OleQueryLinkFromData);
#endif
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI OleQueryCreateFromData(LPDATAOBJECT pSrcDataObject) WCE_LINK(OleQueryCreateFromData);
#endif
WCE_IMPORT HRESULT WINAPI OleCreate(REFCLSID rclsid, REFIID riid, DWORD renderopt, LPFORMATETC pFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreate);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI OleCreateFromData(LPDATAOBJECT pSrcDataObj, REFIID riid, DWORD renderopt, LPFORMATETC pFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreateFromData);
#endif
WCE_IMPORT HRESULT WINAPI OleCreateLinkFromData(LPDATAOBJECT pSrcDataObj, REFIID riid, DWORD renderopt, LPFORMATETC pFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreateLinkFromData);
WCE_IMPORT HRESULT WINAPI OleCreateStaticFromData(LPDATAOBJECT pSrcDataObj, REFIID iid, DWORD renderopt, LPFORMATETC pFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreateStaticFromData);
WCE_IMPORT HRESULT WINAPI OleCreateLink(LPMONIKER pmkLinkSrc, REFIID riid, DWORD renderopt, LPFORMATETC lpFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreateLink);
WCE_IMPORT HRESULT WINAPI OleCreateLinkToFile(LPCOLESTR lpszFileName, REFIID riid, DWORD renderopt, LPFORMATETC lpFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreateLinkToFile);
WCE_IMPORT HRESULT WINAPI OleCreateFromFile(REFCLSID rclsid, LPCOLESTR lpszFileName, REFIID riid, DWORD renderopt, LPFORMATETC lpFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID FAR* ppvObj) WCE_LINK(OleCreateFromFile);
WCE_IMPORT HRESULT WINAPI OleLoad(LPSTORAGE pStg, REFIID riid, LPOLECLIENTSITE pClientSite, LPVOID FAR* ppvObj) WCE_LINK(OleLoad);
WCE_IMPORT HRESULT WINAPI OleSave(LPPERSISTSTORAGE pPS, LPSTORAGE pStg, BOOL fSameAsLoad) WCE_LINK(OleSave);
WCE_IMPORT HRESULT WINAPI OleLoadFromStream(LPSTREAM pStm, REFIID iidInterface, LPVOID FAR* ppvObj) WCE_LINK(OleLoadFromStream);
WCE_IMPORT HRESULT WINAPI OleSaveToStream(LPPERSISTSTREAM pPStm, LPSTREAM pStm) WCE_LINK(OleSaveToStream);
WCE_IMPORT HRESULT WINAPI OleSetContainedObject(LPUNKNOWN pUnknown, BOOL fContained) WCE_LINK(OleSetContainedObject);
WCE_IMPORT HRESULT WINAPI OleNoteObjectVisible(LPUNKNOWN pUnknown, BOOL fVisible) WCE_LINK(OleNoteObjectVisible);
WCE_IMPORT HRESULT WINAPI RegisterDragDrop(HWND hwnd, LPDROPTARGET pDropTarget) WCE_LINK(RegisterDragDrop);
WCE_IMPORT HRESULT WINAPI RevokeDragDrop(HWND hwnd) WCE_LINK(RevokeDragDrop);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT HRESULT WINAPI DoDragDrop(LPDATAOBJECT pDataObj, LPDROPSOURCE pDropSource, DWORD dwOKEffects, LPDWORD pdwEffect) WCE_LINK(DoDragDrop);
#endif
WCE_IMPORT HRESULT WINAPI OleSetClipboard(LPDATAOBJECT pDataObj) WCE_LINK(OleSetClipboard);
WCE_IMPORT HRESULT WINAPI OleGetClipboard(LPDATAOBJECT FAR* ppDataObj) WCE_LINK(OleGetClipboard);
WCE_IMPORT HRESULT WINAPI OleFlushClipboard(void) WCE_LINK(OleFlushClipboard);
WCE_IMPORT HRESULT WINAPI OleIsCurrentClipboard(LPDATAOBJECT pDataObj) WCE_LINK(OleIsCurrentClipboard);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI OleTranslateAccelerator(LPOLEINPLACEFRAME lpFrame, LPOLEINPLACEFRAMEINFO lpFrameInfo, LPMSG lpmsg) WCE_LINK(OleTranslateAccelerator);
#endif
WCE_IMPORT HRESULT WINAPI OleDraw(LPUNKNOWN pUnknown, DWORD dwAspect, HDC hdcDraw, LPCRECT lprcBounds) WCE_LINK(OleDraw);
WCE_IMPORT HRESULT WINAPI OleRun(LPUNKNOWN pUnknown) WCE_LINK(OleRun);
WCE_IMPORT HRESULT WINAPI OleLockRunning(LPUNKNOWN pUnknown, BOOL fLock, BOOL fLastUnlockCloses) WCE_LINK(OleLockRunning);
WCE_IMPORT HRESULT WINAPI CreateOleAdviseHolder(LPOLEADVISEHOLDER FAR* ppOAHolder) WCE_LINK(CreateOleAdviseHolder);
WCE_IMPORT HRESULT WINAPI OleCreateDefaultHandler(REFCLSID clsid, LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR* lplpObj) WCE_LINK(OleCreateDefaultHandler);
WCE_IMPORT HRESULT WINAPI OleCreateEmbeddingHelper(REFCLSID clsid, LPUNKNOWN pUnkOuter, DWORD flags, LPCLASSFACTORY pCF, REFIID riid, LPVOID FAR* lplpObj) WCE_LINK(OleCreateEmbeddingHelper);
WCE_IMPORT HRESULT WINAPI OleRegGetUserType(REFCLSID clsid, DWORD dwFormOfType, LPOLESTR FAR* pszUserType) WCE_LINK(OleRegGetUserType);
WCE_IMPORT HRESULT WINAPI OleRegGetMiscStatus(REFCLSID clsid, DWORD dwAspect, DWORD FAR* pdwStatus) WCE_LINK(OleRegGetMiscStatus);
WCE_IMPORT HRESULT WINAPI OleRegEnumFormatEtc(REFCLSID clsid, DWORD dwDirection, LPENUMFORMATETC FAR* ppenum) WCE_LINK(OleRegEnumFormatEtc);
WCE_IMPORT HRESULT WINAPI OleRegEnumVerbs(REFCLSID clsid, LPENUMOLEVERB FAR* ppenum) WCE_LINK(OleRegEnumVerbs);
WCE_IMPORT HRESULT WINAPI OleConvertIStorageToOLESTREAM(LPSTORAGE pstg, LPOLESTREAM lpolestream) WCE_LINK(OleConvertIStorageToOLESTREAM);
WCE_IMPORT HRESULT WINAPI GetHGlobalFromILockBytes(LPLOCKBYTES plkbyt, HGLOBAL FAR* phglobal) WCE_LINK(GetHGlobalFromILockBytes);
#if (_WIN32_WCE >= 0x420 && _WIN32_WCE < 0x600)
WCE_IMPORT HRESULT WINAPI CreateILockBytesOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease, LPLOCKBYTES FAR* pplkbyt) WCE_LINK(CreateILockBytesOnHGlobal);
#endif
WCE_IMPORT HRESULT WINAPI GetHGlobalFromStream(LPSTREAM pstm, HGLOBAL FAR* phglobal) WCE_LINK(GetHGlobalFromStream);
WCE_IMPORT HRESULT WINAPI CreateStreamOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease, LPSTREAM FAR* ppstm) WCE_LINK(CreateStreamOnHGlobal);
WCE_IMPORT HRESULT WINAPI OleDoAutoConvert(LPSTORAGE pStg, LPCLSID pClsidNew) WCE_LINK(OleDoAutoConvert);
WCE_IMPORT HRESULT WINAPI OleGetAutoConvert(REFCLSID clsidOld, LPCLSID pClsidNew) WCE_LINK(OleGetAutoConvert);
WCE_IMPORT HRESULT WINAPI OleSetAutoConvert(REFCLSID clsidOld, REFCLSID clsidNew) WCE_LINK(OleSetAutoConvert);
WCE_IMPORT HRESULT WINAPI GetConvertStg(LPSTORAGE pStg) WCE_LINK(GetConvertStg);
WCE_IMPORT HRESULT WINAPI SetConvertStg(LPSTORAGE pStg, BOOL fConvert) WCE_LINK(SetConvertStg);

#ifdef __cplusplus
}
#endif
#endif

