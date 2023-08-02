#ifndef TYPES_H
#define TYPES_H

#include <string.h>

#include "config.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;

/*
 * You may use the following defines to adjust the type definitions
 * depending on the architecture:
 * - Define BIGENDIAN on big-endian systems.
 */

#ifdef BIGENDIAN
typedef struct {
	u32 h;
	u32 l;
} u64;
#else
typedef struct {
	u32 l;
	u32 h;
} u64;
#endif

static inline u64 U64(u32 low, u32 high)
{
	u64 self;

	self.l = low;
	self.h = high;

	return self;
}

/*
 * Per SMBIOS v2.8.0 and later, all structures assume a little-endian
 * ordering convention.
 */
static inline u16 WORD(const void *x)
{
	u16 ret;
	memcpy(&ret, x, sizeof(ret));
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	ret = __builtin_bswap16(ret);
#endif
	return ret;
}

static inline u32 DWORD(const void *x)
{
	u32 ret;
	memcpy(&ret, x, sizeof(ret));
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	ret = __builtin_bswap32(ret);
#endif
	return ret;
}

#define QWORD(x) (U64(DWORD(x), DWORD(x + 4)))

#endif
