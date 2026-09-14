# The VoIP COM interfaces the pages name only by `.idl`

Measured at M112.  Three documented `Header:` tokens have no
corresponding `.h` in this tree and no `.h` spelling is printed by
any page: `Voipmediamanager.idl`, `Voipprov.idl`, `Voipstore.idl`.
They name eight COM interfaces that the tree did not declare:

| interface | `.idl` token | interface page | method pages with a print |
|---|---|---|---|
| `IVoIPCallLogDB` | `Voipstore.idl` | ms911672 | 6 |
| `IVoIPCallLogDBEnum` | `Voipstore.idl` | ms911665 | 3 |
| `IVoIPCallRecord` | `Voipstore.idl` | ms911681 | 9 |
| `IVoIPCallerInfoDB` | `Voipstore.idl` | ms911650 | 7 |
| `IVoIPCallerInfoDBEnum` | `Voipstore.idl` | ms911546 | 3 |
| `IVoIPCallerInfoRecord` | `Voipstore.idl` | ms911658 | 9 |
| `IVoIPDirectoryClient` | `Voipprov.idl` | ms911957 | 3 |
| `IVoIPMediaMgr` | `Voipmediamanager.idl` | ms912032 | 21 |

61 method prints, reproduced verbatim below.  Every one is the
page's own code block; nothing is re-typed or reformatted beyond
collapsing the HTML whitespace.

## Why no vtable is declared

A COM interface declaration *is* its vtable layout, so publishing
one asserts a method order.  The only order the pages publish is
the **alphabetical** Methods table on each interface page
(e.g. ms912032 lists `AnswerSession`,
`ConferenceSessions`, `CreatePCToPCSession`, ... `Uninitialize`).
Alphabetical is not vtable order, and no page prints the `idl`
body, a `STDMETHOD`-ordered block, or a header excerpt.  Writing a
vtable from an alphabetical list would invent the ABI, which this
tree does not do: the interfaces are therefore **recorded, not
declared**, and `include/Voipmanager.h` carries a hold note that
points here.

The nine interface-overview pages print no code block at all
(they carry only the alphabetical table), which is why the count
above is 61 of 70 rows.

## `IVoIPCallLogDB`

Interface page ms911672; `Header:` row `Voipstore.idl`.

```c
/* Capacity (ms911663) -- Windows CE .NET 4.2 and later. */
HRESULT put_Capacity( intcRecords);HRESULT get_Capacity( int* cRecords);
/* CreateRecord (ms911664) -- Windows CE .NET 4.2 and later. */
HRESULT CreateRecord( VoIPCallType vct,IVoIPCallRecord** ppiRecord );
/* IncomingEnumerator (ms911670) -- Windows CE .NET 4.2 and later. */
HRESULT get_IncomingEnumerator( IVoIPCallLogDBEnum**ppiEnum);
/* Init (ms911671) -- Windows CE .NET 4.2 and later. */
HRESULT Init( BSTRbstrURI);
/* MissedEnumerator (ms911673) -- Windows CE .NET 4.2 and later. */
HRESULT get_MissedEnumerator( IVoIPCallLogDBEnum** ppiEnum);
/* OutgoingEnumerator (ms911674) -- Windows CE .NET 4.2 and later. */
HRESULT get_OutgoingEnumerator( IVoIPCallLogDBEnum** ppiEnum);
```

## `IVoIPCallLogDBEnum`

Interface page ms911665; `Header:` row `Voipstore.idl`.

```c
/* Next (ms911667) -- Windows CE .NET 4.2 and later. */
HRESULT Next( unsigned longcelt,IVoIPCallRecord**rgVoIPCallRecord,unsigned long*pceltFetched );
/* Reset (ms911668) -- Windows CE .NET 4.2 and later. */
HRESULT Reset();
/* Skip (ms911669) -- Windows CE .NET 4.2 and later. */
HRESULT Skip( unsigned longcelt );
```

## `IVoIPCallRecord`

Interface page ms911681; `Header:` row `Voipstore.idl`.

