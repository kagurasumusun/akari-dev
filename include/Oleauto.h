/*
 * Oleauto.h -- OLE Automation runtime functions (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Restructure 2026-09-16 (docs/CHANGELOG-audit-2026-09-16.md): until
 * this pass, all 245 of the declarations below physically lived in
 * Objbase.h even though every one of their own harvested citations
 * says "Header: Oleauto.h" (M73a, docs/inventory.md, made this a
 * deliberate consolidation for harvest/verification convenience, with
 * this file kept as a thin alias -- #include "Objbase.h" and nothing
 * else). That is a real structural mismatch against what Windows CE
 * itself expects: application source that includes only <oleauto.h>
 * for Automation clients should not need to compile the entire raw
 * COM/IUnknown/IClassFactory surface transitively. Verified before
 * moving: none of these 245 names is referenced anywhere else in
 * Objbase.h outside their own contiguous block (only in harvest-note
 * comments), so the move is one-directional and does not reintroduce
 * a circular #include -- this file needs Objbase.h (for VARIANT,
 * DISPPARAMS, EXCEPINFO, SAFEARRAY, BSTR, and the interface pointer
 * types these functions take), but nothing in Objbase.h needs this
 * file back.
 *
 * Not moved in this pass (tracked as follow-up, not done here):
 * DISPPARAMS itself stays in Objbase.h despite its own citation also
 * saying Header: Oleauto.h -- it is used by IDispatch/ITypeInfo/
 * ITypeInfo2 vtable fields declared elsewhere in Objbase.h, and the
 * Oaidl.h consolidation (164 rows, M73a) is not unwound here; doing
 * both correctly needs untangling VARIANT/DISPPARAMS/ITypeInfo's
 * mutual dependencies first, which is a larger, separate pass.
 */

#ifndef AKARI_OLEAUTO_H
#define AKARI_OLEAUTO_H

#include "Objbase.h"   /* VARIANT, DISPPARAMS, EXCEPINFO, SAFEARRAY, BSTR, ... */

/* ---- OLE Automation (oleaut32.dll) (223 functions) ---- */

/* ms886153 "BstrFromVector" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT BstrFromVector(SAFEARRAY * psa, BSTR * pbstr) AKARI_CE_NAME(BstrFromVector);

/* ms886949 "CreateErrorInfo" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateErrorInfo(ICreateErrorInfo** pperrinfo) AKARI_CE_NAME(CreateErrorInfo);

/* ms886956 "CreateTypeLib2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateTypeLib2(SYSKIND syskind, LPOLESTR szFile, ICreateTypeLib2** ppctlib) AKARI_CE_NAME(CreateTypeLib2);

/* ms886965 "DispGetIDsOfNames" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "ItypeInfo" -> ITypeInfo.
 */
AKARI_CE_IMPORT HRESULT DispGetIDsOfNames(ITypeInfo* ptinfo, OLECHAR **rgszNames, unsigned int cNames, DISPID *rgdispid) AKARI_CE_NAME(DispGetIDsOfNames);

/* ms886966 "DispGetParam" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT DispGetParam(DISPPARAMS * pdispparams, unsigned int position, VARTYPE vtTarg, VARIANT * pvarResult, unsigned int * puArgErr) AKARI_CE_NAME(DispGetParam);

/* ms886969 "DispInvoke" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints pexcepinfo by value; the parameter is documented as a pointer.
 */
AKARI_CE_IMPORT HRESULT DispInvoke(void *_this, ITypeInfo *ptinfo, DISPID dispidMember, unsigned short wFlags, DISPPARAMS *pparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, unsigned int *puArgErr) AKARI_CE_NAME(DispInvoke);

/* ms886972 "DllCanUnloadNow" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT DllCanUnloadNow(void) AKARI_CE_NAME(DllCanUnloadNow);

/* ms886989 "GetErrorInfo" (Header: Oleauto.h; Windows CE 2.10 and later).
 * Page artifact: "IerrorInfo" -> IErrorInfo.
 */
AKARI_CE_IMPORT HRESULT GetErrorInfo(DWORD dwReserved, IErrorInfo **pperrinfo) AKARI_CE_NAME(GetErrorInfo);

/* ms890751 "LoadRegTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: missing comma between wVerMajor/wVerMinor restored.
 */
AKARI_CE_IMPORT HRESULT LoadRegTypeLib(REFGUID rguid, unsigned short wVerMajor, unsigned short wVerMinor, LCID lcid, ITypeLib **pptlib) AKARI_CE_NAME(LoadRegTypeLib);

/* ms890755 "LoadTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT LoadTypeLib(OLECHAR * szFile, ITypeLib ** pptlib) AKARI_CE_NAME(LoadTypeLib);

/* ms891239 "RegisterTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT RegisterTypeLib(ITypeLib * ptlib, OLECHAR * szFullPath, OLECHAR * szHelpDir) AKARI_CE_NAME(RegisterTypeLib);

/* ms891243 "SafeArrayAccessData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayAccessData(SAFEARRAY * psa, void ** ppvData) AKARI_CE_NAME(SafeArrayAccessData);

/* ms891244 "SafeArrayAllocData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayAllocData(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayAllocData);

/* ms891245 "SafeArrayAllocDescriptor" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayAllocDescriptor(unsigned int cDims, SAFEARRAY ** ppsaOut) AKARI_CE_NAME(SafeArrayAllocDescriptor);

/* ms891246 "SafeArrayCopy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayCopy(SAFEARRAY * psa, SAFEARRAY ** ppsaOut) AKARI_CE_NAME(SafeArrayCopy);

/* ms891247 "SafeArrayCopyData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayCopyData(SAFEARRAY * psaSource, SAFEARRAY ** psaTarget) AKARI_CE_NAME(SafeArrayCopyData);

/* ms891248 "SafeArrayCreate" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "SAFEARRRAYBOUND" (three R) -> SAFEARRAYBOUND.
 */
AKARI_CE_IMPORT HRESULT SafeArrayCreate(VARTYPE vt, unsigned int cDims, SAFEARRAYBOUND *rgsabound) AKARI_CE_NAME(SafeArrayCreate);

/* ms891250 "SafeArrayCreateVector" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayCreateVector(VARTYPE vt, long lLbound, unsigned int cElements) AKARI_CE_NAME(SafeArrayCreateVector);

/* ms891251 "SafeArrayDestroy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayDestroy(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayDestroy);

/* ms891252 "SafeArrayDestroyData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayDestroyData(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayDestroyData);

/* ms891253 "SafeArrayDestroyDescriptor" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayDestroyDescriptor(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayDestroyDescriptor);

/* ms891254 "SafeArrayGetDim" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints HRESULT; "Return Values" says the dimension count is returned.
 */
AKARI_CE_IMPORT ULONG SafeArrayGetDim(SAFEARRAY *psa) AKARI_CE_NAME(SafeArrayGetDim);

/* ms891255 "SafeArrayGetElement" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayGetElement(SAFEARRAY * psa, long * rgIndices, void * pv) AKARI_CE_NAME(SafeArrayGetElement);

/* ms891256 "SafeArrayGetElemsize" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints HRESULT; "Return Values" says the element size is returned.
 */
AKARI_CE_IMPORT ULONG SafeArrayGetElemsize(SAFEARRAY *psa) AKARI_CE_NAME(SafeArrayGetElemsize);

/* ms891257 "SafeArrayGetLBound" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayGetLBound(SAFEARRAY * psa, unsigned int nDim, long * plLbound) AKARI_CE_NAME(SafeArrayGetLBound);

/* ms891258 "SafeArrayGetUBound" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayGetUBound(SAFEARRAY * psa, unsigned int nDim, long * plUbound) AKARI_CE_NAME(SafeArrayGetUBound);

/* ms891259 "SafeArrayLock" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayLock(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayLock);

/* ms891260 "SafeArrayPtrOfIndex" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayPtrOfIndex(SAFEARRAY * psa, long * rgIndices, void ** ppvData) AKARI_CE_NAME(SafeArrayPtrOfIndex);

/* ms891261 "SafeArrayPutElement" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayPutElement(SAFEARRAY * psa, long * rgIndices, void * pv) AKARI_CE_NAME(SafeArrayPutElement);

/* ms891262 "SafeArrayRedim" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayRedim(SAFEARRAY * psa, SAFEARRAYBOUND * psaboundNew) AKARI_CE_NAME(SafeArrayRedim);

/* ms891263 "SafeArrayUnaccessData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayUnaccessData(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayUnaccessData);

/* ms891264 "SafeArrayUnlock" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayUnlock(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayUnlock);

/* ms891266 "SetErrorInfo" (Header: Oleauto.h; Windows CE 1.0 and later).
 */
