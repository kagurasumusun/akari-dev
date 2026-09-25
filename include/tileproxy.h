/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_TILEPROXY_H
#define WCE_TILEPROXY_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI CreateTileProxy(HWND hParentWnd, HWND hHtmlWnd, WNDPROC pfnWndProc, LPVOID pCreateParam, HANDLE* phTileProxy) WCE_LINK(CreateTileProxy);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI ReleaseTileProxy(HANDLE hTileProxy) WCE_LINK(ReleaseTileProxy);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetWaitEvent(HANDLE hTileProxy, HANDLE* phEvent) WCE_LINK(TPGetWaitEvent);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPSetHtmlWindow(HANDLE hTileProxy, HWND hWnd) WCE_LINK(TPSetHtmlWindow);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPUpdate(HANDLE hTileProxy) WCE_LINK(TPUpdate);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetIsChanging(HANDLE hTileProxy, BOOL* pIsChanging) WCE_LINK(TPGetIsChanging);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPChangeZoom(HANDLE hTileProxy, POINT ptHitPoint, RECT* pZoomRect, BOOL bAllowVerticalZoom) WCE_LINK(TPChangeZoom);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPChangeZoomScale(HANDLE hTileProxy, float fScale) WCE_LINK(TPChangeZoomScale);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetViewDocSize(HANDLE hTileProxy, SIZE* pDocSize) WCE_LINK(TPGetViewDocSize);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetViewPosition(HANDLE hTileProxy, float* px, float* py) WCE_LINK(TPGetViewPosition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPSetViewPosition(HANDLE hTileProxy, float x, float y) WCE_LINK(TPSetViewPosition);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetViewScale(HANDLE hTileProxy, float* pViewscale) WCE_LINK(TPGetViewScale);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetViewVisBounds(HANDLE hTileProxy, RECT* pRect) WCE_LINK(TPGetViewVisBounds);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPRedraw(HANDLE hTileProxy) WCE_LINK(TPRedraw);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPShowTileWindow(HANDLE hTileProxy, BOOL bShow) WCE_LINK(TPShowTileWindow);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPSetView(HANDLE hTileProxy, POINT ptScrollPosition, float fZoomFactor) WCE_LINK(TPSetView);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPGetHostWindow(HANDLE hTileProxy, HWND* phWnd) WCE_LINK(TPGetHostWindow);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI TPSetPageChanged(HANDLE hTileProxy) WCE_LINK(TPSetPageChanged);
#endif

#ifdef __cplusplus
}
#endif
#endif

