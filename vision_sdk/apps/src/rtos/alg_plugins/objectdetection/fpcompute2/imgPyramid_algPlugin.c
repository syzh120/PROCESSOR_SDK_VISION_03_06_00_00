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
 * \file imgPyramid_algPlugin.c
 *
 * \brief  This file contains plug in functions for Image Pyramid
 *
 * \version 0.0 (Oct 2015) : [BJ] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "imgPyramid_priv.h"
#include "iResizer.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

Int32 AlgorithmLink_imgPyramidCreate(void *pObj, void *pCreateParams);
Int32 AlgorithmLink_imgPyramidProcess(void * pObj);
Int32 AlgorithmLink_imgPyramidControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_imgPyramidStop(void * pObj);
Int32 AlgorithmLink_imgPyramidDelete(void * pObj);
Int32 AlgorithmLink_imgPyramidPrintStatistics (void *pObj,
                        AlgorithmLink_ImgPmdObj *pImgPmdObj);

Void Alg_imgPyramidCalcScaleParams(AlgorithmLink_ImgPmdObj *pImgPmdObj);
Void Alg_imgPyramidAllocBuffers(Void *pObj, AlgorithmLink_ImgPmdObj *pImgPmdObj);
Void Alg_imgPyramidFreeBuffers(AlgorithmLink_ImgPmdObj *pImgPmdObj);
Void AlgorithmLink_generatePyramid(
    AlgorithmLink_ImgPmdObj *pImgPmdObj,
    System_Buffer *pInBuff,
    System_Buffer *pOutBuff);
