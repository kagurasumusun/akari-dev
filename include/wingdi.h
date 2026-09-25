/* Akari WinCE Development API Surface
 * Independently authored declarations for linking Windows CE 6.0 programs.
 * This is an API surface only: not an OS, BSP, OAK, SDK component, or
 * Platform Builder redistribution, and not a copy of upstream source.
 * CE calling convention: stdcall is cdecl, and DLL export names are
 * undecorated. TCHAR is a 16-bit WCHAR. Layouts that differ from desktop
 * Win32 (CRITICAL_SECTION, WIN32_FIND_DATAW, BY_HANDLE_FILE_INFORMATION,
 * OVERLAPPED) follow the CE 6.0 ABI.
 */

#ifndef AKARI_WINGDI_H
#define AKARI_WINGDI_H
#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LF_FACESIZE 32
#define LF_FULLFACESIZE 64

typedef struct tagLOGFONTW {
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
} LOGFONTW, *PLOGFONTW, *NPLOGFONTW, *LPLOGFONTW;
typedef LOGFONTW LOGFONT;
typedef LPLOGFONTW LPLOGFONT;

typedef struct tagBITMAPINFOHEADER {
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

typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD, *LPRGBQUAD;

typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
} BITMAPINFO, *PBITMAPINFO, *LPBITMAPINFO;

typedef struct tagBITMAP {
    LONG bmType;
    LONG bmWidth;
    LONG bmHeight;
    LONG bmWidthBytes;
    WORD bmPlanes;
    WORD bmBitsPixel;
    LPVOID bmBits;
} BITMAP, *PBITMAP, *LPBITMAP;

