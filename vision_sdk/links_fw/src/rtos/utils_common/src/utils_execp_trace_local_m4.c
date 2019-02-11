/*
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
*/

/**
 *******************************************************************************
 * \file utils_execp_trace_local_m4.c
 *
 * \brief  This file has implementation for Exception Trace for local M4 core
 *
 *         Refer Utils_m4ExceptionHookFxn() for details
 *
 * \version 0.0 (Jun 2013) : [SS] First version
 * \version 0.1 (Jul 2013) : [SS] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define  ti_sysbios_family_arm_m3_Hwi__nolocalnames
#define  ti_sysbios_hal_Hwi__nolocalnames
/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
*/
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_uart.h>
#include <elf_linkage.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <xdc/runtime/Text.h>

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
Void Utils_m4ExceptionHookFxn(ti_sysbios_family_arm_m3_Hwi_ExcContext *excCtx);


/**
 *******************************************************************************
 *
 * \brief Implementation for Exception Trace
 *
 *        By default, when an exception occurs, an ExcContext structure is
 *        allocated on the ISR stack and filled in within the exception handler
 *        If excContextBuffer is initialized by the user, the ExcContext
 *        structure will be placed at that address instead. The buffer must be
 *        large enough to contain an ExcContext structure.
 *
 *        By default, when an exception occurs, a pointer to the base address
 *        of the stack being used by the thread causing the exception is used.
 *        If excStackBuffer is initialized by the user, the stack contents of
 *        the thread causing the exception will be copied to that address
 *        instead. The buffer must be large enough to contain the largest task
 *        stack or ISR stack defined in the application.
 *
 * \param   excCtx [IN]
 *
 * \return  None
 *
 *******************************************************************************
*/

Void Utils_m4ExceptionHookFxn(ti_sysbios_family_arm_m3_Hwi_ExcContext *excCtx)
{
    System_printf("Unhandled Exception:\n");
    if (excCtx->threadType == BIOS_ThreadType_Hwi){
            System_printf("Exception occurred in ThreadType_HWI");
    } else if (excCtx->threadType == BIOS_ThreadType_Swi){
            System_printf("Exception occurred in ThreadType_SWI");
    } else if (excCtx->threadType == BIOS_ThreadType_Task){
            System_printf("Exception occurred in ThreadType_Task");
    } else if (excCtx->threadType == BIOS_ThreadType_Main){
            System_printf("Exception occurred in ThreadType_Main");
    }
    else
    {
        /* Misra C fix */
    }

    System_printf("handle: 0x%x.\n", excCtx->threadHandle);
    System_printf("stack base: 0x%x.\n", excCtx->threadStack);

    System_printf("R0 = 0x%08x  R8  = 0x%08x\n", excCtx->r0, excCtx->r8);
    System_printf("R1 = 0x%08x  R9  = 0x%08x\n", excCtx->r1, excCtx->r9);
    System_printf("R2 = 0x%08x  R10 = 0x%08x\n", excCtx->r2, excCtx->r10);
    System_printf("R3 = 0x%08x  R11 = 0x%08x\n", excCtx->r3, excCtx->r11);
    System_printf("R4 = 0x%08x  R12 = 0x%08x\n", excCtx->r4, excCtx->r12);
    System_printf("R5 = 0x%08x  SP(R13) = 0x%08x\n", excCtx->r5, excCtx->sp);
    System_printf("R6 = 0x%08x  LR(R14) = 0x%08x\n", excCtx->r6, excCtx->lr);
    System_printf("R7 = 0x%08x  PC(R15) = 0x%08x\n", excCtx->r7, excCtx->pc);
    System_printf("PSR = 0x%08x\n", excCtx->psr);
    System_printf("ICSR = 0x%08x\n", ti_sysbios_family_arm_m3_Hwi_nvic.ICSR);
    System_printf("MMFSR = 0x%02x\n", ti_sysbios_family_arm_m3_Hwi_nvic.MMFSR);
    System_printf("BFSR = 0x%02x\n", ti_sysbios_family_arm_m3_Hwi_nvic.BFSR);
    System_printf("UFSR = 0x%04x\n", ti_sysbios_family_arm_m3_Hwi_nvic.UFSR);
    System_printf("HFSR = 0x%08x\n", ti_sysbios_family_arm_m3_Hwi_nvic.HFSR);
    System_printf("DFSR = 0x%08x\n", ti_sysbios_family_arm_m3_Hwi_nvic.DFSR);
    System_printf("MMAR = 0x%08x\n", ti_sysbios_family_arm_m3_Hwi_nvic.MMAR);
    System_printf("BFAR = 0x%08x\n", ti_sysbios_family_arm_m3_Hwi_nvic.BFAR);
    System_printf("AFSR = 0x%08x\n", ti_sysbios_family_arm_m3_Hwi_nvic.AFSR);
    System_printf("Terminating Execution...");
}



/* Nothing beyond this point */
