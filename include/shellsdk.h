/* Shell SDK. Original text. Exported by aygshell.dll.
 *
 * The shell library is an optional component of a Windows CE image. It is
 * present on Windows CE 5.0 and later for every CPU this kit targets; on
 * Windows CE 4.2 it was built for x86 only, so the declarations are switched off
 * there rather than offered for CPUs that have no library to link against.
 */
#ifndef AKARI_WCE_SHELLSDK_H
#define AKARI_WCE_SHELLSDK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winuser.h"

#if (_WIN32_WCE >= 0x500)

#define SHIDIM_FLAGS 0x0001

#define SHIDIF_DONEBUTTON      0x0001
#define SHIDIF_SIPDOWN 0x0008
#define SHIDIF_SIZEDLGFULLSCREEN 0x0004
#define SHIDIF_WANTSCROLLBAR   0x0008
#define SHIDIF_WANTSIPOFF      0x0010
#define SHIDIF_FULLSCREENNOMENUBAR 0x0010
#define SHIDIF_EMPTYMENU 0x0020
#define SHIDIF_HIDESIPBUTTON   0x0080

#define SHCMBF_EMPTYBAR        0x0001
#define SHCMBF_HIDDEN          0x0002
#define SHCMBF_HIDESIPBUTTON   0x0004
#define SHCMBF_COLORBK         0x0008
#define SHCMBF_HMENU           0x0010

#define SHFS_HIDESTARTICON 0x0020
#define SHFS_HIDESIPBUTTON 0x0008
#define SHFS_HIDETASKBAR 0x0002
#define SHFS_SHOWSTARTICON 0x0010
#define SHFS_SHOWSIPBUTTON 0x0004
#define SHFS_SHOWTASKBAR 0x0001

#define SHRG_NOTIFYPARENT 0x00000002
#define SHRG_RETURNCMD 0x00000001
#define SHRG_ENABLEDRAGDROP    0x0004
#define SHRG_LONGDELAY         0x0008
#define SHRG_NOANIMATION       0x0010

typedef enum akari_SIPSTATE {
    SIP_UP = 0,
    SIP_DOWN,
    SIP_FORCEDOWN,
    SIP_UNCHANGED,
    SIP_INPUTDIALOG
} SIPSTATE;
#define SIPF_ON                0x00000001
#define SIPF_OFF               0x00000000
#define SIPF_DOCKED 0x00000002
#define SIPF_UNDOCKED          0x00000001
#define SIPF_LOCKED 0x00000004
#define SIPF_ONOFFSWITCHON     0x00000004
#define SIPF_PREVIOUSLYON      0x00000008

#define SHCNF_FLUSH            0x1000
#define SHCNF_FLUSHNOWAIT      0x2000
#define SHCNF_TYPE             0x00FF
#define SHCNF_DWORD            0x0003
#define SHCNF_STRING           0x0004
#define SHCNF_PATH             0x0005

#define SHCNE_UPDATEITEM       0x00002000L
#define SHCNE_RENAMEITEM       0x00000001L
#define SHCNE_CREATE           0x00000002L
#define SHCNE_DELETE           0x00000004L
#define SHCNE_MKDIR            0x00000008L
#define SHCNE_RMDIR            0x00000010L
#define SHCNE_MEDIAINSERTED    0x00000020L
#define SHCNE_MEDIAREMOVED     0x00000040L
#define SHCNE_DRIVEREMOVED     0x00000080L
#define SHCNE_UPDATEIMAGE      0x00008000L
#define SHCNE_ASSOCCHANGED     0x08000000L
#define SHCNE_FREEDISKSPACE    0x00010000L
#define SHCNE_ALLEVENTS        0x7FFFFFFFL
#define SHCNE_INTERRUPT        0x80000000L

#define IDM_SHAREDNEW 10
#define IDM_SHAREDNEWEXCEPTION 1001

#define SPI_GETSIPINFO 225
#define SPI_SETSIPINFO 224
#define SPI_GETSIPMOVE         0xFFF5
#define SPI_SETSIPMOVE         0xFFF6

typedef struct akari_SHINITDLGINFO {
    DWORD dwMask;
    HWND hDlg;
    DWORD dwFlags;
} SHINITDLGINFO, *PSHINITDLGINFO;

