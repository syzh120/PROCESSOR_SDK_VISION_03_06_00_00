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
 *  \file   cp15.c
 *
 *  \brief  coprocessor related definitions
 *
 *  This file contains the API definitions for configuring coprocessor register
 */

#include <stdint.h>
#include <cp15.h>

static void __inline CleanDataCacheLineRegister(uint32_t ptr);
static void __inline InvalidateDataCacheLineRegister(uint32_t ptr);
static void __inline ReadDeviceIDCode(uint32_t *coreid);
static void __inline DataMemoryBarrier(void);

static void __inline CleanDataCacheLineRegister(uint32_t ptr)
{
    asm ("    mcr p15, #0, %[value], C7, C10, #1" ::[value] "r" (ptr));
}

static void __inline InvalidateDataCacheLineRegister(uint32_t ptr)
{
    asm ("    mcr p15, #0, %[value], C7, C6, #1" ::[value] "r" (ptr));
}

static void __inline ReadDeviceIDCode(uint32_t *coreid)
{
    asm ("    mrc p15, 0, r0, c0, c0, 5\n\t"
         "    mov %[result], r0" :[result] "=r" (*coreid));
}

/*****************************************************************************
**                   FUNCTION DEFINITIONS
******************************************************************************/
/**
 * \brief       It ensures that all explicit memory accesses that appear in
 *              program order before the DMB instruction are observed, before
 *              any explicit memory accesses that appear in program order
 *              after the DMB instruction.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
static void __inline DataMemoryBarrier(void)
{
    asm ("    dmb");
}

/*****************************************************************************
**                   FUNCTION DEFINITIONS
******************************************************************************/
/**
 * \brief      This API disable the Instruction cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15ICacheDisable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    bic     r0,  r0, #0x00001000\n\t"
         "    mcr     p15, #0, r0, c1, c0, #0\n\t"
         "    dsb");
}

/**
 * \brief      This API disable the Data cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15DCacheDisable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    bic     r0,  r0, #0x00000004\n\t"
         "    mcr     p15, #0, r0, c1, c0, #0");
}

/**
 * \brief      This API Enables the Instruction cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15ICacheEnable(void)
{
    asm ("    dsb\n\t"
         "    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    orr     r0,  r0, #0x00001000 \n\t"
         "    mcr     p15, #0, r0, c1, c0, #0 \n\t");
}

/**
 * \brief      This API Enables the Data cache.
 *
 * \param      None.
 *
 * \retiurn     None.
 *
 * Note: MMU shall be enabled before enabling D-Cache
 **/
void CP15DCacheEnable(void)
{
    asm ("    mrc     p15, #0, r0, c1, c0, #0\n\t"
         "    orr     r0,  r0, #0x00000004\n\t "
         "    mcr     p15, #0, r0, c1, c0, #0\n\t"
         "    dsb");
}

/**
 * \brief      This API Cleans Invalidates and evicts data cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15DCacheCleanFlush(void)
{
    asm ("    push    {r4-r11} \n\t"
         "    dmb \n\t"
         "    mrc    p15, #1, r0, c0, c0, #1 \n\t"  /* Load CLID register */
         "    ands    r3, r0, #0x7000000  \n\t"     /* Get LoC */
         "    mov    r3, r3, lsr #23 \n\t"
         "    beq    finished \n\t"                 /* if LoC is 0, then no need
                                                     *to clean */
         "    mov    r10, #0 \n\t"                  /* start cleaning at cache
                                                     *level 0 */
         "loop1: add    r2, r10, r10, lsr #1 \n\t"  /* work out 3x current cache
                                                     *level */
         "    mov    r1, r0, lsr r2 \n\t"           /* get cache type */
         "    and    r1, r1, #7 \n\t"               /* mask of the bits for
                                                     *current cache only*/
         "    cmp    r1, #2  \n\t"                  /* cache at this level */
         "    blt    skip \n\t"                     /* skip if no cache, or just
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
         "    ands   r4, r4, r1, lsr #3 \n\t"        /* Max on the way size */
         "    clz    r5, r4 \n\t"                    /* find bit position of way
                                                      *size increment */
         "    ldr    r7, =0x7fff \n\t"
         "    ands    r7, r7, r1, lsr #13 \n\t"      /* Max number of the index
                                                      *size */
         "loop2: mov     r9, r4 \n\t"
         "loop3: orr     r11, r10, r9, lsl r5  \n\t" /* factor way and cache
                                                      *number */
         "    orr    r11, r11, r7, lsl r2 \n\t"      /* factor index number */
         "    mcr    p15, #0, r11, c7, c14, #2 \n\t" /* clean & invalidate by
                                                      *set/way */
         "    subs    r9, r9, #1 \n\t"               /* decrement the way */
         "    bge     loop3 \n\t"
         "    subs    r7, r7, #1 \n\t"               /* decrement the index */
         "    bge     loop2 \n\t"
         "skip: add     r10, r10, #2 \n\t"           /*  increment cache number
                                                     **/
         "    cmp     r3, r10 \n\t"
         "    bgt     loop1 \n\t"
         "finished: mov     r10, #0 \n\t"            /* switch back to cache
                                                      *level 0 */
         "    mcr     p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                      * level in csselr */
         "    isb \n\t"
         "    pop    {r4-r11} \n\t");
}

