/*
 * WMDRM10ND.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: WMDRM10ND.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_WMDRM10ND_H
#define AKARI_WMDRM10ND_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "Objbase.h"   /* BSTR */
#include "Upnp.h"   /* IUPnPService */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* aa456346 DRM_ND_DeregisterFromService: print `long DRM_ND_DeregisterFromService (
BSTR sServerUDN,
);`
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: cardea_wince.lib) */
AKARI_CE_IMPORT long DRM_ND_DeregisterFromService(BSTR sServerUDN) AKARI_CE_NAME(DRM_ND_DeregisterFromService);

/* aa456348 DRM_ND_Init: print `long DRM_ND_Init(void);`
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: cardea_wince.lib) */
AKARI_CE_IMPORT long DRM_ND_Init(void) AKARI_CE_NAME(DRM_ND_Init);

/* aa456349 DRM_ND_RegisterWithService: print `long DRM_ND_RegisterWithService ( BSTR sOurUDN,
BSTR sServerUDN,
IUPnPService *pService
);`
 * (Windows CE 5.0 Networked Media Device Feature Pack.; Link Library: cardea_wince.lib) */
AKARI_CE_IMPORT long DRM_ND_RegisterWithService(BSTR sOurUDN, BSTR sServerUDN, IUPnPService *pService) AKARI_CE_NAME(DRM_ND_RegisterWithService);

#endif /* AKARI_WMDRM10ND_H */
