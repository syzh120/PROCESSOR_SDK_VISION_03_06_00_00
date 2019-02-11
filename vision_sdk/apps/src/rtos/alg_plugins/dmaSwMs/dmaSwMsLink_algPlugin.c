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
 * \file dmaSwMsLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for DMA based SW Mosaic
 *
 * \version 0.0 (Sept 2013) : [KC] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "dmaSwMsLink_priv.h"

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of this algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_DmaSwMs_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_dmaSwMsCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_dmaSwMsProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_dmaSwMsControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_dmaSwMsStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_dmaSwMsDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_DMA_SWMS;
#endif

#ifdef BUILD_M4
    algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;
#endif

#ifdef BUILD_A15
    algId = ALGORITHM_LINK_A15_ALG_DMA_SWMS;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Check layout parameters and whereever possible also try to correct it
 *        instead of returning as invalid. When not possible to correct it
 *        return validity as FALSE
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pDmaSwMsObj       [IN] DMA SW Mosaic Object handle
 *
 * \return  TRUE, valid parameters, FALSE, invalid parameters
 *
 *******************************************************************************
 */
Bool AlgorithmLink_dmaSwMsIsLayoutPrmValid(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj,
                    AlgorithmLink_DmaSwMsLayoutParams *pLayoutPrm
                    )
{
    Bool isValid = TRUE;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;
    System_LinkChInfo *pInChInfo;
    UInt32 winId;

    /* if number of window > max possible then possibly some array overrun
     * occured hence, flag as in valid parameter
     */
    if(pLayoutPrm->numWin>ALGORITHM_LINK_DMA_SW_MS_MAX_WINDOWS)
        isValid = FALSE;

    /* limit output width x height to max buffer width x height */
    if(pLayoutPrm->outBufWidth > pDmaSwMsObj->createArgs.maxOutBufWidth)
    {
        pLayoutPrm->outBufWidth = pDmaSwMsObj->createArgs.maxOutBufWidth;
    }

    if(pLayoutPrm->outBufHeight > pDmaSwMsObj->createArgs.maxOutBufHeight)
    {
        pLayoutPrm->outBufHeight = pDmaSwMsObj->createArgs.maxOutBufHeight;
    }

    if(isValid)
    {
        /* crop input / output region if out of bounds */
        for(winId=0; winId<pLayoutPrm->numWin; winId++)
        {
            pWinInfo = &pLayoutPrm->winInfo[winId];

            if(pWinInfo->chId >= pDmaSwMsObj->prevLinkQueInfo.numCh)
            {
                /* invalid CH ID, ignore window parameters */
                pWinInfo->chId = ALGORITHM_LINK_DMA_SW_MS_INVALID_CH_ID;
                continue;
            }

            if(pWinInfo->outStartX >= pLayoutPrm->outBufWidth)
            {
                /* window is completely outside the frame so mark the
                 * window channel ID as invalid
                 */
                pWinInfo->chId = ALGORITHM_LINK_DMA_SW_MS_INVALID_CH_ID;
            }

            if(pWinInfo->outStartY >= pLayoutPrm->outBufHeight)
            {
                /* window is completely outside the frame so mark the
                 * window channel ID as invalid
                 */
                pWinInfo->chId = ALGORITHM_LINK_DMA_SW_MS_INVALID_CH_ID;
            }

            if( (pWinInfo->outStartX + pWinInfo->width)
                        > pLayoutPrm->outBufWidth
                )
            {
                /* window is partially outside the frame so crop the window
                 * width
                 */
                pWinInfo->width = pLayoutPrm->outBufWidth - pWinInfo->outStartX;
            }

            if( (pWinInfo->outStartY + pWinInfo->height)
                    > pLayoutPrm->outBufHeight
               )
            {
                /* window is partially outside the frame so crop the window
                 * height
                 */
                pWinInfo->height = pLayoutPrm->outBufHeight
                                        - pWinInfo->outStartY;
            }

            if(pWinInfo->chId != ALGORITHM_LINK_DMA_SW_MS_INVALID_CH_ID)
            {
                pInChInfo = &pDmaSwMsObj->prevLinkQueInfo.chInfo
                                [pWinInfo->chId];


                if( (pInChInfo->startX + pWinInfo->inStartX) >= pInChInfo->width)
                {
                    /* window is completely outside the frame so mark the
                     * window channel ID as invalid
                     */
                    pWinInfo->chId = ALGORITHM_LINK_DMA_SW_MS_INVALID_CH_ID;
                }

                if( (pInChInfo->startY + pWinInfo->inStartY)
                            >= pInChInfo->height
                   )
                {
                    /* window is completely outside the frame so mark the
                     * window channel ID as invalid
                     */
                    pWinInfo->chId = ALGORITHM_LINK_DMA_SW_MS_INVALID_CH_ID;
                }

                if( (pInChInfo->startX + pWinInfo->inStartX + pWinInfo->width)
                        > pInChInfo->width
                    )
                {
                    /* window is partially outside the frame so crop the window
                     * width
                     */
                    pWinInfo->width = pInChInfo->width
                                        -
                                    (pInChInfo->startX + pWinInfo->inStartX)
                                      ;
                }

                if( (pInChInfo->startY + pWinInfo->inStartY + pWinInfo->height)
                        > pInChInfo->height
                    )
                {
                    /* window is partially outside the frame so crop the window
                     * width
                     */
                    pWinInfo->height= pInChInfo->height
                                        -
                                    (pInChInfo->startY + pWinInfo->inStartY)
                                      ;
                }
            }
        }
    }

    return isValid;
}

