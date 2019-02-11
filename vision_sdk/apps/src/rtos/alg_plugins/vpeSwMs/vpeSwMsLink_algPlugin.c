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
#include "vpeSwMsLink_priv.h"

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
Int32 AlgorithmLink_VpeSwMs_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_VpeSwMsCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_VpeSwMsProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_VpeSwMsControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_VpeSwMsStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_VpeSwMsDelete;

    algId = ALGORITHM_LINK_IPU_ALG_VPE_SWMS;

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
 * \param  pVpeSwMsObj       [IN] DMA SW Mosaic Object handle
 *
 * \return  TRUE, valid parameters, FALSE, invalid parameters
 *
 *******************************************************************************
 */
Bool AlgorithmLink_VpeSwMsIsLayoutPrmValid(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj,
                    AlgorithmLink_VpeSwMsLayoutParams *pLayoutPrm
                    )
{
    Bool isValid = TRUE;
    AlgorithmLink_VpeSwMsLayoutWinInfo *pWinInfo;
    System_LinkChInfo *pInChInfo;
    UInt32 winId;

    /* if number of window > max possible then possibly some array overrun
     * occured hence, flag as in valid parameter
     */
    if(pLayoutPrm->numWin>ALGORITHM_LINK_VPE_SW_MS_MAX_WINDOWS)
        isValid = FALSE;

    /* limit output width x height to max buffer width x height */
    if(pLayoutPrm->outBufWidth > pVpeSwMsObj->createArgs.maxOutBufWidth)
    {
        pLayoutPrm->outBufWidth = pVpeSwMsObj->createArgs.maxOutBufWidth;
    }

    if(pLayoutPrm->outBufHeight > pVpeSwMsObj->createArgs.maxOutBufHeight)
    {
        pLayoutPrm->outBufHeight = pVpeSwMsObj->createArgs.maxOutBufHeight;
    }

    if(isValid)
    {
        /* crop input / output region if out of bounds */
        for(winId=0; winId<pLayoutPrm->numWin; winId++)
        {
            pWinInfo = &pLayoutPrm->winInfo[winId];

            if(pWinInfo->chId >= pVpeSwMsObj->prevLinkQueInfo.numCh)
            {
                /* invalid CH ID, ignore window parameters */
                pWinInfo->chId = ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID;
                continue;
            }

            if(pWinInfo->outStartX >= pLayoutPrm->outBufWidth)
            {
                /* window is completely outside the frame so mark the
                 * window channel ID as invalid
                 */
                pWinInfo->chId = ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID;
            }

            if(pWinInfo->outStartY >= pLayoutPrm->outBufHeight)
            {
                /* window is completely outside the frame so mark the
                 * window channel ID as invalid
                 */
                pWinInfo->chId = ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID;
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

            if(pWinInfo->chId != ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID)
            {
                pInChInfo = &pVpeSwMsObj->prevLinkQueInfo.chInfo
                                [pWinInfo->chId];


                if( (pInChInfo->startX + pWinInfo->inStartX) >= pInChInfo->width)
                {
                    /* window is completely outside the frame so mark the
                     * window channel ID as invalid
                     */
                    pWinInfo->chId = ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID;
                }

                if( (pInChInfo->startY + pWinInfo->inStartY)
                            >= pInChInfo->height
                   )
                {
                    /* window is completely outside the frame so mark the
                     * window channel ID as invalid
                     */
                    pWinInfo->chId = ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID;
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
 * \param  pVpeSwMsObj       [IN] DMA SW Mosaic Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void AlgorithmLink_VpeSwMsInitQueueInfo(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj)
{
    AlgorithmLink_OutputQueueInfo outputQInfo;
    AlgorithmLink_InputQueueInfo  inputQInfo;
    UInt32 maxWidth;

    memset(&outputQInfo, 0, sizeof(outputQInfo));
    memset(&inputQInfo, 0, sizeof(inputQInfo));

    maxWidth = SystemUtils_align(pVpeSwMsObj->createArgs.maxOutBufWidth,
                            ALGORITHMLINK_FRAME_ALIGN);

    if(pVpeSwMsObj->dataFormat==SYSTEM_DF_YUV422I_UYVY
        ||
        pVpeSwMsObj->dataFormat==SYSTEM_DF_YUV422I_YUYV
    )
    {
        pVpeSwMsObj->outPitch[0] = maxWidth*2;
        pVpeSwMsObj->outPitch[1] = 0;
    }
    else
    if(pVpeSwMsObj->dataFormat==SYSTEM_DF_YUV420SP_UV
        ||
        pVpeSwMsObj->dataFormat==SYSTEM_DF_YUV420SP_VU
    )
    {
        pVpeSwMsObj->outPitch[0] = maxWidth;
        pVpeSwMsObj->outPitch[1] = maxWidth;
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
        pVpeSwMsObj->dataFormat
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
            pVpeSwMsObj->createArgs.initLayoutParams.outBufWidth;
    outputQInfo.queInfo.chInfo[0].height =
            pVpeSwMsObj->createArgs.initLayoutParams.outBufHeight;

    outputQInfo.queInfo.chInfo[0].pitch[0] = pVpeSwMsObj->outPitch[0];
    outputQInfo.queInfo.chInfo[0].pitch[1] = pVpeSwMsObj->outPitch[1];

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

Void AlgorithmLink_VpeSwMsFillFrame(AlgorithmLink_VpeSwMsObj *pVpeSwMsObj, System_VideoFrameBuffer *pVideoFrame)
{

    Uint32 maxHeight;

    /*
     * Make unused portions of the screen black. In order to do so, the Y
     * plane must be 0x00's and the UV plane must be 0x80's.
     */
    maxHeight = SystemUtils_align(pVpeSwMsObj->createArgs.maxOutBufHeight, 2);
    memset(pVideoFrame->bufAddr[0], 0x00,
        (maxHeight*pVpeSwMsObj->outPitch[0]));
    memset(pVideoFrame->bufAddr[1], 0x80,
        pVpeSwMsObj->outBufSize - (maxHeight*pVpeSwMsObj->outPitch[0]));
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
Void AlgorithmLink_VpeSwMsAllocAndQueueOutBuf(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj)
{
    Int32  frameId;
    UInt32 maxHeight;
    System_Buffer              * pSystemBuffer;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;

    UTILS_assert(
        pVpeSwMsObj->createArgs.initLayoutParams.outBufWidth <=
        pVpeSwMsObj->createArgs.maxOutBufWidth
        );

    UTILS_assert(
        pVpeSwMsObj->createArgs.initLayoutParams.outBufHeight <=
        pVpeSwMsObj->createArgs.maxOutBufHeight
        );

    maxHeight = SystemUtils_align(pVpeSwMsObj->createArgs.maxOutBufHeight, 2);

    if(pVpeSwMsObj->createArgs.numOutBuf>VPE_SWMS_LINK_MAX_OUT_BUF)
        pVpeSwMsObj->createArgs.numOutBuf = VPE_SWMS_LINK_MAX_OUT_BUF;

    pVpeSwMsObj->outBufSize = pVpeSwMsObj->outPitch[0] * maxHeight * 2;

    /*
     * Creation of output buffers for output buffer Q = 0 (Used)
     *  - Connecting video frame buffer to system buffer payload
     *  - Memory allocation for Luma and Chroma buffers
     *  - Put the buffer into empty queue
     */
    for(frameId = 0; frameId < pVpeSwMsObj->createArgs.numOutBuf; frameId++)
    {

        pSystemBuffer           = &(pVpeSwMsObj->buffers[frameId]);
        pSystemVideoFrameBuffer = &(pVpeSwMsObj->videoFrames[frameId]);

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
                                ( pVpeSwMsObj->outBufSize ),
                                ALGORITHMLINK_FRAME_ALIGN
                            );

        /*
         * Carving out memory pointer for chroma which will get used in case of
         * SYSTEM_DF_YUV420SP_UV
         */
        pSystemVideoFrameBuffer->bufAddr[1] = (void*)(
            (UInt32) pSystemVideoFrameBuffer->bufAddr[0] +
            (UInt32)(maxHeight*pVpeSwMsObj->outPitch[0])
            );

        UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);

        AlgorithmLink_VpeSwMsFillFrame(pVpeSwMsObj,pSystemVideoFrameBuffer);
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
Void AlgorithmLink_VpeSwMsAllocFillBufLine(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj)
{
    pVpeSwMsObj->dmaFillLineSize = pVpeSwMsObj->outPitch[0] * 2;

    pVpeSwMsObj->dmaFillLineAddr[0] =
                        Utils_memAlloc(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                ( pVpeSwMsObj->dmaFillLineSize ),
                                ALGORITHMLINK_FRAME_ALIGN
                            );
    pVpeSwMsObj->dmaFillLineAddr[1] =
        (Ptr)((UInt32)pVpeSwMsObj->dmaFillLineAddr[0]
            + pVpeSwMsObj->dmaFillLineSize)
            ;

    memset(pVpeSwMsObj->dmaFillLineAddr[0], 0x80, pVpeSwMsObj->dmaFillLineSize);

    Cache_wbInv(pVpeSwMsObj->dmaFillLineAddr[0],
                pVpeSwMsObj->dmaFillLineSize,
                Cache_Type_ALL,
                TRUE);
}

Int32 AlgorithmLink_VpeSwMsInitFrame(AlgorithmLink_VpeSwMsObj *pVpeSwMsObj,
                                     FVID2_Frame *pFrame, System_Buffer *pBuffer,UInt32 chId)
{
    UInt32 idx, planes;
    System_VideoFrameCompositeBuffer *pVideoCompBuff;

    UTILS_assert(pBuffer != NULL);

    UTILS_assert(pBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER);

    pVideoCompBuff = (System_VideoFrameCompositeBuffer*) pBuffer->payload;

    UTILS_assert(UTILS_ARRAYSIZE(pVideoCompBuff->bufAddr[0]) >= UTILS_ARRAYSIZE(pFrame->addr[0]));

    memset(pFrame, 0, sizeof(FVID2_Frame));

    pFrame->chNum       = chId;
    pFrame->timeStamp   = pBuffer->linkLocalTimestamp;
    pFrame->appData     = pBuffer;
    pFrame->fid = FVID2_FID_FRAME;

    planes = UTILS_ARRAYSIZE(pFrame->addr[0]);

    for (idx = 0; idx < planes; idx++)
    {
        pFrame->addr[0][idx] = pVideoCompBuff->bufAddr[idx][chId];
    }

    pFrame->addr[0][0] = (Void*)((UInt32) pVideoCompBuff->bufAddr[0][chId] +
                         ((pVpeSwMsObj->prevLinkQueInfo.chInfo[0].pitch[0] * pVpeSwMsObj->prevLinkQueInfo.chInfo[0].startY) +
                           pVpeSwMsObj->prevLinkQueInfo.chInfo[0].startX));

    pFrame->addr[0][1] = (Void*)((UInt32) pVideoCompBuff->bufAddr[1][chId] +
                         ((pVpeSwMsObj->prevLinkQueInfo.chInfo[0].pitch[1] * pVpeSwMsObj->prevLinkQueInfo.chInfo[0].startY / 2)
                         + pVpeSwMsObj->prevLinkQueInfo.chInfo[0].startX));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *  AlgorithmLink_VpeSwMsUpdateProcList
 *  Updates the process list with the next request buffer information.
 */
Void AlgorithmLink_VpeSwMsCreateProcListBuff(AlgorithmLink_VpeSwMsObj     *pObj,
                                     Fvid2_ProcessList *pList)
{
    UInt32 ch = 0;
    Fvid2_Frame     *pInFrame;
    Fvid2_Frame     *pOutFrame;

    Fvid2ProcessList_init(pList);

    pList->inFrameList[0U] = &pObj->frameList[0];
    pList->outFrameList[0U] = &pObj->frameList[1];
    pList->numInLists       = 1U;
    pList->numOutLists      = 1U;

    Fvid2FrameList_init(pList->inFrameList[0U]);

    for (ch = 0; ch < pObj->createArgs.numInputCh; ch++)
    {
        pInFrame                = &pObj->frames[0][ch];
        pList->inFrameList[0U]->frames[ch] = pInFrame;
        Fvid2Frame_init(pList->inFrameList[0U]->frames[ch]);
        pInFrame->fid           = FVID2_FID_FRAME;
        pInFrame->chNum         = ch;

        pOutFrame               = &pObj->frames[1][ch];
        pList->outFrameList[0U]->frames[ch] = pOutFrame;
        Fvid2Frame_init(pList->outFrameList[0U]->frames[ch]);
    }
    pList->outFrameList[0U]->numFrames = pObj->createArgs.numInputCh;
    pList->inFrameList[0U]->numFrames = pObj->createArgs.numInputCh;


}



/**
 *******************************************************************************
 *
 * \brief Function to create the VPE link channel object
 *
 *        Create the VPE link channel object, one per input channel
 *        - Create the intermediate buffer queue per channel
 *        - Create the intermediate Fvid2 frame freeQ
 *        - Updates the create time SC crop parameters
 *        - Populates the VPS driver create and control parameters
 *
 * \param   pObj     [IN] VPE Link Instance handle
 * \param   chId     [IN] channel number
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMsdrvCreateChObj(AlgorithmLink_VpeSwMsObj * pObj, UInt32 chId)
{
    AlgorithmLink_VpeSwMsChObj *pChObj;
    System_LinkChInfo *pInChInfo;
    Vps_M2mVpeParams *pDrvChParams;
    FVID2_Format *pFormat;

    UTILS_assert((Bool)(chId < pObj->createArgs.numInputCh));

    pChObj = &pObj->chObj[chId];
    pInChInfo = &pObj->prevLinkQueInfo.chInfo[chId];

    pDrvChParams = &pObj->drvChArgs[chId];
    VpsM2mVpeParams_init(pDrvChParams);

    pDrvChParams->chNum = chId;

    pFormat = &pDrvChParams->inFmt;

    pFormat->chNum = chId;
    pFormat->width = pInChInfo->width;
    pFormat->height = pInChInfo->height;

    pFormat->fieldMerged[0] = (UInt32)FALSE;
    pFormat->fieldMerged[1] = pFormat->fieldMerged[0];
    pFormat->fieldMerged[2] = pFormat->fieldMerged[0];
    pFormat->pitch[0] = pInChInfo->pitch[0];
    pFormat->pitch[1] = pInChInfo->pitch[1];
    pFormat->pitch[2] = pInChInfo->pitch[2];
    pFormat->dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(pInChInfo->flags);
    pFormat->scanFormat = System_Link_Ch_Info_Get_Flag_Scan_Format(pInChInfo->flags);
    pFormat->bpp = FVID2_BPP_BITS16;

    pFormat->reserved = NULL;

    pDrvChParams->inMemType = System_Link_Ch_Info_Get_Flag_Mem_Type(pInChInfo->flags);
    pDrvChParams->outMemType = VPS_VPDMA_MT_NONTILEDMEM;

    pFormat = &pDrvChParams->outFmt;

    pFormat->bpp = FVID2_BPP_BITS16;
    pFormat->chNum = chId;
    pFormat->width = pObj->createArgs.chParams[chId].outParams[0].width;
    pFormat->height = pObj->createArgs.chParams[chId].outParams[0].height;

    pFormat->pitch[0] = pInChInfo->width;
    pFormat->pitch[1] = pInChInfo->width;
    pFormat->fieldMerged[1] = FALSE;
    pFormat->fieldMerged[2] = FALSE;
    pFormat->dataFormat = FVID2_DF_YUV420SP_UV;

    pChObj->deiRtCfg.resetDei = FALSE;
    pChObj->deiRtCfg.fldRepeat = FALSE;
    pDrvChParams->scCfg.bypass = FALSE;
    pDrvChParams->scCfg.nonLinear = FALSE;
    pDrvChParams->scCfg.stripSize = 0;
    pDrvChParams->scCfg.enablePeaking = TRUE;
    pDrvChParams->scCfg.enableEdgeDetect = TRUE;
    pDrvChParams->scCfg.advCfg = NULL;

    pDrvChParams->scCropCfg.cropStartX = pObj->createArgs.chParams[chId].scCropCfg.cropStartX;
    pDrvChParams->scCropCfg.cropStartY = pObj->createArgs.chParams[chId].scCropCfg.cropStartY;
    pDrvChParams->scCropCfg.cropWidth = pObj->createArgs.chParams[chId].scCropCfg.cropWidth;
    pDrvChParams->scCropCfg.cropHeight = pObj->createArgs.chParams[chId].scCropCfg.cropHeight;

    Vps_printf("CH%d: IN:%d x %d (%d, %d), OUT:%d x %d (%d, %d)\r\n", chId,
        pInChInfo->width, pInChInfo->height, pInChInfo->pitch[0], pInChInfo->pitch[1],
        pFormat->width, pFormat->height, pFormat->pitch[0], pFormat->pitch[1]);



    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief This is the Call back function registered with VPE driver
 *
 *        This call back function will be invoked by VPE driver once it
 *        processed the frames from a FVID2_frame list
 *
 * \param  handle    [IN] VPE driver handle
 * \param  appData   [IN] Set with link instance handle address
 * \param  reserved  [IN] Not used
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMsdrvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved)
{
    AlgorithmLink_VpeSwMsObj *pObj = (AlgorithmLink_VpeSwMsObj *) appData;

    BspOsal_semPost(pObj->complete);

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This is the Error Call back function registered with VPE driver
 *
 *        This call back function will be invoked by driver once the
 *        processed frames from a FVID2_frame list are in error state
 *
 * \param  handle    [IN] VPE driver handle
 * \param  appData   [IN] Set with link instance handle address
 * \param  errList   [IN] Set with link instance handle address
 * \param  reserved  [IN] Not used
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMsdrvFvidErrCb(FVID2_Handle handle,
                           Ptr appData, Ptr errList, Ptr reserved)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Function to set the scalar coefficients
 *
 *        Check the input and output resolution and set the appropriate
 *        scalar coefficients. Also Program VPE scalar with these coefficients
 *
 * \param   pObj     [IN] VPE Link Instance handle
 *
 * \return  retVal   [OUT] return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMsdrvSetScCoeffs(AlgorithmLink_VpeSwMsObj * pObj)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    Vps_ScCoeffParams coeffPrms;

    VpsScCoeffParams_init(&coeffPrms);
    coeffPrms.scalerId    = VPS_M2M_VPE_SCALER_ID_SC0;

    if (pObj->loadUpsampleCoeffs)
    {
        Vps_printf(" VPE: Loading Up-scaling Co-effs\n");

        coeffPrms.hScalingSet = VPS_SC_US_SET;
        coeffPrms.vScalingSet = VPS_SC_US_SET;
    }
    else
    {
        Vps_printf(" VPE: Loading Down-scaling Co-effs\n");

        coeffPrms.hScalingSet = VPS_SC_DS_SET_8_16;
        coeffPrms.vScalingSet = VPS_SC_DS_SET_8_16;
    }

    /* Program VPE scalar coefficient - Always used */
    retVal = FVID2_control(pObj->fvidHandle,
                           IOCTL_VPS_SET_COEFFS, &coeffPrms, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

    Vps_printf(" VPE: Co-effs Loading ... DONE !!!\n");

    return (retVal);
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
Int32 AlgorithmLink_VpeSwMsCreate(void * pObj, void * pCreateParams)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo              prevLinkInfo;
    UInt32                       prevLinkQueId;
    FVID2_CbParams cbParams;
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;

    AlgorithmLink_VpeSwMsObj          * pVpeSwMsObj;
    AlgorithmLink_VpeSwMsCreateParams * pVpeSwMsCreateParams;

    pVpeSwMsCreateParams =
        (AlgorithmLink_VpeSwMsCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pVpeSwMsObj = (AlgorithmLink_VpeSwMsObj *)
                        malloc(sizeof(AlgorithmLink_VpeSwMsObj));

    UTILS_assert(pVpeSwMsObj!=NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pVpeSwMsObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    pVpeSwMsObj->createArgs = *pVpeSwMsCreateParams;

    /*
     * Channel info of current link will be obtained from previous link.
     */
    status = System_linkGetInfo(pVpeSwMsObj->createArgs.inQueParams.prevLinkId,
                                &prevLinkInfo);

    prevLinkQueId = pVpeSwMsObj->createArgs.inQueParams.prevLinkQueId;

    UTILS_assert(prevLinkQueId < prevLinkInfo.numQue);

    pVpeSwMsObj->prevLinkQueInfo = prevLinkInfo.queInfo[prevLinkQueId];

    /* assuming data format will be same for all channels and hence taking
     * CH0 data format
     */
    pVpeSwMsObj->dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
                    pVpeSwMsObj->prevLinkQueInfo.chInfo[0].flags);

    pVpeSwMsObj->isLayoutSwitch = TRUE;
    pVpeSwMsObj->curLayoutPrm = pVpeSwMsObj->createArgs.initLayoutParams;

    if( !AlgorithmLink_VpeSwMsIsLayoutPrmValid(
                    pObj,
                    pVpeSwMsObj,
                    &pVpeSwMsObj->curLayoutPrm)
        )
    {
        Vps_printf(" DMA_SWMS: Invalid SW Mosaic parameters !!!\n");
        UTILS_assert(0);
    }

    AlgorithmLink_VpeSwMsInitQueueInfo(pObj, pVpeSwMsObj);
    AlgorithmLink_VpeSwMsAllocAndQueueOutBuf(pObj, pVpeSwMsObj);
    AlgorithmLink_VpeSwMsAllocFillBufLine(pObj, pVpeSwMsObj);

    pVpeSwMsObj->loadUpsampleCoeffs = (Bool)FALSE;

    /* Create semaphores */
    pVpeSwMsObj->complete = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(pVpeSwMsObj->complete != NULL);

    VpsM2mCreateParams_init(&pVpeSwMsObj->drvCreateArgs);
    pVpeSwMsObj->drvCreateArgs.numCh = pVpeSwMsObj->createArgs.numInputCh;
    pVpeSwMsObj->drvCreateArgs.isDeiFmdEnable = FALSE;
    pVpeSwMsObj->drvCreateArgs.chInQueueLength = VPS_M2M_DEF_QUEUE_LEN_PER_CH;


    UInt32 ch = 0;
    for (ch = 0; ch < pVpeSwMsObj->createArgs.numInputCh; ch++)
    {
        AlgorithmLink_VpeSwMsdrvCreateChObj(pVpeSwMsObj, ch);
    }


    AlgorithmLink_VpeSwMsCreateProcListBuff(pVpeSwMsObj,&pVpeSwMsObj->processList);

    memset(&cbParams, 0, sizeof(cbParams));

    cbParams.cbFxn = &AlgorithmLink_VpeSwMsdrvFvidCb;
    cbParams.errCbFxn = &AlgorithmLink_VpeSwMsdrvFvidErrCb;
    cbParams.errList = &pVpeSwMsObj->errProcessList;
    cbParams.appData = pVpeSwMsObj;

    pVpeSwMsObj->fvidHandle = FVID2_create(FVID2_VPS_M2M_DRV,
                                    VPS_M2M_INST_VPE1,
                                    &pVpeSwMsObj->drvCreateArgs,
                                    &pVpeSwMsObj->drvCreateStatus, &cbParams);



    UTILS_assert(pVpeSwMsObj->fvidHandle != NULL);

    for (ch = 0; ch < pVpeSwMsObj->createArgs.numInputCh; ch++)
    {
        /* Set VPE params */
        retVal = Fvid2_control(pVpeSwMsObj->fvidHandle,
                               IOCTL_VPS_M2M_SET_VPE_PARAMS,
                               &pVpeSwMsObj->drvChArgs[ch], NULL);
        UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    }

    AlgorithmLink_VpeSwMsdrvSetScCoeffs(pVpeSwMsObj);

    pVpeSwMsObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_VPE_SWMS");
    UTILS_assert(NULL != pVpeSwMsObj->linkStatsInfo);

    pVpeSwMsObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Check if input buffer is valid or not
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pVpeSwMsObj       [IN] DMA SW Mosaic object handle
 * \param  pBuffer           [IN] Input buffer handle
 *
 * \return  TRUE, valid input buffer, FALSE, invalid input buffer
 *
 *******************************************************************************
 */
Bool AlgorithmLink_VpeSwMsIsInputBufValid(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj,
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

Int32 AlgorithmLink_VpeSwMsInitOutFrame(AlgorithmLink_VpeSwMsObj *pVpeSwMsObj,
                                        FVID2_Frame *pFrame,
                                        System_Buffer *pBuffer,
                                        UInt32 winId)
{
    UInt32 bufferWidth = 0;
    System_VideoFrameBuffer *pVideoFrame;
    AlgorithmLink_VpeSwMsLayoutWinInfo *pWinInfo;

    UInt32 winStartX,winStartY;

    UTILS_assert(pBuffer != NULL);

    UTILS_assert((pBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME) ||
            (pBuffer->bufType == SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME));

    pVideoFrame = pBuffer->payload;
    UTILS_assert(pVideoFrame != NULL);

    UTILS_assert(UTILS_ARRAYSIZE(pVideoFrame->bufAddr) >= UTILS_ARRAYSIZE(pFrame->addr[0]));

    memset(pFrame, 0, sizeof(FVID2_Frame));

    pFrame->chNum       = pBuffer->chNum;
    pFrame->timeStamp   = pBuffer->linkLocalTimestamp;
    pFrame->appData     = pBuffer;
    pFrame->fid = System_Video_Frame_Get_Flag_Fid(pVideoFrame->flags);
    pWinInfo = &pVpeSwMsObj->curLayoutPrm.winInfo[winId];
    winStartX = pWinInfo->outStartX;
    winStartY = pWinInfo->outStartY;
    bufferWidth = pVpeSwMsObj->curLayoutPrm.outBufWidth;

    pFrame->addr[0][0] = (Void*)((UInt32)pVideoFrame->bufAddr[0] + winStartX + (bufferWidth * winStartY));
    pFrame->addr[0][1] = (Void*)((UInt32)pVideoFrame->bufAddr[1] + winStartX + (bufferWidth/2 * winStartY));

    return SYSTEM_LINK_STATUS_SOK;
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
Int32 AlgorithmLink_VpeSwMsProcess(void * pObj)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;

    AlgorithmLink_VpeSwMsObj  *pVpeSwMsObj;
    System_BufferList          inputBufList;
    System_BufferList          outputBufListReturn;
    System_Buffer             *pInBuffer;
    System_Buffer             *pOutBuffer;
    Fvid2_Frame     *pInFrame;
    Fvid2_Frame     *pOutFrame;

    UInt32 bufId;
    UInt32 chId;
    UInt32 winId = 0;
    Bool  bufDropFlag[SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST];
    System_LinkStatistics       *linkStatsInfo;

    pVpeSwMsObj = (AlgorithmLink_VpeSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    UTILS_assert(pVpeSwMsObj!=NULL);

    linkStatsInfo = pVpeSwMsObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(
            pVpeSwMsObj->createArgs.inQueParams.prevLinkId,
            pVpeSwMsObj->createArgs.inQueParams.prevLinkQueId,
            &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pVpeSwMsObj->isFirstFrameRecv==FALSE)
        {
            pVpeSwMsObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pVpeSwMsObj->prevLinkQueInfo.numCh,
                    1);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for(bufId=0; bufId<inputBufList.numBuf; bufId++)
        {
            pInBuffer = inputBufList.buffers[bufId];

            if( ! AlgorithmLink_VpeSwMsIsInputBufValid(
                            pObj,
                            pVpeSwMsObj,
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

            linkStatsInfo->linkStats.chStats
                    [pInBuffer->chNum].inBufProcessCount++;
            linkStatsInfo->linkStats.chStats
                    [pInBuffer->chNum].outBufCount[0]++;

            for(winId = 0 ; winId < pVpeSwMsObj->createArgs.numInputCh; winId++)
            {
                chId = pVpeSwMsObj->curLayoutPrm.winInfo[winId].chId;
                pInFrame = &pVpeSwMsObj->frames[0][winId];
                pVpeSwMsObj->processList.inFrameList[0U]->frames[winId] = pInFrame;

                AlgorithmLink_VpeSwMsInitFrame(pVpeSwMsObj, pInFrame, pInBuffer,chId);

                pOutFrame = pVpeSwMsObj->processList.outFrameList[0U]->frames[winId];
                AlgorithmLink_VpeSwMsInitOutFrame(pVpeSwMsObj,pOutFrame, pOutBuffer,chId);
                pOutFrame->fid = FVID2_FID_FRAME;

            }
            pVpeSwMsObj->processList.inFrameList[0U]->numFrames = pVpeSwMsObj->curLayoutPrm.numWin;
            pVpeSwMsObj->processList.outFrameList[0U]->numFrames = pVpeSwMsObj->curLayoutPrm.numWin;

            if(pVpeSwMsObj->curLayoutPrm.numWin > 0)
            {
                status = Fvid2_processFrames(pVpeSwMsObj->fvidHandle, &pVpeSwMsObj->processList);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                BspOsal_semWait(pVpeSwMsObj->complete, BSP_OSAL_WAIT_FOREVER);

                Fvid2_getProcessedFrames(
                                pVpeSwMsObj->fvidHandle,
                                &pVpeSwMsObj->processList,
                                FVID2_TIMEOUT_NONE);
            }

            Utils_updateLatency(&pVpeSwMsObj->linkLatency,
                                pOutBuffer->linkLocalTimestamp);
            Utils_updateLatency(&pVpeSwMsObj->srcToLinkLatency,
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
            System_sendLinkCmd(pVpeSwMsObj->createArgs.outQueParams.nextLink,
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
                    pVpeSwMsObj->createArgs.inQueParams.prevLinkId,
                    pVpeSwMsObj->createArgs.inQueParams.prevLinkQueId,
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

Int32 AlgorithmLink_VpeSwMsControl(void * pObj, void * pControlParams)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;
    AlgorithmLink_VpeSwMsLayoutParams *pLayoutPrm;
    AlgorithmLink_VpeSwMsObj  *pVpeSwMsObj;

    pVpeSwMsObj = (AlgorithmLink_VpeSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    UTILS_assert(pVpeSwMsObj!=NULL);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    switch(pAlgLinkControlPrm->controlCmd)
    {
        case ALGORITHM_LINK_VPE_SW_MS_CONFIG_CMD_SET_LAYOUT_PARAMS:

            if(pAlgLinkControlPrm->size != sizeof(*pLayoutPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pLayoutPrm = (AlgorithmLink_VpeSwMsLayoutParams *)
                                    pControlParams;

                if( ! AlgorithmLink_VpeSwMsIsLayoutPrmValid(
                        pObj,
                        pVpeSwMsObj,
                        pLayoutPrm)
                    )
                {
                    status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                    Vps_printf(" DMA_SWMS: Invalid SW Mosaic parameters !!!\n");
                }
                else
                {
                    pVpeSwMsObj->curLayoutPrm = *pLayoutPrm;
                    pVpeSwMsObj->isLayoutSwitch = TRUE;
                }
            }
            break;
        case ALGORITHM_LINK_VPE_SW_MS_CONFIG_CMD_GET_LAYOUT_PARAMS:

            if(pAlgLinkControlPrm->size != sizeof(*pLayoutPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pLayoutPrm = (AlgorithmLink_VpeSwMsLayoutParams *)
                                    pControlParams;

                *pLayoutPrm = pVpeSwMsObj->curLayoutPrm;

                pLayoutPrm->baseClassControl.size = sizeof(*pLayoutPrm);
                pLayoutPrm->baseClassControl.controlCmd
                        = ALGORITHM_LINK_VPE_SW_MS_CONFIG_CMD_GET_LAYOUT_PARAMS;
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_VpeSwMsPrintStatistics(pObj, pVpeSwMsObj);
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
Int32 AlgorithmLink_VpeSwMsStop(void * pObj)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_VpeSwMsObj  *pVpeSwMsObj;

    pVpeSwMsObj = (AlgorithmLink_VpeSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);
    if(pVpeSwMsObj->fvidHandle != NULL)
    {
        retVal = FVID2_stop(pVpeSwMsObj->fvidHandle, NULL);
    }
    return retVal;
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
Int32 AlgorithmLink_VpeSwMsDelete(void * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_VpeSwMsObj  *pVpeSwMsObj;
    System_VideoFrameBuffer   *pSystemVideoFrameBuffer;
    UInt32 frameId;

    pVpeSwMsObj = (AlgorithmLink_VpeSwMsObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    UTILS_assert(pVpeSwMsObj!=NULL);

    status = Utils_linkStatsCollectorDeAllocInst(pVpeSwMsObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* free memory */
    for(frameId = 0; frameId < pVpeSwMsObj->createArgs.numOutBuf; frameId++)
    {
        pSystemVideoFrameBuffer = &(pVpeSwMsObj->videoFrames[frameId]);

        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pSystemVideoFrameBuffer->bufAddr[0],
                    pVpeSwMsObj->outBufSize
                    );
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pVpeSwMsObj->dmaFillLineAddr[0],
                pVpeSwMsObj->dmaFillLineSize
                  );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = FVID2_delete(pVpeSwMsObj->fvidHandle, NULL);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete semaphores */
    BspOsal_semDelete(&pVpeSwMsObj->complete);

    free(pVpeSwMsObj);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pVpeSwMsObj       [IN] DMA SW Mosaic Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMsPrintStatistics(void * pObj,
                    AlgorithmLink_VpeSwMsObj *pVpeSwMsObj)
{
    UTILS_assert(NULL != pVpeSwMsObj->linkStatsInfo);

    Utils_printLinkStatistics(&pVpeSwMsObj->linkStatsInfo->linkStats, "ALG_DMA_SWMS", TRUE);

    Utils_printLatency("ALG_DMA_SWMS",
                       &pVpeSwMsObj->linkStatsInfo->linkLatency,
                       &pVpeSwMsObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
