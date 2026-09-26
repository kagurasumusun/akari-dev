/*
 * ole2.h -- OLE compound document entry points for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * The CE SDK declares the OLE object and stream helpers in this header,
 * separate from objbase.h, even though ole32.dll exports both sets.  The
 * fifteen entry points below were declared in the kit's objbase.h; they are
 * declared here now, where CE puts them, so that #include <ole2.h> finds them.
 *
 * CE's own ole2.h declares 62 prototypes, but only these fifteen are exports of
 * CE's ole32.dll.  The other forty-seven -- the OleCreateEx and OleCreateLink
 * families, DoDragDrop, the OLESTREAM converters, the clipboard functions -- are
 * declared in the header CE inherited from the desktop SDK and are not exported
 * by the CE library.  They are deliberately not declared here: a declaration for
 * a function the target does not have compiles and then fails to link, which is
 * worse than no declaration at all.
 */
#ifndef AKARI_WCE_OLE2_H
#define AKARI_WCE_OLE2_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <objbase.h>

#ifndef _OLE2_
#define _OLE2_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINOLEAPI
#define WINOLEAPI AKARI_DLLIMPORT
#endif

/* ------------------------------------------------------- prototypes */

WINOLEAPI CreateOleAdviseHolder(LPOLEADVISEHOLDER * ppOAHolder);
WINOLEAPI CreateStreamOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease, LPSTREAM * ppstm);
WINOLEAPI GetHGlobalFromStream(LPSTREAM pstm, HGLOBAL * phglobal);
WINOLEAPI OleCreate(REFCLSID rclsid, REFIID riid, DWORD renderopt, LPFORMATETC pFormatEtc, LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID * ppvObj);
WINOLEAPI OleDraw(LPUNKNOWN pUnknown, DWORD dwAspect, HDC hdcDraw, LPCRECT lprcBounds);
WINOLEAPI OleLoadFromStream(LPSTREAM pStm, REFIID iidInterface, LPVOID * ppvObj);
WINOLEAPI OleRun(LPUNKNOWN pUnknown);
WINOLEAPI OleSave(LPPERSISTSTORAGE pPS, LPSTORAGE pStg, BOOL fSameAsLoad);
WINOLEAPI OleSaveToStream(LPPERSISTSTREAM pPStm, LPSTREAM pStm);
WINOLEAPI OleSetContainedObject(LPUNKNOWN pUnknown, BOOL fContained);
WINOLEAPI OleSetMenuDescriptor(HOLEMENU holemenu, HWND hwndFrame, HWND hwndActiveObject, LPOLEINPLACEFRAME lpFrame, LPOLEINPLACEACTIVEOBJECT lpActiveObj);
WINOLEAPI ReadClassStg(LPSTORAGE pStg, CLSID * pclsid);
WINOLEAPI ReadClassStm(LPSTREAM pStm, CLSID * pclsid);
WINOLEAPI WriteClassStg(LPSTORAGE pStg, REFCLSID rclsid);
WINOLEAPI WriteClassStm(LPSTREAM pStm, REFCLSID rclsid);
#ifdef __cplusplus
}
#endif

#endif /* _OLE2_ */
#endif /* AKARI_WCE_OLE2_H */