AKARI_CE_IMPORT HRESULT SetErrorInfo(DWORD dwReserved, IErrorInfo* perrinfo) AKARI_CE_NAME(SetErrorInfo);

/* ms891285 "SysAllocString" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT BSTR SysAllocString(OLECHAR * sz) AKARI_CE_NAME(SysAllocString);

/* ms891286 "SysAllocStringByteLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT BSTR SysAllocStringByteLen(char * psz, unsigned int len) AKARI_CE_NAME(SysAllocStringByteLen);

/* ms891287 "SysAllocStringLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT BSTR SysAllocStringLen(OLECHAR * pch, unsigned int cch) AKARI_CE_NAME(SysAllocStringLen);

/* ms891288 "SysFreeString" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysFreeString(BSTR bstr) AKARI_CE_NAME(SysFreeString);

/* ms891290 "SysReAllocString" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysReAllocString(BSTR * pbstr, OLECHAR * sz) AKARI_CE_NAME(SysReAllocString);

/* ms891291 "SysReAllocStringLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysReAllocStringLen(BSTR * pbstr, OLECHAR * pch, unsigned int cch) AKARI_CE_NAME(SysReAllocStringLen);

/* ms891292 "SysStringByteLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysStringByteLen(BSTR bstr) AKARI_CE_NAME(SysStringByteLen);

/* ms891293 "SysStringLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysStringLen(BSTR bstr) AKARI_CE_NAME(SysStringLen);

/* ms891294 "SystemTimeToVariantTime" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints the parameter by value; the parameter is documented as a pointer.
 */
AKARI_CE_IMPORT int SystemTimeToVariantTime(LPSYSTEMTIME lpSystemTime, double *pvtime) AKARI_CE_NAME(SystemTimeToVariantTime);

/* ms891303 "UnRegisterTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: missing comma between wVerMajor/wVerMinor restored; the page Link Library field is blank (archive artifact) -- Oleaut32.lib per the documented sibling registration APIs.
 */
AKARI_CE_IMPORT HRESULT UnRegisterTypeLib(REFGUID libID, unsigned short wVerMajor, unsigned short wVerMinor, LCID lcid, SYSKIND syskind) AKARI_CE_NAME(UnRegisterTypeLib);

/* ms891305 "VarBoolFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromCy(CURRENCY cyIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromCy);

/* ms891306 "VarBoolFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromDate(DATE dateIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromDate);

/* ms891307 "VarBoolFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromDec(DECIMAL* pdecIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromDec);

/* ms891308 "VarBoolFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromDisp(IDispatch* pdispIn, LCID lcid, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromDisp);

/* ms891309 "VarBoolFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromI1(char cIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromI1);

/* ms891310 "VarBoolFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromI2(short sIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromI2);

/* ms891311 "VarBoolFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromI4(long lIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromI4);

/* ms891312 "VarBoolFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromR4(float fltIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromR4);

/* ms891313 "VarBoolFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromR8(double dblIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromR8);

/* ms891314 "VarBoolFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromStr);

/* ms891315 "VarBoolFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromUI1(BYTE bIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromUI1);

/* ms891316 "VarBoolFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromUI2(USHORT uiIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromUI2);

/* ms891317 "VarBoolFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromUI4(ULONG ulIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromUI4);

/* ms891318 "VarBstrFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromBool(BOOL boolIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromBool);

/* ms891319 "VarBstrFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromCy(CURRENCY cyIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromCy);

/* ms891320 "VarBstrFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromDate(DATE dateIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromDate);

/* ms891321 "VarBstrFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromDec(DECIMAL* pdecIn, LCID lcid, ULONG dwFlags, BSTR* pbstrOut) AKARI_CE_NAME(VarBstrFromDec);

/* ms891322 "VarBstrFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromDisp(IDispatch* pdispln, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromDisp);

/* ms891323 "VarBstrFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromI1(char cIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromI1);

/* ms891324 "VarBstrFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromI2(short iVal, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromI2);

/* ms891325 "VarBstrFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromI4(long lIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromI4);

/* ms891326 "VarBstrFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromR4(float fltIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromR4);

/* ms891327 "VarBstrFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromR8(double dblIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromR8);

/* ms891328 "VarBstrFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: printed prototype misnames the function and its output type; the title VarBstrFromUI1 and the documented Bstr-from-* 4-parameter form are used.
 */
AKARI_CE_IMPORT HRESULT VarBstrFromUI1(BYTE bIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromUI1);

/* ms891329 "VarBstrFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromUI2(USHORT uiIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromUI2);

/* ms891330 "VarBstrFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromUI4(ULONG ulIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromUI4);

/* ms891331 "VarCyFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromBool(BOOL boolIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromBool);

/* ms891465 "VarCyFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromDate(DATE dateIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromDate);

/* ms891479 "VarCyFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromDec(DECIMAL* pdecIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromDec);

/* ms891485 "VarCyFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromDisp(IDispatch* pdispIn, LCID lcid, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromDisp);

/* ms891500 "VarCyFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromI1(char cIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromI1);

/* ms891507 "VarCyFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromI2(short sIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromI2);

/* ms891510 "VarCyFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromI4(long lIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromI4);

/* ms891516 "VarCyFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromR4(float fltIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromR4);

/* ms891523 "VarCyFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromR8(double dblIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromR8);

/* ms891532 "VarCyFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromStr);

/* ms891539 "VarCyFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromUI1(BYTE bIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromUI1);

/* ms891548 "VarCyFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromUI2(USHORT uiIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromUI2);

/* ms891557 "VarCyFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromUI4(ULONG ulIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromUI4);

/* ms891564 "VarDateFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromBool(BOOL boolIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromBool);

/* ms891578 "VarDateFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromCy(CURRENCY cyIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromCy);

/* ms891584 "VarDateFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromDec(DECIMAL* pdecIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromDec);

/* ms891593 "VarDateFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromDisp(IDispatch* pdispIn, LCID lcid, DATE* pdateOut) AKARI_CE_NAME(VarDateFromDisp);

/* ms891600 "VarDateFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromI1(char cIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromI1);

/* ms891606 "VarDateFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromI2(short sIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromI2);

/* ms891609 "VarDateFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromI4(long lIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromI4);

/* ms891610 "VarDateFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromR4(float fltIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromR4);

/* ms891611 "VarDateFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromR8(double dblIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromR8);

/* ms891612 "VarDateFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, DATE* pdateOut) AKARI_CE_NAME(VarDateFromStr);

/* ms891613 "VarDateFromUdate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUdate(UDATE* pudateIn, unsigned long* dwFlags, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUdate);

/* ms891614 "VarDateFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUI1(unsigned char bIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUI1);

/* ms891615 "VarDateFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUI2(unsigned short uiIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUI2);

/* ms891616 "VarDateFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUI4(unsigned long ulIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUI4);

/* ms891617 "VarDecFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromBool(BOOL boolIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromBool);

/* ms891618 "VarDecFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromCy(CURRENCY cIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromCy);

/* ms891619 "VarDecFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromDate(DATE dateIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromDate);

/* ms891620 "VarDecFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromDisp(IDispatch* pdispIn, LCID lcid, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromDisp);

/* ms891621 "VarDecFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromI1(char cIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromI1);

/* ms891622 "VarDecFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromI2(short sIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromI2);

/* ms891623 "VarDecFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromI4(long lIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromI4);

/* ms891624 "VarDecFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromR4(float fltIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromR4);

/* ms891625 "VarDecFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromR8(double dblIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromR8);

/* ms891626 "VarDecFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromStr);

/* ms891627 "VarDecFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromUI1(BYTE bIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromUI1);

/* ms891628 "VarDecFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromUI2(USHORT uiIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromUI2);

/* ms891629 "VarDecFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: printed prototype says VarDecFromUI1 with a ULONG parameter; the title VarDecFromUI4 is the documented form.
 */
AKARI_CE_IMPORT HRESULT VarDecFromUI4(ULONG ulIn, DECIMAL *pdecOut) AKARI_CE_NAME(VarDecFromUI4);

