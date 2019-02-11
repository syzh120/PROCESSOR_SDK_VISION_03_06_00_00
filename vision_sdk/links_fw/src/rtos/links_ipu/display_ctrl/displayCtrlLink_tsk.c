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
 * \file displayCtrlLink_tsk.c
 *
 * \brief  This file has the implementataion of Display Control Link API
 *
 *         This file implements the state machine logic for this link.
 *         A message command will cause the state machine to take some
 *         action and then move to a different state.
 *         Display controller follows a simple two state machine
 *
 *            Cmds| CREATE | ALL OTHER COMMANDS | DELETE |
 *         States |========|====================|========|
 *           IDLE | RUN    | -                  | -      |
 *           RUN  | -      | RUN                | IDLE   |
 *
 *
 * \version 0.0 (Jun 2013) : [PS] First version
 * \version 0.1 (Jul 2013) : [PS] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "displayCtrlLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
Void DisplayCtrlLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gDisplayCtrlLink_tskStack, 32)
#pragma DATA_SECTION(gDisplayCtrlLink_tskStack, ".bss:taskStackSection")
UInt8 gDisplayCtrlLink_tskStack[DISPLAYCTRL_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
DisplayCtrlLink_Obj gDisplayCtrlLink_obj;


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
 /*
* MISRA.PPARAM.NEEDS.CONS
* MISRAC_2004_Rule_16.7
* Function parameter is not declared as a pointer to const.
* In Other Links it calls Utils_tskRecvMsg where the memory
* pointed by pTsk will be updated .So ptask cannot be made const
* KW State: Defer -> Waiver -> Case by case
*/
Void DisplayCtrlLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32               cmd = Utils_msgGetCmd(pMsg);
    Int32                status = 0;
    DisplayCtrlLink_Obj *pObj;

    pObj = (DisplayCtrlLink_Obj *) pTsk->appData;

    switch (cmd)
    {
        case SYSTEM_CMD_CREATE:
            if(SYSTEM_LINK_STATE_IDLE == pObj->state)
            {
                status = DisplayCtrlLink_drvCreate(pObj);
                if(SYSTEM_LINK_STATUS_SOK == status)
                {
                    pObj->state = SYSTEM_LINK_STATE_RUNNING;
                }
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case DISPLAYCTRL_LINK_CMD_SET_CONFIG:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvSetConfig(
                             pObj,
                             Utils_msgGetPrm(pMsg));
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case DISPLAYCTRL_LINK_CMD_SET_OVLY_PARAMS:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvSetOvlyParams(
                             pObj,
                             Utils_msgGetPrm(pMsg));
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case DISPLAYCTRL_LINK_CMD_SET_OVLY_PIPELINE_PARAMS:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvSetOvlyPipelineParams(
                             pObj,
                             Utils_msgGetPrm(pMsg));
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case DISPLAYCTRL_LINK_CMD_CLR_CONFIG:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvClrConfig(
                             pObj,
                             Utils_msgGetPrm(pMsg));
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case DISPLAYCTRL_LINK_CMD_HDMI_FLIP_DATA_P_N_ORDER:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvHdmiFlipDataPNOrder(pObj);
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvPrintStatus(pObj);
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        /*
         * Start and stop are made as dummy for this link, since there is
         * no need.
         */
        case SYSTEM_CMD_START:
        case SYSTEM_CMD_STOP:

            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        /*
         * Exiting Ready state after deleting the driver
         */
        case SYSTEM_CMD_DELETE:
            if(SYSTEM_LINK_STATE_RUNNING == pObj->state)
            {
                status = DisplayCtrlLink_drvDelete(pObj);
                pObj->state = SYSTEM_LINK_STATE_IDLE;
            }
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;

        /*
         * Invalid command for this state.  ACK it and continue RUN
         */
        default:
            Utils_tskAckOrFreeMsg(pMsg, status);
            break;
    }

    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for display controller link. BIOS task for display
 *        controller link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 DisplayCtrlLink_init(void)
{
    Int32                status;
    System_LinkObj       linkObj;
    DisplayCtrlLink_Obj *pObj;

    pObj = &gDisplayCtrlLink_obj;

    memset(pObj, 0, sizeof(DisplayCtrlLink_Obj));

    pObj->state = SYSTEM_LINK_STATE_IDLE;

    linkObj.pTsk = &pObj->tsk;

    linkObj.linkGetFullBuffers  = NULL;
    linkObj.linkPutEmptyBuffers = NULL;
    linkObj.getLinkInfo         = NULL;

    System_registerLink(SYSTEM_LINK_ID_DISPLAYCTRL, &linkObj);

    /*
     * Create link task, task remains in IDLE state.
     * DisplayCtrlLink_tskMain is called when a message command is received.
     */
    status = Utils_tskCreate(&pObj->tsk,
                             DisplayCtrlLink_tskMain,
                             DISPLAYCTRL_LINK_TSK_PRI,
                             gDisplayCtrlLink_tskStack,
                             DISPLAYCTRL_LINK_TSK_STACK_SIZE,
                             pObj, "DISPLAYCTRL ", UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for display controller link. BIOS task for display
 *        controller link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DisplayCtrlLink_deInit(void)
{
    DisplayCtrlLink_Obj *pObj;

    pObj = &gDisplayCtrlLink_obj;

    Utils_tskDelete(&pObj->tsk);

    return SYSTEM_LINK_STATUS_SOK;
}
