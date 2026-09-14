# Header placement audit

Measured at M116 over all three record sets (33,473 rows).  For every
row whose `Header:` row names a header this tree ships, and whose
title identifier is *declared in code* somewhere under `include/`
(comments stripped, so a held comment record does not count), the
audit asks one question: is it in the header the page names?

**8,035** such names.  **1,334 of them, in 65 groups, are not.**

Every one of the 65 documented headers *is* shipped -- the M112 pass
created the missing ones -- so this is not a missing-header problem.
It is a placement problem: the declaration physically lives in a
different file from the one an app is told to include.

## The dominant defect: `Objbase.h` as a catch-all

`Objbase.h` is 4,669 lines and carries declarations whose pages name
nine different COM/OLE headers:

| page says | names in `Objbase.h` |
|---|---|
| `oleauto.h` | 676 |
| `oaidl.h` | 83 |
| `objidl.h` | 54 |
| `ole2.h` | 48 |
| `ocidl.h` | 29 |
| `oleidl.h` | 24 |
| `wtypes.h` | 15 |
| `cesync.h` | 6 |
| `dccole.h` | 4 |

plus strays from `cesync.h`, `dccole.h`, `docobj.h`, `iaccess.h`,
`storemgr.h`, `unknwn.h`, `winuser.h`, `wingdi.h`, `winbase.h` and
`windows.h`.  The receiving headers are thin by comparison
(`Wtypes.h` 6 lines, `Oleauto.h` 19, `D3dmtypes.h` 47, `Ocidl.h` 102,
`Ole2.h` 139, `Oleidl.h` 158, `Oaidl.h` 273, `Objidl.h` 425), which is
the shape of a move that was never made rather than of a deliberate
grouping.

## Groups that are a documented convention, not a defect

`windows.h` -> `wingdi.h` (145 names), `windows.h` -> `winuser.h` (12),
`windows.h` -> `winbase.h` (5) and `kfuncs.h` -> `winbase.h` (11) are
the convention the README records: the CE 5.0/6.0 pages print
`Header: Windows.h` as the umbrella for components that CE 6 gave
their own names, and `kfuncs.h`/`pkfuncs.h` are the OEM/BSP spelling of
what the application layer reaches through `Winbase.h`.  Those groups
are listed below for completeness and should not be "fixed".

## All 65 groups

| page says | actually in | names |
|---|---|---|
| `oleauto.h` | `objbase.h` | 676 |
| `windows.h` | `wingdi.h` | 145 |
| `oaidl.h` | `objbase.h` | 83 |
| `objidl.h` | `objbase.h` | 54 |
| `ole2.h` | `objbase.h` | 48 |
| `d3dmtypes.h` | `d3dm.h` | 47 |
| `rapi.h` | `windbase.h` | 44 |
| `winsock.h` | `winsock2.h` | 31 |
| `ocidl.h` | `objbase.h` | 29 |
| `oleidl.h` | `objbase.h` | 24 |
| `wtypes.h` | `objbase.h` | 15 |
| `externs.h` | `ndis.h` | 13 |
| `windows.h` | `winuser.h` | 12 |
| `winuser.h` | `wingdi.h` | 11 |
| `kfuncs.h` | `winbase.h` | 11 |
| `cesync.h` | `objbase.h` | 6 |
| `winbase.h` | `windbase.h` | 6 |
| `windows.h` | `winbase.h` | 5 |
| `pchannel.h` | `cchannel.h` | 4 |
| `dccole.h` | `objbase.h` | 4 |
| `tlhelp.h` | `tlhelp32.h` | 4 |
| `bt_api.h` | `winsock2.h` | 4 |
| `wincrypt.h` | `winsock2.h` | 3 |
| `wceemul.h` | `imm.h` | 3 |
| `winuser.h` | `winbase.h` | 2 |
| `ddraw.h` | `dvp.h` | 2 |
| `winuser.h` | `objbase.h,shobjidl.h` | 2 |
| `mqmgmt.h` | `mq.h` | 2 |
| `unimodem.h` | `tapi.h` | 2 |
| `commctrl.h` | `commdlg.h` | 2 |
| `winuser.h` | `objbase.h` | 2 |
| `ndis.h` | `externs.h` | 2 |
| `winuser.h` | `windows.h` | 2 |
| `windbase.h` | `winbase.h` | 2 |
| `commctrl.h` | `winuser.h` | 2 |
| `winddi.h` | `gpe.h` | 1 |
| `ws2tcpip.h` | `p2p.h,winsock2.h` | 1 |
| `windows.h` | `objbase.h` | 1 |
| `iaccess.h` | `objbase.h` | 1 |
| `pwindbas.h` | `windbase.h` | 1 |
| `docobj.h` | `objbase.h` | 1 |
| `ws2tcpip.h` | `fwapi.h,winsock2.h` | 1 |
| `storemgr.h` | `objbase.h` | 1 |
| `ndis.h` | `ntddndis.h` | 1 |
| `usbtypes.h` | `usb100.h` | 1 |
| `d3dmcaps.h` | `d3dm.h` | 1 |
| `windows.h` | `windef.h` | 1 |
| `pkfuncs.h` | `windbase.h` | 1 |
| `wingdi.h` | `windows.h` | 1 |
| `kfuncs.h` | `pkfuncs.h` | 1 |
| `wingdi.h` | `objbase.h` | 1 |
| `unknwn.h` | `objbase.h` | 1 |
| `winbase.h` | `objbase.h` | 1 |
| `winbase.h` | `sspi.h` | 1 |
| `wtype.h` | `winnt.h` | 1 |
| `ntcompat.h` | `winbase.h` | 1 |
| `winsock.h` | `windbase.h` | 1 |
| `winbase.h` | `kfuncs.h` | 1 |
| `wininet.h` | `winbase.h` | 1 |
| `ipexport.h` | `icmpapi.h` | 1 |
| `winsock.h` | `iphlpapi.h,winsock2.h,ws2spi.h,ws2tcpip.h` | 1 |
| `snmp.h` | `snmpapi.h` | 1 |
| `pwinreg.h` | `winbase.h` | 1 |
| `dmoreg.h` | `dmo.h` | 1 |
| `bt_buffer.h` | `bt_hcip.h` | 1 |

## Per-name lists

`name (page id)`, grouped as above.  These are the work list: each
move has to carry the declaration's own `#if _WIN32_WCE` condition and
its page citation with it, and the receiving header has to keep
compiling standalone at 0x420/0x500/0x600.

### `oleauto.h` -> `objbase.h` (676)

