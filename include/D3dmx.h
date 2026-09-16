/*
 * D3dmx.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: d3dmx.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_D3DMX_H
#define AKARI_D3DMX_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#include "D3dm.h"   /* D3DMFORMAT */

/* --- D3DMX types (every page below: Header d3dmx.h, no Link Library row,
 * Windows Embedded CE 6.0 and later).  Each page prints the structure with a
 * `#ifdef __cplusplus` block of constructors, casting and arithmetic
 * operators ahead of the data members.  Only the C-visible layout is shipped
 * here: the operator block references D3DMVECTOR / D3DMMATRIX and declares
 * C++ operators this tree does not carry, so it is recorded verbatim in the
 * comment for each type rather than invented.  The member layout is what the
 * pages print after `#endif //__cplusplus`, so the ABI is the published one. */

/* ee490314 "FIXED": print `typedef int FIXED; // signed 15.16 fixed-point
 * format` */
typedef int FIXED;                    /* signed 15.16 fixed-point */

/* ee490100 "D3DMXVECTOR3": print `typedef struct D3DMXVECTOR3 {
 * #ifdef __cplusplus ... constructors / casting / assignment / unary /
 * binary operators ... #endif //__cplusplus FLOAT x, y, z;
 * } D3DMXVECTOR3, *LPD3DMXVECTOR3;` */
typedef struct D3DMXVECTOR3 {
    FLOAT x, y, z;
} D3DMXVECTOR3, *LPD3DMXVECTOR3;

/* ee490256 "D3DMXVECTOR4": print `typedef struct D3DMXVECTOR4 {
 * #ifdef __cplusplus ... #endif //__cplusplus FLOAT x, y, z, w;
 * } D3DMXVECTOR4, *LPD3DMXVECTOR4;` */
typedef struct D3DMXVECTOR4 {
    FLOAT x, y, z, w;
} D3DMXVECTOR4, *LPD3DMXVECTOR4;

/* ee491446 "D3DMXMATRIX": print `typedef struct D3DMXMATRIX {
 * #ifdef __cplusplus ... #endif //__cplusplus union { struct { FLOAT _11,
 * _12, _13, _14; FLOAT _21, _22, _23, _24; FLOAT _31, _32, _33, _34;
 * FLOAT _41, _42, _43, _44; }; FLOAT m[4][4]; }; } D3DMXMATRIX,
 * *LPD3DMXMATRIX;` */
typedef struct D3DMXMATRIX {
    union {
        struct {
            FLOAT _11, _12, _13, _14;
            FLOAT _21, _22, _23, _24;
            FLOAT _31, _32, _33, _34;
            FLOAT _41, _42, _43, _44;
        };
        FLOAT m[4][4];
    };
} D3DMXMATRIX, *LPD3DMXMATRIX;

/* ee491305 "D3DMXVECTOR3FXD": print `typedef struct D3DMXVECTOR3FXD {
 * #ifdef __cplusplus ... #endif //__cplusplus FIXED x, y, z;
 * } D3DMXVECTOR3FXD, *LPD3DMXVECTOR3FXD;` */
typedef struct D3DMXVECTOR3FXD {
    FIXED x, y, z;
} D3DMXVECTOR3FXD, *LPD3DMXVECTOR3FXD;

/* ee491659 "D3DMXVECTOR4FXD": print `typedef struct D3DMXVECTOR4FXD {
 * #ifdef __cplusplus ... #endif //__cplusplus FIXED x, y, z, w;
 * } D3DMXVECTOR4FXD, *LPD3DMXVECTOR4FXD;` */
typedef struct D3DMXVECTOR4FXD {
    FIXED x, y, z, w;
} D3DMXVECTOR4FXD, *LPD3DMXVECTOR4FXD;

/* ee490729 "D3DMXMATRIXFXD": print `typedef struct D3DMXMATRIXFXD {
 * #ifdef __cplusplus ... #endif //__cplusplus union { struct { FIXED _11,
 * _12, _13, _14; FIXED _21, _22, _23, _24; FIXED _31, _32, _33, _34;
 * FIXED _41, _42, _43, _44; }; FIXED m[4][4]; }; } D3DMXMATRIXFXD,
 * *LPD3DMXMATRIXFXD;` */
