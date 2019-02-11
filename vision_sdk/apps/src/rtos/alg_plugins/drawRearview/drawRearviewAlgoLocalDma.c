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

/**
 *******************************************************************************
 *
 * \file drawRearviewAlgoLocalDma.c
 *
 * \brief Algorithm for Alg_drawRearview on DSP/EVE using Local EDMA
 *
 *        This Alg_drawRearview algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *        This algorithm does a frame copy. Height and width gets decided during
 *        Create. If height / width needs to be altered, then control call
 *        needs to be done.
 *
 *        This implementation uses CPU or DMA to copy the frames
 *        EDMA3LLD APIs are used to copy the frames.
 *        EDMA3LLD is initialized via Utils_dmaInit() during system init.
 *
 * \version 0.0 (Sept 2013) : [KC] First version
 * \version 0.1 (Sept 2013) : [PS] Merged CPU copy version also
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "iDrawRearviewAlgo.h"
#include "src/rtos/utils_common/include/utils_dma.h"

/**
 *******************************************************************************
 *
 *   \brief Structure for frame copy algoirthm object
 *
 *******************************************************************************
*/
typedef struct
{
    Alg_drawRearview_Obj     drawRearviewObj;
    /**< Base Frame copy object */

    unsigned int edmaChId;
    /**< EDMA CH ID that is used for this EDMA */

    unsigned int tccId;
    /**< EDMA TCC ID that is used for this EDMA */

    EDMA3_DRV_Handle hEdma;
    /**< Handle to EDMA controller associated with this logical DMA channel */

    EDMA3_DRV_PaRAMRegs *pParamSet;
    /**< Pointer to physical area of PaRAM for this channel */

} Alg_drawRearviewDma_Obj;

/**
 *******************************************************************************
 *
 * \brief Implementation of create for frame copy algo
 *
 * \param  pCreateParams    [IN] Creation parameters for frame copy Algorithm
 *
 * \return  Handle to algorithm
 *
 *******************************************************************************
 */
