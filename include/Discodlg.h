/*
 * Discodlg.h -- Remote Desktop ActiveX Control interface records for
 *               Windows CE (Discodlg.h / Mstsax.idl layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every record is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Remote Desktop Protocol :: RDP Reference ::
 * Remote Desktop ActiveX Control Interface" (tools/manifests/rdp.manifest);
 * method signatures were cross-read against the CE 6.0
 * (v=winembedded.60) twins (tools/manifests/m54-ce60.manifest).
 *
 * Interface-record policy (M44/M53): every interface page prints
 * "Header: Discodlg.h, Mstsax.idl" and "Link Library: Mstsax.lib", and
 * the method pages print IDL-style method syntax only -- the interfaces
 * are recorded as opaque forward typedefs with their documented method
 * lists and verbatim method signatures in comments (no vtables, no
 * defs; see docs/inventory.md M54).
 *
 * OS Versions: "Windows CE .NET 4.0 and later" on every page.
 */

#ifndef AKARI_DISCODLG_H
#define AKARI_DISCODLG_H

#include "Windef.h"
#include "Objbase.h"   /* HRESULT, BSTR, VARIANT_BOOL (M44) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Opaque interface records (M44/M53 model).                           */
/* ------------------------------------------------------------------ */

typedef struct IMsRdpClient               IMsRdpClient;
typedef struct IMsRdpClientAdvancedSettings IMsRdpClientAdvancedSettings;
typedef struct IMsRdpClientNonScriptable  IMsRdpClientNonScriptable;
typedef struct IMsRdpClientSecuredSettings IMsRdpClientSecuredSettings;
typedef struct IMsTscAdvancedSettings     IMsTscAdvancedSettings;
typedef struct IMsTscAx                   IMsTscAx;
typedef struct IMsTscAxEvents             IMsTscAxEvents;
typedef struct IMsTscNonScriptable        IMsTscNonScriptable;
typedef struct IMsTscSecuredSettings      IMsTscSecuredSettings;

/* ------------------------------------------------------------------ */
/* Published enumerations.                                             */
/* ------------------------------------------------------------------ */

/* aa513913 IMsRdpClient::get_ExtendedDisconnectReason parameter
 * enumeration (values printed on the page). */
typedef enum {
    exDiscReasonNoInfo                        = 0x0000,
    exDiscReasonAPIInitiatedDisconnect        = 0x0001,
    exDiscReasonAPIInitiatedLogoff            = 0x0002,
    exDiscReasonServerIdleTimeout             = 0x0003,
    exDiscReasonServerLogonTimeout            = 0x0004,
    exDiscReasonReplacedByOtherConnection     = 0x0005,
    exDiscReasonOutOfMemory                   = 0x0006,
    exDiscReasonServerDeniedConnection        = 0x0007,
    exDiscReasonLicenseInternal               = 0x0100,
    exDiscReasonLicenseNoLicenseServer        = 0x0101,
    exDiscReasonLicenseNoLicense              = 0x0102,
    exDiscReasonLicenseErrClientMsg           = 0x0103,
    exDiscReasonLicenseHwidDoesntMatchLicense = 0x0104,
    exDiscReasonLicenseErrClientLicense       = 0x0105,
    exDiscReasonLicenseCantFinishProtocol     = 0x0106,
    exDiscReasonLicenseClientEndedProtocol    = 0x0107,
    exDiscReasonLicenseErrClientEncryption    = 0x0108,
    exDiscReasonLicenseCantUpgradeLicense     = 0x0109,
    exDiscReasonLicenseNoRemoteConnections    = 0x010A
} ExtendedDisconnectReasonCode;

/* aa513913 also publishes the internal-protocol-error range
 * exDiscReasonProtocolRangeStart (0x1000) through
 * exDiscReasonProtocolRangeEnd (0x7FFF); the range endpoints are
 * recorded in docs/inventory.md M54 (they are value markers, not
 * enumeration members, on the page). */

/* aa513927 IMsRdpClient::RequestClose parameter: the page prints the
 * two ControlCloseStatus names (ControlCloseCanProceed,
 * ControlCloseWaitForEvents) without values -- held. */

