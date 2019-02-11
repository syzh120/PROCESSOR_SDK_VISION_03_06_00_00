@
@  Copyright (c) 2015-2017, Texas Instruments Incorporated
@  All rights reserved.
@
@  Redistribution and use in source and binary forms, with or without
@  modification, are permitted provided that the following conditions
@  are met:
@
@  *  Redistributions of source code must retain the above copyright
@     notice, this list of conditions and the following disclaimer.
@
@  *  Redistributions in binary form must reproduce the above copyright
@     notice, this list of conditions and the following disclaimer in the
@     documentation and/or other materials provided with the distribution.
@
@  *  Neither the name of Texas Instruments Incorporated nor the names of
@     its contributors may be used to endorse or promote products derived
@     from this software without specific prior written permission.
@
@  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
@  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
@  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
@  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
@  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
@  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
@  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
@  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
@  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
@  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
@  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
@
@ ======== Cache_asm_gnu.asm ========
@

        .equ Cache_sizeL1dCacheLine, 64
        .equ Cache_sizeL1pCacheLine, 64
        .equ Cache_sizeL2CacheLine, 64

        .global CSL_a15DisableFiq
        .global CSL_a15EnableFiq
        .global CSL_a15DisableIrq
        .global CSL_a15EnableIrq
        .global CSL_a15SetVectorTable
        .global CSL_a15DisableMmu
        .global CSL_a15EnableMmu
        .global CSL_a15EnableMmuLongDescTranslationTable
        .global CSL_a15EnableMmuShortDescTranslationTable
        .global CSL_a15SetMmuLongDescTranslationTable
        .global CSL_a15SetMmuShortDescTranslationTable
        .global CSL_a15InvalidateAllMmuTranslationTable
        .global CSL_a15IsMmuEnabled
        .global CSL_a15SetMmuMair
        .global CSL_a15DisableDataCache
        .global CSL_a15DisableInstrCache
        .global CSL_a15EnableDataCache
        .global CSL_a15EnableInstrCache
        .global CSL_a15DisableBranchPrediction
        .global CSL_a15EnableBranchPrediction
        .global CSL_a15InvDataCache
        .global CSL_a15InvInstrCache
        .global CSL_a15InvAllDataCache
        .global CSL_a15InvAllInstrCache
        .global CSL_a15WbDataCache
        .global CSL_a15WbInvDataCache
        .global CSL_a15WbAllDataCache
        .global CSL_a15WbInvAllDataCache
        .global CSL_a15CachePreload
        .global CSL_a15CycleCntEnable
        .global CSL_a15CycleCntRead
        .global CSL_a15ECCEnable
        .global CSL_a15ECCDisable
        .global CSL_a15ECCGetErrStatus
        .global CSL_a15ReadCoreId
        .global CSL_a15FPUEnable
        .global CSL_a15GetCacheType
        .global CSL_a15SwitchToPrivMode
        .global CSL_a15SwitchToUserMode
        .global CSL_a15IntrStatus
        .global CSL_a15VectorBaseAddrSet
        .global CSL_armGicGlobalDisableInterrupt
        .global CSL_armGicGlobalRestoreInterrupt

        .arm
        .align  4

@
@ ======== CSL_a15DisableFiq ========
@ Disable FIR.
@
        .text
        .func CSL_a15DisableFiq

CSL_a15DisableFiq:
        mrs     r0, cpsr
        orr     r12, r0, #64
        msr     cpsr, r12
        bx      r14
        .endfunc

@
@ ======== CSL_a15EnableFiq ========
@ Enable FIQ.
@
        .text
        .func CSL_a15EnableFiq

CSL_a15EnableFiq:
        mrs     r0, cpsr
        bic     r12, r0, #64
        msr     cpsr, r12
        bx      r14
        .endfunc

@
@ ======== CSL_a15DisableIrq ========
@ Disable IRQ.
@
        .text
        .func CSL_a15DisableIrq

CSL_a15DisableIrq:
        mrs     r0, cpsr
        orr     r12, r0, #128
        msr     cpsr, r12
        bx      r14
        .endfunc

