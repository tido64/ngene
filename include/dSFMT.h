/**
 * @file dSFMT.h
 *
 * @brief double precision SIMD oriented Fast Mersenne Twister(dSFMT)
 * pseudorandom number generator based on IEEE 754 format.
 *
 * @author Mutsuo Saito (Hiroshima University)
 * @author Makoto Matsumoto (Hiroshima University)
 *
 * Copyright (C) 2007, 2008 Mutsuo Saito, Makoto Matsumoto and
 * Hiroshima University. All rights reserved.
 *
 * The new BSD License is applied to this software.
 * see LICENSE.txt
 *
 * @note We assume that your system has inttypes.h.  If your system
 * doesn't have inttypes.h, you have to typedef uint32_t and uint64_t,
 * and you have to define PRIu64 and PRIx64 in this file as follows:
 * @verbatim
	typedef unsigned int uint32_t
	typedef unsigned long long uint64_t
	#define PRIu64 "llu"
	#define PRIx64 "llx"
@endverbatim
 * uint32_t must be exactly 32-bit unsigned integer type (no more, no
 * less), and uint64_t must be exactly 64-bit unsigned integer type.
 * PRIu64 and PRIx64 are used for printf function to print 64-bit
 * unsigned int and 64-bit unsigned int in hexadecimal format.
 */

#ifndef DSFMT_H_
#define DSFMT_H_

#include <cassert>
#include <cstdio>

/*-----------------
  BASIC DEFINITIONS
  -----------------*/

/// Mersenne Exponent. The period of the sequence is a multiple of
/// 2^DSFMT_MEXP-1.
#define DSFMT_MEXP 19937

/// DSFMT generator has an internal state array of 128-bit integers, and N is
/// its size.
#define DSFMT_N ((DSFMT_MEXP - 128) / 104 + 1)

/// N32 is the size of internal state array when regarded as an array of 32-bit
/// integers.
#define DSFMT_N32 (DSFMT_N * 4)

/// N64 is the size of internal state array when regarded as an array of 64-bit
/// integers.
#define DSFMT_N64 (DSFMT_N * 2)

#if !defined(DSFMT_BIG_ENDIAN)
#	if defined(__BYTE_ORDER) && defined(__BIG_ENDIAN)
#		if __BYTE_ORDER == __BIG_ENDIAN
#			define DSFMT_BIG_ENDIAN 1
#		endif
#	elif defined(_BYTE_ORDER) && defined(_BIG_ENDIAN)
#		if _BYTE_ORDER == _BIG_ENDIAN
#			define DSFMT_BIG_ENDIAN 1
#		endif
#	elif defined(__BYTE_ORDER__) && defined(__BIG_ENDIAN__)
#		if __BYTE_ORDER__ == __BIG_ENDIAN__
#			define DSFMT_BIG_ENDIAN 1
#		endif
#	elif defined(BYTE_ORDER) && defined(BIG_ENDIAN)
#		if BYTE_ORDER == BIG_ENDIAN
#			define DSFMT_BIG_ENDIAN 1
#		endif
#	elif defined(__BIG_ENDIAN) || defined(_BIG_ENDIAN) \
		|| defined(__BIG_ENDIAN__) || defined(BIG_ENDIAN)
#			define DSFMT_BIG_ENDIAN 1
#	endif
#endif

#if defined(DSFMT_BIG_ENDIAN) && defined(__amd64)
#	undef DSFMT_BIG_ENDIAN
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#	include <inttypes.h>
#elif defined(_MSC_VER) || defined(__BORLANDC__)
#	if !defined(DSFMT_UINT32_DEFINED) && !defined(SFMT_UINT32_DEFINED)
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#		define UINT64_C(v) (v ## ui64)
#		define DSFMT_UINT32_DEFINED
#		if !defined(inline)
#			define inline __inline
#		endif
#	endif
#else
#	include <inttypes.h>
#	if !defined(inline)
#		if defined(__GNUC__)
#			define inline __inline__
#		else
#			define inline
#		endif
#	endif
#endif

#ifndef PRIu64
#	if defined(_MSC_VER) || defined(__BORLANDC__)
#		define PRIu64 "I64u"
#		define PRIx64 "I64x"
#	else
#		define PRIu64 "llu"
#		define PRIx64 "llx"
#	endif
#endif

#ifndef UINT64_C
#	define UINT64_C(v) (v ## ULL)
#endif

/*------------------------------------------
  128-bit SIMD like data type for standard C
  ------------------------------------------*/
#if defined(__ALTIVEC__)
#	if !defined(__APPLE__)
#		include <altivec.h>
#	endif

/// 128-bit data structure
union W128_T
{
    vector unsigned int s;
    uint64_t u[2];
    uint32_t u32[4];
    double d[2];
};

#elif defined(__SSE2__)
#	include <emmintrin.h>

/// 128-bit data structure
union W128_T
{
    __m128i si;
    __m128d sd;
    uint64_t u[2];
    uint32_t u32[4];
    double d[2];
};

#else  // standard C

/// 128-bit data structure
union W128_T
{
    uint64_t u[2];
    uint32_t u32[4];
    double d[2];
};

#endif

/// 128-bit data type
typedef union W128_T w128_t;

/// the 128-bit internal state array
struct DSFMT_T
{
    w128_t status[DSFMT_N + 1];
    int idx;
};

typedef struct DSFMT_T dsfmt_t;

#endif