/* ms891631 "VarI1FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromBool(BOOL boolIn, char* pcOut) AKARI_CE_NAME(VarI1FromBool);

/* ms891632 "VarI1FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromCy(CURRENCY cyIn, char* pcOut) AKARI_CE_NAME(VarI1FromCy);

/* ms891633 "VarI1FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromDate(DATE dateIn, char* pcOut) AKARI_CE_NAME(VarI1FromDate);

/* ms891634 "VarI1FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromDec(DECIMAL* pdecIn, char* pcOut) AKARI_CE_NAME(VarI1FromDec);

/* ms891635 "VarI1FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromDisp(IDispatch* pdispIn, LCID lcid, char* pcOut) AKARI_CE_NAME(VarI1FromDisp);

/* ms891636 "VarI1FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromI2(short sIn, char* pcOut) AKARI_CE_NAME(VarI1FromI2);

/* ms891637 "VarI1FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromI4(long lIn, char* pcOut) AKARI_CE_NAME(VarI1FromI4);

/* ms891638 "VarI1FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromR4(float fltIn, char* pcOut) AKARI_CE_NAME(VarI1FromR4);

/* ms891639 "VarI1FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromR8(double dblIn, char* pcOut) AKARI_CE_NAME(VarI1FromR8);

/* ms891640 "VarI1FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromStr(BSTR strIn, LCID lcid, ULONG dwFlags, char* pcOut) AKARI_CE_NAME(VarI1FromStr);

/* ms891641 "VarI1FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromUI1(BYTE bIn, char* pcOut) AKARI_CE_NAME(VarI1FromUI1);

/* ms891642 "VarI1FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromUI2(USHORT uiIn, char* pcOut) AKARI_CE_NAME(VarI1FromUI2);

/* ms891643 "VarI1FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromUI4(ULONG ulIn, char* pcOut) AKARI_CE_NAME(VarI1FromUI4);

/* ms891644 "VarI2FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromBool(BOOL boolIn, short* psOut) AKARI_CE_NAME(VarI2FromBool);

/* ms891645 "VarI2FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromCy(CURRENCY cyIn, short* psOut) AKARI_CE_NAME(VarI2FromCy);

/* ms891646 "VarI2FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromDate(DATE dateIn, short* psOut) AKARI_CE_NAME(VarI2FromDate);

/* ms891647 "VarI2FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromDec(DECIMAL* pdecIn, short* psOut) AKARI_CE_NAME(VarI2FromDec);

/* ms891648 "VarI2FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromDisp(IDispatch* pdispIn, LCID lcid, short* psOut) AKARI_CE_NAME(VarI2FromDisp);

/* ms891649 "VarI2FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromI1(CHAR cIn, short* psOut) AKARI_CE_NAME(VarI2FromI1);

/* ms891650 "VarI2FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromI4(LONG lIn, short* psOut) AKARI_CE_NAME(VarI2FromI4);

/* ms891651 "VarI2FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromR4(float fltIn, short* psOut) AKARI_CE_NAME(VarI2FromR4);

/* ms891652 "VarI2FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromR8(double dblIn, short* psOut) AKARI_CE_NAME(VarI2FromR8);

/* ms891653 "VarI2FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, short* psOut) AKARI_CE_NAME(VarI2FromStr);

/* ms891654 "VarI2FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromUI1(BYTE bIn, short* psOut) AKARI_CE_NAME(VarI2FromUI1);

/* ms891655 "VarI2FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromUI2(USHORT uiIn, short* psOut) AKARI_CE_NAME(VarI2FromUI2);

/* ms891656 "VarI2FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromUI4(ULONG ulIn, short* psOut) AKARI_CE_NAME(VarI2FromUI4);

/* ms891657 "VarI4FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromBool(BOOL boolIn, long* plOut) AKARI_CE_NAME(VarI4FromBool);

/* ms891658 "VarI4FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "CURRENTY" -> CURRENCY.
 */
AKARI_CE_IMPORT HRESULT VarI4FromCy(CURRENCY cyIn, long *plOut) AKARI_CE_NAME(VarI4FromCy);

/* ms891660 "VarI4FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromDec(DECIMAL* pdecIn, long* plOut) AKARI_CE_NAME(VarI4FromDec);

/* ms891661 "VarI4FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromDisp(IDispatch* pdispIn, LCID lcid, long* plOut) AKARI_CE_NAME(VarI4FromDisp);

/* ms891662 "VarI4FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromI1(CHAR cIn, long* plOut) AKARI_CE_NAME(VarI4FromI1);

/* ms891663 "VarI4FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: printed prototype says VarI4FromUI1 with a short parameter; the title VarI4FromI2 is the documented form.
 */
AKARI_CE_IMPORT HRESULT VarI4FromI2(short sIn, long *plOut) AKARI_CE_NAME(VarI4FromI2);

/* ms891664 "VarI4FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromR4(float fltIn, long* plOut) AKARI_CE_NAME(VarI4FromR4);

/* ms891665 "VarI4FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromR8(double dblIn, long* plOut) AKARI_CE_NAME(VarI4FromR8);

/* ms891667 "VarI4FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, long* plOut) AKARI_CE_NAME(VarI4FromStr);

/* ms891668 "VarI4FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromUI1(BYTE bIn, long* plOut) AKARI_CE_NAME(VarI4FromUI1);

/* ms891669 "VarI4FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromUI2(USHORT uiIn, long* plOut) AKARI_CE_NAME(VarI4FromUI2);

/* ms891670 "VarI4FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromUI4(ULONG ulIn, long* plOut) AKARI_CE_NAME(VarI4FromUI4);

/* ms891671 "VariantChangeType" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantChangeType(VARIANTARG * pvargDest, VARIANTARG * pvarSrc, unsigned short wFlags, VARTYPE vt) AKARI_CE_NAME(VariantChangeType);

/* ms891672 "VariantChangeTypeEx" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantChangeTypeEx(VARIANTARG * pvargDest, VARIANTARG * pvarSrc, LCID lcid, unsigned short wFlags, VARTYPE vt) AKARI_CE_NAME(VariantChangeTypeEx);

/* ms891673 "VariantClear" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantClear(VARIANTARG * pvarg) AKARI_CE_NAME(VariantClear);

/* ms891674 "VariantCopy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantCopy(VARIANTARG * pvargDest, VARIANTARG * pvargSrc) AKARI_CE_NAME(VariantCopy);

/* ms891675 "VariantCopyInd" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantCopyInd(VARIANT * pvarDest, VARIANTARG * pvargSrc) AKARI_CE_NAME(VariantCopyInd);

/* ms891676 "VariantInit" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantInit(VARIANTARG * pvarg) AKARI_CE_NAME(VariantInit);

/* ms891677 "VariantTimeToSystemTime" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT int VariantTimeToSystemTime(double vtime, LPSYSTEMTIME lpSystemTime) AKARI_CE_NAME(VariantTimeToSystemTime);

/* ms891680 "VarNumFromParseNum" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarNumFromParseNum(NUMPARSE* pnumprs, unsigned char* rgbDig, unsigned long dwVtBits, VARIANT* pvar) AKARI_CE_NAME(VarNumFromParseNum);

/* ms891681 "VarParseNumFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarParseNumFromStr(OLECHAR* strIn, LCID lcid, unsigned long dwFlags, NUMPARSE* pnumprs, unsigned char* rgbDig) AKARI_CE_NAME(VarParseNumFromStr);

/* ms891682 "VarR4FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromBool(BOOL boolIn, float* pfltOut) AKARI_CE_NAME(VarR4FromBool);

/* ms891683 "VarR4FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromCy(CURRENCY cyIn, float* pfltOut) AKARI_CE_NAME(VarR4FromCy);

/* ms891684 "VarR4FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromDate(DATE dateIn, float* pfltOut) AKARI_CE_NAME(VarR4FromDate);

/* ms891685 "VarR4FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromDec(DECIMAL* pdecIn, float* pfltOut) AKARI_CE_NAME(VarR4FromDec);

/* ms891686 "VarR4FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromDisp(IDispatch* pdispIn, LCID lcid, float* pfltOut) AKARI_CE_NAME(VarR4FromDisp);

/* ms891687 "VarR4FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "DOUBLE cIn" -> char cIn (the I1 form).
 */
