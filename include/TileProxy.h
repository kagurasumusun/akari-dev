/*
 * TileProxy.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: TileProxy.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_TILEPROXY_H
#define AKARI_TILEPROXY_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee487455 TPGetViewVisBounds: print `HRESULT TPGetViewVisBounds(
HANDLE hTileProxy,
RECT* pRect);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetViewVisBounds(HANDLE hTileProxy, RECT *pRect) AKARI_CE_NAME(TPGetViewVisBounds);

/* ee487466 TPChangeZoomScale: print `HRESULT TPChangeZoomScale(
HANDLE hTileProxy,
float fScale);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPChangeZoomScale(HANDLE hTileProxy, float fScale) AKARI_CE_NAME(TPChangeZoomScale);

/* ee487469 TPRedraw: print `HRESULT TPRedraw(
HANDLE hTileProxy);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPRedraw(HANDLE hTileProxy) AKARI_CE_NAME(TPRedraw);

/* ee487471 TPWindowToPage: print `HRESULT TPWindowToPage(
HANDLE hTileProxy,
INT32* px,
INT32* py);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPWindowToPage(HANDLE hTileProxy, INT32 *px, INT32 *py) AKARI_CE_NAME(TPWindowToPage);

/* ee487483 TPGetViewPosition: print `HRESULT TPGetViewPosition(
HANDLE hTileProxy,
float* px,
float* py);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetViewPosition(HANDLE hTileProxy, float *px, float *py) AKARI_CE_NAME(TPGetViewPosition);

/* ee487486 TPChangeZoom: print `HRESULT TPChangeZoom(
HANDLE hTileProxy,
POINT ptHitPoint,
RECT* pZoomRect,
BOOL bAllowVerticalZoom);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPChangeZoom(HANDLE hTileProxy, POINT ptHitPoint, RECT *pZoomRect, BOOL bAllowVerticalZoom) AKARI_CE_NAME(TPChangeZoom);

/* ee487487 TPGetViewDocSize: print `HRESULT TPGetViewDocSize(
HANDLE hTileProxy,
SIZE* pDocSize);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetViewDocSize(HANDLE hTileProxy, SIZE *pDocSize) AKARI_CE_NAME(TPGetViewDocSize);

/* ee487507 TPGetWaitTimeout: print `HRESULT TPGetWaitTimeout(
HANDLE hTileProxy,
UINT32* piTimeout);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetWaitTimeout(HANDLE hTileProxy, UINT32 *piTimeout) AKARI_CE_NAME(TPGetWaitTimeout);

/* ee487508 TPGetHostWindow: print `HRESULT TPGetHostWindow(
HANDLE hTileProxy,
HWND* phWnd);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetHostWindow(HANDLE hTileProxy, HWND *phWnd) AKARI_CE_NAME(TPGetHostWindow);

/* ee487553 TPChangePos: print `HRESULT TPChangePos(
HANDLE hTileProxy,
INT32 dxPage,
INT32 dyPage);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPChangePos(HANDLE hTileProxy, INT32 dxPage, INT32 dyPage) AKARI_CE_NAME(TPChangePos);

/* ee487559 TPForwardWindowInput: print `HRESULT TPForwardWindowInput(
HANDLE hTileProxy,
UINT32 msg,
POINT pt);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPForwardWindowInput(HANDLE hTileProxy, UINT32 msg, POINT pt) AKARI_CE_NAME(TPForwardWindowInput);

/* ee487571 TPSetView: print `HRESULT TPSetView(
HANDLE hTileProxy,
POINT ptScrollPosition,
float fZoomFactor);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPSetView(HANDLE hTileProxy, POINT ptScrollPosition, float fZoomFactor) AKARI_CE_NAME(TPSetView);

/* ee487584 TPShowTileWindow: print `HRESULT TPShowTileWindow(
__in HANDLE hTileProxy,
__in BOOL bShow);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPShowTileWindow(HANDLE hTileProxy, BOOL bShow) AKARI_CE_NAME(TPShowTileWindow);

/* ee487611 TPGetWaitEvent: print `HRESULT TPGetWaitEvent(
HANDLE hTileProxy,
HANDLE* phEvent)`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetWaitEvent(HANDLE hTileProxy, HANDLE *phEvent) AKARI_CE_NAME(TPGetWaitEvent);

/* ee487617 TPGetIsChanging: print `HRESULT TPGetIsChanging(
HANDLE hTileProxy,
BOOL* pIsChanging);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetIsChanging(HANDLE hTileProxy, BOOL *pIsChanging) AKARI_CE_NAME(TPGetIsChanging);

/* ee487648 TPSetHtmlWindow: print `HRESULT TPSetHtmlWindow(
HANDLE hTileProxy,
HWND hWnd);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPSetHtmlWindow(HANDLE hTileProxy, HWND hWnd) AKARI_CE_NAME(TPSetHtmlWindow);

/* ee487667 TPSetPageChanged: print `HRESULT TPSetPageChanged(
HANDLE hTileProxy);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPSetPageChanged(HANDLE hTileProxy) AKARI_CE_NAME(TPSetPageChanged);

/* ee487669 ReleaseTileProxy: print `HRESULT ReleaseTileProxy(
HANDLE hTileProxy);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT ReleaseTileProxy(HANDLE hTileProxy) AKARI_CE_NAME(ReleaseTileProxy);

/* ee487791 TPSetViewPosition: print `HRESULT TPSetViewPosition(
HANDLE hTileProxy,
float x,
float y);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPSetViewPosition(HANDLE hTileProxy, float x, float y) AKARI_CE_NAME(TPSetViewPosition);

/* ee487837 TPUpdate: print `HRESULT TPUpdate(
HANDLE hTileProxy);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPUpdate(HANDLE hTileProxy) AKARI_CE_NAME(TPUpdate);

/* ee487843 TPGetViewScale: print `HRESULT TPGetViewScale(
HANDLE hTileProxy,
float* pViewscale);`
 * (Windows Embedded CE 6.0 R3; Link Library: tileengine.dll) */
AKARI_CE_IMPORT HRESULT TPGetViewScale(HANDLE hTileProxy, float *pViewscale) AKARI_CE_NAME(TPGetViewScale);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_TILEPROXY_H */
