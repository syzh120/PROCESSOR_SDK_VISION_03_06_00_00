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
 * \file ipcOutLink_drv.c
 *
 * \brief  This file has the implementataion of IPC OUT Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ipcOutLink_priv.h"

/*******************************************************************************
 *  Function Prototype's
 *******************************************************************************
 */
Int32 IpcOutLink_drvChCreate(IpcOutLink_Obj *pObj);
Void  IpcOutLink_drvCopySystemBufferToIpcBuffer(
                    IpcOutLink_Obj *pObj,
                    const System_Buffer *pBuffer,
                    System_IpcBuffer *pIpcBuffer
                    );
Bool IpcOutLink_drvDoFrameSkip(IpcOutLink_Obj *pObj, UInt32 chNum);
Void IpcOut_timerCallback(UInt32 arg);

/**
 *******************************************************************************
 *
 * \brief This function is called when next link send a notify or
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
Void IpcOutLink_drvNotifyCb(const Utils_TskHndl * pTsk)
{
    IpcOutLink_Obj * pObj = (IpcOutLink_Obj * )pTsk->appData;

    pObj->linkStatsInfo->linkStats.notifyEventCount++;

    if(Utils_ipcQueIsEmpty(&pObj->ipcIn2OutQue)==FALSE)
    {
        /*
         * send command to release frames only if there are elements in the
         * que
         */
        System_sendLinkCmd(pObj->linkId,
                            IPC_OUT_LINK_CMD_RELEASE_FRAMES,
                            (Void*)NULL);
    }
}

Void IpcOut_timerCallback(UInt32 arg)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is a generic implementation which supports all dataTypes.
     * This typecasting is necessary.
     */
    IpcOutLink_Obj * pObj = (IpcOutLink_Obj * )arg;

    IpcOutLink_drvNotifyCb((const Utils_TskHndl *)&pObj->tsk);
}


/**
 *******************************************************************************
 *
 * \brief Channel specific initialization
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvChCreate(IpcOutLink_Obj *pObj)
{
    IpcOutLink_ChObj *pChObj;
    UInt32 chId;

    for(chId=0; chId<SYSTEM_MAX_CH_PER_OUT_QUE; chId++)
    {
        pChObj = &pObj->chObj[chId];

        /* reset skip buf context to not skip any frames */
        Utils_resetSkipBufContext(&pChObj->bufSkipContext, 30U, 30U);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Create IPC Out link
 *
 *        Following happens during create phase,
 *        - Call 'get link info” on previous link.
 *          When IPC IN from other processers asks link info it gives back
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
 *          DES_ID: DOX_DES_TAG(DES_IPCOutIn_001)
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
 * \param  pPrm     [IN]  Create arguments
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvCreate(IpcOutLink_Obj *pObj, const IpcLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char                 tskName[32];

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Create in progress !!!\n",
               pObj->linkInstId
              );
