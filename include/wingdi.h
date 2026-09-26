/* GDI. Original text. Exported by coredll.dll. */
#ifndef AKARI_WCE_WINGDI_H
#define AKARI_WCE_WINGDI_H

#include "winbase.h"

typedef HANDLE HGDIOBJ;

#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g)) << 8)) | \
                                 (((DWORD)(BYTE)(b)) << 16)))
#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb) >> 16))

typedef DWORD COLORREF;
typedef DWORD *LPCOLORREF;

#define LF_FACESIZE 32
#define LF_FULLFACESIZE 64

typedef struct akari_LOGFONTW {
    LONG lfHeight;
    LONG lfWidth;
    LONG lfEscapement;
    LONG lfOrientation;
    LONG lfWeight;
    BYTE lfItalic;
    BYTE lfUnderline;
    BYTE lfStrikeOut;
    BYTE lfCharSet;
    BYTE lfOutPrecision;
    BYTE lfClipPrecision;
    BYTE lfQuality;
    BYTE lfPitchAndFamily;
    WCHAR lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW, *LPLOGFONTW;

typedef struct akari_TEXTMETRICW {
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    WCHAR tmFirstChar;
    WCHAR tmLastChar;
    WCHAR tmDefaultChar;
    WCHAR tmBreakChar;
    BYTE tmItalic;
    BYTE tmUnderlined;
    BYTE tmStruckOut;
    BYTE tmPitchAndFamily;
    BYTE tmCharSet;
} TEXTMETRICW, *PTEXTMETRICW, *LPTEXTMETRICW;

typedef struct akari_RGBQUAD { BYTE rgbBlue; BYTE rgbGreen; BYTE rgbRed; BYTE rgbReserved; }
    RGBQUAD;

typedef struct akari_BITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER, *LPBITMAPINFOHEADER;

typedef struct akari_BITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
} BITMAPINFO, *PBITMAPINFO, *LPBITMAPINFO;

typedef struct akari_BITMAP {
    LONG bmType;
    LONG bmWidth;
    LONG bmHeight;
    LONG bmWidthBytes;
    WORD bmPlanes;
    WORD bmBitsPixel;
    LPVOID bmBits;
} BITMAP, *PBITMAP, *LPBITMAP;

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

#define ANSI_CHARSET        0
#define DEFAULT_CHARSET     1
#define SYMBOL_CHARSET      2
#define SHIFTJIS_CHARSET    128
#define HANGEUL_CHARSET     129
#define CHINESEBIG5_CHARSET 136
#define OEM_CHARSET         255

#define DEFAULT_PITCH   0
#define FIXED_PITCH     1
#define VARIABLE_PITCH  2
#define FF_DONTCARE     (0 << 4)
#define FF_ROMAN        (1 << 4)
#define FF_SWISS        (2 << 4)
#define FF_MODERN       (3 << 4)

#define FW_DONTCARE 0
#define FW_NORMAL   400
#define FW_BOLD     700

#define MM_TEXT        1
#define MM_LOMETRIC    2
#define MM_HIMETRIC    3
#define MM_LOENGLISH   4
#define MM_HIENGLISH   5
#define MM_TWIPS       6
#define MM_ISOTROPIC   7
#define MM_ANISOTROPIC 8

#define TRANSPARENT 1
#define OPAQUE      2

#define PS_SOLID  0
#define PS_DASH   1
#define PS_DOT    2
#define PS_NULL   5

#define BS_SOLID   0
#define BS_NULL    1
#define BS_HOLLOW  BS_NULL

#define SRCCOPY     0x00CC0020
#define SRCPAINT    0x00EE0086
#define SRCAND      0x008800C6
#define SRCINVERT   0x00660046
#define PATCOPY     0x00F00021
#define BLACKNESS   0x00000042
#define WHITENESS   0x00FF0062

#define TA_NOUPDATECP 0
#define TA_UPDATECP   1
#define TA_LEFT       0
#define TA_RIGHT      2
#define TA_CENTER     6
#define TA_TOP        0
#define TA_BOTTOM     8
#define TA_BASELINE   24

#define HORZSIZE   4
#define VERTSIZE   6
#define LOGPIXELSX 88
#define LOGPIXELSY 90

#define DT_TOP          0x00000000
#define DT_LEFT         0x00000000
#define DT_CENTER       0x00000001
#define DT_RIGHT        0x00000002
#define DT_VCENTER      0x00000004
#define DT_BOTTOM       0x00000008
#define DT_WORDBREAK    0x00000010
#define DT_SINGLELINE   0x00000020
#define DT_NOPREFIX     0x00000800

