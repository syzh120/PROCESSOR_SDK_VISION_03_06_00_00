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
 * \file autosar_ipcInLink_drv.c
 *
 * \brief  This file has the implementation of IPC IN Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (Aug 2018) : [AKG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "autosar_ipcInLink_priv.h"


extern System_IpcSharedMemObj  gSystem_autosarIpcSharedMemObj;

/*******************************************************************************
 *  Function prototype's
 *******************************************************************************
 */
Void printInfo(System_AutosarIpcBuffer *pBuffer);

/**
 *******************************************************************************
 *
 * \brief This function is called when autosar module send a notify
 *
 *        A command is sent to the IPC thread to read buffer's from Autosar
 *        to Vision queue
 *
 * \param  pTsk     [IN]  Task Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AutosarIpcInLink_drvNotifyCb(UInt32 remoteProcId, UInt32 eventId,
                                UInt32 payload,
                                Void     *arg,
                                Int32  status)
{
    if (eventId != AUTOSAR_IPC_IN_NEW_BUFF_IPC_EVENT_ID)
    {
        Vps_printf("AUTOSAR_IPC_IN: Unexpected event ID received on IPC! %d", eventId);
    }
    else if (status != IPCLIB_SOK)
    {
        Vps_printf("AUTOSAR_IPC_IN: Error received on IPC! %d", status);
    }
    else
    {
        AutosarIpcInLink_obj * pObj = (AutosarIpcInLink_obj * )arg;
        pObj->linkStatsInfo->linkStats.notifyEventCount++;

        if(Utils_ipcQueIsEmpty(&pObj->ipcA2VQue)==FALSE)
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
    return IPCLIB_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Create Autosar IPC In link
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AutosarIpcInLink_drvCreate(AutosarIpcInLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char                 tskName[32];

#ifdef SYSTEM_DEBUG_AUTOSAR_IPC
    Vps_printf(" AUTOSAR_IPC_IN_%d   : Create in progress !!!\n",
               pObj->linkInstId
               );
#endif

    UTILS_MEMLOG_USED_START();

    /* allocate shared memory for IPC queue */
    pObj->a2vSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queA2VObj[pObj->linkInstId]; //0 for IPU2 to IPU1
    UTILS_assert(pObj->a2vSharedMemBaseAddr!=NULL);

    pObj->v2aSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queV2AObj[pObj->linkInstId]; //0 for IPU2 to IPU1
    UTILS_assert(pObj->v2aSharedMemBaseAddr!=NULL);

    /* create IPC queue's */
    status = Utils_ipcQueCreate(
                        &pObj->ipcA2VQue,
                        SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U,
                        pObj->a2vSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = Utils_ipcQueCreate(
                        &pObj->ipcV2AQue,
                        SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U,
                        pObj->v2aSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = Utils_ipcQueReset(&pObj->ipcA2VQue,
                        pObj->a2vSharedMemBaseAddr,
                        (Bool)TRUE,//rdidx
                        (Bool)TRUE); //wridx

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_ipcQueReset(&pObj->ipcV2AQue,
                        pObj->v2aSharedMemBaseAddr,
                        (Bool)TRUE,
                        (Bool)TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Application callback */
    pObj->appCb = printInfo;

    pObj->isFirstFrameRecv = (Bool)FALSE;

    snprintf(tskName, sizeof(tskName), "AUTOSAR_IPC_IN_%u", (UInt32)pObj->linkInstId);

    /* Assign pointer to link stats object */
    pObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(pObj->linkId, tskName);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    UTILS_MEMLOG_USED_END(pObj->memUsed);
    UTILS_MEMLOG_PRINT("AUTOSAR_IPC_IN:",
                   pObj->memUsed,
                   UTILS_ARRAYSIZE(pObj->memUsed));

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" AUTOSAR_IPC_IN_%d   : Create Done !!!\n",
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
Int32 AutosarIpcInLink_drvDelete(AutosarIpcInLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_AUTOSAR_IPC
    Vps_printf(" AUTOSAR_IPC_IN_%d   : Delete in progress !!!\n",
           pObj->linkInstId
          );
#endif

    /* delete ipc queue */
    Utils_ipcQueDelete(&pObj->ipcA2VQue);
    Utils_ipcQueDelete(&pObj->ipcV2AQue);

    status = Utils_linkStatsCollectorDeAllocInst(pObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

#ifdef SYSTEM_DEBUG_IPC
    Vps_printf(" AUTOSAR_IPC_IN_%d   : Delete Done !!!\n",
           pObj->linkInstId
          );
#endif
    return status;
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
Int32 AutosarIpcInLink_drvProcessBuffers(AutosarIpcInLink_obj *pObj)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    Int32 queStatus = SYSTEM_LINK_STATUS_SOK;
    UInt32            idx;
    UInt32 numBufs = 0;
    System_LinkStatistics *linkStatsInfo;
    System_AutosarIpcBuffer *pIpcBuffer;

    linkStatsInfo = pObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pObj->isFirstFrameRecv == FALSE)
    {
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                          1,
                          (UInt32)TRUE);

        pObj->isFirstFrameRecv = (Bool)TRUE;
    }

    /* MISRA.CAST.PTR
     * MISRAC_2004 Rule_11.4
     * MISRAC_WAIVER:
     * This is a generic queue implementation which supports all dataTypes.
     * This typecasting is necessary.
     */
    queStatus = Utils_ipcQueRead( &pObj->ipcA2VQue,
                                 (UInt8*)&idx,
                                  sizeof(UInt32));

    UTILS_assert(queStatus==SYSTEM_LINK_STATUS_SOK);
    pIpcBuffer =
            &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queElements[idx];

    if(pIpcBuffer == NULL)
    {
        pObj->linkStatsInfo->linkStats.inBufErrorCount++;
    }
    UTILS_assert(pIpcBuffer != NULL);

    if(pIpcBuffer != NULL)
    {
        Cache_inv(pIpcBuffer->payload, pIpcBuffer->payloadSize, Cache_Type_ALL, TRUE);
        linkStatsInfo->linkStats.chStats[0].
                inBufRecvCount++;

        linkStatsInfo->linkStats.chStats[0].
                    inBufProcessCount++;
        linkStatsInfo->linkStats.chStats[0].
                    outBufCount[0]++;

        numBufs++;
    }
    if(numBufs>0)
    {
        /* Inform Application to print the information */
        pObj->appCb(pIpcBuffer);

        status = Utils_ipcQueWrite( &pObj->ipcV2AQue,
                                    (UInt8*)&idx,
                                    sizeof(UInt32));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        status = IpcLib_interruptSendEvent(IPCLIB_IPU2_0_ID,
                                           AUTOSAR_IPC_IN_BUFF_FREE_IPC_EVENT_ID,
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
 * \brief Print IPC link related statistics
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AutosarIpcInLink_drvPrintStatistics(AutosarIpcInLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char  tskName[32];

    snprintf(tskName, sizeof(tskName), "AUTOSAR_IPC_IN_%u", (UInt32)pObj->linkInstId);

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
