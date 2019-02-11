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
 * \file mcal_tx.c
 *
 * \brief  This file has the implementation of MCAL Transmitter Module
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
McalTx_Obj gMcalTx_Obj;

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
Int32 McalTx_allocAndInitializeQueue(McalTx_Obj *pObj)
{
    UInt32 elemId;
    Int32 status;

    /* allocate shared memory for IPC queue */
    pObj->a2vSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queA2VObj[0]; //0 for IPU2 to IPU1
    UTILS_assert(pObj->a2vSharedMemBaseAddr!=NULL);

    pObj->v2aSharedMemBaseAddr =
                &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queV2AObj[0]; //0 for IPU2 to IPU1
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
    /* create local queue */
    status = Utils_queCreate(&pObj->localQue,
                         MCAL_QUE_MAX_ELEMENTS,
                         pObj->localQueMem,
                         UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(elemId=0; elemId <MCAL_QUE_MAX_ELEMENTS; elemId++)
    {
        /* Fill elements into the local queue */
        status = Utils_quePut(&pObj->localQue,
                             (Ptr)elemId,
                             0
                             );	
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
Int32 McalTx_deAlloc(McalTx_Obj *pObj)
{
    Int32 status;
    /* Delete local queue */
    status = Utils_queDelete(&pObj->localQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    return status;
}
/**
 *******************************************************************************
 *
 * \brief Release Data
 *
 * \param NULL
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
 */
Int32 McalTx_releaseData()
{
    Int32 status;
    McalTx_Obj *pObj = &gMcalTx_Obj;
    UInt32 idx;
    System_AutosarMetaBuffer     *pMetaBuffer;
    System_AutosarIpcBuffer *pIpcBuffer;

    idx = (UInt32)0xFFFFFFFFU;

    /* Get index from IPC queue */
    status = Utils_ipcQueRead(
                    &pObj->ipcV2AQue,
                    (UInt8*)&idx,
                    sizeof(UInt32)
                    );

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        /* Get the IPC buffer using the index */
        pIpcBuffer =
            &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queElements[idx];

        if(pIpcBuffer != NULL)
        {
            pMetaBuffer = (System_AutosarMetaBuffer*)pIpcBuffer->orgMetaBufferPtr;

            /* Put the index to local queue */
            status = Utils_quePut(&pObj->localQue,
                                 (Ptr)idx,
                                 0
                                 );
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

            if(pMetaBuffer!=NULL)
            {
                /* Inform Receiver Modules */
                McalRx_cb(pMetaBuffer);
            }
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Copy of Meta to IPC buffer
 *
 * \param pIpcBuffer      [IN]      IPC Buffer
 * \param pMetaBuffer     [IN]      Meta Buffer
 *
 *******************************************************************************
 */
Void McalTx_copyIpcToMetaBuffer(System_AutosarIpcBuffer *pIpcBuffer, System_AutosarMetaBuffer *pMetaBuffer)
{
    pIpcBuffer->payloadSize      = pMetaBuffer->payloadSize;
    pIpcBuffer->flag             = pMetaBuffer->flag;
    pIpcBuffer->payload          = pMetaBuffer->payload;
    pIpcBuffer->orgMetaBufferPtr = (UInt32)pMetaBuffer;
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
Void McalTx_cb(System_AutosarMetaBuffer *pMetaBuffer)
{
    Int32 status;
    McalTx_Obj *pObj = &gMcalTx_Obj;
    Bool sendNotify = TRUE;
    Uint32 idx;
    System_AutosarIpcBuffer *pIpcBuffer;

    idx = (UInt32)0xFFFFFFFFU;
    /* Get an Index */
    status =
        Utils_queGet(&pObj->localQue,
                    (Ptr *) &idx,
                     1U,
                     BSP_OSAL_NO_WAIT
                    );

    /* Get the IPC buffer using the index */
    pIpcBuffer =
            &gSystem_autosarIpcSharedMemObj.autosarIpcQueObj.autosarIpcQueProcObj[0U].queElements[idx];

    if((status!=SYSTEM_LINK_STATUS_SOK) || (pIpcBuffer == NULL))
    {
        sendNotify = FALSE;
    }
    else
    {
        /* Copy Meta buffer to IPC buffer */
        McalTx_copyIpcToMetaBuffer(pIpcBuffer, pMetaBuffer);

        /* Write to IPC queue */
        status = Utils_ipcQueWrite(
                            &pObj->ipcA2VQue,
                            (UInt8*)&idx,
                            sizeof(UInt32)
                            );

        if(status!=SYSTEM_LINK_STATUS_SOK)
        {
            sendNotify = FALSE;

            /* return the extracted element to local queue */
            status = Utils_quePut(&pObj->localQue,
                                 (Ptr)idx,
                                  0
                                 );
            UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
        }
    }

    /* if notify mode is enabled and atleast one element added to que
     * then send notify
     */
    if(sendNotify)
    {
        status = Cdd_IpcSendEvent(IPC_CORE_1,
                                  MCAL_TX_NEW_BUFF_IPC_EVENT_ID, (UInt32)NULL, 1U);
    }
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
Int32 McalTx_registerListener()
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    status = Cdd_IpcRegisterEvent(IPC_CORE_1,
                                  MCAL_TX_BUFF_FREE_IPC_EVENT_ID,
                                  &status);
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
Int32 McalTx_unRegisterListener()
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    status = Cdd_IpcUnRegisterEvent(IPC_CORE_1,
                                    MCAL_TX_BUFF_FREE_IPC_EVENT_ID);
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
Void McalTx_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    McalTx_Obj *pObj;

    pObj = &gMcalTx_Obj;
    status = McalTx_registerListener();
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = McalTx_allocAndInitializeQueue(pObj);
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
Void McalTx_deInit(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    McalTx_Obj *pObj;

    pObj = &gMcalTx_Obj;
    status = McalTx_unRegisterListener();
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    status = McalTx_deAlloc(pObj);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
}

