/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_TAPI_H
#define WCE_TAPI_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagLINEADDRESSSTATUS { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwNumInUse; DWORD dwNumActiveCalls; DWORD dwNumOnHoldCalls; DWORD dwNumOnHoldPendCalls; DWORD dwAddressFeatures; DWORD dwNumRingsNoAnswer; DWORD dwForwardNumEntries; DWORD dwForwardSize; DWORD dwForwardOffset; DWORD dwTerminalModesSize; DWORD dwTerminalModesOffset; DWORD dwDevSpecificSize; DWORD dwDevSpecificOffset; } LINEADDRESSSTATUS, *PLINEADDRESSSTATUS, *LPLINEADDRESSSTATUS;
typedef struct tagLINEDIALPARAMS { DWORD dwDialPause; DWORD dwDialSpeed; DWORD dwDigitDuration; DWORD dwWaitForDialtone; } LINEDIALPARAMS, *PLINEDIALPARAMS, *LPLINEDIALPARAMS;
typedef struct tagLINECALLLIST { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwCallsNumEntries; DWORD dwCallsSize; DWORD dwCallsOffset; } LINECALLLIST, *PLINECALLLIST, *LPLINECALLLIST;
typedef struct tagLINECALLSTATUS { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwCallState; DWORD dwCallStateMode; DWORD dwCallPrivilege; DWORD dwCallFeatures; DWORD dwDevSpecificSize; DWORD dwDevSpecificOffset; DWORD dwCallFeatures2; SYSTEMTIME tStateEntryTime; } LINECALLSTATUS, *PLINECALLSTATUS, *LPLINECALLSTATUS;
typedef struct tagLINECALLTREATMENTENTRY { DWORD dwCallTreatmentID; DWORD dwCallTreatmentNameSize; DWORD dwCallTreatmentNameOffset; } LINECALLTREATMENTENTRY, *PLINECALLTREATMENTENTRY, *LPLINECALLTREATMENTENTRY;
typedef struct tagLINECARDENTRY { DWORD dwPermanentCardID; DWORD dwCardNameSize; DWORD dwCardNameOffset; DWORD dwCardNumberDigits; DWORD dwSameAreaRuleSize; DWORD dwSameAreaRuleOffset; DWORD dwLongDistanceRuleSize; DWORD dwLongDistanceRuleOffset; DWORD dwInternationalRuleSize; DWORD dwInternationalRuleOffset; DWORD dwOptions; } LINECARDENTRY, *PLINECARDENTRY, *LPLINECARDENTRY;
typedef struct tagLINECOUNTRYENTRY { DWORD dwCountryID; DWORD dwCountryCode; DWORD dwNextCountryID; DWORD dwCountryNameSize; DWORD dwCountryNameOffset; DWORD dwSameAreaRuleSize; DWORD dwSameAreaRuleOffset; DWORD dwLongDistanceRuleSize; DWORD dwLongDistanceRuleOffset; DWORD dwInternationalRuleSize; DWORD dwInternationalRuleOffset; } LINECOUNTRYENTRY, *PLINECOUNTRYENTRY, *LPLINECOUNTRYENTRY;
typedef struct tagLINECOUNTRYLIST { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwNumCountries; DWORD dwCountryListSize; DWORD dwCountryListOffset; } LINECOUNTRYLIST, *PLINECOUNTRYLIST, *LPLINECOUNTRYLIST;
typedef struct tagLINEDEVSTATUS { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwNumOpens; DWORD dwOpenMediaModes; DWORD dwNumActiveCalls; DWORD dwNumOnHoldCalls; DWORD dwNumOnHoldPendCalls; DWORD dwLineFeatures; DWORD dwNumCallCompletions; DWORD dwRingMode; DWORD dwSignalLevel; DWORD dwBatteryLevel; DWORD dwRoamMode; DWORD dwDevStatusFlags; DWORD dwTerminalModesSize; DWORD dwTerminalModesOffset; DWORD dwDevSpecificSize; DWORD dwDevSpecificOffset; DWORD dwAvailableMediaModes; DWORD dwAppInfoSize; DWORD dwAppInfoOffset; } LINEDEVSTATUS, *PLINEDEVSTATUS, *LPLINEDEVSTATUS;
typedef struct tagLINEEXTENSIONID { DWORD dwExtensionID0; DWORD dwExtensionID1; DWORD dwExtensionID2; DWORD dwExtensionID3; } LINEEXTENSIONID, *PLINEEXTENSIONID, *LPLINEEXTENSIONID;
typedef struct tagLINEFORWARD { DWORD dwForwardMode; DWORD dwCallerAddressSize; DWORD dwCallerAddressOffset; DWORD dwDestCountryCode; DWORD dwDestAddressSize; DWORD dwDestAddressOffset; } LINEFORWARD, *PLINEFORWARD, *LPLINEFORWARD;
typedef struct tagLINEFORWARDLIST { DWORD dwTotalSize; DWORD dwNumEntries; LINEFORWARD ForwardList[1]; } LINEFORWARDLIST, *PLINEFORWARDLIST, *LPLINEFORWARDLIST;
typedef struct tagLINEGENERATETONE { DWORD dwFrequency; DWORD dwCadenceOn; DWORD dwCadenceOff; DWORD dwVolume; } LINEGENERATETONE, *PLINEGENERATETONE, *LPLINEGENERATETONE;
typedef struct tagLINELOCATIONENTRY { DWORD dwPermanentLocationID; DWORD dwLocationNameSize; DWORD dwLocationNameOffset; DWORD dwCountryCode; DWORD dwCityCodeSize; DWORD dwCityCodeOffset; DWORD dwPreferredCardID; DWORD dwLocalAccessCodeSize; DWORD dwLocalAccessCodeOffset; DWORD dwLongDistanceAccessCodeSize; DWORD dwLongDistanceAccessCodeOffset; DWORD dwTollPrefixListSize; DWORD dwTollPrefixListOffset; DWORD dwCountryID; DWORD dwOptions; DWORD dwCancelCallWaitingSize; DWORD dwCancelCallWaitingOffset; } LINELOCATIONENTRY, *PLINELOCATIONENTRY, *LPLINELOCATIONENTRY;
typedef struct tagLINEMEDIACONTROLCALLSTATE { DWORD dwCallStates; DWORD dwMediaControl; } LINEMEDIACONTROLCALLSTATE, *PLINEMEDIACONTROLCALLSTATE, *LPLINEMEDIACONTROLCALLSTATE;
typedef struct tagLINEMEDIACONTROLDIGIT { DWORD dwDigit; DWORD dwDigitModes; DWORD dwMediaControl; } LINEMEDIACONTROLDIGIT, *PLINEMEDIACONTROLDIGIT, *LPLINEMEDIACONTROLDIGIT;
typedef struct tagLINEMEDIACONTROLMEDIA { DWORD dwMediaModes; DWORD dwDuration; DWORD dwMediaControl; } LINEMEDIACONTROLMEDIA, *PLINEMEDIACONTROLMEDIA, *LPLINEMEDIACONTROLMEDIA;
typedef struct tagLINEMEDIACONTROLTONE { DWORD dwAppSpecific; DWORD dwDuration; DWORD dwFrequency1; DWORD dwFrequency2; DWORD dwFrequency3; DWORD dwMediaControl; } LINEMEDIACONTROLTONE, *PLINEMEDIACONTROLTONE, *LPLINEMEDIACONTROLTONE;
typedef struct tagLINEMESSAGE { DWORD hDevice; DWORD dwMessageID; DWORD dwCallbackInstance; DWORD dwParam1; DWORD dwParam2; DWORD dwParam3; } LINEMESSAGE, *PLINEMESSAGE, *LPLINEMESSAGE;
typedef struct tagLINEMONITORTONE { DWORD dwAppSpecific; DWORD dwDuration; DWORD dwFrequency1; DWORD dwFrequency2; DWORD dwFrequency3; } LINEMONITORTONE, *PLINEMONITORTONE, *LPLINEMONITORTONE;
typedef struct tagLINEPROVIDERENTRY { DWORD dwPermanentProviderID; DWORD dwProviderFilenameSize; DWORD dwProviderFilenameOffset; } LINEPROVIDERENTRY, *PLINEPROVIDERENTRY, *LPLINEPROVIDERENTRY;
typedef struct tagLINEPROVIDERLIST { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwNumProviders; DWORD dwProviderListSize; DWORD dwProviderListOffset; } LINEPROVIDERLIST, *PLINEPROVIDERLIST, *LPLINEPROVIDERLIST;
typedef struct tagLINETERMCAPS { DWORD dwTermDev; DWORD dwTermModes; DWORD dwTermSharing; } LINETERMCAPS, *PLINETERMCAPS, *LPLINETERMCAPS;
typedef struct tagLINETRANSLATECAPS { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwNumLocations; DWORD dwLocationListSize; DWORD dwLocationListOffset; DWORD dwCurrentLocationID; DWORD dwNumCards; DWORD dwCardListSize; DWORD dwCardListOffset; DWORD dwCurrentPreferredCardID; } LINETRANSLATECAPS, *PLINETRANSLATECAPS, *LPLINETRANSLATECAPS;
typedef struct tagLINETRANSLATEOUTPUT { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwDialableStringSize; DWORD dwDialableStringOffset; DWORD dwDisplayableStringSize; DWORD dwDisplayableStringOffset; DWORD dwCurrentCountry; DWORD dwDestCountry; DWORD dwTranslateResults; } LINETRANSLATEOUTPUT, *PLINETRANSLATEOUTPUT, *LPLINETRANSLATEOUTPUT;
typedef struct tagPHONEBUTTONINFO { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwButtonMode; DWORD dwButtonFunction; DWORD dwButtonTextSize; DWORD dwButtonTextOffset; DWORD dwDevSpecificSize; DWORD dwDevSpecificOffset; DWORD dwButtonState; } PHONEBUTTONINFO, *PPHONEBUTTONINFO, *LPPHONEBUTTONINFO;
typedef struct tagPHONEEXTENSIONID { DWORD dwExtensionID0; DWORD dwExtensionID1; DWORD dwExtensionID2; DWORD dwExtensionID3; } PHONEEXTENSIONID, *PPHONEEXTENSIONID, *LPPHONEEXTENSIONID;
typedef struct tagPHONEMESSAGE { DWORD hDevice; DWORD dwMessageID; DWORD dwCallbackInstance; DWORD dwParam1; DWORD dwParam2; DWORD dwParam3; } PHONEMESSAGE, *PPHONEMESSAGE, *LPPHONEMESSAGE;
typedef struct tagPHONESTATUS { DWORD dwTotalSize; DWORD dwNeededSize; DWORD dwUsedSize; DWORD dwStatusFlags; DWORD dwNumOwners; DWORD dwNumMonitors; DWORD dwRingMode; DWORD dwRingVolume; DWORD dwHandsetHookSwitchMode; DWORD dwHandsetVolume; DWORD dwHandsetGain; DWORD dwSpeakerHookSwitchMode; DWORD dwSpeakerVolume; DWORD dwSpeakerGain; DWORD dwHeadsetHookSwitchMode; DWORD dwHeadsetVolume; DWORD dwHeadsetGain; DWORD dwDisplaySize; DWORD dwDisplayOffset; DWORD dwLampModesSize; DWORD dwLampModesOffset; DWORD dwOwnerNameSize; DWORD dwOwnerNameOffset; DWORD dwDevSpecificSize; DWORD dwDevSpecificOffset; DWORD dwPhoneFeatures; } PHONESTATUS, *PPHONESTATUS, *LPPHONESTATUS;