/**
 *******************************************************************************
 *
 * \brief Init link queue info
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pDmaSwMsObj       [IN] DMA SW Mosaic Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void AlgorithmLink_dmaSwMsInitQueueInfo(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj)
{
    AlgorithmLink_OutputQueueInfo outputQInfo;
    AlgorithmLink_InputQueueInfo  inputQInfo;
    UInt32 maxWidth;

    memset(&outputQInfo, 0, sizeof(outputQInfo));
    memset(&inputQInfo, 0, sizeof(inputQInfo));

    maxWidth = SystemUtils_align(pDmaSwMsObj->createArgs.maxOutBufWidth,
                            ALGORITHMLINK_FRAME_ALIGN);

    if(pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV422I_UYVY
        ||
        pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV422I_YUYV
    )
    {
        pDmaSwMsObj->outPitch[0] = maxWidth*2;
        pDmaSwMsObj->outPitch[1] = 0;
    }
    else
    if(pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV420SP_UV
        ||
        pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV420SP_VU
    )
    {
        pDmaSwMsObj->outPitch[0] = maxWidth;
        pDmaSwMsObj->outPitch[1] = maxWidth;
    }
    else
    {
        /* invalid data format */
        UTILS_assert(0);
    }
    /*
     * Populating parameters corresponding to Q usage of frame copy
     * algorithm link
     */
    inputQInfo.qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    outputQInfo.qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    outputQInfo.queInfo.numCh = 1;

    outputQInfo.queInfo.chInfo[0].flags = 0;

    outputQInfo.queInfo.chInfo[0].flags = System_Link_Ch_Info_Set_Flag_Data_Format(
        outputQInfo.queInfo.chInfo[0].flags,
        pDmaSwMsObj->dataFormat
        );

    outputQInfo.queInfo.chInfo[0].flags = System_Link_Ch_Info_Set_Flag_Mem_Type(
        outputQInfo.queInfo.chInfo[0].flags,
        SYSTEM_MT_NONTILEDMEM
        );

    outputQInfo.queInfo.chInfo[0].flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
        outputQInfo.queInfo.chInfo[0].flags,
        SYSTEM_SF_PROGRESSIVE
        );

    outputQInfo.queInfo.chInfo[0].flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
        outputQInfo.queInfo.chInfo[0].flags,
        SYSTEM_BUFFER_TYPE_VIDEO_FRAME
        );


    outputQInfo.queInfo.chInfo[0].startX = 0;
    outputQInfo.queInfo.chInfo[0].startY = 0;
    outputQInfo.queInfo.chInfo[0].width  =
            pDmaSwMsObj->createArgs.initLayoutParams.outBufWidth;
    outputQInfo.queInfo.chInfo[0].height =
            pDmaSwMsObj->createArgs.initLayoutParams.outBufHeight;

    outputQInfo.queInfo.chInfo[0].pitch[0] = pDmaSwMsObj->outPitch[0];
    outputQInfo.queInfo.chInfo[0].pitch[1] = pDmaSwMsObj->outPitch[1];

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                1,
                                &inputQInfo,
                                1,
                                &outputQInfo
                                );

}