```c
/* CallType (ms911675) -- Windows CE .NET 4.2 and later. */
HRESULT put_CallType( VoIPCallType vctType);HRESULT get_CallType( VoIPCallType* pvctType);
/* Commit (ms911676) -- Windows CE .NET 4.2 and later. */
HRESULT Commit();
/* DeleteFromDB (ms911677) -- Windows CE .NET 4.2 and later. */
HRESULT DeleteFromDB();
/* Duration (ms911678) -- Windows CE .NET 4.2 and later. */
HRESULT get_Duration( SYSTEMTIME* ptime);
/* EndTime (ms911679) -- Windows CE .NET 4.2 and later. */
HRESULT put_EndTime( SYSTEMTIME time);HRESULT get_EndTime( SYSTEMTIME* ptime );
/* FriendlyName (ms911680) -- Windows CE .NET 4.2 and later. */
HRESULT put_FriendlyName( BSTR bstrFriendlyName );HRESULT get_FriendlyName( BSTR* pbstrFriendlyName );
/* StartTime (ms911682) -- Windows CE .NET 4.2 and later. */
HRESULT put_StartTime( SYSTEMTIME time);HRESULT get_StartTime( SYSTEMTIME* ptime);
/* URI (ms911683) -- Windows CE .NET 4.2 and later. */
HRESULT put_URI( BSTR bstrURI );HRESULT get_URI( BSTR* pbstrURI );
/* VoIPName (ms911684) -- Windows CE .NET 4.2 and later. */
HHRESULT put_VoIPName( BSTR bstrVoIPName);HRESULT get_VoIPName( BSTR* pbstrVoIPName);
```

## `IVoIPCallerInfoDB`

Interface page ms911650; `Header:` row `Voipstore.idl`.

```c
/* CreateRecord (ms911532) -- Windows CE .NET 4.2 and later. */
HRESULT CreateRecord( IVoIPCallerInfoRecord** ppiRecord);
/* Enumerator (ms911539) -- Windows CE .NET 4.2 and later. */
HRESULT get_Enumerator( IVoIPCallerInfoDBEnum**ppiEnum);
/* FindCallerInfoBySpeedDialEntry (ms931238) -- Windows CE .NET 4.2 and later. */
HRESULT FindCallerInfoBySpeedDialEntry( INTidxSpeedDial,IVoIPCallerInfoRecord** ppiRecord);
/* FindCallerInfoByURI (ms931345) -- Windows CE .NET 4.2 and later. */
HRESULT FindCallerInfoByURI( BSTRbstrURI,IVoIPCallerInfoRecord** ppiRecord);
/* FriendlyNameEnumerator (ms911634) -- Windows CE .NET 4.2 and later. */
HRESULT get_FriendlyNameEnumerator( IVoIPCallerInfoDBEnum** ppiEnum);
/* Init (ms911647) -- Windows CE .NET 4.2 and later. */
HRESULT Init( BSTRbstrURI);
/* SpeedDialEnumerator (ms911651) -- Windows CE .NET 4.2 and later. */
HRESULT get_SpeedDialEnumerator( IVoIPCallerInfoDBEnum** ppiEnum);
```

## `IVoIPCallerInfoDBEnum`

Interface page ms911546; `Header:` row `Voipstore.idl`.

```c
/* Next (ms911553) -- Windows CE .NET 4.2 and later. */
HRESULT Next( unsigned longcelt,IVoIPCallerInfoRecord** rgVoIPCallerInfoRecord,unsigned long* pceltFetched);
/* Reset (ms911567) -- Windows CE .NET 4.2 and later. */
HRESULT Reset();
/* Skip (ms931185) -- Windows CE .NET 4.2 and later. */
HRESULT Skip( unsigned longcelt);
```

## `IVoIPCallerInfoRecord`

Interface page ms911658; `Header:` row `Voipstore.idl`.

```c
/* Blocked (ms911652) -- Windows CE .NET 4.2 and later. */
HRESULT put_Blocked( VARIANT_BOOLfBlocked);HRESULT get_Blocked( VARIANT_BOOL* pfBlocked);
/* Commit (ms911654) -- Windows CE .NET 4.2 and later. */
HRESULT Commit();
/* DeleteFromDB (ms911655) -- Windows CE .NET 4.2 and later. */
HRESULT DeleteFromDB();
/* ForwardingURI (ms911656) -- Windows CE .NET 4.2 and later. */
HRESULT put_ForwardingURI( BSTRbstrForwardingURI);HRESULT get_ForwardingURI( BSTR* pbstrForwardingURI);
/* FriendlyName (ms911657) -- Windows CE .NET 4.2 and later. */
HRESULT put_FriendlyName( BSTRbstrFriendlyName );HRESULT get_FriendlyName( BSTR* pbstrFriendlyName);
/* RingTone (ms911659) -- Windows CE .NET 4.2 and later. */
HRESULT put_RingTone( BSTRbstrRingTonePath);HRESULT get_RingTone( BSTR* pbstrRingTonePath);
/* SpeedDialEntry (ms911660) -- Windows CE .NET 4.2 and later. */
HRESULT put_SpeedDialEntry( intidxSpeedDial);HRESULT get_SpeedDialEntry( int* pidxSpeedDial);
/* URI (ms911661) -- Windows CE .NET 4.2 and later. */
HRESULT put_URI( BSTRbstrURI);HRESULT get_URI( BSTR* pbstrURI);
/* VoIPName (ms911662) -- Windows CE .NET 4.2 and later. */
HRESULT put_VoIPName( BSTRbstrVoIPName);HRESULT get_VoIPName( BSTR* pbstrVoIPName);
```

