/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_IMGUTIL_H
#define WCE_IMGUTIL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI GetMaxMIMEIDBytes(ULONG* pnMaxBytes) WCE_LINK(GetMaxMIMEIDBytes);
WCE_IMPORT HRESULT WINAPI IdentifyMIMEType(const BYTE* pbBytes, ULONG nBytes, UINT* pnFormat) WCE_LINK(IdentifyMIMEType);
WCE_IMPORT HRESULT WINAPI ComputeInvCMAP(const RGBQUAD *pRGBColors, ULONG nColors, BYTE *pInvTable, ULONG cbTable) WCE_LINK(ComputeInvCMAP);
WCE_IMPORT HRESULT WINAPI DitherTo8(BYTE * pDestBits, LONG nDestPitch, BYTE * pSrcBits, LONG nSrcPitch, REFGUID bfidSrc, RGBQUAD * prgbDestColors, RGBQUAD * prgbSrcColors, BYTE * pbDestInvMap, LONG x, LONG y, LONG cx, LONG cy, LONG lDestTrans, LONG lSrcTrans) WCE_LINK(DitherTo8);

#ifdef __cplusplus
}
#endif
#endif

