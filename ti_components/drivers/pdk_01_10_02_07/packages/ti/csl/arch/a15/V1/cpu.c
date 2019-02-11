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
 *  \file   cpu.c
 *
 *  \brief  CPU related definitions
 *
 *  This file contains the API definitions for configuring CPU
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <cpu.h>
#include <interrupt.h>

/* ========================================================================== */
/*               Internal Function Declarations                               */
/* ========================================================================== */
static void __inline MovePSRtoGenPurposeReg(uint32_t *stat);

static void __inline MovePSRtoGenPurposeReg(uint32_t *stat)
{
    /* IRQ and FIQ in CPSR */
    asm ("    mrs     r0, CPSR\n\t"
         "    and     %[result], r0, #0xC0" :[result] "=r" (*stat));
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void CPUSwitchToPrivilegedMode(void)
{
    asm ("    SWI   458752");
}

void CPUSwitchToUserMode(void)
{
    asm ("    mrs     r0, CPSR\n\t"
         "    bic     r0, #0x0F\n\t"
         "    orr     r0, #0x10\n\t "
         "    msr     CPSR, r0");
}

void CPUAbortHandler(void)
{
    Intc_AbortHandler();
}

uint32_t CPUIntStatus(void)
{
    uint32_t stat;

    MovePSRtoGenPurposeReg(&stat);
    return stat;
}

void CPUirqd(void)
{
    /* Disable IRQ in CPSR */
    asm ("    mrs     r0, CPSR\n\t"
         "    orr     r0, #0x80\n\t"
         "    msr     CPSR, r0");
}

void CPUirqe(void)
{
    /* Enable IRQ in CPSR */
    asm ("    mrs     r0, CPSR\n\t"
         "    bic     r0, #0x80\n\t"
         "    msr     CPSR, r0");
}

void CPUfiqd(void)
{
    /* Disable FIQ in CPSR */
    asm ("    mrs     r0, CPSR\n\t"
         "    orr     r0, #0x40\n\t"
         "    msr     CPSR, r0");
}

void CPUfiqe(void)
{
    /* Enable FIQ in CPSR */
    asm ("    mrs     r0, CPSR\n\t"
         "    bic     r0, #0x40\n\t"
         "    msr     CPSR, r0");
}

void CPUSendEvent(void)
{
    /*Data Synchronization Barrier */
    asm (" DSB");
    /*SEV Instruction */
    asm (" SEV");
}

void CPUDisableCPSRABit(void)
{
    asm ("    mrs     r0, CPSR\n\t"
         "    bic     r0, #0x100\n\t"
         "    msr     CPSR_cx, r0");
}

/**************************** End Of File ************************************/
