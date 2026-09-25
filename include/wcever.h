/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_VER_H
#define WCE_VER_H
/* Surveyed build versions: CE 4.2 = 0x420, CE 5.0 = 0x500, CE 6.0 = 0x600. */
#ifndef _WIN32_WCE
#define _WIN32_WCE 0x600
#endif
#ifndef UNDER_CE
#define UNDER_CE 1
#endif
#ifndef WINVER
#define WINVER 0x0500
#endif
#endif
