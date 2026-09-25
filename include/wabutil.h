/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WABUTIL_H
#define WCE_WABUTIL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI HrAllocAdviseSink(LPNOTIFCALLBACK lpfnCallback, LPVOID lpvContext, LPMAPIADVISESINK FAR *lppAdviseSink) WCE_LINK(HrAllocAdviseSink);
WCE_IMPORT HRESULT WINAPI HrThisThreadAdviseSink(LPMAPIADVISESINK lpAdviseSink, LPMAPIADVISESINK FAR *lppAdviseSink) WCE_LINK(HrThisThreadAdviseSink);
WCE_IMPORT HRESULT WINAPI HrDispatchNotifications(ULONG ulFlags) WCE_LINK(HrDispatchNotifications);
WCE_IMPORT HRESULT WINAPI BuildDisplayTable(LPALLOCATEBUFFER lpAllocateBuffer, LPALLOCATEMORE lpAllocateMore, LPFREEBUFFER lpFreeBuffer, LPMALLOC lpMalloc, HINSTANCE hInstance, UINT cPages, LPDTPAGE lpPage, ULONG ulFlags, LPMAPITABLE * lppTable, LPTABLEDATA * lppTblData) WCE_LINK(BuildDisplayTable);
WCE_IMPORT HRESULT WINAPI HrGetOneProp(LPMAPIPROP lpMapiProp, ULONG ulPropTag, LPSPropValue FAR *lppProp) WCE_LINK(HrGetOneProp);
WCE_IMPORT HRESULT WINAPI HrSetOneProp(LPMAPIPROP lpMapiProp, LPSPropValue lpProp) WCE_LINK(HrSetOneProp);
WCE_IMPORT HRESULT WINAPI HrQueryAllRows(LPMAPITABLE lpTable, LPSPropTagArray lpPropTags, LPSRestriction lpRestriction, LPSSortOrderSet lpSortOrderSet, LONG crowsMax, LPSRowSet FAR *lppRows) WCE_LINK(HrQueryAllRows);
WCE_IMPORT HRESULT WINAPI WrapStoreEntryID(ULONG ulFlags, LPTSTR lpszDLLName, ULONG cbOrigEntry, LPENTRYID lpOrigEntry, ULONG *lpcbWrappedEntry, LPENTRYID *lppWrappedEntry) WCE_LINK(WrapStoreEntryID);

#ifdef __cplusplus
}
#endif
#endif

