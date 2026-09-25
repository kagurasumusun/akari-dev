/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_DBT_H
#define WCE_DBT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagDEV_BROADCAST_VOLUME_A { DWORD dbcv_size; DWORD dbcv_devicetype; DWORD dbcv_reserved; DWORD dbcv_unitmask; WORD dbcv_flags; char dbcv_name[1]; } DEV_BROADCAST_VOLUME_A, *PDEV_BROADCAST_VOLUME_A, *LPDEV_BROADCAST_VOLUME_A;
typedef struct tagDEV_BROADCAST_PORT_A { DWORD dbcp_size; DWORD dbcp_devicetype; DWORD dbcp_reserved; char dbcp_name[1]; } DEV_BROADCAST_PORT_A, *PDEV_BROADCAST_PORT_A, *LPDEV_BROADCAST_PORT_A;
typedef struct tagDEV_BROADCAST_DEVICEINTERFACE_A { DWORD dbcc_size; DWORD dbcc_devicetype; DWORD dbcc_reserved; GUID dbcc_classguid; char dbcc_name[1]; } DEV_BROADCAST_DEVICEINTERFACE_A, *PDEV_BROADCAST_DEVICEINTERFACE_A, *LPDEV_BROADCAST_DEVICEINTERFACE_A;
typedef struct tagDEV_BROADCAST_HANDLE { DWORD dbch_size; DWORD dbch_devicetype; DWORD dbch_reserved; DWORD dbch_handle; DWORD dbch_hdevnotify; GUID dbch_eventguid; LONG dbch_nameoffset; BYTE dbch_data[1]; } DEV_BROADCAST_HANDLE, *PDEV_BROADCAST_HANDLE, *LPDEV_BROADCAST_HANDLE;


#ifdef __cplusplus
}
#endif
#endif

