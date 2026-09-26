/* Power management. Original text. Exported by coredll.dll. */
#ifndef AKARI_WCE_PM_H
#define AKARI_WCE_PM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"
#include "tchar.h"

typedef struct akari_POWER_BROADCAST {
    DWORD Message;
    DWORD Flags;
    DWORD Length;
    WCHAR SystemPowerState[1];
} POWER_BROADCAST, *PPOWER_BROADCAST;

typedef struct akari_SYSTEM_POWER_STATUS_EX {
    BYTE ACLineStatus;
    BYTE BatteryFlag;
    BYTE BatteryLifePercent;
    BYTE Reserved1;
    DWORD BatteryLifeTime;
    DWORD BatteryFullLifeTime;
    BYTE Reserved2;
    BYTE BackupBatteryFlag;
    BYTE BackupBatteryLifePercent;
    BYTE Reserved3;
    DWORD BackupBatteryLifeTime;
    DWORD BackupBatteryFullLifeTime;
} SYSTEM_POWER_STATUS_EX, *PSYSTEM_POWER_STATUS_EX;

typedef struct akari_SYSTEM_POWER_STATUS_EX2 {
    BYTE ACLineStatus;
    BYTE BatteryFlag;
    BYTE BatteryLifePercent;
    BYTE Reserved1;
    DWORD BatteryLifeTime;
    DWORD BatteryFullLifeTime;
    BYTE Reserved2;
    BYTE BackupBatteryFlag;
    BYTE BackupBatteryLifePercent;
    BYTE Reserved3;
    DWORD BackupBatteryLifeTime;
    DWORD BackupBatteryFullLifeTime;
    DWORD BatteryVoltage;
    DWORD BatteryCurrent;
    DWORD BatteryAverageCurrent;
    DWORD BatteryAverageInterval;
    DWORD BatterymAHourConsumed;
    DWORD BatteryTemperature;
    DWORD BackupBatteryVoltage;
    BYTE BatteryChemistry;
} SYSTEM_POWER_STATUS_EX2, *PSYSTEM_POWER_STATUS_EX2;

#define AC_LINE_OFFLINE     0x00
#define AC_LINE_ONLINE      0x01
#define AC_LINE_BACKUP_POWER 0x02
#define AC_LINE_UNKNOWN     0xFF

#define BATTERY_FLAG_HIGH          0x01
#define BATTERY_FLAG_LOW           0x02
#define BATTERY_FLAG_CRITICAL      0x04
#define BATTERY_FLAG_CHARGING      0x08
#define BATTERY_FLAG_NO_BATTERY    0x80
#define BATTERY_FLAG_UNKNOWN       0xFF

#define PBT_TRANSITION        1
#define PBT_RESUME            2
#define PBT_POWERINFOCHANGE   8
#define PBT_OEMACTION         4
#define POWER_STATE_ON (DWORD)(0x00010000)
#define POWER_STATE_OFF (DWORD)(0x00020000)
#define POWER_STATE_CRITICAL (DWORD)(0x00040000)
#define POWER_STATE_USERIDLE (DWORD)(0x01000000)
#define POWER_STATE_BACKLIGHT 0x00200000

typedef HANDLE HPOWER_NOTIFY, *PHPOWER_NOTIFY;
typedef DWORD DEVICE_POWER_NOTIFY;
typedef DWORD (*PFN_POWER_NOTIFY)(DWORD, PVOID);

/* Device power states, Dx. */
typedef enum akari_CEDEVICE_POWER_STATE {
    PwrDeviceUnspecified = -1,
    D0 = 0,
    D1,
    D2,
    D3,
    D4,
    PwrDeviceMaximum
} CEDEVICE_POWER_STATE, *PCEDEVICE_POWER_STATE;

PMAPI BOOL WINAPI GetSystemPowerStatusEx(PSYSTEM_POWER_STATUS_EX pSystemPowerStatus,
    BOOL fUpdate);
PMAPI DWORD WINAPI GetSystemPowerStatusEx2(PSYSTEM_POWER_STATUS_EX2 pSystemPowerStatus,
    DWORD dwLen, BOOL fUpdate);
PMAPI DWORD WINAPI SetSystemPowerState(LPCWSTR pwszStateName, DWORD dwHint, DWORD dwFlags);
PMAPI DWORD WINAPI GetSystemPowerState(LPTSTR pwszName, DWORD nBufferSize, PDWORD pdwFlags);
PMAPI DWORD WINAPI DevicePowerNotify(PVOID pvDevice,
    CEDEVICE_POWER_STATE DeviceState, DWORD Flags);
#if (_WIN32_WCE >= 0x500)
PMAPI DWORD WINAPI GetIdleTime(VOID);
#endif
/*
 * DevicePowerNotifyClose, GetSystemPowerUpTime, SetThreadTime and
 * SetGwesPowerUpTime are not exports on any supported release, so they are not
 * declared here.
 */

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_PM_H */