## `IVoIPDirectoryClient`

Interface page ms911957; `Header:` row `Voipprov.idl`.

```c
/* RegistrationParameters (ms911968) -- Windows CE .NET 4.2. */
HRESULT put_RegistrationParameters( DirectoryClientRegParams* pdcrp);
/* SipPassword (ms911977) -- Windows CE .NET 4.2. */
HRESULT put_SipPassword( BSTR bstrSipPassword);
/* SipServerParameters (ms911983) -- Windows CE .NET 4.2. */
HRESULT get_SipServerParameters( BSTR* pbstrMyURI,BSTR*pbstrMyServer,BSTR*pbstrProfileString);
```

## `IVoIPMediaMgr`

Interface page ms912032; `Header:` row `Voipmediamanager.idl`.

```c
/* AnswerSession (ms911989) -- Windows CE .NET 4.2 and later. */
HRESULT AnswerSession( IRTCSession2* piSession);
/* ConferenceSessions (aa525641) -- Windows CE 5.0 and later. */
HRESULT ConferenceSessions( IRTCSession2* piSessionA, IRTCSession2* piSessionB);
/* CreatePCToPCSession (ms911998) -- Windows CE .NET 4.2 and later. */
HRESULT CreatePCToPCSession( IRTCClient2*piClient,IRTCProfile*piProfile,IRTCSession2** ppiSession);
/* EvaluateSessionDescription (ms912006) -- Windows CE .NET 4.2 and later. */
HRESULT EvaluateSessionDescription( BSTRbstrContentType,BSTRbstrSessionDescription,VARIANT_BOOL* pfApplicationSession);
/* HoldSession (ms912013) -- Windows CE .NET 4.2 and later. */
HRESULT HoldSession( IRTCSession2* piSession);
/* Initialize (ms912020) -- Windows CE .NET 4.2 and later. */
HRESULT Initialize();
/* InitializeRTCClient (ms912027) -- Windows CE .NET 4.2 and later. */
HRESULT InitializeRTCClient( IRTCClient2* piClient );
/* MicrophoneMute (ms912036) -- Windows CE .NET 4.2 and later. */
HRESULT put_MicrophoneMute( VARIANT_BOOL fMuted);HRESULT get_MicrophoneMute( VARIANT_BOOL* pfMuted);
/* MicrophoneVolume (ms912043) -- Windows CE .NET 4.2 and later. */
HRESULT put_MicrophoneVolume( float fpVolume);HRESULT get_MicrophoneVolume( float* pfpVolume);
/* OnReinviteEvent (ms912055) -- Windows CE .NET 4.2 and later. */
HRESULT OnReinviteEvent( IRTCReInviteEvent*piReinviteEvent);
/* OnSessionOperationCompleteEvent (aa525642) -- Windows CE 5.0 and later. */
HRESULT OnSessionOperationCompleteEvent( IRTCSessionOperationCompleteEvent* piEvent);
/* OnSessionStateChangeEvent (ms912064) -- Windows CE .NET 4.2 and later. */
HRESULT OnSessionStateChangeEvent( IRTCSessionStateChangeEvent*piSSCEvent);
/* PlayProgressTone (ms912071) -- Windows CE .NET 4.2 and later. */
HRESULT PlayProgressTone( VoIPProgressTone vpt);
/* PlaySound (ms912081) -- Windows CE .NET 4.2 and later. */
HRESULT PlaySound( BSTR bstrFilePath,INT_PTRhCallback);
/* SendDTMF (ms912089) -- Windows CE .NET 4.2 and later. */
HRESULT SendDTMF( RTC_DTMF dtmf);
/* SpeakerMute (ms912098) -- Windows CE .NET 4.2 and later. */
HRESULT put_SpeakerMute( VARIANT_BOOL fMuted);HRESULT get_SpeakerMute( VARIANT_BOOL* pfMuted);
/* SpeakerVolume (ms912109) -- Windows CE .NET 4.2 and later. */
HRESULT put_SpeakerVolume( float fpVolume);HRESULT get_SpeakerVolume( float* pfpVolume );
/* StopProgressTone (ms912118) -- Windows CE .NET 4.2 and later. */
HRESULT StopProgressTone();
/* StopSound (ms912124) -- Windows CE .NET 4.2 and later. */
HRESULT StopSound();
/* UnholdSession (ms912130) -- Windows CE .NET 4.2 and later. */
HRESULT UnholdSession( IRTCSession2* piSession);
/* Uninitialize (ms912137) -- Windows CE 5.0 and later. */
HRESULT Uninitialize();
```

