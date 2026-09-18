/* Tapicomn.h -- Telephony Service Provider Interface (TSPI) functions
 * for Windows CE.
 *
 * Evidence model (clean room; same as winsock2.h / tapi.h):
 *
 *  (a) every prototype is transcribed from the official CE 5.0 "TSPI
 *      Reference" function pages: 52 TSPI_line* pages (aa451008..
 *      aa451095), 21 TSPI_phone* pages (aa451096..aa451126) and 8
 *      TSPI_provider* pages (aa451127..aa451134).  Every function
 *      page's Requirements rows state: Header: Tapicomn.h, Link
 *      Library: Coredll.lib, OS: Windows CE 3.0 and later (the
 *      per-page records are docs/inventory.md, M43 section).
 *
 *  (b) the CE 5.0 archive strips whitespace inside the code blocks;
 *      the type/name boundaries in the parameter lists are restored
 *      against the documented types of tapi.h (no CE page needs the
 *      documented CE 6.0 twin procedure).
 *
 *  (c) recorded-not-defined: TSPI_lineSetCurrentLocation ("This
 *      function is obsolete" -- no prototype printed) and
 *      TSPI_lineConditionalMediaDetection (the archive prototype is
 *      corrupted beyond unambiguous restoration:
 *      "(HDRVLINEhdLine,hdConsultCalldwMediaModes,hdConsultCallconst
 *      lpCallParams)").  TSPI_lineForward was held in M43 for the
 *      unpublished LINEFORWARD element layout; it is declared in M45
 *      through the opaque LPLINEFORWARDLIST pointer (tapi.h note
 *      (e)).  docs/inventory.md (M43/M45) records each.
 */

#ifndef _TAPICOMN_H
#define _TAPICOMN_H

#include "Tapi.h"   /* TAPI types, structures, TSPIAPI, callback types */

/* ------------------------------------------------------------------ */
/* TSPI line device functions                         */
/* ------------------------------------------------------------------ */

/* aa451008: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineAccept(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineAccept);

/* aa451010: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineAddToConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdConfCall,
    HDRVCALL hdConsultCall)
    AKARI_CE_NAME(TSPI_lineAddToConference);

/* aa451012: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineAnswer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineAnswer);

/* aa451014: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineBlindTransfer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode)
    AKARI_CE_NAME(TSPI_lineBlindTransfer);

/* aa451016: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineClose(
    HDRVLINE hdLine)
    AKARI_CE_NAME(TSPI_lineClose);

/* aa451018: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineCloseCall(
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineCloseCall);

/* aa451020: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineCompleteTransfer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    HDRVCALL hdConsultCall,
    HTAPICALL htConfCall,
    LPHDRVCALL lphdConfCall,
    DWORD dwTransferMode)
    AKARI_CE_NAME(TSPI_lineCompleteTransfer);

/* aa451024: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineConfigDialogEdit(
    DWORD dwDeviceID,
    HWND hwndOwner,
    LPCWSTR lpszDeviceClass,
    LPVOID const lpDeviceConfigIn,
    DWORD dwSize,
    LPVARSTRING lpDeviceConfigOut)
    AKARI_CE_NAME(TSPI_lineConfigDialogEdit);

/* aa451025: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineDevSpecific(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HDRVCALL hdCall,
    LPVOID lpParams,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineDevSpecific);

/* aa451028: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineDial(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode)
    AKARI_CE_NAME(TSPI_lineDial);

/* aa451030: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineDrop(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineDrop);

/* M45: the M43 hold is resolved -- the LPLINEFORWARDLIST parameter
 * is declared as an opaque pointer (tapi.h note (e)), which is all
 * the prototype needs.  Prototype restored from the glued archive
 * print of page aa451032 against the documented tapi.h types. */
AKARI_CE_IMPORT LONG TSPI_lineForward(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD bAllAddresses,
    DWORD dwAddressID,
    LPLINEFORWARDLIST const lpForwardList,
    DWORD dwNumRingsNoAnswer,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineForward);

AKARI_CE_IMPORT LONG TSPI_lineGenerateDigits(
    HDRVCALL hdCall,
    DWORD dwEndToEndID,
    DWORD dwDigitMode,
    LPCWSTR lpszDigits,
    DWORD dwDuration)
    AKARI_CE_NAME(TSPI_lineGenerateDigits);