```
  GetErrorInfo (aa515037)  VarCyFromUI1 (aa518631)  VarCyFromUI2 (aa518802)  VarCyFromUI4 (aa519021)
  VarDateFromBool (aa519022)  VarDateFromCy (aa519023)  VarDateFromDec (aa519024)  VarDateFromDisp (aa519025)
  VarDateFromI1 (aa519026)  VarDateFromI2 (aa519027)  VarDateFromI4 (aa519028)  VarDateFromR4 (aa519029)
  VarDateFromR8 (aa519030)  VarDateFromStr (aa519031)  VarDateFromUdate (aa519032)  VarDateFromUI1 (aa519033)
  VarDateFromUI2 (aa519034)  VarDateFromUI4 (aa519035)  VarDecFromBool (aa519036)  VarDecFromCy (aa519037)
  VarDecFromDate (aa519038)  VarDecFromDisp (aa519039)  VarDecFromI1 (aa519040)  VarDecFromI2 (aa519041)
  VarDecFromI4 (aa519042)  VarDecFromR4 (aa519043)  VarDecFromR8 (aa519044)  VarDecFromStr (aa519045)
  VarDecFromUI1 (aa519046)  VarDecFromUI2 (aa519047)  VarDecFromUI4 (aa519048)  VarI1FromBool (aa519050)
  VarI1FromCy (aa519051)  VarI1FromDate (aa519052)  VarI1FromDec (aa519053)  VarI1FromDisp (aa519054)
  VarI1FromI2 (aa519055)  VarI1FromI4 (aa519056)  VarI1FromR4 (aa519057)  VarI1FromR8 (aa519058)
  VarI1FromStr (aa519059)  VarI1FromUI1 (aa519060)  VarI1FromUI2 (aa519061)  VarI1FromUI4 (aa519062)
  VarI2FromBool (aa519063)  VarI2FromCy (aa519064)  VarI2FromDate (aa519065)  VarI2FromDec (aa519066)
  VarI2FromDisp (aa519067)  VarI2FromI1 (aa519068)  VarI2FromI4 (aa519069)  VarI2FromR4 (aa519070)
  VarI2FromR8 (aa519071)  VarI2FromStr (aa519072)  VarI2FromUI1 (aa519073)  VarI2FromUI2 (aa519074)
  VarI2FromUI4 (aa519075)  VarI4FromBool (aa519076)  VarI4FromCy (aa519077)  VarI4FromDate (aa519078)
  VarI4FromDec (aa519079)  VarI4FromDisp (aa519080)  VarI4FromI1 (aa519081)  VarI4FromI2 (aa519082)
  VarI4FromR4 (aa519083)  VarI4FromR8 (aa519084)  VarI4FromStr (aa519085)  VarI4FromUI1 (aa519086)
  VarI4FromUI2 (aa519087)  VarI4FromUI4 (aa519088)  VariantChangeType (aa519090)  VariantChangeTypeEx (aa519091)
  VariantClear (aa519092)  VariantCopy (aa519093)  VariantCopyInd (aa519094)  VariantInit (aa519095)
  VariantTimeToSystemTime (aa519096)  VarNumFromParseNum (aa519098)  VarParseNumFromStr (aa519099)  VarR4FromBool (aa519100)
  VarR4FromCy (aa519101)  VarR4FromDate (aa519102)  VarR4FromDec (aa519103)  VarR4FromDisp (aa519104)
  VarR4FromI1 (aa519105)  VarR4FromI2 (aa519107)  VarR4FromI4 (aa519109)  VarR4FromR8 (aa519114)
  VarR4FromStr (aa519115)  VarR4FromUI1 (aa519118)  VarR4FromUI2 (aa519121)  VarR4FromUI4 (aa519124)
  VarR8FromBool (aa519126)  VarR8FromCy (aa519130)  VarR8FromDate (aa519132)  VarR8FromDec (aa519134)
  VarR8FromDisp (aa519138)  VarR8FromI1 (aa519141)  BstrFromVector (ms863869)  CreateErrorInfo (ms864392)
  CreateTypeLib2 (ms864403)  DispGetIDsOfNames (ms864421)  DispGetParam (ms864422)  DispInvoke (ms864425)
  DISPPARAMS (ms864426)  LoadRegTypeLib (ms892335)  LoadTypeLib (ms892336)  METHODDATA (ms892346)
  PARAMDATA (ms892619)  RegisterTypeLib (ms892648)  SafeArrayAccessData (ms893348)  SafeArrayAllocData (ms893355)
  SafeArrayAllocDescriptor (ms893361)  SafeArrayCopy (ms893371)  SafeArrayCopyData (ms893377)  SafeArrayCreate (ms893380)
  SafeArrayCreateVector (ms893388)  SafeArrayDestroy (ms893389)  SafeArrayDestroyData (ms893396)  SafeArrayDestroyDescriptor (ms893402)
  SafeArrayGetDim (ms893408)  SafeArrayGetElement (ms893416)  SafeArrayGetElemsize (ms893423)  SafeArrayGetLBound (ms893432)
  SafeArrayGetUBound (ms893434)  SafeArrayLock (ms893435)  SafeArrayPtrOfIndex (ms893436)  SafeArrayPutElement (ms893437)
  SafeArrayRedim (ms893438)  SafeArrayUnaccessData (ms893439)  SafeArrayUnlock (ms893440)  SetErrorInfo (ms893458)
  SysAllocString (ms896470)  SysAllocStringByteLen (ms896471)  SysAllocStringLen (ms896472)  SysFreeString (ms896473)
  SysReAllocString (ms896475)  SysReAllocStringLen (ms896476)  SysStringByteLen (ms896477)  SysStringLen (ms896478)
  SystemTimeToVariantTime (ms896482)  UnRegisterTypeLib (ms896499)  VarBoolFromCy (ms896506)  VarBoolFromDate (ms896507)
  VarBoolFromDec (ms896508)  VarBoolFromDisp (ms896509)  VarBoolFromI1 (ms896510)  VarBoolFromI2 (ms896511)
  VarBoolFromI4 (ms896512)  VarBoolFromR4 (ms896513)  VarBoolFromR8 (ms896514)  VarBoolFromStr (ms896515)
  VarBoolFromUI1 (ms896516)  VarBoolFromUI2 (ms896517)  VarBoolFromUI4 (ms896518)  VarBstrFromBool (ms896519)
  VarBstrFromCy (ms896520)  VarBstrFromDate (ms896521)  VarBstrFromDec (ms896522)  VarBstrFromDisp (ms896523)
  VarBstrFromI1 (ms896524)  VarBstrFromI2 (ms896525)  VarBstrFromI4 (ms896526)  VarBstrFromR4 (ms896527)
  VarBstrFromR8 (ms896528)  VarBstrFromUI1 (ms896529)  VarBstrFromUI2 (ms896530)  VarBstrFromUI4 (ms896531)
  VarCyFromBool (ms896532)  VarCyFromDate (ms896533)  VarCyFromDec (ms896534)  VarCyFromDisp (ms896535)
  VarCyFromI1 (ms896536)  VarCyFromI2 (ms896537)  VarCyFromI4 (ms896538)  VarCyFromR4 (ms896539)
  VarCyFromR8 (ms896540)  VarCyFromStr (ms896541)  VarR8FromI2 (ms896713)  VarR8FromI4 (ms896721)
  VarR8FromR4 (ms896833)  VarR8FromStr (ms896942)  VarR8FromUI1 (ms897055)  VarR8FromUI2 (ms897137)
  VarR8FromUI4 (ms897139)  VarUdateFromDate (ms897142)  VarUI1FromBool (ms897143)  VarUI1FromCy (ms897144)
  VarUI1FromDate (ms897145)  VarUI1FromDec (ms897146)  VarUI1FromDisp (ms897147)  VarUI1FromI1 (ms897148)
  VarUI1FromI2 (ms897149)  VarUI1FromI4 (ms897150)  VarUI1FromR4 (ms897151)  VarUI1FromR8 (ms897153)
  VarUI1FromStr (ms897154)  VarUI1FromUI2 (ms897155)  VarUI1FromUI4 (ms897156)  VarUI2FromBool (ms897157)
  VarUI2FromCy (ms897158)  VarUI2FromDate (ms897159)  VarUI2FromDec (ms897160)  VarUI2FromDisp (ms897161)
  VarUI2FromI1 (ms897162)  VarUI2FromI2 (ms897163)  VarUI2FromI4 (ms897164)  VarUI2FromR4 (ms897165)
  VarUI2FromR8 (ms897166)  VarUI2FromStr (ms897167)  VarUI2FromUI1 (ms897168)  VarUI2FromUI4 (ms897169)
  VarUI4FromBool (ms897170)  VarUI4FromCy (ms897171)  VarUI4FromDate (ms897172)  VarUI4FromDec (ms897173)
  VarUI4FromDisp (ms897174)  VarUI4FromI1 (ms897175)  VarUI4FromI2 (ms897176)  VarUI4FromI4 (ms897177)
  VarUI4FromR4 (ms897178)  VarUI4FromR8 (ms897179)  VarUI4FromStr (ms897180)  VarUI4FromUI1 (ms897181)
  VarUI4FromUI2 (ms897182)  VectorFromBstr (ms897183)  GetErrorInfo (_wcesdk_COM_GetErrorInfo)  DISPPARAMS (_wcesdk_DISPPARAMS)
  VarBoolFromCy (_wcesdk_VarBoolFromCy)  VarBoolFromDate (_wcesdk_VarBoolFromDate)  VarBoolFromDec (_wcesdk_VarBoolFromDec)  VarBoolFromDisp (_wcesdk_VarBoolFromDisp)
  VarBoolFromI1 (_wcesdk_VarBoolFromI1)  VarBoolFromI2 (_wcesdk_VarBoolFromI2)  VarBoolFromI4 (_wcesdk_VarBoolFromI4)  VarBoolFromR4 (_wcesdk_VarBoolFromR4)
  VarBoolFromR8 (_wcesdk_VarBoolFromR8)  VarBoolFromStr (_wcesdk_VarBoolFromStr)  VarBoolFromUI1 (_wcesdk_VarBoolFromUI1)  VarBoolFromUI2 (_wcesdk_VarBoolFromUI2)
  VarBoolFromUI4 (_wcesdk_VarBoolFromUI4)  VarBstrFromBool (_wcesdk_VarBstrFromBool)  VarBstrFromCy (_wcesdk_VarBstrFromCy)  VarBstrFromDate (_wcesdk_VarBstrFromDate)
  VarBstrFromDec (_wcesdk_VarBstrFromDec)  VarBstrFromDisp (_wcesdk_VarBstrFromDisp)  VarBstrFromI1 (_wcesdk_VarBstrFromI1)  VarBstrFromI2 (_wcesdk_VarBstrFromI2)
  VarBstrFromI4 (_wcesdk_VarBstrFromI4)  VarBstrFromR4 (_wcesdk_VarBstrFromR4)  VarBstrFromR8 (_wcesdk_VarBstrFromR8)  VarBstrFromUI1 (_wcesdk_VarBstrFromUI1)
  VarBstrFromUI2 (_wcesdk_VarBstrFromUI2)  VarBstrFromUI4 (_wcesdk_VarBstrFromUI4)  VarCyFromBool (_wcesdk_VarCyFromBool)  VarCyFromDate (_wcesdk_VarCyFromDate)
  VarCyFromDec (_wcesdk_VarCyFromDec)  VarCyFromDisp (_wcesdk_VarCyFromDisp)  VarCyFromI1 (_wcesdk_VarCyFromI1)  VarCyFromI2 (_wcesdk_VarCyFromI2)
  VarCyFromI4 (_wcesdk_VarCyFromI4)  VarCyFromR4 (_wcesdk_VarCyFromR4)  VarCyFromR8 (_wcesdk_VarCyFromR8)  VarCyFromStr (_wcesdk_VarCyFromStr)
  VarCyFromUI1 (_wcesdk_VarCyFromUI1)  VarCyFromUI2 (_wcesdk_VarCyFromUI2)  VarCyFromUI4 (_wcesdk_VarCyFromUI4)  VarDateFromBool (_wcesdk_VarDateFromBool)
  VarDateFromCy (_wcesdk_VarDateFromCy)  VarDateFromDec (_wcesdk_VarDateFromDec)  VarDateFromDisp (_wcesdk_VarDateFromDisp)  VarDateFromI1 (_wcesdk_VarDateFromI1)
  VarDateFromI2 (_wcesdk_VarDateFromI2)  VarDateFromI4 (_wcesdk_VarDateFromI4)  VarDateFromR4 (_wcesdk_VarDateFromR4)  VarDateFromR8 (_wcesdk_VarDateFromR8)
  VarDateFromStr (_wcesdk_VarDateFromStr)  VarDateFromUI1 (_wcesdk_VarDateFromUI1)  VarDateFromUI2 (_wcesdk_VarDateFromUI2)  VarDateFromUI4 (_wcesdk_VarDateFromUI4)
  VarDateFromUdate (_wcesdk_VarDateFromUdate)  VarDecFromBool (_wcesdk_VarDecFromBool)  VarDecFromCy (_wcesdk_VarDecFromCy)  VarDecFromDate (_wcesdk_VarDecFromDate)
  VarDecFromDisp (_wcesdk_VarDecFromDisp)  VarDecFromI1 (_wcesdk_VarDecFromI1)  VarDecFromI2 (_wcesdk_VarDecFromI2)  VarDecFromI4 (_wcesdk_VarDecFromI4)
  VarDecFromR4 (_wcesdk_VarDecFromR4)  VarDecFromR8 (_wcesdk_VarDecFromR8)  VarDecFromStr (_wcesdk_VarDecFromStr)  VarDecFromUI1 (_wcesdk_VarDecFromUI1)
  VarDecFromUI2 (_wcesdk_VarDecFromUI2)  VarDecFromUI4 (_wcesdk_VarDecFromUI4)  VarI1FromBool (_wcesdk_VarI1FromBool)  VarI1FromCy (_wcesdk_VarI1FromCy)
  VarI1FromDate (_wcesdk_VarI1FromDate)  VarI1FromDec (_wcesdk_VarI1FromDec)  VarI1FromDisp (_wcesdk_VarI1FromDisp)  VarI1FromI2 (_wcesdk_VarI1FromI2)
  VarI1FromI4 (_wcesdk_VarI1FromI4)  VarI1FromR4 (_wcesdk_VarI1FromR4)  VarI1FromR8 (_wcesdk_VarI1FromR8)  VarI1FromStr (_wcesdk_VarI1FromStr)
  VarI1FromUI1 (_wcesdk_VarI1FromUI1)  VarI1FromUI2 (_wcesdk_VarI1FromUI2)  VarI1FromUI4 (_wcesdk_VarI1FromUI4)  VarI2FromBool (_wcesdk_VarI2FromBool)
  VarI2FromCy (_wcesdk_VarI2FromCy)  VarI2FromDate (_wcesdk_VarI2FromDate)  VarI2FromDec (_wcesdk_VarI2FromDec)  VarI2FromDisp (_wcesdk_VarI2FromDisp)
  VarI2FromI1 (_wcesdk_VarI2FromI1)  VarI2FromI4 (_wcesdk_VarI2FromI4)  VarI2FromR4 (_wcesdk_VarI2FromR4)  VarI2FromR8 (_wcesdk_VarI2FromR8)
  VarI2FromStr (_wcesdk_VarI2FromStr)  VarI2FromUI1 (_wcesdk_VarI2FromUI1)  VarI2FromUI2 (_wcesdk_VarI2FromUI2)  VarI2FromUI4 (_wcesdk_VarI2FromUI4)
  VarI4FromBool (_wcesdk_VarI4FromBool)  VarI4FromCy (_wcesdk_VarI4FromCy)  VarI4FromDate (_wcesdk_VarI4FromDate)  VarI4FromDec (_wcesdk_VarI4FromDec)
  VarI4FromDisp (_wcesdk_VarI4FromDisp)  VarI4FromI1 (_wcesdk_VarI4FromI1)  VarI4FromI2 (_wcesdk_VarI4FromI2)  VarI4FromR4 (_wcesdk_VarI4FromR4)
  VarI4FromR8 (_wcesdk_VarI4FromR8)  VarI4FromStr (_wcesdk_VarI4FromStr)  VarI4FromUI1 (_wcesdk_VarI4FromUI1)  VarI4FromUI2 (_wcesdk_VarI4FromUI2)
  VarI4FromUI4 (_wcesdk_VarI4FromUI4)  VarR4FromBool (_wcesdk_VarR4FromBool)  VarR4FromCy (_wcesdk_VarR4FromCy)  VarR4FromDate (_wcesdk_VarR4FromDate)
  VarR4FromDec (_wcesdk_VarR4FromDec)  VarR4FromDisp (_wcesdk_VarR4FromDisp)  VarR4FromI1 (_wcesdk_VarR4FromI1)  VarR4FromI2 (_wcesdk_VarR4FromI2)
  VarR4FromI4 (_wcesdk_VarR4FromI4)  VarR4FromR8 (_wcesdk_VarR4FromR8)  VarR4FromStr (_wcesdk_VarR4FromStr)  VarR4FromUI1 (_wcesdk_VarR4FromUI1)
  VarR4FromUI2 (_wcesdk_VarR4FromUI2)  VarR4FromUI4 (_wcesdk_VarR4FromUI4)  VarR8FromBool (_wcesdk_VarR8FromBool)  VarR8FromCy (_wcesdk_VarR8FromCy)
  VarR8FromDate (_wcesdk_VarR8FromDate)  VarR8FromDec (_wcesdk_VarR8FromDec)  VarR8FromDisp (_wcesdk_VarR8FromDisp)  VarR8FromI1 (_wcesdk_VarR8FromI1)
  VarR8FromI2 (_wcesdk_VarR8FromI2)  VarR8FromI4 (_wcesdk_VarR8FromI4)  VarR8FromR4 (_wcesdk_VarR8FromR4)  VarR8FromStr (_wcesdk_VarR8FromStr)
  VarR8FromUI1 (_wcesdk_VarR8FromUI1)  VarR8FromUI2 (_wcesdk_VarR8FromUI2)  VarR8FromUI4 (_wcesdk_VarR8FromUI4)  VarUI1FromBool (_wcesdk_VarUI1FromBool)
  VarUI1FromCy (_wcesdk_VarUI1FromCy)  VarUI1FromDate (_wcesdk_VarUI1FromDate)  VarUI1FromDec (_wcesdk_VarUI1FromDec)  VarUI1FromDisp (_wcesdk_VarUI1FromDisp)
  VarUI1FromI1 (_wcesdk_VarUI1FromI1)  VarUI1FromI2 (_wcesdk_VarUI1FromI2)  VarUI1FromI4 (_wcesdk_VarUI1FromI4)  VarUI1FromR4 (_wcesdk_VarUI1FromR4)
  VarUI1FromR8 (_wcesdk_VarUI1FromR8)  VarUI1FromStr (_wcesdk_VarUI1FromStr)  VarUI1FromUI2 (_wcesdk_VarUI1FromUI2)  VarUI1FromUI4 (_wcesdk_VarUI1FromUI4)
  VarUI2FromBool (_wcesdk_VarUI2FromBool)  VarUI2FromCy (_wcesdk_VarUI2FromCy)  VarUI2FromDate (_wcesdk_VarUI2FromDate)  VarUI2FromDec (_wcesdk_VarUI2FromDec)
  VarUI2FromDisp (_wcesdk_VarUI2FromDisp)  VarUI2FromI1 (_wcesdk_VarUI2FromI1)  VarUI2FromI2 (_wcesdk_VarUI2FromI2)  VarUI2FromI4 (_wcesdk_VarUI2FromI4)
  VarUI2FromR4 (_wcesdk_VarUI2FromR4)  VarUI2FromStr (_wcesdk_VarUI2FromStr)  VarUI2FromUI1 (_wcesdk_VarUI2FromUI1)  VarUI2FromUI4 (_wcesdk_VarUI2FromUI4)
  VarUI4FromBool (_wcesdk_VarUI4FromBool)  VarUI4FromCy (_wcesdk_VarUI4FromCy)  VarUI4FromDate (_wcesdk_VarUI4FromDate)  VarUI4FromDec (_wcesdk_VarUI4FromDec)
  VarUI4FromDisp (_wcesdk_VarUI4FromDisp)  VarUI4FromI1 (_wcesdk_VarUI4FromI1)  VarUI4FromI2 (_wcesdk_VarUI4FromI2)  VarUI4FromI4 (_wcesdk_VarUI4FromI4)
  VarUI4FromR4 (_wcesdk_VarUI4FromR4)  VarUI4FromR8 (_wcesdk_VarUI4FromR8)  VarUI4FromStr (_wcesdk_VarUI4FromStr)  VarUI4FromUI1 (_wcesdk_VarUI4FromUI1)
  VarUI4FromUI2 (_wcesdk_VarUI4FromUI2)  VarUdateFromDate (_wcesdk_VarUdateFromDate)  BstrFromVector (_wcesdk_oa96_BstrFromVector)  CreateErrorInfo (_wcesdk_oa96_CreateErrorInfo)
  CreateTypeLib2 (_wcesdk_oa96_CreateTypeLib2)  DispGetIDsOfNames (_wcesdk_oa96_DispGetIDsOfNames)  DispGetParam (_wcesdk_oa96_DispGetParam)  DispInvoke (_wcesdk_oa96_DispInvoke)
  LoadRegTypeLib (_wcesdk_oa96_LoadRegTypeLib)  LoadTypeLib (_wcesdk_oa96_LoadTypeLib)  METHODDATA (_wcesdk_oa96_METHODDATA)  PARAMDATA (_wcesdk_oa96_PARAMDATA)
  RegisterTypeLib (_wcesdk_oa96_RegisterTypeLib)  SafeArrayAccessData (_wcesdk_oa96_SafeArrayAccessData)  SafeArrayAllocData (_wcesdk_oa96_SafeArrayAllocData)  SafeArrayAllocDescriptor (_wcesdk_oa96_SafeArrayAllocDescriptor)
  SafeArrayCopy (_wcesdk_oa96_SafeArrayCopy)  SafeArrayCopyData (_wcesdk_oa96_SafeArrayCopyData)  SafeArrayCreate (_wcesdk_oa96_SafeArrayCreate)  SafeArrayCreateVector (_wcesdk_oa96_SafeArrayCreateVector)
  SafeArrayDestroy (_wcesdk_oa96_SafeArrayDestroy)  SafeArrayDestroyData (_wcesdk_oa96_SafeArrayDestroyData)  SafeArrayDestroyDescriptor (_wcesdk_oa96_SafeArrayDestroyDescriptor)  SafeArrayGetDim (_wcesdk_oa96_SafeArrayGetDim)
  SafeArrayGetElement (_wcesdk_oa96_SafeArrayGetElement)  SafeArrayGetElemsize (_wcesdk_oa96_SafeArrayGetElemsize)  SafeArrayGetLBound (_wcesdk_oa96_SafeArrayGetLBound)  SafeArrayGetUBound (_wcesdk_oa96_SafeArrayGetUBound)
  SafeArrayLock (_wcesdk_oa96_SafeArrayLock)  SafeArrayPtrOfIndex (_wcesdk_oa96_SafeArrayPtrOfIndex)  SafeArrayPutElement (_wcesdk_oa96_SafeArrayPutElement)  SafeArrayRedim (_wcesdk_oa96_SafeArrayRedim)
  SafeArrayUnaccessData (_wcesdk_oa96_SafeArrayUnaccessData)  SafeArrayUnlock (_wcesdk_oa96_SafeArrayUnlock)  SysAllocString (_wcesdk_oa96_SysAllocString)  SysAllocStringByteLen (_wcesdk_oa96_SysAllocStringByteLen)
  SysAllocStringLen (_wcesdk_oa96_SysAllocStringLen)  SysFreeString (_wcesdk_oa96_SysFreeString)  SysReAllocString (_wcesdk_oa96_SysReAllocString)  SysReAllocStringLen (_wcesdk_oa96_SysReAllocStringLen)
  SysStringByteLen (_wcesdk_oa96_SysStringByteLen)  SysStringLen (_wcesdk_oa96_SysStringLen)  SystemTimeToVariantTime (_wcesdk_oa96_SystemTimeToVariantTime)  UnRegisterTypeLib (_wcesdk_oa96_UnRegisterTypeLib)
  VarNumFromParseNum (_wcesdk_oa96_VarNumFromParseNum)  VarParseNumFromStr (_wcesdk_oa96_VarParseNumFromStr)  VariantChangeType (_wcesdk_oa96_VariantChangeType)  VariantChangeTypeEx (_wcesdk_oa96_VariantChangeTypeEx)
  VariantClear (_wcesdk_oa96_VariantClear)  VariantCopy (_wcesdk_oa96_VariantCopy)  VariantCopyInd (_wcesdk_oa96_VariantCopyInd)  VariantInit (_wcesdk_oa96_VariantInit)
  VariantTimeToSystemTime (_wcesdk_oa96_VariantTimeToSystemTime)  VectorFromBstr (_wcesdk_oa96_VectorFromBstr)  BstrFromVector (ms886153)  CreateErrorInfo (ms886949)
  CreateTypeLib2 (ms886956)  DispGetIDsOfNames (ms886965)  DispGetParam (ms886966)  DispInvoke (ms886969)
  DISPPARAMS (ms886970)  GetErrorInfo (ms886989)  LoadRegTypeLib (ms890751)  LoadTypeLib (ms890755)
  METHODDATA (ms890768)  PARAMDATA (ms891225)  RegisterTypeLib (ms891239)  SafeArrayAccessData (ms891243)
  SafeArrayAllocData (ms891244)  SafeArrayAllocDescriptor (ms891245)  SafeArrayCopy (ms891246)  SafeArrayCopyData (ms891247)
  SafeArrayCreate (ms891248)  SafeArrayCreateVector (ms891250)  SafeArrayDestroy (ms891251)  SafeArrayDestroyData (ms891252)
  SafeArrayDestroyDescriptor (ms891253)  SafeArrayGetDim (ms891254)  SafeArrayGetElement (ms891255)  SafeArrayGetElemsize (ms891256)
  SafeArrayGetLBound (ms891257)  SafeArrayGetUBound (ms891258)  SafeArrayLock (ms891259)  SafeArrayPtrOfIndex (ms891260)
  SafeArrayPutElement (ms891261)  SafeArrayRedim (ms891262)  SafeArrayUnaccessData (ms891263)  SafeArrayUnlock (ms891264)
  SetErrorInfo (ms891266)  SysAllocString (ms891285)  SysAllocStringByteLen (ms891286)  SysAllocStringLen (ms891287)
  SysFreeString (ms891288)  SysReAllocString (ms891290)  SysReAllocStringLen (ms891291)  SysStringByteLen (ms891292)
  SysStringLen (ms891293)  SystemTimeToVariantTime (ms891294)  UnRegisterTypeLib (ms891303)  VarBoolFromCy (ms891305)
  VarBoolFromDate (ms891306)  VarBoolFromDec (ms891307)  VarBoolFromDisp (ms891308)  VarBoolFromI1 (ms891309)
  VarBoolFromI2 (ms891310)  VarBoolFromI4 (ms891311)  VarBoolFromR4 (ms891312)  VarBoolFromR8 (ms891313)
  VarBoolFromStr (ms891314)  VarBoolFromUI1 (ms891315)  VarBoolFromUI2 (ms891316)  VarBoolFromUI4 (ms891317)
  VarBstrFromBool (ms891318)  VarBstrFromCy (ms891319)  VarBstrFromDate (ms891320)  VarBstrFromDec (ms891321)
  VarBstrFromDisp (ms891322)  VarBstrFromI1 (ms891323)  VarBstrFromI2 (ms891324)  VarBstrFromI4 (ms891325)
  VarBstrFromR4 (ms891326)  VarBstrFromR8 (ms891327)  VarBstrFromUI1 (ms891328)  VarBstrFromUI2 (ms891329)
  VarBstrFromUI4 (ms891330)  VarCyFromBool (ms891331)  VarCyFromDate (ms891465)  VarCyFromDec (ms891479)
  VarCyFromDisp (ms891485)  VarCyFromI1 (ms891500)  VarCyFromI2 (ms891507)  VarCyFromI4 (ms891510)
  VarCyFromR4 (ms891516)  VarCyFromR8 (ms891523)  VarCyFromStr (ms891532)  VarCyFromUI1 (ms891539)
  VarCyFromUI2 (ms891548)  VarCyFromUI4 (ms891557)  VarDateFromBool (ms891564)  VarDateFromCy (ms891578)
  VarDateFromDec (ms891584)  VarDateFromDisp (ms891593)  VarDateFromI1 (ms891600)  VarDateFromI2 (ms891606)
  VarDateFromI4 (ms891609)  VarDateFromR4 (ms891610)  VarDateFromR8 (ms891611)  VarDateFromStr (ms891612)
  VarDateFromUdate (ms891613)  VarDateFromUI1 (ms891614)  VarDateFromUI2 (ms891615)  VarDateFromUI4 (ms891616)
  VarDecFromBool (ms891617)  VarDecFromCy (ms891618)  VarDecFromDate (ms891619)  VarDecFromDisp (ms891620)
  VarDecFromI1 (ms891621)  VarDecFromI2 (ms891622)  VarDecFromI4 (ms891623)  VarDecFromR4 (ms891624)
  VarDecFromR8 (ms891625)  VarDecFromStr (ms891626)  VarDecFromUI1 (ms891627)  VarDecFromUI2 (ms891628)
  VarDecFromUI4 (ms891629)  VarI1FromBool (ms891631)  VarI1FromCy (ms891632)  VarI1FromDate (ms891633)
  VarI1FromDec (ms891634)  VarI1FromDisp (ms891635)  VarI1FromI2 (ms891636)  VarI1FromI4 (ms891637)
  VarI1FromR4 (ms891638)  VarI1FromR8 (ms891639)  VarI1FromStr (ms891640)  VarI1FromUI1 (ms891641)
  VarI1FromUI2 (ms891642)  VarI1FromUI4 (ms891643)  VarI2FromBool (ms891644)  VarI2FromCy (ms891645)
  VarI2FromDate (ms891646)  VarI2FromDec (ms891647)  VarI2FromDisp (ms891648)  VarI2FromI1 (ms891649)
  VarI2FromI4 (ms891650)  VarI2FromR4 (ms891651)  VarI2FromR8 (ms891652)  VarI2FromStr (ms891653)
  VarI2FromUI1 (ms891654)  VarI2FromUI2 (ms891655)  VarI2FromUI4 (ms891656)  VarI4FromBool (ms891657)
  VarI4FromCy (ms891658)  VarI4FromDate (ms891659)  VarI4FromDec (ms891660)  VarI4FromDisp (ms891661)
  VarI4FromI1 (ms891662)  VarI4FromI2 (ms891663)  VarI4FromR4 (ms891664)  VarI4FromR8 (ms891665)
  VarI4FromStr (ms891667)  VarI4FromUI1 (ms891668)  VarI4FromUI2 (ms891669)  VarI4FromUI4 (ms891670)
  VariantChangeType (ms891671)  VariantChangeTypeEx (ms891672)  VariantClear (ms891673)  VariantCopy (ms891674)
  VariantCopyInd (ms891675)  VariantInit (ms891676)  VariantTimeToSystemTime (ms891677)  VarNumFromParseNum (ms891680)
  VarParseNumFromStr (ms891681)  VarR4FromBool (ms891682)  VarR4FromCy (ms891683)  VarR4FromDate (ms891684)
  VarR4FromDec (ms891685)  VarR4FromDisp (ms891686)  VarR4FromI1 (ms891687)  VarR4FromI2 (ms891688)
  VarR4FromI4 (ms891689)  VarR4FromR8 (ms891690)  VarR4FromStr (ms891691)  VarR4FromUI1 (ms891700)
  VarR4FromUI2 (ms891773)  VarR4FromUI4 (ms891776)  VarR8FromBool (ms891785)  VarR8FromCy (ms891790)
  VarR8FromDate (ms891796)  VarR8FromDec (ms891802)  VarR8FromDisp (ms891810)  VarR8FromI1 (ms891812)
  VarR8FromI2 (ms891816)  VarR8FromI4 (ms891823)  VarR8FromR4 (ms891825)  VarR8FromStr (ms891831)
  VarR8FromUI1 (ms891836)  VarR8FromUI2 (ms891839)  VarR8FromUI4 (ms891846)  VarUdateFromDate (ms891856)
  VarUI1FromBool (ms891863)  VarUI1FromCy (ms891867)  VarUI1FromDate (ms891869)  VarUI1FromDec (ms891876)
  VarUI1FromDisp (ms891887)  VarUI1FromI1 (ms891893)  VarUI1FromI2 (ms891901)  VarUI1FromI4 (ms891905)
  VarUI1FromR4 (ms891912)  VarUI1FromR8 (ms891915)  VarUI1FromStr (ms891922)  VarUI1FromUI2 (ms891926)
  VarUI1FromUI4 (ms891930)  VarUI2FromBool (ms891935)  VarUI2FromCy (ms891940)  VarUI2FromDate (ms891947)
  VarUI2FromDec (ms891951)  VarUI2FromDisp (ms891955)  VarUI2FromI1 (ms891961)  VarUI2FromI2 (ms891966)
  VarUI2FromI4 (ms891970)  VarUI2FromR4 (ms891981)  VarUI2FromR8 (ms891986)  VarUI2FromStr (ms891993)
  VarUI2FromUI1 (ms891998)  VarUI2FromUI4 (ms892004)  VarUI4FromBool (ms892011)  VarUI4FromCy (ms892020)
  VarUI4FromDate (ms892026)  VarUI4FromDec (ms892103)  VarUI4FromDisp (ms892107)  VarUI4FromI1 (ms892116)
  VarUI4FromI2 (ms892117)  VarUI4FromI4 (ms892118)  VarUI4FromR4 (ms892119)  VarUI4FromR8 (ms892120)
  VarUI4FromStr (ms892121)  VarUI4FromUI1 (ms892122)  VarUI4FromUI2 (ms892123)  VectorFromBstr (ms892124)
```

