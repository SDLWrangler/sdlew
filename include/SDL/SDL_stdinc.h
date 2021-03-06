/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

/** @file SDL_stdinc.h
 *  This is a general header that includes C language support
 */

#ifndef _SDL_stdinc_h
#define _SDL_stdinc_h

#include "SDL_config.h"


#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif
#if defined(STDC_HEADERS)
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
#else
# if defined(HAVE_STDLIB_H)
#  include <stdlib.h>
# elif defined(HAVE_MALLOC_H)
#  include <malloc.h>
# endif
# if defined(HAVE_STDDEF_H)
#  include <stddef.h>
# endif
# if defined(HAVE_STDARG_H)
#  include <stdarg.h>
# endif
#endif
#ifdef HAVE_STRING_H
# if !defined(STDC_HEADERS) && defined(HAVE_MEMORY_H)
#  include <memory.h>
# endif
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#if defined(HAVE_INTTYPES_H)
# include <inttypes.h>
#elif defined(HAVE_STDINT_H)
# include <stdint.h>
#endif
#ifdef HAVE_CTYPE_H
# include <ctype.h>
#endif
#if defined(HAVE_ICONV) && defined(HAVE_ICONV_H)
# include <iconv.h>
#endif

/** The number of elements in an array */
#define SDL_arraysize(array)	(sizeof(array)/sizeof(array[0]))
#define SDL_TABLESIZE(table)	SDL_arraysize(table)

/* Use proper C++ casts when compiled as C++ to be compatible with the option
 -Wold-style-cast of GCC (and -Werror=old-style-cast in GCC 4.2 and above. */
#ifdef __cplusplus
#define SDL_reinterpret_cast(type, expression) reinterpret_cast<type>(expression)
#define SDL_static_cast(type, expression) static_cast<type>(expression)
#else
#define SDL_reinterpret_cast(type, expression) ((type)(expression))
#define SDL_static_cast(type, expression) ((type)(expression))
#endif

/** @name Basic data types */
/*@{*/
typedef enum {
	SDL_FALSE = 0,
	SDL_TRUE  = 1
} SDL_bool;

typedef int8_t		Sint8;
typedef uint8_t		Uint8;
typedef int16_t		Sint16;
typedef uint16_t	Uint16;
typedef int32_t		Sint32;
typedef uint32_t	Uint32;

#ifdef SDL_HAS_64BIT_TYPE
typedef int64_t		Sint64;
#ifndef SYMBIAN32_GCCE
typedef uint64_t	Uint64;
#endif
#else
/* This is really just a hack to prevent the compiler from complaining */
typedef struct {
	Uint32 hi;
	Uint32 lo;
} Uint64, Sint64;
#endif

/*@}*/

/** @name Make sure the types really have the right sizes */
/*@{*/
#define SDL_COMPILE_TIME_ASSERT(name, x)               \
       typedef int SDL_dummy_ ## name[(x) * 2 - 1]

SDL_COMPILE_TIME_ASSERT(uint8, sizeof(Uint8) == 1);
SDL_COMPILE_TIME_ASSERT(sint8, sizeof(Sint8) == 1);
SDL_COMPILE_TIME_ASSERT(uint16, sizeof(Uint16) == 2);
SDL_COMPILE_TIME_ASSERT(sint16, sizeof(Sint16) == 2);
SDL_COMPILE_TIME_ASSERT(uint32, sizeof(Uint32) == 4);
SDL_COMPILE_TIME_ASSERT(sint32, sizeof(Sint32) == 4);
SDL_COMPILE_TIME_ASSERT(uint64, sizeof(Uint64) == 8);
SDL_COMPILE_TIME_ASSERT(sint64, sizeof(Sint64) == 8);
/*@}*/

/** @name Enum Size Check
 *  Check to make sure enums are the size of ints, for structure packing.
 *  For both Watcom C/C++ and Borland C/C++ the compiler option that makes
 *  enums having the size of an int must be enabled.
 *  This is "-b" for Borland C/C++ and "-ei" for Watcom C/C++ (v11).
 */