AKARI_CE_IMPORT LONG TSPI_lineGenerateTone(
    HDRVCALL hdCall,
    DWORD dwEndToEndID,
    DWORD dwToneMode,
    DWORD dwDuration,
    DWORD dwNumTones,
    LPLINEGENERATETONE const lpTones)
    AKARI_CE_NAME(TSPI_lineGenerateTone);

/* aa451038: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetAddressCaps(
    DWORD dwDeviceID,
    DWORD dwAddressID,
    DWORD dwTSPIVersion,
    DWORD dwExtVersion,
    LPLINEADDRESSCAPS lpAddressCaps)
    AKARI_CE_NAME(TSPI_lineGetAddressCaps);

/* aa451040: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetAddressID(
    HDRVLINE hdLine,
    LPDWORD lpdwAddressID,
    DWORD dwAddressMode,
    LPCWSTR lpsAddress,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineGetAddressID);

/* aa451042: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetAddressStatus(
    HDRVLINE hdLine,
    DWORD dwAddressID,
    LPLINEADDRESSSTATUS lpAddressStatus)
    AKARI_CE_NAME(TSPI_lineGetAddressStatus);

/* aa451044: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetCallAddressID(
    HDRVCALL hdCall,
    LPDWORD lpdwAddressID)
    AKARI_CE_NAME(TSPI_lineGetCallAddressID);

/* aa451046: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetCallInfo(
    HDRVCALL hdCall,
    LPLINECALLINFO lpCallInfo)
    AKARI_CE_NAME(TSPI_lineGetCallInfo);

/* aa451048: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetCallStatus(
    HDRVCALL hdCall,
    LPLINECALLSTATUS lpCallStatus)
    AKARI_CE_NAME(TSPI_lineGetCallStatus);

/* aa451050: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetDevCaps(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwExtVersion,
    LPLINEDEVCAPS lpLineDevCaps)
    AKARI_CE_NAME(TSPI_lineGetDevCaps);

/* aa451052: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetDevConfig(
    DWORD dwDeviceID,
    LPVARSTRING lpDeviceConfig,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(TSPI_lineGetDevConfig);

/* aa451054: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetExtensionID(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    LPLINEEXTENSIONID lpExtensionID)
    AKARI_CE_NAME(TSPI_lineGetExtensionID);

/* aa451056: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetIcon(
    DWORD dwDeviceID,
    LPCWSTR lpszDeviceClass,
    LPHICON lphIcon)
    AKARI_CE_NAME(TSPI_lineGetIcon);

/* aa451057: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetID(
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HDRVCALL hdCall,
    DWORD dwSelect,
    LPVARSTRING lpDeviceID,
    LPCWSTR lpszDeviceClass,
    HANDLE hTargetProcess)
    AKARI_CE_NAME(TSPI_lineGetID);

/* aa451059: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetLineDevStatus(
    HDRVLINE hdLine,
    LPLINEDEVSTATUS lpLineDevStatus)
    AKARI_CE_NAME(TSPI_lineGetLineDevStatus);

/* aa451061: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineGetNumAddressIDs(
    HDRVLINE hdLine,
    LPDWORD lpdwNumAddressIDs)
    AKARI_CE_NAME(TSPI_lineGetNumAddressIDs);

/* aa451063: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineHold(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineHold);

/* aa451066: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineMakeCall(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    HTAPICALL htCall,
    LPHDRVCALL lphdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineMakeCall);

/* aa451068: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineMonitorDigits(
    HDRVCALL hdCall,
    DWORD dwDigitModes)
    AKARI_CE_NAME(TSPI_lineMonitorDigits);

/* aa451069: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineMonitorMedia(
    HDRVCALL hdCall,
    DWORD dwMediaModes)
    AKARI_CE_NAME(TSPI_lineMonitorMedia);

/* aa451071: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineNegotiateExtVersion(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwExtVersion)
    AKARI_CE_NAME(TSPI_lineNegotiateExtVersion);

/* aa451072: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineNegotiateTSPIVersion(
    DWORD dwDeviceID,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwTSPIVersion)
    AKARI_CE_NAME(TSPI_lineNegotiateTSPIVersion);

/* aa451073: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineOpen(
    DWORD dwDeviceID,
    HTAPILINE htLine,
    LPHDRVLINE lphdLine,
    DWORD dwTSPIVersion,
    LINEEVENT lpfnEventProc)
    AKARI_CE_NAME(TSPI_lineOpen);

/* aa451074: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_linePickup(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HTAPICALL htCall,
    LPHDRVCALL lphdCall,
    LPCWSTR lpszDestAddress,
    LPCWSTR lpszGroupID)
    AKARI_CE_NAME(TSPI_linePickup);

/* aa451075: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_linePrepareAddToConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdConfCall,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_linePrepareAddToConference);

/* aa451076: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineRedirect(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode)
    AKARI_CE_NAME(TSPI_lineRedirect);

/* aa451077: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineReleaseUserUserInfo(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineReleaseUserUserInfo);

/* aa451078: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineRemoveFromConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineRemoveFromConference);

/* aa451080: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSendUserUserInfo(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineSendUserUserInfo);

/* aa451082: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetCallParams(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    DWORD dwBearerMode,
    DWORD dwMinRate,
    DWORD dwMaxRate,
    LPLINEDIALPARAMS const lpDialParams)
    AKARI_CE_NAME(TSPI_lineSetCallParams);

/* aa451086: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetDefaultMediaDetection(
    HDRVLINE hdLine,
    DWORD dwMediaModes)
    AKARI_CE_NAME(TSPI_lineSetDefaultMediaDetection);

/* ms928303: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetDevConfig(
    DWORD dwDeviceID,
    LPVOID const lpDeviceConfig,
    DWORD dwSize,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(TSPI_lineSetDevConfig);

/* aa451089: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetMediaMode(
    HDRVCALL hdCall,
    DWORD dwMediaMode)
    AKARI_CE_NAME(TSPI_lineSetMediaMode);

/* aa451090: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetStatusMessages(
    HDRVLINE hdLine,
    DWORD dwLineStates,
    DWORD dwAddressStates)
    AKARI_CE_NAME(TSPI_lineSetStatusMessages);

/* aa451091: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetTerminal(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HDRVCALL hdCall,
    DWORD dwSelect,
    DWORD dwTerminalModes,
    DWORD dwTerminalID,
    DWORD bEnable)
    AKARI_CE_NAME(TSPI_lineSetTerminal);

/* aa451092: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetupConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    HDRVLINE hdLine,
    HTAPICALL htConfCall,
    LPHDRVCALL lphdConfCall,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    DWORD dwNumParties,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineSetupConference);

/* aa451093: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSetupTransfer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineSetupTransfer);

/* aa451094: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineSwapHold(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdActiveCall,
    HDRVCALL hdHeldCall)
    AKARI_CE_NAME(TSPI_lineSwapHold);

/* aa451095: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_lineUnhold(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineUnhold);

/* ------------------------------------------------------------------ */
/* TSPI phone device functions                        */
/* ------------------------------------------------------------------ */