AKARI_CE_IMPORT HRESULT VarR4FromI1(char cIn, float *pfltOut) AKARI_CE_NAME(VarR4FromI1);

/* ms891688 "VarR4FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromI2(short sIn, float* pfltOut) AKARI_CE_NAME(VarR4FromI2);

/* ms891689 "VarR4FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromI4(long lIn, float* pfltOut) AKARI_CE_NAME(VarR4FromI4);

/* ms891690 "VarR4FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "DOUBLE dblIn" -> double dblIn.
 */
AKARI_CE_IMPORT HRESULT VarR4FromR8(double dblIn, float *pfltOut) AKARI_CE_NAME(VarR4FromR8);

/* ms891691 "VarR4FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "Ulong" -> ULONG.
 */
AKARI_CE_IMPORT HRESULT VarR4FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, float *pfltOut) AKARI_CE_NAME(VarR4FromStr);

/* ms891700 "VarR4FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromUI1(BYTE bIn, float* pfltOut) AKARI_CE_NAME(VarR4FromUI1);

/* ms891773 "VarR4FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromUI2(USHORT uiIn, float* pfltOut) AKARI_CE_NAME(VarR4FromUI2);

/* ms891776 "VarR4FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromUI4(ULONG ulIn, float* pfltOut) AKARI_CE_NAME(VarR4FromUI4);

/* ms891785 "VarR8FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromBool(BOOL boolIn, double* pdblOut) AKARI_CE_NAME(VarR8FromBool);

/* ms891790 "VarR8FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromCy(CURRENCY cyIn, double* pdblOut) AKARI_CE_NAME(VarR8FromCy);

/* ms891796 "VarR8FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromDate(DATE dateIn, double* pdblOut) AKARI_CE_NAME(VarR8FromDate);

/* ms891802 "VarR8FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromDec(DECIMAL* pdecIn, double* pdblOut) AKARI_CE_NAME(VarR8FromDec);

/* ms891810 "VarR8FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "VarR8FromDips" -> VarR8FromDisp.
 */
AKARI_CE_IMPORT HRESULT VarR8FromDisp(IDispatch *pdispIn, LCID lcid, double *pdblOut) AKARI_CE_NAME(VarR8FromDisp);

/* ms891812 "VarR8FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromI1(char cIn, double* pdblOut) AKARI_CE_NAME(VarR8FromI1);

/* ms891816 "VarR8FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromI2(short sIn, double* pdblOut) AKARI_CE_NAME(VarR8FromI2);

/* ms891823 "VarR8FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromI4(long lIn, double* pdblOut) AKARI_CE_NAME(VarR8FromI4);

/* ms891825 "VarR8FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromR4(float fltIn, double* pdblOut) AKARI_CE_NAME(VarR8FromR4);

/* ms891831 "VarR8FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, double* pdblOut) AKARI_CE_NAME(VarR8FromStr);

/* ms891836 "VarR8FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromUI1(BYTE bIn, double* pdblOut) AKARI_CE_NAME(VarR8FromUI1);

/* ms891839 "VarR8FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromUI2(USHORT uiIn, double* pdblOut) AKARI_CE_NAME(VarR8FromUI2);

/* ms891846 "VarR8FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page title misprints VarR8FromI4; the printed ULONG parameter is the UI4 form.
 */
AKARI_CE_IMPORT HRESULT VarR8FromUI4(ULONG ulIn, double *pdblOut) AKARI_CE_NAME(VarR8FromUI4);

/* ms891856 "VarUdateFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUdateFromDate(DATE* dateIn, unsigned long dwFlags, UDATE* pudateOut) AKARI_CE_NAME(VarUdateFromDate);

/* ms891863 "VarUI1FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromBool(BOOL boolIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromBool);

/* ms891867 "VarUI1FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromCy(CURRENCY cyIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromCy);

/* ms891869 "VarUI1FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromDate(DATE dateIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromDate);

/* ms891876 "VarUI1FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromDec(DECIMAL* pdecIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromDec);

/* ms891887 "VarUI1FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromDisp(IDispatch* pdispIn, LCID lcid, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromDisp);

/* ms891893 "VarUI1FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromI1(char cIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromI1);

/* ms891901 "VarUI1FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromI2(short sIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromI2);

/* ms891905 "VarUI1FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromI4(long lIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromI4);

/* ms891912 "VarUI1FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromR4(float fltIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromR4);

/* ms891915 "VarUI1FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromR8(double dblIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromR8);

/* ms891922 "VarUI1FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromStr);

/* ms891926 "VarUI1FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromUI2(USHORT uiIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromUI2);

/* ms891930 "VarUI1FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromUI4(ULONG ulIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromUI4);

/* ms891935 "VarUI2FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromBool(BOOL boolIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromBool);

/* ms891940 "VarUI2FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromCy(CURRENCY cyIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromCy);

/* ms891947 "VarUI2FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromDate(DATE dateIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromDate);

/* ms891951 "VarUI2FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromDec(DECIMAL* pdecIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromDec);

/* ms891955 "VarUI2FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromDisp(IDispatch* pdispIn, LCID lcid, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromDisp);

/* ms891961 "VarUI2FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromI1(char cIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromI1);

/* ms891966 "VarUI2FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromI2(short uiIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromI2);

/* ms891970 "VarUI2FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromI4(long lIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromI4);

/* ms891981 "VarUI2FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromR4(float fltIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromR4);

/* ms891986 "VarUI2FromR8" (Header: Oleauto.h; Windows CE 2.12 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromR8(double dblIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromR8);

/* ms891993 "VarUI2FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromStr(BSTR strIn, LCID lcid, ULONG dwFlags, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromStr);

/* ms891998 "VarUI2FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromUI1(BYTE bIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromUI1);

/* ms892004 "VarUI2FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromUI4(ULONG ulIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromUI4);

/* ms892011 "VarUI4FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromBool(BOOL boolIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromBool);

/* ms892020 "VarUI4FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromCy(CURRENCY cyIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromCy);

/* ms892026 "VarUI4FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromDate(DATE dateIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromDate);

/* ms892103 "VarUI4FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromDec(DECIMAL* pdecIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromDec);

/* ms892107 "VarUI4FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromDisp(IDispatch* pdispIn, LCID lcid, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromDisp);

/* ms892116 "VarUI4FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromI1(char cIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromI1);

/* ms892117 "VarUI4FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromI2(short sIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromI2);

/* ms892118 "VarUI4FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromI4(long lIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromI4);

/* ms892119 "VarUI4FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromR4(float fltIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromR4);

/* ms892120 "VarUI4FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromR8(double dblIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromR8);

/* ms892121 "VarUI4FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromStr(BSTR strIn, LCID lcid, ULONG dwFlags, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromStr);

/* ms892122 "VarUI4FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromUI1(BYTE bIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromUI1);

/* ms892123 "VarUI4FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromUI2(USHORT uiIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromUI2);

/* aa519078 "VarI4FromDate": the page's syntax print is a copy-paste
 * artifact of VarI4FromUI1 ("HRESULTVarI4FromUI1(DATE dateIn,long*
 * plOut )" -- wrong name in the print); the page's own parameters
 * (dateIn/plOut) and the uniform VarI4FromXXX family shape govern;
 * print recorded. */
AKARI_CE_IMPORT HRESULT VarI4FromDate(DATE dateIn,
                    long *plOut) AKARI_CE_NAME(VarI4FromDate);

/* PROPVARIANT (aa519284): the print embeds by value a large set of
 * counted-array unions (CAC, CAUB, ... CABSTRBLOB, CAPROPVARIANT)
 * and helper types (BSTRBLOB, BLOB, CLIPDATA, VERSIONEDSTREAM)
 * that no CE page defines -- the layout is HELD (incomplete type,
 * pointer-only; the PropVariant* functions below take pointers). */
typedef struct PROPVARIANT PROPVARIANT;

/* aa519285 "PropVariantClear": WINOLEAPI print (empty convention
 * macro in this tree, Objbase.h line ~88 -> HRESULT declared). */
AKARI_CE_IMPORT HRESULT PropVariantClear(
                    PROPVARIANT *pvar) AKARI_CE_NAME(PropVariantClear);

/* aa519286 "PropVariantCopy". */
AKARI_CE_IMPORT HRESULT PropVariantCopy(PROPVARIANT *pvarDest,
                    const PROPVARIANT *pvarSrc) AKARI_CE_NAME(PropVariantCopy);

