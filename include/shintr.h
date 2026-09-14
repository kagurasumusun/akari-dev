/*
 * shintr.h -- declarations recovered from the official
 * page prints (tools/decl-d1.py, M105 header creation).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Every declaration below is an official page's own
 * print (page id cited).  Prints whose types include/
 * cannot yet resolve are recorded verbatim in the
 * header comment blocks by later passes; nothing is
 * dropped or invented.
 */

#ifndef AKARI_SHINTR_H_
#define AKARI_SHINTR_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms882188: page-printed prototype (Windows CE .NET 4.0 and later.). */
float _Dot3dVW0(float* vector1, float* vector2);

/* ms882200: page-printed prototype (Windows CE .NET 4.0 and later.). */
float _Dot3dVW1(float* vector1, float* vector2);

/* ms882207: page-printed prototype (Windows CE .NET 4.0 and later.). */
float _Dot4dV(float* vector1, float* vector2);

/* ms882214: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _LoadMatrix(float* matrix);

/* ms882234: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _Multiply4dM(float* result, float* matrix1, float* matrix2);

/* ms882241: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _SaveMatrix(float* matrix);

/* ms882252: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _XDMultMatrix(float* matrix);

/* ms882285: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _XDXform3dV(float* src, float* dst);

/* ms882379: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _XDXform4dV(float* src, float* dst);

/* ms882386: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _Xform3dV(float* dst, float* src, float* matrix);

/* ms882393: page-printed prototype (Windows CE .NET 4.0 and later.). */
float* _Xform4dV(float* dst, float* src, float* matrix);

/* ms881409: page-printed prototype (Windows CE .NET 4.0 and later.). */
void __movca(unsigned long value, unsigned long* addr);

/* ms881410: page-printed prototype (Windows CE .NET 4.0 and later.). */
void __prefetch(unsigned long* addr);

#endif /* AKARI_SHINTR_H_ */
