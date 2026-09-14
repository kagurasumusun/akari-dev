# CE generation audit

Measured at M117 from `docs/generation-map.tsv` (5,541 attributed
declarations) against the `#if _WIN32_WCE` nesting actually present in
each header.  For every attributed name the audit computes the
*effective* minimum generation -- the strongest `_WIN32_WCE >= 0xNNNN`
condition enclosing its declaration -- and compares it with the
generation the official `OS Versions:` row states.

The comparison only means something against the lowest target this
tree builds, CE 4.2 (`0x0420`).  A name documented from CE 1.0 needs no
guard and is not a violation; an unguarded name documented from CE 5.0
is one, because a 4.2 build sees it.

## Direction 1: visible earlier than documented (unguarded)

**235** declarations are documented as arriving after CE 4.2
and carry no `_WIN32_WCE` condition at all, so a CE 4.2 build sees
them.  By header:

| header | names |
|---|---|
| `include/D3dmddk.h` | 46 |
| `include/Usp10.h` | 40 |
| `include/D3dm.h` | 37 |
| `include/Shobjidl.h` | 22 |
| `include/Windbase.h` | 20 |
| `include/oak/DwCeDump.h` | 16 |
| `include/Wingdi.h` | 14 |
| `include/Winbase.h` | 13 |
| `include/oak/Pkfuncs.h` | 7 |
| `include/oak/Sdcardddk.h` | 6 |
| `include/oak/Fsdmgr.h` | 3 |
| `include/Commctrl.h` | 2 |
| `include/Socksv2.h` | 2 |
| `include/oak/Ndis.h` | 2 |
| `include/oak/Sdmem.h` | 2 |
| `include/Cchannel.h` | 1 |
| `include/ErrorRep.h` | 1 |
| `include/oak/Ddhal.h` | 1 |

These are candidates, not yet defects: a whole-header component that
only ever existed from CE 5.0 (`D3dm.h` is the clearest) is arguably
guarded by not being included on a 4.2 build, and guarding a type whose
every consumer is already 5.0-only adds conditions without changing
what compiles.  Each needs the same treatment M111 gave the units it
did guard: wrap the unit, then prove the 0x420/0x500/0x600 passes still
compile.  The per-name list is below.

## Direction 2: visible later than documented (over-guarded)

Seven declarations were guarded `>= 0x0500` although their pages say
CE .NET 4.0 or 4.2 -- i.e. hidden from a CE 4.2 build that the
documentation says should have them.  Each was relaxed and the 0x420
pass re-run:

| header | names | page says | outcome |
|---|---|---|---|
| `Shlobj.h` | `SHGetDesktopFolder` | CE .NET 4.2 and later | **guard removed** -- 0x420 compiles |
| `pm.h` | `RegisterPowerRelationship` | CE .NET 4.0 and later | **guard removed** -- 0x420 compiles |
| `CEDDK.h` | `TransBusAddrToVirtual`, `TransBusAddrToStatic` | CE .NET 4.0 and later | guard **kept**: `PPVOID` is unknown at 0x420 |
| `Cred.h` | `CredRead`, `CredUpdate`, `CredWrite` | CE .NET 4.0 and later | guard **kept**: `PCRED`/`PPCRED` are unknown at 0x420 |

The two removals are the fix.  The other five are not generation
claims at all but **dependency holds** of the kind
`docs/generation-held.tsv` records: the API is documented from 4.0, and
it stays behind a 5.0 condition only because a type in its prototype
does not exist on this tree's 4.2 pass.  Both cases were added to that
file with the reason spelled out, and the in-header comment now says
the same, so the guard is not mistaken for a generation claim again.

Attempting the removal is what established this: relaxing all seven
failed the 0x420 compile with `unknown type name 'PPVOID'` and then
`unknown type name 'PPCRED'`, which is how the five were told apart
from the two.

## Per-name list for direction 1

`header:line name (documented minimum, page)`

