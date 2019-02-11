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
 * \file issAewb1Link_algPlugin.c
 *
 * \brief  This file contains plug in functions for algorithm plugin
 *         Link
 *
 * \version 0.0 (Feb 2014) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "issAewb1Link_priv.h"
#include <TI_dcc.h>
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#include <TI_aewb.h>

/**
 * Default digital gains, used in case AE is disabled,
 * Merge calculating usees digital gain, so even if AE is disabled
 * digital gain must be set to default value.
 */
#define ALGORITHMS_AEWB_DEF_DIGITAL_GAIN            (512U)

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

Int32 AlgorithmLink_issAewb1_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_issAewb1Create;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_issAewb1Process;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_issAewb1Control;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_issAewb1Stop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_issAewb1Delete;

#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
    {
        algId = ALGORITHM_LINK_IPU_ALG_ISS_AEWB1;
    }
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_issAewb1Create(void * pObj,void * pCreateParams)
{
    Int32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    UInt32 chId;
    System_LinkInfo                prevLinkInfo;
    AlgorithmLink_IssAewbObj       * pAlgObj;
    AlgorithmLink_OutputQueueInfo  * pOutputQInfo;
    AlgorithmLink_InputQueueInfo   * pInputQInfo;
    System_LinkChInfo              * pOutChInfo;
    System_Buffer                  * pSystemBuffer;
    System_MetaDataBuffer          * pMetaDataBuffer;
    AlgorithmLink_IssAewbCreateParams *pLinkCreateParams;
    AlgorithmLink_IssAewbH3aParams * pH3aParams;

    pLinkCreateParams = (AlgorithmLink_IssAewbCreateParams *)pCreateParams;

    System_resetLinkMemAllocInfo(&pLinkCreateParams->memAllocInfo);

    if(System_useLinkMemAllocInfo(&pLinkCreateParams->memAllocInfo)==FALSE)
    {
        pAlgObj = (AlgorithmLink_IssAewbObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_IssAewbObj),
                        128);
    }
    else
    {
        pAlgObj = (AlgorithmLink_IssAewbObj *)
                    System_allocLinkMemAllocInfo(
                        &pLinkCreateParams->memAllocInfo,
                        sizeof(AlgorithmLink_IssAewbObj),
                        128);
    }
    UTILS_assert(pAlgObj != NULL);

    memset(pAlgObj, 0x0U, sizeof(AlgorithmLink_IssAewbObj));

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    pInputQInfo       = &pAlgObj->inputQInfo;
    pOutputQInfo      = &pAlgObj->outputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(&pAlgObj->algLinkCreateParams,
           pLinkCreateParams,
           sizeof(pAlgObj->algLinkCreateParams));

    pLinkCreateParams = &pAlgObj->algLinkCreateParams;

    /* Check for errors in parameters */
    if (pAlgObj->algLinkCreateParams.numH3aPlanes > ALGORITHM_AEWB1_MAX_PLANES)
    {
        /* Does not support more than 2 planes of H3A data */
        UTILS_assert(FALSE);
    }

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    status = System_linkGetInfo(
                    pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
                    &prevLinkInfo
                    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= 1);

    prevLinkQId = pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId;
    pAlgObj->inQueInfo = prevLinkInfo.queInfo[prevLinkQId];

    if (TRUE == pLinkCreateParams->runAewbOnlyForOneCh)
    {
        /* When Single Channel AE is enabled, output queue will have
           only one channel */
        pOutputQInfo->queInfo.numCh = 1U;
    }
    else
    {
        pOutputQInfo->queInfo.numCh = pAlgObj->inQueInfo.numCh;
    }
    UTILS_assert(pOutputQInfo->queInfo.numCh<=ISS_AEWB1_LINK_MAX_CH);

    for(chId=0; chId<pOutputQInfo->queInfo.numCh; chId++)
    {
        pOutChInfo          = &pOutputQInfo->queInfo.chInfo[chId];
        pOutChInfo->flags   = 0;
        pOutChInfo->height  = 0;
        pOutChInfo->width   = 0;
    }

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                1,
                                pInputQInfo,
                                1,
                                pOutputQInfo);

    if(pAlgObj->algLinkCreateParams.numOutBuffers >
        ISS_AEWB1_LINK_MAX_NUM_OUTPUT)
    {
        pAlgObj->algLinkCreateParams.numOutBuffers =
            ISS_AEWB1_LINK_MAX_NUM_OUTPUT;
    }

    pAlgObj->lock = BspOsal_semCreate(1u, TRUE);
    UTILS_assert(NULL != pAlgObj->lock);

    /* Allocate input and output buffers for the DCC*/
    if (pAlgObj->algLinkCreateParams.enableDcc)
    {
        status = Dcc_Create(pAlgObj,
            &pAlgObj->algLinkCreateParams.memAllocInfo);
        UTILS_assert(0 == status);
    }

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

        pMetaDataBuffer->numMetaDataPlanes  =
            pAlgObj->algLinkCreateParams.numH3aPlanes;

        pMetaDataBuffer->metaBufSize[0U] = ISS_AEWB1_LINK_MAX_BUF_SIZE;

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

        ((AlgorithmLink_IssAewbOutParams*)
            pMetaDataBuffer->bufAddr[0U])->channelId =
                pAlgObj->algLinkCreateParams.channelId;
        ((AlgorithmLink_IssAewbOutParams*)
            pMetaDataBuffer->bufAddr[0U])->numParams =
                pAlgObj->algLinkCreateParams.numH3aPlanes;

        pMetaDataBuffer->flags = 0;

        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /* Create AWB Algorithm,
        created only if mode is AE/AWB/AEWB
        For the DCC only mode, where mode is set to none, algorithm instance
        is not created */
    if ((ALGORITHMS_ISS_AEWB_MODE_AWB == pAlgObj->algLinkCreateParams.mode) ||
        (ALGORITHMS_ISS_AEWB_MODE_AE == pAlgObj->algLinkCreateParams.mode) ||
        (ALGORITHMS_ISS_AEWB_MODE_AEWB == pAlgObj->algLinkCreateParams.mode))
    {
        UInt32 pixCtWin;

        pH3aParams = &pAlgObj->algLinkCreateParams.h3aParams;

        /* Calculate the Pixel count in the a window */
        pixCtWin = (pH3aParams->winSizeV /
                    pH3aParams->winSkipV) *
                   (pH3aParams->winSizeH /
                    pH3aParams->winSkipH);

        for(chId=0; chId<pOutputQInfo->queInfo.numCh; chId++)
        {
            pAlgObj->algHndl[chId] = ALG_aewbCreate(
            pAlgObj->algLinkCreateParams.mode,
            pH3aParams->winCountH, pH3aParams->winCountV, pixCtWin,
            pAlgObj->algLinkCreateParams.dataFormat,
            pAlgObj->algLinkCreateParams.numSteps,
            &pAlgObj->algLinkCreateParams.aeDynParams,
            pAlgObj->algLinkCreateParams.calbData,
            &pAlgObj->algLinkCreateParams.memAllocInfo,
                1);

            UTILS_assert(NULL != pAlgObj->algHndl[chId]);
        }
    }
    else
    {
        for(chId=0; chId<pOutputQInfo->queInfo.numCh; chId++)
        {
                pAlgObj->algHndl[chId] = NULL;
    }
    }

    /* By Default, both the algorithms are in Auto mode,
       it can be later on changed to Manual mode by calling set_2a_params
       ioctl */
    pAlgObj->aewbOut[0].aeMode = 0;
    pAlgObj->aewbOut[0].awbMode = 0;

    /* For SRV, AE is in Auto mode for all channels
        AWB is in Auto mode for channel 0 and manual
        mode for all other channels. Channels 1-3 will
        use AWB results computed for Channel 0
    */

    for(chId=1U; chId<pOutputQInfo->queInfo.numCh; chId++)
    {
        pAlgObj->aewbOut[chId].aeMode = 0;
        pAlgObj->aewbOut[chId].awbMode = 1U;
    }

    pAlgObj->isFirstFrameRecv    = FALSE;

    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_ISS_AEWB");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    System_assertLinkMemAllocOutOfMem(
        &pAlgObj->algLinkCreateParams.memAllocInfo,
        "ALG_ISS_AEWB"
        );

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmLink_issAewb1RunAlg(
    AlgorithmLink_IssAewbObj *pAlgObj,
    System_MetaDataBuffer *pInMetaBuf,
    System_MetaDataBuffer *pOutMetaBuf,
    UInt32 planeId,
    UInt32 chNum)
{
    AlgorithmLink_IssAewbOutParams *pAlgOut = NULL;
    ALG_Output output = {0};

    Cache_inv(
        pInMetaBuf->bufAddr[planeId],
        pInMetaBuf->metaBufSize[planeId],
        Cache_Type_ALLD,
        TRUE);

    /* When AEWB is enabled only for one channel, chnum for the Algorithm is 0 */
    if ((UInt32)TRUE == pAlgObj->algLinkCreateParams.runAewbOnlyForOneCh)
    {
        chNum = 0U;
    }

    /* Update Dynamic Parameters,
       as of now, there is no interface to do this, so using
       default parameters only */

    /* Run AE and AWB Algorithms */
    ALG_aewbRun(pAlgObj->algHndl[chNum], pInMetaBuf->bufAddr[planeId], &output, chNum);

    /* Convert to format suitable for next link (ISS ISP processing)
     */
    pAlgOut
        = (AlgorithmLink_IssAewbOutParams*) pOutMetaBuf->bufAddr[0U];

    pAlgOut->channelId = chNum;

    BspOsal_semWait(pAlgObj->lock, BSP_OSAL_WAIT_FOREVER);
    /* Copy Parameters for Auto Mode */
    if (!pAlgObj->aewbOut[chNum].awbMode)
    {
        pAlgOut->outPrms[planeId].useWbCfg = output.useWbCfg;
        pAlgOut->outPrms[planeId].gain[0U] = output.rGain;
        pAlgOut->outPrms[planeId].gain[1U] = output.grGain;
        pAlgOut->outPrms[planeId].gain[2U] = output.gbGain;
        pAlgOut->outPrms[planeId].gain[3U] = output.bGain;

        pAlgOut->outPrms[planeId].offset[0U] = output.rOffset;
        pAlgOut->outPrms[planeId].offset[1U] = output.grOffset;
        pAlgOut->outPrms[planeId].offset[2U] = output.gbOffset;
        pAlgOut->outPrms[planeId].offset[3U] = output.bOffset;

        pAlgOut->outPrms[planeId].useColorTemp = output.useColorTemp;
        pAlgOut->outPrms[planeId].colorTemparature =
            output.colorTemparature;

        if (TRUE == output.useColorTemp)
        {
            pAlgObj->aewbOut[chNum].colorTemp = output.colorTemparature;
        }
        if (TRUE == output.useWbCfg)
        {
            pAlgObj->aewbOut[chNum].rGain = output.rGain;
            pAlgObj->aewbOut[chNum].gGain = output.grGain;
            pAlgObj->aewbOut[chNum].bGain = output.bGain;
        }
    }
    else
    {
        pAlgOut->outPrms[planeId].useWbCfg = TRUE;
        pAlgOut->outPrms[planeId].gain[0U] = pAlgObj->aewbOut[0].rGain;
        pAlgOut->outPrms[planeId].gain[1U] = pAlgObj->aewbOut[0].gGain;
        pAlgOut->outPrms[planeId].gain[2U] = pAlgObj->aewbOut[0].gGain;
        pAlgOut->outPrms[planeId].gain[3U] = pAlgObj->aewbOut[0].bGain;

        pAlgOut->outPrms[planeId].offset[0U] = 0;
        pAlgOut->outPrms[planeId].offset[1U] = 0;
        pAlgOut->outPrms[planeId].offset[2U] = 0;
        pAlgOut->outPrms[planeId].offset[3U] = 0;

        pAlgOut->outPrms[planeId].useColorTemp = TRUE;
        pAlgOut->outPrms[planeId].colorTemparature =
            pAlgObj->aewbOut[0].colorTemp;
    }

    /* Copy Parameters for Auto Mode */
    if ((ALGORITHMS_ISS_AEWB_MODE_AE == pAlgObj->algLinkCreateParams.mode) ||
        (ALGORITHMS_ISS_AEWB_MODE_AEWB == pAlgObj->algLinkCreateParams.mode))
    {
        if (!pAlgObj->aewbOut[chNum].aeMode)
        {
            pAlgOut->outPrms[planeId].useAeCfg = output.useAeCfg;
            pAlgOut->outPrms[planeId].exposureTime = output.exposureTime;
            pAlgOut->outPrms[planeId].analogGain = output.analogGain;
            pAlgOut->outPrms[planeId].digitalGain = output.digitalGain;

            if (TRUE == output.useAeCfg)
            {
                /* Keeping copy of AE parameters for DCC */
                pAlgObj->aewbOut[chNum].expTime = output.exposureTime;
                pAlgObj->aewbOut[chNum].analogGain = output.analogGain;;
                pAlgObj->aewbOut[chNum].digitalGain = output.digitalGain;;
            }
        }
        else
        {
            pAlgOut->outPrms[planeId].useAeCfg = TRUE;
            pAlgOut->outPrms[planeId].exposureTime = pAlgObj->aewbOut[chNum].expTime;
            pAlgOut->outPrms[planeId].analogGain = pAlgObj->aewbOut[chNum].analogGain;
            pAlgOut->outPrms[planeId].digitalGain =
                pAlgObj->aewbOut[chNum].digitalGain;
        }
    }
    else
    {
        pAlgOut->outPrms[planeId].digitalGain =
            ALGORITHMS_AEWB_DEF_DIGITAL_GAIN;
    }

    if (pAlgOut->outPrms[planeId].useAeCfg)
    {
        pAlgObj->chObj[chNum].analogGain = pAlgOut->outPrms[planeId].analogGain;
        pAlgObj->chObj[chNum].expTime = pAlgOut->outPrms[planeId].exposureTime;
    }

    if (pAlgOut->outPrms[planeId].useColorTemp)
    {
        pAlgObj->chObj[chNum].colorTemp = pAlgOut->outPrms[planeId].colorTemparature;
    }

    BspOsal_semPost(pAlgObj->lock);

    return 0;
}

