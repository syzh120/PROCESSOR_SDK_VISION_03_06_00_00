/*
   LZ4 - Fast LZ compression algorithm
   Copyright (C) 2011-2017, Yann Collet.

   BSD 2-Clause License (http://www.opensource.org/licenses/bsd-license.php)

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

       * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following disclaimer
   in the documentation and/or other materials provided with the
   distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   You can contact the author at :
    - LZ4 homepage : http://www.lz4.org
    - LZ4 source repository : https://github.com/lz4/lz4
*/


/*-************************************
*  Tuning parameters
**************************************/
/*
 * LZ4_HEAPMODE :
 * Select how default compression functions will allocate memory for their hash table,
 * in memory stack (0:default, fastest), or in memory heap (1:requires malloc()).
 */
#ifndef LZ4_HEAPMODE
#  define LZ4_HEAPMODE 0
#endif

/*
 * ACCELERATION_DEFAULT :
 * Select "acceleration" for LZ4_compress_fast() when parameter value <= 0
 */
#define ACCELERATION_DEFAULT 1


/*-************************************
*  CPU Feature Detection
**************************************/
/* LZ4_FORCE_MEMORY_ACCESS
 * By default, access to unaligned memory is controlled by `memcpy()`, which is safe and portable.
 * Unfortunately, on some target/compiler combinations, the generated assembly is sub-optimal.
 * The below switch allow to select different access method for improved performance.
 * Method 0 (default) : use `memcpy()`. Safe and portable.
 * Method 1 : `__packed` statement. It depends on compiler extension (ie, not portable).
 *            This method is safe if your compiler supports it, and *generally* as fast or faster than `memcpy`.
 * Method 2 : direct access. This method is portable but violate C standard.
 *            It can generate buggy code on targets which assembly generation depends on alignment.
 *            But in some circumstances, it's the only known way to get the most performance (ie GCC + ARMv6)
 * See https://fastcompression.blogspot.fr/2015/08/accessing-unaligned-memory.html for details.
 * Prefer these methods in priority order (0 > 1 > 2)
 */

/*
 * LZ4_FORCE_SW_BITCOUNT
 * Define this parameter if your target system or compiler does not support hardware bit count
 */


/*-************************************
*  Dependency
**************************************/
#include "lz4.h"

/*-************************************
*  Compiler Options
**************************************/
#ifndef FORCE_INLINE
#      define FORCE_INLINE static
#endif /* LZ4_FORCE_INLINE */

/* LZ4_FORCE_O2_GCC_PPC64LE and LZ4_FORCE_O2_INLINE_GCC_PPC64LE
 * Gcc on ppc64le generates an unrolled SIMDized loop for LZ4_wildCopy,
 * together with a simple 8-byte copy loop as a fall-back path.
 * However, this optimization hurts the decompression speed by >30%,
 * because the execution does not go to the optimized loop
 * for typical compressible data, and all of the preamble checks
 * before going to the fall-back path become useless overhead.
 * This optimization happens only with the -O3 flag, and -O2 generates
 * a simple 8-byte copy loop.
 * With gcc on ppc64le, all of the LZ4_decompress_* and LZ4_wildCopy
 * functions are annotated with __attribute__((optimize("O2"))),
 * and also LZ4_wildCopy is forcibly inlined, so that the O2 attribute
 * of LZ4_wildCopy does not affect the compression speed.
 */
#  define LZ4_FORCE_O2_GCC_PPC64LE
#  define LZ4_FORCE_O2_INLINE_GCC_PPC64LE static
#  define expect(expr,value)    (expr)

#define likely(expr)     expect((expr) != 0, 1)
#define unlikely(expr)   expect((expr) != 0, 0)


/*-************************************
*  Memory routines
**************************************/
#include "../../../../../apps/src/include/chains_common_osal.h"   /* malloc, calloc, free */
#define ALLOCATOR(n,s) ChainsCommon_Osal_memAlloc(n*s, 0)
#define FREEMEM        free
#include <string.h>   /* memset, memcpy */
#define MEM_INIT       memset

/*-************************************
*  Basic Types
**************************************/
# include <stdint.h>

/*-************************************
*  Reading and writing into memory
**************************************/
static uint32_t LZ4_isLittleEndian(void)
{
    const union { uint32_t u; uint8_t c[4]; } one = { 1 };   /* don't use static : performance detrimental */
    return one.c[0];
}

static uint16_t LZ4_read16(const void* memPtr)
{
    uint16_t val; memcpy(&val, memPtr, sizeof(val)); return val;
}

static uint32_t LZ4_read32(const void* memPtr)
{
    uint32_t val; memcpy(&val, memPtr, sizeof(val)); return val;
}

static uint64_t LZ4_read_ARCH(const void* memPtr)
{
    uint64_t val; memcpy(&val, memPtr, sizeof(val)); return val;
}

static void LZ4_write16(void* memPtr, uint16_t value)
{
    memcpy(memPtr, &value, sizeof(value));
}

static void LZ4_write32(void* memPtr, uint32_t value)
{
    memcpy(memPtr, &value, sizeof(value));
}

static uint16_t LZ4_readLE16(const void* memPtr)
{
    if (LZ4_isLittleEndian()) {
        return LZ4_read16(memPtr);
    } else {
        const uint8_t* p = (const uint8_t*)memPtr;
        return (uint16_t)((uint16_t)p[0] + (p[1]<<8));
    }
}

static void LZ4_writeLE16(void* memPtr, uint16_t value)
{
    if (LZ4_isLittleEndian()) {
        LZ4_write16(memPtr, value);
    } else {
        uint8_t* p = (uint8_t*)memPtr;
        p[0] = (uint8_t) value;
        p[1] = (uint8_t)(value>>8);
    }
}

static void LZ4_copy8(void* dst, const void* src)
{
    memcpy(dst,src,8);
}

/* customized variant of memcpy, which can overwrite up to 8 bytes beyond dstEnd */
static void LZ4_wildCopy(void* dstPtr, const void* srcPtr, void* dstEnd)
{
    uint8_t* d = (uint8_t*)dstPtr;
    const uint8_t* s = (const uint8_t*)srcPtr;
    uint8_t* const e = (uint8_t*)dstEnd;

    do { LZ4_copy8(d,s); d+=8; s+=8; } while (d<e);
}


/*-************************************
*  Common Constants
**************************************/
#define MINMATCH 4

#define WILDCOPYLENGTH 8
#define LASTLITERALS 5
#define MFLIMIT (WILDCOPYLENGTH+MINMATCH)
static const int32_t LZ4_minLength = (MFLIMIT+1);

#define GB *(1U<<30)

#define MAXD_LOG 16
#define MAX_DISTANCE ((1 << MAXD_LOG) - 1)

#define ML_BITS  4
#define ML_MASK  ((1U<<ML_BITS)-1)
#define RUN_BITS (8-ML_BITS)
#define RUN_MASK ((1U<<RUN_BITS)-1)


/*-************************************
*  Error detection
**************************************/
#define LZ4_STATIC_ASSERT(c)    { enum { LZ4_static_assert = 1/(int32_t)(!!(c)) }; }   /* use only *after* variable declarations */

