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
 * \file epLink_tsk.c
 *
 * \brief  This file has the implementation of Endpoint Link API
 *
 *         This file implements the state machine logic for this link.
 *         A message command will cause the state machine to take some
 *         action and then move to a different state.
 *         Endpoint link follows the below state machine
 *
 *            Cmds| CREATE | STOP | ALL OTHER COMMANDS | DELETE |
 *         States |========|======|====================|========|
 *           IDLE | RUN    | -    | -                  | -      |
 *           RUN  | -      | STOP | -                  | -      |
 *           STOP | -      | -    | -                  | IDLE   |
 *
 * \version 0.0 (Aug 2013) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "src/hlos/system/system_priv_common.h"
#include "epLink_priv.h"

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
EpLink_obj gEpLink_obj[EP_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function return the channel info to the next link
 *
 * \param  pTsk     [IN]  Task Handle
 * \param  pTsk     [OUT] channel info
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_getLinkInfo(Void *pTsk,
                             System_LinkInfo *info)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    OSA_TskHndl * pTskHndl = (OSA_TskHndl *)pTsk;
    EpLink_obj * pObj = (EpLink_obj * )pTskHndl->appData;

    /**
      * 'info' structure is set with valid values during 'create' phase
      * this function should work well for both source and sink.
     */
    memcpy(info, &pObj->linkInfo, sizeof(*info));

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback implemented by link to give full buffers to nextLink.
 *
 * Endpoint link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from Endpoint
 * output queue.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/

Int32 EpLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    EpLink_obj *pObj = (EpLink_obj *) pTsk->appData;

    if (pObj->ep_ctx.type == EP_SINK) {
        /**
         * it's not required to implement 'getFullBuffers' for sink
         */
        status = SYSTEM_LINK_STATUS_EUNSUPPORTED_CMD;
    }
    else if (pObj->ep_ctx.type == EP_SOURCE) {
        /**
         * source eplink sends filled buffers to next link
         */
        status = EpLink_drvSourceGetFullBuffers(pObj, pBufList);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback implemented by link to return empty buffers to prevLink
 *        link.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EpLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    EpLink_obj *pObj = (EpLink_obj *) pTsk->appData;

    if (pObj->ep_ctx.type == EP_SINK) {
        /* sink eplink receives empty buffers from vivi */
        status = EpLink_drvSinkPutEmptyBuffers(pObj, pBufList);
    }
    else if (pObj->ep_ctx.type == EP_SOURCE) {
        /* source eplink receives empty buffers from next link */
        status = EpLink_drvSourcePutEmptyBuffers(pObj, pBufList);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Create buffer queue handle for Endpoint(EP) link
 *
 *        This function opens the message queue created by the vivi framework
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvCreateQueHandle(EpLink_obj *pObj, OSA_MsgHndl *pMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    struct ep_buf_que *pQue;
    pQue = OSA_msgGetPrm(pMsg);
    pObj->post_buf = pQue->post_buf;
		
		memcpy(pObj->ep_ctx.qh,pQue->qh,(sizeof(int)*2));
		if(pObj->ep_ctx.qh[0] < 0){
#ifdef SYSTEM_DEBUG_EP
        Vps_printf(" EP_%d   : Failed to create que handle !!!\n",
            pObj->instId
              );
#endif
        return SYSTEM_LINK_STATUS_EFAIL;
    }

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%d   : Create Que Handle Done !!!\n",
           pObj->instId
          );
#endif
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Close buffer queue handle for Endpoint(EP) link
 *
 *        This function closes the message queue as pointed by the mqdes
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvCloseQueHandle(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    if (!pObj->ep_ctx.qh[0]) {
        return status;
    }

    status = close(pObj->ep_ctx.qh[0])+close(pObj->ep_ctx.qh[1]);
    
		if (status < 0) {
#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%d   : Failed to close que handle !!!\n",
           pObj->instId
          );
#endif
        return SYSTEM_LINK_STATUS_EFAIL;
    }

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%d   : Close Que Handle Done !!!\n",
           pObj->instId
          );
#endif
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Run and stop state.
 *
 *        In this state link gets commands to process incoming frames from
 *        previous link and release processed frames from next link to previous
 *        link
 *
 * \param  pTsk     [IN] Task Handle
 * \param  pObj     [IN] Link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_tskRun(EpLink_obj * pObj, OSA_TskHndl * pTsk)
{
    Int32          status  = SYSTEM_LINK_STATUS_SOK;
    Bool           runDone = FALSE;
    OSA_MsgHndl    *pRunMsg;
    System_Buffer  *pBuffer;
    UInt32         cmd;

    /*
     * This while loop implements RUN state. All the commands for Endpoint
     * are received and serviced in this while loop. Control remains
     * in this loop until delete commands arrives.
     */
    while (!runDone)
    {
        /*
         * Wait for message indefinitely here. Once message arrives, extract
         * the command.
         */
        status = OSA_tskWaitMsg(pTsk, &pRunMsg);
        if (status != OSA_SOK)
            break;
        cmd = OSA_msgGetCmd(pRunMsg);

        /*
         * Different commands are serviced via this switch case. For each
         * command, after servicing, ACK or free message is sent before
         * proceeding to next state.
         */
        switch (cmd)
        {
            case EP_CMD_PUT_BUF:
                /**
                 * For source - issued by vivi framework
                 */
                pBuffer = OSA_msgGetPrm(pRunMsg);
                status  = EpLink_drvSourceProcessBuffers(pObj, pBuffer);

                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_NEW_DATA:
                /**
                 * For sink - issued by prevLink
                 */

                if (pObj->ep_ctx.type == EP_SINK)
                {
                    status  = EpLink_drvSinkProcessBuffers(pObj);
                }
                else
                {
                    status = SYSTEM_LINK_STATUS_EUNSUPPORTED_CMD;
                }

                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_STOP:
                if (pObj->ep_ctx.type == EP_SINK)
                    status = EpLink_drvSinkStop(pObj);
                else if (pObj->ep_ctx.type == EP_SOURCE)
                    status = EpLink_drvSourceStop(pObj);

                runDone = TRUE;
                //status  = SYSTEM_LINK_STATUS_SOK;
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            /*
             * Invalid command for this state.  ACK it and continue RUN
             */
            default:
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Idle state.
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Int32 EpLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    EpLink_obj          *pObj;
    EpLink_CreateParams *pPrm;
    UInt32              nameLen = 0;
    Int32               status = SYSTEM_LINK_STATUS_SOK;
    UInt32              cmd = OSA_msgGetCmd(pMsg);

    pObj = (EpLink_obj *) pTsk->appData;

    cmd = OSA_msgGetCmd(pMsg);

    switch (cmd) {
        case SYSTEM_CMD_CREATE:
            /*
             * Create command received, create the Endpoint related data structure's
             */
            pPrm = OSA_msgGetPrm(pMsg);
            pObj->ep_ctx.type = pPrm->epType;
            pObj->ep_ctx.chain_id = pPrm->chainId;

            nameLen = strlen(pPrm->plugName);
            if (nameLen >= VIVI_MAX_NAME)
                return SYSTEM_LINK_STATUS_EFAIL;

            strcpy(pObj->ep_ctx.pname, pPrm->plugName);

            /* keep a copy of create args */
            memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

            if (pObj->ep_ctx.type == EP_SINK)
                status = EpLink_drvSinkCreate(pObj);
            else if (pObj->ep_ctx.type == EP_SOURCE)
                status = EpLink_drvSourceCreate(pObj, &pPrm->srcConfig);

            OSA_tskAckOrFreeMsg(pMsg, status);
						break;

        case EP_CMD_CREATE_QUE_HANDLE:
            /**
             * This command will be sent by the vivi framework to create
             * Que handle. This is sent after the chain is created and before
             * it's started.
             */
            status = EpLink_drvCreateQueHandle(pObj, pMsg);
            OSA_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_START:
            if (pObj->ep_ctx.type == EP_SINK)
                status = EpLink_drvSinkStart(pObj);
            else if (pObj->ep_ctx.type == EP_SOURCE)
                status = EpLink_drvSourceStart(pObj);

            OSA_tskAckOrFreeMsg(pMsg, status);
            status = EpLink_tskRun(pObj, pTsk);
            break;

        case SYSTEM_CMD_DELETE:
           if (pObj->ep_ctx.type == EP_SINK) {
               EpLink_drvSinkDelete(pObj);
           }
           else if (pObj->ep_ctx.type == EP_SOURCE) {
               EpLink_drvSourceDelete(pObj);
           }
           else {
               status = SYSTEM_LINK_STATUS_EFAIL;
           }
           OSA_tskAckOrFreeMsg(pMsg, status);
           break;

        default:
            OSA_tskAckOrFreeMsg(pMsg, OSA_EFAIL);
            status = OSA_EFAIL;
        }
    /*
     * Entering IDLE state
     */
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Init function for Endpoint link. BIOS task for
 *        link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 EpLink_init()
{
    Int32                status;
    UInt32               instId;
    System_LinkObj       linkObj;
    EpLink_obj           *pObj;
    UInt32               procId = System_getSelfProcId();

    for(instId = 0; instId<EP_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gEpLink_obj[instId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId =
            SYSTEM_MAKE_LINK_ID(procId,
                                SYSTEM_LINK_ID_EP_0 + instId);

        pObj->ep_ctx.id = pObj->linkId;
        pObj->instId = instId;

        memset(&linkObj, 0, sizeof(linkObj));

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = EpLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = EpLink_putEmptyBuffers;
        linkObj.getLinkInfo         = EpLink_getLinkInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * EpLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "EP_%u", (unsigned int)instId);
        status = OSA_tskCreate(&pObj->tsk,
                                 EpLink_tskMain,
                                 EP_LINK_TSK_PRI,
                                 EP_LINK_TSK_STACK_SIZE,
                                 0,
                                 pObj,
                                 pObj->tskName);
        OSA_assert(status == OSA_SOK);
        Vps_printf(" %s : Init done - linkid-0x%x\n", pObj->tskName, pObj->linkId);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for Endpoint link. BIOS task for
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EpLink_deInit()
{
    EpLink_obj *pObj;
    UInt32     instId;

    for(instId = 0; instId<EP_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gEpLink_obj[instId];

        OSA_tskDelete(&pObj->tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
            gEpLink_obj[instId].tskName, gEpLink_obj[instId].linkId);
    }

    return SYSTEM_LINK_STATUS_SOK;
}
