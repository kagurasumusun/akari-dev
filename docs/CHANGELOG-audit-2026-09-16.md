# 2026-09-16 監査: ヘッダー名/構成の不一致の解決と、実コンパイラで発見した既存バグの修正

このセッションでは、実際の WinCE ターゲット clang
(`kagurasumusun/llvm-project` release `test/wince-llvm-linux.zip`) を
ダウンロードして動かし、**推測ではなく実コンパイル結果に基づいて**作業した。

前提の再確認(このリポジトリの役割):
cellvm-sdk は WinCE の **SDK でも OS 再実装でも C/C++ 標準ライブラリでもない**。
「WinCE アプリをビルドするために必要な、Microsoft が公開した CE の API
ヘッダー一式」を提供する。Linux でいう `-dev` パッケージ、役割として近いのは
cegcc の w32api (デスクトップの w32api とは用途が全く違う)。

---

## 1. 今回の主目的: ヘッダーファイル名と構成の不一致

### 問題の構造

`docs/inventory.md` の M69a〜M76a に経緯が残っている。

- 当初、`windows.h` と `Windows.h` の**両方を実ファイルとして**配置していた。
- しかしこれは **case-insensitive なファイルシステム**(Windows / macOS、
  つまり実際の CE 開発者が使うプラットフォーム)で `git clone` すると
  2 ファイルが衝突してツリーが壊れる。
- M76a でこれを是正し、**ヘッダーは MSDN が印字している綴りで 1 ファイルのみ**
  という方針に統一した。

この判断自体は正しい。だが、それによって別方向のギャップが残った:

- 実在する CE / eVC アプリのソースは、ほぼ全てが Windows 上でのみ書かれ、
  Windows 上でのみコンパイルされてきた。NTFS/FAT は case-preserving だが
  **case-insensitive** なので、`#include <windows.h>` と小文字で書いても
  通ってしまう。結果、現実のコードは小文字綴りが圧倒的多数。
- cellvm-sdk が動く先は **case-sensitive な Linux クロスビルドホスト**。
  そこでは `#include <windows.h>` は解決できない。

つまり「checkout の正しさ」と「実在ソースのビルド可能性」がトレードオフに
なっていた。

### 解決: VFS overlay による別名解決 (ファイルを増やさない)

`tools/gen-case-vfs.py` を新規追加。`include/` と `include/oak/` を走査し、
小文字綴り → 実在する MSDN 綴りファイル への **Clang VFS overlay**
(`build/case-overlay.yaml`) を生成する。

これが M76a の問題を再発させない理由:
- 生成物は `build/` の下の **1 ファイルだけ**。`.gitignore` 済みで、
  **リポジトリには一切コミットされない**。
- したがって checkout の中身は何も変わらず、case-insensitive な
  ファイルシステムで新たに衝突しうるものは増えない。

安全装置として、2 つのヘッダーが小文字化で衝突する場合は生成を中止する
(M76a の不変条件が壊れたことの検出になる)。実測では衝突ゼロ、
`include/` 307 本 + `include/oak/` 73 本、別名 363 件を生成。

Makefile に 2 つのターゲットを追加:
- `make case-vfs` — overlay を生成
- `make crosscheck-lc` — overlay 経由で、**小文字綴りの `#include`** を使って
  crosscheck と同じヘッダー行列を 6 ターゲット全部で再検証する回帰テスト

### 実証

現実的な eVC 風アプリ (小文字 include、`windows.h` / `commctrl.h` /
`tchar.h` / `winsock2.h`、`WinMain`、`STICKYKEYS`、`WM_MOUSEMOVE`、
`WSAStartup`、`InitCommonControls` などを実際に使用) を書いて、
`arm-pc-wince4.2` / `5.0` / `6.0` / `i386-pc-wince6.0` の 4 ターゲットで
**警告ゼロ・エラーゼロでコンパイル成功**することを確認した。

---

## 2. 実コンパイラを動かして発見した既存バグ (今回の作業とは無関係に壊れていた)

`make crosscheck` は、今回の作業を始める前の時点で**すでに失敗していた**。
実際のコンパイラを回すまで表面化していなかったもの。

### 2-1. `_ReturnAddress` が Clang/GCC の組み込みと衝突 (`oak/Cmnintrin.h`)

