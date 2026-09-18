/*
 * Wap.h -- Windows CE WAP (Wireless Application Protocol) API header
 * of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive, wince-docs-corpus
 * clone; page ids cited per record).  All pages in this cluster print
 * "Header: wap.h".
 *
 * GAP FOUND 2026-09-19 during a cross-check of this tree against
 * wince-docs-corpus: docs/def-gap-triage-2026-09-18.tsv lists
 * "wap" (12 pages) as an app-candidate DLL with no .def, and its note
 * says "WAP push / services" without checking for plain function
 * exports -- but 6 of its pages are NOT COM methods (unlike the other
 * 7 libraries in that same triage bucket, which are genuinely
 * COM-vtable-only and correctly have no .def): WapOpen, WapClose,
 * WapPing, WapRead, WapSend and WapGetNextPrimitiveSize are ordinary
 * flat C functions with "Link Library: Wap.lib".  No tools/manifests/
 * *.manifest ever queued this cluster, so it was never harvested by
 * name and the header was simply never written.  This file and
 * def/wap-doc.def close that specific gap; docs/def-gap.md and
 * docs/def-gap-triage-2026-09-18.tsv need their "wap" rows corrected
 * to reflect it (see docs/SESSION-STATE addendum).
 */

#ifndef AKARI_WAP_H
#define AKARI_WAP_H

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT */

