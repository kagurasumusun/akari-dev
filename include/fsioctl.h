/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_FSIOCTL_H
#define WCE_FSIOCTL_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagFILE_ZERO_DATA_INFORMATION { LARGE_INTEGER FileOffset; LARGE_INTEGER BeyondFinalZero; } FILE_ZERO_DATA_INFORMATION, *PFILE_ZERO_DATA_INFORMATION, *LPFILE_ZERO_DATA_INFORMATION;
typedef struct tagENCRYPTION_BUFFER { DWORD EncryptionOperation; BYTE Private[1]; } ENCRYPTION_BUFFER, *PENCRYPTION_BUFFER, *LPENCRYPTION_BUFFER;
typedef struct tagFILE_ALLOCATED_RANGE_BUFFER { LARGE_INTEGER FileOffset; LARGE_INTEGER Length; } FILE_ALLOCATED_RANGE_BUFFER, *PFILE_ALLOCATED_RANGE_BUFFER, *LPFILE_ALLOCATED_RANGE_BUFFER;
typedef struct tagAFS_MOUNT_INFO { DWORD cbSize; int iAFSIndex; DWORD dwVolume; DWORD dwMountFlags; } AFS_MOUNT_INFO, *PAFS_MOUNT_INFO, *LPAFS_MOUNT_INFO;
typedef struct tagFS_SIMULATION_MODE_INFO { DWORD cbSize; DWORD dwSimulationMode; } FS_SIMULATION_MODE_INFO, *PFS_SIMULATION_MODE_INFO, *LPFS_SIMULATION_MODE_INFO;
typedef struct tagFILE_STREAM_INFO_STANDARD { DWORD dwAttributes; DWORD dwExtendedAttributes; FILETIME ftCreationTime; FILETIME ftLastAccessTime; FILETIME ftLastWriteTime; LARGE_INTEGER logicalStreamSize; LARGE_INTEGER physicalStreamSize; } FILE_STREAM_INFO_STANDARD, *PFILE_STREAM_INFO_STANDARD, *LPFILE_STREAM_INFO_STANDARD;


#ifdef __cplusplus
}
#endif
#endif

