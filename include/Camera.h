/*
 * Camera.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: camera.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CAMERA_H
#define AKARI_CAMERA_H

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


/* ee482927 CSPROPERTY_BUFFER_MODE: page print
 * typedef enum { CSPROPERTY_BUFFER_DRIVER = 1, CSPROPERTY_BUFFER_CLIENT_LIMITED = 2, CSPROPERTY_BUFFER_CLIENT_UNLIMITED = 4 } CSPROPERTY_BUFFER_MODE;
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    CSPROPERTY_BUFFER_DRIVER = 1,
    CSPROPERTY_BUFFER_CLIENT_LIMITED = 2,
    CSPROPERTY_BUFFER_CLIENT_UNLIMITED = 4
} CSPROPERTY_BUFFER_MODE;

/* ee483385 BUFFER_COMMANDS: page print
 * typedef enum { CS_ALLOCATE, CS_ENQUEUE, CS_DEALLOCATE } BUFFER_COMMANDS;
 * (Windows Embedded CE 6.0 and later) */
typedef enum {
    CS_ALLOCATE,
    CS_ENQUEUE,
    CS_DEALLOCATE
} BUFFER_COMMANDS;

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_CAMERA_H */
