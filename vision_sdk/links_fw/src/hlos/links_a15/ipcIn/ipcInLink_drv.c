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
 * \version 0.0 (May 2014) : [YM] First version ported to linux
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ipcInLink_priv.h"

/**
 *******************************************************************************
 * \brief Shared Region from where IPC buffers are allocated
 *
 *        For performance reasons it is assumed video frame buffers are always
 *        allocated from SR1. This saves a look up during address translation.
 *
 *        This can be changed to OSA_MEM_REGION_TYPE_AUTO to support buffers
 *        from other SRs
 *******************************************************************************
 */
#define IPC_IN_MEM_REGION_TYPE  OSA_MEM_REGION_TYPE_AUTO

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
Void IpcInLink_drvNotifyCb(OSA_TskHndl * pTsk)
{
    IpcInLink_obj * pObj = (IpcInLink_obj * )pTsk->appData;

    pObj->linkStats.notifyEventCount++;

    if(OSA_ipcQueIsEmpty(&pObj->ipcOut2InQue)==FALSE)
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
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IpcInLink_drvCreate(IpcInLink_obj *pObj, IpcLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_Buffer *pSysBuf;
    UInt32 elemId;

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Create in progress !!!\n",
               pObj->linkInstId
               );
#endif

    /* keep a copy of create args */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* get previous link info */
    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId,
                    &pObj->prevLinkInfo);

    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* validate previous link que ID */
    OSA_assert(pObj->createArgs.inQueParams.prevLinkQueId <
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

    status = OSA_mutexCreate(&(pObj->lock));
    OSA_assert(status == OSA_SOK);

    status = OSA_ipcQueReset(&pObj->ipcOut2InQue,
                        (void *)System_ipcGetIpcOut2InQue(
                                    pObj->createArgs.inQueParams.prevLinkId),
                            TRUE,
                            FALSE);

    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = OSA_ipcQueReset(&pObj->ipcIn2OutQue,
                        (void *)System_ipcGetIpcIn2OutQue(
                                    pObj->createArgs.inQueParams.prevLinkId),
                             FALSE,
                             TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = OSA_bufCreate(&pObj->outBufQue, FALSE, FALSE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* allocate memory for IPC data structure's in shared memory */
    for(elemId=0; elemId <SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS; elemId++)
    {
        pObj->buffers[elemId].payload = pObj->payload[elemId];
        /* queue to free Frame queue */
        pSysBuf = &pObj->buffers[elemId];

        status = OSA_bufPutEmptyBuffer(&pObj->outBufQue, pSysBuf);

        OSA_assert(status==SYSTEM_LINK_STATUS_SOK);
    }

    pObj->isFirstFrameRecv = FALSE;

    OSA_resetLatency(&pObj->linkLatency);
    OSA_resetLatency(&pObj->srcToLinkLatency);

    IpcInLink_latencyStatsReset(pObj);

    OSA_resetLinkStatistics(&pObj->linkStats,
                              pObj->linkInfo.queInfo[0].numCh,
                              1);

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Create Done !!!\n",
           pObj->linkInstId
          );
#endif

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

    /* delete local queue */
    status = OSA_bufDelete(&pObj->outBufQue);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
    OSA_mutexDelete(&pObj->lock);

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" IPC_IN_%d   : Delete Done !!!\n",
           pObj->linkInstId
          );
#endif
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Translates pointers in the payload of system buffer to Linux virutal
 *        space based on buffer type. This is essential step before buffers
 *        can be forwarded to next link on A15 in the chain.
 *
 * \param  pBuffer     [IN]  Pointer to system buffer information
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Void IpcInLink_drvTranslateSystemBufferPayloadPtrs(
            IpcInLink_obj *pObj,
            System_Buffer *pBuffer)
{
    UInt32 planes = 0;
    UInt32 frames = 0;
    System_VideoFrameBuffer * pVideoFrameBuffer                   = NULL;
    System_BitstreamBuffer * pBitstreamBuffer                     = NULL;
    System_MetaDataBuffer * pVideoMetaDataBuffer                  = NULL;
    System_VideoFrameCompositeBuffer * pVideoFrameCompositeBuffer = NULL;
    System_EglPixmapVideoFrameBuffer * pEglPixmapVideoFrameBuffer = NULL;
    System_LinkChInfo * link_chInfo                               = NULL;
    System_LinkChInfo * buf_chInfo                                = NULL;
    UInt32 size = 0;

    OSA_assert(pBuffer != NULL);
    link_chInfo = &pObj->linkInfo.queInfo[0].chInfo[0];

    switch(pBuffer->bufType)
    {
        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:

            pVideoFrameBuffer = (System_VideoFrameBuffer *)pBuffer->payload;
            pVideoFrameBuffer->flags = link_chInfo->flags;
            buf_chInfo = &pVideoFrameBuffer->chInfo;

            for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
            {
                if(pVideoFrameBuffer->bufAddr[planes] != NULL)
                {
                    pVideoFrameBuffer->bufAddr[planes] =
                                       (Void *)OSA_memPhys2Virt(
                                               (UInt32)pVideoFrameBuffer->bufAddr[planes],
                                                IPC_IN_MEM_REGION_TYPE);

                    if (planes != 0 ) {
                         pVideoFrameBuffer->dmaFd[planes] = -1;
                         continue;
                    }
                    if (pVideoFrameBuffer->dmaFd[planes] == 0)
                    {
                        size = (link_chInfo->pitch[planes] * link_chInfo->height * 3) / 2;

                        System_exportDmaBuf(pVideoFrameBuffer->bufAddr[planes],
                            size,
                            &pVideoFrameBuffer->dmaFd[planes]);
                    }
                }
            }
            if(pVideoFrameBuffer->metaBufAddr != NULL)
            {
                pVideoFrameBuffer->metaBufAddr =
                                       (Void *)OSA_memPhys2Virt(
                                               (UInt32) pVideoFrameBuffer->metaBufAddr,
                                                IPC_IN_MEM_REGION_TYPE);
            }
        break;
        case SYSTEM_BUFFER_TYPE_BITSTREAM:

            pBitstreamBuffer = (System_BitstreamBuffer *)pBuffer->payload;
            if(pBitstreamBuffer->bufAddr != NULL)
            {
                pBitstreamBuffer->bufAddr =
                                        (Void *)OSA_memPhys2Virt(
                                                (UInt32)pBitstreamBuffer->bufAddr,
                                                 IPC_IN_MEM_REGION_TYPE);

                System_exportDmaBuf(pBitstreamBuffer->bufAddr,
                            pBitstreamBuffer->bufSize,
                            &pBitstreamBuffer->dmaFd);

            }

            if(pBitstreamBuffer->metaBufAddr != NULL)
            {
                pBitstreamBuffer->metaBufAddr =
                                        (Void *)OSA_memPhys2Virt(
                                                (UInt32) pBitstreamBuffer->metaBufAddr,
                                                IPC_IN_MEM_REGION_TYPE);
            }
        break;
        case SYSTEM_BUFFER_TYPE_METADATA:

            pVideoMetaDataBuffer = (System_MetaDataBuffer *)pBuffer->payload;
            for (planes = 0; planes < pVideoMetaDataBuffer->numMetaDataPlanes; planes++)
            {
                if(pVideoMetaDataBuffer->bufAddr[planes] != NULL)
                {
                    pVideoMetaDataBuffer->bufAddr[planes] =
                                         (Void *)OSA_memPhys2Virt(
                                                 (UInt32)pVideoMetaDataBuffer->bufAddr[planes],
                                                 IPC_IN_MEM_REGION_TYPE);

                    System_exportDmaBuf(pVideoMetaDataBuffer->bufAddr[planes],
                            pVideoMetaDataBuffer->metaBufSize[planes],
                            &pVideoMetaDataBuffer->dmaFd[planes]);


                }
            }
        break;
        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER:

            pVideoFrameCompositeBuffer = (System_VideoFrameCompositeBuffer *)pBuffer->payload;
            pVideoFrameCompositeBuffer->flags = link_chInfo->flags;
            buf_chInfo = &pVideoFrameCompositeBuffer->chInfo;

            for (frames = 0; frames < pVideoFrameCompositeBuffer->numFrames; frames++)
            {
                for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
                {
                    if (pVideoFrameCompositeBuffer->bufAddr[planes][frames] != NULL) {

                        pVideoFrameCompositeBuffer->bufAddr[planes][frames] =
                                (Void *)OSA_memPhys2Virt(
                                       (UInt32)pVideoFrameCompositeBuffer->bufAddr[planes][frames],
                                        IPC_IN_MEM_REGION_TYPE);

                        if (planes != 0 ) {
                            pVideoFrameCompositeBuffer->dmaFd[planes][frames] = -1;
                            continue;
                        }
                        if (pVideoFrameCompositeBuffer->dmaFd[planes][frames] == 0)
                        {
                            size = (link_chInfo->pitch[planes] * link_chInfo->height * 3) / 2;

                            System_exportDmaBuf(pVideoFrameCompositeBuffer->bufAddr[planes][frames],
                                size,
                                &pVideoFrameCompositeBuffer->dmaFd[planes][frames]);
                        }
                    }
                }

                pVideoFrameCompositeBuffer->metaBufAddr[frames] =
                                (Void *)OSA_memPhys2Virt(
                                        (UInt32)pVideoFrameCompositeBuffer->metaBufAddr[frames],
                                        IPC_IN_MEM_REGION_TYPE);

            }
        break;
        case SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME:

            pEglPixmapVideoFrameBuffer = (System_EglPixmapVideoFrameBuffer *)pBuffer->payload;
            pEglPixmapVideoFrameBuffer->flags = link_chInfo->flags;
            buf_chInfo = &pEglPixmapVideoFrameBuffer->chInfo;
    break;
        default:
            Vps_printf("\nUnsupported System Buffer received on A15!!\n");
            OSA_assert(0);
        break;
    }

    /* Some links may not put the channel info - can't rely on the buffer chInfo
     * Copy the create time link channel info to buffer
     * This will not reflect any runtime chInfo updates
     */
    if (buf_chInfo)
        *buf_chInfo = *link_chInfo;
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
                    System_IpcBuffer *pIpcBuffer,
                    UInt32 index)
{
    UInt32 flags = 0;

    flags = pIpcBuffer->flags;

    pBuffer->bufType            = (System_BufferType)System_Buffer_Flag_Get_Buf_Type(flags);
    pBuffer->chNum              = System_Buffer_Flag_Get_Ch_Num(flags);
    pBuffer->payloadSize        = System_Buffer_Flag_Get_Payload_Size(flags);
    pBuffer->srcTimestamp       = pIpcBuffer->srcTimestamp;
    pBuffer->frameId            = pIpcBuffer->frameId;
    pBuffer->ipcInOrgQueElem    = (UInt32)index;

    pBuffer->ipcPrfTimestamp64[0] = pIpcBuffer->ipcPrfTimestamp64[0];
    pBuffer->ipcPrfTimestamp64[1] = pIpcBuffer->ipcPrfTimestamp64[1];

    OSA_assert(pBuffer->payloadSize <= SYSTEM_MAX_PAYLOAD_SIZE );

    memcpy(pBuffer->payload, pIpcBuffer->payload, pBuffer->payloadSize);
    IpcInLink_drvTranslateSystemBufferPayloadPtrs(pObj, pBuffer);
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
    UInt32            index;
    UInt32 numBufs = 0;
    System_Buffer     *pSysBuffer;
    Bool sendNotifyToPrevLink = FALSE;
    UInt64 tmpTimestamp64;

    if(pObj->isFirstFrameRecv == FALSE)
    {
        OSA_resetLatency(&pObj->linkLatency);
        OSA_resetLatency(&pObj->srcToLinkLatency);

        OSA_resetLinkStatistics(&pObj->linkStats,
                          pObj->linkInfo.queInfo[0].numCh,
                          1);

        pObj->isFirstFrameRecv = TRUE;
    }

    while(1)
    {
        queStatus = OSA_ipcQueRead( &pObj->ipcOut2InQue,
                                     (UInt8*)&index,
                                      sizeof(UInt32));

        tmpTimestamp64 = OSA_getCurGlobalTimeInUsec();

        if(queStatus!=SYSTEM_LINK_STATUS_SOK)
            break; /* no more data to read from IPC queue */

        System_IpcBuffer *pIpcBuffer;

        status = OSA_bufGetEmptyBuffer(&pObj->outBufQue,&pSysBuffer,
                                        OSA_TIMEOUT_NONE);
        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            /* failed to get the buffer returning ipcbuffer to free
             * no need to convert to virtual as its a failure case and queElemPhysAddr
             * is physical address
             */
            status = OSA_ipcQueWrite( &pObj->ipcIn2OutQue,
                                        (UInt8*)&index,
                                        sizeof(UInt32));
            sendNotifyToPrevLink = TRUE;
            continue;
        }

        /* Translate to virtual */
        pIpcBuffer = System_ipcGetIpcBuffer(
                        pObj->createArgs.inQueParams.prevLinkId,
                        index
                     );


        if(pIpcBuffer == NULL)
        {
            pObj->linkStats.inBufErrorCount++;
        }
        OSA_assert(pIpcBuffer != NULL);
        if(pSysBuffer == NULL)
        {
            pObj->linkStats.inBufErrorCount++;
        }
        OSA_assert(pSysBuffer != NULL);

        pSysBuffer->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();

        IpcInLink_drvCopyIpcBufferToSystemBuffer(
            pObj,
            pSysBuffer,
            pIpcBuffer,
            index);

        pObj->linkStats.chStats[pSysBuffer->chNum].inBufRecvCount++;

        OSA_updateLatency(&pObj->linkLatency,
                            pSysBuffer->linkLocalTimestamp);
        OSA_updateLatency(&pObj->srcToLinkLatency,
                            pSysBuffer->srcTimestamp);

        pSysBuffer->ipcPrfTimestamp64[0]
            = OSA_getCurGlobalTimeInUsec() - pSysBuffer->ipcPrfTimestamp64[0];
        pSysBuffer->ipcPrfTimestamp64[1]
            = tmpTimestamp64 - pSysBuffer->ipcPrfTimestamp64[1];

        IpcInLink_latencyStatsUpdate(pObj,
                pSysBuffer->ipcPrfTimestamp64[0],
                pSysBuffer->ipcPrfTimestamp64[1]
                        );

        status = OSA_bufPutFullBuffer(&pObj->outBufQue, pSysBuffer);
        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            pObj->linkStats.chStats[pSysBuffer->chNum].inBufDropCount++;
            pObj->linkStats.chStats[pSysBuffer->chNum].outBufDropCount[0]++;
        }
        else
        {
            pObj->linkStats.chStats[pSysBuffer->chNum].inBufProcessCount++;
            pObj->linkStats.chStats[pSysBuffer->chNum].outBufCount[0]++;
        }
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

        numBufs++;
    }
    if(sendNotifyToPrevLink)
    {
        System_ipcSendNotify(pObj->createArgs.inQueParams.prevLinkId);
        sendNotifyToPrevLink = FALSE;
    }
    if(numBufs)
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
    UInt32 index;

    OSA_mutexLock(&(pObj->lock));

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        pBuf = pBufList->buffers[bufId];
        if(pBuf==NULL)
            continue;

        index = pBuf->ipcInOrgQueElem;

        pObj->linkStats.putEmptyBufCount++;
        status = OSA_ipcQueWrite( &pObj->ipcIn2OutQue,
                                    (UInt8*)&index,
                                    sizeof(UInt32));
    }

    if(pBufList->numBuf)
    {
        System_ipcSendNotify(pObj->createArgs.inQueParams.prevLinkId);
    }


    status = OSA_bufPutEmpty(&pObj->outBufQue, pBufList);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);


    OSA_mutexUnlock(&(pObj->lock));
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
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

    status =  OSA_bufGetFull(&pObj->outBufQue, pBufList, OSA_TIMEOUT_NONE);
    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        pObj->linkStats.getFullBufCount++;
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

    snprintf(tskName, sizeof(tskName), "IPC_IN_%u", (unsigned int)pObj->linkInstId);

    OSA_printLinkStatistics(&pObj->linkStats, tskName, TRUE);

    OSA_printLatency( tskName,
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );

    IpcInLink_latencyStatsPrint(pObj, TRUE);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief IPC In link periodic call back function
 *
 *        Calls the notify callback
 *
 * \param   arg     [IN] Link object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void IpcInLink_drvPrdCb(UArg arg)
{
    IpcInLink_obj *pObj = (IpcInLink_obj *)arg;

    IpcInLink_drvNotifyCb(&pObj->tsk);
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
    OSA_mutexLock(&(pObj->lock));

    memset(&pObj->ipcLatencyStats, 0, sizeof(pObj->ipcLatencyStats));

    pObj->ipcLatencyStats.minIpcLatency = 0xFFFFFFFF;
    pObj->ipcLatencyStats.minNotifyLatency = 0xFFFFFFFF;

    OSA_mutexUnlock(&(pObj->lock));
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
    OSA_mutexLock(&(pObj->lock));

    pObj->ipcLatencyStats.count++;
    pObj->ipcLatencyStats.totalIpcLatency += ipcLatency;
    pObj->ipcLatencyStats.totalNotifyLatency
                        += notifyLatency;

    if(ipcLatency < pObj->ipcLatencyStats.minIpcLatency)
        pObj->ipcLatencyStats.minIpcLatency = ipcLatency;

    if(ipcLatency > pObj->ipcLatencyStats.maxIpcLatency)
        pObj->ipcLatencyStats.maxIpcLatency = ipcLatency;


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

    OSA_mutexUnlock(&(pObj->lock));
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
    UInt64 avgTime64=0, minTime64, maxTime64;

    snprintf(tskName, sizeof(tskName), "IPC_IN_%u", (unsigned int)pObj->linkInstId);

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

    avgTime64 = 0;
    if(pObj->ipcLatencyStats.count)
    {
        /* One way buffer passing time is
            round trip time - one-way interrupt handling time
         */
        avgTime64 = (pObj->ipcLatencyStats.totalIpcLatency
                        /
                        pObj->ipcLatencyStats.count);
                    ;
    }

    minTime64 = pObj->ipcLatencyStats.minIpcLatency;
                    ;

    maxTime64 = pObj->ipcLatencyStats.maxIpcLatency;
                    ;

    Vps_printf(" IPC One-way Buffer Passing Latency   (usecs) :"
               " Avg = %6d, Min = %6d, Max = %6d\n",
                (UInt32)avgTime64,
                (UInt32)minTime64,
                (UInt32)maxTime64
               );

    avgTime64 = 0;
    if(pObj->ipcLatencyStats.count)
    {
        avgTime64 = (pObj->ipcLatencyStats.totalNotifyLatency
                    /
                    pObj->ipcLatencyStats.count);
                ;
    }
    minTime64 = pObj->ipcLatencyStats.minNotifyLatency;
                    ;

    maxTime64 = pObj->ipcLatencyStats.maxNotifyLatency;

    /* since two interrupts are exchanged per IPC, we divide the value by 2 */
    Vps_printf(" IPC One-way Notify Interrupt Latency (usecs) :"
               " Avg = %6d, Min = %6d, Max = %6d\n",
                (UInt32)avgTime64,
                (UInt32)minTime64,
                (UInt32)maxTime64
               );

    if(resetStats)
    {
        IpcInLink_latencyStatsReset(pObj);
    }
}
