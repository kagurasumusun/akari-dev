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

#if _WIN32_WCE >= 0x0500   /* Windows CE 5.0 and later. (ms896358) */
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
#endif /* _WIN32_WCE >= 0x0500 */

/* --- Record-only (page print truncated; values absent). -----------
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
 * The three server structures that the M75f record listed as held
 * (RASCNTL_SERVERLINE, RASCNTL_SERVERUSERCREDENTIALS,
 * RASCNTL_SERVERCONNECTION) are declared live at the foot of this
 * header now that RASDEVINFO/HRASCONN/RASCONNSTATE/UNLEN/DNLEN/
 * PWLEN are closed. */

/* ================================================================== */
/* RAS client API (dial-up networking).                              */
/* Official Windows CE 3.0 archive pages (wcesdkr*, "Versions: N and */
/* later", Defined in Ras.h -- the dual-header rows also list        */
/* Afdfunc.h) cross-checked against the CE 5.0 archive twins         */
/* (ms896359/ms896360/ms896361/aa450833/aa450835/aa450836/aa450837/  */
/* aa450853/aa450854/aa450865), which print identical declarations.  */
/* Every client function page lists Link to: Ppp.lib; the            */
/* device-dump-audited coredll export surface of the sysroot         */
/* (corpus coredll def files, clean-room.md 3.2) verifies that all Ras*  */
/* functions are exported by coredll.dll on CE 4/5/6, so they are    */
/* declared with the coredll import decoration and carried by        */
/* def/coredll-doc.def.                                              */
/*                                                                   */
/* Value adoptions (clean-room.md 4, R1 = CeGCC-lineage w32api,      */
/* public domain, CE lineage): the CE pages print the constant NAMES */
/* but no values; the numeric values below are adopted from R1 with  */
/* provenance, never copied expression.  Where a CE page prints a    */
/* value itself (RASPROJECTION), the page wins.                      */
/* ================================================================== */

/* --- Adopted size/length constants (R1 lineage values). -----------
 * CE pages printing the names: wcesdkrRASCONN_str, wcesdkrRASDIALPAR
 * AMS_str, wcesdkrRASENTRY_str, wcesdkrRASENTRYNAME_str,
 * wcesdkrRASDEVINFO_str, wcesdkrRASCONNSTATUS_str, wcesdkrRASPPPIP
 * (+ CE 5.0 twins).  No CE page prints a value; adopted from the R1
 * CE lineage (include/ras.h, include/lmcons.h). */
#define RAS_MaxEntryName       256
#define RAS_MaxPhoneNumber     128
#define RAS_MaxCallbackNumber  RAS_MaxPhoneNumber
#define RAS_MaxDeviceType      16
#define RAS_MaxDeviceName      128
#define RAS_MaxAreaCode        10
#define RAS_MaxPadType         32
#define RAS_MaxX25Address      200
#define RAS_MaxFacilities      200
#define RAS_MaxUserData        200
#define RAS_MaxIpAddress       15

/* Account-length constants used by RASDIALPARAMS (CE page prints the
 * names in the struct print); values adopted from the R1 lineage
 * lmcons values. */
#define UNLEN  256
#define PWLEN  256
#define DNLEN  15

/* --- Connection handle (opaque). ----------------------------------
 * No CE page prints the typedef; the R1 CE-lineage ABI fact is a
 * DECLARE_HANDLE-class opaque pointer (R1 include/ras.h).  The tree
 * declares HANDLE-class opaque pointers as void* (windef.h HWND
 * convention). */
typedef void *HRASCONN;
typedef HRASCONN *LPHRASCONN;

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

/* wcesdkrRASCONN_str "RASCONN" (+ CE 5.0 twin ms896359): struct
 * printed verbatim.  CE 1.0+; Ras.h.  Returned as an array by
 * RasEnumConnections. */
typedef struct _RASCONN {
    DWORD    dwSize;
    HRASCONN hrasconn;
    TCHAR    szEntryName[RAS_MaxEntryName + 1];
} RASCONN, *LPRASCONN;

/* wcesdkrRASCONNSTATE_str "RASCONNSTATE" (+ CE 5.0 twin ms896360):
 * enum printed verbatim (the anchors RASCS_PAUSED/RASCS_DONE are
 * documented as bitmasks classifying paused/done states; their
 * values 0x1000/0x2000 are adopted from the R1 CE lineage).
 * CE 1.0+; Ras.h. */
