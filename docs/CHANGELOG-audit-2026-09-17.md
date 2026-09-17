# 2026-09-17 監査: NLS 定数の証拠撤回(A)と Enum* NLS 関数の宣言補完(C)

このセッションは「現状報告 → ユーザー決定 → 実施」の順で進めた。
証拠方針(2026-09-17 ユーザー確定):

1. 実装・調査・検証の根拠は公式公開 CE 資料(Microsoft Learn / MSDN /
   公式アーカイブ)のみ。
2. 第三者実装(Wine / ReactOS / CeGCC / w32api / mingw 等)は**照合・裏取り
   目的であっても採用根拠にしない**。比較は混入確認目的のみ。
3. 「Win32 にある=CE にある」式の ABI 安定性推論を根拠にしない。
4. CE 資料で確認できない仕様は推測で追加せず「公式資料で確認できない」
   と明記して held にする。

corpus は kagurasumusun/wince-docs-corpus(66,897 ページ、CE 1.0–6.0 公式
ページ全集)に対して検証した。ページ ID はすべて corpus 実物の確認済み。

---

## A. Winnls.h の LOCALE_* 数値 20 個の撤去(commit 051ee54 の一部撤回)

### A-1. 対象集合の確定(件数の突き合わせ)

commit 051ee54(2026-09-16 "fix header"、監査日付は 2026-09-16)が
include/Winnls.h に追加した #define は **20 個**:

| 分類 | 個数 | 名前 |
|---|---|---|
| LCTYPE 定数 | 18 | LOCALE_SDECIMAL, STHOUSAND, SGROUPING, SCURRENCY, SINTLSYMBOL, SMONDECIMALSEP, SMONTHOUSANDSEP, SMONGROUPING, ICURRDIGITS, IINTLCURRDIGITS, SPOSITIVESIGN, SNEGATIVESIGN, IPOSSIGNPOSN, INEGSIGNPOSN, IPOSSYMPRECEDES, IPOSSEPBYSPACE, INEGSYMPRECEDES, INEGSEPBYSPACE |
| 既定 LCID | 2 | LOCALE_USER_DEFAULT, LOCALE_SYSTEM_DEFAULT |

051ee54 のコメントが書いた「exactly these **19 LCTYPE values** plus the
LOCALE_USER_DEFAULT LCID」は**数え間違い**。正しくは:

- llvm-project `libcxx/src/support/wince/locale_wince.cpp` が消費するのは
  **19 値 = LCTYPE 18 個 + LOCALE_USER_DEFAULT**(ソース実物で 1 呼び出し
  ずつ確認: nls_string 10 + nls_int 8 + LCID 1)。
- LOCALE_SYSTEM_DEFAULT は libcxx では未使用の 20 個目(「usual pair」として
  同時追加されたもの)。
- 過去報告の「未確認19定数」は libcxx 消費分(19)、「20個」は追加 define 総数。
  撤去対象は**追加された 20 個全部**(消費されていない
  LOCALE_SYSTEM_DEFAULT も根拠が同じなので同時に撤去)。

### A-2. 証拠状況(corpus 全検索で確定)

- **LCTYPE Constants ページは 4 世代すべてで名前+説明のみ、数値の印字なし**:
  CE 3.0 `_wcesdk_LCTYPE_Constants` / CE .NET 4.2 `ms921463` /
  CE 5.0 `ms906223` / CE 6.0 `ee491958`。いずれも 16 進値ゼロを実測。
- GetLocaleInfo(`ms905243`)/ SetLocaleInfo(`ms906277`, CE 6.0 `ee491893`,
  CE 3.0 `_wcesdk_Win32_GetLocaleInfo/_wcesdk_Win32_SetLocaleInfo`)は
  LOCALE_SYSTEM_DEFAULT / LOCALE_USER_DEFAULT / LOCALE_NEUTRAL を
  ** predefined value の「名前」として**列挙するが数値を印字しない。
- 数値アンカーは「Language Identifiers and Locales」の LCID 表のみ
  (`ms903928`/CE5.0、`ms921461`/CE4.2、`ee491651`/CE6.0、
  `_wcesdk_Language_Identifiers_and_Locales`/CE3.0):
  実在ロケールの LCID(0x0409 等)と特殊識別子 **0x0000 = Language-Neutral /
  0x0400 = Process Default Language** を印字。
  **0x0400 を LOCALE_USER_DEFAULT という名前に結び付けるページは無い。**
  **0x0800 を LCID 文脈で印字するページは corpus 全体に無い。**
