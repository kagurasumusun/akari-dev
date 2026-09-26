/* Common controls. Original text. Exported by commctrl.dll. */
#ifndef AKARI_WCE_COMMCTRL_H
#define AKARI_WCE_COMMCTRL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winuser.h"


#define WC_LISTVIEWW       L"SysListView32"
#define WC_TREEVIEWW       L"SysTreeView32"
#define WC_TABCONTROLW     L"SysTabControl32"
#define TOOLBARCLASSNAMEW  L"ToolbarWindow32"
#define STATUSCLASSNAMEW   L"msctls_statusbar32"
#define TRACKBAR_CLASSW    L"msctls_trackbar32"
#define UPDOWN_CLASSW      L"msctls_updown32"
#define PROGRESS_CLASSW    L"msctls_progress32"

#define ICC_LISTVIEW_CLASSES   0x00000001
#define ICC_TREEVIEW_CLASSES   0x00000002
#define ICC_BAR_CLASSES        0x00000004
#define ICC_TAB_CLASSES        0x00000008
#define ICC_UPDOWN_CLASS       0x00000010
#define ICC_PROGRESS_CLASS     0x00000020
#define ICC_HOTKEY_CLASS       0x00000040
#define ICC_DATE_CLASSES       0x00000100
#define ICC_ANIMATE_CLASS      0x00000080

typedef struct akari_INITCOMMONCONTROLSEX {
    DWORD dwSize;
    DWORD dwICC;
} INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;

#define LVS_ICON            0x0000
#define LVS_REPORT          0x0001
#define LVS_SMALLICON       0x0002
#define LVS_LIST            0x0003
#define LVS_SINGLESEL       0x0004
#define LVS_SHOWSELALWAYS   0x0008
#define LVS_SORTASCENDING   0x0010
#define LVS_SORTDESCENDING  0x0020
#define LVS_NOLABELWRAP     0x0080
#define LVS_EDITLABELS      0x0200
#define LVS_OWNERDATA       0x1000
#define LVS_NOSCROLL        0x2000
#define LVS_NOCOLUMNHEADER  0x4000
#define LVS_NOSORTHEADER    0x8000

#define LVS_EX_CHECKBOXES      0x00000004
#define LVS_EX_FULLROWSELECT   0x00000020
#define LVS_EX_GRIDLINES       0x00000001
#define LVS_EX_ONECLICKACTIVATE 0x00000040
#define LVS_EX_SUBITEMIMAGES   0x00000002
#define LVS_EX_HEADERDRAGDROP  0x00000010

#define LVM_FIRST               0x1000
#define LVM_INSERTITEMW         (LVM_FIRST + 77)
#define LVM_SETITEMW            (LVM_FIRST + 76)
#define LVM_GETITEMW            (LVM_FIRST + 75)
#define LVM_DELETEITEM          (LVM_FIRST + 8)
#define LVM_DELETEALLITEMS      (LVM_FIRST + 9)
#define LVM_GETITEMCOUNT        (LVM_FIRST + 4)
#define LVM_SETITEMSTATE        (LVM_FIRST + 43)
#define LVM_GETITEMSTATE        (LVM_FIRST + 44)
#define LVM_SETITEMTEXTW        (LVM_FIRST + 116)
#define LVM_GETITEMTEXTW        (LVM_FIRST + 115)
#define LVM_SETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 54)
#define LVM_GETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 55)
#define LVM_INSERTCOLUMNW       (LVM_FIRST + 97)
#define LVM_DELETECOLUMN        (LVM_FIRST + 28)
#define LVM_GETSELECTEDCOUNT    (LVM_FIRST + 50)
#define LVM_GETNEXTITEM         (LVM_FIRST + 12)
#define LVM_ENSUREVISIBLE       (LVM_FIRST + 19)
#define LVM_SCROLL              (LVM_FIRST + 20)
#define LVM_SETCOLUMNWIDTH      (LVM_FIRST + 30)
#define LVM_SETIMAGELIST        (LVM_FIRST + 3)
#define LVM_GETIMAGELIST        (LVM_FIRST + 2)

#define LVIF_TEXT        0x00000001
#define LVIF_IMAGE       0x00000002
#define LVIF_PARAM       0x00000004
#define LVIF_STATE       0x00000008
#define LVIF_NORECOMPUTE 0x00000800