#define RASCS_PAUSED 0x1000
#define RASCS_DONE   0x2000
typedef enum _RASCONNSTATE {
    RASCS_OpenPort = 0,
    RASCS_PortOpened,
    RASCS_ConnectDevice,
    RASCS_DeviceConnected,
    RASCS_AllDevicesConnected,
    RASCS_Authenticate,
    RASCS_AuthNotify,
    RASCS_AuthRetry,
    RASCS_AuthCallback,
    RASCS_AuthChangePassword,
    RASCS_AuthProject,
    RASCS_AuthLinkSpeed,
    RASCS_AuthAck,
    RASCS_ReAuthenticate,
    RASCS_Authenticated,
    RASCS_PrepareForCallback,
    RASCS_WaitForModemReset,
    RASCS_WaitForCallback,
    RASCS_Projected,
    RASCS_Interactive = RASCS_PAUSED,
    RASCS_RetryAuthentication,
    RASCS_CallbackSetByCaller,
    RASCS_PasswordExpired,
    RASCS_Connected = RASCS_DONE,
    RASCS_Disconnected
} RASCONNSTATE;

/* wcesdkrRASCONNSTATUS_str "RASCONNSTATUS" (+ CE 5.0 twin
 * ms896361): struct printed verbatim.  CE 1.0+; Ras.h.  Filled by
 * RasGetConnectStatus. */
typedef struct _RASCONNSTATUS {
    DWORD        dwSize;
    RASCONNSTATE rasconnstate;
    DWORD        dwError;
    TCHAR        szDeviceType[RAS_MaxDeviceType + 1];
    TCHAR        szDeviceName[RAS_MaxDeviceName + 1];
} RASCONNSTATUS, *LPRASCONNSTATUS;

/* wcesdkrRASDIALPARAMS_str "RASDIALPARAMS" (+ CE 5.0 twin
 * aa450835): struct printed verbatim.  CE 1.0+; Ras.h.  CE 3.0+
 * remark: RasGetEntryDialParams returns a saved-password handle in
 * szPassword instead of the plain-text password. */
typedef struct _RASDIALPARAMS {
    DWORD dwSize;
    TCHAR szEntryName[RAS_MaxEntryName + 1];
    TCHAR szPhoneNumber[RAS_MaxPhoneNumber + 1];
    TCHAR szCallbackNumber[RAS_MaxCallbackNumber + 1];
    TCHAR szUserName[UNLEN + 1];
    TCHAR szPassword[PWLEN + 1];
    TCHAR szDomain[DNLEN + 1];
} RASDIALPARAMS, *LPRASDIALPARAMS;

/* wcesdkrRASENTRYNAME_str "RASENTRYNAME" (+ CE 5.0 twin aa450837):
 * struct printed verbatim.  CE 1.0+; Ras.h.  Returned as an array
 * by RasEnumEntries. */
typedef struct _RASENTRYNAME {
    DWORD dwSize;
    TCHAR szEntryName[RAS_MaxEntryName + 1];
} RASENTRYNAME, *LPRASENTRYNAME;

/* wcesdkrRASENTRY_str "RASENTRY" (+ CE 5.0 twin aa450836): the
 * CE 3.0 archive print ends at dwReserved2; the CE 5.0 archive
 * print appends dwCustomAuthKey -- declared for all supported
 * targets (CE .NET 4.x and later).  CE 1.0+; Ras.h.
 * dwfOptions/dwfNetProtocols/dwFramingProtocol flag values below. */
