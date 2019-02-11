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
 * \file sceneObstructionDetectLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for frame copy Link
 *
 * \version 0.0 (Nov 2015) : [VC] First version
 * \version 0.1 (Dec 2015) : [VC]
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sceneObstructionDetectLink_priv.h"
#include <include/link_api/system_common.h>
#include <include/link_api/issIspConfiguration.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/link_api/grpxSrcLink.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sceneObstructionDetect_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
            AlgorithmLink_sceneObstructionDetectCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
            AlgorithmLink_sceneObstructionDetectProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
            AlgorithmLink_sceneObstructionDetectControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
            AlgorithmLink_sceneObstructionDetectStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
            AlgorithmLink_sceneObstructionDetectDelete;
#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SCENE_OBSTRUCTION_DETECT;
#endif
#ifdef BUILD_M4
    algId = ALGORITHM_LINK_IPU_ALG_SCENE_OBSTRUCTION_DETECT;
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
UInt32 AlgorithmLink_sceneObstructionDetectInitIOBuffers( AlgorithmLink_SceneObstructionDetectObj *pObj,
                          AlgorithmLink_SceneObstructionDetectCreateParams * pLinkCreateParams )
{
    UInt32              idx;
    UInt32              bufferSize;

    IVISION_InBufs      * pInBufs;
    IVISION_OutBufs     * pOutBufs;

    bufferSize= pLinkCreateParams->paxNumH* pLinkCreateParams->paxNumV*sizeof(IssAfH3aOutOverlay);
    pInBufs = &pObj->inBufs;
    pInBufs->size       = sizeof(IVISION_InBufs);
    pInBufs->numBufs    = SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_IN_TOTAL;
    pInBufs->bufDesc    = pObj->inBufDescList;
    pObj->inBufDescList[0]  = &pObj->inBufDesc;

    pOutBufs = &pObj->outBufs;
    pOutBufs->size      = sizeof(IVISION_OutBufs);
    pOutBufs->numBufs   = SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_OUT_TOTAL;
    pOutBufs->bufDesc   = pObj->outBufDescList;
    pObj->outBufDescList[0]= &pObj->outBufDesc;

    idx = SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_IN_FV_STATS;
    pInBufs->bufDesc[idx]->numPlanes = 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y= 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].width= bufferSize;
    pInBufs->bufDesc[idx]->bufPlanes[0].height= 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.width= bufferSize;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.height= 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width= 4;
    pOutBufs->bufDesc[idx]->bufPlanes[0].height= 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width= 4;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height= 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType= 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf= NULL;

    return SYSTEM_LINK_STATUS_SOK;

}