/* Enable enums always int in CodeWarrior (for MPW use "-enum int") */
#ifdef __MWERKS__
#pragma enumsalwaysint on
#endif

typedef enum {
	DUMMY_ENUM_VALUE
} SDL_DUMMY_ENUM;

#ifndef __NDS__
SDL_COMPILE_TIME_ASSERT(enum, sizeof(SDL_DUMMY_ENUM) == sizeof(int));
#endif
/*@}*/

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_MALLOC
#define SDL_malloc	malloc
#else
typedef void * SDLCALL tSDL_malloc(size_t size);
#endif

#ifdef HAVE_CALLOC
#define SDL_calloc	calloc
#else
typedef void * SDLCALL tSDL_calloc(size_t nmemb, size_t size);
#endif

#ifdef HAVE_REALLOC
#define SDL_realloc	realloc
#else
typedef void * SDLCALL tSDL_realloc(void *mem, size_t size);
#endif

#ifdef HAVE_FREE
#define SDL_free	free
#else
typedef void SDLCALL tSDL_free(void *mem);
#endif

#if defined(HAVE_ALLOCA) && !defined(alloca)
# if defined(HAVE_ALLOCA_H)
#  include <alloca.h>
# elif defined(__GNUC__)
#  define alloca __builtin_alloca
# elif defined(_MSC_VER)
#  include <malloc.h>
#  define alloca _alloca
# elif defined(__WATCOMC__)
#  include <malloc.h>
# elif defined(__BORLANDC__)
#  include <malloc.h>
# elif defined(__DMC__)
#  include <stdlib.h>
# elif defined(__AIX__)
  #pragma alloca
# elif defined(__MRC__)
   void *alloca (unsigned);
# else
   char *alloca ();
# endif
#endif
#ifdef HAVE_ALLOCA
#define SDL_stack_alloc(type, count)    (type*)alloca(sizeof(type)*(count))
#define SDL_stack_free(data)
#else
#define SDL_stack_alloc(type, count)    (type*)SDL_malloc(sizeof(type)*(count))
#define SDL_stack_free(data)            SDL_free(data)
#endif

#ifdef HAVE_GETENV
#define SDL_getenv	getenv
#else
typedef char * SDLCALL tSDL_getenv(const char *name);
#endif

#ifdef HAVE_PUTENV
#define SDL_putenv	putenv
#else
typedef int SDLCALL tSDL_putenv(const char *variable);
#endif

#ifdef HAVE_QSORT
#define SDL_qsort	qsort
#else
typedef void SDLCALL tSDL_qsort(void *base, size_t nmemb, size_t size,
           int (*compare)(const void *, const void *));
#endif

#ifdef HAVE_ABS
#define SDL_abs		abs
#else
#define SDL_abs(X)	((X) < 0 ? -(X) : (X))
#endif

#define SDL_min(x, y)	(((x) < (y)) ? (x) : (y))
#define SDL_max(x, y)	(((x) > (y)) ? (x) : (y))

#ifdef HAVE_CTYPE_H
#define SDL_isdigit(X)  isdigit(X)
#define SDL_isspace(X)  isspace(X)
#define SDL_toupper(X)  toupper(X)
#define SDL_tolower(X)  tolower(X)
#else
#define SDL_isdigit(X)  (((X) >= '0') && ((X) <= '9'))
#define SDL_isspace(X)  (((X) == ' ') || ((X) == '\t') || ((X) == '\r') || ((X) == '\n'))
#define SDL_toupper(X)  (((X) >= 'a') && ((X) <= 'z') ? ('A'+((X)-'a')) : (X))
#define SDL_tolower(X)  (((X) >= 'A') && ((X) <= 'Z') ? ('a'+((X)-'A')) : (X))
#endif

#ifdef HAVE_MEMSET
#define SDL_memset      memset
#else
typedef void * SDLCALL tSDL_memset(void *dst, int c, size_t len);
#endif

