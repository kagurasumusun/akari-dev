/* Multimedia timers. Original text. Exported by mmtimer.dll.
 *
 * This header covers only the timer surface of the multimedia API; the audio and
 * joystick families live in separate modules on Windows CE.
 */
#ifndef AKARI_WCE_MMSYSTEM_H
#define AKARI_WCE_MMSYSTEM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"

typedef UINT MMRESULT;

#define TIMERR_BASE       96
#define TIMERR_NOERROR    (0)
#define TIMERR_NOCANDO    (TIMERR_BASE + 1)
#define TIMERR_STRUCT     (TIMERR_BASE + 33)

#define TIME_PERIODIC     0x0001
#define TIME_ONESHOT      0x0000
#define TIME_CALLBACK_FUNCTION 0x0000
#define TIME_CALLBACK_EVENT_SET 0x0010
#define TIME_CALLBACK_EVENT_PULSE 0x0020

typedef struct akari_TIMECAPS {
    UINT wPeriodMin;
    UINT wPeriodMax;
} TIMECAPS, *PTIMECAPS, *LPTIMECAPS;

typedef void (CALLBACK TIMECALLBACK)(UINT uTimerID, UINT uMsg, DWORD dwUser,
    DWORD dw1, DWORD dw2);
typedef TIMECALLBACK *LPTIMECALLBACK;

MMTIMERAPI MMRESULT WINAPI timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc);
MMTIMERAPI MMRESULT WINAPI timeBeginPeriod(UINT uPeriod);
MMTIMERAPI MMRESULT WINAPI timeEndPeriod(UINT uPeriod);
MMTIMERAPI DWORD WINAPI timeGetTime(VOID);
MMTIMERAPI DWORD WINAPI timeGetTimeSinceInterrupt(VOID);
MMTIMERAPI DWORD WINAPI timeGetHardwareFrequency(VOID);
MMTIMERAPI MMRESULT WINAPI timeSetEvent(UINT uDelay, UINT uResolution,
    LPTIMECALLBACK fptc, DWORD dwUser, UINT fuEvent);
MMTIMERAPI MMRESULT WINAPI timeKillEvent(UINT uID);

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_MMSYSTEM_H */
