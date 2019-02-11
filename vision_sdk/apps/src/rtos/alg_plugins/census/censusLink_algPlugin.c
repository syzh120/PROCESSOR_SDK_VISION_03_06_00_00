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
 * \file censusLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Census transform algorithm
 *         Link
 *
 * \version 0.1 (Sep 2014) : [SR] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
/*#define _TEST_STATIC_INPUT*/

#include "censusLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/* Uncomment below line to feed a static left and right images input corresponding to this post processing link
    The left static input is assumed to be contained in a global array gCensusTestLeftInput[]
    of dimensions 896*416= CENSUS_INPUT_IMAGE_WIDTH*CENSUS_INPUT_IMAGE_HEIGHT bytes
    The right static input is assumed to be contained in a global array gCensusTestRightInput[]
    of dimensions 896*416= CENSUS_INPUT_IMAGE_WIDTH*CENSUS_INPUT_IMAGE_HEIGHT bytes
    These arrays are not included in any VISION SDK file. They would be for test purpose and the user
    is free to create his own static arrays C file and drop them in the same census plug in source directory
    and modify the make depend file SRC_FILES.MK so they get compiled in.
    Purpose of feeding a static image is for testing the stereo-vision algorithm independently only,
    isolated from any pre-processing step such as remap, ISP.
*/


