/* Alternate name for tlhelp32.h.  Original text.
 *
 * Windows CE calls this header tlhelp32.h; there is no toolhelp.h in the CE SDK.
 * The alias is kept because the module the entry points are exported from is
 * named toolhelp.dll, so code that includes by that name should still build.
 */
#ifndef AKARI_WCE_TOOLHELP_H
#define AKARI_WCE_TOOLHELP_H

#include "tlhelp32.h"

#endif /* AKARI_WCE_TOOLHELP_H */
