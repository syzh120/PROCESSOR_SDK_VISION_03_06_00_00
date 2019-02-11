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
 * \file issM2mIspLink_tsk.c
 *
 * \brief  This file has the implementation of Iss M2m Isp Link API
 *
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 *           The state machine table is as shown below
 *
 *   Cmds   | CREATE | START | NEW_DATA | STOP   | DELETE |
 *   States |========|=======|==========|========|========|========|
 *   IDLE   | READY  | -     | -        | -      | -      | -      |
 *   READY  | -      | READY | RUN      | -      | READY  | IDLE   |
 *   RUN    | -      | -     | -        | RUN    | READY  | IDLE   |
 *
 *
 * \version 0.0 (Jul 2014) : [PS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "issM2mIspLink_priv.h"

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gIssM2mIspLink_tskStack, 32)
#pragma DATA_SECTION(gIssM2mIspLink_tskStack, ".bss:taskStackSection")
UInt8 gIssM2mIspLink_tskStack[ISSM2MISP_LINK_OBJ_MAX][ISSM2MISP_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
/* link object, stores all link related information */
IssM2mIspLink_Obj gIssM2mIspLink_obj[ISSM2MISP_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Run state of link.
 *
 * In this state link waits for command from application or next link.
 * Basically all are control commands except the new_data command where
 * link gets input data from previous link to be processed. After
 * that it sends command to next link.
 *
 * \param  pObj     [IN] Link object
 * \param  pTsk     [IN] Link Task handle
 * \param  pMsg     [IN] Message for the link. Contains command and args.
 * \param  done     [IN] Flag to exit idle state.
 * \param  ackMsg   [IN] Flag to decide whether to send ack message or not to
 *                       caller
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_tskRun(IssM2mIspLink_Obj * pObj, Utils_TskHndl * pTsk,
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
    runDone = (Bool)FALSE;
    runAckMsg = (Bool)FALSE;

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
                /* new data frames have been captured, process them */

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                status = IssM2mIspLink_drvProcessData(pObj);

                /* INVARIANT_CONDITION.UNREACH
                * MISRAC_2004_Rule_13.7
                * MISRAC_WAIVER:
                * Code is currently unreachable.
                * This is kept to ensure future updates by the called function.
                */
                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    /* in case of error exit RUN loop */
                    runDone = (Bool)TRUE;

                    /* since message is already ACK'ed or free'ed do not ACK
                     * or free it again */
                    runAckMsg = (Bool)FALSE;
                }
                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                /* new data frames have been captured, process them */

                IssM2mIspLink_drvPrintStatus(pObj);

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_STOP:
                /* stop RUN loop and goto READY state */
                runDone = (Bool)TRUE;

                /* ACK message after actually stopping the driver outside the
                 * RUN loop */
                runAckMsg = (Bool)TRUE;
                break;

            case SYSTEM_CMD_DELETE:

                /* stop RUN loop and goto IDLE state */

                /* exit RUN loop */
                runDone = (Bool)TRUE;

                /* exit READY loop */
                *done = (Bool)TRUE;

                /* ACK message after exiting READY loop */
                *ackMsg = (Bool)TRUE;

                /* Pass the received message to the READY loop */
                *pMsg = pRunMsg;

                break;

            case ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS:
            {
                Void *pParams;
                /* New AWB data has arrived, update the ISP params based
                   on AEWB output */

                pParams = (Void *) Utils_msgGetPrm(pRunMsg);
                IssM2mIspLink_drvUpdateAwbResults(pObj, pParams);

                /* ACK or free message
                   Freeing after updating parameters so
                   that no new_data come while updating parameters.
                   NEW_DATA and this ioctl are both part of the same task,
                   so anyway, only one of them will be running at a time. */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                break;
            }

            case ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS:
            {
                Void *pParams;
                /* New AWB data has arrived, update the ISP params based
                   on AEWB output */

                pParams = (Void *) Utils_msgGetPrm(pRunMsg);
                IssM2mIspLink_drvUpdateWdrMergeParams(pObj, pParams);

                /* ACK or free message
                   Freeing after updating parameters so
                   that no new_data come while updating parameters.
                   NEW_DATA and this ioctl are both part of the same task,
                   so anyway, only one of them will be running at a time. */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                break;
            }

            case ISSM2MISP_LINK_CMD_SET_ISPCONFIG:
            {
                IssIspConfigurationParameters *pParams;

                pParams = (IssIspConfigurationParameters *) Utils_msgGetPrm(pRunMsg);
                status = IssM2mIspLink_drvSetIspConfig(pObj, pParams, 0);

                /* If set params, display status and remain in same state */
                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    Vps_printf("ISS M2M Isp Link: Setting IspConfig failed");
                }

                Utils_tskAckOrFreeMsg(pRunMsg, status);

                break;
            }

            case ISSM2MISP_LINK_CMD_SAVE_FRAME:
            {
                UInt32 chId;

                chId = *(UInt32 *)Utils_msgGetPrm(pRunMsg);
                IssM2mIspLink_drvSaveFrame(pObj, chId);

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                break;
            }

            case ISSM2MISP_LINK_CMD_GET_SAVE_FRAME_STATUS:

                status = IssM2mIspLink_drvGetSaveFrameStatus(pObj,
                            Utils_msgGetPrm(pRunMsg));

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case ISSM2MISP_LINK_CMD_SET_TAP_PARAMS:
            {
#ifdef ISS_ENABLE_DEBUG_TAPS
                status = IssM2mIspLink_updateTapParams(
                    pObj, Utils_msgGetPrm(pRunMsg));
#endif
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                break;
            }
            case ISSM2MISP_LINK_CMD_SET_ISP_ROUTE_CFG:

                status = IssM2mIspLink_drvSetIspRouteCfg(pObj,
                            (IssM2mIspLink_RouteCfg*)Utils_msgGetPrm(pRunMsg));

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            default:

                /* invalid command for this state ACK it and continue RUN
                 * loop */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop driver */

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
Void IssM2mIspLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status;
    IssM2mIspLink_Obj *pObj;

    /* IDLE state */

    pObj = (IssM2mIspLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
         * with error status */
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
    }
    else
    {

               /* Create command received, create the driver */
               status = IssM2mIspLink_drvCreate(pObj, (const IssM2mIspLink_CreateParams * )Utils_msgGetPrm(pMsg));

               /* ACK based on create status */
               Utils_tskAckOrFreeMsg(pMsg, status);

               /* if create status is error then remain in IDLE state */
               if (status == (Int32)SYSTEM_LINK_STATUS_SOK)
               {

                          /* create success, entering READY state */

                             done = (Bool)FALSE;
                             ackMsg = (Bool)FALSE;

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

                                      /* ACK based on create status */
                                      Utils_tskAckOrFreeMsg(pMsg, status);

                                      /* if start status is error then remain in READY state */
                                      if (status == SYSTEM_LINK_STATUS_SOK)
                                      {
                                          /* start success, entering RUN state */
                                          status =
                                              IssM2mIspLink_tskRun(pObj, pTsk, &pMsg, &done, &ackMsg);

                                          /** done = FALSE, exit RUN state
                                            done = TRUE, exit RUN and READY state
                                           */
                                      }

                                      break;

                                  case (UInt32) ISSM2MISP_LINK_CMD_SET_ISPCONFIG:
                                  {
                                      IssIspConfigurationParameters *pParams;

                                      pParams = (IssIspConfigurationParameters *) Utils_msgGetPrm(pMsg);
                                      status = IssM2mIspLink_drvSetIspConfig(pObj, pParams, 0);

                                      /* If set params, display status and remain in same state */
                                      if (status != SYSTEM_LINK_STATUS_SOK)
                                      {
                                          Vps_printf("ISS M2M Isp Link: Setting IspConfig failed");
                                      }

                                      Utils_tskAckOrFreeMsg(pMsg, status);

                                      break;
                                  }
                                  case ISSM2MISP_LINK_CMD_SET_ISP_ROUTE_CFG:

                                      status = IssM2mIspLink_drvSetIspRouteCfg(pObj,
                                                    (IssM2mIspLink_RouteCfg*)Utils_msgGetPrm(pMsg));

                                      /* ACK or free message before proceding */
                                      Utils_tskAckOrFreeMsg(pMsg, status);
                                      break;

                                  case ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS:
                                  {
                                      Void *pParams;
                                      /* New AWB data has arrived, update the ISP params based
                                         on AEWB output */

                                      pParams = (Void *) Utils_msgGetPrm(pMsg);
                                      IssM2mIspLink_drvUpdateAwbResults(pObj, pParams);

                                      /* ACK or free message
                                         Freeing after updating parameters so
                                         that no new_data come while updating parameters.
                                         NEW_DATA and this ioctl are both part of the same task,
                                         so anyway, only one of them will be running at a time. */
                                      Utils_tskAckOrFreeMsg(pMsg, status);

                                      break;
                                  }

                                  case ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS:
                                  {
                                      Void *pParams;
                                      /* New AWB data has arrived, update the ISP params based
                                         on AEWB output */

                                      pParams = (Void *) Utils_msgGetPrm(pMsg);
                                      IssM2mIspLink_drvUpdateWdrMergeParams(pObj, pParams);

                                      /* ACK or free message
                                         Freeing after updating parameters so
                                         that no new_data come while updating parameters.
                                         NEW_DATA and this ioctl are both part of the same task,
                                         so anyway, only one of them will be running at a time. */
                                      Utils_tskAckOrFreeMsg(pMsg, status);

                                      break;
                                  }
                                  case (UInt32) SYSTEM_CMD_DELETE:

                                      /* exit READY state */
                                      done = (Bool)TRUE;
                                      ackMsg = (Bool)TRUE;
                                      break;
                                  default:
                                      /* invalid command for this state ACK it and continue READY
                                       * loop */
                                      Vps_printf("ISS M2M Isp Link: Unsupported link command");
                                      Utils_tskAckOrFreeMsg(pMsg, status);
                                      break;
                              }
                          }

                          /* exiting READY state, delete driver */
                          IssM2mIspLink_drvDelete(pObj);

                          /* ACK message if not previously ACK'ed */

                          if ((ackMsg != (Bool)FALSE) && (pMsg != NULL))
                          {
                                   Utils_tskAckOrFreeMsg(pMsg, status);
                          }
                 }
    }

    /* entering IDLE state */
    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for link. BIOS task for the
 *  link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_init(void)
{
    Int32 status;
    UInt32 instId;

    System_LinkObj linkObj;
    IssM2mIspLink_Obj *pObj;

    /* register link with system API */
    for(instId = 0U; instId < ISSM2MISP_LINK_OBJ_MAX; instId++ )
    {
        pObj = &gIssM2mIspLink_obj[instId];

        memset(pObj, 0, sizeof*pObj);

        pObj->linkId = SYSTEM_LINK_ID_ISSM2MISP_0 + instId;

        linkObj.pTsk                = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &IssM2mIspLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &IssM2mIspLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &IssM2mIspLink_getInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /* Create link task, task remains in IDLE state
         * IssM2mIspLink_tskMain is called when a message command is received
         */

        status = Utils_tskCreate(&pObj->tsk,
            IssM2mIspLink_tskMain,
            ISSM2MISP_LINK_TSK_PRI,
            &gIssM2mIspLink_tskStack[instId][0],
            ISSM2MISP_LINK_TSK_STACK_SIZE, pObj, "ISSM2MISP ",
            UTILS_TSK_AFFINITY_CORE0);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for capture link. BIOS task for capture
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 IssM2mIspLink_deInit(void)
{
    IssM2mIspLink_Obj *pObj;
    UInt32 instId;

    for(instId = 0U; instId < ISSM2MISP_LINK_OBJ_MAX; instId ++)
    {
        pObj = &gIssM2mIspLink_obj[instId];

        /*
         * Delete link task
         */
        Utils_tskDelete(&pObj->tsk);
    }

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
Int32 IssM2mIspLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    IssM2mIspLink_Obj *pObj = (IssM2mIspLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * Link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from this link
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
Int32 IssM2mIspLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    IssM2mIspLink_Obj *pObj = (IssM2mIspLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 idx = 0;

    UTILS_assert(queId < ISSM2MISP_LINK_OUTPUTQUE_MAXNUM);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    /* IssM2mIspLink_Obj uses two queues. Hence queId is used here */
    if ((UInt32)TRUE != Utils_queIsEmpty(&pObj->linkOutObj[queId].
            fullBufQue))
    {
        for (idx = 0U; idx < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST; idx++)
        {
            /* MISRA.CAST.PTR:MISRAC_2004 Rule_11.4
            MISRAC_WAIVER:
            Generic implementation of queue expects data in Ptr* type,
            so typecasted it to Ptr *. */
            status = Utils_queGet(&pObj->linkOutObj[queId].fullBufQue,
                                (Ptr *) & pBufList->buffers[idx],
                                (UInt32)1U,
                                (UInt32)BSP_OSAL_NO_WAIT);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS;
    }

    pBufList->numBuf = idx;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
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
Int32 IssM2mIspLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList)
{
    Int32 status;
    UInt32 idx;
    UInt32 chNum;

    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    IssM2mIspLink_Obj *pObj = (IssM2mIspLink_Obj *) pTsk->appData;

    UTILS_assert(queId < ISSM2MISP_LINK_OUTPUTQUE_MAXNUM);

    /* IssM2mIspLink_Obj uses multiple output queues. Also since this link
     * supports multi channel processing, each channel has its own empty
     * buffer queue. Hence Que id and channel number is used while
     * putting a buffer into empty queue.
     */
    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        chNum  = pBufList->buffers[idx]->chNum;
        status = Utils_quePut(&pObj->linkOutObj[queId].emptyBufQue[chNum],
                               (Ptr)pBufList->buffers[idx],
                               (UInt32)BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}