WCE_IMPORT LONG WINAPI lineAddProvider(LPCWSTR lpszProviderFilename, HWND hwndOwner, LPDWORD lpdwPermanentProviderID) WCE_LINK(lineAddProvider);
WCE_IMPORT LONG WINAPI lineConfigDialogEdit(DWORD dwDeviceID, HWND hwndOwner, LPCWSTR lpszDeviceClass, LPVOID const lpDeviceConfigIn, DWORD dwSize, LPVARSTRING lpDeviceConfigOut) WCE_LINK(lineConfigDialogEdit);
WCE_IMPORT LONG WINAPI lineGetAppPriority(LPCWSTR lpszAppFilename, DWORD dwMediaMode, LPLINEEXTENSIONID lpExtensionID, DWORD dwRequestMode, LPVARSTRING lpExtensionName, LPDWORD lpdwPriority) WCE_LINK(lineGetAppPriority);
WCE_IMPORT LONG WINAPI lineGetDevConfig(DWORD dwDeviceID, LPVARSTRING lpDeviceConfig, LPCWSTR lpszDeviceClass) WCE_LINK(lineGetDevConfig);
WCE_IMPORT LONG WINAPI lineGetIcon(DWORD dwDeviceID, LPCWSTR lpszDeviceClass, LPHICON lphIcon) WCE_LINK(lineGetIcon);
WCE_IMPORT LONG WINAPI lineGetProviderList(DWORD dwAPIVersion, LPLINEPROVIDERLIST lpProviderList) WCE_LINK(lineGetProviderList);
WCE_IMPORT LONG WINAPI lineSetAppPriority(LPCWSTR lpszAppFilename, DWORD dwMediaMode, LPLINEEXTENSIONID lpExtensionID, DWORD dwRequestMode, LPCWSTR lpszExtensionName, DWORD dwPriority) WCE_LINK(lineSetAppPriority);
WCE_IMPORT LONG WINAPI lineSetDevConfig(DWORD dwDeviceID, LPVOID const lpDeviceConfig, DWORD dwSize, LPCWSTR lpszDeviceClass) WCE_LINK(lineSetDevConfig);
WCE_IMPORT LONG WINAPI phoneConfigDialog(DWORD dwDeviceID, HWND hwndOwner, LPCWSTR lpszDeviceClass) WCE_LINK(phoneConfigDialog);
WCE_IMPORT LONG WINAPI phoneGetIcon(DWORD dwDeviceID, LPCWSTR lpszDeviceClass, LPHICON lphIcon) WCE_LINK(phoneGetIcon);
WCE_IMPORT LONG WINAPI phoneInitializeEx(LPHPHONEAPP lphPhoneApp, HINSTANCE hInstance, PHONECALLBACK lpfnCallback, LPCWSTR lpszFriendlyAppName, LPDWORD lpdwNumDevs, LPDWORD lpdwAPIVersion, LPPHONEINITIALIZEEXPARAMS lpPhoneInitializeExParams) WCE_LINK(phoneInitializeEx);

#ifdef __cplusplus
}
#endif
#endif