#if defined(__GNUC__) && defined(i386)
#define SDL_memset4(dst, val, len)				\
do {								\
	int u0, u1, u2;						\
	__asm__ __volatile__ (					\
		"cld\n\t"					\
		"rep ; stosl\n\t"				\
		: "=&D" (u0), "=&a" (u1), "=&c" (u2)		\
		: "0" (dst), "1" (val), "2" (SDL_static_cast(Uint32, len))	\
		: "memory" );					\
} while(0)
#endif
#ifndef SDL_memset4
#define SDL_memset4(dst, val, len)		\
do {						\
	unsigned _count = (len);		\
	unsigned _n = (_count + 3) / 4;		\
	Uint32 *_p = SDL_static_cast(Uint32 *, dst);	\
	Uint32 _val = (val);			\
	if (len == 0) break;			\
        switch (_count % 4) {			\
        case 0: do {    *_p++ = _val;		\
        case 3:         *_p++ = _val;		\
        case 2:         *_p++ = _val;		\
        case 1:         *_p++ = _val;		\
		} while ( --_n );		\
	}					\
} while(0)
#endif

/* We can count on memcpy existing on Mac OS X and being well-tuned. */
#if defined(__MACH__) && defined(__APPLE__)
#define SDL_memcpy(dst, src, len) memcpy(dst, src, len)
#elif defined(__GNUC__) && defined(i386)
#define SDL_memcpy(dst, src, len)					  \
do {									  \
	int u0, u1, u2;						  	  \
	__asm__ __volatile__ (						  \
		"cld\n\t"						  \
		"rep ; movsl\n\t"					  \
		"testb $2,%b4\n\t"					  \
		"je 1f\n\t"						  \
		"movsw\n"						  \
		"1:\ttestb $1,%b4\n\t"					  \
		"je 2f\n\t"						  \
		"movsb\n"						  \
		"2:"							  \
		: "=&c" (u0), "=&D" (u1), "=&S" (u2)			  \
		: "0" (SDL_static_cast(unsigned, len)/4), "q" (len), "1" (dst),"2" (src) \
		: "memory" );						  \
} while(0)
#endif
#ifndef SDL_memcpy
#ifdef HAVE_MEMCPY
#define SDL_memcpy      memcpy
#elif defined(HAVE_BCOPY)
#define SDL_memcpy(d, s, n)	bcopy((s), (d), (n))
#else
typedef void * SDLCALL tSDL_memcpy(void *dst, const void *src, size_t len);
#endif
#endif

/* We can count on memcpy existing on Mac OS X and being well-tuned. */
#if defined(__MACH__) && defined(__APPLE__)
#define SDL_memcpy4(dst, src, len) memcpy(dst, src, (len)*4)
#elif defined(__GNUC__) && defined(i386)
#define SDL_memcpy4(dst, src, len)				\
do {								\
	int ecx, edi, esi;					\
	__asm__ __volatile__ (					\
		"cld\n\t"					\
		"rep ; movsl"					\
		: "=&c" (ecx), "=&D" (edi), "=&S" (esi)		\
		: "0" (SDL_static_cast(unsigned, len)), "1" (dst), "2" (src)	\
		: "memory" );					\
} while(0)
#endif
#ifndef SDL_memcpy4
#define SDL_memcpy4(dst, src, len)	SDL_memcpy(dst, src, (len) << 2)
#endif

#if defined(__GNUC__) && defined(i386)
#define SDL_revcpy(dst, src, len)			\
do {							\
	int u0, u1, u2;					\
	char *dstp = SDL_static_cast(char *, dst);	\
	char *srcp = SDL_static_cast(char *, src);	\
	int n = (len);					\
	if ( n >= 4 ) {					\
	__asm__ __volatile__ (				\
		"std\n\t"				\
		"rep ; movsl\n\t"			\
		"cld\n\t"				\
		: "=&c" (u0), "=&D" (u1), "=&S" (u2)	\
		: "0" (n >> 2),				\
		  "1" (dstp+(n-4)), "2" (srcp+(n-4))	\
		: "memory" );				\
	}						\
	switch (n & 3) {				\
		case 3: dstp[2] = srcp[2];		\
		case 2: dstp[1] = srcp[1];		\
		case 1: dstp[0] = srcp[0];		\
			break;				\
		default:				\
			break;				\
	}						\
} while(0)
#endif
#ifndef SDL_revcpy
typedef void * SDLCALL tSDL_revcpy(void *dst, const void *src, size_t len);
#endif

