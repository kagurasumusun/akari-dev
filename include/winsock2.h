/* WinCE development API surface.
 * Original declarations written from a survey of CE 4.2, 5.0, and 6.0
 * public interface facts (names, types, layouts, constants, exports).
 * Not an OS, BSP, OAK, or Platform Builder component, and not a copy
 * of upstream source.
 */

#ifndef WCE_WINSOCK2_H
#define WCE_WINSOCK2_H
#include "windef.h"
#include "winnt.h"
#include "wceunk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagWSABUF { u_long len; char FAR * buf; } WSABUF, *PWSABUF, *LPWSABUF;
typedef struct tagSOCKET_ADDRESS { LPSOCKADDR lpSockaddr; INT iSockaddrLength; } SOCKET_ADDRESS, *PSOCKET_ADDRESS, *LPSOCKET_ADDRESS;
typedef struct tagAFPROTOCOLS { INT iAddressFamily; INT iProtocol; } AFPROTOCOLS, *PAFPROTOCOLS, *LPAFPROTOCOLS;
typedef struct tagWSANSCLASSINFOA { LPSTR lpszName; DWORD dwNameSpace; DWORD dwValueType; DWORD dwValueSize; LPVOID lpValue; } WSANSCLASSINFOA, *PWSANSCLASSINFOA, *LPWSANSCLASSINFOA;
typedef struct tagWSANSCLASSINFOW { LPWSTR lpszName; DWORD dwNameSpace; DWORD dwValueType; DWORD dwValueSize; LPVOID lpValue; } WSANSCLASSINFOW, *PWSANSCLASSINFOW, *LPWSANSCLASSINFOW;
typedef struct tagWSASERVICECLASSINFOA { LPGUID lpServiceClassId; LPSTR lpszServiceClassName; DWORD dwCount; LPWSANSCLASSINFOA lpClassInfos; } WSASERVICECLASSINFOA, *PWSASERVICECLASSINFOA, *LPWSASERVICECLASSINFOA;
typedef struct tagWSASERVICECLASSINFOW { LPGUID lpServiceClassId; LPWSTR lpszServiceClassName; DWORD dwCount; LPWSANSCLASSINFOW lpClassInfos; } WSASERVICECLASSINFOW, *PWSASERVICECLASSINFOW, *LPWSASERVICECLASSINFOW;
typedef struct tagWSANAMESPACE_INFOA { GUID NSProviderId; DWORD dwNameSpace; BOOL fActive; DWORD dwVersion; LPSTR lpszIdentifier; } WSANAMESPACE_INFOA, *PWSANAMESPACE_INFOA, *LPWSANAMESPACE_INFOA;
typedef struct tagWSANAMESPACE_INFOW { GUID NSProviderId; DWORD dwNameSpace; BOOL fActive; DWORD dwVersion; LPWSTR lpszIdentifier; } WSANAMESPACE_INFOW, *PWSANAMESPACE_INFOW, *LPWSANAMESPACE_INFOW;

