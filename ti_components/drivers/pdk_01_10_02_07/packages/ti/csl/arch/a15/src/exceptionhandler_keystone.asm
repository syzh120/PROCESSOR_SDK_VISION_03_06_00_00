@******************************************************************************
@
@ Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
@
@
@  Redistribution and use in source and binary forms, with or without
@  modification, are permitted provided that the following conditions
@  are met:
@
@    Redistributions of source code must retain the above copyright
@    notice, this list of conditions and the following disclaimer.
@
@    Redistributions in binary form must reproduce the above copyright
@    notice, this list of conditions and the following disclaimer in the
@    documentation and/or other materials provided with the
@    distribution.
@
@    Neither the name of Texas Instruments Incorporated nor the names of
@    its contributors may be used to endorse or promote products derived
@    from this software without specific prior written permission.
@
@  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
@  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
@  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
@  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
@  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
@  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
@  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES@ LOSS OF USE,
@  DATA, OR PROFITS@ OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
@  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
@  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
@  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
@
@******************************************************************************
@
@******************************************************************************
@
@ exceptionhandler.S - Definitions of exception handlers
@
@
@******************************************************************************
@
@ Share header file with assembly source code
@
#include <ti/csl/arch/a15/hw_intc.h>

@************************** Global symbols ************************************
        .global IRQHandler
        .global FIQHandler
        .global AbortHandler
        .global SVC_Handler
        .global UndefInstHandler
        .global Intc_AbortHandler
        .global fnRAMVectors
        .global addrIar
        .global addrEoi

@**************************** Text Section ************************************
        .text

@ This source file is assembled for ARM instructions
        .code 32
@******************************************************************************
@*                  Function Definition of SWI Handler
@******************************************************************************
@
@ The SVC Handler switches to system mode if the SVC number is 458752. If the
@ SVC number is different, no mode switching will be done. No other SVC are
@ handled here
@
SVC_Handler:
        STMFD     r13!, {r0-r1, r14}       @ Save context in SVC stack
        SUB       r13, r13, #0x4           @ Adjust the stack pointer
        LDR       r0, [r14, #-4]           @ R0 points to SWI instruction
        BIC       r0, r0, #MASK_SVC_NUM    @ Get the SWI number
        CMP       r0, #458752
        MRSEQ     r1, spsr                 @ Copy SPSR
        ORREQ     r1, r1, #0x1F            @ Change the mode to System
        MSREQ     spsr_cf, r1              @ Restore SPSR
        ADD       r13, r13, #0x4           @ Adjust the stack pointer
        LDMFD     r13!, {r0-r1, pc}^       @ Restore registers from IRQ stack

@******************************************************************************
@*                  Function Definition of IRQ Handler
@******************************************************************************
@
@ The IRQ handler saves the context and jumps to the common handler which calls
@ the handlers of highest priority pending IRQ.
@
IRQHandler:
        SUB       r14, r14, #4             @ Apply lr correction
        STMFD     r13!, {r0-r3, r12, r14}  @ Save context
        MRS       r12, spsr                @ Copy spsr
        VMRS      r1, FPSCR                @ Copy fpscr
        VMRS      r2, FPEXC                @ Copy fpexc
        STMFD     r13!, {r1-r2, r12}       @ Save spsr, fpscr and fpexc
        VSTMDB    r13!, {d0-d7}            @ Save D0-D7 Neon/VFP registers
        VSTMDB    r13!, {d16-d31}          @ Save D16-D31 Neon/VFP registers

        bl        INTCCommonIntrHandler

        VLDMIA    r13!, {d16-d31}          @ Restore D16-D31 Neon/VFP registers
        VLDMIA    r13!, {d0-d7}            @ Restore D0-D7 Neon/VFP registers
        LDMFD     r13!, {r1-r2, r12}       @ Get fpscr, fpexc and spsr
        MSR       spsr, r12                @ Restore spsr
        VMSR      fpscr, r1                @ Restore fpscr
        VMSR      fpexc, r2                @ Restore fpexc

        LDMFD     r13!, {r0-r3, r12, pc}^  @ Restore the context and return

@******************************************************************************
@*                  Function Definition of FIQ Handler
@******************************************************************************
@
@ FIQ is not supported in this version of software.
@
FIQHandler:
        SUBS      pc, r14, #0x4            @ Return to program before FIQ

@******************************************************************************
@*             Function Definition of Abort/Undef Handler
@******************************************************************************
@
@ The Abort handler goes to the C handler of abort mode. Note that the undefined
@ instruction is not handled separately.
@ if nothing is done in the abort mode, the execution enters infinite loop.
@
AbortHandler:
UndefInstHandler:
@
@ Disable all the interrupts
@
        MRS     r0, cpsr                  @ Read from CPSR
        ORR     r0, r0, #0xC0             @ Clear the IRQ and FIQ bits
        MSR     cpsr, r0                  @ Write to CPSR
        ADD     r14, pc, #0               @ Store the return address
@
@ Go to infinite loop
@
loop0:
        B       loop0
@*****************************************************************************
@
@ End of the file
@
    .end