### `windows.h` -> `wingdi.h` (145)

```
  EnumDisplayMonitors (aa451688)  GetMonitorInfo (aa451738)  AlphaBlend (aa452850)  BitBlt (aa452879)
  BITMAP (aa452880)  BITMAPCOREHEADER (aa452881)  BITMAPCOREINFO (aa452882)  BITMAPFILEHEADER (aa452883)
  BITMAPINFO (aa452884)  BITMAPINFOHEADER (aa452885)  BLENDFUNCTION (aa452889)  DeleteDC (aa452930)
  DeleteObject (aa452933)  DEVMODE (aa452943)  DIBSECTION (aa452953)  DISPLAY_DEVICE (aa452957)
  DrawEdge (aa452968)  DrawFocusRect (aa452969)  Ellipse (aa452997)  EnumDisplayDevices (aa453048)
  EnumDisplaySettings (aa453049)  EqualRgn (aa453056)  ExcludeClipRect (aa453058)  ExtCreateRegion (aa453061)
  ExtEscape (aa453063)  FillRect (aa453067)  FillRgn (aa453068)  GetLayout (aa453133)
  GetNearestColor (aa453140)  GetNearestPaletteIndex (aa453141)  GetObjectType (aa453148)  GetPaletteEntries (aa453151)
  GetPixel (aa453153)  GetRegionData (aa453157)  GetRgnBox (aa453159)  GetROP2 (aa453160)
  GetRValue (aa453161)  GetStockObject (aa453164)  GetStretchBltMode (aa453165)  GetSysColorBrush (aa453168)
  GetSystemPaletteEntries (aa453171)  GradientFill (aa453192)  GRADIENT_RECT (aa453193)  LineTo (aa453296)
  LOGBRUSH (aa453418)  LOGPALETTE (aa453419)  LOGPEN (aa453420)  PtInRegion (aa453602)
  RealizePalette (aa453638)  SetPixel (aa453646)  SetRectRgn (aa453650)  SetROP2 (aa453651)
  SetStretchBltMode (aa453655)  SetViewportOrgEx (aa453660)  TransparentBlt (aa453778)  TransparentImage (aa453779)
  TRIVERTEX (aa453818)  GetViewportExtEx (aa453949)  GetViewportOrgEx (aa453950)  GetWindowExtEx (aa453951)
  GetWindowOrgEx (aa453952)  OffsetViewportOrgEx (aa453953)  SetWindowOrgEx (aa453954)  GetFontData (aa520325)
  ABC (ms901108)  GetTextAlign (ms901132)  GetTextColor (ms901134)  SetTextAlign (ms901143)
  SetTextColor (ms901145)  ChangeDisplaySettingsEx (ms908108)  CreateBitmap (ms908163)  CreateCompatibleBitmap (ms908165)
  CreateCompatibleDC (ms908166)  CreateDIBPatternBrushPt (ms908173)  CreateDIBSection (ms908174)  CreatePalette (ms908178)
  CreatePatternBrush (ms908179)  CreatePen (ms908180)  CreatePenIndirect (ms908181)  CreateRectRgn (ms908184)
  CreateRectRgnIndirect (ms908185)  CreateSolidBrush (ms908187)  IntersectClipRect (ms909855)  InvalidateRgn (ms909858)
  InvertRect (ms909859)  MaskBlt (ms911792)  OffsetRgn (ms911892)  PALETTEENTRY (ms911913)
  PatBlt (ms911916)  Polygon (ms911933)  Polyline (ms911934)  Rectangle (ms912947)
  RectInRegion (ms913051)  RectVisible (ms913070)  RedrawWindow (ms913080)  ValidateRgn (ms914092)
  CombineRgn (ms928608)  GetBkColor (ms929205)  GetBkMode (ms929206)  GetBValue (ms929207)
  GetClipBox (ms929219)  GetClipRgn (ms929221)  GetCurrentObject (ms929223)  GetCurrentPositionEx (ms929224)
  GetDeviceCaps (ms929230)  GetDIBColorTable (ms929232)  GetGValue (ms929246)  MoveToEx (ms931457)
  MonitorFromPoint (ms932198)  MonitorFromRect (ms932208)  MonitorFromWindow (ms932212)  MONITORINFO (ms932213)
  SelectClipRgn (ms932714)  SelectObject (ms932715)  SelectPalette (ms932716)  OUTLINETEXTMETRICW (ms934025)
  RestoreDC (ms939800)  RGBQUAD (ms939815)  RGBTRIPLE (ms939824)  RGNDATA (ms939837)
  RGNDATAHEADER (ms939847)  RoundRect (ms939867)  SaveDC (ms939894)  SetBitmapBits (ms939987)
  SetBkColor (ms939988)  SetBkMode (ms939989)  SetBrushOrgEx (ms940010)  SetDIBColorTable (ms940018)
  SetDIBitsToDevice (ms940019)  SetLayout (ms940026)  SetPaletteEntries (ms940028)  StretchBlt (ms940373)
  StretchDIBits (ms940374)  GetTextColor (ms900694)  SetTextColor (ms900716)  GetTextAlign (ms900729)
  SetTextAlign (ms900733)  ABC (ms900753)  EnumDisplayMonitors (ms921262)  GetMonitorInfo (ms921263)
  MonitorFromPoint (ms921265)  MonitorFromRect (ms921266)  MonitorFromWindow (ms921267)  MONITORINFO (ms921268)
  MONITORINFOEX (ms921269)
```