Int32 AlgorithmLink_issAewb1Process(void * pObj)
{
    UInt32 bufId, cnt;
    Int32 status;
    Bool   bufDropFlag;
    AlgorithmLink_IssAewbObj            * pAlgObj;
    System_BufferList                   inputBufList;
    AlgorithmLink_IssAewbCreateParams   * pLinkCreatePrms;
    System_Buffer                       * pSysOutBuffer;
    System_Buffer                       * pSysInBuffer;
    System_MetaDataBuffer               * pInMetaBuf;
    System_MetaDataBuffer               * pOutMetaBuf;
    System_BufferList                   bufListReturn;
    System_LinkStatistics               * linkStatsInfo;
    IssIspConfigurationParameters       * pIspCfg;

    pAlgObj = (AlgorithmLink_IssAewbObj *)
                AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pAlgObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pLinkCreatePrms = &pAlgObj->algLinkCreateParams;

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
            if ((UInt32)TRUE == pLinkCreatePrms->runAewbOnlyForOneCh)
            {
                if (pLinkCreatePrms->chId != pSysInBuffer->chNum)
                {
                    /* First release this buffer back to input */
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
                    continue;
                }
            }
            else
            {
                UTILS_assert(pSysInBuffer->chNum <
                             pAlgObj->outputQInfo.queInfo.numCh);
            }

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
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp =
                    Utils_getCurGlobalTimeInUsec();
                pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;
                pInMetaBuf  = (System_MetaDataBuffer *) pSysInBuffer->payload;

                pOutMetaBuf->numMetaDataPlanes = pInMetaBuf->numMetaDataPlanes;
                pIspCfg = (IssIspConfigurationParameters *)
                    ((UInt32)pOutMetaBuf->bufAddr[0U] +
                        sizeof(AlgorithmLink_IssAewbOutParams));

                /* Run AEWB Algorithm only if it is enabled at create time */
                if ((ALGORITHMS_ISS_AEWB_MODE_AWB == pLinkCreatePrms->mode) ||
                    (ALGORITHMS_ISS_AEWB_MODE_AE == pLinkCreatePrms->mode) ||
                    (ALGORITHMS_ISS_AEWB_MODE_AEWB == pLinkCreatePrms->mode))
                {
                    for (cnt = 0u; cnt < pOutMetaBuf->numMetaDataPlanes;
                         cnt ++)
                    {
                        AlgorithmLink_issAewb1RunAlg(pAlgObj, pInMetaBuf,
                            pOutMetaBuf, cnt, pSysInBuffer->chNum);
                    }
                }

                if (TRUE == pAlgObj->algLinkCreateParams.enableDcc)
                {
                    Dcc_update_params(pAlgObj, pIspCfg, pSysInBuffer->chNum);
                }

                Cache_wb(
                    pOutMetaBuf->bufAddr[0],
                    pOutMetaBuf->metaBufSize[0],
                    Cache_Type_ALLD,
                    TRUE);

                /* This function should not be null */
                UTILS_assert(NULL != pLinkCreatePrms->cfgCbFxn);

                if ((UInt32)TRUE == pLinkCreatePrms->runAewbOnlyForOneCh)
                {
                    for (cnt = 0U; cnt < pAlgObj->inQueInfo.numCh; cnt ++)
                    {
                        ((AlgorithmLink_IssAewbOutParams*)
                            pOutMetaBuf->bufAddr[0U])->channelId = cnt;
                        pIspCfg->channelId = cnt;
                        pLinkCreatePrms->cfgCbFxn(
                            (AlgorithmLink_IssAewbOutParams *)
                                pOutMetaBuf->bufAddr[0U],
                            pIspCfg, pLinkCreatePrms->appData);
                    }
                }
                else
                {
                    pLinkCreatePrms->cfgCbFxn(
                        (AlgorithmLink_IssAewbOutParams *)
                            pOutMetaBuf->bufAddr[0U],
                        pIspCfg, pLinkCreatePrms->appData);
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


                if ((TRUE == pLinkCreatePrms->isWdrEnable) &&
                    (NULL != pLinkCreatePrms->mergeCbFxn))
                {
                    pLinkCreatePrms->mergeCbFxn(
                        (AlgorithmLink_IssAewbOutParams *)
                            pOutMetaBuf->bufAddr[0U], pIspCfg,
                        pLinkCreatePrms->appData);
                }
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

Int32 AlgorithmLink_issAewb1Control(void *pObj, void *pControlParams)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_IssAewbObj *pAlgObj = NULL;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm = NULL;
    AlgorithmLink_IssAewbAeControlParams *aeCtrlPrms = NULL;
    AlgorithmLink_IssAewbAwbControlParams *awbCtrlPrms = NULL;
    AlgorithmLink_IssAewbDccControlParams *dccCtrlPrms = NULL;
    AlgorithmLink_IssAewbCreateParams     *createPrms;

    pAlgObj = (AlgorithmLink_IssAewbObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    createPrms = &pAlgObj->algLinkCreateParams;

    /* Check for errors */
    /* AE/AWB parameters can be changed only if they are created/enabled
       at the algorithm create time */
    if ((ALGORITHMS_ISS_AEWB_MODE_AWB != createPrms->mode) &&
        (ALGORITHMS_ISS_AEWB_MODE_AEWB != createPrms->mode))
    {
        /* AWB parameters cannot be set since create mode does not
           include AWB */
        if (ALGORITHM_AEWB_LINK_CMD_SET_AWB_CALB_DATA ==
            pAlgLinkControlPrm->controlCmd)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }
    if ((ALGORITHMS_ISS_AEWB_MODE_AE != createPrms->mode) &&
        (ALGORITHMS_ISS_AEWB_MODE_AEWB != createPrms->mode))
    {
        /* AE parameters cannot be set since create mode does not
           include AE */
        if (ALGORITHM_AEWB_LINK_CMD_SET_AE_DYNAMIC_PARAMS ==
            pAlgLinkControlPrm->controlCmd)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }
    /* None of the DCC commands are valid if DCC is not enabled
       at create time */
    if (!createPrms->enableDcc)
    {
        if ((ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS ==
                pAlgLinkControlPrm->controlCmd) ||
            (ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS ==
                pAlgLinkControlPrm->controlCmd))
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        /* Returning from here,
           This voilates MICRA-C */
        return (status);
    }

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     */
    switch(pAlgLinkControlPrm->controlCmd)
    {
        /* Control command is to set AE dynamic parameters */
        case ALGORITHM_AEWB_LINK_CMD_SET_AE_DYNAMIC_PARAMS:
        {
            aeCtrlPrms = (AlgorithmLink_IssAewbAeControlParams *)
                                    pControlParams;

            if (NULL != aeCtrlPrms)
            {
                UInt32 chId;
                for(chId = 0; chId < ISS_AEWB1_LINK_MAX_CH; chId++)
                {
                      if(pAlgObj->algHndl[chId])
                      {
                status = ALG_aewbSetAeDynParams(
                                        pAlgObj->algHndl[chId],
                            aeCtrlPrms->aeDynParams);
            }
                }
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        }

        /* Control command is to set AWB Calibration data */
        case ALGORITHM_AEWB_LINK_CMD_SET_AWB_CALB_DATA:
        {
            awbCtrlPrms = (AlgorithmLink_IssAewbAwbControlParams *)
                                    pControlParams;

            if (NULL != awbCtrlPrms)
            {
                UInt32 chId;
                for(chId = 0; chId < ISS_AEWB1_LINK_MAX_CH; chId++)
                {
                      if(pAlgObj->algHndl[chId])
                      {
                status = ALG_aewbSetAwbCalbData(
                            pAlgObj->algHndl,
                            awbCtrlPrms->calbData);
            }
                }
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        }

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_issAewb1PrintStatistics(pObj, pAlgObj);
            break;

        /* Parse DCC parameters and set them in ISP */
        case ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS:
        {
            dccCtrlPrms = (AlgorithmLink_IssAewbDccControlParams *)
                                    pControlParams;

            if (NULL != dccCtrlPrms)
            {
                if (NULL != pAlgObj->dccObj.dccInBuf)
                {
                    dccCtrlPrms->dccBuf = pAlgObj->dccObj.dccInBuf;
                }
                else
                {
                    dccCtrlPrms->dccBuf = NULL;
                }
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        }

        /* Parse DCC parameters and set them in ISP */
        case ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS:
        {
            dccCtrlPrms = (AlgorithmLink_IssAewbDccControlParams *)
                                    pControlParams;

            if (NULL != dccCtrlPrms)
            {
                /* ISP Config is local object, so ok to reset it. */
                memset(&pAlgObj->dccObj.ispCfgPrms,
                       0,
                       sizeof(IssIspConfigurationParameters));
                memset(&pAlgObj->dccObj.simcopCfgPrms,
                       0,
                       sizeof(IssM2mSimcopLink_ConfigParams));
                status = Dcc_parse_and_save_params(
                            pAlgObj,
                            &pAlgObj->dccObj.ispCfgPrms,
                            &pAlgObj->dccObj.simcopCfgPrms,
                            dccCtrlPrms->dccBufSize);

                if (0 == status)
                {
                    /* Set the AWB Calb Parameters */
                    if (TRUE == pAlgObj->dccObj.dccOutPrms.useAwbCalbCfg)
                    {
                        /* Setting AWB Calibration data immediately
                            structures AlgorithmLink_IssAewbAwbCalbData and
                            awb_calc_data_t are exactly same, so type
                            casting here, awb_calc_data_t is used internally
                            by algorithm, whereas
                            AlgorithmLink_IssAewbAwbCalbData is used by the
                            AEWB link plugin */

                        UInt32 chId;
                        for(chId = 0; chId < ISS_AEWB1_LINK_MAX_CH; chId++)
                        {
                            if(pAlgObj->algHndl[chId])
                            {
                                status = ALG_aewbSetAwbCalbData(
                                    pAlgObj->algHndl[chId],
                                    (AlgorithmLink_IssAewbAwbCalbData *)
                                    &pAlgObj->dccObj.dccOutPrms.
                                        awbCalbData);
                            }
                        }
                    }

                    if (NULL != createPrms->dccIspCfgFxn)
                    {
                        /* Call the callback function to update
                           parameters in ISP */
                        pAlgObj->dccObj.ispCfgPrms.channelId =
                            pAlgObj->algLinkCreateParams.channelId;
                        createPrms->dccIspCfgFxn(
                            &pAlgObj->dccObj.ispCfgPrms,
                            &pAlgObj->dccObj.simcopCfgPrms,
                            createPrms->dccAppData);
                    }
                }
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        }

        case ALGORITHM_AEWB_LINK_CMD_SET_CAMERA_INFO:
        {
            AlgorithmLink_IssAewbDccCameraInfo *pCamInfo;

            pCamInfo = (AlgorithmLink_IssAewbDccCameraInfo *)
                                    pControlParams;

            if (NULL != pCamInfo)
            {
                pAlgObj->algLinkCreateParams.dccCameraId = pCamInfo->cameraId;
                pAlgObj->dccObj.width = pCamInfo->width;
                pAlgObj->dccObj.height = pCamInfo->height;
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }

            break;
        }

        case ALGORITHM_AEWB_LINK_CMD_GET_2A_PARAMS:
        {
/*
           Currently there is no mechanism to pass camera ID to control
           commands. Till this is added, control is assumed to be on
           camera 0 only.
*/
            AlgorithmLink_IssAewb2AControlParams *pAewb2APrms;

            pAewb2APrms = (AlgorithmLink_IssAewb2AControlParams *)
                                    pControlParams;

            if (NULL != pAewb2APrms)
            {
                /* Copy Parameters only if Auto mode is selected */
                memcpy(&pAewb2APrms->aewb2APrms, &pAlgObj->aewbOut,
                    sizeof(AlgorithmLink_IssAewb2AParams));
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        }

        case ALGORITHM_AEWB_LINK_CMD_SET_2A_PARAMS:
        {
/*
           Currently there is no mechanism to pass camera ID to control
           commands. Till this is added, control is assumed to be on
           camera 0 only.
*/
            AlgorithmLink_IssAewb2AControlParams *pAewb2APrms;

            pAewb2APrms = (AlgorithmLink_IssAewb2AControlParams *)
                                    pControlParams;

            if (NULL != pAewb2APrms)
            {
                BspOsal_semWait(pAlgObj->lock, BSP_OSAL_WAIT_FOREVER);
                if (pAewb2APrms->aewb2APrms.aeMode)
                {
                    /* Copy Fixed output parameters for AE */
                    pAlgObj->aewbOut[0].digitalGain = pAewb2APrms->aewb2APrms.digitalGain;
                    pAlgObj->aewbOut[0].analogGain = pAewb2APrms->aewb2APrms.analogGain;
                    pAlgObj->aewbOut[0].expTime = pAewb2APrms->aewb2APrms.expTime;
                    pAlgObj->aewbOut[0].aeMode = TRUE;
                }
                else
                {
                    /* AUTO Mode is selected */
                    pAlgObj->aewbOut[0].aeMode = FALSE;
                }

                if (pAewb2APrms->aewb2APrms.awbMode)
                {
                    /* Copy Fixed output parameters for AWB */
                    pAlgObj->aewbOut[0].rGain = pAewb2APrms->aewb2APrms.rGain;
                    pAlgObj->aewbOut[0].gGain = pAewb2APrms->aewb2APrms.gGain;
                    pAlgObj->aewbOut[0].bGain = pAewb2APrms->aewb2APrms.bGain;
                    pAlgObj->aewbOut[0].colorTemp = pAewb2APrms->aewb2APrms.colorTemp;
                    pAlgObj->aewbOut[0].awbMode = TRUE;
                }
                else
                {
                    /* AUTO Mode is selected */
                    pAlgObj->aewbOut[0].awbMode = FALSE;
                }
                BspOsal_semPost(pAlgObj->lock);
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        }
        default:
            break;
    }

    return (status);
}

Int32 AlgorithmLink_issAewb1Stop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_issAewb1Delete(void * pObj)
{

    UInt32 status;
    UInt32 bufId;
    UInt32 chId;
    AlgorithmLink_IssAewbObj *pAlgObj;
    System_MetaDataBuffer *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_IssAewbObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if (NULL != pAlgObj->lock)
    {
        BspOsal_semDelete(&pAlgObj->lock);
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

    for(chId=0; chId<pAlgObj->outputQInfo.queInfo.numCh; chId++)
    {

    /* Delete only if the algorithm instance is created */
            if (NULL != pAlgObj->algHndl[chId])
    {
                   ALG_aewbDelete(pAlgObj->algHndl[chId],
                   &pAlgObj->algLinkCreateParams.memAllocInfo);
                   pAlgObj->algHndl[chId] = NULL;
          }
    }

    if (TRUE == pAlgObj->algLinkCreateParams.enableDcc)
    {
        Dcc_delete(pAlgObj,
            &pAlgObj->algLinkCreateParams.memAllocInfo);
    }

    if(System_useLinkMemAllocInfo(
        &pAlgObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_LOCAL,
            pAlgObj,
            sizeof(AlgorithmLink_IssAewbObj)
            );
    }

    pAlgObj = NULL;

    return status;
}

Int32 AlgorithmLink_issAewb1PrintStatistics(void *pObj,
                AlgorithmLink_IssAewbObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
                            "ALG_ISS_AEWB",
                            TRUE);

    Utils_printLatency("ALG_ISS_AEWB",
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                        TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

