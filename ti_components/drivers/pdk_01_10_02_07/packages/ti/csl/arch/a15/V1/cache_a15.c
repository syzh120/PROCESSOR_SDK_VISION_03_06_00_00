/*
 *  Copyright (c) Texas Instruments Incorporated 2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     cache_a15.c
 *
 *  \brief    This file contains the A15 Cache HAL APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <cp15.h>
#include <ti/csl/csl_types.h>
#include <cache_a15.h>
#include <cache_a15_gcc_asm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t CACHEA15GetEnabled(void)
{
    uint32_t retVal = 0U;

    retVal = CACHEA15GetEnabledASM();

    return retVal;
}

void CACHEA15Enable(uint32_t cacheType)
{
    uint32_t disabledCache;

    /* Only enable cache if it is disabled */
    disabledCache = ~(CACHEA15GetEnabled());

    /* Enable L1D and L2 Cache */
    if (0U != (disabledCache &
               (cacheType & ((uint32_t) CACHE_A15_TYPE_L1D |
                             (uint32_t) CACHE_A15_TYPE_L2))))
    {
        CP15DCacheEnable();
    }

    /* Enable L1I Cache */
    if (0U != (disabledCache & (cacheType & ((uint32_t) CACHE_A15_TYPE_L1I))))
    {
        CP15ICacheEnable();
    }
}

void CACHEA15Disable(uint32_t cacheType)
{
    uint32_t enabledCache;

    /* Only disable cache if it is enabled */
    enabledCache = CACHEA15GetEnabled();

    /* Disable L1D and L2 Cache */
    if (0U != (enabledCache &
               (cacheType & ((uint32_t) CACHE_A15_TYPE_L1D |
                             (uint32_t) CACHE_A15_TYPE_L2))))
    {
        CP15DCacheDisable();
    }

    /* Disable L1I Cache */
    if (0U != (enabledCache & (cacheType & ((uint32_t) CACHE_A15_TYPE_L1I))))
    {
        CP15ICacheDisable();
    }
}

void CACHEA15Invalidate(uint32_t cacheType,
                        uint32_t startAddress,
                        uint32_t byteCount)
{
    /* Invalidate I Cache */
    if (0U != (cacheType &
               ((uint32_t) CACHE_A15_TYPE_L1I | (uint32_t) CACHE_A15_TYPE_L2I)))
    {
        CP15InvalidateICache(startAddress, byteCount);
    }

    /*Invalidate D Cache */
    if (0U != (cacheType &
               ((uint32_t) CACHE_A15_TYPE_L1D | (uint32_t) CACHE_A15_TYPE_L2D)))
    {
        CP15InvalidateDCache(startAddress, byteCount);
    }
}

void CACHEA15DisableStreamCacheLine(void)
{
    CACHEA15DisableStreamCacheLineASM();
}

void CACHEA15WriteBack(uint32_t startAddress,
                       uint32_t byteCount)
{
    /* R0: startAddress, R1: byteCount */
    asm ("    add     r1, r0, r1\n\t"  /* Calculate last address */
         "    bic     r0, r0, #63\n\t" /* Align startAddress to cache line */
                                       /* Write back single entry */
         "    loop6: mcr     p15, #0, r0, c7, c10, #1\n\t"
         "    add     r0, r0, #64\n\t" /* Increment address by cache line size
                                       **/
         "    cmp     r0, r1\n\t"      /* Compare to last address */
         "    blo     loop6\n\t"       /* loop if > 0 */
         "    dsb\n\t"                 /* drain write buffer */
         );
}

