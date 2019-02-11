/*
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
*/

/**
 *******************************************************************************
 * \file ipcInLink.c
 *
 * \brief  This file has the implementation of IPC IN Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (Aug 2013) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ipcInLink_priv.h"

/*******************************************************************************
 *  Function prototype's
 *******************************************************************************
 */
Void  IpcInLink_drvCopyIpcBufferToSystemBuffer(
                    IpcInLink_obj *pObj,
                    System_Buffer *pBuffer,
                    const System_IpcBuffer *pIpcBuffer,
                    UInt32 idx);
Void IpcIn_timerCallback(UInt32 arg);

/**
 *******************************************************************************
 *
 * \brief This function is called when previous link send a notify or
 *        periodic timer expires
 *
 *        A command is sent to the IPC thread to read buffer's from IPC IN ->
 *        IPC OUT queue and release the buffers back to the previous link
 *
 * \param  pTsk     [IN]  Task Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void IpcInLink_drvNotifyCb(const Utils_TskHndl * pTsk)
{
    IpcInLink_obj * pObj = (IpcInLink_obj * )pTsk->appData;

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    if(Utils_ipcQueIsEmpty(&pObj->ipcOut2InQue)==FALSE)
    {
        /*
         * send command to process frames only if there are elements in the
         * que
         */
        System_sendLinkCmd(pObj->linkId,
                            SYSTEM_CMD_NEW_DATA,
                            NULL);
    }
}

Void IpcIn_timerCallback(UInt32 arg)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic implementation which supports all dataTypes.
     * This typecasting is necessary.
     */
    IpcInLink_obj * pObj = (IpcInLink_obj * )arg;

    IpcInLink_drvNotifyCb((const Utils_TskHndl *)&pObj->tsk);
}

