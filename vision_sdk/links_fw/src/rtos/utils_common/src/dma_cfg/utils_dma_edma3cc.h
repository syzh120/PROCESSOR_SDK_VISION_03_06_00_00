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
 * \file utils_dma_edma3cc.h
 *
 * \brief EDMA controller specific configuration
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_DMA_EDMA3CC_H_
#define UTILS_DMA_EDMA3CC_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_dma.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Maximum number of EDMA instances that are supported
 *******************************************************************************
 */
/* At max there can be 2 instances of EDMA contorller
 * - System EDMA
 * - Local EDMA
 *
 * DSP  supports - System EDMA as well as local EDMA
 * EVE  supports - Only Local EDMA
 * IPU1 supports - Only System EDMA
 * A15  supports - Only System EDMA
 *
 */
#define UTILS_DMA_MAX_EDMA_INST     (2U)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Information related to interrupt for this EDMA controller on this
 *         CPU
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 ccXferCompCpuInt;
    /**< DMA transfer complete interrupt number at the CPU */

    UInt32 ccXferCompXbarInt;
    /**< DMA transfer complete interrupt number at the XBAR */

    UInt32 ccXferCompCtrlModXbarIndex;
    /**< DMA transfer complete interrupt control module XBAR index number */

    UInt32 ccErrorCpuInt;
    /**< DMA transfer error interrupt number at the CPU */

    UInt32 ccErrorXbarInt;
    /**< DMA transfer error interrupt number at the XBAR */

    UInt32 ccErrorCtrlModXbarIndex;
    /**< DMA transfer error interrupt control module XBAR index number */

    UInt32 tc0ErrorCpuInt;
    /**< DMA transfer controller error interrupt number at the CPU */

    UInt32 tc0ErrorXbarInt;
    /**< DMA transfer controller error interrupt number at the XBAR */

    UInt32 tc0ErrorCtrlModXbarIndex;
    /**< DMA transfer controller error interrupt control
     *   module XBAR index number */

    UInt32 tc1ErrorCpuInt;
    /**< DMA transfer controller error interrupt number at the CPU */

    UInt32 tc1ErrorXbarInt;
    /**< DMA transfer controller error interrupt number at the XBAR */

    UInt32 tc1ErrorCtrlModXbarIndex;
    /**< DMA transfer controller error interrupt control module XBAR
     *   index number */

    UInt32 ccXferCompCpuHwiInt;
    /**< DMA transfer complete interrupt CPU interrupt vector number
     *   ONLY applicable for DSP
     */

    UInt32 ccErrorCpuHwiInt;
    /**< DMA transfer error interrupt CPU interrupt vector number
     *   ONLY applicable for DSP
     */

    UInt32 tc0ErrorCpuHwiInt;
    /**< DMA transfer contorller error interrupt CPU interrupt vector number
     *   ONLY applicable for DSP
     */

    UInt32 tc1ErrorCpuHwiInt;
    /**< DMA transfer contorller error interrupt CPU interrupt vector number
     *   ONLY applicable for DSP
     */

} Utils_DmaIntrCfg;

/**
 *******************************************************************************
 *
 *  \brief Information related to a specific EDMA controller
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 edma3InstanceId;
    /**< EDMA controller instance ID */

    EDMA3_DRV_Handle hEdma;
    /**< Handle to EDMA controller LLD driver */

    BspOsal_IntrHandle   hwiCCXferCompInt;
    /**< Handle to HWI for transfer complete */

    UInt32 regionId;
    /**< EDMA region ID associated with this CPU */

    EDMA3_OS_Sem_Handle semHandle;
    /**< EDMA controller semaphore used by driver internally */

    EDMA3_DRV_GblConfigParams *pGblCfgParams;
    /**< EDMA controller config */

    EDMA3_DRV_InstanceInitConfig *pInstInitConfig;
    /**< EDMA controller config specific to this CPU */

    Utils_DmaIntrCfg  *pIntrConfig;
    /**< DMA controller interrupt related config for this CPU */

} Utils_DmaObj;



/*******************************************************************************
 *  Functions
 *******************************************************************************
 */


EDMA3_DRV_Result Utils_edma3Init (UInt32 edma3Id);

EDMA3_DRV_Result Utils_edma3DeInit (UInt32 edma3Id);

