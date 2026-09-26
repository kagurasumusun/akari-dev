/*
 * prsht.h -- Property sheets for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * The CE SDK declares the property sheet handle, the notification record and
 * the three property sheet entry points in this header, separate from
 * commctrl.h, even though commctrl.dll exports them.  They were previously
 * split across the kit's windef.h and commctrl.h; they are declared here now,
 * where CE puts them, so that #include <prsht.h> finds them.
 *
 * HPROPSHEETPAGE was declared in windef.h as an alias for HANDLE.  CE declares
 * it as a pointer to an incomplete struct _PSP, which is what it is here now.
 * Both are pointer sized, but matching the reference keeps the types
 * interchangeable with anything else that declares the handle the CE way.
 */
#ifndef AKARI_WCE_PRSHT_H
#define AKARI_WCE_PRSHT_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <commctrl.h>

#ifndef _PRSHT_
#define _PRSHT_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINCOMMCTRLAPI
#define WINCOMMCTRLAPI AKARI_DLLIMPORT
#endif

/* --------------------------------------------------------- handles */

struct _PSP;
typedef struct _PSP FAR *HPROPSHEETPAGE;

/* --------------------------------------------------- notification record */

struct _PSHNOTIFY {
    NMHDR hdr;
    BOOL  lParam;
};
typedef struct _PSHNOTIFY PSHNOTIFY, FAR *LPPSHNOTIFY;

#define PSNRET_NOERROR              0
#define PSNRET_INVALID              1
#define PSNRET_INVALID_NOCHANGEPAGE 2

#define PSN_SETACTIVE      (0U-200U)
#define PSN_KILLACTIVE     (0U-201U)
#define PSN_APPLY          (0U-202U)
#define PSN_RESET          (0U-203U)
#define PSN_HELP           (0U-205U)
#define PSN_WIZBACK        (0U-206U)
#define PSN_WIZNEXT        (0U-207U)
#define PSN_WIZFINISH      (0U-208U)
#define PSN_QUERYCANCEL    (0U-209U)

#define PSM_SETFINISHTEXT   (WM_USER+115)
#define PSM_PRESSBUTTON     (WM_USER+113)
#define PSBTN_BACK          0
#define PSBTN_NEXT          1
#define PSBTN_FINISH        2
#define PSBTN_OK            3
#define PSBTN_APPLYNOW      4
#define PSBTN_CANCEL        5
#define PSBTN_HELP          6
#define PSBTN_MAX           6
#define PropSheet_PressButton(h, i) \
    (BOOL)SendMessage((HWND)(h), PSM_PRESSBUTTON, (WPARAM)(i), 0)


/* Moved here from commctrl.h: the CE SDK declares the property sheet
 * notification, message and button constants in prsht.h.
 */
#define PSN_FIRST          ((UINT)-200)
#define PSNRET_MESSAGEHANDLED  3
#define PSM_SETCURSEL       (WM_USER + 101)
#define PSM_CHANGED         (WM_USER + 104)
#define PSM_RESTARTWINDOWS  (WM_USER + 105)
#define PSM_REBOOTSYSTEM    (WM_USER + 106)
#define PSM_CANCELTOCLOSE   (WM_USER + 107)
#define PSM_QUERYSIBLINGS   (WM_USER + 108)
#define PSM_UNCHANGED       (WM_USER + 109)
#define PSM_APPLY           (WM_USER + 110)

/* ------------------------------------------------------- prototypes */

WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageW(
    LPCPROPSHEETPAGEW lppsp);
WINCOMMCTRLAPI BOOL WINAPI DestroyPropertySheetPage(HPROPSHEETPAGE hPSPage);
WINCOMMCTRLAPI int  WINAPI PropertySheetW(LPCPROPSHEETHEADERW ppsph);

#ifdef __cplusplus
}
#endif

#endif /* _PRSHT_ */
#endif /* AKARI_WCE_PRSHT_H */
