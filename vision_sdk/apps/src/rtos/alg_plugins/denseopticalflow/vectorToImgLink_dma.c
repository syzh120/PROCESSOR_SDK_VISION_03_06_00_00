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
 * \file vectorToImageLink_dma.c
 *
 * \brief  This file contains DMA APIs for use with vector to image conversion
 *
 * \version 0.0 (Nov 2013) : [KC] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "vectorToImgLink_priv.h"

//#define USE_SYSTEM_DMA


#ifdef USE_SYSTEM_DMA
#define DSP_EDMA_REGION     (3)
#define DSP_EDMA_CC_ADDR    (0x43300000)
#define DSP_EMDA_INST_ID    UTILS_DMA_SYSTEM_EDMA_INST_ID
#define DSP_L2_EDMA_OFFSET  (0x40000000)
#else
#define DSP_L2_EDMA_OFFSET  (0x00000000)
#define DSP_EDMA_REGION     (0)
#define DSP_EDMA_CC_ADDR    (0x01D10000)
#define DSP_EMDA_INST_ID    UTILS_DMA_LOCAL_EDMA_INST_ID
#endif

#define DSP_EDMA_ESR        *(volatile UInt32*)(DSP_EDMA_CC_ADDR+0x2010+0x200*DSP_EDMA_REGION)
#define DSP_EDMA_ESRH       *(volatile UInt32*)(DSP_EDMA_CC_ADDR+0x2014+0x200*DSP_EDMA_REGION)
#define DSP_EDMA_IPR        *(volatile UInt32*)(DSP_EDMA_CC_ADDR+0x2068+0x200*DSP_EDMA_REGION)
#define DSP_EDMA_IPRH       *(volatile UInt32*)(DSP_EDMA_CC_ADDR+0x206C+0x200*DSP_EDMA_REGION)
#define DSP_EDMA_ICR        *(volatile UInt32*)(DSP_EDMA_CC_ADDR+0x2070+0x200*DSP_EDMA_REGION)
#define DSP_EDMA_ICRH       *(volatile UInt32*)(DSP_EDMA_CC_ADDR+0x2074+0x200*DSP_EDMA_REGION)



