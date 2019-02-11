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
 * \ingroup DUP_LINK_API
 * \defgroup DUP_LINK_IMPL Dup Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file dupLink_priv.h Dup Link private API/Data structures
 *
 * \brief  This file is a private header file for dup link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of dup link.
 *         Dup Link is used in cases where the output buffers from one link is
 *         to be sent to multiple links. Dup link simply duplicates the buffers
 *         without actually duplicating the video frame and send these buffers
 *         across all output queues. Dup link implements the logic to release
 *         buffers to it's previous link only when every link connected to it's
 *         output queue release the buffers.
 *
 * \version 0.0 (Apr 2016) : [YM] Ported to HLOS
 *
 *******************************************************************************
 */

#ifndef DUP_LINK_PRIV_H_
#define DUP_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <links_fw/src/hlos/osa/include/osa.h>
#include <links_fw/src/hlos/osa/include/osa_tsk.h>
#include <links_fw/src/hlos/osa/include/osa_mem.h>
#include <links_fw/src/hlos/osa/include/osa_buf.h>
#include <include/link_api/dupLink.h>
#include <links_fw/src/hlos/system/system_priv_common.h>
#include <stdio.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Maximum number of dup link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DUP_LINK_OBJ_MAX    (5U)

/**
 *******************************************************************************
 *
 * \brief Maximum frmaes an output queue can support
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DUP_LINK_MAX_FRAMES_PER_OUT_QUE    \
                           (SYSTEM_LINK_FRAMES_PER_CH*SYSTEM_MAX_CH_PER_OUT_QUE)

/**
 *******************************************************************************
 * \brief Size DUP link stack
 *******************************************************************************
 */
#define DUP_LINK_TSK_STACK_SIZE (OSA_TSK_STACK_SIZE_DEFAULT)


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 * \brief Stat structure that stores information about the number of
 *  - Recevied buffers
 *  - Forwarded buffers ( Sent to next link )
 *  - Released buffers ( Sent back to the previous link )
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 recvCount;
    UInt32 forwardCount[DUP_LINK_MAX_OUT_QUE];
    UInt32 releaseCount[DUP_LINK_MAX_OUT_QUE];
} DupLink_StatsObj;

/**
 *******************************************************************************
 *
 * \brief Structure to hold all Dup link related information
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 linkId;
    /**< Link ID of this Link Obj */

    UInt32 tskId;
    /**< Placeholder to store dup link task id */

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    OSA_TskHndl tsk;
    /**< Handle to capture link task */

    char tskName[32];
    /**< Link task name */

    DupLink_CreateParams createArgs;
    /**< Create params for dup link */

    UInt32 getFrameCount;
    /**< Count of incoming frames */

    UInt32 putFrameCount;
    /**< Count of outgoing frames */

    System_LinkInfo inTskInfo;
    /**< Output queue information of previous link */

    System_LinkInfo info;
    /**< Output queue information of this link */

    OSA_BufHndl outFrameQue[DUP_LINK_MAX_OUT_QUE];
    /**< Handles to each of the output queues */

    System_Buffer
                sysBufs[DUP_LINK_MAX_OUT_QUE * DUP_LINK_MAX_FRAMES_PER_OUT_QUE];
    /**< Placeholder to store the incoming buffers */

    System_BufferList inBufList;

    System_BufferList outBufList[DUP_LINK_MAX_OUT_QUE];

    OSA_MutexHndl lock;
    /**< Link level lock, used while updating the link params */

    DupLink_StatsObj stats;
    /**< To store statistics of the buffers */
} DupLink_Obj;

extern DupLink_Obj gDupLink_obj[DUP_LINK_OBJ_MAX];

Void DupLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState);

Int32 DupLink_tskCreate(UInt32 instId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