### `oaidl.h` -> `objbase.h` (83)

```
  EXCEPINFO (aa514943)  FUNCDESC (aa515005)  FUNCFLAGS (aa515008)  FUNCKIND (aa515010)
  IDLDESC (aa515591)  VARDESC (aa519049)  VARKIND (aa519097)  FreePropVariantArray (aa519255)
  PROPVARIANT (aa519284)  PropVariantClear (aa519285)  PropVariantCopy (aa519286)  ARRAYDESC (ms863667)
  BINDPTR (ms863861)  CALLCONV (ms863871)  CUSTDATA (ms864406)  CUSTDATAITEM (ms864407)
  DESCKIND (ms864416)  ELEMDESC (ms864455)  INVOKEKIND (ms882878)  PARAMDESC (ms892620)
  SAFEARRAY (ms893344)  SAFEARRAYBOUND (ms893364)  SYSKIND (ms896474)  TLIBATTR (ms896486)
  TYPEATTR (ms896493)  TYPEDESC (ms896494)  TYPEFLAGS (ms896495)  TYPEKIND (ms896496)
  CALLCONV (_wcesdk_CALLCONV)  DESCKIND (_wcesdk_DESCKIND)  ELEMDESC (_wcesdk_ELEMDESC)  FUNCKIND (_wcesdk_FUNCKIND)
  INVOKEKIND (_wcesdk_INVOKEKIND)  TYPEKIND (_wcesdk_TYPEKIND)  IAdviseSink (_wcesdk_com_IAdviseSink)  IEnumSTATDATA (_wcesdk_com_IEnumSTATDATA)
  ARRAYDESC (_wcesdk_oa96_ARRAYDESC)  BINDPTR (_wcesdk_oa96_BINDPTR)  CUSTDATA (_wcesdk_oa96_CUSTDATA)  CUSTDATAITEM (_wcesdk_oa96_CUSTDATAITEM)
  EXCEPINFO (_wcesdk_oa96_EXCEPINFO)  FUNCDESC (_wcesdk_oa96_FUNCDESC)  ICreateErrorInfo (_wcesdk_oa96_ICreateErrorInfo_interface)  ICreateTypeInfo (_wcesdk_oa96_ICreateTypeInfo_interface)
  ICreateTypeLib (_wcesdk_oa96_ICreateTypeLib_interface)  IDispatch (_wcesdk_oa96_IDispatch_interface)  IEnumVARIANT (_wcesdk_oa96_IEnumVARIANT_interface)  IErrorInfo (_wcesdk_oa96_IErrorInfo_interface)
  ITypeComp (_wcesdk_oa96_ITypeComp_interface)  ITypeInfo2 (_wcesdk_oa96_ITypeInfo2_interface)  ITypeInfo (_wcesdk_oa96_ITypeInfo_interface)  ITypeLib (_wcesdk_oa96_ITypeLib_interface)
  PARAMDESC (_wcesdk_oa96_PARAMDESC)  TYPEATTR (_wcesdk_oa96_TYPEATTR)  TYPEDESC (_wcesdk_oa96_TYPEDESC)  VARDESC (_wcesdk_oa96_VARDESC)
  IDLDESC (wcesdkrIDLDESC)  SAFEARRAY (wcesdkroa96_SAFEARRAY_Data_Type)  SAFEARRAYBOUND (wcesdkroa96_SAFEARRAY_Data_TypeBOUND)  FUNCFLAGS (ms886002)
  ARRAYDESC (ms886091)  BINDPTR (ms886124)  CALLCONV (ms886161)  CUSTDATA (ms886959)
  CUSTDATAITEM (ms886960)  DESCKIND (ms886963)  ELEMDESC (ms886983)  EXCEPINFO (ms886984)
  FUNCDESC (ms886986)  FUNCKIND (ms886987)  INVOKEKIND (ms889336)  PARAMDESC (ms891232)
  SYSKIND (ms891289)  TLIBATTR (ms891296)  TYPEATTR (ms891299)  TYPEDESC (ms891300)
  TYPEFLAGS (ms891301)  TYPEKIND (ms891302)  VARDESC (ms891630)  VARKIND (ms891679)
  IDLDESC (ms892132)  SAFEARRAY (ms892133)  SAFEARRAYBOUND (ms892134)
```

