/* WinInet. Original text. Exported by wininet.dll.
 *
 * Windows CE ships the wide and narrow forms side by side for most of this
 * surface, so both are declared; the text-mapped names at the end select between
 * them the usual way.
 */
#ifndef AKARI_WCE_WININET_H
#define AKARI_WCE_WININET_H
#ifdef __cplusplus
extern "C" {
#endif

#include "winbase.h"
#include "tchar.h"

typedef void *HINTERNET;
typedef HINTERNET *LPHINTERNET;
typedef WORD INTERNET_PORT;
typedef INTERNET_PORT *LPINTERNET_PORT;

typedef void (WINAPI *INTERNET_STATUS_CALLBACK)(HINTERNET hInternet,
    DWORD_PTR dwContext, DWORD dwInternetStatus, void *lpvStatusInformation,
    DWORD dwStatusInformationLength);
typedef INTERNET_STATUS_CALLBACK *LPINTERNET_STATUS_CALLBACK;

#define INTERNET_INVALID_PORT_NUMBER 0
#define INTERNET_DEFAULT_HTTP_PORT   80
#define INTERNET_DEFAULT_HTTPS_PORT  443
#define INTERNET_DEFAULT_FTP_PORT    21

#define INTERNET_FLAG_RELOAD              0x80000000
#define INTERNET_FLAG_RAW_DATA            0x40000000
#define INTERNET_FLAG_EXISTING_CONNECT    0x20000000
#define INTERNET_FLAG_ASYNC               0x10000000
#define INTERNET_FLAG_PASSIVE             0x08000000
#define INTERNET_FLAG_NO_CACHE_WRITE      0x04000000
#define INTERNET_FLAG_DONT_CACHE          INTERNET_FLAG_NO_CACHE_WRITE
#define INTERNET_FLAG_MAKE_PERSISTENT     0x02000000
#define INTERNET_FLAG_FROM_CACHE          0x01000000
#define INTERNET_FLAG_OFFLINE             INTERNET_FLAG_FROM_CACHE
#define INTERNET_FLAG_SECURE              0x00800000
#define INTERNET_FLAG_KEEP_CONNECTION     0x00400000
#define INTERNET_FLAG_NO_AUTO_REDIRECT    0x00200000
#define INTERNET_FLAG_READ_PREFETCH       0x00100000
#define INTERNET_FLAG_NO_COOKIES          0x00080000
#define INTERNET_FLAG_NO_AUTH             0x00040000
#define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP  0x00008000
#define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS 0x00004000
#define INTERNET_FLAG_IGNORE_CERT_DATE_INVALID 0x00002000
#define INTERNET_FLAG_IGNORE_CERT_CN_INVALID   0x00001000
#define INTERNET_FLAG_MUST_CACHE_REQUEST  0x00000010
#define INTERNET_FLAG_RESYNCHRONIZE       0x00000800
#define INTERNET_FLAG_HYPERLINK           0x00000400
#define INTERNET_FLAG_NO_UI               0x00000200
#define INTERNET_FLAG_PRAGMA_NOCACHE      0x00000100
#define INTERNET_FLAG_CACHE_ASYNC         0x00000080
#define INTERNET_FLAG_FORMS_SUBMIT        0x00000040

#define INTERNET_OPEN_TYPE_PRECONFIG      0
#define INTERNET_OPEN_TYPE_DIRECT         1
#define INTERNET_OPEN_TYPE_PROXY          3
#define INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY 4

#define INTERNET_SERVICE_FTP    1
#define INTERNET_SERVICE_GOPHER 2
#define INTERNET_SERVICE_HTTP   3

#define HTTP_MAJOR_VERSION 1
#define HTTP_MINOR_VERSION 0
#define HTTP_VERSIONA "HTTP/1.0"
#define HTTP_VERSIONW L"HTTP/1.0"

#define HTTP_QUERY_MIME_VERSION        0
#define HTTP_QUERY_CONTENT_TYPE        1
#define HTTP_QUERY_CONTENT_TRANSFER_ENCODING 2
#define HTTP_QUERY_CONTENT_ID          3
#define HTTP_QUERY_CONTENT_LENGTH      5
#define HTTP_QUERY_CONTENT_LANGUAGE    6
#define HTTP_QUERY_ALLOW               7
#define HTTP_QUERY_PUBLIC              8
#define HTTP_QUERY_DATE                9
#define HTTP_QUERY_EXPIRES             10
#define HTTP_QUERY_LAST_MODIFIED       11
#define HTTP_STATUS_CODE               19
#define HTTP_QUERY_SERVER              37
#define HTTP_QUERY_ETAG 54
#define HTTP_QUERY_SET_COOKIE          43
#define HTTP_QUERY_COOKIE              44
#define HTTP_QUERY_RAW_HEADERS         21
#define HTTP_QUERY_RAW_HEADERS_CRLF    22
#define HTTP_QUERY_FLAG_NUMBER         0x20000000
#define HTTP_QUERY_FLAG_STRING         0x40000000
#define HTTP_QUERY_FLAG_REQUEST_HEADERS 0x80000000

#define HTTP_ADDREQ_INDEX_MASK   0x0000FFFF
#define HTTP_ADDREQ_FLAG_ADD     0x20000000
#define HTTP_ADDREQ_FLAG_REPLACE 0x80000000
#define HTTP_ADDREQ_FLAG_ADD_IF_NEW 0x10000000

#define INTERNET_OPTION_CALLBACK 1
#define INTERNET_OPTION_CONNECT_TIMEOUT 2
#define INTERNET_OPTION_CONNECT_RETRIES 3
#define INTERNET_OPTION_SEND_TIMEOUT 5
#define INTERNET_OPTION_RECEIVE_TIMEOUT 6
#define INTERNET_OPTION_DATA_RECEIVE_TIMEOUT 8
#define INTERNET_OPTION_DATA_SEND_TIMEOUT 7
#define INTERNET_OPTION_USER_AGENT 41
#define INTERNET_OPTION_USERNAME 28
#define INTERNET_OPTION_PASSWORD 29
#define INTERNET_OPTION_PROXY             38
#define INTERNET_OPTION_END_BROWSER_SESSION 42
#define INTERNET_OPTION_SECURITY_CERTIFICATE 35
#define INTERNET_OPTION_SECURITY_KEY_BITNESS 36

#define INTERNET_STATUS_RESOLVING_NAME     10
#define INTERNET_STATUS_NAME_RESOLVED      11
#define INTERNET_STATUS_CONNECTING_TO_SERVER 20
#define INTERNET_STATUS_CONNECTED_TO_SERVER 21
#define INTERNET_STATUS_SENDING_REQUEST 30
#define INTERNET_STATUS_REQUEST_SENT 31
#define INTERNET_STATUS_RECEIVING_RESPONSE 40
#define INTERNET_STATUS_RESPONSE_RECEIVED 41
#define INTERNET_STATUS_CLOSING_CONNECTION 50
#define INTERNET_STATUS_CONNECTION_CLOSED 51
#define INTERNET_STATUS_HANDLE_CREATED 60
#define INTERNET_STATUS_HANDLE_CLOSING 70
#define INTERNET_STATUS_REQUEST_COMPLETE 100
#define INTERNET_STATUS_REDIRECT 110

typedef DWORD INTERNET_SCHEME;

#define INTERNET_SCHEME_HTTP  1
#define INTERNET_SCHEME_HTTPS 2
#define INTERNET_SCHEME_FTP   3

#define ICU_ESCAPE      0x80000000
#define ICU_NO_ENCODE   0x20000000
#define ICU_DECODE      0x10000000
#define ICU_NO_META     0x08000000
#define ICU_ESCAPE_SLASHES 0x04000000
#define ICU_REJECT_INPUTPWD 0x02000000

#define ICU_BROWSER_MODE 0x02000000
#define ICU_USERNAME     0x40000000
#define ICU_PASSWORD     0x20000000
#define ICU_ESCAPE       0x80000000
#define ICU_ESCAPE_AUTHORITY 0x00002000
#define ICU_ENCODE_SPACES_ONLY 0x04000000

#define URL_DONT_ESCAPE_EXTRA_INFO 0x02000000
#define URL_ESCAPE_SPACES_ONLY     0x04000000
#define URL_ESCAPE_PERCENT         0x00001000
#define URL_ESCAPE_SEGMENT_ONLY    0x00002000
#define URL_UNESCAPE_INPLACE       0x00100000
#define URL_INTERNAL_PATH          0x00800000

#define INTERNET_INVALID_STATUS_CALLBACK ((INTERNET_STATUS_CALLBACK)(-1L))

#define INTERNET_FLAG_TRANSFER_ASCII  1
#define INTERNET_FLAG_TRANSFER_BINARY 2

#define INTERNET_RFC1123_BUFSIZE 30

#define MAX_GOPHER_DISPLAY_TEXT 128
#define INTERNET_MAX_HOST_NAME_LENGTH 256
#define MAX_GOPHER_HOST_NAME    INTERNET_MAX_HOST_NAME_LENGTH

typedef struct akari_URL_COMPONENTSW {
    DWORD dwStructSize;
    LPWSTR lpszScheme;
    DWORD dwSchemeLength;
    INTERNET_SCHEME nScheme;
    LPWSTR lpszHostName;
    DWORD dwHostNameLength;
    INTERNET_PORT nPort;
    LPWSTR lpszUserName;
    DWORD dwUserNameLength;
    LPWSTR lpszPassword;
    DWORD dwPasswordLength;
    LPWSTR lpszUrlPath;
    DWORD dwUrlPathLength;
    LPWSTR lpszExtraInfo;
    DWORD dwExtraInfoLength;
} URL_COMPONENTSW, *LPURL_COMPONENTSW;

typedef struct akari_URL_COMPONENTSA {
    DWORD dwStructSize;
    LPSTR lpszScheme;
    DWORD dwSchemeLength;
    INTERNET_SCHEME nScheme;
    LPSTR lpszHostName;
    DWORD dwHostNameLength;
    INTERNET_PORT nPort;
    LPSTR lpszUserName;
    DWORD dwUserNameLength;
    LPSTR lpszPassword;
    DWORD dwPasswordLength;
    LPSTR lpszUrlPath;
    DWORD dwUrlPathLength;
    LPSTR lpszExtraInfo;
    DWORD dwExtraInfoLength;
} URL_COMPONENTSA, *LPURL_COMPONENTSA;

typedef struct akari_INTERNET_PROXY_INFO {
    DWORD dwAccessType;
    LPCTSTR lpszProxy;
    LPCTSTR lpszProxyBypass;
} INTERNET_PROXY_INFO, *LPINTERNET_PROXY_INFO;

WININETAPI HINTERNET WINAPI InternetOpenW(LPCWSTR lpszAgent, DWORD dwAccessType,
    LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
WININETAPI HINTERNET WINAPI InternetOpenA(LPCSTR lpszAgent, DWORD dwAccessType,
    LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);
WININETAPI BOOL WINAPI InternetCloseHandle(HINTERNET hInternet);
WININETAPI HINTERNET WINAPI InternetConnectW(HINTERNET hInternet, LPCWSTR lpszServerName,
    INTERNET_PORT nServerPort, LPCWSTR lpszUserName, LPCWSTR lpszPassword, DWORD dwService,
    DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI HINTERNET WINAPI InternetConnectA(HINTERNET hInternet, LPCSTR lpszServerName,
    INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService,
    DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI HINTERNET WINAPI InternetOpenUrlW(HINTERNET hInternet, LPCWSTR lpszUrl,
    LPCWSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI HINTERNET WINAPI InternetOpenUrlA(HINTERNET hInternet, LPCSTR lpszUrl,
    LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI BOOL WINAPI InternetReadFile(HINTERNET hFile, LPVOID lpBuffer,
    DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead);
WININETAPI BOOL WINAPI InternetWriteFile(HINTERNET hFile, LPCVOID lpBuffer,
    DWORD dwNumberOfBytesToWrite, LPDWORD lpdwNumberOfBytesWritten);
WININETAPI BOOL WINAPI InternetQueryDataAvailable(HINTERNET hFile, LPDWORD lpdwNumber,
    DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI DWORD WINAPI InternetSetFilePointer(HINTERNET hFile, LONG lDistanceToMove,
    void *lpDistanceToMoveHigh, DWORD dwMoveMethod, DWORD_PTR dwContext);
WININETAPI BOOL WINAPI InternetLockRequestFile(HINTERNET hInternet, HANDLE *lphLockRequestHandle);
WININETAPI BOOL WINAPI InternetUnlockRequestFile(HANDLE hLockRequestInfo);
WININETAPI DWORD WINAPI InternetAttemptConnect(DWORD dwReserved);
WININETAPI DWORD WINAPI InternetErrorDlg(HWND hWnd, HINTERNET hRequest, DWORD dwError,
    DWORD dwFlags, void **lppData);

WININETAPI HINTERNET WINAPI HttpOpenRequestW(HINTERNET hConnect, LPCWSTR lpszVerb,
    LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferer,
    LPCWSTR *lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI HINTERNET WINAPI HttpOpenRequestA(HINTERNET hConnect, LPCSTR lpszVerb,
    LPCSTR lpszObjectName, LPCSTR lpszVersion, LPCSTR lpszReferer,
    LPCSTR *lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext);
WININETAPI BOOL WINAPI HttpSendRequestW(HINTERNET hRequest, LPCWSTR lpszHeaders,
    DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
WININETAPI BOOL WINAPI HttpSendRequestA(HINTERNET hRequest, LPCSTR lpszHeaders,
    DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
WININETAPI BOOL WINAPI HttpAddRequestHeadersW(HINTERNET hRequest, LPCWSTR lpszHeaders,
    DWORD dwHeadersLength, DWORD dwModifiers);
WININETAPI BOOL WINAPI HttpAddRequestHeadersA(HINTERNET hRequest, LPCSTR lpszHeaders,
    DWORD dwHeadersLength, DWORD dwModifiers);
WININETAPI BOOL WINAPI HttpQueryInfoW(HINTERNET hRequest, DWORD dwInfoLevel,
    LPVOID lpvBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex);
WININETAPI BOOL WINAPI HttpQueryInfoA(HINTERNET hRequest, DWORD dwInfoLevel,
    LPVOID lpvBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex);
WININETAPI BOOL WINAPI HttpEndRequestW(HINTERNET hRequest, void *lpBuffersIn, DWORD dwFlags,
    DWORD_PTR dwContext);
WININETAPI BOOL WINAPI HttpEndRequestA(HINTERNET hRequest, void *lpBuffersIn, DWORD dwFlags,
    DWORD_PTR dwContext);

WININETAPI BOOL WINAPI InternetSetOptionW(HINTERNET hInternet, DWORD dwOption,
    LPVOID lpBuffer, DWORD dwBufferLength);
WININETAPI BOOL WINAPI InternetSetOptionA(HINTERNET hInternet, DWORD dwOption,
    LPVOID lpBuffer, DWORD dwBufferLength);
WININETAPI BOOL WINAPI InternetQueryOptionW(HINTERNET hInternet, DWORD dwOption,
    LPVOID lpBuffer, LPDWORD lpdwBufferLength);
WININETAPI BOOL WINAPI InternetQueryOptionA(HINTERNET hInternet, DWORD dwOption,
    LPVOID lpBuffer, LPDWORD lpdwBufferLength);
WININETAPI INTERNET_STATUS_CALLBACK WINAPI InternetSetStatusCallbackW(HINTERNET hInternet,
    INTERNET_STATUS_CALLBACK lpfnInternetCallback);
WININETAPI INTERNET_STATUS_CALLBACK WINAPI InternetSetStatusCallbackA(HINTERNET hInternet,
    INTERNET_STATUS_CALLBACK lpfnInternetCallback);
WININETAPI BOOL WINAPI InternetSetStatusCallback(HINTERNET hInternet,
    INTERNET_STATUS_CALLBACK lpfnInternetCallback);

WININETAPI BOOL WINAPI InternetCheckConnectionW(LPCWSTR lpszUrl, DWORD dwFlags,
    DWORD dwReserved);
WININETAPI BOOL WINAPI InternetCheckConnectionA(LPCSTR lpszUrl, DWORD dwFlags,
    DWORD dwReserved);
WININETAPI BOOL WINAPI InternetGetConnectedState(LPDWORD lpdwFlags, DWORD dwReserved);
WININETAPI BOOL WINAPI InternetGetConnectedStateEx(LPDWORD lpdwFlags,
    LPTSTR lpszConnectionName, DWORD dwNameLen, DWORD dwReserved);

WININETAPI BOOL WINAPI InternetCrackUrlW(LPCWSTR lpszUrl, DWORD dwUrlLength, DWORD dwFlags,
    LPURL_COMPONENTSW lpUrlComponents);
WININETAPI BOOL WINAPI InternetCrackUrlA(LPCSTR lpszUrl, DWORD dwUrlLength, DWORD dwFlags,
    LPURL_COMPONENTSA lpUrlComponents);
WININETAPI BOOL WINAPI InternetCombineUrlW(LPCWSTR lpszBaseUrl, LPCWSTR lpszRelativeUrl,
    LPWSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags);
WININETAPI BOOL WINAPI InternetCombineUrlA(LPCSTR lpszBaseUrl, LPCSTR lpszRelativeUrl,
    LPSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags);
WININETAPI BOOL WINAPI InternetCanonicalizeUrlW(LPCWSTR lpszUrl, LPWSTR lpszBuffer,
    LPDWORD lpdwBufferLength, DWORD dwFlags);
WININETAPI BOOL WINAPI InternetCanonicalizeUrlA(LPCSTR lpszUrl, LPSTR lpszBuffer,
    LPDWORD lpdwBufferLength, DWORD dwFlags);

WININETAPI BOOL WINAPI InternetGetCookieW(LPCWSTR lpszUrl, LPCWSTR lpszCookieName,
    LPWSTR lpszCookieData, LPDWORD lpdwSize);
WININETAPI BOOL WINAPI InternetGetCookieA(LPCSTR lpszUrl, LPCSTR lpszCookieName,
    LPSTR lpszCookieData, LPDWORD lpdwSize);
WININETAPI BOOL WINAPI InternetSetCookieW(LPCWSTR lpszUrl, LPCWSTR lpszCookieName,
    LPCWSTR lpszCookieData);
WININETAPI BOOL WINAPI InternetSetCookieA(LPCSTR lpszUrl, LPCSTR lpszCookieName,
    LPCSTR lpszCookieData);

WININETAPI BOOL WINAPI InternetTimeToSystemTimeW(LPCWSTR lpszTime,
    LPSYSTEMTIME lpSystemTime, DWORD dwReserved);
WININETAPI BOOL WINAPI InternetTimeToSystemTimeA(LPCSTR lpszTime,
    LPSYSTEMTIME lpSystemTime, DWORD dwReserved);
WININETAPI BOOL WINAPI InternetTimeFromSystemTimeW(const SYSTEMTIME *pst, DWORD dwRFC,
    LPWSTR lpszTime, DWORD cbTime);
WININETAPI BOOL WINAPI InternetTimeFromSystemTimeA(const SYSTEMTIME *pst, DWORD dwRFC,
    LPSTR lpszTime, DWORD cbTime);

WININETAPI BOOL WINAPI InternetFindNextFileW(HINTERNET hFind, LPVOID lpvFindData);
WININETAPI BOOL WINAPI InternetFindNextFileA(HINTERNET hFind, LPVOID lpvFindData);

/* Text-mapped names. */
#define InternetOpen            InternetOpenW
#define InternetConnect         InternetConnectW
#define InternetOpenUrl         InternetOpenUrlW
#define HttpOpenRequest         HttpOpenRequestW
#define HttpSendRequest         HttpSendRequestW
#define HttpAddRequestHeaders   HttpAddRequestHeadersW
#define HttpQueryInfo           HttpQueryInfoW
#define HttpEndRequest          HttpEndRequestW
#define InternetSetOption       InternetSetOptionW
#define InternetQueryOption     InternetQueryOptionW
#define InternetCheckConnection InternetCheckConnectionW
#define InternetCrackUrl        InternetCrackUrlW
#define InternetCombineUrl      InternetCombineUrlW
#define InternetCanonicalizeUrl InternetCanonicalizeUrlW
#define InternetGetCookie       InternetGetCookieW
#define InternetSetCookie       InternetSetCookieW
#define InternetTimeToSystemTime InternetTimeToSystemTimeW
#define InternetTimeFromSystemTime InternetTimeFromSystemTimeW
#define InternetFindNextFile    InternetFindNextFileW

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WININET_H */