/*-************************************
*  Common functions
**************************************/
static uint32_t LZ4_NbCommonBytes (register uint64_t val)
{
    if (LZ4_isLittleEndian()) {
        if (sizeof(val)==8) {
            static const int32_t DeBruijnBytePos[64] = { 0, 0, 0, 0, 0, 1, 1, 2, 0, 3, 1, 3, 1, 4, 2, 7, 0, 2, 3, 6, 1, 5, 3, 5, 1, 3, 4, 4, 2, 5, 6, 7, 7, 0, 1, 2, 3, 3, 4, 6, 2, 6, 5, 5, 3, 4, 5, 6, 7, 1, 2, 4, 6, 4, 4, 5, 7, 2, 6, 5, 7, 6, 7, 7 };
            return DeBruijnBytePos[((uint64_t)((val & -(int64_t)val) * 0x0218A392CDABBD3FULL)) >> 58];
        } else /* 32 bits */ {
            static const int32_t DeBruijnBytePos[32] = { 0, 0, 3, 0, 3, 1, 3, 0, 3, 2, 2, 1, 3, 2, 0, 1, 3, 3, 1, 2, 2, 2, 2, 0, 3, 1, 2, 0, 1, 0, 1, 1 };
            return DeBruijnBytePos[((uint32_t)((val & -(int32_t)val) * 0x077CB531U)) >> 27];
        }
    } else   /* Big Endian CPU */ {
        if (sizeof(val)==8) {   /* 64-bits */
            static const uint32_t by32 = sizeof(val)*4;  /* 32 on 64 bits (goal), 16 on 32 bits.
                Just to avoid some static analyzer complaining about shift by 32 on 32-bits target.
                Note that this code path is never triggered in 32-bits mode. */
            uint32_t r;
            if (!(val>>by32)) { r=4; } else { r=0; val>>=by32; }
            if (!(val>>16)) { r+=2; val>>=8; } else { val>>=24; }
            r += (!val);
            return r;
        } else /* 32 bits */ {
            uint32_t r;
            if (!(val>>16)) { r=2; val>>=8; } else { r=0; val>>=24; }
            r += (!val);
            return r;
        }
    }
}

#define STEPSIZE sizeof(uint64_t)
static uint32_t LZ4_count(const uint8_t* pIn, const uint8_t* pMatch, const uint8_t* pInLimit)
{
    const uint8_t* const pStart = pIn;

    while (likely(pIn<pInLimit-(STEPSIZE-1))) {
        uint64_t const diff = LZ4_read_ARCH(pMatch) ^ LZ4_read_ARCH(pIn);
        if (!diff) { pIn+=STEPSIZE; pMatch+=STEPSIZE; continue; }
        pIn += LZ4_NbCommonBytes(diff);
        return (uint32_t)(pIn - pStart);
    }

    if ((STEPSIZE==8) && (pIn<(pInLimit-3)) && (LZ4_read32(pMatch) == LZ4_read32(pIn))) { pIn+=4; pMatch+=4; }
    if ((pIn<(pInLimit-1)) && (LZ4_read16(pMatch) == LZ4_read16(pIn))) { pIn+=2; pMatch+=2; }
    if ((pIn<pInLimit) && (*pMatch == *pIn)) pIn++;
    return (uint32_t)(pIn - pStart);
}


#ifndef LZ4_COMMONDEFS_ONLY
/*-************************************
*  Local Constants
**************************************/
static const int32_t LZ4_64Klimit = ((64 * 1024) + (MFLIMIT-1));
static const uint32_t LZ4_skipTrigger = 6;  /* Increase this value ==> compression run slower on incompressible data */


/*-************************************
*  Local Structures and types
**************************************/
typedef enum { notLimited = 0, limitedOutput = 1 } limitedOutput_directive;
typedef enum { byPtr, byU32, byU16 } tableType_t;

typedef enum { noDict = 0, withPrefix64k, usingExtDict } dict_directive;
typedef enum { noDictIssue = 0, dictSmall } dictIssue_directive;

typedef enum { endOnOutputSize = 0, endOnInputSize = 1 } endCondition_directive;
typedef enum { full = 0, partial = 1 } earlyEnd_directive;


/*-************************************
*  Local Utils
**************************************/
int32_t LZ4_versionNumber (void) { return LZ4_VERSION_NUMBER; }
const char* LZ4_versionString(void) { return LZ4_VERSION_STRING; }
int32_t LZ4_compressBound(int32_t isize)  { return LZ4_COMPRESSBOUND(isize); }
int32_t LZ4_sizeofState() { return LZ4_STREAMSIZE; }


/*-******************************
*  Compression functions
********************************/
static uint32_t LZ4_hash4(uint32_t sequence, tableType_t const tableType)
{
    if (tableType == byU16)
        return ((sequence * 2654435761U) >> ((MINMATCH*8)-(LZ4_HASHLOG+1)));
    else
        return ((sequence * 2654435761U) >> ((MINMATCH*8)-LZ4_HASHLOG));
}

static uint32_t LZ4_hash5(uint64_t sequence, tableType_t const tableType)
{
    static const uint64_t prime5bytes = 889523592379ULL;
    static const uint64_t prime8bytes = 11400714785074694791ULL;
    const uint32_t hashLog = (tableType == byU16) ? LZ4_HASHLOG+1 : LZ4_HASHLOG;
    if (LZ4_isLittleEndian())
        return (uint32_t)(((sequence << 24) * prime5bytes) >> (64 - hashLog));
    else
        return (uint32_t)(((sequence >> 24) * prime8bytes) >> (64 - hashLog));
}

FORCE_INLINE uint32_t LZ4_hashPosition(const void* const p, tableType_t const tableType)
{
    if ((sizeof(uint64_t)==8) && (tableType != byU16)) return LZ4_hash5(LZ4_read_ARCH(p), tableType);
    return LZ4_hash4(LZ4_read32(p), tableType);
}

static void LZ4_putPositionOnHash(const uint8_t* p, uint32_t h, void* tableBase, tableType_t const tableType, const uint8_t* srcBase)
{
    switch (tableType)
    {
    case byPtr: { const uint8_t** hashTable = (const uint8_t**)tableBase; hashTable[h] = p; return; }
    case byU32: { uint32_t* hashTable = (uint32_t*) tableBase; hashTable[h] = (uint32_t)(p-srcBase); return; }
    case byU16: { uint16_t* hashTable = (uint16_t*) tableBase; hashTable[h] = (uint16_t)(p-srcBase); return; }
    }
}

FORCE_INLINE void LZ4_putPosition(const uint8_t* p, void* tableBase, tableType_t tableType, const uint8_t* srcBase)
{
    uint32_t const h = LZ4_hashPosition(p, tableType);
    LZ4_putPositionOnHash(p, h, tableBase, tableType, srcBase);
}

static const uint8_t* LZ4_getPositionOnHash(uint32_t h, void* tableBase, tableType_t tableType, const uint8_t* srcBase)
{
    if (tableType == byPtr) { const uint8_t** hashTable = (const uint8_t**) tableBase; return hashTable[h]; }
    if (tableType == byU32) { const uint32_t* const hashTable = (uint32_t*) tableBase; return hashTable[h] + srcBase; }
    { const uint16_t* const hashTable = (uint16_t*) tableBase; return hashTable[h] + srcBase; }   /* default, to ensure a return */
}

FORCE_INLINE const uint8_t* LZ4_getPosition(const uint8_t* p, void* tableBase, tableType_t tableType, const uint8_t* srcBase)
{
    uint32_t const h = LZ4_hashPosition(p, tableType);
    return LZ4_getPositionOnHash(h, tableBase, tableType, srcBase);
}


/** LZ4_compress_generic() :
    inlined, to ensure branches are decided at compilation time */