WINBASEAPI HDC WINAPI GetDC(HWND hWnd);
WINBASEAPI HDC WINAPI GetWindowDC(HWND hWnd);
WINBASEAPI int WINAPI ReleaseDC(HWND hWnd, HDC hDC);
WINBASEAPI HDC WINAPI CreateCompatibleDC(HDC hdc);
WINBASEAPI BOOL WINAPI DeleteDC(HDC hdc);
WINBASEAPI HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ hgdiobj);
WINBASEAPI BOOL WINAPI DeleteObject(HGDIOBJ hObject);
WINBASEAPI HPEN WINAPI CreatePen(int nPenStyle, int nWidth, COLORREF crColor);
WINBASEAPI HPEN WINAPI CreatePenIndirect(const void *lplgpn);
WINBASEAPI HBRUSH WINAPI CreateSolidBrush(COLORREF crColor);
WINBASEAPI HBITMAP WINAPI CreateCompatibleBitmap(HDC hdc, int nWidth, int nHeight);
/* Windows CE builds fonts from a LOGFONT only; there is no CreateFont. */
WINBASEAPI HFONT WINAPI CreateFontIndirectW(const LOGFONTW *lplf);
WINBASEAPI COLORREF WINAPI SetTextColor(HDC hdc, COLORREF crColor);
WINBASEAPI COLORREF WINAPI SetBkColor(HDC hdc, COLORREF crColor);
WINBASEAPI int WINAPI SetBkMode(HDC hdc, int iBkMode);
/* TextOut is not an export on Windows CE; it is ExtTextOut with no options. */
#define TextOutW(hdc, x, y, lpString, cchString) \
        ExtTextOutW((hdc), (x), (y), 0, NULL, (lpString), (cchString), NULL)
#define TextOut TextOutW
WINBASEAPI BOOL WINAPI ExtTextOutW(HDC hdc, int x, int y, UINT fuOptions, const RECT *lprc,
    LPCWSTR lpString, UINT cchString, const INT *lpDx);
WINBASEAPI int WINAPI DrawTextW(HDC hdc, LPCWSTR lpString, int nCount, LPRECT lpRect,
    UINT uFormat);
WINBASEAPI BOOL WINAPI GetTextMetricsW(HDC hdc, LPTEXTMETRICW lptm);
/* GetTextExtentPoint32 is not an export; the "ExPoint" form is, and passing a
 * maximum extent larger than any real string reproduces the simpler call. */
#define GetTextExtentPoint32W(hdc, lpString, c, lpSize) \
        GetTextExtentExPointW((hdc), (lpString), (c), 0x7FFFFFFF, NULL, NULL, (lpSize))
#define GetTextExtentPoint32 GetTextExtentPoint32W
WINBASEAPI BOOL WINAPI GetTextExtentExPointW(HDC hdc, LPCWSTR lpszStr, int cchString,
    int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize);
WINBASEAPI UINT WINAPI SetTextAlign(HDC hdc, UINT fMode);
WINBASEAPI BOOL WINAPI MoveToEx(HDC hdc, int X, int Y, LPPOINT lpPoint);
WINBASEAPI BOOL WINAPI LineTo(HDC hdc, int nXEnd, int nYEnd);
WINBASEAPI BOOL WINAPI Rectangle(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
WINBASEAPI BOOL WINAPI Ellipse(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
WINBASEAPI BOOL WINAPI RoundRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect, int nWidth, int nHeight);
WINBASEAPI BOOL WINAPI Polygon(HDC hdc, const POINT *lpPoints, int nCount);
WINBASEAPI BOOL WINAPI Polyline(HDC hdc, const POINT *lpPoints, int nCount);
WINBASEAPI BOOL WINAPI SetPixel(HDC hdc, int x, int y, COLORREF crColor);
WINBASEAPI COLORREF WINAPI GetPixel(HDC hdc, int nXPos, int nYPos);
WINBASEAPI int WINAPI FillRect(HDC hDC, const RECT *lprc, HBRUSH hbr);
WINBASEAPI BOOL WINAPI InvertRect(HDC hDC, const RECT *lprc);
WINBASEAPI BOOL WINAPI BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
    HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
WINBASEAPI BOOL WINAPI StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc,
    int nWidthSrc, int nHeightSrc, DWORD dwRop);
WINBASEAPI HBITMAP WINAPI CreateBitmap(int nWidth, int nHeight, UINT cPlanes,
    UINT cBitsPerPel, const VOID *lpvBits);
WINBASEAPI BOOL WINAPI SetDIBitsToDevice(HDC hdc, int XDest, int YDest, DWORD dwWidth,
    DWORD dwHeight, int XSrc, int YSrc, UINT uStartScan, UINT cScanLines,
    const VOID *lpvBits, const BITMAPINFO *lpbmi, UINT fuColorUse);
WINBASEAPI int WINAPI GetDeviceCaps(HDC hdc, int nIndex);
WINBASEAPI int WINAPI SaveDC(HDC hdc);
WINBASEAPI BOOL WINAPI RestoreDC(HDC hdc, int nSavedDC);
/* Windows CE device contexts only support MM_TEXT, so the mapping mode is a
 * constant rather than an export. */
static __inline int SetMapMode(HDC hdc, int fnMapMode)
{
    (void)hdc; (void)fnMapMode;
    return MM_TEXT;
}
static __inline int GetMapMode(HDC hdc) { (void)hdc; return MM_TEXT; }
WINBASEAPI COLORREF WINAPI GetTextColor(HDC hdc);
#if (_WIN32_WCE >= 0x600)
WINBASEAPI int WINAPI MulDiv(int nNumber, int nNumerator, int nDenominator);
#endif
WINBASEAPI BOOL WINAPI GetObjectW(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject);
WINBASEAPI int WINAPI SetROP2(HDC hdc, int fnDrawMode);

#endif /* AKARI_WCE_WINGDI_H */