#ifdef HAVE_MEMMOVE
#define SDL_memmove     memmove
#elif defined(HAVE_BCOPY)
#define SDL_memmove(d, s, n)	bcopy((s), (d), (n))
#else
#define SDL_memmove(dst, src, len)			\
do {							\
	if ( dst < src ) {				\
		SDL_memcpy(dst, src, len);		\
	} else {					\
		SDL_revcpy(dst, src, len);		\
	}						\
} while(0)
#endif

#ifdef HAVE_MEMCMP
#define SDL_memcmp      memcmp
#else
typedef int SDLCALL tSDL_memcmp(const void *s1, const void *s2, size_t len);
#endif

#ifdef HAVE_STRLEN
#define SDL_strlen      strlen
#else
typedef size_t SDLCALL tSDL_strlen(const char *string);
#endif

#ifdef HAVE_STRLCPY
#define SDL_strlcpy     strlcpy
#else
typedef size_t SDLCALL tSDL_strlcpy(char *dst, const char *src, size_t maxlen);
#endif

#ifdef HAVE_STRLCAT
#define SDL_strlcat    strlcat
#else
typedef size_t SDLCALL tSDL_strlcat(char *dst, const char *src, size_t maxlen);
#endif

#ifdef HAVE_STRDUP
#define SDL_strdup     strdup
#else
typedef char * SDLCALL tSDL_strdup(const char *string);
#endif

#ifdef HAVE__STRREV
#define SDL_strrev      _strrev
#else
typedef char * SDLCALL tSDL_strrev(char *string);
#endif

#ifdef HAVE__STRUPR
#define SDL_strupr      _strupr
#else
typedef char * SDLCALL tSDL_strupr(char *string);
#endif

#ifdef HAVE__STRLWR
#define SDL_strlwr      _strlwr
#else
typedef char * SDLCALL tSDL_strlwr(char *string);
#endif

#ifdef HAVE_STRCHR
#define SDL_strchr      strchr
#elif defined(HAVE_INDEX)
#define SDL_strchr      index
#else
typedef char * SDLCALL tSDL_strchr(const char *string, int c);
#endif

#ifdef HAVE_STRRCHR
#define SDL_strrchr     strrchr
#elif defined(HAVE_RINDEX)
#define SDL_strrchr     rindex
#else
typedef char * SDLCALL tSDL_strrchr(const char *string, int c);
#endif

#ifdef HAVE_STRSTR
#define SDL_strstr      strstr
#else
typedef char * SDLCALL tSDL_strstr(const char *haystack, const char *needle);
#endif

#ifdef HAVE_ITOA
#define SDL_itoa        itoa
#else
#define SDL_itoa(value, string, radix)	SDL_ltoa((long)value, string, radix)
#endif

#ifdef HAVE__LTOA
#define SDL_ltoa        _ltoa
#else
typedef char * SDLCALL tSDL_ltoa(long value, char *string, int radix);
#endif

#ifdef HAVE__UITOA
#define SDL_uitoa       _uitoa
#else
#define SDL_uitoa(value, string, radix)	SDL_ultoa((long)value, string, radix)
#endif

#ifdef HAVE__ULTOA
#define SDL_ultoa       _ultoa
#else
typedef char * SDLCALL tSDL_ultoa(unsigned long value, char *string, int radix);
#endif

#ifdef HAVE_STRTOL
#define SDL_strtol      strtol
#else
typedef long SDLCALL tSDL_strtol(const char *string, char **endp, int base);
#endif

#ifdef HAVE_STRTOUL
#define SDL_strtoul      strtoul
#else
extern DECLSPEC unsigned long SDLCALL SDL_strtoul(const char *string, char **endp, int base);
#endif

#ifdef SDL_HAS_64BIT_TYPE

#ifdef HAVE__I64TOA
#define SDL_lltoa       _i64toa
#else
extern DECLSPEC char* SDLCALL SDL_lltoa(Sint64 value, char *string, int radix);
#endif

