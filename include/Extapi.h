/*
 * Extapi.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: extapi.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_EXTAPI_H
#define AKARI_EXTAPI_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Tapi.h"   /* HLINE */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee496938 LINEGENERALINFO: page print
 * typedef struct linegeneralinfo_tag { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwManufacturerSize; DWORD dwManufacturerOffset; DW
 * (Windows CE 3.0 and later) */
typedef struct linegeneralinfo_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwManufacturerSize;
    DWORD dwManufacturerOffset;
    DWORD dwModelSize;
    DWORD dwModelOffset;
    DWORD dwRevisionSize;
    DWORD dwRevisionOffset;
    DWORD dwSerialNumberSize;
    DWORD dwSerialNumberOffset;
    DWORD dwSubscriberNumberSize;
    DWORD dwSubscriberNumberOffset;
} LINEGENERALINFO, * LPLINEGENERALINFO;

/* ee497834 LINEOPERATORSTATUS: page print
 * typedef struct lineoperatorstatus_tag { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwPreferredCount; DWORD dwPreferredSize; DWORD 
 * (Windows Embedded CE 6.0 and later) */
typedef struct lineoperatorstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwPreferredCount;
    DWORD dwPreferredSize;
    DWORD dwPreferredOffset;
    DWORD dwAvailableCount;
    DWORD dwAvailableSize;
    DWORD dwAvailableOffset;
} LINEOPERATORSTATUS, * LPLINEOPERATORSTATUS;


