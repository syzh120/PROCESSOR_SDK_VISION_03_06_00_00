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
 * \ingroup DISPDISTSRC_LINK_API
 * \defgroup DISPDISTSRC_LINK_IMPL Disp Dist Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file dispDistSrcLink_priv.h Disp Dist Source Link private API/Data structures
 *
 * \brief  This file is a private header file for disp dist Source link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of disp dist link.
 *
 * \version 0.0 (Nov 2017) : [BJ] First version
 *
 *******************************************************************************
 */

#ifndef _DISP_DIST_SRC_LINK_PRIV_H_
#define _DISP_DIST_SRC_LINK_PRIV_H_

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
#include <include/link_api/dispDistSrcLink.h>
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
 * \brief Size of Disp Dist Src link stack
 *******************************************************************************
 */
#define DISP_DIST_SRC_LINK_TSK_STACK_SIZE (OSA_TSK_STACK_SIZE_DEFAULT)

/**
 *******************************************************************************
 * \brief Size of Disp Dist Src link queues
 *******************************************************************************
 */
#define DISP_DIST_SRC_MAX_OUT_BUFS        (4)
#define DISP_DIST_SRC_LINK_QUEUE_LEN      (16)
#define DISP_DIST_SRC_LINK_EVENT_BUF_SZ   (4096)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Structure to hold all Disp dist src link related information
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

    DispDistSrcLink_CreateParams createArgs;
    /**< Create params for null link */

    System_LinkInfo linkInfo;
    /* Null source link info that is returned when queried by next link */

    OSA_QueHndl outThrBufQue;
    /**< Null Source link thread side empty buffer queue */

    OSA_ThrHndl workThread;
    /**< Null Source link worker thread*/

    OSA_LatencyStats linkLatency;
    /**< Structure to find out min, max and average latency of the link */
    OSA_LatencyStats srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */
    OSA_LinkStatistics linkStats;
    /* link specific statistics */

    Bool isFirstBufferSent;
    /**< flag indicates if disp dist Src Link has sent any buffers to next link yet*/

    Int32 v_fd;

    UInt32 provider_id;

    UInt32 outSerial;
    UInt32 inSerial;

} DispDistSrcLink_Obj;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
