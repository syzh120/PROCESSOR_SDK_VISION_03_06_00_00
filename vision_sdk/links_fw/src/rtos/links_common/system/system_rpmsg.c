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
 * \file system_rpmsg.c
 *
 * \brief  This file implements System_rpmsg module used by System_rpmsgNotify
 *         and System_rpmsgMessageQ for IPC. This is done to move system from
 *         from multiendpt to single endpt per remote core.
 *
 *         RPMessage is used for notify between A15 and IPU/DSP
 *         when A15_TARGET_OS is Linux
 *
 * \version 0.0 (Mar 2015) : [YM] First version implemented
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/rtos/links_common/system/system_priv_ipc.h>
#include <ti/ipc/MultiProc.h>

#define RPMSG_NS_2_0

#include <ti/ipc/rpmsg/NameMap.h>
#include <ti/ipc/rpmsg/RPMessage.h>
#include <ti/ipc/remoteproc/Resource.h>
#include <ti/ipc/ipcmgr/IpcMgr.h>

#define RPMSG_LATE_ATTACH_A15_VDEV_ID 7
#define RPMSG_LATE_ATTACH_TSK_PRI 9

#pragma DATA_ALIGN(gIpcHlosConnect_tskStack, 32)
#pragma DATA_SECTION(gIpcHlosConnect_tskStack, ".bss:taskStackSection")
UInt8 gIpcHlosConnect_tskStack[16384];
Void System_ipcConnectToHLOSThread(Void);

typedef struct {
    RPMessage_Handle rpmsgHandle;
    /**< Handle for IPC notify */
    UInt32 localEndpoint;
    /**< RPMessage end point */
} System_RpMsg_Obj;

System_RpMsg_Obj gSystem_rpmsgObj;

/**
 *******************************************************************************
 *
 * \brief System wide notify handler function.
 *
 *        This function gets registered via System_ipcRegisterNotifyCb.
 *        Based on
 *        payload linkId is derived. From linkID callback of the specific
 *        link gets invoked.
 *
 * \param   handle      [IN] RP Message handle
 * \param   arg         [IN] not used
 * \param   payload     [IN] 4-byte notify payload. From this procId and
 *                           linkId is derived to invoke link specific
 *                           callback function
 * \param   len         [IN] length of payload
 * \param   src         [IN] source of the notify
 *
 *******************************************************************************
 */

static Void System_rpmsgCbHandler(RPMessage_Handle handle,
                                  UArg arg,
                                  Ptr payload,
                                  UInt16 len,
                                  UInt32 src)
{
    UInt32 payloadValue;

    payloadValue = *(volatile UInt32 *)payload;

    #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
    if(SYSTEM_LINK_ID_TEST_ROUTE_BIT_TRUE(payloadValue))
    {
        SYSTEM_LINK_ID_CLEAR_ROUTE_BIT(payloadValue);
        System_ipcNotifySendEvent(payloadValue);
        return;
    }
    #endif

    System_ipcHandler(payloadValue);
}

/**
 *******************************************************************************
 *
 * \brief Remote-cores trying to connect with the A15 (running Linux) are 
 *        managed on a sepearte thread 
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_rpmsgInit(void)
{
   /*
    */
    BspOsal_taskCreate((BspOsal_TaskFuncPtr)System_ipcConnectToHLOSThread,
            "Connect to HLOS task",
            RPMSG_LATE_ATTACH_TSK_PRI,
            gIpcHlosConnect_tskStack,
            sizeof(gIpcHlosConnect_tskStack),
            NULL,
            UTILS_TSK_AFFINITY_CORE0);

    return SYSTEM_LINK_STATUS_SOK;
}

/*
 This function gets the VdevStatus of the A15 core. If the returned VDEVStatus
 matches the condition then the A15 has successfully late-attached with the
 remote-core, and can proceed with rpMsgInit and create RPMessage instance and
 announce rpmsg service. 
 It registers a callback function to receive commands from A15.
 */

Void System_ipcConnectToHLOSThread(void)
{
    UInt32 retryCnt=0;
    UInt32 retval;
    
    Vps_printf("RpmsgInit in progress...\n");

    while(1)
    {
       retval = Resource_getVdevStatus(RPMSG_LATE_ATTACH_A15_VDEV_ID);
       if(retval != RPMSG_LATE_ATTACH_A15_VDEV_ID)
       {
           BspOsal_sleep(10);
           retryCnt++;
       }
       else
       {
           Vps_printf("Connection established with HLOS, calling rpmsgInit\n");
           break;
       }
    }
    
    IpcMgr_rpmsgStartup();
    memset(&gSystem_rpmsgObj, 0, sizeof(gSystem_rpmsgObj));

    /* Create the messageQ for receiving, and register callback: */
    gSystem_rpmsgObj.rpmsgHandle =
            RPMessage_create(
                    SYSTEM_RPMSG_ENDPT_REMOTE,
                    System_rpmsgCbHandler,
                    NULL,
                    &gSystem_rpmsgObj.localEndpoint
                    );
    UTILS_assert(gSystem_rpmsgObj.rpmsgHandle!=NULL);

    /* Announce we are here: */
    NameMap_register(
            "rpmsg-proto",
            "rpmsg-proto",
            SYSTEM_RPMSG_ENDPT_REMOTE
            );
}

Int32 System_rpmsgDeInit(void)
{
    NameMap_unregister(
            "rpmsg-proto",
            "rpmsg-proto",
            SYSTEM_RPMSG_ENDPT_REMOTE);

    RPMessage_delete(&gSystem_rpmsgObj.rpmsgHandle);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Utility function to invoke the notify to remote processor.
 *
 *        This function generates the notify event. It takes linkId as input
 *        maps linkId with procId and generates notify event on that processor
 *
 * \param   linkId      [IN] Link Id to which notify needs to be generated.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_rpmsgSendNotify(UInt32 linkId)
{
    UInt32 procId = SYSTEM_GET_PROC_ID(linkId);
    Int32 status;

    UTILS_assert(procId < SYSTEM_PROC_MAX);

    /* RPMessage exists only for communication with A15 (running Linux)*/
    UTILS_assert(procId == SYSTEM_PROC_A15_0);

#ifdef SYSTEM_IPC_MSGQ_DEBUG
    Vps_printf(" SYSTEM: NOTIFY: Sending Notify to [%s] !!!\n", System_getProcName(procId));
#endif

    /* Payload in the message is a linkId */
    status = RPMessage_send(System_getSyslinkProcId(SYSTEM_PROC_A15_0),
                            SYSTEM_RPMSG_NOTIFY_ENDPT_HOST,
                            gSystem_rpmsgObj.localEndpoint,
                            (Ptr) &linkId,
                            sizeof(UInt32));

    if (status != RPMessage_S_SUCCESS)
    {
        Vps_printf
            (" SYSTEM: RPMSG: Send to A15 failed !!! (status = %d)\n", status);

        UTILS_assert(status == RPMessage_S_SUCCESS);
    }

    return status;
}