#ifdef HAVE__UI64TOA
#define SDL_ulltoa      _ui64toa
#else
extern DECLSPEC char* SDLCALL SDL_ulltoa(Uint64 value, char *string, int radix);
#endif

#ifdef HAVE_STRTOLL
#define SDL_strtoll     strtoll
#else
typedef Sint64 SDLCALL tSDL_strtoll(const char *string, char **endp, int base);
#endif

#ifdef HAVE_STRTOULL
#define SDL_strtoull     strtoull
#else
typedef Uint64 SDLCALL tSDL_strtoull(const char *string, char **endp, int base);
#endif

#endif /* SDL_HAS_64BIT_TYPE */

#ifdef HAVE_STRTOD
#define SDL_strtod      strtod
#else
typedef double SDLCALL tSDL_strtod(const char *string, char **endp);
#endif

#ifdef HAVE_ATOI
#define SDL_atoi        atoi
#else
#define SDL_atoi(X)     SDL_strtol(X, NULL, 0)
#endif

#ifdef HAVE_ATOF
#define SDL_atof        atof
#else
#define SDL_atof(X)     SDL_strtod(X, NULL)
#endif

#ifdef HAVE_STRCMP
#define SDL_strcmp      strcmp
#else
typedef int SDLCALL tSDL_strcmp(const char *str1, const char *str2);
#endif

#ifdef HAVE_STRNCMP
#define SDL_strncmp     strncmp
#else
typedef int SDLCALL tSDL_strncmp(const char *str1, const char *str2, size_t maxlen);
#endif

#ifdef HAVE_STRCASECMP
#define SDL_strcasecmp  strcasecmp
#elif defined(HAVE__STRICMP)
#define SDL_strcasecmp  _stricmp
#else
typedef int SDLCALL tSDL_strcasecmp(const char *str1, const char *str2);
#endif

#ifdef HAVE_STRNCASECMP
#define SDL_strncasecmp strncasecmp
#elif defined(HAVE__STRNICMP)
#define SDL_strncasecmp _strnicmp
#else
typedef int SDLCALL tSDL_strncasecmp(const char *str1, const char *str2, size_t maxlen);
#endif

#ifdef HAVE_SSCANF
#define SDL_sscanf      sscanf
#else
typedef int SDLCALL tSDL_sscanf(const char *text, const char *fmt, ...);
#endif

#ifdef HAVE_SNPRINTF
#define SDL_snprintf    snprintf
#else
typedef int SDLCALL tSDL_snprintf(char *text, size_t maxlen, const char *fmt, ...);
#endif

#ifdef HAVE_VSNPRINTF
#define SDL_vsnprintf   vsnprintf
#else
typedef int SDLCALL tSDL_vsnprintf(char *text, size_t maxlen, const char *fmt, va_list ap);
#endif

/** @name SDL_ICONV Error Codes
 *  The SDL implementation of iconv() returns these error codes 
 */
/*@{*/
#define SDL_ICONV_ERROR		(size_t)-1
#define SDL_ICONV_E2BIG		(size_t)-2
#define SDL_ICONV_EILSEQ	(size_t)-3
#define SDL_ICONV_EINVAL	(size_t)-4
/*@}*/

#if defined(HAVE_ICONV) && defined(HAVE_ICONV_H)
#define SDL_iconv_t     iconv_t
#define SDL_iconv_open  iconv_open
#define SDL_iconv_close iconv_close
#else
typedef struct _SDL_iconv_t *SDL_iconv_t;
typedef SDL_iconv_t SDLCALL tSDL_iconv_open(const char *tocode, const char *fromcode);
typedef int SDLCALL tSDL_iconv_close(SDL_iconv_t cd);
#endif
typedef size_t SDLCALL tSDL_iconv(SDL_iconv_t cd, const char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft);
/** This function converts a string between encodings in one pass, returning a
 *  string that must be freed with SDL_free() or NULL on error.
 */