@
@ ======== CSL_a15EnableIrq ========
@ Enable IRQ.
@
        .text
        .func CSL_a15EnableIrq

CSL_a15EnableIrq:
        mrs     r0, cpsr
        bic     r12, r0, #128
        msr     cpsr, r12
        bx      r14
        .endfunc

@
@ ======== CSL_a15SetVectorTable ========
@ Low level ARM mode-specific register initialization for vector table
@
@       r0 - contains vector base address
@

        .text
        .func CSL_a15SetVectorTable

CSL_a15SetVectorTable:
        mcr     p15, #0, r0, c12, c0, #0

        bx      lr
        .endfunc


@
@ ======== CSL_a15DisableMmu ========
@ Disable MMU.
@
        .text
        .func CSL_a15DisableMmu

CSL_a15DisableMmu:
        mrc  p15, #0, r0, c1, c0, #0    @ read register c1
        mov  r1, #0x1                   @ move #1 into r1
        bic  r0, r0, r1                 @ clear bit 1 in r0
        mcr  p15, #0, r0, c1, c0, #0    @ mmu disabled (bit 1 = 0)

        bx   r14
        .endfunc

@
@ ======== CSL_a15EnableMmu ========
@ Enable MMU.
@
        .text
        .func CSL_a15EnableMmu

CSL_a15EnableMmu:
        mrc  p15, #0, r0, c1, c0, #0    @ read register c1
        mov  r1, #0x1                   @ move #1 into r1
        orr  r0, r0, r1                 @ OR r1 with r0 into r0
        mcr  p15, #0, r0, c1, c0, #0    @ mmu enabled (bit 1 = 1)

        bx   r14
        .endfunc

@
@ ======== CSL_a15IsMmuEnabled ========
@ Determines if MMU is enabled. Returns TRUE if enabled otherwise FALSE.
@
        .text
        .func CSL_a15IsMmuEnabled

CSL_a15IsMmuEnabled:
        mov    r0, #0
        mrc    p15, #0, r1, c1, c0, #0  @ read register c1 to r1
        tst    r1, #0x1                 @ test bit 1
        movne  r0, #1                   @ if not 0, MMU is enabled

        bx     r14
        .endfunc

@
@ ======== CSL_a15EnableMmuLongDescTranslationTable ========
@ Use the 40-bit translation system, with the Long-descriptor translation table format
@
        .text
        .func CSL_a15EnableMmuLongDescTranslationTable

CSL_a15EnableMmuLongDescTranslationTable:
        mov  r0, #1                     @ TTBR0 used and desc uses Long format
        lsl  r0, r0, #31                @ Set TTBCR.EAE bit
        mcr  p15, #0, r0, c2, c0, #2    @ write r0 to TTBCR
        isb                             @ flush instruction pipeline
                                        @ isb makes sure cp15 changes
                                        @ are visible to all subsequent
                                        @ instructions

        bx   r14
        .endfunc

@
@ ======== CSL_a15EnableMmuShortDescTranslationTable ========
@ Use the 32-bit translation system, with the Short-descriptor translation table format
@
        .text
        .func CSL_a15EnableMmuShortDescTranslationTable

CSL_a15EnableMmuShortDescTranslationTable:
        mov  r0, #0                     @ TTBR0 used and desc uses Short format
        mcr  p15, #0, r0, c2, c0, #2    @ write r0 to TTBCR
        isb                             @ flush instruction pipeline
                                        @ isb makes sure cp15 changes
                                        @ are visible to all subsequent
                                        @ instructions

        bx   r14
        .endfunc

@
@ ======== CSL_a15SetMmuLongDescTranslationTable ========
@ Set translation table for Long-descriptor translation table format
@
@       r0 - contains translation table base address
@
        .text
        .func CSL_a15SetMmuLongDescTranslationTable

CSL_a15SetMmuLongDescTranslationTable:
        mov  r1, #0
        mcrr p15, #0, r0, r1, c2        @ write TTBR0 with translation table.

        bx   r14
        .endfunc

@
@ ======== CSL_a15SetMmuShortDescTranslationTable ========
@ Set translation table for Short-descriptor translation table format
@
@       r0 - contains translation table base address
@
        .text
        .func CSL_a15SetMmuShortDescTranslationTable

