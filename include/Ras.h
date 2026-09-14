/* Ras.h -- RAS server administration structures (Servers book,
 * RAS Server/PPTP node; used with the RasIOControl record in
 * Service.h).  See docs/inventory.md M75f. */

#ifndef AKARI_RAS_H
#define AKARI_RAS_H

#include "Windef.h"    /* BOOL, DWORD, BYTE */

/* ms896355 "RASCNTL_SERVERSTATUS": print
 * `typedef struct tagRasCntlServerStatus {BOOLbEnable;
 * DWORDbmFlags;BOOLbUseDhcpAddresses;DWORDdwStaticIpAddrStart;
 * DWORDdwStaticIpAddrCount;DWORD bmAuthenticationMethods;
 * DWORDdwNumLines;} RASCNTL_SERVERSTATUS, *PRASCNTL_SERVERSTATUS;` */
typedef struct tagRasCntlServerStatus {
    BOOL  bEnable;
    DWORD bmFlags;
    BOOL  bUseDhcpAddresses;
    DWORD dwStaticIpAddrStart;
    DWORD dwStaticIpAddrCount;
    DWORD bmAuthenticationMethods;
    DWORD dwNumLines;
} RASCNTL_SERVERSTATUS, *PRASCNTL_SERVERSTATUS;

/* ms896358 "RASCNTL_SERVER_IPV6_NET_PREFIX": print
 * `typedef struct tagRasCntlServerIPV6NetPrefix {
 * BYTE IPV6NetPrefix[16]; DWORD IPV6NetPrefixBitLength;
 * DWORD IPV6NetPrefixCount;} RASCNTL_SERVER_IPV6_NET_PREFIX,
 * *PRASCNTL_SERVER_IPV6_NET_PREFIX;` */
typedef struct tagRasCntlServerIPV6NetPrefix {
    BYTE  IPV6NetPrefix[16];
    DWORD IPV6NetPrefixBitLength;
    DWORD IPV6NetPrefixCount;
} RASCNTL_SERVER_IPV6_NET_PREFIX, *PRASCNTL_SERVER_IPV6_NET_PREFIX;

/* --- Record-only (members depend on unpublished types). ----------
 * ms896353 "RasCntlEnum": print (truncated on the page, values
 * absent, several commas missing -- verbatim):
 *   typedef enum tagRasCntlEnum { RASCNTL_SERVER_GET_STATUS,
 *   RASCNTL_SERVER_ENABLE, RASCNTL_SERVER_DISABLE,
 *   RASCNTL_SERVER_GET_PARAMETERS, RASCNTL_SERVER_SET_PARAMETERS,
 *   RASCNTL_SERVER_LINE_ADD, RASCNTL_SERVER_LINE_REMOVE,
 *   RASCNTL_SERVER_LINE_ENABLE, RASCNTL_SERVER_LINE_DISABLE,
 *   RASCNTL_SERVER_LINE_GET_PARAMETERS,
 *   RASCNTL_SERVER_LINE_SET_PARAMETERS,
 *   RASCNTL_SERVER_USER_SET_CREDENTIALS,
 *   RASCNTL_SERVER_USER_DELETE_CREDENTIALS,
 *   RASCNTL_SERVER_GET_IPV6_NET_PREFIX RASCNTL_SERVER_SET_IPV6_NET_PREFIX
 *   RASCNTL_SERVER_LINE_GET_CO... (page ends mid-identifier)
 * ms896354 "RASCNTL_SERVERLINE": `typedef struct tagRasCntlServerLine
 * {RASDEVINFOrasDevInfo;BOOLbEnable;DWORDbmFlags;
 * UINTDisconnectIdleSeconds;DWORDdwDevConfigSize;BYTEDevConfig[1];}
 * RASCNTL_SERVERLINE, *PRASCNTL_SERVERLINE;` (RASDEVINFO unpublished)
 * CROSS-GENERATION (M86 sweep): the CE 4.0 twin ms924959 prints the
 * same members but drops the semicolon after `BYTE DevConfig[1]`
 * (archive print artifact; members identical).
 * ms896356 "RASCNTL_SERVERUSERCREDENTIALS": `typedef struct
 * tagRasCntlServerUser{TCHAR tszUserName[UNLEN + 1];
 * TCHARtszDomainName[DNLEN + 1];BYTEpassword[PWLEN];DWORDcbPassword;}
 * RASCNTL_SERVERUSERCREDENTIALS, *PRASCNTL_SERVERUSERCREDENTIALS;`
 * (UNLEN/DNLEN/PWLEN unpublished)
 * ms896357 "RASCNTL_SERVERCONNECTION": `typedef struct
 * tagRasCntlServerConnection { RASDEVINFO rasDevInfo;
 * HRASCONN hrasconn; DWORD dwServerIpAddress;
 * DWORD dwClientIpAddress; RASCONNSTATE RasConnState;
 * TCHAR tszUserName[DNLEN + 1 + UNLEN + 1];} RASCNTL_SERVERCONNECTION,
 * *PRASCNTL_SERVERCONNECTION;` (RASDEVINFO/HRASCONN/RASCONNSTATE/
 * UNLEN/DNLEN unpublished). */

