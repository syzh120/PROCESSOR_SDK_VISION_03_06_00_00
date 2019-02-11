/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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

/**
 *******************************************************************************
 * \file radarDspProcessEdmaUtils.c
 *
 * \brief  This file contains plug in functions for radar DSP based 2D FFT,
 *         Object detection and angle of arrival estimation.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>
#include "radarDspProcessEdmaUtils.h"

/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the EDMA resource.
 *
 * \param  hEdma     [IN] EDMA Handle
 * \param  resource  [IN] Pointer to the EDMA resource.
 * \param  queueId   [IN] Queue ID for which TPTC to use.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspAllocEdmaResource(EDMA3_DRV_Handle hEdma,
    AlgorithmFxn_RadarDspEdmaResource *resource, UInt32 queueId)
{
    EDMA3_DRV_Result result;
    UInt32 paramAddr;

    resource->tccId  = EDMA3_DRV_TCC_ANY;
    resource->chId = EDMA3_DRV_DMA_CHANNEL_ANY;
    result = EDMA3_DRV_requestChannel( hEdma,
                                       &resource->chId,
                                       &resource->tccId,
                                       (EDMA3_RM_EventQueue)queueId,
                                       NULL,
                                       NULL );
    UTILS_assert(result == EDMA3_DRV_SOK);

    resource->shadowChId = EDMA3_DRV_LINK_CHANNEL;
    result = EDMA3_DRV_requestChannel( hEdma,
                                       &resource->shadowChId,
                                       0, /* not used in the case of link
                                           * channel here */
                                       (EDMA3_RM_EventQueue)queueId,
                                       NULL,
                                       NULL );
    UTILS_assert(result == EDMA3_DRV_SOK);

    result = EDMA3_DRV_getPaRAMPhyAddr(hEdma,
                                       resource->chId,
                                       &paramAddr);

    resource->pChParamRegs = (EDMA3_DRV_PaRAMRegs *) paramAddr;

    result = EDMA3_DRV_getPaRAMPhyAddr(hEdma,
                                       resource->shadowChId,
                                       &paramAddr);

    resource->pShadowParamRegs = (EDMA3_DRV_PaRAMRegs *) paramAddr;

    UTILS_assert(result == EDMA3_DRV_SOK);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Start function for the EDMA resource.
 *
 * \param  hEdma     [IN] EDMA Handle
 * \param  resource  [IN] Pointer to the EDMA resource.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspStartEdmaTransfer(
    EDMA3_DRV_Handle hEdma, AlgorithmFxn_RadarDspEdmaResource *resource)
{
    EDMA3_DRV_Result result;

    result = EDMA3_DRV_enableTransfer(hEdma, resource->chId,
        EDMA3_DRV_TRIG_MODE_MANUAL);
    UTILS_assert(result == EDMA3_DRV_SOK);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Wait function for the EDMA resource.
 *
 * \param  hEdma     [IN] EDMA Handle
 * \param  resource  [IN] Pointer to the EDMA resource.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
    EDMA3_DRV_Handle hEdma, AlgorithmFxn_RadarDspEdmaResource *resource)
{
    EDMA3_DRV_Result result;

    result = EDMA3_DRV_waitAndClearTcc(hEdma, resource->tccId);
    UTILS_assert(result == EDMA3_DRV_SOK);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of De-allocate function for the EDMA resource.
 *
 * \param  hEdma     [IN] EDMA Handle
 * \param  resource  [IN] Pointer to the EDMA resource.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspDeallocEdmaResource(
    EDMA3_DRV_Handle hEdma,
    AlgorithmFxn_RadarDspEdmaResource *resource)
{
    EDMA3_DRV_Result result;
    result = EDMA3_DRV_freeChannel(hEdma, resource->chId);
    UTILS_assert(result == EDMA3_DRV_SOK);
    result = EDMA3_DRV_freeChannel(hEdma, resource->shadowChId);
    UTILS_assert(result == EDMA3_DRV_SOK);
}
