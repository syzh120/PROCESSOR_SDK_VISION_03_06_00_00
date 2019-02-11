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
  ******************************************************************************
 * \file ultrasonicCaptureLink_tsk.c
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ultrasonicCaptureLink_priv.h"
#include <ti/drv/vps/include/boards/bsp_board.h>

#define ULTRASONIC_CAPTURE_LINK_TSK_STACK_SIZE  (16*KB)
#define ULTRASONIC_CAPTURE_LINK_TSK_PRI         (10)

/* polling interval in units of msecs */
#define ULTRASONIC_CAPTURE_POLLING_INTERVAL     (1)

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gUltrasonicCaptureLink_tskStack, 32)
#pragma DATA_SECTION(gUltrasonicCaptureLink_tskStack, ".bss:taskStackSection")
UInt8 gUltrasonicCaptureLink_tskStack[ULTRASONIC_CAPTURE_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
UltrasonicCaptureLink_Obj gUltrasonicCaptureLink_obj;

/**
 *******************************************************************************
 * \brief Function called by links connected to ULTRASONIC_CAPTURE link to get data from
 *    the output queue of ULTRASONIC_CAPTURE link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [OUT] A List of buffers needed for the next link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_getFullBuffers(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList)
{
    Int32 status;
    UltrasonicCaptureLink_Obj *pObj;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    pObj = (UltrasonicCaptureLink_Obj *) pTsk->appData;

    status = Utils_bufGetFull(&pObj->outFrameQue, pBufList,
                              BSP_OSAL_NO_WAIT);

    return status;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to ULTRASONIC_CAPTURE link to get output queue
 *    Information of ULTRASONIC_CAPTURE link
 *
 * \param  ptr      [IN]  Handle to task
 * \param  info     [OUT] output queues information of ULTRASONIC_CAPTURE link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_getLinkInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    UltrasonicCaptureLink_Obj *pObj = (UltrasonicCaptureLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->info, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Function called by links connected to ULTRASONIC_CAPTURE link to return back
 *    buffers
 *
 * \param  ptr      [IN]  Handle to task
 * \param  queId    [IN]  output queue Id
 * \param  pBufList [IN]  A List of buffers returned back to ULTRASONIC_CAPTURE link
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList)
{
    Int32 status;
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;
    UltrasonicCaptureLink_Obj *pObj = (UltrasonicCaptureLink_Obj *) pTsk->appData;

    status = Utils_bufPutEmpty(&pObj->outFrameQue, pBufList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Create task for this link
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_tskCreate(int usm_id)
{
    Int32                status;
    UltrasonicCaptureLink_Obj        *pObj;
    char                 tskName[32];

    pObj = &gUltrasonicCaptureLink_obj;

    sprintf(tskName, "ULTRASONIC_CAPTURE");

    /*
     * Create link task, task remains in IDLE state.
     * UltrasonicCaptureLink_tskMain is called when a message command is received.
     */
    switch (usm_id)
    {
        case USM_ID_PGA460:
            status = Utils_tskCreate(&pObj->tsk,
                             UltrasonicCaptureLink_PGA460_tskMain,
                             ULTRASONIC_CAPTURE_LINK_TSK_PRI,
                             gUltrasonicCaptureLink_tskStack,
                             ULTRASONIC_CAPTURE_LINK_TSK_STACK_SIZE,
                             pObj,
                             tskName,
                             UTILS_TSK_AFFINITY_CORE0);
            break;
        case USM_ID_PGA450:
        default:
            status = Utils_tskCreate(&pObj->tsk,
                             UltrasonicCaptureLink_PGA450_tskMain,
                             ULTRASONIC_CAPTURE_LINK_TSK_PRI,
                             gUltrasonicCaptureLink_tskStack,
                             ULTRASONIC_CAPTURE_LINK_TSK_STACK_SIZE,
                             pObj,
                             tskName,
                             UTILS_TSK_AFFINITY_CORE0);
            break;
    }


    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Init function for ULTRASONIC_CAPTURE link. This function does the following for each
 *   ULTRASONIC_CAPTURE link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 UltrasonicCaptureLink_init(int usm_id)
{
    Int32 status;
    System_LinkObj linkObj;
    UltrasonicCaptureLink_Obj *pObj;
    Bsp_Pga460InitParams    pga460InitParams;
    Bsp_Pga450InitParams    pga450InitParams;


    UInt32 procId = System_getSelfProcId();
    if(!Bsp_platformIsTda2xxFamilyBuild())
        return 0;

    pObj = &gUltrasonicCaptureLink_obj;

    memset(pObj, 0, sizeof(*pObj));

    pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                      SYSTEM_LINK_ID_ULTRASONIC_CAPTURE);

    linkObj.pTsk = &pObj->tsk;
    linkObj.linkGetFullBuffers = UltrasonicCaptureLink_getFullBuffers;
    linkObj.linkPutEmptyBuffers = UltrasonicCaptureLink_putEmptyBuffers;
    linkObj.getLinkInfo = UltrasonicCaptureLink_getLinkInfo;

    System_registerLink(pObj->tskId, &linkObj);

    switch (usm_id)
    {
        case USM_ID_PGA460:
            BspPga460InitParams_init(&pga460InitParams);
            pga460InitParams.uartInstId[0U] = BSP_DEVICE_UART_INST_ID_2;
            status = Bsp_pga460Init(&pga460InitParams);
            break;
        case USM_ID_PGA450:
        default:
            /* Setup pinmux and power on UART */
            UltrasonicCaptureLink_hwSetup();
            BspPga450InitParams_init(&pga450InitParams);
            status = Bsp_pga450Init(&pga450InitParams);
            break;
    }

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);



    status = UltrasonicCaptureLink_tskCreate(usm_id);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for ULTRASONIC_CAPTURE link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 UltrasonicCaptureLink_deInit(int usm_id)
{
    if(!Bsp_platformIsTda2xxFamilyBuild())
        return 0;

    Utils_tskDelete(&gUltrasonicCaptureLink_obj.tsk);

    switch (usm_id)
    {
        case USM_ID_PGA460:
            Bsp_pga460DeInit();
            break;
        case USM_ID_PGA450:
        default:
            Bsp_pga450DeInit();
            break;
    }


    return SYSTEM_LINK_STATUS_SOK;
}