/**
 * \brief      This API Invalidates Instruction cache.
 *
 * \param      None.
 *
 * \return     None.
 *
 **/
void CP15ICacheFlush(void)
{
    asm ("    mov     r0, #0\n\t"
         "    mcr     p15, #0, r0, c7, c5, #0\n\t");
}

/**
 * \brief      Cleans the D-cache lines corresponding to the buffer pointer
 *             upto the specified length.
 *
 * \param      bufPtr     Buffer start address
 * \param      size       Size of the buffer in bytes
 *
 * \return     None.
 *
 **/
void CP15DCacheCleanBuff(uint32_t bufPtr, uint32_t size)
{
    uint32_t ptr;

    ptr = bufPtr & (~(uint32_t) 0x3fU);

    DataMemoryBarrier();
    while (ptr < (bufPtr + size))
    {
        CleanDataCacheLineRegister(ptr);
        ptr += 64U;
    }
}

/**
 * \brief      Flushes cache lines corresponding to the buffer pointer
 *             upto the specified length.
 *
 * \param      bufPtr     Buffer start address
 * \param      size       Size of the buffer in bytes
 *
 * \return     None.
 *
 **/
void CP15ICacheFlushBuff(uint32_t bufPtr, uint32_t size)
{
    uint32_t ptr;

    ptr = bufPtr & (~(uint32_t) 0x3fU);

    while (ptr < (bufPtr + size))
    {
        InvalidateDataCacheLineRegister(ptr);
        ptr += 64U;
    }
}

/**
 * \brief     This API Configures translation table base register 0 with
 *            with page table starting address.
 *
 * \param     ttb  is the starting address of the pageTable.
 *
 * \return    None.
 *
 *  Note : Page Table starting address should be aligned to 16k.
 **/
void CP15Ttb0Set(uint32_t ttb)
{
    /* sets translation table base register with page table
     * starting address.
     */
    asm ("   mcr p15, #0, %[value], c2, c0, 0" ::[value] "r" (ttb));
}

/**
 * \brief     This API invalidates the TLB
 *
 * \param     None
 *
 * \return    None.
 *
 **/
void CP15TlbInvalidate(void)
{
    /* Invalidates all TLBs.Domain access is selected as
     * client by configuring domain access register,
     * in that case access controlled by permission value
     * set by page table entry
     */
    asm ("   mov r1, #0\n\t"
         "   mcr p15, #0, r1, c8, c7, #0\n\t"
         "   ldr r1, =0x55555555\n\t"
         "   mcr p15, #0, r1, c3, c0, #0\n\t");
}

/**
 * \brief     This API disables the MMU.
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15MMUDisable(void)
{
    asm ("    mov r0, #0\n\t"
         "    mcr p15, #0, r0, c8, c7, #0\n\t"
         "    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    mov r1, #0x1\n\t"
         "    bic r0, r0, r1\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     This API enables the MMU.
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15MMUEnable(void)
{
    asm ("    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    orr r0, r0, #0x00000001\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     Set the exception table base address
 *
 * \param     addr    The base address of the exception vector table
 *
 * \return    None.
 *
 **/
