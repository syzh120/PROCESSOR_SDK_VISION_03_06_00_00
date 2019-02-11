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
 * \ingroup SYNC_LINK_API
 * \defgroup SYNC_LINK_IMPL Sync Link Implementation
 *
 * @{
 */

 /**
 *******************************************************************************
 *
 * \file syncLink_priv.h
 *
 * \brief Sync Link Private Header File
 *
 *        This file has the structures, enums, function prototypes
 *        for sync link, which are not exposed to the application
 *
 * \version 0.0 (Aug 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef SYNC_LINK_PRIV_H
#define SYNC_LINK_PRIV_H

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/links_common/system/system_priv_common.h>
#include <include/link_api/syncLink.h>

/**
 *******************************************************************************
 *
 * \brief Maximum number of sync link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SYNC_LINK_OBJ_MAX    (4U)

/**
 *******************************************************************************
 * \brief Max number of elemtns in sync link local queue
 *******************************************************************************
 */
#define SYNC_LINK_LOCAL_QUE_MAX_ELEMENTS        (10U)

/**
 *******************************************************************************
 * \brief Sync link max frames per out queue.
 *
 *******************************************************************************
 */
#define SYNC_LINK_MAX_FRAMES_PER_OUT_QUE        (8U)


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
    Utils_QueHandle    localQueHandle;
    /**< Handle to the queue for this channel */
    System_Buffer      *queMem[SYNC_LINK_LOCAL_QUE_MAX_ELEMENTS];
    /**< Queue memory */
} SyncLink_ChObj;


/**
 *******************************************************************************
 * \brief Structure to hold the original System Buffer pointers when a
 *        composite frame is constructed
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 numCh;
    System_Buffer *pOrgBuf[SYNC_LINK_MAX_CHANNELS];
} SyncLink_OrgBufferPtr;

/**
 *******************************************************************************
 *
 *  \brief  Sync Link Object
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 tskId;
    /**< Placeholder to store sync link task id */

    char name[32];
    /**< Link name */

    Utils_TskHndl tsk;
    /**< Link task handle */

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    UInt32 linkInstId;
    /**< Instance Id of the link */

    UInt32 numCh;
    /**< Number of channels to sync */

    SyncLink_CreateParams  createArgs;
    /**< create time arguments */

    System_LinkInfo prevLinkInfo;
    /**< Previous link information */

    System_LinkInfo linkInfo;
    /**< Current link information */

    SyncLink_ChObj  chObj[SYNC_LINK_MAX_CHANNELS];
    /**< Instances for each channel */

    Utils_BufHndl outFrameQue;
    /**< Handle for the output queue */

    System_VideoFrameCompositeBuffer compBuf[SYNC_LINK_MAX_FRAMES_PER_OUT_QUE];
    /**< Composite buffers instances */

    System_Buffer outBuf[SYNC_LINK_MAX_FRAMES_PER_OUT_QUE];
    /**< Output System Buffer instances */

    SyncLink_OrgBufferPtr orgBufPtr[SYNC_LINK_MAX_FRAMES_PER_OUT_QUE];
    /**< Structure to hold the original System Buffer pointers when a composite
         frame is constructed */

    System_BufferList dropBufList;
    /**< Holds all dropped frames while sync logic iterates through */

    UInt64 masterTimeStamp;
    /**< Current master timestamp, which is the average of all timestamps
         of buffers in the channel or master channel timestamp */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrame;
    /**< Flag to indicate first frame is received */

    BspOsal_ClockHandle timer;
    /**<Timer used to generate new data at a set interval*/

    UInt32 outputFrmCnt;
    /**< Sync Link output frame counter */

} SyncLink_Obj;

extern SyncLink_Obj gSyncLink_obj[SYNC_LINK_OBJ_MAX];

Void SyncLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

Int32 SyncLink_tskCreate(UInt32 instId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