void CACHEA15Preload(uint32_t startAddress,
                     uint32_t byteCount)
{
    /* R0: startAddress, R1: byteCount */
    asm ("    add     r1, r0, r1\n\t"  /* Calculate last address */
         "    bic     r0, r0, #63\n\t" /* Align startAddress to cache line */
                                       /* Writeback inv this cache line to
                                        *remove it from any other cache */
         "    loop7: mcr     p15, #0, r0, c7, c14, #1\n\t"
         "    ldr     r6, [r0]\n\t"    /* Load first word of cache line */
         "    add     r0, r0, #64\n\t" /* Increment address by cache line size
                                       **/
         "    cmp     r0, r1\n\t"      /* Compare to last address */
         "    blo     loop7\n\t"       /* loop if > 0 */
         "    dsb\n\t"                 /* drain write buffer */
         );
}

void CACHEA15WriteBackAndInvalidate(uint32_t startAddress,
                                    uint32_t byteCount)
{
    /* R0: startAddress, R1: byteCount */
    asm ("    add     r1, r0, r1\n\t"  /* Calculate last address */
         "    bic     r0, r0, #63\n\t" /* Align startAddress to cache line */
                                       /* Write back and Invalidate single
                                        *entry*/
         "    loop8: mcr     p15, #0, r0, c7, c14, #1\n\t"
         "    add     r0, r0, #64\n\t" /* Increment address by cache line size
                                       **/
         "    cmp     r0, r1\n\t"      /* Compare to last address */
         "    blo     loop8\n\t"       /* loop if > 0 */
         "    dsb\n\t"                 /* drain write buffer */
         );
}

void CACHEA15InvalidateL1IAll(void)
{
    asm ("    mcr     p15, #0, r0, c7, c5, #0\n\t"
         "    dsb\n\t"   /* drain write buffer */
         );
}

void CACHEA15InvalidateL1DAll(void)
{
    asm ("    push    {r4-r11} \n\t"
         "    dmb \n\t"
         "    mrc    p15, #1, r0, c0, c0, #1 \n\t"  /* Load CLID register */
         "    ands    r3, r0, #0x7000000  \n\t"     /* Get LoC */
         "    mov    r3, r3, lsr #23 \n\t"
         "    beq    finished1 \n\t"                /* if LoC is 0, then no need
                                                     *to clean */
         "    mov    r10, #0 \n\t"                  /* start cleaning at cache
                                                     *level 0 */
         "loop11: add    r2, r10, r10, lsr #1 \n\t" /* work out 3x current cache
                                                     *level */
         "    mov    r1, r0, lsr r2 \n\t"           /* get cache type */
         "    and    r1, r1, #7 \n\t"               /* mask of the bits for
                                                     *current cache only*/
         "    cmp    r1, #2  \n\t"                  /* cache at this level */
         "    blt    skip1 \n\t"                    /* skip if no cache, or just
                                                     *i-cache */
         "    mcr    p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                     * level
                                                     **/
         "    isb \n\t"                             /* isb to sych the new CSSR
                                                     * &
                                                     *CSIDR */
         "    mrc    p15, #1, r1, c0, c0, #0 \n\t"  /* read the new CSIDR */
         "    and    r2, r1, #7 \n\t"               /* extract the length of the
                                                     *cache lines */
         "    add    r2, r2, #4 \n\t"
         "    ldr    r4, =0x3ff \n\t"
         "    ands   r4, r4, r1, lsr #3 \n\t"         /* Max on the way size */
         "    clz    r5, r4 \n\t"                     /* find bit position of
                                                       * way
                                                       *size increment */
         "    ldr    r7, =0x7fff \n\t"
         "    ands    r7, r7, r1, lsr #13 \n\t"       /* Max number of the index
                                                       *size */
         "loop21: mov     r9, r4 \n\t"
         "loop31: orr     r11, r10, r9, lsl r5  \n\t" /* factor way and cache
                                                       *number */
         "    orr    r11, r11, r7, lsl r2 \n\t"       /* factor index number */
         "    mcr    p15, #0, r11, c7, c6, #2 \n\t"   /* invalidate by set/way
                                                      **/
         "    subs    r9, r9, #1 \n\t"                /* decrement the way */
         "    bge     loop31 \n\t"
         "    subs    r7, r7, #1 \n\t"                /* decrement the index */
         "    bge     loop21 \n\t"
         "skip1: add     r10, r10, #2 \n\t"           /*  increment cache number
                                                      **/
         "    cmp     r3, r10 \n\t"
         "    bgt     loop11 \n\t"
         "finished1: mov     r10, #0 \n\t"           /* switch back to cache
                                                      *level 0 */
         "    mcr     p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                      *  level in csselr */
         "    isb \n\t"
         "    pop    {r4-r11} \n\t");
}

