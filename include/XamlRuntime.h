/*
 * XamlRuntime.h -- Windows CE book-surface header of record (Akari API)
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (learn.microsoft.com previous-versions archive; page ids cited per
 * record).  The pages in this book print "Header: XamlRuntime.h".
 *
 * Created in M135: tools/coverage-audit.py had been reporting this header
 * in its "header not shipped here" bucket -- the pages name it, include/
 * did not contain it, and no audit downstream could act on a gap with no
 * file to put the declarations in.
 */

#ifndef AKARI_XAMLRUNTIME_H
#define AKARI_XAMLRUNTIME_H

#if _WIN32_WCE >= 0x0600   /* every declaration below is documented
 * from this generation or later (each block's
 * citation comment carries the page's own
 * OS Versions row; tools/gen-guard.py's
 * mapping) */

#include "Windef.h"    /* base Win32 types */
#include "Winnt.h"     /* HRESULT, LARGE_INTEGER, GUID */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


/* ee501486 XRLineStackingStrategy: page print
 * enum XRLineStackingStrategy{ XRLineStackingStrategy_MaxHeight=0, XRLineStackingStrategy_BlockLineHeight=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRLineStackingStrategy {
    XRLineStackingStrategy_MaxHeight = 0,
    XRLineStackingStrategy_BlockLineHeight = 1
} XRLineStackingStrategy;

/* ee501505 XRTextWrapping: page print
 * enum XRTextWrapping{ XRTextWrapping_NoWrap = 1, XRTextWrapping_Wrap = 2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRTextWrapping {
    XRTextWrapping_NoWrap = 1,
    XRTextWrapping_Wrap = 2
} XRTextWrapping;

/* ee501509 XRFontWeight: page print
 * enum XRFontWeight{ XRFontWeight_Thin=100, XRFontWeight_ExtraLight=200, XRFontWeight_Light=300, XRFontWeight_Normal=400, XRFontWeight_Medium=500, XRFon
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRFontWeight {
    XRFontWeight_Thin = 100,
    XRFontWeight_ExtraLight = 200,
    XRFontWeight_Light = 300,
    XRFontWeight_Normal = 400,
    XRFontWeight_Medium = 500,
    XRFontWeight_SemiBold = 600,
    XRFontWeight_Bold = 700,
    XRFontWeight_ExtraBold = 800,
    XRFontWeight_Black = 900,
    XRFontWeight_ExtraBlack = 950
} XRFontWeight;

/* ee501538 XRPenLineJoin: page print
 * enum XRPenLineJoin{ XRPenLineJoin_Miter=0, XRPenLineJoin_Bevel=1, XRPenLineJoin_Round=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRPenLineJoin {
    XRPenLineJoin_Miter = 0,
    XRPenLineJoin_Bevel = 1,
    XRPenLineJoin_Round = 2
} XRPenLineJoin;

/* ee501556 XRPoint: page print
 * struct XRPoint{ float x; float y; };
 * (Windows Embedded CE 6.0 R3) */
struct XRPoint {
    float x;
    float y;
};

