/*
 * Af_irda.h -- Windows CE IrDA (IR sockets) address-family header.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive; page
 * ids cited per record).  Sources:
 *   * pages3/_wcesdk_IAS_QUERY_str.html  (CE 3.0, Header: Af_irda.h)
 *   * pages3/_wcesdk_IAS_SET_str.html    (CE 3.0, Header: Af_irda.h)
 *   * pages4/aa450935.html  (CE .NET 4.0 setsockopt, Header: Winsock2.h)
 *   * pages6/ee493640.html  (CE 6.0 setsockopt, Header: Winsock2.h)
 *   * pages4/ms911745.html  (setsockopt, OS Versions: CE 1.0 and later)
 *
 * HELD (nothing is compiled from this file yet): the two generations of
 * the official pages print the same structures with different member
 * types AND different array dimensions, and the CE .NET 4.0+ / CE 6.0
 * prints express every dimension with IAS_MAX_* constants whose VALUES
 * are not published anywhere in the harvested official corpus (48,849
 * pages scanned for IAS_MAX_CLASSNAME / IAS_MAX_ATTRIBNAME /
 * IAS_MAX_OCTET_STRING / IAS_MAX_USER_STRING: the only three pages that
 * mention them are the two setsockopt pages above and ms911745, and all
 * three use them symbolically).  Compiling the 4.0+ form would mean
 * inventing the four constants -- i.e. inventing the struct layout --
 * so the prints are carried verbatim and the only compiled form that
 * could be written (the CE 3.0 literal-dimension one) is deliberately
 * NOT compiled either: it is not the CE 4.0/5.0/6.0 layout of the same
 * struct, and a silent layout mismatch is worse than a missing
 * declaration.  Nothing below is invented.
 */

#ifndef AKARI_AF_IRDA_H
#define AKARI_AF_IRDA_H

#include <Windows.h>
#include "Winsock2.h"   /* u_char / u_short / u_long (the winsock types
                         * the IAS structural prints use) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------
 * IAS_QUERY / IAS_SET -- page prints (verbatim), CE 3.0 vs CE .NET 4.0+
 * ------------------------------------------------------------------ */

/* CE 3.0 (pages3/_wcesdk_IAS_QUERY_str.html; Header: Af_irda.h;
 * "Windows CE 3.0"):
 *   typedef struct IAS_QUERY { u_char irdaDeviceID[4] ;
 *     char irdaClassName[61] ; char irdaAttribName[61] ;
 *     u_short irdaAttribType ; union { int irdaAttribInt ;
 *       struct { int Len ; u_char OctetSeq[1] ; u_char Reserved[3] ; }
 *         irdaAttribOctetSeq;
 *       struct { int Len ; u_char CharSet ; u_char UsrStr[1] ;
 *         u_char Reserved[2] ; } irda AttribUsrStr; } irdaAttribute; }
 *     _IAS_QUERY, *PIAS_QUERY;
 * (the print's own spacing artifacts: `irda AttribUsrStr` is one
 * identifier, and the tag/alias underscores are swapped relative to the
 * page's own type name). */

/* CE .NET 4.0 (pages4/aa450935.html) and CE 6.0 (pages6/ee493640.html),
 * both printed on the setsockopt page and identical:
 *   typedef struct _WINDOWS_IAS_QUERY {
 *     u_char irdaDeviceID[4];
 *     char irdaClassName[IAS_MAX_CLASSNAME];
 *     char irdaAttribName[IAS_MAX_ATTRIBNAME];
 *     u_long irdaAttribType;
 *     union {
 *       LONG irdaAttribInt;
 *       struct { u_long Len; u_char OctetSeq[IAS_MAX_OCTET_STRING];
 *       } irdaAttribOctetSeq;
 *       struct { u_long Len; u_long CharSet;
 *                u_char UsrStr[IAS_MAX_USER_STRING];
 *       } irdaAttribUsrStr;
 *     } irdaAttribute;
 *   } IAS_QUERY, *PIAS_QUERY, FAR *LPIAS_QUERY;
 * HELD: IAS_MAX_* values not published (see the file header). */

/* CE 3.0 (pages3/_wcesdk_IAS_SET_str.html; Header: Af_irda.h;
 * "Windows CE 3.0"):
 *   typedef struct _IAS_SET { char irdaClassName[61] ;
 *     char irdaAttribName[61] ; u_short irdaAttribType ;
 *     union { int irdaAttribInt ;
 *       struct { int Len ; u_char OctetSeq[1] ; u_char Reserved[3] ; }
 *         irdaAttribOctetSeq;
 *       struct { int Len ; u_char CharSet ; u_char UsrStr[1] ;
 *         u_char Reserved[2] ; } irda AttribUsrStr; } irdaAttribute; }
 *     _IAS_SET, *PIAS_SET;
 */

/* CE .NET 4.0 (pages4/aa450935.html), CE 6.0 (pages6/ee493640.html) and
 * the CE 1.0-and-later print on pages4/ms911745.html (all three
 * byte-identical):
 *   typedef struct _IAS_SET {
 *     char irdaClassName[IAS_MAX_CLASSNAME];
 *     char irdaAttribName[IAS_MAX_ATTRIBNAME];
 *     u_long irdaAttribType;
 *     union {
 *       LONG irdaAttribInt;
 *       struct { u_short Len; u_char OctetSeq[IAS_MAX_OCTET_STRING];
 *       } irdaAttribOctetSeq;
 *       struct { u_char Len; u_char CharSet;
 *                u_char UsrStr[IAS_MAX_USER_STRING];
 *       } irdaAttribUsrStr;
 *     } irdaAttribute;
 *   } IAS_SET, *PIAS_SET, FAR *LPIAS_SET;
 * HELD: IAS_MAX_* values not published (see the file header). */

/* The two setsockopt pages add the usage note this header records for
 * the benefit of anyone porting IrDA code: "The Af_irda.h header file
 * must be explicitly included" for IrDA sockets, and the IrDA socket
 * level is SOL_IRLMP (see Winsock2.h for the option names documented
 * there).  No function is documented with Header: Af_irda.h, so this
 * header has no prototypes. */

#ifdef __cplusplus
}
#endif


/* aa450461 "IRDA_DEVICE_INFO" (af_irda.h; Windows CE 1.0 and later): the
 * page prints
 *   typedef struct IRDA_DEVICE_INFO {u_char irdaDeviceID[4];
 *     char irdaDeviceName[22]; u_char Reserved[2];} _IRDA_DEVICE_INFO;
 * Shipped exactly as printed: the tag is IRDA_DEVICE_INFO and the typedef
 * name the page gives is _IRDA_DEVICE_INFO.  Recovered by the M133
 * table-of-contents coverage audit -- this page was never in the harvested
 * corpus, so no earlier audit could see the gap. */
typedef struct IRDA_DEVICE_INFO {
    u_char irdaDeviceID[4];
    char   irdaDeviceName[22];
    u_char Reserved[2];
} _IRDA_DEVICE_INFO;

#endif /* AKARI_AF_IRDA_H */
