/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_SMS_H
#define WCE_SMS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagSMS_RANGE { DWORD dwMinimum; DWORD dwMaximum; } SMS_RANGE, *PSMS_RANGE, *LPSMS_RANGE;
typedef struct tagSMS_BROADCAST_RANGES { DWORD cbSize; DWORD dwParams; DWORD dwNumRanges; DWORD dwBroadcastMsgLangs; BOOL bAccept; SMS_RANGE smsrBroadcastRanges[]; } SMS_BROADCAST_RANGES, *PSMS_BROADCAST_RANGES, *LPSMS_BROADCAST_RANGES;

#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI SmsClearMessageNotification(const LPCTSTR tszProtocolName) WCE_LINK(SmsClearMessageNotification);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI SmsGetBroadcastMsgRanges(SMS_BROADCAST_RANGES* const psmsbrBroadcastRanges) WCE_LINK(SmsGetBroadcastMsgRanges);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI SmsSetBroadcastMsgRanges(const SMS_BROADCAST_RANGES* const psmsbrBroadcastRanges) WCE_LINK(SmsSetBroadcastMsgRanges);
#endif
#if (_WIN32_WCE >= 0x600)
WCE_IMPORT HRESULT WINAPI SmsGetTime(SYSTEMTIME* const ptsCurrentTime, DWORD* const pdwErrorMargin) WCE_LINK(SmsGetTime);
#endif

#ifdef __cplusplus
}
#endif
#endif