/* ee501562 XRClockState: page print
 * enum XRClockState { XRClockState_Active=0, XRClockState_Filling=1, XRClockState_Stopped=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRClockState {
    XRClockState_Active = 0,
    XRClockState_Filling = 1,
    XRClockState_Stopped = 2
} XRClockState;

/* ee501619 XRColorInterpolationMode: page print
 * enum XRColorInterpolationMode{ XRColorInterpolationMode_ScRgbLinearInterpolation=0, XRColorInterpolationMode_SRgbLinearInterpolation=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRColorInterpolationMode {
    XRColorInterpolationMode_ScRgbLinearInterpolation = 0,
    XRColorInterpolationMode_SRgbLinearInterpolation = 1
} XRColorInterpolationMode;

/* ee501637 XRGridUnitType: page print
 * enum XRGridUnitType{ XRGridUnitType_Auto=0, XRGridUnitType_Pixel=1, XRGridUnitType_Star=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRGridUnitType {
    XRGridUnitType_Auto = 0,
    XRGridUnitType_Pixel = 1,
    XRGridUnitType_Star = 2
} XRGridUnitType;

/* ee501819 XRStretch: page print
 * enum XRStretch{ XRStretch_None=0, XRStretch_Fill=1, XRStretch_Uniform=2, XRStretch_UniformToFill=3 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRStretch {
    XRStretch_None = 0,
    XRStretch_Fill = 1,
    XRStretch_Uniform = 2,
    XRStretch_UniformToFill = 3
} XRStretch;

/* ee501839 XRStyleSimulations: page print
 * enum XRStyleSimulations{ XRStyleSimulations_None=0, XRStyleSimulations_BoldSimulation=1, XRStyleSimulations_ItalicSimulation=2, XRStyleSimulations_Bol
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRStyleSimulations {
    XRStyleSimulations_None = 0,
    XRStyleSimulations_BoldSimulation = 1,
    XRStyleSimulations_ItalicSimulation = 2,
    XRStyleSimulations_BoldItalicSimulation = 3
} XRStyleSimulations;

/* ee501840 XRGradientSpreadMethod: page print
 * enum XRGradientSpreadMethod{ XRGradientSpreadMethod_Pad=0, XRGradientSpreadMethod_Reflect=1, XRGradientSpreadMethod_Repeat=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRGradientSpreadMethod {
    XRGradientSpreadMethod_Pad = 0,
    XRGradientSpreadMethod_Reflect = 1,
    XRGradientSpreadMethod_Repeat = 2
} XRGradientSpreadMethod;

/* ee501855 XRThreeState: page print
 * enum XRThreeState { XRThreeState_Unchecked = 0, XRThreeState_Checked, XRThreeState_Indeterminate };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRThreeState {
    XRThreeState_Unchecked = 0,
    XRThreeState_Checked,
    XRThreeState_Indeterminate
} XRThreeState;

/* ee502118 XRPenLineCap: page print
 * enum XRPenLineCap{ XRPenLineCap_Flat=0, XRPenLineCap_Square=1, XRPenLineCap_Round=2, XRPenLineCap_Triangle=3 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRPenLineCap {
    XRPenLineCap_Flat = 0,
    XRPenLineCap_Square = 1,
    XRPenLineCap_Round = 2,
    XRPenLineCap_Triangle = 3
} XRPenLineCap;

/* ee502120 XRAlignmentY: page print
 * enum XRAlignmentY{ XRAlignmentY_Top=0, XRAlignmentY_Center=1, XRAlignmentY_Bottom=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRAlignmentY {
    XRAlignmentY_Top = 0,
    XRAlignmentY_Center = 1,
    XRAlignmentY_Bottom = 2
} XRAlignmentY;

/* ee502139 XRBrushMappingMode: page print
 * enum XRBrushMappingMode { XRBrushMappingMode_Absolute=0, XRBrushMappingMode_RelativeToBoundingBox=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRBrushMappingMode {
    XRBrushMappingMode_Absolute = 0,
    XRBrushMappingMode_RelativeToBoundingBox = 1
} XRBrushMappingMode;

/* ee502425 XRVerticalAlignment: page print
 * enum XRVerticalAlignment{ XRVerticalAlignment_Top=0, XRVerticalAlignment_Center=1, XRVerticalAlignment_Bottom=2, XRVerticalAlignment_Stretch=3 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRVerticalAlignment {
    XRVerticalAlignment_Top = 0,
    XRVerticalAlignment_Center = 1,
    XRVerticalAlignment_Bottom = 2,
    XRVerticalAlignment_Stretch = 3
} XRVerticalAlignment;

/* ee502426 XRVisibility: page print
 * enum XRVisibility{ XRVisibility_Visible = 0, XRVisibility_Collapsed = 1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRVisibility {
    XRVisibility_Visible = 0,
    XRVisibility_Collapsed = 1
} XRVisibility;

/* ee502439 XREventArgs: page print
 * struct XREventArgs{ UINT Size; };
 * (Windows Embedded CE 6.0 R3) */
struct XREventArgs {
    UINT Size;
};