#define LVIS_FOCUSED   0x0001
#define LVIS_SELECTED  0x0002
#define LVIS_CUT       0x0004
#define LVIS_DROPHILITED 0x0008
#define LVIS_ACTIVATING 0x0020

#define LVNI_ALL        0x0000
#define LVNI_FOCUSED    0x0001
#define LVNI_SELECTED   0x0002
#define LVNI_CUT        0x0004
#define LVNI_ABOVE      0x0100
#define LVNI_BELOW      0x0200

#define LVCF_FMT     0x0001
#define LVCF_WIDTH   0x0002
#define LVCF_TEXT    0x0004
#define LVCF_SUBITEM 0x0008

#define LVCFMT_LEFT   0x0000
#define LVCFMT_RIGHT  0x0001
#define LVCFMT_CENTER 0x0002

#define LVN_FIRST               ((UINT)-100)
#define LVN_ITEMCHANGING        (LVN_FIRST - 0)
#define LVN_ITEMCHANGED         (LVN_FIRST - 1)
#define LVN_INSERTITEM          (LVN_FIRST - 2)
#define LVN_DELETEITEM          (LVN_FIRST - 3)
#define LVN_DELETEALLITEMS      (LVN_FIRST - 4)
#define LVN_ITEMACTIVATE        (LVN_FIRST - 14)
#define LVN_COLUMNCLICK         (LVN_FIRST - 8)
#define LVN_BEGINDRAG           (LVN_FIRST - 9)
#define LVN_GETDISPINFOW        (LVN_FIRST - 77)
#define LVN_SETDISPINFOW        (LVN_FIRST - 78)
#define LVN_ODCACHEHINT         (LVN_FIRST - 13)
#define LVN_ODFINDITEMW         (LVN_FIRST - 79)

typedef struct akari_LVITEMW {
    UINT mask;
    int iItem;
    int iSubItem;
    UINT state;
    UINT stateMask;
    LPWSTR pszText;
    int cchTextMax;
    int iImage;
    LPARAM lParam;
    int iIndent;
    int iGroupId;
} LVITEMW, *LPLVITEMW;

typedef struct akari_LVCOLUMNW {
    UINT mask;
    int fmt;
    int cx;
    LPWSTR pszText;
    int cchTextMax;
    int iSubItem;
    int iImage;
    int iOrder;
} LVCOLUMNW, *LPLVCOLUMNW;

typedef struct akari_NMLISTVIEW {
    NMHDR hdr;
    int iItem;
    int iSubItem;
    UINT uNewState;
    UINT uOldState;
    UINT uChanged;
    POINT ptAction;
    LPARAM lParam;
} NMLISTVIEW, *LPNMLISTVIEW;

typedef struct akari_NMLVDISPINFOW {
    NMHDR hdr;
    LVITEMW item;
} NMLVDISPINFOW, *LPNMLVDISPINFOW;

typedef struct akari_NMCACHEHINT {
    NMHDR hdr;
    int iFrom;
    int iTo;
} NMLVCACHEHINT, *LPNMLVCACHEHINT;

typedef struct akari_LVFINDINFOW {
    UINT flags;
    LPCWSTR psz;
    LPARAM lParam;
    POINT pt;
    UINT vkDirection;
} LVFINDINFOW, *LPFINDINFOW;

typedef struct akari_NMLVFINDITEMW {
    NMHDR hdr;
    LVFINDINFOW lvfi;
    int iStart;
} NMLVFINDITEMW, *LPNMLVFINDITEMW;

#define LVFI_PARAM     0x0001
#define LVFI_STRINGW   0x0002
#define LVFI_PARTIAL   0x0008
#define LVFI_WRAP      0x0020
#define LVFI_NOSTRING  0x0004

#define TCS_SCROLLOPPOSITE      0x0001
#define TCS_BOTTOM              0x0002
#define TCS_RIGHT               0x0002
#define TCS_MULTISELECT         0x0004
#define TCS_FLATBUTTONS         0x0008
#define TCS_FORCEICONLEFT       0x0010
#define TCS_FORCELABELLEFT      0x0020
#define TCS_HOTTRACK            0x0040
#define TCS_VERTICAL            0x0080
#define TCS_TABS                0x0000
#define TCS_BUTTONS             0x0100
#define TCS_SINGLELINE          0x0000
#define TCS_MULTILINE           0x0200
#define TCS_FIXEDWIDTH          0x0400