### `objidl.h` -> `objbase.h` (54)

```
  ADVF (aa513925)  FORMATETC (aa514993)  BIND_OPTS (ms863848)  BIND_OPTS2 (ms863857)
  DATADIR (ms864408)  DVTARGETDEVICE (ms864453)  INTERFACEINFO (ms882877)  MKRREDUCE (ms892348)
  MKSYS (ms892349)  MULTI_QI (ms892354)  SOLE_AUTHENTICATION_SERVICE (ms893478)  STATSTG (ms896194)
  STGMEDIUM (ms896247)  TYMED (ms896492)  BIND_OPTS (_wcesdk_com_BIND_OPTS)  BIND_OPTS2 (_wcesdk_com_BIND_OPTS2)
  DVTARGETDEVICE (_wcesdk_com_DVTARGETDEVICE)  FORMATETC (_wcesdk_com_FORMATETC)  IClassActivator (_wcesdk_com_IClassActivator)  IClientSecurity (_wcesdk_com_IClientSecurity)
  IEnumMoniker (_wcesdk_com_IEnumMoniker)  IEnumSTATSTG (_wcesdk_com_IEnumSTATSTG)  IEnumString (_wcesdk_com_IEnumString)  IExternalConnection (_wcesdk_com_IExternalConnection)
  IFillLockBytes (_wcesdk_com_IFillLockBytes)  IMarshal (_wcesdk_com_IMarshal)  IMessageFilter (_wcesdk_com_IMessageFilter)  IMultiQI (_wcesdk_com_IMultiQI)
  IPersistFile (_wcesdk_com_IPersistFile)  IROTData (_wcesdk_com_IROTData)  IRunnableObject (_wcesdk_com_IRunnableObject)  IRunningObjectTable (_wcesdk_com_IRunningObjectTable)
  ISequentialStream (_wcesdk_com_ISequentialStream)  IServerSecurity (_wcesdk_com_IServerSecurity)  IStdMarshalInfo (_wcesdk_com_IStdMarshalInfo)  IStorage (_wcesdk_com_IStorage)
  IStream (_wcesdk_com_IStream)  STATSTG (_wcesdk_com_STATSTG)  STGMEDIUM (_wcesdk_com_STGMEDIUM)  TYMED (_wcesdk_com_TYMED)
  ADVF (ms886084)  BIND_OPTS (ms886131)  BIND_OPTS2 (ms886139)  DATADIR (ms886961)
  DVTARGETDEVICE (ms886982)  FORMATETC (ms886985)  INTERFACEINFO (ms889334)  MKRREDUCE (ms890778)
  MKSYS (ms890786)  MULTI_QI (ms890798)  SOLE_AUTHENTICATION_SERVICE (ms891267)  STATSTG (ms891269)
  STGMEDIUM (ms891275)  TYMED (ms891298)
```