/* ee502478 XRSweepDirection: page print
 * enum XRSweepDirection { XRSweepDirection_Counterclockwise=0, XRSweepDirection_Clockwise=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRSweepDirection {
    XRSweepDirection_Counterclockwise = 0,
    XRSweepDirection_Clockwise = 1
} XRSweepDirection;

/* ee502711 XRTextDecorationType: page print
 * enum XRTextDecorationType{ XRTextDecorationType_None=0, XRTextDecorationType_Underline=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRTextDecorationType {
    XRTextDecorationType_None = 0,
    XRTextDecorationType_Underline = 1
} XRTextDecorationType;

/* ee502747 XRTextAlignment: page print
 * enum XRTextAlignment{ XRTextAlignment_Center=0, XRTextAlignment_Left=1, XRTextAlignment_Right=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRTextAlignment {
    XRTextAlignment_Center = 0,
    XRTextAlignment_Left = 1,
    XRTextAlignment_Right = 2
} XRTextAlignment;

/* ee502981 XRCornerRadius: page print
 * struct XRCornerRadius{ float TopLeft; float TopRight; float BottomRight; float BottomLeft; };
 * (Windows Embedded CE 6.0 R3) */
struct XRCornerRadius {
    float TopLeft;
    float TopRight;
    float BottomRight;
    float BottomLeft;
};

/* ee502998 XRFontStretch: page print
 * enum XRFontStretch{ XRFontStretch_UltraCondensed=1, XRFontStretch_ExtraCondensed=2, XRFontStretch_Condensed=3, XRFontStretch_SemiCondensed=4, XRFontSt
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRFontStretch {
    XRFontStretch_UltraCondensed = 1,
    XRFontStretch_ExtraCondensed = 2,
    XRFontStretch_Condensed = 3,
    XRFontStretch_SemiCondensed = 4,
    XRFontStretch_Normal = 5,
    XRFontStretch_Medium = 5,
    XRFontStretch_SemiExpanded = 6,
    XRFontStretch_Expanded = 7,
    XRFontStretch_ExtraExpanded = 8,
    XRFontStretch_UltraExpanded = 9
} XRFontStretch;

/* ee503028 XRFillRule: page print
 * enum XRFillRule { XRFillRule_EvenOdd=0, XRFillRule_Nonzero=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRFillRule {
    XRFillRule_EvenOdd = 0,
    XRFillRule_Nonzero = 1
} XRFillRule;

/* ee503321 XRKeyboardNavigationMode: page print
 * enum XRKeyboardNavigationMode{ XRKeyboardNavigationMode_Local=0, XRKeyboardNavigationMode_Cycle=1, XRKeyboardNavigationMode_Once=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRKeyboardNavigationMode {
    XRKeyboardNavigationMode_Local = 0,
    XRKeyboardNavigationMode_Cycle = 1,
    XRKeyboardNavigationMode_Once = 2
} XRKeyboardNavigationMode;

/* ee503344 XRHorizontalAlignment: page print
 * enum XRHorizontalAlignment{ XRHorizontalAlignment_Left=0, XRHorizontalAlignment_Center=1, XRHorizontalAlignment_Right=2, XRHorizontalAlignment_Stretch
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRHorizontalAlignment {
    XRHorizontalAlignment_Left = 0,
    XRHorizontalAlignment_Center = 1,
    XRHorizontalAlignment_Right = 2,
    XRHorizontalAlignment_Stretch = 3
} XRHorizontalAlignment;

/* ee503559 XRThickness: page print
 * struct XRThickness{ float Left; float Top; float Right; float Bottom; };
 * (Windows Embedded CE 6.0 R3) */
struct XRThickness {
    float Left;
    float Top;
    float Right;
    float Bottom;
};

