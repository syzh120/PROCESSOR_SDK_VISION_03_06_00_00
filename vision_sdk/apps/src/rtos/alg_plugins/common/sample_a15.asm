/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
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
	@Write Performance Monitor Control Register
	MRC P15, #0, R0, C9, C12, #0	
	ORR R0, R0, #0xD                          @PMCCNTR counts once every 64 clock cycles
	MCR P15, #0, R0, C9, C12, #0 @Reset Cycle count register
	MOV R1, #0x80000000
	MCR P15, #0, R1, C9, C12, #1	@Enable the cycle count
	BX  LR

	.global  ARM_CCNT_Read	
ARM_CCNT_Read:
	MRC P15, #0, R0, C9, C13, #0
	BX  LR