/* aa519255 "FreePropVariantArray". */
AKARI_CE_IMPORT HRESULT FreePropVariantArray(ULONG cVariants,
                    PROPVARIANT *rgvars) AKARI_CE_NAME(FreePropVariantArray);

/* ms892124 "VectorFromBstr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VectorFromBstr(BSTR bstr, SAFEARRAY ** ppsa) AKARI_CE_NAME(VectorFromBstr);



/* ================================================================
 * M73b: COM and DCOM Reference -- remaining interface surface
 * (COM/OLE/Storage books, manifests dcom-{com,ole,storage}).
 * ================================================================ */

/* Opaque interface forwards (32; the COM and DCOM Reference pages
 * print Header rows Objidl.h / Oleidl.h / Ocidl.h / Comcat.h /
 * IAccess.h / Dccole.h / Unknwn.h with Link Library rows
 * "Ole32.lib, Uuid.lib" (GUID linkage -- no export surface; the
 * documented-case aliases for those headers point here). */
typedef struct IAccessControl IAccessControl;
typedef struct ICatInformation ICatInformation;
typedef struct ICatRegister ICatRegister;
typedef struct IContinueCallback IContinueCallback;
typedef struct IDccMan IDccMan;
typedef struct IDccManSink IDccManSink;
typedef struct IEnumOLEVERB IEnumOLEVERB;
typedef struct IObjectSafety IObjectSafety;
typedef struct IOleAdviseHolder IOleAdviseHolder;
typedef struct IOleClientSite IOleClientSite;
typedef struct IOleContainer IOleContainer;
typedef struct IOleControlSite IOleControlSite;
typedef struct IOleInPlaceSite IOleInPlaceSite;
typedef struct IOleLink IOleLink;
typedef struct IOleObject IOleObject;
typedef struct IOleWindow IOleWindow;
typedef struct IParseDisplayName IParseDisplayName;
typedef struct IPersist IPersist;
typedef struct IPersistStorage IPersistStorage;
typedef struct IPersistStream IPersistStream;
typedef struct IPersistStreamInit IPersistStreamInit;
typedef struct IProgressNotify IProgressNotify;
typedef struct IProvideClassInfo IProvideClassInfo;
typedef struct IProvideClassInfo2 IProvideClassInfo2;
typedef struct IROTData IROTData;
typedef struct IRootStorage IRootStorage;
typedef struct IRunnableObject IRunnableObject;
typedef struct ISequentialStream ISequentialStream;
typedef struct IServerSecurity IServerSecurity;
typedef struct IStdMarshalInfo IStdMarshalInfo;
typedef struct IViewObject IViewObject;
typedef struct IViewObject2 IViewObject2;

/* Pointer-form closures printed by the function signatures below
 * (mechanical pointer typedefs over the documented interface
 * names; replace on an official print). */
typedef IOleObject *LPOLEOBJECT;
typedef const RECT   *LPCRECT;

/* --- Functions (Ole32.lib rows -> def/ole32-doc.def; Olectl.h
 * rows recorded). ------------------------------------------------ */

/* ms863900 "CoFreeUnusedLibrariesEx": print `void CoFreeUnusedLibrariesEx( DWORD dwUnloadDelay, DWORD dwReserved);` */
AKARI_CE_IMPORT void CoFreeUnusedLibrariesEx(DWORD dwUnloadDelay,
                    DWORD dwReserved) AKARI_CE_NAME(CoFreeUnusedLibrariesEx);

/* ms886018 "IsEqualGUID": print `BOOL IsEqualGUID(REFGUID rguid1,REFGUID rguid2);` */
AKARI_CE_IMPORT BOOL IsEqualGUID(REFGUID rguid1,
                    REFGUID rguid2) AKARI_CE_NAME(IsEqualGUID);

/* ms864401 "CreateStreamOnHGlobal": print `WINOLEAPI CreateStreamOnHGlobal(HGLOBAL hGlobal,BOOL fDeleteOnRelease,LPSTREAM* ppstm);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT CreateStreamOnHGlobal(HGLOBAL hGlobal,
                    BOOL fDeleteOnRelease,
                    LPSTREAM *ppstm) AKARI_CE_NAME(CreateStreamOnHGlobal);

/* aa515040 "GetHGlobalFromStream": print `WINOLEAPI GetHGlobalFromStream(IStream* pstm,HGLOBAL* phglobal);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT GetHGlobalFromStream(IStream *pstm,
                    HGLOBAL *phglobal) AKARI_CE_NAME(GetHGlobalFromStream);

/* ms864397 "CreateOleAdviseHolder": print `WINOLEAPICreateOleAdviseHolder(IOleAdviseHolder FAR* FAR* ppOAHolder);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT CreateOleAdviseHolder(
                    IOleAdviseHolder **ppOAHolder) AKARI_CE_NAME(CreateOleAdviseHolder);

/* ms892596 "OleRun": print `WINOLEAPIOleRun(LPUNKNOWNpUnknown);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleRun(LPUNKNOWN pUnknown) AKARI_CE_NAME(OleRun);

/* ms892593 "OleIsRunning": print `BOOLOleIsRunning(LPOLEOBJECTpObject);` */
AKARI_CE_IMPORT BOOL OleIsRunning(
                    LPOLEOBJECT pObject) AKARI_CE_NAME(OleIsRunning);

/* ms892595 "OleLoadFromStream": print `WINOLEAPI OleLoadFromStream(IStream* pStm,REFIID iidInterface,void** ppvObj);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleLoadFromStream(IStream *pStm,
                    REFIID iidInterface, void **ppvObj) AKARI_CE_NAME(OleLoadFromStream);

/* ms892598 "OleSaveToStream": print `WINOLEAPI OleSaveToStream(IPersistStream* pPStm,IStream* pStm);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleSaveToStream(IPersistStream *pPStm,
                    IStream *pStm) AKARI_CE_NAME(OleSaveToStream);

/* ms892597 "OleSave": print `WINOLEAPI OleSave(IPersistStorage* pPS,IStorage* pStg,BOOLfSameAsLoad);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleSave(IPersistStorage *pPS,
                    IStorage *pStg, BOOL fSameAsLoad) AKARI_CE_NAME(OleSave);

/* ms892599 "OleSetContainedObject": print `WINOLEAPIOleSetContainedObject(LPUNKNOWNpUnk,BOOLfContained);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleSetContainedObject(LPUNKNOWN pUnk,
                    BOOL fContained) AKARI_CE_NAME(OleSetContainedObject);

/* ms892590 "OleCreate": print `WINOLEAPI OleCreate( REFCLSIDrclsid,REFIIDriid,DWORDrenderopt,FORMATETC* pFormatEtc,IOleClientSite* pClientSite,IStorage* pStg,void** ppvObject);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleCreate(REFCLSID rclsid, REFIID riid,
                    DWORD renderopt, FORMATETC *pFormatEtc,
                    IOleClientSite *pClientSite, IStorage *pStg,
                    void **ppvObj) AKARI_CE_NAME(OleCreate);

/* ms892591 "OleDraw": print `WINOLEAPIOleDraw(IUnknown* pUnk,DWORDdwAspect,HDChdcDraw,LPCRECTlprcBounds);` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT OleDraw(IUnknown *pUnk, DWORD dwAspect,
                    HDC hdcDraw, LPCRECT lprcBounds) AKARI_CE_NAME(OleDraw);

/* ms892641 "ReadClassStg": print `WINOLEAPI ReadClassStg( IStorage* pStg,CLSID* pclsid );` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT ReadClassStg(IStorage *pStg, CLSID *pclsid) AKARI_CE_NAME(ReadClassStg);

/* ms892642 "ReadClassStm": print `WINOLEAPI ReadClassStm(IStream* pStm,CLSID* pclsid );` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT ReadClassStm(IStream *pSm, CLSID *pclsid) AKARI_CE_NAME(ReadClassStm);

/* ms897190 "WriteClassStg": print `WINOLEAPIWriteClassStg(IStorage* pStg,REFCLSIDrclsid );` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT WriteClassStg(IStorage *pStg, REFCLSID rclsid) AKARI_CE_NAME(WriteClassStg);

/* ms897191 "WriteClassStm": print `WINOLEAPIWriteClassStm(IStream* pStm,REFCLSIDrclsid );` -- WINOLEAPI/STDAPI are empty convention macros here (HRESULT) */
AKARI_CE_IMPORT HRESULT WriteClassStm(IStream *pSm, REFCLSID rclsid) AKARI_CE_NAME(WriteClassStm);