/* ------------------------------------------------------------------ */
/* IMsRdpClient (aa513905; methods aa513913/aa513915/aa513927/aa513936;
 * properties aa513922).                                               */
/* ------------------------------------------------------------------ */
/*
 * HRESULT get_ExtendedDisconnectReason(
 *     ExtendedDisconnectReasonCode* pExtendedDisconnectReason);   aa513913
 * HRESULT GetVirtualChannelOptions(
 *     BSTR ChanName, LONG* pChanOptions);                         aa513915
 * HRESULT RequestClose(ControlCloseStatus* pCloseStatus);        aa513927
 * HRESULT SetVirtualChannelOptions(
 *     BSTR chanName, LONG chanOptions);                           aa513936
 */

/* ------------------------------------------------------------------ */
/* IMsRdpClientNonScriptable (aa513916; methods aa513918/aa513920).   */
/* ------------------------------------------------------------------ */
/*
 * HRESULT NotifyRedirectDeviceChange(WPARAM wParam, LPARAM lParam); aa513918
 * HRESULT SendKeys(LONG numKeys, VARIANT_BOOL* pbArrayKeyUp,
 *                  LONG* plKeyData);                              aa513920
 */

/* ------------------------------------------------------------------ */
/* IMsRdpClientSecuredSettings (aa513931; properties aa513933).       */
/* ------------------------------------------------------------------ */
/*
 * HRESULT get_StartProgram(BSTR* pStartProgram);  (properties page) aa513933
 * HRESULT get_WorkDir(BSTR* pWorkDir);                             aa513933
 */

/* ------------------------------------------------------------------ */
/* IMsTscAdvancedSettings (aa513937; 14 method pages).                */
/* ------------------------------------------------------------------ */
/*
 * HRESULT get_allowBackgroundInput(long* pallowBackgroundInput);  aa513942
 * HRESULT put_allowBackgroundInput(long allowBackgroundInput);    aa513953
 * HRESULT get_BitmapPersistence(long* pBitmapPersistence);        aa513944
 * HRESULT put_BitmapPersistence(long bitmapPersistence);          aa513954
 * HRESULT get_Compress(long* pCompress);                          aa513946
 * HRESULT put_Compress(long compress);                            aa513955
 * HRESULT get_ContainerHandledFullScreen(
 *     BOOL* pContainerHandledFullScreen);                         aa513948
 * HRESULT put_ContainerHandledFullScreen(
 *     BOOL containerHandledFullScreen);                           aa513956
 * HRESULT get_DisableRdpdr(BOOL* pDisableRdpdr);                  aa513952
 * HRESULT put_DisableRdpdr(BOOL DisableRdpdr);                    aa513957
 * HRESULT put_IconFile(BSTR IconFile);                            aa513958
 * HRESULT put_IconIndex(LONG IconIndex);                          aa513959
 * HRESULT put_KeyBoardLayoutStr(BSTR KeyBoardLayoutStr);          aa513960
 * HRESULT put_PluginDlls(BSTR pluginList);                        aa513961
 */