#endif

    UTILS_MEMLOG_USED_START();

    /* keep a copy of create args */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* get previous link info */
    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId,
                    &pObj->prevLinkInfo
                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* validate previous link que ID */
    UTILS_assert(pObj->createArgs.inQueParams.prevLinkQueId < pObj->prevLinkInfo.numQue);

    /*
     * Setup current link que information
     * Current queue is considered to have one output queue
     * with que information same as selected previous link queue
     */
    pObj->linkInfo.numQue = 1;
    memcpy(&pObj->linkInfo.queInfo[0],
           &pObj->prevLinkInfo.queInfo
                [pObj->createArgs.inQueParams.prevLinkQueId],
           sizeof(pObj->linkInfo.queInfo[0])
          );


    /* allocate shared memory for IPC queue */
    pObj->ipcOut2InSharedMemBaseAddr =
                System_ipcGetIpcOut2InQue(pObj->linkId);
    UTILS_assert(pObj->ipcOut2InSharedMemBaseAddr!=NULL);

    pObj->ipcIn2OutSharedMemBaseAddr =
                System_ipcGetIpcIn2OutQue(pObj->linkId);
    UTILS_assert(pObj->ipcIn2OutSharedMemBaseAddr!=NULL);

    /* create IPC queue's */
    status = Utils_ipcQueCreate(
                        &pObj->ipcOut2InQue,
                        SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U,
                        pObj->ipcOut2InSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = Utils_ipcQueCreate(
                        &pObj->ipcIn2OutQue,
                        SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U,
                        pObj->ipcIn2OutSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);


    /* reset IPC queue's */

    Utils_ipcQueReset(&pObj->ipcOut2InQue,
                        pObj->ipcOut2InSharedMemBaseAddr,
                        (Bool)TRUE,
                        (Bool)TRUE
                    );
    Utils_ipcQueReset(&pObj->ipcIn2OutQue,
                        pObj->ipcIn2OutSharedMemBaseAddr,
                        (Bool)TRUE,
                        (Bool)TRUE
                    );

    {
        UInt32 elemId;

        /* create local queue */
        status = Utils_queCreate(&pObj->localQue,
                             SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS,
                             pObj->localQueMem,
                             UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


        /* allocate memory for IPC data structure's in shared memory */
        for(elemId=0; elemId <SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS; elemId++)
        {
            /* MISRA.CAST.PTR
             * MISRAC_2004 Rule_11.4
             * MISRAC_WAIVER:
             * This is a generic queue implementation which supports all dataTypes.
             * This typecasting is necessary.
             */
            /* queue to local queue
             * local que and IPC queue only stores index's, actual pointer to
             * IPC Buffer can be retrrieved via API System_ipcGetIpcBuffer
             * which takes IPC Out link ID and index as input
             */
            status = Utils_quePut(&pObj->localQue,
                         (Ptr)elemId,
                         0
                    );
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
        }
    }

    IpcOutLink_drvChCreate(pObj);

    pObj->isFirstFrameRecv = (Bool)FALSE;

    snprintf(tskName, sizeof(tskName), "IPC_OUT_%u", (UInt32)pObj->linkInstId);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, tskName);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("IPC_OUT:",
                   pObj->memUsed,
                   UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Create Done !!!\n",
           pObj->linkInstId
          );
#endif


    pObj->timer = BspOsal_clockCreate(
                            &IpcOut_timerCallback,
                            IPC_OUT_LINK_TIME_OUT_IN_MS, (Bool)FALSE, pObj);
    UTILS_assert(pObj->timer != NULL);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete IPC Out link
 *
 *        This function free's resources allocated during create
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvDelete(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Delete in progress !!!\n", pObj->linkInstId);
#endif

    /* delete local queue */
    Utils_queDelete(&pObj->localQue);


    /* delete ipc queue */
    Utils_ipcQueDelete(&pObj->ipcIn2OutQue);
    Utils_ipcQueDelete(&pObj->ipcOut2InQue);

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* no need for any channel delete logic */

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Delete Done !!!\n",
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
 * \brief Copy information from system buffer to IPC buffer
 *
 * \param  pObj        [IN]  Link object
 * \param  pBuffer     [IN]  Pointer to system buffer information
 * \param  pIpcBuffer  [IN]  Pointer to IPC buffer information
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Void  IpcOutLink_drvCopySystemBufferToIpcBuffer(
                    IpcOutLink_Obj *pObj,
                    const System_Buffer *pBuffer,
                    System_IpcBuffer *pIpcBuffer
                    )
{
    UInt32 flags = 0;

    flags = System_Buffer_Flag_Set_Buf_Type(flags, (UInt32)pBuffer->bufType);
    flags = System_Buffer_Flag_Set_Ch_Num(flags, pBuffer->chNum);
    flags = System_Buffer_Flag_Set_Payload_Size(flags, pBuffer->payloadSize);

    pIpcBuffer->flags               = flags;
    /* MISRA.CAST.PTR
     * MISRAC_2004 Rule_11.4
     * MISRAC_WAIVER:
     * This is a generic queue implementation which supports all dataTypes.
     * This typecasting is necessary.
     */
    pIpcBuffer->orgSystemBufferPtr  = (UInt32)pBuffer;
    pIpcBuffer->srcTimestamp        = pBuffer->srcTimestamp;
    pIpcBuffer->frameId             = pBuffer->frameId;
    pIpcBuffer->linkLocalTimestamp  = pBuffer->linkLocalTimestamp;

    pIpcBuffer->ipcPrfTimestamp64[0] = pBuffer->ipcPrfTimestamp64[0];

    UTILS_assert(pBuffer->payloadSize <= SYSTEM_MAX_PAYLOAD_SIZE );

    memcpy(pIpcBuffer->payload, pBuffer->payload, pBuffer->payloadSize);
}

/**
 *******************************************************************************
 *
 * \brief Check if frame needs to be skipped
 *
 * \param  pObj     [IN] Link object
 * \param  chNum    [IN] channel Id
 *
 * \return TRUE: skip frame, FALSE: process frame
 *
 *******************************************************************************
 */
Bool IpcOutLink_drvDoFrameSkip(IpcOutLink_Obj *pObj, UInt32 chNum)
{
    System_LinkQueInfo *pLinkQueInfo;
    IpcOutLink_ChObj *pChObj;
    Bool doFrameSkip = (Bool)TRUE;

    pLinkQueInfo = &pObj->linkInfo.queInfo[0];

    if(chNum >=  pLinkQueInfo->numCh )
    {
        doFrameSkip = (Bool)TRUE; /* invalid channel, skip frame */
    }
    else
    {
        pChObj = &pObj->chObj[chNum];

        doFrameSkip = Utils_doSkipBuf(&pChObj->bufSkipContext);
    }

    return doFrameSkip;
}

/**
 *******************************************************************************
 *
 * \brief Process buffer's
 *
 *        - Previous link will send a command NEW_DATA to IPC out link when
 *          buffers are available to be sent across processors
 *
 *        - IPC Out link will call 'get full buffer' to get the buffer
 *           information pointers
 *
 *        - For each buffer information pointer it will
 *          -  Apply frame-rate control and release frame immediately if this
 *             frame needs to be dropped
 *             - continue to next buffer pointer
 *          -  If uni-cache operation
 *             - Insert the pointer into the IPC queue (IPC OUT-> IPC IN Q)
 *             - continue to next buffer pointer
 *          -  If non-uni-cache operation
 *             - Get a IPC shared memory buffer information structures
 *               pointer from local queue
 *             - If no buffer information structures pointer in local queue
 *               then release incoming buffer immediately to previous link
 *               and continue. This should normally not happen but idea is
 *               to let processing continue even in this case
 *             - Translate the information from previous link buffer pointer
 *               to a IPC shared memory buffer information structure
 *             - This is where address is translated if required in case
 *               address space between the two core’s is different
 *             - The original system buffer pointer is also set in the IPC
 *               shared memory buffer information structure
 *             - Insert the IPC shared memory buffer information structure
 *               pointer in the IPC queue (IPC OUT-> IPC IN Q)
 *             - continue to next buffer pointer
 *
 *        - If notify is enabled and at least one element was put into
 *          IPC queue then send a notify to the other processor with
 *          IPC IN link ID as the notify payload. The next processor ID
 *          is embedded inside the next link ID
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvProcessBuffers(IpcOutLink_Obj *pObj)
{
    Int32             status      = SYSTEM_LINK_STATUS_SOK;
    System_Buffer     *pBuffer;
    UInt32            idx;
    System_BufferList bufList;
    System_BufferList freeBufList;
    Bool              sendNotify  = FALSE;
    UInt32            bufId;
    System_LinkStatistics *linkStatsInfo;

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

    linkStatsInfo->linkStats.newDataCmdCount++;

    bufList.numBuf = 0;
    System_getLinksFullBuffers(
                    pObj->createArgs.inQueParams.prevLinkId,
                    pObj->createArgs.inQueParams.prevLinkQueId,
                    &bufList);

    freeBufList.numBuf = 0;

    if(bufList.numBuf)
    {
        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {

            pBuffer = bufList.buffers[bufId];
            if((pBuffer==NULL)
                ||
               (pBuffer->chNum >= pObj->linkInfo.queInfo[0].numCh)
               )
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                /* invalid buffer pointer, skip it */
            }
            else
            {
                pBuffer->ipcPrfTimestamp64[0] = Utils_getCurGlobalTimeInUsec();

                pBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufRecvCount++;

                if(IpcOutLink_drvDoFrameSkip(pObj, pBuffer->chNum))
                {
                    linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufUserDropCount++;

                    /* skip frame */
                    UTILS_assert(freeBufList.numBuf < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

                    freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                    freeBufList.numBuf++;
                }
                else
                {
                    System_IpcBuffer *pIpcBuffer;

                    Utils_updateLatency(&linkStatsInfo->linkLatency,
                                        pBuffer->linkLocalTimestamp);
                    Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                        pBuffer->srcTimestamp);

                    idx = (UInt32)0xFFFFFFFFU;

                    /* MISRA.CAST.PTR
                     * MISRAC_2004 Rule_11.4
                     * MISRAC_WAIVER:
                     * This is a generic queue implementation which supports all dataTypes.
                     * This typecasting is necessary.
                     */
                    status =
                        Utils_queGet(&pObj->localQue,
                                    (Ptr *) &idx,
                                    1U,
                                    BSP_OSAL_NO_WAIT
                                    );

                    pIpcBuffer = System_ipcGetIpcBuffer(pObj->linkId, idx);

                    if((status!=SYSTEM_LINK_STATUS_SOK) || (pIpcBuffer == NULL))
                    {
                        linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufDropCount++;

                        /* if could not get free element from local queue,
                         * then free the system buffer
                         */

                        UTILS_assert(freeBufList.numBuf <
                                        SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

                        freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                        freeBufList.numBuf++;
                    }
                    else
                    {
                        IpcOutLink_drvCopySystemBufferToIpcBuffer(
                            pObj,
                            pBuffer,
                            pIpcBuffer
                            );

                        pIpcBuffer->ipcPrfTimestamp64[1] = Utils_getCurGlobalTimeInUsec();

                        /* MISRA.CAST.PTR
                         * MISRAC_2004 Rule_11.4
                         * MISRAC_WAIVER:
                         * This is a generic queue implementation which supports all dataTypes.
                         * This typecasting is necessary.
                         */
                        status = Utils_ipcQueWrite(
                                        &pObj->ipcOut2InQue,
                                        (UInt8*)&idx,
                                        sizeof(UInt32)
                                        );

                        if(status!=SYSTEM_LINK_STATUS_SOK)
                        {
                            linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufDropCount++;

                            /* if could not add element to queue, then free the
                             * system buffer
                             */

                            UTILS_assert(freeBufList.numBuf <
                                            SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

                            freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                            freeBufList.numBuf++;

                            /* return the extracted element to local queue */
                            status = Utils_quePut(&pObj->localQue,
                                 (Ptr)idx,
                                 0
                                );
                            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
                        }
                        else
                        {
                            linkStatsInfo->linkStats.chStats[pBuffer->chNum].inBufProcessCount++;

                            linkStatsInfo->linkStats.chStats[pBuffer->chNum].outBufCount[0]++;

                            /* atleast one element successfuly inserted in the IPC que
                             * So send notify to next link
                             */
                            sendNotify = (Bool)TRUE;
                        }
                    }
                }
            }
        }

        if(freeBufList.numBuf)
        {
            System_putLinksEmptyBuffers(
                pObj->createArgs.inQueParams.prevLinkId,
                pObj->createArgs.inQueParams.prevLinkQueId,
                &freeBufList
                );
        }

        /* if notify mode is enabled and atleast one element added to que
         * then send notify
         */
        if(sendNotify)
        {
            System_ipcSendNotify(pObj->createArgs.outQueParams.nextLink);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Release buffer returned by IPC IN link to previous link
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvReleaseBuffers(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 queStatus = SYSTEM_LINK_STATUS_SOK;
    System_Buffer    *pBuffer;
    UInt32 idx;
    System_BufferList freeBufList;
    Bool innerLoopDone;

    pObj->linkStatsInfo->linkStats.releaseDataCmdCount++;

    freeBufList.numBuf = 0;

    while(queStatus == SYSTEM_LINK_STATUS_SOK)
    {
        innerLoopDone = (Bool)FALSE;

        while(!innerLoopDone)
        {
            idx = (UInt32)0xFFFFFFFFU;

            /* MISRA.CAST.PTR
             * MISRAC_2004 Rule_11.4
             * MISRAC_WAIVER:
             * This is a generic queue implementation which supports all dataTypes.
             * This typecasting is necessary.
             */
            queStatus = Utils_ipcQueRead(
                    &pObj->ipcIn2OutQue,
                    (UInt8*)&idx,
                    sizeof(UInt32)
                    );

            if(queStatus!=SYSTEM_LINK_STATUS_SOK)
            {
                innerLoopDone = (Bool)TRUE; /* no more data to read from IPC queue */
            }
            else
            {
                System_IpcBuffer *pIpcBuffer;

                pIpcBuffer = System_ipcGetIpcBuffer(pObj->linkId, idx);

                if(pIpcBuffer == NULL)
                {
                    pObj->linkStatsInfo->linkStats.inBufErrorCount++;
                    /* this condition will not happen */
                }
                else
                {
                    /* MISRA.CAST.PTR
                     * MISRAC_2004 Rule_11.4
                     * MISRAC_WAIVER:
                     * This is a generic queue implementation which supports all dataTypes.
                     * This typecasting is necessary.
                     */
                    pBuffer = (System_Buffer*)pIpcBuffer->orgSystemBufferPtr;

                    /* MISRA.CAST.PTR
                     * MISRAC_2004 Rule_11.4
                     * MISRAC_WAIVER:
                     * This is a generic queue implementation which supports all dataTypes.
                     * This typecasting is necessary.
                     */
                    /* queue to local queue */
                    status = Utils_quePut(&pObj->localQue,
                                 (Ptr)idx,
                                 0
                            );
                    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

                    if(pBuffer==NULL)
                    {
                        pObj->linkStatsInfo->linkStats.inBufErrorCount++;
                        /* this condition will not happen */
                    }
                    else
                    {
                        freeBufList.buffers[freeBufList.numBuf] = pBuffer;
                        freeBufList.numBuf++;

                        if(freeBufList.numBuf>=SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST)
                        {
                            innerLoopDone = (Bool)TRUE;
                        }
                    }
                }
            }
        }

        if(freeBufList.numBuf)
        {
            System_putLinksEmptyBuffers(
                pObj->createArgs.inQueParams.prevLinkId,
                pObj->createArgs.inQueParams.prevLinkQueId,
                &freeBufList
                );
        }
    }
    return queStatus;
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
Int32 IpcOutLink_drvStop(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_OUT_%d   : Stop Done !!!\n", pObj->linkInstId);
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Set frame-rate
 *
 *        This function controls the rate at which buffers are
 *        processed and dropped
 *
 * \param  pObj     [IN] Link object
 * \param  pPrm     [IN] Frame rate control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcOutLink_drvSetFrameRate(IpcOutLink_Obj *pObj,
                              const IpcLink_FrameRateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkQueInfo *pLinkQueInfo;
    IpcOutLink_ChObj *pChObj;

    pLinkQueInfo = &pObj->linkInfo.queInfo[0];

    if(pPrm->chNum >=  pLinkQueInfo->numCh )
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        pChObj = &pObj->chObj[pPrm->chNum];

        Utils_resetSkipBufContext(
            &pChObj->bufSkipContext,
            pPrm->inputFrameRate,
            pPrm->outputFrameRate
            );
    }

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
Int32 IpcOutLink_drvPrintStatistics(IpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char                 tskName[32];

    snprintf(tskName, sizeof(tskName), "IPC_OUT_%u", (UInt32)pObj->linkInstId);

    UTILS_assert(NULL != pObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObj->linkStatsInfo->linkStats,
                            tskName,
                            (Bool)TRUE);

    Utils_printLatency(tskName,
                       &pObj->linkStatsInfo->linkLatency,
                       &pObj->linkStatsInfo->srcToLinkLatency,
                       (Bool)TRUE);

    return status;
}

