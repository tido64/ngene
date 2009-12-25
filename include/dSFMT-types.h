#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#	include <inttypes.h>
#elif defined(_MSC_VER) || defined(__BORLANDC__)
#	if !defined(DSFMT_UINT32_DEFINED) && !defined(SFMT_UINT32_DEFINED)
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
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

#else // plain C

/// 128-bit data structure */
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