ページの印字は `void _ReturnAddress(void);` だが、Clang/GCC は同名を
`void *(void)` を返す**組み込み関数**として持っている。CE 時代のページが
書かれた後に組み込み化されたケース。`__GNUC__`/`__clang__` の下では
再宣言しないようガードした(ページの記録内容自体は変更していない)。

### 2-2. 同一関数の二重宣言 (plain 版と dllimport 版) — 4 ファイル 17 箇所

2 つの生成パスが、**同じ関数を別のページ ID から収集**し、互いに
重複排除しないまま両方書き出していた:

- 先行パス (M104, `ms9xxxxx`/`aa4xxxxx` 系) → `RET WINAPI name(...);` の素の宣言
- 後続パス (`ee4xxxxx`/`ee5xxxxx` 系) → `AKARI_CE_IMPORT ... AKARI_CE_NAME(...)`

Clang は後から `dllimport` を付ける再宣言を拒否する
(`-Wdll-attribute-on-redeclaration`)ため、6 ターゲット全部で失敗していた。

機械的な検出スクリプトを書いてツリー全体を走査し、該当を**網羅的に**特定:

| ファイル | 重複数 |
|---|---|
| `include/Gwebypasscoredllthunk.hpp` | 5 |
| `include/Netui.h` | 6 |
| `include/Kernel.h` | 4 |
| `include/Startui.h` | 2 |

いずれも **`AKARI_CE_IMPORT` 版を残し、素の宣言を削除**した。理由は、
import 版が `AKARI_CE_NAME` によるインポート名解決を担っており、
そちらを消すとリンク時の名前解決が黙って変わってしまうため。

**情報は失っていない**: 削除した側のページは、後続パスのページが
"generation not stated" としているのに対し、世代 (`Windows CE 2.10 and later.`
など) を明記していた。そのため削除したページ ID と世代情報を、
残した宣言のコメントに全て転記した。

例 (`Kernel.h`):
```
/* ee479202 KLocalFileTimeToFileTime: ...
 * (ee page states no generation; the ms903211 print of the same
 * function, removed as a duplicate above, stated Windows CE 2.10 and
 * later. -- the earliest generation of the four; Link Library: nk.lib) */
```

import 版の相手がいない宣言 (`OEMCacheRangeFlush`, `LineTranslateDialog`,
`Startup_Initialize`, `Startup_PowerOnNotification`) は**そのまま残した**。

### 2-3. `tests/host/tu_compile.c` が世代非対応だった

`gen-guard.py` のコメントで以前から「TU が世代非対応なのでガード注入を
適用できない」と記録されていた問題が、実際に表面化した形。

ヘッダー側では正しく `_WIN32_WCE >= 0x0500` でガードされている型
(D3DM* 一式、`CHANNEL_ENTRY_POINTS_EX`、`LVBKIMAGE`、`NMLVGETINFOTIP`、
`DEVMGR_DEVICE_INFORMATION`) を、TU 側が**無条件に** `_Static_assert` して
いたため、CE 4.2 ビルドで "use of undeclared identifier" になっていた。

該当 17 箇所を、ヘッダー側と同じ `#if _WIN32_WCE >= 0x0500` で囲んだ。
これで TU は世代ごとに正しく縮退する。

### 2-4. `Tchar.h` が libc を要求していた (これは私が前セッションで入れたバグ)

前セッションで私が追加した `Tchar.h` が `#include <wchar.h>` と
`#include <string.h>` を持っていた。しかしこのプロジェクトは
**libc を提供しない**ので、libc の無い sysroot では
`'wchar.h' file not found` で即死し、`tchar.h` を include する
実在の CE ソースを巻き添えにしていた。

上記の eVC 風アプリをコンパイルして初めて発覚した。

修正: **libc の include を削除**した。`_tcsXXX` は全てオブジェクト形式
マクロ(単なるトークン置換)なので、include 時点で宣言は不要。
`_tcslen` を呼ぶ TU が `<wchar.h>` を自分で include すればよく、
これはデスクトップの `<tchar.h>` と同じ責任分界。
これにより `TCHAR` / `_T()` / `_TEXT()` の部分(純粋な Win32 で、
ランタイム不要。実際の CE ソースが tchar.h から取るものの大半)が
libc 無しで使えるようになった。

