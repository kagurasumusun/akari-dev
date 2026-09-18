/* Autodial.h -- Autodial helper module (Windows CE; Autodial.lib).
 * See docs/inventory.md M77b. */

#ifndef AKARI_AUTODIAL_H
#define AKARI_AUTODIAL_H

#include "Windef.h"    /* DWORD, TCHAR */
#include "Ras.h"       /* RASCONNSTATUS (AutoDialGetConnectionStatus) */

/* aa450290: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD AutoDialCleanupModule(void)
                    AKARI_CE_NAME(AutoDialCleanupModule);
/* aa450291: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD AutoDialEndConnection(void)
                    AKARI_CE_NAME(AutoDialEndConnection);
/* aa450293: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD AutoDialInitializeModule(void)
                    AKARI_CE_NAME(AutoDialInitializeModule);
/* aa450294: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD AutoDialStartConnection(TCHAR *szUseDialEntry)
                    AKARI_CE_NAME(AutoDialStartConnection);

/* AutoDialGetConnectionStatus: print `DWORD
 * AutoDialGetConnectionStatus( RASCONNSTATUS* lpRasConn,
 * TCHAR* szRasName);` -- the RASCONNSTATUS type is not published on
 * any CE page (Ras.h M75f hold family); recorded verbatim. */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* aa450292: page-printed prototype (Windows CE .NET 4.0 and later.; autodial.lib). */
DWORD AutoDialGetConnectionStatus(RASCONNSTATUS* lpRasConn, TCHAR* szRasName);

#endif /* AKARI_AUTODIAL_H */