/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for frame copy algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sceneObstructionDetectCreate(void * pObj, void * pCreateParams)
{
    Void          * algHandle;
    UInt32                       bufId, i;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer              * pSystemBuffer;
    System_MetaDataBuffer      * pMetaDataBuffer;
    System_LinkInfo              prevLinkInfo;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;

    AlgorithmLink_SceneObstructionDetectObj          * pAlgObj;
    AlgorithmLink_SceneObstructionDetectCreateParams * pLinkCreateParams;
    AlgorithmLink_OutputQueueInfo       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo        * pInputQInfo;


    pLinkCreateParams =
            (AlgorithmLink_SceneObstructionDetectCreateParams *)pCreateParams;

    System_resetLinkMemAllocInfo(&pLinkCreateParams->memAllocInfo);

    if(System_useLinkMemAllocInfo(&pLinkCreateParams->memAllocInfo)==FALSE)
    {
        pAlgObj = (AlgorithmLink_SceneObstructionDetectObj *)
                            Utils_memAlloc(
                                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                                    sizeof(AlgorithmLink_SceneObstructionDetectObj),
                                    128);
    }
    else
    {
        pAlgObj = (AlgorithmLink_SceneObstructionDetectObj *)
                            System_allocLinkMemAllocInfo(
                                    &pLinkCreateParams->memAllocInfo,
                                    sizeof(AlgorithmLink_SceneObstructionDetectObj),
                                    128);
    }
    UTILS_assert(pAlgObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    pOutputQInfo = &pAlgObj->outputQInfo;
    pInputQInfo  = &pAlgObj->inputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(&pAlgObj->algLinkCreateParams,
            pLinkCreateParams,
            sizeof(pAlgObj->algLinkCreateParams));

    /*
     * Populating parameters corresponding to Q usage of frame copy
     * algorithm link
     */
    numInputQUsed     = 1;
    numOutputQUsed    = 1;
    numChannelsUsed   = 1;
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo->queInfo.numCh = numChannelsUsed;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In frame copy example, only pitch changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(
            pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
            &prevLinkInfo
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    prevLinkQueId = pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId;
    pAlgObj->inQueInfo = prevLinkInfo.queInfo[prevLinkQueId];

    pOutputQInfo->queInfo.numCh = pAlgObj->inQueInfo.numCh;
    UTILS_assert(pOutputQInfo->queInfo.numCh<=SCENE_OBSTRUCTION_DETECT_LINK_MAX_CH);


    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
            numInputQUsed,
            pInputQInfo,
            numOutputQUsed,
            pOutputQInfo
    );

    if(pAlgObj->algLinkCreateParams.numOutBuffers >
    SCENE_OBSTRUCTION_DETECT_LINK_MAX_NUM_OUTPUT)
    {
        pAlgObj->algLinkCreateParams.numOutBuffers =
                SCENE_OBSTRUCTION_DETECT_LINK_MAX_NUM_OUTPUT;
    }

    /*
     * Channel Info Population
     */
    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */
    for (bufId = 0; bufId <
    pOutputQInfo->queInfo.numCh*pAlgObj->algLinkCreateParams.numOutBuffers;
    bufId++)
    {
        pSystemBuffer       =   &pAlgObj->buffers[bufId];
        pMetaDataBuffer     =   &pAlgObj->metaDataBuffers[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pMetaDataBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =
                bufId / pAlgObj->algLinkCreateParams.numOutBuffers;

        pMetaDataBuffer->numMetaDataPlanes  = 1;

        pMetaDataBuffer->metaBufSize[0U] = SCENE_OBSTRUCTION_DETECT_LINK_MAX_BUF_SIZE;

        if(System_useLinkMemAllocInfo(
                &pAlgObj->algLinkCreateParams.memAllocInfo)==FALSE)
        {
            pMetaDataBuffer->bufAddr[0U] =  Utils_memAlloc(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pMetaDataBuffer->metaBufSize[0U],
                    128);
        }
        else
        {
            pMetaDataBuffer->bufAddr[0U]
                                     =  (Ptr)System_allocLinkMemAllocInfo(
                                             &pAlgObj->algLinkCreateParams.memAllocInfo,
                                             pMetaDataBuffer->metaBufSize[0U],
                                             128);
        }

        pMetaDataBuffer->metaFillLength[0U] =
                pMetaDataBuffer->metaBufSize[0U];

        UTILS_assert(pMetaDataBuffer->bufAddr[0U] != NULL);

        pMetaDataBuffer->flags = 0;

        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */

    pAlgObj->createParams.paxNumH = pAlgObj->algLinkCreateParams.paxNumH;
    pAlgObj->createParams.paxNumV = pAlgObj->algLinkCreateParams.paxNumV;
    pAlgObj->createParams.wdrEnable = pAlgObj->algLinkCreateParams.wdrEnable;
    pAlgObj->createParams.vfEnable = pAlgObj->algLinkCreateParams.vfEnable;
    pAlgObj->createParams.scaleFactor = pAlgObj->algLinkCreateParams.scaleFactor;
    pAlgObj->createParams.sensitivity = pAlgObj->algLinkCreateParams.sensitivity;
    pAlgObj->createParams.frameSkipInterval = pAlgObj->algLinkCreateParams.frameSkipInterval;
    pAlgObj->createParams.numBlockedFramesThreshold= pAlgObj->algLinkCreateParams.numBlockedFramesThreshold;

    for(i=0; i < sizeof(pAlgObj->createParams.classifierCoef)/sizeof(float); i++)
    {
        pAlgObj->createParams.classifierCoef[i]= pAlgObj->algLinkCreateParams.classifierCoef[i];
    }

    algHandle = AlgIvision_create_useLinkMem(&pAlgObj->algLinkCreateParams.memAllocInfo, &SCENE_OBSTRUCTION_DETECT_TI_VISION_FXNS, (IALG_Params *)(&pAlgObj->createParams));
    UTILS_assert(algHandle!=NULL);

    pAlgObj->algHandle = algHandle;
    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
            AlgorithmLink_getLinkId(pObj), "ALG_SCENE_OBSTRUCTION_DETECT");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    AlgorithmLink_sceneObstructionDetectInitIOBuffers(pAlgObj, &pAlgObj->algLinkCreateParams);

    pAlgObj->isFirstFrameRecv = FALSE;
    pAlgObj->sceneObstructionState= FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for frame copy algorithm link
 *
 *        This function executes on the DSP or EVE or IPU or A15 processor.
 *        Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sceneObstructionDetectProcess(void * pObj)
{
    UInt32 bufId;
    Int32 status;
    Bool   bufDropFlag;
    AlgorithmLink_SceneObstructionDetectObj            * pAlgObj;
    System_BufferList                   inputBufList;
    AlgorithmLink_SceneObstructionDetectCreateParams   * pLinkCreatePrms;
    System_Buffer                       * pSysOutBuffer;
    System_Buffer                       * pSysInBuffer;
    System_MetaDataBuffer               * pInMetaBuf;
    System_MetaDataBuffer               * pOutMetaBuf;
    System_BufferList                   bufListReturn;
    System_LinkStatistics               * linkStatsInfo;
    IVISION_InBufs                          * pInBufs;
    IVISION_OutBufs                         * pOutBufs;
    IVISION_InArgs                          * pInArgs;
    IVISION_OutArgs                       * pOutArgs;
    GrpxSrcLink_StringRunTimePrintParams printPrms;
    char *displayString;
    char sceneObstructedString[]="SCENE OBSTRUCTED";
    char sceneClearString[]="                ";


    pAlgObj = (AlgorithmLink_SceneObstructionDetectObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pAlgObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pLinkCreatePrms = &pAlgObj->algLinkCreateParams;

    pInBufs  = &pAlgObj->inBufs;
    pOutBufs = &pAlgObj->outBufs;

    if (pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }


    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(pLinkCreatePrms->inQueParams.prevLinkId,
            pLinkCreatePrms->inQueParams.prevLinkQueId,
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

            UTILS_assert(pSysInBuffer->chNum <
                    pAlgObj->outputQInfo.queInfo.numCh);

            linkStatsInfo->linkStats.chStats
            [pSysInBuffer->chNum].inBufRecvCount++;

            status = AlgorithmLink_getEmptyOutputBuffer(
                    pObj,
                    0,
                    pSysInBuffer->chNum,
                    &pSysOutBuffer);
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                linkStatsInfo->linkStats.chStats
                [pSysInBuffer->chNum].inBufDropCount++;
                linkStatsInfo->linkStats.chStats
                [pSysInBuffer->chNum].outBufDropCount[0]++;
            }
            else
            {
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->linkLocalTimestamp =
                        Utils_getCurGlobalTimeInUsec();
                pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;
                pInMetaBuf  = (System_MetaDataBuffer *) pSysInBuffer->payload;

                pOutMetaBuf->numMetaDataPlanes = pInMetaBuf->numMetaDataPlanes;

                pInBufs->bufDesc[0]->bufPlanes[0].buf
                                    = pInMetaBuf->bufAddr[0U];
                pInBufs->bufDesc[0]->bufferId   = (UInt32)pSysInBuffer;

                /*
                 * Index 0: Meta data format
                 */
                pOutBufs->bufDesc[0]->bufPlanes[0].buf
                                    = pOutMetaBuf->bufAddr[0U];

                pInArgs  = &pAlgObj->inArgs;
                pOutArgs = &pAlgObj->outArgs;

                Cache_inv(
                    pInMetaBuf->bufAddr[0U],
                    pInMetaBuf->metaBufSize[0U],
                    Cache_Type_ALLD,
                    TRUE);

                status = AlgIvision_process(
                                         pAlgObj->algHandle,
                                         pInBufs,
                                         pOutBufs,
                                         (IVISION_InArgs *)pInArgs,
                                         (IVISION_OutArgs *)pOutArgs
                                        );
                UTILS_assert(status == IALG_EOK);

                Cache_wb(
                    pOutMetaBuf->bufAddr[0U],
                    4,
                    Cache_Type_ALLD,
                    TRUE);

                /* Show scene obstructed" on the display */

                printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
                printPrms.duration_ms = (24*60*60*1000);
                printPrms.stringInfo.fontType = 0;
                printPrms.stringInfo.startX   = 670;
                printPrms.stringInfo.startY   = 335;
                if ( (*((UInt32*)pOutMetaBuf->bufAddr[0U])== 1)  && (pAlgObj->sceneObstructionState== FALSE))
                {
                    displayString= sceneObstructedString;
                    pAlgObj->sceneObstructionState= TRUE;
                }
                else if ( (*((UInt32*)pOutMetaBuf->bufAddr[0U])== 0)  && (pAlgObj->sceneObstructionState== TRUE))
                {
                    displayString= sceneClearString;
                    pAlgObj->sceneObstructionState= FALSE;
                }
                else 
                {
                    displayString= NULL;
                }

                if (displayString != NULL) {
                    snprintf(printPrms.stringInfo.string,
                             sizeof(printPrms.stringInfo.string) - 1,
                             displayString);
                
                    System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                                   GRPX_SRC_LINK_CMD_PRINT_STRING,
                                   &printPrms,
                                   sizeof(printPrms),
                                   TRUE);
                }

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                        pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                        pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                [pSysInBuffer->chNum].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                [pSysInBuffer->chNum].outBufCount[0]++;

                status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSysOutBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            }

            bufListReturn.numBuf = 1;
            bufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                    pObj,
                    0,
                    pLinkCreatePrms->inQueParams.prevLinkId,
                    pLinkCreatePrms->inQueParams.prevLinkQueId,
                    &bufListReturn,
                    &bufDropFlag);
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for frame copy algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_sceneObstructionDetectControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_SceneObstructionDetectObj     * pAlgObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgorithmLink_SceneObstructionDetectObj *)
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
        AlgorithmLink_sceneObstructionDetectPrintStatistics(pObj, pAlgObj);
        break;

    default:
        break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for frame copy algorithm link
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
Int32 AlgorithmLink_sceneObstructionDetectStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for frame copy algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sceneObstructionDetectDelete(void * pObj)
{
    UInt32 status;
    UInt32 bufId;
    AlgorithmLink_SceneObstructionDetectObj *pAlgObj;
    System_MetaDataBuffer *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_SceneObstructionDetectObj *)
                                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if (NULL != pAlgObj->algHandle)
    {
        status = AlgIvision_delete_useLinkMem(&pAlgObj->algLinkCreateParams.memAllocInfo, pAlgObj->algHandle);
        UTILS_assert(status == 0);
        pAlgObj->algHandle = NULL;
     }

    /*
     * Free link buffers
     */
    for (bufId = 0;
            bufId < pAlgObj->outputQInfo.queInfo.numCh*
            pAlgObj->algLinkCreateParams.numOutBuffers;
            bufId++)
    {
        pMetaDataBuffer     =   &pAlgObj->metaDataBuffers[bufId];

        UTILS_assert(NULL != pMetaDataBuffer->bufAddr[0]);
        if(System_useLinkMemAllocInfo(
                &pAlgObj->algLinkCreateParams.memAllocInfo)==FALSE)
        {
            status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pMetaDataBuffer->bufAddr[0],
                    pMetaDataBuffer->metaBufSize[0]
            );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    if(System_useLinkMemAllocInfo(
            &pAlgObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_LOCAL,
                pAlgObj,
                sizeof(AlgorithmLink_SceneObstructionDetectObj)
        );
    }

    pAlgObj = NULL;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pFrameCopyObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sceneObstructionDetectPrintStatistics(void *pObj,
        AlgorithmLink_SceneObstructionDetectObj *pAlgObj)
{

    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
            "ALG_SCENE_OBSTRUCTION_DETECT",
            TRUE);

    Utils_printLatency("ALG_SCENE_OBSTRUCTION_DETECT",
            &pAlgObj->linkStatsInfo->linkLatency,
            &pAlgObj->linkStatsInfo->srcToLinkLatency,
            TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