- 「Specifying Locales with NLS」(`_wcesdk_Specifying_Locales_with_NLS` /
  `ms904358`)は LCID/LANGID のビット構成(Reserved 31-20, Sort ID 19-16,
  Language ID 15-0 / Secondary 15-10, Primary 9-0)と
  「LOCALE_NEUTRAL は LOCALE_USER_DEFAULT と同じ」ことを印字するが、
  数値は印字しない。MAKELCID のページ(`ms906226`/`ms921466`/`ee491150`/
  `_wcesdk_win32_MAKELCID`)も SORT_* 定数を名前のみで列挙。

### A-3. 撤去の根拠と処置

051ee54 のコメントは根拠を (i)「Win32/NT 以来固定の NLS 定数 ID 空間」という
ABI 安定性推論、(ii)「Wine include/winnls.h と ReactOS
sdk/include/psdk/winnls.h の完全一致」と明記していた。(i) は方針 3、
(ii) は方針 2 に違反する。値が実機で正しいか否かではなく、
**現行の採用ルールでは採用可能な証拠ではない**ため撤去する
(2026-09-17 ユーザー決定:「いったん証拠不成立として撤去 → 必要なら
独立した公式ソース探索で再採用」。再探索は別タスクであり、
撤去された数値を出発点としない)。

処置:

- `include/Winnls.h`: 20 #define と監査コメントを削除し、証拠状況と撤回
  理由を記した held 記録コメントに置換(削除理由がヘッダから追跡可能)。
- `docs/unpublished-constants.tsv`: 20 行を held として追加
  (pages_mentioning_it は corpus 実測: USER_DEFAULT 61 / SYSTEM_DEFAULT 57 /
  S 系・I 系 4〜8)。
- `docs/CHANGELOG-audit-2026-09-16.md` §7: 原文は歴史記録として残し、
  §8 として撤回記録を追記。
- 再採用の可否判断用に、公式側の唯一の数値アンカー(0x0400 =
  Process Default Language)をコメントと TSV に明記。

下流影響(既知・意図済み): `locale_wince.cpp` は 19 値を消費するため、
再整備(task D)まで cellvm-sdk の Winnls.h に対してコンパイル不能になる。

---

## A-2. Winuser.h の同種問題 — 一覧化のみ(今回は未変更)

2026-09-14 監査(`docs/CHANGELOG-audit-2026-09-14.md`、Winuser.h 2114-2231
付近)が追加した 21 個の数値も、同じ証拠状況にあることを corpus で確認した。
**今回のコミットでは変更しない**(ユーザー指示: 一覧化してから同じ原則で処理)。

| 定数 | 現値 | 公式ページ(実在確認済み) | ページの値印字 | 現行の根拠 |
|---|---|---|---|---|
| WM_MOUSEMOVE | 0x0200 | ms924867(CE4.2)/ aa453885(CE5.0)ほか名前言及49ページ | **なし**(hex 印字ゼロ) | 「WM_MOUSEFIRST と同値」+ WM_MOUSEFIRST 自体が R1 採用値(Winuser.h "WM_ family (14 names; R1)")+ Wine/ReactOS cross-check |
| ATF_TIMEOUTON / ATF_ONOFFFEEDBACK / ATF_AVAILABLE | 0x01/0x02/0x04 | aa452839(CE5.0)/ ms858519(CE4.2)/ ee504120(CE6.0) | **名前+説明のみ** | Wine/ReactOS cross-check(2026-09-14 コメント明記) |
| HCF_HIGHCONTRASTON / HCF_AVAILABLE / HCF_HOTKEYACTIVE / HCF_HOTKEYSOUND / HCF_HOTKEYAVAILABLE | 0x01/0x02/0x04/0x10/0x40 | ms929931(CE5.0)/ ms858526(CE4.2)/ ee499669(CE6.0) | **名前+説明のみ** | 同上 |
| SSF_SOUNDSENTRYON / SSF_AVAILABLE | 0x01/0x02 | ms940347(CE5.0)/ ms858538(CE4.2)/ aa452645 | **名前+説明のみ** | 同上 |
| SKF_STICKYKEYSON / SKF_AVAILABLE / SKF_HOTKEYACTIVE / SKF_HOTKEYSOUND / SKF_AUDIBLEFEEDBACK / SKF_TRISTATE | 0x01/0x02/0x04/0x10/0x40/0x80 | ms940365(CE5.0)/ ms858544(CE4.2)/ ee500762(CE6.0)/ aa931348 | **名前+説明のみ** | 同上 |
| TKF_TOGGLEKEYSON / TKF_AVAILABLE / TKF_HOTKEYACTIVE / TKF_HOTKEYSOUND | 0x01/0x02/0x04/0x10 | aa453748(CE5.0)/ ms858550(CE4.2)/ ee502269(CE6.0) | **名前+説明のみ** | 同上 |

