/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MMSYSTEM_H
#define WCE_MMSYSTEM_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDRVCONFIGINFOEX { DWORD dwDCISize; LPCWSTR lpszDCISectionName; LPCWSTR lpszDCIAliasName; DWORD dnDevNode; } DRVCONFIGINFOEX, *PDRVCONFIGINFOEX, *LPDRVCONFIGINFOEX;
typedef struct tagDRVCONFIGINFO { DWORD dwDCISize; LPCWSTR lpszDCISectionName; LPCWSTR lpszDCIAliasName; } DRVCONFIGINFO, *PDRVCONFIGINFO, *LPDRVCONFIGINFO;
typedef struct tagWAVEMSG { UINT uMsg; HANDLE hWav; DWORD dwInstance; DWORD dwParam1; DWORD dwParam2; } WAVEMSG, *PWAVEMSG, *LPWAVEMSG;
typedef struct tagWAVEFORMAT { WORD wFormatTag; WORD nChannels; DWORD nSamplesPerSec; DWORD nAvgBytesPerSec; WORD nBlockAlign; } WAVEFORMAT, *PWAVEFORMAT, *LPWAVEFORMAT;
typedef struct tagPCMWAVEFORMAT { WAVEFORMAT wf; WORD wBitsPerSample; } PCMWAVEFORMAT, *PPCMWAVEFORMAT, *LPPCMWAVEFORMAT;
typedef struct tagAUDIOGAINCLASS { DWORD dwPriority; DWORD dwRelativeGain; } AUDIOGAINCLASS, *PAUDIOGAINCLASS, *LPAUDIOGAINCLASS;
typedef struct tagSTREAMPROPS { DWORD dwClassID; DWORD dwFlags; } STREAMPROPS, *PSTREAMPROPS, *LPSTREAMPROPS;
typedef struct tagAUDIODISCONTINUITY { DWORD dwMask; DWORD dwApp; DWORD dwSwMixer; DWORD dwDriver; } AUDIODISCONTINUITY, *PAUDIODISCONTINUITY, *LPAUDIODISCONTINUITY;
typedef struct tagWAVEFORMATEX { WORD wFormatTag; WORD nChannels; DWORD nSamplesPerSec; DWORD nAvgBytesPerSec; WORD nBlockAlign; WORD wBitsPerSample; WORD cbSize; } WAVEFORMATEX, *PWAVEFORMATEX, *LPWAVEFORMATEX;
typedef struct tagMIDIEVENT { DWORD dwDeltaTime; DWORD dwStreamID; DWORD dwEvent; DWORD dwParms[1]; } MIDIEVENT, *PMIDIEVENT, *LPMIDIEVENT;
typedef struct tagMIDISTRMBUFFVER { DWORD dwVersion; DWORD dwMid; DWORD dwOEMVersion; } MIDISTRMBUFFVER, *PMIDISTRMBUFFVER, *LPMIDISTRMBUFFVER;
typedef struct tagMIDIPROPTIMEDIV { DWORD cbStruct; DWORD dwTimeDiv; } MIDIPROPTIMEDIV, *PMIDIPROPTIMEDIV, *LPMIDIPROPTIMEDIV;
typedef struct tagMIDIPROPTEMPO { DWORD cbStruct; DWORD dwTempo; } MIDIPROPTEMPO, *PMIDIPROPTEMPO, *LPMIDIPROPTEMPO;
typedef struct tagMIXERCONTROLDETAILS_BOOLEAN { LONG fValue; } MIXERCONTROLDETAILS_BOOLEAN, *PMIXERCONTROLDETAILS_BOOLEAN, *LPMIXERCONTROLDETAILS_BOOLEAN;
typedef struct tagMIXERCONTROLDETAILS_SIGNED { LONG lValue; } MIXERCONTROLDETAILS_SIGNED, *PMIXERCONTROLDETAILS_SIGNED, *LPMIXERCONTROLDETAILS_SIGNED;
typedef struct tagMIXERCONTROLDETAILS_UNSIGNED { DWORD dwValue; } MIXERCONTROLDETAILS_UNSIGNED, *PMIXERCONTROLDETAILS_UNSIGNED, *LPMIXERCONTROLDETAILS_UNSIGNED;
typedef struct tagTIMECAPS { UINT wPeriodMin; UINT wPeriodMax; } TIMECAPS, *PTIMECAPS, *LPTIMECAPS;

WCE_IMPORT BOOL WINAPI sndPlaySoundW(LPCWSTR lpszSoundName, UINT fuSound) WCE_LINK(sndPlaySoundW);
WCE_IMPORT BOOL WINAPI PlaySoundA(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound) WCE_LINK(PlaySoundA);
WCE_IMPORT BOOL WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound) WCE_LINK(PlaySoundW);
WCE_IMPORT UINT WINAPI waveOutGetNumDevs(void) WCE_LINK(waveOutGetNumDevs);
WCE_IMPORT UINT WINAPI waveInGetNumDevs(void) WCE_LINK(waveInGetNumDevs);
WCE_IMPORT UINT WINAPI midiOutGetNumDevs(void) WCE_LINK(midiOutGetNumDevs);
WCE_IMPORT UINT WINAPI midiInGetNumDevs(void) WCE_LINK(midiInGetNumDevs);
WCE_IMPORT UINT WINAPI mixerGetNumDevs(void) WCE_LINK(mixerGetNumDevs);
WCE_IMPORT DWORD WINAPI timeGetTime(void) WCE_LINK(timeGetTime);
WCE_IMPORT DWORD WINAPI timeGetTimeSinceInterrupt(void) WCE_LINK(timeGetTimeSinceInterrupt);
WCE_IMPORT DWORD WINAPI timeGetHardwareFrequency(void) WCE_LINK(timeGetHardwareFrequency);

#define sndPlaySound sndPlaySoundW
#define PlaySound PlaySoundW
#ifdef __cplusplus
}
#endif
#endif