typedef struct akari_SHMENUBARINFO {
    DWORD cbSize;
    HWND hwndParent;
    DWORD dwFlags;
    UINT nToolBarId;
    HINSTANCE hInstRes;
    int nBmpId;
    int cBmpImages;
    HWND hwndMB;
    COLORREF clrBk;
} SHMENUBARINFO, *PSHMENUBARINFO;

typedef struct akari_SHRGINFO {
    DWORD cbSize;
    HWND hwndClient;
    POINT ptDown;
    DWORD dwFlags;
} SHRGINFO, *PSHRGINFO;

typedef struct akari_SIPINFO {
    DWORD cbSize;
    DWORD fdwFlags;
    RECT rcVisibleDesktop;
    RECT rcSipRect;
    DWORD dwImDataSize;
    PVOID pvImData;
} SIPINFO, *PSIPINFO;

typedef struct akari_SHACTIVATEINFO {
    DWORD cbSize;
    HWND hwndLastFocus;
    UINT fSipUp :1;
    UINT fSipOnDeactivation :1;
    UINT fActive :1;
    UINT fReserved :29;
} SHACTIVATEINFO, *PSHACTIVATEINFO;

typedef struct akari_FILECHANGEINFO {
    DWORD    cbSize;
    LONG     wEventId;
    ULONG    uFlags;
    DWORD    dwItem1;
    DWORD    dwItem2;
    DWORD    dwAttributes;
    FILETIME ftModified;
    ULONG    nFileSize;
} FILECHANGEINFO, *LPFILECHANGEINFO;

typedef FILECHANGEINFO const *LPCFILECHANGEINFO;

typedef struct akari_FILECHANGENOTIFY {
    DWORD          dwRefCount;
    FILECHANGEINFO fci;
} FILECHANGENOTIFY;

typedef struct akari_SHCHANGENOTIFYENTRY {
    DWORD  dwEventMask;
    LPWSTR pszWatchDir;
    BOOL   fRecursive;
} SHCHANGENOTIFYENTRY, *PSHCHANGENOTIFYENTRY;

SHELLAPI BOOL WINAPI SHInitDialog(PSHINITDLGINFO pshidi);
SHELLAPI BOOL WINAPI SHCreateMenuBar(PSHMENUBARINFO pmbi);
SHELLAPI HWND WINAPI SHFindMenuBar(HWND hwnd);
SHELLAPI BOOL WINAPI SHFullScreen(HWND hwndRequester, DWORD dwState);
SHELLAPI BOOL WINAPI SHDoneButton(HWND hwndRequester, DWORD dwState);
SHELLAPI BOOL WINAPI SHSipInfo(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
SHELLAPI BOOL WINAPI SHSipPreference(HWND hwnd, SIPSTATE st);
SHELLAPI BOOL WINAPI SHSetNavBarText(HWND hWnd, LPCWSTR lpszNewText);
SHELLAPI DWORD WINAPI SHRecognizeGesture(PSHRGINFO shrg);
SHELLAPI void WINAPI SHInputDialog(HWND hwnd, UINT uMsg, WPARAM wParam);
SHELLAPI BOOL WINAPI SHInitExtraControls(VOID);
SHELLAPI BOOL WINAPI SHSetAppKeyWndAssoc(BYTE bVk, HWND hwnd);
SHELLAPI BYTE WINAPI SHGetAppKeyAssoc(LPCWSTR ptszApp);
SHELLAPI BOOL WINAPI SHGetAutoRunPath(LPWSTR pwzPath);
SHELLAPI HRESULT WINAPI SHCreateNewItem(HWND hwndOwner, const CLSID *const clsid);
SHELLAPI BOOL WINAPI SHChangeNotifyRegister(HWND hwnd, SHCHANGENOTIFYENTRY *pshcne);
SHELLAPI BOOL WINAPI SHChangeNotifyDeregister(HWND hwnd);
SHELLAPI void WINAPI SHChangeNotifyFree(FILECHANGENOTIFY *pfcn);
SHELLAPI BOOL WINAPI SHGetInputContext(HWND hWnd, void *pImInfo);
SHELLAPI BOOL WINAPI SHSetInputContext(HWND hWnd, const void *pImInfo);

#endif /* _WIN32_WCE >= 0x500 */

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_SHELLSDK_H */