void CACHEA15WriteBackAll(void)
{
    asm ("    push    {r4-r11} \n\t"
         "    dmb \n\t"
         "    mrc    p15, #1, r0, c0, c0, #1 \n\t"  /* Load CLID register */
         "    ands    r3, r0, #0x7000000  \n\t"     /* Get LoC */
         "    mov    r3, r3, lsr #23 \n\t"
         "    beq    finished2 \n\t"                /* if LoC is 0, then no need
                                                     *to clean */
         "    mov    r10, #0 \n\t"                  /* start cleaning at cache
                                                     *level 0 */
         "loop12: add    r2, r10, r10, lsr #1 \n\t" /* work out 3x current cache
                                                     *level */
         "    mov    r1, r0, lsr r2 \n\t"           /* get cache type */
         "    and    r1, r1, #7 \n\t"               /* mask of the bits for
                                                     *current cache only*/
         "    cmp    r1, #2  \n\t"                  /* cache at this level */
         "    blt    skip2 \n\t"                    /* skip if no cache, or just
                                                     *i-cache */
         "    mcr    p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                     * level
                                                     **/
         "    isb \n\t"                             /* isb to sych the new CSSR
                                                     * &
                                                     *CSIDR */
         "    mrc    p15, #1, r1, c0, c0, #0 \n\t"  /* read the new CSIDR */
         "    and    r2, r1, #7 \n\t"               /* extract the length of the
                                                     *cache lines */
         "    add    r2, r2, #4 \n\t"
         "    ldr    r4, =0x3ff \n\t"
         "    ands   r4, r4, r1, lsr #3 \n\t"         /* Max on the way size */
         "    clz    r5, r4 \n\t"                     /* find bit position of
                                                       * way
                                                       *size increment */
         "    ldr    r7, =0x7fff \n\t"
         "    ands    r7, r7, r1, lsr #13 \n\t"       /* Max number of the index
                                                       *size */
         "loop22: mov     r9, r4 \n\t"
         "loop32: orr     r11, r10, r9, lsl r5  \n\t" /* factor way and cache
                                                       *number */
         "    orr    r11, r11, r7, lsl r2 \n\t"       /* factor index number */
         "    mcr    p15, #0, r11, c7, c10, #2 \n\t"  /* clean by set/way */
         "    subs    r9, r9, #1 \n\t"                /* decrement the way */
         "    bge     loop32 \n\t"
         "    subs    r7, r7, #1 \n\t"                /* decrement the index */
         "    bge     loop22 \n\t"
         "skip2: add     r10, r10, #2 \n\t"           /*  increment cache number
                                                      **/
         "    cmp     r3, r10 \n\t"
         "    bgt     loop12 \n\t"
         "finished2: mov     r10, #0 \n\t"           /* switch back to cache
                                                      *level 0 */
         "    mcr     p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                      * level in csselr */
         "    isb \n\t"
         "    pop    {r4-r11} \n\t");
}

void CACHEA15WriteBackAndInvalidateAll(void)
{
    CP15DCacheCleanFlush();
}

void CACHEA15Wait(void)
{
    /* Drain write buffer */
    asm ("    mcr     p15, #0, r0, c7, c10, #4");
}

void CACHEA15EnableBP(void)
{
    /* Enable branch prediction */
    CP15BranchPredictionEnable();
}

void CACHEA15DisableBP(void)
{
    /* Disable branch prediction */
    CP15BranchPredictionDisable();

    /* Invalidate branch prediction */
    CP15BranchPredictorInvalidate();
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
