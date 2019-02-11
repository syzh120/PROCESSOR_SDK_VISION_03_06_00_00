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
 * \ingroup IPC_OUT_LINK_API
 * \defgroup IPC_OUT_LINK_IMPL IPC Out Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file ipcOutLink_priv.h
 *
 * \brief IPC OUT Link Private Header File
 *
 *        This file has the structures, enums, function prototypes
 *        for IPC OUT link, which are not exposed to the application
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef _IPC_OUT_LINK_PRIV_H_
#define _IPC_OUT_LINK_PRIV_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <links_fw/src/hlos/system/system_priv_ipc.h>
#include <include/link_api/ipcLink.h>
#include <links_fw/src/hlos/osa/include/osa_ipc_que.h>
#include <links_fw/src/hlos/osa/include/osa_prf.h>
#include <links_fw/src/hlos/osa/include/osa_tsk.h>

/**
 *******************************************************************************
 *
 *   \brief Maximum number of IPC links to be used and stack sizes
 *          to be used.
 *
 *          It is defined based on the processor core, thus giving
 *          flexibility of different number of links / stack sizes for different
 *          processor cores. However for different links on the same processor
 *          core, stack size is kept same.
 *
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */

#define IPC_OUT_LINK_OBJ_MAX        (5U)

/**
 *******************************************************************************
 * \brief Size IPC_OUT link stack
 *******************************************************************************
 */
#define IPC_OUT_LINK_TSK_STACK_SIZE (OSA_TSK_STACK_SIZE_DEFAULT)



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
#define IPC_OUT_LINK_CMD_RELEASE_FRAMES     (0x5100)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *  \brief  Channel specific information
 *
 *******************************************************************************
 */
typedef struct {

    OSA_BufSkipContext bufSkipContext;

} IpcOutLink_ChObj;

/**
 *******************************************************************************
 *
 *  \brief  IPC Out Link Object
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 linkId;
    /**< Link ID of this Link Obj */

    UInt32 linkInstId;
    /**< Instance index of this link */

    OSA_TskHndl tsk;
    /**< Link task handle */

    char tskName[32];
    /**< Link task name */

    IpcLink_CreateParams  createArgs;
    /**< create time arguments */

    System_LinkInfo prevLinkInfo;
    /**< Previous Link channel info */

    System_LinkInfo linkInfo;
    /**< Current Link channel info */

    OSA_IpcQueHandle ipcOut2InQue;
    /**< IPC OUT to IPC IN queue */

    OSA_IpcQueHandle ipcIn2OutQue;
    /**< IPC IN to IPC OUT queue */

    Ptr ipcOut2InSharedMemBaseAddr;
    /**< Base address of IPC queue area */

    Ptr ipcIn2OutSharedMemBaseAddr;
    /**< Base address of IPC queue area */

    OSA_QueHndl localQue;
    /**< local queue handle */

    Ptr localQueMem[SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS];
    /**< Memory for local queue */

    IpcOutLink_ChObj    chObj[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel specific information */

    OSA_LatencyStats  linkLatency;
    /**< Structure to find out min, max and average latency of the link */

    OSA_LatencyStats  srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */

    OSA_LinkStatistics linkStats;
    /**< Statistics related to this link */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

} IpcOutLink_Obj;

extern IpcOutLink_Obj gIpcOutLink_obj[];

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32 IpcOutLink_drvProcessBuffers(IpcOutLink_Obj *pObj);

Int32 IpcOutLink_drvReleaseBuffers(IpcOutLink_Obj *pObj);

Int32 IpcOutLink_drvStop(IpcOutLink_Obj *pObj);

Int32 IpcOutLink_drvSetFrameRate(IpcOutLink_Obj *pObj,
                              IpcLink_FrameRateParams *pPrm);

Int32 IpcOutLink_drvPrintStatistics(IpcOutLink_Obj *pObj);

Int32 IpcOutLink_drvCreate(IpcOutLink_Obj *pObj, IpcLink_CreateParams *pPrm);

Int32 IpcOutLink_drvDelete(IpcOutLink_Obj *pObj);

Int32 IpcOutLink_getLinkInfo(Void *pTsk,
                             System_LinkInfo *info);

Void  IpcOutLink_drvNotifyCb(OSA_TskHndl * pTsk);

Int32 IpcOutLink_drvPrdStart(IpcOutLink_Obj *pObj);

Int32 IpcOutLink_drvPrdStop(IpcOutLink_Obj *pObj);


#endif

/* @} */
