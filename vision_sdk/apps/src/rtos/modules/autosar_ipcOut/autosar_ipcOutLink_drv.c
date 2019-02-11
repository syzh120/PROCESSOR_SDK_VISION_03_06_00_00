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
 * \file autosar_ipcOutLink_drv.c
 *
 * \brief  This file has the implementataion of IPC OUT Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (August 2018) : [AKG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "autosar_ipcOutLink_priv.h"

extern System_IpcSharedMemObj  gSystem_autosarIpcSharedMemObj;


/*******************************************************************************
 *  Function Prototype's
 *******************************************************************************
 */
Void  AutosarIpcOutLink_drvCopySystemBufferToIpcBuffer(
                    AutosarIpcOutLink_Obj *pObj,
                    const System_AutosarMetaBuffer *pBuffer,
                    System_AutosarMetaBuffer *pMetaBuffer,
                    System_AutosarIpcBuffer *pIpcBuffer
                    );
/**
 *******************************************************************************
 *
 * \brief This function is called when autosar module send a notify
 *
 *        A command is sent to the IPC thread to read buffer's from Autosar
 *        to Vision  queue
 *
 * \param  pTsk     [IN]  Task Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AutosarIpcOutLink_drvNotifyCb(UInt32 remoteProcId, UInt32 eventId,
                                UInt32 payload,
                                Void     *arg,
                                Int32  status)
{
    if (eventId != AUTOSAR_IPC_OUT_BUFF_FREE_IPC_EVENT_ID)
    {
        Vps_printf("AUTOSAR_IPC_OUT: Unexpected event ID received on IPC! %d", eventId);
    }
    else if (status != IPCLIB_SOK)
    {
        Vps_printf("AUTOSAR_IPC_OUT: Error received on IPC! %d", status);
    }
    else
    {
        AutosarIpcOutLink_Obj * pObj = (AutosarIpcOutLink_Obj * )arg;

        UTILS_assert(NULL != pObj);

        pObj->linkStatsInfo->linkStats.notifyEventCount++;

        if(Utils_ipcQueIsEmpty(&pObj->ipcA2VQue)==FALSE)
        {
            /*
             * send command to release frames only if there are elements in the
             * que
             */
            System_sendLinkCmd(pObj->linkId,
                                AUTOSAR_IPC_OUT_LINK_CMD_RELEASE_FRAMES,
                                (Void*)NULL);
        }
    }
    return IPCLIB_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Create Autosar IPC Out link
 *
 * \param  pObj     [IN]  Link object
 * \param  pPrm     [IN]  Create arguments
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AutosarIpcOutLink_drvCreate(AutosarIpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char                 tskName[32];

#ifdef SYSTEM_DEBUG_AUTOSAR_IPC_OUT
    Vps_printf(" AUTOSAR_IPC_OUT_%d   : Create in progress !!!\n",
               pObj->linkInstId
              );
#endif

    UTILS_MEMLOG_USED_START();

    /* allocate shared memory for IPC queue */
    pObj->v2aSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queV2AObj[pObj->linkInstId];
    UTILS_assert(pObj->v2aSharedMemBaseAddr!=NULL);

    pObj->a2vSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queA2VObj[pObj->linkInstId];
    UTILS_assert(pObj->a2vSharedMemBaseAddr!=NULL);

    /* create IPC queue's */
    status = Utils_ipcQueCreate(
                        &pObj->ipcV2AQue,
                        SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U,
                        pObj->v2aSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = Utils_ipcQueCreate(
                        &pObj->ipcA2VQue,
                        SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U,
                        pObj->a2vSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);


    /* reset IPC queue's */

    Utils_ipcQueReset(&pObj->ipcV2AQue,
                        pObj->v2aSharedMemBaseAddr,
                        (Bool)TRUE,
                        (Bool)TRUE
                    );
    Utils_ipcQueReset(&pObj->ipcA2VQue,
                        pObj->a2vSharedMemBaseAddr,
                        (Bool)TRUE,
                        (Bool)TRUE
                    );
    /* create the output queue */
    status = Utils_bufCreate(&pObj->outBufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

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
          * IPC Buffer
          */
         status = Utils_quePut(&pObj->localQue,
                         (Ptr)elemId,
                         0
                    );
         UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

         pObj->buffers[elemId].payload = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,BUFFER_SIZE, 0);
         UTILS_assert(pObj->buffers[elemId].payload != NULL);
         pObj->buffers[elemId].payloadMcal = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,BUFFER_SIZE, 0);
         UTILS_assert(pObj->buffers[elemId].payloadMcal != NULL);

         status = Utils_bufPutEmptyBuffer(&pObj->outBufQue, (System_Buffer *)(&(pObj->buffers[elemId])));

         UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    }

    pObj->isFirstFrameRecv = (Bool)FALSE;

    snprintf(tskName, sizeof(tskName), "AUTOSAR_IPC_OUT_%u", (UInt32)pObj->linkInstId);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, tskName);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("AUTOSAR_IPC_OUT:",
                   pObj->memUsed,
                   UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_AUTOSAR_IPC_OUT
    Vps_printf(" AUTOSAR_IPC_OUT_%d   : Create Done !!!\n",
           pObj->linkInstId
          );
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete Autosar IPC Out link
 *
 *        This function free's resources allocated during create
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AutosarIpcOutLink_drvDelete(AutosarIpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 elemId;

#ifdef SYSTEM_DEBUG_AUTOSAR_IPC_OUT
    Vps_printf(" AUTOSAR_IPC_OUT_%d   : Delete in progress !!!\n", pObj->linkInstId);
#endif

    /* delete local queue */
    Utils_queDelete(&pObj->localQue);


    /* delete ipc queue */
    Utils_ipcQueDelete(&pObj->ipcA2VQue);
    Utils_ipcQueDelete(&pObj->ipcV2AQue);

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* delete output queue */
    status = Utils_bufDelete(&pObj->outBufQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(elemId=0; elemId <SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS; elemId++)
    {
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pObj->buffers[elemId].payload,
                                BUFFER_SIZE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pObj->buffers[elemId].payloadMcal,
                                BUFFER_SIZE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

#ifdef SYSTEM_DEBUG_AUTOSAR_IPC_OUT
    Vps_printf(" AUTOSAR_IPC_OUT_%d   : Delete Done !!!\n",
           pObj->linkInstId
        );
#endif

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
Void  AutosarIpcOutLink_drvCopySystemBufferToIpcBuffer(
                    AutosarIpcOutLink_Obj *pObj,
                    const System_AutosarMetaBuffer *pBuffer,
                    System_AutosarMetaBuffer *pMetaBuffer,
                    System_AutosarIpcBuffer *pIpcBuffer
                    )
{
    UTILS_assert(pBuffer->payload != NULL );

    memcpy(pMetaBuffer->payload, pBuffer->payload, pBuffer->payloadSize);
    Cache_wbInvAll();
    pMetaBuffer->payloadSize        = pBuffer->payloadSize;
    pMetaBuffer->flag               = pBuffer->flag;

    pIpcBuffer->payload             = pMetaBuffer->payload;
    pIpcBuffer->payloadMcal         = pMetaBuffer->payloadMcal;
    pIpcBuffer->payloadSize         = pMetaBuffer->payloadSize;
    pIpcBuffer->flag                = pMetaBuffer->flag;
    pIpcBuffer->orgMetaBufferPtr    = (UInt32)pMetaBuffer;
}

/**
 *******************************************************************************
 *
 * \brief Process buffer's
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AutosarIpcOutLink_drvProcessBuffers(AutosarIpcOutLink_Obj *pObj, System_AutosarMetaBuffer *pBuffer)
{
    Int32             status      = SYSTEM_LINK_STATUS_SOK;
    UInt32            idx;
    System_Buffer     *pMetaBuffer;
    Bool              sendNotify  = TRUE;

    System_LinkStatistics *linkStatsInfo;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstFrameRecv == FALSE)
    {
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                                  0,
                                 (UInt32)TRUE);

        pObj->isFirstFrameRecv = (Bool)TRUE;
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    if(pBuffer==NULL)
    {
        linkStatsInfo->linkStats.inBufErrorCount++;
        sendNotify = FALSE;
        /* invalid buffer pointer, skip it */
    }
    else
    {
        linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

        status = Utils_bufGetEmptyBuffer(&pObj->outBufQue,&pMetaBuffer,
                                        BSP_OSAL_NO_WAIT);

        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            sendNotify = FALSE;
        }
        else
        {
            System_AutosarIpcBuffer *pIpcBuffer;

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

            pIpcBuffer =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queElements[idx];

            if((status!=SYSTEM_LINK_STATUS_SOK) || (pIpcBuffer == NULL))
            {
                linkStatsInfo->linkStats.chStats[0].inBufDropCount++;
                /* if could not get free element from local queue,
                 * then free the meta buffer
                 */
                sendNotify = FALSE;
            }
            else
            {
                AutosarIpcOutLink_drvCopySystemBufferToIpcBuffer(
                    pObj,
                    pBuffer,
                    (System_AutosarMetaBuffer *)pMetaBuffer,
                    pIpcBuffer
                    );

                /* MISRA.CAST.PTR
                 * MISRAC_2004 Rule_11.4
                 * MISRAC_WAIVER:
                 * This is a generic queue implementation which supports all dataTypes.
                 * This typecasting is necessary.
                 */
                status = Utils_ipcQueWrite(
                                &pObj->ipcV2AQue,
                                (UInt8*)&idx,
                                sizeof(UInt32)
                                );

                if(status!=SYSTEM_LINK_STATUS_SOK)
                {
                    linkStatsInfo->linkStats.chStats[0].inBufDropCount++;

                    /* if could not add element to queue, then free the
                     * system buffer
                     */

                    sendNotify = FALSE;

                    /* return the extracted element to local queue */
                    status = Utils_quePut(&pObj->localQue,
                                          (Ptr)idx,
                                           0
                                          );
                    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
                }
                else
                {
                    linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;

                    linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

                    /* atleast one element successfuly inserted in the IPC que
                     * So send notify to next link
                     */
                    sendNotify = (Bool)TRUE;
                }
            }
        }
    }
        /* if notify mode is enabled and atleast one element added to que
         * then send notify
         */
        if(sendNotify)
        {
            status = IpcLib_interruptSendEvent(IPCLIB_IPU2_0_ID,
                                      AUTOSAR_IPC_OUT_NEW_BUFF_IPC_EVENT_ID,
                                      (UInt32)NULL,
                                      (UInt32)TRUE);
            if (status != IPCLIB_SOK)
            {
                Vps_printf
                    (" SYSTEM: NOTIFY: Send Event to [%s][%d] failed !!! (status = %d)\n",
                    SYSTEM_IPC_PROC_NAME_IPU2, status);
                UTILS_assert((Bool)FALSE);
            }
        }

    return status;
}
/**
 *******************************************************************************
 *
 * \brief Release buffer returned by Autosar Application
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AutosarIpcOutLink_drvReleaseBuffers(AutosarIpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 queStatus = SYSTEM_LINK_STATUS_SOK;
    System_AutosarMetaBuffer    *pBuffer;
    UInt32 idx;
    Bool innerLoopDone;

    pObj->linkStatsInfo->linkStats.releaseDataCmdCount++;

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
                    &pObj->ipcA2VQue,
                    (UInt8*)&idx,
                    sizeof(UInt32)
                    );

            if(queStatus!=SYSTEM_LINK_STATUS_SOK)
            {
                innerLoopDone = (Bool)TRUE; /* no more data to read from IPC queue */
            }
            else
            {
                System_AutosarIpcBuffer *pIpcBuffer;

                pIpcBuffer =
                    &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queElements[idx];

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
                    pBuffer = (System_AutosarMetaBuffer*)pIpcBuffer->orgMetaBufferPtr;

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
                        status = Utils_bufPutEmptyBuffer(&pObj->outBufQue,(System_Buffer *)pBuffer);
                        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
                    }
                }
            }
        }
    }
    return queStatus;
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
Int32 AutosarIpcOutLink_drvPrintStatistics(AutosarIpcOutLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char                 tskName[32];

    snprintf(tskName, sizeof(tskName), "AUTOSAR_IPC_OUT%u", (UInt32)pObj->linkInstId);

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