#define TCM_FIRST          0x1300
#define TCM_GETIMAGELIST   (TCM_FIRST + 2)
#define TCM_SETIMAGELIST   (TCM_FIRST + 3)
#define TCM_GETITEMCOUNT   (TCM_FIRST + 4)
#define TCM_GETITEMW       (TCM_FIRST + 60)
#define TCM_SETITEMW       (TCM_FIRST + 61)
#define TCM_INSERTITEMW    (TCM_FIRST + 62)
#define TCM_DELETEITEM     (TCM_FIRST + 8)
#define TCM_DELETEALLITEMS (TCM_FIRST + 9)
#define TCM_GETCURSEL      (TCM_FIRST + 11)
#define TCM_SETCURSEL      (TCM_FIRST + 12)
#define TCM_GETCURFOCUS    (TCM_FIRST + 47)

#define TCN_FIRST          ((UINT)-550)
#define TCN_KEYDOWN        (TCN_FIRST - 0)
#define TCN_SELCHANGE      (TCN_FIRST - 1)
#define TCN_SELCHANGING    (TCN_FIRST - 2)

#define TCIF_TEXT          0x0001
#define TCIF_IMAGE         0x0002
#define TCIF_RTLREADING    0x0004
#define TCIF_PARAM         0x0008

typedef struct akari_TCITEMW {
    UINT mask;
    DWORD dwState;
    DWORD dwStateMask;
    LPWSTR pszText;
    int cchTextMax;
    int iImage;
    LPARAM lParam;
} TCITEMW, *LPTCITEMW;

typedef struct akari_NMTCKEYDOWN {
    NMHDR hdr;
    WORD wVKey;
    UINT flags;
} NMTCKEYDOWN, *LPNMTCKEYDOWN;

#define TBS_AUTOTICKS      0x0001
#define TBS_VERT           0x0002
#define TBS_HORZ           0x0000
#define TBS_TOP            0x0004
#define TBS_BOTTOM         0x0000
#define TBS_LEFT           0x0004
#define TBS_RIGHT          0x0000
#define TBS_NOTICKS        0x0010
#define TBS_BOTH           0x0008

#define TBM_GETPOS         (WM_USER)
#define TBM_SETPOS         (WM_USER + 5)
#define TBM_SETRANGE       (WM_USER + 6)
#define TBM_SETTIC         (WM_USER + 4)
#define TBM_SETLINESIZE    (WM_USER + 23)
#define TBM_SETPAGESIZE    (WM_USER + 21)
#define TBM_GETRANGEMIN    (WM_USER + 1)
#define TBM_GETRANGEMAX    (WM_USER + 2)

#define UDS_WRAP           0x0001
#define UDS_SETBUDDYINT    0x0002
#define UDS_ALIGNRIGHT     0x0004
#define UDS_ALIGNLEFT      0x0008
#define UDS_AUTOBUDDY      0x0010
#define UDS_ARROWKEYS      0x0020
#define UDS_HORZ           0x0040
#define UDS_NOTHOUSANDS    0x0080

#define UDM_SETRANGE       (WM_USER + 101)
#define UDM_GETRANGE       (WM_USER + 102)
#define UDM_SETPOS         (WM_USER + 103)
#define UDM_GETPOS         (WM_USER + 104)
#define UDM_SETBUDDY       (WM_USER + 105)
#define UDM_GETBUDDY       (WM_USER + 106)

#define PBM_SETRANGE       (WM_USER + 1)
#define PBM_SETPOS         (WM_USER + 2)
#define PBM_DELTAPOS       (WM_USER + 3)
#define PBM_SETSTEP        (WM_USER + 4)
#define PBM_STEPIT         (WM_USER + 5)

#define SBARS_SIZEGRIP     0x0100
#define SB_SETTEXTW        (WM_USER + 11)
#define SB_GETTEXTW        (WM_USER + 13)
#define SB_GETTEXTLENGTHW  (WM_USER + 12)
#define SB_SETPARTS        (WM_USER + 4)
#define SB_GETPARTS        (WM_USER + 6)
#define SB_SIMPLE          (WM_USER + 9)

#define CCS_TOP            0x00000001
#define CCS_NOMOVEY        0x00000002
#define CCS_BOTTOM         0x00000003
#define CCS_NORESIZE       0x00000004
#define CCS_NOPARENTALIGN  0x00000008
#define CCS_NODIVIDER      0x00000040
#define CCS_VERT           0x00000080
#define CCS_LEFT           (CCS_VERT | CCS_TOP)
#define CCS_RIGHT          (CCS_VERT | CCS_BOTTOM)