Bool Utils_dmaIsIntrSupported(UInt32 edmaInstId);

EDMA3_DRV_Result Utils_edma3OsSemCreate(Int32 initVal,
                            EDMA3_OS_Sem_Handle *hSem);

EDMA3_Result Utils_edma3OsSemDelete(EDMA3_OS_Sem_Handle hSem);

EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *errorCode);

UInt32 determineProcId(void);

EDMA3_DRV_Result edma3deinit (UInt32 edma3Id, EDMA3_DRV_Handle hEdma);

EDMA3_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int32_t mSecTimeout);

EDMA3_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem);

/*
 *******************************************************************************
 * Below function's are specific to a CPU, every CPU implementing EDMA APIs
 * needs to implement the below functions specific to their configuration
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Register the ISRs with the underlying OS
 *
 *        This API is implemented by CPU specific file
 *        dma_cfg\utils_dma_edma3cc_<cpu>_intr.c
 *
 *  \param pObj     [IN] EDMA controller information
 *
 *******************************************************************************
 */
void Utils_edma3RegisterInterrupts (Utils_DmaObj *pObj);

/**
 *******************************************************************************
 *
 *  \brief Un-Register the ISRs with the underlying OS
 *
 *        This API is implemented by CPU specific file
 *        dma_cfg\utils_dma_edma3cc_<cpu>_intr.c
 *
 *  \param pObj     [IN] EDMA controller information
 *
 *******************************************************************************
 */
void Utils_edma3UnRegisterInterrupts (Utils_DmaObj *pObj);

/**
 *******************************************************************************
 *
 *  \brief Find the region ID associated with EDMA controller and CPU ID
 *
 *        This API is implemented by CPU specific config file
 *        dma_cfg\utils_dma_cfg_<cpu>.c
 *
 *  \param edmaInstId   [IN] EDMA controller ID
 *
 *  \return region ID to use
 *
 *******************************************************************************
 */
UInt32 Utils_edma3GetRegionId(UInt32 edmaInstId);

/**
 *******************************************************************************
 *
 *  \brief To check whether the global EDMA3 configuration is required or not.
 *
 *        It should be done ONCE by any of the masters present in the system.
 *        This function checks whether the global configuration is required
 *        by the current master or not.
 *        In case of many masters, it should be done only by one of the masters.
 *        Hence this function will return TRUE only once and FALSE for all
 *        other masters.
 *
 *        This API is implemented by CPU specific config file
 *        dma_cfg\utils_dma_cfg_<cpu>.c
 *
 *  \param edmaInstId   [IN] EDMA controller ID
 *
 *  \return TRUE, perform global init
 *
 *******************************************************************************
 */
Bool Utils_edma3IsGblConfigRequired(UInt32 edmaInstId);

/**
 *******************************************************************************
 *
 *  \brief Return EDMA controller global config for this CPU
 *
 *        This API is implemented by CPU specific config file
 *        dma_cfg\utils_dma_cfg_<cpu>.c
 *
 *  \param edmaInstId   [IN] EDMA controller ID
 *
 *  \return Pointer to config
 *
 *******************************************************************************
 */
EDMA3_DRV_GblConfigParams *Utils_edma3GetGblCfg  (UInt32 edmaInstId);

/**
 *******************************************************************************
 *
 *  \brief Return EDMA controller instance specific config for this CPU
 *
 *        This API is implemented by CPU specific config file
 *        dma_cfg\utils_dma_cfg_<cpu>.c
 *
 *  \param edmaInstId   [IN] EDMA controller ID
 *
 *  \return Pointer to config
 *
 *******************************************************************************
 */
EDMA3_DRV_InstanceInitConfig *Utils_edma3GetInstCfg (UInt32 edmaInstId);

/**
 *******************************************************************************
 *
 *  \brief Return EDMA controller interrupt related config for this CPU
 *
 *        This API is implemented by CPU specific config file
 *        dma_cfg\utils_dma_cfg_<cpu>.c
 *
 *  \param edmaInstId   [IN] EDMA controller ID
 *
 *  \return Pointer to config
 *
 *******************************************************************************
 */
Utils_DmaIntrCfg *Utils_edma3GetIntrCfg (UInt32 edmaInstId);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  /* _UTILS_DMA_EDMA3CC_H_ */

