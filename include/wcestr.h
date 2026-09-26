/* Subset of the C run time that Windows CE exports from coredll.dll.
 * Original text.
 *
 * On Windows CE the C run time lives inside coredll, so these entry points are
 * ordinary DLL imports rather than static library calls. Each block is keyed off
 * the include guard of the matching standard header, so a program that pulls in
 * the real <string.h>, <wchar.h>, <stdlib.h> or <stdio.h> gets those
 * declarations instead and this file stays out of the way.
 *
 * Only entry points that the release in question exports publicly are listed.
 * Windows CE 6.0 marks the whole run time export set of coredll private, because
 * from that release on the run time is linked from corelibc rather than imported;
 * the declarations are therefore switched off for that target and come from the
 * run time headers instead.
 */
#ifndef AKARI_WCE_WCESTR_H
#define AKARI_WCE_WCESTR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "wcever.h"
#include "windef.h"

#if (_WIN32_WCE < 0x600)

#ifndef _INC_STRING
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *dst, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
char *strcat(char *dst, const char *src);
size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *s1, const char *s2);
char *strtok(char *s, const char *delim);
char *strpbrk(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
size_t strspn(const char *s, const char *accept);
char *_strdup(const char *s);
int _stricmp(const char *s1, const char *s2);
int _strnicmp(const char *s1, const char *s2, size_t n);
char *_strlwr(char *s);
char *_strupr(char *s);
char *_strrev(char *s);
char *_strnset(char *s, int c, size_t n);
char *_strset(char *s, int c);
void *_memccpy(void *dst, const void *src, int c, size_t n);
int _memicmp(const void *s1, const void *s2, size_t n);
#endif /* _INC_STRING */

#ifndef _INC_WCHAR
wchar_t *wcscpy(wchar_t *dst, const wchar_t *src);
wchar_t *wcsncpy(wchar_t *dst, const wchar_t *src, size_t n);
wchar_t *wcscat(wchar_t *dst, const wchar_t *src);
size_t wcslen(const wchar_t *s);
int wcscmp(const wchar_t *s1, const wchar_t *s2);
int wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n);
int _wcsicmp(const wchar_t *s1, const wchar_t *s2);
int _wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t n);
wchar_t *wcschr(const wchar_t *s, wchar_t c);
wchar_t *wcsrchr(const wchar_t *s, wchar_t c);
wchar_t *wcsstr(const wchar_t *s1, const wchar_t *s2);
wchar_t *_wcsupr(wchar_t *s);
wchar_t *_wcslwr(wchar_t *s);
wchar_t *_wcsdup(const wchar_t *s);
size_t wcscspn(const wchar_t *s, const wchar_t *reject);
size_t wcsspn(const wchar_t *s, const wchar_t *accept);
wchar_t *wcspbrk(const wchar_t *s, const wchar_t *accept);
wchar_t *wcstok(wchar_t *s, const wchar_t *delim);
wchar_t *wcsncat(wchar_t *dst, const wchar_t *src, size_t n);
wchar_t *_wcsdup(const wchar_t *s);
wchar_t *_wcsrev(wchar_t *s);
wchar_t *_wcsnset(wchar_t *s, wchar_t c, size_t n);
wchar_t *_wcsset(wchar_t *s, wchar_t c);
double wcstod(const wchar_t *s, wchar_t **endptr);
long wcstol(const wchar_t *s, wchar_t **endptr, int base);
unsigned long wcstoul(const wchar_t *s, wchar_t **endptr, int base);
wint_t towupper(wint_t c);
wint_t towlower(wint_t c);
int iswctype(wint_t c, int mask);
#endif /* _INC_WCHAR */

#ifndef _INC_STDLIB
void *malloc(size_t size);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
size_t _msize(void *ptr);
int atoi(const char *s);
long atol(const char *s);
double atof(const char *s);
long strtol(const char *s, char **endptr, int base);
unsigned long strtoul(const char *s, char **endptr, int base);
char *_itoa(int value, char *str, int radix);
char *_ltoa(long value, char *str, int radix);
char *_ultoa(unsigned long value, char *str, int radix);
wchar_t *_itow(int value, wchar_t *str, int radix);
wchar_t *_ltow(long value, wchar_t *str, int radix);
wchar_t *_ultow(unsigned long value, wchar_t *str, int radix);
long _wtol(const wchar_t *s);
long long _wtoll(const wchar_t *s);
long long _atoi64(const char *s);
double strtod(const char *s, char **endptr);
size_t mbstowcs(wchar_t *dst, const char *src, size_t n);
size_t wcstombs(char *dst, const wchar_t *src, size_t n);
void _swab(char *src, char *dst, size_t n);
int tolower(int c);
int toupper(int c);
int rand(void);
void srand(unsigned int seed);
typedef struct akari_DIV_T { int quot; int rem; } akari_div_t;
typedef struct akari_LDIV_T { long quot; long rem; } akari_ldiv_t;
akari_div_t div(int numer, int denom);
akari_ldiv_t ldiv(long numer, long denom);
int abs(int n);
long labs(long n);
void qsort(void *base, size_t num, size_t width,
    int (*compare)(const void *, const void *));
#endif /* _INC_STDLIB */

#ifndef _INC_STDIO
int _snprintf(char *buffer, size_t count, const char *format, ...);
int _vsnprintf(char *buffer, size_t count, const char *format, void *argptr);
int _snwprintf(wchar_t *buffer, size_t count, const wchar_t *format, ...);
int _vsnwprintf(wchar_t *buffer, size_t count, const wchar_t *format, void *argptr);
#endif /* _INC_STDIO */

#endif /* _WIN32_WCE < 0x600 */

#ifdef __cplusplus
}
#endif
#endif /* AKARI_WCE_WCESTR_H */