void CP15VectorBaseAddrSet(uint32_t addr)
{
    asm ("   mcr p15, #0, %[value], c12, c0, 0" ::[value] "r" (addr));
}

/**
 * \brief     This API Invalidates the branch predictor
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15BranchPredictorInvalidate(void)
{
    asm ("    mcr p15, #0, r0, c7, c5, #6");
}

/**
 * \brief     This API Enables the branch prediction logic
 *
 * \param     None.
 *
 *
 *
 **/
void CP15BranchPredictionEnable(void)
{
    asm ("    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    orr r0, r0, #0x00000800\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     This API disables the branch prediction logic
 *
 * \param     None.
 *
 * \return    None.
 *
 **/
void CP15BranchPredictionDisable(void)
{
    asm ("    mrc p15, #0, r0, c1, c0, #0\n\t"
         "    bic r0, r0, #0x00000800\n\t"
         "    mcr p15, #0, r0, c1, c0, #0\n\t");
}

/**
 * \brief     Sets the domain access to client
 *
 * \param     None
 *
 * \return    None.
 *
 **/
void CP15DomainAccessClientSet(void)
{
    asm ("    ldr r0, =0x55555555 \n\t"
         "    mcr p15, 0, r0, c3, c0, 0");
}

void CP15FPUEnable(void)
{
    asm ("movw r0, #0x0000 \n\t"
         "movt r0, #0x00F0 \n\t"
         "mcr p15, #0, r0, c1, c0, #2 \n\t"
         "isb \n\t"
         "movw r0, #0x0000  \n\t"
         "movt r0, #0x4000  \n\t"
         "fmxr fpexc, r0"
         );

/*set the FPEXC.EN bit to enable Advanced SIMD and VFP      */

/*gcc does not support UAL equivalent
 *                                                                      */
/*instruction, vmsr*/
}

/**
 * \brief     Invalidate the I Cache
 *
 * \param      bufPtr     Buffer start address
 * \param      size       Size of the buffer in bytes
 *
 * \return    None.
 *
 **/
void CP15InvalidateICache(uint32_t bufPtr, uint32_t size)
{
    /* R0: bufPtr, R1: size */
    asm ("    add     r1, r0, r1\n\t"  /* Calculate last address */
         "    bic     r0, r0, #63\n\t" /* Align bufPtr to cache line */
                                       /* Invalidate single entry */
         "    loop4: mcr     p15, #0, r0, c7, c5, #1\n\t"
         "    add     r0, r0, #64\n\t" /* Increment address by cache line size
                                       **/
         "    cmp     r0, r1\n\t"      /* Compare to last address */
         "    blo     loop4\n\t"       /* loop if > 0 */
         "    dsb\n\t"                 /* drain write buffer */
         );
}

/**
 * \brief     Invalidate the D Cache
 *
 * \param      bufPtr     Buffer start address
 * \param      size       Size of the buffer in bytes
 *
 * \return    None.
 *
 **/
void CP15InvalidateDCache(uint32_t bufPtr, uint32_t size)
{
    /* R0: bufPtr, R1: size */
    asm ("    add     r1, r0, r1\n\t"  /* Calculate last address */
         "    bic     r0, r0, #63\n\t" /* Align bufPtr to cache line */
                                       /* Invalidate single entry */
         "    loop5: mcr     p15, #0, r0, c7, c6, #1\n\t"
         "    add     r0, r0, #64\n\t" /* Increment address by cache line size
                                       **/
         "    cmp     r0, r1\n\t"      /* Compare to last address */
         "    blo     loop5\n\t"       /* loop if > 0 */
         "    dsb\n\t"                 /* drain write buffer */
         );
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
/**
 * \brief     Read Core ID register
 *
 * \param     None
 *
 * \return    Core ID
 *
 **/
uint32_t CP15ReadCoreId(void)
{
    uint32_t coreid;

    ReadDeviceIDCode(&coreid);
    return coreid;
}

#endif

/********************************* End Of File ********************************/