/* ee503573 XROrientation: page print
 * enum XROrientation{ XROrientation_Vertical=0, XROrientation_Horizontal=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XROrientation {
    XROrientation_Vertical = 0,
    XROrientation_Horizontal = 1
} XROrientation;

/* ee503585 XRScrollEventType: page print
 * enum XRScrollEventType{ XRScrollEventType_EndScroll = 8, XRScrollEventType_First = 6, XRScrollEventType_LargeDecrement = 2, XRScrollEventType_LargeInc
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRScrollEventType {
    XRScrollEventType_EndScroll = 8,
    XRScrollEventType_First = 6,
    XRScrollEventType_LargeDecrement = 2,
    XRScrollEventType_LargeIncrement = 3,
    XRScrollEventType_Last = 7,
    XRScrollEventType_SmallDecrement = 0,
    XRScrollEventType_SmallIncrement = 1,
    XRScrollEventType_ThumbPosition = 4,
    XRScrollEventType_ThumbTrack = 5
} XRScrollEventType;

/* ee503686 XRClickMode: page print
 * enum XRClickMode{ XRClickMode_Release = 0, XRClickMode_Press, XRClickMode_Hover, };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRClickMode {
    XRClickMode_Release = 0,
    XRClickMode_Press,
    XRClickMode_Hover
} XRClickMode;

/* ee503994 XRFillBehavior: page print
 * enum XRFillBehavior{ XRFillBehavior_HoldEnd=0, XRFillBehavior_Stop=1 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRFillBehavior {
    XRFillBehavior_HoldEnd = 0,
    XRFillBehavior_Stop = 1
} XRFillBehavior;

/* ee504017 XRAlignmentX: page print
 * enum XRAlignmentX{ XRAlignmentX_Left=0, XRAlignmentX_Center=1, XRAlignmentX_Right=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRAlignmentX {
    XRAlignmentX_Left = 0,
    XRAlignmentX_Center = 1,
    XRAlignmentX_Right = 2
} XRAlignmentX;

/* ee504059 XRSize: page print
 * struct XRSize{ float cx; float cy; };
 * (Windows Embedded CE 6.0 R3) */
struct XRSize {
    float cx;
    float cy;
};

/* ee504179 XRScrollBarVisibility: page print
 * enum XRScrollBarVisibility { XRScrollBarVisibility_Disabled = 0, XRScrollBarVisibility_Auto, XRScrollBarVisibility_Hidden, XRScrollBarVisibility_Visib
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRScrollBarVisibility {
    XRScrollBarVisibility_Disabled = 0,
    XRScrollBarVisibility_Auto,
    XRScrollBarVisibility_Hidden,
    XRScrollBarVisibility_Visible
} XRScrollBarVisibility;

/* ee504201 XRCursor: page print
 * enum XRCursor { XRCursor_Default = 0, XRCursor_Arrow = 1, XRCursor_Hand = 2, XRCursor_Wait = 3, XRCursor_IBeam = 4, XRCursor_Stylus = 5, XRCursor_Eras
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRCursor {
    XRCursor_Default = 0,
    XRCursor_Arrow = 1,
    XRCursor_Hand = 2,
    XRCursor_Wait = 3,
    XRCursor_IBeam = 4,
    XRCursor_Stylus = 5,
    XRCursor_Eraser = 6,
    XRCursor_SizeNS = 7,
    XRCursor_SizeWE = 8,
    XRCursor_None = 9
} XRCursor;

/* ee504428 XRRect: page print
 * struct XRRect{ float left; float top; float right; float bottom; };
 * (Windows Embedded CE 6.0 R3) */
struct XRRect {
    float left;
    float top;
    float right;
    float bottom;
};

/* ee504467 XRFontStyle: page print
 * enum XRFontStyle{ XRFontStyle_Normal=0, XRFontStyle_Oblique=1, XRFontStyle_Italic=2 };
 * (Windows Embedded CE 6.0 R3) */
typedef enum XRFontStyle {
    XRFontStyle_Normal = 0,
    XRFontStyle_Oblique = 1,
    XRFontStyle_Italic = 2
} XRFontStyle;

/* ee504494 XRGridLength: page print
 * struct XRGridLength{ float UnitValue; XRGridUnitType UnitType; };
 * (Windows Embedded CE 6.0 R3) */
struct XRGridLength {
    float UnitValue;
    XRGridUnitType UnitType;
};

#endif /* _WIN32_WCE >= 0x0600 */
#endif /* AKARI_XAMLRUNTIME_H */