CSL_a15SetMmuShortDescTranslationTable:
        mcr  p15, #0, r0, c2, c0, #0    @ write TTBR0 with translation table.

        bx   r14
        .endfunc

@
@ ======== CSL_a15InvalidateAllMmuTranslationTable ========
@
        .text
        .func CSL_a15InvalidateAllMmuTranslationTable

CSL_a15InvalidateAllMmuTranslationTable:
        dsb                             @ wait for invalidation to complete
        mcr  p15, #0, r0, c8, c7, #0
                                        @ invalidate unified TLB
        dsb                             @ wait for invalidation to complete
        isb                             @ flush instruction pipeline

        bx     r14
        .endfunc

@
@ ======== CSL_a15SetMmuMair ========
@ Write attr to appropriate byte offset within the selected MAIR register.
@
@       r0 - contains Index of MAIRn register. 0 for MAIR0 and 1 for MAIR1
@       r1 - contains Attribute to be written into MAIRn
@
        .text
        .func CSL_a15SetMmuMair

CSL_a15SetMmuMair:
        and  r2, r0, #0x3               @ attrIndx[1:0] gives byte offset
        lsl  r2, r2, #0x3               @ multiply by 8 to get bit offset
        mov  r3, #0xFF
        and  r1, r1, r3                 @ extract lsb byte from r1
        lsl  r1, r1, r2                 @ r1 is the encoded attribute
        lsl  r3, r3, r2                 @ generate bit mask
        tst  r0, #0x4                   @ attrIndx[2] selects MAIR 0 or 1
        bne  mair1

mair0:
        mrc  p15, #0, r0, c10, c2, #0   @ read MAIR0 into r0
        bic  r0, r0, r3
        orr  r0, r0, r1                 @ OR encoded attribute with MAIR0
        mcr  p15, #0, r0, c10, c2, #0   @ write r0 to  MAIR0
        b    exitSetMAIR

mair1:
        mrc  p15, #0, r0, c10, c2, #1   @ read MAIR1 into r0
        bic  r0, r0, r3
        orr  r0, r0, r1                 @ OR encoded attribute with MAIR1
        mcr  p15, #0, r0, c10, c2, #1   @ write r0 to  MAIR1

exitSetMAIR:
        isb                             @ flush instruction pipeline
        bx   r14
        .endfunc

@
@ ======== CSL_a15DisableDataCache ========
@ To disable the L1 data cache, first set the C bit to 0 in
@ SCTLR register, then writeback invalidate the whole L1 data
@ cache.
@
        .text
        .func CSL_a15DisableDataCache
CSL_a15DisableDataCache:
        stmfd   sp!, {r0-r7, r9-r11, lr}

        mrc     p15, #0, r0, c1, c0, #0 @ read register CR
        bic     r0, r0, #0x0004         @ clear C bit in CR
        mcr     p15, #0, r0, c1, c0, #0 @ DCache disabled
        ldmfd   sp!, {r0-r7, r9-r11, lr}
        bx      lr
        .endfunc


@
@ ======== CSL_a15DisableInstrCache ========
@ To disable the L1 instruction cache, first set the I bit to 0 in SCTLR
@ register, then invalidate the whole instruction cache.
@
        .text
        .func CSL_a15DisableInstrCache
CSL_a15DisableInstrCache:
        mrc     p15, #0, r0, c1, c0, #0 @ read register CR
        bic     r0, r0, #0x1000         @ clear I bit in CR
        mcr     p15, #0, r0, c1, c0, #0 @ ICache disabled
        bx      lr
        .endfunc


@
@ ======== CSL_a15EnableDataCache ========
@ To enable the L1 data cache set the C bit to 1 in the SCTLR register.
@
        .text
        .func CSL_a15EnableDataCache
CSL_a15EnableDataCache:
        mrc     p15, #0, r0, c1, c0, #0 @ read register CR
        orr     r0, r0, #0x0004         @ set C bit (bit 2) to 1
        mcr     p15, #0, r0, c1, c0, #0 @ L1D Cache enabled
        dsb                             @ drain write buffer
        bx      lr
        .endfunc