注記:

- WM_MOUSEMOVE は依存が二重に非公式: 等値主張「WM_MOUSEFIRST is
  WM_MOUSEMOVE under another name」自体が CE ページに印字されておらず、
  比較先の WM_MOUSEFIRST=0x0200 も R1(CeGCC 系 w32api)採用値。
- 処理方針(次回): A と同じ原則 — 公式ページが値を印字していないものは
  撤去して held 化(構造体自体は公式ページがメンバー表を印字しているので
  維持)。WM_ 系 R1 採用値の扱いは B(clean-room.md 証拠ポリシー再整理)の
  結論に依存するため、B と同時に処理するのが妥当。

---

## C. Enum* NLS 4 関数の宣言補完(公式資料から直接復元)

### C-1. 発見: 「no compiled prototype」記録は誤り

Winnls.h の intl-book 記録と `docs/undeclared-blocked.tsv` は、
EnumCalendarInfo / EnumDateFormats / EnumSystemLocales / EnumTimeFormats を
「ページが prototype を印字していない(`` 空)」または「*_ENUMPROC を定義する
ページが無い」ため宣言不能としていた。**corpus 実物ページで反証を確認**:

- 4 関数ページはすべて完全なプロトタイプを印字:
  CE 5.0 `ms904721`/`ms904724`/`ms905070`/`ms905077`、
  CE .NET 4.2 `ms919176`/`ms919196`/`ms919238`/`ms919245`、
  CE 6.0 `ee491359`/`ee491363`/`ee491192`/`ee491332`。
  要件行は全世代一致: Header winnls.h / Library Coreloc.lib / CE .NET 4.0+。
- コールバック 4 ページ(`ms904722` EnumCalendarInfoProc / `ms904740`
  EnumDateFormatsProc / `ms904848` EnumLocalesProc / `ms905083`
  EnumTimeFormatsProc)は `BOOL CALLBACK Enum*Proc(LPWSTR lp*String);` を印字し、
  **「Windows CE supports only the Unicode version of this function.」を明記**。
  関数ページの引数説明は「Pointer to an application-defined callback
  function → 該当 Enum*Proc ページ参照」。
- 空 `` 記録は ce-fetch.py の抽出失敗(ハーベスト側の欠陥)であり、
  ページの性質ではなかった。

### C-2. 宣言したもの / held のままのもの

宣言(M139、すべて上記ページの印字からのみ構成):

- `typedef BOOL (CALLBACK *LOCALE_ENUMPROC)(LPWSTR)`(ms905070 + ms904848)
- `typedef BOOL (CALLBACK *DATEFMT_ENUMPROC)(LPWSTR)`(ms904724 + ms904740)
- `typedef BOOL (CALLBACK *TIMEFMT_ENUMPROC)(LPWSTR)`(ms905077 + ms905083)
- `typedef BOOL (CALLBACK *CALINFO_ENUMPROC)(LPWSTR)`(ms904721 + ms904722)
- `EnumSystemLocalesW` + `#define EnumSystemLocales`(ms905070)
- `EnumDateFormatsW` + `#define EnumDateFormats`(ms904724)
- `EnumTimeFormatsW` + `#define EnumTimeFormats`(ms905077)

W 綴りの根拠: コールバックページの Unicode-only 明記 + LPWSTR プロトタイプ
(EnumSystemCodePagesW / GetLocaleInfoW / LCMapStringW と同じ UNICODE_ONLY
規則。gen-doc-def.py に 4 名を追加)。

**held: EnumCalendarInfo(W)** — 引数型 `CALID` と `CALTYPE` を**定義する
ページがどの世代にも存在しない**(カタログ全検索で確認。CAL_* カレンダ
識別子と CALTYPE 定数も名前のみ印字・値なし)。型の定義を Win32 から
移植するのは方針 3 違反のため宣言しない。`docs/undeclared-blocked.tsv` の
該当行を正しい blocked 理由(CALID, CALTYPE)に更新済み
(旧理由は「CALINFO_ENUMPROC 未定義」で、それは M139 で解消)。
CALINFO_ENUMPROC 自体は両方の印字が揃っているため宣言した。

### C-3. def の帰属整理

