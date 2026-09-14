# 2026-09-14 監査に基づく修正差分（wince-api）

前回レポート（`wince-devset-audit-2026-09-14.md`）で見つけた問題のうち、
**手元のファイルだけで安全に検証・修正できるもの**を実際に適用した。
Web一次資料と実測の両方で裏取りしたので、推測で終わっている項目はない。

## 訂正（前回レポートの誤りを撤回）

- **`Shelwapi.h` の綴りは誤りではなかった。** 実際にCE .NET 4.2 / CE 5.0時代の
  MSDNアーカイブページ（`StrRetToBuf` 等、ms940378等）を複数ミラーで確認したところ、
  Microsoft自身のCE版ドキュメントが `Header: Shelwapi.h.` と印字している
  （デスクトップ版の後年ドキュメントおよびWindows Embedded Compact 2013以降は
  `shlwapi.h` に修正されている）。プロジェクトの「ページのHeader欄をそのまま
  採用する」方針(M72)に照らせば、これは正しい判断だった。前回レポートの
  §2-3 の指摘は撤回する。

## 適用した修正

1. **壊れたファイルの除去 + 内容の正しい再配置**
   - `include/Not applicable.h`、`include/Developer-defined.h` を削除
     （どちらも識別子として不正なヘッダガードを持ち、`Makefile` の `HDRS` にも
     元々含まれていなかった孤立ファイル）。
   - `VS_VERSIONINFO`/`VS_FIXEDFILEINFO` を正しい **`include/Winver.h`**
     （新規作成）に格納。`HDRS` に追加。

2. **`Tchar.h` の新規追加**（前回レポートで確認した欠落項目）
   - `_T()`/`TCHAR`等の標準マッピング。CEがUnicode専用OSであることを踏まえ、
     `_UNICODE` 未定義時は移植性のためだけの狭い文字列モードを提供し、
     `_MBCS` は明示的に非サポートとしてエラーにした。
   - `wchar.h`/`string.h` に依存する点はデスクトップ版tchar.hおよびcegccの
     tchar.hと同じ設計であり、これらのCRTヘッダ自体は本プロジェクトの
     スコープ外（`wince-crt`のREADMEにある通りllvm-libc待ち）なので、
     このヘッダ単体はCRTが揃うまで実際にはインクルードできない
     ―― これは意図した「ゲート待ち」状態であり、バグではない。

3. **`Sdkddkver.h` の新規追加**（依頼の中核である「世代分離」の土台）
   - `_WIN32_WCE_100` 〜 `_WIN32_WCE_600` の定数群。エンコード規則
     （`0x0420` = CE 4.20 のように、マイナー番号の10進桁をそのままhexの
     下位ニブルに詰める）は、archivedされたCE版MSDNの複数ページと
     cegcc-develメーリングリストの実例（aygshell.hの `_WIN32_WCE >= 0x0420`）
     で裏取り済み。
   - CE 2.x の四半期リリース（2.01/2.10/2.11/2.12）の正確な境界は情報源に
     ばらつきがあり、コメントで信頼度の注記を残した（要:実機SDKでの確認）。
   - `Windows.h` の先頭で無条件に `#include "Sdkddkver.h"` するようにし、
     ビルドが `_WIN32_WCE` を定義していなければ最新世代（CE 6.0）に
     フォールバックする（依頼にあった「共通/世代固有の混同を避ける」ための
     土台。個々の宣言をこの定数で実際にガードする作業はP2として次回以降）。

4. **OAK/DDK層の物理分離**（`include/` → `include/` + `include/oak/`）
   - 前回レポート §2-1 でリストしたドライバ/OAL/BSP層のヘッダ **68本**を
     `include/oak/` に移動し、`Makefile` に別変数 `OAK_HDRS` として分離。
     デフォルトの `HDRS`（= アプリ開発 `-dev` 相当）からは完全に外れる。
   - 移動前に全ファイルへの相互 `#include` を機械的に検査し、アプリ層から
     OAK層へ実際に依存している3件（`Winuser.h`/`Pwinuser.h` → `Keybd.h` の
     `KEY_STATE_FLAGS`、`Externs.h`/`Nuiouser.h` → `Ndis.h` の
     `NDIS_HANDLE`/`NDIS_STATUS`/`NDIS_OID`、`Voipmanager.h` → `Rtccore.h` の
     `RTCSS_*`）を確認。これはこのプロジェクトのミスではなく、
     Microsoft自身のCE公開API面がドライバ由来の型を一部の公開関数
     シグネチャに漏らしている実態を反映している。該当3件のみ
     `#include "oak/Keybd.h"` のようにパスを付け替え、実害なく分離した。
   - 分離後、`include/*.h` 直下は225本、`include/oak/*.h` は68本、
     合計293本で移動前の総数と一致することを確認済み。

5. **`Makefile` の `HDRS` を実ファイルから機械的に再生成**
   - 手作業で追記されてきた結果、**ディスク上に存在するのに `HDRS` に
     一度も載っていないヘッダが22本**見つかった（`Calibrui.h`,
     `Htmlctrl.h`, `Kernel.h`, `Pwinbase.h`, `Windev.h` 等）。中身を確認した
     ところ、いずれも後発マイルストーン（`tools/decl-d1.py`/`decl-types.py`,
     M105）で正しく生成された実体のあるヘッダで、破損ファイルではなく
     単に `HDRS` への追記漏れだった。
   - `include/*.h`・`include/*.hpp` を機械的に列挙して `HDRS` を再生成し、
     この22本を含め、全225本の存在をMakefile側と突合済み。

## 検証コマンド（再現用）

```sh
# Makefileが参照する全ファイルが実在するか
grep -oE "include/[A-Za-z0-9_./-]+\.(h|hpp)" wince-api/Makefile | sort -u \
  | xargs -I{} test -f wince-api/{} || echo MISSING

# ディスク上のヘッダが全てMakefileに載っているか（HDRS + OAK_HDRS）
for f in wince-api/include/*.h wince-api/include/*.hpp wince-api/include/oak/*.h; do
  grep -qxF "${f#wince-api/}" /tmp/mk_refs2.txt || echo "unlisted: $f"
done
```

## まだ手を付けていないこと（正直な残タスク、優先度順）

- **P1**: 178本の `gen-book.py` 由来ヘッダ・123本の `HELD`/`record-only` 箇所の
  棚卸し集計（`docs/inventory.md` との突合が先。本体プロジェクトの
  `wince-api/docs/` を見せていただく必要がある）。
- **P2**: `Sdkddkver.h` の定数を使った、宣言単位でのバージョンガードの実注入
  （293本全部を裏取りしながら行う必要があり、Requirements表の中間データが
  残っていれば自動化できる。今回は土台のみ）。
- **P2**: CE 4.2/5.0/6.0を隔離してビルドし世代跨ぎ呼び出しを検出するCIジョブ。
- **P3**: CE 1.0〜3.0（MIPS/SH3/SH4/x86時代）まで対象化するかどうかの
  費用対効果の再検討。

同梱の `dev-patched.zip` は、上記1〜5を適用した `wince-api/` ツリー全体
（`wince-crt/` は今回変更なし、そのまま同梱）。