typedef char * SDLCALL tSDL_iconv_string(const char *tocode, const char *fromcode, const char *inbuf, size_t inbytesleft);
#define SDL_iconv_utf8_locale(S)	SDL_iconv_string("", "UTF-8", S, SDL_strlen(S)+1)
#define SDL_iconv_utf8_ucs2(S)		(Uint16 *)SDL_iconv_string("UCS-2", "UTF-8", S, SDL_strlen(S)+1)
#define SDL_iconv_utf8_ucs4(S)		(Uint32 *)SDL_iconv_string("UCS-4", "UTF-8", S, SDL_strlen(S)+1)

#ifndef HAVE_MALLOC
extern tSDL_malloc *SDL_malloc;
#endif
#ifndef HAVE_CALLOC
extern tSDL_calloc *SDL_calloc;
#endif
#ifndef HAVE_REALLOC
extern tSDL_realloc *SDL_realloc;
#endif
#ifndef HAVE_FREE
extern tSDL_free *SDL_free;
#endif
#ifndef HAVE_GETENV
extern tSDL_getenv *SDL_getenv;
#endif
#ifndef HAVE_PUTENV
extern tSDL_putenv *SDL_putenv;
#endif
#ifndef HAVE_QSORT
extern tSDL_qsort *SDL_qsort;
#endif
#ifndef HAVE_MEMSET
extern tSDL_memset *SDL_memset;
#endif
#ifndef HAVE_MEMCPY
extern tSDL_memcpy *SDL_memcpy;
#endif
extern tSDL_revcpy *SDL_revcpy;
#ifndef HAVE_MEMCMP
extern tSDL_memcmp *SDL_memcmp;
#endif
#ifndef HAVE_STRLEN
extern tSDL_strlen *SDL_strlen;
#endif
#ifndef HAVE_STRLCPY
extern tSDL_strlcpy *SDL_strlcpy;
#endif
#ifndef HAVE_STRLCAT
extern tSDL_strlcat *SDL_strlcat;
#endif
#ifndef HAVE_STRDUP
extern tSDL_strdup *SDL_strdup;
#endif
#ifndef HAVE__STRREV
extern tSDL_strrev *SDL_strrev;
#endif
#ifndef HAVE__STRUPR
extern tSDL_strupr *SDL_strupr;
#endif
#ifndef HAVE__STRLWR
extern tSDL_strlwr *SDL_strlwr;
#endif
#ifndef HAVE_STRCHR
extern tSDL_strchr *SDL_strchr;
#endif
#ifndef HAVE_STRRCHR
extern tSDL_strrchr *SDL_strrchr;
#endif
#ifndef HAVE_STRSTR
extern tSDL_strstr *SDL_strstr;
#endif
#ifndef HAVE__LTOA
extern tSDL_ltoa *SDL_ltoa;
#endif
#ifndef HAVE__ULTOA
extern tSDL_ultoa *SDL_ultoa;
#endif
#ifndef HAVE_STRTOL
extern tSDL_strtol *SDL_strtol;
#endif
#ifndef HAVE_STRTOLL
extern tSDL_strtoll *SDL_strtoll;
#endif
#ifndef HAVE_STRTOULL
extern tSDL_strtoull *SDL_strtoull;
#endif
#ifndef HAVE_STRTOD
extern tSDL_strtod *SDL_strtod;
#endif
#ifndef HAVE_STRCMP
extern tSDL_strcmp *SDL_strcmp;
#endif
#ifndef HAVE_STRNCMP
extern tSDL_strncmp *SDL_strncmp;
#endif
#ifndef HAVE_STRCASECMP
extern tSDL_strcasecmp *SDL_strcasecmp;
#endif
#ifndef HAVE_STRNCASECMP
extern tSDL_strncasecmp *SDL_strncasecmp;
#endif
#ifndef HAVE_SSCANF
extern tSDL_sscanf *SDL_sscanf;
#endif
#ifndef HAVE_SNPRINTF
extern tSDL_snprintf *SDL_snprintf;
#endif
#ifndef HAVE_VSNPRINTF
extern tSDL_vsnprintf *SDL_vsnprintf;
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
extern tSDL_iconv_open *SDL_iconv_open;
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
extern tSDL_iconv_close *SDL_iconv_close;
#endif
extern tSDL_iconv *SDL_iconv;
extern tSDL_iconv_string *SDL_iconv_string;

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _SDL_stdinc_h */