typedef struct _RASENTRY {
    DWORD     dwSize;
    DWORD     dwfOptions;
    DWORD     dwCountryID;
    DWORD     dwCountryCode;
    TCHAR     szAreaCode[RAS_MaxAreaCode + 1];
    TCHAR     szLocalPhoneNumber[RAS_MaxPhoneNumber + 1];
    DWORD     dwAlternatesOffset;
    RASIPADDR ipaddr;
    RASIPADDR ipaddrDns;
    RASIPADDR ipaddrDnsAlt;
    RASIPADDR ipaddrWins;
    RASIPADDR ipaddrWinsAlt;
    DWORD     dwFrameSize;
    DWORD     dwfNetProtocols;
    DWORD     dwFramingProtocol;
    TCHAR     szScript[MAX_PATH];
    TCHAR     szAutoDialDll[MAX_PATH];
    TCHAR     szAutoDialFunc[MAX_PATH];
    TCHAR     szDeviceType[RAS_MaxDeviceType + 1];
    TCHAR     szDeviceName[RAS_MaxDeviceName + 1];
    TCHAR     szX25PadType[RAS_MaxPadType + 1];
    TCHAR     szX25Address[RAS_MaxX25Address + 1];
    TCHAR     szX25Facilities[RAS_MaxFacilities + 1];
    TCHAR     szX25UserData[RAS_MaxUserData + 1];
    DWORD     dwChannels;
    DWORD     dwReserved1;
    DWORD     dwReserved2;
    DWORD     dwCustomAuthKey;
} RASENTRY, *LPRASENTRY;

/* dwfOptions flags: names on the CE 3.0/5.0 RASENTRY pages; values
 * adopted from the R1 CE lineage.  Six CE-5.0-page flag names have
 * no value in any allowed source and stay recorded only (below). */
#define RASEO_UseCountryAndAreaCodes  0x00000001
#define RASEO_SpecificIpAddr          0x00000002
#define RASEO_SpecificNameServers     0x00000004
#define RASEO_IpHeaderCompression     0x00000008
#define RASEO_RemoteDefaultGateway    0x00000010
#define RASEO_DisableLcpExtensions    0x00000020
#define RASEO_ModemLights             0x00000100
#define RASEO_SwCompression           0x00000200
#define RASEO_RequireEncryptedPw      0x00000400
#define RASEO_RequireMsEncryptedPw    0x00000800
#define RASEO_RequireDataEncryption   0x00001000
#define RASEO_NetworkLogon            0x00002000
#define RASEO_UseLogonCredentials     0x00004000
#define RASEO_PromoteAlternates       0x00008000
#define RASEO_PreviewUserPw           0x01000000
#define RASEO_CustomScript            0x80000000
/* Names recorded without a value (CE 5.0 page names only; absent
 * from every allowed value source): RASEO_DialAsLocalCall,
 * RASEO_ProhibitPAP, RASEO_ProhibitCHAP, RASEO_ProhibitEAP,
 * RASEO_ProhibitMsCHAP, RASEO_ProhibitMsCHAP2. */

/* dwfNetProtocols values (name family on the RASENTRY member prose;
 * values adopted from the R1 CE lineage). */
#define RASNP_NetBEUI 0x00000001
#define RASNP_Ipx     0x00000002
#define RASNP_Ip      0x00000004

/* dwFramingProtocol values (same provenance). */
#define RASFP_Ppp  0x00000001
#define RASFP_Slip 0x00000002
#define RASFP_Ras  0x00000004

/* wcesdkrRASDEVINFO_str "RASDEVINFO" (+ CE 5.0 twin aa450833):
 * struct printed verbatim with CHAR arrays (TAPI device strings are
 * ANSI on CE by the official print).  The RasEnumDevices prototype
 * uses the W spelling; RASDEVINFOW aliases the same struct.
 * CE 1.0+; Ras.h. */
typedef struct tagRASDEVINFO {
    DWORD dwSize;
    CHAR  szDeviceType[RAS_MaxDeviceType + 1];
    CHAR  szDeviceName[RAS_MaxDeviceName + 1];
} RASDEVINFO, RASDEVINFOW, *LPRASDEVINFO, *LPRASDEVINFOW;

/* szDeviceType string constants (names on the RASDEVINFO page;
 * literals adopted from the R1 CE lineage). */
#define RASDT_Modem TEXT("modem")
#define RASDT_Isdn  TEXT("isdn")
#define RASDT_X25   TEXT("x25")
#define RASDT_Vpn   TEXT("vpn")
#define RASDT_Pad   TEXT("pad")

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
} RASPROJECTION, *LPRASPROJECTION;

/* wcesdkrRASPPPIP "RASPPPIP" (+ CE 5.0 twin aa450854): struct
 * printed verbatim.  CE 1.0+; Ras.h.  Returned by
 * RasGetProjectionInfo for RASP_PppIp.  CE remark: dwSize must
 * specify the size of the structure without the desktop
 * szServerIpAddress member. */