### `ole2.h` -> `objbase.h` (48)

```
  GetHGlobalFromStream (aa515040)  CreateOleAdviseHolder (ms864397)  CreateStreamOnHGlobal (ms864401)  OleCreate (ms892590)
  OleDraw (ms892591)  OleIsRunning (ms892593)  OleLoadFromStream (ms892595)  OleRun (ms892596)
  OleSave (ms892597)  OleSaveToStream (ms892598)  OleSetContainedObject (ms892599)  ReadClassStg (ms892641)
  ReadClassStm (ms892642)  ReleaseStgMedium (ms892649)  WriteClassStg (ms897190)  WriteClassStm (ms897191)
  CreateOleAdviseHolder (_wcesdk_COM_CreateOleAdviseHolder)  OleCreate (_wcesdk_COM_OleCreate)  OleDraw (_wcesdk_COM_OleDraw)  OleIsRunning (_wcesdk_COM_OleIsRunning)
  OleRun (_wcesdk_COM_OleRun)  OleSave (_wcesdk_COM_OleSave)  OleSetContainedObject (_wcesdk_COM_OleSetContainedObject)  ReadClassStm (_wcesdk_COM_ReadClassStm)
  ReleaseStgMedium (_wcesdk_COM_ReleaseStgMedium)  WriteClassStg (_wcesdk_COM_WriteClassStg)  WriteClassStm (_wcesdk_COM_WriteClassStm)  CreateStreamOnHGlobal (_wcesdk_com_CreateStreamOnHGlobal)
  GetHGlobalFromStream (_wcesdk_com_GetHGlobalFromStream)  OleLoadFromStream (_wcesdk_com_OleLoadFromStream)  OleSaveToStream (_wcesdk_com_OleSaveToStream)  ReadClassStg (_wcesdk_com_ReadClassStg)
  CreateOleAdviseHolder (ms886953)  CreateStreamOnHGlobal (ms886955)  GetHGlobalFromStream (ms886990)  OleCreate (ms890815)
  OleDraw (ms890819)  OleIsRunning (ms890830)  OleLoadFromStream (ms890841)  OleRun (ms890845)
  OleSave (ms890847)  OleSaveToStream (ms890854)  OleSetContainedObject (ms890858)  ReadClassStg (ms891237)
  ReadClassStm (ms891238)  ReleaseStgMedium (ms891240)  WriteClassStg (ms892128)  WriteClassStm (ms892129)
```

### `d3dmtypes.h` -> `d3dm.h` (47)

```
  D3DMCULL (ms907687)  D3DMDEVICE_CREATION_PARAMETERS (ms907701)  D3DMDEVTYPE (ms907702)  D3DMDISPLAYMODE (ms907703)
  D3DMFILLMODE (ms907704)  D3DMFOGMODE (ms907705)  D3DMFORMAT (ms907707)  D3DMFVF_TEXCOORDFIXED (ms907709)
  D3DMFVF_TEXCOORDFLOAT (ms907710)  D3DMINDEXBUFFER_DESC (ms907712)  D3DMLIGHT (ms907713)  D3DMLIGHTTYPE (ms907714)
  D3DMLOCKED_RECT (ms907716)  D3DMMATERIAL (ms907718)  D3DMMATERIALCOLORSOURCE (ms907719)  D3DMMATRIX (ms907720)
  D3DMMULTISAMPLE_TYPE (ms907721)  D3DMPOOL (ms907725)  D3DMPRESENT_PARAMETERS (ms907729)  D3DMPRIMITIVETYPE (ms907730)
  D3DMPROFILE (ms907731)  D3DMRENDERSTATETYPE (ms907737)  D3DMRESOURCETYPE (ms907739)  D3DMSHADEMODE (ms907740)
  D3DMSTENCILOP (ms907742)  D3DMSURFACE_DESC (ms907743)  D3DMSWAPEFFECT (ms907745)  D3DMTEXTUREADDRESS (ms907748)
  D3DMTEXTUREFILTERTYPE (ms907749)  D3DMTEXTUREOP (ms907750)  D3DMTEXTURESTAGESTATETYPE (ms907751)  D3DMTEXTURETRANSFORMFLAGS (ms907752)
  D3DMTRANSFORMSTATETYPE (ms907753)  D3DMVECTOR (ms907757)  D3DMVERTEXBUFFER_DESC (ms907758)  D3DMVIEWPORT (ms907759)
  D3DMZBUFFERTYPE (ms907762)  D3DM_MAKE_RSVALUE (ms907764)  D3DMBACKBUFFER_TYPE (ms939134)  D3DMBLEND (ms939135)
  D3DMBLENDOP (ms939136)  D3DMCLIPSTATUS (ms939140)  D3DMCMPFUNC (ms939141)  D3DMCOLORVALUE (ms939143)
  D3DMCOLOR_ARGB (ms939145)  D3DMCOLOR_RGBA (ms939146)  D3DMCOLOR_XRGB (ms939147)
```