/* ee496899 lineGetHSCSDState: print `LONG WINAPI lineGetHSCSDState(
HLINE hLine,
LPDWORD lpdwChannelsIn,
LPDWORD lpdwMaxChannelsIn,
LPDWORD lpdwChannelCodings,
LPDWORD lpdwAirInterfaceRate
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetHSCSDState(HLINE hLine, LPDWORD lpdwChannelsIn, LPDWORD lpdwMaxChannelsIn, LPDWORD lpdwChannelCodings, LPDWORD lpdwAirInterfaceRate) AKARI_CE_NAME(lineGetHSCSDState);

/* ee496925 lineGetRegisterStatus: print `LONG WINAPI lineGetRegisterStatus(
HLINE hLine,
LPDWORD lpdwRegisterStatus
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetRegisterStatus(HLINE hLine, LPDWORD lpdwRegisterStatus) AKARI_CE_NAME(lineGetRegisterStatus);

/* ee496946 lineGetUSSD: print `LONG WINAPI lineGetUSSD(
HLINE hLine,
DWORD dwID,
LPBYTE lpbUSSD,
DWORD dwUSSDSize,
LPDWORD lpdwFlags
);`
 * (Windows Embedded CE 6.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetUSSD(HLINE hLine, DWORD dwID, LPBYTE lpbUSSD, DWORD dwUSSDSize, LPDWORD lpdwFlags) AKARI_CE_NAME(lineGetUSSD);

/* ee497029 lineSetSendCallerIDState: print `LONG WINAPI lineSetSendCallerIDState(
HLINE hLine,
DWORD dwState
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetSendCallerIDState(HLINE hLine, DWORD dwState) AKARI_CE_NAME(lineSetSendCallerIDState);

/* ee497124 lineGetCurrentSystemType: print `HRESULT lineGetCurrentSystemType (
HLINE hLine,
LPDWORD lpdwCurrentSystemType
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT lineGetCurrentSystemType(HLINE hLine, LPDWORD lpdwCurrentSystemType) AKARI_CE_NAME(lineGetCurrentSystemType);

/* ee497171 lineGetGPRSClass: print `LONG WINAPI lineGetGPRSClass(
HLINE hLine,
LPDWORD lpdwClass
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetGPRSClass(HLINE hLine, LPDWORD lpdwClass) AKARI_CE_NAME(lineGetGPRSClass);

/* ee497245 lineGetHSCSDCaps: print `LONG WINAPI lineGetHSCSDCaps(
HLINE hLine,
LPDWORD lpdwClass,
LPDWORD lpdwChannelsIn,
LPDWORD lpdwChannelsOut,
LPDWORD lpdwChannelsSum,
LPDWORD lpdwChannelCodings
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetHSCSDCaps(HLINE hLine, LPDWORD lpdwClass, LPDWORD lpdwChannelsIn, LPDWORD lpdwChannelsOut, LPDWORD lpdwChannelsSum, LPDWORD lpdwChannelCodings) AKARI_CE_NAME(lineGetHSCSDCaps);

/* ee497249 lineGetCurrentHSCSDStatus: print `LONG WINAPI lineGetCurrentHSCSDStatus(
HLINE hLine,
LPDWORD lpdwChannelsIn,
LPDWORD lpdwChannelsOut,
LPDWORD lpdwChannelCoding,
LPDWORD lpdwAirInterfaceRate
);`
 * (Windows Embedded CE 6.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetCurrentHSCSDStatus(HLINE hLine, LPDWORD lpdwChannelsIn, LPDWORD lpdwChannelsOut, LPDWORD lpdwChannelCoding, LPDWORD lpdwAirInterfaceRate) AKARI_CE_NAME(lineGetCurrentHSCSDStatus);

/* ee497307 lineGetCallBarringState: print `LONG WINAPI lineGetCallBarringState(
HLINE hLine,
DWORD dwMode,
LPDWORD lpdwClasses,
LPCTSTR lpszPassword
);`
 * (Windows Embedded CE 6.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetCallBarringState(HLINE hLine, DWORD dwMode, LPDWORD lpdwClasses, LPCTSTR lpszPassword) AKARI_CE_NAME(lineGetCallBarringState);

/* ee497336 lineSetMuteState: print `LONG WINAPI lineSetMuteState(
HLINE hLine,
DWORD dwState
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetMuteState(HLINE hLine, DWORD dwState) AKARI_CE_NAME(lineSetMuteState);

/* ee497350 lineGetSendCallerIDState: print `LONG WINAPI lineGetSendCallerIDState(
HLINE hLine,
LPDWORD lpdwState
);`
 * (Windows Embedded CE 6.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetSendCallerIDState(HLINE hLine, LPDWORD lpdwState) AKARI_CE_NAME(lineGetSendCallerIDState);

/* ee497399 lineRegister: print `LONG WINAPI lineRegister(
HLINE hLine,
DWORD dwRegisterMode,
LPCTSTR lpszOperator,
DWORD dwOperatorFormat
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineRegister(HLINE hLine, DWORD dwRegisterMode, LPCTSTR lpszOperator, DWORD dwOperatorFormat) AKARI_CE_NAME(lineRegister);

/* ee497439 lineSetEquipmentState: print `LONG WINAPI lineSetEquipmentState(
HLINE hLine,
DWORD dwState
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetEquipmentState(HLINE hLine, DWORD dwState) AKARI_CE_NAME(lineSetEquipmentState);

/* ee497463 lineGetRadioPresence: print `LONG WINAPI lineGetRadioPresence(
HLINE hLine,
LPDWORD lpdwRadioPresence
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetRadioPresence(HLINE hLine, LPDWORD lpdwRadioPresence) AKARI_CE_NAME(lineGetRadioPresence);

/* ee497465 lineGetCallBarringCaps: print `LONG WINAPI lineGetCallBarringCaps(
HLINE hLine,
LPDWORD lpdwModes,
LPDWORD lpdwClasses
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetCallBarringCaps(HLINE hLine, LPDWORD lpdwModes, LPDWORD lpdwClasses) AKARI_CE_NAME(lineGetCallBarringCaps);

/* ee497486 lineUnregister: print `LONG WINAPI lineUnregister(
HLINE hLine
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineUnregister(HLINE hLine) AKARI_CE_NAME(lineUnregister);

/* ee497627 lineSetCallBarringPassword: print `LONG WINAPI lineSetCallBarringPassword(
HLINE hLine,
DWORD dwMode,
LPCTSTR lpszOldPassword,
LPCTSTR lpszNewPassword
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetCallBarringPassword(HLINE hLine, DWORD dwMode, LPCTSTR lpszOldPassword, LPCTSTR lpszNewPassword) AKARI_CE_NAME(lineSetCallBarringPassword);

/* ee497680 lineSetHSCSDState: print `LONG WINAPI lineSetHSCSDState(
HLINE hLine,
DWORD dwChannelsIn,
DWORD dwMaxChannelsIn,
DWORD dwChannelCodings,
DWORD dwAirInterfaceRate
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetHSCSDState(HLINE hLine, DWORD dwChannelsIn, DWORD dwMaxChannelsIn, DWORD dwChannelCodings, DWORD dwAirInterfaceRate) AKARI_CE_NAME(lineSetHSCSDState);

/* ee497843 lineSetCallBarringState: print `LONG WINAPI lineSetCallBarringState(
HLINE hLine,
DWORD dwMode,
DWORD dwClasses,
LPCTSTR lpszPassword
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetCallBarringState(HLINE hLine, DWORD dwMode, DWORD dwClasses, LPCTSTR lpszPassword) AKARI_CE_NAME(lineSetCallBarringState);

/* ee497891 lineGetCurrentAddressID: print `HRESULT lineGetCurrentAddressID (
HLINE hLine,
LPDWORD lpdwAddressID,
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT lineGetCurrentAddressID(HLINE hLine, LPDWORD lpdwAddressID) AKARI_CE_NAME(lineGetCurrentAddressID);

/* ee497893 lineGetOperatorStatus: print `LONG WINAPI lineGetOperatorStatus(
HLINE hLine,
LPLINEOPERATORSTATUS lpOperatorStatus
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetOperatorStatus(HLINE hLine, LPLINEOPERATORSTATUS lpOperatorStatus) AKARI_CE_NAME(lineGetOperatorStatus);

/* ee498061 lineGetNumberCalls: print `LONG WINAPI lineGetNumberCalls(
HLINE hLine,
LPDWORD lpdwNumActiveCalls,
LPDWORD lpdwNumOnHoldCalls,
LPDWORD lpdwNumOnHoldPendCalls
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetNumberCalls(HLINE hLine, LPDWORD lpdwNumActiveCalls, LPDWORD lpdwNumOnHoldCalls, LPDWORD lpdwNumOnHoldPendCalls) AKARI_CE_NAME(lineGetNumberCalls);

/* ee498073 lineGetGeneralInfo: print `LONG WINAPI lineGetGeneralInfo(
HLINE hLine,
LPLINEGENERALINFO lpLineGeneralInfo
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetGeneralInfo(HLINE hLine, LPLINEGENERALINFO lpLineGeneralInfo) AKARI_CE_NAME(lineGetGeneralInfo);

/* ee498076 lineGetCallWaitingCaps: print `LONG WINAPI lineGetCallWaitingCaps(
HLINE hLine,
LPDWORD lpdwClasses
);`
 * (Windows Embedded CE 6.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetCallWaitingCaps(HLINE hLine, LPDWORD lpdwClasses) AKARI_CE_NAME(lineGetCallWaitingCaps);

/* ee498088 lineGetEquipmentState: print `LONG WINAPI lineGetEquipmentState(
HLINE hLine,
LPDWORD lpdwState,
LPDWORD lpdwRadioSupport
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetEquipmentState(HLINE hLine, LPDWORD lpdwState, LPDWORD lpdwRadioSupport) AKARI_CE_NAME(lineGetEquipmentState);

/* ee498231 lineSetGPRSClass: print `LONG WINAPI lineSetGPRSClass(
HLINE hLine,
DWORD dwClass
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetGPRSClass(HLINE hLine, DWORD dwClass) AKARI_CE_NAME(lineSetGPRSClass);

/* ee498252 lineSetCallWaitingState: print `LONG WINAPI lineSetCallWaitingState (
HLINE hLine,
DWORD dwClasses,
DWORD dwState
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineSetCallWaitingState(HLINE hLine, DWORD dwClasses, DWORD dwState) AKARI_CE_NAME(lineSetCallWaitingState);

/* ee498265 lineGetMuteState: print `LONG WINAPI lineGetMuteState(
HLINE hLine,
LPDWORD lpdwState
);`
 * (Windows Embedded CE 6.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetMuteState(HLINE hLine, LPDWORD lpdwState) AKARI_CE_NAME(lineGetMuteState);

/* ee498266 lineGetCallWaitingState: print `LONG WINAPI lineGetCallWaitingState(
HLINE hLine,
LPDWORD lpdwClasses
);`
 * (Windows CE 3.0 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT LONG lineGetCallWaitingState(HLINE hLine, LPDWORD lpdwClasses) AKARI_CE_NAME(lineGetCallWaitingState);

/* ee498294 lineSetCurrentAddressID: print `HRESULT lineSetCurrentAddressID (
HLINE hLine,
DWORD dwAddressID,
);`
 * (Windows CE .NET 4.2 and later; Link Library: cellcore.lib) */
AKARI_CE_IMPORT HRESULT lineSetCurrentAddressID(HLINE hLine, DWORD dwAddressID) AKARI_CE_NAME(lineSetCurrentAddressID);

#endif /* AKARI_EXTAPI_H */
