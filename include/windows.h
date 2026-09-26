/* windows.h -- Windows CE application entry header. Original text.
 *
 * Include order matters: the base types come first, then GDI, then the user
 * interface. commdlg.h, commctrl.h and winsock2.h are deliberately NOT pulled
 * in here, matching Windows CE, because they bind to separate modules.
 */
#ifndef AKARI_WCE_WINDOWS_H
#define AKARI_WCE_WINDOWS_H

#include "wcever.h"
#include "winnt.h"
#include "excpt.h"
#include "winerror.h"
#include "windef.h"
#include "winbase.h"
#include "tchar.h"
#include "winreg.h"
#include "winnls.h"
#include "wingdi.h"
#include "winuser.h"

#if defined(AKARI_HAVE_STORE_MANAGER)
#include "storemgr.h"
#endif

#include "pm.h"
#include "notify.h"

#endif /* AKARI_WCE_WINDOWS_H */
