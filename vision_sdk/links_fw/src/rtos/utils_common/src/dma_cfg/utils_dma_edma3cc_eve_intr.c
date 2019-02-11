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
 *
 * \file utils_dma_edma3cc_ipu_a15_intr.c
 *
 * \brief This file has the implementation of registering interrupts for
 *        IPU, A15 CPUs
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/src/dma_cfg/utils_dma_edma3cc.h>

#include <ti/sysbios/family/c64p/EventCombiner.h>

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
void Utils_edma3RegisterInterrupts (Utils_DmaObj *pObj)
{
    UInt32 cookie = 0;
    UInt32 intrId;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    intrId = pObj->pIntrConfig->ccXferCompCpuInt;

    Vps_printf(" UTILS: DMA: HWI Create for INT%d !!!\n", intrId);

    pObj->hwiCCXferCompInt = BspOsal_registerIntr(
                                intrId,
                                (BspOsal_IntrFuncPtr)&lisrEdma3ComplHandler0,
    /* MISRA.CAST.PTR_TO_INT:MISRAC_2004 Rule_11.3
       MISRAC_WAIVER:
       Interrupt private argument, passed back to the handler,
       Handler uses this to knwo instance id.
        */
                                (void*)pObj->edma3InstanceId);

    if (pObj->hwiCCXferCompInt == NULL)
    {
        Vps_printf(" UTILS: DMA: HWI Create Failed !!!\n");
        UTILS_assert((Bool)FALSE);
    }

    Hwi_enableInterrupt(intrId);

    /* Restore interrupts */
    Hwi_restore(cookie);
}

/**
 *******************************************************************************
 * \brief See utils_dma_edma3cc.h for function description
 *******************************************************************************
 */
void Utils_edma3UnRegisterInterrupts (Utils_DmaObj *pObj)
{
    UInt32 cookie = 0;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    BspOsal_unRegisterIntr(&pObj->hwiCCXferCompInt);

    /* Restore interrupts */
    Hwi_restore(cookie);
}