FORCE_INLINE int32_t LZ4_compress_generic(
                 LZ4_stream_t_internal* const cctx,
                 const char* const source,
                 char* const dest,
                 const int32_t inputSize,
                 const int32_t maxOutputSize,
                 const limitedOutput_directive outputLimited,
                 const tableType_t tableType,
                 const dict_directive dict,
                 const dictIssue_directive dictIssue,
                 const uint32_t acceleration)
{
    const uint8_t* ip = (const uint8_t*) source;
    const uint8_t* base;
    const uint8_t* lowLimit;
    const uint8_t* const lowRefLimit = ip - cctx->dictSize;
    const uint8_t* const dictionary = cctx->dictionary;
    const uint8_t* const dictEnd = dictionary + cctx->dictSize;
    const int64_t dictDelta = dictEnd - (const uint8_t*)source;
    const uint8_t* anchor = (const uint8_t*) source;
    const uint8_t* const iend = ip + inputSize;
    const uint8_t* const mflimit = iend - MFLIMIT;
    const uint8_t* const matchlimit = iend - LASTLITERALS;

    uint8_t* op = (uint8_t*) dest;
    uint8_t* const olimit = op + maxOutputSize;

    uint32_t forwardH;

    /* Init conditions */
    if ((uint32_t)inputSize > (uint32_t)LZ4_MAX_INPUT_SIZE) return 0;   /* Unsupported inputSize, too large (or negative) */
    switch(dict)
    {
    case noDict:
    default:
        base = (const uint8_t*)source;
        lowLimit = (const uint8_t*)source;
        break;
    case withPrefix64k:
        base = (const uint8_t*)source - cctx->currentOffset;
        lowLimit = (const uint8_t*)source - cctx->dictSize;
        break;
    case usingExtDict:
        base = (const uint8_t*)source - cctx->currentOffset;
        lowLimit = (const uint8_t*)source;
        break;
    }
    if ((tableType == byU16) && (inputSize>=LZ4_64Klimit)) return 0;   /* Size too large (not within 64K limit) */
    if (inputSize<LZ4_minLength) goto _last_literals;                  /* Input too small, no compression (all literals) */

    /* First Byte */
    LZ4_putPosition(ip, cctx->hashTable, tableType, base);
    ip++; forwardH = LZ4_hashPosition(ip, tableType);

    /* Main Loop */
    for ( ; ; ) {
        int64_t refDelta = 0;
        const uint8_t* match;
        uint8_t* token;

        /* Find a match */
        {   const uint8_t* forwardIp = ip;
            uint32_t step = 1;
            uint32_t searchMatchNb = acceleration << LZ4_skipTrigger;
            do {
                uint32_t const h = forwardH;
                ip = forwardIp;
                forwardIp += step;
                step = (searchMatchNb++ >> LZ4_skipTrigger);

                if (unlikely(forwardIp > mflimit)) goto _last_literals;

                match = LZ4_getPositionOnHash(h, cctx->hashTable, tableType, base);
                if (dict==usingExtDict) {
                    if (match < (const uint8_t*)source) {
                        refDelta = dictDelta;
                        lowLimit = dictionary;
                    } else {
                        refDelta = 0;
                        lowLimit = (const uint8_t*)source;
                }   }
                forwardH = LZ4_hashPosition(forwardIp, tableType);
                LZ4_putPositionOnHash(ip, h, cctx->hashTable, tableType, base);

            } while ( ((dictIssue==dictSmall) ? (match < lowRefLimit) : 0)
                || ((tableType==byU16) ? 0 : (match + MAX_DISTANCE < ip))
                || (LZ4_read32(match+refDelta) != LZ4_read32(ip)) );
        }

        /* Catch up */
        while (((ip>anchor) & (match+refDelta > lowLimit)) && (unlikely(ip[-1]==match[refDelta-1]))) { ip--; match--; }

        /* Encode Literals */
        {   uint32_t const litLength = (uint32_t)(ip - anchor);
            token = op++;
            if ((outputLimited) &&  /* Check output buffer overflow */
                (unlikely(op + litLength + (2 + 1 + LASTLITERALS) + (litLength/255) > olimit)))
                return 0;
            if (litLength >= RUN_MASK) {
                int32_t len = (int32_t)litLength-RUN_MASK;
                *token = (RUN_MASK<<ML_BITS);
                for(; len >= 255 ; len-=255) *op++ = 255;
                *op++ = (uint8_t)len;
            }
            else *token = (uint8_t)(litLength<<ML_BITS);

            /* Copy Literals */
            LZ4_wildCopy(op, anchor, op+litLength);
            op+=litLength;
        }

_next_match:
        /* Encode Offset */
        LZ4_writeLE16(op, (uint16_t)(ip-match)); op+=2;

        /* Encode MatchLength */
        {   uint32_t matchCode;

            if ((dict==usingExtDict) && (lowLimit==dictionary)) {
                const uint8_t* limit;
                match += refDelta;
                limit = ip + (dictEnd-match);
                if (limit > matchlimit) limit = matchlimit;
                matchCode = LZ4_count(ip+MINMATCH, match+MINMATCH, limit);
                ip += MINMATCH + matchCode;
                if (ip==limit) {
                    uint32_t const more = LZ4_count(ip, (const uint8_t*)source, matchlimit);
                    matchCode += more;
                    ip += more;
                }
            } else {
                matchCode = LZ4_count(ip+MINMATCH, match+MINMATCH, matchlimit);
                ip += MINMATCH + matchCode;
            }

            if ( outputLimited &&    /* Check output buffer overflow */
                (unlikely(op + (1 + LASTLITERALS) + (matchCode>>8) > olimit)) )
                return 0;
            if (matchCode >= ML_MASK) {
                *token += ML_MASK;
                matchCode -= ML_MASK;
                LZ4_write32(op, 0xFFFFFFFF);
                while (matchCode >= 4*255) op+=4, LZ4_write32(op, 0xFFFFFFFF), matchCode -= 4*255;
                op += matchCode / 255;
                *op++ = (uint8_t)(matchCode % 255);
            } else
                *token += (uint8_t)(matchCode);
        }

        anchor = ip;

        /* Test end of chunk */
        if (ip > mflimit) break;

        /* Fill table */
        LZ4_putPosition(ip-2, cctx->hashTable, tableType, base);

        /* Test next position */
        match = LZ4_getPosition(ip, cctx->hashTable, tableType, base);
        if (dict==usingExtDict) {
            if (match < (const uint8_t*)source) {
                refDelta = dictDelta;
                lowLimit = dictionary;
            } else {
                refDelta = 0;
                lowLimit = (const uint8_t*)source;
        }   }
        LZ4_putPosition(ip, cctx->hashTable, tableType, base);
        if ( ((dictIssue==dictSmall) ? (match>=lowRefLimit) : 1)
            && (match+MAX_DISTANCE>=ip)
            && (LZ4_read32(match+refDelta)==LZ4_read32(ip)) )
        { token=op++; *token=0; goto _next_match; }

        /* Prepare next loop */
        forwardH = LZ4_hashPosition(++ip, tableType);
    }

_last_literals:
    /* Encode Last Literals */
    {   uint64_t const lastRun = (uint64_t)(iend - anchor);
        if ( (outputLimited) &&  /* Check output buffer overflow */
            ((op - (uint8_t*)dest) + lastRun + 1 + ((lastRun+255-RUN_MASK)/255) > (uint32_t)maxOutputSize) )
            return 0;
        if (lastRun >= RUN_MASK) {
            uint64_t accumulator = lastRun - RUN_MASK;
            *op++ = RUN_MASK << ML_BITS;
            for(; accumulator >= 255 ; accumulator-=255) *op++ = 255;
            *op++ = (uint8_t) accumulator;
        } else {
            *op++ = (uint8_t)(lastRun<<ML_BITS);
        }
        memcpy(op, anchor, lastRun);
        op += lastRun;
    }

    /* End */
    return (int32_t) (((char*)op)-dest);
}