typedef struct tagTEXTMETRICW {
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

typedef struct tagLOGBRUSH {
    UINT lbStyle;
    COLORREF lbColor;
    LONG lbHatch;
} LOGBRUSH, *PLOGBRUSH, *LPLOGBRUSH;

typedef struct tagLOGPEN {
    UINT lopnStyle;
    POINT lopnWidth;
    COLORREF lopnColor;
} LOGPEN, *PLOGPEN, *LPLOGPEN;

typedef struct tagPALETTEENTRY {
    BYTE peRed;
    BYTE peGreen;
    BYTE peBlue;
    BYTE peFlags;
} PALETTEENTRY, *PPALETTEENTRY, *LPPALETTEENTRY;

typedef struct tagLOGPALETTE {
    WORD palVersion;
    WORD palNumEntries;
    PALETTEENTRY palPalEntry[1];
} LOGPALETTE, *PLOGPALETTE, *LPLOGPALETTE;

#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g))) << 8) | (((DWORD)(BYTE)(b)) << 16)))
#define GetRValue(rgb) (LOBYTE(rgb))
#define GetGValue(rgb) (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) (LOBYTE((rgb) >> 16))

#define HORZRES 8
#define TA_LEFT 0
#define LTGRAY_BRUSH 1
#define BS_INDEXED 4
#define BI_BITFIELDS 3L
#define PC_WIDESTYLED 64
#define BS_NULL 1
#define OPAQUE 2
#define FW_EXTRALIGHT 200
#define ASPECTX 40
#define BS_DIBPATTERN 5
#define GDI_ERROR (0xFFFFFFFFL)
#define NULL_PEN 8
#define BLACK_PEN 7
#define ETO_RTLREADING 0x0080
#define R2_BLACK 1
#define WHITENESS (DWORD)0x00FF0062
#define ETO_OPAQUE 0x0002
#define TA_TOP 0
#define TRANSPARENT 1
#define PS_DASH 1
#define NOTSRCERASE (DWORD)0x001100A6
#define R2_MERGENOTPEN 12
#define DRAFT_QUALITY 1
#define TA_RTLREADING 256
#define R2_WHITE 16
#define ANTIALIASED_QUALITY 4
#define OUT_RASTER_PRECIS 6
#define ETO_IGNORELANGUAGE 0x1000
#define DIB_RGB_COLORS 0
#define PC_WIDE 16
#define FW_DONTCARE 0
#define BLACK_BRUSH 4
#define PC_NONE 0
#define FW_NORMAL 400
#define SYSTEM_FONT 13
#define WHITE_BRUSH 0
#define BITSPIXEL 12
#define R2_XORPEN 7
#define PC_INTERIORS 128
#define ETO_CLIPPED 0x0004
#define MERGECOPY (DWORD)0x00C000CA
#define SRCAND (DWORD)0x008800C6
#define PS_SOLID 0
#define BS_DIBPATTERN8X8 8
#define FW_THIN 100
#define BS_DIBPATTERNPT 6
#define R2_NOT 6
#define R2_NOTCOPYPEN 4
#define ASPECTXY 44
#define FW_HEAVY 900
#define ANSI_CHARSET 0
#define MERGEPAINT (DWORD)0x00BB0226
#define PS_NULL 5
#define NONANTIALIASED_QUALITY 3
#define OUT_DEFAULT_PRECIS 0
#define FW_BOLD 700
#define DEFAULT_PITCH 0
#define NUMBRUSHES 16
#define R2_NOTMERGEPEN 2
#define DEFAULT_CHARSET 1
#define R2_MASKNOTPEN 3
#define NOTSRCCOPY (DWORD)0x00330008
#define TA_CENTER 6
#define FW_MEDIUM 500
#define BI_ALPHABITFIELDS 6L
#define CLIP_DEFAULT_PRECIS 0
#define BS_PATTERN8X8 7
#define SRCINVERT (DWORD)0x00660046
#define ASPECTY 42
#define PC_STYLED 32
#define R2_MERGEPEN 15
#define PLANES 14
#define R2_NOTMASKPEN 8
#define GRAY_BRUSH 2
#define DKGRAY_BRUSH 3
#define PC_RECTANGLE 2
#define OUT_STRING_PRECIS 1
#define PC_EXPLICIT 0x02
#define R2_NOP 11
#define R2_COPYPEN 13
#define FW_SEMIBOLD 600
#define DSTINVERT (DWORD)0x00550009
#define R2_MERGEPENNOT 14
#define PC_POLYGON 1
#define DEFAULT_PALETTE 15
#define BS_MONOPATTERN 9
#define CLIP_STROKE_PRECIS 2
#define FW_LIGHT 300
#define CLEARTYPE_QUALITY 5
#define BI_FOURCC 7L
#define LOGPIXELSY 90
#define PC_TRAPEZOID 4
#define TA_RIGHT 2
#define BI_RGB 0
#define HALFTONE 4
#define CLR_INVALID 0xFFFFFFFF
#define BS_HOLLOW BS_NULL
#define SRCERASE (DWORD)0x00440328
#define PC_SCANLINE 8
#define VERTSIZE 6
#define PATCOPY (DWORD)0x00F00021
#define TA_BASELINE 24
#define VERTRES 10
#define R2_NOTXORPEN 10
#define HORZSIZE 4
#define FW_EXTRABOLD 800
#define R2_MASKPENNOT 5
#define LOGPIXELSX 88
#define SRCCOPY (DWORD)0x00CC0020
#define DEFAULT_QUALITY 0
#define NUMPENS 18
#define BLACKONWHITE 1
#define PATINVERT (DWORD)0x005A0049
#define NUMCOLORS 24
#define R2_MASKPEN 9
#define TA_UPDATECP 1
#define CLEARTYPE_COMPAT_QUALITY 6
#define BS_PATTERN 3
#define PATPAINT (DWORD)0x00FB0A09
#define BI_SRCPREROTATE 0x8000
#define TA_NOUPDATECP 0
#define SRCPAINT (DWORD)0x00EE0086
#define BS_SOLID 0
#define NUMFONTS 22
#define NULL_BRUSH 5
#define BLACKNESS (DWORD)0x00000042
#define WHITE_PEN 6
#define DIB_PAL_COLORS 1
#define PC_RESERVED 0x01
#define PC_WINDPOLYGON 4
#define COLORONCOLOR 3
#define R2_LAST 16
#define TA_BOTTOM 8
#define CLIP_CHARACTER_PRECIS 1
#define HOLLOW_BRUSH NULL_BRUSH
#define TA_ALIGNMASK (TA_BASELINE | TA_CENTER )
#define TA_MASK (TA_BASELINE | TA_CENTER |TA_UPDATECP |TA_RTLREADING)

AKARI_IMPORT HDC WINAPI CreateCompatibleDC(HDC) AKARI_NAME(CreateCompatibleDC);
AKARI_IMPORT BOOL WINAPI DeleteDC(HDC) AKARI_NAME(DeleteDC);
AKARI_IMPORT BOOL WINAPI DeleteObject(HGDIOBJ) AKARI_NAME(DeleteObject);
AKARI_IMPORT COLORREF WINAPI GetBkColor(HDC) AKARI_NAME(GetBkColor);
AKARI_IMPORT int WINAPI GetBkMode(HDC) AKARI_NAME(GetBkMode);
AKARI_IMPORT HGDIOBJ WINAPI GetCurrentObject(HDC,UINT) AKARI_NAME(GetCurrentObject);
AKARI_IMPORT int WINAPI GetDeviceCaps(HDC,int) AKARI_NAME(GetDeviceCaps);
AKARI_IMPORT int WINAPI GetObjectW(HGDIOBJ, int, LPVOID) AKARI_NAME(GetObjectW);
AKARI_IMPORT DWORD WINAPI GetObjectType(HGDIOBJ h) AKARI_NAME(GetObjectType);
AKARI_IMPORT HGDIOBJ WINAPI GetStockObject(int) AKARI_NAME(GetStockObject);
AKARI_IMPORT COLORREF WINAPI GetTextColor(HDC) AKARI_NAME(GetTextColor);
AKARI_IMPORT HGDIOBJ WINAPI SelectObject(HDC,HGDIOBJ) AKARI_NAME(SelectObject);
AKARI_IMPORT COLORREF WINAPI SetBkColor(HDC,COLORREF) AKARI_NAME(SetBkColor);
AKARI_IMPORT int WINAPI SetBkMode(HDC,int) AKARI_NAME(SetBkMode);
AKARI_IMPORT COLORREF WINAPI SetTextColor(HDC,COLORREF) AKARI_NAME(SetTextColor);
AKARI_IMPORT UINT WINAPI GetDIBColorTable(HDC,UINT,UINT,RGBQUAD *) AKARI_NAME(GetDIBColorTable);
AKARI_IMPORT UINT WINAPI SetDIBColorTable(HDC,UINT,UINT,CONST RGBQUAD *) AKARI_NAME(SetDIBColorTable);
AKARI_IMPORT BOOL WINAPI SetViewportOrgEx(HDC,int,int,LPPOINT) AKARI_NAME(SetViewportOrgEx);
AKARI_IMPORT BOOL WINAPI SetWindowOrgEx(HDC,int,int,LPPOINT) AKARI_NAME(SetWindowOrgEx);
AKARI_IMPORT BOOL WINAPI GetWindowOrgEx(HDC,LPPOINT) AKARI_NAME(GetWindowOrgEx);
AKARI_IMPORT BOOL WINAPI GetWindowExtEx(HDC,LPSIZE) AKARI_NAME(GetWindowExtEx);
AKARI_IMPORT BOOL WINAPI OffsetViewportOrgEx(HDC hdc, int x, int y, LPPOINT lppt) AKARI_NAME(OffsetViewportOrgEx);
AKARI_IMPORT BOOL WINAPI GetViewportOrgEx(HDC,LPPOINT) AKARI_NAME(GetViewportOrgEx);
AKARI_IMPORT BOOL WINAPI GetViewportExtEx(HDC,LPSIZE) AKARI_NAME(GetViewportExtEx);
AKARI_IMPORT HBRUSH WINAPI CreatePatternBrush(HBITMAP) AKARI_NAME(CreatePatternBrush);
AKARI_IMPORT HPEN WINAPI CreatePen(int, int, COLORREF) AKARI_NAME(CreatePen);
AKARI_IMPORT BOOL WINAPI FillRgn(HDC, HRGN, HBRUSH) AKARI_NAME(FillRgn);
AKARI_IMPORT int WINAPI SetROP2(HDC, int) AKARI_NAME(SetROP2);
AKARI_IMPORT int WINAPI GetROP2(HDC) AKARI_NAME(GetROP2);
AKARI_IMPORT HBRUSH WINAPI CreateDIBPatternBrushPt(CONST VOID *,UINT) AKARI_NAME(CreateDIBPatternBrushPt);
AKARI_IMPORT HPEN WINAPI CreatePenIndirect(CONST LOGPEN *) AKARI_NAME(CreatePenIndirect);
AKARI_IMPORT HBRUSH WINAPI CreateSolidBrush(COLORREF) AKARI_NAME(CreateSolidBrush);
AKARI_IMPORT BOOL WINAPI DrawEdge(HDC,RECT *,UINT,UINT) AKARI_NAME(DrawEdge);
AKARI_IMPORT BOOL WINAPI DrawFocusRect(HDC,CONST RECT *) AKARI_NAME(DrawFocusRect);
AKARI_IMPORT BOOL WINAPI Ellipse(HDC,int,int,int,int) AKARI_NAME(Ellipse);
AKARI_IMPORT int WINAPI FillRect(HDC,CONST RECT *,HBRUSH) AKARI_NAME(FillRect);
AKARI_IMPORT COLORREF WINAPI GetPixel(HDC,int,int) AKARI_NAME(GetPixel);
AKARI_IMPORT HBRUSH WINAPI GetSysColorBrush(int) AKARI_NAME(GetSysColorBrush);
AKARI_IMPORT BOOL WINAPI Polygon(HDC hdc, CONST POINT * lppt, int c) AKARI_NAME(Polygon);
AKARI_IMPORT BOOL WINAPI Polyline(HDC hdc, CONST POINT * lppt, int c) AKARI_NAME(Polyline);
AKARI_IMPORT BOOL WINAPI Rectangle(HDC,int,int,int,int) AKARI_NAME(Rectangle);
AKARI_IMPORT BOOL WINAPI RoundRect(HDC,int,int,int,int,int,int) AKARI_NAME(RoundRect);
AKARI_IMPORT BOOL WINAPI SetBrushOrgEx(HDC hdc, int x, int y, LPPOINT lppt) AKARI_NAME(SetBrushOrgEx);
AKARI_IMPORT COLORREF WINAPI SetPixel(HDC,int,int,COLORREF) AKARI_NAME(SetPixel);
AKARI_IMPORT BOOL WINAPI MoveToEx(HDC,int,int,LPPOINT) AKARI_NAME(MoveToEx);
AKARI_IMPORT BOOL WINAPI LineTo(HDC,int,int) AKARI_NAME(LineTo);
AKARI_IMPORT BOOL WINAPI GetCurrentPositionEx(HDC,LPPOINT) AKARI_NAME(GetCurrentPositionEx);
AKARI_IMPORT HBITMAP WINAPI CreateBitmap(int,int,UINT,UINT,CONST VOID *) AKARI_NAME(CreateBitmap);
AKARI_IMPORT HBITMAP WINAPI CreateCompatibleBitmap(HDC,int,int) AKARI_NAME(CreateCompatibleBitmap);
AKARI_IMPORT LONG WINAPI SetBitmapBits(HBITMAP,DWORD,CONST VOID*) AKARI_NAME(SetBitmapBits);
AKARI_IMPORT int WINAPI CombineRgn(HRGN,HRGN,HRGN,int) AKARI_NAME(CombineRgn);
AKARI_IMPORT HRGN WINAPI CreateRectRgnIndirect(CONST RECT *) AKARI_NAME(CreateRectRgnIndirect);
AKARI_IMPORT BOOL WINAPI EqualRgn(HRGN,HRGN) AKARI_NAME(EqualRgn);
AKARI_IMPORT int WINAPI ExcludeClipRect(HDC,int,int,int,int) AKARI_NAME(ExcludeClipRect);
AKARI_IMPORT int WINAPI GetClipBox(HDC,LPRECT) AKARI_NAME(GetClipBox);
AKARI_IMPORT int WINAPI GetClipRgn(HDC,HRGN) AKARI_NAME(GetClipRgn);
AKARI_IMPORT int WINAPI GetRgnBox(HRGN,RECT *) AKARI_NAME(GetRgnBox);
AKARI_IMPORT int WINAPI IntersectClipRect(HDC,int,int,int,int) AKARI_NAME(IntersectClipRect);
AKARI_IMPORT int WINAPI OffsetRgn(HRGN,int,int) AKARI_NAME(OffsetRgn);
AKARI_IMPORT BOOL WINAPI PtInRegion(HRGN,int,int) AKARI_NAME(PtInRegion);
AKARI_IMPORT BOOL WINAPI RectInRegion(HRGN,CONST RECT *) AKARI_NAME(RectInRegion);
AKARI_IMPORT int WINAPI SelectClipRgn(HDC,HRGN) AKARI_NAME(SelectClipRgn);
AKARI_IMPORT HRGN WINAPI CreateRectRgn(int, int, int, int) AKARI_NAME(CreateRectRgn);
AKARI_IMPORT BOOL WINAPI RectVisible(HDC, CONST RECT *) AKARI_NAME(RectVisible);
AKARI_IMPORT BOOL WINAPI SetRectRgn(HRGN, int, int, int, int) AKARI_NAME(SetRectRgn);
AKARI_IMPORT BOOL WINAPI BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD) AKARI_NAME(BitBlt);
AKARI_IMPORT BOOL WINAPI MaskBlt(HDC,int,int,int,int,HDC,int,int,HBITMAP,int,int,DWORD) AKARI_NAME(MaskBlt);
AKARI_IMPORT BOOL WINAPI PatBlt(HDC,int,int,int,int,DWORD) AKARI_NAME(PatBlt);
AKARI_IMPORT BOOL WINAPI StretchBlt(HDC,int,int,int,int,HDC,int,int,int,int,DWORD) AKARI_NAME(StretchBlt);
AKARI_IMPORT BOOL WINAPI InvertRect(HDC hDC, CONST RECT * lprc) AKARI_NAME(InvertRect);
AKARI_IMPORT int WINAPI SetStretchBltMode(HDC, int) AKARI_NAME(SetStretchBltMode);
AKARI_IMPORT int WINAPI GetStretchBltMode(HDC) AKARI_NAME(GetStretchBltMode);
AKARI_IMPORT BOOL WINAPI StretchDIBits(HDC, int, int, int, int, int, int, int, int, CONST VOID *, CONST BITMAPINFO *, UINT, DWORD) AKARI_NAME(StretchDIBits);
AKARI_IMPORT int WINAPI SetDIBitsToDevice(HDC,int, int,DWORD,DWORD,int,int,UINT,UINT,CONST VOID *,CONST BITMAPINFO *, UINT) AKARI_NAME(SetDIBitsToDevice);
AKARI_IMPORT BOOL WINAPI TransparentImage(HDC,int,int,int,int,HANDLE,int,int,int,int,COLORREF) AKARI_NAME(TransparentImage);
AKARI_IMPORT int WINAPI AddFontResourceW(LPCWSTR) AKARI_NAME(AddFontResourceW);
AKARI_IMPORT HFONT WINAPI CreateFontIndirectW(CONST LOGFONTW *) AKARI_NAME(CreateFontIndirectW);
AKARI_IMPORT BOOL WINAPI ExtTextOutW(HDC hdc, int x, int y, UINT options, CONST RECT * lprect, LPCWSTR lpString, UINT c, CONST INT * lpDx) AKARI_NAME(ExtTextOutW);
AKARI_IMPORT BOOL WINAPI RemoveFontResourceW(LPCWSTR) AKARI_NAME(RemoveFontResourceW);
AKARI_IMPORT UINT WINAPI SetTextAlign(HDC,UINT) AKARI_NAME(SetTextAlign);
AKARI_IMPORT UINT WINAPI GetTextAlign(HDC) AKARI_NAME(GetTextAlign);
AKARI_IMPORT int WINAPI SetTextCharacterExtra(HDC,int) AKARI_NAME(SetTextCharacterExtra);
AKARI_IMPORT int WINAPI GetTextCharacterExtra(HDC) AKARI_NAME(GetTextCharacterExtra);
AKARI_IMPORT DWORD WINAPI GetFontData(HDC,DWORD,DWORD,LPVOID,DWORD) AKARI_NAME(GetFontData);
AKARI_IMPORT HANDLE WINAPI AddFontMemResourceEx(PVOID,DWORD,PVOID,DWORD*) AKARI_NAME(AddFontMemResourceEx);
AKARI_IMPORT BOOL WINAPI RemoveFontMemResourceEx(HANDLE) AKARI_NAME(RemoveFontMemResourceEx);
AKARI_IMPORT int WINAPI GetTextFaceW(HDC hdc, int c, LPWSTR lpName) AKARI_NAME(GetTextFaceW);
AKARI_IMPORT BOOL WINAPI EnableEUDC(BOOL) AKARI_NAME(EnableEUDC);
AKARI_IMPORT HBITMAP WINAPI CreateDIBSection(HDC,CONST BITMAPINFO *,UINT,VOID **,HANDLE,DWORD) AKARI_NAME(CreateDIBSection);
AKARI_IMPORT BOOL WINAPI RestoreDC(HDC,int) AKARI_NAME(RestoreDC);
AKARI_IMPORT int WINAPI SaveDC(HDC) AKARI_NAME(SaveDC);
AKARI_IMPORT int WINAPI ExtEscape(HDC, int, int, LPCSTR, int, LPSTR) AKARI_NAME(ExtEscape);
AKARI_IMPORT HPALETTE WINAPI CreatePalette(CONST LOGPALETTE *) AKARI_NAME(CreatePalette);
AKARI_IMPORT UINT WINAPI GetNearestPaletteIndex(HPALETTE, COLORREF) AKARI_NAME(GetNearestPaletteIndex);
AKARI_IMPORT UINT WINAPI RealizePalette(HDC) AKARI_NAME(RealizePalette);
AKARI_IMPORT HPALETTE WINAPI SelectPalette(HDC, HPALETTE, BOOL) AKARI_NAME(SelectPalette);
AKARI_IMPORT UINT WINAPI SetPaletteEntries(HPALETTE, UINT, UINT, CONST PALETTEENTRY *) AKARI_NAME(SetPaletteEntries);
AKARI_IMPORT COLORREF WINAPI GetNearestColor(HDC, COLORREF) AKARI_NAME(GetNearestColor);
AKARI_IMPORT int WINAPI AbortDoc(HDC) AKARI_NAME(AbortDoc);
AKARI_IMPORT int WINAPI EndDoc(HDC) AKARI_NAME(EndDoc);
AKARI_IMPORT int WINAPI EndPage(HDC) AKARI_NAME(EndPage);
AKARI_IMPORT int WINAPI StartPage(HDC) AKARI_NAME(StartPage);
AKARI_IMPORT DWORD WINAPI SetLayout(HDC , DWORD) AKARI_NAME(SetLayout);
AKARI_IMPORT DWORD WINAPI GetLayout(HDC) AKARI_NAME(GetLayout);
AKARI_IMPORT int WINAPI MulDiv(int,int,int) AKARI_NAME(MulDiv);

#define AddFontResource AddFontResourceW
#define CreateFontIndirect CreateFontIndirectW
#define ExtTextOut ExtTextOutW
#define GetObject GetObjectW
#define GetTextFace GetTextFaceW
#define RemoveFontResource RemoveFontResourceW

#ifdef __cplusplus
}
#endif
#endif