- `def/coreloc-doc.def`: `EnumDateFormatsW` / `EnumSystemLocalesW` /
  `EnumTimeFormatsW` を追加(ページの Link Library 行 = Coreloc.lib に従う
  tier1 帰属。37 → 40 exports)。
- `def/coredll-doc.def`: 同名の tier2(device-dump 由来)3 エントリを削除。
  放置すると M110 記録のアルファベット順解決で coredll-doc.lib が勝ち、
  文書化された Coreloc.lib 帰属が上書きされてしまうため。
  `EnumCalendarInfoW` は関数が held のため tier2 に**そのまま残置**
  (tier2 全体の扱いは task B の対象)。
- `tools/gen-doc-def.py`:
  - UNICODE_ONLY に 4 名追加(根拠コメント付き)。
  - NOT_EXPORTS に NLS/UI 系コールバック 6 名追加
    (EnumCalendarInfoProc/EnumCodePagesProc/EnumDateFormatsProc/
    EnumLocalesProc/EnumTimeFormatsProc/EnumUILanguagesProc)。
    M121 がコールバックのプロトタイプを宣言した結果、ページ要件行の
    Coreloc.lib を根拠に**アプリ実装のコールバックが import def に
    漏れ出す**ようになった(再生成で実測)。M63 の waveInProc 判断と
    同じ「ユーザー側実装 = import ではない」規則。

### C-4. 発見した既存 drift(今回は未修正、記録のみ)

corpus の rows.json で `gen-doc-def.py` を再生成すると、committed def と
今回の変更範囲外に差分が出る(= committed def は別のハーベスト状態で
生成/手当てされたもの)。実測差分:

- coreloc: committed の `EnumUILanguages`(無印)は、現行ヘッダが
  `EnumUILanguagesW` しか宣言しないため再生成では落ちる。ページ ms905092 は
  Unicode-only 明記も W 綴りも印字しない(LPTSTR のコールバック
  ms905116)ので、UNICODE_ONLY 追加の根拠が無い。ヘッダ側 W 宣言の
  根拠確認と合わせて**別タスクで裁定**する必要。
- ceshell: `BrowseCallbackProc` が再生成で漏れ出す(コールバック漏出の
  同種。NOT_EXPORTS 未登録)。
- accel/acmdwrap/autodial/coreimm 等の増減、ddi_*-doc.def 6 本の欠落、
  device-doc.def の新規出現 — いずれも rows.json の世代差。
- 結論: **今回の def 編集は手当て(3 名追加/3 名削除)で行い、
  全量再生成はしていない**。全量再生成は rows.json の再統一が先。

### C-5. コメント訂正

- Winnls.h intl-book ブロックの「print `` -- recorded verbatim (no compiled
  prototype)」4 行を、訂正説明 + 現在状態(宣言済み / held)に置換。
- Winnls.h M121 ブロックの「五つの Enum* は *_ENUMPROC 未宣言のため未宣言
  のまま」を現在状態(5 typedef すべて宣言済み、5 関数中 4 宣言済み、
  EnumCalendarInfo のみ CALID/CALTYPE で held)に更新。

---

## 検証

- `make check`(hostcheck 380 ヘッダ × 3 世代 / cxxcheck / defcheck)GREEN。
- `gen-doc-def.py` 再生成(dry, /tmp)との coreloc-doc.def 差分が
  「既存 drift の EnumUILanguages 1 行のみ」であることを確認
  (= 手当て 3 名は生成器出力と一致)。
- 撤去 20 定数・新規宣言 7 名とも、ツリー内/include・tests・startup に
  他の使用者が無いことを grep で確認(使用者は llvm-project 側の
  locale_wince.cpp のみ → task D で処理)。

## 残タスク(優先順)

1. **B**: clean-room.md の証拠ポリシー再整理(§3.2 device-dump tier2、
   §4 R1 採用 870 行/26 ヘッダ・M96 1,381 defines・M97 vtable)と、
   def 全量再生成の前提となる rows.json 再統一。
2. **A-2**: Winuser.h 21 値の同原則処理(B の R1 裁定と同時が効率的)。
3. **D**: llvm-project artifact(run 35158153825 / artifact 10471324818,
   `wince-llvm-0b129e08…`, 363MB)展開 → locale_wince.cpp の
   定数非依存バグ(C ロケール localeconv、lc_c ゼロ初期化、_UPPER 系
   MSVC 私有定数、mbsnrtowcs/wcsnrtombs の nullptr 差分 UB、
   __locale_t 所有権、frac_digits=-1、__strtold 精度)修正 → ビルド検証。
   19 値の再採用要否は A の独立公式ソース調査(別タスク)の結論待ち。