@
@ ======== CSL_a15EnableInstrCache ========
@ To enable the L1 instruction cache set the I bit to 1 in the c1 register.
@
        .text
        .func CSL_a15EnableInstrCache
CSL_a15EnableInstrCache:
        mrc     p15, #0, r0, c1, c0, #0 @ read register CR
        orr     r0, r0, #0x1000         @ set I bit (bit 12) to 1
        mcr     p15, #0, r0, c1, c0, #0 @ ICache enabled
        bx      lr
        .endfunc


@
@ ======== CSL_a15InvDataCache ========
@ Invalidates a range of MVA (modified virtual addresses) in the L1 data cache
@     CSL_a15InvDataCache(Ptr blockPtr, SizeT byteCnt)
@
@       r0 - contains blockPtr
@       r1 - contains byteCnt
@
        .text
        .func CSL_a15InvDataCache
CSL_a15InvDataCache:
        add     r1, r0, r1              @ calculate last address
        bic     r0, r0, #Cache_sizeL1dCacheLine - 1
                                        @ align blockPtr to cache line
1:
        mcr     p15, #0, r0, c7, c6, #1 @ invalidate single entry in DCache
        add     r0, r0, #Cache_sizeL1dCacheLine
                                        @ increment address by cache line size
        cmp     r0, r1                  @ compare to last address
        blo     1b                      @ loop if > 0
        dsb                             @ drain write buffer
        bx      lr                      @ return
        .endfunc


@
@ ======== CSL_a15InvInstrCache ========
@ Invalidates a range of modified virtual addresses in L1 instruction cache
@     CSL_a15InvInstrCache(Ptr blockPtr, SizeT byteCnt)
@
@       r0 - contains blockPtr
@       r1 - contains byteCnt
@
        .text
        .func CSL_a15InvInstrCache
CSL_a15InvInstrCache:
        add     r1, r0, r1               @ calculate last address
        bic     r0, r0, #Cache_sizeL1pCacheLine - 1
                                         @ align blockPtr to cache line
1:
        mcr     p15, #0, r0, c7, c5, #1  @ invalidate single entry in ICache
        add     r0, r0, #Cache_sizeL1pCacheLine
                                         @ increment address by cache line size
        cmp     r0, r1                   @ compare to last address
        blo     1b                       @ loop if > 0
        dsb                              @ drain write buffer
        bx      lr
        .endfunc


@
@ ======== CSL_a15InvAllDataCache ========
@ Invalidates all in data cache. Note: This is risky since data cache may
@ contain some stack variable or valid data that should not be invalidated.
@ Only use this function if you know for sure the data cache contains unwanted
@ information.
@
        .text
        .func CSL_a15InvAllDataCache
CSL_a15InvAllDataCache:
        stmfd   sp!, {r0-r7, r9-r11, lr}
        mrc     p15, #1, r0, c0, c0, #1 @ read clidr
        ands    r3, r0, #0x7000000      @ extract loc from clidr
        mov     r3, r3, lsr #23         @ left align loc bit field
        beq     5f                      @ if loc is 0, then no need to clean
        mov     r10, #0                 @ start clean at cache level 0
1:
        add     r2, r10, r10, lsr #1    @ work out 3x current cache level
        mov     r1, r0, lsr r2          @ extract cache type bits from clidr
        and     r1, r1, #7              @ mask of the bits for current cache only
        cmp     r1, #2                  @ see what cache we have at this level
        blt     4f                      @ skip if no cache, or just i-cache

        mcr     p15, #2, r10, c0, c0, #0@ select current cache level in cssr
        isb                             @ flush prefetch buffer
        mrc     p15, #1, r1, c0, c0, #0 @ read the new csidr
        and     r2, r1, #7              @ extract the length of the cache lines
        add     r2, r2, #4              @ add 4 (line length offset)
        movw    r4, #0x3ff
        ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
        clz     r5, r4                  @ find bit position of way size increment
        movw    r7, #0x7fff
        ands    r7, r7, r1, lsr #13     @ extract max number of the index size
