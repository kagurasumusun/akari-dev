/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RTCAUDIOINTERFACE_H
#define WCE_RTCAUDIOINTERFACE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT HRESULT WINAPI RTC_GlobalSetup() WCE_LINK(RTC_GlobalSetup);
WCE_IMPORT HRESULT WINAPI RTC_GlobalCleanup() WCE_LINK(RTC_GlobalCleanup);
WCE_IMPORT HRESULT WINAPI RTC_OpenPlaybackDevice(DWORD dwWaveID, DWORD dwBuffLen, DWORD dwSampleRate, WORD dwNumChannels, DWORD dwNumBits) WCE_LINK(RTC_OpenPlaybackDevice);
WCE_IMPORT HRESULT WINAPI RTC_StartPlaybackDevice() WCE_LINK(RTC_StartPlaybackDevice);
WCE_IMPORT HRESULT WINAPI RTC_SetPlaybackVolume(DWORD dwVolume) WCE_LINK(RTC_SetPlaybackVolume);
WCE_IMPORT HRESULT WINAPI RTC_GetPlaybackVolume(DWORD* pdwVolume) WCE_LINK(RTC_GetPlaybackVolume);
WCE_IMPORT HRESULT WINAPI RTC_IsPlaying(BOOL* pfPlaying) WCE_LINK(RTC_IsPlaying);
WCE_IMPORT HRESULT WINAPI RTC_OpenRecordDevice(DWORD dwWaveID, DWORD dwBuffLen, DWORD dwSampleRate, WORD dwNumChannels, DWORD dwNumBits) WCE_LINK(RTC_OpenRecordDevice);
WCE_IMPORT HRESULT WINAPI RTC_IsRecording(BOOL* pfRecording) WCE_LINK(RTC_IsRecording);

#ifdef __cplusplus
}
#endif
#endif

