#ifndef DSFMT_PARAMS_H_
#define DSFMT_PARAMS_H_

#define DSFMT_LOW_MASK		UINT64_C(0x000FFFFFFFFFFFFF)
#define DSFMT_HIGH_CONST	UINT64_C(0x3FF0000000000000)
#define DSFMT_SR			12

#if defined(__SSE2__)
#	define SSE2_SHUFF 0x1b
#elif defined(__ALTIVEC__)
#	if defined(__APPLE__)
#		define ALTI_SR		(vector unsigned char)(4)
#		define ALTI_SR_PERM	(vector unsigned char)(15,0,1,2,3,4,5,6,15,8,9,10,11,12,13,14)
#		define ALTI_SR_MSK	(vector unsigned int)(0x000fffffU,0xffffffffU,0x000fffffU,0xffffffffU)
#		define ALTI_PERM	(vector unsigned char)(12,13,14,15,8,9,10,11,4,5,6,7,0,1,2,3)
#	else
#		define ALTI_SR      {4}
#		define ALTI_SR_PERM	{15,0,1,2,3,4,5,6,15,8,9,10,11,12,13,14}
#		define ALTI_SR_MSK  {0x000fffffU,0xffffffffU,0x000fffffU,0xffffffffU}
#		define ALTI_PERM    {12,13,14,15,8,9,10,11,4,5,6,7,0,1,2,3}
#	endif
#endif

// Begin dSFMT-params19937.h
#define DSFMT_MEXP		19937
//#define DSFMT_N			191
//#define DSFMT_MAXDEGREE	19992
#define DSFMT_POS1		117
#define DSFMT_SL1		19
#define DSFMT_MSK1		UINT64_C(0x000ffafffffffb3f)
#define DSFMT_MSK2		UINT64_C(0x000ffdfffc90fffd)
#define DSFMT_MSK32_1	0x000ffaffU
#define DSFMT_MSK32_2	0xfffffb3fU
#define DSFMT_MSK32_3	0x000ffdffU
#define DSFMT_MSK32_4	0xfc90fffdU
#define DSFMT_FIX1		UINT64_C(0x90014964b32f4329)
#define DSFMT_FIX2		UINT64_C(0x3b8d12ac548a7c7a)
#define DSFMT_PCV1		UINT64_C(0x3d84e1ac0dc82880)
#define DSFMT_PCV2		UINT64_C(0x0000000000000001)
#define DSFMT_IDSTR		"dSFMT2-19937:117-19:ffafffffffb3f-ffdfffc90fffd"

// Parameters for AltiVec
#if defined(__APPLE__) // For OSX
	#define ALTI_SL1 (vector unsigned int)(3, 3, 3, 3)
	#define ALTI_SL1_PERM (vector unsigned char)(2,3,4,5,6,7,30,30,10,11,12,13,14,15,0,1)
	#define ALTI_SL1_MSK (vector unsigned int)(0xffffffffU,0xfff80000U,0xffffffffU,0xfff80000U)
	#define ALTI_MSK (vector unsigned int)(DSFMT_MSK32_1, DSFMT_MSK32_2, DSFMT_MSK32_3, DSFMT_MSK32_4)
#else // For OTHER OSs(Linux?)
    #define ALTI_SL1 {3, 3, 3, 3}
    #define ALTI_SL1_PERM {2,3,4,5,6,7,30,30,10,11,12,13,14,15,0,1}
    #define ALTI_SL1_MSK {0xffffffffU,0xfff80000U,0xffffffffU,0xfff80000U}
    #define ALTI_MSK {DSFMT_MSK32_1, DSFMT_MSK32_2, DSFMT_MSK32_3, DSFMT_MSK32_4}
#endif
// End dSFMT-params19937.h

/// DSFMT generator has an internal state array of 128-bit integers, and N is its size.
#define DSFMT_N ((DSFMT_MEXP - 128) / 104 + 1)
/// N32 is the size of internal state array when regarded as an array of 32-bit integers.
#define DSFMT_N32 (DSFMT_N * 4)
/// N64 is the size of internal state array when regarded as an array of 64-bit integers.
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
#	elif defined(__BIG_ENDIAN) || defined(_BIG_ENDIAN) || defined(__BIG_ENDIAN__) || defined(BIG_ENDIAN)
#		define DSFMT_BIG_ENDIAN 1
#	endif
#endif

#if defined(DSFMT_BIG_ENDIAN) && defined(__amd64)
#	undef DSFMT_BIG_ENDIAN
#endif

#include "dSFMT-types.h"

#endif