Alg_drawRearview_Obj * Alg_drawRearviewCreate(
                        Alg_drawRearviewCreateParams *pCreateParams)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    UInt32 paramPhyAddr;
    Alg_drawRearviewDma_Obj * pAlgHandle;

    pAlgHandle = (Alg_drawRearviewDma_Obj *) malloc(sizeof(Alg_drawRearviewDma_Obj));

    UTILS_assert(pAlgHandle != NULL);

    pAlgHandle->drawRearviewObj.maxHeight   = pCreateParams->maxHeight;
    pAlgHandle->drawRearviewObj.maxWidth    = pCreateParams->maxWidth;

    pAlgHandle->hEdma     =
        Utils_dmaGetEdma3Hndl(UTILS_DMA_LOCAL_EDMA_INST_ID);

    UTILS_assert(pAlgHandle->hEdma!=NULL);

    pAlgHandle->tccId       = EDMA3_DRV_TCC_ANY;
    pAlgHandle->edmaChId    = EDMA3_DRV_DMA_CHANNEL_ANY;

    edma3Result = EDMA3_DRV_requestChannel(
                                    pAlgHandle->hEdma,
                                    (uint32_t*)&pAlgHandle->edmaChId,
                                    (uint32_t*)&pAlgHandle->tccId,
                                    (EDMA3_RM_EventQueue)0,
                                    NULL, (void *)pAlgHandle);

    if (edma3Result == EDMA3_DRV_SOK)
    {
        Vps_printf(" ALG_drawRearview: DMA: Allocated CH (TCC) = %d (%d)\n",
                        pAlgHandle->edmaChId,
                        pAlgHandle->tccId);

        edma3Result = EDMA3_DRV_clearErrorBits(
                            pAlgHandle->hEdma,
                            pAlgHandle->edmaChId
                        );
    }
    else
    {
        Vps_printf(" ALG_drawRearview: DMA: ERROR in EDMA CH allocation\n");
    }

    if (edma3Result == EDMA3_DRV_SOK)
    {
        edma3Result = EDMA3_DRV_getPaRAMPhyAddr(
                                pAlgHandle->hEdma,
                                pAlgHandle->edmaChId,
                                &paramPhyAddr);

        pAlgHandle->pParamSet = (EDMA3_DRV_PaRAMRegs*)paramPhyAddr;
    }

    UTILS_assert(edma3Result == EDMA3_DRV_SOK);

    return &pAlgHandle->drawRearviewObj;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for frame copy algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV.
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned.
 *
 * \param  algHandle    [IN] Algorithm object handle
 * \param  inPtr[]      [IN] Array of input pointers
 *                           Index 0 - Pointer to Y data in case of YUV420SP,
 *                                   - Single pointer for YUV422IL or RGB
 *                           Index 1 - Pointer to UV data in case of YUV420SP
 * \param  outPtr[]     [IN] Array of output pointers. Indexing similar to
 *                           array of input pointers
 * \param  width        [IN] width of image
 * \param  height       [IN] height of image
 * \param  inPitch[]    [IN] Array of pitch of input image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  outPitch[]   [IN] Array of pitch of output image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  dataFormat   [IN] Different image data formats. Refer
 *                           System_VideoDataFormat
 * \param  copyMode     [IN] 0 - copy by CPU, 1 - copy by DMA
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_drawRearviewProcess(Alg_drawRearview_Obj *algHandle,
                           UInt32            *inPtr[],
                           UInt32            *outPtr[],
                           UInt32             width,
                           UInt32             height,
                           UInt32             inPitch[],
                           UInt32             outPitch[],
                           UInt32             dataFormat,
                           Uint32             copyMode
                          )
{
    Int32 rowIdx;
    Int32 colIdx;
    UInt32 *inputPtr;
    UInt32 *outputPtr;
    UInt32 numPlanes;
    UInt32 wordWidth;
    UInt32 lineSizeInBytes;
    UInt32 opt;
    uint16_t tccStatus;
    Alg_drawRearviewDma_Obj * pAlgHandle;

    pAlgHandle = (Alg_drawRearviewDma_Obj *)algHandle;

    if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
    {
        numPlanes = 1;
        lineSizeInBytes = width*2;
        wordWidth = (width*2)>>2;
    }
    else if(dataFormat == SYSTEM_DF_YUV420SP_UV)
    {
        numPlanes = 2;
        lineSizeInBytes = width;
        wordWidth = (width)>>2;
    }
    else
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    if(copyMode == 0)
    {
        /*
         * For Luma plane of 420SP OR RGB OR 422IL
         */
        inputPtr  = inPtr[0];
        outputPtr = outPtr[0];

        for(rowIdx = 0; rowIdx < height ; rowIdx++)
        {
            for(colIdx = 0; colIdx < wordWidth ; colIdx++)
            {
                *(outputPtr+colIdx) = *(inputPtr+colIdx);
            }
            inputPtr += (inPitch[0] >> 2);
            outputPtr += (outPitch[0] >> 2);
        }

        /*
         * For chroma plane of 420SP
         */
        if(numPlanes == 2)
        {
            inputPtr  = inPtr[1];
            outputPtr = outPtr[1];
            for(rowIdx = 0; rowIdx < (height >> 1) ; rowIdx++)
            {
                for(colIdx = 0; colIdx < wordWidth ; colIdx++)
                {
                    *(outputPtr+colIdx) = *(inputPtr+colIdx);
                }
                inputPtr += (inPitch[1] >> 2);
                outputPtr += (outPitch[1] >> 2);
            }
        }

    }
    else
    {
        opt  =
            (EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT)
               |
            ((pAlgHandle->tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                        & EDMA3_CCRL_OPT_TCC_MASK
             )
               |
            (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
               |
            (EDMA3_CCRL_OPT_TCINTEN_ENABLE
                        << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
            ;

        /*
         * For Luma plane of 420SP OR RGB OR 422IL
         */
        pAlgHandle->pParamSet->destAddr   = (UInt32)outPtr[0];
        pAlgHandle->pParamSet->srcAddr    = (UInt32)inPtr[0];
        pAlgHandle->pParamSet->srcBIdx    = inPitch[0];
        pAlgHandle->pParamSet->destBIdx   = outPitch[0];
        pAlgHandle->pParamSet->srcCIdx    = 0;
        pAlgHandle->pParamSet->destCIdx   = 0;
        pAlgHandle->pParamSet->aCnt       = lineSizeInBytes;
        pAlgHandle->pParamSet->bCnt       = height;
        pAlgHandle->pParamSet->cCnt       = 1;
        pAlgHandle->pParamSet->bCntReload = height;
        pAlgHandle->pParamSet->opt        = opt;
        pAlgHandle->pParamSet->linkAddr   = 0xFFFF;

        EDMA3_DRV_checkAndClearTcc(pAlgHandle->hEdma,
                                   pAlgHandle->tccId,
                                   &tccStatus);
        EDMA3_DRV_clearErrorBits (pAlgHandle->hEdma,pAlgHandle->edmaChId);
        EDMA3_DRV_enableTransfer (pAlgHandle->hEdma,pAlgHandle->edmaChId,
                                               EDMA3_DRV_TRIG_MODE_MANUAL);
        EDMA3_DRV_waitAndClearTcc(pAlgHandle->hEdma,pAlgHandle->tccId);

        /*
         * For chroma plane of 420SP
         */
        if(numPlanes == 2)
        {
            pAlgHandle->pParamSet->destAddr   = (UInt32)outPtr[1];
            pAlgHandle->pParamSet->srcAddr    = (UInt32)inPtr[1];
            pAlgHandle->pParamSet->srcBIdx    = inPitch[1];
            pAlgHandle->pParamSet->destBIdx   = outPitch[1];
            pAlgHandle->pParamSet->srcCIdx    = 0;
            pAlgHandle->pParamSet->destCIdx   = 0;
            pAlgHandle->pParamSet->aCnt       = lineSizeInBytes;
            pAlgHandle->pParamSet->bCnt       = height/2;
            pAlgHandle->pParamSet->cCnt       = 1;
            pAlgHandle->pParamSet->bCntReload = height/2;
            pAlgHandle->pParamSet->opt        = opt;
            pAlgHandle->pParamSet->linkAddr   = 0xFFFF;

            EDMA3_DRV_enableTransfer (pAlgHandle->hEdma,pAlgHandle->edmaChId,
                                               EDMA3_DRV_TRIG_MODE_MANUAL);
            EDMA3_DRV_waitAndClearTcc(pAlgHandle->hEdma,pAlgHandle->tccId);
        }

        EDMA3_DRV_clearErrorBits (pAlgHandle->hEdma,pAlgHandle->edmaChId);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for frame copy algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_drawRearviewControl(Alg_drawRearview_Obj          *pAlgHandle,
                           Alg_drawRearviewControlParams *pControlParams)
{
    /*
     * Any alteration of algorithm behavior
     */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop for frame copy algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_drawRearviewStop(Alg_drawRearview_Obj *algHandle)
{
      return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for frame copy algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_drawRearviewDelete(Alg_drawRearview_Obj *algHandle)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    Alg_drawRearviewDma_Obj * pAlgHandle;

    pAlgHandle = (Alg_drawRearviewDma_Obj *)algHandle;

    edma3Result = EDMA3_DRV_freeChannel(
                        pAlgHandle->hEdma,
                        pAlgHandle->edmaChId
                  );

    free(pAlgHandle);

    return edma3Result;
}

/* Nothing beyond this point */
