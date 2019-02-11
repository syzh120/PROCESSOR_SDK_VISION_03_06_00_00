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
 *
 * \ingroup AUTOSAR_IPC_OUT_LINK_API
 * \defgroup AUTOSAR_IPC_OUT_LINK_IMPL AUTOSAR IPC Out Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file autosar_ipcOutLink_priv.h
 *
 * \brief AUTOSAR IPC OUT Link Private Header File
 *
 *        This file has the structures, enums, function prototypes
 *        for IPC OUT link, which are not exposed to the application
 *
 * \version 0.0 (August 2018) : [AKG] First version
 *
 *******************************************************************************
 */

#ifndef AUTOSAR_IPC_OUT_LINK_PRIV_H_
#define AUTOSAR_IPC_OUT_LINK_PRIV_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/links_common/system/system_priv_ipc.h>
#include <include/link_api/autosar_ipcLink.h>
#include <src/rtos/utils_common/include/utils_ipc_que.h>
#include <ti/drv/ipc_lite/ipclib_interrupt.h>

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Command to tell IPC Out link to look at its
 *                    IPC IN->IPC OUT shared memory queue for buffers to be
 *                    released to previous link
 *
 *   \param None
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define AUTOSAR_IPC_OUT_LINK_CMD_RELEASE_FRAMES     (0x5100U)

#define AUTOSAR_IPC_OUT_LINK_OBJ_MAX                (SYSTEM_AUTOSAR_IPC_OUT_LINK_MAX)

#define BUFFER_SIZE                                 (1024)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Autosar IPC Out Link Object
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 linkId;
    /**< Link ID of this Link Obj */

    char name[32];
    /**< Link name */

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    UInt32 linkInstId;
    /**< Instance index of this link */

    Utils_TskHndl tsk;
    /**< Link task handle */

    Utils_IpcQueHandle ipcV2AQue;
    /**< IPC OUT to IPC IN queue */

    Utils_IpcQueHandle ipcA2VQue;
    /**< IPC IN to IPC OUT queue */

    Ptr v2aSharedMemBaseAddr;
    /**< Base address of IPC queue area */

    Ptr a2vSharedMemBaseAddr;
    /**< Base address of IPC queue area */

    Utils_QueHandle localQue;
    /**< local queue handle */

    Ptr localQueMem[SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS];
    /**< Memory for local queue */

    System_AutosarMetaBuffer buffers[SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS];
    /**< Placeholder to store the incoming buffers */

     Utils_BufHndl outBufQue;
    /**< Handle to buffer queue */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by this link */

} AutosarIpcOutLink_Obj;

extern AutosarIpcOutLink_Obj gIpcOutLink_obj[AUTOSAR_IPC_OUT_LINK_OBJ_MAX];

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32 AutosarIpcOutLink_drvProcessBuffers(AutosarIpcOutLink_Obj *pObj, System_AutosarMetaBuffer *pBuffer);

Int32 AutosarIpcOutLink_drvReleaseBuffers(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_drvStart(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_drvStop(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_drvPrintStatistics(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_drvCreate(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_drvDelete(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_registerInterruptCallback(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_unRegisterInterruptCallback(AutosarIpcOutLink_Obj *pObj);

Int32 AutosarIpcOutLink_drvNotifyCb(UInt32 remoteProcId, UInt32 eventId,
                                UInt32 payload,
                                Void     *arg,
                                Int32  status);

Void AutosarIpcOutLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

Int32 AutosarIpcOutLink_tskCreate(UInt32 instId);

#endif

/* @} */
