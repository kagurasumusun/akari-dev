/*
 * Tchaud.h -- type definitions recovered from the official
 * page prints (tools/decl-types.py).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 */

#ifndef AKARI_TCHAUD_H_
#define AKARI_TCHAUD_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* wceddkTOUCHPANEL_POINT_SAMPLE: page-printed definition (Windows CE OS). */
typedef struct _TOUCHPANEL_POINT_SAMPLE {
    USHORT XSample;
    USHORT XzaSample;
    USHORT XzbSample;
    USHORT YSample;
    USHORT YzaSample;
    USHORT YzbSample;
} TOUCHPANEL_POINT_SAMPLE;

#endif /* AKARI_TCHAUD_H_ */
