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
 * \file colorToGrayLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for frame copy Link
 *
 * \version 0.0 (Sept 2013) : [NN] First version
 * \version 0.1 (Sept 2013) : [PS] Added code for stats collector
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "colorToGrayLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

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
Int32 AlgorithmLink_ColorToGray_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_ColorToGrayCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_ColorToGrayProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_ColorToGrayControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_ColorToGrayStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_ColorToGrayDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_COLORTOGRAY;
#endif

#ifdef BUILD_A15
    algId = ALGORITHM_LINK_A15_ALG_COLORTOGRAY;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for color to gray algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_ColorToGrayCreate(void * pObj, void * pCreateParams)
{
    Alg_ColorToGray_Obj              * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo              prevLinkInfo;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       dataFormat;

    AlgorithmLink_OutputQueueInfo outputQInfo;
    AlgorithmLink_InputQueueInfo  inputQInfo;

    AlgorithmLink_ColorToGrayObj          * pColorToGrayObj;
    AlgorithmLink_ColorToGrayCreateParams * pColorToGrayCreateParams;

    pColorToGrayCreateParams =
        (AlgorithmLink_ColorToGrayCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pColorToGrayObj = (AlgorithmLink_ColorToGrayObj *)
                        malloc(sizeof(AlgorithmLink_ColorToGrayObj));

    UTILS_assert(pColorToGrayObj!=NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pColorToGrayObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */

    memcpy((void*)(&pColorToGrayObj->outQueParams),
           (void*)(&pColorToGrayCreateParams->outQueParams),
           sizeof(System_LinkOutQueParams));
    memcpy((void*)(&pColorToGrayObj->inQueParams),
           (void*)(&pColorToGrayCreateParams->inQueParams),
           sizeof(System_LinkInQueParams));

    /*
     * Populating parameters corresponding to Q usage of color to gray
     * algorithm link
     */
    numInputQUsed     = 1;
    numOutputQUsed    = 1;

    inputQInfo.qMode  = ALGORITHM_LINK_QUEUEMODE_INPLACE;
    outputQInfo.qMode = ALGORITHM_LINK_QUEUEMODE_INPLACE;

    /*
     * If any output buffer Q gets used in INPLACE manner, then
     * outputQInfo.inQueParams and
     * outputQInfo.inputQId need to be populated appropriately.
     */

    outputQInfo.inputQId = 0;

    memcpy((void*)(&outputQInfo.inQueParams),
           (void*)(&pColorToGrayCreateParams->inQueParams),
            sizeof(outputQInfo.inQueParams)
        );
    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * outputQInfo.queInfo.chInfo[channelId]
     */

    status = System_linkGetInfo(pColorToGrayCreateParams->inQueParams.prevLinkId,
                                &prevLinkInfo);

    prevLinkQueId = pColorToGrayCreateParams->inQueParams.prevLinkQueId;

    numChannelsUsed = prevLinkInfo.queInfo[prevLinkQueId].numCh;
    pColorToGrayObj->numInputChannels = numChannelsUsed;
    outputQInfo.queInfo.numCh = numChannelsUsed;


    for(channelId = 0; channelId < numChannelsUsed; channelId++)
    {
        dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
                      prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId].flags);
        UTILS_assert(dataFormat == SYSTEM_DF_YUV422I_YUYV);
        memcpy((void *)&(outputQInfo.queInfo.chInfo[channelId]),
        (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
        sizeof(System_LinkChInfo)
        );
    }

    /*
     * Taking a copy of input channel info in the link object for future use
     */

    for(channelId = 0; channelId < numChannelsUsed; channelId++)
    {
        memcpy((void *)&(pColorToGrayObj->inputChInfo[channelId]),
           (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
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
                                &inputQInfo,
                                numOutputQUsed,
                                &outputQInfo
                                );

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */
    algHandle = Alg_ColorToGrayCreate(&pColorToGrayObj->createParams);
    UTILS_assert(algHandle != NULL);

    pColorToGrayObj->algHandle = algHandle;

    pColorToGrayObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_COLORTOGRAY");
    UTILS_assert(NULL != pColorToGrayObj->linkStatsInfo);

    pColorToGrayObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for color to gray algorithm link
 *
 *        This function executes on the DSP processor. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_ColorToGrayProcess(void * pObj)
{
    AlgorithmLink_ColorToGrayObj * pColorToGrayObj;
    Alg_ColorToGray_Obj          * algHandle;
    Int32                        inputQId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    UInt32                       outputQId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSysBufferInput;
    System_VideoFrameBuffer    * pSysVideoFrameBufferInput;
    UInt32                       dataFormat;
    UInt32                       bufSize[SYSTEM_MAX_PLANES];
    UInt32                       bufCntr;
    UInt32                       numBuffs;
    UInt32                       channelId;
    System_LinkChInfo          * pInputChInfo;
    Bool                         bufDropFlag = FALSE;
    System_LinkStatistics      * linkStatsInfo;



    pColorToGrayObj = (AlgorithmLink_ColorToGrayObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pColorToGrayObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle     = pColorToGrayObj->algHandle;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pColorToGrayObj->inQueParams.prevLinkId,
                               pColorToGrayObj->inQueParams.prevLinkQueId,
                               &inputBufList);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    if(inputBufList.numBuf)
    {

        if(pColorToGrayObj->isFirstFrameRecv==FALSE)
        {
            pColorToGrayObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pColorToGrayObj->numInputChannels,
                    1);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
          /*
           * Getting free (empty) buffers from pool of output buffers
           */
          outputQId        = 0;

          pSysBufferInput           = inputBufList.buffers[bufId];
          pSysVideoFrameBufferInput = pSysBufferInput->payload;

          channelId = pSysBufferInput->chNum;
          if(channelId < pColorToGrayObj->numInputChannels)
          {
            linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;
          }

          /*
           * Error checks can be done on the input buffer and only later,
           * it can be picked for processing
           */
          if((pSysBufferInput->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
             ||
             (channelId >= pColorToGrayObj->numInputChannels)
            )
          {
            bufDropFlag = TRUE;
            linkStatsInfo->linkStats.inBufErrorCount++;
          }
          else
          {

              dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
                            pColorToGrayObj->inputChInfo[channelId].flags);

              if(dataFormat != SYSTEM_DF_YUV422I_YUYV)
              {
                  bufDropFlag = TRUE;
                  linkStatsInfo->linkStats.inBufErrorCount++;
              }
              else
              {
                  /*
                   * Call to the algorithm
                   */
                  bufDropFlag = FALSE;

                  pInputChInfo = &(pColorToGrayObj->inputChInfo[channelId]);

                  switch (dataFormat)
                  {
                      case SYSTEM_DF_YUV422I_YUYV:
                          numBuffs    = 1;
                          bufSize[0]  = ((pInputChInfo->height)*(pInputChInfo->pitch[0]));
                          break;
                      case SYSTEM_DF_YUV420SP_UV:
                          numBuffs    = 1;
                          bufSize[0]  = ((pInputChInfo->height)*(pInputChInfo->pitch[0]));
                          break;
                      default:
                          numBuffs    = 1;
                          bufSize[0]  = ((pInputChInfo->height)*(pInputChInfo->pitch[0]));
                          UTILS_assert (0);
                          break;
                  }

                  pSysBufferInput->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                  for(bufCntr = 0; bufCntr < numBuffs; bufCntr++)
                  {
                    Cache_inv(pSysVideoFrameBufferInput->bufAddr[bufCntr],
                              bufSize[bufCntr],
                              Cache_Type_ALL,
                              TRUE
                             );
                  }

                  Alg_ColorToGrayProcess(algHandle,
                                       (UInt32 **)pSysVideoFrameBufferInput->bufAddr,
                                       pInputChInfo->width,
                                       pInputChInfo->height,
                                       pInputChInfo->pitch,
                                       dataFormat
                                      );

                  for(bufCntr = 0; bufCntr < numBuffs; bufCntr++)
                  {
                    Cache_wb(pSysVideoFrameBufferInput->bufAddr[bufCntr],
                              bufSize[bufCntr],
                              Cache_Type_ALL,
                              TRUE
                             );
                  }

                  Utils_updateLatency(&linkStatsInfo->linkLatency,
                                      pSysBufferInput->linkLocalTimestamp);
                  Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                      pSysBufferInput->srcTimestamp);

                  linkStatsInfo->linkStats.chStats
                            [channelId].inBufProcessCount++;
                  linkStatsInfo->linkStats.chStats
                            [channelId].outBufCount[0]++;

                  /*
                   * Putting modified input buffer into output full buffer Q
                   * Note that this does not mean algorithm has freed the output buffer
                   */
                  status = AlgorithmLink_putFullOutputBuffer(pObj,
                                                             outputQId,
                                                             pSysBufferInput);

                  UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                  /*
                   * Informing next link that a new data has peen put for its
                   * processing
                   */
                  System_sendLinkCmd(pColorToGrayObj->outQueParams.nextLink,
                                     SYSTEM_CMD_NEW_DATA,
                                     NULL);
              }
          }

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
                                      pColorToGrayObj->inQueParams.prevLinkId,
                                      pColorToGrayObj->inQueParams.prevLinkQueId,
                                      &inputBufListReturn,
                                      &bufDropFlag);

        }

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for color to gray algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_ColorToGrayControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_ColorToGrayObj     * pColorToGrayObj;
    AlgorithmLink_ControlParams      * pAlgLinkControlPrm;
    Alg_ColorToGray_Obj              * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pColorToGrayObj = (AlgorithmLink_ColorToGrayObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pColorToGrayObj->algHandle;

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
            AlgorithmLink_ColorToGrayPrintStatistics(pObj, pColorToGrayObj);
            break;

        default:
            status = Alg_ColorToGrayControl(algHandle,
                                            &(pColorToGrayObj->controlParams)
                                           );
            break;
    }


    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for color to gray algorithm link
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
Int32 AlgorithmLink_ColorToGrayStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for color to gray algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_ColorToGrayDelete(void * pObj)
{
    AlgorithmLink_ColorToGrayObj * pColorToGrayObj;
    Alg_ColorToGray_Obj              * algHandle;
    Int32                        status = SYSTEM_LINK_STATUS_SOK;

    pColorToGrayObj = (AlgorithmLink_ColorToGrayObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pColorToGrayObj->algHandle;

    status = Utils_linkStatsCollectorDeAllocInst(pColorToGrayObj->linkStatsInfo);
    UTILS_assert(status == 0);

    status = Alg_ColorToGrayDelete(algHandle);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    free(pColorToGrayObj);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pColorToGrayObj       [IN] Color to gray Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_ColorToGrayPrintStatistics(void *pObj,
                     AlgorithmLink_ColorToGrayObj *pColorToGrayObj)
{
    UTILS_assert(NULL != pColorToGrayObj->linkStatsInfo);

    Utils_printLinkStatistics(&pColorToGrayObj->linkStatsInfo->linkStats, "ALG_COLORTOGRAY", TRUE);

    Utils_printLatency("ALG_COLORTOGRAY",
                       &pColorToGrayObj->linkStatsInfo->linkLatency,
                       &pColorToGrayObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}


/* Nothing beyond this point */
