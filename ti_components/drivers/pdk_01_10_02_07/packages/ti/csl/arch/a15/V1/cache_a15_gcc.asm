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
@; Cache_a15_gcc.asm - A15 Cache assembly code
@;

@;****************************** Global Symbols *********************************
        .global CACHEA15GetEnabledASM
        .global CACHEA15DisableStreamCacheLineASM

@;******************************* Code Section **********************************

@;================ CACHEA15GetEnabledASM ================
        .text
        .func CACHEA15GetEnabledASM

CACHEA15GetEnabledASM:
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

@;================ CACHEA15DisableStreamCacheLineASM ================
        .text
        .func CACHEA15DisableStreamCacheLineASM

CACHEA15DisableStreamCacheLineASM:

        MRC p15, 0, r0, c1, c0, 1     @ Read ACTLR Register
        ORR r0, r0, #0x1E000000       @ Disables streaming on Write streaming no-allocate threshold bit
        PUSH {r1-r12, lr}             @ Save registers - ROM code may pollute
                                      @ our registers

        LDR r12, =0x107    @; Set Auxiliary control register - value in R0
        SMC 0x1            @; Call ROM Code API to set control register
        POP {r1-r12, pc}   @; Restore registers
        .endfunc