/* GUID. Original text.
 *
 * Windows CE applications that use the registry, shell or COM APIs need the
 * 128-bit identifier type, so it is kept in its own small header rather than
 * buried in winnt.h.
 */
#ifndef AKARI_WCE_GUIDDEF_H
#define AKARI_WCE_GUIDDEF_H

#include "windef.h"

#ifndef _GUID_DEFINED
#define _GUID_DEFINED

typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

typedef GUID CLSID;
typedef CLSID *LPCLSID;
typedef const GUID *LPCGUID;
typedef GUID IID;
typedef IID *LPIID;
typedef GUID FMTID;
typedef GUID UUID;

/*
 * Compared field by field rather than with memcmp so that the test works even on
 * targets where the run time is linked separately from coredll.
 */
static __inline int IsEqualGUID(const GUID *a, const GUID *b)
{
    int i;

    if (a->Data1 != b->Data1 || a->Data2 != b->Data2 || a->Data3 != b->Data3)
        return 0;
    for (i = 0; i < 8; i++) {
        if (a->Data4[i] != b->Data4[i])
            return 0;
    }
    return 1;
}
#define IsEqualIID(a, b)   IsEqualGUID(&(a), &(b))
#define IsEqualCLSID(a, b) IsEqualGUID(&(a), &(b))

#endif /* _GUID_DEFINED */

#ifndef DEFINE_GUID
#ifdef INITGUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern const GUID name
#else
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern const GUID name
#endif
#endif

#endif /* AKARI_WCE_GUIDDEF_H */