/* aa451096: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT long TSPI_phoneClose(
    HDRVPHONE hdPhone)
    AKARI_CE_NAME(TSPI_phoneClose);

/* aa451097: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneConfigDialog(
    DWORD dwDeviceID,
    HWND hwndOwner,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(TSPI_phoneConfigDialog);

/* aa451098: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneDevSpecific(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    LPVOID lpParams,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_phoneDevSpecific);

/* aa451099: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetDevCaps(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwExtVersion,
    LPPHONECAPS lpPhoneCaps)
    AKARI_CE_NAME(TSPI_phoneGetDevCaps);

/* aa451100: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetExtensionID(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    LPPHONEEXTENSIONID lpExtensionID)
    AKARI_CE_NAME(TSPI_phoneGetExtensionID);

/* aa451101: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetGain(
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    LPDWORD lpdwGain)
    AKARI_CE_NAME(TSPI_phoneGetGain);

/* aa451102: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetHookSwitch(
    HDRVPHONE hdPhone,
    LPDWORD lpdwHookSwitchDevs)
    AKARI_CE_NAME(TSPI_phoneGetHookSwitch);

/* aa451103: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetIcon(
    DWORD dwDeviceID,
    LPCWSTR lpszDeviceClass,
    LPHICON lphIcon)
    AKARI_CE_NAME(TSPI_phoneGetIcon);

/* aa451104: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetID(
    HDRVPHONE hdPhone,
    LPVARSTRING lpDeviceID,
    LPCWSTR lpszDeviceClass,
    HANDLE hTargetProcess)
    AKARI_CE_NAME(TSPI_phoneGetID);

/* aa451105: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetRing(
    HDRVPHONE hdPhone,
    LPDWORD lpdwRingMode,
    LPDWORD lpdwVolume)
    AKARI_CE_NAME(TSPI_phoneGetRing);

/* aa451106: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetStatus(
    HDRVPHONE hdPhone,
    LPPHONESTATUS lpPhoneStatus)
    AKARI_CE_NAME(TSPI_phoneGetStatus);

/* aa451107: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneGetVolume(
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    LPDWORD lpdwVolume)
    AKARI_CE_NAME(TSPI_phoneGetVolume);

/* aa451108: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneNegotiateExtVersion(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwExtVersion)
    AKARI_CE_NAME(TSPI_phoneNegotiateExtVersion);

/* aa451109: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneNegotiateTSPIVersion(
    DWORD dwDeviceID,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwTSPIVersion)
    AKARI_CE_NAME(TSPI_phoneNegotiateTSPIVersion);

/* aa451120: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneOpen(
    DWORD dwDeviceID,
    HTAPIPHONE htPhone,
    LPHDRVPHONE lphdPhone,
    DWORD dwTSPIVersion,
    PHONEEVENT lpfnEventProc)
    AKARI_CE_NAME(TSPI_phoneOpen);

/* aa451121: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneSelectExtVersion(
    HDRVPHONE hdPhone,
    DWORD dwExtVersion)
    AKARI_CE_NAME(TSPI_phoneSelectExtVersion);

/* aa451122: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneSetGain(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    DWORD dwGain)
    AKARI_CE_NAME(TSPI_phoneSetGain);

/* aa451123: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneSetHookSwitch(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDevs,
    DWORD dwHookSwitchMode)
    AKARI_CE_NAME(TSPI_phoneSetHookSwitch);

/* aa451124: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneSetRing(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwRingMode,
    DWORD dwVolume)
    AKARI_CE_NAME(TSPI_phoneSetRing);

/* aa451125: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneSetStatusMessages(
    HDRVPHONE hdPhone,
    DWORD dwPhoneStates,
    DWORD dwButtonModes,
    DWORD dwButtonStates)
    AKARI_CE_NAME(TSPI_phoneSetStatusMessages);

/* aa451126: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_phoneSetVolume(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    DWORD dwVolume)
    AKARI_CE_NAME(TSPI_phoneSetVolume);

/* ------------------------------------------------------------------ */
/* TSPI service provider functions                    */
/* ------------------------------------------------------------------ */