#define TBSTYLE_TOOLTIPS      0x0100
#define TBSTYLE_WRAPABLE      0x0200
#define TBSTYLE_ALTDRAG       0x0400
#define TBSTYLE_FLAT          0x0800
#define TBSTYLE_LIST          0x1000
#define TBSTYLE_CUSTOMERASE   0x2000
#define TBSTATE_CHECKED       0x01
#define TBSTATE_PRESSED       0x02
#define TBSTATE_ENABLED       0x04
#define TBSTATE_HIDDEN        0x08

#define TBIF_TEXT        0x00000002
#define TBIF_STATE       0x0004
#define TBIF_STYLE       0x0008
#define TBIF_COMMAND     0x0020
#define TBIF_IMAGE       0x0001

#define TB_BUTTONCOUNT        (WM_USER + 24)
#define TB_ADDBUTTONSW        (WM_USER + 68)
#define TB_INSERTBUTTONW      (WM_USER + 67)
#define TB_DELETEBUTTON       (WM_USER + 22)
#define TB_ENABLEBUTTON       (WM_USER + 1)
#define TB_CHECKBUTTON        (WM_USER + 2)
#define TB_PRESSBUTTON        (WM_USER + 3)
#define TB_ISBUTTONENABLED    (WM_USER + 9)
#define TB_SETBUTTONINFOW     (WM_USER + 64)
#define TB_GETBUTTONINFOW     (WM_USER + 63)
#define TB_GETBUTTONTEXTW     (WM_USER + 75)

#define BTNSTYLE_BUTTON   0x0000
#define BTNSTYLE_SEP      0x0001
#define BTNSTYLE_CHECK    0x0002
#define BTNSTYLE_GROUP    0x0004
#define TBSTYLE_BUTTON    BTNSTYLE_BUTTON
#define TBSTYLE_SEP       BTNSTYLE_SEP
#define TBSTYLE_CHECK     BTNSTYLE_CHECK
#define TBSTYLE_GROUP     BTNSTYLE_GROUP

typedef struct akari_TBBUTTON {
    int iBitmap;
    int idCommand;
    BYTE fsState;
    BYTE fsStyle;
    BYTE bReserved[2];
    DWORD_PTR dwData;
    INT_PTR iString;
} TBBUTTON, *PTBBUTTON, *LPTBBUTTON;

typedef struct akari_TBBUTTONINFOW {
    UINT cbSize;
    DWORD dwMask;
    int idCommand;
    int iImage;
    BYTE fsState;
    BYTE fsStyle;
    WORD cx;
    LPARAM lParam;
    LPWSTR pszText;
    int cchText;
} TBBUTTONINFOW, *LPTBBUTTONINFOW;

typedef struct akari_TBADDBITMAP {
    HINSTANCE hInst;
    UINT_PTR nID;
} TBADDBITMAP, *LPTBADDBITMAP;

#define PSH_DEFAULT        0x00000000
#define PSH_PROPTITLE      0x00000001
#define PSH_USEICONID      0x00000004
#define PSH_PROPSHEETPAGE  0x00000008
#define PSH_HASHELP        0x0200
#define PSH_NOAPPLYNOW     0x00000080
#define PSH_USECALLBACK    0x0100

#define PSP_DEFAULT        0x00000000
#define PSP_DLGINDIRECT    0x00000001
#define PSP_USEHICON       0x00000002
#define PSP_USEICONID      0x00000004
#define PSP_USETITLE       0x00000008
#define PSP_HASHELP        0x00000020
#define PSP_USEREFPARENT   0x00000040
#define PSP_USECALLBACK    0x00000080

#define PSN_FIRST          ((UINT)-200)
#define PSN_SETACTIVE      (PSN_FIRST - 0)
#define PSN_KILLACTIVE     (PSN_FIRST - 1)
#define PSN_APPLY          (PSN_FIRST - 2)
#define PSN_RESET          (PSN_FIRST - 3)
#define PSN_HELP           (PSN_FIRST - 5)
#define PSN_WIZBACK        (PSN_FIRST - 6)
#define PSN_WIZNEXT        (PSN_FIRST - 7)
#define PSN_WIZFINISH      (PSN_FIRST - 8)
#define PSN_QUERYCANCEL    (PSN_FIRST - 9)

#define PSNRET_NOERROR         0
#define PSNRET_INVALID         1
#define PSNRET_INVALID_NOCHANGEPAGE 2
#define PSNRET_MESSAGEHANDLED  3