#ifdef _TEST_STATIC_INPUT
extern unsigned short gCensusTestLeftInput[896*416/2];
extern unsigned short gCensusTestRightInput[896*416/2];
#endif

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plug-ins of census algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_census_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_censusCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_censusProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_censusControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_censusStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_censusDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_CENSUS;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief census Alg uses the IVISION standard to interact with the
 *        framework. All process/control calls to the algorithm should adhere
 *        to the IVISION standard. This function initializes input and output
 *        buffers
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
UInt32 AlgorithmLink_censusInitIOBuffers( AlgorithmLink_CensusObj *pObj,
                          AlgorithmLink_CensusCreateParams * pLinkCreateParams )
{
    UInt32              idx;
    UInt32              bufferSize;
    UInt32              numCensusOrientations;
    UInt32              numBytesPerCensus;

    IVISION_InBufs      * pInBufs;
    IVISION_OutBufs     * pOutBufs;

    pInBufs = &pObj->inBufs;
    pInBufs->size       = sizeof(IVISION_InBufs);
    pInBufs->numBufs    = CENSUS_BUFDESC_IN_TOTAL;
    pInBufs->bufDesc    = pObj->inBufDescList;
    pObj->inBufDescList[0]  = &pObj->inBufDesc;

    pOutBufs = &pObj->outBufs;
    pOutBufs->size      = sizeof(IVISION_OutBufs);
    pOutBufs->numBufs   = CENSUS_BUFDESC_OUT_TOTAL;
    pOutBufs->bufDesc   = pObj->outBufDescList;
    pObj->outBufDescList[0]= &pObj->outBufDesc;

    idx = CENSUS_BUFDESC_IN;
    pInBufs->bufDesc[idx]->numPlanes = 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x
                                        = (pLinkCreateParams->winWidth - 1)/2;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y
                                        = (pLinkCreateParams->winHeight - 1)/2;
    pInBufs->bufDesc[idx]->bufPlanes[0].width
                                        = pLinkCreateParams->srcImageWidth;
    pInBufs->bufDesc[idx]->bufPlanes[0].height
                                        = pLinkCreateParams->srcImageHeight;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
                                        = pLinkCreateParams->imageRoiWidth;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
                                        = pLinkCreateParams->imageRoiHeight;
    pInBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = CENSUS_BUFDESC_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
                                        = pLinkCreateParams->imageRoiWidth;
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
                                        = pLinkCreateParams->imageRoiHeight;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
                                        = pLinkCreateParams->imageRoiWidth;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
                                        = pLinkCreateParams->imageRoiHeight;
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType= 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf= NULL;

    numCensusOrientations= _CENSUS_WIN_SIZE(pLinkCreateParams->winWidth,
                                            pLinkCreateParams->winHeight,
                                            pLinkCreateParams->winHorzStep,
                                            pLinkCreateParams->winVertStep);
    numBytesPerCensus= (numCensusOrientations + 7) >> 3;
    bufferSize = (numBytesPerCensus*pLinkCreateParams->imageRoiWidth
                    *pLinkCreateParams->imageRoiHeight);

    pObj->outBufferSize = bufferSize;
    pObj->output_pitch = pLinkCreateParams->imageRoiWidth;

    return SYSTEM_LINK_STATUS_SOK;

}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for census alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_censusCreate(void * pObj,void * pCreateParams)
{
    UInt32                  status = SYSTEM_LINK_STATUS_SOK;
    UInt32                  bufferSize;
    UInt32                  numInputQUsed;
    UInt32                  numOutputQUsed;
    UInt32                  channelId;
    UInt32                  outputQId;
    UInt32                  prevLinkQueId;
    UInt32                  bufId;

    System_LinkInfo                     prevLinkInfo;
    System_LinkChInfo                   * pOutChInfo;
    System_LinkChInfo                   * pPrevChInfo;
    System_Buffer                       * pSystemBuffer;
    System_VideoFrameCompositeBuffer    * pSysCompositeBufferOutput;
    AlgorithmLink_InputQueueInfo        * pInputQInfo;
    AlgorithmLink_OutputQueueInfo       * pOutputQInfo;
    CENSUS_TI_CreateParams              * pAlgCreateParams;
    AlgorithmLink_CensusCreateParams    * pLinkCreateParams;
    AlgorithmLink_CensusObj             * pCensusObj;

    IVISION_InArgs      *pInArgs;
    CENSUS_TI_outArgs   *pOutArgs;


    pLinkCreateParams = (AlgorithmLink_CensusCreateParams *)
                         pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pCensusObj = (AlgorithmLink_CensusObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_CensusObj),
                        32);
    UTILS_assert(pCensusObj != NULL);
    AlgorithmLink_setAlgorithmParamsObj(pObj, pCensusObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pCensusObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_CensusCreateParams)
           );

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */
    pAlgCreateParams = &pCensusObj->algCreateParams;
    pAlgCreateParams->visionParams.algParams.size = sizeof(*pAlgCreateParams);
    pAlgCreateParams->visionParams.cacheWriteBack = NULL;
    pAlgCreateParams->imgFrameWidth         = pLinkCreateParams->imageRoiWidth;
    pAlgCreateParams->imgFrameHeight        = pLinkCreateParams->imageRoiHeight;
    pAlgCreateParams->inputBitDepth         = pLinkCreateParams->inputBitDepth;
    pAlgCreateParams->winWidth              = pLinkCreateParams->winWidth;
    pAlgCreateParams->winHeight             = pLinkCreateParams->winHeight;
    pAlgCreateParams->winHorzStep           = pLinkCreateParams->winHorzStep;
    pAlgCreateParams->winVertStep           = pLinkCreateParams->winVertStep;

    pCensusObj->handle = AlgIvision_create(&CENSUS_TI_VISION_FXNS, (IALG_Params *)(pAlgCreateParams));
    UTILS_assert(pCensusObj->handle!=NULL);

    /*
     * Populating parameters corresponding to Q usage of census
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = 1;
    pInputQInfo       = &pCensusObj->inputQInfo;
    pOutputQInfo      = &pCensusObj->outputQInfo;
    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    outputQId                   = 0;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In census Link, only data format changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(
                                  pLinkCreateParams->inQueParams.prevLinkId,
                                  &prevLinkInfo
                                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= numInputQUsed);

    prevLinkQueId = pLinkCreateParams->inQueParams.prevLinkQueId;
    pCensusObj->numInputChannels = prevLinkInfo.queInfo[prevLinkQueId].numCh;
    pOutputQInfo->queInfo.numCh = 1;

    /*
     * Initialize input output buffers
     */
    AlgorithmLink_censusInitIOBuffers(pCensusObj, pLinkCreateParams);

    /*
     * Channel Info Population
     */
        channelId = 0;
        pOutChInfo = &(pOutputQInfo->queInfo.chInfo[channelId]);
        pPrevChInfo = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

        /*
         * Certain channel info parameters simply get defined by previous link
         * channel info. Hence copying them to output channel info.
         * Update the data format for OutCh to YUV420SP
         */
        pOutChInfo->startX = 0;
        pOutChInfo->startY = 0;
        pOutChInfo->width  = pLinkCreateParams->imageRoiWidth;
        pOutChInfo->height = pLinkCreateParams->imageRoiHeight;
        pOutChInfo->flags = pPrevChInfo->flags;
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pOutChInfo->flags,
                                            SYSTEM_BUFFER_TYPE_METADATA);
        /*
         * Certain channel info parameters are properties of the current link,
         * They are set here.
         */
    pOutChInfo->pitch[0] = pCensusObj->output_pitch;
    pOutChInfo->pitch[1] = pCensusObj->output_pitch;
        pOutChInfo->pitch[2] = 0;

    for(channelId =0 ; channelId < pCensusObj->numInputChannels; channelId++)
    {
        /*
         * Taking a copy of input channel info in the link object for any future
         * use
         */
        memcpy((void *)&(pCensusObj->inputChInfo[channelId]),
            (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
            sizeof(System_LinkChInfo)
            );
    }

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    status = AlgorithmLink_queueInfoInit(
                                    pObj,
                                    numInputQUsed,
                                    pInputQInfo,
                                    numOutputQUsed,
                                    pOutputQInfo
                               );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */
    bufferSize = pCensusObj->outBufferSize;
        for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
        {
        pSystemBuffer   = &pCensusObj->buffers[bufId];
        pSysCompositeBufferOutput
                        = &pCensusObj->censusOpBuffers[bufId];
        memset(pSysCompositeBufferOutput, 0, sizeof(System_VideoFrameCompositeBuffer));
            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->payload      =   pSysCompositeBufferOutput;
        pSystemBuffer->payloadSize  =   sizeof(System_VideoFrameCompositeBuffer);
        pSystemBuffer->chNum        =   0;

        pSysCompositeBufferOutput->numFrames = 2;
        pSysCompositeBufferOutput->bufAddr[0][0] = Utils_memAlloc(
                                                   UTILS_HEAPID_DDR_CACHED_SR,
                                                   bufferSize,
                                                   ALGORITHMLINK_FRAME_ALIGN
                                                   );
        UTILS_assert(pSysCompositeBufferOutput->bufAddr[0][0] != NULL);
        pSysCompositeBufferOutput->bufAddr[0][1] = Utils_memAlloc(
                                               UTILS_HEAPID_DDR_CACHED_SR,
                                               bufferSize,
                                               ALGORITHMLINK_FRAME_ALIGN
                                               );
        UTILS_assert(pSysCompositeBufferOutput->bufAddr[0][0] != NULL);
        pSysCompositeBufferOutput->flags = 0;
            status = AlgorithmLink_putEmptyOutputBuffer
                                            (pObj, outputQId, pSystemBuffer);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        memcpy((void *)&(pSysCompositeBufferOutput->chInfo),
        (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
        sizeof(System_LinkChInfo)
        );
        }

    pInArgs = &(pCensusObj->inArgs);
    pOutArgs = &(pCensusObj->outArgs);

        pInArgs->subFrameInfo = 0;
        pInArgs->size = sizeof(IVISION_InArgs);

        pOutArgs->iVisionOutArgs.size = sizeof(CENSUS_TI_outArgs);

    pCensusObj->isFirstFrameRecv = FALSE;
    /* Assign pointer to link stats object */
    pCensusObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_CENSUS");
    UTILS_assert(NULL != pCensusObj->linkStatsInfo);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for census algorithm link
 *
 *        This function executes on the EVE The processor gets locked with
 *        execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_censusProcess(void * pObj)
{
    UInt32                                  status = SYSTEM_LINK_STATUS_SOK;
    UInt32                                  bufId;
    UInt32                                  inputQId;
    UInt32                                  channelId;
    UInt32                                  outputQId;
    Bool                                    bufDropFlag;

    AlgorithmLink_CensusObj                 * pCensusObj;
    AlgorithmLink_CensusCreateParams        * pLinkCreateParams;

    System_Buffer                           * pSysOutBuffer;
    System_Buffer                           * pSysInBuffer;
#ifndef    _TEST_STATIC_INPUT
    System_VideoFrameCompositeBuffer        * pSysCompositeBufferInput;
#endif
    System_VideoFrameCompositeBuffer        * pSysCompositeBufferOutput;

    IVISION_InBufs                          * pInBufs;
    IVISION_OutBufs                         * pOutBufs;
    IVISION_InArgs                          * pInArgs;
    CENSUS_TI_outArgs                       * pOutArgs;

    System_BufferList                       inputBufList;
    System_BufferList                       outputBufListReturn;
    System_BufferList                       inputBufListReturn;
    System_LinkStatistics *linkStatsInfo;

    pCensusObj = (AlgorithmLink_CensusObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pCensusObj->algLinkCreateParams;

    pInBufs  = &pCensusObj->inBufs;
    pOutBufs = &pCensusObj->outBufs;

    linkStatsInfo = pCensusObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    System_getLinksFullBuffers(
                        pLinkCreateParams->inQueParams.prevLinkId,
                        pLinkCreateParams->inQueParams.prevLinkQueId,
                        &inputBufList);

    linkStatsInfo->linkStats.newDataCmdCount++;

    if (inputBufList.numBuf)
    {
        if (pCensusObj->isFirstFrameRecv == FALSE)
        {
            pCensusObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics
                    (&linkStatsInfo->linkStats, pCensusObj->numInputChannels, 1);
            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];
            if(pSysInBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            channelId = pSysInBuffer->chNum;
            for(channelId=0; channelId < pCensusObj->numInputChannels; channelId++)
            {
                /* Repeating the count for RightInput and LeftInput */
                linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;
            }

            /*
             * Getting free (empty) buffers from pool of output buffers
             */
            outputQId        = 0;
            channelId = 0;
            status = AlgorithmLink_getEmptyOutputBuffer(
                                                        pObj,
                                                        outputQId,
                                                        channelId,
                                                        &pSysOutBuffer
                                                        );
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                 linkStatsInfo->linkStats.chStats[channelId].inBufDropCount++;
                 linkStatsInfo->linkStats.chStats[channelId].outBufDropCount[0]++;
            }
            else
            {
                /*
                 * Get video frame buffer out of the system Buffer for both
                 * input and output buffers.
                 * Associate the input/output buffer pointers with inBufs
                 * and outBufs
                 * Record the bufferId with the address of the System Buffer
                 */
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp
                                            = Utils_getCurGlobalTimeInUsec();

                pSysCompositeBufferOutput
                            = (System_VideoFrameCompositeBuffer*)pSysOutBuffer->payload;
#ifndef _TEST_STATIC_INPUT
                pSysCompositeBufferInput
                            = (System_VideoFrameCompositeBuffer *)pSysInBuffer->payload;
#endif

                //TBD change this for loop to take numberof frames in coposite buffer
                for(channelId=0; channelId < pCensusObj->numInputChannels; channelId++)
                {

                /*
                 * Index 0: YUV420 data format, Only Y plane is used
                 */
#ifdef _TEST_STATIC_INPUT
                if (channelId== 0) {
                    pInBufs->bufDesc[0]->bufPlanes[0].buf
                    = gCensusTestRightInput;
                    }
                else {
                    pInBufs->bufDesc[0]->bufPlanes[0].buf
                    = gCensusTestLeftInput;
                    }
#else
                pInBufs->bufDesc[0]->bufPlanes[0].buf
                                    = pSysCompositeBufferInput->bufAddr[0][channelId];
#endif
                pInBufs->bufDesc[0]->bufferId   = (UInt32)pSysInBuffer;

                /*
                 * Index 0: Meta data format
                 */
                pOutBufs->bufDesc[0]->bufPlanes[0].buf
                                    = pSysCompositeBufferOutput->bufAddr[0][channelId];

                pInArgs  = &pCensusObj->inArgs;
                pOutArgs = &pCensusObj->outArgs;

                status = AlgIvision_process(
                                         pCensusObj->handle,
                                         pInBufs,
                                         pOutBufs,
                                         (IVISION_InArgs *)pInArgs,
                                         (IVISION_OutArgs *)pOutArgs
                                        );
                UTILS_assert(status == IALG_EOK);


               linkStatsInfo->linkStats.chStats
                                [channelId].inBufProcessCount++;
               linkStatsInfo->linkStats.chStats
                                [channelId].outBufCount[0]++;
                    }

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                     pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                     pSysOutBuffer->srcTimestamp);

               /*
                * <TODO For Now not handling locking of output buffers
                *  case >
                */
               status = AlgorithmLink_putFullOutputBuffer(
                                                pObj,
                                                outputQId,
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
               outputBufListReturn.numBuf = 1;
               outputBufListReturn.buffers[0] = pSysOutBuffer;

               status = AlgorithmLink_releaseOutputBuffer(
                                                  pObj,
                                                  outputQId,
                                                  &outputBufListReturn
                                                  );
               UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }

            inputQId                        = 0;
            inputBufListReturn.numBuf       = 1;
            inputBufListReturn.buffers[0]   = pSysInBuffer;
            bufDropFlag = FALSE;
            status = AlgorithmLink_releaseInputBuffer(
                              pObj,
                              inputQId,
                              pLinkCreateParams->inQueParams.prevLinkId,
                              pLinkCreateParams->inQueParams.prevLinkQueId,
                              &inputBufListReturn,
                              &bufDropFlag);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for census algo
 *
 * \param  pObj                  [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_censusControl(void * pObj, void * pControlParams)
{
    Int32                               status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_CensusObj             * pCensusObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    pCensusObj = (AlgorithmLink_CensusObj *)
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
            AlgorithmLink_censusPrintStatistics(pObj,
                                                pCensusObj
                                                );
            break;

        default:
            //No other control call implemented in this link
            UTILS_assert(NULL);
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for census algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_censusStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for census algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_censusDelete(void * pObj)
{
    Int32                                   status;
    UInt32                                  bufId;
    UInt32                                  bufferSize;

    AlgorithmLink_CensusObj                 * pCensusObj;
    AlgorithmLink_CensusCreateParams        * pLinkCreateParams;
    System_VideoFrameCompositeBuffer        * pSysCompositeBufferOutput;

    pCensusObj = (AlgorithmLink_CensusObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pCensusObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pCensusObj->linkStatsInfo);
    UTILS_assert(status == 0);

    status = AlgIvision_delete(pCensusObj->handle);
    UTILS_assert(status == 0);

    /*
     * Free link buffers
     */
    bufferSize = pCensusObj->outBufferSize;

        for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
        {
        pSysCompositeBufferOutput = &pCensusObj->censusOpBuffers[bufId];

            /*
             * Free'ing up of allocated buffers
             */
            status = Utils_memFree(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                pSysCompositeBufferOutput->bufAddr[0][0],
                                bufferSize
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pSysCompositeBufferOutput->bufAddr[0][1],
                                    bufferSize
                                   );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        }

   Utils_memFree(
                   UTILS_HEAPID_DDR_CACHED_LOCAL,
                   pCensusObj,
                   sizeof(AlgorithmLink_CensusObj)
                );
    return status;
}


/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pEdgeDetectionObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_censusPrintStatistics(void *pObj,
                AlgorithmLink_CensusObj *pCensusObj)
{
    UTILS_assert(NULL != pCensusObj->linkStatsInfo);

    Utils_printLinkStatistics(&pCensusObj->linkStatsInfo->linkStats,
                            "ALG_CENSUS",
                            TRUE);

    Utils_printLatency("ALG_CENSUS",
                       &pCensusObj->linkStatsInfo->linkLatency,
                       &pCensusObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