2:
        mov     r9, r4                  @ create working copy of max way size
3:
        orr     r11, r10, r9, lsl r5    @ factor way and cache number into r11
        orr     r11, r11, r7, lsl r2    @ factor index number into r11
        mcr     p15, #0, r11, c7, c6, #2 @ invalidate by set/way
        subs    r9, r9, #1              @ decrement the way
        bge     3b
        subs    r7, r7, #1              @ decrement the index
        bge     2b
4:
        add     r10, r10, #2            @ increment cache number
        cmp     r3, r10
        bgt     1b
5:
        mov     r10, #0                 @ swith back to cache level 0
        mcr     p15, #2, r10, c0, c0, #0@ select current cache level in csselr
        isb                             @ flush prefetch buffer
        ldmfd   sp!, {r0-r7, r9-r11, lr}
        bx      lr
        .endfunc


@
@ ======== CSL_a15InvAllInstrCache ========
@ Invalidates all entries in the instruction cache
@
        .text
        .func CSL_a15InvAllInstrCache
CSL_a15InvAllInstrCache:
        mcr p15, #0, r0, c7, c5, #0
                                        @ invalidate all entries in ICache
        dsb                             @ drain write buffer
        bx      lr                      @ return
        .endfunc


@
@ ======== CSL_a15WbDataCache ========
@ Writes back the range of MVA in data cache.
@
@     CSL_a15WbDataCache(Ptr blockPtr, SizeT byteCnt)
@
@       r0 - contains blockPtr
@       r1 - contains byteCnt
@
        .text
        .func CSL_a15WbDataCache

CSL_a15WbDataCache:
        add     r1, r0, r1              @ calculate last address
        bic     r0, r0, #Cache_sizeL1dCacheLine - 1
                                        @ align address to cache line
1:
        mcr     p15, #0, r0, c7, c10, #1 @ write back a cache line
        add     r0, r0, #Cache_sizeL1dCacheLine
                                        @ increment address by cache line size
        cmp     r0, r1                  @ compare to last address
        blo     1b                      @ loop if count > 0
        dsb                             @ drain write buffer
        bx      lr
        .endfunc


@
@ ======== CSL_a15WbInvDataCache ========
@ Writes back and invalidates the range of MVA in data cache.
@
@     CSL_a15WbInvDataCache(Ptr blockPtr, SizeT byteCnt)
@
@       r0 - contains blockPtr
@       r1 - contains byteCnt
@
        .text
        .func CSL_a15WbInvDataCache

CSL_a15WbInvDataCache:
        add     r1, r0, r1              @ calculate last address
        bic     r0, r0, #Cache_sizeL1dCacheLine - 1
                                        @ align blockPtr to cache line
1:
        mcr     p15, #0, r0, c7, c14, #1@ writeback inv a cache line
        add     r0, r0, #Cache_sizeL1dCacheLine
                                        @ increment address by cache line size
        cmp     r0, r1                  @ compare to last address
        blo     1b                      @ loop if count > 0
        dsb                             @ drain write buffer
        bx      lr
        .endfunc


@
@ ======== CSL_a15WbAllDataCache ========
@ Write back all of L1 data cache
@
        .text
        .func CSL_a15WbAllDataCache

CSL_a15WbAllDataCache:
        stmfd   sp!, {r0-r7, r9-r11, lr}
        mrc     p15, #1, r0, c0, c0, #1 @ read clidr
        ands    r3, r0, #0x7000000      @ extract loc from clidr
        mov     r3, r3, lsr #23         @ left align loc bit field
        beq     5f                      @ if loc is 0, then no need to clean

        mov     r10, #0                 @ start clean at cache level 0