#define PSM_SETCURSEL       (WM_USER + 101)
#define PSM_CHANGED         (WM_USER + 104)
#define PSM_RESTARTWINDOWS  (WM_USER + 105)
#define PSM_REBOOTSYSTEM    (WM_USER + 106)
#define PSM_CANCELTOCLOSE   (WM_USER + 107)
#define PSM_QUERYSIBLINGS   (WM_USER + 108)
#define PSM_UNCHANGED       (WM_USER + 109)
#define PSM_APPLY           (WM_USER + 110)
#define PSM_PRESSBUTTON     (WM_USER + 113)
#define PSBTN_BACK    0
#define PSBTN_NEXT    1
#define PSBTN_FINISH  2
#define PSBTN_OK      3
#define PSBTN_APPLYNOW 4
#define PSBTN_CANCEL  5
#define PSBTN_HELP    6

typedef UINT (CALLBACK *LPFNPSPCALLBACKW)(HWND hwnd, UINT uMsg, void *ppsp);
typedef int (CALLBACK *PFNPROPSHEETCALLBACK)(HWND hwnd, UINT uMsg, LPARAM lParam);
typedef BOOL (CALLBACK *DLGPROC_PTR)(HWND, UINT, WPARAM, LPARAM);

typedef struct akari_PROPSHEETPAGEW {
    DWORD dwSize;
    DWORD dwFlags;
    HINSTANCE hInstance;
    LPCWSTR pszTemplate;
    HICON hIcon;
    LPCWSTR pszTitle;
    DLGPROC_PTR pfnDlgProc;
    LPARAM lParam;
    LPFNPSPCALLBACKW pfnCallback;
    void *pcRefParent;
} PROPSHEETPAGEW, *LPPROPSHEETPAGEW;

typedef struct akari_PROPSHEETHEADERW {
    DWORD dwSize;
    DWORD dwFlags;
    HWND hwndParent;
    HINSTANCE hInstance;
    HICON hIcon;
    LPCWSTR pszCaption;
    UINT nPages;
    UINT nStartPage;
    const PROPSHEETPAGEW *ppsp;
    PFNPROPSHEETCALLBACK pfnCallback;
} PROPSHEETHEADERW, *LPPROPSHEETHEADERW;

WINBASEAPI void WINAPI InitCommonControls(VOID);
WINBASEAPI BOOL WINAPI InitCommonControlsEx(const INITCOMMONCONTROLSEX *);
WINBASEAPI HWND WINAPI CreateToolbarEx(HWND hwnd, DWORD ws, UINT wID, int nBitmaps,
    HINSTANCE hBMInst, UINT_PTR wBMID, const TBBUTTON *lpButtons, int iNumButtons,
    int dxButton, int dyButton, int dxBitmap, int dyBitmap, UINT uStructSize);
WINBASEAPI HWND WINAPI CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy,
    HWND hwndParent, int nID, HINSTANCE hInst, HWND hwndBuddy, int nUpper, int nLower,
    int nPos);
WINBASEAPI HWND WINAPI CreateStatusWindowW(LONG style, LPCWSTR lpszText, HWND hwndParent,
    UINT wID);
WINBASEAPI void WINAPI DrawStatusTextW(HDC hDC, LPRECT lprc, LPCWSTR text, UINT uFlags);
WINBASEAPI HWND WINAPI CommandBar_Create(HINSTANCE hInst, HWND hwndParent, UINT uId);
WINBASEAPI BOOL WINAPI CommandBar_Show(HWND hwndCB, BOOL fShow);
WINBASEAPI int WINAPI CommandBar_Height(HWND hwndCB);
WINBASEAPI BOOL WINAPI CommandBar_AddAdornments(HWND hwndCB, DWORD dwFlags, DWORD dwReserved);
WINBASEAPI BOOL WINAPI CommandBar_AddBitmap(HWND hwndCB, HINSTANCE hInst, int iBitmapID,
    int iNumImages, int iImageWidth, int iImageHeight);
WINBASEAPI HWND WINAPI CommandBar_InsertMenubar(HWND hwndCB, HINSTANCE hInst, UINT uMenuID,
    UINT uIndex);
WINBASEAPI HWND WINAPI CommandBar_InsertMenubarEx(HWND hwndCB, HINSTANCE hInst, UINT uMenuID,
    UINT uIndex, WORD dwFlags);
