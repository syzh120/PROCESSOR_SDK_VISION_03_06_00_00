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
 * \file vectorToImageLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for vector to image Link
 *
 * \version 0.0 (Nov 2013) : [PS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "vectorToImgLink_priv.h"
#include "vectorToImgLink_dma.h"


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of synthesis algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImage_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_vectorToImageCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_vectorToImageProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_vectorToImageControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_vectorToImageStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_vectorToImageDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_VECTORTOIMAGE;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/*
 Formula used for RGB to YUV

 Y = 0.299R + 0.587G + 0.114B
 U = 0.492 (B-Y) + 128
 V = 0.877 (R-Y) + 128
*/
#define SWOSD_RGB2YUV_MUL_YR  0x132
#define SWOSD_RGB2YUV_MUL_YG  0x259
#define SWOSD_RGB2YUV_MUL_YB  0x074
#define SWOSD_RGB2YUV_MUL_U   0x1F7
#define SWOSD_RGB2YUV_MUL_V   0x382

#define SWOSD_RGB2YUV_OFFSET_UV 128
#define SWOSD_RGB2YUV_QSHIFT     10

inline UInt32 AlgorithmLink_vectorToImageRgb565toYuv422(UInt16 rgb)
{
  Int32 r, g, b;
  Int32 y, u, v;

  r  = (rgb & 0xF800) >> (11-3);
  g  = (rgb & 0x07E0) >> (5-2);
  b  = (rgb & 0x001F) << (3);

  y = ( ( r*SWOSD_RGB2YUV_MUL_YR + g*SWOSD_RGB2YUV_MUL_YG + b*SWOSD_RGB2YUV_MUL_YB) >> (SWOSD_RGB2YUV_QSHIFT) );
  u = (( ( SWOSD_RGB2YUV_MUL_U * (b-y)) >> (SWOSD_RGB2YUV_QSHIFT) ) + SWOSD_RGB2YUV_OFFSET_UV);
  v = (( ( SWOSD_RGB2YUV_MUL_V * (r-y)) >> (SWOSD_RGB2YUV_QSHIFT) ) + SWOSD_RGB2YUV_OFFSET_UV);

  if(v>255)
    v = 255;
  if(v<0)
    v = 0;

  return ( (UInt32)v  << 24 ) +
         ( (UInt32)y  << 16 ) +
         ( (UInt32)u  <<  8 ) +
         ( (UInt32)y  <<  0 ) ;
}

/**
 *******************************************************************************
 *
 * \brief Alloc and setup YUV422 LUT if required
 *
 * \param  pVectorToImageObj              [IN] Algorithm plugin object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageAllocYuvLut(
                    AlgorithmLink_VectorToImageObj * pVectorToImageObj)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32 i, j;
    UInt16 *pRgb565Lut;
    UInt32 *pYuv422Lut;

    pVectorToImageObj->pVectorToImageYUV422LUT = NULL;
    pVectorToImageObj->vectorToImageYUV422LUTSize = 0;

    if(pVectorToImageObj->algLinkCreateParams.dataFormat==
        SYSTEM_DF_YUV422I_YUYV )
    {
        pVectorToImageObj->lutBpp = ALG_VECTOR_TO_IMAGE_LUT_YUV422_BPP;
        pVectorToImageObj->lutPitch = pVectorToImageObj->lutWidth*
                                        pVectorToImageObj->lutBpp
                                        ;

        pVectorToImageObj->vectorToImageYUV422LUTSize
            =
            pVectorToImageObj->lutPitch*pVectorToImageObj->lutHeight;

        pVectorToImageObj->pVectorToImageYUV422LUT
            =
            Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                    pVectorToImageObj->vectorToImageYUV422LUTSize,
                    128
                    );

        UTILS_assert(pVectorToImageObj->pVectorToImageYUV422LUT!=NULL);

        /* convert RGB565 LUT to YUV422 LUT */
        pRgb565Lut = (UInt16*)pVectorToImageObj->pVectorToImageLUT;
        pYuv422Lut = (UInt32*)pVectorToImageObj->pVectorToImageYUV422LUT;

        for(i=0; i<pVectorToImageObj->lutHeight; i++)
        {
            for(j=0; j<pVectorToImageObj->lutWidth; j++)
            {
                *pYuv422Lut
                    = AlgorithmLink_vectorToImageRgb565toYuv422(*pRgb565Lut);

                pYuv422Lut++;
                pRgb565Lut++;
            }
        }

        /* point pVectorToImageLUT to YUV422 LUT */
        pVectorToImageObj->pVectorToImageLUT =
            pVectorToImageObj->pVectorToImageYUV422LUT;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Free YUV422 LUT if required
 *
 * \param  pVectorToImageObj              [IN] Algorithm plugin object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageFreeYuvLut(
                    AlgorithmLink_VectorToImageObj * pVectorToImageObj)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    if(pVectorToImageObj->pVectorToImageYUV422LUT != NULL)
    {
        Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                pVectorToImageObj->pVectorToImageYUV422LUT,
                pVectorToImageObj->vectorToImageYUV422LUTSize
                );

        pVectorToImageObj->pVectorToImageYUV422LUT = NULL;
        pVectorToImageObj->vectorToImageYUV422LUTSize = 0;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for vector to image alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageCreate(void * pObj, void * pCreateParams)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_VideoFrameBuffer    * pSystemVideoDataBuffer;
    System_LinkInfo              prevLinkInfo;
    System_LinkChInfo          * pOutChInfo;
    UInt32                       maxHeight;
    UInt32                       maxWidth;
    UInt32                       prevLinkId;
    UInt32                       prevLinkQueId;
    System_LinkChInfo          * pPrevChInfo;
    UInt32                       prevChInfoFlags;

    AlgorithmLink_VectorToImageObj              * pVectorToImageObj;
    AlgorithmLink_VectorToImageCreateParams     * pVectorToImageLinkCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;

    pVectorToImageLinkCreateParams =
        (AlgorithmLink_VectorToImageCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pVectorToImageObj = (AlgorithmLink_VectorToImageObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                                   sizeof(AlgorithmLink_VectorToImageObj), 32);

    UTILS_assert(pVectorToImageObj!=NULL);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pVectorToImageObj->algLinkCreateParams),
           (void*)(pVectorToImageLinkCreateParams),
           sizeof(AlgorithmLink_VectorToImageCreateParams)
          );


    pOutputQInfo = &pVectorToImageObj->outputQInfo;
    pInputQInfo  = &pVectorToImageObj->inputQInfo;

    maxHeight = pVectorToImageLinkCreateParams->maxHeight;
    maxWidth  = pVectorToImageLinkCreateParams->maxWidth;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pVectorToImageObj);

    /*
     * Populating parameters corresponding to Q usage of vector to image
     * algorithm link
     */
    pInputQInfo->qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo->qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo->queInfo.numCh = 1;

    prevLinkId =
        pVectorToImageLinkCreateParams->inQueParams.prevLinkId;

    prevLinkQueId =
        pVectorToImageLinkCreateParams->inQueParams.prevLinkQueId;

    status = System_linkGetInfo(
                prevLinkId,
                &prevLinkInfo);

    pOutChInfo  = &(pOutputQInfo->queInfo.chInfo[0]);
    pPrevChInfo = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]);

    /*
     * Certain channel info parameters simply get defined by previous link
     * channel info. Hence copying them to output channel info
     */
    pOutChInfo->startX = pPrevChInfo->startX;
    pOutChInfo->startY = pPrevChInfo->startY;
    pOutChInfo->width  = pPrevChInfo->width - DOPT_FLOW_WIDTH_PADDING_FACTOR;
    pOutChInfo->height = pPrevChInfo->height - DOPT_FLOW_HEIGHT_PADDING_FACTOR;

    pVectorToImageObj->inPitch = pPrevChInfo->pitch[0];

    if(pOutChInfo->width>maxWidth
        ||
       pOutChInfo->height>maxHeight
        )
    {
        Vps_printf(" VECTOR_TO_IMG: ERROR:"
                   " Input Width x Height > Max Width x Height !!!\n");
        UTILS_assert(0);
    }

    pOutChInfo->pitch[0] = SystemUtils_align(
                                maxWidth*ALG_VECTOR_TO_IMAGE_LUT_BPP,
                                ALGORITHMLINK_FRAME_ALIGN);
    prevChInfoFlags = pPrevChInfo->flags;

    prevChInfoFlags = System_Link_Ch_Info_Set_Flag_Mem_Type(prevChInfoFlags,
                                        SYSTEM_MT_NONTILEDMEM);

    prevChInfoFlags = System_Link_Ch_Info_Set_Flag_Scan_Format(prevChInfoFlags,
                                        SYSTEM_SF_PROGRESSIVE);

    prevChInfoFlags = System_Link_Ch_Info_Set_Flag_Buf_Type(prevChInfoFlags,
                                        SYSTEM_BUF_FMT_FRAME);


    if(pVectorToImageLinkCreateParams->dataFormat==
        SYSTEM_DF_YUV422I_YUYV )
    {
        /*
         * Setting output format as SYSTEM_DF_YUV422I_UYVY and this is independent
         * of the input image data format
         */
        prevChInfoFlags = System_Link_Ch_Info_Set_Flag_Data_Format(prevChInfoFlags,
                                   SYSTEM_DF_YUV422I_YUYV);
    }
    else
    {
        /*
         * Setting output format as SYSTEM_DF_RGB16_565 and this is independent
         * of the input image data format
         */
        prevChInfoFlags = System_Link_Ch_Info_Set_Flag_Data_Format(prevChInfoFlags,
                                                 SYSTEM_DF_BGR16_565);
    }

    pVectorToImageObj->lutBpp    = ALG_VECTOR_TO_IMAGE_LUT_BPP;

    if (pVectorToImageLinkCreateParams->isLutSize_129x129 == TRUE)
    {
        pVectorToImageObj->lutWidth  = ALG_VECTOR_TO_IMAGE_LUT129x129_WIDTH;
        pVectorToImageObj->lutHeight = ALG_VECTOR_TO_IMAGE_LUT129x129_HEIGHT;
    }
    else
    {
        pVectorToImageObj->lutWidth  = ALG_VECTOR_TO_IMAGE_LUT65x65_WIDTH;
        pVectorToImageObj->lutHeight = ALG_VECTOR_TO_IMAGE_LUT65x65_HEIGHT;
    }

    pVectorToImageObj->lutOffset = pVectorToImageObj->lutWidth/2;
    pVectorToImageObj->lutPitch
        = pVectorToImageObj->lutWidth*pVectorToImageObj->lutBpp;

    /* choose the LUT to use for vector to image */
    switch(pVectorToImageLinkCreateParams->lutId)
    {
        default:
        case 0:
            if (pVectorToImageLinkCreateParams->isLutSize_129x129 == TRUE)
            {
                pVectorToImageObj->pVectorToImageLUT
                = gAlg_vectorToImageLUT_16x16x0_25_129x129_0;
            }
            else
            {
                pVectorToImageObj->pVectorToImageLUT
                = gAlg_vectorToImageLUT_8x8x0_25_65x65_0;
            }
            break;
        case 1:
            if (pVectorToImageLinkCreateParams->isLutSize_129x129 == TRUE)
            {
                pVectorToImageObj->pVectorToImageLUT
                = gAlg_vectorToImageLUT_16x16x0_25_129x129_1;
            }
            else
            {
                pVectorToImageObj->pVectorToImageLUT
                = gAlg_vectorToImageLUT_8x8x0_25_65x65_1;
            }
            break;
    }

    AlgorithmLink_vectorToImageAllocYuvLut(pVectorToImageObj);

    pOutChInfo->flags  = prevChInfoFlags;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                1,
                                pInputQInfo,
                                1,
                                pOutputQInfo
                                );
    /*
     * No Algorithm creation needs to happen. Simple stateless algo.
     */

    if(pVectorToImageObj->algLinkCreateParams.numOutputFrames
            >
        VECTORTOIMAGE_LINK_MAX_NUM_OUTPUT
        )
    {
        pVectorToImageObj->algLinkCreateParams.numOutputFrames
            = VECTORTOIMAGE_LINK_MAX_NUM_OUTPUT;
    }

    pVectorToImageObj->outBufSize
        = maxHeight*pOutChInfo->pitch[0];

    /*
     * Creation of output buffers for output Q
     *  - Connecting video buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    for(frameIdx = 0;
        frameIdx < pVectorToImageObj->algLinkCreateParams
                    .numOutputFrames;
        frameIdx++)
    {
        pSystemBuffer         =
                             &(pVectorToImageObj->buffers[frameIdx]);
        pSystemVideoDataBuffer =
                             &(pVectorToImageObj->vectorToImageFrame[frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemVideoDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->chNum       = 0;

        memcpy((void *)&pSystemVideoDataBuffer->chInfo,
               (void *)&(pOutputQInfo->queInfo.chInfo[0]),
               sizeof(System_LinkChInfo));

        /*
         * Buffer allocation done for maxHeight, maxWidth and for data Format
         * SYSTEM_DF_RGB16_565
         */
        pSystemVideoDataBuffer->bufAddr[0]
                    = Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pVectorToImageObj->outBufSize,
                            ALGORITHMLINK_FRAME_ALIGN
                        );

        UTILS_assert(pSystemVideoDataBuffer->bufAddr[0] != NULL);

        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }

    pVectorToImageObj->useDma = ALG_VECTOR_TO_IMAGE_ENABLE_DMA;

    if(pVectorToImageObj->useDma)
    {
        status = AlgorithmLink_vectorToImageDmaCreate(pVectorToImageObj);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    pVectorToImageObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_VECTOR_TO_IMG");
    UTILS_assert(NULL != pVectorToImageObj->linkStatsInfo);

    pVectorToImageObj->isFirstFrameRecv   = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Process frame in non-ROI mode
 *
 * \param pVectorToImageObj [IN] Algorithm plugin handle
 * \param pInSysBuffer      [IN] Input buffer
 * \param pOutBuffer        [IN] Output buffer
 * \param pOutChInfo        [IN] Output Info
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageProcessNonRoi(
            AlgorithmLink_VectorToImageObj    * pVectorToImageObj,
            System_Buffer              * pInSysBuffer,
            System_VideoFrameBuffer    * pOutBuffer,
            System_LinkChInfo          * pOutChInfo
            )
{
    Int32 status;
    System_MetaDataBuffer      * pInBuffer;

    pInBuffer     = (System_MetaDataBuffer *)pInSysBuffer->payload;
    if(pVectorToImageObj->useDma)
    {
        status = AlgorithmLink_vectorToImageDmaConvert(
                     pVectorToImageObj,
                     pInBuffer->bufAddr[0],
                     pInBuffer->bufAddr[1],
                     pVectorToImageObj->inPitch,
                     pOutBuffer->bufAddr[0],
                     pOutChInfo->width,
                     pOutChInfo->height,
                     pOutChInfo->pitch[0]
                     );
    }
    else
    {
        Cache_inv(pInBuffer->bufAddr[0],
                  pInBuffer->metaBufSize[0],
                  Cache_Type_ALLD,
                  TRUE);

        Cache_inv(pInBuffer->bufAddr[1],
                  pInBuffer->metaBufSize[1],
                  Cache_Type_ALLD,
                  TRUE);

        status = AlgorithmLink_vectorToImageConvert(
                     pVectorToImageObj,
                     pInBuffer->bufAddr[0],
                     pInBuffer->bufAddr[1],
                     pVectorToImageObj->inPitch,
                     pOutBuffer->bufAddr[0],
                     pOutChInfo->width,
                     pOutChInfo->height,
                     pOutChInfo->pitch[0],
                     (UInt16*)pVectorToImageObj->pVectorToImageLUT
                     );

        Cache_wb(pOutBuffer->bufAddr[0],
             (pOutChInfo->height * pOutChInfo->pitch[0]),
             Cache_Type_ALLD,
             TRUE
            );
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Process frame in ROI mode
 *
 * \param pVectorToImageObj [IN] Algorithm plugin handle
 * \param pInSysBuffer      [IN] Input buffer
 * \param pOutBuffer        [IN] Output buffer
 * \param pOutChInfo        [IN] Output Info
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageProcessRoi(
            AlgorithmLink_VectorToImageObj    * pVectorToImageObj,
            System_Buffer              * pInSysBuffer,
            System_VideoFrameBuffer    * pOutBuffer,
            System_LinkChInfo          * pOutChInfo
            )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i, outWidth, outHeight;
    System_VideoFrameCompositeBuffer      * pInBuffer;
    UInt32 outBufOffset;
    AlgorithmLink_VectorToImageCreateParams  * pVectorToImageLinkCreateParams;

    pVectorToImageLinkCreateParams = (AlgorithmLink_VectorToImageCreateParams *)
                                    &pVectorToImageObj->algLinkCreateParams;

    pInBuffer     = (System_VideoFrameCompositeBuffer *)pInSysBuffer->payload;

    for(i=0; i<pInBuffer->numFrames; i++)
    {
        outBufOffset =
            pOutChInfo->pitch[0]*
            pVectorToImageLinkCreateParams->roiParams[i].startY
            +
            pVectorToImageLinkCreateParams->roiParams[i].startX*
            ALG_VECTOR_TO_IMAGE_LUT_BPP
            ;

        outWidth = pVectorToImageLinkCreateParams->roiParams[i].width;
        outHeight = pVectorToImageLinkCreateParams->roiParams[i].height;


        if(pVectorToImageObj->useDma)
        {
            status = AlgorithmLink_vectorToImageDmaConvert(
                         pVectorToImageObj,
                         pInBuffer->bufAddr[0][i],
                         pInBuffer->bufAddr[1][i],
                         pVectorToImageObj->inPitch,
                         (UInt8*)pOutBuffer->bufAddr[0] + outBufOffset,
                         outWidth,
                         outHeight,
                         pOutChInfo->pitch[0]
                         );
        }
        else
        {
            Cache_inv(pInBuffer->bufAddr[0][i],
                      pVectorToImageObj->inPitch*outHeight,
                      Cache_Type_ALLD,
                      TRUE);

            Cache_inv(pInBuffer->bufAddr[1][i],
                      pVectorToImageObj->inPitch*outHeight,
                      Cache_Type_ALLD,
                      TRUE);

            status = AlgorithmLink_vectorToImageConvert(
                         pVectorToImageObj,
                         pInBuffer->bufAddr[0][i],
                         pInBuffer->bufAddr[1][i],
                         pVectorToImageObj->inPitch,
                         (UInt8*)pOutBuffer->bufAddr[0] + outBufOffset,
                         outWidth,
                         outHeight,
                         pOutChInfo->pitch[0],
                         (UInt16*)pVectorToImageObj->pVectorToImageLUT
                         );

            Cache_wb(pOutBuffer->bufAddr[0],
                 (outHeight * pOutChInfo->pitch[0]),
                 Cache_Type_ALLD,
                 TRUE
                );
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of vector to image alg link
 *
 *        This function and the algorithm process function execute
 *        on same processor core. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageProcess(void * pObj)
{
    AlgorithmLink_VectorToImageObj    * pVectorToImageObj;
    Int32                        status      = SYSTEM_LINK_STATUS_SOK;
    Int32                        inputStatus = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pInSysBuffer;
    System_Buffer              * pOutSysBuffer;
    Bool                         bufDropFlag;
    System_VideoFrameBuffer    * pOutBuffer;
    System_LinkChInfo          * pOutChInfo;
    AlgorithmLink_VectorToImageCreateParams  * pVectorToImageLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;


    pVectorToImageObj = (AlgorithmLink_VectorToImageObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pVectorToImageObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    pVectorToImageLinkCreateParams = (AlgorithmLink_VectorToImageCreateParams *)
                                    &pVectorToImageObj->algLinkCreateParams;

    if(pVectorToImageObj->isFirstFrameRecv==FALSE)
    {
        pVectorToImageObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            1,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    pOutChInfo = &pVectorToImageObj->outputQInfo.queInfo.chInfo[0];

    /*
     * Get Input buffers from previous link and process them if output is
     * available
     */
    System_getLinksFullBuffers(
        pVectorToImageLinkCreateParams->inQueParams.prevLinkId,
        pVectorToImageLinkCreateParams->inQueParams.prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
          pInSysBuffer  = inputBufList.buffers[bufId];

          if(pInSysBuffer==NULL)
          {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
          }
          linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

          bufDropFlag   = TRUE;

          /* Check for parameter correctness. If in error, return */
          inputStatus = SYSTEM_LINK_STATUS_SOK;
          if(pVectorToImageLinkCreateParams->roiEnable==FALSE)
          {
              if(pInSysBuffer->bufType != SYSTEM_BUFFER_TYPE_METADATA)
              {
                  inputStatus = SYSTEM_LINK_STATUS_EFAIL;
                  linkStatsInfo->linkStats.inBufErrorCount++;
              }
          }
          else
          {
              if(pInSysBuffer->bufType
                  !=
                  SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
              {
                  inputStatus = SYSTEM_LINK_STATUS_EFAIL;
                  linkStatsInfo->linkStats.inBufErrorCount++;
              }
          }

          if(inputStatus == SYSTEM_LINK_STATUS_SOK)
          {
              /*
               * For frame to be processed:
               *  - Output buffer will be queried
               *  - If output buffer is available, then algorithm will be called
               */
              status = AlgorithmLink_getEmptyOutputBuffer(
                                                pObj,
                                                0,
                                                0,
                                                &pOutSysBuffer);

              if(status != SYSTEM_LINK_STATUS_SOK)
              {
                   /*
                    * If output buffer is not available, then input buffer
                    * is just returned back
                    */
                    linkStatsInfo->linkStats.chStats
                                    [0].inBufDropCount++;
                    linkStatsInfo->linkStats.chStats
                                    [0].outBufDropCount[0]++;

              }
              else
              {
                    pOutSysBuffer->srcTimestamp = pInSysBuffer->srcTimestamp;
                    pOutSysBuffer->frameId = pInSysBuffer->frameId;
                    pOutSysBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                    pOutBuffer =
                        (System_VideoFrameBuffer *)pOutSysBuffer->payload;


                    if(pVectorToImageLinkCreateParams->roiEnable==FALSE)
                    {
                        status = AlgorithmLink_vectorToImageProcessNonRoi(
                                    pVectorToImageObj,
                                    pInSysBuffer,
                                    pOutBuffer,
                                    pOutChInfo
                                    );
                    }
                    else
                    {
                        status = AlgorithmLink_vectorToImageProcessRoi(
                                    pVectorToImageObj,
                                    pInSysBuffer,
                                    pOutBuffer,
                                    pOutChInfo
                                    );
                    }
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    Utils_updateLatency(&pVectorToImageObj->linkLatency,
                                    pOutSysBuffer->linkLocalTimestamp);
                    Utils_updateLatency(&pVectorToImageObj->srcToLinkLatency,
                                    pOutSysBuffer->srcTimestamp);

                    linkStatsInfo->linkStats.chStats
                      [0].inBufProcessCount++;
                    linkStatsInfo->linkStats.chStats
                      [0].outBufCount[0]++;

                   /*
                    * Putting filled buffer into output full buffer
                    */
                    status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                              0,
                                                              pOutSysBuffer);

                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /*
                     * Informing next link that a new data has peen put for its
                     * processing
                     */
                    System_sendLinkCmd(
                        pVectorToImageLinkCreateParams->outQueParams.nextLink,
                        SYSTEM_CMD_NEW_DATA,
                        NULL);

                    /*
                     * Releasing (Free'ing) output buffers, since algorithm does not need
                     * it for any future usage.
                     */
                    outputBufListReturn.numBuf     = 1;
                    outputBufListReturn.buffers[0] = pOutSysBuffer;
                    AlgorithmLink_releaseOutputBuffer(pObj,
                                                    0,
                                                    &outputBufListReturn);


                    bufDropFlag = FALSE;
                }
          } /* (inputStatus == SYSTEM_LINK_STATUS_SOK) */

          /*
           * Releasing (Free'ing) Input buffers, since algorithm does not need
           * it for any future usage.
           */
          inputBufListReturn.numBuf     = 1;
          inputBufListReturn.buffers[0] = pInSysBuffer;
          AlgorithmLink_releaseInputBuffer(
                pObj,
                0,
                pVectorToImageLinkCreateParams->inQueParams.prevLinkId,
                pVectorToImageLinkCreateParams->inQueParams.prevLinkQueId,
                &inputBufListReturn,
                &bufDropFlag);

        } /* for (bufId = 0; bufId < inputBufList.numBuf; bufId++) */
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for vector to image algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_vectorToImageControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_VectorToImageObj  * pVectorToImageObj;
    AlgorithmLink_ControlParams     * pAlgLinkControlPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pVectorToImageObj = (AlgorithmLink_VectorToImageObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */
    switch(pAlgLinkControlPrm->controlCmd)
    {

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_vectorToImagePrintStatistics(pObj, pVectorToImageObj);
            break;

        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for vector to image algorithm link
 *
 *        For this algorithm there is no locking of frames and hence no
 *        flushing of frames. Also there are no any other functionality to be
 *        done at the end of execution of this algorithm. Hence this function
 *        is an empty function for this algorithm.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for synthesis algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_VideoFrameBuffer    * pSystemVideoDataBuffer;

    AlgorithmLink_VectorToImageObj           * pVectorToImageObj;

    pVectorToImageObj = (AlgorithmLink_VectorToImageObj *)
                            AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pVectorToImageObj->linkStatsInfo);
    UTILS_assert(status==0);

    if(pVectorToImageObj->useDma)
    {
        AlgorithmLink_vectorToImageDmaDelete(pVectorToImageObj);
    }

    AlgorithmLink_vectorToImageFreeYuvLut(pVectorToImageObj);

    for(frameIdx = 0;
        frameIdx < pVectorToImageObj->algLinkCreateParams
                    .numOutputFrames;
        frameIdx++)
    {
        pSystemVideoDataBuffer
                = &pVectorToImageObj->vectorToImageFrame[frameIdx];

        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemVideoDataBuffer->bufAddr[0],
                                pVectorToImageObj->outBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Space for Algorithm specific object gets freed here.
     */
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                           pVectorToImageObj,
                           sizeof(AlgorithmLink_VectorToImageObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pVectorToImageObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImagePrintStatistics(void *pObj,
                       AlgorithmLink_VectorToImageObj *pVectorToImageObj)
{
    UTILS_assert(NULL != pVectorToImageObj->linkStatsInfo);

    Utils_printLinkStatistics(&pVectorToImageObj->linkStatsInfo->linkStats,
                            "ALG_VECTOR_TO_IMAGE",
                            TRUE);

    Utils_printLatency("ALG_VECTOR_TO_IMAGE",
                       &pVectorToImageObj->linkStatsInfo->linkLatency,
                       &pVectorToImageObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}



/*******************************************************************************
 *
 * \brief Implementation of Process for vector to image converter
 *
 *        This function coverts optical flow vectors into color image
 *        Following are the assumptions / behavior of this function:
 *        1. X component of flow vectors
 *        2. Y component of flow vectors
 *        3. Output color image is of the data type SYSTEM_DF_BGR16_565
 *
 * \param  pVectorX    [IN] Pointer to array of X component of flow vectors
 * \param  pVectorY    [IN] Pointer to array of Y component of flow vectors
 * \param  pImage      [IN] Pointer to buffer for o.p. image
 * \param  height      [IN] Height of image
 * \param  width       [IN] Width of image
 * \param  pitch       [IN] Pitch of image
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************/
Int32 AlgorithmLink_vectorToImageConvert(
                               AlgorithmLink_VectorToImageObj *pVectorToImageObj,
                               Int8  * restrict pVectorX,
                               Int8  * restrict pVectorY,
                               UInt32  inPitch,
                               UInt8  * restrict pImage,
                               UInt32  width,
                               UInt32  height,
                               UInt32  outPitch,
                               UInt16 * restrict pColorMapLut
                               )
{
    UInt8   oFx;
    UInt8   oFy;
    UInt32  row;
    UInt32  col;
    UInt32  lutIndex;
    UInt32  lutOffset_tmp, lutWidthTmp;
    Bool    useYuvOutput = FALSE;

    lutOffset_tmp = pVectorToImageObj->lutOffset;
    lutWidthTmp = pVectorToImageObj->lutWidth;

    if(pVectorToImageObj->algLinkCreateParams.dataFormat
            ==SYSTEM_DF_YUV422I_YUYV)
    {
        useYuvOutput = TRUE;
    }

    if(useYuvOutput==FALSE)
    {
        UInt16 * restrict imagePtr;

        imagePtr = (UInt16*)pImage;

        for(row = 0; row < height; row++)
        {
            for(col = 0; col < width; col++)
            {
                oFx = (UInt8)(pVectorX[col] + lutOffset_tmp);
                oFy = (UInt8)(pVectorY[col] + lutOffset_tmp);

                lutIndex = lutWidthTmp*oFy
                            + oFx
                            ;

                imagePtr[col] = pColorMapLut[lutIndex];
            }
            imagePtr = (UInt16*)((UInt32)imagePtr + outPitch);
            pVectorX = (Int8*)  ((UInt32)pVectorX + inPitch);
            pVectorY = (Int8*)  ((UInt32)pVectorY + inPitch);
        }
    }
    else
    {
        UInt32  yuv32[2];
        UInt32  * restrict pColorMapLutYuv422;
        UInt32  * restrict imagePtrYuv422;

        pColorMapLutYuv422 = (UInt32*)pColorMapLut;
        imagePtrYuv422     = (UInt32*)pImage;

        for(row = 0; row < height; row++)
        {
            for(col = 0; col < width/2; col++)
            {
                oFx = (UInt8)(pVectorX[2*col] + lutOffset_tmp);
                oFy = (UInt8)(pVectorY[2*col] + lutOffset_tmp);

                lutIndex = lutWidthTmp*oFy
                            + oFx
                            ;

                yuv32[0] = pColorMapLutYuv422[lutIndex];

                oFx = (UInt8)(pVectorX[2*col+1] + lutOffset_tmp);
                oFy = (UInt8)(pVectorY[2*col+1] + lutOffset_tmp);

                lutIndex = lutWidthTmp*oFy
                            + oFx
                            ;

                yuv32[1] = pColorMapLutYuv422[lutIndex];

                imagePtrYuv422[col] =
                    (yuv32[0] & 0xFF00FFFF)
                    |
                    (yuv32[1] & 0x00FF0000)
                    ;
            }
            imagePtrYuv422 = (UInt32*)((UInt32)imagePtrYuv422 + outPitch);
            pVectorX       = (Int8*)  ((UInt32)pVectorX + inPitch);
            pVectorY       = (Int8*)  ((UInt32)pVectorY + inPitch);
        }
    }
    return 0;

}

/* Nothing beyond this point */
