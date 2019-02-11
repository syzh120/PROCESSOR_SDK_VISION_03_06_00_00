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
 * \file imagePreProcessLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for filter 2D
 *         Link
 *
 * \version 0.0 (Nov 2015) : [YM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "imagePreProcessLink_priv.h"


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ALG_IMG_PREPROCESS_BUFFER_ALIGN    (32U)
/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of gAlign algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imagePreProcess_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_imagePreProcessCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_imagePreProcessProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_imagePreProcessControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_imagePreProcessStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_imagePreProcessDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_IMAGEPREPROCESS;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for feature plane computation alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imagePreProcessCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_ImagePreProcessObj                    * pImagePreProcessObj;
    AlgorithmLink_ImagePreProcessCreateParams           * pLinkCreateParams;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_LinkChInfo                                   * pPrevChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_VideoFrameBuffer                             * pSystemVideoFrameBuffer;

    pImagePreProcessObj = (AlgorithmLink_ImagePreProcessObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_ImagePreProcessObj),
                        32);
    UTILS_assert(pImagePreProcessObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pImagePreProcessObj);

    pLinkCreateParams = (AlgorithmLink_ImagePreProcessCreateParams *)
                         pCreateParams;
    pInputQInfo       = &pImagePreProcessObj->inputQInfo;
    pOutputQInfo      = &pImagePreProcessObj->outputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pImagePreProcessObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_ImagePreProcessCreateParams)
           );

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->queInfo.numCh = 1;

    status = System_linkGetInfo(
                                  pLinkCreateParams->inQueParams.prevLinkId,
                                  &prevLinkInfo
                                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= 1);

    prevLinkQId = pLinkCreateParams->inQueParams.prevLinkQueId;

    pImagePreProcessObj->inChInfo = prevLinkInfo.queInfo[prevLinkQId].chInfo[0];
    pPrevChInfo = &pImagePreProcessObj->inChInfo;

    if(System_Link_Ch_Info_Get_Flag_Data_Format(pPrevChInfo->flags)
        !=
        SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(0);
    }

    UTILS_assert(
                  (pPrevChInfo->width  >= pLinkCreateParams->imgFrameWidth)
                  ||
                  (pPrevChInfo->height >= pLinkCreateParams->imgFrameHeight)
                );

    pOutChInfo           = &pOutputQInfo->queInfo.chInfo[0];
    pOutChInfo->height   = pLinkCreateParams->imgFrameHeight;
    pOutChInfo->width    = pLinkCreateParams->imgFrameWidth;
    pOutChInfo->flags    = pPrevChInfo->flags;


    pOutChInfo->pitch[0] = pOutChInfo->width;
    pOutChInfo->pitch[1] = pOutChInfo->pitch[0];
    pOutChInfo->pitch[2] = pOutChInfo->pitch[0];


    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(
                                pObj,
                                1,
                                pInputQInfo,
                                1,
                                pOutputQInfo
                               );


    Alg_filter2dCreate(
        &pImagePreProcessObj->algFilter2dObj,
        pLinkCreateParams->imgFrameWidth,
        pLinkCreateParams->imgFrameHeight,
        pPrevChInfo->pitch,
        FALSE,
        TRUE,
        TRUE
        );

    pImagePreProcessObj->filter2dTime = 0;
    pImagePreProcessObj->frameCount = 0;

    /*
     * Allocate memory for the output buffers with system Buffer
     */

    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer           = &pImagePreProcessObj->buffers[bufId];
        pSystemVideoFrameBuffer = &pImagePreProcessObj->videoFrames[bufId];
        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->payload      =   pSystemVideoFrameBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_VideoFrameBuffer);
        pSystemBuffer->chNum        =   0;

        /*
         * Buffer allocation done for maxHeight, maxWidth and also assuming
         * worst case num planes = 2, for data Format SYSTEM_DF_YUV422I_YUYV
         * run time (frame exchanges) are initialized here
         */
        pSystemVideoFrameBuffer->bufAddr[0] = Utils_memAlloc(
                                           UTILS_HEAPID_DDR_CACHED_SR,
                                           (pImagePreProcessObj->inChInfo.height*(pImagePreProcessObj->inChInfo.pitch[0])*2),
                                           ALGORITHMLINK_FRAME_ALIGN);

        /*
         * Carving out memory pointer for chroma which will get used in case of
         * SYSTEM_DF_YUV422SP_UV
         */
        pSystemVideoFrameBuffer->bufAddr[1] = (void*)(
            (UInt32) pSystemVideoFrameBuffer->bufAddr[0] +
            (UInt32)(pImagePreProcessObj->inChInfo.height*(pImagePreProcessObj->inChInfo.pitch[0]))
            );

        UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);


        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }

    pImagePreProcessObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_IMAGEPREPROCESS");
    UTILS_assert(NULL != pImagePreProcessObj->linkStatsInfo);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmLink_imagePreProcessProcess(void * pObj)
{
    UInt32 bufId;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_ImagePreProcessObj                    * pImagePreProcessObj;
    System_BufferList                                     inputBufList;
    AlgorithmLink_ImagePreProcessCreateParams           * pLinkCreateParams;
    System_Buffer                                       * pSysOutBuffer;
    System_Buffer                                       * pSysInBuffer;
    System_VideoFrameBuffer                             * pVideoFrameInBuffer;
    System_VideoFrameBuffer                             * pVideoFrameOutBuffer;
    System_BufferList                                     bufListReturn;
    System_LinkStatistics                               * linkStatsInfo;
    UInt8 *inBufAddr[2];
    UInt8 *outBufAddr[2];
    UInt64 curTime;

    pImagePreProcessObj = (AlgorithmLink_ImagePreProcessObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pImagePreProcessObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pLinkCreateParams = &pImagePreProcessObj->algLinkCreateParams;

    if (pImagePreProcessObj->isFirstFrameRecv == FALSE)
    {
        pImagePreProcessObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                        pLinkCreateParams->inQueParams.prevLinkId,
                        pLinkCreateParams->inQueParams.prevLinkQueId,
                        &inputBufList);

    if (inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];
            if(pSysInBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

            status = AlgorithmLink_getEmptyOutputBuffer(
                                                        pObj,
                                                        0,
                                                        0,
                                                        &pSysOutBuffer
                                                        );
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                 linkStatsInfo->linkStats.chStats
                                [0].inBufDropCount++;
                 linkStatsInfo->linkStats.chStats
                                [0].outBufDropCount[0]++;
            }
            else
            {
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                pVideoFrameInBuffer = (System_VideoFrameBuffer *)pSysInBuffer->payload;
                pVideoFrameOutBuffer = (System_VideoFrameBuffer *)pSysOutBuffer->payload;

                inBufAddr[0] = pVideoFrameInBuffer->bufAddr[0];
                inBufAddr[1] = pVideoFrameInBuffer->bufAddr[1];

                inBufAddr[0] += pImagePreProcessObj->inChInfo.pitch[0]*pLinkCreateParams->imgFrameStartY
                                +
                                pLinkCreateParams->imgFrameStartX;

                inBufAddr[1] += pImagePreProcessObj->inChInfo.pitch[1]*pLinkCreateParams->imgFrameStartY/2
                                +
                                pLinkCreateParams->imgFrameStartX;

                curTime = Utils_getCurGlobalTimeInUsec();

                outBufAddr[0] = pVideoFrameOutBuffer->bufAddr[0];
                outBufAddr[1] = pVideoFrameOutBuffer->bufAddr[1];

                Alg_filter2dProcess(
                    &pImagePreProcessObj->algFilter2dObj,
                    (Void**)inBufAddr,
                    (Void**)outBufAddr
                    );

                curTime = Utils_getCurGlobalTimeInUsec() - curTime;

                pImagePreProcessObj->filter2dTime += curTime;

                curTime = Utils_getCurGlobalTimeInUsec();

                pImagePreProcessObj->imagePreProcessTime += curTime;

                pImagePreProcessObj->frameCount++;

                #if 0
                if((pImagePreProcessObj->frameCount > 0) && (pImagePreProcessObj->frameCount%300==0))
                {
                    Vps_printf(
                        " ALG_IMAGEPREPROCESS: filter2d2 (avg) = %d us\n",
                            pImagePreProcessObj->filter2dTime/pImagePreProcessObj->frameCount
                        );

                    pImagePreProcessObj->filter2dTime = 0;
                    pImagePreProcessObj->frameCount = 0;
                }
                #endif

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                                [0].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                                [0].outBufCount[0]++;

                status = AlgorithmLink_putFullOutputBuffer(
                                                pObj,
                                                0,
                                                pSysOutBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(
                      pLinkCreateParams->outQueParams.nextLink,
                      SYSTEM_CMD_NEW_DATA,
                      NULL);
                /*
                 * Releasing (Free'ing) output buffers, since algorithm
                 * does not need it for any future usage.
                 */
                bufListReturn.numBuf = 1;
                bufListReturn.buffers[0] = pSysOutBuffer;

                AlgorithmLink_releaseOutputBuffer(
                                                  pObj,
                                                  0,
                                                  &bufListReturn
                                                  );
            }
            bufListReturn.numBuf = 1;
            bufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                              pObj,
                              0,
                              pLinkCreateParams->inQueParams.prevLinkId,
                              pLinkCreateParams->inQueParams.prevLinkQueId,
                              &bufListReturn,
                              &bufDropFlag);
        }
    }

    return status;
}