/* ms892649 "ReleaseStgMedium": print `void ReleaseStgMedium( STGMEDIUM* pmedium);` */
AKARI_CE_IMPORT void ReleaseStgMedium(
                    STGMEDIUM *pmedium) AKARI_CE_NAME(ReleaseStgMedium);

/* ms864429 "DllRegisterServer" / ms864430 "DllUnregisterServer"
 * (Olectl.h rows): prints `STDAPI DllRegisterServer(void);` /
 * `STDAPI DllUnregisterServer(void);` (STDAPI is an empty convention
 * macro here).  Link Library rows say Oleaut32.lib, but these are
 * implemented and self-exported by each control DLL -- recorded;
 * no import declaration. */

/* OleSetMenuDescriptor (Ole2.h row): HELD -- the print takes
 * HOLEMENU / LPOLEINPLACEFRAME / LPOLEINPLACEACTIVEOBJECT
 * parameters whose typedefs no CE page publishes.  Verbatim:
 *   WINOLEAPI OleSetMenuDescriptor( HOLEMENUholemenu,HWND hwndFrame,
 *     HWND hwndActiveObject,LPOLEINPLACEFRAME lpFrame,
 *     LPOLEINPLACEACTIVEOBJECT lpActiveObj, HWND hwndBackup);
 */


/* --- Types: OLE enums and structures (Oleidl.h rows). -------------- */

/* ms892592 "OLEGETMONIKER" (CE 3.0+): print
 * `typedef enum tagOLEGETMONIKER { OLEGETMONIKER_ONLYIFTHERE = 1,
 * OLEGETMONIKER_FORCEASSIGN = 2, OLEGETMONIKER_UNASSIGN = 3,
 * OLEGETMONIKER_TEMPFORUSER = 4} OLEGETMONIKER;` */
typedef enum tagOLEGETMONIKER {
    OLEGETMONIKER_ONLYIFTHERE = 1,
    OLEGETMONIKER_FORCEASSIGN = 2,
    OLEGETMONIKER_UNASSIGN = 3,
    OLEGETMONIKER_TEMPFORUSER = 4
} OLEGETMONIKER;

/* ms892594 "OLELINKBIND" (CE 3.0+): print
 * `typedef enum tagOLELINKBIND { OLELINKBIND_EVENIFCLASSDIFF = 1, } OLELINKBIND;` */
typedef enum tagOLELINKBIND {
    OLELINKBIND_EVENIFCLASSDIFF = 1
} OLELINKBIND;

/* ms892601 "OLEUPDATE" (CE 3.0+): print
 * `typedef enum tagOLEUPDATE { OLEUPDATE_ALWAYS = 1, OLEUPDATE_ONCALL = 3 } OLEUPDATE;` */
typedef enum tagOLEUPDATE {
    OLEUPDATE_ALWAYS = 1,
    OLEUPDATE_ONCALL = 3
} OLEUPDATE;

/* ms892603 "OLEVERBATTRIB" (CE 2.0+): print
 * `typedef enum tagOLEVERBATTRIB {OLEVERBATTRIB_NEVERDIRTIES= 1,
 * OLEVERBATTRIB_ONCONTAINERMENU= 2 } OLEVERBATTRIB;` */
typedef enum tagOLEVERBATTRIB {
    OLEVERBATTRIB_NEVERDIRTIES = 1,
    OLEVERBATTRIB_ONCONTAINERMENU = 2
} OLEVERBATTRIB;

/* ms892604 "OLEWHICHMK" (CE 3.0+): print
 * `typedef enum tagOLEWHICHMK { OLEWHICHMK_CONTAINER = 1,
 * OLEWHICHMK_OBJREL = 2, OLEWHICHMK_OBJFULL = 3 } OLEWHICHMK;` */
typedef enum tagOLEWHICHMK {
    OLEWHICHMK_CONTAINER = 1,
    OLEWHICHMK_OBJREL = 2,
    OLEWHICHMK_OBJFULL = 3
} OLEWHICHMK;

/* ms892602 "OLEVERB" (CE 2.0+): print
 * `typedef struct tagOLEVERB { LONGlVerb;LPWSTRlpszVerbName;DWORDfuFlags;
 * DWORDgrfAttribs;} OLEVERB, *LPOLEVERB;`
 * CROSS-GENERATION (M86 sweep): the CE 4.0 twin ms889374 prints the
 * first member as `LONG iVerb;` (CE 5.0: lVerb), `LPOLESTR
 * lpszVerbName;` (CE 5.0: LPWSTR) and no *LPOLEVERB typedef.
 * Same member sizes/order; source-spelling difference recorded. */
typedef struct tagOLEVERB {
    LONG   lVerb;
    LPWSTR lpszVerbName;
    DWORD  fuFlags;
    DWORD  grfAttribs;
} OLEVERB, *LPOLEVERB;

/* ms882883 "IOleAdviseHolder::EnumAdvise" (CE 3.0+): print
 * `typedef struct tagSTATDATA { FORMATETC Formatetc; DWORD grfAdvf;
 * IAdviseSink * pAdvise; DWORD dwConnection; }STATDATA;` */
typedef struct tagSTATDATA {
    FORMATETC   Formatetc;
    DWORD       grfAdvf;
    IAdviseSink *pAdvise;
    DWORD       dwConnection;
} STATDATA;

/* ms896271 "STOREINFO (COM)" (CE 2.0+, Header row Cesync.h -- the CE
 * COM reference carries this sync-store struct here): print
 * `typedef struct tagStoreInfo {UINT cbStruct;UINT uFlags;
 * TCHAR szProgId[256];TCHAR szStoreDesc[200];UINT uTimerRes;
 * UINT cbMaxStoreId;UINT cbStoreId;LPBYTE lpbStoreId;} STOREINFO,*PSTOREINFO;` */
typedef struct tagStoreInfo {
    UINT  cbStruct;
    UINT  uFlags;
    TCHAR szProgId[256];
    TCHAR szStoreDesc[200];
    UINT  uTimerRes;
    UINT  cbMaxStoreId;
    UINT  cbStoreId;
    LPBYTE lpbStoreId;
} STOREINFO, *PSTOREINFO;


/* --- Held names (no CE page prints values or signatures). ---------- */
/* COINIT_MULTITHREADED / COINIT_APARTMENTTHREADED: named as dwCoInit
 * values on the CoInitializeEx pages (ms863915 CE 5.0; ms863914 says
 * "call CoInitializeEx using the COINIT_MULTITHREADED constant") but
 * NO CE page prints their numeric values -- held (users pass 0). */
/* DirectInputCreate (ms864419, Dinput.h / Dinput.lib): appears in the
 * COM book harvest but belongs to the DirectInput surface -- deferred
 * to the DirectInput queue. */

/* --- Interface method records (verbatim; M44 comment policy). --- */

/* IAccessControl: documented methods (6 pages).  Signatures recorded verbatim (do not compile):
 *   aa515095 GetAllAccessRights: HRESULT GetAllAccessRights(LPWSTRlpProperty,PACTRL_ACCESSW* ppAccessList,PTRUSTEEW* ppOwner,PTRUSTEEW* ppGroup);
 *   aa515097 GrantAccessRights: HRESULT GrantAccessRights(PACTRL_ACCESSWpAccessList);
 *   aa515099 IsAccessAllowed: HRESULT IsAccessAllowed(PTRUSTEEWpTrustee,LPWSTRlpProperty,ACCESS_RIGHTSAccessRights,BOOL* pfAccessAllowed);
 *   aa515102 RevokeAccessRights: HRESULT RevokeAccessRights(LPWSTRlpProperty,ULONGcTrustees,TRUSTEEWprgTrustees[]);
 *   aa515103 SetAccessRights: HRESULT SetAccessRights(PACTRL_ACCESSWpAccessList);
 *   aa515104 SetOwner: HRESULT SetOwner(PTRUSTEEWpOwner,PTRUSTEEWpGroup);
 */