1:
        add     r2, r10, r10, lsr #1    @ work out 3x current cache level
        mov     r1, r0, lsr r2          @ extract cache type bits from clidr
        and     r1, r1, #7              @ mask of the bits for current cache only
        cmp     r1, #2                  @ see what cache we have at this level
        blt     4f                      @ skip if no cache, or just i-cache

        mcr     p15, #2, r10, c0, c0, #0@ select current cache level in cssr
        mcr     p15, #0, r10, c7, c5, #4@ flush prefetch buffer,
                                        @ with armv7 this is 'isb',
                                        @ but we compile with armv5
        mrc     p15, #1, r1, c0, c0, #0 @ read the new csidr
        and     r2, r1, #7              @ extract the length of the cache lines
        add     r2, r2, #4              @ add 4 (line length offset)
        movw    r4, #0x3ff
        ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
        clz     r5, r4                  @ find bit position of way size increment
        movw    r7, #0x7fff
        ands    r7, r7, r1, lsr #13     @ extract max number of the index size
2:
        mov     r9, r4                  @ create working copy of max way size
3:
        orr     r11, r10, r9, lsl r5    @ factor way and cache number into r11
        orr     r11, r11, r7, lsl r2    @ factor index number into r11
        mcr     p15, #0, r11, c7, c10, #2 @ clean line by set/way
        subs    r9, r9, #1              @ decrement the way
        bge     3b
        subs    r7, r7, #1              @ decrement the index
        bge     2b
4:
        add     r10, r10, #2            @ increment cache number
        cmp     r3, r10
        bgt     1b

5:
        mov     r10, #0                 @ switch back to cache level 0
        mcr     p15, #2, r10, c0, c0, #0@ select current cache level in cssr
        isb                             @ flush prefetch buffer
        ldmfd   sp!, {r0-r7, r9-r11, lr}
        bx      lr
        .endfunc


@
@ ======== CSL_a15WbInvAllDataCache ========
@ Write back and invalidate entire data cache
@
        .text
        .func CSL_a15WbInvAllDataCache

CSL_a15WbInvAllDataCache:
        stmfd   sp!, {r0-r7, r9-r11, lr}
        mrc     p15, #1, r0, c0, c0, #1 @ read clidr
        ands    r3, r0, #0x7000000      @ extract loc from clidr
        mov     r3, r3, lsr #23         @ left align loc bit field
        beq     5f                      @ if loc is 0, then no need to clean

        mov     r10, #0                 @ start clean at cache level 0

1:
        add     r2, r10, r10, lsr #1    @ work out 3x current cache level
        mov     r1, r0, lsr r2          @ extract cache type bits from clidr
        and     r1, r1, #7              @ mask of the bits for current cache only
        cmp     r1, #2                  @ see what cache we have at this level
        blt     4f                      @ skip if no cache, or just i-cache

        mcr     p15, #2, r10, c0, c0, #0@ select current cache level in cssr
        isb                             @ flush prefetch buffer
        mrc     p15, #1, r1, c0, c0, #0 @ read the new csidr
        and     r2, r1, #7              @ extract the length of the cache lines
        add     r2, r2, #4              @ add 4 (line length offset)
        movw    r4, #0x3ff
        ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
        clz     r5, r4                  @ find bit position of way size increment
        movw    r7, #0x7fff
        ands    r7, r7, r1, lsr #13     @ extract max number of the index size
2:
        mov     r9, r4                  @ create working copy of max way size
3:
        orr     r11, r10, r9, lsl r5    @ factor way and cache number into r11
        orr     r11, r11, r7, lsl r2    @ factor index number into r11
        mcr     p15, #0, r11, c7, c14, #2 @ clean & invalidate by set/way
        subs    r9, r9, #1              @ decrement the way
        bge     3b
        subs    r7, r7, #1              @ decrement the index
        bge     2b
4:
        add     r10, r10, #2            @ increment cache number
        cmp     r3, r10
        bgt     1b
5:
        mov     r10, #0                 @ swith back to cache level 0
        mcr     p15, #2, r10, c0, c0, #0@ select current cache level in cssr
        isb                             @ flush prefetch buffer
        ldmfd   sp!, {r0-r7, r9-r11, lr}
        bx      lr
        .endfunc


@
@ ======== CSL_a15CachePreload ========
@ Flush then pull memory block into L2 cache.
@
@ NO data accesses between context save/restore other than
@ loading the memory block.
@
@     CSL_a15CachePreload(Ptr blockPtr, SizeT byteCnt)
@
@       r0 - contains blockPtr
@       r1 - contains byteCnt
@
        .text
        .func CSL_a15CachePreload