/**
 *******************************************************************************
 *
 * \brief Alloc and queue output buffers
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void AlgorithmLink_dmaSwMsAllocAndQueueOutBuf(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj)
{
    Int32  frameId;
    UInt32 maxHeight;
    System_Buffer              * pSystemBuffer;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;

    UTILS_assert(
        pDmaSwMsObj->createArgs.initLayoutParams.outBufWidth <=
        pDmaSwMsObj->createArgs.maxOutBufWidth
        );

    UTILS_assert(
        pDmaSwMsObj->createArgs.initLayoutParams.outBufHeight <=
        pDmaSwMsObj->createArgs.maxOutBufHeight
        );

    maxHeight = SystemUtils_align(pDmaSwMsObj->createArgs.maxOutBufHeight, 2);

    if(pDmaSwMsObj->createArgs.numOutBuf>DMA_SWMS_LINK_MAX_OUT_BUF)
        pDmaSwMsObj->createArgs.numOutBuf = DMA_SWMS_LINK_MAX_OUT_BUF;

    pDmaSwMsObj->outBufSize = pDmaSwMsObj->outPitch[0] * maxHeight * 2;

    /*
     * Creation of output buffers for output buffer Q = 0 (Used)
     *  - Connecting video frame buffer to system buffer payload
     *  - Memory allocation for Luma and Chroma buffers
     *  - Put the buffer into empty queue
     */
    for(frameId = 0; frameId < pDmaSwMsObj->createArgs.numOutBuf; frameId++)
    {

        pSystemBuffer           = &(pDmaSwMsObj->buffers[frameId]);
        pSystemVideoFrameBuffer = &(pDmaSwMsObj->videoFrames[frameId]);

        memset(pSystemBuffer, 0, sizeof(*pSystemBuffer));
        memset(pSystemVideoFrameBuffer, 0, sizeof(*pSystemVideoFrameBuffer));

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemVideoFrameBuffer;
        pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->chNum       = 0;

        memset((void *)&pSystemVideoFrameBuffer->chInfo,
               0,
               sizeof(System_LinkChInfo));

        /*
         * Buffer allocation done for maxHeight, maxWidth and also assuming
         * worst case num planes = 2, for data Format YUV422
         */
        pSystemVideoFrameBuffer->bufAddr[0] =
                        Utils_memAlloc(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                ( pDmaSwMsObj->outBufSize ),
                                ALGORITHMLINK_FRAME_ALIGN
                            );

        /*
         * Carving out memory pointer for chroma which will get used in case of
         * SYSTEM_DF_YUV420SP_UV
         */
        pSystemVideoFrameBuffer->bufAddr[1] = (void*)(
            (UInt32) pSystemVideoFrameBuffer->bufAddr[0] +
            (UInt32)(maxHeight*pDmaSwMsObj->outPitch[0])
            );

        UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);

        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }
}