/* ICatInformation: documented methods (6 pages).  Signatures recorded verbatim (do not compile):
 *   ms879987 EnumCategories: HRESULT EnumCategories(LCIDlcid,IEnumCATEGORYINFO** ppenumCatInfo );
 *   ms880012 EnumClassesOfCategories: HRESULT EnumClassesOfCategories(ULONGcImplemented,CATIDrgcatidImpl,ULONGcRequired,CATIDrgcatidReq,IEnumCLSID** ppenumCLSID);
 *   ms880020 EnumImplCategoriesOfClass: HRESULT EnumImplCategoriesOfClass(REFCLSIDrclsid,IEnumCATID** ppenumCATD);
 *   ms880024 EnumReqCategoriesOfClass: HRESULT EnumReqCategoriesOfClass(REFCLSIDrclsid,IEnumCATID** ppenumCATD);
 *   ms880029 GetCategoryDesc: HRESULT GetCategoryDesc(REFCATIDrcatid,LCIDlcid,PWCHAR* ppszDesc);
 *   ms880032 IsClassOfCategories: HRESULT IsClassOfCategories(REFCLSIDrclsid,ULONGcImplemented,CATIDrgcatidImpl[],ULONGcRequired,CATIDrgcatidReq[]);
 */

/* ICatRegister: documented methods (6 pages).  Signatures recorded verbatim (do not compile):
 *   ms880045 RegisterCategories: HRESULT RegisterCategories(ULONGcCategories,CATEGORYINFOrgCategoryInfo[]);
 *   ms880052 RegisterClassImplCategories: HRESULT RegisterClassImplCategories(REFCLSIDrclsid,ULONGcCategories,CATIDrgcatid[]);
 *   ms880057 RegisterClassReqCategories: HRESULT RegisterClassReqCategories(REFCLSIDrclsid,ULONGcCategories,CATIDrgcatid[]);
 *   ms880063 UnRegisterCategories: HRESULT UnRegisterCategories(ULONGcCategories,CATIDrgcatid[]);
 *   ms880068 UnRegisterClassImplCategories: HRESULT UnRegisterClassImplCategories(REFCLSIDrclsid,ULONGcCategories,CATIDrgcatid[]);
 *   ms880073 UnRegisterClassReqCategories: HRESULT UnRegisterClassReqCategories(REFCLSIDrclsid,ULONGcCategories,CATIDrgcatid[]);
 */

/* IContinueCallback: documented methods (2 pages).  Signatures recorded verbatim (do not compile):
 *   ms880185 FContinue: HRESULT FContinue(void);
 *   ms880191 FContinuePrinting: HRESULT FContinuePrinting(LONGcPagesPrinted,LONGnCurrentPage,LPOLESTRpszPrintStatus);
 */

/* IEnumOLEVERB: documented methods (4 pages).  Signatures recorded verbatim (do not compile):
 *   aa515631 Clone: HRESULT Clone( IEnumOLEVERB ** ppenum);
 *   aa515635 Next: HRESULT Next( ULONG celt, LPOLEVERB rgelt, ULONG * pceltFetched);
 *   aa515636 Reset: HRESULT Reset(void);
 *   aa515638 Skip: HRESULT Skip( ULONG celt);
 */

/* IObjectSafety: documented methods (2 pages).  Signatures recorded verbatim (do not compile):
 *   ms882879 GetInterfaceSafetyOptions: HRESULT GetInterfaceSafetyOptions(REFIIDriid,DWORD*pdwSupportedOptions,DWORD*pdwEnabledOptions);
 *   ms882881 SetInterfaceSafetyOptions: HRESULT SetInterfaceSafetyOptions(REFIIDriid,DWORDdwOptionSetMask,DWORDdwEnabledOptions);
 */

/* IOleAdviseHolder: documented methods (6 pages).  Signatures recorded verbatim (do not compile):
 *   ms882882 Advise: HRESULT Advise( IAdviseSink* pAdvise,DWORD* pdwConnection);
 *   ms882883 EnumAdvise: HRESULT EnumAdvise( IENumSTATDATA* ppEnumAdvise);
 *   ms882885 SendOnClose: 
 *   ms882886 SendOnRename: HRESULT SendOnRename( IMoniker* pmk);
 *   ms882887 SendOnSave: 
 *   ms882889 Unadvise: HRESULT Unadvise(DWORDdwConnection);
 */

/* IOleClientSite: documented methods (5 pages).  Signatures recorded verbatim (do not compile):
 *   ms882891 GetMoniker: HRESULT GetMoniker( DWORD dwAssign, DWORD dwWhichMoniker, IMoniker** ppmk);
 *   ms882893 OnShowWindow: HRESULT OnShowWindow( BOOL fShow);
 *   ms882894 RequestNewObjectLayout: HRESULT RequestNewObjectLayout();
 *   ms882895 SaveObject: HRESULT SaveObject(void);
 *   ms882896 ShowObject: HRESULT ShowObject();
 */

/* IOleContainer: documented methods (2 pages).  Signatures recorded verbatim (do not compile):
 *   aa519256 EnumObjects: HRESULT EnumObjects( DWORDgrfFlags, //Value specifying what is to be enumerated IEnumUnknown**ppenum //Address of output variable that receives the );
 *   aa519258 LockContainer: HRESULT LockContainer( BOOLfLock //Value indicating lock or unlock );
 */

/* IOleControlSite: documented methods (7 pages).  Signatures recorded verbatim (do not compile):
 *   aa519259 GetExtendedControl: HRESULT GetExtendedControl( IDispatch** ppDisp);
 *   aa519261 LockInPlaceActive: HRESULT LockInPlaceActive( BOOL fLock);
 *   aa519262 OnControlInfoChanged: HRESULT OnControlInfoChanged(void);
 *   aa519263 OnFocus: HRESULT OnFocus( BOOL fGotFocus);
 *   aa519264 ShowPropertyFrame: HRESULT ShowPropertyFrame(void);
 *   aa519265 TransformCoords: HRESULT TransformCoords( POINTL* pPtlHimetric , POINTF* pPtfContainer , DWORD dwFlags);
 *   aa519266 TranslateAccelerator: HRESULT TranslateAccelerator( LPMSG pMsg , DWORD grfModifiers);
 */

/* IOleInPlaceSite: documented methods (7 pages).  Signatures recorded verbatim (do not compile):
 *   aa519268 CanInPlaceActivate: HRESULT CanInPlaceActivate();
 *   aa519271 GetWindowContext: HRESULT GetWindowContext( IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);
 *   aa519273 OnInPlaceActivate: HRESULT OnInPlaceActivate();
 *   aa519274 OnInPlaceDeactivate: HRESULT OnInPlaceDeactivate();
 *   aa519275 OnPosRectChange: HRESULT OnPosRectChange( LPCRECT lprcPosRect);
 *   aa519277 OnUIDeactivate: HRESULT OnUIDeactivate( BOOL fUndoable);
 *   aa519278 Scroll: HRESULT Scroll( SIZE scrollExtent);
 */

/* IOleLink: documented methods (11 pages).  Signatures recorded verbatim (do not compile):
 *   ms882901 BindIfRunning: HRESULT BindIfRunning(void);
 *   ms882902 BindToSource: HRESULT BindToSource(DWORDbindflags,IBindCtx* pbc);
 *   ms882903 GetBoundSource: HRESULT GetBoundSource(IUnknown** ppunk);
 *   ms882904 GetSourceDisplayName: HRESULT GetSourceDisplayName(LPOLESTR* ppszDisplayName);
 *   ms882905 GetSourceMoniker: HRESULT GetSourceMoniker(IMoniker** ppmk);
 *   ms882906 GetUpdateOptions: HRESULT GetUpdateOptions(DWORD* pdwUpdateOpt);
 *   ms882908 SetSourceDisplayName: HRESULT SetSourceDisplayName(LPCOLESTRpszStatusText);
 *   ms882909 SetSourceMoniker: HRESULT SetSourceMoniker(IMoniker* pmk,REFCLSIDrclsid);
 *   ms882910 SetUpdateOptions: HRESULT SetUpdateOptions(DWORDdwUpdateOpt);
 *   ms882911 UnbindSource: HRESULT UnbindSource(void);
 *   ms882912 Update: HRESULT Update(IBindCtx* pbc);
 */