int32_t LZ4_compress_fast_extState(void* state, const char* source, char* dest, int32_t inputSize, int32_t maxOutputSize, int32_t acceleration)
{
    LZ4_stream_t_internal* ctx = &((LZ4_stream_t*)state)->internal_donotuse;
    LZ4_resetStream((LZ4_stream_t*)state);
    if (acceleration < 1) acceleration = ACCELERATION_DEFAULT;

    if (maxOutputSize >= LZ4_compressBound(inputSize)) {
        if (inputSize < LZ4_64Klimit)
            return LZ4_compress_generic(ctx, source, dest, inputSize,             0,    notLimited,                        byU16, noDict, noDictIssue, acceleration);
        else
            return LZ4_compress_generic(ctx, source, dest, inputSize,             0,    notLimited, (sizeof(void*)==8) ? byU32 : byPtr, noDict, noDictIssue, acceleration);
    } else {
        if (inputSize < LZ4_64Klimit)
            return LZ4_compress_generic(ctx, source, dest, inputSize, maxOutputSize, limitedOutput,                        byU16, noDict, noDictIssue, acceleration);
        else
            return LZ4_compress_generic(ctx, source, dest, inputSize, maxOutputSize, limitedOutput, (sizeof(void*)==8) ? byU32 : byPtr, noDict, noDictIssue, acceleration);
    }
}


int32_t LZ4_compress_fast(const char* source, char* dest, int32_t inputSize, int32_t maxOutputSize, int32_t acceleration)
{
#if (LZ4_HEAPMODE)
    void* ctxPtr = ALLOCATOR(1, sizeof(LZ4_stream_t));   /* malloc-calloc always properly aligned */
#else
    LZ4_stream_t ctx;
    void* const ctxPtr = &ctx;
#endif

    int32_t const result = LZ4_compress_fast_extState(ctxPtr, source, dest, inputSize, maxOutputSize, acceleration);

#if (LZ4_HEAPMODE)
    FREEMEM(ctxPtr);
#endif
    return result;
}


int32_t LZ4_compress_default(const char* source, char* dest, int32_t inputSize, int32_t maxOutputSize)
{
    return LZ4_compress_fast(source, dest, inputSize, maxOutputSize, 1);
}


/* hidden debug function */
/* strangely enough, gcc generates faster code when this function is uncommented, even if unused */
int32_t LZ4_compress_fast_force(const char* source, char* dest, int32_t inputSize, int32_t maxOutputSize, int32_t acceleration)
{
    LZ4_stream_t ctx;
    LZ4_resetStream(&ctx);

    if (inputSize < LZ4_64Klimit)
        return LZ4_compress_generic(&ctx.internal_donotuse, source, dest, inputSize, maxOutputSize, limitedOutput, byU16,                        noDict, noDictIssue, acceleration);
    else
        return LZ4_compress_generic(&ctx.internal_donotuse, source, dest, inputSize, maxOutputSize, limitedOutput, sizeof(void*)==8 ? byU32 : byPtr, noDict, noDictIssue, acceleration);
}


/*-******************************
*  *_destSize() variant
********************************/

static int32_t LZ4_compress_destSize_generic(
                       LZ4_stream_t_internal* const ctx,
                 const char* const src,
                       char* const dst,
                       int32_t*  const srcSizePtr,
                 const int32_t targetDstSize,
                 const tableType_t tableType)
{
    const uint8_t* ip = (const uint8_t*) src;
    const uint8_t* base = (const uint8_t*) src;
    const uint8_t* lowLimit = (const uint8_t*) src;
    const uint8_t* anchor = ip;
    const uint8_t* const iend = ip + *srcSizePtr;
    const uint8_t* const mflimit = iend - MFLIMIT;
    const uint8_t* const matchlimit = iend - LASTLITERALS;

    uint8_t* op = (uint8_t*) dst;
    uint8_t* const oend = op + targetDstSize;
    uint8_t* const oMaxLit = op + targetDstSize - 2 /* offset */ - 8 /* because 8+MINMATCH==MFLIMIT */ - 1 /* token */;
    uint8_t* const oMaxMatch = op + targetDstSize - (LASTLITERALS + 1 /* token */);
    uint8_t* const oMaxSeq = oMaxLit - 1 /* token */;

    uint32_t forwardH;


    /* Init conditions */
    if (targetDstSize < 1) return 0;                                     /* Impossible to store anything */
    if ((uint32_t)*srcSizePtr > (uint32_t)LZ4_MAX_INPUT_SIZE) return 0;            /* Unsupported input size, too large (or negative) */
    if ((tableType == byU16) && (*srcSizePtr>=LZ4_64Klimit)) return 0;   /* Size too large (not within 64K limit) */
    if (*srcSizePtr<LZ4_minLength) goto _last_literals;                  /* Input too small, no compression (all literals) */

    /* First Byte */
    *srcSizePtr = 0;
    LZ4_putPosition(ip, ctx->hashTable, tableType, base);
    ip++; forwardH = LZ4_hashPosition(ip, tableType);

    /* Main Loop */
    for ( ; ; ) {
        const uint8_t* match;
        uint8_t* token;

        /* Find a match */
        {   const uint8_t* forwardIp = ip;
            uint32_t step = 1;
            uint32_t searchMatchNb = 1 << LZ4_skipTrigger;

            do {
                uint32_t h = forwardH;
                ip = forwardIp;
                forwardIp += step;
                step = (searchMatchNb++ >> LZ4_skipTrigger);

                if (unlikely(forwardIp > mflimit)) goto _last_literals;

                match = LZ4_getPositionOnHash(h, ctx->hashTable, tableType, base);
                forwardH = LZ4_hashPosition(forwardIp, tableType);
                LZ4_putPositionOnHash(ip, h, ctx->hashTable, tableType, base);

            } while ( ((tableType==byU16) ? 0 : (match + MAX_DISTANCE < ip))
                || (LZ4_read32(match) != LZ4_read32(ip)) );
        }

        /* Catch up */
        while ((ip>anchor) && (match > lowLimit) && (unlikely(ip[-1]==match[-1]))) { ip--; match--; }

        /* Encode Literal length */
        {   uint32_t litLength = (uint32_t)(ip - anchor);
            token = op++;
            if (op + ((litLength+240)/255) + litLength > oMaxLit) {
                /* Not enough space for a last match */
                op--;
                goto _last_literals;
            }
            if (litLength>=RUN_MASK) {
                uint32_t len = litLength - RUN_MASK;
                *token=(RUN_MASK<<ML_BITS);
                for(; len >= 255 ; len-=255) *op++ = 255;
                *op++ = (uint8_t)len;
            }
            else *token = (uint8_t)(litLength<<ML_BITS);

            /* Copy Literals */
            LZ4_wildCopy(op, anchor, op+litLength);
            op += litLength;
        }

_next_match:
        /* Encode Offset */
        LZ4_writeLE16(op, (uint16_t)(ip-match)); op+=2;

        /* Encode MatchLength */
        {   uint64_t matchLength = LZ4_count(ip+MINMATCH, match+MINMATCH, matchlimit);

            if (op + ((matchLength+240)/255) > oMaxMatch) {
                /* Match description too long : reduce it */
                matchLength = (15-1) + (oMaxMatch-op) * 255;
            }
            ip += MINMATCH + matchLength;

            if (matchLength>=ML_MASK) {
                *token += ML_MASK;
                matchLength -= ML_MASK;
                while (matchLength >= 255) { matchLength-=255; *op++ = 255; }
                *op++ = (uint8_t)matchLength;
            }
            else *token += (uint8_t)(matchLength);
        }

        anchor = ip;

        /* Test end of block */
        if (ip > mflimit) break;
        if (op > oMaxSeq) break;

        /* Fill table */
        LZ4_putPosition(ip-2, ctx->hashTable, tableType, base);

        /* Test next position */
        match = LZ4_getPosition(ip, ctx->hashTable, tableType, base);
        LZ4_putPosition(ip, ctx->hashTable, tableType, base);
        if ( (match+MAX_DISTANCE>=ip)
            && (LZ4_read32(match)==LZ4_read32(ip)) )
        { token=op++; *token=0; goto _next_match; }

        /* Prepare next loop */
        forwardH = LZ4_hashPosition(++ip, tableType);
    }

_last_literals:
    /* Encode Last Literals */
    {   uint64_t lastRunSize = (uint64_t)(iend - anchor);
        if (op + 1 /* token */ + ((lastRunSize+240)/255) /* litLength */ + lastRunSize /* literals */ > oend) {
            /* adapt lastRunSize to fill 'dst' */
            lastRunSize  = (oend-op) - 1;
            lastRunSize -= (lastRunSize+240)/255;
        }
        ip = anchor + lastRunSize;

        if (lastRunSize >= RUN_MASK) {
            uint64_t accumulator = lastRunSize - RUN_MASK;
            *op++ = RUN_MASK << ML_BITS;
            for(; accumulator >= 255 ; accumulator-=255) *op++ = 255;
            *op++ = (uint8_t) accumulator;
        } else {
            *op++ = (uint8_t)(lastRunSize<<ML_BITS);
        }
        memcpy(op, anchor, lastRunSize);
        op += lastRunSize;
    }

    /* End */
    *srcSizePtr = (int32_t) (((const char*)ip)-src);
    return (int32_t) (((char*)op)-dst);
}