typedef struct D3DMXMATRIXFXD {
    union {
        struct {
            FIXED _11, _12, _13, _14;
            FIXED _21, _22, _23, _24;
            FIXED _31, _32, _33, _34;
            FIXED _41, _42, _43, _44;
        };
        FIXED m[4][4];
    };
} D3DMXMATRIXFXD, *LPD3DMXMATRIXFXD;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee490107 D3DMXIMAGE_INFO: page print
 * typedef struct _D3DMXIMAGE_INFO { UINT Width; UINT Height; UINT Depth; UINT MipLevels; D3DMFORMAT Format; } D3DMXIMAGE_INFO;
 * (Windows Embedded CE 6.0 and later) */
typedef struct _D3DMXIMAGE_INFO {
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    D3DMFORMAT Format;
} D3DMXIMAGE_INFO;


/* ee490058 D3DMXVec3LengthSqFxd: print `FIXED D3DMXVec3LengthSqFxd(
CONST D3DMXVECTOR3FXD* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FIXED D3DMXVec3LengthSqFxd(const D3DMXVECTOR3FXD *pV) AKARI_CE_NAME(D3DMXVec3LengthSqFxd);

/* ee490069 D3DMXVec4LengthSq: print `FLOAT D3DMXVec4LengthSq(
CONST D3DMXVECTOR4* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FLOAT D3DMXVec4LengthSq(const D3DMXVECTOR4 *pV) AKARI_CE_NAME(D3DMXVec4LengthSq);

/* ee490073 D3DMXVec3Length: print `FLOAT D3DMXVec3Length(
CONST D3DMXVECTOR3* pV
)`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FLOAT D3DMXVec3Length(const D3DMXVECTOR3 *pV) AKARI_CE_NAME(D3DMXVec3Length);

/* ee490084 D3DMXVec3Dot: print `FLOAT D3DMXVec3Dot(
CONST D3DMXVECTOR3* pV1,
CONST D3DMXVECTOR3* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FLOAT D3DMXVec3Dot(const D3DMXVECTOR3 *pV1, const D3DMXVECTOR3 *pV2) AKARI_CE_NAME(D3DMXVec3Dot);

/* ee490119 D3DMXVec4Dot: print `FLOAT D3DMXVec4Dot(
CONST D3DMXVECTOR4* pV1,
CONST D3DMXVECTOR4* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FLOAT D3DMXVec4Dot(const D3DMXVECTOR4 *pV1, const D3DMXVECTOR4 *pV2) AKARI_CE_NAME(D3DMXVec4Dot);

/* ee490132 D3DMXVec3LengthFxd: print `FIXED D3DMXVec3LengthFxd(
CONST D3DMXVECTOR3FXD* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FIXED D3DMXVec3LengthFxd(const D3DMXVECTOR3FXD *pV) AKARI_CE_NAME(D3DMXVec3LengthFxd);

/* ee490501 D3DMXVec4LengthFxd: print `FIXED D3DMXVec4LengthFxd(
CONST D3DMXVECTOR4FXD* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FIXED D3DMXVec4LengthFxd(const D3DMXVECTOR4FXD *pV) AKARI_CE_NAME(D3DMXVec4LengthFxd);

/* ee490516 D3DMXMatrixfDeterminant: print `FLOAT WINAPI D3DMXMatrixfDeterminant(
CONST D3DMXMATRIX* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT FLOAT D3DMXMatrixfDeterminant(const D3DMXMATRIX *pM) AKARI_CE_NAME(D3DMXMatrixfDeterminant);

/* ee490525 D3DMXVec4LengthSqFxd: print `FIXED D3DMXVec4LengthSqFxd(
CONST D3DMXVECTOR4FXD* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FIXED D3DMXVec4LengthSqFxd(const D3DMXVECTOR4FXD *pV) AKARI_CE_NAME(D3DMXVec4LengthSqFxd);

/* ee490527 D3DMXVec4DotFxd: print `FIXED D3DMXVec4DotFxd(
CONST D3DMXVECTOR4FXD* pV1,
CONST D3DMXVECTOR4FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FIXED D3DMXVec4DotFxd(const D3DMXVECTOR4FXD *pV1, const D3DMXVECTOR4FXD *pV2) AKARI_CE_NAME(D3DMXVec4DotFxd);

/* ee490715 D3DMXVec3DotFxd: print `FIXED D3DMXVec3DotFxd(
CONST D3DMXVECTOR3FXD* pV1,
CONST D3DMXVECTOR3FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FIXED D3DMXVec3DotFxd(const D3DMXVECTOR3FXD *pV1, const D3DMXVECTOR3FXD *pV2) AKARI_CE_NAME(D3DMXVec3DotFxd);

/* ee490834 D3DMXVec3LengthSq: print `FLOAT D3DMXVec3LengthSq(
CONST D3DMXVECTOR3* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FLOAT D3DMXVec3LengthSq(const D3DMXVECTOR3 *pV) AKARI_CE_NAME(D3DMXVec3LengthSq);

/* ee491443 D3DMXMatrixfDeterminantFxd: print `FIXED WINAPI D3DMXMatrixfDeterminantFxd(
CONST D3DMXMATRIXFXD* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT FIXED D3DMXMatrixfDeterminantFxd(const D3DMXMATRIXFXD *pM) AKARI_CE_NAME(D3DMXMatrixfDeterminantFxd);

/* ee491467 D3DMXVec4Length: print `FLOAT D3DMXVec4Length(
CONST D3DMXVECTOR4* pV
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT FLOAT D3DMXVec4Length(const D3DMXVECTOR4 *pV) AKARI_CE_NAME(D3DMXVec4Length);


/* ee490048 D3DMXVec4CrossFxd: print `D3DMXVECTOR4FXD* WINAPI D3DMXVec4CrossFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR4FXD* pV1,
CONST D3DMXVECTOR4FXD* pV2,
CONST D3DMXVECTOR4FXD* pV3
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec4CrossFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR4FXD *pV1, const D3DMXVECTOR4FXD *pV2, const D3DMXVECTOR4FXD *pV3) AKARI_CE_NAME(D3DMXVec4CrossFxd);

/* ee490065 D3DMXMatrixMultiply: print `D3DMXMATRIX* WINAPI D3DMXMatrixMultiply(
D3DMXMATRIX* pOut,
CONST D3DMXMATRIX* pM1,
CONST D3DMXMATRIX* pM2
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixMultiply(D3DMXMATRIX *pOut, const D3DMXMATRIX *pM1, const D3DMXMATRIX *pM2) AKARI_CE_NAME(D3DMXMatrixMultiply);

/* ee490097 D3DMXVec4Scale: print `D3DMXVECTOR4* D3DMXVec4Scale(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR4* pV,
FLOAT s
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec4Scale(D3DMXVECTOR4 *pOut, const D3DMXVECTOR4 *pV, FLOAT s) AKARI_CE_NAME(D3DMXVec4Scale);

/* ee490122 D3DMXVec4Normalize: print `D3DMXVECTOR4* WINAPI D3DMXVec4Normalize(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR4* pV
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec4Normalize(D3DMXVECTOR4 *pOut, const D3DMXVECTOR4 *pV) AKARI_CE_NAME(D3DMXVec4Normalize);

/* ee490245 D3DMXVec3Normalize: print `D3DMXVECTOR3* WINAPI D3DMXVec3Normalize(
D3DMXVECTOR3* pOut,
CONST D3DMXVECTOR3* pV
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR3* D3DMXVec3Normalize(D3DMXVECTOR3 *pOut, const D3DMXVECTOR3 *pV) AKARI_CE_NAME(D3DMXVec3Normalize);

/* ee490268 D3DMXVec3Add: print `D3DMXVECTOR3* D3DMXVec3Add(
D3DMXVECTOR3* pOut,
CONST D3DMXVECTOR3* pV1,
CONST D3DMXVECTOR3* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3* D3DMXVec3Add(D3DMXVECTOR3 *pOut, const D3DMXVECTOR3 *pV1, const D3DMXVECTOR3 *pV2) AKARI_CE_NAME(D3DMXVec3Add);

/* ee490286 D3DMXVec4AddFxd: print `D3DMXVECTOR4FXD* D3DMXVec4AddFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR4FXD* pV1,
CONST D3DMXVECTOR4FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec4AddFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR4FXD *pV1, const D3DMXVECTOR4FXD *pV2) AKARI_CE_NAME(D3DMXVec4AddFxd);

/* ee490306 D3DMXVec3Scale: print `D3DMXVECTOR3* D3DMXVec3Scale(
D3DMXVECTOR3* pOut,
CONST D3DMXVECTOR3* pV,
FLOAT s
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3* D3DMXVec3Scale(D3DMXVECTOR3 *pOut, const D3DMXVECTOR3 *pV, FLOAT s) AKARI_CE_NAME(D3DMXVec3Scale);

/* ee490343 D3DMXVec4NormalizeFxd: print `D3DMXVECTOR4FXD* WINAPI D3DMXVec4NormalizeFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR4FXD* pV
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec4NormalizeFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR4FXD *pV) AKARI_CE_NAME(D3DMXVec4NormalizeFxd);

/* ee490471 D3DMXVec4ScaleFxd: print `D3DMXVECTOR4FXD* D3DMXVec4ScaleFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR4FXD* pV,
FIXED s
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec4ScaleFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR4FXD *pV, FIXED s) AKARI_CE_NAME(D3DMXVec4ScaleFxd);

/* ee490472 D3DMXMatrixTranslationFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixTranslationFxd(
D3DMXMATRIXFXD* pOut,
FIXED x,
FIXED y,
FIXED z
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixTranslationFxd(D3DMXMATRIXFXD *pOut, FIXED x, FIXED y, FIXED z) AKARI_CE_NAME(D3DMXMatrixTranslationFxd);

/* ee490493 D3DMXMatrixPerspectiveFovLHFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixPerspectiveFovLHFxd(
D3DMXMATRIXFXD* pOut,
FIXED fovy,
FIXED Aspect,
FIXED zn,
FIXED zf
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixPerspectiveFovLHFxd(D3DMXMATRIXFXD *pOut, FIXED fovy, FIXED Aspect, FIXED zn, FIXED zf) AKARI_CE_NAME(D3DMXMatrixPerspectiveFovLHFxd);

/* ee490497 D3DMXMatrixRotationYawPitchRoll: print `D3DMXMATRIX* WINAPI D3DMXMatrixRotationYawPitchRoll(
D3DMXMATRIX* pOut,
FLOAT Yaw,
FLOAT Pitch,
FLOAT Roll
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixRotationYawPitchRoll(D3DMXMATRIX *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll) AKARI_CE_NAME(D3DMXMatrixRotationYawPitchRoll);

/* ee490508 D3DMXMatrixPerspectiveOffCenterLHFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixPerspectiveOffCenterLHFxd(
D3DMXMATRIXFXD* pOut,
FIXED l,
FIXED r,
FIXED b,
FIXED t,
FIXED zn,
FIXED zf
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixPerspectiveOffCenterLHFxd(D3DMXMATRIXFXD *pOut, FIXED l, FIXED r, FIXED b, FIXED t, FIXED zn, FIXED zf) AKARI_CE_NAME(D3DMXMatrixPerspectiveOffCenterLHFxd);

/* ee490513 D3DMXMatrixRotationZ: print `D3DMXMATRIX* WINAPI D3DMXMatrixRotationZ(
D3DMXMATRIX* pOut,
FLOAT Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixRotationZ(D3DMXMATRIX *pOut, FLOAT Angle) AKARI_CE_NAME(D3DMXMatrixRotationZ);

/* ee490534 D3DMXVec4Transform: print `D3DMXVECTOR4* WINAPI D3DMXVec4Transform(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR4* pV,
CONST D3DMXMATRIX* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec4Transform(D3DMXVECTOR4 *pOut, const D3DMXVECTOR4 *pV, const D3DMXMATRIX *pM) AKARI_CE_NAME(D3DMXVec4Transform);

/* ee490540 D3DMXVec3CrossFxd: print `D3DMXVECTOR3FXD* D3DMXVec3CrossFxd(
D3DMXVECTOR3FXD* pOut,
CONST D3DMXVECTOR3FXD* pV1,
CONST D3DMXVECTOR3FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3FXD* D3DMXVec3CrossFxd(D3DMXVECTOR3FXD *pOut, const D3DMXVECTOR3FXD *pV1, const D3DMXVECTOR3FXD *pV2) AKARI_CE_NAME(D3DMXVec3CrossFxd);

/* ee490656 D3DMXMatrixInverse: print `D3DMXMATRIX* WINAPI D3DMXMatrixInverse(
D3DMXMATRIX* pOut,
FLOAT* pDeterminant,
CONST D3DMXMATRIX* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixInverse(D3DMXMATRIX *pOut, FLOAT *pDeterminant, const D3DMXMATRIX *pM) AKARI_CE_NAME(D3DMXMatrixInverse);

/* ee490663 D3DMXMatrixRotationX: print `D3DMXMATRIX* WINAPI D3DMXMatrixRotationX(
D3DMXMATRIX* pOut,
FLOAT Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixRotationX(D3DMXMATRIX *pOut, FLOAT Angle) AKARI_CE_NAME(D3DMXMatrixRotationX);

/* ee490680 D3DMXMatrixRotationYFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationYFxd(
D3DMXMATRIXFXD* pOut,
FIXED Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixRotationYFxd(D3DMXMATRIXFXD *pOut, FIXED Angle) AKARI_CE_NAME(D3DMXMatrixRotationYFxd);

/* ee490684 D3DMXMatrixTransposeFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixTransposeFxd(
D3DMXMATRIXFXD* pOut,
CONST D3DMXMATRIXFXD* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixTransposeFxd(D3DMXMATRIXFXD *pOut, const D3DMXMATRIXFXD *pM) AKARI_CE_NAME(D3DMXMatrixTransposeFxd);

/* ee490711 D3DMXMatrixRotationAxisFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationAxisFxd(
D3DMXMATRIXFXD* pOut,
CONST D3DMXVECTOR3FXD* pV,
FIXED Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixRotationAxisFxd(D3DMXMATRIXFXD *pOut, const D3DMXVECTOR3FXD *pV, FIXED Angle) AKARI_CE_NAME(D3DMXMatrixRotationAxisFxd);

/* ee490713 D3DMXVec4Add: print `D3DMXVECTOR4* D3DMXVec4Add(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR4* pV1,
CONST D3DMXVECTOR4* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec4Add(D3DMXVECTOR4 *pOut, const D3DMXVECTOR4 *pV1, const D3DMXVECTOR4 *pV2) AKARI_CE_NAME(D3DMXVec4Add);

/* ee490726 D3DMXMatrixScaling: print `D3DMXMATRIX* WINAPI D3DMXMatrixScaling(
D3DMXMATRIX* pOut,
FLOAT sx,
FLOAT sy,
FLOAT sz
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixScaling(D3DMXMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz) AKARI_CE_NAME(D3DMXMatrixScaling);

/* ee490738 D3DMXMatrixTranspose: print `D3DMXMATRIX* WINAPI D3DMXMatrixTranspose(
D3DMXMATRIX* pOut,
CONST D3DMXMATRIX* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixTranspose(D3DMXMATRIX *pOut, const D3DMXMATRIX *pM) AKARI_CE_NAME(D3DMXMatrixTranspose);

/* ee490807 D3DMXMatrixIdentity: print `D3DMXMATRIX* D3DMXMatrixIdentity(
D3DMXMATRIX* pOut
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixIdentity(D3DMXMATRIX *pOut) AKARI_CE_NAME(D3DMXMatrixIdentity);

/* ee490827 D3DMXMatrixPerspectiveOffCenterLH: print `D3DMXMATRIX* WINAPI D3DMXMatrixPerspectiveOffCenterLH(
D3DMXMATRIX* pOut,
FLOAT l,
FLOAT r,
FLOAT b,
FLOAT t,
FLOAT zn,
FLOAT zf
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixPerspectiveOffCenterLH(D3DMXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf) AKARI_CE_NAME(D3DMXMatrixPerspectiveOffCenterLH);

/* ee490829 D3DMXMatrixRotationXFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationXFxd(
D3DMXMATRIXFXD* pOut,
FIXED Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixRotationXFxd(D3DMXMATRIXFXD *pOut, FIXED Angle) AKARI_CE_NAME(D3DMXMatrixRotationXFxd);

/* ee490851 D3DMXVec3Cross: print `D3DMXVECTOR3* D3DMXVec3Cross(
D3DMXVECTOR3* pOut,
CONST D3DMXVECTOR3* pV1,
CONST D3DMXVECTOR3* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3* D3DMXVec3Cross(D3DMXVECTOR3 *pOut, const D3DMXVECTOR3 *pV1, const D3DMXVECTOR3 *pV2) AKARI_CE_NAME(D3DMXVec3Cross);

/* ee490862 D3DMXVec3TransformFxd: print `D3DMXVECTOR4FXD* WINAPI D3DMXVec3TransformFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR3FXD* pV,
CONST D3DMXMATRIXFXD* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec3TransformFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR3FXD *pV, const D3DMXMATRIXFXD *pM) AKARI_CE_NAME(D3DMXVec3TransformFxd);

/* ee490864 D3DMXVec3NormalizeFxd: print `D3DMXVECTOR3FXD* WINAPI D3DMXVec3NormalizeFxd(
D3DMXVECTOR3FXD* pOut,
CONST D3DMXVECTOR3FXD* pV
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR3FXD* D3DMXVec3NormalizeFxd(D3DMXVECTOR3FXD *pOut, const D3DMXVECTOR3FXD *pV) AKARI_CE_NAME(D3DMXVec3NormalizeFxd);

/* ee490866 D3DMXVec4TransformFxd: print `D3DMXVECTOR4FXD* WINAPI D3DMXVec4TransformFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR4FXD* pV,
CONST D3DMXMATRIXFXD* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec4TransformFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR4FXD *pV, const D3DMXMATRIXFXD *pM) AKARI_CE_NAME(D3DMXVec4TransformFxd);

/* ee490873 D3DMXMatrixRotationYawPitchRollFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationYawPitchRollFxd(
D3DMXMATRIXFXD* pOut,
FIXED Yaw,
FIXED Pitch,
FIXED Roll
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixRotationYawPitchRollFxd(D3DMXMATRIXFXD *pOut, FIXED Yaw, FIXED Pitch, FIXED Roll) AKARI_CE_NAME(D3DMXMatrixRotationYawPitchRollFxd);

/* ee491029 D3DMXMatrixInverseFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixInverseFxd(
D3DMXMATRIXFXD* pOut,
FIXED* pDeterminant,
CONST D3DMXMATRIXFXD* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixInverseFxd(D3DMXMATRIXFXD *pOut, FIXED *pDeterminant, const D3DMXMATRIXFXD *pM) AKARI_CE_NAME(D3DMXMatrixInverseFxd);

/* ee491035 D3DMXVec3AddFxd: print `D3DMXVECTOR3FXD* D3DMXVec3AddFxd(
D3DMXVECTOR3FXD* pOut,
CONST D3DMXVECTOR3FXD* pV1,
CONST D3DMXVECTOR3FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3FXD* D3DMXVec3AddFxd(D3DMXVECTOR3FXD *pOut, const D3DMXVECTOR3FXD *pV1, const D3DMXVECTOR3FXD *pV2) AKARI_CE_NAME(D3DMXVec3AddFxd);

/* ee491067 D3DMXVec3ScaleFxd: print `D3DMXVECTOR3FXD* D3DMXVec3ScaleFxd(
D3DMXVECTOR3FXD* pOut,
CONST D3DMXVECTOR3FXD* pV,
FIXED s
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3FXD* D3DMXVec3ScaleFxd(D3DMXVECTOR3FXD *pOut, const D3DMXVECTOR3FXD *pV, FIXED s) AKARI_CE_NAME(D3DMXVec3ScaleFxd);

/* ee491077 D3DMXVec3SubtractFxd: print `D3DMXVECTOR3FXD* D3DMXVec3SubtractFxd(
D3DMXVECTOR3FXD* pOut,
CONST D3DMXVECTOR3FXD* pV1,
CONST D3DMXVECTOR3FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3FXD* D3DMXVec3SubtractFxd(D3DMXVECTOR3FXD *pOut, const D3DMXVECTOR3FXD *pV1, const D3DMXVECTOR3FXD *pV2) AKARI_CE_NAME(D3DMXVec3SubtractFxd);

/* ee491083 D3DMXVec4Cross: print `D3DMXVECTOR4* WINAPI D3DMXVec4Cross(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR4* pV1,
CONST D3DMXVECTOR4* pV2,
CONST D3DMXVECTOR4* pV3
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec4Cross(D3DMXVECTOR4 *pOut, const D3DMXVECTOR4 *pV1, const D3DMXVECTOR4 *pV2, const D3DMXVECTOR4 *pV3) AKARI_CE_NAME(D3DMXVec4Cross);

/* ee491093 D3DMXMatrixOrthoOffCenterLHFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixOrthoOffCenterLHFxd(
D3DMXMATRIXFXD* pOut,
FIXED l,
FIXED r,
FIXED b,
FIXED t,
FIXED zn,
FIXED zf
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixOrthoOffCenterLHFxd(D3DMXMATRIXFXD *pOut, FIXED l, FIXED r, FIXED b, FIXED t, FIXED zn, FIXED zf) AKARI_CE_NAME(D3DMXMatrixOrthoOffCenterLHFxd);

/* ee491234 D3DMXMatrixRotationY: print `D3DMXMATRIX* WINAPI D3DMXMatrixRotationY(
D3DMXMATRIX* pOut,
FLOAT Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixRotationY(D3DMXMATRIX *pOut, FLOAT Angle) AKARI_CE_NAME(D3DMXMatrixRotationY);

/* ee491266 D3DMXMatrixOrthoOffCenterLH: print `D3DMXMATRIX* WINAPI D3DMXMatrixOrthoOffCenterLH(
D3DMXMATRIX* pOut,
FLOAT l,
FLOAT r,
FLOAT b,
FLOAT t,
FLOAT zn,
FLOAT zf
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixOrthoOffCenterLH(D3DMXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf) AKARI_CE_NAME(D3DMXMatrixOrthoOffCenterLH);

/* ee491287 D3DMXVec4Subtract: print `D3DMXVECTOR4* D3DMXVec4Subtract(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR4* pV1,
CONST D3DMXVECTOR4* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec4Subtract(D3DMXVECTOR4 *pOut, const D3DMXVECTOR4 *pV1, const D3DMXVECTOR4 *pV2) AKARI_CE_NAME(D3DMXVec4Subtract);

/* ee491290 D3DMXMatrixRotationAxis: print `D3DMXMATRIX* WINAPI D3DMXMatrixRotationAxis(
D3DMXMATRIX* pOut,
CONST D3DMXVECTOR3* pV,
FLOAT Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixRotationAxis(D3DMXMATRIX *pOut, const D3DMXVECTOR3 *pV, FLOAT Angle) AKARI_CE_NAME(D3DMXMatrixRotationAxis);

/* ee491434 D3DMXMatrixScalingFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixScalingFxd(
D3DMXMATRIXFXD* pOut,
FIXED sx,
FIXED sy,
FIXED sz
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixScalingFxd(D3DMXMATRIXFXD *pOut, FIXED sx, FIXED sy, FIXED sz) AKARI_CE_NAME(D3DMXMatrixScalingFxd);

/* ee491471 D3DMXVec3Transform: print `D3DMXVECTOR4* WINAPI D3DMXVec3Transform(
D3DMXVECTOR4* pOut,
CONST D3DMXVECTOR3* pV,
CONST D3DMXMATRIX* pM
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXVECTOR4* D3DMXVec3Transform(D3DMXVECTOR4 *pOut, const D3DMXVECTOR3 *pV, const D3DMXMATRIX *pM) AKARI_CE_NAME(D3DMXVec3Transform);

/* ee491483 D3DMXVec4SubtractFxd: print `D3DMXVECTOR4FXD* D3DMXVec4SubtractFxd(
D3DMXVECTOR4FXD* pOut,
CONST D3DMXVECTOR4FXD* pV1,
CONST D3DMXVECTOR4FXD* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR4FXD* D3DMXVec4SubtractFxd(D3DMXVECTOR4FXD *pOut, const D3DMXVECTOR4FXD *pV1, const D3DMXVECTOR4FXD *pV2) AKARI_CE_NAME(D3DMXVec4SubtractFxd);

/* ee491511 D3DMXMatrixMultiplyFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixMultiplyFxd(
D3DMXMATRIXFXD* pOut,
CONST D3DMXMATRIXFXD* pM1,
CONST D3DMXMATRIXFXD* pM2
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixMultiplyFxd(D3DMXMATRIXFXD *pOut, const D3DMXMATRIXFXD *pM1, const D3DMXMATRIXFXD *pM2) AKARI_CE_NAME(D3DMXMatrixMultiplyFxd);

/* ee491593 D3DMXMatrixRotationZFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixRotationZFxd(
D3DMXMATRIXFXD* pOut,
FIXED Angle
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixRotationZFxd(D3DMXMATRIXFXD *pOut, FIXED Angle) AKARI_CE_NAME(D3DMXMatrixRotationZFxd);

/* ee491600 D3DMXMatrixTranslation: print `D3DMXMATRIX* WINAPI D3DMXMatrixTranslation(
D3DMXMATRIX* pOut,
FLOAT x,
FLOAT y,
FLOAT z
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixTranslation(D3DMXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z) AKARI_CE_NAME(D3DMXMatrixTranslation);

/* ee491621 D3DMXMatrixPerspectiveFovLH: print `D3DMXMATRIX* WINAPI D3DMXMatrixPerspectiveFovLH(
D3DMXMATRIX* pOut,
FLOAT fovy,
FLOAT Aspect,
FLOAT zn,
FLOAT zf
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixPerspectiveFovLH(D3DMXMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf) AKARI_CE_NAME(D3DMXMatrixPerspectiveFovLH);

/* ee491628 D3DMXMatrixLookAtLHFxd: print `D3DMXMATRIXFXD* WINAPI D3DMXMatrixLookAtLHFxd(
D3DMXMATRIXFXD* pOut,
CONST D3DMXVECTOR3FXD* pEye,
CONST D3DMXVECTOR3FXD* pAt,
CONST D3DMXVECTOR3FXD* pUp
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixLookAtLHFxd(D3DMXMATRIXFXD *pOut, const D3DMXVECTOR3FXD *pEye, const D3DMXVECTOR3FXD *pAt, const D3DMXVECTOR3FXD *pUp) AKARI_CE_NAME(D3DMXMatrixLookAtLHFxd);

/* ee491634 D3DMXVec3Subtract: print `D3DMXVECTOR3* D3DMXVec3Subtract(
D3DMXVECTOR3* pOut,
CONST D3DMXVECTOR3* pV1,
CONST D3DMXVECTOR3* pV2
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXVECTOR3* D3DMXVec3Subtract(D3DMXVECTOR3 *pOut, const D3DMXVECTOR3 *pV1, const D3DMXVECTOR3 *pV2) AKARI_CE_NAME(D3DMXVec3Subtract);

/* ee491650 D3DMXMatrixIdentityFxd: print `D3DMXMATRIXFXD* D3DMXMatrixIdentityFxd(
D3DMXMATRIXFXD* pOut
);`
 * (generation not stated; Link Library: Implemented) */
AKARI_CE_IMPORT D3DMXMATRIXFXD* D3DMXMatrixIdentityFxd(D3DMXMATRIXFXD *pOut) AKARI_CE_NAME(D3DMXMatrixIdentityFxd);

/* ee491676 D3DMXMatrixLookAtLH: print `D3DMXMATRIX* WINAPI D3DMXMatrixLookAtLH(
D3DMXMATRIX* pOut,
CONST D3DMXVECTOR3* pEye,
CONST D3DMXVECTOR3* pAt,
CONST D3DMXVECTOR3* pUp
);`
 * (generation not stated; Link Library: D3dmx.lib) */
AKARI_CE_IMPORT D3DMXMATRIX* D3DMXMatrixLookAtLH(D3DMXMATRIX *pOut, const D3DMXVECTOR3 *pEye, const D3DMXVECTOR3 *pAt, const D3DMXVECTOR3 *pUp) AKARI_CE_NAME(D3DMXMatrixLookAtLH);

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_D3DMX_H */