/* ================================================================== */
/* RAS client API (dial-up networking).                              */
/* Official Windows CE 3.0 archive pages (wcesdkr*, "Versions: N and  */
/* later", Defined in Ras.h -- the dual-header rows also list         */
/* Afdfunc.h) cross-checked against the CE 5.0 archive twins          */
/* (ms896359/ms896360/ms896361/aa450835/aa450836/aa450837/aa450853/   */
/* aa450854/aa450865), which print identical declarations.  Every     */
/* client function page lists Link to: Ppp.lib (a static support      */
/* library, not a DLL), so no doc-def entry is claimed for them.      */
/* ================================================================== */

/* wcesdkrRASIPADDR_str "RASIPADDR" (+ CE 5.0 twin aa450853):
 * struct printed verbatim.  CE 1.0+; Ras.h.  IP address carrier for
 * the RAS phone-book entry structures.  CE remark: on Windows CE the
 * byte order of the a, b, c, d members is transposed (d, c, b, a);
 * use htonl to reverse the byte order. */
typedef struct RASIPADDR {
    BYTE a;
    BYTE b;
    BYTE c;
    BYTE d;
} RASIPADDR;

/* wcesdkrRASPROJECTION "RASPROJECTION": enum printed with values.
 * CE 1.0+; Ras.h.  Passed to RasGetProjectionInfo to select the
 * protocol of interest.  The archive print drops the commas after
 * RASP_PppIp and RASP_PppCcp (printing artifact; commas restored).
 * Windows CE supports the RASP_PppIp value. */
typedef enum _RASPROJECTION {
    RASP_Amb    = 0x10000,
    RASP_PppNbf = 0x803F,
    RASP_PppIpx = 0x802B,
    RASP_PppIp  = 0x8021,
    RASP_PppCcp = 0x80FD,
    RASP_PppLcp = 0xC021,
    RASP_Slip   = 0x20000
} RASPROJECTION;

/* aa450865 "RAS_STATS (Windows CE 5.0)": struct printed verbatim.
 * CE .NET 4.0+ (OS Versions row of the page); Ras.h.  Accumulated
 * statistics for a single-link or multilink RAS connection, filled
 * by RasGetLinkStatistics (dwConnectDuration in milliseconds). */
typedef struct _RAS_STATS {
    DWORD dwSize;
    DWORD dwBytesXmited;
    DWORD dwBytesRcved;
    DWORD dwFramesXmited;
    DWORD dwFramesRcved;
    DWORD dwCrcErr;
    DWORD dwTimeoutErr;
    DWORD dwAlignmentErr;
    DWORD dwHardwareOverrunErr;
    DWORD dwFramingErr;
    DWORD dwBufferOverrunErr;
    DWORD dwCompressionRatioIn;
    DWORD dwCompressionRatioOut;
    DWORD dwBps;
    DWORD dwConnectDuration;
} RAS_STATS, *PRAS_STATS;

/* wcesdkrRasDeleteEntry "RasDeleteEntry":
 * DWORD RasDeleteEntry(LPWSTR, LPWSTR).  CE 3.0+; Ras.h, Afdfunc.h;
 * Ppp.lib.  Deletes a phone-book entry (lpszPhonebook is ignored on
 * CE -- entries live in the registry). */
DWORD RasDeleteEntry(LPWSTR lpszPhonebook, LPWSTR lpszEntry);

/* wcesdkrRasRenameEntry "RasRenameEntry":
 * DWORD RasRenameEntry(LPWSTR, LPWSTR, LPWSTR).  CE 1.0+; Ras.h,
 * Afdfunc.h; Ppp.lib.  Renames a phone-book entry; call
 * RasValidateEntryName on the new name first. */
DWORD RasRenameEntry(LPWSTR lpszPhonebook, LPWSTR lpszOldEntry,
                     LPWSTR lpszNewEntry);

