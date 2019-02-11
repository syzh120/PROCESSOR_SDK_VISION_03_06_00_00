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
 * \file mcal_rx.c
 *
 * \brief  This file has the implementation of MCAL Receiver Module
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
#include "mcal_rx_tx.h"

/**
 *******************************************************************************
 * \brief Module object, stores all module related information
 *******************************************************************************
 */
McalRx_Obj gMcalRx_Obj;

/**
 *******************************************************************************
 * \brief IPC object, stores all IPC module related information
 *******************************************************************************
 */
extern System_IpcSharedMemObj  gSystem_autosarIpcSharedMemObj;

/**
 *******************************************************************************
 *
 * \brief Allocation and Initialization of buffers
 *
 * \param pObj      [IN]    Module object
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 McalRx_allocAndInitializeQueue(McalRx_Obj *pObj)
{
    UInt32 elemId;
    Int32 status;

    /* allocate shared memory for IPC queue */
    pObj->a2vSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queA2VObj[0]; //0 for IPU2 to IPU1
    UTILS_assert(pObj->a2vSharedMemBaseAddr!=NULL);

    pObj->v2aSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queV2AObj[0]; //0 for IPU2 to IPU1
    UTILS_assert(pObj->v2aSharedMemBaseAddr!=NULL);

    /* Create IPC queue's */

    Utils_ipcQueCreate(&pObj->ipcV2AQue,
                        MCAL_QUE_MAX_ELEMENTS+1U,
                        pObj->v2aSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    Utils_ipcQueCreate(&pObj->ipcA2VQue,
                        MCAL_QUE_MAX_ELEMENTS+1U,
                        pObj->a2vSharedMemBaseAddr,
                        sizeof(UInt32)
                    );
    /* create the output queue */
    status = Utils_bufCreate(&pObj->outBufQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Fill the queue */
    for(elemId=0; elemId <MCAL_QUE_MAX_ELEMENTS; elemId++)
    {
        status = Utils_bufPutEmptyBuffer(&pObj->outBufQue, (System_Buffer *)(&(pObj->buffers[elemId])));
        UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);	
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Deallocation of buffers
 *
 * \param pObj      [IN]    Module object
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 McalRx_deAlloc(McalRx_Obj *pObj)
{
    Int32 status;

    /* Delete the output queue */
    status = Utils_bufDelete(&pObj->outBufQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    return status;
}
/**
 *******************************************************************************
 *
 * \brief Copy of IPC to Meta buffer
 *
 * \param pIpcBuffer      [IN]      IPC Buffer
 * \param pMetaBuffer     [IN]      Meta Buffer
 *
 *******************************************************************************
 */
Void McalRx_compareMetaBuffer(System_AutosarIpcBuffer *pIpcBuffer, System_AutosarMetaBuffer *pMetaBuffer)
{
    char v2aMsg[]             = "Sending message from vision sdk to Autosar";
    char a2vPositiveAckMsg[]  = "Auotsar Ack : Received proper message from vision sdk";
    char a2vNegativeAckMsg[]  = "Auotsar Ack : Received wrong message from vision sdk";
    UInt32 verifyMsg;

    /* Using the memory allocated by IPU1_0 */
    pMetaBuffer->payload = pIpcBuffer->payloadMcal;

    /* Verify the messgae */
    Cache_inv(pIpcBuffer->payload, pIpcBuffer->payloadSize, Cache_Type_ALL, TRUE);
    verifyMsg = strncmp((char *)pIpcBuffer->payload,v2aMsg,sizeof(v2aMsg));
    if (verifyMsg == 0)
    {
        memcpy(pMetaBuffer->payload, a2vPositiveAckMsg, sizeof(a2vPositiveAckMsg));
        pMetaBuffer->payloadSize    = sizeof(a2vPositiveAckMsg);
	}
    else
    {
        memcpy(pMetaBuffer->payload, a2vNegativeAckMsg, sizeof(a2vNegativeAckMsg));
        pMetaBuffer->payloadSize    = sizeof(a2vNegativeAckMsg);
    }
    pMetaBuffer->flag           = pIpcBuffer->flag;
    Cache_wbInvAll();
}

/**
 *******************************************************************************
 *
 * \brief Process Data
 *
 * \param NULL
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
 */
Int32 McalRx_processData()
{
    Int32 status;
    McalRx_Obj *pObj = &gMcalRx_Obj;
    UInt32 idx;
    System_Buffer     *pMetaBuffer;
    System_AutosarIpcBuffer *pIpcBuffer;
    Bool sendNotify  = TRUE;

    /* Get an Empty buffer */
    status = Utils_bufGetEmptyBuffer(&pObj->outBufQue,&pMetaBuffer,
                                    BSP_OSAL_NO_WAIT);
    if(status!=SYSTEM_LINK_STATUS_SOK)
    {
        sendNotify = FALSE;
    }
    else
    {
        /* Read IPC queue */
        status = Utils_ipcQueRead( &pObj->ipcV2AQue,
                                 (UInt8*)&idx,
                                 sizeof(UInt32));

        if(status!=SYSTEM_LINK_STATUS_SOK)
        {
            sendNotify = FALSE;
        }
        else
        {
            /* Get the IPC buffer using the index */
            pIpcBuffer =
                    &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[1U].queElements[idx];
            UTILS_assert(pIpcBuffer != NULL);

            /* Copy IPC buffer to meta buffer */
            McalRx_compareMetaBuffer(pIpcBuffer, (System_AutosarMetaBuffer *)pMetaBuffer);
            if(sendNotify == TRUE)
            {
                /* Inform Transmitter Module */
                McalTx_cb((System_AutosarMetaBuffer *)pMetaBuffer);

                /* Write back to IPC queue */
                status = Utils_ipcQueWrite(&pObj->ipcA2VQue,
                                          (UInt8*)&idx,
                                          sizeof(UInt32));
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Moduke callback
 *
 * \param pMetaBuffer       [IN]      Meta buffer
 *
 *******************************************************************************
 */
Void McalRx_cb(System_AutosarMetaBuffer *pMetaBuffer)
{
    Int32 status;
    McalRx_Obj *pObj = &gMcalRx_Obj;
    UTILS_assert(pMetaBuffer != NULL);

    /* Send an event to IPU1_0 */
    status = Cdd_IpcSendEvent(IPC_CORE_1,
                        MCAL_RX_BUFF_FREE_IPC_EVENT_ID, (UInt32)NULL, 1U);
    /* Put empty buffer to queue */
    status = Utils_bufPutEmptyBuffer(&pObj->outBufQue, (System_Buffer *)pMetaBuffer);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
}

/**
 *******************************************************************************
 *
 * \brief Register callback for IPC event
 *
 * \param NULL
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
 */
Int32 McalRx_registerListener()
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    status = Cdd_IpcRegisterEvent(IPC_CORE_1,
                                  MCAL_RX_NEW_BUFF_IPC_EVENT_ID,
                                  &status);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Un-Register callback for IPC event
 *
 * \param NULL
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
 */
Int32 McalRx_unRegisterListener()
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    status = Cdd_IpcUnRegisterEvent(IPC_CORE_1,
                                   MCAL_RX_NEW_BUFF_IPC_EVENT_ID);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
    return status;
}
/**
 *******************************************************************************
 *
 * \brief Module Init
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void McalRx_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    McalRx_Obj *pObj;

    pObj = &gMcalRx_Obj;
    status = McalRx_registerListener();
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = McalRx_allocAndInitializeQueue(pObj);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
}

/**
 *******************************************************************************
 *
 * \brief Module De-Init
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void McalRx_deInit(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    McalRx_Obj *pObj;

    pObj = &gMcalRx_Obj;
    status = McalRx_unRegisterListener();
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = McalRx_deAlloc(pObj);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
}

