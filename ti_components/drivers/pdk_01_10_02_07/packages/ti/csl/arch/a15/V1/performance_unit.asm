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
/*---------------------------------------------------------------------------
* File: peformance_unit.asm
* Author: vinoth: Modified the original SDO code for cortex-A15
*---------------------------------------------------------------------------

*---------------------------------------------------------------------------
*
* Functions to Enable, Reset & Read the Cycle Count Register (CCNT)
*
* CCNT enabled and reset via Performance Monitor Control Register (PMNC)
* The CCNT is divided by 64 (by setting Bit 3 of PMNC to 1)
* CCNT is checked for overflow by looking at bit 10 of PMNC
* CCNT Read returns the clock value divided by 64 cycles.
* To get the actual CPU cycle multiple it with 64
*---------------------------------------------------------------------------*/

	.text


.set CCNT_CP1, C9
.set CCNT_CP2, C13

	.global  ARM_CCNT_Enable
	.global  ARM_CCNT_Reset


ARM_CCNT_Enable:
ARM_CCNT_Reset:
	mrc p15, #0, r0, c9, c12, #0 @Read Performance Monitor Control Register
	orr r0, r0, #0xd             @PMCCNTR counts once every 64 clock cycles
	mcr p15, #0, r0, c9, c12, #0 @Reset Cycle count register
	mov r1, #0x80000000
	mcr p15, #0, r1, c9, c12, #1 @Enable the cycle count
	bx  lr

	.global  ARM_CCNT_Read
ARM_CCNT_Read:
	mrc p15, #0, r0, c9, c13, #0
	bx  lr

