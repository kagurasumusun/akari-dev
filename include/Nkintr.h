/*
 * Nkintr.h -- declarations recovered from the official
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

#ifndef AKARI_NKINTR_H_
#define AKARI_NKINTR_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_OEMClearDebugCommError: page-printed prototype (Windows CE OS). */
void OEMClearDebugCommError(void);

/* _wcepb_OEMGetExtensionDRAM: page-printed prototype (Windows CE OS). */
BOOL OEMGetExtensionDRAM(LPDWORD lpMemStart, LPDWORD lpMemLen);

/* _wcepb_OEMInit: page-printed prototype (Windows CE OS). */
void OEMInit(void);

/* _wcepb_OEMInitDebugSerial: page-printed prototype (Windows CE OS). */
void OEMInitDebugSerial(void);

/* _wcepb_OEMInterruptDisable: page-printed prototype (Windows CE OS). */
void OEMInterruptDisable(DWORD idInt);

/* _wcepb_OEMInterruptDone: page-printed prototype (Windows CE OS). */
void OEMInterruptDone(DWORD idInt);

/* _wcepb_OEMInterruptEnable: page-printed prototype (Windows CE OS). */
BOOL OEMInterruptEnable(DWORD idInt, LPVOID pvData, DWORD cbData);

/* _wcepb_OEMParallelPortGetByte: page-printed prototype (Windows CE OS). */
int OEMParallelPortGetByte(void);

/* _wcepb_OEMParallelPortSendByte: page-printed prototype (Windows CE OS). */
void OEMParallelPortSendByte(BYTE ch);

/* ms919027: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
void OEMPowerOff(void);

/* ms919056: page-printed prototype (Windows CE 2.12 and later.; nk.lib). */
int OEMReadDebugByte(void);

/* ms919102: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
void OEMWriteDebugByte(BYTE ch);

/* ms919112: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
void OEMWriteDebugLED(WORD wIndex, DWORD dwPattern);

/* ms919121: page-printed prototype (Windows CE 2.10 and later.; nk.lib). */
void OEMWriteDebugString(unsigned short* str);

/* _wcepb_SetInterruptEvent: page-printed prototype (Windows CE OS). */
AKARI_CE_IMPORT BOOL SetInterruptEvent(DWORD idInt) AKARI_CE_NAME(SetInterruptEvent);

/* _wcepb_SetKernelCommDev: page-printed prototype (Windows CE OS). */
BOOL SetKernelCommDev(UCHAR Service, UCHAR CommDevice);

#endif /* AKARI_NKINTR_H_ */