WCE_IMPORT int WINAPI closesocket(IN SOCKET s) WCE_LINK(closesocket);
WCE_IMPORT int WINAPI ioctlsocket(IN SOCKET s, IN long cmd, IN OUT u_long FAR * argp) WCE_LINK(ioctlsocket);
WCE_IMPORT int WINAPI getsockopt(IN SOCKET s, IN int level, IN int optname, OUT char FAR * optval, IN OUT int FAR * optlen) WCE_LINK(getsockopt);
WCE_IMPORT u_long WINAPI htonl(IN u_long hostlong) WCE_LINK(htonl);
WCE_IMPORT u_short WINAPI htons(IN u_short hostshort) WCE_LINK(htons);
WCE_IMPORT unsigned long WINAPI inet_addr(IN const char FAR * cp) WCE_LINK(inet_addr);
WCE_IMPORT int WINAPI listen(IN SOCKET s, IN int backlog) WCE_LINK(listen);
WCE_IMPORT u_long WINAPI ntohl(IN u_long netlong) WCE_LINK(ntohl);
WCE_IMPORT u_short WINAPI ntohs(IN u_short netshort) WCE_LINK(ntohs);
WCE_IMPORT int WINAPI recv(IN SOCKET s, OUT char FAR * buf, IN int len, IN int flags) WCE_LINK(recv);
WCE_IMPORT int WINAPI send(IN SOCKET s, IN const char FAR * buf, IN int len, IN int flags) WCE_LINK(send);
WCE_IMPORT int WINAPI setsockopt(IN SOCKET s, IN int level, IN int optname, IN const char FAR * optval, IN int optlen) WCE_LINK(setsockopt);
WCE_IMPORT int WINAPI shutdown(IN SOCKET s, IN int how) WCE_LINK(shutdown);
WCE_IMPORT SOCKET WINAPI socket(IN int af, IN int type, IN int protocol) WCE_LINK(socket);
WCE_IMPORT int WINAPI gethostname(OUT char FAR * name, IN int namelen) WCE_LINK(gethostname);
WCE_IMPORT int WINAPI sethostname(IN char *pName, IN int cName) WCE_LINK(sethostname);
WCE_IMPORT int WINAPI WSAStartup(IN WORD wVersionRequested, OUT LPWSADATA lpWSAData) WCE_LINK(WSAStartup);
WCE_IMPORT int WINAPI WSACleanup(void) WCE_LINK(WSACleanup);
WCE_IMPORT void WINAPI WSASetLastError(IN int iError) WCE_LINK(WSASetLastError);
WCE_IMPORT int WINAPI WSAGetLastError(void) WCE_LINK(WSAGetLastError);
WCE_IMPORT BOOL WINAPI WSAIsBlocking(void) WCE_LINK(WSAIsBlocking);
WCE_IMPORT int WINAPI WSAUnhookBlockingHook(void) WCE_LINK(WSAUnhookBlockingHook);
WCE_IMPORT FARPROC WINAPI WSASetBlockingHook(IN FARPROC lpBlockFunc) WCE_LINK(WSASetBlockingHook);
WCE_IMPORT int WINAPI WSACancelBlockingCall(void) WCE_LINK(WSACancelBlockingCall);
WCE_IMPORT HANDLE WINAPI WSAAsyncGetServByName(IN HWND hWnd, IN u_int wMsg, IN const char FAR * name, IN const char FAR * proto, OUT char FAR * buf, IN int buflen) WCE_LINK(WSAAsyncGetServByName);
WCE_IMPORT HANDLE WINAPI WSAAsyncGetServByPort(IN HWND hWnd, IN u_int wMsg, IN int port, IN const char FAR * proto, OUT char FAR * buf, IN int buflen) WCE_LINK(WSAAsyncGetServByPort);
WCE_IMPORT HANDLE WINAPI WSAAsyncGetProtoByName(IN HWND hWnd, IN u_int wMsg, IN const char FAR * name, OUT char FAR * buf, IN int buflen) WCE_LINK(WSAAsyncGetProtoByName);
WCE_IMPORT HANDLE WINAPI WSAAsyncGetProtoByNumber(IN HWND hWnd, IN u_int wMsg, IN int number, OUT char FAR * buf, IN int buflen) WCE_LINK(WSAAsyncGetProtoByNumber);
WCE_IMPORT HANDLE WINAPI WSAAsyncGetHostByName(IN HWND hWnd, IN u_int wMsg, IN const char FAR * name, OUT char FAR * buf, IN int buflen) WCE_LINK(WSAAsyncGetHostByName);
WCE_IMPORT HANDLE WINAPI WSAAsyncGetHostByAddr(IN HWND hWnd, IN u_int wMsg, IN const char FAR * addr, IN int len, IN int type, OUT char FAR * buf, IN int buflen) WCE_LINK(WSAAsyncGetHostByAddr);
WCE_IMPORT int WINAPI WSACancelAsyncRequest(IN HANDLE hAsyncTaskHandle) WCE_LINK(WSACancelAsyncRequest);
WCE_IMPORT int WINAPI WSAAsyncSelect(IN SOCKET s, IN HWND hWnd, IN u_int wMsg, IN long lEvent) WCE_LINK(WSAAsyncSelect);
WCE_IMPORT int WINAPI WSADuplicateSocketA(IN SOCKET s, IN DWORD dwProcessId, OUT LPWSAPROTOCOL_INFOA lpProtocolInfo) WCE_LINK(WSADuplicateSocketA);
WCE_IMPORT int WINAPI WSADuplicateSocketW(IN SOCKET s, IN DWORD dwProcessId, OUT LPWSAPROTOCOL_INFOW lpProtocolInfo) WCE_LINK(WSADuplicateSocketW);
WCE_IMPORT int WINAPI WSAEnumProtocolsA(IN LPINT lpiProtocols, OUT LPWSAPROTOCOL_INFOA lpProtocolBuffer, IN OUT LPDWORD lpdwBufferLength) WCE_LINK(WSAEnumProtocolsA);
WCE_IMPORT int WINAPI WSAEnumProtocolsW(IN LPINT lpiProtocols, OUT LPWSAPROTOCOL_INFOW lpProtocolBuffer, IN OUT LPDWORD lpdwBufferLength) WCE_LINK(WSAEnumProtocolsW);
WCE_IMPORT BOOL WINAPI WSAGetOverlappedResult(IN SOCKET s, IN LPWSAOVERLAPPED lpOverlapped, OUT LPDWORD lpcbTransfer, IN BOOL fWait, OUT LPDWORD lpdwFlags) WCE_LINK(WSAGetOverlappedResult);
WCE_IMPORT BOOL WINAPI WSAGetQOSByName(IN SOCKET s, IN LPWSABUF lpQOSName, OUT LPQOS lpQOS) WCE_LINK(WSAGetQOSByName);
WCE_IMPORT int WINAPI WSAHtonl(IN SOCKET s, IN u_long hostlong, OUT u_long FAR * lpnetlong) WCE_LINK(WSAHtonl);
WCE_IMPORT int WINAPI WSAHtons(IN SOCKET s, IN u_short hostshort, OUT u_short FAR * lpnetshort) WCE_LINK(WSAHtons);
WCE_IMPORT int WINAPI WSAIoctl(IN SOCKET s, IN DWORD dwIoControlCode, IN LPVOID lpvInBuffer, IN DWORD cbInBuffer, OUT LPVOID lpvOutBuffer, IN DWORD cbOutBuffer, OUT LPDWORD lpcbBytesReturned, IN LPWSAOVERLAPPED lpOverlapped, IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) WCE_LINK(WSAIoctl);
WCE_IMPORT int WINAPI WSANtohl(IN SOCKET s, IN u_long netlong, OUT u_long FAR * lphostlong) WCE_LINK(WSANtohl);
WCE_IMPORT int WINAPI WSANtohs(IN SOCKET s, IN u_short netshort, OUT u_short FAR * lphostshort) WCE_LINK(WSANtohs);
WCE_IMPORT int WINAPI WSARecv(IN SOCKET s, IN OUT LPWSABUF lpBuffers, IN DWORD dwBufferCount, OUT LPDWORD lpNumberOfBytesRecvd, IN OUT LPDWORD lpFlags, IN LPWSAOVERLAPPED lpOverlapped, IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) WCE_LINK(WSARecv);
WCE_IMPORT int WINAPI WSARecvDisconnect(IN SOCKET s, OUT LPWSABUF lpInboundDisconnectData) WCE_LINK(WSARecvDisconnect);
WCE_IMPORT int WINAPI WSASend(IN SOCKET s, IN LPWSABUF lpBuffers, IN DWORD dwBufferCount, OUT LPDWORD lpNumberOfBytesSent, IN DWORD dwFlags, IN LPWSAOVERLAPPED lpOverlapped, IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) WCE_LINK(WSASend);
WCE_IMPORT int WINAPI WSASendDisconnect(IN SOCKET s, IN LPWSABUF lpOutboundDisconnectData) WCE_LINK(WSASendDisconnect);
WCE_IMPORT INT WINAPI WSAAddressToStringA(IN LPSOCKADDR lpsaAddress, IN DWORD dwAddressLength, IN LPWSAPROTOCOL_INFOA lpProtocolInfo, IN OUT LPSTR lpszAddressString, IN OUT LPDWORD lpdwAddressStringLength) WCE_LINK(WSAAddressToStringA);
WCE_IMPORT INT WINAPI WSAAddressToStringW(IN LPSOCKADDR lpsaAddress, IN DWORD dwAddressLength, IN LPWSAPROTOCOL_INFOW lpProtocolInfo, IN OUT LPWSTR lpszAddressString, IN OUT LPDWORD lpdwAddressStringLength) WCE_LINK(WSAAddressToStringW);
WCE_IMPORT INT WINAPI WSAStringToAddressA(IN LPSTR AddressString, IN INT AddressFamily, IN LPWSAPROTOCOL_INFOA lpProtocolInfo, OUT LPSOCKADDR lpAddress, IN OUT LPINT lpAddressLength) WCE_LINK(WSAStringToAddressA);
WCE_IMPORT INT WINAPI WSAStringToAddressW(IN LPWSTR AddressString, IN INT AddressFamily, IN LPWSAPROTOCOL_INFOW lpProtocolInfo, OUT LPSOCKADDR lpAddress, IN OUT LPINT lpAddressLength) WCE_LINK(WSAStringToAddressW);
WCE_IMPORT INT WINAPI WSALookupServiceBeginA(IN LPWSAQUERYSETA lpqsRestrictions, IN DWORD dwControlFlags, OUT LPHANDLE lphLookup) WCE_LINK(WSALookupServiceBeginA);
WCE_IMPORT INT WINAPI WSALookupServiceBeginW(IN LPWSAQUERYSETW lpqsRestrictions, IN DWORD dwControlFlags, OUT LPHANDLE lphLookup) WCE_LINK(WSALookupServiceBeginW);
WCE_IMPORT INT WINAPI WSALookupServiceNextA(IN HANDLE hLookup, IN DWORD dwControlFlags, IN OUT LPDWORD lpdwBufferLength, OUT LPWSAQUERYSETA lpqsResults) WCE_LINK(WSALookupServiceNextA);
WCE_IMPORT INT WINAPI WSALookupServiceNextW(IN HANDLE hLookup, IN DWORD dwControlFlags, IN OUT LPDWORD lpdwBufferLength, OUT LPWSAQUERYSETW lpqsResults) WCE_LINK(WSALookupServiceNextW);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT INT WINAPI WSANSPIoctl(IN HANDLE hLookup, IN DWORD dwControlCode, IN LPVOID lpvInBuffer, IN DWORD cbInBuffer, OUT LPVOID lpvOutBuffer, IN DWORD cbOutBuffer, OUT LPDWORD lpcbBytesReturned, IN LPWSACOMPLETION lpCompletion) WCE_LINK(WSANSPIoctl);
#endif
WCE_IMPORT INT WINAPI WSALookupServiceEnd(IN HANDLE hLookup) WCE_LINK(WSALookupServiceEnd);
WCE_IMPORT INT WINAPI WSAInstallServiceClassA(IN LPWSASERVICECLASSINFOA lpServiceClassInfo) WCE_LINK(WSAInstallServiceClassA);
WCE_IMPORT INT WINAPI WSAInstallServiceClassW(IN LPWSASERVICECLASSINFOW lpServiceClassInfo) WCE_LINK(WSAInstallServiceClassW);
WCE_IMPORT INT WINAPI WSARemoveServiceClass(IN LPGUID lpServiceClassId) WCE_LINK(WSARemoveServiceClass);
WCE_IMPORT INT WINAPI WSAGetServiceClassInfoA(IN LPGUID lpProviderId, IN LPGUID lpServiceClassId, IN OUT LPDWORD lpdwBufSize, OUT LPWSASERVICECLASSINFOA lpServiceClassInfo) WCE_LINK(WSAGetServiceClassInfoA);
WCE_IMPORT INT WINAPI WSAGetServiceClassInfoW(IN LPGUID lpProviderId, IN LPGUID lpServiceClassId, IN OUT LPDWORD lpdwBufSize, OUT LPWSASERVICECLASSINFOW lpServiceClassInfo) WCE_LINK(WSAGetServiceClassInfoW);
WCE_IMPORT INT WINAPI WSAEnumNameSpaceProvidersA(IN OUT LPDWORD lpdwBufferLength, OUT LPWSANAMESPACE_INFOA lpnspBuffer) WCE_LINK(WSAEnumNameSpaceProvidersA);
WCE_IMPORT INT WINAPI WSAEnumNameSpaceProvidersW(IN OUT LPDWORD lpdwBufferLength, OUT LPWSANAMESPACE_INFOW lpnspBuffer) WCE_LINK(WSAEnumNameSpaceProvidersW);
WCE_IMPORT INT WINAPI WSAGetServiceClassNameByClassIdA(IN LPGUID lpServiceClassId, OUT LPSTR lpszServiceClassName, IN OUT LPDWORD lpdwBufferLength) WCE_LINK(WSAGetServiceClassNameByClassIdA);
WCE_IMPORT INT WINAPI WSAGetServiceClassNameByClassIdW(IN LPGUID lpServiceClassId, OUT LPWSTR lpszServiceClassName, IN OUT LPDWORD lpdwBufferLength) WCE_LINK(WSAGetServiceClassNameByClassIdW);
WCE_IMPORT INT WINAPI WSAProviderConfigChange(IN OUT LPHANDLE lpNotificationHandle, IN LPWSAOVERLAPPED lpOverlapped, IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) WCE_LINK(WSAProviderConfigChange);
#if (_WIN32_WCE >= 0x500)
WCE_IMPORT DWORD WINAPI WSAControl(DWORD Protocol, DWORD Action, LPVOID InputBuffer, LPDWORD InputBufferLength, LPVOID OutputBuffer, LPDWORD OutputBufferLength) WCE_LINK(WSAControl);
#endif

#define WSADuplicateSocket WSADuplicateSocketW
#define WSAEnumProtocols WSAEnumProtocolsW
#define WSAAddressToString WSAAddressToStringW
#define WSAStringToAddress WSAStringToAddressW
#define WSALookupServiceBegin WSALookupServiceBeginW
#define WSALookupServiceNext WSALookupServiceNextW
#define WSAInstallServiceClass WSAInstallServiceClassW
#define WSAGetServiceClassInfo WSAGetServiceClassInfoW
#define WSAEnumNameSpaceProviders WSAEnumNameSpaceProvidersW
#define WSAGetServiceClassNameByClassId WSAGetServiceClassNameByClassIdW
#ifdef __cplusplus
}
#endif
#endif

