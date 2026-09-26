/* Store Manager. Original text. Exported by coredll.dll.
 *
 * The store and partition calls only exist on Windows CE 6.0; earlier releases
 * have no export to link against, so everything except CeGetVolumeInfo is
 * switched off there. CeGetVolumeInfo arrived one release earlier, on CE 5.0.
 */
#ifndef AKARI_WCE_STOREMGR_H
#define AKARI_WCE_STOREMGR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"
#include "tchar.h"

#define STORE_MOUNT_GUID_STRING L"{C1115848-46FD-4976-BDE9-D79448457004}"

/* STOREINFO dwAttributes. */
#define STORE_ATTRIBUTE_READONLY     0x00000001
#define STORE_ATTRIBUTE_REMOVABLE    0x00000002
#define STORE_ATTRIBUTE_UNFORMATTED  0x00000004
#define STORE_ATTRIBUTE_AUTOFORMAT   0x00000008
#define STORE_ATTRIBUTE_AUTOPART     0x00000010
#define STORE_ATTRIBUTE_AUTOMOUNT    0x00000020

/* PARTINFO dwAttributes. */
#define PARTITION_ATTRIBUTE_EXPENDABLE 0x00000001
#define PARTITION_ATTRIBUTE_READONLY   0x00000002
#define PARTITION_ATTRIBUTE_AUTOFORMAT 0x00000004
#define PARTITION_ATTRIBUTE_ACTIVE     0x00000008
#define PARTITION_ATTRIBUTE_BOOT       0x00000008
#define PARTITION_ATTRIBUTE_MOUNTED    0x00000010

/* STORAGEDEVICEINFO dwDeviceClass. */
#define STORAGE_DEVICE_CLASS_BLOCK       0x1
#define STORAGE_DEVICE_CLASS_MULTIMEDIA  0x2

/* STORAGEDEVICEINFO dwDeviceType. */
#define STORAGE_DEVICE_TYPE_PCIIDE           (1 << 0)
#define STORAGE_DEVICE_TYPE_FLASH            (1 << 1)
#define STORAGE_DEVICE_TYPE_ATA              (1 << 2)
#define STORAGE_DEVICE_TYPE_ATAPI            (1 << 4)
#define STORAGE_DEVICE_TYPE_PCCARD           (1 << 5)
#define STORAGE_DEVICE_TYPE_CFCARD           (1 << 6)
#define STORAGE_DEVICE_TYPE_SRAM             (1 << 7)
#define STORAGE_DEVICE_TYPE_DVD              (1 << 8)
#define STORAGE_DEVICE_TYPE_CDROM            (1 << 9)
#define STORAGE_DEVICE_TYPE_USB              (1 << 10)
#define STORAGE_DEVICE_TYPE_1394             (1 << 11)
#define STORAGE_DEVICE_TYPE_DOC              (1 << 12)
#define STORAGE_DEVICE_TYPE_UNKNOWN          (1 << 29)
#define STORAGE_DEVICE_TYPE_REMOVABLE_DRIVE  (1 << 30)
#define STORAGE_DEVICE_TYPE_REMOVABLE_MEDIA  (1 << 31)

/* STORAGEDEVICEINFO dwDeviceFlags. */
#define STORAGE_DEVICE_FLAG_READWRITE   (1 << 0)
#define STORAGE_DEVICE_FLAG_READONLY    (1 << 1)
#define STORAGE_DEVICE_FLAG_TRANSACTED  (1 << 2)
#define STORAGE_DEVICE_FLAG_MEDIASENSE  (1 << 3)
#define STORAGE_DEVICE_FLAG_XIP         (1 << 4)

/* CE_VOLUME_INFO dwAttributes and dwFlags. */
#define CE_VOLUME_ATTRIBUTE_READONLY  0x1
#define CE_VOLUME_ATTRIBUTE_HIDDEN    0x2
#define CE_VOLUME_ATTRIBUTE_REMOVABLE 0x4
#define CE_VOLUME_ATTRIBUTE_SYSTEM    0x8
#define CE_VOLUME_ATTRIBUTE_BOOT      0x10

#define CE_VOLUME_TRANSACTION_SAFE             0x1
#define CE_VOLUME_FLAG_TRANSACT_WRITE          0x2
#define CE_VOLUME_FLAG_WFSC_SUPPORTED          0x4
#define CE_VOLUME_FLAG_LOCKFILE_SUPPORTED      0x8
#define CE_VOLUME_FLAG_NETWORK                 0x10
#define CE_VOLUME_FLAG_STORE                   0x20
#define CE_VOLUME_FLAG_RAMFS                   0x40
#define CE_VOLUME_FLAG_FILE_SECURITY_SUPPORTED 0x80
#define CE_VOLUME_FLAG_64BIT_FILES_SUPPORTED   0x100

/* Fixed array sizes used by the structures below. */
#define DEVICENAMESIZE     8
#define STORENAMESIZE      32
#define FILESYSNAMESIZE    32
#define PARTITIONNAMESIZE  32
#define PROFILENAMESIZE    32
#define VOLUMENAMESIZE     64

/* A sector number or sector count. */
typedef ULONGLONG SECTORNUM;