---

## 3. 最終状態: 全 5 チェックがグリーン

| ターゲット | 結果 |
|---|---|
| `make crosscheck` (6 CE ターゲット) | OK / 0 errors |
| `make crosscheck-lc` (小文字綴り、6 CE ターゲット) | OK / 0 errors |
| `make hostcheck` (CE 0x420/0x500/0x600) | OK / 0 errors |
| `make cxxcheck` (C++ ヘッダー) | OK / 0 errors |
| `make defcheck` | OK / 0 errors |

`crosscheck` は着手時点では**失敗していた**ことを再度明記しておく。

## 4. 再現手順

```sh
# 小文字別名 overlay を生成
make case-vfs

# 通常の crosscheck (MSDN 綴り)
make crosscheck    WINCECLANG=/path/to/wince-clang

# 小文字綴りでの回帰テスト
make crosscheck-lc WINCECLANG=/path/to/wince-clang
```

## 6. 続き (同日): ヘッダー構成/名前/内容配置の全面点検 + 基本 API 欠落チェック

前段(1〜5)の小文字別名問題とは別の、依頼された 2 つの追加作業。

### 6-1. 内容配置の機械検証: 「Header: X.h」自己申告との突合

このツリーのほぼ全宣言は、由来ページを引用するコメントを持ち、多くが
文字通り `Header: X.h` と印字内容を記録している。これを**ファイル自身の
ファイル名と突合**するスクリプトを書いた: 一致しなければ「その宣言は
自分がどこにあるべきか自己申告しているのに、違う場所に置かれている」
ことになる。

初回スキャン: **414 件の不一致、28 ファイル**。

#### 実際に修正した 2 件(全体の 86%)

**Objbase.h -> Oleauto.h (245 個の関数/型)**: OLE Automation 関数 223+個が
`Header: Oleauto.h` と自己申告しているにもかかわらず、物理的に
`Objbase.h` に同居していた。`docs/inventory.md` M73a を確認したところ、
これは事故ではなく「ハーベスト/検証パイプラインの都合上の意図的な統合」
だったと判明(`Oleauto.h` は `#include "Objbase.h"` するだけの薄いエイリアス
だった)。しかし、これは実際の Windows CE が期待する構成とは異なる
――`<oleauto.h>` だけを include するオートメーションクライアントが、
生の COM/IUnknown 一式まで巻き込まれる必要はない。

自己完結した 245 個のブロックを実際に `Oleauto.h` へ移動。移動前に
「このブロック外の Objbase.h のどこからも参照されていないか」を機械
チェック済みだったが、**関数名だけをチェックし、ブロック内にあった
`typedef struct X X;` という不透明前方宣言 27 個を見落としていた**
――実際にコンパイルすると `Objbase.h` 側の残存コード(`ICatRegister`,
`IOleObject`, `IPersistStream` 等 27 個のインターフェースの vtable 定義)
がこれらの前方宣言を必要としており、即座にエラーになった。C11 では
同一型への typedef 再宣言が合法(6.7p3)なので、この 27 行だけを
`Objbase.h` にも再掲載して解決。6 ターゲット全部で `make crosscheck`
以下 5 チェック全てグリーンを確認。

**Cchannel.h -> Discodlg.h (インベントリコメント 134 件)**: こちらは
実コードではなく、「ページは見つけたがまだ宣言化していない」ことを
記録する棚卸しコメントブロックが、間違ったファイル(`Cchannel.h`、
しかも 2 回重複)に置かれていた。本来の置き場所 `Discodlg.h` は
既に存在していたが、こちらは 6 件+重複という不完全な状態だった。

`Cchannel.h` から削除する前に、**一度うっかりそのまま消してしまい**
(`Discodlg.h` 側が不完全だと気づく前だった)、アップロード元 zip から
元の内容を復元して 77 件を回収、`Discodlg.h` 側の重複と合わせて
78 件に重複排除してから `Discodlg.h` に統合。`Cchannel.h` の削除作業でも
`#ifdef __cplusplus` を巻き添えで消してしまいコンパイルエラーになったが、
即座に実コンパイラで検出・修正。

#### 残り 26 ファイル(60 件)は誤検知と判断

