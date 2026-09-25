/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_MEASURE_H
#define WCE_MEASURE_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif


WCE_IMPORT void WINAPI Msr_Init(void) WCE_LINK(Msr_Init);
WCE_IMPORT void WINAPI Msr_Terminate(void) WCE_LINK(Msr_Terminate);
WCE_IMPORT int WINAPI Msr_Register(LPTSTR Incident) WCE_LINK(Msr_Register);
WCE_IMPORT void WINAPI Msr_Reset(int Id) WCE_LINK(Msr_Reset);
WCE_IMPORT void WINAPI Msr_Control(int iAction) WCE_LINK(Msr_Control);
WCE_IMPORT void WINAPI Msr_Start(int Id) WCE_LINK(Msr_Start);
WCE_IMPORT void WINAPI Msr_Stop(int Id) WCE_LINK(Msr_Stop);
WCE_IMPORT void WINAPI Msr_Note(int Id) WCE_LINK(Msr_Note);
WCE_IMPORT void WINAPI Msr_Integer(int Id, int n) WCE_LINK(Msr_Integer);
WCE_IMPORT void WINAPI Msr_Float(int Id, float n) WCE_LINK(Msr_Float);
WCE_IMPORT void WINAPI Msr_Dump(HANDLE hFile) WCE_LINK(Msr_Dump);
WCE_IMPORT void WINAPI Msr_DumpStats(HANDLE hFile) WCE_LINK(Msr_DumpStats);
WCE_IMPORT void WINAPI MSR_DUMPPROC(HANDLE hFile) WCE_LINK(MSR_DUMPPROC);
WCE_IMPORT void WINAPI MSR_CONTROLPROC(int iAction) WCE_LINK(MSR_CONTROLPROC);

#ifdef __cplusplus
}
#endif
#endif

