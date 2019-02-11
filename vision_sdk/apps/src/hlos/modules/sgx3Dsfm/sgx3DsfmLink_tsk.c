/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 * \file sgx3DsfmLink_tsk.c
 *
 * \brief  This file has the implementation of Sgx3Dsfm Link Init and Run API
 *
 *         This file implements the state machine logic for this link.
 *         Sgx3DsfmLink_init() get calls from system_init and the same create
 *         the link task and basic messaging interfaces. Once the link is
 *         initiated it waits for the create cmd. This create cmd creates the
 *         complete link infrastructure.  Then waits for various data and
 *         control cmds.
 *
 *         This file also implements the sgx3Dsfm link tear down functionality
 *
 * \version 0.0 (Dec 2015) : [MM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sgx3DsfmLink_priv.h"

/**
 *******************************************************************************
 * \brief Sgx3Dsfm Link object, stores all link related information
 *******************************************************************************
 */
Sgx3DsfmLink_Obj gSgx3DsfmLink_obj[SGX3DSFM_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function implements the sgx3Dsfm link Run/Steady state
 *
 *        In this state link gets commands to
 *         - Stop/delete of link
 *         - Data events/cmds
 *         - All dynamic cmds that the link supports
 *         - All stats/status cmds
 *
 * \param  pObj     [IN]  Sgx3Dsfm link instance handle
 * \param  pTsk     [IN]  Link Task Handle
 * \param  pMsg     [IN]  Message Handle
 * \param  done     [IN]  sgx3Dsfm link Run state, set to TRUE once it get the
 *                        is DELETE CMD
 * \param  ackMsg   [OUT] ACK message
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_tskRun(Sgx3DsfmLink_Obj *pObj, OSA_TskHndl *pTsk,
                            OSA_MsgHndl **pMsg, Bool *done, Bool *ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone = FALSE, runAckMsg = FALSE;
    OSA_MsgHndl *pRunMsg;
    UInt32 cmd;

    *done = FALSE;
    *ackMsg = FALSE;

    runDone = FALSE;
    runAckMsg = FALSE;

    *pMsg = NULL;

    /*
     * This while loop implements RUN state. All the run time commands for
     * ackMsg Link are received and serviced in this while loop.
     * Control remains in this loop until delete commands arrives.
     */
    while (!runDone)
    {
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
            case SYSTEM_CMD_STOP:
                runDone = TRUE;
                runAckMsg = TRUE;
                break;

            case SYSTEM_CMD_NEW_DATA:
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                status = Sgx3DsfmLink_drvDoProcessFrames(pObj);
                break;

            case SYSTEM_CMD_DELETE:
                *done = TRUE;
                *ackMsg = TRUE;
                *pMsg = pRunMsg;
                runDone = TRUE;
                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                Sgx3DsfmLink_drvPrintStatistics(pObj);
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_COMMON_CMD_GET_SGX_LOAD: /* SGX Load */
                system_get_pvrscope_profile_data(&pObj->pvrscopeObj);
                {
                    Utils_SystemLoadStats *pStats =
                          (Utils_SystemLoadStats *) OSA_msgGetPrm(pRunMsg);
                    pStats->totalLoadParams.integerValue =
                          pObj->pvrscopeObj.loadStats.totalLoadParams.integerValue;
                    pStats->totalLoadParams.fractionalValue =
                          pObj->pvrscopeObj.loadStats.totalLoadParams.fractionalValue;
                }
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            default:
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }
    }

    Sgx3DsfmLink_drvStop(pObj);

    if (runAckMsg)
        OSA_tskAckOrFreeMsg(pRunMsg, status);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the START/RUN state of sgx3Dsfm Link.
 *
 *        In this state link gets commands to
 *         - Create the Sgx3Dsfm Driver
 *         - Start the Sgx3Dsfm Driver
 *         - Moves to RUN state
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_tskMain(struct OSA_TskHndl *pTsk,
                                    OSA_MsgHndl *pMsg, UInt32 curState)
{
    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status;
    Sgx3DsfmLink_Obj *pObj = (Sgx3DsfmLink_Obj *) pTsk->appData;

    /*
     * At this stage only create command is the expected command.
     * If other message gets received Ack with error status
     */
    if (cmd != SYSTEM_CMD_CREATE)
    {
        OSA_tskAckOrFreeMsg(pMsg, OSA_EFAIL);
        return OSA_EFAIL;
    }

    /*
     * Create command received, create the driver
     */
    status = Sgx3DsfmLink_drvCreate(pObj, OSA_msgGetPrm(pMsg));

    OSA_tskAckOrFreeMsg(pMsg, status);

    if (status != SYSTEM_LINK_STATUS_SOK)
        return OSA_EFAIL;

    done = FALSE;
    ackMsg = FALSE;

    while (!done)
    {
        status = OSA_tskWaitMsg(pTsk, &pMsg);
        if (status != SYSTEM_LINK_STATUS_SOK)
            break;

        cmd = OSA_msgGetCmd(pMsg);

        switch (cmd)
        {
            /*
             * CMD to prime and start the sgx3Dsfm driver. Link will be in
             * running state and ready to sgx3Dsfm the video/graphic frames
             * available at the input side
             */
            case SYSTEM_CMD_START:
                status = Sgx3DsfmLink_drvStart(pObj);

                OSA_tskAckOrFreeMsg(pMsg, status);

                /*
                 * Entering RUN state
                 */
                if (status == SYSTEM_LINK_STATUS_SOK)
                {
                    status =
                        Sgx3DsfmLink_tskRun(pObj, pTsk, &pMsg, &done, &ackMsg);
                }

                break;
            case SGXLINK_CMD_ACQUIRE_EGL_INFO:
                status = Sgx3DsfmLink_drvDoProcessEglInfo(pObj, OSA_msgGetPrm(pMsg));
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
            case SYSTEM_CMD_DELETE:
                done = TRUE;
                ackMsg = TRUE;
                break;

            default:
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    Sgx3DsfmLink_drvDelete(pObj);

    if (ackMsg && pMsg != NULL)
        OSA_tskAckOrFreeMsg(pMsg, status);

    return OSA_SOK;
}

/**
 *******************************************************************************
 *
 *   \brief Sgx3Dsfm link register and init function
 *
 *          For each sgx3Dsfm instance (VID1, VID2, VID3 or GRPX1)
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Sgx3DsfmLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 sgx3DsfmId;
    Sgx3DsfmLink_Obj *pObj;

    for (sgx3DsfmId = 0; sgx3DsfmId < SGX3DSFM_LINK_OBJ_MAX; sgx3DsfmId++)
    {
        pObj = &gSgx3DsfmLink_obj[sgx3DsfmId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId = SYSTEM_LINK_ID_SGX3DSFM_0 + sgx3DsfmId;

        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &Sgx3DsfmLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &Sgx3DsfmLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &Sgx3DsfmLink_getLinkInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * Sgx3DsfmLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "SGX3DSFM_%u", (unsigned int)sgx3DsfmId);
        status = OSA_tskCreate(&pObj->tsk,
                               Sgx3DsfmLink_tskMain,
                               OSA_THR_PRI_DEFAULT,
                               SGX3DSFM_LINK_TSK_STACK_SIZE,
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
 *   \brief Sgx3Dsfm link de-register and de-init function
 *
 *          For each sgx3Dsfm instance (VID1, VID2, VID3 or GRPX1)
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Sgx3DsfmLink_deInit(void)
{
    Sgx3DsfmLink_Obj *pObj;
    UInt32 sgx3DsfmId;

    for (sgx3DsfmId = 0; sgx3DsfmId < SGX3DSFM_LINK_OBJ_MAX; sgx3DsfmId++)
    {
        pObj = &gSgx3DsfmLink_obj[sgx3DsfmId];

        OSA_tskDelete(&pObj->tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
            gSgx3DsfmLink_obj[sgx3DsfmId].tskName, gSgx3DsfmLink_obj[sgx3DsfmId].linkId);
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
Int32 Sgx3DsfmLink_getLinkInfo(Void *pTsk,
                               System_LinkInfo *info)
{
    OSA_TskHndl * pTskHndl = (OSA_TskHndl *)pTsk;
    Sgx3DsfmLink_Obj * pObj = (Sgx3DsfmLink_Obj * )pTskHndl->appData;

    /* 'info' structure is set with valid values during 'create' phase
     * Simply pass on previous link info to next link
     */

    memcpy(info, &pObj->tskInfo, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Sgx3Dsfm link to get data from
 *    the output queue of the link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Sgx3DsfmLink_getFullBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList)
{
    System_Buffer *nextBuf;
    OSA_TskHndl * pTskHndl = (OSA_TskHndl *)ptr;
    Sgx3DsfmLink_Obj * pObj = (Sgx3DsfmLink_Obj * )pTskHndl->appData;
    UInt64 srcTimeStamp;

    pBufList->numBuf = 0;

    nextBuf = System_eglWindowGetNextBuffer(&(pObj->eglWindowObj), &srcTimeStamp);
    OSA_assert(nextBuf != NULL);
    nextBuf->srcTimestamp = srcTimeStamp;

    pBufList->buffers[pBufList->numBuf] = nextBuf;
    pBufList->numBuf++;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to Sgx3Dsfm link to put empty frames
 *    to the output queue of the link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Sgx3DsfmLink_putEmptyBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList)
{
    System_Buffer *nextBuf;
    OSA_TskHndl * pTskHndl = (OSA_TskHndl *)ptr;
    Sgx3DsfmLink_Obj * pObj = (Sgx3DsfmLink_Obj * )pTskHndl->appData;
    Int32 count;

    /*Add them to the empty list. ProcessBUffers will fill them up*/
    for (count = 0; count < pBufList->numBuf; count++) {
      nextBuf = pBufList->buffers[count];
      System_eglWindowPutBuffer(&(pObj->eglWindowObj), nextBuf);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