CSL_a15CachePreload:
        stmfd   sp!, {r4-r8}

        @ No data reads beyond this point other than
        @ loading memory block into L2 cache

        add     r1, r0, r1                  @ calculate last address
        bic     r0, r0, #Cache_sizeL2CacheLine - 1

        @ now, pull block into this cache way
1:
        mcr     p15, #0, r0, c7, c14, #1    @ writeback inv this cache line to
                                            @ remove it from any other cache
                                            @ way
        ldr     r6, [r0]                    @ Load first word of cache line
                                            @ into this L2 cache way
                                            @ (unified, so data load works)
        add     r0, r0, #Cache_sizeL2CacheLine
                                            @ increment address by cache
                                            @ line size
        cmp     r0, r1                      @ compare to last address
        blo     1b

        ldmfd   sp!, {r4-r8}
        bx      lr
        .endfunc

@
@ ======== CSL_a15CycleCntEnable ========
@ Enable Cycle Count Register (CCNT)
@
        .text
        .func CSL_a15CycleCntEnable

CSL_a15CycleCntEnable:
        mrc p15, #0, r0, c9, c12, #0 @Read Performance Monitor Control Register
        orr r0, r0, #0xd             @PMCCNTR counts once every 64 clock cycles
        mcr p15, #0, r0, c9, c12, #0 @Reset Cycle count register
        mov r1, #0x80000000
        mcr p15, #0, r1, c9, c12, #1 @Enable the cycle count
        bx  lr
        .endfunc
@
@ ======== CSL_a15CycleCntRead ========
@ Read the Performance Monitor Control Register Counter
@
        .text
        .func CSL_a15CycleCntRead

CSL_a15CycleCntRead:
        mrc p15, #0, r0, c9, c13, #0
        bx  lr
        .endfunc
@
@ ======== CSL_a15ECCEnable ========
@ Enable the A15 ECC
@
        .text
        .func CSL_a15ECCEnable

CSL_a15ECCEnable:
        mrc p15, #1, r0, c9, c0, #2 @ Read L2 Control Register
        orr r0, r0, #0x200000       @ Enable ECC and Parity for A15
        push {r1-r12, lr}           @ Save registers - ROM code may pollute
                                    @ our registers
        ldr r12, =0x105             @ Set L2 control register - value in R0
        smc 0x1                     @ Call ROM Code API to set control register
        pop {r1-r12, pc}            @ Restore registers
        bx  lr
        .endfunc
@
@ ======== CSL_a15ECCDisable ========
@ Disable the A15 ECC
@
        .text
        .func CSL_a15ECCDisable

CSL_a15ECCDisable:
        mrc p15, #1, r0, c9, c0, #2 @ Read L2 Control Register
        and r0, r0, #0xffdfffff     @ Disable ECC and Parity for A15
        push {r1-r12, lr}           @ Save registers - ROM code may pollute
                                    @ our registers
        ldr r12, =0x105             @ Set L2 control register - value in R0
        smc 0x1                     @ Call ROM Code API to set control register
        pop {r1-r12, pc}            @ Restore registers
        bx  lr
        .endfunc
@
@ ======== CSL_a15ECCGetErrStatus ========
@ Read the A15 ECC error status
@
        .text
        .func CSL_a15ECCGetErrStatus

CSL_a15ECCGetErrStatus:
        mrc p15, #0, r0, c5, c1, #0 @ Read Auxiliary Data Fault Status Register
        bx  lr
        .endfunc
@
@ ======== CSL_a15DisableBranchPrediction ========
@
        .text
        .func CSL_a15DisableBranchPrediction

CSL_a15DisableBranchPrediction:
        mrc     p15, #0, r0, c1, c0, #0 @ read register SCTLR
        bic     r0, r0, #0x0800         @ clear Z bit in SCTLR to disable BP
        mcr     p15, #0, r0, c1, c0, #0 @ BP disabled
        mcr     p15, #0, r0, c7, c5, #6
                                        @ Invalidate all branch predictors
        bx      lr
        .endfunc