/**
 *******************************************************************************
 *
 * \brief Create IPC In link
 *
 *        Following happens during create phase,
 *        - Call 'get link info” on previous link.
 *          When link from other processors asks link info it gives back
 *          this link info to the next link (IPC IN)
 *        - IPC shared memory buffer information structures are allocated
 *          for non uni-cache IPC OUT/IN pair
 *        - IPC shared memory buffer information structure pointers
 *          are placed in internal local queue for non uni-cache
 *          IPC OUT/IN pair
 *        - Both IPC shared memory queue's
 *          (IPC OUT -> IPC IN, IPC IN -> IPC OUT) is reset to empty state.
 *        - Clock object is created for periodic polling if requested
 *          during create params
 *
 *          DES_ID: DOX_DES_TAG(DES_IPCOutIn_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-925)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1398)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1399)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1400)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1401)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1402)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1403)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1404)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1405)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1406)
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_drvCreate(IpcInLink_obj *pObj, const IpcLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_Buffer *pSysBuf;
    UInt32 elemId;
    char                 tskName[32];

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Create in progress !!!\n",
               pObj->linkInstId
               );
#endif

    UTILS_MEMLOG_USED_START();

    /* keep a copy of create args */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* get previous link info */
    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId,
                    &pObj->prevLinkInfo);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* validate previous link que ID */
    UTILS_assert(pObj->createArgs.inQueParams.prevLinkQueId <
                  pObj->prevLinkInfo.numQue);

    /*
     * Setup current link que information
     * Current queue is considered to have one output queue
     * with que information same as selected previous link queue
     */
    pObj->linkInfo.numQue = 1;
    memcpy(&pObj->linkInfo.queInfo[0],
           &pObj->prevLinkInfo.queInfo
                [pObj->createArgs.inQueParams.prevLinkQueId],
           sizeof(pObj->linkInfo.queInfo[0]));

    pObj->lock = BspOsal_semCreate(1, (Bool)TRUE);
    UTILS_assert(pObj->lock != NULL);

    status = Utils_ipcQueReset(&pObj->ipcOut2InQue,
                        (void *)System_ipcGetIpcOut2InQue(
                                    pObj->createArgs.inQueParams.prevLinkId),
                        (Bool)TRUE,
                        (Bool)FALSE);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_ipcQueReset(&pObj->ipcIn2OutQue,
                        (void *)System_ipcGetIpcIn2OutQue(
                                    pObj->createArgs.inQueParams.prevLinkId),
                        (Bool)FALSE,
                        (Bool)TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_bufCreate(&pObj->outBufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* allocate memory for IPC data structure's in shared memory */
    for(elemId=0; elemId <IPC_IN_LINK_IPC_QUE_MAX_ELEMENTS; elemId++)
    {
        pObj->buffers[elemId].payload = pObj->payload[elemId];
        /* queue to free Frame queue */
        pSysBuf = &pObj->buffers[elemId];

        status = Utils_bufPutEmptyBuffer(&pObj->outBufQue, pSysBuf);

        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    pObj->isFirstFrameRecv = (Bool)FALSE;

    snprintf(tskName, sizeof(tskName), "IPC_IN_%u", (UInt32)pObj->linkInstId);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, tskName);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    IpcInLink_latencyStatsReset(pObj);

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("IPC_IN:",
                   pObj->memUsed,
                   UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Create Done !!!\n",
           pObj->linkInstId
          );
#endif

    pObj->timer = BspOsal_clockCreate(
                            &IpcIn_timerCallback,
                            IPC_IN_LINK_TIME_OUT_IN_MS, (Bool)FALSE, pObj);
    UTILS_assert(pObj->timer != NULL);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete IPC In link
 *
 *        This function free's resources allocated during create
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_drvDelete(IpcInLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Delete in progress !!!\n",
           pObj->linkInstId
          );
#endif

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* delete local queue */
    status = Utils_bufDelete(&pObj->outBufQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    BspOsal_semDelete(&pObj->lock);

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Delete Done !!!\n",
           pObj->linkInstId
          );
#endif

    if (NULL != pObj->timer)
    {
        BspOsal_clockDelete(&pObj->timer);
    }

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Copy information from IPC buffer to system buffer
 *
 * \param  pObj        [IN]  Link object
 * \param  pBuffer     [IN]  Pointer to system buffer information
 * \param  pIpcBuffer  [IN]  Pointer to IPC buffer information
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void  IpcInLink_drvCopyIpcBufferToSystemBuffer(
                    IpcInLink_obj *pObj,
                    System_Buffer *pBuffer,
                    const System_IpcBuffer *pIpcBuffer,
                    UInt32 idx)
{
    UInt32 flags = 0;

    flags = pIpcBuffer->flags;

    pBuffer->bufType            = (System_BufferType)System_Buffer_Flag_Get_Buf_Type(flags);
    pBuffer->chNum              = System_Buffer_Flag_Get_Ch_Num(flags);
    pBuffer->payloadSize        = System_Buffer_Flag_Get_Payload_Size(flags);
    pBuffer->srcTimestamp       = pIpcBuffer->srcTimestamp;
    pBuffer->frameId            = pIpcBuffer->frameId;
    pBuffer->ipcInOrgQueElem    = (UInt32)idx;

    pBuffer->ipcPrfTimestamp64[0] = pIpcBuffer->ipcPrfTimestamp64[0];
    pBuffer->ipcPrfTimestamp64[1] = pIpcBuffer->ipcPrfTimestamp64[1];

    UTILS_assert(pBuffer->payloadSize <= SYSTEM_MAX_PAYLOAD_SIZE );
    UTILS_assert(pBuffer->payload != NULL );
    UTILS_assert(pIpcBuffer->payload != NULL );

    /* KW error fix */
    if(pBuffer->payloadSize > (UInt32)sizeof(pIpcBuffer->payload))
    {
        pBuffer->payloadSize = (UInt32)sizeof(pIpcBuffer->payload);
    }

    memcpy(pBuffer->payload, pIpcBuffer->payload, pBuffer->payloadSize);
}

/**
 *******************************************************************************
 *
 * \brief Process buffer's
 *
 *        - Previous link will notify when buffers are available
 *            to be sent across processors
 *
 *        - IPC In link picks the buffers from the ipcOut2InQue
 *
 *        - For each buffer information pointer it will
 *          -  If uni-cache operation
 *             - Pick a Queue Element from free queue, copy the data and put the
 *              Frame back to out queue
 *             - Translate the information from IPC shared memory buffer
 *               to system buffer information
 *             - The original IPC shared memory buffer pointer is also set in
 *                 system buffer information structure
 *          -  If non-uni-cache operation
 *             - Place the same buffer into out queue
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_drvProcessBuffers(IpcInLink_obj *pObj)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    Int32 queStatus = SYSTEM_LINK_STATUS_SOK;
    UInt32            idx;
    UInt32 numBufs = 0;
    System_Buffer     *pSysBuffer;
    Bool sendNotifyToPrevLink = FALSE;
    UInt64 tmpTimestamp64;
    System_LinkStatistics *linkStatsInfo;
    System_IpcBuffer *pIpcBuffer;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstFrameRecv == FALSE)
    {
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                          pObj->linkInfo.queInfo[0].numCh,
                          (UInt32)TRUE);

        pObj->isFirstFrameRecv = (Bool)TRUE;
    }

    while(1)
    {
        /* MISRA.CAST.PTR
         * MISRAC_2004 Rule_11.4
         * MISRAC_WAIVER:
         * This is a generic queue implementation which supports all dataTypes.
         * This typecasting is necessary.
         */
        queStatus = Utils_ipcQueRead( &pObj->ipcOut2InQue,
                                     (UInt8*)&idx,
                                      sizeof(UInt32));

        tmpTimestamp64 = Utils_getCurGlobalTimeInUsec();

        if(queStatus!=SYSTEM_LINK_STATUS_SOK)
        {
            break; /* no more data to read from IPC queue */
        }

        status = Utils_bufGetEmptyBuffer(&pObj->outBufQue,&pSysBuffer,
                                        BSP_OSAL_NO_WAIT);
        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            /* MISRA.CAST.PTR
             * MISRAC_2004 Rule_11.4
             * MISRAC_WAIVER:
             * This is a generic queue implementation which supports all dataTypes.
             * This typecasting is necessary.
             */

            /* failed to get the buffer returning ipcbuffer to free */
            status = Utils_ipcQueWrite( &pObj->ipcIn2OutQue,
                                        (UInt8*)&idx,
                                        sizeof(UInt32));
            sendNotifyToPrevLink = (Bool)TRUE;
        }
        else
        {
            pIpcBuffer = System_ipcGetIpcBuffer(
                            pObj->createArgs.inQueParams.prevLinkId,
                            idx
                         );

            if(pIpcBuffer == NULL)
            {
                pObj->linkStatsInfo->linkStats.inBufErrorCount++;
            }
            UTILS_assert(pIpcBuffer != NULL);
            if(pSysBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
            }
            UTILS_assert(pSysBuffer != NULL);

            if((pSysBuffer != NULL) && (pIpcBuffer != NULL))
            {
                pSysBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                IpcInLink_drvCopyIpcBufferToSystemBuffer(
                    pObj,
                    pSysBuffer,
                    pIpcBuffer,
                    idx);
                if(pSysBuffer->chNum >= SYSTEM_MAX_CH_PER_OUT_QUE)
                {
                    UTILS_assert((Bool)FALSE);
                }
                else
                {
                    linkStatsInfo->linkStats.chStats[pSysBuffer->chNum].
                        inBufRecvCount++;

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pSysBuffer->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pSysBuffer->srcTimestamp);

                    pSysBuffer->ipcPrfTimestamp64[0]
                        = Utils_getCurGlobalTimeInUsec() -
                        pSysBuffer->ipcPrfTimestamp64[0];
                    pSysBuffer->ipcPrfTimestamp64[1]
                        = tmpTimestamp64 - pSysBuffer->ipcPrfTimestamp64[1];

                    IpcInLink_latencyStatsUpdate(pObj,
                            pSysBuffer->ipcPrfTimestamp64[0],
                            pSysBuffer->ipcPrfTimestamp64[1]
                                    );

                    status = Utils_bufPutFullBuffer(&pObj->outBufQue, pSysBuffer);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    linkStatsInfo->linkStats.chStats[pSysBuffer->chNum].
                        inBufProcessCount++;
                    linkStatsInfo->linkStats.chStats[pSysBuffer->chNum].
                        outBufCount[0]++;

                    numBufs++;
                }
            }
        }
    }
    if(sendNotifyToPrevLink==(Bool)TRUE)
    {
        System_ipcSendNotify(pObj->createArgs.inQueParams.prevLinkId);
    }
    if(numBufs>0)
    {
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                            SYSTEM_CMD_NEW_DATA, NULL);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 * \param  pObj     [IN]  Link object
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IpcInLink_drvPutEmptyBuffers(IpcInLink_obj *pObj,
                                    System_BufferList *pBufList)
{

    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 bufId;
    System_Buffer *pBuf;
    UInt32 idx;

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];
        if(pBuf!=NULL)
        {
            idx = pBuf->ipcInOrgQueElem;

            pObj->linkStatsInfo->linkStats.putEmptyBufCount++;

            /* MISRA.CAST.PTR
             * MISRAC_2004 Rule_11.4
             * MISRAC_WAIVER:
             * This is a generic queue implementation which supports all dataTypes.
             * This typecasting is necessary.
             */
            status = Utils_ipcQueWrite( &pObj->ipcIn2OutQue,
                                        (UInt8*)&idx,
                                        sizeof(UInt32));
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    if(pBufList->numBuf)
    {
        System_ipcSendNotify(pObj->createArgs.inQueParams.prevLinkId);
    }


    status = Utils_bufPutEmpty(&pObj->outBufQue, pBufList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    BspOsal_semPost(pObj->lock);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * ipcIn link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from ipcIn
 * output queue.
 *
 * \param  pObj     [IN]  Link object
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IpcInLink_drvGetFullBuffers(IpcInLink_obj *pObj,
                                    System_BufferList *pBufList)
{
    Int32 status;

    status =  Utils_bufGetFull(&pObj->outBufQue, pBufList, BSP_OSAL_NO_WAIT);
    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        pObj->linkStatsInfo->linkStats.getFullBufCount++;
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Stop buffer processing
 *
 *        This function must be called before calling delete
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_drvStop(IpcInLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Stop Done !!!\n",
           pObj->linkInstId
          );
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print IPC link related statistics
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_drvPrintStatistics(IpcInLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char  tskName[32];

    snprintf(tskName, sizeof(tskName), "IPC_IN_%u", (UInt32)pObj->linkInstId);

    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
                            tskName,
                            (Bool)TRUE);

    Utils_printLatency(tskName,
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                       (Bool)TRUE);

    IpcInLink_latencyStatsPrint(pObj, (Bool)TRUE);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Reset IPC latency stats
 *
 * \param   pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Void IpcInLink_latencyStatsReset(IpcInLink_obj *pObj)
{
    UInt32 oldIntState;

    oldIntState = Hwi_disable();

    memset(&pObj->ipcLatencyStats, 0, sizeof(pObj->ipcLatencyStats));

    pObj->ipcLatencyStats.minIpcLatency = 0xFFFFFFFFU;
    pObj->ipcLatencyStats.minNotifyLatency = 0xFFFFFFFFU;

    Hwi_restore(oldIntState);
}

/**
 *******************************************************************************
 *
 * \brief Update IPC latency stats
 *
 * \param   pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Void IpcInLink_latencyStatsUpdate(IpcInLink_obj *pObj,
                                UInt64 ipcLatency,
                                UInt64 notifyLatency )
{
    UInt32 oldIntState;

    oldIntState = Hwi_disable();

    if(notifyLatency < 1000UL)
    {
        /* threshold below which measurement is done
         * Anything higher is considered as a anomaly
         */
        pObj->ipcLatencyStats.count++;
        pObj->ipcLatencyStats.totalIpcLatency += ipcLatency;
        pObj->ipcLatencyStats.totalNotifyLatency
                            += notifyLatency;

        if(ipcLatency < pObj->ipcLatencyStats.minIpcLatency)
        {
            pObj->ipcLatencyStats.minIpcLatency = ipcLatency;
        }

        if(ipcLatency > pObj->ipcLatencyStats.maxIpcLatency)
        {
            pObj->ipcLatencyStats.maxIpcLatency = ipcLatency;
        }


        if(notifyLatency
                <
            pObj->ipcLatencyStats.minNotifyLatency)
        {
            pObj->ipcLatencyStats.minNotifyLatency
                = notifyLatency;
        }

        if(notifyLatency
                >
            pObj->ipcLatencyStats.maxNotifyLatency)
        {
            pObj->ipcLatencyStats.maxNotifyLatency = notifyLatency;
        }
    }

    Hwi_restore(oldIntState);
}


/**
 *******************************************************************************
 *
 * \brief Print IPC latency stats
 *
 * \param   pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Void IpcInLink_latencyStatsPrint(IpcInLink_obj *pObj, Bool resetStats)
{
    char   tskName[32];
    UInt64 avgTime64, minTime64, maxTime64;

    snprintf(tskName, sizeof(tskName), "IPC_IN_%u", (UInt32)pObj->linkInstId);

    Vps_printf(" [ %s ] Detailed IPC Latency Statistics [ %s -> %s ] ,\n",
                tskName,
                System_getProcName(
                            SYSTEM_GET_PROC_ID(
                                pObj->createArgs.inQueParams.prevLinkId
                                        )
                            ),
                System_getProcName(System_getSelfProcId())
                );
    Vps_printf(
            " ***************************************************************\n");

    if (pObj->ipcLatencyStats.count)
    {

        /* One way buffer passing time is
            round trip time - one-way interrupt handling time
         */
        avgTime64 = pObj->ipcLatencyStats.totalIpcLatency
                        /
                        pObj->ipcLatencyStats.count;
                    ;

        minTime64 = pObj->ipcLatencyStats.minIpcLatency;


        maxTime64 = pObj->ipcLatencyStats.maxIpcLatency;


        Vps_printf(" IPC One-way Buffer Passing Latency   (usecs) :"
                   " Avg = %6d, Min = %6d, Max = %6d\n",
                    (UInt32)avgTime64,
                    (UInt32)minTime64,
                    (UInt32)maxTime64
                   );

        avgTime64 = pObj->ipcLatencyStats.totalNotifyLatency
                        /
                        pObj->ipcLatencyStats.count;
                    ;

        minTime64 = pObj->ipcLatencyStats.minNotifyLatency;


        maxTime64 = pObj->ipcLatencyStats.maxNotifyLatency;

        /* since two interrupts are exchanged per IPC, we divide the value by 2 */
        Vps_printf(" IPC One-way Notify Interrupt Latency (usecs) :"
                   " Avg = %6d, Min = %6d, Max = %6d\n",
                    (UInt32)avgTime64,
                    (UInt32)minTime64,
                    (UInt32)maxTime64
                   );
    }

    if(resetStats)
    {
        IpcInLink_latencyStatsReset(pObj);
    }
}