/* ------------------------------------------------------------------ */
/* IMsTscAx (aa513962; 23 method pages).                              */
/* ------------------------------------------------------------------ */
/*
 * HRESULT Connect();                                              aa513963
 * HRESULT CreateVirtualChannels(BSTR channelNames);               aa513964
 * HRESULT Disconnect();                                           aa513965
 * HRESULT SendOnVirtualChannel(BSTR ChanName, BSTR ChanData);     aa514278
 * HRESULT get_AdvancedSettings(
 *     IMsTscAdvancedSettings** ppAdvancedSettings);               aa513976
 * HRESULT get_CipherStrength(LONG* pCipherStrength);              aa513977
 * HRESULT get_Connected(short* pIsConnected);                     aa514247
 * HRESULT get_ConnectingText(BSTR* pConnectingText);              aa514248
 * HRESULT put_ConnectingText(BSTR connectingText);                aa514268
 * HRESULT get_DesktopHeight(LONG* pVal);                          aa514249
 * HRESULT get_DesktopWidth(LONG* pVal);                           aa514250
 * HRESULT get_DisconnectedText(BSTR* DisconnectedText);           aa514252
 * HRESULT put_DisconnectedText(BSTR disconnectText);              aa514270
 * HRESULT get_Domain(BSTR* pDomain);                              aa514253
 * HRESULT put_Domain(BSTR domainProperty);                        aa514271
 * HRESULT get_HorizontalScrollBarVisible(
 *     BOOL* pfHScrollVisible);                                    aa514254
 * HRESULT get_SecuredSettings2(
 *     IMsTscSecuredSettings** ppSecuredSettings);                 aa514256
 * HRESULT get_Server(BSTR* Server);                               aa514258
 * HRESULT put_Server(BSTR serverProperty);                        aa514273
 * HRESULT get_UserName(BSTR* pUserName);                          aa514260
 * HRESULT put_UserName(BSTR userName);                            aa514276
 * HRESULT get_Version(BSTR* pVersion);                            aa514262
 * HRESULT get_VerticalScrollBarVisible(BOOL* pfVScrollVisible);   aa514265
 */

/* ------------------------------------------------------------------ */
/* IMsTscAxEvents (aa513966; 9 event pages).                          */
/* ------------------------------------------------------------------ */
/*
 * VOID OnConfirmClose(VARIANT_BOOL* pfAllowClose);                aa513967
 * VOID OnConnected();                                             aa513968
 * VOID OnConnecting();                                            aa513969
 * VOID OnDisconnected(long discReason);                           aa513970
 * VOID OnFatalError(long errorCode);                              aa513971
 * VOID OnIdleTimeoutNotification();                               aa513972
 * VOID OnLoginComplete();                                         aa513973
 * VOID OnRequestContainerMinimize();                              aa513974
 * VOID OnWarning(long warningCode);                               aa513975
 */

/* ------------------------------------------------------------------ */
/* IMsTscNonScriptable (aa514279; 9 method pages).                    */
/* ------------------------------------------------------------------ */
/*
 * HRESULT get_BinaryPassword(BSTR* pBinaryPassword);              aa514281
 * HRESULT put_BinaryPassword(BSTR newPassword);                   aa514289
 * HRESULT get_BinarySalt(BSTR* pSalt);                            aa514283
 * HRESULT put_BinarySalt(BSTR newSalt);                           aa514290
 * HRESULT put_ClearTextPassword(BSTR newClearTextPass);           aa514292
 * HRESULT get_PortablePassword(BSTR* pPortablePass);              aa514285
 * HRESULT put_PortablePassword(BSTR newPortablePassVal);          aa514295
 * HRESULT get_PortableSalt(BSTR* pPortableSalt);                  aa514287
 * HRESULT put_PortableSalt(BSTR newPortableSalt);                 aa514297
 * HRESULT ResetPassword();                                        aa514299
 */

/* ------------------------------------------------------------------ */
/* IMsTscSecuredSettings (aa514300; 4 method pages).                  */
/* ------------------------------------------------------------------ */
/*
 * HRESULT get_StartProgram(BSTR* pStartProgram);                  aa514302
 * HRESULT put_StartProgram(BSTR programName);                     aa514305
 * HRESULT get_WorkDir(BSTR* pWorkDir);                            aa514303
 * HRESULT put_WorkDir(BSTR workingDir);                           aa514307
 */