### `rapi.h` -> `windbase.h` (44)

```
  CeCreateDatabaseEx (aa513326)  CeCreateDatabase (aa513327)  CeDeleteDatabaseEx (aa513342)  CeDeleteDatabase (aa513343)
  CeDeleteRecord (aa513345)  CeEnumDBVolumes (aa513346)  CeFindFirstDatabaseEx (aa513351)  CeFindFirstDatabase (aa513352)
  CeFindNextDatabaseEx (aa513354)  CeFindNextDatabase (aa513355)  CeMountDBVol (aa513375)  CeOidGetInfoEx (aa513377)
  CeOidGetInfo (aa513378)  CeOpenDatabaseEx (aa513379)  CeOpenDatabase (aa513380)  CeReadRecordPropsEx (aa513389)
  CeReadRecordProps (aa513390)  CeSeekDatabase (aa513402)  CeSetDatabaseInfoEx (aa513403)  CeSetDatabaseInfo (aa513404)
  CeUnmountDBVol (aa513846)  CeWriteRecordProps (aa513850)  CeCreateDatabaseEx (_wcesdk_CeCreateDatabaseEx_RAPI_)  CeCreateDatabase (_wcesdk_CeCreateDatabase_RAPI_)
  CeDeleteDatabaseEx (_wcesdk_CeDeleteDatabaseEx_RAPI_)  CeDeleteDatabase (_wcesdk_CeDeleteDatabase_RAPI_)  CeDeleteRecord (_wcesdk_CeDeleteRecord_RAPI_)  CeEnumDBVolumes (_wcesdk_CeEnumDBVolumes_RAPI_)
  CeFindFirstDatabaseEx (_wcesdk_CeFindFirstDatabaseEx_RAPI_)  CeFindFirstDatabase (_wcesdk_CeFindFirstDatabase_RAPI_)  CeFindNextDatabaseEx (_wcesdk_CeFindNextDatabaseEx_RAPI_)  CeFindNextDatabase (_wcesdk_CeFindNextDatabase_RAPI_)
  CeMountDBVol (_wcesdk_CeMountDBVol_RAPI_)  CeOidGetInfoEx (_wcesdk_CeOidGetInfoEx_RAPI_)  CeOidGetInfo (_wcesdk_CeOidGetInfo_RAPI_)  CeOpenDatabaseEx (_wcesdk_CeOpenDatabaseEx_RAPI_)
  CeOpenDatabase (_wcesdk_CeOpenDatabase_RAPI_)  CeReadRecordPropsEx (_wcesdk_CeReadRecordPropsEx_RAPI_)  CeReadRecordProps (_wcesdk_CeReadRecordProps_RAPI_)  CeSeekDatabase (_wcesdk_CeSeekDatabase_RAPI_)
  CeSetDatabaseInfoEx (_wcesdk_CeSetDatabaseInfoEx_RAPI_)  CeSetDatabaseInfo (_wcesdk_CeSetDatabaseInfo_RAPI_)  CeUnmountDBVol (_wcesdk_CeUnmountDBVol_RAPI_)  CeWriteRecordProps (_wcesdk_CeWriteRecordProps_RAPI_)
```

### `winsock.h` -> `winsock2.h` (31)

```
  hostent (wcesdkrHOSTENT)  WSACleanup (wcesdkrWSACleanup)  WSADATA (wcesdkrWSADATA)  WSAGetLastError (wcesdkrWSAGetLastError)
  WSASetLastError (wcesdkrWSASetLastError)  WSAStartup (wcesdkrWSAStartup)  accept (wcesdkraccept_function)  bind (wcesdkrbind)
  connect (wcesdkrconnect_function)  gethostbyaddr (wcesdkrgethostbyaddr)  gethostbyname (wcesdkrgethostbyname)  gethostname (wcesdkrgethostname)
  getpeername (wcesdkrgetpeername)  getsockname (wcesdkrgetsockname)  getsockopt (wcesdkrgetsockopt)  htonl (wcesdkrhtonl)
  htons (wcesdkrhtons)  inet_addr (wcesdkrinet_addr)  inet_ntoa (wcesdkrinet_ntoa)  ioctlsocket (wcesdkrioctlsocket)
  listen (wcesdkrlisten_function)  ntohl (wcesdkrntohl)  ntohs (wcesdkrntohs)  recv (wcesdkrrecv)
  recvfrom (wcesdkrrecvfrom)  select (wcesdkrselect)  send (wcesdkrsend)  sendto (wcesdkrsendto)
  shutdown (wcesdkrshutdown_function)  sockaddr_irda (wcesdkrsockaddr_irda)  socket (wcesdkrsocket)
```

### `ocidl.h` -> `objbase.h` (29)

```
  HITRESULT (aa515087)  IOleControlSite (aa519260)  CONNECTDATA (ms863928)  CONTROLINFO (ms864020)
  DVASPECT2 (ms864438)  DVASPECTINFO (ms864439)  DVASPECTINFOFLAG (ms864450)  DVEXTENTINFO (ms864451)
  DVEXTENTMODE (ms864452)  LICINFO (ms892327)  VIEWSTATUS (ms897186)  CONTROLINFO (_wcesdk_com_CONTROLINFO)
  DVEXTENTINFO (_wcesdk_com_DVEXTENTINFO)  IClassFactory2 (_wcesdk_com_IClassFactory2)  IConnectionPoint (_wcesdk_com_IConnectionPoint)  IConnectionPointContainer (_wcesdk_com_IConnectionPointContainer)
  IEnumConnectionPoints (_wcesdk_com_IEnumConnectionPoints)  IEnumConnections (_wcesdk_com_IEnumConnections)  IPersistStreamInit (_wcesdk_com_IPersistStreamInit)  CONNECTDATA (ms886466)
  CONTROLINFO (ms886467)  DVASPECT2 (ms886977)  DVASPECTINFO (ms886978)  DVASPECTINFOFLAG (ms886979)
  DVEXTENTINFO (ms886980)  DVEXTENTMODE (ms886981)  HITRESULT (ms886993)  LICINFO (ms890747)
  VIEWSTATUS (ms892127)
```

### `oleidl.h` -> `objbase.h` (24)

```
  IOleContainer (aa519257)  IOleInPlaceSite (aa519272)  IOleWindow (aa519281)  OLEGETMONIKER (ms892592)
  OLELINKBIND (ms892594)  OLEUPDATE (ms892601)  OLEVERB (ms892602)  OLEVERBATTRIB (ms892603)
  OLEWHICHMK (ms892604)  STATDATA (ms896188)  IOleAdviseHolder (_wcesdk_com_IOleAdviseHolder)  IOleClientSite (_wcesdk_com_IOleClientSite)
  IOleObject (_wcesdk_com_IOleObject)  IPersist (_wcesdk_com_IPersist)  IPersistStorage (_wcesdk_com_IPersistStorage)  IRootStorage (_wcesdk_com_IRootStorage)
  IViewObject (_wcesdk_com_IViewObject)  OLEGETMONIKER (ms890826)  OLELINKBIND (ms890835)  OLEUPDATE (ms890865)
  OLEVERB (ms890871)  OLEVERBATTRIB (ms890872)  OLEWHICHMK (ms891202)  STATDATA (ms891268)
```

### `wtypes.h` -> `objbase.h` (15)

```
  CLSCTX (ms863882)  COAUTHIDENTITY (ms863886)  COAUTHINFO (ms863887)  COSERVERINFO (ms864158)
  DVASPECT (ms864437)  STGC (ms896217)  COAUTHINFO (_wcesdk_com_COAUTHINFO)  COSERVERINFO (_wcesdk_com_COSERVERINFO)
  DVASPECT (_wcesdk_com_DVASPECT)  CLSCTX (ms886177)  COAUTHIDENTITY (ms886203)  COAUTHINFO (ms886208)
  COSERVERINFO (ms886935)  DVASPECT (ms886976)  STGC (ms891270)
```

### `externs.h` -> `ndis.h` (13)

```
  MiniportCheckForHang (aa447842)  MiniportDisableInterrupt (aa447843)  MiniportEnableInterrupt (aa447844)  MiniportHalt (aa447845)
  MiniportInitialize (aa447847)  MiniportISR (aa447848)  MiniportQueryInformation (aa447849)  MiniportReconfigure (aa447850)
  MiniportReset (aa447851)  MiniportReturnPacket (aa447852)  MiniportSend (aa447853)  MiniportSetInformation (aa447855)
  MiniportTransferData (aa447859)
```

### `windows.h` -> `winuser.h` (12)

```
  ACCESSTIMEOUT (ms858519)  HIGHCONTRAST (ms858526)  MOUSEKEYS (ms858531)  SOUNDSENTRY (ms858538)
  STICKYKEYS (ms858544)  TOGGLEKEYS (ms858550)  GetMouseMovePoints (ms924840)  GetCapture (ms924848)
  GetDoubleClickTime (ms924852)  mouse_event (ms924856)  ReleaseCapture (ms924857)  SetCapture (ms924858)
```

### `winuser.h` -> `wingdi.h` (11)