@
@ ======== CSL_a15EnableBranchPrediction ========
@
        .text
        .func CSL_a15EnableBranchPrediction

CSL_a15EnableBranchPrediction:
        mrc     p15, #0, r0, c1, c0, #0 @ read register SCTLR
        orr     r0, r0, #0x0800         @ set Z bit in SCTLR to enable BP
        mcr     p15, #0, r0, c1, c0, #0 @ BP enabled
        bx      lr
        .endfunc

@
@ ======== CSL_a15ReadCoreId ========
@ Read Core ID.
@
        .text
        .func CSL_a15ReadCoreId

CSL_a15ReadCoreId:
        mrc p15, 0, r0, c0, c0, 5
        and r0, r0, #3
        bx   lr
        .endfunc

@
@ ======== CSL_a15FPUEnable ========
@ Enable FPU.
@
        .text
        .func CSL_a15FPUEnable

CSL_a15FPUEnable:
        movw r0, #0x0000
        movt r0, #0x00F0
        mcr p15, #0, r0, c1, c0, #2
        isb
        movw r0, #0x0000
        movt r0, #0x4000
        fmxr fpexc, r0
        bx   lr
        .endfunc

@
@ ======== CSL_a15GetCacheType ========
@ Determine the mask of enabled caches
@
        .text
        .func CSL_a15GetCacheType

CSL_a15GetCacheType:
        mov     r0, #0
        mrc     p15, #0, r1, c1, c0, #0 @ fetch Control Register into r1

        @ Check if program cache enabled
        tst     r1, #0x1000             @ test I bit (bit 12) for program cache
        addne   r0, r0, #5              @ if I bit is true, program caches are
                                        @ enabled

        @ Check if data cache enabled
        tst     r1, #0x0004             @ test C bit (bit 2) for data cache
        addne   r0, r0, #0xa            @ if C bit is true, L1D and unified L2
                                        @ data cache is enabled

        @ Check if all cache enabled
        cmp     r0, #0xf
        movweq  r0, #0x7fff

        bx      lr
        .endfunc

@
@ ======== CSL_a15SwitchToPrivMode ========
@ Switch to privmode
@
        .text
        .func CSL_a15SwitchToPrivMode

CSL_a15SwitchToPrivMode:
        SWI  1
        bx   lr
        .endfunc		

@
@ ======== CSL_a15SwitchToUserMode ========
@ Switch to userMode
@
        .text
        .func CSL_a15SwitchToUserMode

CSL_a15SwitchToUserMode:
        mrs  r0, CPSR
        bic  r0, #0x0f
        orr  r0, #0x10
        msr  CPSR, r0
        bx   lr
        .endfunc

@
@ ======== CSL_a15IntrStatus ========
@ get the interrupt status
@
        .text
        .func CSL_a15IntrStatus

CSL_a15IntrStatus:
        mrs  r0, CPSR
        and  r0, #0xc0
        bx   lr
        .endfunc

@
@ ======== CSL_a15VectorBaseAddrSet ========
@ Low level ARM mode-specific register initialization for vector table
@
@       r0 - contains vector base address
@

        .text
        .func CSL_a15VectorBaseAddrSet

CSL_a15VectorBaseAddrSet:
        mcr     p15, #0, r0, c12, c0, #0

        bx      lr
        .endfunc


@
@ ======== CSL_armGicGlobalDisableInterrupt ========
@ Low level ARM mode-specific register initialization for vector table
@
@       r0 - contains previous value of CPSR as return
@

        .text
        .func CSL_armGicGlobalDisableInterrupt

CSL_armGicGlobalDisableInterrupt:
        dsb
        mrs     r0, cpsr_cf
        cpsid   i
        bx      lr
        .endfunc

@
@ ======== CSL_armGicGlobalRestoreInterrupt ========
@ Enable IRQ.
@
        .text
        .func CSL_armGicGlobalRestoreInterrupt

CSL_armGicGlobalRestoreInterrupt:
        dsb
        and     r1, r0, #128
        mrs     r0, cpsr_cf
        bic     r0, r0, #128
        orr     r1, r1, r0
        msr     cpsr_cf, r1
        bx      lr
        .endfunc


