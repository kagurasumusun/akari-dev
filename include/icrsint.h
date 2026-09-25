/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_ICRSINT_H
#define WCE_ICRSINT_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagADO_BINDING_ENTRY { ULONG ulOrdinal; WORD wDataType; BYTE bPrecision; BYTE bScale; ULONG ulSize; ULONG ulBufferOffset; ULONG ulStatusOffset; ULONG ulLengthOffset; ULONG ulADORecordBindingOffSet; BOOL fModify; } ADO_BINDING_ENTRY, *PADO_BINDING_ENTRY, *LPADO_BINDING_ENTRY;


#ifdef __cplusplus
}
#endif
#endif