Int32 AlgorithmLink_imagePreProcessControl(void * pObj,
                                           void * pControlParams)
{
    AlgorithmLink_ImagePreProcessObj* pImagePreProcessObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pImagePreProcessObj = (AlgorithmLink_ImagePreProcessObj *)
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
            AlgorithmLink_imagePreProcessPrintStatistics(pObj, pImagePreProcessObj);
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_imagePreProcessStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_imagePreProcessDelete(void * pObj)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId;
    AlgorithmLink_ImagePreProcessObj            * pImagePreProcessObj;
    AlgorithmLink_ImagePreProcessCreateParams   * pLinkCreateParams;
    System_VideoFrameBuffer                     * pVideoFrameBuffer;

    pImagePreProcessObj = (AlgorithmLink_ImagePreProcessObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pImagePreProcessObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pImagePreProcessObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Alg_filter2dDelete(&pImagePreProcessObj->algFilter2dObj);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pVideoFrameBuffer     =   &pImagePreProcessObj->videoFrames[bufId];


        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pVideoFrameBuffer->bufAddr[0],
                                (pImagePreProcessObj->inChInfo.height*(pImagePreProcessObj->inChInfo.pitch[0])*2)
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    Utils_memFree( UTILS_HEAPID_DDR_CACHED_LOCAL,
                   pImagePreProcessObj,
                   sizeof(AlgorithmLink_ImagePreProcessObj));

    return status;
}

Int32 AlgorithmLink_imagePreProcessPrintStatistics(void *pObj,
                AlgorithmLink_ImagePreProcessObj *pFeaturePlaneComputeObj)
{
    UTILS_assert(NULL != pFeaturePlaneComputeObj->linkStatsInfo);

    Utils_printLinkStatistics(&pFeaturePlaneComputeObj->linkStatsInfo->linkStats,
                            "ALG_IMAGEPREPROCESS",
                            TRUE);

    Utils_printLatency("ALG_IMAGEPREPROCESS",
                       &pFeaturePlaneComputeObj->linkStatsInfo->linkLatency,
                       &pFeaturePlaneComputeObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

