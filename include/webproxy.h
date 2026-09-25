/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WEBPROXY_H
#define WCE_WEBPROXY_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPROXY_HTTP_INFORMATION { DWORD dwSize; DWORD dwProxyVersion; } PROXY_HTTP_INFORMATION, *PPROXY_HTTP_INFORMATION, *LPPROXY_HTTP_INFORMATION;


#ifdef __cplusplus
}
#endif
#endif

