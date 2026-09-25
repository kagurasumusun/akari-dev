/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RPCNDR_H
#define WCE_RPCNDR_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagARRAY_INFO { long Dimension; unsigned long * BufferConformanceMark; unsigned long * BufferVarianceMark; unsigned long * MaxCountArray; unsigned long * OffsetArray; unsigned long * ActualCountArray; } ARRAY_INFO, *PARRAY_INFO, *LPARRAY_INFO;
typedef struct tagNDR_PIPE_STATE { int CurrentState; int ElemsInChunk; int ElemAlign; int ElemWireSize; int ElemMemSize; int PartialBufferSize; unsigned char * PartialElem; int PartialElemSize; int PartialOffset; int EndOfPipe; } NDR_PIPE_STATE, *PNDR_PIPE_STATE, *LPNDR_PIPE_STATE;
typedef struct tagCOMM_FAULT_OFFSETS { short CommOffset; short FaultOffset; } COMM_FAULT_OFFSETS, *PCOMM_FAULT_OFFSETS, *LPCOMM_FAULT_OFFSETS;
typedef struct tagMIDL_FORMAT_STRING { short Pad; unsigned char Format[]; } MIDL_FORMAT_STRING, *PMIDL_FORMAT_STRING, *LPMIDL_FORMAT_STRING;


#ifdef __cplusplus
}
#endif
#endif