typedef struct _RASPPPIP {
    DWORD dwSize;
    DWORD dwError;
    TCHAR szIpAddress[RAS_MaxIpAddress + 1];
} RASPPPIP, *LPRASPPPIP;

/* Audit 2026-09-14 (docs/surface-audit.tsv): RASPPPIPV6 was absent
 * though RASPROJECTION/RASPPPIP (its siblings, same page family) were
 * already shipped. Verified against three independent mirrors of the
 * same CE archive page (aa450855 / ms897068 / ee496784, the CE 6.0
 * twin): OS Versions: Windows CE .NET 4.1 and later.; Header: Ras.h.
 * Field names transcribed exactly as the CE page prints them
 * (LocalInterfaceIdentifier, not the later desktop SDK's
 * bLocalInterfaceIdentifier -- the CE-era archive page never gained
 * that later desktop rename). Returned by RasGetProjectionInfo for
 * RASP_PppIp6 (not itself found live at CE 4.1/5.0/6.0 -- see note
 * below; the struct is shipped as the page documents it regardless,
 * matching the project's declared-independent-of-consumer policy for
 * struct records). The page's own Syntax block writes the tag via a
 * macro alias (`#define RASPPPIPV6 struct tagRASPPPIPV6`) rather than
 * a typedef; reproduced as printed rather than normalized to a
 * typedef. */
#define RASPPPIPV6 struct tagRASPPPIPV6
RASPPPIPV6 {
    DWORD dwSize;
    DWORD dwError;
    BYTE  LocalInterfaceIdentifier[8];
    BYTE  PeerInterfaceIdentifier[8];
    BYTE  LocalCompressionProtocol[2];
    BYTE  PeerCompressionProtocol[2];
};
#define LPRASPPPIPV6 RASPPPIPV6*

/* RASDIALEXTENSIONS: referenced by the RasDial prototype (the CE
 * page says the parameter is ignored and should be NULL).  The CE
 * pages do not print the struct; the layout is adopted from the R1
 * CE lineage (ABI fact, clean-room.md 4). */
typedef struct tagRASDIALEXTENSIONS {
    DWORD dwSize;
    DWORD dwfOptions;
    HWND  hwndParent;
    ULONG_PTR reserved;
} RASDIALEXTENSIONS, *LPRASDIALEXTENSIONS;

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

/* --- RAS client functions. ----------------------------------------
 * Prototypes printed by the CE 3.0 archive pages (cross-checked
 * against the CE 5.0 twins where they exist); coredll exports
 * verified on the audited sysroot surface (CE 4, 5, 6 ARM + CE 6
 * x86). */

/* wcesdkrRasDial "RasDial": CE 1.0+; Ras.h, Afdfunc.h.  dialExten
 * sions and phoneBookPath are ignored on CE (NULL); NotifierType
 * 0xFFFFFFFF makes notifier an HWND receiving WM_RASDIALEVENT. */
/* ee496966: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasDial(LPRASDIALEXTENSIONS dialExtensions,
                    LPTSTR phoneBookPath, LPRASDIALPARAMS rasDialParam,
                    DWORD NotifierType, LPVOID notifier,
                    LPHRASCONN pRasConn) AKARI_CE_NAME(RasDial);

/* wcesdkrRasEnumConnections "RasEnumConnections": CE 1.0+; Ras.h,
 * Afdfunc.h. */
