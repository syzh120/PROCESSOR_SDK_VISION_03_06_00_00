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
 * \file crcLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for CRC Link
 *
 * \version 0.0 (May 2015) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "crc_algLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of CRC algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_Crc_initPlugin ()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_crcCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_crcProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_crcControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_crcStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_crcDelete;

    algId = ALGORITHM_LINK_IPU_ALG_HW_CRC;

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for CRC algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_crcCreate (void * pObj, void * pCreateParams)
{
    Int32                           status    = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo                 prevLinkInfo;
    Int32                           channelId;
    Int32                           numChannelsUsed;
    Int32                           numInputQUsed;
    Int32                           numOutputQUsed;
    UInt32                          prevLinkQueId;
    AlgorithmLink_CrcObj          * pCrcObj;
    AlgorithmLink_CrcCreateParams * pCrcCreateParams;
    AlgorithmLink_OutputQueueInfo * pOutputQInfo;
    AlgorithmLink_InputQueueInfo  * pInputQInfo;

    pCrcCreateParams = (AlgorithmLink_CrcCreateParams *)pCreateParams;

    System_resetLinkMemAllocInfo(&pCrcCreateParams->memAllocInfo);

    if(System_useLinkMemAllocInfo(&pCrcCreateParams->memAllocInfo)==FALSE)
    {
        pCrcObj = (AlgorithmLink_CrcObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_CrcObj),
                        128);
    }
    else
    {
        pCrcObj = (AlgorithmLink_CrcObj *)
                    System_allocLinkMemAllocInfo(
                        &pCrcCreateParams->memAllocInfo,
                        sizeof(AlgorithmLink_CrcObj),
                        128);
    }
    UTILS_assert(pCrcObj!=NULL);

    pOutputQInfo = &pCrcObj->outputQInfo;
    pInputQInfo  = &pCrcObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pCrcObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    pCrcObj->algLinkCreateParams.startX     = pCrcCreateParams->startX;
    pCrcObj->algLinkCreateParams.startY     = pCrcCreateParams->startY;
    pCrcObj->algLinkCreateParams.roiHeight  = pCrcCreateParams->roiHeight;
    pCrcObj->algLinkCreateParams.roiWidth   = pCrcCreateParams->roiWidth;
    pCrcObj->algLinkCreateParams.cfgCbFxn   = pCrcCreateParams->cfgCbFxn;
    pCrcObj->algLinkCreateParams.appData    = pCrcCreateParams->appData;

    /* This function should not be null */
    UTILS_assert(NULL != pCrcObj->algLinkCreateParams.cfgCbFxn);
    UTILS_assert(NULL != pCrcObj->algLinkCreateParams.appData);

    memcpy((void*)(&pCrcObj->inQueParams),
           (void*)(&pCrcCreateParams->inQueParams),
           sizeof(System_LinkInQueParams));

    /*
     * Populating parameters corresponding to Q usage of CRC
     * algorithm link
     */
    numInputQUsed       = 1;
    numOutputQUsed      = 0;
    numChannelsUsed     = 1;
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->queInfo.numCh = numChannelsUsed;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In CRC example, only pitch changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(pCrcCreateParams->inQueParams.prevLinkId,
                                &prevLinkInfo);

    prevLinkQueId = pCrcCreateParams->inQueParams.prevLinkQueId;

    pCrcObj->numInputChannels = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    UTILS_assert(pCrcObj->numInputChannels == 1);
    UTILS_assert(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].width >=
          pCrcObj->algLinkCreateParams.roiWidth + pCrcObj->algLinkCreateParams.startX);
    UTILS_assert(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0].height >=
          pCrcObj->algLinkCreateParams.roiHeight + pCrcObj->algLinkCreateParams.startY);

    /*
     * Channel Info Population
     */
    for(channelId =0 ; channelId < SYSTEM_MAX_CH_PER_OUT_QUE; channelId++)
    {
      /*
       * Taking a copy of input channel info in the link object for any future
       * use
       */
      memcpy((void *)&(pCrcObj->inputChInfo[channelId]),
             (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
             sizeof(System_LinkChInfo)
            );
    }

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

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */

    pCrcObj->createParams.startX     = pCrcObj->algLinkCreateParams.startX;
    pCrcObj->createParams.startY     = pCrcObj->algLinkCreateParams.startY;
    pCrcObj->createParams.roiHeight  = pCrcObj->algLinkCreateParams.roiHeight;
    pCrcObj->createParams.roiWidth   =
        (pCrcObj->algLinkCreateParams.roiWidth/8)*8;
    pCrcObj->createParams.dataFormat =
        System_Link_Ch_Info_Get_Flag_Data_Format(pCrcObj->inputChInfo[0].flags);

    status = Alg_CrcCreate(&pCrcObj->algHandle, &pCrcObj->createParams);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pCrcObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_CRC");
    UTILS_assert(NULL != pCrcObj->linkStatsInfo);

    pCrcObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for CRC algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_crcProcess (void * pObj)
{
    AlgorithmLink_CrcObj       * pCrcObj;
    Alg_CrcDma_Obj             * algHandle;
    Int32                        inputQId;
    UInt32                       channelId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSysBufferInput;
    System_VideoFrameBuffer    * pSysVideoFrameBufferInput;
    UInt32                       dataFormat;
    UInt64                       linkLocalTimestamp;
    System_LinkChInfo          * pInputChInfo;
    Bool                         bufDropFlag;
    System_LinkStatistics      * linkStatsInfo;

    pCrcObj = (AlgorithmLink_CrcObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    algHandle     = &pCrcObj->algHandle;

    linkStatsInfo = pCrcObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pCrcObj->inQueParams.prevLinkId,
                               pCrcObj->inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pCrcObj->isFirstFrameRecv==FALSE)
        {
            pCrcObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pCrcObj->numInputChannels,
                    1);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {

          pSysBufferInput           = inputBufList.buffers[bufId];
          pSysVideoFrameBufferInput = pSysBufferInput->payload;

          channelId = pSysBufferInput->chNum;
          linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;

          /*
           * Error checks can be done on the input buffer and only later,
           * it can be picked for processing
           */
          if(pSysBufferInput->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
          {
            bufDropFlag = TRUE;
            linkStatsInfo->linkStats.inBufErrorCount++;
            linkStatsInfo->linkStats.chStats
                            [pSysBufferInput->chNum].inBufDropCount++;
          }
          else
          {
            pInputChInfo  = &(pCrcObj->inputChInfo[channelId]);

            /*
             * If there is any parameter change on the input channel,
             *  - Update the local copies present in inputChInfo
             */

            if(System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update(
                          pSysVideoFrameBufferInput->chInfo.flags))
            {
              pInputChInfo = &(pSysVideoFrameBufferInput->chInfo);

              memcpy(&(pCrcObj->inputChInfo[channelId]),
                     pInputChInfo,
                     sizeof(System_LinkChInfo));
            }

            dataFormat =
                    System_Link_Ch_Info_Get_Flag_Data_Format(pInputChInfo->flags);

            linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

            Alg_CrcProcess(algHandle,
                           (UInt32 **)pSysVideoFrameBufferInput->bufAddr,
                           pInputChInfo->width,
                           pInputChInfo->height,
                           pInputChInfo->pitch,
                           dataFormat
                          );

            pCrcObj->crcSig.crcVal_L = algHandle->crcObj.sectSignVal.regL;
            pCrcObj->crcSig.crcVal_H = algHandle->crcObj.sectSignVal.regH;

            /* Call the App registered callback function to return the
               CRC signature of the frame to the application */
            pCrcObj->algLinkCreateParams.cfgCbFxn(
                    (AlgorithmLink_CrcSig_Obj *) &pCrcObj->crcSig,
                     pCrcObj->algLinkCreateParams.appData);

            Utils_updateLatency(&linkStatsInfo->linkLatency,
                                linkLocalTimestamp);
            Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pSysBufferInput->srcTimestamp);

            linkStatsInfo->linkStats.chStats
                      [pSysBufferInput->chNum].inBufProcessCount++;
            linkStatsInfo->linkStats.chStats
                      [pSysBufferInput->chNum].outBufCount[0]++;

            bufDropFlag = FALSE;

          } /* Input Buffer validity */

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
                                      pCrcObj->inQueParams.prevLinkId,
                                      pCrcObj->inQueParams.prevLinkQueId,
                                      &inputBufListReturn,
                                      &bufDropFlag);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for CRC algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_crcControl (void * pObj, void * pControlParams)
{
    AlgorithmLink_CrcObj         * pCrcObj;
    AlgorithmLink_ControlParams  * pAlgLinkControlPrm;
    Alg_CrcDma_Obj               * algHandle;
    Int32                          status    = SYSTEM_LINK_STATUS_SOK;

    pCrcObj = (AlgorithmLink_CrcObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = &pCrcObj->algHandle;

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
            AlgorithmLink_crcPrintStatistics(pObj, pCrcObj);
            break;

        default:
            status = Alg_CrcControl(algHandle,
                                    &(pCrcObj->controlParams)
                                   );
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for CRC algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_crcStop (void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for CRC algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_crcDelete (void * pObj)
{
    Alg_CrcDma_Obj       * algHandle;
    Int32                  status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_CrcObj * pCrcObj;

    pCrcObj = (AlgorithmLink_CrcObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = &pCrcObj->algHandle;

    status = Utils_linkStatsCollectorDeAllocInst(pCrcObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Alg_CrcDelete(algHandle);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    if(System_useLinkMemAllocInfo(
        &pCrcObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_LOCAL,
            pCrcObj,
            sizeof(AlgorithmLink_CrcObj)
            );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pCrcObj       [IN] CRC link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_crcPrintStatistics (void *pObj,
                        AlgorithmLink_CrcObj *pCrcObj)
{

    UTILS_assert(NULL != pCrcObj->linkStatsInfo);

    Utils_printLinkStatistics(&pCrcObj->linkStatsInfo->linkStats, "ALG_CRC", TRUE);

    Utils_printLatency("ALG_CRC",
                       &pCrcObj->linkStatsInfo->linkLatency,
                       &pCrcObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */

