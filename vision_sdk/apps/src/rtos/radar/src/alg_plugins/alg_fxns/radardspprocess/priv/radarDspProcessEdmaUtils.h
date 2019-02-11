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
 *
 * \file radarDspProcessEdmaUtils.h  Radar DSP based Radar processing
 *                               private EDMA Utility header file.
 *
 * \brief  This link private header file has defined
 *         - EDMA Utiliy Functions and Macros.
 *
 *******************************************************************************
 */

#ifndef ALG_FXN_RADAR_DSP_PROCESS_EDMA_UTILS_H_
#define ALG_FXN_RADAR_DSP_PROCESS_EDMA_UTILS_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <xdc/std.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/** Default EDMA Burst Size */
#define ALG_FXN_RADAR_DSP_EDMA_DEFAULT_BURST_SIZE_IN_BYTES (128U)

#define ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR (2U)
#define ALG_FXN_RADAR_DSP_EDMA_PING_INDEX (0U)
#define ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX (1U)

#define ALG_FXN_RADAR_DSP_EDMA_QUEUE_ID_0  (0U)
#define ALG_FXN_RADAR_DSP_EDMA_QUEUE_ID_1  (1U)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
/** \brief EDMA Resource Structure */
typedef struct
{
    UInt32 tccId;
    /**< Transfer completion channel ID */
    UInt32 chId;
    /**< DMA Channel Id */
    UInt32 shadowChId;
    /**< Shadow Parameter ID */
    EDMA3_DRV_PaRAMRegs *pChParamRegs;
    /**< Pointer to the registers for the transfer param space for the chId */
    EDMA3_DRV_PaRAMRegs *pShadowParamRegs;
    /**< Pointer to the registers for the transfer param space for the
     *   shadowChId */
} AlgorithmFxn_RadarDspEdmaResource;

/*******************************************************************************
 *  Algorithm Function Private Functions
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspAllocEdmaResource(
    EDMA3_DRV_Handle hEdma,
    AlgorithmFxn_RadarDspEdmaResource *resource,
    UInt32 queueId);
Void AlgorithmFxn_RadarDspDeallocEdmaResource(
    EDMA3_DRV_Handle hEdma,
    AlgorithmFxn_RadarDspEdmaResource *resource);

Void AlgorithmFxn_RadarDspStartEdmaTransfer(
    EDMA3_DRV_Handle hEdma,
    AlgorithmFxn_RadarDspEdmaResource *resource);

Void AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
    EDMA3_DRV_Handle hEdma,
    AlgorithmFxn_RadarDspEdmaResource *resource);

static inline Void AlgorithmFxn_RadarDspSetSourceAddress(
    AlgorithmFxn_RadarDspEdmaResource *resource,
    UInt32 srcAddr)
{
    resource->pChParamRegs->srcAddr = srcAddr;
}

static inline Void AlgorithmFxn_RadarDspSetDestinationAddress(
    AlgorithmFxn_RadarDspEdmaResource *resource,
    UInt32 destAddr)
{
    resource->pChParamRegs->destAddr = destAddr;
}

#endif /* ALG_FXN_RADAR_DSP_PROCESS_EDMA_UTILS_H_ */