```
include/Cchannel.h:250  tagCHANNEL_ENTRY_POINTS_EX  doc>=0x0500  (aa513861)
include/Commctrl.h:1137  tagLVBKIMAGE  doc>=0x0500  (aa453422)
include/Commctrl.h:1230  tagNMLVGETINFOTIP  doc>=0x0500  (ms931639)
include/D3dm.h:44  D3DMVALUE  doc>=0x0500  (ms907756)
include/D3dm.h:47  D3DMCOLOR  doc>=0x0500  (ms939142)
include/D3dm.h:574  _D3DMMATRIX  doc>=0x0500  (ms907720)
include/D3dm.h:596  _FACD3DM  doc>=0x0500  (ms932027)
include/D3dm.h:597  MAKE_D3DMHRESULT  doc>=0x0500  (ms932027)
include/D3dm.h:598  D3DMERR_ALREADYLOCKED  doc>=0x0500  (ms932027)
include/D3dm.h:599  D3DMERR_CONFLICTINGRENDERSTATE  doc>=0x0500  (ms932027)
include/D3dm.h:600  D3DMERR_CONFLICTINGTEXTUREFILTER  doc>=0x0500  (ms932027)
include/D3dm.h:601  D3DMERR_CONFLICTINGTEXTUREPALETTE  doc>=0x0500  (ms932027)
include/D3dm.h:602  D3DMERR_DEVICELOST  doc>=0x0500  (ms932027)
include/D3dm.h:603  D3DMERR_DEVICENOTRESET  doc>=0x0500  (ms932027)
include/D3dm.h:604  D3DMERR_DRIVERINTERNALERROR  doc>=0x0500  (ms932027)
include/D3dm.h:605  D3DMERR_DRIVERINVALIDCALL  doc>=0x0500  (ms932027)
include/D3dm.h:606  D3DMERR_DRIVERUNSUPPORTED  doc>=0x0500  (ms932027)
include/D3dm.h:607  D3DMERR_INVALIDCALL  doc>=0x0500  (ms932027)
include/D3dm.h:608  D3DMERR_INVALIDDEVICE  doc>=0x0500  (ms932027)
include/D3dm.h:609  D3DMERR_MEMORYPOOLEMPTY  doc>=0x0500  (ms932027)
include/D3dm.h:610  D3DMERR_MOREDATA  doc>=0x0500  (ms932027)
include/D3dm.h:611  D3DMERR_NOTAVAILABLE  doc>=0x0500  (ms932027)
include/D3dm.h:612  D3DMERR_NOTFOUND  doc>=0x0500  (ms932027)
include/D3dm.h:613  D3DMERR_TOOMANYOPERATIONS  doc>=0x0500  (ms932027)
include/D3dm.h:614  D3DMERR_UNSUPPORTEDALPHAARG  doc>=0x0500  (ms932027)
include/D3dm.h:615  D3DMERR_UNSUPPORTEDALPHAOPERATION  doc>=0x0500  (ms932027)
include/D3dm.h:616  D3DMERR_UNSUPPORTEDCOLORARG  doc>=0x0500  (ms932027)
include/D3dm.h:617  D3DMERR_UNSUPPORTEDCOLOROPERATION  doc>=0x0500  (ms932027)
include/D3dm.h:618  D3DMERR_UNSUPPORTEDFACTORVALUE  doc>=0x0500  (ms932027)
include/D3dm.h:619  D3DMERR_UNSUPPORTEDTEXTUREFILTER  doc>=0x0500  (ms932027)
include/D3dm.h:620  D3DMERR_WRONGTEXTUREFORMAT  doc>=0x0500  (ms932027)
include/D3dm.h:628  IDirect3DMobile  doc>=0x0500  (ms929153)
include/D3dm.h:629  IDirect3DMobileDevice  doc>=0x0500  (ms929153)
include/D3dm.h:630  IDirect3DMobileResource  doc>=0x0500  (ms929153)
include/D3dm.h:631  IDirect3DMobileBaseTexture  doc>=0x0500  (ms929153)
include/D3dm.h:632  IDirect3DMobileSurface  doc>=0x0500  (ms929153)
include/D3dm.h:633  IDirect3DMobileTexture  doc>=0x0500  (ms929153)
include/D3dm.h:634  IDirect3DMobileVertexBuffer  doc>=0x0500  (ms929153)
include/D3dm.h:635  IDirect3DMobileIndexBuffer  doc>=0x0500  (ms929153)
include/D3dm.h:636  IDirect3DMobileSwapChain  doc>=0x0500  (ms929153)
include/D3dmddk.h:30  _D3DM_CLEAR  doc>=0x0500  (aa447711)
include/D3dmddk.h:39  _D3DM_COLORFILL  doc>=0x0500  (aa447712)
include/D3dmddk.h:45  _D3DM_COMMAND  doc>=0x0500  (aa447713)
include/D3dmddk.h:51  _D3DM_COPYRECT  doc>=0x0500  (aa447714)
include/D3dmddk.h:58  _D3DM_CREATECONTEXT_DATA  doc>=0x0500  (aa447715)
include/D3dmddk.h:63  _D3DM_CREATELIGHT  doc>=0x0500  (aa447717)
include/D3dmddk.h:67  _D3DM_CREATEPALETTE  doc>=0x0500  (aa447718)
include/D3dmddk.h:71  _D3DM_DESTROYCONTEXT_DATA  doc>=0x0500  (aa447721)
include/D3dmddk.h:76  _D3DM_DESTROYSURFACE_DATA  doc>=0x0500  (aa447723)
include/D3dmddk.h:81  _D3DM_DRAWINDEXEDPRIMITIVE  doc>=0x0500  (aa447726)
include/D3dmddk.h:90  _D3DM_DRAWPRIMITIVE  doc>=0x0500  (aa447727)
include/D3dmddk.h:96  _D3DM_DRAWPRIMITIVE_DATA  doc>=0x0500  (aa447728)
include/D3dmddk.h:104  _D3DM_GETINFO_DATA  doc>=0x0500  (ms896732)
include/D3dmddk.h:112  _D3DM_INDEXBUFFER  doc>=0x0500  (ms896734)
include/D3dmddk.h:117  _D3DM_LOCKSURFACE_DATA  doc>=0x0500  (ms896737)
include/D3dmddk.h:125  _D3DM_MATERIAL  doc>=0x0500  (ms896739)
include/D3dmddk.h:130  _D3DM_OPERATION  doc>=0x0500  (ms896740)
include/D3dmddk.h:155  _D3DM_PRESENT  doc>=0x0500  (ms896741)
include/D3dmddk.h:163  _D3DM_PROCESSVERTICES  doc>=0x0500  (ms896742)
include/D3dmddk.h:171  _D3DM_RENDERSTATE  doc>=0x0500  (ms896743)
include/D3dmddk.h:176  _D3DM_RENDERTARGET  doc>=0x0500  (ms896744)
include/D3dmddk.h:181  _D3DM_SETLIGHT_DATATYPE  doc>=0x0500  (ms896749)
include/D3dmddk.h:188  _D3DM_SETLIGHT_WITHDATA  doc>=0x0500  (ms896750)
include/D3dmddk.h:195  _D3DM_SETPALETTE_DATATYPE  doc>=0x0500  (ms896752)
include/D3dmddk.h:200  _D3DM_SETPALETTE_WITHENTRIES  doc>=0x0500  (ms896753)
include/D3dmddk.h:206  _D3DM_STRETCHRECT  doc>=0x0500  (ms896754)
include/D3dmddk.h:214  _D3DM_TEXTURESTAGESTATE  doc>=0x0500  (ms896755)
include/D3dmddk.h:220  _D3DM_TRANSFORM  doc>=0x0500  (ms896756)
include/D3dmddk.h:226  _D3DM_UNLOCKSURFACE_DATA  doc>=0x0500  (ms896757)
include/D3dmddk.h:231  _D3DM_VALIDATEDEVICE_DATA  doc>=0x0500  (ms896759)
include/D3dmddk.h:237  _D3DM_VERTEXBUFFER  doc>=0x0500  (ms896761)
include/D3dmddk.h:243  _D3DM_VIEWPORT  doc>=0x0500  (ms896762)
include/D3dmddk.h:247  _D3DMTEXTURE_DESC  doc>=0x0500  (aa447707)
include/D3dmddk.h:342  D3DM_CREATESURFACE_DATA  doc>=0x0500  (aa447695)
include/D3dmddk.h:343  D3DM_GETADAPTERINFO_DATA  doc>=0x0500  (aa447695)
include/D3dmddk.h:344  D3DM_INITIALIZE_DATA  doc>=0x0500  (aa447695)
include/D3dmddk.h:345  D3DM_RESOURCEMANAGER_DATA  doc>=0x0500  (aa447695)
include/D3dmddk.h:346  D3DMADAPTER_IDENTIFIER  doc>=0x0500  (aa447695)
include/D3dmddk.h:347  D3DMDEVICEFORMAT  doc>=0x0500  (aa447695)
include/D3dmddk.h:351  _D3DM_RESOURCEMANAGER_ACTION  doc>=0x0500  (ms896745)
include/D3dmddk.h:342  _D3DM_CREATESURFACE_DATA  doc>=0x0500  (aa447719)
include/D3dmddk.h:343  _D3DM_GETADAPTERINFO_DATA  doc>=0x0500  (ms896729)
include/D3dmddk.h:344  _D3DM_INITIALIZE_DATA  doc>=0x0500  (ms896735)
include/D3dmddk.h:345  _D3DM_RESOURCEMANAGER_DATA  doc>=0x0500  (ms896746)
include/D3dmddk.h:346  _D3DMADAPTER_IDENTIFIER  doc>=0x0500  (ms939133)
include/D3dmddk.h:347  _D3DMDEVICEFORMAT  doc>=0x0500  (aa447699)
include/ErrorRep.h:33  EFaultRepRetVal  doc>=0x0500  (ms886799)
include/Shobjidl.h:119  SVSI_DESELECT  doc>=0x0500  (ms909891)
include/Shobjidl.h:120  SVSI_SELECT  doc>=0x0500  (ms909891)
include/Shobjidl.h:121  SVSI_EDIT  doc>=0x0500  (ms909891)
include/Shobjidl.h:122  SVSI_DESELECTOTHERS  doc>=0x0500  (ms909891)
include/Shobjidl.h:123  SVSI_ENSUREVISIBLE  doc>=0x0500  (ms909891)
include/Shobjidl.h:124  SVSI_FOCUSED  doc>=0x0500  (ms909891)
include/Shobjidl.h:125  SVSI_TRANSLATEPT  doc>=0x0500  (ms909891)
include/Shobjidl.h:126  SVSI_SELECTIONMARK  doc>=0x0500  (ms909891)
include/Shobjidl.h:127  SVSI_POSITIONITEM  doc>=0x0500  (ms909891)
include/Shobjidl.h:128  SVSI_CHECK  doc>=0x0500  (ms909891)
include/Shobjidl.h:133  SVGIO_BACKGROUND  doc>=0x0500  (ms909887)
include/Shobjidl.h:134  SVGIO_SELECTION  doc>=0x0500  (ms909887)
include/Shobjidl.h:135  SVGIO_ALLVIEW  doc>=0x0500  (ms909887)
include/Shobjidl.h:136  SVGIO_CHECKED  doc>=0x0500  (ms909887)
include/Shobjidl.h:137  SVGIO_TYPE_MASK  doc>=0x0500  (ms909887)
include/Shobjidl.h:138  SVGIO_FLAG_VIEWORDER  doc>=0x0500  (ms909887)
include/Shobjidl.h:151  IDropTarget  doc>=0x0500  (ms909893)
include/Shobjidl.h:152  IPersistFolder  doc>=0x0500  (ms909893)
include/Shobjidl.h:153  IShellFolder  doc>=0x0500  (ms909893)
include/Shobjidl.h:154  IShellView  doc>=0x0500  (ms909893)
include/Shobjidl.h:155  ITaskbarList  doc>=0x0500  (ms909893)
include/Shobjidl.h:156  ITaskbarList2  doc>=0x0500  (ms909893)
include/Socksv2.h:53  SS_POWER_ENTRY  doc>=0x0500  (ms921890)
include/Socksv2.h:54  SS_SOCKETSTATE  doc>=0x0500  (ms921944)
include/Usp10.h:27  tagGOFFSET  doc>=0x0500  (ms905336)
include/Usp10.h:35  tag_SCRIPT_STATE  doc>=0x0500  (ms906273)
include/Usp10.h:50  tag_SCRIPT_ANALYSIS  doc>=0x0500  (ms906264)
include/Usp10.h:62  tag_SCRIPT_CONTROL  doc>=0x0500  (ms906266)
include/Usp10.h:76  tag_SCRIPT_DIGITSUBSTITUTE  doc>=0x0500  (ms906267)
include/Usp10.h:84  tag_SCRIPT_FONTPROPERTIES  doc>=0x0500  (ms906268)
include/Usp10.h:94  tag_SCRIPT_ITEM  doc>=0x0500  (ms906269)
include/Usp10.h:101  tag_SCRIPT_JUSTIFY  doc>=0x0500  (ms906270)
include/Usp10.h:121  tag_SCRIPT_LOGATTR  doc>=0x0500  (ms906271)
include/Usp10.h:131  tag_SCRIPT_PROPERTIES  doc>=0x0500  (ms906272)
include/Usp10.h:150  SCRIPT_CACHE  doc>=0x0500  (ms906265)
include/Usp10.h:154  SCRIPT_STRING_ANALYSIS  doc>=0x0500  (ms906274)
include/Usp10.h:157  tag_SCRIPT_TABDEF  doc>=0x0500  (ms906275)
include/Usp10.h:165  tag_SCRIPT_VISATTR  doc>=0x0500  (ms906276)
include/Usp10.h:176  ScriptApplyDigitSubstitution  doc>=0x0500  (ms906233)
include/Usp10.h:180  ScriptApplyLogicalWidth  doc>=0x0500  (ms906234)
include/Usp10.h:184  ScriptBreak  doc>=0x0500  (ms906235)
include/Usp10.h:188  ScriptCPtoX  doc>=0x0500  (ms906237)
include/Usp10.h:192  ScriptCacheGetHeight  doc>=0x0500  (ms906236)
include/Usp10.h:196  ScriptFreeCache  doc>=0x0500  (ms906238)
include/Usp10.h:200  ScriptGetCMap  doc>=0x0500  (ms906239)
include/Usp10.h:204  ScriptGetFontProperties  doc>=0x0500  (ms906240)
include/Usp10.h:208  ScriptGetGlyphABCWidth  doc>=0x0500  (ms906241)
include/Usp10.h:212  ScriptGetLogicalWidths  doc>=0x0500  (ms906242)
include/Usp10.h:216  ScriptGetProperties  doc>=0x0500  (ms906243)
include/Usp10.h:220  ScriptIsComplex  doc>=0x0500  (ms906244)
include/Usp10.h:224  ScriptItemize  doc>=0x0500  (ms906245)
include/Usp10.h:228  ScriptJustify  doc>=0x0500  (ms906246)
include/Usp10.h:232  ScriptLayout  doc>=0x0500  (ms906247)
include/Usp10.h:236  ScriptPlace  doc>=0x0500  (ms906248)
include/Usp10.h:240  ScriptRecordDigitSubstitution  doc>=0x0500  (ms906249)
include/Usp10.h:244  ScriptShape  doc>=0x0500  (ms906250)
include/Usp10.h:248  ScriptStringAnalyse  doc>=0x0500  (ms906251)
include/Usp10.h:252  ScriptStringCPtoX  doc>=0x0500  (ms906252)
include/Usp10.h:256  ScriptStringFree  doc>=0x0500  (ms906253)
include/Usp10.h:260  ScriptStringGetLogicalWidths  doc>=0x0500  (ms906254)
include/Usp10.h:264  ScriptStringGetOrder  doc>=0x0500  (ms906255)
include/Usp10.h:268  ScriptStringOut  doc>=0x0500  (ms906256)
include/Usp10.h:272  ScriptStringValidate  doc>=0x0500  (ms906257)
include/Usp10.h:276  ScriptStringXtoCP  doc>=0x0500  (ms906258)
include/Winbase.h:711  COPY_FILE_FAIL_IF_EXISTS  doc>=0x0500  (aa517311)
include/Winbase.h:712  COPY_FILE_RESTARTABLE  doc>=0x0500  (aa517311)
include/Winbase.h:713  COPY_FILE_ALLOW_DECRYPTED_DESTINATION  doc>=0x0500  (aa517311)
include/Winbase.h:724  CopyFileExW  doc>=0x0500  (aa517311)
include/Winbase.h:1110  HeapCompact  doc>=0x0500  (ms885655)
include/Winbase.h:1465  GetDllVersion  doc>=0x0500  (ms885617)
include/Winbase.h:1694  LOCKFILE_FAIL_IMMEDIATELY  doc>=0x0500  (ms891385)
include/Winbase.h:1695  LOCKFILE_EXCLUSIVE_LOCK  doc>=0x0500  (ms891385)
include/Winbase.h:1701  LockFileEx  doc>=0x0500  (ms891385)
include/Winbase.h:1709  UnlockFileEx  doc>=0x0500  (ms892364)
include/Winbase.h:1768  CeGetCanonicalPathNameW  doc>=0x0500  (aa517144)
include/Winbase.h:2599  _DevmgrDeviceInformation_tag  doc>=0x0500  (ms899309)
include/Winbase.h:1591  enum  doc>=0x0500  (ms898292)
include/Windbase.h:643  CEDBISOLATIONLEVEL  doc>=0x0500  (aa516980)
include/Windbase.h:647  CEPROPSPEC  doc>=0x0500  (aa517225)
include/Windbase.h:677  CEVOLUMEOPTIONS  doc>=0x0500  (aa516924)
include/Windbase.h:682  CeAddDatabaseProps  doc>=0x0500  (aa516979)
include/Windbase.h:687  CeBeginTransaction  doc>=0x0500  (aa516980)
include/Windbase.h:697  CeCreateDatabaseWithProps  doc>=0x0500  (aa516989)
include/Windbase.h:702  CeCreateSession  doc>=0x0500  (aa516990)
include/Windbase.h:711  CeEndTransaction  doc>=0x0500  (aa517002)
include/Windbase.h:731  CeGetDatabaseProps  doc>=0x0500  (aa517146)
include/Windbase.h:736  CeGetDatabaseSession  doc>=0x0500  (aa517147)
include/Windbase.h:744  CeMountDBVolEx  doc>=0x0500  (aa517182)
include/Windbase.h:752  CeOpenDatabaseInSession  doc>=0x0500  (aa517220)
include/Windbase.h:758  CeOpenStream  doc>=0x0500  (aa517223)
include/Windbase.h:768  CeRemoveDatabaseProps  doc>=0x0500  (aa517242)
include/Windbase.h:783  CeSetSessionOption  doc>=0x0500  (aa517268)
include/Windbase.h:787  CeStreamRead  doc>=0x0500  (aa517270)
include/Windbase.h:792  CeStreamSaveChanges  doc>=0x0500  (aa517272)
include/Windbase.h:795  CeStreamSeek  doc>=0x0500  (aa517274)
include/Windbase.h:800  CeStreamSetSize  doc>=0x0500  (aa517275)
include/Windbase.h:803  CeStreamWrite  doc>=0x0500  (aa517278)
include/Wingdi.h:198  _BLENDFUNCTION  doc>=0x0500  (aa452889)
include/Wingdi.h:316  tagPANOSE  doc>=0x0500  (ms934025)
include/Wingdi.h:358  _OUTLINETEXTMETRICW  doc>=0x0500  (ms934025)
include/Wingdi.h:401  AlphaBlend  doc>=0x0500  (aa452850)
include/Wingdi.h:441  GetLayout  doc>=0x0500  (aa453133)
include/Wingdi.h:468  GetStretchBltMode  doc>=0x0500  (aa453165)
include/Wingdi.h:498  SetStretchBltMode  doc>=0x0500  (aa453655)
include/Wingdi.h:510  GetViewportExtEx  doc>=0x0500  (aa453949)
include/Wingdi.h:512  GetViewportOrgEx  doc>=0x0500  (aa453950)
include/Wingdi.h:514  GetWindowExtEx  doc>=0x0500  (aa453951)
include/Wingdi.h:516  GetWindowOrgEx  doc>=0x0500  (aa453952)
include/Wingdi.h:518  OffsetViewportOrgEx  doc>=0x0500  (aa453953)
include/Wingdi.h:521  SetWindowOrgEx  doc>=0x0500  (aa453954)
include/Wingdi.h:620  GetOutlineTextMetricsW  doc>=0x0500  (ms933897)
include/oak/Ddhal.h:28  struct  doc>=0x0500  (aa448303)
include/oak/DwCeDump.h:40  PCEDUMP_BUCKET_PARAMETERS  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:41  PCEDUMP_ELEMENT_LIST  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:42  PCEDUMP_EXCEPTION  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:43  PCEDUMP_EXCEPTION_STREAM  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:44  PCEDUMP_FIELD_INFO  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:45  PCEDUMP_MEMORY_LIST  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:46  PCEDUMP_SYSTEM_INFO  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:47  PCEDUMP_THREAD_CALL_STACK  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:48  PCEDUMP_THREAD_CALL_STACK_FRAME  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:49  PCEDUMP_THREAD_CALL_STACK_LIST  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:50  PMINIDUMP_DIRECTORY  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:51  PMINIDUMP_HEADER  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:52  _MINIDUMP_LOCATION_DESCRIPTOR  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:54  PMINIDUMP_MEMORY_DESCRIPTOR  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:55  PMINIDUMP_STRING  doc>=0x0500  (ms939650)
include/oak/DwCeDump.h:65  _MINIDUMP_STREAM_TYPE  doc>=0x0500  (ms939649)
include/oak/Fsdmgr.h:39  _FILELOCKSTATE  doc>=0x0500  (aa517917)
include/oak/Fsdmgr.h:137  FSDMGR_EmptyLockContainer  doc>=0x0500  (aa517921)
include/oak/Fsdmgr.h:226  MyFSD_LockFileEx  doc>=0x0500  (aa517926)
include/oak/Ndis.h:1241  NdisReadPcmciaAttributeMemory  doc>=0x0500  (ms904123)
include/oak/Ndis.h:1417  NdisWritePcmciaAttributeMemory  doc>=0x0500  (ms905058)
include/oak/Pkfuncs.h:27  CaptureDumpFileOnDevice  doc>=0x0500  (ms939622)
include/oak/Pkfuncs.h:129  CeCloseCallerBuffer  doc>=0x0600  (ee488934)
include/oak/Pkfuncs.h:136  CeOpenCallerBuffer  doc>=0x0600  (ee488382)
include/oak/Pkfuncs.h:139  GetCallerVMProcessId  doc>=0x0600  (ee482772)
include/oak/Pkfuncs.h:142  GetDirectCallerProcessId  doc>=0x0600  (ee482980)
include/oak/Pkfuncs.h:145  SetEventData  doc>=0x0600  (ee482792)
include/oak/Pkfuncs.h:148  VirtualAllocCopyEx  doc>=0x0600  (ee488184)
include/oak/Sdcardddk.h:28  enum  doc>=0x0500  (ms920432)
include/oak/Sdcardddk.h:28  enum  doc>=0x0500  (ms920436)
include/oak/Sdcardddk.h:40  _SD_RESPONSE_TYPE  doc>=0x0500  (ms920454)
include/oak/Sdcardddk.h:28  enum  doc>=0x0500  (ms920459)
include/oak/Sdcardddk.h:64  _SDCARD_DEVICE_TYPE  doc>=0x0500  (ms920321)
include/oak/Sdcardddk.h:181  sd_io_transfer_type_tag  doc>=0x0500  (ms920440)
include/oak/Sdmem.h:28  SDDeinitializeCardLib  doc>=0x0500  (ms920339)
include/oak/Sdmem.h:31  SDInitializeCardLib  doc>=0x0500  (ms920376)
```
