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
