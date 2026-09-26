/* Storage Manager. Original text. CE 5.0 and later; exported by coredll.dll. */
#ifndef AKARI_WCE_STOREMGR_H
#define AKARI_WCE_STOREMGR_H

#include "winbase.h"

#define MAXDEVICENAME  64
#define MAXFATNAME     16
#define MAXFATTYPE     16
#define MAXVOLNAME     64
#define MAXGUID        16
#define MAXREGPATH     256

typedef struct akari_STOREINFO {
    DWORD cbSize;
    WCHAR szDeviceName[MAXDEVICENAME];
    WCHAR szDeviceFolder[MAXREGPATH];
    DWORD dwDeviceFlags;
    DWORD dwStoreFlags;
    WCHAR szStoreName[MAXDEVICENAME];
    GUID StoreGuid;
    WCHAR szProfile[MAXDEVICENAME];
    DWORD dwStoreId;
    DWORD dwPartitionId;
    DWORD dwStoreType;
    DWORD dwReserved;
    DWORD dwStoreVersion;
} STOREINFO, *PSTOREINFO;

typedef struct akari_PARTITIONINFO {
    DWORD cbSize;
    WCHAR szPartitionName[MAXDEVICENAME];
    WCHAR szFolderName[MAXFATNAME];
    GUID PartGuid;
    DWORD dwStoreId;
    DWORD dwPartitionId;
    DWORD dwFirstSector;
    DWORD dwLastSector;
    WCHAR szMountPath[MAXFATNAME];
    DWORD dwPartType;
    DWORD dwPartAttributes;
    FILETIME ftMounted;
} PARTITIONINFO, *PPARTITIONINFO;

#define DEVICE_FLAG_READONLY    0x00000001
#define DEVICE_FLAG_READWRITE   0x00000002
#define DEVICE_FLAG_REMOVABLE   0x00000004
#define DEVICE_FLAG_MANAGED     0x00000008

#define STORE_FLAG_READWRITE    0x00000001
#define STORE_FLAG_ROOTFS       0x00000002
#define STORE_FLAG_REMOVABLE    0x00000004
#define STORE_FLAG_UNNAMED      0x00000008
#define STORE_FLAG_BINARYIMAGE  0x00000010

STOREAPI HANDLE WINAPI FindFirstStore(PSTOREINFO pStoreInfo);
STOREAPI BOOL WINAPI FindNextStore(HANDLE hSearch, PSTOREINFO pStoreInfo);
STOREAPI BOOL WINAPI FindCloseStore(HANDLE hSearch);
STOREAPI BOOL WINAPI GetStoreInfo(HANDLE hStore, PSTOREINFO pStoreInfo);
STOREAPI HANDLE WINAPI FindFirstPartition(HANDLE hStore, PPARTITIONINFO pPartInfo);
STOREAPI BOOL WINAPI FindNextPartition(HANDLE hSearch, PPARTITIONINFO pPartInfo);
STOREAPI BOOL WINAPI FindClosePartition(HANDLE hSearch);
STOREAPI BOOL WINAPI GetPartitionInfo(HANDLE hPartition, PPARTITIONINFO pPartInfo);
STOREAPI BOOL WINAPI OpenStore(LPCWSTR szDeviceName, HANDLE *pStore);
STOREAPI BOOL WINAPI DismountStore(HANDLE hStore);
/*
 * There is no CloseStore export: a store handle is released with DismountStore,
 * and the search handles returned by FindFirst* are released with
 * FindCloseStore / FindClosePartition.
 */
STOREAPI BOOL WINAPI CreatePartition(HANDLE hStore, LPCWSTR pwszPartName, DWORD dwMBPartSize,
    HANDLE *phPartition, PPARTITIONINFO pPartInfo);
STOREAPI BOOL WINAPI FormatPartition(HANDLE hPartition, LPCWSTR pwszPartType, DWORD dwFlags);
STOREAPI BOOL WINAPI MountPartition(HANDLE hPartition);
STOREAPI BOOL WINAPI DismountPartition(HANDLE hPartition);
STOREAPI BOOL WINAPI DeletePartition(HANDLE hPartition);
STOREAPI BOOL WINAPI RenamePartition(HANDLE hPartition, LPCWSTR pwszPartName);

#endif /* AKARI_WCE_STOREMGR_H */
