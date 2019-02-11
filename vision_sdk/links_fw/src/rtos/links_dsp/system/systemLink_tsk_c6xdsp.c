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
 * \file systemLink_tsk_c6xdsp.c
 *
 * \brief  This file has the implementataion of systemlink task and
 *         handles the commands received.
 *
 * \version 0.0 (Jun 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "systemLink_priv_c6xdsp.h"

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gSystemLink_tskStack, 32)
#pragma DATA_SECTION(gSystemLink_tskStack, ".bss:taskStackSection")
UInt8 gSystemLink_tskStack[SYSTEM_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link Object holds the task id and handle
 *******************************************************************************
 */
SystemLink_Obj gSystemLink_obj;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static Int32 SystemLink_cmdHandler(SystemLink_Obj * pObj, UInt32 cmd, Void * pPrm);

Void SystemLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);


/**
 *******************************************************************************
 *
 * \brief Handles the Commands received.
 *        Handles the commands for Profiling and core stats
 *
 * \param   pObj           [IN] SystemLink_Obj
 *
 * \param   cmd            [IN] input command
 *
 * \param   pPrm           [IN] input message
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
static Int32 SystemLink_cmdHandler(SystemLink_Obj * pObj, UInt32 cmd, Void * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    switch (cmd)
    {
        case SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START:
            Utils_prfLoadCalcStart();
            break;

        case SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP:
            Utils_prfLoadCalcStop();
            break;

        case SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET:
            Utils_prfLoadCalcReset();
            break;

        case SYSTEM_COMMON_CMD_PRINT_STATUS:
        {
            SystemCommon_PrintStatus *prm = (SystemCommon_PrintStatus *) pPrm;

            if (prm->printCpuLoad)
            {
                status = Utils_prfLoadPrintAll(prm->printTskLoad);
            }
            if (prm->printHeapStatus)
            {
                System_memPrintHeapStatus();
            }
        }
            break;

        case SYSTEM_COMMON_CMD_CORE_STATUS:
            Vps_printf(" Core is active\n");
            break;

        case SYSTEM_COMMON_CMD_GET_LOAD:
            Utils_prfGetLoad(pPrm);
            break;

        case SYSTEM_COMMON_CMD_RUN_DMA_TEST:
            Utils_dmaTestCopyFill(FALSE);
            break;

        case SYSTEM_COMMON_CMD_RUN_TIMER_TEST:
            Utils_TestTimer((Int32 *)pPrm);
            break;
        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Creates Command handler task
 *        handles the commands for Profiling and core stats
 *
 * \param   pTsk    [IN]  Utils_TskHndl
 *
 * \param   pMsg    [IN]  Utils_MsgHndl
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

Void SystemLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    Int32 status;
    SystemLink_Obj *pObj = (SystemLink_Obj *) pTsk->appData;

    status = SystemLink_cmdHandler(pObj,
                                   Utils_msgGetCmd(pMsg),
                                   Utils_msgGetPrm(pMsg));

    SystemLink_userCmdHandler(Utils_msgGetCmd(pMsg),
                            Utils_msgGetPrm(pMsg));

    Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *******************************************************************************
 *
 * \brief Initialize the ipu systemLink
 *        Initializes the linkObj and creates the task for SystemLink_tskMain
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SystemLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    SystemLink_Obj *pObj;
    UInt32 coreId;

    pObj = &gSystemLink_obj;

    memset(pObj, 0, sizeof(*pObj));
    coreId = System_getSelfProcId();
    pObj->tskId = SYSTEM_MAKE_LINK_ID(coreId, SYSTEM_LINK_ID_PROCK_LINK_ID);

    memset(&linkObj, 0, sizeof(linkObj));
    linkObj.pTsk = &pObj->tsk;
    linkObj.linkGetFullBuffers = NULL;
    linkObj.linkPutEmptyBuffers = NULL;
    linkObj.getLinkInfo = NULL;

    System_registerLink(pObj->tskId, &linkObj);

    snprintf(pObj->name, 32U, "SYSTEM_DSP_%u", pObj->tskId);

    status = Utils_tskCreate(&pObj->tsk,
                             SystemLink_tskMain,
                             SYSTEM_TSK_PRI,
                             gSystemLink_tskStack,
                             SYSTEM_TSK_STACK_SIZE, pObj, pObj->name,
                             UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Initialize the ipu systemLink
 *        Delete the SystemLink_tskMain created
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SystemLink_deInit(void)
{

    Utils_tskDelete(&gSystemLink_obj.tsk);

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
