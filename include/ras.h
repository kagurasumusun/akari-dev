/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_RAS_H
#define WCE_RAS_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagRASIPADDR { BYTE a; BYTE b; BYTE c; BYTE d; } RASIPADDR, *PRASIPADDR, *LPRASIPADDR;
typedef struct tagRASCOMMSETTINGS { DWORD dwSize; BYTE bParity; BYTE bStop; WORD wAlign; } RASCOMMSETTINGS, *PRASCOMMSETTINGS, *LPRASCOMMSETTINGS;
typedef struct tagRASPPPADDR { DWORD dwSize; DWORD dwError; BOOL Valid; DWORD IpAddress; } RASPPPADDR, *PRASPPPADDR, *LPRASPPPADDR;
typedef struct tagRASCNTL_SERVER_IPV6_NET_PREFIX { BYTE IPV6NetPrefix[16]; DWORD IPV6NetPrefixBitLength; DWORD IPV6NetPrefixCount; } RASCNTL_SERVER_IPV6_NET_PREFIX, *PRASCNTL_SERVER_IPV6_NET_PREFIX, *LPRASCNTL_SERVER_IPV6_NET_PREFIX;
typedef struct tagRAS_STATS { DWORD dwSize; DWORD dwBytesXmited; DWORD dwBytesRcved; DWORD dwFramesXmited; DWORD dwFramesRcved; DWORD dwCrcErr; DWORD dwTimeoutErr; DWORD dwAlignmentErr; DWORD dwHardwareOverrunErr; DWORD dwFramingErr; DWORD dwBufferOverrunErr; DWORD dwCompressionRatioIn; DWORD dwCompressionRatioOut; DWORD dwBps; DWORD dwConnectDuration; } RAS_STATS, *PRAS_STATS, *LPRAS_STATS;

WCE_IMPORT DWORD WINAPI RasEnumDevicesW(LPRASDEVINFOW, LPDWORD, LPDWORD) WCE_LINK(RasEnumDevicesW);
WCE_IMPORT DWORD WINAPI RasGetDispPhoneNumW(LPCWSTR szPhonebook, LPCWSTR szEntry, LPWSTR szPhoneNum, DWORD dwPhoneNumLen) WCE_LINK(RasGetDispPhoneNumW);
WCE_IMPORT DWORD WINAPI RasDevConfigDialogEditW(LPCWSTR szDeviceName, LPCWSTR szDeviceType, HWND hWndOwner, LPVOID lpDeviceConfigIn, DWORD dwSize, LPVARSTRING lpDeviceConfigOut) WCE_LINK(RasDevConfigDialogEditW);
WCE_IMPORT DWORD WINAPI RasIOControl(LPVOID hRasConn, DWORD dwCode, PBYTE pBufIn, DWORD dwLenIn, PBYTE pBufOut, DWORD dwLenOut, PDWORD pdwActualOut) WCE_LINK(RasIOControl);
WCE_IMPORT DWORD WINAPI RasGetEapUserData(IN HANDLE hToken, IN LPCTSTR pszPhonebook, IN LPCTSTR pszEntry, OUT PBYTE pbEapData, IN OUT PDWORD pdwSizeofEapData) WCE_LINK(RasGetEapUserData);
WCE_IMPORT DWORD WINAPI RasSetEapUserData(IN HANDLE hToken, IN LPCTSTR pszPhonebook, IN LPCTSTR pszEntry, IN PBYTE pbEapData, IN DWORD dwSizeofEapData) WCE_LINK(RasSetEapUserData);
WCE_IMPORT DWORD WINAPI RasGetEapConnectionData(IN LPCTSTR pszPhonebook, IN LPCTSTR pszEntry, OUT PBYTE pbEapData, IN OUT PDWORD pdwSizeofEapData) WCE_LINK(RasGetEapConnectionData);
WCE_IMPORT DWORD WINAPI RasSetEapConnectionData(IN LPCTSTR pszPhonebook, IN LPCTSTR pszEntry, IN PBYTE pbEapData, IN DWORD dwSizeofEapData) WCE_LINK(RasSetEapConnectionData);

#define RasEnumDevices RasEnumDevicesW
#define RasGetDispPhoneNum RasGetDispPhoneNumW
#define RasDevConfigDialogEdit RasDevConfigDialogEditW
#ifdef __cplusplus
}
#endif
#endif

