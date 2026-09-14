/*
 * Unimodem.h -- type definitions recovered from the official
 * page prints (tools/decl-types.py).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 */

#ifndef AKARI_UNIMODEM_H_
#define AKARI_UNIMODEM_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms927488: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef struct _UNIMDM_CHG_DEVCFG {
    DWORD dwCommand;
    LPCWSTR lpszDeviceClass;
    LPVARSTRING lpDeviceConfig;
    DWORD dwOption;
    DWORD dwValue;
} UNIMDM_CHG_DEVCFG;

#endif /* AKARI_UNIMODEM_H_ */
