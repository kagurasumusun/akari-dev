/*
 * Controldefinitions.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: controldefinitions.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_CONTROLDEFINITIONS_H
#define AKARI_CONTROLDEFINITIONS_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Wingdi.h"   /* COLORREF */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee499254 STATUS_HEADER_PRIORITY: page print
 * typedef enum _STATUS_HEADER_PRIORITY { shpError = 0, shpTempChanges, shpNodeHelp, shpSystem, shpHelp, shpForwarding, shpIncomingCall, shpMissedCalls, 
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum _STATUS_HEADER_PRIORITY {
    shpError = 0,
    shpTempChanges,
    shpNodeHelp,
    shpSystem,
    shpHelp,
    shpForwarding,
    shpIncomingCall,
    shpMissedCalls,
    shpDefault,
    StatusHeaderPriorities
} STATUS_HEADER_PRIORITY;

/* ee499265 PHMS_ITEM: page print
 * typedef struct _PHMS_ITEM { int Identifier; int StringId; } PHMS_ITEM;
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef struct _PHMS_ITEM {
    int Identifier;
    int StringId;
} PHMS_ITEM;

/* ee499844 PH_COLOR: page print
 * typedef enum _PH_COLOR { phcDefaultTransparentColor = 0, phcDefaultBackgroundColor, phcDefaultTextColor, phcDisplayItemBackgroundColor, phcDisplayItem
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum _PH_COLOR {
    phcDefaultTransparentColor = 0,
    phcDefaultBackgroundColor,
    phcDefaultTextColor,
    phcDisplayItemBackgroundColor,
    phcDisplayItemSelectedBackgroundColor,
    phcDisplayItemTextColor,
    phcDisplayItemSelectedTextColor,
    phcDisplayItemBorderColor,
    phcDisplayItemSelectedBorderColor,
    phcLast
} PH_COLOR;

/* ee500372 PH_FONT: page print
 * typedef enum _PH_FONT { phfStandardText = 0, phfStandardTextBold, phfInformationText, phfLargeText, phfBigNumbersText, phfLast, } PH_FONT;
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
typedef enum _PH_FONT {
    phfStandardText = 0,
    phfStandardTextBold,
    phfInformationText,
    phfLargeText,
    phfBigNumbersText,
    phfLast
} PH_FONT;


/* ee499558 PHRegisterSingletonApplication: print `BOOL PHRegisterSingletonApplication(
const WCHAR* pNameToRegister,
HANDLE* phApplication
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT BOOL PHRegisterSingletonApplication(const WCHAR *pNameToRegister, HANDLE *phApplication) AKARI_CE_NAME(PHRegisterSingletonApplication);

/* ee499853 PHDrawBackground: print `BOOL PHDrawBackground(
HDC hdc,
RECT* pDrawRectangle
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT BOOL PHDrawBackground(HDC hdc, RECT *pDrawRectangle) AKARI_CE_NAME(PHDrawBackground);

/* ee499881 PHGetColor: print `COLORREF PHGetColor(
PH_COLOR Id
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT COLORREF PHGetColor(PH_COLOR Id) AKARI_CE_NAME(PHGetColor);

/* ee501040 PHGetFont: print `HFONT PHGetFont(
PH_FONT Id
);`
 * (Windows Embedded CE 6.0 and later; Link Library: PhCommon.dll) */
AKARI_CE_IMPORT HFONT PHGetFont(PH_FONT Id) AKARI_CE_NAME(PHGetFont);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_CONTROLDEFINITIONS_H */
