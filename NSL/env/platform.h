/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_PLATFORM_H
#define NSL_PLATFORM_H

#if defined(__clang__) || defined(__GNUC__)  || defined(__GNUG__)
# define GNU_COMPILER
#endif

	// FORCE INLINING
#if defined(GNU_COMPILER)
# define FORCEINLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
# define FORCEINLINE __forceinline
#else
# define FORCEINLINE inline
#endif

	// FUNCTION RETURNING A MEMORY ALLOCATED BLOC
#if defined(GNU_COMPILER)
# define MALLOC_ATTR __attribute__((malloc))
#else
# define MALLOC_ATTR
#endif

# include <assert.h>

typedef char				bool8;
typedef short				bool16;
typedef int					bool32;
typedef long long			bool64;

typedef char				char1w;
typedef short				char2w;
typedef wchar_t				char4w;

typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef float				float32;
typedef double				float64;

#endif