/* ------------------------------------------------------------------ */
/* IMsRdpClientAdvancedSettings (aa513907) and                      */
/* IMsRdpClientSecuredSettings (aa513931) property sets: the CE book  */
/* documents these interfaces' members as property-description lists   */
/* (ms861195 Bitmap and Caching, ms861243 Connection/Timeout/Interval  */
/* and Event, ms861737 Redirection, aa514412 Keyboard and Mouse,       */
/* aa514423 Other; aa513933 IMsRdpClientSecuredSettings Properties),   */
/* not as per-method pages; the property names are recorded in        */
/* docs/inventory.md M54.                                             */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------
 * Book surface: rdp (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms861195 Bitmap and Caching Properties of IMsRdpClientAdvancedSettings */
/* ms861243 Connection, Timeout, Interval and Event Properties of IMsRdpClientAdvancedSettings */
/* aa513922 IMsRdpClient Properties (Header: Discodlg.h. Mstsax.idl.) */
/* aa513913 IMsRdpClient::get_ExtendedDisconnectReason (Header: Discodlg.h. Mstsax.idl.) */
/* aa513915 IMsRdpClient::GetVirtualChannelOptions (Header: Discodlg.h. Mstsax.idl.) */
/* aa513927 IMsRdpClient::RequestClose (Header: Discodlg.h. Mstsax.idl.) */
/* aa513936 IMsRdpClient::SetVirtualChannelOptions (Header: Discodlg.h. Mstsax.idl.) */
/* aa513909 IMsRdpClientAdvancedSettings Properties */
/* aa513910 IMsRdpClientAdvancedSettings Property Descriptions */
/* aa513918 IMsRdpClientNonScriptable::NotifyRedirectDeviceChange (Header: Discodlg.h. Mstsax.idl.) */
/* aa513920 IMsRdpClientNonScriptable::SendKeys (Header: Discodlg.h. Mstsax.idl.) */
/* aa513933 IMsRdpClientSecuredSettings Properties (Header: Discodlg.h. Mstsax.idl.) */
/* aa513942 IMsTscAdvancedSettings::get_allowBackgroundInput (Header: Discodlg.h. Mstsax.idl.) */
/* aa513944 IMsTscAdvancedSettings::get_BitmapPersistence (Header: Discodlg.h. Mstsax.idl.) */
/* aa513946 IMsTscAdvancedSettings::get_Compress (Header: Discodlg.h. Mstsax.idl.) */
/* aa513948 IMsTscAdvancedSettings::get_ContainerHandledFullScreen (Header: Discodlg.h. Mstsax.idl.) */
/* aa513952 IMsTscAdvancedSettings::get_DisableRdpdr (Header: Discodlg.h. Mstsax.idl.) */
/* aa513953 IMsTscAdvancedSettings::put_allowBackgroundInput (Header: Discodlg.h. Mstsax.idl.) */
/* aa513954 IMsTscAdvancedSettings::put_BitmapPersistence (Header: Discodlg.h. Mstsax.idl.) */
/* aa513955 IMsTscAdvancedSettings::put_Compress (Header: Discodlg.h. Mstsax.idl.) */
/* aa513956 IMsTscAdvancedSettings::put_ContainerHandledFullScreen (Header: Discodlg.h. Mstsax.idl.) */
/* aa513958 IMsTscAdvancedSettings::put_IconFile (Header: Discodlg.h. Mstsax.idl.) */
/* aa513959 IMsTscAdvancedSettings::put_IconIndex (Header: Discodlg.h. Mstsax.idl.) */
/* aa513960 IMsTscAdvancedSettings::put_KeyBoardLayoutStr (Header: Discodlg.h. Mstsax.idl.) */
/* aa513961 IMsTscAdvancedSettings::put_PluginDlls (Header: Discodlg.h. Mstsax.idl.) */
/* aa513963 IMsTscAx::Connect (Header: Discodlg.h. Mstsax.idl.) */
/* aa513964 IMsTscAx::CreateVirtualChannels (Header: Discodlg.h. Mstsax.idl.) */
/* aa513965 IMsTscAx::Disconnect (Header: Discodlg.h. Mstsax.idl.) */
/* aa513976 IMsTscAx::get_AdvancedSettings (Header: Discodlg.h. Mstsax.idl.) */
/* aa513977 IMsTscAx::get_CipherStrength (Header: Discodlg.h. Mstsax.idl.) */
/* aa514247 IMsTscAx::get_Connected (Header: Discodlg.h. Mstsax.idl.) */
/* aa514248 IMsTscAx::get_ConnectingText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514249 IMsTscAx::get_DesktopHeight (Header: Discodlg.h. Mstsax.idl.) */
/* aa514250 IMsTscAx::get_DesktopWidth (Header: Discodlg.h. Mstsax.idl.) */
/* aa514252 IMsTscAx::get_DisconnectedText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514253 IMsTscAx::get_Domain (Header: Discodlg.h. Mstsax.idl.) */
/* aa514254 IMsTscAx::get_HorizontalScrollBarVisible (Header: Discodlg.h. Mstsax.idl.) */
/* aa514256 IMsTscAx::get_SecuredSettings2 (Header: Discodlg.h. Mstsax.idl.) */
/* aa514258 IMsTscAx::get_Server (Header: Discodlg.h. Mstsax.idl.) */
/* aa514260 IMsTscAx::get_UserName (Header: Discodlg.h. Mstsax.idl.) */
/* aa514262 IMsTscAx::get_Version (Header: Discodlg.h. Mstsax.idl.) */
/* aa514265 IMsTscAx::get_VerticalScrollBarVisible (Header: Discodlg.h. Mstsax.idl.) */
/* aa514268 IMsTscAx::put_ConnectingText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514270 IMsTscAx::put_DisconnectedText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514271 IMsTscAx::put_Domain (Header: Discodlg.h. Mstsax.idl.) */
/* aa514273 IMsTscAx::put_Server (Header: Discodlg.h. Mstsax.idl.) */
/* aa514276 IMsTscAx::put_UserName (Header: Discodlg.h. Mstsax.idl.) */
/* aa514278 IMsTscAx::SendOnVirtualChannel (Header: Discodlg.h. Mstsax.idl.) */
/* aa513967 IMsTscAxEvents::OnConfirmClose (Header: Discodlg.h. Mstsax.idl.) */
/* aa513968 IMsTscAxEvents::OnConnected (Header: Discodlg.h. Mstsax.idl.) */
/* aa513969 IMsTscAxEvents::OnConnecting (Header: Discodlg.h. Mstsax.idl.) */
/* aa513970 IMsTscAxEvents::OnDisconnected (Header: Discodlg.h. Mstsax.idl.) */
/* aa513971 IMsTscAxEvents::OnFatalError (Header: Discodlg.h. Mstsax.idl.) */
/* aa513972 IMsTscAxEvents::OnIdleTimeoutNotification (Header: Discodlg.h. Mstsax.idl.) */
/* aa513973 IMsTscAxEvents::OnLoginComplete (Header: Discodlg.h. Mstsax.idl.) */
/* aa513974 IMsTscAxEvents::OnRequestContainerMinimize (Header: Discodlg.h. Mstsax.idl.) */
/* aa513975 IMsTscAxEvents::OnWarning (Header: Discodlg.h. Mstsax.idl.) */
/* aa514281 IMsTscNonScriptable::get_BinaryPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514283 IMsTscNonScriptable::get_BinarySalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514285 IMsTscNonScriptable::get_PortablePassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514287 IMsTscNonScriptable::get_PortableSalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514289 IMsTscNonScriptable::put_BinaryPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514290 IMsTscNonScriptable::put_BinarySalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514292 IMsTscNonScriptable::put_ClearTextPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514295 IMsTscNonScriptable::put_PortablePassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514297 IMsTscNonScriptable::put_PortableSalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514299 IMsTscNonScriptable::ResetPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514302 IMsTscSecuredSettings::get_StartProgram (Header: Discodlg.h. Mstsax.idl.) */
/* aa514303 IMsTscSecuredSettings::get_WorkDir (Header: Discodlg.h. Mstsax.idl.) */
/* aa514305 IMsTscSecuredSettings::put_StartProgram (Header: Discodlg.h. Mstsax.idl.) */
/* aa514307 IMsTscSecuredSettings::put_WorkDir (Header: Discodlg.h. Mstsax.idl.) */
/* aa514412 Keyboard and Mouse Properties of IMsRdpClientAdvancedSettings */
/* aa514423 Other IMsRdpClientAdvancedSettings Properties */
/* aa513318 RDP Functions */
/* aa513320 RDP Structures */
/* ms861737 Redirection Properties of IMsRdpClientAdvancedSettings */
/* ms861766 Remote Desktop ActiveX Control Interface */
/* aa513957 IMsTscAdvancedSettings::put_DisableRdpdr (Header: Discodlg.h, Mstsax.idl.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DISCODLG_H */