/* aa451127: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerCreateLineDevice(
    HKEY hActive,
    LPCWSTR szDevKey,
    LPCWSTR szDevName)
    AKARI_CE_NAME(TSPI_providerCreateLineDevice);

/* aa451128: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerCreatePhoneDevice(
    HKEY hActive,
    LPCWSTR szDevKey,
    LPCWSTR szDevName)
    AKARI_CE_NAME(TSPI_providerCreatePhoneDevice);

/* aa451129: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerEnumDevices(
    DWORD dwPermanentProviderID,
    LPDWORD lpdwNumLines,
    LPDWORD lpdwNumPhones,
    HPROVIDER hProvider,
    LINEEVENT lpfnLineCreateProc,
    PHONEEVENT lpfnPhoneCreateProc)
    AKARI_CE_NAME(TSPI_providerEnumDevices);

/* aa451130: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerInit(
    DWORD dwTSPIVersion,
    DWORD dwPermanentProviderID,
    DWORD dwLineDeviceIDBase,
    DWORD dwPhoneDeviceIDBase,
    DWORD_PTR dwNumLines,
    DWORD_PTR dwNumPhones,
    ASYNC_COMPLETION lpfnCompletionProc,
    LPDWORD lpdwTSPIOptions)
    AKARI_CE_NAME(TSPI_providerInit);

/* aa451131: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerInstall(
    HWND hwndOwner,
    DWORD dwPermanentProviderID)
    AKARI_CE_NAME(TSPI_providerInstall);

/* aa451132: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerRemove(
    HWND hwndOwner,
    DWORD dwPermanentProviderID)
    AKARI_CE_NAME(TSPI_providerRemove);

/* aa451133: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerRemoveDevice(
    LPCWSTR lpszDeviceName)
    AKARI_CE_NAME(TSPI_providerRemoveDevice);

/* aa451134: param-list verified against this page; the print shows the TSPIAPI decoration (TSPIAPI is WINAPI, empty in this tree) (proto-cite) */
AKARI_CE_IMPORT LONG TSPI_providerShutdown(
    DWORD dwTSPIVersion,
    DWORD dwPermanentProviderID)
    AKARI_CE_NAME(TSPI_providerShutdown);

/* ------------------------------------------------------------------
 * Book surface: tspi-all (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451084 TSPI_lineSetCurrentLocation */
/* ------------------------------------------------------------------
 * Book surface: tspi-all (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451084 TSPI_lineSetCurrentLocation */
#endif  /* _TAPICOMN_H */
