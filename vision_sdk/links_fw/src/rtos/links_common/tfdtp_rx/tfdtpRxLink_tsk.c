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
 * \file tfdtpRxLink_tsk.c
 *
 * \brief  This file has the implementation of TFDTP Rx Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 *           The state machine table is as shown below
 *
 *   Cmds   | CREATE | DETECT_VIDEO | START | NEW_DATA  | STOP   | DELETE |
 *   States |========|==============|=======|===========|========|========|
 *   IDLE   | READY  | -            | -     | -         | -      | -      |
 *   READY  | -      | READY        | RUN   | -         | READY  | IDLE   |
 *   RUN    | -      | -            | -     | RUN       | READY  | IDLE   |
 *
 *
 * \version 0.0 (Nov 2016) : [PYJ] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "tfdtpRxLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */

Void TfdtpSrcLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

Int32 TfdtpRxLink_tskRun(TfdtpRxLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);
/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gTfdtpRxLink_tskStack, 32)
#pragma DATA_SECTION(gTfdtpRxLink_tskStack, ".bss:taskStackSection")
UInt8 gTfdtpRxLink_tskStack[TFDTP_RX_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
/* link object, stores all link related information */
TfdtpRxLink_Obj gTfdtpRxLink_obj;

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Run state of link.
 *
 * In this state link waits for command from application or next link or from
 * driver. Basically all are control commands except the new_data command where
 * link gets the MJPEG frames from TFDTP driver and puts in output queue. After
 * that it sends command to next link.
 *
 * \param  pObj     [IN] TFDTPRx link object
 * \param  pTsk     [IN] TFDTPRx link Task handle
 * \param  pMsg     [IN] Message for the link. Contains command and args.
 * \param  done     [IN] Flag to exit idle state.
 * \param  ackMsg   [IN] Flag to decide whether to send ack message or not to
 *                       caller
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_tskRun(TfdtpRxLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone, runAckMsg;
    Utils_MsgHndl *pRunMsg;
    UInt32 cmd;

    /* READY loop done and ackMsg status */
    *done = (Bool)FALSE;
    *ackMsg = (Bool)FALSE;
    *pMsg = NULL;

    /* RUN loop done and ackMsg status */
    runDone = (Bool) FALSE;
    runAckMsg = (Bool) FALSE;

    /* RUN state loop */
    while (!runDone)
    {
        /* wait for message */
        status = Utils_tskRecvMsg(pTsk, &pRunMsg, BSP_OSAL_WAIT_FOREVER);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }

        /* extract message command from message */
        cmd = Utils_msgGetCmd(pRunMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                /* new data frames have been captured, process them */

                TfdtpRxLink_drvPrintStatus(pObj);

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                TfdtpRxLink_printBufferStatus(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_STOP:
                /* stop RUN loop and goto READY state */
                runDone = (Bool) TRUE;

                /* ACK message after actually stopping the driver outside the
                 * RUN loop */
                runAckMsg = (Bool) TRUE;
                break;

            case SYSTEM_CMD_DELETE:

                /* stop RUN loop and goto IDLE state */

                /* exit RUN loop */
                runDone = (Bool) TRUE;

                /* exit READY loop */
                *done = (Bool) TRUE;

                /* ACK message after exiting READY loop */
                *ackMsg = (Bool) TRUE;

                /* Pass the received message to the READY loop */
                *pMsg = pRunMsg;

                break;
            default:

                /* invalid command for this state ACK it and continue RUN
                 * loop */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop driver */
    TfdtpRxLink_drvStop(pObj);

    /* ACK message if not ACKed earlier */
    if (runAckMsg)
    {
        Utils_tskAckOrFreeMsg(pRunMsg, status);
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
Void TfdtpSrcLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    TfdtpRxLink_Obj *pObj;

    /* IDLE state */

    pObj = (TfdtpRxLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
         * with error status */
        Utils_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EFAIL);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the driver */

        status = TfdtpRxLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

        /* ACK based on create status */
        Utils_tskAckOrFreeMsg(pMsg, status);
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* create success, entering READY state */
        done = (Bool) FALSE;
        ackMsg = (Bool) FALSE;

        /* READY state loop */
        while (!done)
        {
            /* wait for message */
            status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }

            /* extract message command from message */
            cmd = Utils_msgGetCmd(pMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_START:
                    /* Start capture driver */
                    status = TfdtpRxLink_drvStart(pObj);

                    /* ACK based on create status */
                    Utils_tskAckOrFreeMsg(pMsg, status);

                    /* if start status is error then remain in READY state */
                    if (status == SYSTEM_LINK_STATUS_SOK)
                    {
                        /* start success, entering RUN state */
                        status =
                            TfdtpRxLink_tskRun(pObj, pTsk, &pMsg, &done, &ackMsg);

                        /** done = FALSE, exit RUN state
                        done = TRUE, exit RUN and READY state
                        */
                    }

                    break;
                case SYSTEM_CMD_DELETE:

                    /* exit READY state */
                    done = (Bool) TRUE;
                    ackMsg = (Bool) TRUE;
                    break;
                default:
                    /* invalid command for this state ACK it and continue READY
                    * loop */
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        /* exiting READY state, delete driver */
        TfdtpRxLink_drvDelete(pObj);

        /* ACK message if not previously ACK'ed */
        if ((ackMsg != (Bool)FALSE) && (pMsg != NULL))
        {
            Utils_tskAckOrFreeMsg(pMsg, status);
        }
        /* entering IDLE state */
    }
    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for capture link. BIOS task for capture
 *  link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    TfdtpRxLink_Obj *pObj;

    /* register link with system API */

    pObj = &gTfdtpRxLink_obj;

    memset(pObj, 0, sizeof(*pObj));

    pObj->tskId = SYSTEM_LINK_ID_TFDTP_RX;

    linkObj.pTsk                = &pObj->tsk;
    linkObj.linkGetFullBuffers  = &TfdtpRxLink_getFullBuffers;
    linkObj.linkPutEmptyBuffers = &TfdtpRxLink_putEmptyBuffers;
    linkObj.getLinkInfo         = &TfdtpRxLink_getInfo;

    System_registerLink(pObj->tskId, &linkObj);

    /* Create link task, task remains in IDLE state
     * TfdtpSrcLink_tskMain is called when a message command is received
     */

    status = Utils_tskCreate(&pObj->tsk,
            TfdtpSrcLink_tskMain,
            TFDTP_RX_LINK_TSK_PRI,
            gTfdtpRxLink_tskStack,
            TFDTP_RX_LINK_TSK_STACK_SIZE, pObj, "TFDTPRX ",
            UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for TfdtpRx link. BIOS task for TfdtpRx
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 TfdtpRxLink_deInit(void)
{
    TfdtpRxLink_Obj *pObj;

    pObj = &gTfdtpRxLink_obj;

    /*
     * Delete link task */
    Utils_tskDelete(&pObj->tsk);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get the buffer and queue information about link.
 *
 * \param  ptr  [IN] Task Handle
 * \param  info [IN] Pointer to link information handle

 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 TfdtpRxLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    TfdtpRxLink_Obj *pObj = (TfdtpRxLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * TFDTPRx link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from TFDTPRx
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
Int32 TfdtpRxLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    TfdtpRxLink_Obj *pObj = (TfdtpRxLink_Obj *) pTsk->appData;
    Int32 status;

    UTILS_assert(queId < TFDTP_RX_LINK_MAX_OUT_QUE);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    /* TfdtpRxLink_Obj uses a single queue. queId is still passed as
     * this function is common to all the links. Here we just ignore
     * the queId */
    status =  Utils_bufGetFull(&pObj->bufQue, pBufList, BSP_OSAL_NO_WAIT);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 *
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 TfdtpRxLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    TfdtpRxLink_Obj *pObj = (TfdtpRxLink_Obj *) pTsk->appData;

    UTILS_assert(queId < TFDTP_RX_LINK_MAX_OUT_QUE);

    return TfdtpRxLink_drvPutEmptyBuffers(pObj, pBufList);
}
