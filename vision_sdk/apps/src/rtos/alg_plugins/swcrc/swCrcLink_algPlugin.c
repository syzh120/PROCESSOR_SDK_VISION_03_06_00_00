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
 * \file swCrcLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for software CRC Link
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "swCrc_algLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/link_api/grpxSrcLink.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of SW CRC algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SwCrc_initPlugin ()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_swCrcCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_swCrcProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_swCrcControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_swCrcStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_swCrcDelete;

    algId = ALGORITHM_LINK_DSP_ALG_SW_CRC;

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
Int32 AlgorithmLink_swCrcCreate (void * pObj, void * pCreateParams)
{
    Int32                             status    = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo                   prevLinkInfo;
    Int32                             channelId;
    Int32                             numChannelsUsed;
    Int32                             numInputQUsed;
    Int32                             numOutputQUsed;
    UInt32                            prevLinkQueId;
    AlgorithmLink_SwCrcObj          * pSwCrcObj;
    AlgorithmLink_SwCrcCreateParams * pSwCrcCreateParams;
    AlgorithmLink_OutputQueueInfo   * pOutputQInfo;
    AlgorithmLink_InputQueueInfo    * pInputQInfo;
    Int32                             i;

    pSwCrcCreateParams = (AlgorithmLink_SwCrcCreateParams *)pCreateParams;

    System_resetLinkMemAllocInfo(&pSwCrcCreateParams->memAllocInfo);

    if(System_useLinkMemAllocInfo(&pSwCrcCreateParams->memAllocInfo)==FALSE)
    {
        pSwCrcObj = (AlgorithmLink_SwCrcObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_SwCrcObj),
                        128);
    }
    else
    {
        pSwCrcObj = (AlgorithmLink_SwCrcObj *)
                    System_allocLinkMemAllocInfo(
                        &pSwCrcCreateParams->memAllocInfo,
                        sizeof(AlgorithmLink_SwCrcObj),
                        128);
    }
    UTILS_assert(pSwCrcObj!=NULL);

    pOutputQInfo = &pSwCrcObj->outputQInfo;
    pInputQInfo  = &pSwCrcObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pSwCrcObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    pSwCrcObj->algLinkCreateParams.startX     = pSwCrcCreateParams->startX;
    pSwCrcObj->algLinkCreateParams.startY     = pSwCrcCreateParams->startY;
    pSwCrcObj->algLinkCreateParams.roiWidth   = pSwCrcCreateParams->roiWidth;
    pSwCrcObj->algLinkCreateParams.roiHeight  = pSwCrcCreateParams->roiHeight;

    memcpy((void*)(&pSwCrcObj->inQueParams),
           (void*)(&pSwCrcCreateParams->inQueParams),
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
     * In SW CRC example, only pitch changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(pSwCrcCreateParams->inQueParams.prevLinkId,
                                &prevLinkInfo);

    prevLinkQueId = pSwCrcCreateParams->inQueParams.prevLinkQueId;

    pSwCrcObj->numInputChannels = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    UTILS_assert(pSwCrcObj->numInputChannels == 1);

    /*
     * Channel Info Population
     */
    for(channelId =0 ; channelId < SYSTEM_MAX_CH_PER_OUT_QUE; channelId++)
    {
      /*
       * Taking a copy of input channel info in the link object for any future
       * use
       */
      memcpy((void *)&(pSwCrcObj->inputChInfo[channelId]),
             (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
             sizeof(System_LinkChInfo)
            );
    }

    pSwCrcObj->prevSigIndex = 0;
    pSwCrcObj->isFrameFreezeDetected = FALSE;
    for (i=0; i<SWCRC_PREV_OBJ_MAX; i++)
    {
        pSwCrcObj->prevSig[i].swCrcVal_L = i;
        pSwCrcObj->prevSig[i].swCrcVal_H = i;
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

    pSwCrcObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_SWCRC");
    UTILS_assert(NULL != pSwCrcObj->linkStatsInfo);

    pSwCrcObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *****************************************************************************
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
swCrc_t crc_update(swCrc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    unsigned int tbl_idx;//, jump_count = 0;

    while (data_len--) {
        tbl_idx = (crc ^ *d) & 0xff;
        crc = (swCrc_table[tbl_idx] ^ (crc >> 8)) & 0xffffffffffffffff;

        d += 2;
    }
    return crc & 0xffffffffffffffff;
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
Int32 AlgorithmLink_swCrcProcess (void * pObj)
{
    AlgorithmLink_SwCrcObj       * pSwCrcObj;
    Int32                        inputQId;
    UInt32                       channelId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSysBufferInput;
    System_VideoFrameBuffer    * pSysVideoFrameBufferInput;
    UInt64                       linkLocalTimestamp;
    System_LinkChInfo          * pInputChInfo;
    Bool                         bufDropFlag;
    System_LinkStatistics      * linkStatsInfo;
    swCrc_t                      swCrcV = 0;
    UInt32                     * imageData = NULL;
    Bool                         isFrameFreezeDetect;
    UInt32                       i, index;
    GrpxSrcLink_StringRunTimePrintParams printPrms;

    pSwCrcObj = (AlgorithmLink_SwCrcObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pSwCrcObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pSwCrcObj->inQueParams.prevLinkId,
                               pSwCrcObj->inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pSwCrcObj->isFirstFrameRecv==FALSE)
        {
            pSwCrcObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pSwCrcObj->numInputChannels,
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
                pInputChInfo  = &(pSwCrcObj->inputChInfo[channelId]);

                /*
                 * If there is any parameter change on the input channel,
                 *  - Update the local copies present in inputChInfo
                 */

                if(System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update(
                          pSysVideoFrameBufferInput->chInfo.flags))
                {
                    pInputChInfo = &(pSysVideoFrameBufferInput->chInfo);

                    memcpy(&(pSwCrcObj->inputChInfo[channelId]),
                        pInputChInfo, sizeof(System_LinkChInfo));
                }

                linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                /* Perform the crc_update to check on the table */
                imageData = (UInt32 *)pSysVideoFrameBufferInput->bufAddr;
                swCrcV = crc_update(0, (const void *)(*imageData),
                    (size_t)((pSwCrcObj->algLinkCreateParams.roiWidth * pSwCrcObj->algLinkCreateParams.roiHeight) / 2));

                /* Store the data to the prevSig array */
                pSwCrcObj->prevSig[pSwCrcObj->prevSigIndex].swCrcVal_L = swCrcV & 0xFFFFFFFFU;
                pSwCrcObj->prevSig[pSwCrcObj->prevSigIndex].swCrcVal_H = (swCrcV >> 32U) & 0xFFFFFFFFU;
                pSwCrcObj->prevSigIndex++;
                /* To keep the prevSigIndex within 0 to SWCRC_PREV_OBJ_MAX */
                pSwCrcObj->prevSigIndex %= SWCRC_PREV_OBJ_MAX;

                index = 1;
                isFrameFreezeDetect = FALSE;
                for (i = 0; i < SWCRC_PREV_OBJ_MAX-index; i++)
                {
                    if ((pSwCrcObj->prevSig[i].swCrcVal_H == pSwCrcObj->prevSig[i+index].swCrcVal_H) &&
                        (pSwCrcObj->prevSig[i].swCrcVal_L == pSwCrcObj->prevSig[i+index].swCrcVal_L))
                    {
                        isFrameFreezeDetect = TRUE;
                    }
                    else
                    {
                        isFrameFreezeDetect = FALSE;
                        break;
                    }
                }

                if (isFrameFreezeDetect != pSwCrcObj->isFrameFreezeDetected)
                {
                    printPrms.duration_ms = SWCRC_DISPLAY_DURATION_MS;
                    printPrms.stringInfo.fontType = SWCRC_DISPLAY_FONTID;
                    printPrms.stringInfo.startX  = 50;
                    printPrms.stringInfo.startY  = 800-60;

                    if (isFrameFreezeDetect)
                    {
                        Vps_printf("\nALG SW CRC: Frame Freeze Detected \n");
                                                snprintf(printPrms.stringInfo.string,
                            sizeof(printPrms.stringInfo.string) - 1,
                            "Frame Freeze Detected !!! \n");

                        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
                        status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                           GRPX_SRC_LINK_CMD_PRINT_STRING,
                           &printPrms,
                           sizeof(printPrms),
                           TRUE);

                    }
                    else
                    {
                        Vps_printf("\nALG SW CRC: No Frame Freeze Detected \n");

                        snprintf(printPrms.stringInfo.string,
                            sizeof(printPrms.stringInfo.string) - 1,
                            " \n");

                        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
                        status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                           GRPX_SRC_LINK_CMD_PRINT_STRING,
                           &printPrms,
                           sizeof(printPrms),
                           TRUE);
                    }

                }

                pSwCrcObj->isFrameFreezeDetected = isFrameFreezeDetect;

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
                                      pSwCrcObj->inQueParams.prevLinkId,
                                      pSwCrcObj->inQueParams.prevLinkQueId,
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

Int32 AlgorithmLink_swCrcControl (void * pObj, void * pControlParams)
{
    AlgorithmLink_SwCrcObj         * pSwCrcObj;
    AlgorithmLink_ControlParams  * pAlgLinkControlPrm;
    Int32                          status    = SYSTEM_LINK_STATUS_SOK;

    pSwCrcObj = (AlgorithmLink_SwCrcObj *)
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
            AlgorithmLink_swCrcPrintStatistics(pObj, pSwCrcObj);
            break;

        default:
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
Int32 AlgorithmLink_swCrcStop (void * pObj)
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
Int32 AlgorithmLink_swCrcDelete (void * pObj)
{
    Int32                  status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_SwCrcObj * pSwCrcObj;

    pSwCrcObj = (AlgorithmLink_SwCrcObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pSwCrcObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


    if(System_useLinkMemAllocInfo(
        &pSwCrcObj->algLinkCreateParams.memAllocInfo)==FALSE)
    {
        Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_LOCAL,
            pSwCrcObj,
            sizeof(AlgorithmLink_SwCrcObj)
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
 * \param  pSwCrcObj       [IN] CRC link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_swCrcPrintStatistics (void *pObj,
                        AlgorithmLink_SwCrcObj *pSwCrcObj)
{

    UTILS_assert(NULL != pSwCrcObj->linkStatsInfo);

    Utils_printLinkStatistics(&pSwCrcObj->linkStatsInfo->linkStats, "ALG_SWCRC", TRUE);

    Utils_printLatency("ALG_SWCRC",
                       &pSwCrcObj->linkStatsInfo->linkLatency,
                       &pSwCrcObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