Int32 AlgorithmLink_imgPyramidPutEmptyBuffers(
    Void *pObj,
    UInt16 queId,
    System_BufferList *pBufList);


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of Image Pyramid algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidComputation_initPlugin ()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_imgPyramidCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_imgPyramidProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_imgPyramidControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_imgPyramidStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_imgPyramidDelete;

    algId = ALGORITHM_LINK_IPU_ALG_IMG_PYRAMID;

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for Image Pyramid algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidCreate(void *pObj, void *pCreateParams)
{
    Int32                           status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                          cnt, found = 0, i;
    System_LinkInfo                 prevLinkInfo;
    UInt32                          prevLinkQueId;
    AlgorithmLink_ImgPmdObj       * pImgPmdObj;
    AlgorithmLink_ImgPyramidCreateParams * pImgPmdCreateParams;
    AlgorithmLink_OutputQueueInfo * pOutputQInfo;
    AlgorithmLink_InputQueueInfo  * pInputQInfo;

    pImgPmdCreateParams = (AlgorithmLink_ImgPyramidCreateParams *)pCreateParams;

    if (pImgPmdCreateParams->numOutBuffers > ALG_LINK_IMG_PYRAMID_MAX_OUT_BUF)
    {
        pImgPmdCreateParams->numOutBuffers = ALG_LINK_IMG_PYRAMID_MAX_OUT_BUF;
    }

    /* Get the resizer module to be used for image pyramid */
    for (cnt = 0U; cnt < ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_MAX; cnt ++)
    {
        if (pImgPmdCreateParams->rszModule == gImgPyramidRszModule[cnt].rszModule)
        {
            found = 1;
            break;
        }
    }
    if ((0 == found) || (cnt == ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_MAX))
    {
        Vps_printf(" ALG_IMGPYRAMID: Given Resizer module is not supported\n");
        UTILS_assert(FALSE);
    }

    if (TRUE == pImgPmdCreateParams->enableRoi)
    {
        /* All other parameters must be even */
        UTILS_assert(0U == (pImgPmdCreateParams->roiStartX % 2U));
        UTILS_assert(0U == (pImgPmdCreateParams->roiStartY % 2U));
        UTILS_assert(0U == (pImgPmdCreateParams->roiWidth % 2U));
        UTILS_assert(0U == (pImgPmdCreateParams->roiHeight % 2U));
    }

    System_resetLinkMemAllocInfo(&pImgPmdCreateParams->memAllocInfo);

    if(System_useLinkMemAllocInfo(&pImgPmdCreateParams->memAllocInfo)==FALSE)
    {
        pImgPmdObj = (AlgorithmLink_ImgPmdObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_ImgPmdObj),
                        128);
    }
    else
    {
        pImgPmdObj = (AlgorithmLink_ImgPmdObj *)
                    System_allocLinkMemAllocInfo(
                        &pImgPmdCreateParams->memAllocInfo,
                        sizeof(AlgorithmLink_ImgPmdObj),
                        128);
    }
    UTILS_assert(pImgPmdObj!=NULL);

    /* Reset complete Image Pyramid Object */
    memset(pImgPmdObj, 0x0, sizeof(AlgorithmLink_ImgPmdObj));

    /* Initialize pointer to the structure containing driver's
       function pointer */
    pImgPmdObj->pRszDrvFxn = &gImgPyramidRszModule[cnt];

    pOutputQInfo = &pImgPmdObj->outputQInfo;
    pInputQInfo  = &pImgPmdObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pImgPmdObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(&pImgPmdObj->algLinkCreateParams, pImgPmdCreateParams,
        sizeof(AlgorithmLink_ImgPyramidCreateParams));

    /*
     * Populating parameters corresponding to Q usage of image pyramid
     * algorithm link
     */
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    prevLinkQueId = pImgPmdCreateParams->inQueParams.prevLinkQueId;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     */
    status = System_linkGetInfo(
        pImgPmdCreateParams->inQueParams.prevLinkId, &prevLinkInfo);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    UTILS_assert(prevLinkInfo.queInfo[prevLinkQueId].numCh == 1);
    if(System_Link_Ch_Info_Get_Flag_Data_Format(
        prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].flags) !=
            SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(0);
    }
    UTILS_assert(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].pitch[0] >=
                 prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].width);

    /* Check for errors in create parameters */
    UTILS_assert(pImgPmdObj->algLinkCreateParams.numScales <=
           ALGORITHLINK_IMGPYRAMID_MAX_SCALES);
    UTILS_assert(pImgPmdObj->algLinkCreateParams.scaleSteps <=
           pImgPmdCreateParams->numScales);

    pOutputQInfo->queInfo.numCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    /*
     * Taking a copy of input channel info in the link object for any future
     * use
     */
    memcpy((void *)&(pImgPmdObj->inputChInfo),
           (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
           sizeof(System_LinkChInfo));
    memcpy(&pOutputQInfo->queInfo.chInfo[0],
           &pImgPmdObj->inputChInfo,
           sizeof(System_LinkChInfo));

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                1U,
                                pInputQInfo,
                                1U,
                                pOutputQInfo
                                );

    pImgPmdObj->lock = BspOsal_semCreate(1u, TRUE);
    UTILS_assert(NULL != pImgPmdObj->lock);

    if (FALSE == pImgPmdObj->algLinkCreateParams.enableRoi)
    {
        pImgPmdObj->algLinkCreateParams.roiStartX = 0U;
        pImgPmdObj->algLinkCreateParams.roiStartY = 0U;
        pImgPmdObj->algLinkCreateParams.roiWidth =
            pImgPmdObj->inputChInfo.width;
        pImgPmdObj->algLinkCreateParams.roiHeight =
            pImgPmdObj->inputChInfo.height;
    }

    UTILS_assert(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].width >=
          (pImgPmdCreateParams->roiWidth +
           pImgPmdCreateParams->roiStartX));
    UTILS_assert(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].height >=
          (pImgPmdCreateParams->roiHeight +
           pImgPmdCreateParams->roiStartY));

    /* Allocate Frame Descriptors */
    for (i = 0; i < pImgPmdCreateParams->numOutBuffers; i ++)
    {
        pImgPmdObj->outFrmDesc[i] = Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            sizeof(AlgorithmLink_ImgPyramidFrameDesc) *
            pImgPmdCreateParams->numScales,
            ALG_IMG_PMD_BUFFER_ALIGN);

        UTILS_assert(NULL != pImgPmdObj->outFrmDesc[i]);

        memset(pImgPmdObj->outFrmDesc[i], 0x0,
            sizeof(AlgorithmLink_ImgPyramidFrameDesc) *
            pImgPmdCreateParams->numScales);
    }

    /* Calculate the resizer output frames size based on input frames size
       and ROI */
    Alg_imgPyramidCalcScaleParams(pImgPmdObj);

    /* Allocate the output frames */
    Alg_imgPyramidAllocBuffers(pObj, pImgPmdObj);

    /* Create Driver */
    UTILS_assert(NULL != pImgPmdObj->pRszDrvFxn);
    UTILS_assert(NULL != pImgPmdObj->pRszDrvFxn->createDrv);
    pImgPmdObj->pRszObj = pImgPmdObj->pRszDrvFxn->createDrv(pImgPmdObj, NULL);
    UTILS_assert(pImgPmdObj->pRszObj != NULL);

    pImgPmdObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_IMG_PYRAMID");
    UTILS_assert(NULL != pImgPmdObj->linkStatsInfo);

    pImgPmdObj->isFirstFrameRecv = FALSE;

    System_assertLinkMemAllocOutOfMem(
        &pImgPmdCreateParams->memAllocInfo,
        "ALG_IMG_PYRAMID");


    AlgorithmLink_registerPutEmptyBuffersPlugin(
        pObj,
        AlgorithmLink_imgPyramidPutEmptyBuffers);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for image pyramid algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidProcess(void * pObj)
{
    AlgorithmLink_ImgPmdObj    *pImgPmdObj = NULL;
    Int32                       inputQId;
    UInt32                      channelId;
    Int32                       status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                      bufId, outputQId = 0U;
    System_BufferList           inputBufList;
    System_BufferList           inputBufListReturn;
    System_BufferList           outputBufListReturn;
    System_Buffer              *pSysBufferInput = NULL, *pSysOutBuffer = NULL;
    Bool                        bufDropFlag;
    System_LinkStatistics      *linkStatsInfo = NULL;
    AlgorithmLink_ImgPyramidCreateParams *pImgPmdCreateParams = NULL;

    pImgPmdObj = (AlgorithmLink_ImgPmdObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pImgPmdObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    pImgPmdCreateParams = &pImgPmdObj->algLinkCreateParams;

    /* Getting input buffers from previous link */
    System_getLinksFullBuffers(pImgPmdCreateParams->inQueParams.prevLinkId,
                               pImgPmdCreateParams->inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        /* One receiving first frame, reset the statistics */
        if(pImgPmdObj->isFirstFrameRecv==FALSE)
        {
            pImgPmdObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    1U,
                    1U);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0U; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput = inputBufList.buffers[bufId];

            if ((pSysBufferInput == NULL) ||
                (pSysBufferInput->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME))
            {
                bufDropFlag = TRUE;
                linkStatsInfo->linkStats.inBufErrorCount ++;
            }
            else
            {
                channelId = pSysBufferInput->chNum;
                UTILS_assert(channelId < pImgPmdObj->outputQInfo.queInfo.numCh);

                linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;

                status = AlgorithmLink_getEmptyOutputBuffer(
                                        pObj,
                                        outputQId,
                                        pSysBufferInput->chNum,
                                        &pSysOutBuffer);

                if(status != SYSTEM_LINK_STATUS_SOK)
                {
                    linkStatsInfo->linkStats.chStats
                                [channelId].inBufDropCount++;
                    linkStatsInfo->linkStats.chStats
                                [channelId].outBufDropCount[0]++;
                }
                else
                {
                    pSysOutBuffer->srcTimestamp       = pSysBufferInput->srcTimestamp;
                    pSysOutBuffer->frameId            = pSysBufferInput->frameId;
                    pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                    BspOsal_semWait(pImgPmdObj->lock, BSP_OSAL_WAIT_FOREVER);

                    /* Process Data */
                    AlgorithmLink_generatePyramid(
                        pImgPmdObj,
                        pSysBufferInput,
                        pSysOutBuffer);

                    BspOsal_semPost(pImgPmdObj->lock);

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pSysOutBuffer->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pSysBufferInput->srcTimestamp);

                    linkStatsInfo->linkStats.chStats
                              [channelId].inBufProcessCount++;
                    linkStatsInfo->linkStats.chStats
                              [channelId].outBufCount[0]++;

                    /*
                     * Putting filled buffer into output full buffer Q
                     * Note that this does not mean algorithm has
                     * freed the output buffer
                     */
                    status = AlgorithmLink_putFullOutputBuffer(pObj,
                                                               outputQId,
                                                               pSysOutBuffer);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /* Informing next link that a new data has peen put for its
                     * processing
                     */
                    System_sendLinkCmd(
                        pImgPmdCreateParams->outQueParams.nextLink,
                        SYSTEM_CMD_NEW_DATA,
                        NULL);

                    /*
                     * Releasing (Free'ing) output buffer, since algorithm does not need
                     * it for any future usage.
                     * In case of INPLACE computation, there is no need to free output
                     * buffer, since it will be freed as input buffer.
                     */
                    outputBufListReturn.numBuf     = 1;
                    outputBufListReturn.buffers[0] = pSysOutBuffer;

                    AlgorithmLink_releaseOutputBuffer(pObj,
                                                      outputQId,
                                                      &outputBufListReturn);

                    bufDropFlag = FALSE;
                }

            } /* Input Buffer validity */

            if (TRUE == bufDropFlag)
            {
                /*
                 * Releasing (Free'ing) input buffer, since algorithm does not need
                 * it for any future usage.
                 */
                inputQId                      = 0;
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pSysBufferInput;
                AlgorithmLink_releaseInputBuffer(
                    pObj,
                    inputQId,
                    pImgPmdCreateParams->inQueParams.prevLinkId,
                    pImgPmdCreateParams->inQueParams.prevLinkQueId,
                    &inputBufListReturn,
                    &bufDropFlag);
            }
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for image pyramid algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_imgPyramidControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_ImgPmdObj      * pImgPmdObj;
    AlgorithmLink_ControlParams  * pAlgLinkControlPrm;
    AlgorithmLink_ImgPyramidInfo * pImgPmdInfo = NULL;
    AlgorithmLink_ImgPyramidImgPyramidInfoControlParams *imgPyramidInfoControlParams;
    Int32                          status    = SYSTEM_LINK_STATUS_SOK;

    pImgPmdObj = (AlgorithmLink_ImgPmdObj *)
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
            AlgorithmLink_imgPyramidPrintStatistics(pObj, pImgPmdObj);
            break;

        case ALGORITHM_LINK_IMAGE_PYRAMID_CMD_GET_PYRAMID_INFO:
            imgPyramidInfoControlParams = (AlgorithmLink_ImgPyramidImgPyramidInfoControlParams *)
                                    pControlParams;

            if (NULL != imgPyramidInfoControlParams)
            {
                pImgPmdInfo = &(imgPyramidInfoControlParams->imgPyramidInfo);

                /* Copy Parameters from the Create Params */
                pImgPmdInfo->sreachStep = ALG_IMG_PMD_SREACH_STEP;
                pImgPmdInfo->numScales =
                    pImgPmdObj->algLinkCreateParams.numScales;
                pImgPmdInfo->scaleSteps =
                    pImgPmdObj->algLinkCreateParams.scaleSteps;

                /* Copy Output frame size information for all scales */
                memcpy(pImgPmdInfo->frmDesc,
                       pImgPmdObj->outFrmDesc[0U],
                       sizeof(AlgorithmLink_ImgPyramidFrameDesc) *
                       pImgPmdInfo->numScales);
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            break;
        default:
            status = SYSTEM_LINK_STATUS_EUNSUPPORTED_CMD;
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for image pyramid algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for image pyramid algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidDelete(void * pObj)
{
    Int32                    status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                   i;
    AlgorithmLink_ImgPmdObj *pImgPmdObj;

    pImgPmdObj = (AlgorithmLink_ImgPmdObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pImgPmdObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if (NULL != pImgPmdObj->lock)
    {
        BspOsal_semDelete(&pImgPmdObj->lock);
        pImgPmdObj->lock = NULL;
    }

    UTILS_assert(NULL != pImgPmdObj->pRszDrvFxn);
    UTILS_assert(NULL != pImgPmdObj->pRszDrvFxn->deleteDrv);
    pImgPmdObj->pRszDrvFxn->deleteDrv(pImgPmdObj->pRszObj, NULL);

    Alg_imgPyramidFreeBuffers(pImgPmdObj);

    /* Allocate Frame Descriptors */
    for (i = 0; i < pImgPmdObj->algLinkCreateParams.numOutBuffers; i ++)
    {
        status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pImgPmdObj->outFrmDesc[i],
            sizeof(AlgorithmLink_ImgPyramidFrameDesc) *
            pImgPmdObj->algLinkCreateParams.numScales);
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    if(System_useLinkMemAllocInfo(
        &pImgPmdObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_LOCAL,
            pImgPmdObj,
            sizeof(AlgorithmLink_ImgPmdObj));
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pImgPmdObj          [IN] image pyramid link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidPrintStatistics (void *pObj,
                        AlgorithmLink_ImgPmdObj *pImgPmdObj)
{

    UTILS_assert(NULL != pImgPmdObj->linkStatsInfo);

    Utils_printLinkStatistics(&pImgPmdObj->linkStatsInfo->linkStats, "ALG_IMG_PYRAMID", TRUE);

    Utils_printLatency("ALG_IMG_PYRAMID",
                       &pImgPmdObj->linkStatsInfo->linkLatency,
                       &pImgPmdObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}


/* ========================================================================== */
/*                 Internal Function Definations                              */
/* ========================================================================== */

Void Alg_imgPyramidCalcScaleParams(AlgorithmLink_ImgPmdObj *pImgPmdObj)
{
    UInt32 i, idx;
    UInt32 numScales, scaleSteps;
    UInt32 RoiCenterX, RoiCenterY, RoiHeight, RoiWidth;
    UInt32 xNum, yNum, xDen, imWidth, imHeight;
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc, *inFrmDesc;
    UInt32 dataFormat;
    UInt32 scaleRatiosQ12[ALG_IMAGE_PYRAMID_MAX_SCALE_STEPS];
    UInt32 scaleRatioQ12;
    UInt32 sreachStep;

    outFrmDesc = pImgPmdObj->outFrmDesc[0U];
    inFrmDesc = pImgPmdObj->inFrmDesc;

    /* The parameters for the first instance of input frame
       descriptors comes from the input channel
       The input frame size is same as the Roi provided.
       Assuming ROI is same is frame size if ROI is not required
       */
    inFrmDesc[0U].startX = pImgPmdObj->algLinkCreateParams.roiStartX;
    inFrmDesc[0U].startY = pImgPmdObj->algLinkCreateParams.roiStartY;
    inFrmDesc[0U].width = pImgPmdObj->algLinkCreateParams.roiWidth;
    inFrmDesc[0U].height = pImgPmdObj->algLinkCreateParams.roiHeight;
    /* orgWidth/orgHeight parameters are not used in inFrmDesc.
       its only width/height are used */
    inFrmDesc[0U].orgHeight = pImgPmdObj->inputChInfo.height;
    inFrmDesc[0U].orgWidth = pImgPmdObj->inputChInfo.width;
    inFrmDesc[0U].pitch[0U] = pImgPmdObj->inputChInfo.pitch[0U];
    inFrmDesc[0U].pitch[1U] = pImgPmdObj->inputChInfo.pitch[1U];
    inFrmDesc[0U].pitch[2U] = pImgPmdObj->inputChInfo.pitch[2U];

    /* The first output frame descriptror parameters are same
       as 0th instance of the input descriptor
       no scaling required for the first instance,
       Even buffer addresses are reused from the input frame.
       */
    memcpy(&outFrmDesc[0], &inFrmDesc[0],
        sizeof(AlgorithmLink_ImgPyramidFrameDesc));

    numScales = pImgPmdObj->algLinkCreateParams.numScales;
    scaleSteps = pImgPmdObj->algLinkCreateParams.scaleSteps;
    sreachStep = ALG_IMG_PMD_SREACH_STEP;

    /* Based on the number of steps, different number of scale ratio are used */
    if(scaleSteps == 6)
    {
        scaleRatiosQ12[0] = 8192U;
        scaleRatiosQ12[1] = 4597U;
        scaleRatiosQ12[2] = 5160U;
        scaleRatiosQ12[3] = 5792U;
        scaleRatiosQ12[4] = 6501U;
        scaleRatiosQ12[5] = 7298U;
    }
    else if(scaleSteps == 4)
    {
        scaleRatiosQ12[0] = 8192U;
        scaleRatiosQ12[1] = 4871U;
        scaleRatiosQ12[2] = 5792U;
        scaleRatiosQ12[3] = 6888U;
    }
    else
    {
        scaleRatiosQ12[0] = 8192U;
        scaleRatiosQ12[1] = 4466U;
        scaleRatiosQ12[2] = 4870U;
        scaleRatiosQ12[3] = 5311U;
        scaleRatiosQ12[4] = 5792U;
        scaleRatiosQ12[5] = 6316U;
        scaleRatiosQ12[6] = 6888U;
        scaleRatiosQ12[7] = 7512U;
    }

    /* Calculate original output frame size */
    for (i = 1U; i < numScales; i ++)
    {
        outFrmDesc[i].orgWidth =
            ((outFrmDesc[((i - 1U) / scaleSteps) * scaleSteps].orgWidth *
                (1 << ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)) /
                    scaleRatiosQ12[i % scaleSteps])&(~1);
        outFrmDesc[i].orgHeight =
            ((outFrmDesc[((i - 1U) / scaleSteps) * scaleSteps].orgHeight *
                (1 << ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)) /
                    scaleRatiosQ12[i % scaleSteps])&(~1);
    }

    RoiCenterX = pImgPmdObj->algLinkCreateParams.roiStartX +
        (pImgPmdObj->algLinkCreateParams.roiWidth / 2U);
    RoiCenterY = pImgPmdObj->algLinkCreateParams.roiStartY +
        (pImgPmdObj->algLinkCreateParams.roiHeight / 2U); ;
    RoiWidth = pImgPmdObj->algLinkCreateParams.roiWidth;
    RoiHeight = pImgPmdObj->algLinkCreateParams.roiHeight;

    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
        pImgPmdObj->inputChInfo.flags);

    /* Calculate the output frame parameters */
    for( i = 0; i < numScales; i++)
    {
        xNum  = ((RoiCenterX >> (i/scaleSteps)) *
            (1 << ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO));
        yNum  = ((RoiCenterY >> (i/scaleSteps)) *
            (1 << ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO));
        xDen  = (scaleRatiosQ12[i%scaleSteps]);
        imWidth  = outFrmDesc[i].orgWidth ;
        imHeight  = outFrmDesc[i].orgHeight;

        if(i%scaleSteps)
        {
            xNum = (xNum/xDen);
            yNum = (yNum/xDen);
        }
        else
        {
            xNum = (xNum/(1 << ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO));
            yNum = (yNum/(1 << ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO));
        }

        if ((RoiWidth >= imWidth) || ((0U != i) && (i%scaleSteps == 0)))
        {
            outFrmDesc[i].startX = 0;
            outFrmDesc[i].width = imWidth;
        }
        else
        {
            outFrmDesc[i].width = RoiWidth;
            outFrmDesc[i].startX = ((int)xNum-(int)outFrmDesc[i].width/2) < 0 ?
              0 : (xNum-outFrmDesc[i].width/2);
            outFrmDesc[i].startX = (outFrmDesc[i].startX + RoiWidth) > imWidth ?
              imWidth - outFrmDesc[i].width : outFrmDesc[i].startX;
        }

        if((RoiHeight >= imHeight) || ((0U != i) && (i%scaleSteps == 0)))
        {
            outFrmDesc[i].startY = 0;
            outFrmDesc[i].height = imHeight;
        }
        else
        {
            outFrmDesc[i].height = RoiHeight;
            outFrmDesc[i].startY =((int)yNum-(int)outFrmDesc[i].height/2) < 0 ?
                0 :(yNum-outFrmDesc[i].height/2) ;
            outFrmDesc[i].startY = (outFrmDesc[i].startY + RoiHeight) > imHeight ?
                imHeight - outFrmDesc[i].height : outFrmDesc[i].startY;
        }

        outFrmDesc[i].startX = (outFrmDesc[i].startX / sreachStep)*sreachStep;
        outFrmDesc[i].startY = (outFrmDesc[i].startY / sreachStep)*sreachStep;
        outFrmDesc[i].width  = (outFrmDesc[i].width / sreachStep)*sreachStep;
        outFrmDesc[i].height = (outFrmDesc[i].height / sreachStep)*sreachStep;

        /* Calculate the output pitch
           For 0th scale, output pitch is same as the input pitch */
        if (i > 0)
        {
            if (SYSTEM_DF_YUV420SP_UV == dataFormat)
            {
                outFrmDesc[i].pitch[0U] =
                    SystemUtils_align(outFrmDesc[i].width,
                        ALG_IMG_PMD_BUFFER_ALIGN);
                outFrmDesc[i].pitch[1U] = outFrmDesc[i].pitch[0U];
                outFrmDesc[i].pitch[2U] = outFrmDesc[i].pitch[0U];
            }
            else
            {
                outFrmDesc[i].pitch[0U] =
                    SystemUtils_align(outFrmDesc[i].width * 2U,
                        ALG_IMG_PMD_BUFFER_ALIGN);
                outFrmDesc[i].pitch[1U] = outFrmDesc[i].pitch[0U];
                outFrmDesc[i].pitch[2U] = outFrmDesc[i].pitch[0U];
            }
        }
    }

    i = 0U;
    /* Calculate the input size parameters */
    for(i = 1U; i < numScales; i++)
    {
        /* Original input width, input channels ROI, is stored
           in 0th instance of in frame descriptor */
        inFrmDesc[i].width   = inFrmDesc[0U].orgWidth >> ((i - 1U) / scaleSteps);
        inFrmDesc[i].height  = inFrmDesc[0U].orgHeight >> ((i - 1U) / scaleSteps);

        scaleRatioQ12  = scaleRatiosQ12[i%scaleSteps];

        if (i <= scaleSteps)
        {
            /*  For the first set of scales, input pitch is same as
                the input buffers pitch */
            inFrmDesc[i].pitch[0U] = pImgPmdObj->inputChInfo.pitch[0U];
            inFrmDesc[i].pitch[1U] = pImgPmdObj->inputChInfo.pitch[1U];
            inFrmDesc[i].pitch[2U] = pImgPmdObj->inputChInfo.pitch[2U];
        }
        else
        {
            /* For the other scales, input pitch is same as one of the
               previous output pitch */
            idx = ((i - 1U)/scaleSteps)*scaleSteps;

            inFrmDesc[i].pitch[0U] = outFrmDesc[idx].pitch[0U];
            inFrmDesc[i].pitch[1U] = outFrmDesc[idx].pitch[1U];
            inFrmDesc[i].pitch[2U] = outFrmDesc[idx].pitch[2U];
        }

        if (i % scaleSteps == 0U)
        {
            inFrmDesc[i].startX = 0U;
            inFrmDesc[i].startY = 0U;
        }
        else
        {
            inFrmDesc[i].startX = ((outFrmDesc[i].startX * scaleRatioQ12) /
                (1 << (ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)));
            inFrmDesc[i].startY = ((outFrmDesc[i].startY * scaleRatioQ12) /
                (1 << (ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)));

            /* Make input frame position to be even so that
               chroma buffer location is correct for YUV420 format */
            inFrmDesc[i].startX = inFrmDesc[i].startX & (~0x1);
            inFrmDesc[i].startY = inFrmDesc[i].startY & (~0x1);
        }

        /* If the ROI is enabled, calculate the input frame size
           and position based on the output size and position,
           This is not required for non Roi mode as input size
           remains same for all the scales in scaleSteps. */
        if (TRUE == pImgPmdObj->algLinkCreateParams.enableRoi)
        {
            if (1U == i)
            {
                inFrmDesc[i].width = ((outFrmDesc[i].width * scaleRatioQ12) /
                    (1 << (ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)));
                inFrmDesc[i].height = ((outFrmDesc[i].height * scaleRatioQ12) /
                    (1 << (ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)));
            }
            else if (i%scaleSteps == 0U)
            {
                inFrmDesc[i].width = inFrmDesc[0U].orgWidth >>
                    ((i-1U)/scaleSteps);
                inFrmDesc[i].height = inFrmDesc[0U].orgHeight >>
                    ((i-1U)/scaleSteps);
            }
            else
            {
                inFrmDesc[i].width = ((outFrmDesc[i].width * scaleRatioQ12) /
                    (1 << (ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)));
                inFrmDesc[i].height = ((outFrmDesc[i].height * scaleRatioQ12) /
                    (1 << (ALG_IMG_PMD_Q_FORMATE_SCALE_RATIO)));
            }

            /* Make sure that the Input frame size is always even. */
            inFrmDesc[i].width &= (~1U);
            inFrmDesc[i].height &= (~1U);
        }
    }

    /* Copy output frame descriptor in all output frames */
    for (i = 1U; i < pImgPmdObj->algLinkCreateParams.numOutBuffers; i ++)
    {
        memcpy(pImgPmdObj->outFrmDesc[i], pImgPmdObj->outFrmDesc[i - 1U],
            sizeof(AlgorithmLink_ImgPyramidFrameDesc) * numScales);
    }

    for (i = 0U; i < numScales; i ++)
    {
        Vps_printf(" ALG_IMAGEPYRAMID: #%2d Input  %3d,%3d : %4d x %4d (%4d B) (In  Org %4d x %4d)",
            i,
            inFrmDesc[i].startX, inFrmDesc[i].startY,
            inFrmDesc[i].width, inFrmDesc[i].height,
            inFrmDesc[i].pitch[0],
            inFrmDesc[i].orgWidth, inFrmDesc[i].orgHeight);
        Vps_printf("                       Output %3d,%3d : %4d x %4d (%4d B) (Out Org %4d x %4d)",
            outFrmDesc[i].startX, outFrmDesc[i].startY,
            outFrmDesc[i].width,  outFrmDesc[i].height,
            outFrmDesc[i].pitch[0],
            outFrmDesc[i].orgWidth,  outFrmDesc[i].orgHeight
            );
    }

}

Void Alg_imgPyramidAllocBuffers(Void *pObj, AlgorithmLink_ImgPmdObj *pImgPmdObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i, j;
    UInt32 dataFormat;
    UInt32 bufSize;
    System_Buffer *pSysBuffer;
    System_MetaDataBuffer *pMetaDataBuffer;
    AlgorithmLink_ImgPyramidCreateParams *pImgPmdCreateParams;
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc;

    /* Resizer output format is same as the input data format,
       so get the dataformat from input channel information */
    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
            pImgPmdObj->inputChInfo.flags);
    pImgPmdCreateParams = &pImgPmdObj->algLinkCreateParams;

    for (i = 0U; i < pImgPmdObj->algLinkCreateParams.numOutBuffers; i ++)
    {
        /* Start from 1 index since the output buffer for instance 0 is
           from the input buffer */
        for (j = 1U; j < pImgPmdObj->algLinkCreateParams.numScales; j ++)
        {
            outFrmDesc = pImgPmdObj->outFrmDesc[i] + j;

            bufSize = outFrmDesc->pitch[0U] * outFrmDesc->height;

            /* For the YUV420 dataformat, add chroma size */
            if (SYSTEM_DF_YUV420SP_UV == dataFormat)
            {

                bufSize += outFrmDesc->pitch[1U] * (outFrmDesc->height / 2U) ;
            }

            if (System_useLinkMemAllocInfo(
                    &pImgPmdCreateParams->memAllocInfo) == FALSE)
            {
                outFrmDesc->bufAddr[0U] = Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        bufSize,
                        ALG_IMG_PMD_BUFFER_ALIGN);
            }
            else
            {
                outFrmDesc->bufAddr[0U] =
                    (Ptr)System_allocLinkMemAllocInfo(
                        &pImgPmdCreateParams->memAllocInfo,
                        bufSize,
                        ALG_IMG_PMD_BUFFER_ALIGN);

            }
            UTILS_assert(NULL != outFrmDesc->bufAddr[0U]);
            memset(outFrmDesc->bufAddr[0U], 0xFF, bufSize);

            if (SYSTEM_DF_YUV420SP_UV == dataFormat)
            {
                outFrmDesc->bufAddr[1U] =
                    (Ptr)((UInt32)outFrmDesc->bufAddr[0U] +
                        outFrmDesc->pitch[0U] * outFrmDesc->height);
            }
        }
    }

    /* Initialize System Buffer and MetaBuffer */
    for (i = 0U; i < pImgPmdObj->algLinkCreateParams.numOutBuffers; i ++)
    {
        pMetaDataBuffer = &pImgPmdObj->metaDataBuffer[i];
        pSysBuffer = &pImgPmdObj->sysBuffers[i];

        /* Initialize MetaDataBuffer */
        pMetaDataBuffer->numMetaDataPlanes = 1U;
        pMetaDataBuffer->bufAddr[0U] = pImgPmdObj->outFrmDesc[i];
        pMetaDataBuffer->metaBufSize[0U] =
            pImgPmdCreateParams->numScales *
                sizeof(AlgorithmLink_ImgPyramidFrameDesc);
        pMetaDataBuffer->metaFillLength[0U] =
            pMetaDataBuffer->metaBufSize[0U];
        pMetaDataBuffer->flags = 0U;

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSysBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSysBuffer->payload      =   pMetaDataBuffer;
        pSysBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSysBuffer->chNum        =   0U;

        Cache_wb(pMetaDataBuffer->bufAddr[0U],
                (pImgPmdCreateParams->numScales *
                sizeof(AlgorithmLink_ImgPyramidFrameDesc)),
                Cache_Type_ALLD,
                TRUE);

        /* Enqueue output buffer in output queue */
        status = AlgorithmLink_putEmptyOutputBuffer(
            pObj, 0U, pSysBuffer);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
}

Void Alg_imgPyramidFreeBuffers(AlgorithmLink_ImgPmdObj *pImgPmdObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i, j;
    UInt32 dataFormat, bufSize;
    AlgorithmLink_ImgPyramidCreateParams *pImgPmdCreateParams;
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc;

    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
            pImgPmdObj->inputChInfo.flags);

    pImgPmdCreateParams = &pImgPmdObj->algLinkCreateParams;

    /* Start from 1 index since the output buffer for instance 0 is
       from the input buffer */
    for (i = 0U; i < pImgPmdObj->algLinkCreateParams.numOutBuffers; i ++)
    {
        /* Start from 1 index since the output buffer for instance 0 is
           from the input buffer */
        for (j = 1U; j < pImgPmdObj->algLinkCreateParams.numScales; j ++)
        {
            outFrmDesc = pImgPmdObj->outFrmDesc[i] + j;

            bufSize = outFrmDesc->pitch[0U] * outFrmDesc->height;

            /* For the YUV420 dataformat, add chroma size */
            if (SYSTEM_DF_YUV420SP_UV == dataFormat)
            {
                bufSize += outFrmDesc->pitch[1U] * (outFrmDesc->height/ 2U) ;
            }

            if ((System_useLinkMemAllocInfo(
                    &pImgPmdCreateParams->memAllocInfo) == FALSE) &&
                (NULL != outFrmDesc->bufAddr[0U]))
            {
                status = Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        outFrmDesc->bufAddr[0U],
                        bufSize);

                UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
            }
        }
    }
}

Void AlgorithmLink_generatePyramid(
    AlgorithmLink_ImgPmdObj *pImgPmdObj,
    System_Buffer *pInBuff,
    System_Buffer *pOutBuff)
{
    UInt32 numScales, frmDescCnt, scaleSteps, idx;
    System_VideoFrameBuffer *pVideoInBuf;
    System_MetaDataBuffer *pMetaDataBuffer;
    AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc;
    AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc;

    UTILS_assert(NULL != pImgPmdObj->pRszDrvFxn);
    UTILS_assert(NULL != pImgPmdObj->pRszDrvFxn->processFrame);

    pMetaDataBuffer = (System_MetaDataBuffer *)pOutBuff->payload;
    UTILS_assert(pMetaDataBuffer != NULL);

    outFrmDesc = (AlgorithmLink_ImgPyramidFrameDesc *)
        pMetaDataBuffer->bufAddr[0U];
    UTILS_assert(outFrmDesc != NULL);

    pVideoInBuf = (System_VideoFrameBuffer *)pInBuff->payload;
    UTILS_assert(pVideoInBuf != NULL);

    inFrmDesc = &pImgPmdObj->inFrmDesc[0U];

    inFrmDesc->bufAddr[0U] = pVideoInBuf->bufAddr[0U];
    inFrmDesc->bufAddr[1U] = pVideoInBuf->bufAddr[1U];
    inFrmDesc->bufAddr[2U] = pVideoInBuf->bufAddr[2U];

    memcpy(outFrmDesc, inFrmDesc, sizeof(AlgorithmLink_ImgPyramidFrameDesc));

    numScales = pImgPmdObj->algLinkCreateParams.numScales - 1U;
    scaleSteps = pImgPmdObj->algLinkCreateParams.scaleSteps;

    for (frmDescCnt = 1U;
            frmDescCnt < numScales;
            frmDescCnt += 2U)
    {
        /* Copy buffer address into input descriptor */
        if (frmDescCnt <= scaleSteps)
        {
            /*  For the first set of scales, input buffer is same as
                the given input buffer */
            inFrmDesc[frmDescCnt].bufAddr[0U] = pVideoInBuf->bufAddr[0U];
            inFrmDesc[frmDescCnt].bufAddr[1U] = pVideoInBuf->bufAddr[1U];
            inFrmDesc[frmDescCnt].bufAddr[2U] = pVideoInBuf->bufAddr[2U];
        }
        else
        {
            /* For the other scales, input bufaddress is same as one of the
               previous output bufaddress */
            idx = ((frmDescCnt - 1U)/scaleSteps)*scaleSteps;

            inFrmDesc[frmDescCnt].bufAddr[0U] = outFrmDesc[idx].bufAddr[0U];
            inFrmDesc[frmDescCnt].bufAddr[1U] = outFrmDesc[idx].bufAddr[1U];
            inFrmDesc[frmDescCnt].bufAddr[2U] = outFrmDesc[idx].bufAddr[2U];
        }
        /* Copying same frame address for input frame descriptor + 1 as
           it is also passed to processFrame API. */
        inFrmDesc[frmDescCnt + 1U].bufAddr[0U] =
            inFrmDesc[frmDescCnt].bufAddr[0U];
        inFrmDesc[frmDescCnt + 1U].bufAddr[1U] =
            inFrmDesc[frmDescCnt].bufAddr[1U];
        inFrmDesc[frmDescCnt + 1U].bufAddr[2U] =
            inFrmDesc[frmDescCnt].bufAddr[2U];

        /* Run Resizer and generated two outputs from the same input,
           but need to pass both the input frame descriptor,
           since the start position and frame size is different
           for the both the outputs.
           Resizer internally will take care of start address and
           frame size for both the inputs. */
        pImgPmdObj->pRszDrvFxn->processFrame(
            pImgPmdObj->pRszObj,
            &inFrmDesc[frmDescCnt],
            &outFrmDesc[frmDescCnt],
            &inFrmDesc[frmDescCnt + 1U],
            &outFrmDesc[frmDescCnt + 1U],
            NULL);
    }

    /* Generate the last scale for the odd number of scales */
    if ((0U != numScales % 2U) && (frmDescCnt == numScales))
    {
        /* Copy buffer address into input descriptor */
        if (frmDescCnt <= scaleSteps)
        {
            /*  For the first set of scales, input buffer is same as
                the given input buffer */
            inFrmDesc[frmDescCnt].bufAddr[0U] = pVideoInBuf->bufAddr[0U];
            inFrmDesc[frmDescCnt].bufAddr[1U] = pVideoInBuf->bufAddr[1U];
            inFrmDesc[frmDescCnt].bufAddr[2U] = pVideoInBuf->bufAddr[2U];
        }
        else
        {
            /* For the other scales, input bufaddress is same as one of the
               previous output bufaddress */
            idx = ((frmDescCnt - 1U)/scaleSteps)*scaleSteps;

            inFrmDesc[frmDescCnt].bufAddr[0U] = outFrmDesc[idx].bufAddr[0U];
            inFrmDesc[frmDescCnt].bufAddr[1U] = outFrmDesc[idx].bufAddr[1U];
            inFrmDesc[frmDescCnt].bufAddr[2U] = outFrmDesc[idx].bufAddr[2U];
        }

        /* Run Resizer and generated two outputs from the same input */
        pImgPmdObj->pRszDrvFxn->processFrame(
            pImgPmdObj->pRszObj,
            &inFrmDesc[frmDescCnt],
            &outFrmDesc[frmDescCnt],
            NULL,
            NULL,
            NULL);
    }
    else
    {
    }

    /* Typically this is used by the Dup link,
       but this link also cannot release input buffer until
       corresponding output frame is not returned back from next link.
       This is because, the buffer of the input descriptor 0 is same as
       the buffer of the descriptor 0 */
    pOutBuff->pImgPmdLinkPrivate = pInBuff;
    pOutBuff->dupCount = 0U;
}

Int32 AlgorithmLink_imgPyramidPutEmptyBuffers(
    Void *pObj,
    UInt16 queId,
    System_BufferList *pBufList)
{
    UInt32 cnt;
    Bool dropFlag = FALSE;
    System_BufferList inputBufListReturn;
    System_Buffer *pSysBuf, *pOrgInBuf;
    AlgorithmLink_ImgPmdObj *pImgPmdObj;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pBufList);

    pImgPmdObj = (AlgorithmLink_ImgPmdObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    UTILS_assert(NULL != pImgPmdObj);

    for (cnt = 0U; cnt < pBufList->numBuf; cnt ++)
    {
        pSysBuf = pBufList->buffers[cnt];

        pOrgInBuf = pSysBuf->pImgPmdLinkPrivate;
        UTILS_assert(NULL != pOrgInBuf);

        inputBufListReturn.buffers[cnt] = pOrgInBuf;
    }

    inputBufListReturn.numBuf = pBufList->numBuf;

    /* Since output buffer is released,
        Release this input buffer now */
    AlgorithmLink_releaseInputBuffer(
       pObj,
       0U,
       pImgPmdObj->algLinkCreateParams.inQueParams.prevLinkId,
       pImgPmdObj->algLinkCreateParams.inQueParams.prevLinkQueId,
       &inputBufListReturn,
       &dropFlag);

    return (SYSTEM_LINK_STATUS_SOK);
}