/* wcesdkrRasValidateEntryName "RasValidateEntryName":
 * DWORD RasValidateEntryName(LPWSTR, LPWSTR).  CE 1.0+; Ras.h,
 * Afdfunc.h; Ppp.lib.  Validates an entry name (at least one
 * alphanumeric character; no | > < ? * \ / : characters). */
DWORD RasValidateEntryName(LPWSTR lpszPhonebook, LPWSTR lpszEntry);

/* --- RAS client declarations HELD (zero-gap policy). ---------------
 *
 * The pages below print their declarations verbatim, but each
 * declaration depends on identifiers that no official CE page
 * (CE 1.0/2.x/3.0 archive, CE 5.0 and CE 6.0 trees) publishes a
 * value or definition for.  Nothing is invented; the prints are
 * recorded so the surface is traceable and the declarations can be
 * completed the day the missing facts are officially published.
 *
 * Handle type (no CE page prints the typedef):
 *   HRASCONN / LPHRASCONN -- "Handle to the remote access
 *   connection" (wcesdkrRASCONN_str member remarks, wcesdkrRasDial
 *   pRasConn parameter).
 *
 * Array-size constants (names printed in the struct prints below;
 * no CE page prints a value):
 *   RAS_MaxEntryName RAS_MaxPhoneNumber RAS_MaxCallbackNumber
 *   RAS_MaxDeviceType RAS_MaxDeviceName RAS_MaxAreaCode
 *   RAS_MaxPadType RAS_MaxX25Address RAS_MaxFacilities
 *   RAS_MaxUserData RAS_MaxIpAddress
 *
 * Account-length constants (names printed in RASDIALPARAMS; no CE
 * page prints a value):  UNLEN PWLEN DNLEN
 *
 * State-class bitmasks (names printed in the RASCONNSTATE remarks:
 * fDoneState = (state & RASCS_DONE), fPausedState = (state &
 * RASCS_PAUSED); no CE page prints values):
 *   RASCS_PAUSED RASCS_DONE
 *
 * wcesdkrRASCONN_str "RASCONN" (+ CE 5.0 twin ms896359).  CE 1.0+;
 * Ras.h.  Held: RAS_MaxEntryName, HRASCONN.
 *   typedef struct _RASCONN {
 *       DWORD dwSize;
 *       HRASCONN hrasconn;
 *       TCHAR szEntryName[RAS_MaxEntryName + 1];
 *   } RASCONN;
 *
 * wcesdkrRASDIALPARAMS_str "RASDIALPARAMS" (+ aa450835).  CE 1.0+;
 * Ras.h.  Held: the RAS_Max size constants and UNLEN/PWLEN/DNLEN.
 *   typedef struct _RASDIALPARAMS {
 *       DWORD dwSize;
 *       TCHAR szEntryName[RAS_MaxEntryName + 1];
 *       TCHAR szPhoneNumber[RAS_MaxPhoneNumber + 1];
 *       TCHAR szCallbackNumber[RAS_MaxCallbackNumber + 1];
 *       TCHAR szUserName[UNLEN + 1];
 *       TCHAR szPassword[PWLEN + 1];
 *       TCHAR szDomain[DNLEN + 1];
 *   } RASDIALPARAMS;
 *   (CE 3.0+ remark: RasGetEntryDialParams returns a saved-password
 *   handle in szPassword instead of the plain-text password.)
 *
 * wcesdkrRASENTRYNAME_str "RASENTRYNAME" (+ aa450837).  CE 1.0+;
 * Ras.h.  Held: RAS_MaxEntryName.
 *   typedef struct _RASENTRYNAME {
 *       DWORD dwSize;
 *       TCHAR szEntryName[RAS_MaxEntryName + 1];
 *   } RASENTRYNAME;
 *
 * wcesdkrRASENTRY_str "RASENTRY" (+ aa450836).  CE 1.0+; Ras.h.
 * Held: RAS_Max* family.  The CE 5.0 twin appends the
 * dwCustomAuthKey member (CE 3.0 print ends at dwReserved2):
 *   typedef struct _RASENTRY {
 *       DWORD dwSize;
 *       DWORD dwfOptions;
 *       DWORD dwCountryID;
 *       DWORD dwCountryCode;
 *       TCHAR szAreaCode[RAS_MaxAreaCode + 1];
 *       TCHAR szLocalPhoneNumber[RAS_MaxPhoneNumber + 1];
 *       DWORD dwAlternatesOffset;
 *       RASIPADDR ipaddr;
 *       RASIPADDR ipaddrDns;
 *       RASIPADDR ipaddrDnsAlt;
 *       RASIPADDR ipaddrWins;
 *       RASIPADDR ipaddrWinsAlt;
 *       DWORD dwFrameSize;
 *       DWORD dwfNetProtocols;
 *       DWORD dwFramingProtocol;
 *       TCHAR szScript[MAX_PATH];
 *       TCHAR szAutoDialDll[MAX_PATH];
 *       TCHAR szAutoDialFunc[MAX_PATH];
 *       TCHAR szDeviceType[RAS_MaxDeviceType + 1];
 *       TCHAR szDeviceName[RAS_MaxDeviceName + 1];
 *       TCHAR szX25PadType[RAS_MaxPadType + 1];
 *       TCHAR szX25Address[RAS_MaxX25Address + 1];
 *       TCHAR szX25Facilities[RAS_MaxFacilities + 1];
 *       TCHAR szX25UserData[RAS_MaxUserData + 1];
 *       DWORD dwChannels;
 *       DWORD dwReserved1;
 *       DWORD dwReserved2;
 *       DWORD dwCustomAuthKey;   (CE 5.0 print only)
 *   } RASENTRY;
 * dwfOptions flag names (names only; no CE page prints values):
 *   CE 3.0 print: RASEO_UseCountryAndAreaCodes RASEO_SpecificIpAddr
 *   RASEO_SpecificNameServers RASEO_IpHeaderCompression
 *   RASEO_RemoteDefaultGateway RASEO_DisableLcpExtensions
 *   RASEO_ModemLights RASEO_SwCompression RASEO_RequireEncryptedPw
 *   RASEO_RequireMsEncryptedPw RASEO_RequireDataEncryption
 *   RASEO_NetworkLogon; CE 5.0 adds RASEO_CustomScript
 *   RASEO_DialAsLocalCall RASEO_PreviewUserPw RASEO_ProhibitCHAP
 *   RASEO_ProhibitEAP RASEO_ProhibitMsCHAP RASEO_ProhibitMsCHAP2
 *   RASEO_ProhibitPAP RASEO_PromoteAlternates
 *   RASEO_UseLogonCredentials.  dwfNetProtocols/dwFramingProtocol
 *   value names (the RASNP_ and RASFP_ families) and RASDT_*
 *   device-type string
 *   names appear in the member prose; no values printed either.
 *
 * wcesdkrRASDEVINFO_str "RASDEVINFO" (+ CE 5.0 twin aa450833).
 * CE 1.0+; Ras.h.  Held: RAS_MaxDeviceType/RAS_MaxDeviceName.
 *   typedef struct tagRASDEVINFO {
 *       DWORD dwSize;
 *       CHAR szDeviceType[RAS_MaxDeviceType + 1];
 *       CHAR szDeviceName[RAS_MaxDeviceName + 1];
 *   } RASDEVINFO;
 *   szDeviceType string constants (names only): RASDT_Modem
 *   RASDT_Isdn RASDT_X25 RASDT_Vpn (CE 3.0+) RASDT_Pad.
 *
 * wcesdkrRASCONNSTATE_str "RASCONNSTATE" (+ ms896360).  CE 1.0+;
 * Ras.h.  Held: RASCS_PAUSED/RASCS_DONE anchors.
 *   typedef enum _RASCONNSTATE {
 *       RASCS_OpenPort = 0, RASCS_PortOpened, RASCS_ConnectDevice,
 *       RASCS_DeviceConnected, RASCS_AllDevicesConnected,
 *       RASCS_Authenticate, RASCS_AuthNotify, RASCS_AuthRetry,
 *       RASCS_AuthCallback, RASCS_AuthChangePassword,
 *       RASCS_AuthProject, RASCS_AuthLinkSpeed, RASCS_AuthAck,
 *       RASCS_ReAuthenticate, RASCS_Authenticated,
 *       RASCS_PrepareForCallback, RASCS_WaitForModemReset,
 *       RASCS_WaitForCallback, RASCS_Projected,
 *       RASCS_Interactive = RASCS_PAUSED,
 *       RASCS_RetryAuthentication, RASCS_CallbackSetByCaller,
 *       RASCS_PasswordExpired, RASCS_Connected = RASCS_DONE,
 *       RASCS_Disconnected
 *   } RASCONNSTATE;
 *
 * wcesdkrRASCONNSTATUS_str "RASCONNSTATUS" (+ ms896361).  CE 1.0+;
 * Ras.h.  Held: RAS_MaxDeviceType/RAS_MaxDeviceName, RASCONNSTATE.
 *   typedef struct _RASCONNSTATUS {
 *       DWORD dwSize;
 *       RASCONNSTATE rasconnstate;
 *       DWORD dwError;
 *       TCHAR szDeviceType[RAS_MaxDeviceType + 1];
 *       TCHAR szDeviceName[RAS_MaxDeviceName + 1];
 *   } RASCONNSTATUS;
 *
 * wcesdkrRASPPPIP "RASPPPIP" (+ aa450854).  CE 1.0+; Ras.h.
 * Held: RAS_MaxIpAddress.  CE remark: dwSize must specify the size
 * of the structure without the desktop szServerIpAddress member.
 *   typedef struct _RASPPPIP {
 *       DWORD dwSize;
 *       DWORD dwError;
 *       TCHAR szIpAddress[RAS_MaxIpAddress + 1];
 *   } RASPPPIP;
 *
 * Held function prototypes (depend on the held types above; pages:
 * wcesdkrRasDial / wcesdkrRasEnumConnections / wcesdkrRasEnumDevices
 * / wcesdkrRasEnumEntries / wcesdkrRasGetConnectStatus /
 * wcesdkrRasGetEntryDialParams / wcesdkrRasGetEntryProperties /
 * wcesdkrRasGetLinkStatistics / wcesdkrRasGetProjectionInfo /
 * wcesdkrRasHangUp / wcesdkrRasSetEntryDialParams /
 * wcesdkrRasSetEntryProperties):
 *   DWORD RasDial(LPRASDIALEXTENSIONS dialExtensions,
 *                 LPTSTR phoneBookPath, LPRASDIALPARAMS rasDialParam,
 *                 DWORD NotifierType, LPVOID notifier,
 *                 LPHRASCONN pRasConn);            (CE 1.0+)
 *   DWORD RasEnumConnections(LPRASCONN lprasconn, LPDWORD lpcb,
 *                 LPDWORD lpcConnections);         (CE 1.0+)
 *   DWORD RasEnumDevices(LPRASDEVINFOW lpRasDevinfo, LPDWORD lpcb,
 *                 LPDWORD lpcDevices);             (CE 3.0+)
 *   DWORD RasEnumEntries(LPWSTR Reserved, LPWSTR lpszPhoneBookPath,
 *                 LPRASENTRYNAME lprasentryname, LPDWORD lpcb,
 *                 LPDWORD lpcEntries);             (CE 1.0+)
 *   DWORD RasGetConnectStatus(HRASCONN rasconn,
 *                 LPRASCONNSTATUS lprasconnstatus); (CE 1.0+)
 *   DWORD RasGetEntryDialParams(LPWSTR lpszPhoneBook,
 *                 LPRASDIALPARAMS lpRasDialParams, LPBOOL lpfPassword);
 *                                                  (CE 1.0+)
 *   DWORD RasGetEntryProperties(LPWSTR lpszPhoneBook, LPWSTR szEntry,
 *                 LPRASENTRY lpbEntry, LPDWORD lpdwEntrySize,
 *                 LPBYTE lpb, LPDWORD lpdwSize);   (CE 1.0+)
 *   DWORD RasGetLinkStatistics(HRASCONN hRasConn, DWORD dwSubEntry,
 *                 RAS_STATS *lpStatistics);        (CE 3.0+)
 *   DWORD RasGetProjectionInfo(HRASCONN hrasconn,
 *                 RASPROJECTION rasprojection, LPVOID lpprojection,
 *                 LPDWORD lpcb);                   (CE 3.0+)
 *   DWORD RasHangUp(HRASCONN Session);             (CE 1.0+)
 *   DWORD RasSetEntryDialParams(LPWSTR lpszPhoneBook,
 *                 LPRASDIALPARAMS lpRasDialParams, BOOL fRemovePassword);
 *                                                  (CE 1.0+)
 *   DWORD RasSetEntryProperties(LPWSTR lpszPhoneBook, LPWSTR szEntry,
 *                 LPRASENTRY lpbEntry, DWORD dwEntrySize,
 *                 LPBYTE lpb, DWORD dwSize);       (CE 1.0+)
 * (RasDial's dialExtensions parameter references RASDIALEXTENSIONS,
 * likewise unpublished on CE; the parameter is ignored on CE.) */

#endif /* AKARI_RAS_H */
