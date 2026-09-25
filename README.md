# WinCE Development API Surface Kit

Windows CE 6.0 向けの、開発とリンクに使う API サーフェスです。
Windows CE の OS 再実装ではなく、BSP / OAK / Platform Builder 用コンポーネントでもありません。

このリポジトリにあるのは次だけです。

```text
include/   独自に書いた CE API ヘッダ
def/       モジュールごとの公開エクスポート定義
lib/       その定義から生成したインポートライブラリ
```

## 対象

- Windows CE 6.0（`_WIN32_WCE` の既定は `0x600`）
- `ARMV4I`: インポートライブラリのマシンタイプは `IMAGE_FILE_MACHINE_ARM` (`0x01C0`)
- `X86`: `IMAGE_FILE_MACHINE_I386`。エクスポート名に先頭アンダースコアも `@n` も付けない

CE では `__stdcall` は `__cdecl` です。DLL のエクスポート名は ARM / x86 とも装飾なしです。
`TCHAR` は 16-bit の `WCHAR` です。`wchar_t` が 16-bit のターゲット（`*-pc-wince` や `-fshort-wchar`）では `L"..."` が `LPCWSTR` になります。

## 作り方

Shared Source は API 名、シグネチャ、構造体レイアウト、定数、呼び出し規約、DLL とエクスポートの対応を調べるための情報源です。
Microsoft の C/C++ ソース、コメント、モジュール定義ファイルの本文、インポートライブラリのバイナリは、このリポジトリに入れていません。
ヘッダ、`.def`、インポートライブラリは、調べた仕様から独自に書いています。

インポートライブラリに入れたのは、調査したモジュール定義で import library 対象だった公開エクスポートだけです。
`PRIVATE` のエクスポートは含めていません。`malloc` や `memcpy` などの CRT 入口は coredll.dll からは出ていますが、この契約ではインポートライブラリの外なので `lib/coredll.lib` にはありません。CRT は別途必要です。

ドライバ入口（`XXX_Init` / `XXX_IOControl` が大半のもの）と NDIS は入れていません。
`pimstore` と `smbconfig` は、調査した定義に公開エクスポートがありませんでした。

## レイアウト

```text
include/windows.h          アンブレラ
include/windef.h           基本型、ハンドル、RECT/POINT
include/winbase.h          ファイル、プロセス、同期、メモリ
include/winuser.h          ウィンドウとメッセージ
include/wingdi.h           GDI
include/winreg.h           レジストリ
include/winnls.h           コードページ
include/winerror.h         エラー定数
include/winsock2.h         ws2 の中核ソケット API
include/commctrl.h         commctrl のうち型が閉じている宣言
def/ARMV4I/<dll>.def
def/X86/<dll>.def
lib/ARMV4I/<dll>.lib
lib/X86/<dll>.lib
```

ヘッダは、典型的な CE プログラムをコンパイルするためのコア面です。
`def/` と `lib/` にある全 DLL の全関数を宣言しているわけではありません。
宣言のないエクスポートは、対応する `.lib` でリンクできます。

CE 6.0 固有のレイアウトをそのまま使っています。

- `CRITICAL_SECTION` はデスクトップの `RTL_CRITICAL_SECTION` ではない
- `WIN32_FIND_DATAW` は `dwOID` を持ち、短い代替名は持たない
- `BY_HANDLE_FILE_INFORMATION` も末尾に `dwOID` を持つ
- `OVERLAPPED` は `Internal` / `InternalHigh` / `Offset` / `OffsetHigh` / `hEvent` の並び
- `GetProcAddressW` のプロシージャ名は `LPCWSTR`

x86 の宣言は `__declspec(dllimport)` とアセンブラ名で、装飾なしの `__imp_<name>` を参照します。
ARM は装飾がないので、インポートライブラリのサンクで解決します。

## リンクする DLL

`autodial` `aygshell` `btdrt` `cellcore` `ceshell` `chsime03` `commctrl` `commdlg` `coredll` `crypt32` `d3dm` `ddraw` `dnsapi` `fwapi` `gpsapi` `hwxcht` `hwxjpn` `hwxkor` `hwxusa` `imejpp` `iphlpapi` `mlang` `msdmo` `msmqrt` `netapi32` `netui` `ntlmssp` `ole32` `oleaut32` `phcommon` `secur32` `sms` `snmpapi` `splusa` `toolhelp` `upnpcapi` `urlmon` `uspce` `wap` `wininet` `winscard` `wldap32` `ws2` `wsdapi` `wzcsapi`

`coredll` の公開エクスポートは ARM と x86 で 1 個だけ違います。ARM に `InterlockedTestExchange`、x86 に `NPXNPHandler` があります。

## 例

```c
#include <windows.h>

int wWinMain(HINSTANCE hi, HINSTANCE hp, LPWSTR cmd, int show) {
    MessageBoxW(0, L"hello", L"akari", MB_OK);
    return 0;
}
```

インポートライブラリは `lib/ARMV4I/coredll.lib` または `lib/X86/coredll.lib` を、CE 向けのリンカに渡します。
