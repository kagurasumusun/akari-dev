/*
 * Sockserv.h -- type definitions recovered from the official
 * page prints (tools/decl-types.py).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 */

#ifndef AKARI_SOCKSERV_H_
#define AKARI_SOCKSERV_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* wceddkPDCARD_ADAPTER_INFO: page-printed definition (Windows CE OS). */
typedef struct _PDCARD_ADAPTER_INFO {
    UINT32 uMemGranularity;
    UINT8 fAdapterCaps;
    UINT8 uCacheLine;
    UINT16 uPowerEntries;
} PDCARD_ADAPTER_INFO;

/* wceddkPDCARD_POWER_ENTRY: page-printed definition (Windows CE OS). */
typedef struct _PDCARD_POWER_ENTRY {
    UINT8 uPowerLevel;
    UINT8 fSupply;
} PDCARD_POWER_ENTRY;

/* wceddkPDCARD_SOCKET_STATE: page-printed definition (Windows CE OS). */
typedef struct _PDCARD_SOCKET_STATE {
    UINT8 fSocketCaps;
    UINT8 fInterruptEvents;
    UINT8 fNotifyEvents;
    UINT8 fControlCaps;
    UINT8 fInterfaceType;
    UINT8 fIREQRouting;
    UINT8 fVcc;
    UINT8 uVpp1;
    UINT8 uVpp2;
} PDCARD_SOCKET_STATE;

/* wceddkPDCARD_WINDOW_INFO: page-printed definition (Windows CE OS). */
typedef struct _PDCARD_WINDOW_INFO {
    UINT16 fSockets;
    UINT16 fWindowCaps;
    UINT16 fMemoryCaps;
    UINT16 fIOCaps;
    UINT32 uMemFirstByte;
    UINT32 uMemLastByte;
    UINT32 uMemMinSize;
    UINT32 uMemMaxSize;
    UINT32 uMemGranularity;
    UINT32 uMemBase;
    UINT32 uMemOffset;
    UINT32 uIOFirstByte;
    UINT32 uIOLastByte;
    UINT32 uIOMinSize;
    UINT32 uIOMaxSize;
    UINT32 uIOGranularity;
    UINT8 uAddressLines;
    UINT8 fSlowest;
    UINT8 fFastest;
} PDCARD_WINDOW_INFO;

/* wceddkPDCARD_WINDOW_STATE: page-printed definition (Windows CE OS). */
typedef struct _PDCARD_WINDOW_STATE {
    UINT16 uSocket;
    UINT8 fState;
    UINT8 fSpeed;
    UINT32 uSize;
    UINT32 uBase;
    UINT32 uOffset;
} PDCARD_WINDOW_STATE;

#endif /* AKARI_SOCKSERV_H_ */