```
  DLGTEMPLATEEX (aa452961)  SetSysColors (aa453656)  DLGTEMPLATEEX (_wcesdk_win32_DLGTEMPLATEEX_str)  SetSysColors (_wcesdk_win32_SetSysColors)
  EnumDisplayMonitors (wcesdkrEnumDisplayMonitors)  GetMonitorInfo (wcesdkrGetMonitorInfo)  MONITORINFO (wcesdkrMONITORINFO)  MONITORINFOEX (wcesdkrMONITORINFOEX)
  MonitorFromPoint (wcesdkrMonitorFromPoint)  MonitorFromRect (wcesdkrMonitorFromRect)  MonitorFromWindow (wcesdkrMonitorFromWindow)
```

### `kfuncs.h` -> `winbase.h` (11)

```
  DebugBreak (ms885194)  GetCurrentProcess (ms885613)  GetCurrentThread (ms885615)  ResetEvent (ms886800)
  SetEvent (ms886810)  PulseEvent (_wcesdk_Win32_PulseEvent)  ResetEvent (_wcesdk_Win32_ResetEvent)  SetEvent (_wcesdk_Win32_SetEvent)
  DebugBreak (wcesdkrDebugBreak)  GetCurrentProcess (wcesdkrGetCurrentProcess)  GetCurrentThread (wcesdkrGetCurrentThread)
```

### `cesync.h` -> `objbase.h` (6)

```
  ReportStatus (aa514455)  STOREINFO (aa514458)  STOREINFO (ms896271)  ReportStatus (_wcesdk_ReportStatus)
  STOREINFO (_wcesdk_STOREINFO)  STOREINFO (ms891278)
```

### `winbase.h` -> `windbase.h` (6)

```
  CEDIRINFO (_wcesdk_CEDIRINFO)  CEFILEINFO (_wcesdk_CEFILEINFO)  CEPROPVAL (_wcesdk_CEPROPVAL)  CERECORDINFO (_wcesdk_CERECORDINFO)
  CEVALUNION (_wcesdk_CEVALUNION)  CheckPassword (_wcesdk_CheckPassword)
```

### `windows.h` -> `winbase.h` (5)

```
  CompareFileTime (ms885172)  DuplicateHandle (ms885208)  InterlockedCompareExchange (ms885667)  InterlockedExchangeAdd (ms885671)
  EXTENDED_NAME_FORMAT (ms902883)
```

### `pchannel.h` -> `cchannel.h` (4)

```
  CHANNEL_DEF (aa513856)  CHANNEL_PDU_HEADER (aa513859)  CHANNEL_DEF (ms925144)  CHANNEL_PDU_HEADER (ms925146)
```

### `dccole.h` -> `objbase.h` (4)

```
  IDccMan (aa515545)  IDccManSink (aa515547)  IDccManSink (_wcesdk_IDccManSink_IUnknown)  IDccMan (_wcesdk_IDccMan_IUnknown)
```

### `tlhelp.h` -> `tlhelp32.h` (4)

```
  Heap32First (ms885650)  Heap32ListFirst (ms885651)  Heap32First (wcesdkrHeap32First)  Heap32ListFirst (wcesdkrHeap32ListFirst)
```

### `bt_api.h` -> `winsock2.h` (4)

```
  WSASetService (ms863409)  WSALookupServiceBegin (ms863410)  WSALookupServiceEnd (ms863411)  WSALookupServiceNext (ms863412)
```

### `wincrypt.h` -> `winsock2.h` (3)

```
  BLOB (ms937016)  BLOB (_wcesdk_crypto2_BLOB)  BLOB (ms884463)
```

### `wceemul.h` -> `imm.h` (3)

```
  CANDIDATEFORM (_wcesdk_win32_CANDIDATEFORM_str)  CANDIDATELIST (_wcesdk_win32_CANDIDATELIST_str)  COMPOSITIONFORM (_wcesdk_win32_COMPOSITIONFORM_str)
```

### `winuser.h` -> `winbase.h` (2)

```
  TlsAlloc (aa450945)  TlsAlloc (wcesdkrTlsAlloc)
```

### `ddraw.h` -> `dvp.h` (2)

```
  EnumVideoCallback (aa451694)  EnumVideoCallback (ms893908)
```

### `winuser.h` -> `objbase.h,shobjidl.h` (2)

```
  TranslateAccelerator (aa453775)  TranslateAccelerator (_wcesdk_win32_TranslateAccelerator)
```

### `mqmgmt.h` -> `mq.h` (2)

```
  MQMgmtAction (ms895121)  MQMgmtGetInfo (ms895123)
```

### `unimodem.h` -> `tapi.h` (2)

```
  PHONECAPS (ms895911)  PHONECAPS (ms927425)
```

### `commctrl.h` -> `commdlg.h` (2)

```
  CommDlgExtendedError (ms908144)  CommDlgExtendedError (_wcesdk_win32_CommDlgExtendedError)
```

### `winuser.h` -> `objbase.h` (2)

```
  GetClassInfo (ms929211)  GetClassInfo (_wcesdk_win32_GetClassInfo)
```

### `ndis.h` -> `externs.h` (2)

```
  MiniportHandleInterrupt (_wcesdk_MiniportHandleInterrupt)  MiniportWanSend (_wcesdk_MiniportWanSend)
```

### `winuser.h` -> `windows.h` (2)

```
  ScrollDC (_wcesdk_Win32_ScrollDC)  DRAWITEMSTRUCT (_wcesdk_win32_DRAWITEMSTRUCT)
```

### `windbase.h` -> `winbase.h` (2)

```
  CeSetThreadPriority (wcesdkrCeSetThreadPriority)  CeSetThreadQuantum (wcesdkrCeSetThreadQuantum)
```

### `commctrl.h` -> `winuser.h` (2)

```
  ICONINFO (wcesdkrICONINFO_str)  ICONINFO (ms924853)
```

### `winddi.h` -> `gpe.h` (1)

```
  DRVENABLEDATA (aa447740)
```

### `ws2tcpip.h` -> `p2p.h,winsock2.h` (1)

```
  sockaddr_in6 (aa450948)
```

### `windows.h` -> `objbase.h` (1)

```
  GetObject (aa453147)
```

### `iaccess.h` -> `objbase.h` (1)

```
  IAccessControl (aa515101)
```

### `pwindbas.h` -> `windbase.h` (1)

```
  CeChangeDatabaseLCID (aa516982)
```

### `docobj.h` -> `objbase.h` (1)

```
  IContinueCallback (ms880195)
```

### `ws2tcpip.h` -> `fwapi.h,winsock2.h` (1)

```
  in6_addr (ms890972)
```

### `storemgr.h` -> `objbase.h` (1)

```
  STOREINFO (ms892106)
```

### `ndis.h` -> `ntddndis.h` (1)

```
  NDIS_WLAN_BSSID (ms905053)
```

### `usbtypes.h` -> `usb100.h` (1)

```
  USB_ENDPOINT (ms923242)
```

### `d3dmcaps.h` -> `d3dm.h` (1)

```
  D3DMCAPS (ms939138)
```

### `windows.h` -> `windef.h` (1)

```
  SIZE (ms940344)
```

### `pkfuncs.h` -> `windbase.h` (1)

```
  CeChangeDatabaseLCID (_wcepb_CeChangeDatabaseLCID)
```

### `wingdi.h` -> `windows.h` (1)

```
  EnableEUDC (_wcesdk_EnableEUDC)
```

### `kfuncs.h` -> `pkfuncs.h` (1)

```
  KernelIoControl (_wcesdk_KernelIoControl)
```

### `wingdi.h` -> `objbase.h` (1)

```
  GetObject (_wcesdk_Win32_GetObject)
```

### `unknwn.h` -> `objbase.h` (1)

```
  IUnknown (_wcesdk_com_IUnknown)
```

### `winbase.h` -> `objbase.h` (1)

```
  SetErrorInfo (_wcesdk_oa96_SetErrorInfo)
```

### `winbase.h` -> `sspi.h` (1)

```
  QueryContextAttributes (_wcesdk_win32_QueryContextAttributes)
```

### `wtype.h` -> `winnt.h` (1)

```
  ULARGE_INTEGER (_wcesdk_win32_ULARGE_INTEGER_str)
```

### `ntcompat.h` -> `winbase.h` (1)

```
  RegisterDevice (wceddkRegisterDevice)
```

### `winsock.h` -> `windbase.h` (1)

```
  CEBLOB (wcesdkrCEBLOB)
```

### `winbase.h` -> `kfuncs.h` (1)

```
  CeGetCallerTrust (wcesdkrCeGetCallerTrust)
```

### `wininet.h` -> `winbase.h` (1)

```
  GetCommMask (wcesdkrGetCommMask)
```

### `ipexport.h` -> `icmpapi.h` (1)

```
  IP_OPTION_INFORMATION (wcesdkrIP_OPTION_INFORMATION)
```

### `winsock.h` -> `iphlpapi.h,winsock2.h,ws2spi.h,ws2tcpip.h` (1)

```
  sockaddr (wcesdkrSOCKADDR)
```

### `snmp.h` -> `snmpapi.h` (1)

```
  SnmpUtilMemAlloc (wcesdkrSnmpUtilMemAlloc)
```

### `pwinreg.h` -> `winbase.h` (1)

```
  CeGenRandom (ms884390)
```

### `dmoreg.h` -> `dmo.h` (1)

```
  DMORegister (ms897589)
```

### `bt_buffer.h` -> `bt_hcip.h` (1)

```
  BD_BUFFER (ms920205)
```

## Reproducing

Strip comments from every `include/**/*.{h,hpp}`, index declarations
(prototype, `} NAME` typedef tail, `struct|union|enum NAME`), then for
each corpus row with a shipped `Header:` token compare the header that
token names against the header(s) that actually declare the title
identifier.  Rows whose title contains `::` are COM methods and are
excluded.
