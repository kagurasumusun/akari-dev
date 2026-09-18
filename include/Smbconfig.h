/* Smbconfig.h -- SMB server share configuration (Windows CE 5.0).
 * Link Library rows print Smbconfig.lib (def/smbconfig-doc.def).
 * Prints: Add_Share / Change_ACL / Del_Share /
 * List_Connected_Users / QueryAmountTransfered.  See
 * docs/inventory.md M75e. */

#ifndef AKARI_SMBCONFIG_H
#define AKARI_SMBCONFIG_H

#include "Windef.h"    /* DWORD, UINT */
#include "Objbase.h"   /* HRESULT */
#include "Winnt.h"     /* LARGE_INTEGER */

/* aa450283 "Add_Share" (Windows CE 5.0 and later): print `HRESULT
 * Add_Share( const WCHAR* pName, DWORD dwType, const WCHAR* pPath,
 * const WCHAR* pACL, const WCHAR* pROACL, const WCHAR* pDriver,
 * const WCHAR* pComment);` -- the earlier 3-param form and the
 * aa450328 cite were wrong (aa450328 is the Del_Share page; fixed
 * 2026-09-18). */
AKARI_CE_IMPORT HRESULT Add_Share(const WCHAR *pName, DWORD dwType, const WCHAR *pPath, const WCHAR *pACL, const WCHAR *pROACL, const WCHAR *pDriver, const WCHAR *pComment) AKARI_CE_NAME(Add_Share);
AKARI_CE_IMPORT HRESULT Del_Share(const WCHAR *pName)
                    AKARI_CE_NAME(Del_Share);

/* ms887907: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT HRESULT Change_ACL(const WCHAR *pShareName,
                    const WCHAR *pACL, const WCHAR *pPath)
                    AKARI_CE_NAME(Change_ACL);

/* ms894568: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT HRESULT List_Connected_Users(WCHAR *pBuffer,
                    UINT *puiLen) AKARI_CE_NAME(List_Connected_Users);

/* ms896350: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT HRESULT QueryAmountTransfered(
                    LARGE_INTEGER *pRead, LARGE_INTEGER *pWrite)
                    AKARI_CE_NAME(QueryAmountTransfered);

#endif /* AKARI_SMBCONFIG_H */