/**
 *******************************************************************************
 *
 * \brief Alloc line buffer used to fill output buffer when no input
 *        is available
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void AlgorithmLink_dmaSwMsAllocFillBufLine(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj)
{
    pDmaSwMsObj->dmaFillLineSize = pDmaSwMsObj->outPitch[0] * 2;

    pDmaSwMsObj->dmaFillLineAddr[0] =
                        Utils_memAlloc(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                ( pDmaSwMsObj->dmaFillLineSize ),
                                ALGORITHMLINK_FRAME_ALIGN
                            );
    pDmaSwMsObj->dmaFillLineAddr[1] =
        (Ptr)((UInt32)pDmaSwMsObj->dmaFillLineAddr[0]
            + pDmaSwMsObj->dmaFillLineSize)
            ;

    memset(pDmaSwMsObj->dmaFillLineAddr[0], 0x80, pDmaSwMsObj->dmaFillLineSize);

    Cache_wbInv(pDmaSwMsObj->dmaFillLineAddr[0],
                pDmaSwMsObj->dmaFillLineSize,
                Cache_Type_ALL,
                TRUE);
}

/**
 *******************************************************************************
 *
 * \brief Create DMA channel
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void AlgorithmLink_dmaSwMsCreateDmaCh(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj)
{
    Int32 status;
    UInt32 winId;
    Utils_DmaCopyFill2D *pDmaPrm;

    Utils_DmaChCreateParams_Init(&pDmaSwMsObj->dmaCreateArgs);

    pDmaSwMsObj->dmaCreateArgs.maxTransfers
        = ALGORITHM_LINK_DMA_SW_MS_MAX_WINDOWS;

    if(System_getSelfProcId()==SYSTEM_PROC_DSP1
        ||
        System_getSelfProcId()==SYSTEM_PROC_DSP2
        )
    {
        if(pDmaSwMsObj->createArgs.useLocalEdma)
        {
            pDmaSwMsObj->dmaCreateArgs.edmaInstId
                = UTILS_DMA_LOCAL_EDMA_INST_ID;
        }
    }

    status = Utils_dmaCreateCh(
                &pDmaSwMsObj->dmaChObj,
                &pDmaSwMsObj->dmaCreateArgs
                );

    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    /* set constant DMA copy/fill params */
    for( winId = 0; winId<ALGORITHM_LINK_DMA_SW_MS_MAX_WINDOWS; winId++)
    {
        pDmaPrm = &pDmaSwMsObj->dmaCopyPrms[winId];

        if(pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV422I_UYVY
            ||
            pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV422I_YUYV
        )
        {
            pDmaPrm->dataFormat    = SYSTEM_DF_RAW16;
        }
        else
        if(pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV420SP_UV
            ||
            pDmaSwMsObj->dataFormat==SYSTEM_DF_YUV420SP_VU
        )
        {
            pDmaPrm->dataFormat    = SYSTEM_DF_YUV420SP_UV;
        }

        pDmaPrm->destAddr[0]   = NULL;
        pDmaPrm->destAddr[1]   = NULL;
        pDmaPrm->destPitch[0]  = pDmaSwMsObj->outPitch[0];
        pDmaPrm->destPitch[1]  = pDmaSwMsObj->outPitch[1];
        pDmaPrm->destStartX    = 0;
        pDmaPrm->destStartY    = 0;
        pDmaPrm->width         = 0;
        pDmaPrm->height        = 0;
        pDmaPrm->srcAddr[0]    = NULL;
        pDmaPrm->srcAddr[1]    = NULL;
        pDmaPrm->srcPitch[0]   = 0;
        pDmaPrm->srcPitch[1]   = 0;
        pDmaPrm->srcStartX     = 0;
        pDmaPrm->srcStartY     = 0;
    }

    pDmaPrm = &pDmaSwMsObj->dmaFillPrms;

    pDmaPrm->dataFormat    = pDmaSwMsObj->dmaCopyPrms[0].dataFormat;
    pDmaPrm->destAddr[0]   = NULL;
    pDmaPrm->destAddr[1]   = NULL;
    pDmaPrm->destPitch[0]  = pDmaSwMsObj->outPitch[0];
    pDmaPrm->destPitch[1]  = pDmaSwMsObj->outPitch[1];
    pDmaPrm->destStartX    = 0;
    pDmaPrm->destStartY    = 0;
    pDmaPrm->width         = 0;
    pDmaPrm->height        = 0;
    pDmaPrm->srcAddr[0]    = pDmaSwMsObj->dmaFillLineAddr[0];
    pDmaPrm->srcAddr[1]    = pDmaSwMsObj->dmaFillLineAddr[1];
    pDmaPrm->srcPitch[0]   = pDmaSwMsObj->dmaFillLineSize;
    pDmaPrm->srcPitch[1]   = pDmaSwMsObj->dmaFillLineSize;
    pDmaPrm->srcStartX     = 0;
    pDmaPrm->srcStartY     = 0;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for this algorithm
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_dmaSwMsCreate(void * pObj, void * pCreateParams)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo              prevLinkInfo;
    UInt32                       prevLinkQueId;

    AlgorithmLink_DmaSwMsObj          * pDmaSwMsObj;
    AlgorithmLink_DmaSwMsCreateParams * pDmaSwMsCreateParams;

    pDmaSwMsCreateParams =
        (AlgorithmLink_DmaSwMsCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pDmaSwMsObj = (AlgorithmLink_DmaSwMsObj *)
                        malloc(sizeof(AlgorithmLink_DmaSwMsObj));

    UTILS_assert(pDmaSwMsObj!=NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pDmaSwMsObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    pDmaSwMsObj->createArgs = *pDmaSwMsCreateParams;

    /*
     * Channel info of current link will be obtained from previous link.
     */
    status = System_linkGetInfo(pDmaSwMsObj->createArgs.inQueParams.prevLinkId,
                                &prevLinkInfo);

    prevLinkQueId = pDmaSwMsObj->createArgs.inQueParams.prevLinkQueId;

    UTILS_assert(prevLinkQueId < prevLinkInfo.numQue);

    pDmaSwMsObj->prevLinkQueInfo = prevLinkInfo.queInfo[prevLinkQueId];

    /* assuming data format will be same for all channels and hence taking
     * CH0 data format
     */
    pDmaSwMsObj->dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
                    pDmaSwMsObj->prevLinkQueInfo.chInfo[0].flags);

    pDmaSwMsObj->isLayoutSwitch = TRUE;
    pDmaSwMsObj->curLayoutPrm = pDmaSwMsObj->createArgs.initLayoutParams;

    if( !AlgorithmLink_dmaSwMsIsLayoutPrmValid(
                    pObj,
                    pDmaSwMsObj,
                    &pDmaSwMsObj->curLayoutPrm)
        )
    {
        Vps_printf(" DMA_SWMS: Invalid SW Mosaic parameters !!!\n");
        UTILS_assert(0);
    }

    AlgorithmLink_dmaSwMsInitQueueInfo(pObj, pDmaSwMsObj);
    AlgorithmLink_dmaSwMsAllocAndQueueOutBuf(pObj, pDmaSwMsObj);
    AlgorithmLink_dmaSwMsAllocFillBufLine(pObj, pDmaSwMsObj);
    AlgorithmLink_dmaSwMsCreateDmaCh(pObj, pDmaSwMsObj);

    pDmaSwMsObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_DMA_SWMS");
    UTILS_assert(NULL != pDmaSwMsObj->linkStatsInfo);

    pDmaSwMsObj->isFirstFrameRecv = FALSE;

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Check if input buffer is valid or not
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pDmaSwMsObj       [IN] DMA SW Mosaic object handle
 * \param  pBuffer           [IN] Input buffer handle
 *
 * \return  TRUE, valid input buffer, FALSE, invalid input buffer
 *
 *******************************************************************************
 */
Bool AlgorithmLink_dmaSwMsIsInputBufValid(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj,
                    System_Buffer *pBuffer
                    )
{
    Bool isValid = TRUE;

    if(pBuffer==NULL)
    {
        isValid = FALSE;
    }
    else if(pBuffer->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER
        ||
       pBuffer->chNum > 0
        ||
       pBuffer->payloadSize != sizeof(System_VideoFrameCompositeBuffer)
        ||
       pBuffer->payload == NULL
       )
    {
        isValid = FALSE;
    }

    return isValid;
}

/**
 *******************************************************************************
 *
 * \brief Check and fill output buffer with bank color is required
 *
 * \param  pObj                     [IN] Algorithm link object handle
 * \param  pDmaSwMsObj              [IN] DMA SW Mosaic object handle
 * \param  pOutFrameBuffer          [IN] Output frame buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_dmaSwMsDoDmaFill(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj,
                    System_VideoFrameBuffer *pOutFrameBuffer
                    )
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_DmaSwMsLayoutParams *pLayoutPrm;
    Utils_DmaCopyFill2D *pDmaPrm;

    pLayoutPrm = &pDmaSwMsObj->curLayoutPrm;

    if(pDmaSwMsObj->isLayoutSwitch)
    {
        /* Layout switch occured, there could be regions in the output buffer
         * where no input is present, hence clear the full output
         * buffer before copying input from output.
         * This needs to be done only pDmaSwMsObj->createArgs.numOutBuf
         * times
         */
        pDmaSwMsObj->isLayoutSwitch = FALSE;
        pDmaSwMsObj->doFillBuf = pDmaSwMsObj->createArgs.numOutBuf;
    }

    if(pDmaSwMsObj->doFillBuf)
    {
        pDmaSwMsObj->doFillBuf--;

        /* fill complete output buffer with blank color */
        pDmaPrm = &pDmaSwMsObj->dmaFillPrms;

        pDmaPrm->destAddr[0]   = pOutFrameBuffer->bufAddr[0];
        pDmaPrm->destAddr[1]   = pOutFrameBuffer->bufAddr[1];
        pDmaPrm->width         = pLayoutPrm->outBufWidth;
        pDmaPrm->height        = pLayoutPrm->outBufHeight;

        status = Utils_dmaFill2D(
                &pDmaSwMsObj->dmaChObj,
                &pDmaSwMsObj->dmaFillPrms,
                1
                );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Copy data from input into output based on layout parameters
 *
 * \param  pObj                     [IN] Algorithm link object handle
 * \param  pDmaSwMsObj              [IN] DMA SW Mosaic object handle
 * \param  pInFrameCompositeBuffer  [IN] Input composite buffer
 * \param  pOutFrameBuffer          [IN] Output frame buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_dmaSwMsDoDmaCopyFill(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj,
                    System_VideoFrameCompositeBuffer *pInFrameCompositeBuffer,
                    System_VideoFrameBuffer *pOutFrameBuffer
                    )
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_DmaSwMsLayoutParams *pLayoutPrm;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;
    Utils_DmaCopyFill2D *pDmaPrm;
    System_LinkChInfo *pInChInfo;
    UInt32 numDmaCopy, winId;

    AlgorithmLink_dmaSwMsDoDmaFill(pObj, pDmaSwMsObj, pOutFrameBuffer);

    pLayoutPrm = &pDmaSwMsObj->curLayoutPrm;

    numDmaCopy = 0;
    for(winId=0; winId<pLayoutPrm->numWin; winId++)
    {
        pWinInfo = &pLayoutPrm->winInfo[winId];

        if(pWinInfo->chId >= pInFrameCompositeBuffer->numFrames
            ||
           pWinInfo->chId >= pDmaSwMsObj->prevLinkQueInfo.numCh
            )
        {
            /* invalid CH ID, ignore any copy */
            continue;
        }

        pDmaPrm = &pDmaSwMsObj->dmaCopyPrms[numDmaCopy];

        pDmaPrm->destAddr[0]   = pOutFrameBuffer->bufAddr[0];
        pDmaPrm->destAddr[1]   = pOutFrameBuffer->bufAddr[1];
        pDmaPrm->destStartX    = pWinInfo->outStartX;
        pDmaPrm->destStartY    = pWinInfo->outStartY;
        pDmaPrm->width         = pWinInfo->width;
        pDmaPrm->height        = pWinInfo->height;

        pDmaPrm->srcAddr[0]
            = pInFrameCompositeBuffer->bufAddr[0][pWinInfo->chId];
        pDmaPrm->srcAddr[1]
            = pInFrameCompositeBuffer->bufAddr[1][pWinInfo->chId];

        UTILS_assert(pDmaPrm->srcAddr[0]!=NULL);

        pInChInfo = &pDmaSwMsObj->prevLinkQueInfo.chInfo[pWinInfo->chId];

        pDmaPrm->srcPitch[0] = pInChInfo->pitch[0];
        pDmaPrm->srcPitch[1] = pInChInfo->pitch[1];

        pDmaPrm->srcStartX   = pInChInfo->startX + pWinInfo->inStartX;
        pDmaPrm->srcStartY   = pInChInfo->startY + pWinInfo->inStartY;

        numDmaCopy++;
    }

    if(numDmaCopy)
    {
        status = Utils_dmaCopy2D(
                &pDmaSwMsObj->dmaChObj,
                &pDmaSwMsObj->dmaCopyPrms[0],
                numDmaCopy
                );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for this algorithm
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_dmaSwMsProcess(void * pObj)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;

    AlgorithmLink_DmaSwMsObj  *pDmaSwMsObj;
    System_BufferList          inputBufList;
    System_BufferList          outputBufListReturn;
    System_Buffer             *pInBuffer;
    System_Buffer             *pOutBuffer;
    System_VideoFrameBuffer   *pOutFrameBuffer;
    System_VideoFrameCompositeBuffer *pInFrameCompositeBuffer;
    UInt32 bufId;
    Bool  bufDropFlag[SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST];
    System_LinkStatistics      * linkStatsInfo;

    pDmaSwMsObj = (AlgorithmLink_DmaSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    UTILS_assert(pDmaSwMsObj!=NULL);

    linkStatsInfo = pDmaSwMsObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(
            pDmaSwMsObj->createArgs.inQueParams.prevLinkId,
            pDmaSwMsObj->createArgs.inQueParams.prevLinkQueId,
            &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pDmaSwMsObj->isFirstFrameRecv==FALSE)
        {
            pDmaSwMsObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pDmaSwMsObj->prevLinkQueInfo.numCh,
                    1);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for(bufId=0; bufId<inputBufList.numBuf; bufId++)
        {
            pInBuffer = inputBufList.buffers[bufId];

            if( ! AlgorithmLink_dmaSwMsIsInputBufValid(
                            pObj,
                            pDmaSwMsObj,
                            pInBuffer
                            )
                )
            {
                bufDropFlag[bufId] = TRUE;

                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            linkStatsInfo->linkStats.chStats[pInBuffer->chNum].inBufRecvCount++;

            status = AlgorithmLink_getEmptyOutputBuffer(
                                pObj,
                                0,
                                0,
                                &pOutBuffer
                                );

            if(status != SYSTEM_LINK_STATUS_SOK
                ||
                pOutBuffer == NULL
                )
            {

                linkStatsInfo->linkStats.outBufErrorCount++;
                linkStatsInfo->linkStats.chStats
                        [pInBuffer->chNum].inBufDropCount++;
                linkStatsInfo->linkStats.chStats
                        [pInBuffer->chNum].outBufDropCount[0]++;

                bufDropFlag[bufId] = TRUE;
                continue;
            }

            pOutBuffer->srcTimestamp = pInBuffer->srcTimestamp;
            pOutBuffer->frameId = pInBuffer->frameId;
            pOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

            bufDropFlag[bufId] = FALSE;
            pOutFrameBuffer = (System_VideoFrameBuffer*)pOutBuffer->payload;

            pInFrameCompositeBuffer = (System_VideoFrameCompositeBuffer*)
                                            pInBuffer->payload;

            linkStatsInfo->linkStats.chStats
                    [pInBuffer->chNum].inBufProcessCount++;
            linkStatsInfo->linkStats.chStats
                    [pInBuffer->chNum].outBufCount[0]++;

            AlgorithmLink_dmaSwMsDoDmaCopyFill(
                    pObj,
                    pDmaSwMsObj,
                    pInFrameCompositeBuffer,
                    pOutFrameBuffer
                    );

            Utils_updateLatency(&pDmaSwMsObj->linkLatency,
                                pOutBuffer->linkLocalTimestamp);
            Utils_updateLatency(&pDmaSwMsObj->srcToLinkLatency,
                                pOutBuffer->srcTimestamp);

            /*
             * Putting filled buffer into output full buffer Q
             */
            status = AlgorithmLink_putFullOutputBuffer(pObj,
                                                       0,
                                                       pOutBuffer);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            /*
             * Informing next link that a new data has peen put for its
             * processing
             */
            System_sendLinkCmd(pDmaSwMsObj->createArgs.outQueParams.nextLink,
                               SYSTEM_CMD_NEW_DATA,
                               NULL);

            /*
             * Releasing (Free'ing) output buffer, since algorithm does not
             * need it for any future usage.
             * In case of INPLACE computation, there is no need to free output
             * buffer, since it will be freed as input buffer.
             */
            outputBufListReturn.numBuf     = 1;
            outputBufListReturn.buffers[0] = pOutBuffer;

            AlgorithmLink_releaseOutputBuffer(pObj,
                                              0,
                                              &outputBufListReturn);
        }

        /* release input buffers */
        AlgorithmLink_releaseInputBuffer(
                    pObj,
                    0,
                    pDmaSwMsObj->createArgs.inQueParams.prevLinkId,
                    pDmaSwMsObj->createArgs.inQueParams.prevLinkQueId,
                    &inputBufList,
                    bufDropFlag
            );
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for this algorithm
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pControlParams    [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_dmaSwMsControl(void * pObj, void * pControlParams)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;
    AlgorithmLink_DmaSwMsLayoutParams *pLayoutPrm;
    AlgorithmLink_DmaSwMsObj  *pDmaSwMsObj;

    pDmaSwMsObj = (AlgorithmLink_DmaSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    UTILS_assert(pDmaSwMsObj!=NULL);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    switch(pAlgLinkControlPrm->controlCmd)
    {
        case ALGORITHM_LINK_DMA_SW_MS_CONFIG_CMD_SET_LAYOUT_PARAMS:

            if(pAlgLinkControlPrm->size != sizeof(*pLayoutPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pLayoutPrm = (AlgorithmLink_DmaSwMsLayoutParams *)
                                    pControlParams;

                if( ! AlgorithmLink_dmaSwMsIsLayoutPrmValid(
                        pObj,
                        pDmaSwMsObj,
                        pLayoutPrm)
                    )
                {
                    status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                    Vps_printf(" DMA_SWMS: Invalid SW Mosaic parameters !!!\n");
                }
                else
                {
                    pDmaSwMsObj->curLayoutPrm = *pLayoutPrm;
                    pDmaSwMsObj->isLayoutSwitch = TRUE;
                }
            }
            break;
        case ALGORITHM_LINK_DMA_SW_MS_CONFIG_CMD_GET_LAYOUT_PARAMS:

            if(pAlgLinkControlPrm->size != sizeof(*pLayoutPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pLayoutPrm = (AlgorithmLink_DmaSwMsLayoutParams *)
                                    pControlParams;

                *pLayoutPrm = pDmaSwMsObj->curLayoutPrm;

                pLayoutPrm->baseClassControl.size = sizeof(*pLayoutPrm);
                pLayoutPrm->baseClassControl.controlCmd
                        = ALGORITHM_LINK_DMA_SW_MS_CONFIG_CMD_GET_LAYOUT_PARAMS;
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_dmaSwMsPrintStatistics(pObj, pDmaSwMsObj);
            break;
        default:
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for this algorithm
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
Int32 AlgorithmLink_dmaSwMsStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for this algorithm
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_dmaSwMsDelete(void * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_DmaSwMsObj  *pDmaSwMsObj;
    System_VideoFrameBuffer   *pSystemVideoFrameBuffer;
    UInt32 frameId;

    pDmaSwMsObj = (AlgorithmLink_DmaSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    UTILS_assert(pDmaSwMsObj!=NULL);

    status = Utils_linkStatsCollectorDeAllocInst(pDmaSwMsObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* free DMA channel */
    status = Utils_dmaDeleteCh(&pDmaSwMsObj->dmaChObj);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    /* free memory */
    for(frameId = 0; frameId < pDmaSwMsObj->createArgs.numOutBuf; frameId++)
    {
        pSystemVideoFrameBuffer = &(pDmaSwMsObj->videoFrames[frameId]);

        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pSystemVideoFrameBuffer->bufAddr[0],
                    pDmaSwMsObj->outBufSize
                    );
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pDmaSwMsObj->dmaFillLineAddr[0],
                pDmaSwMsObj->dmaFillLineSize
                  );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    free(pDmaSwMsObj);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pDmaSwMsObj       [IN] DMA SW Mosaic Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_dmaSwMsPrintStatistics(void * pObj,
                    AlgorithmLink_DmaSwMsObj *pDmaSwMsObj)
{
    UTILS_assert(NULL != pDmaSwMsObj->linkStatsInfo);

    Utils_printLinkStatistics(&pDmaSwMsObj->linkStatsInfo->linkStats, "ALG_DMA_SWMS", TRUE);

    Utils_printLatency("ALG_DMA_SWMS",
                       &pDmaSwMsObj->linkStatsInfo->linkLatency,
                       &pDmaSwMsObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
