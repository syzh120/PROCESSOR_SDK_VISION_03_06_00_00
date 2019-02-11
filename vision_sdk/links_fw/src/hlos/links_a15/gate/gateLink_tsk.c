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
  ******************************************************************************
 * \file gateLink_tsk.c
 *
 * \brief  This file has the implementation of GATE Link API
 **
 *         This file implements the state machine logic for this link.
 *         A message command will cause the state machine
 *         to take some action and then move to a different state.
 *
 * \version 0.0 (Apr 2015) : [YM] First version ported to HLOS
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "gateLink_priv.h"

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
GateLink_Obj gGateLink_obj[GATE_LINK_OBJ_MAX];

/**
 *******************************************************************************
 * \brief Gate link allows application writers to have connections with links
 *        which will be instantiated later in the course of execution.
 *        Based on the state this is in, it either returns buffer immediately
 *        or forwards it to the next link.
 *
 *        This function does the following,
 *
 *        - Copies the user passed create params into the link object
 *          create params
 *        - Based on prevLinkIsCreated calls linkGetInfo or expects data about
 *          "would be" previous link from create parameters
 *
 * \param  pObj     [IN]  GATE link instance handle
 * \param  pPrm     [IN]  Create params for GATE link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_drvCreate(GateLink_Obj * pObj, const GateLink_CreateParams * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    memcpy((Ptr)&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    pObj->opStatus = GATE_LINK_OPERATION_STATUS_OFF;

    if(pObj->createArgs.prevLinkIsCreated)
    {
        status = System_linkGetInfo(
                        pObj->createArgs.inQueParams.prevLinkId, &pObj->createArgs.prevLinkInfo);

        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
        OSA_assert(pPrm->inQueParams.prevLinkQueId < pObj->createArgs.prevLinkInfo.numQue);
    }

    status = OSA_mutexCreate(&(pObj->lock));
    OSA_assert(status == OSA_SOK);

    pObj->bufCount = 0;

    return status;
}

/**
 *******************************************************************************
 * \brief GATE Link based on its state either forwards buffers to next link
 *        or returns buffers to previous link, it doesnt have any input or
 *        output queues of its own.
 *
 * \param  pObj     [IN]  GATE link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 GateLink_drvProcessData(GateLink_Obj * pObj)
{
    GateLink_CreateParams *pCreateArgs;
    System_BufferList bufList;

    pCreateArgs = &pObj->createArgs;

    if (pObj->opStatus == GATE_LINK_OPERATION_STATUS_ON)
    {
        System_sendLinkCmd(pCreateArgs->outQueParams.nextLink,
                        SYSTEM_CMD_NEW_DATA, NULL);
    }
    else if(pObj->opStatus == GATE_LINK_OPERATION_STATUS_OFF)
    {
        System_getLinksFullBuffers(
                    pCreateArgs->inQueParams.prevLinkId,
                    pCreateArgs->inQueParams.prevLinkQueId,
                    &bufList);

        /* Return the buffers to previous link */
        System_putLinksEmptyBuffers(
                    pObj->createArgs.inQueParams.prevLinkId,
                    pObj->createArgs.inQueParams.prevLinkQueId,
                    &bufList);

    }
    else
    {
        OSA_assert((Bool)0U);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to GATE link to get data from
 *    the output queue of GATE link's previous link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GateLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    GateLink_Obj *pObj;
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;
    GateLink_CreateParams *pCreateArgs;

    pObj = (GateLink_Obj *) pTsk->appData;

    OSA_mutexLock(&(pObj->lock));
    pCreateArgs = &pObj->createArgs;
    if(pObj->opStatus == GATE_LINK_OPERATION_STATUS_ON)
    {
        System_getLinksFullBuffers(
                    pCreateArgs->inQueParams.prevLinkId,
                    pCreateArgs->inQueParams.prevLinkQueId,
                    pBufList);

        pObj->bufCount += pBufList->numBuf;
    }
    else if(pObj->opStatus == GATE_LINK_OPERATION_STATUS_OFF)
    {
        pBufList->numBuf = 0;
    }
    else
    {
        OSA_assert((Bool)0U);
    }
    OSA_mutexUnlock(&(pObj->lock));;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to GATE link to get output queue
 *    Information of GATE link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of GATE link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GateLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    GateLink_Obj *pObj = (GateLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->createArgs.prevLinkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to GATE link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to GATE link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GateLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{

    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;
    GateLink_Obj *pObj = (GateLink_Obj *) pTsk->appData;

    OSA_mutexLock(&(pObj->lock));;
    System_putLinksEmptyBuffers(
                    pObj->createArgs.inQueParams.prevLinkId,
                    pObj->createArgs.inQueParams.prevLinkQueId,
                    pBufList);

    pObj->bufCount -= pBufList->numBuf;
    OSA_assert(pObj->bufCount >= 0);
    OSA_mutexUnlock(&(pObj->lock));;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function to delete GATE link. This will simply delete all output
 *    queues and the semaphore
 *
 * \param  pObj     [IN]  GATE link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 GateLink_drvDelete(GateLink_Obj * pObj)
{

    OSA_mutexDelete(&pObj->lock);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating GATE link
 *     - Arrival of new data
 *     - Deleting GATE link
 *     - Changing operation status
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
 /*
* MISRA.PPARAM.NEEDS.CONS
* MISRAC_2004_Rule_16.7
* Function parameter is not declared as a pointer to const.
* In Other Links it calls OSA_tskRecvMsg where the memory
* pointed by pTsk will be updated .So ptask cannot be made const
* KW State: Defer -> Waiver -> Case by case
*/
Void GateLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Int32 status = 0;

    GateLink_Obj *pObj = (GateLink_Obj*) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(pObj->state==SYSTEM_LINK_STATE_IDLE)
            {
                status = GateLink_drvCreate(pObj, OSA_msgGetPrm(pMsg));
                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    pObj->state = SYSTEM_LINK_STATE_RUNNING;
                }
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_NEW_DATA:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                status = GateLink_drvProcessData(pObj);
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_DELETE:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                GateLink_drvDelete(pObj);
                pObj->state = SYSTEM_LINK_STATE_IDLE;
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;

        case GATE_LINK_CMD_SET_OPERATION_MODE_ON:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                OSA_mutexLock(&(pObj->lock));
                pObj->opStatus = GATE_LINK_OPERATION_STATUS_ON;
                OSA_mutexUnlock(&(pObj->lock));
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;

        case GATE_LINK_CMD_SET_OPERATION_MODE_OFF:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                OSA_mutexLock(&(pObj->lock));
                pObj->opStatus = GATE_LINK_OPERATION_STATUS_OFF;
                GateLink_drvProcessData(pObj);
                OSA_mutexUnlock(&(pObj->lock));
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;

        case GATE_LINK_CMD_GET_BUFFER_FORWARD_COUNT:
            if(pObj->state==SYSTEM_LINK_STATE_RUNNING)
            {
                UInt32 *bufCount = (UInt32 *) OSA_msgGetPrm(pMsg);
                *bufCount = pObj->bufCount;
            }
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;


        default:
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for GATE link. This function does the following for each
 *   GATE link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 GateLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 gateId;
    GateLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    for(gateId = 0; gateId < GATE_LINK_OBJ_MAX; gateId++)
    {
        pObj = &gGateLink_obj[gateId];

        memset(pObj, 0, sizeof(GateLink_Obj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_GATE_0 + gateId);

        pObj->state = SYSTEM_LINK_STATE_IDLE;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &GateLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &GateLink_putEmptyBuffers;
        linkObj.getLinkInfo = &GateLink_getLinkInfo;

        System_registerLink(pObj->tskId, &linkObj);

        status = GateLink_tskCreate(gateId);
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for GATE link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 GateLink_deInit(void)
 {
    UInt32 gateId;

    for(gateId = 0; gateId < GATE_LINK_OBJ_MAX; gateId++)
    {
        OSA_tskDelete(&gGateLink_obj[gateId].tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
             gGateLink_obj[gateId].tskName, gGateLink_obj[gateId].linkId);
    }
    return SYSTEM_LINK_STATUS_SOK;
 }
