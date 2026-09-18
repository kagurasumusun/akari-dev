/*
 * Dinput.h -- DirectInput creation function record.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE page
 * ms864419 (DirectX for Windows CE documentation, harvested into
 * build/rows.json; Requirements row prints Header Dinput.h).  See
 * docs/inventory.md M85.
 *
 * The page prints the full prototype but states the function "is not
 * supported as of Windows CE .NET 4.2 and Windows Mobile 2003"; the
 * LPDIRECTINPUT pointer type it names has no CE page (no IDirectInput
 * interface pages are preserved in the corpus), so the function is
 * recorded, not declared (HRC/ALC M83 precedent).
 */

#ifndef AKARI_DINPUT_H
#define AKARI_DINPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/* LPDIRECTINPUT: no CE page prints the typedef (checked 2026-09-18;
 * no IDirectSound-style wcesdkr record either).  Derived as the
 * standard opaque interface-pointer spelling the print itself
 * requires (LPDIRECTINPUT* = pointer to interface pointer), same
 * pattern Dsound.h carries from the wcesdkr prints.  Replace on an
 * official print. */
typedef struct IDirectInput *LPDIRECTINPUT;

/* ms864419 "DirectInputCreate": print `HRESULT WINAPI
 * DirectInputCreate(HINSTANCE hinst,DWORD dwVersion,LPDIRECTINPUT*
 * lplpDirectInput,LPUNKNOWN punkOuter);` (punkOuter = controlling
 * IUnknown for aggregation; LPUNKNOWN is carried by Objbase.h).
 * Page: Windows CE 2.12 through .NET 4.1; not supported as of
 * .NET 4.2 / Windows Mobile 2003.  No Link Library row is printed. */
#if _WIN32_WCE >= 0x0212 && _WIN32_WCE <= 0x0410
AKARI_CE_IMPORT HRESULT WINAPI DirectInputCreate(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUT *lplpDirectInput, LPUNKNOWN punkOuter) AKARI_CE_NAME(DirectInputCreate);
#endif

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DINPUT_H */