/**
 *******************************************************************************
 *
 * \brief Create DMA related resources required for this algo
 *
 *        DMA channel allocation and line buffer allocation in internal
 *        memory happens here
 *
 * \param  pObj         [IN] Algorithm Plugin object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageDmaCreate(AlgorithmLink_VectorToImageObj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    UInt32 paramPhyAddr;
    UInt32 i, inBufSize, outBufSize, lutSize;
    System_LinkChInfo   * pOutChInfo;
    uint16_t tccStatus;
    UInt32 lutSize_tmp;
    Utils_MemHeapStats memStats;

    AlgorithmLink_VectorToImageDmaObj *pDmaObj;

    pDmaObj = &pObj->dmaObj;

    pOutChInfo  = &(pObj->outputQInfo.queInfo.chInfo[0]);

    lutSize_tmp = pObj->lutPitch*pObj->lutHeight;

    pDmaObj->numLines = NUM_LINES_IN_BUF;
    pDmaObj->inBytesPerLine = pOutChInfo->width * ALG_VECTOR_TO_IMAGE_INPUT_BPP;
    pDmaObj->outBytesPerLine = pOutChInfo->width * ALG_VECTOR_TO_IMAGE_LUT_BPP;
    pDmaObj->inPitch = pObj->inPitch;
    pDmaObj->outPitch = pOutChInfo->pitch[0];

    inBufSize = SystemUtils_align(
                    pDmaObj->inBytesPerLine*pDmaObj->numLines,
                    128);

    outBufSize = SystemUtils_align(
                    pDmaObj->outBytesPerLine*pDmaObj->numLines,
                    128);

    lutSize    = SystemUtils_align(
                    lutSize_tmp,
                    128
                 );

    pDmaObj->allocSizeL2
            = inBufSize*2*NUM_PING_PONG_BUF
            + outBufSize*NUM_PING_PONG_BUF
            + lutSize;


    Utils_memGetHeapStats(UTILS_HEAPID_L2_LOCAL, &memStats);

    Vps_printf(" VECTOR_TO_IMAGE: inBufSize (x2)         = %d B\n",
                    inBufSize);
    Vps_printf(" VECTOR_TO_IMAGE: outBufSize             = %d B\n",
                    outBufSize);
    Vps_printf(" VECTOR_TO_IMAGE: lutSize                = %d B\n",
                    lutSize);
    Vps_printf(" VECTOR_TO_IMAGE: num lines in buf       = %d lines\n",
                    pDmaObj->numLines);
    Vps_printf(" VECTOR_TO_IMAGE: num bufs               = %d \n",
                    NUM_PING_PONG_BUF);
    Vps_printf(" VECTOR_TO_IMAGE: total memory used      = %d B\n",
                    pDmaObj->allocSizeL2);
    Vps_printf(" VECTOR_TO_IMAGE: total memory available = %d B\n",
                    memStats.freeSize);

    if(memStats.freeSize < pDmaObj->allocSizeL2)
    {
        Vps_printf(" VECTOR_TO_IMAGE: Internal Memory required (%d B) "
                   "> Internal memory available (%d B)\n",
                    pDmaObj->allocSizeL2,
                    memStats.freeSize
                   );
        UTILS_assert(0);
    }

    pDmaObj->pAllocAddrL2 = Utils_memAlloc(
                                UTILS_HEAPID_L2_LOCAL,
                                pDmaObj->allocSizeL2,
                                32
                                );

    UTILS_assert(pDmaObj->pAllocAddrL2!=NULL);

    /* assign internal memory address's */
    pDmaObj->pColorMapLut       = (UInt8*)pDmaObj->pAllocAddrL2;
    pDmaObj->pLineBufVectorX[0] = pDmaObj->pColorMapLut       + lutSize;
    pDmaObj->pLineBufVectorX[1] = pDmaObj->pLineBufVectorX[0] + inBufSize;
    pDmaObj->pLineBufVectorY[0] = pDmaObj->pLineBufVectorX[1] + inBufSize;
    pDmaObj->pLineBufVectorY[1] = pDmaObj->pLineBufVectorY[0] + inBufSize;
    pDmaObj->pLineBufOutput [0] = pDmaObj->pLineBufVectorY[1] + inBufSize;
    pDmaObj->pLineBufOutput [1] = pDmaObj->pLineBufOutput [0] + outBufSize;

    memcpy(pDmaObj->pColorMapLut,
           pObj->pVectorToImageLUT,
           lutSize_tmp
           );

    pDmaObj->hEdma =
        Utils_dmaGetEdma3Hndl(DSP_EMDA_INST_ID);

    pDmaObj->channelEnableMaskL = 0;
    pDmaObj->channelEnableMaskH = 0;

    for(i=0; i<NUM_DMA_CH; i++)
    {
        pDmaObj->tccId[i]       = EDMA3_DRV_TCC_ANY;
        pDmaObj->edmaChId[i]    = EDMA3_DRV_DMA_CHANNEL_ANY;

        edma3Result = EDMA3_DRV_requestChannel(
                                        pDmaObj->hEdma,
                                        (uint32_t*)&pDmaObj->edmaChId[i],
                                        (uint32_t*)&pDmaObj->tccId[i],
                                        (EDMA3_RM_EventQueue)0,
                                        NULL, (void *)pDmaObj);

        if (edma3Result == EDMA3_DRV_SOK)
        {
            Vps_printf(" VECTOR_TO_IMAGE: DMA: Allocated CH (TCC) = %d (%d)\n",
                            pDmaObj->edmaChId[i],
                            pDmaObj->tccId[i]);

            edma3Result = EDMA3_DRV_clearErrorBits(
                                pDmaObj->hEdma,
                                pDmaObj->edmaChId[i]
                            );

            EDMA3_DRV_checkAndClearTcc(pDmaObj->hEdma,
                               pDmaObj->tccId[i],
                               &tccStatus);
        }
        else
        {
            Vps_printf(" VECTOR_TO_IMAGE: DMA: ERROR in EDMA CH allocation\n");
        }

        if(pDmaObj->edmaChId[i]<32)
            pDmaObj->channelEnableMaskL |= (1<<pDmaObj->edmaChId[i]);
        else
            pDmaObj->channelEnableMaskH |= (1<<pDmaObj->edmaChId[i]);

        if (edma3Result == EDMA3_DRV_SOK)
        {
            edma3Result = EDMA3_DRV_getPaRAMPhyAddr(
                                    pDmaObj->hEdma,
                                    pDmaObj->edmaChId[i],
                                    &paramPhyAddr);

            pDmaObj->pParamSet[i] = (EDMA3_DRV_PaRAMRegs*)paramPhyAddr;
        }

        UTILS_assert(edma3Result == EDMA3_DRV_SOK);

        pDmaObj->edmaOpt[i]  =
            ((pDmaObj->tccId[i] << EDMA3_CCRL_OPT_TCC_SHIFT)
                        & EDMA3_CCRL_OPT_TCC_MASK
             )
               |
            (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
               |
            (EDMA3_CCRL_OPT_TCINTEN_ENABLE
                        << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
               |
            (EDMA3_CCRL_OPT_ITCINTEN_ENABLE
                        << EDMA3_CCRL_OPT_ITCINTEN_SHIFT)
               ;
    }

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Free DMA related resources required for this algo
 *
 * \param  pObj         [IN] Algorithm Plugin object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageDmaDelete(AlgorithmLink_VectorToImageObj *pObj)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    AlgorithmLink_VectorToImageDmaObj *pDmaObj;
    UInt32 i;

    pDmaObj = &pObj->dmaObj;

    for(i=0; i<NUM_DMA_CH; i++)
    {
        edma3Result = EDMA3_DRV_freeChannel(
                        pDmaObj->hEdma,
                        pDmaObj->edmaChId[i]
                  );
    }

    Utils_memFree(
                UTILS_HEAPID_L2_LOCAL,
                pDmaObj->pAllocAddrL2,
                pDmaObj->allocSizeL2
                  );

    return edma3Result;
}

static inline void AlgorithmLink_vectorToImageDmaSetParam(
                    AlgorithmLink_VectorToImageDmaObj *pDmaObj
                    )
{
    UInt32 i;

    for(i=0; i<NUM_DMA_CH;i++)
    {
        pDmaObj->pParamSet[i]->destAddr   = (UInt32)0;
        pDmaObj->pParamSet[i]->srcAddr    = (UInt32)0;
        pDmaObj->pParamSet[i]->srcCIdx    = 0;
        pDmaObj->pParamSet[i]->destCIdx   = 0;
        pDmaObj->pParamSet[i]->bCnt       = pDmaObj->numLines;
        pDmaObj->pParamSet[i]->cCnt       = 0xFFF;
        pDmaObj->pParamSet[i]->bCntReload = pDmaObj->numLines;
        pDmaObj->pParamSet[i]->opt        = pDmaObj->edmaOpt[i];
        pDmaObj->pParamSet[i]->linkAddr   = 0xFFFF;

        if(i==0 || i==1)
        {
            /* input buffers */
            pDmaObj->pParamSet[i]->srcBIdx    = pDmaObj->inPitch;
            pDmaObj->pParamSet[i]->destBIdx   = pDmaObj->inBytesPerLine;
            pDmaObj->pParamSet[i]->aCnt       = pDmaObj->inBytesPerLine;
        }
        else
        {
            /* output buffers */
            pDmaObj->pParamSet[i]->srcBIdx    = pDmaObj->outBytesPerLine;
            pDmaObj->pParamSet[i]->destBIdx   = pDmaObj->outPitch;
            pDmaObj->pParamSet[i]->aCnt       = pDmaObj->outBytesPerLine;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Set EDMA params and trigger the EDMA for ping or pong buffer
 *
 * \param  pDmaObj         [IN] Algorithm DMA object handle
 * \param  idx             [IN] 0 or 1, ping or pong buffer index
 * \param  pVectorX        [IN] Pointer to input in extrnal memory
 * \param  pVectorY        [IN] Pointer to input in extrnal memory
 * \param  pOutput         [IN] Pointer to output in extrnal memory
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_vectorToImageDmaSubmit(
                    AlgorithmLink_VectorToImageDmaObj *pDmaObj,
                    UInt32 idx,
                    UInt8  *pVectorX,
                    UInt8  *pVectorY,
                    UInt8  *pOutput
                    )
{
    pDmaObj->pParamSet[0]->destAddr   = (UInt32)pDmaObj->pLineBufVectorX[idx] + DSP_L2_EDMA_OFFSET;
    pDmaObj->pParamSet[0]->srcAddr    = (UInt32)pVectorX;

    pDmaObj->pParamSet[1]->destAddr   = (UInt32)pDmaObj->pLineBufVectorY[idx] + DSP_L2_EDMA_OFFSET;
    pDmaObj->pParamSet[1]->srcAddr    = (UInt32)pVectorY;

    pDmaObj->pParamSet[2]->destAddr   = (UInt32)pOutput;
    pDmaObj->pParamSet[2]->srcAddr    = (UInt32)pDmaObj->pLineBufOutput[idx] + DSP_L2_EDMA_OFFSET;

    DSP_EDMA_ESR  = pDmaObj->channelEnableMaskL;
    DSP_EDMA_ESRH = pDmaObj->channelEnableMaskH;
}

/**
 *******************************************************************************
 *
 * \brief Wait for previously triggered EDMA to complete
 *
 * \param  pDmaObj         [IN] Algorithm DMA object handle
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_vectorToImageDmaWaitComplete(
                    AlgorithmLink_VectorToImageDmaObj *pDmaObj)
{

    while(! ((DSP_EDMA_IPR & pDmaObj->channelEnableMaskL) == pDmaObj->channelEnableMaskL))
        ;
    DSP_EDMA_ICR = pDmaObj->channelEnableMaskL;

    while(! ((DSP_EDMA_IPRH & pDmaObj->channelEnableMaskH) == pDmaObj->channelEnableMaskH))
        ;
    DSP_EDMA_ICRH = pDmaObj->channelEnableMaskH;
}


/*******************************************************************************
 *
 * \brief Implementation of Process for vector to image converter using DMA
 *
 *        This function coverts optical flow vectors into color image
 *        Following are the assumptions / behavior of this function:
 *        1. X component of flow vectors
 *        2. Y component of flow vectors
 *        3. Output color image is of the data type SYSTEM_DF_BGR16_565
 *
 * \param  pObj        [IN] Algorithm plugin handle
 * \param  pVectorX    [IN] Pointer to array of X component of flow vectors
 * \param  pVectorY    [IN] Pointer to array of Y component of flow vectors
 * \param  pImage      [IN] Pointer to buffer for o.p. image
 * \param  height      [IN] Height of image
 * \param  width       [IN] Width of image
 * \param  pitch       [IN] Pitch of image
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************/
Int32 AlgorithmLink_vectorToImageDmaConvert(
                               AlgorithmLink_VectorToImageObj *pObj,
                               Int8   *pVectorX,
                               Int8   *pVectorY,
                               UInt32  inPitch,
                               UInt8  *pImage,
                               UInt32  width,
                               UInt32  height,
                               UInt32  outPitch
                               )
{
    UInt32 idx = 0;
    UInt32 numIterations, i, inBufSize, outBufSize;
    AlgorithmLink_VectorToImageDmaObj *pDmaObj;

    pDmaObj = &pObj->dmaObj;

    numIterations = height/pDmaObj->numLines;
    inBufSize = pDmaObj->inBytesPerLine*pDmaObj->numLines;
    outBufSize = pDmaObj->outBytesPerLine*pDmaObj->numLines;

    AlgorithmLink_vectorToImageDmaSetParam(pDmaObj);

    /* read first set of lines */
    AlgorithmLink_vectorToImageDmaSubmit(
            pDmaObj,
            idx,
            (UInt8*)pVectorX,
            (UInt8*)pVectorY,
            (UInt8*)pImage
        );

    AlgorithmLink_vectorToImageDmaWaitComplete(pDmaObj);

    for(i=0; i<numIterations; i++)
    {
        if(i!=(numIterations-1))
        {
            /* dont increment for last iteration since we readh end of frame */
            pVectorX = (Int8*)((UInt32)pVectorX + inPitch*pDmaObj->numLines);
            pVectorY = (Int8*)((UInt32)pVectorY + inPitch*pDmaObj->numLines);
        }

        AlgorithmLink_vectorToImageDmaSubmit(
            pDmaObj,
            idx^1,
            (UInt8*)pVectorX,
            (UInt8*)pVectorY,
            (UInt8*)pImage
        );

        Cache_inv(pDmaObj->pLineBufVectorX[idx],
                  inBufSize,
                  Cache_Type_L1D,
                  TRUE);

        Cache_inv(pDmaObj->pLineBufVectorY[idx],
                  inBufSize,
                  Cache_Type_L1D,
                  TRUE);

        AlgorithmLink_vectorToImageConvert(
            pObj,
            (Int8*)pDmaObj->pLineBufVectorX[idx],
            (Int8*)pDmaObj->pLineBufVectorY[idx],
            pDmaObj->inBytesPerLine,
            pDmaObj->pLineBufOutput[idx],
            width,
            pDmaObj->numLines,
            pDmaObj->outBytesPerLine,
            (UInt16*)pDmaObj->pColorMapLut
            );

        Cache_wb(pDmaObj->pLineBufOutput[idx],
             outBufSize,
             Cache_Type_L1D,
             TRUE
            );

        if(i>0)
        {
            /* dont increment for first iteration since first output not written
             * to external memory yet
             */
            pImage   = (UInt8*)((UInt32)pImage   + outPitch*pDmaObj->numLines);
        }

        idx = idx ^ 1; /* toggle buffers */

        AlgorithmLink_vectorToImageDmaWaitComplete(pDmaObj);
    }

    /* output last set of lines */
    AlgorithmLink_vectorToImageDmaSubmit(
            pDmaObj,
            idx^1,
            (UInt8*)pVectorX,
            (UInt8*)pVectorY,
            (UInt8*)pImage
        );

    AlgorithmLink_vectorToImageDmaWaitComplete(pDmaObj);

    return 0;
}

