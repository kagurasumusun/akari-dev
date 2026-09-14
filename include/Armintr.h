/*
 * Armintr.h -- declarations recovered from the official
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

#ifndef AKARI_ARMINTR_H_
#define AKARI_ARMINTR_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms864519: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _AddSatInt(int Arg1, int Arg2);

/* ms879732: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _DAddSatInt(int Arg1, int Arg2);

/* ms879740: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _DSubSatInt(int Arg1, int Arg2);

/* ms880216: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _PreLoad(unsigned long* addr);

/* ms880593: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _SmulAddHiLo_SW_ACC(int Arg1, int Arg2);

/* ms880599: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulAddHiLo_SW_SL(int Arg1, int Arg2, int Arg3);

/* ms880612: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _SmulAddHi_SW_ACC(int Arg1, int Arg2);

/* ms880697: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulAddHi_SW_SL(int Arg1, int Arg2, int Arg3);

/* ms880782: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _SmulAddLoHi_SW_ACC(int Arg1, int Arg2);

/* ms880786: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulAddLoHi_SW_SL(int Arg1, int Arg2, int Arg3);

/* ms880788: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _SmulAddLo_SW_ACC(int Arg1, int Arg2);

/* ms880789: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulAddLo_SW_SL(int Arg1, int Arg2, int Arg3);

/* ms880792: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _SmulAddPack_2SW_ACC(int Arg1, int Arg2);

/* ms880793: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulAddWHi_SW_SL(int Arg1, int Arg2, int Arg3);

/* ms880794: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulAddWLo_SW_SL(int Arg1, int Arg2);

/* ms880795: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _SmulAdd_SL_ACC(int Arg1, int Arg2);

/* ms880796: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulHiLo_SW_SL(int Arg1, int Arg2);

/* ms880797: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulHi_SW_SL(int Arg1, int Arg2);

/* ms880798: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulLoHi_SW_SL(int Arg1, int Arg2);

/* ms880799: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulLo_SW_SL(int Arg1, int Arg2);

/* ms880800: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulWHi_SW_SL(int Arg1, int Arg2);

/* ms880801: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SmulWLo_SW_SL(int Arg1, int Arg2);

/* ms880808: page-printed prototype (Windows CE .NET 4.0 and later.). */
int _SubSatInt(int Arg1, int Arg2);

#endif /* AKARI_ARMINTR_H_ */