#ifdef __cplusplus
extern "C" {
#endif

/* ee497276 WAP_LAYER page print (Header: wap.h; Windows CE 3.0 and
 * later):
 *   enum WAP_LAYER{ WAP_LAYER_WDP = 1, WAP_LAYER_WTLS, WAP_LAYER_WTP,
 *     WAP_LAYER_WSP, WAP_LAYER_WAE };                                  */
typedef enum WAP_LAYER {
    WAP_LAYER_WDP = 1,
    WAP_LAYER_WTLS,
    WAP_LAYER_WTP,
    WAP_LAYER_WSP,
    WAP_LAYER_WAE
} WAP_LAYER;

/* --- Handle type no CE page typedefs. --------------------------------
 * WAP_HANDLE: no corpus page prints a typedef for it, but ee497681
 * "WapOpen" prints `HRESULT WapOpen( const WAP_LAYER wlLayer, const
 * DWORD dwLocalPort, WAP_HANDLE* const pwhHandle, HANDLE* const
 * phMessageAvailableEvent );` and ee497805 "WapClose" prints `HRESULT
 * WapClose( const WAP_HANDLE whHandle );` (both Header: wap.h, Link
 * Library: Wap.lib) -- a value the open call fills and the close call
 * consumes is a handle; the WDP sample page (ee497490) assigns it a
 * literal (`WAP_HANDLE hWapSend = 0L;`), confirming a scalar, not a
 * struct.  Same precedent as SMS_HANDLE (see Sms.h). */
typedef HANDLE WAP_HANDLE;

/* ee497093 WAP_PRIMITIVE_BASE page print (Header: wap.h; Windows
 * Embedded CE 6.0 and later):
 *   typedef struct wap_primitive_base_tag{ WAP_PRIMITIVE_ID
 *     wpiPrimitiveID; WAP_PRIMITIVE_TYPE wptPrimitiveType; DWORD
 *     dwValidFields; } WAP_PRIMITIVE_BASE;
 * Its two enum members are printed in full (no unpublished values),
 * so the struct ships complete. */

/* ee498091 WAP_PRIMITIVE_ID page print:
 *   enum WAP_PRIMITIVE_ID{ WAP_PRIMITIVE_ID_T_DUNITDATA = 1,
 *     WAP_PRIMITIVE_ID_TR_INVOKE, WAP_PRIMITIVE_ID_TR_RESULT,
 *     WAP_PRIMITIVE_ID_TR_ABORT };                                     */
typedef enum WAP_PRIMITIVE_ID {
    WAP_PRIMITIVE_ID_T_DUNITDATA = 1,
    WAP_PRIMITIVE_ID_TR_INVOKE,
    WAP_PRIMITIVE_ID_TR_RESULT,
    WAP_PRIMITIVE_ID_TR_ABORT
} WAP_PRIMITIVE_ID;

/* ee496868 WAP_PRIMITIVE_TYPE page print:
 *   enum WAP_PRIMITIVE_TYPE{ WAP_PRIMITIVE_TYPE_REQUEST = 1,
 *     WAP_PRIMITIVE_TYPE_INDICATION, WAP_PRIMITIVE_TYPE_RESPONSE,
 *     WAP_PRIMITIVE_TYPE_CONFIRM };                                    */
typedef enum WAP_PRIMITIVE_TYPE {
    WAP_PRIMITIVE_TYPE_REQUEST = 1,
    WAP_PRIMITIVE_TYPE_INDICATION,
    WAP_PRIMITIVE_TYPE_RESPONSE,
    WAP_PRIMITIVE_TYPE_CONFIRM
} WAP_PRIMITIVE_TYPE;

typedef struct wap_primitive_base_tag {
    WAP_PRIMITIVE_ID   wpiPrimitiveID;
    WAP_PRIMITIVE_TYPE wptPrimitiveType;
    DWORD              dwValidFields;
} WAP_PRIMITIVE_BASE;

#if _WIN32_WCE >= 0x0600
/* ee497372 WAP_ADDRESS_TYPE page print (Header: wap.h; Windows
 * Embedded CE 6.0 and later):
 *   enum WAP_ADDRESS_TYPE{ WAP_ADDRESS_TYPE_UDP = 1,
 *     WAP_ADDRESS_TYPE_GSM_SMS };                                      */
typedef enum WAP_ADDRESS_TYPE {
    WAP_ADDRESS_TYPE_UDP = 1,
    WAP_ADDRESS_TYPE_GSM_SMS
} WAP_ADDRESS_TYPE;

/* WAP_ADDRESS HELD as a complete definition: ee497374 prints
 *   typedef struct WAP_ADDRESS_tag{ WAP_ADDRESS_TYPE watAddressType;
 *     TCHAR ptsAddress[MAX_WAP_ADDRESS_LENGTH]; } WAP_ADDRESS;
 * but no corpus page prints a value for MAX_WAP_ADDRESS_LENGTH (three
 * pages use it as an array bound, none defines it; checked
 * 2026-09-19, see docs/unpublished-constants.tsv).  Per clean-room.md
 * policy v3 section 5 the value stays held pending an R1
 * (CeGCC-lineage) confirmation this session did not have the R1
 * checkout to run.  All six wap.h functions that touch WAP_ADDRESS
 * take it only by pointer, so an opaque forward declaration is
 * sufficient for every documented prototype below and does not
 * require inventing the array bound. */
typedef struct WAP_ADDRESS_tag WAP_ADDRESS;
#endif /* _WIN32_WCE >= 0x0600 */

/* ee497681 WapOpen page print (Header: wap.h, Link Library: Wap.lib,
 * Windows Embedded CE 6.0 and later):
 *   HRESULT WapOpen( const WAP_LAYER wlLayer, const DWORD dwLocalPort,
 *     WAP_HANDLE* const pwhHandle, HANDLE* const
 *     phMessageAvailableEvent ); */
AKARI_CE_IMPORT HRESULT WapOpen(const WAP_LAYER wlLayer, const DWORD dwLocalPort, WAP_HANDLE *const pwhHandle, HANDLE *const phMessageAvailableEvent) AKARI_CE_NAME(WapOpen);

/* ee497805 WapClose page print (Header: wap.h, Link Library: Wap.lib,
 * Windows CE 3.0 and later):
 *   HRESULT WapClose( const WAP_HANDLE whHandle ); */
AKARI_CE_IMPORT HRESULT WapClose(const WAP_HANDLE whHandle) AKARI_CE_NAME(WapClose);

#if _WIN32_WCE >= 0x0600
/* ee497695 WapPing page print (Header: wap.h, Link Library: Wap.lib,
 * Windows Embedded CE 6.0 and later; takes WAP_ADDRESS by pointer
 * only, so the opaque forward declaration above suffices):
 *   HRESULT WapPing( const WAP_ADDRESS* const pwaAddress, const WORD
 *     wIdentifier, const DWORD dwSendDataSize, DWORD* const
 *     pdwReceiveDataSize, const DWORD dwTimeout ); */
AKARI_CE_IMPORT HRESULT WapPing(const WAP_ADDRESS *const pwaAddress, const WORD wIdentifier, const DWORD dwSendDataSize, DWORD *const pdwReceiveDataSize, const DWORD dwTimeout) AKARI_CE_NAME(WapPing);
#endif /* _WIN32_WCE >= 0x0600 */

/* ee498210 WapRead page print (Header: wap.h, Link Library: Wap.lib,
 * Windows CE 3.0 and later):
 *   HRESULT WapRead( const WAP_HANDLE whHandle, WAP_PRIMITIVE_BASE*
 *     const pwpbPrimitiveBuffer, const DWORD dwPrimitiveBufferSize ); */
AKARI_CE_IMPORT HRESULT WapRead(const WAP_HANDLE whHandle, WAP_PRIMITIVE_BASE *const pwpbPrimitiveBuffer, const DWORD dwPrimitiveBufferSize) AKARI_CE_NAME(WapRead);

/* ee497328 WapSend page print (Header: wap.h, Link Library: Wap.lib,
 * Windows CE 3.0 and later):
 *   HRESULT WapSend( const WAP_HANDLE whHandle, WAP_PRIMITIVE_BASE*
 *     const pwpbPrimitive ); */
AKARI_CE_IMPORT HRESULT WapSend(const WAP_HANDLE whHandle, WAP_PRIMITIVE_BASE *const pwpbPrimitive) AKARI_CE_NAME(WapSend);

/* ee496873 WapGetNextPrimitiveSize page print (Header: wap.h, Link
 * Library: Wap.lib, Windows CE 3.0 and later):
 *   HRESULT WapGetNextPrimitiveSize( const WAP_HANDLE whHandle,
 *     DWORD* const pdwNextPrimitiveSize ); */
AKARI_CE_IMPORT HRESULT WapGetNextPrimitiveSize(const WAP_HANDLE whHandle, DWORD *const pdwNextPrimitiveSize) AKARI_CE_NAME(WapGetNextPrimitiveSize);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WAP_H */
