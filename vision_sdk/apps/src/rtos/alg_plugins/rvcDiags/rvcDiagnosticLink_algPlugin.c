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
 * \file rvcDiagnosticLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for diagnos RVC software registers.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "rvcDiagnostic_algLink_priv.h"
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/link_api/grpxSrcLink.h>

static unsigned int rvc_pf_diag_counter = 0;
static int diag_error = 0;

int RVC_perFrameDiagnostics(unsigned int mode)
{
    unsigned int RegFieldValue[MAX_PF_DIAG_REGFIELDS];
    unsigned int i;

    rvc_pf_diag_counter++;

    /*
     * Read the current register value.
     */
    for (i=0; i<MAX_PF_DIAG_REGFIELDS; i++)
    {
        RegFieldValue[i] =
            HW_RD_FIELD32_RAW(perFrameDiagnosticsRegField[i].base + perFrameDiagnosticsRegField[i].offset, perFrameDiagnosticsRegField[i].mask, \
            perFrameDiagnosticsRegField[i].shift);
    }

    /*
     * Handling RVC_perFrameDiagnostics when mode is to dump/print the registers.
     */
    if (mode == DUMP_REGISTERS)
    {
        if (rvc_pf_diag_counter%30 == 0)
        {
            for (i=0; i<MAX_PF_DIAG_REGFIELDS; i++)
            {
                Vps_printf("RegField %d: %x\n",i,RegFieldValue[i]);
            }
        }
        return diag_error;
    }

    /*
     * Handling RVC_perFrameDiagnostics when mode is to compare the registers.
     */
    if (mode == COMPARE_SOME_REGISTERS)
    {
        if (rvc_pf_diag_counter%5 == 0)
        {
            diag_error = 0;
            for (i=0; i<MAX_PF_DIAG_REGFIELDS; i++)
            {
                if (RegFieldValue[i] != perFrameDiagnosticsRegField[i].reference)
                {
                    Vps_printf("RegField %d error: is: %x should be %x\n", i, RegFieldValue[i], perFrameDiagnosticsRegField[i].reference);
                    diag_error = 1;
                }
            }
            return diag_error;
        }
    }

    /*
     * Handling RVC_perFrameDiagnostics when mode is to fix the registers with the reference value.
     */
    if (mode == FIX_REGISTERS)
    {
        for (i=0; i<MAX_PF_DIAG_REGFIELDS; i++)
        {
            if (RegFieldValue[i] != perFrameDiagnosticsRegField[i].reference)
            {
                // Vps_printf("RegField %d error: is: %x AUTO REPLACE with %x\n", i, RegFieldValue[i], perFrameDiagnosticsRegField[i].reference);
                HW_WR_REG32_RAW(perFrameDiagnosticsRegField[i].base + perFrameDiagnosticsRegField[i].offset, perFrameDiagnosticsRegField[i].reference);
            }

            /* Updated the RegFieldValue[] after fixing. */
            RegFieldValue[i] =
                HW_RD_FIELD32_RAW(perFrameDiagnosticsRegField[i].base + perFrameDiagnosticsRegField[i].offset, perFrameDiagnosticsRegField[i].mask, \
                    perFrameDiagnosticsRegField[i].shift);
        }

        /* Reset diag_error as all should be fixed. */
        diag_error = 0;

        /* Compare registers before returning to make sure all registers are corrected. */
        for (i=0; i<MAX_PF_DIAG_REGFIELDS; i++)
        {
            if (RegFieldValue[i] != perFrameDiagnosticsRegField[i].reference)
            {
                Vps_printf("AFTER FIXING RegField %d error: is: %x should be %x\n", i, RegFieldValue[i], perFrameDiagnosticsRegField[i].reference);
                diag_error = 1;
            }
        }
        return diag_error;
    }

    return diag_error;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of RVC Diagnostic algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RvcDiagnostic_initPlugin ()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_rvcDiagnosticCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_rvcDiagnosticProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_rvcDiagnosticControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_rvcDiagnosticStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_rvcDiagnosticDelete;

    algId = ALGORITHM_LINK_IPU_ALG_RVC_DIAGNOSTIC;

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for RVC Diagnostic algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_rvcDiagnosticCreate (void * pObj, void * pCreateParams)
{
    Int32                             status    = SYSTEM_LINK_STATUS_SOK;
    System_LinkInfo                   prevLinkInfo;
    Int32                             channelId;
    Int32                             numInputQUsed;
    Int32                             numOutputQUsed;
    UInt32                            prevLinkQueId;
    AlgorithmLink_RvcDiagnosticObj    * pRvcDiagnosticObj;
    AlgorithmLink_RvcDiagnosticCreateParams * pRvcDiagnosticCreateParams;
    AlgorithmLink_OutputQueueInfo     * pOutputQInfo;
    AlgorithmLink_InputQueueInfo      * pInputQInfo;

    pRvcDiagnosticCreateParams = (AlgorithmLink_RvcDiagnosticCreateParams *)pCreateParams;

    pRvcDiagnosticObj = (AlgorithmLink_RvcDiagnosticObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_RvcDiagnosticObj),
                        128);
    UTILS_assert(pRvcDiagnosticObj!=NULL);

    pOutputQInfo = &pRvcDiagnosticObj->outputQInfo;
    pInputQInfo  = &pRvcDiagnosticObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pRvcDiagnosticObj);

    pRvcDiagnosticObj->algLinkCreateParams.appData = pRvcDiagnosticCreateParams->appData;

    memcpy(
            (void*)(&pRvcDiagnosticObj->algLinkCreateParams),
            (void*)(pRvcDiagnosticCreateParams),
            sizeof(AlgorithmLink_RvcDiagnosticCreateParams)
           );

    memcpy((void*)(&pRvcDiagnosticObj->outQueParams),
           (void*)(&pRvcDiagnosticCreateParams->outQueParams),
           sizeof(System_LinkOutQueParams));
    memcpy((void*)(&pRvcDiagnosticObj->inQueParams),
           (void*)(&pRvcDiagnosticCreateParams->inQueParams),
           sizeof(System_LinkInQueParams));

    /*
     * Populating parameters corresponding to Q usage of Rvc Diagnostic
     * algorithm link
     */
    numInputQUsed       = 1;
    numOutputQUsed      = 1;
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_INPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_INPLACE;

    /*
     * If any output buffer Q gets used in INPLACE manner, then
     * poutputQInfo.inQueParams and
     * poutputQInfo.inputQId need to be populated appropriately.
     */
    pOutputQInfo->inputQId = 0;

    memcpy((void*)(&pOutputQInfo->inQueParams),
           (void*)(&pRvcDiagnosticCreateParams->inQueParams),
            sizeof(pOutputQInfo->inQueParams)
        );

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     */
    status = System_linkGetInfo(pRvcDiagnosticCreateParams->inQueParams.prevLinkId,
                                &prevLinkInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    prevLinkQueId = pRvcDiagnosticCreateParams->inQueParams.prevLinkQueId;

    pRvcDiagnosticObj->numInputChannels = prevLinkInfo.queInfo[prevLinkQueId].numCh;
    pOutputQInfo->queInfo.numCh = pRvcDiagnosticObj->numInputChannels;

    for(channelId = 0; channelId < pRvcDiagnosticObj->numInputChannels; channelId++)
    {
        memcpy((void *)&(pOutputQInfo->queInfo.chInfo[channelId]),
             (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
             sizeof(System_LinkChInfo)
            );
    }

    /*
     * Taking a copy of input channel info in the link object for any future use
     */
    for(channelId = 0; channelId < pRvcDiagnosticObj->numInputChannels; channelId++)
    {
        memcpy((void *)&(pRvcDiagnosticObj->inputChInfo[channelId]),
            (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
             sizeof(System_LinkChInfo));
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

    pRvcDiagnosticObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_RVCDIAG");
    UTILS_assert(NULL != pRvcDiagnosticObj->linkStatsInfo);

    pRvcDiagnosticObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for RVC Diagnostic algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_rvcDiagnosticProcess (void * pObj)
{
    AlgorithmLink_RvcDiagnosticObj * pRvcDiagnosticObj;
    Int32                          inputQId;
    UInt32                         channelId;
    Int32                          status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                         bufId;
    System_BufferList              inputBufList;
    System_BufferList              inputBufListReturn;
    UInt32                         outputQId;
    System_Buffer                  * pSysBufferInput;
    System_VideoFrameBuffer        * pSysVideoFrameBufferInput;
    System_LinkChInfo              * pInputChInfo;
    Bool                           bufDropFlag;
    AlgorithmLink_RvcDiagnosticCreateParams * pRvcDiagnosticCreateParams;
    System_LinkStatistics          * linkStatsInfo;
    static Int32                   frame_count = 0;
    static Int32                   dssRegError = 0;
    static Int32                   dssRegPosted = 0;
    static Int32                   autoCount;
    GrpxSrcLink_StringRunTimePrintParams printPrms;

    pRvcDiagnosticObj = (AlgorithmLink_RvcDiagnosticObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pRvcDiagnosticCreateParams = &pRvcDiagnosticObj->algLinkCreateParams;

    linkStatsInfo = pRvcDiagnosticObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);
    linkStatsInfo->linkStats.newDataCmdCount++;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pRvcDiagnosticObj->inQueParams.prevLinkId,
                               pRvcDiagnosticObj->inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pRvcDiagnosticObj->isFirstFrameRecv == FALSE)
        {
            pRvcDiagnosticObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pRvcDiagnosticObj->numInputChannels,
                    1);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput           = inputBufList.buffers[bufId];
            pSysVideoFrameBufferInput = pSysBufferInput->payload;

            channelId = pSysBufferInput->chNum;
            if(channelId < pRvcDiagnosticObj->numInputChannels)
            {
                linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;
            }

            /*
             * Error checks can be done on the input buffer and only later,
             * it can be picked for processing
             */
            if((pSysBufferInput->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME) ||
               (channelId >= pRvcDiagnosticObj->numInputChannels))
            {
                bufDropFlag = TRUE;
                linkStatsInfo->linkStats.inBufErrorCount++;
            }
            else
            {
                /*
                 * Perform RVC_perFrameDiagnostics.
                 */
                frame_count++;
                if(!(frame_count%5))
                {
                    /* Perform RVC_perFrameDiagnostics after every 5 process call. */
                    if(dssRegError > 0)
                    {
                        /* If RVC_perFrameDiagnostics detects a discrepancy,
                           then print the notification once after 30 process call.*/
                        if(!(frame_count%30))
                        {
                            if(!dssRegPosted)
                            {
                                /* Calls GRPX to print a DSS config error message to the screen
                                   Set the autoCount to perform automatic update after autoCount reach 0.*/
                                printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
                                printPrms.duration_ms = RVC_DIAG_DISPLAY_DURATION_MS;
                                printPrms.stringInfo.fontType = RVC_DIAG_DISPLAY_FONTID;
                                printPrms.stringInfo.startX = 50;
                                printPrms.stringInfo.startY = 800-60;

                                if(pRvcDiagnosticCreateParams->autoCorrectFlag) {
                                    snprintf(printPrms.stringInfo.string,
                                        sizeof(printPrms.stringInfo.string) - 1,
                                        "DSS Config Error Detected; automatic will be applied after %d count.\n",
                                        pRvcDiagnosticCreateParams->autoCorrectCount);
                                    autoCount = pRvcDiagnosticCreateParams->autoCorrectCount;
                                } else {
                                    snprintf(printPrms.stringInfo.string,
                                        sizeof(printPrms.stringInfo.string) - 1,
                                        "DSS Config Error Detected\n");
                                }

                                status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                                    GRPX_SRC_LINK_CMD_PRINT_STRING,
                                    &printPrms,
                                    sizeof(printPrms),
                                    TRUE);

                                Vps_printf("\nALG RVC DIAG: Detecting Error on reference registers.\n");

                                dssRegPosted = 1;
                            }

                            if(pRvcDiagnosticCreateParams->autoCorrectFlag)
                            {
                                --autoCount;

                                if(!autoCount) {
                                    dssRegError = RVC_perFrameDiagnostics(FIX_REGISTERS);
                                    autoCount = pRvcDiagnosticCreateParams->autoCorrectCount;
                                }
                            }
                        }
                    }

                    dssRegError = RVC_perFrameDiagnostics(COMPARE_SOME_REGISTERS);
                    if((!dssRegError) && dssRegPosted)
                    {
                        /* If no more dssReqError and dssRegPosted was set then clear the message.
                           Call GRPX to clear the DSS config error message from the screen*/
                        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
                        printPrms.duration_ms = RVC_DIAG_DISPLAY_DURATION_MS;
                        printPrms.stringInfo.fontType = RVC_DIAG_DISPLAY_FONTID;
                        printPrms.stringInfo.startX = 50;
                        printPrms.stringInfo.startY = 800-60;

                        snprintf(printPrms.stringInfo.string,
                            sizeof(printPrms.stringInfo.string) - 1,
                            " \n");

                        status = System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                            GRPX_SRC_LINK_CMD_PRINT_STRING,
                            &printPrms,
                            sizeof(printPrms),
                            TRUE);
                        dssRegPosted = 0;
                    }
                }

                pInputChInfo  = &(pRvcDiagnosticObj->inputChInfo[channelId]);

                /*
                 * If there is any parameter change on the input channel,
                 *  - Update the local copies present in inputChInfo
                 */

                if(System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update(
                          pSysVideoFrameBufferInput->chInfo.flags))
                {
                    pInputChInfo = &(pSysVideoFrameBufferInput->chInfo);

                    memcpy(&(pRvcDiagnosticObj->inputChInfo[channelId]),
                        pInputChInfo, sizeof(System_LinkChInfo));
                }

                pSysBufferInput->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                    pSysBufferInput->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                    pSysBufferInput->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                    [pSysBufferInput->chNum].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                    [pSysBufferInput->chNum].outBufCount[0]++;

                /*
                 * Putting modified input buffer into output full buffer Q
                 * Note that this does not mean algorithm has freed the output buffer
                 */
                outputQId = 0;
                status = AlgorithmLink_putFullOutputBuffer(pObj,
                         outputQId,
                         pSysBufferInput);

                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(pRvcDiagnosticObj->outQueParams.nextLink,
                    SYSTEM_CMD_NEW_DATA,
                    NULL);

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
                                      pRvcDiagnosticObj->inQueParams.prevLinkId,
                                      pRvcDiagnosticObj->inQueParams.prevLinkQueId,
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

Int32 AlgorithmLink_rvcDiagnosticControl (void * pObj, void * pControlParams)
{
    AlgorithmLink_RvcDiagnosticObj  * pRvcDiagnosticObj;
    AlgorithmLink_ControlParams     * pAlgLinkControlPrm;
    Int32                           status = SYSTEM_LINK_STATUS_SOK;

    pRvcDiagnosticObj = (AlgorithmLink_RvcDiagnosticObj *)
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
            AlgorithmLink_rvcDiagnosticPrintStatistics(pObj, pRvcDiagnosticObj);
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
Int32 AlgorithmLink_rvcDiagnosticStop (void * pObj)
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
Int32 AlgorithmLink_rvcDiagnosticDelete (void * pObj)
{
    Int32                  status    = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_RvcDiagnosticObj * pRvcDiagnosticObj;

    pRvcDiagnosticObj = (AlgorithmLink_RvcDiagnosticObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pRvcDiagnosticObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_memFree(
        UTILS_HEAPID_DDR_CACHED_LOCAL,
        pRvcDiagnosticObj,
        sizeof(AlgorithmLink_RvcDiagnosticObj)
        );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pRvcDiagnosticObj           [IN] CRC link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_rvcDiagnosticPrintStatistics (void *pObj,
                        AlgorithmLink_RvcDiagnosticObj *pRvcDiagnosticObj)
{

    UTILS_assert(NULL != pRvcDiagnosticObj->linkStatsInfo);

    Utils_printLinkStatistics(&pRvcDiagnosticObj->linkStatsInfo->linkStats, "ALG_RVCDIAG", TRUE);

    Utils_printLatency("ALG_RVCDIAG",
                       &pRvcDiagnosticObj->linkStatsInfo->linkLatency,
                       &pRvcDiagnosticObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}