## B-1. clean-room.md 証拠ポリシー改訂(commit 0a3a904)

- §3 冒頭に 2026-09-17 改訂バナー: 宣言・数値・型・vtable 順・レイアウト・
  エクスポート名の根拠は公式 CE 資料のみ。第三者ツリー(R1 w32api/mingw/
  Wine/ReactOS 等)は数値・vtable・存在スコープの根拠にも「裏付け」にも
  ならない。許容されるのは汚染チェックと、数値と名目のみを記録する parity
  計測(ツリーに何も持ち込まない)。device dump 等のバイナリ観測は公式文書
  ではない。公式ページが値を印字しない定数は hold(「公式資料で確認できない」)。
- §3.2 device-dump 源を strikethrough で撤去(既存 tier-2 def エントリは
  §7 処分対象の legacy)。toolchain の compiler/ABI 挙動(自社検証
  toolchain の事実)は維持。
- §4 の 2026-09-10 R1 ABI-fact 採用許可を R2 先例と同じ書式で REMOVED 化。
  歴史的文章は可視のまま保持。
- §5.2: *adopted* 経路を新規に対して閉鎖。既存注記は処分まで残す
  (値より先に来歴記録を消すとトレーサビリティが切れるため)。
- 新 §7: legacy 採用の棚卸し表と処分原則 4 項目。
- **B step 2(家族ごとの実処分: M96 1,381 defines、M97 vtables、M99 混合、
  R1 注記 870 行/26 ヘッダ、tier-2 def、Winuser.h 21 値)は未着手。**

## D. locale_wince.cpp 修正と下流パイプライン検証(llvm-project cc5c872a8)

成果物: Actions artifact 10471324818(`wince-llvm-0b129e08…`、363,236,621
bytes、1 回目は 45 秒 max-time で truncation → 再取得して完全一致を確認)を
展開した clang 22.1.8 + lld(bin/+lib/clang のみ、target runtime 無し)。
kagurasumusun/cellvm-build(sysroot/runtimes 組立スクリプト、llvm-project
LLVM-WinCE と cellvm-sdk を submodule 消費)を発見し、実パイプラインで検証。

修正内容(llvm-project LLVM-WinCE、commit cc5c872a8、2 files +116/−107):

1. **__localeconv の NLS クエリ全削除**: GetLocaleInfoW + 19 個の撤回済み
   LOCALE_* 値 + LOCALE_USER_DEFAULT + CP_ACP への依存を除去。wince.h 自身の
   契約(「CE には C ロケールのみ」)通り、C99 7.11.2.1 規定の C ロケール
   lconv(decimal_point="."、他文字列 ""、数値系 CHAR_MAX、llvm-libc の
   MSVC 互換メンバ順に対し名前指定代入、int_p_sign_posn/int_n_sign_posn 含む
   全 14 数値メンバ)を返す。旧コードのバグ 1(C ロケールでデバイス値)・
   バグ 2(lc_c ゼロ初期化 → nullptr/0)・バグ 6(frac_digits=-1)を同時解消。
   TU からの <windows.h>/<winnls.h> 依存も消滅(sysroot は M100 方針で
   Windows.h のみ格納 → 旧 include はどのみち解決不能だった)。
2. **_UPPER 系 MSVC CRT 私有マスク 9 個 → 標準 isw*() 関数**(バグ 3)。
   llvm-libc は _UPPER 等を定義しない。
3. **__strtold → ::strtold、__strtof → ::strtof**(バグ 7)。llvm-libc に
   両実装の存在を確認(libc/src/stdlib/strtold.cpp、strtof.cpp)。
4. **__mbsnrtowcs/__wcsnrtombs の nullptr ポインタ差分 UB 修正**(バグ 4):
   開始ポインタをローカル変数 base に保持(*src は終端変換時に nullptr 化
   されるため、以降の p - *src は UB)。
5. **__locale_t::operator= の lconv ストレージリーク修正**(バグ 5)。

検証(全て実ツールチェーン + 実 sysroot):

- build-wince-sysroot.sh EXIT=0: Akari CRT startup + **117 個の doc 由来
  import library**(libcoredll{,4,6}.a 472KB、libcoreloc.a 9.2KB 含む)が
  cellvm-sdk 99bf610 状態から生成成功。pthread/gmon/posix は C 庫ゲートで
  スキップ(設計通り)。
