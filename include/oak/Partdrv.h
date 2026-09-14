/* Partdrv.h -- partition driver (partdrv) DDI (record surface).
 *
 * Source pages: File Systems and Data Store book, Partition Manager
 * rows printing "Header: Partdrv.h" (17 PD_* function pages + the
 * PD_PARTINFO / PD_STOREINFO structure pages ms891440 / ms891443).
 * The PD_* entry points are implemented by the partition driver
 * (driver-supplied, MyFSD callback precedent); prototypes are
 * recorded.  The structures embed the unpublished SECTORNUM type,
 * so they are held (prints recorded, opaque closure).
 * See docs/inventory.md M79b.
 */

#ifndef AKARI_PARTDRV_H
#define AKARI_PARTDRV_H

#include "Windef.h"    /* DWORD, BYTE, BOOL, HANDLE, LPCTSTR, LPDWORD */

/* --- Held structures (SECTORNUM unpublished). ------------------- */
/* ms891440 "PD_PARTINFO": print `typedef struct _PD_PARTINFO {DWORD
 * cbSize;TCHAR szPartitionName[PARTITIONNAMESIZE];SECTORNUM
 * snNumSectors;FILETIME ftCreated;FILETIME ftLastModified;DWORD
 * dwAttributes;BYTE bPartType;} PD_PARTINFO, *PPD_PARTINFO;` --
 * PARTITIONNAMESIZE and SECTORNUM are not printed by any CE page;
 * held. */
typedef struct _PD_PARTINFO PD_PARTINFO, *PPD_PARTINFO;

/* ms891443 "PD_STOREINFO": print `typedef struct _PD_STOREINFO {DWORD
 * cbSize;SECTORNUM snNumSectors;DWORD dwBytesPerSector;SECTORNUM
 * snFreeSectors;SECTORNUM snBiggestPartCreatable;FILETIME ftCreated;
 * FILETIME ftLastModified;DWORD dwAttributes;} PD_STOREINFO,
 * *PPD_STOREINFO;` -- held (SECTORNUM). */
typedef struct _PD_STOREINFO PD_STOREINFO, *PPD_STOREINFO;

/* --- Recorded driver-supplied prototypes. ---------------------- */
/* `PD_ClosePartition void PD_ClosePartition(DWORD dwPartitionId);` */
/* `PD_CloseStore void PD_CloseStore(DWORDdwStoreId);` */
/* `PD_CreatePartition DWORD PD_CreatePartition(DWORD dwStoreId,LPCTSTR szPartName,BYTE bPartType, SECTORNUM numSectors, BOOL bAuto);` */
/* `PD_DeletePartition DWORD PD_DeletePartition(DWORD dwStoreId, LPCTSTR szPartName);` */
/* `PD_DeviceIoControl DWORD PD_DeviceIoControl(DWORD dwPartitionId, DWORD dwCode, PBYTE pInBuf, DWORD nInBufSize, PBYTE pOutBuf, DWORD nOutBufSize, PDWORD pBytesReturned);` */
/* `PD_FindPartitionClose void PD_FindPartitionClose(DWORDdwSearchId);` */
/* `PD_FindPartitionNext DWORD PD_FindPartitionNext(DWORDdwSearchId, PD_PARTINFO* pInfo);` */
/* `PD_FindPartitionStart DWORD PD_FindPartitionStart(DWORD dwStoreId, LPDWORD pdwSearchId);` */
/* `PD_FormatPartition DWORD PD_FormatPartition(DWORDdwStoreId, LPCTSTR szPartName, BYTE bPartType, BOOL bAuto);` */
/* `PD_FormatStore DWORD PD_FormatStore(DWORDdwStoreId);` */
/* `PD_GetPartitionInfo DWORD PD_GetPartitionInfo(DWORDdwStoreId, LPCTSTR szPartName, PD_PARTINFO* pInfo);` */
/* `PD_GetStoreInfo DWORD PD_GetStoreInfo(DWORDdwStoreId,PD_STOREINFO* pInfo);` */
/* `PD_IsStoreFormatted DWORD PD_IsStoreFormatted(DWORDdwStoreId);` */
/* `PD_OpenPartition DWORD PD_OpenPartition(DWORD dwStoreId, LPCTSTR szPartName, LPDWORD pdwPartitionId);` */
/* `PD_OpenStore DWORD PD_OpenStore(HANDLE hDisk, LPDWORD pdwStoreId);` */
/* `PD_RenamePartition DWORD PD_RenamePartition(DWORD dwStoreId, LPCTSTR szOldName, LPCTSTR szNewName);` */
/* `PD_SetPartitionAttrs DWORD PD_SetPartitionAttrs(DWORDdwStoreId, LPCTSTR szPartName, DWORD dwAttr);` */


/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms891425: page-printed prototype (Windows CE .NET 4.0 and later.). */
void PD_ClosePartition(DWORD dwPartitionId);

/* ms891426: page-printed prototype (Windows CE .NET 4.0 and later.). */
void PD_CloseStore(DWORD dwStoreId);

/* ms891428: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_DeletePartition(DWORD dwStoreId, LPCTSTR szPartName);

/* ms891429: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_DeviceIoControl(DWORD dwPartitionId, DWORD dwCode, PBYTE pInBuf, DWORD nInBufSize, PBYTE pOutBuf, DWORD nOutBufSize, PDWORD pBytesReturned);

/* ms891430: page-printed prototype (Windows CE .NET 4.0 and later.). */
void PD_FindPartitionClose(DWORD dwSearchId);

/* ms891431: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_FindPartitionNext(DWORD dwSearchId, PD_PARTINFO* pInfo);

/* ms891432: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_FindPartitionStart(DWORD dwStoreId, LPDWORD pdwSearchId);

/* ms891433: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_FormatPartition(DWORD dwStoreId, LPCTSTR szPartName, BYTE bPartType, BOOL bAuto);

/* ms891434: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_FormatStore(DWORD dwStoreId);

/* ms891435: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_GetPartitionInfo(DWORD dwStoreId, LPCTSTR szPartName, PD_PARTINFO* pInfo);

/* ms891436: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_GetStoreInfo(DWORD dwStoreId, PD_STOREINFO* pInfo);

/* ms891437: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_IsStoreFormatted(DWORD dwStoreId);

/* ms891438: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_OpenPartition(DWORD dwStoreId, LPCTSTR szPartName, LPDWORD pdwPartitionId);

/* ms891439: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_OpenStore(HANDLE hDisk, LPDWORD pdwStoreId);

/* ms891441: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_RenamePartition(DWORD dwStoreId, LPCTSTR szOldName, LPCTSTR szNewName);

/* ms891442: page-printed prototype (Windows CE .NET 4.0 and later.). */
DWORD PD_SetPartitionAttrs(DWORD dwStoreId, LPCTSTR szPartName, DWORD dwAttr);

#endif /* AKARI_PARTDRV_H */