static int32_t LZ4_compress_destSize_extState (LZ4_stream_t* state, const char* src, char* dst, int32_t* srcSizePtr, int32_t targetDstSize)
{
    LZ4_resetStream(state);

    if (targetDstSize >= LZ4_compressBound(*srcSizePtr)) {  /* compression success is guaranteed */
        return LZ4_compress_fast_extState(state, src, dst, *srcSizePtr, targetDstSize, 1);
    } else {
        if (*srcSizePtr < LZ4_64Klimit)
            return LZ4_compress_destSize_generic(&state->internal_donotuse, src, dst, srcSizePtr, targetDstSize, byU16);
        else
            return LZ4_compress_destSize_generic(&state->internal_donotuse, src, dst, srcSizePtr, targetDstSize, sizeof(void*)==8 ? byU32 : byPtr);
    }
}


int32_t LZ4_compress_destSize(const char* src, char* dst, int32_t* srcSizePtr, int32_t targetDstSize)
{
#if (LZ4_HEAPMODE)
    LZ4_stream_t* ctx = (LZ4_stream_t*)ALLOCATOR(1, sizeof(LZ4_stream_t));   /* malloc-calloc always properly aligned */
#else
    LZ4_stream_t ctxBody;
    LZ4_stream_t* ctx = &ctxBody;
#endif

    int32_t result = LZ4_compress_destSize_extState(ctx, src, dst, srcSizePtr, targetDstSize);

#if (LZ4_HEAPMODE)
    FREEMEM(ctx);
#endif
    return result;
}



/*-******************************
*  Streaming functions
********************************/

LZ4_stream_t* LZ4_createStream(void)
{
    LZ4_stream_t* lz4s = (LZ4_stream_t*)ALLOCATOR(8, LZ4_STREAMSIZE_U64);
    LZ4_STATIC_ASSERT(LZ4_STREAMSIZE >= sizeof(LZ4_stream_t_internal));    /* A compilation error here means LZ4_STREAMSIZE is not large enough */
    LZ4_resetStream(lz4s);
    return lz4s;
}

void LZ4_resetStream (LZ4_stream_t* LZ4_stream)
{
    MEM_INIT(LZ4_stream, 0, sizeof(LZ4_stream_t));
}

int32_t LZ4_freeStream (LZ4_stream_t* LZ4_stream)
{
    if (!LZ4_stream) return 0;   /* support free on NULL */
    FREEMEM(LZ4_stream);
    return (0);
}


#define HASH_UNIT sizeof(uint64_t)
int32_t LZ4_loadDict (LZ4_stream_t* LZ4_dict, const char* dictionary, int32_t dictSize)
{
    LZ4_stream_t_internal* dict = &LZ4_dict->internal_donotuse;
    const uint8_t* p = (const uint8_t*)dictionary;
    const uint8_t* const dictEnd = p + dictSize;
    const uint8_t* base;

    if ((dict->initCheck) || (dict->currentOffset > 1 GB))  /* Uninitialized structure, or reuse overflow */
        LZ4_resetStream(LZ4_dict);

    if (dictSize < (int32_t)HASH_UNIT) {
        dict->dictionary = NULL;
        dict->dictSize = 0;
        return 0;
    }

    if ((dictEnd - p) > 64 * 1024) p = dictEnd - 64 * 1024;
    dict->currentOffset += 64 * 1024;
    base = p - dict->currentOffset;
    dict->dictionary = p;
    dict->dictSize = (uint32_t)(dictEnd - p);
    dict->currentOffset += dict->dictSize;

    while (p <= dictEnd-HASH_UNIT) {
        LZ4_putPosition(p, dict->hashTable, byU32, base);
        p+=3;
    }

    return dict->dictSize;
}


static void LZ4_renormDictT(LZ4_stream_t_internal* LZ4_dict, const uint8_t* src)
{
    if ((LZ4_dict->currentOffset > 0x80000000) ||
        ((uint64_t)LZ4_dict->currentOffset > (uint64_t)src)) {   /* address space overflow */
        /* rescale hash table */
        uint32_t const delta = LZ4_dict->currentOffset - 64 * 1024;
        const uint8_t* dictEnd = LZ4_dict->dictionary + LZ4_dict->dictSize;
        int32_t i;
        for (i=0; i<LZ4_HASH_SIZE_U32; i++) {
            if (LZ4_dict->hashTable[i] < delta) LZ4_dict->hashTable[i]=0;
            else LZ4_dict->hashTable[i] -= delta;
        }
        LZ4_dict->currentOffset = 64 * 1024;
        if (LZ4_dict->dictSize > 64 * 1024) LZ4_dict->dictSize = 64 * 1024;
        LZ4_dict->dictionary = dictEnd - LZ4_dict->dictSize;
    }
}