/* ee496203: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasEnumConnections(LPRASCONN lprasconn, LPDWORD lpcb,
                    LPDWORD lpcConnections) AKARI_CE_NAME(RasEnumConnections);

/* wcesdkrRasEnumDevices "RasEnumDevices": CE 3.0+; Ras.h. */
/* ee497423: page print verified (proto-cite) */
AKARI_CE_IMPORT DWORD RasEnumDevicesW(LPRASDEVINFOW lpRasDevinfo, LPDWORD lpcb,
                    LPDWORD lpcDevices) AKARI_CE_NAME(RasEnumDevicesW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define RasEnumDevices RasEnumDevicesW

/* wcesdkrRasEnumEntries "RasEnumEntries": CE 1.0+; Ras.h,
 * Afdfunc.h.  lpszPhoneBookPath is ignored on CE. */
/* ee496207: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasEnumEntries(LPWSTR Reserved, LPWSTR lpszPhoneBookPath,
                    LPRASENTRYNAME lprasentryname, LPDWORD lpcb,
                    LPDWORD lpcEntries) AKARI_CE_NAME(RasEnumEntries);

/* wcesdkrRasGetConnectStatus "RasGetConnectStatus": CE 1.0+;
 * Ras.h, Afdfunc.h. */
/* ee497517: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasGetConnectStatus(HRASCONN rasconn,
                    LPRASCONNSTATUS lprasconnstatus) AKARI_CE_NAME(RasGetConnectStatus);

/* wcesdkrRasGetEntryDialParams "RasGetEntryDialParams": CE 1.0+;
 * Ras.h, Afdfunc.h. */
/* ee496835: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasGetEntryDialParams(LPWSTR lpszPhoneBook,
                    LPRASDIALPARAMS lpRasDialParams,
                    LPBOOL lpfPassword) AKARI_CE_NAME(RasGetEntryDialParams);

/* wcesdkrRasGetEntryProperties "RasGetEntryProperties": CE 1.0+;
 * Ras.h, Afdfunc.h. */
/* ee496231: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasGetEntryProperties(LPWSTR lpszPhoneBook, LPWSTR szEntry,
                    LPRASENTRY lpbEntry, LPDWORD lpdwEntrySize,
                    LPBYTE lpb, LPDWORD lpdwSize) AKARI_CE_NAME(RasGetEntryProperties);

/* wcesdkrRasGetLinkStatistics "RasGetLinkStatistics": CE 3.0+;
 * Ras.h, Afdfunc.h. */
/* ee496606: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasGetLinkStatistics(HRASCONN hRasConn, DWORD dwSubEntry,
                    RAS_STATS *lpStatistics) AKARI_CE_NAME(RasGetLinkStatistics);

/* wcesdkrRasGetProjectionInfo "RasGetProjectionInfo": CE 3.0+;
 * Ras.h, Afdfunc.h. */
/* ee496239: page print verified (proto-cite) */
AKARI_CE_IMPORT DWORD RasGetProjectionInfoW(HRASCONN hrasconn,
                    RASPROJECTION rasprojection, LPVOID lpprojection,
                    LPDWORD lpcb) AKARI_CE_NAME(RasGetProjectionInfoW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define RasGetProjectionInfo RasGetProjectionInfoW

/* wcesdkrRasHangUp "RasHangUp": CE 1.0+; Ras.h, Afdfunc.h. */
/* ee497206: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasHangUp(HRASCONN Session) AKARI_CE_NAME(RasHangUp);

/* wcesdkrRasSetEntryDialParams "RasSetEntryDialParams": CE 1.0+;
 * Ras.h, Afdfunc.h. */
/* ee496751: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasSetEntryDialParams(LPWSTR lpszPhoneBook,
                    LPRASDIALPARAMS lpRasDialParams,
                    BOOL fRemovePassword) AKARI_CE_NAME(RasSetEntryDialParams);

/* wcesdkrRasSetEntryProperties "RasSetEntryProperties": CE 1.0+;
 * Ras.h, Afdfunc.h. */
/* ee497296: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasSetEntryProperties(LPWSTR lpszPhoneBook, LPWSTR szEntry,
                    LPRASENTRY lpbEntry, DWORD dwEntrySize,
                    LPBYTE lpb, DWORD dwSize) AKARI_CE_NAME(RasSetEntryProperties);

/* wcesdkrRasDeleteEntry "RasDeleteEntry":
 * DWORD RasDeleteEntry(LPWSTR, LPWSTR).  CE 3.0+; Ras.h, Afdfunc.h.
 * Deletes a phone-book entry (lpszPhonebook is ignored on CE --
 * entries live in the registry). */
/* ee497338: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasDeleteEntry(LPWSTR lpszPhonebook, LPWSTR lpszEntry)
                    AKARI_CE_NAME(RasDeleteEntry);

/* wcesdkrRasRenameEntry "RasRenameEntry":
 * DWORD RasRenameEntry(LPWSTR, LPWSTR, LPWSTR).  CE 1.0+; Ras.h,
 * Afdfunc.h.  Renames a phone-book entry; call RasValidateEntryName
 * on the new name first. */
/* ee497260: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasRenameEntry(LPWSTR lpszPhonebook, LPWSTR lpszOldEntry,
                    LPWSTR lpszNewEntry) AKARI_CE_NAME(RasRenameEntry);

/* wcesdkrRasValidateEntryName "RasValidateEntryName":
 * DWORD RasValidateEntryName(LPWSTR, LPWSTR).  CE 1.0+; Ras.h,
 * Afdfunc.h.  Validates an entry name (at least one alphanumeric
 * character; no | > < ? * \ / : characters). */
/* ee496752: param-list verified against this page (proto-cite) */
AKARI_CE_IMPORT DWORD RasValidateEntryName(LPWSTR lpszPhonebook, LPWSTR lpszEntry)
                    AKARI_CE_NAME(RasValidateEntryName);

/* --- RAS server administration structures that depend on the RAS
 * client types above (Servers book, used with the RasIOControl
 * record in Service.h; see docs/inventory.md M75f). */

/* ms896354 "RASCNTL_SERVERLINE": print verbatim (archive glues the
 * type/parameter spellings; spacing restored).  CROSS-GENERATION
 * (M86 sweep): the CE 4.0 twin ms924959 prints the same members but
 * drops the semicolon after `BYTE DevConfig[1]` (archive print
 * artifact; members identical). */
typedef struct tagRasCntlServerLine {
    RASDEVINFO rasDevInfo;
    BOOL       bEnable;
    DWORD      bmFlags;
    UINT       DisconnectIdleSeconds;
    DWORD      dwDevConfigSize;
    BYTE       DevConfig[1];
} RASCNTL_SERVERLINE, *PRASCNTL_SERVERLINE;

/* ms896356 "RASCNTL_SERVERUSERCREDENTIALS": print verbatim. */
typedef struct tagRasCntlServerUser {
    TCHAR tszUserName[UNLEN + 1];
    TCHAR tszDomainName[DNLEN + 1];
    BYTE  password[PWLEN];
    DWORD cbPassword;
} RASCNTL_SERVERUSERCREDENTIALS, *PRASCNTL_SERVERUSERCREDENTIALS;

/* ms896357 "RASCNTL_SERVERCONNECTION": print verbatim. */
#if _WIN32_WCE >= 0x0500   /* Windows CE 5.0 and later. (ms896357) */
typedef struct tagRasCntlServerConnection {
    RASDEVINFO   rasDevInfo;
    HRASCONN     hrasconn;
    DWORD        dwServerIpAddress;
    DWORD        dwClientIpAddress;
    RASCONNSTATE RasConnState;
    TCHAR        tszUserName[DNLEN + 1 + UNLEN + 1];
} RASCNTL_SERVERCONNECTION, *PRASCNTL_SERVERCONNECTION;
#endif /* _WIN32_WCE >= 0x0500 */

/* VARSTRING -- needed by RasDevConfigDialogEdit (ms897088).  The
 * type page is ms898569 (Header: Tapi.h); the identical print is
 * carried under Tapi.h, guarded so both headers may coexist. */
#ifndef AKARI_VARSTRING_DEFINED
#define AKARI_VARSTRING_DEFINED
typedef struct varstring_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwStringFormat;
    DWORD dwStringSize;
    DWORD dwStringOffset;
} VARSTRING;
typedef VARSTRING *LPVARSTRING;
#endif /* AKARI_VARSTRING_DEFINED */

/* --- M104 declarations: printed prototypes recovered
 * from the official pages (tools/decl-d1.py). -------- */

/* ms897088: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT DWORD RasDevConfigDialogEditW(LPCWSTR szDeviceName, LPCWSTR szDeviceType, HWND hWndOwner, LPVOID lpDeviceConfigIn, DWORD dwSize, LPVARSTRING lpDeviceConfigOut) AKARI_CE_NAME(RasDevConfigDialogEditW);
/* the verified coredll surface exports only the W form;
 * the documented generic name is its alias (CE is
 * Unicode-only). */
#define RasDevConfigDialogEdit RasDevConfigDialogEditW

/* ms897102: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT DWORD RasGetEapConnectionData(LPCTSTR pszPhonebook, LPCTSTR pszEntry, PBYTE pbEapData, PDWORD pdwSizeofEapData) AKARI_CE_NAME(RasGetEapConnectionData);

/* ms897103: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT DWORD RasGetEapUserData(HANDLE hToken, LPCTSTR pszPhonebook, LPCTSTR pszEntry, PBYTE pbEapData, PDWORD pdwSizeofEapData) AKARI_CE_NAME(RasGetEapUserData);

/* ms897092: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT DWORD RasSetEapConnectionData(LPCTSTR pszPhonebook, LPCTSTR pszEntry, PBYTE pbEapData, PDWORD pdwSizeofEapData) AKARI_CE_NAME(RasSetEapConnectionData);

/* ms897117: page-printed prototype (Windows CE .NET 4.0 and later.; coredll.lib). */
AKARI_CE_IMPORT DWORD RasSetEapUserData(HANDLE hToken, LPCTSTR pszPhonebook, LPCTSTR pszEntry, BYTE* pbEapData, DWORD dwSizeofEapData) AKARI_CE_NAME(RasSetEapUserData);


/* --- type definitions from official page prints
 * (tools/decl-types.py). ----------------------------- */

/* ms924957: page-printed definition (Windows CE .NET 4.0 and later.). */
typedef enum tagRasCntlEnum { RASCNTL_SERVER_GET_STATUS, RASCNTL_SERVER_ENABLE, RASCNTL_SERVER_DISABLE, RASCNTL_SERVER_GET_PARAMETERS, RASCNTL_SERVER_SET_PARAMETERS, RASCNTL_SERVER_LINE_ADD, RASCNTL_SERVER_LINE_REMOVE, RASCNTL_SERVER_LINE_ENABLE, RASCNTL_SERVER_LINE_DISABLE, RASCNTL_SERVER_LINE_GET_PARAMETERS, RASCNTL_SERVER_LINE_SET_PARAMETERS, RASCNTL_SERVER_USER_SET_CREDENTIALS, RASCNTL_SERVER_USER_DELETE_CREDENTIALS } RasCntlEnum;

/* --- Audit 2026-09-14 (docs/surface-audit.tsv): the five "RAS Custom
 * Scripting DLL Functions" (RasGetBuffer/RasFreeBuffer/RasSendBuffer/
 * RasReceiveBuffer/RasRetrieveBuffer) surfaced as undeclared names
 * with a Ppp.lib Library row, but they are not coredll imports: each
 * page's own text says "RAS passes the function pointer ... the
 * custom-scripting DLL calls X through a function pointer" -- X is a
 * placeholder name for a callback the DLL author implements, exactly
 * the callback-typedef shape docs/app-surface.md already excludes
 * (see BrowseCallbackProc/AbortProc there). What IS declarable is the
 * PFNRASxxx pointer-to-function typedef each page prints; that is
 * what is added below. Confirmed via CE 5.0 pages aa450842 (GetBuffer),
 * ee496582 (FreeBuffer, CE 6.0 twin), aa450860 (SendBuffer), and the
 * desktop ras.h reference page nc-ras-pfnrasreceivebuffer for the
 * ReceiveBuffer parameter list (dwTimeOut/hEvent), which the CE-side
 * RasCustomScriptExecute page corroborates has the same five-parameter
 * shape on CE (custom-scripting is a coredll RAS feature, unchanged
 * across the desktop/CE split); RasRetrieveBuffer via aa450859/
 * ee496641 (CE 6.0 twin). All five: OS Versions: Windows CE .NET 4.0
 * and later.; Header: Ras.h.; Link Library: Ppp.lib. */
typedef DWORD (APIENTRY *PFNRASGETBUFFER)(PBYTE *ppBuffer, PDWORD pdwSize);
typedef DWORD (APIENTRY *PFNRASFREEBUFFER)(PBYTE pBuffer);
typedef DWORD (APIENTRY *PFNRASSENDBUFFER)(HANDLE hPort, PBYTE pBuffer, PDWORD dwSize);
typedef DWORD (APIENTRY *PFNRASRECEIVEBUFFER)(HANDLE hPort, PBYTE pBuffer, PDWORD pdwSize, DWORD dwTimeOut, HANDLE hEvent);
typedef DWORD (APIENTRY *PFNRASRETRIEVEBUFFER)(HANDLE hPort, PBYTE pBuffer, PDWORD pdwSize);

#endif /* AKARI_RAS_H */
