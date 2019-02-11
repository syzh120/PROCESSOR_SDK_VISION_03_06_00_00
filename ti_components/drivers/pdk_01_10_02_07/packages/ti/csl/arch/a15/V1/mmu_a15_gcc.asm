@
@  Copyright (c) 2015, Texas Instruments Incorporated
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
@;*******************************************************************************
@;
@; mmu_a15_gcc.asm - A15 MMU assembly code
@;

@;****************************** Global Symbols *********************************
        .global MMUA15InitASM
        .global MMUA15DisableASM
        .global MMUA15EnableASM
        .global MMUA15IsEnabledASM
        .global MMUA15WriteMAIRASM
        .global MMUA15TLBInvalidateASM
        .global MMUA15TLBInvalidateAllASM

@;******************************* Code Section **********************************

@;================ MMUA15InitASM ================
        .text
        .func MMUA15InitASM

MMUA15InitASM:
        mov  r0, #1                     @ TTBR0 used and desc uses Long format
        lsl  r0, r0, #31                @ Set TTBCR.EAE bit
        mcr  p15, #0, r0, c2, c0, #2    @ write r0 to TTBCR
        isb                             @ flush instruction pipeline
                                        @ isb makes sure cp15 changes
                                        @ are visible to all subsequent
                                        @ instructions

        bx   r14
        .endfunc

@;================ MMUA15DisableASM ================
        .text
        .func MMUA15DisableASM

MMUA15DisableASM:
        mrc  p15, #0, r0, c1, c0, #0    @ read register c1
        mov  r1, #0x1                   @ move #1 into r1
        bic  r0, r0, r1                 @ clear bit 1 in r0
        mcr  p15, #0, r0, c1, c0, #0    @ mmu disabled (bit 1 = 0)

        bx   r14
        .endfunc

@;================ MMUA15EnableASM ================
        .text
        .func MMUA15EnableASM

MMUA15EnableASM:
        mov  r1, #0
        mov  r10, r0                    @ get page table pointer
        mcrr p15, #0, r10, r1, c2       @ write TTBR0 with Module->tableBuf.

        mrc  p15, #0, r0, c1, c0, #0    @ read register c1
        mov  r1, #0x1                   @ move #1 into r1
        orr  r0, r0, r1                 @ OR r1 with r0 into r0
        mcr  p15, #0, r0, c1, c0, #0    @ mmu enabled (bit 1 = 1)

        bx   r14
        .endfunc

@;================ MMUA15IsEnabledASM ================
        .text
        .func MMUA15IsEnabledASM

MMUA15IsEnabledASM:
        mov    r0, #0
        mrc    p15, #0, r1, c1, c0, #0  @ read register c1 to r1
        tst    r1, #0x1                 @ test bit 1
        movne  r0, #1                   @ if not 0, MMU is enabled

        bx     r14
        .endfunc

@;================ MMUA15WriteMAIRASM ================
        .text
        .func MMUA15WriteMAIRASM

MMUA15WriteMAIRASM:
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

@;================ MMUA15TLBInvalidateASM ================
        .text
        .func MMUA15TLBInvalidateASM

MMUA15TLBInvalidateASM:
        dsb                             @ wait for invalidation to complete
        add     r1, r0, r1              @ calculate last address
        lsr     r0, r0, #12             @ align pagePtr
        lsl     r0, r0, #12
tlbInv:
        mcr  p15, #0, r0, c8, c7, #3    @ invalidate unified TLB
        add     r0, r0, #4096           @ increment address by page size
        cmp     r0, r1                  @ compare to last address
        blo     tlbInv                  @ loop if count > 0
        dsb                             @ wait for invalidation to complete
        isb                             @ flush instruction pipeline

        bx      r14
        .endfunc

@;================ MMUA15TLBInvalidateAllASM ================
        .text
        .func MMUA15TLBInvalidateAllASM

MMUA15TLBInvalidateAllASM:
        dsb                             @ wait for invalidation to complete
        mcr  p15, #0, r0, c8, c7, #0    @ invalidate unified TLB
        dsb                             @ wait for invalidation to complete
        isb                             @ flush instruction pipeline

        bx     r14
        .endfunc