/* IOleObject: documented methods (20 pages).  Signatures recorded verbatim (do not compile):
 *   ms882913 Advise: HRESULT Advise( IAdviseSink* pAdvSink, DWORD* pdwConnection);
 *   ms882914 Close: HRESULT Close( DWORD dwSaveOption);
 *   ms882915 DoVerb: HRESULT DoVerb( LONG iVerb, LPMSG lpmsg, IOleClientSite* pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect );
 *   ms882916 EnumAdvise: HRESULT IEnumSTATDATA( IEnumSTATDATA** ppenumAdvise);
 *   ms882917 EnumVerbs: HRESULT EnumVerbs( IEnumOleVerb** ppEnumOleVerb);
 *   ms882918 GetClientSite: HRESULT GetClientSite( IOleClientSite** ppClientSite);
 *   ms882919 GetClipboardData: HRESULT GetClipboardData( DWORD dwReserved, IDataObject** ppDataObject);
 *   ms882920 GetExtent: HRESULT GetExtent( DWORD dwDrawAspect, SIZEL* psizel);
 *   ms882921 GetMiscStatus: HRESULT GetMiscStatus( DWORD dwAspect, DWORD* pdwStatus);
 *   ms882922 GetMoniker: HRESULT GetMoinker( DWORD dwAssign, DWORDdwWhichMoniker, IMoniker** ppmk );
 *   ms882923 GetUserClassID: HRESULT GetUserClassID( CLSID* pClsid);
 *   ms882924 GetUserType: HRESULT GetUserType( DWORD dwFormOfType, LPOLESTR* pszUserType);
 *   ms882925 InitFromData: HRESULT InitFromData( IDataObject* pDataObject, BOOL fCreation, DWORD dwReserved);
 *   ms882926 IsUpToDate: HRESULT IsUpToDate();
 *   ms882928 SetClientSite: HRESULT SetClientSite( IOleClientSite* pClientSite);
 *   ms882929 SetColorScheme: HRESULT SetColorScheme( LOGPALETTE* pLogpal);
 *   ms882930 SetExtent: HRESULT SetExtent( DWORD dwDrawAspect, SIZEL* psizel);
 *   ms882931 SetHostNames: HRESULT SetHostNames( LPCOLESTR szContainerApp, LPCOLESTR szContainerObj);
 *   ms882933 Unadvise: HRESULT Unadvise( DWORD dwConnection);
 *   ms882934 Update: HRESULT Update();
 */

/* IOleWindow: documented methods (2 pages).  Signatures recorded verbatim (do not compile):
 *   aa519279 ContextSensitiveHelp: HRESULT ContextSensitiveHelp( BOOL fEnterMode);
 *   aa519280 GetWindow: HRESULT GetWindow( HWND * phwnd);
 */

/* IParseDisplayName: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms882936 ParseDisplayName: HRESULT ParseDisplayName(IBindCtx* pbc,LPOLESTR pszDisplayName, ULONG* pchEaten,IMoniker** ppmkOut);
 */

/* IPersist: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms883501 GetClassID: HRESULT GetClassID( CLSID* pClassID);
 */

/* IPersistStorage: documented methods (6 pages).  Signatures recorded verbatim (do not compile):
 *   ms883673 HandsOffStorage: HRESULT HandsOfStorage(void);
 *   ms883686 InitNew: HRESULT InitNew( IStorage* pStg);
 *   ms883704 IsDirty: HRESULT IsDirty(void);
 *   ms883717 Load: HRESULT Load( IStorage* pStg);
 *   ms883726 Save: HRESULT Save( IStorage* pStgSave, BOOL fSameAsLoad);
 *   ms883737 SaveCompleted: HRESULT SaveCompleted( IStorage* pStgNew);
 */

/* IPersistStream: documented methods (4 pages).  Signatures recorded verbatim (do not compile):
 *   ms883746 GetSizeMax: HRESULT GetSizeMax(ULARGE_INTEGER* pcbSize);
 *   ms883830 IsDirty: HRESULT IsDirty(void);
 *   ms883840 Load: HRESULT Load(IStream* pStm);
 *   ms883850 Save: HRESULT Save(IStream* pStm,BOOLfClearDirty);
 */

/* IPersistStreamInit: documented methods (5 pages).  Signatures recorded verbatim (do not compile):
 *   ms883758 GetSizeMax: HRESULT GetSizeMax(ULARGE_INTEGER* pcbSize);
 *   ms883767 InitNew: HRESULT InitNew(void);
 *   ms883784 IsDirty: HRESULT IsDirty(void);
 *   ms883792 Load: HRESULT Load(LPSTREAM pStm);
 *   ms883806 Save: HRESULT Save(LPSTREAM pStm,BOOL fClearDirty);
 */

/* IProgressNotify: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms884240 OnProgress: HRESULT OnProgress(DWORDdwProgressCurrent,DWORDdwProgressMaximum,BOOLfAccurate,BOOLfOwner);
 */

/* IProvideClassInfo: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms884308 GetClassInfo: HRESULT GetClassInfo(ITypeInfo** ppTI);
 */

/* IProvideClassInfo2: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms884278 GetGUID: HRESULT GetGUID(DWORDdwGuidKind,GUID* pGUID);
 */

/* IROTData: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms884587 GetComparisonData: HRESULT GetComparisonData(byte* pbData,ULONG cbMax,ULONG* pcbData);
 */

/* IRootStorage: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms884586 SwitchToFile: HRESULT SwitchTofFile( LPOLESTR pszFile);
 */

/* IRunnableObject: documented methods (5 pages).  Signatures recorded verbatim (do not compile):
 *   ms884589 GetRunningClass: HRESULT GetRunningClass(LPCLSID lpClsid);
 *   ms884590 IsRunning: BOOL IsRunning();
 *   ms884593 LockRunning: HRESULT LockRunning(BOOL fLock,BOOL fLastUnlockCloses);
 *   ms884594 Run: HRESULT Run(LPBC lpbc);
 *   ms884595 SetContainedObject: HRESULT SetContainedObject(BOOL fContained);
 */

/* ISequentialStream: documented methods (2 pages).  Signatures recorded verbatim (do not compile):
 *   ms886039 Read: HRESULT Read(void* pv,ULONG cb,ULONG* pcbRead);
 *   ms886049 Write: HRESULT Write(void const* pv,ULONG cb,ULONG* pcbWritten);
 */

/* IServerSecurity: documented methods (4 pages).  Signatures recorded verbatim (do not compile):
 *   ms886057 ImpersonateClient: 
 *   ms886067 IsImpersonating: 
 *   ms886085 QueryBlanket: HRESULT QueryBlanket(DWORD* pAuthnSvc,DWORD* pAuthzSvc,OLECHAR** pServerPrincName,DWORD* pAuthnLevel,DWORD* pImpLevel,RPC_AUTHZ_HANDLE* pPrivs,DWORD* pCapabilities);
 *   ms886097 RevertToSelf: 
 */

/* IStdMarshalInfo: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms890547 GetClassForHandler: HRESULT GetClassForHandler(DWORD dwDestContext,void* pvDestContext,CLSID* pClsid);
 */

/* IViewObject: documented methods (6 pages).  Signatures recorded verbatim (do not compile):
 *   ms891568 Draw: HRESULT Draw( DWORD dwAspect, LONG lindex, void* pvAspect, DVTARGETDEVICE* ptd, HDC hicTargetDev, HDC hdcDraw, const LPRECTL lprcBounds, const LPRECTL lprcWBounds, BOOL (*) (DWORD) pfnContinue, DWORD 
 *   ms891597 Freeze: HRESULT Freeze( DWORD dwAspect, LONG lindex, void* pvAspect, DWORD* pdwFreeze);
 *   ms891602 GetAdvise: HRESULT GetAdvise( DWORD* pdwAspect, DWORD* padvf, IAdviseSink** ppAdvSink);
 *   ms891695 GetColorSet: HRESULT GetColorSet( DWORD dwAspect, LONG lindex, void* pvAspect, DVTARGETDEVICE* ptd, HDChicTargetDev, LOGPALETTE** ppColorSet );
 *   ms891709 SetAdvise: HRESULT SetAdvise( DWORD dwAspect, DWORD advf, IAdviseSink* pAdvSink);
 *   ms891710 Unfreeze: HRESULT Unfreeze( DWORD dwFreeze);
 */

/* IViewObject2: documented methods (1 page).  Signatures recorded verbatim (do not compile):
 *   ms891559 GetExtent: HRESULT GetExtent(DWORDdwAspect,LONGlindex,DVTARGETDEVICEptd,LPSIZELlpsizel);
 */

/* ================================================================== */

#endif /* AKARI_OLEAUTO_H */