int32_t LZ4_compress_fast_continue (LZ4_stream_t* LZ4_stream, const char* source, char* dest, int32_t inputSize, int32_t maxOutputSize, int32_t acceleration)
{
    LZ4_stream_t_internal* streamPtr = &LZ4_stream->internal_donotuse;
    const uint8_t* const dictEnd = streamPtr->dictionary + streamPtr->dictSize;

    const uint8_t* smallest = (const uint8_t*) source;
    if (streamPtr->initCheck) return 0;   /* Uninitialized structure detected */
    if ((streamPtr->dictSize>0) && (smallest>dictEnd)) smallest = dictEnd;
    LZ4_renormDictT(streamPtr, smallest);
    if (acceleration < 1) acceleration = ACCELERATION_DEFAULT;

    /* Check overlapping input/dictionary space */
    {   const uint8_t* sourceEnd = (const uint8_t*) source + inputSize;
        if ((sourceEnd > streamPtr->dictionary) && (sourceEnd < dictEnd)) {
            streamPtr->dictSize = (uint32_t)(dictEnd - sourceEnd);
            if (streamPtr->dictSize > 64 * 1024) streamPtr->dictSize = 64 * 1024;
            if (streamPtr->dictSize < 4) streamPtr->dictSize = 0;
            streamPtr->dictionary = dictEnd - streamPtr->dictSize;
        }
    }

    /* prefix mode : source data follows dictionary */
    if (dictEnd == (const uint8_t*)source) {
        int32_t result;
        if ((streamPtr->dictSize < 64 * 1024) && (streamPtr->dictSize < streamPtr->currentOffset))
            result = LZ4_compress_generic(streamPtr, source, dest, inputSize, maxOutputSize, limitedOutput, byU32, withPrefix64k, dictSmall, acceleration);
        else
            result = LZ4_compress_generic(streamPtr, source, dest, inputSize, maxOutputSize, limitedOutput, byU32, withPrefix64k, noDictIssue, acceleration);
        streamPtr->dictSize += (uint32_t)inputSize;
        streamPtr->currentOffset += (uint32_t)inputSize;
        return result;
    }

    /* external dictionary mode */
    {   int32_t result;
        if ((streamPtr->dictSize < 64 * 1024) && (streamPtr->dictSize < streamPtr->currentOffset))
            result = LZ4_compress_generic(streamPtr, source, dest, inputSize, maxOutputSize, limitedOutput, byU32, usingExtDict, dictSmall, acceleration);
        else
            result = LZ4_compress_generic(streamPtr, source, dest, inputSize, maxOutputSize, limitedOutput, byU32, usingExtDict, noDictIssue, acceleration);
        streamPtr->dictionary = (const uint8_t*)source;
        streamPtr->dictSize = (uint32_t)inputSize;
        streamPtr->currentOffset += (uint32_t)inputSize;
        return result;
    }
}


/* Hidden debug function, to force external dictionary mode */
int32_t LZ4_compress_forceExtDict (LZ4_stream_t* LZ4_dict, const char* source, char* dest, int32_t inputSize)
{
    LZ4_stream_t_internal* streamPtr = &LZ4_dict->internal_donotuse;
    int32_t result;
    const uint8_t* const dictEnd = streamPtr->dictionary + streamPtr->dictSize;

    const uint8_t* smallest = dictEnd;
    if (smallest > (const uint8_t*) source) smallest = (const uint8_t*) source;
    LZ4_renormDictT(streamPtr, smallest);

    result = LZ4_compress_generic(streamPtr, source, dest, inputSize, 0, notLimited, byU32, usingExtDict, noDictIssue, 1);

    streamPtr->dictionary = (const uint8_t*)source;
    streamPtr->dictSize = (uint32_t)inputSize;
    streamPtr->currentOffset += (uint32_t)inputSize;

    return result;
}


/*! LZ4_saveDict() :
 *  If previously compressed data block is not guaranteed to remain available at its memory location,
 *  save it into a safer place (char* safeBuffer).
 *  Note : you don't need to call LZ4_loadDict() afterwards,
 *         dictionary is immediately usable, you can therefore call LZ4_compress_fast_continue().
 *  Return : saved dictionary size in bytes (necessarily <= dictSize), or 0 if error.
 */
int32_t LZ4_saveDict (LZ4_stream_t* LZ4_dict, char* safeBuffer, int32_t dictSize)
{
    LZ4_stream_t_internal* const dict = &LZ4_dict->internal_donotuse;
    const uint8_t* const previousDictEnd = dict->dictionary + dict->dictSize;

    if ((uint32_t)dictSize > 64 * 1024) dictSize = 64 * 1024;   /* useless to define a dictionary > 64 * 1024 */
    if ((uint32_t)dictSize > dict->dictSize) dictSize = dict->dictSize;

    memmove(safeBuffer, previousDictEnd - dictSize, dictSize);

    dict->dictionary = (const uint8_t*)safeBuffer;
    dict->dictSize = (uint32_t)dictSize;

    return dictSize;
}



/*-*****************************
*  Decompression functions
*******************************/
/*! LZ4_decompress_generic() :
 *  This generic decompression function cover all use cases.
 *  It shall be instantiated several times, using different sets of directives
 *  Note that it is important this generic function is really inlined,
 *  in order to remove useless branches during compilation optimization.
 */
