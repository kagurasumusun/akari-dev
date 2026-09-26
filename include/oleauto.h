/*
 * oleauto.h -- OLE Automation entry points for Windows CE.
 *
 * Part of the WinCE development API surface kit.  Covers CE 4.2, 5.0 and 6.0.
 *
 * The CE SDK splits the automation surface in two: oaidl.h carries the types --
 * VARIANT, SAFEARRAY, TYPEDESC, the enumerations, the descriptor records -- and
 * this header carries the WINOLEAUTAPI entry points, including oaidl.h for the
 * types it needs.  The kit previously had both halves in oaidl.h; the
 * prototypes are here now, where CE puts them, so that #include <oleauto.h>
 * finds them.
 *
 * oaidl.h is left declaring the types and no longer declares any function.
 */
#ifndef AKARI_WCE_OLEAUTO_H
#define AKARI_WCE_OLEAUTO_H

#include <wcever.h>
#include <windef.h>
#include <winnt.h>
#include <oaidl.h>

#ifndef _OLEAUTO_
#define _OLEAUTO_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINOLEAUTAPI
#define WINOLEAUTAPI         AKARI_DLLIMPORT
#define WINOLEAUTAPI_(t)     AKARI_DLLIMPORT t
#endif

/* ------------------------------------------------------- prototypes */

