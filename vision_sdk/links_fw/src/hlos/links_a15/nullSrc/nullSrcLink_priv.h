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
 * \ingroup NULLSRC_LINK_API
 * \defgroup NULLSRC_LINK_IMPL Null Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file nullSrcLink_priv.h Null Source Link private API/Data structures
 *
 * \brief  This file is a private header file for null Source link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of null link.
 *
 * \version 0.0 (Dec 2015) : [BJ] First version ported to Linux
 *
 *******************************************************************************
 */

#ifndef _NULL_SRC_LINK_PRIV_H_
#define _NULL_SRC_LINK_PRIV_H_

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
#include <links_fw/src/hlos/osa/include/osa_prf.h>
#include <include/link_api/nullSrcLink.h>
#include <links_fw/src/hlos/system/system_priv_common.h>
#include <links_fw/src/hlos/osa/include/osa_timer.h>

#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Size NULL link stack
 *******************************************************************************
 */
#define NULL_SRC_LINK_TSK_STACK_SIZE (OSA_TSK_STACK_SIZE_DEFAULT)

/**
 ******************************************************************************
 *
 * \brief Maximum number of output buffers in null source link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_MAX_OUT_BUFFERS   (NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH \
                                            * NULL_SRC_LINK_MAX_CH)


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Structure to hold all Dup link related information
 *
 *******************************************************************************
 */

typedef struct {
    UInt32 tskId;
    /**< Placeholder to store null link task id */

    OSA_TskHndl tsk;
    /**< Handle to null link task */

    char tskName[32];
    /**< Link task name */

    NullSrcLink_CreateParams createArgs;
    /**< Create params for null link */

    System_LinkInfo linkInfo;
    /* Null source link info that is returned when queried by next link */

    OSA_BufHndl outBufQue;
    /**< Null Source link output side full buffer queue */

    System_Buffer *pBufferOnFullQ[NULL_SRC_LINK_MAX_OUT_BUFFERS];
    /** Holds full buffers */

    System_Buffer *pBufferOnEmptyQ[NULL_SRC_LINK_MAX_CH]
                                  [NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH];
   /** Holds individual channel empty buffers */

    System_Buffer buffers[NULL_SRC_LINK_MAX_CH]
                         [NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[NULL_SRC_LINK_MAX_CH]
                                       [NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH];
    /**< Payload for System buffers in case of YUV data*/

    System_BitstreamBuffer bitstreamBuf[NULL_SRC_LINK_MAX_CH]
                                       [NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH];
    /*< Payload for System buffers in case of compressed data*/

    OSA_TimerHndl timerHndl;
    /**<Timer used to generate new data at a set interval*/

    FILE *fpDataStream[NULL_SRC_LINK_MAX_CH];
    /**< Binary File containing the stream data.*/

    FILE *fpIndexFile[NULL_SRC_LINK_MAX_CH];
    /**< File used to index into fpDataStream.
    * It will contain frame sizes in bytes.
    */

    OSA_LatencyStats linkLatency;
    /**< Structure to find out min, max and average latency of the link */
    OSA_LatencyStats srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */
    OSA_LinkStatistics linkStats;
    /* link specific statistics */

    Bool isFirstBufferSent;
    /**< flag indicates if Null Src Link has sent any buffers to next link yet*/

    UInt32 numPendingCmds;
    /**< Number of pending NEW_DATA_CMD that are yet to handled */

    Ptr allocatedAddr[NULL_SRC_LINK_MAX_CH]
                     [NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH];

    Ptr bufferAddr[NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH];
} NullSrcLink_Obj;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