FORCE_INLINE int32_t LZ4_decompress_generic(
                 const char* const source,
                 char* const dest,
                 int32_t inputSize,
                 int32_t outputSize,         /* If endOnInput==endOnInputSize, this value is the max size of Output Buffer. */

                 int32_t endOnInput,         /* endOnOutputSize, endOnInputSize */
                 int32_t partialDecoding,    /* full, partial */
                 int32_t targetOutputSize,   /* only used if partialDecoding==partial */
                 int32_t dict,               /* noDict, withPrefix64k, usingExtDict */
                 const uint8_t* const lowPrefix,  /* == dest when no prefix */
                 const uint8_t* const dictStart,  /* only if dict==usingExtDict */
                 const uint64_t dictSize         /* note : = 0 if noDict */
                 )
{
    /* Local Variables */
    const uint8_t* ip = (const uint8_t*) source;
    const uint8_t* const iend = ip + inputSize;

    uint8_t* op = (uint8_t*) dest;
    uint8_t* const oend = op + outputSize;
    uint8_t* cpy;
    uint8_t* oexit = op + targetOutputSize;
    const uint8_t* const lowLimit = lowPrefix - dictSize;

    const uint8_t* const dictEnd = (const uint8_t*)dictStart + dictSize;
    const uint32_t dec32table[] = {0, 1, 2, 1, 4, 4, 4, 4};
    const int32_t dec64table[] = {0, 0, 0, -1, 0, 1, 2, 3};

    const int32_t safeDecode = (endOnInput==endOnInputSize);
    const int32_t checkOffset = ((safeDecode) && (dictSize < (int32_t)(64 * 1024)));


    /* Special cases */
    if ((partialDecoding) && (oexit > oend-MFLIMIT)) oexit = oend-MFLIMIT;                        /* targetOutputSize too high => decode everything */
    if ((endOnInput) && (unlikely(outputSize==0))) return ((inputSize==1) && (*ip==0)) ? 0 : -1;  /* Empty output buffer */
    if ((!endOnInput) && (unlikely(outputSize==0))) return (*ip==0?1:-1);

    /* Main Loop : decode sequences */
    while (1) {
        uint64_t length;
        const uint8_t* match;
        uint64_t offset;

        /* get literal length */
        uint32_t const token = *ip++;
        if ((length=(token>>ML_BITS)) == RUN_MASK) {
            uint32_t s;
            do {
                s = *ip++;
                length += s;
            } while ( likely(endOnInput ? ip<iend-RUN_MASK : 1) & (s==255) );
            if ((safeDecode) && unlikely((uint64_t)(op)+length<(uint64_t)(op))) goto _output_error;   /* overflow detection */
            if ((safeDecode) && unlikely((uint64_t)(ip)+length<(uint64_t)(ip))) goto _output_error;   /* overflow detection */
        }

        /* copy literals */
        cpy = op+length;
        if ( ((endOnInput) && ((cpy>(partialDecoding?oexit:oend-MFLIMIT)) || (ip+length>iend-(2+1+LASTLITERALS))) )
            || ((!endOnInput) && (cpy>oend-WILDCOPYLENGTH)) )
        {
            if (partialDecoding) {
                if (cpy > oend) goto _output_error;                           /* Error : write attempt beyond end of output buffer */
                if ((endOnInput) && (ip+length > iend)) goto _output_error;   /* Error : read attempt beyond end of input buffer */
            } else {
                if ((!endOnInput) && (cpy != oend)) goto _output_error;       /* Error : block decoding must stop exactly there */
                if ((endOnInput) && ((ip+length != iend) || (cpy > oend))) goto _output_error;   /* Error : input must be consumed */
            }
            memcpy(op, ip, length);
            ip += length;
            op += length;
            break;     /* Necessarily EOF, due to parsing restrictions */
        }
        LZ4_wildCopy(op, ip, cpy);
        ip += length; op = cpy;

        /* get offset */
        offset = LZ4_readLE16(ip); ip+=2;
        match = op - offset;
        if ((checkOffset) && (unlikely(match < lowLimit))) goto _output_error;   /* Error : offset outside buffers */
        LZ4_write32(op, (uint32_t)offset);   /* costs ~1%; silence an msan warning when offset==0 */

        /* get matchlength */
        length = token & ML_MASK;
        if (length == ML_MASK) {
            uint32_t s;
            do {
                s = *ip++;
                if ((endOnInput) && (ip > iend-LASTLITERALS)) goto _output_error;
                length += s;
            } while (s==255);
            if ((safeDecode) && unlikely((uint64_t)(op)+length<(uint64_t)op)) goto _output_error;   /* overflow detection */
        }
        length += MINMATCH;

        /* check external dictionary */
        if ((dict==usingExtDict) && (match < lowPrefix)) {
            if (unlikely(op+length > oend-LASTLITERALS)) goto _output_error;   /* doesn't respect parsing restriction */

            if (length <= (uint64_t)(lowPrefix-match)) {
                /* match can be copied as a single segment from external dictionary */
                memmove(op, dictEnd - (lowPrefix-match), length);
                op += length;
            } else {
                /* match encompass external dictionary and current block */
                uint64_t const copySize = (uint64_t)(lowPrefix-match);
                uint64_t const restSize = length - copySize;
                memcpy(op, dictEnd - copySize, copySize);
                op += copySize;
                if (restSize > (uint64_t)(op-lowPrefix)) {  /* overlap copy */
                    uint8_t* const endOfMatch = op + restSize;
                    const uint8_t* copyFrom = lowPrefix;
                    while (op < endOfMatch) *op++ = *copyFrom++;
                } else {
                    memcpy(op, lowPrefix, restSize);
                    op += restSize;
            }   }
            continue;
        }

        /* copy match within block */
        cpy = op + length;
        if (unlikely(offset<8)) {
            const int32_t dec64 = dec64table[offset];
            op[0] = match[0];
            op[1] = match[1];
            op[2] = match[2];
            op[3] = match[3];
            match += dec32table[offset];
            memcpy(op+4, match, 4);
            match -= dec64;
        } else { LZ4_copy8(op, match); match+=8; }
        op += 8;

        if (unlikely(cpy>oend-12)) {
            uint8_t* const oCopyLimit = oend-(WILDCOPYLENGTH-1);
            if (cpy > oend-LASTLITERALS) goto _output_error;    /* Error : last LASTLITERALS bytes must be literals (uncompressed) */
            if (op < oCopyLimit) {
                LZ4_wildCopy(op, match, oCopyLimit);
                match += oCopyLimit - op;
                op = oCopyLimit;
            }
            while (op<cpy) *op++ = *match++;
        } else {
            LZ4_copy8(op, match);
            if (length>16) LZ4_wildCopy(op+8, match+8, cpy);
        }
        op=cpy;   /* correction */
    }

    /* end of decoding */
    if (endOnInput)
       return (int32_t) (((char*)op)-dest);     /* Nb of output bytes decoded */
    else
       return (int32_t) (((const char*)ip)-source);   /* Nb of input bytes read */

    /* Overflow error detected */
_output_error:
    return (int32_t) (-(((const char*)ip)-source))-1;
}


int32_t LZ4_decompress_safe(const char* source, char* dest, int32_t compressedSize, int32_t maxDecompressedSize)
{
    return LZ4_decompress_generic(source, dest, compressedSize, maxDecompressedSize, endOnInputSize, full, 0, noDict, (uint8_t*)dest, NULL, 0);
}

int32_t LZ4_decompress_safe_partial(const char* source, char* dest, int32_t compressedSize, int32_t targetOutputSize, int32_t maxDecompressedSize)
{
    return LZ4_decompress_generic(source, dest, compressedSize, maxDecompressedSize, endOnInputSize, partial, targetOutputSize, noDict, (uint8_t*)dest, NULL, 0);
}

int32_t LZ4_decompress_fast(const char* source, char* dest, int32_t originalSize)
{
    return LZ4_decompress_generic(source, dest, 0, originalSize, endOnOutputSize, full, 0, withPrefix64k, (uint8_t*)(dest - 64 * 1024), NULL, 64 * 1024);
}


/*===== streaming decompression functions =====*/

LZ4_streamDecode_t* LZ4_createStreamDecode(void)
{
    LZ4_streamDecode_t* lz4s = (LZ4_streamDecode_t*) ALLOCATOR(1, sizeof(LZ4_streamDecode_t));
    return lz4s;
}

int32_t LZ4_freeStreamDecode (LZ4_streamDecode_t* LZ4_stream)
{
    if (!LZ4_stream) return 0;   /* support free on NULL */
    FREEMEM(LZ4_stream);
    return 0;
}

/*!
 * LZ4_setStreamDecode() :
 * Use this function to instruct where to find the dictionary.
 * This function is not necessary if previous data is still available where it was decoded.
 * Loading a size of 0 is allowed (same effect as no dictionary).
 * Return : 1 if OK, 0 if error
 */
int32_t LZ4_setStreamDecode (LZ4_streamDecode_t* LZ4_streamDecode, const char* dictionary, int32_t dictSize)
{
    LZ4_streamDecode_t_internal* lz4sd = &LZ4_streamDecode->internal_donotuse;
    lz4sd->prefixSize = (uint64_t) dictSize;
    lz4sd->prefixEnd = (const uint8_t*) dictionary + dictSize;
    lz4sd->externalDict = NULL;
    lz4sd->extDictSize  = 0;
    return 1;
}

/*
*_continue() :
    These decoding functions allow decompression of multiple blocks in "streaming" mode.
    Previously decoded blocks must still be available at the memory position where they were decoded.
    If it's not possible, save the relevant part of decoded data into a safe buffer,
    and indicate where it stands using LZ4_setStreamDecode()
*/
int32_t LZ4_decompress_safe_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* source, char* dest, int32_t compressedSize, int32_t maxOutputSize)
{
    LZ4_streamDecode_t_internal* lz4sd = &LZ4_streamDecode->internal_donotuse;
    int32_t result;

    if (lz4sd->prefixEnd == (uint8_t*)dest) {
        result = LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize,
                                        endOnInputSize, full, 0,
                                        usingExtDict, lz4sd->prefixEnd - lz4sd->prefixSize, lz4sd->externalDict, lz4sd->extDictSize);
        if (result <= 0) return result;
        lz4sd->prefixSize += result;
        lz4sd->prefixEnd  += result;
    } else {
        lz4sd->extDictSize = lz4sd->prefixSize;
        lz4sd->externalDict = lz4sd->prefixEnd - lz4sd->extDictSize;
        result = LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize,
                                        endOnInputSize, full, 0,
                                        usingExtDict, (uint8_t*)dest, lz4sd->externalDict, lz4sd->extDictSize);
        if (result <= 0) return result;
        lz4sd->prefixSize = result;
        lz4sd->prefixEnd  = (uint8_t*)dest + result;
    }

    return result;
}

