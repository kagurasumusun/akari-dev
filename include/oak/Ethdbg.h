/*
 * Ethdbg.h -- declarations recovered from the official
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

#ifndef AKARI_ETHDBG_H_
#define AKARI_ETHDBG_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_EdbgDeregisterClient: page-printed prototype (Windows CE OS; ethdbg.lib, ethdbg.dll). */
BOOL EdbgDeregisterClient(UCHAR Id);


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _wcepb_EdbgRecv: page-printed prototype (Windows CE OS; ethdbg.lib). */
BOOL EdbgRecv(UCHAR Id, UCHAR* pRecvBuf, DWORD* pdwLen, DWORD Timeout);

/* _wcepb_EdbgResetDevice: page-printed prototype (Windows CE OS). */
BOOL EdbgResetDevice(CHAR* DeviceName, UCHAR Id, BOOL CleanBoot);

/* _wcepb_EdbgSend: page-printed prototype (Windows CE OS; ethdbg.lib, edbg.dll). */
BOOL EdbgSend(UCHAR Id, UCHAR* pUserData, DWORD dwUserDataLen);

#endif /* AKARI_ETHDBG_H_ */
