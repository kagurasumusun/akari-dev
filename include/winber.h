/*
 * winber.h -- LDAP Basic Encoding Rules (LBER) for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 * These are exported by wldap32.dll and are split out from winldap.h the same
 * way the CE SDK splits them.
 */
#ifndef AKARI_WCE_WINBER_H
#define AKARI_WCE_WINBER_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>

#ifndef _WINBER_
#define _WINBER_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINBERAPI
#define WINBERAPI AKARI_DLLIMPORT
#endif

#ifndef BERAPI
#define BERAPI __cdecl
#endif

/* The BER element handle is opaque; its layout is internal to wldap32. */
struct berelement;
typedef struct berelement BerElement;

/* A length-prefixed octet string, used throughout the BER layer. */
typedef struct akari_berval {
    ULONG bv_len;
    char *bv_val;
} LDAP_BERVAL, *PLDAP_BERVAL, BERVAL, *PBERVAL, BerValue;

#define LBER_USE_DER        0x01
#define LBER_USE_INDEFINITE_LEN 0x02
#define LBER_TRANSLATE_TAGS 0x04

#define LDAP_TAG_MASK       0x1f
#define LBER_CLASS_UNIVERSAL   0x00
#define LBER_CLASS_APPLICATION 0x40
#define LBER_CLASS_CONTEXT     0x80
#define LBER_CLASS_PRIVATE     0xc0
#define LBER_PRIMITIVE      0x00
#define LBER_CONSTRUCTED    0x20

#define LBER_SEQUENCE       0x30
#define LBER_SET            0x31

#define LBER_ERROR          (-1)
#define LBER_DEFAULT        (-1)
#define LBER_END_OF_SEQORSET (-1)
#define LBER_USE_DER_ENCODED 0x01

WINBERAPI BerElement * BERAPI ber_alloc_t(INT options);
WINBERAPI BerElement * BERAPI ber_init(BERVAL *pBerVal);
WINBERAPI VOID BERAPI ber_free(BerElement *pBerElement, INT fbuf);
WINBERAPI VOID BERAPI ber_bvfree(BERVAL *pBerVal);
WINBERAPI VOID BERAPI ber_bvecfree(PBERVAL *pBerVal);
WINBERAPI BERVAL * BERAPI ber_bvdup(BERVAL *pBerVal);
WINBERAPI INT BERAPI ber_flatten(BerElement *pBerElement, PBERVAL *pBerVal);
WINBERAPI INT BERAPI ber_printf(BerElement *pBerElement, PCHAR fmt, ...);
WINBERAPI ULONG BERAPI ber_scanf(BerElement *pBerElement, PCHAR fmt, ...);
WINBERAPI ULONG BERAPI ber_first_element(BerElement *pBerElement, ULONG *pLen, CHAR **ppOpaque);
WINBERAPI ULONG BERAPI ber_next_element(BerElement *pBerElement, ULONG *pLen, CHAR *opaque);
WINBERAPI ULONG BERAPI ber_peek_tag(BerElement *pBerElement, ULONG *pLen);
WINBERAPI ULONG BERAPI ber_skip_tag(BerElement *pBerElement, ULONG *pLen);

#ifdef __cplusplus
}
#endif

#endif /* _WINBER_ */
#endif /* AKARI_WCE_WINBER_H */