個別に文脈を確認したところ、これらは実際の宣言の誤配置ではなく、
**「このページは Header: X.h と印字しているが、理由があってここに
置いている」という説明コメント**だった(例: Winuser.h 冒頭のコメントは
「Header: Windows.h や Winbase.h と印字されている項目は windows.h /
winbase.h 側にあり、ここでは注記するだけ」と明記している)。これらは
機械的な文字列検索が拾った誤検知であり、実際の配置は既に妥当と判断し、
変更しなかった。

### 6-2. 「基本的・一般的に知られている」API の欠落チェック

CreateFileW, ReadFile, WriteFile, CreateThread, RegOpenKeyExW, MessageBoxW,
HeapAlloc, CreateWindowExW, SendMessageW, LoadLibraryW, WaitForSingleObject,
VirtualAlloc, FindFirstFileW, InterlockedIncrement, MultiByteToWideChar 等、
約 55 個の代表的な基本 Win32 API を一括チェック。

欠落 0 件(`DefWindowProc` はベース名で存在を確認)。ただし
`lstrcpy`/`lstrlen`/`lstrcmp` 系統が完全に不在だったため、これも欠落かと
一度疑ったが、**書く前に**裏取りした:
- CE 版の公式ページ "String Manipulation"(aa934507, Windows Embedded CE
  Supported)は、CE の推奨文字列関数として `wcscpy`/`wcscmp`/`wcscat`/
  `strlen` 等の **CRT 関数**を明記しており、`lstrXXX` には触れていない。
- 1999 年当時の互換性リファレンスは `lstrcmpi` を明示的に
  **"Windows CE: Not Supported"** と記録している。

これは winsvc.h / Richedit.h のときと同種の「デスクトップ Win32 の
思い込みで CE にもあるはずと判断しかける」ケースであり、今回はコードを
書く前に踏みとどまった。`lstrXXX` は追加していない。

### 検証

`make crosscheck` / `crosscheck-lc` / `hostcheck` / `cxxcheck` / `defcheck`
の 5 つ全てが今回の変更後もグリーン。


- `gen-guard.py --apply` による**宣言単位の世代ガード全面注入**は今回も
  実施していない。2-3 で TU 側の世代非対応という阻害要因の 1 つは
  解消したので前進はしたが、`gen-guard.py` が挙げるもう 1 つの理由
  (ヘッダー跨ぎの型依存、例: `Winbase.h` の型を CE5.0+ で囲むと
  世代情報を持たない `CEDDK.h` が壊れる) は未解決。
- `docs/app-surface.md` が測定した残ギャップ
  (母集団 c: 未宣言 117 / 宣言済み未 export 237) の全件解消。
  今回は `Winuser.h` のアクセシビリティ構造体 6 種 + `WM_MOUSEMOVE`、
  `Ras.h` の RAS custom-scripting コールバック typedef 5 種を埋めた。
- 重複宣言を**生成時に**防ぐガードを `decl-d1.py` 等の生成器側に入れること
  (今回は結果を機械検出して手当てしたが、再発防止は未実装)。

## 7. 続き (同日): llvm-project 側の監査から見つかった wince-api の欠落

`kagurasumusun/llvm-project` の WinCE 対応(libc++ 等)を監査していたところ、
libc++ の WinCE ロケール実装 (`libcxx/src/support/wince/locale_wince.cpp`)
が呼び出す **19 個の `LOCALE_*` 定数が `Winnls.h` に一つも存在しない**
ことが判明した。`Winnls.h` 自身のコメントは以前から
「LCType takes the LCTYPE constants (the ms906223 table); their values
are not yet transcribed (recorded)」と、この欠落を既知の未着手事項
として記録していた。

Wine と ReactOS 両方の `winnls.h`(独立した2つの実装が完全一致)で
値を裏取りし、19 個全てを追加。追加後、`Winnls.h` 単体および
`wince-api` の `crosscheck` 一式(6ターゲット)がエラー0件であることを
実コンパイラで確認済み。

これは3リポジトリ統合監査(`AGENT.md` の "Three-Repository Integration
Rule")の実例で、`llvm-project` 側のコードを読んでいなければ気づけな
かった欠落。詳細は `kagurasumusun/llvm-project` 側の
`docs/WinCE/audit-2026-09-16.md` を参照。
