/*
 * Halether.h -- declarations recovered from the official
 * page prints (tools/decl-d1.py, M105 header creation).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own
 * print (page id cited).  Prints whose types include/
 * cannot yet resolve are recorded verbatim in the
 * header comment blocks by later passes; nothing is
 * dropped or invented.
 */

#ifndef AKARI_HALETHER_H_
#define AKARI_HALETHER_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms902071: page-printed prototype (Windows CE .NET 4.0 and later.; hal.lib). */
BOOL CallEdbgDeregisterClient(UCHAR Id);

/* ms902072: page-printed prototype (Windows CE .NET 4.0 and later.; hal.lib). */
BOOL CallEdbgRecv(UCHAR Id, UCHAR* pRecvBuf, DWORD* pdwLen, DWORD Timeout);

/* ms902073: page-printed prototype (Windows CE .NET 4.0 and later.; hal.lib). */
BOOL CallEdbgRegisterClient(UCHAR* pId, char* ServiceName, UCHAR Flags, UCHAR WindowSize, UCHAR* pBufferPool);

/* ms902074: page-printed prototype (Windows CE .NET 4.0 and later.; hal.lib). */
BOOL CallEdbgSend(UCHAR Id, UCHAR* pUserData, DWORD dwUserDataLen);

/* ms902075: page-printed prototype (Windows CE .NET 4.0 and later.; hal.lib). */
BOOL CallEdbgSetDebug(DWORD ZoneMask);

/* _wcepb_OEMEthDisableInts: page-printed prototype (Windows CE OS). */
void OEMEthDisableInts(void);

/* _wcepb_OEMEthEnableInts: page-printed prototype (Windows CE OS). */
void OEMEthEnableInts(void);

/* _wcepb_OEMEthGetSecs: page-printed prototype (Windows CE OS). */
DWORD OEMEthGetSecs(void);

/* _wcepb_OEMEthISR: page-printed prototype (Windows CE OS). */
void OEMEthISR(void);

/* _wcepb_EdbgInit: page-printed prototype (Windows CE OS). */
BOOL EdbgInit(void);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms902858: page-printed definition (Windows CE 2.10 and later.). */
typedef struct _EDBG_ADDR {
    DWORD dwIP;
    USHORT wMAC[3];
    USHORT wPort;
} EDBG_ADDR;

#endif /* AKARI_HALETHER_H_ */