WINBASEAPI HMENU WINAPI CommandBar_GetMenu(HWND hwndCB, UINT uIndex);
WINBASEAPI HWND WINAPI CommandBar_InsertComboBox(HWND hwndCB, HINSTANCE hInst, UINT uIndex,
    UINT uWidth, UINT uID, UINT uPosition);
WINBASEAPI BOOL WINAPI CommandBar_DrawMenuBar(HWND hwndCB, UINT uIndex);
WINBASEAPI void WINAPI CommandBar_AlignAdornments(HWND hwndCB);
WINBASEAPI HWND WINAPI CommandBands_Create(HINSTANCE hInstance, HWND hwndParent, UINT uID,
    DWORD dwFlags, HMENU hmenu, const void *prb, HIMAGELIST himlLarge, HIMAGELIST himlSmall,
    UINT nBtnTextLen);
WINBASEAPI BOOL WINAPI CommandBands_Show(HWND hwndCB, BOOL fShow);
WINBASEAPI BOOL WINAPI CommandBands_AddBands(HWND hwndCB, HINSTANCE hInst, UINT uBandCount,
    DWORD dwBandFlags, const void *prb, HMENU hmenu, HIMAGELIST himlSmall, UINT nBtnTextLen);
WINBASEAPI BOOL WINAPI CommandBands_AddAdornments(HWND hwndCB, DWORD dwFlags, DWORD dwReserved);
WINBASEAPI HWND WINAPI CommandBands_GetCommandBar(HWND hwndCB, UINT uBandIndex);
WINBASEAPI BOOL WINAPI CommandBands_GetRestoreInformation(HWND hwndCB, UINT uBandIndex,
    void *pcri);
WINBASEAPI BOOL WINAPI IsCommandBarMessage(HWND hwndCB, MSG *pMsg);
WINBASEAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageW(const PROPSHEETPAGEW *pPSPage);
WINBASEAPI BOOL WINAPI DestroyPropertySheetPage(HPROPSHEETPAGE hPSPage);
WINBASEAPI INT_PTR WINAPI PropertySheetW(const PROPSHEETHEADERW *pPSHead);
WINBASEAPI BOOL WINAPI ImageList_SetImageCount(HIMAGELIST himl, UINT uNewCount);
WINBASEAPI int WINAPI ImageList_Add(HIMAGELIST himl, HBITMAP hbmImage, HBITMAP hbmMask);
WINBASEAPI int WINAPI ImageList_AddMasked(HIMAGELIST himl, HBITMAP hbmImage, COLORREF crMask);
WINBASEAPI HIMAGELIST WINAPI ImageList_Create(int cx, int cy, UINT flags, int cInitial,
    int cGrow);
WINBASEAPI BOOL WINAPI ImageList_Destroy(HIMAGELIST himl);
WINBASEAPI BOOL WINAPI ImageList_Draw(HIMAGELIST himl, int i, HDC hdcDst, int x, int y,
    UINT fStyle);
WINBASEAPI int WINAPI ImageList_GetImageCount(HIMAGELIST himl);
WINBASEAPI BOOL WINAPI ImageList_Remove(HIMAGELIST himl, int i);
WINBASEAPI BOOL WINAPI ImageList_ReplaceIcon(HIMAGELIST himl, int i, HICON hicon);
WINBASEAPI HICON WINAPI ImageList_GetIcon(HIMAGELIST himl, int i, UINT flags);

#define ILD_NORMAL     0x00000000
#define ILD_TRANSPARENT 0x00000001
#define ILD_BLEND25    0x00000002
#define ILD_BLEND50    0x00000004
#define ILD_SELECTED   ILD_BLEND50
#define ILD_FOCUS      ILD_BLEND25
#define ILD_MASK       0x00000010
#define ILC_COLOR      0x00000000
#define ILC_COLOR4     0x00000004
#define ILC_COLOR8     0x00000008
#define ILC_COLOR16    0x00000010
#define ILC_COLOR32    0x00000020
#define ILC_MASK       0x00000001

#define LBS_NOTIFY            0x0001L
#define LBS_SORT              0x0002L
#define LBS_MULTIPLESEL       0x0008L
#define LBS_OWNERDRAWFIXED    0x0010L
#define LBS_HASSTRINGS        0x0040L
#define LBS_NOINTEGRALHEIGHT  0x0100L
#define LBS_EXTENDEDSEL       0x0800L


#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_COMMCTRL_H */