- build-wince-runtimes.sh EXIT=0: compiler-rt builtins 140/140 ビルド成功、
  libclang_rt.builtins-arm.a インストール。libunwind/libcxxabi/libcxx は
  C 庫マーカー(<sysroot>/include/stdlib.h、llvm-libc 待ち)でゲートスキップ
  — 設計通り。**このゲートのため libcxx は CI で一度もビルドされておらず、
  下記の TU 検証が初の実ビルド検証。**
- C 庫ヘッダは検証専用スタブ(C99/llvm-libc 準拠、.cache/c-stubs、非 commit・
  非インストール)で代替し、runtimes cmake configure(実スクリプトと同じ
  フラグ + CMAKE_POSITION_INDEPENDENT_CODE=OFF)→ compile_commands.json の
  cxx_static コマンドをそのまま実行。
- 修正前ベースライン: fatal 'windows.h' file not found(M100 sysroot は
  Windows.h のみ)→ include 綴り修正版で 33 errors/28 undeclared
  identifiers = 19 LOCALE_* + 9 _UPPER 系マスク(CP_ACP は Winnls.h に
  値が残存していたため解決 — 下記 E-3 参照)。
- 修正後: locale_wince.cpp **EXIT=0、無警告**、IMAGE_FILE_MACHINE_ARM
  (0x1C0) の .o 生成(8,547 bytes、期待 mangling 確認)。主要な消費者
  src/locale.cpp も EXIT=0(4.6s、無診断)→ wince.h 変更の非破壊確認。

## E. 下流検証で発見・修正した cellvm-sdk 側の欠陥(e2e ゲート復活)

1. **Winbase.h DllMain 宣言の M137 回帰**(commit e874b51 で修正):
   M137(8159ce0、corpus 全域スキャン)が ee488450 引用で DllMain を
   AKARI_CE_IMPORT(dllimport)+ AKARI_CE_NAME 付きで >= 0x0600 ブロックに
   宣言し、直下の M132 hold(ms885202「意図的に未宣言」)を上書きしていた。
   x86 では自前 DllMain を定義する全 DLL が -Winconsistent-dllimport で
   コンパイル不能(実測: make e2e i386-pc-wince6.0/e2e_module)。ARM では
   マクロが空のため無症状。公式ページは全世代(CE 3.0 archive
   wcesdkrDllMain「Runs On: Windows CE OS 1.0 and later; Defined in
   Winbase.h」、CE 5.0 ms885202、CE 6.0 ee488450)で本文が「DLL への
   optional な入口」「システムから呼ばれる」「library-defined 関数名の
   placeholder」と明記 → アプリ定義エントリポイントであり coredll import
   ではない(gen-doc-def.py NOT_EXPORTS の Enum*Proc と同原則)。DllMain は
   どの def にも存在しないことを確認済み。宣言を撤去記録に置換し、M132
   注記を全世代カバレッジに拡張。
2. **e2e ゲート配線**(commit 99bf610): (a) e8dad10 が crt/ → startup/ に
   リネームした際、Makefile(CRTDIR=$(CURDIR)/crt)と cellvm-build
   (WINCECRT_SRC=wince-api/crt)が消費する crt symlink が未 commit だった
   → commit(create mode 120000)。(b) 051ee54 が OLE Automation 245 関数を
   Objbase.h → Oleauto.h に移動した際、tests/e2e/e2e_console.c の include が
   未更新で 13 errors(M73a/M73b/M136 の SysAllocString/IsEqualGUID/OleRun/
   CoFreeUnusedLibrariesEx/VariantInit/VariantClear/SafeArrayDestroy/
   LoadTypeLib 等)→ <Oleauto.h> 追加(M100 方針: 使用者が公式綴りを
   明示する)。
3. **新発見(未処理): Winnls.h の Win32-ABI 推定値家族**(Winnls.h:25-50,
   84-103)。「values are the fixed Win32 ABI values」等注記付きの 21 define:
   CP_ACP 0、CP_OEMCP 1、CP_MACCP 2、CP_THREAD_ACP 3、CP_SYMBOL 42、
   CP_UTF7 65000、CP_UTF8 65001、MB_* 4 個、WC_* 4 個、CT_CTYPE1/2/3 1/2/4、
   LCID_INSTALLED/SUPPORTED 1/2、MAX_DEFAULTCHAR 2。これはルール 4(Win32
   定義の CE への推定禁止)に抵触する家族で、§2-2 監査で「名前のみ公式・
   値は非公式」と分類済みだったが A の撤去対象(20 個)には含まれていない。
   処分時に再確認: CSTR_LESS_THAN/CSTR_GREATER_THAN 1/3(ページ印字が確認
   済みなのは CSTR_EQUAL 2 のみ、ms904713)。ページ印字済みで対象外:
   CSTR_EQUAL 2、MAX_LEADBYTES 12(ms904717)。clean-room.md §7 に新行として
   登録、処分は B step 2 待ち。
