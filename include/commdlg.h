/* Common dialogs. Original text. Exported by commdlg.dll.
 *
 * Windows CE 6.0 does not ship the file dialogs (GetOpenFileName and friends) in
 * commdlg.dll; those live in ceshell.dll. Only the five entries below are the
 * commdlg surface for that release, so only those are declared here.
 */
#ifndef AKARI_WCE_COMMDLG_H
#define AKARI_WCE_COMMDLG_H
#ifdef __cplusplus
extern "C" {
#endif

#include "wingdi.h"


#define CF_SCREENFONTS   0x00000001
#define CF_INITTOLOGFONTSTRUCT 0x00000040L
#define CF_EFFECTS       0x00000100
#define CF_APPLY         0x00000200
#define CF_NOSIMULATIONS 0x00001000
#define CF_LIMITSIZE     0x00002000
#define CF_FIXEDPITCHONLY 0x00004000
#define CF_NOSCRIPTSEL   0x00800000
#define CF_NOVERTFONTS   0x01000000

#define CC_RGBINIT       0x00000001
#define CC_FULLOPEN      0x00000002
#define CC_PREVENTFULLOPEN 0x00000004
#define CC_SHOWHELP      0x00000008
#define CC_SOLIDCOLOR    0x00000080
#define CC_ANYCOLOR      0x00000100

#define PD_ALLPAGES        0x00000000
#define PD_SELECTION       0x00000001
#define PD_PAGENUMS        0x00000002
#define PD_NOSELECTION     0x00000004
#define PD_NOPAGENUMS      0x00000008
#define PD_COLLATE         0x00000010
#define PD_PRINTTOFILE     0x00000020
#define PD_PRINTSETUP      0x00000040
#define PD_NOWARNING       0x00000080
#define PD_RETURNDC        0x00000100
#define PD_RETURNIC        0x00000200
#define PD_RETURNDEFAULT   0x00000400
#define PD_SHOWHELP        0x00000800
#define PD_USEDEVMODECOPIES 0x00040000
#define PD_DISABLEPRINTTOFILE 0x00080000
#define PD_HIDEPRINTTOFILE 0x00100000

#define PSD_DEFAULTMINMARGINS     0x00000000
#define PSD_INWININIINTLMEASURE   0x00000000
#define PSD_MINMARGINS            0x00000001
#define PSD_MARGINS               0x00000002
#define PSD_INTHOUSANDTHSOFINCHES 0x00000004
#define PSD_INHUNDREDTHSOFMILLIMETERS 0x00000008
#define PSD_DISABLEMARGINS        0x00000010
#define PSD_DISABLEPRINTER        0x00000020
#define PSD_NOWARNING             0x00000080
#define PSD_DISABLEORIENTATION    0x00000100
#define PSD_RETURNDEFAULT         0x00000400
#define PSD_DISABLEPAPER          0x00000200

#define CD_LBSELNOITEMS (-1)
#define CD_LBSELCHANGE   0
#define CD_LBSELSUB      1
#define CD_LBSELADD      2

#define FNERR_BUFFERTOOSMALL     0x3003
#define CDERR_FINDRESFAILURE     0x0006
#define CDERR_GENERALCODES       0x0000
#define CDERR_INITIALIZATION     0x0002
#define CDERR_LOADRESFAILURE     0x0007
#define CDERR_LOADSTRFAILURE     0x0005
#define CDERR_LOCKRESFAILURE     0x0008
#define CDERR_MEMALLOCFAILURE    0x0009
#define CDERR_MEMLOCKFAILURE     0x000A
#define CDERR_NOHINSTANCE        0x0004
#define CDERR_NOTEMPLATE         0x0003
#define CDERR_REGISTERMSGFAIL    0x000C
#define CDERR_STRUCTSIZE         0x0001
#define CFERR_CHOOSEFONTCODES    0x2000
#define CFERR_MAXLESSTHANMIN     0x2002
#define CFERR_NOFONTS            0x2001
#define FRERR_BUFFERLENGTHZERO   0x4001

typedef struct akari_CHOOSECOLORW {
    DWORD lStructSize;
    HWND hwndOwner;
    HINSTANCE hInstance;
    COLORREF rgbResult;
    COLORREF *lpCustColors;
    DWORD Flags;
    LPARAM lCustData;
    void *lpfnHook;
    LPCWSTR lpTemplateName;
} CHOOSECOLORW, *LPCHOOSECOLORW;

typedef struct akari_CHOOSEFONTW {
    DWORD lStructSize;
    HWND hwndOwner;
    HDC hDC;
    LPLOGFONTW lpLogFont;
    INT iPointSize;
    DWORD Flags;
    DWORD rgbColors;
    LPARAM lCustData;
    void *lpfnHook;
    LPCWSTR lpTemplateName;
    HINSTANCE hInstance;
    LPWSTR lpszStyle;
    WORD nFontType;
    WORD ___MISSING_ALIGNMENT__;
    INT nSizeMin;
    INT nSizeMax;
} CHOOSEFONTW, *LPCHOOSEFONTW;

typedef struct akari_PRINTDLGW {
    DWORD lStructSize;
    HWND hwndOwner;
    HGLOBAL hDevMode;
    HGLOBAL hDevNames;
    HDC hDC;
    DWORD Flags;
    WORD nFromPage;
    WORD nToPage;
    WORD nMinPage;
    WORD nMaxPage;
    WORD nCopies;
    HINSTANCE hInstance;
    LPARAM lCustData;
    void *lpfnPrintHook;
    void *lpfnSetupHook;
    LPCWSTR lpPrintTemplateName;
    LPCWSTR lpSetupTemplateName;
    HGLOBAL hPrintTemplate;
    HGLOBAL hSetupTemplate;
} PRINTDLGW, *LPPRINTDLGW;

typedef struct akari_DEVNAMES {
    WORD wDriverOffset;
    WORD wDeviceOffset;
    WORD wOutputOffset;
    WORD wDefault;
} DEVNAMES, *LPDEVNAMES;

typedef struct akari_PAGESETUPDLGW {
    DWORD lStructSize;
    HWND hwndOwner;
    HGLOBAL hDevMode;
    HGLOBAL hDevNames;
    DWORD Flags;
    POINT ptPaperSize;
    RECT rtMinMargin;
    RECT rtMargin;
    HINSTANCE hInstance;
    LPARAM lCustData;
    void *lpfnPageSetupHook;
    void *lpfnPagePaintHook;
    LPCWSTR lpPageSetupTemplateName;
    HGLOBAL hPageSetupTemplate;
} PAGESETUPDLGW, *LPPAGESETUPDLGW;

typedef UINT (CALLBACK *LPPRINTHOOKPROC)(HWND, UINT, WPARAM, LPARAM);
typedef UINT (CALLBACK *LPSETUPHOOKPROC)(HWND, UINT, WPARAM, LPARAM);

WINBASEAPI BOOL WINAPI ChooseColor(CHOOSECOLORW *lpcc);
WINBASEAPI BOOL WINAPI ChooseFontW(LPCHOOSEFONTW lpcf);
WINBASEAPI DWORD WINAPI CommDlgExtendedError(VOID);
WINBASEAPI BOOL WINAPI PageSetupDlgW(LPPAGESETUPDLGW);
WINBASEAPI BOOL WINAPI PrintDlg(LPPRINTDLGW lppd);

#define PRINTDLG PrintDlg


#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_COMMDLG_H */