typedef enum akari_CE_VOLUME_INFO_LEVEL {
    CeVolumeInfoLevelStandard = 0
} CE_VOLUME_INFO_LEVEL;

typedef struct akari_CE_VOLUME_INFO {
    DWORD cbSize;
    DWORD dwAttributes;
    DWORD dwFlags;
    DWORD dwBlockSize;
    TCHAR szStoreName[STORENAMESIZE];
    TCHAR szPartitionName[PARTITIONNAMESIZE];
} CE_VOLUME_INFO, *PCE_VOLUME_INFO, *LPCE_VOLUME_INFO;

#if (_WIN32_WCE >= 0x500)
WINBASEAPI BOOL WINAPI CeGetVolumeInfoW(LPCWSTR pszRootPath,
    CE_VOLUME_INFO_LEVEL InfoLevel, LPCE_VOLUME_INFO lpVolumeInfo);
#define CeGetVolumeInfo CeGetVolumeInfoW
#endif

#if (_WIN32_WCE >= 0x600)

typedef struct akari_STORAGEDEVICEINFO {
    DWORD cbSize;
    TCHAR szProfile[PROFILENAMESIZE];
    DWORD dwDeviceClass;
    DWORD dwDeviceType;
    DWORD dwDeviceFlags;
} STORAGEDEVICEINFO, *PSTORAGEDEVICEINFO;

typedef struct akari_STOREINFO {
    DWORD cbSize;
    TCHAR szDeviceName[DEVICENAMESIZE];
    TCHAR szStoreName[STORENAMESIZE];
    DWORD dwDeviceClass;
    DWORD dwDeviceType;
    STORAGEDEVICEINFO sdi;
    DWORD dwDeviceFlags;
    SECTORNUM snNumSectors;
    DWORD dwBytesPerSector;
    SECTORNUM snFreeSectors;
    SECTORNUM snBiggestPartCreatable;
    FILETIME ftCreated;
    FILETIME ftLastModified;
    DWORD dwAttributes;
    DWORD dwPartitionCount;
    DWORD dwMountCount;
} STOREINFO, *PSTOREINFO;

typedef struct akari_PARTINFO {
    DWORD cbSize;
    TCHAR szPartitionName[PARTITIONNAMESIZE];
    TCHAR szFileSys[FILESYSNAMESIZE];
    TCHAR szVolumeName[VOLUMENAMESIZE];
    SECTORNUM snNumSectors;
    FILETIME ftCreated;
    FILETIME ftLastModified;
    DWORD dwAttributes;
    BYTE bPartType;
} PARTINFO, *PPARTINFO;

typedef struct akari_STORAGECONTEXT {
    DWORD cbSize;
    STOREINFO StoreInfo;
    PARTINFO PartInfo;
    DWORD dwFlags;
} STORAGECONTEXT, *PSTORAGECONTEXT;

STOREAPI HANDLE WINAPI OpenStore(LPCTSTR szDeviceName);
STOREAPI BOOL WINAPI DismountStore(HANDLE hStore);
STOREAPI BOOL WINAPI FormatStore(HANDLE hStore);
STOREAPI HANDLE WINAPI FindFirstStore(PSTOREINFO pStoreInfo);
STOREAPI BOOL WINAPI FindNextStore(HANDLE hSearch, PSTOREINFO pStoreInfo);
STOREAPI BOOL WINAPI FindCloseStore(HANDLE hSearch);
STOREAPI BOOL WINAPI GetStoreInfo(HANDLE hStore, PSTOREINFO pStoreInfo);
STOREAPI BOOL WINAPI CreatePartition(HANDLE hStore, LPCTSTR szPartitionName,
    SECTORNUM snNumSectors);
STOREAPI BOOL WINAPI CreatePartitionEx(HANDLE hStore, LPCTSTR szPartitionName,
    BYTE bPartType, SECTORNUM snNumSectors);
STOREAPI BOOL WINAPI DeletePartition(HANDLE hStore, LPCTSTR szPartitionName);
STOREAPI HANDLE WINAPI OpenPartition(HANDLE hStore, LPCTSTR szPartitionName);
STOREAPI BOOL WINAPI MountPartition(HANDLE hPartition);
STOREAPI BOOL WINAPI DismountPartition(HANDLE hPartition);
STOREAPI BOOL WINAPI RenamePartition(HANDLE hPartition, LPCTSTR szNewName);
STOREAPI BOOL WINAPI SetPartitionAttributes(HANDLE hPartition, DWORD dwAttrs);
STOREAPI BOOL WINAPI GetPartitionInfo(HANDLE hPartition, PPARTINFO pPartInfo);
STOREAPI BOOL WINAPI FormatPartition(HANDLE hPartition);
STOREAPI BOOL WINAPI FormatPartitionEx(HANDLE hPartition, BYTE bPartType,
    BOOL bAuto);
STOREAPI HANDLE WINAPI FindFirstPartition(HANDLE hStore, PPARTINFO pPartInfo);
STOREAPI BOOL WINAPI FindNextPartition(HANDLE hSearch, PPARTINFO pPartInfo);
STOREAPI BOOL WINAPI FindClosePartition(HANDLE hSearch);

#endif /* _WIN32_WCE >= 0x600 */

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_STOREMGR_H */