WINOLEAUTAPI_(HRESULT) BstrFromVector(SAFEARRAY *psa, BSTR *pbstr);
WINOLEAUTAPI_(HRESULT) CreateErrorInfo(ICreateErrorInfo ** pperrinfo);
WINOLEAUTAPI_(HRESULT) CreateTypeLib2(SYSKIND syskind, LPCOLESTR szFile, ICreateTypeLib2 **ppctlib);
WINOLEAUTAPI_(HRESULT) DispCallFunc(void * pvInstance, ULONG oVft, CALLCONV cc, VARTYPE vtReturn, UINT cActuals, VARTYPE * prgvt, VARIANTARG ** prgpvarg, VARIANT * pvargResult);
WINOLEAUTAPI_(HRESULT) DispGetIDsOfNames(ITypeInfo * ptinfo, OLECHAR ** rgszNames, UINT cNames, DISPID * rgdispid);
WINOLEAUTAPI_(HRESULT) DispGetParam(DISPPARAMS * pdispparams, UINT position, VARTYPE vtTarg, VARIANT * pvarResult, UINT * puArgErr);
WINOLEAUTAPI_(HRESULT) DispInvoke(void * _this, ITypeInfo * ptinfo, DISPID dispidMember, WORD wFlags, DISPPARAMS * pparams, VARIANT * pvarResult, EXCEPINFO * pexcepinfo, UINT * puArgErr);
WINOLEAUTAPI_(HRESULT) FreePropVariantArray(ULONG cVariants, PROPVARIANT * rgvars);
WINOLEAUTAPI_(HRESULT) GetErrorInfo(ULONG dwReserved, IErrorInfo ** pperrinfo);
WINOLEAUTAPI_(HRESULT) LoadRegTypeLib(REFGUID rguid, WORD wVerMajor, WORD wVerMinor, LCID lcid, ITypeLib ** pptlib);
WINOLEAUTAPI_(HRESULT) LoadTypeLib(const OLECHAR *szFile, ITypeLib ** pptlib);
WINOLEAUTAPI_(HRESULT) PropVariantClear(PROPVARIANT * pvar);
WINOLEAUTAPI_(HRESULT) PropVariantCopy(PROPVARIANT * pvarDest, const PROPVARIANT * pvarSrc);
WINOLEAUTAPI_(HRESULT) RegisterTypeLib(ITypeLib * ptlib, OLECHAR *szFullPath, OLECHAR *szHelpDir);
WINOLEAUTAPI_(HRESULT) SafeArrayAccessData(SAFEARRAY * psa, void HUGEP** ppvData);
WINOLEAUTAPI_(HRESULT) SafeArrayAllocData(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayAllocDescriptor(UINT cDims, SAFEARRAY ** ppsaOut);
WINOLEAUTAPI_(HRESULT) SafeArrayCopy(SAFEARRAY * psa, SAFEARRAY ** ppsaOut);
WINOLEAUTAPI_(HRESULT) SafeArrayCopyData(SAFEARRAY *psaSource, SAFEARRAY *psaTarget);
WINOLEAUTAPI_(SAFEARRAY *) SafeArrayCreate(VARTYPE vt, UINT cDims, SAFEARRAYBOUND * rgsabound);
WINOLEAUTAPI_(SAFEARRAY *) SafeArrayCreateVector(VARTYPE vt, LONG lLbound, ULONG cElements);
WINOLEAUTAPI_(HRESULT) SafeArrayDestroy(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayDestroyData(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayDestroyDescriptor(SAFEARRAY * psa);
WINOLEAUTAPI_(UINT) SafeArrayGetDim(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayGetElement(SAFEARRAY * psa, LONG * rgIndices, void * pv);
WINOLEAUTAPI_(UINT) SafeArrayGetElemsize(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayGetLBound(SAFEARRAY * psa, UINT nDim, LONG * plLbound);
WINOLEAUTAPI_(HRESULT) SafeArrayGetUBound(SAFEARRAY * psa, UINT nDim, LONG * plUbound);
WINOLEAUTAPI_(HRESULT) SafeArrayLock(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayPtrOfIndex(SAFEARRAY * psa, LONG * rgIndices, void ** ppvData);
WINOLEAUTAPI_(HRESULT) SafeArrayPutElement(SAFEARRAY * psa, LONG * rgIndices, void * pv);
WINOLEAUTAPI_(HRESULT) SafeArrayRedim(SAFEARRAY * psa, SAFEARRAYBOUND * psaboundNew);
WINOLEAUTAPI_(HRESULT) SafeArrayUnaccessData(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SafeArrayUnlock(SAFEARRAY * psa);
WINOLEAUTAPI_(HRESULT) SetErrorInfo(ULONG dwReserved, IErrorInfo * perrinfo);
WINOLEAUTAPI_(BSTR) SysAllocString(const OLECHAR *);
WINOLEAUTAPI_(BSTR) SysAllocStringByteLen(LPCSTR psz, UINT len);
WINOLEAUTAPI_(BSTR) SysAllocStringLen(const OLECHAR *, UINT len);
WINOLEAUTAPI_(void) SysFreeString(BSTR);
WINOLEAUTAPI_(INT) SysReAllocString(BSTR *, const OLECHAR *);
WINOLEAUTAPI_(INT) SysReAllocStringLen(BSTR *, const OLECHAR *, UINT);
WINOLEAUTAPI_(UINT) SysStringByteLen(BSTR bstr);
WINOLEAUTAPI_(UINT) SysStringLen(BSTR);
WINOLEAUTAPI_(INT) SystemTimeToVariantTime(LPSYSTEMTIME lpSystemTime, DOUBLE *pvtime);
WINOLEAUTAPI_(HRESULT) VarBoolFromCy(CY cyIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromDate(DATE dateIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromDec(DECIMAL *pdecIn, VARIANT_BOOL *pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromDisp(IDispatch * pdispIn, LCID lcid, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromI1(CHAR cIn, VARIANT_BOOL *pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromI2(SHORT sIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromI4(LONG lIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromR4(FLOAT fltIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromR8(DOUBLE dblIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromUI1(BYTE bIn, VARIANT_BOOL * pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromUI2(USHORT uiIn, VARIANT_BOOL *pboolOut);
WINOLEAUTAPI_(HRESULT) VarBoolFromUI4(ULONG ulIn, VARIANT_BOOL *pboolOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromBool(VARIANT_BOOL boolIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromCy(CY cyIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromDate(DATE dateIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromDec(DECIMAL *pdecIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromDisp(IDispatch * pdispIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromI1(CHAR cIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromI2(SHORT iVal, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromI4(LONG lIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromR4(FLOAT fltIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromR8(DOUBLE dblIn, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromUI1(BYTE bVal, LCID lcid, ULONG dwFlags, BSTR * pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromUI2(USHORT uiIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
WINOLEAUTAPI_(HRESULT) VarBstrFromUI4(ULONG ulIn, LCID lcid, ULONG dwFlags, BSTR *pbstrOut);
WINOLEAUTAPI_(HRESULT) VarCyFromBool(VARIANT_BOOL boolIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromDate(DATE dateIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromDec(DECIMAL *pdecIn, CY *pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromDisp(IDispatch * pdispIn, LCID lcid, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromI1(CHAR cIn, CY *pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromI2(SHORT sIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromI4(LONG lIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromR4(FLOAT fltIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromR8(DOUBLE dblIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromUI1(BYTE bIn, CY * pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromUI2(USHORT uiIn, CY *pcyOut);
WINOLEAUTAPI_(HRESULT) VarCyFromUI4(ULONG ulIn, CY *pcyOut);
WINOLEAUTAPI_(HRESULT) VarDateFromBool(VARIANT_BOOL boolIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromCy(CY cyIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromDec(DECIMAL *pdecIn, DATE *pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromDisp(IDispatch * pdispIn, LCID lcid, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromI1(CHAR cIn, DATE *pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromI2(SHORT sIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromI4(LONG lIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromR4(FLOAT fltIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromR8(DOUBLE dblIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, DATE *pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromUdate(UDATE *pudateIn, ULONG dwFlags, DATE *pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromUI1(BYTE bIn, DATE * pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromUI2(USHORT uiIn, DATE *pdateOut);
WINOLEAUTAPI_(HRESULT) VarDateFromUI4(ULONG ulIn, DATE *pdateOut);
WINOLEAUTAPI_(HRESULT) VarDecFromBool(VARIANT_BOOL boolIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromCy(CY cyIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromDate(DATE dateIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromDisp(IDispatch *pdispIn, LCID lcid, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromI1(CHAR cIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromI2(SHORT uiIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromI4(LONG lIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromR4(FLOAT fltIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromR8(DOUBLE dblIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromUI1(BYTE bIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromUI2(USHORT uiIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarDecFromUI4(ULONG ulIn, DECIMAL *pdecOut);
WINOLEAUTAPI_(HRESULT) VarI1FromBool(VARIANT_BOOL boolIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromCy(CY cyIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromDate(DATE dateIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromDec(DECIMAL *pdecIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromDisp(IDispatch *pdispIn, LCID lcid, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromI2(SHORT uiIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromI4(LONG lIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromR4(FLOAT fltIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromR8(DOUBLE dblIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromUI1(BYTE bIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromUI2(USHORT uiIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI1FromUI4(ULONG ulIn, CHAR *pcOut);
WINOLEAUTAPI_(HRESULT) VarI2FromBool(VARIANT_BOOL boolIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromCy(CY cyIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromDate(DATE dateIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromDec(DECIMAL *pdecIn, SHORT *psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromDisp(IDispatch * pdispIn, LCID lcid, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromI1(CHAR cIn, SHORT *psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromI4(LONG lIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromR4(FLOAT fltIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromR8(DOUBLE dblIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromUI1(BYTE bIn, SHORT * psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromUI2(USHORT uiIn, SHORT *psOut);
WINOLEAUTAPI_(HRESULT) VarI2FromUI4(ULONG ulIn, SHORT *psOut);
WINOLEAUTAPI_(HRESULT) VarI4FromBool(VARIANT_BOOL boolIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromCy(CY cyIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromDate(DATE dateIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromDec(DECIMAL *pdecIn, LONG *plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromDisp(IDispatch * pdispIn, LCID lcid, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromI1(CHAR cIn, LONG *plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromI2(SHORT sIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromR4(FLOAT fltIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromR8(DOUBLE dblIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromUI1(BYTE bIn, LONG * plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromUI2(USHORT uiIn, LONG *plOut);
WINOLEAUTAPI_(HRESULT) VarI4FromUI4(ULONG ulIn, LONG *plOut);
WINOLEAUTAPI_(HRESULT) VariantChangeType(VARIANTARG * pvargDest, VARIANTARG * pvarSrc, USHORT wFlags, VARTYPE vt);
WINOLEAUTAPI_(HRESULT) VariantChangeTypeEx(VARIANTARG * pvargDest, VARIANTARG * pvarSrc, LCID lcid, USHORT wFlags, VARTYPE vt);
WINOLEAUTAPI_(HRESULT) VariantClear(VARIANTARG * pvarg);
WINOLEAUTAPI_(HRESULT) VariantCopy(VARIANTARG * pvargDest, VARIANTARG * pvargSrc);
WINOLEAUTAPI_(HRESULT) VariantCopyInd(VARIANT * pvarDest, VARIANTARG * pvargSrc);
WINOLEAUTAPI_(void) VariantInit(VARIANTARG * pvarg);
WINOLEAUTAPI_(INT) VariantTimeToSystemTime(DOUBLE vtime, LPSYSTEMTIME lpSystemTime);
WINOLEAUTAPI_(HRESULT) VarNumFromParseNum(NUMPARSE * pnumprs, BYTE * rgbDig, ULONG dwVtBits, VARIANT * pvar);
WINOLEAUTAPI_(HRESULT) VarParseNumFromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, NUMPARSE * pnumprs, BYTE * rgbDig);
WINOLEAUTAPI_(HRESULT) VarR4FromBool(VARIANT_BOOL boolIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromCy(CY cyIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromDate(DATE dateIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromDec(DECIMAL *pdecIn, FLOAT *pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromDisp(IDispatch * pdispIn, LCID lcid, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromI1(CHAR cIn, FLOAT *pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromI2(SHORT sIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromI4(LONG lIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromR8(DOUBLE dblIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, FLOAT *pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromUI1(BYTE bIn, FLOAT * pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromUI2(USHORT uiIn, FLOAT *pfltOut);
WINOLEAUTAPI_(HRESULT) VarR4FromUI4(ULONG ulIn, FLOAT *pfltOut);
WINOLEAUTAPI_(HRESULT) VarR8FromBool(VARIANT_BOOL boolIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromCy(CY cyIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromDate(DATE dateIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromDec(DECIMAL *pdecIn, DOUBLE *pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromDisp(IDispatch * pdispIn, LCID lcid, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromI1(CHAR cIn, DOUBLE *pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromI2(SHORT sIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromI4(LONG lIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromR4(FLOAT fltIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, DOUBLE *pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromUI1(BYTE bIn, DOUBLE * pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromUI2(USHORT uiIn, DOUBLE *pdblOut);
WINOLEAUTAPI_(HRESULT) VarR8FromUI4(ULONG ulIn, DOUBLE *pdblOut);
WINOLEAUTAPI_(HRESULT) VarUdateFromDate(DATE dateIn, ULONG dwFlags, UDATE *pudateOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromBool(VARIANT_BOOL boolIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromCy(CY cyIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromDate(DATE dateIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromDec(DECIMAL *pdecIn, BYTE *pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromDisp(IDispatch * pdispIn, LCID lcid, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromI1(CHAR cIn, BYTE *pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromI2(SHORT sIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromI4(LONG lIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromR4(FLOAT fltIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromR8(DOUBLE dblIn, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromStr(OLECHAR * strIn, LCID lcid, ULONG dwFlags, BYTE * pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromUI2(USHORT uiIn, BYTE *pbOut);
WINOLEAUTAPI_(HRESULT) VarUI1FromUI4(ULONG ulIn, BYTE *pbOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromBool(VARIANT_BOOL boolIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromCy(CY cyIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromDate(DATE dateIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromDec(DECIMAL *pdecIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromDisp(IDispatch *pdispIn, LCID lcid, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromI1(CHAR cIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromI2(SHORT uiIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromI4(LONG lIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromR4(FLOAT fltIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromR8(DOUBLE dblIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromUI1(BYTE bIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI2FromUI4(ULONG ulIn, USHORT *puiOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromBool(VARIANT_BOOL boolIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromCy(CY cyIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromDate(DATE dateIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromDec(DECIMAL *pdecIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromDisp(IDispatch *pdispIn, LCID lcid, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromI1(CHAR cIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromI2(SHORT uiIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromI4(LONG lIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromR4(FLOAT fltIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromR8(DOUBLE dblIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromUI1(BYTE bIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VarUI4FromUI2(USHORT uiIn, ULONG *pulOut);
WINOLEAUTAPI_(HRESULT) VectorFromBstr(BSTR bstr, SAFEARRAY ** ppsa);
unsigned long __RPC_USER BSTR_UserSize(unsigned long *pFlags, unsigned long dw, BSTR *pBstr);
unsigned char * __RPC_USER BSTR_UserMarshal(unsigned long *pFlags, unsigned char *pBuf, BSTR *pBstr);
unsigned char * __RPC_USER BSTR_UserUnmarshal(unsigned long *pFlags, unsigned char *pBuf, BSTR *pBstr);
void __RPC_USER BSTR_UserFree(unsigned long *pFlags, BSTR *pBstr);
unsigned long __RPC_USER LPSAFEARRAY_UserSize(unsigned long *pFlags, unsigned long dw, LPSAFEARRAY *ppArray);
unsigned char * __RPC_USER LPSAFEARRAY_UserMarshal(unsigned long *pFlags, unsigned char *pBuf, LPSAFEARRAY *ppArray);
unsigned char * __RPC_USER LPSAFEARRAY_UserUnmarshal(unsigned long *pFlags, unsigned char *pBuf, LPSAFEARRAY *ppArray);
void __RPC_USER LPSAFEARRAY_UserFree(unsigned long *pFlags, LPSAFEARRAY *ppArray);
unsigned long __RPC_USER VARIANT_UserSize(unsigned long *pFlags, unsigned long dw, VARIANT *pVariant);
unsigned char * __RPC_USER VARIANT_UserMarshal(unsigned long *pFlags, unsigned char *pBuf, VARIANT *pVariant);
unsigned char * __RPC_USER VARIANT_UserUnmarshal(unsigned long *pFlags, unsigned char *pBuf, VARIANT *pVariant);
void __RPC_USER VARIANT_UserFree(unsigned long *pFlags, VARIANT *pVariant);
#ifdef __cplusplus
}
#endif

#endif /* _OLEAUTO_ */
#endif /* AKARI_WCE_OLEAUTO_H */