4. **cellvm-build 側の発見(報告のみ、未修正)**: build-wince-runtimes.sh の
   LIBUNWIND/LIBCXXABI/LIBCXX_ENABLE_PIC=OFF は LLVM 22 で unused(cmake
   警告)、-fPIC は CMAKE_POSITION_INDEPENDENT_CODE 由来で arm-pc-wince では
   unsupported option となり static 構築が不能 → runtimes 段の cmake に
   -DCMAKE_POSITION_INDEPENDENT_CODE=OFF が必要(今回の検証ではその形で
   configure した)。[2/2] がゲートで一度も実行されていなかったため未発見
   だった。cellvm-build への修正 push はユーザー判断待ち。

## 検証(追補 2026-09-17 深夜)

- `make check` EXIT=0(e874b51/99bf610 後)。
- `make e2e WINCECLANG=<artifact clang>` EXIT=0 — 6 triples 全通過
  (arm/i386 × CE 4.2/5.0/6.0、compile + lld-link -wince PE 生成 +
  machine/subsystem/import assertions)。**e2e ゲートは初緑。**
- llvm-project: locale_wince.cpp / locale.cpp の cxx_static TU 検証 EXIT=0
  (上記 D 参照)。

## 残タスク(優先順)

1. **B step 2**: §7 棚卸しの家族別実処分(M96 1,381 defines、M97 vtables、
   M99 混合、R1 注記 870 行/26 ヘッダ、coredll-doc.def tier-2、
   Winuser.h 21 値 = A-2、Winnls.h CP/MB/WC = E-3)と rows.json 再統一。
2. **cellvm-build 修正**(E-4: -DCMAKE_POSITION_INDEPENDENT_CODE=OFF 追加)—
   ユーザー承認待ち。
3. **19 値の再採用要否調査**(A の独立公式ソース調査、別タスク)は
   不必要性が確定: D の修正で locale_wince.cpp は NLS 定数を一切消費し
   なくなった。他の消費者も無い(grep 確認済み)。再採用調査の動機は
   消滅した(必要になれば別途)。

## F. 証拠ポリシー v2 の確立と旧規約の全面撤回(2026-09-17 ユーザー指示・同日第 2 改訂)

前ターンの B-1(clean-room.md v1→公式のみ改訂)を含む**旧規約・旧方針はすべて
撤回**され、新ポリシー v2 が docs/clean-room.md に確立された。要点:

1. **公式 MSDN/MS Learn/Archive/公式 Wayback = 最優先調査対象。**
2. **CeGCC / mingwrt(CeGCC 版)/ w32api(CeGCC 系、kagurasumusun/w32api = R1)**:
   コピーは一切禁止。ただし**参考・比較・値確認対象として許容**(v1 の B-1 改訂で
   全面禁止していたのを転換)。公式ページが値を印字しない定数は、CeGCC 系の値確認で
   根拠付け可能(記録上「value-confirmed」と明示し、公式印字と混同しない)。
3. **mingw / mingw-w64 / mingw-w32 / Wine / ReactOS / w64api / 非 CeGCC w32api**:
   参考も調査も一切禁止(値確認・裏付け・相互チェックも含め完全に対象外)。
4. **Shared Source / Visual Studio 内部・準内部 / Platform Builder**: 一切調査・参考禁止。
5. **公式ではないが大手の信頼できる合法の公開情報**: 調査対象(二次的、非公式と明示)。
6. **非公式・流出に類するもの**: 対象外。device dump 等のバイナリ観測も新ポリシーの
   ソース分類に含まれない(tier-2 def は legacy のまま)。
7. **WinCE 固有機構優先**: WinCE API が提供する機能は WinCE 提供版を使う
   (汎用 C 代替ではない)。**例: NLS — WinCE には NLS がある(GetLocaleInfo/
   SetLocaleInfo/Enum* NLS/CompareString/LCMapString/GetStringType* 等、Coreloc.lib、
   公式ページで文書化、include/Winnls.h が宣言)ので、libc++ WinCE ロケールバック
   エンドはそれに接続する。**

### F-1. この改訂が前ターン記録に与える影響

