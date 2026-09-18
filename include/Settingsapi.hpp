/*
 * Settingsapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: settingsapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_SETTINGSAPI_H
#define AKARI_SETTINGSAPI_H

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


/* ee499871 PHSetting: page print
 * enum PHSetting { phsDoNotDisturb = 0, phsCallForwarding, phsAutoDial, phsBlockCallerId, phsMissedCalls, phsIncomingCalls, phsOutgoingCalls, phsGalFilt
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum PHSetting {
    phsDoNotDisturb = 0,
    phsCallForwarding,
    phsAutoDial,
    phsBlockCallerId,
    phsMissedCalls,
    phsIncomingCalls,
    phsOutgoingCalls,
    phsGalFilterType,
    phsContactFilterType,
    phsDeviceLocked,
    phsAutoDialRulesAvailability,
    phsPhoneAppStatus,
    phsDisableAGC,
    phsLockPhoneAfterUpdatingPIN
} PHSetting;

/* ee500378 PHVolumeSetting: page print
 * enum PHVolumeSetting { phvsSpeakerVolume, phvsRingerVolume, phvsHandsetVolume, phvsMicrophoneVolume, };
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum PHVolumeSetting {
    phvsSpeakerVolume,
    phvsRingerVolume,
    phvsHandsetVolume,
    phvsMicrophoneVolume
} PHVolumeSetting;

/* ee501527 PHActiveVolumeMode: page print
 * enum PHActiveVolumeMode { SpeakerVolumeMode = 0, RingerVolumeMode, LastVolumeMode, };
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum PHActiveVolumeMode {
    SpeakerVolumeMode = 0,
    RingerVolumeMode,
    LastVolumeMode
} PHActiveVolumeMode;

/* ee501567 AuthenticationResult_e: page print
 * enum AuthenticationResult_e { AuthCanceled = 0, AuthInProgress, AuthSucceeded, };
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum AuthenticationResult_e {
    AuthCanceled = 0,
    AuthInProgress,
    AuthSucceeded
} AuthenticationResult_e;


/* ee500686 PH_AUTHENTICATE_USER_PARAMETERS: page print
 * typedef struct tagPH_AUTHENTICATE_USER_PARAMETERS { UINT StructSize; HWND NotificationWindow; UINT NotificationMessage; AuthenticationResult_e Result;
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef struct tagPH_AUTHENTICATE_USER_PARAMETERS {
    UINT StructSize;
    HWND NotificationWindow;
    UINT NotificationMessage;
    AuthenticationResult_e Result;
} PH_AUTHENTICATE_USER_PARAMETERS;


/* ee499873 PHGetVolumeSetting: print `DWORD PHGetVolumeSetting(
PHVolumeSetting Setting
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT DWORD PHGetVolumeSetting(PHVolumeSetting Setting) AKARI_CE_NAME(PHGetVolumeSetting);

/* ee499875 PHSetValue: print `HRESULT PHSetValue(
PHSetting Setting,
DWORD Value
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHSetValue(PHSetting Setting, DWORD Value) AKARI_CE_NAME(PHSetValue);

/* ee500423 PHReadPIN: print `HRESULT PHReadPIN(
WCHAR* pPinBuffer,
int BufferLength
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHReadPIN(WCHAR *pPinBuffer, int BufferLength) AKARI_CE_NAME(PHReadPIN);

/* ee500680 PHSetActiveVolume: print `HRESULT PHSetActiveVolume (
PHActiveVolumeMode VolumeMode
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHSetActiveVolume(PHActiveVolumeMode VolumeMode) AKARI_CE_NAME(PHSetActiveVolume);

/* ee500995 PHAuthenticateUser: print `HRESULT PHAuthenticateUser(
PH_AUTHENTICATE_USER_PARAMETERS* pParams
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHAuthenticateUser(PH_AUTHENTICATE_USER_PARAMETERS *pParams) AKARI_CE_NAME(PHAuthenticateUser);

/* ee501008 PHWritePIN: print `HRESULT PHWritePIN(
WCHAR* pPinString
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHWritePIN(WCHAR *pPinString) AKARI_CE_NAME(PHWritePIN);

/* ee501292 PHSetVolume: print `HRESULT PHSetVolume(
PHVolumeSetting Setting,
DWORD Value
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHSetVolume(PHVolumeSetting Setting, DWORD Value) AKARI_CE_NAME(PHSetVolume);

/* ee501360 PHCancelAuthenticationRequest: print `HRESULT PHCancelAuthenticationRequest(
HWND hwnd
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HRESULT PHCancelAuthenticationRequest(HWND hwnd) AKARI_CE_NAME(PHCancelAuthenticationRequest);

/* ee501650 PHGetSetting: print `DWORD PHGetSetting(
PHSetting Setting
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT DWORD PHGetSetting(PHSetting Setting) AKARI_CE_NAME(PHGetSetting);

/* ee501700 PHGetActiveVolume: print `PHActiveVolumeMode PHGetActiveVolume ( void );`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT PHActiveVolumeMode PHGetActiveVolume(void) AKARI_CE_NAME(PHGetActiveVolume);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_SETTINGSAPI_H */