int32_t LZ4_decompress_fast_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* source, char* dest, int32_t originalSize)
{
    LZ4_streamDecode_t_internal* lz4sd = &LZ4_streamDecode->internal_donotuse;
    int32_t result;

    if (lz4sd->prefixEnd == (uint8_t*)dest) {
        result = LZ4_decompress_generic(source, dest, 0, originalSize,
                                        endOnOutputSize, full, 0,
                                        usingExtDict, lz4sd->prefixEnd - lz4sd->prefixSize, lz4sd->externalDict, lz4sd->extDictSize);
        if (result <= 0) return result;
        lz4sd->prefixSize += originalSize;
        lz4sd->prefixEnd  += originalSize;
    } else {
        lz4sd->extDictSize = lz4sd->prefixSize;
        lz4sd->externalDict = lz4sd->prefixEnd - lz4sd->extDictSize;
        result = LZ4_decompress_generic(source, dest, 0, originalSize,
                                        endOnOutputSize, full, 0,
                                        usingExtDict, (uint8_t*)dest, lz4sd->externalDict, lz4sd->extDictSize);
        if (result <= 0) return result;
        lz4sd->prefixSize = originalSize;
        lz4sd->prefixEnd  = (uint8_t*)dest + originalSize;
    }

    return result;
}


/*
Advanced decoding functions :
*_usingDict() :
    These decoding functions work the same as "_continue" ones,
    the dictionary must be explicitly provided within parameters
*/

FORCE_INLINE int32_t LZ4_decompress_usingDict_generic(const char* source, char* dest, int32_t compressedSize, int32_t maxOutputSize, int32_t safe, const char* dictStart, int32_t dictSize)
{
    if (dictSize==0)
        return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, safe, full, 0, noDict, (uint8_t*)dest, NULL, 0);
    if (dictStart+dictSize == dest) {
        if (dictSize >= (int32_t)(64 * 1024 - 1))
            return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, safe, full, 0, withPrefix64k, (uint8_t*)dest-64 * 1024, NULL, 0);
        return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, safe, full, 0, noDict, (uint8_t*)dest-dictSize, NULL, 0);
    }
    return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, safe, full, 0, usingExtDict, (uint8_t*)dest, (const uint8_t*)dictStart, dictSize);
}

int32_t LZ4_decompress_safe_usingDict(const char* source, char* dest, int32_t compressedSize, int32_t maxOutputSize, const char* dictStart, int32_t dictSize)
{
    return LZ4_decompress_usingDict_generic(source, dest, compressedSize, maxOutputSize, 1, dictStart, dictSize);
}

int32_t LZ4_decompress_fast_usingDict(const char* source, char* dest, int32_t originalSize, const char* dictStart, int32_t dictSize)
{
    return LZ4_decompress_usingDict_generic(source, dest, 0, originalSize, 0, dictStart, dictSize);
}

/* debug function */
int32_t LZ4_decompress_safe_forceExtDict(const char* source, char* dest, int32_t compressedSize, int32_t maxOutputSize, const char* dictStart, int32_t dictSize)
{
    return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, endOnInputSize, full, 0, usingExtDict, (uint8_t*)dest, (const uint8_t*)dictStart, dictSize);
}


/*=*************************************************
*  Obsolete Functions
***************************************************/
/* obsolete compression functions */
int32_t LZ4_compress_limitedOutput(const char* source, char* dest, int32_t inputSize, int32_t maxOutputSize) { return LZ4_compress_default(source, dest, inputSize, maxOutputSize); }
int32_t LZ4_compress(const char* source, char* dest, int32_t inputSize) { return LZ4_compress_default(source, dest, inputSize, LZ4_compressBound(inputSize)); }
int32_t LZ4_compress_limitedOutput_withState (void* state, const char* src, char* dst, int32_t srcSize, int32_t dstSize) { return LZ4_compress_fast_extState(state, src, dst, srcSize, dstSize, 1); }
int32_t LZ4_compress_withState (void* state, const char* src, char* dst, int32_t srcSize) { return LZ4_compress_fast_extState(state, src, dst, srcSize, LZ4_compressBound(srcSize), 1); }
int32_t LZ4_compress_limitedOutput_continue (LZ4_stream_t* LZ4_stream, const char* src, char* dst, int32_t srcSize, int32_t maxDstSize) { return LZ4_compress_fast_continue(LZ4_stream, src, dst, srcSize, maxDstSize, 1); }
int32_t LZ4_compress_continue (LZ4_stream_t* LZ4_stream, const char* source, char* dest, int32_t inputSize) { return LZ4_compress_fast_continue(LZ4_stream, source, dest, inputSize, LZ4_compressBound(inputSize), 1); }

/*
These function names are deprecated and should no longer be used.
They are only provided here for compatibility with older user programs.
- LZ4_uncompress is totally equivalent to LZ4_decompress_fast
- LZ4_uncompress_unknownOutputSize is totally equivalent to LZ4_decompress_safe
*/
int32_t LZ4_uncompress (const char* source, char* dest, int32_t outputSize) { return LZ4_decompress_fast(source, dest, outputSize); }
int32_t LZ4_uncompress_unknownOutputSize (const char* source, char* dest, int32_t isize, int32_t maxOutputSize) { return LZ4_decompress_safe(source, dest, isize, maxOutputSize); }


/* Obsolete Streaming functions */

int32_t LZ4_sizeofStreamState() { return LZ4_STREAMSIZE; }

static void LZ4_init(LZ4_stream_t* lz4ds, uint8_t* base)
{
    MEM_INIT(lz4ds, 0, sizeof(LZ4_stream_t));
    lz4ds->internal_donotuse.bufferStart = base;
}

int32_t LZ4_resetStreamState(void* state, char* inputBuffer)
{
    if ((((uint64_t)state) & 3) != 0) return 1;   /* Error : pointer is not aligned on 4-bytes boundary */
    LZ4_init((LZ4_stream_t*)state, (uint8_t*)inputBuffer);
    return 0;
}

void* LZ4_create (char* inputBuffer)
{
    LZ4_stream_t* lz4ds = (LZ4_stream_t*)ALLOCATOR(8, sizeof(LZ4_stream_t));
    LZ4_init (lz4ds, (uint8_t*)inputBuffer);
    return lz4ds;
}

char* LZ4_slideInputBuffer (void* LZ4_Data)
{
    LZ4_stream_t_internal* ctx = &((LZ4_stream_t*)LZ4_Data)->internal_donotuse;
    int32_t dictSize = LZ4_saveDict((LZ4_stream_t*)LZ4_Data, (char*)ctx->bufferStart, 64 * 1024);
    return (char*)(ctx->bufferStart + dictSize);
}

/* Obsolete streaming decompression functions */

int32_t LZ4_decompress_safe_withPrefix64k(const char* source, char* dest, int32_t compressedSize, int32_t maxOutputSize)
{
    return LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize, endOnInputSize, full, 0, withPrefix64k, (uint8_t*)dest - 64 * 1024, NULL, 64 * 1024);
}

int32_t LZ4_decompress_fast_withPrefix64k(const char* source, char* dest, int32_t originalSize)
{
    return LZ4_decompress_generic(source, dest, 0, originalSize, endOnOutputSize, full, 0, withPrefix64k, (uint8_t*)dest - 64 * 1024, NULL, 64 * 1024);
}

#endif   /* LZ4_COMMONDEFS_ONLY */
