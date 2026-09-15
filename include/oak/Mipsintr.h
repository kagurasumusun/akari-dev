/*
 * Mipsintr.h -- declarations recovered from the official
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

#ifndef AKARI_MIPSINTR_H_
#define AKARI_MIPSINTR_H_

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, ... */
#include "Cmnintrin.h" /* _ReturnAddress: ms880435 prints "Header: mipsintr.h"
                        * and ms933599 prints "Header: cmnintrin.h" for the same
                        * intrinsic, so the one declaration lives in the common
                        * header and this one reaches it (M134) */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* _ReturnAddress moved to oak/Cmnintrin.h in M134: ms933599 prints
 * "Header: cmnintrin.h", and it is a common (not MIPS-specific) intrinsic. */

/* ms864520: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _add_ob(double Arg1, double Arg2, int Arg3);

/* ms864526: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _alni_ob(double Arg1, double Arg2, int Arg3);

/* ms864527: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _and_ob(double Arg1, double Arg2, int Arg3);

/* ms864549: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _c_eq_ob(double Arg1, double Arg2, int Arg3);

/* ms864561: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _c_le_ob(double Arg1, double Arg2, int Arg3);

/* ms864567: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _c_lt_ob(double Arg1, double Arg2, int Arg3);

/* ms879766: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _max_ob(double Arg1, double Arg2, int Arg3);

/* ms879767: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _min_ob(double Arg1, double Arg2, int Arg3);

/* ms880046: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _mul_ob(double Arg1, double Arg2, int Arg3);

/* ms880022: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _mula_ob(double Arg1, double Arg2, int Arg3);

/* ms880031: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _mull_ob(double Arg1, double Arg2, int Arg3);

/* ms880038: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _muls_ob(double Arg1, double Arg2, int Arg3);

/* ms880035: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _mulsl_ob(double Arg1, double Arg2, int Arg3);

/* ms880161: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _nor_ob(double Arg1, double Arg2, int Arg3);

/* ms880167: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _or_ob(double Arg1, double Arg2, int Arg3);

/* ms880179: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _pickf_ob(double Arg1, double Arg2, int Arg3);

/* ms880188: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _pickt_ob(double Arg1, double Arg2, int Arg3);

/* ms880249: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _rach_ob(void);

/* ms880253: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _racl_ob(void);

/* ms880264: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _racm_ob(void);

/* ms880501: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _rzu_ob(double Arg1, int Arg2);

/* ms880529: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _shfl_mixh_ob(double Arg1, double Arg2);

/* ms880538: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _shfl_mixl_ob(double Arg1, double Arg2);

/* ms880552: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _shfl_pach_ob(double Arg1, double Arg2);

/* ms880569: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _shfl_pacl_ob(double Arg1, double Arg2);

/* ms880583: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _sll_ob(double Arg1, double Arg2, int Arg3);

/* ms880807: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _srl_ob(double Arg1, double Arg2, int Arg3);

/* ms880809: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _sub_ob(double Arg1, double Arg2, int Arg3);

/* ms881378: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _wach_ob(double Arg1);

/* ms881383: page-printed prototype (Windows CE .NET 4.0 and later.). */
void _wacl_ob(double Arg1, double Arg2);

/* ms881398: page-printed prototype (Windows CE .NET 4.0 and later.). */
double _xor_ob(double Arg1, double Arg2, int Arg3);

#endif /* AKARI_MIPSINTR_H_ */