- **「CE には C ロケールのみ」規約は事実誤りとして撤回。** llvm-project の
  wince.h 冒頭注記とその主張に従った D の localeconv 改作(cc5c872a8)は方針が
  誤りだった。cc5c872a8 のうち標準 C 契約由来の修正(_UPPER 系 MSVC 私有マスク
  除去、strtold/strtof、nullptr 差分 UB、operator= リーク)は v2 下でも有効な
  まま。__localeconv の C ロケール定数実装は**暫定フォールバック**に格下げされ、
  WinCE NLS(GetLocaleInfoW)接続への再改作が次タスク(D-2)。
- **A(d830cab)の撤去自体は維持、根拠は読み替え**: Wine/ReactOS 相互チェックに
  よる根拠付けは v2 でも絶対排除(撤回は正当)。一方「公式のみ」ルール由来の
  再採用制限は v2 で緩和され、20 値は**再検証候補**(公式優先 → CeGCC 系値確認)
  となった。再検証が記録されるまで撤去状態のまま(投機的復元はしない)。
- **A-2(Winuser.h 21 値)と E-3(Winnls.h 21 値)**: 根拠(Wine/ReactOS 相互
  チェック、Win32-ABI 推定)は v2 でも不成立。両家族は v2 §4 の再検証待ち。
  Winuser.h の監査ブロック注記は撤回記録に書き換え済み(値は暫定保持)。
- **M96/M97/M99(R1 採用 870 行/26 ヘッダ、1,381 defines、vtables)**: CeGCC 系の
  値確認が v2 で許容されたため「違反」ではなくなり、**未再検証の legacy** に
  位置づけ直し(公式優先で再検証し、記録を value-confirmed 注記に更新する)。
- **B step 2 の処分原則は v2 §4 の読み替えキーに置き換え**(旧 §7 の処分原則
  1-4 は撤回)。

### F-2. このターンで実施した文書・コメント更新

- docs/clean-room.md: v2 全面改訂(旧版全文の撤回 + 撤回台帳 §5 付き)。
- docs/plan-ce-net.md / docs/parity-target.md / docs/ce-not-nt.md: v2 への
  ポインタ更新バナー。
- include/Winnls.h: 撤回記録の再採用条項を v2 経路に更新。
- include/Winuser.h: 2026-09-14 監査ブロックの Wine/ReactOS 引用と Win32
  不変性論証を撤回(21 値は UNCONFIRMED・暫定保持・再検証候補と明記)。
  これにより include/ 内の Wine/ReactOS 引用は Winnls.h 撤回記録(歴史記述)
  のみとなる。
- llvm-project(LLVM-WinCE、**commit cd55776d2**): wince.h 冒頭契約注記と
  locale_wince.cpp 設計注記を v2 §2 の方針(WinCE NLS 接続、現状態は暫定
  フォールバック)に更新。__setlocale の例外メッセージも撤回済み主張
  (「only the "C" locale exists on Windows CE」)を避けた文言に更新。
  random.cpp の NLS 相互参照コメントも現状化。検証: locale_wince.cpp /
  locale.cpp とも cxx_static TU が EXIT=0(clang 22.1.8、arm-pc-wince、
  cellvm-sdk 由来 sysroot)。
- **新発見(F-3 に追加)**: libcxx の WinCE 系 TU は <windows.h> を小文字で
  include する(random.cpp、atomic.cpp、chrono.cpp、fstream.cpp、
  filesystem/*)。M100 sysroot は Windows.h(文書化綴り)のみ格納するため、
  runtimes [2/2] のゲート解放時に一括で file-not-found になる潜在問題。
  cellvm-build には sysroot/gen-include-aliases.py(消費者側エイリアス生成)
  が既にあり、D-2/runtimes 有効化ターンで「エイリアス生成をパイプラインに
  組み込む」か「libcxx 側を文書化綴りにする」かを決定する。

### F-3. 次タスク(優先順)

1. **D-2**: locale_wince.cpp を WinCE NLS 接続に再改作(GetLocaleInfoW で
   ロケールデータを取得)。前提として 20 値(LCTYPE 18 + LCID 2)の v2 再検証:
   公式ページ(名前のみ)→ R1(kagurasumusun/w32api、CeGCC 系)値確認 →
   記録更新 → Winnls.h への再採用。CP_ACP(WideCharToMultiByte 用)も同様。
   setlocale が受理する CE ロケール名の公式 CRT ページ調査も含む。
2. **A-2/E-3 の再検証**(同原則: 公式優先、CeGCC 系値確認)。
3. **M96/M97/M99/tier-2 の家族別再検証**(v2 §4)。
4. rows.json 再統一(def 一括再生成の前提)。
