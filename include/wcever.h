/* WinCE Development API Surface Kit - target selection.
 *
 * Original text. The declarations in this kit were written from interface
 * facts recorded by a survey of the public Windows CE headers: names,
 * parameter and return types, structure layouts, constants, calling
 * conventions and the mapping of names to modules. No upstream source text,
 * comment text or implementation detail is reproduced anywhere in this kit.
 */
#ifndef AKARI_WCE_WCEVER_H
#define AKARI_WCE_WCEVER_H

/* Target OS release. Define _WIN32_WCE before including anything to select a
 * different release; 0x600 is the default. */
#if !defined(_WIN32_WCE)
#define _WIN32_WCE 0x600
#endif

#if (_WIN32_WCE != 0x420) && (_WIN32_WCE != 0x500) && (_WIN32_WCE != 0x600)
#error "This kit covers Windows CE .NET 4.2, CE 5.0 and CE 6.0 (0x420/0x500/0x600)."
#endif

/* CPU selection. The macros follow the ones the CE toolchains predefine. */
#if defined(_M_IX86) || defined(_X86_) || (defined(__i386__) && !defined(__MINGW32__))
#define AKARI_CPU_X86 1
#elif defined(_M_ARM) || defined(_ARM_) || defined(__arm__)
#define AKARI_CPU_ARM 1
#elif defined(_M_SH) || defined(_SH4_) || defined(__SH4__)
#define AKARI_CPU_SH4 1
#elif defined(_M_MRX000) || defined(_MIPS_) || defined(__mips__)
#define AKARI_CPU_MIPS 1
#endif

/* Calling convention. Windows CE has one calling convention for the API: the
 * argument order of the C calling convention, on every CPU. Names are not
 * decorated in the export tables, and the x86 object files keep the ordinary
 * leading underscore that the import libraries resolve. */
#if !defined(WINAPI)
#if defined(_MSC_VER) && (defined(AKARI_CPU_X86) || defined(AKARI_CPU_ARM) || \
    defined(AKARI_CPU_SH4) || defined(AKARI_CPU_MIPS))
#define WINAPI __cdecl
#elif defined(__i386__) && !defined(__cdecl)
#define WINAPI
#else
#define WINAPI
#endif
#endif

#if !defined(WINAPIV)
#define WINAPIV
#endif

#if !defined(CALLBACK)
#define CALLBACK WINAPI
#endif

/* Imported objects. Everything in this kit comes from a DLL. */
#if !defined(WINBASEAPI)
#if defined(_MSC_VER) || defined(__declspec)
#define AKARI_DLLIMPORT __declspec(dllimport)
#else
#define AKARI_DLLIMPORT
#endif
#define WINBASEAPI AKARI_DLLIMPORT
#define WINUSERAPI AKARI_DLLIMPORT
#define COMMCTRLAPI AKARI_DLLIMPORT
#define COMMDLGAPI AKARI_DLLIMPORT
#define WINSOCKAPI AKARI_DLLIMPORT
#define WININETAPI AKARI_DLLIMPORT
#define SHELLAPI AKARI_DLLIMPORT
#define STOREAPI AKARI_DLLIMPORT
#define PMAPI AKARI_DLLIMPORT
#define NOTIFYAPI AKARI_DLLIMPORT
#define OLE32API AKARI_DLLIMPORT
#define OLEAUT32API AKARI_DLLIMPORT
#define CRYPT32API AKARI_DLLIMPORT
#define WS2API AKARI_DLLIMPORT
#endif

#if !defined(_WIN32)
#define _WIN32 1
#endif
#if !defined(WIN32)
#define WIN32 1
#endif
#if !defined(UNDER_CE)
#define UNDER_CE _WIN32_WCE
#endif

/* Feature switches used across the headers. */
#if (_WIN32_WCE >= 0x500)
#define AKARI_HAVE_FILE_MAPPING 1
#endif
#if (_WIN32_WCE >= 0x600)
#define AKARI_HAVE_STORE_MANAGER 1
#define AKARI_HAVE_CELL_SDK 1
#endif

#endif /* AKARI_WCE_WCEVER_H */
