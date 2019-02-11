/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
 *******************************************************************************
 *
 * \ingroup DATA_COLLECT_LINK_API
 * \defgroup DATA_COLLECT_LINK_IMPL DataCollect Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file dataCollectLink_priv.h DataCollect Link private API/Data structures
 *
 * \brief  This file is a private header file for dataCollect link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of dataCollect link.
 *
 * \version 0.0 (Jun 2014) : [NN] First version ported to Linux
 *
 *******************************************************************************
 */

#ifndef _DATA_COLLECT_LINK_PRIV_H_
#define _DATA_COLLECT_LINK_PRIV_H_

#include <bucket.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/hlos/osa/include/osa.h>
#include <src/hlos/osa/include/osa_tsk.h>
#include <src/hlos/osa/include/osa_mem.h>
#include <src/hlos/osa/include/osa_prf.h>
#include <include/link_api/dataCollectLink.h>
#include <src/hlos/system/system_priv_common.h>
#include <stdio.h>
#include <osa_cache.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Size DATA_COLLECT link stack
 *******************************************************************************
 */
#define DATA_COLLECT_LINK_TSK_STACK_SIZE (OSA_TSK_STACK_SIZE_DEFAULT)



#define DATA_COLLECT_BUCKET_MAX_BYTES        ((uint64_t)2047*MB)


 /**
 *******************************************************************************
 *
 * \brief Maximum number of dataCollect link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DATA_COLLECT_LINK_OBJ_MAX    (1)

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
    /**< Placeholder to store dataCollect link task id */

    UInt32 linkInstId;
    /**< Instance ID of this link */

    OSA_TskHndl tsk;
    /**< Handle to dataCollect link task */

    DataCollectLink_CreateParams createArgs;
    /**< Create params for dataCollect link */

    UInt32 enableDataCollect;
    /**< Data collection mode */

    System_LinkQueInfo  inQueInfo;
    /**< Input Queue info */

    Bucket  *bucket;
    /**< data collection bucket */

    OSA_LinkStatistics linkStats;
    /**< Statistics related to this link */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    UInt64 totalTime;
    UInt32 minTime;
    UInt32 maxTime;
    UInt32 numFrames;
    UInt32 realMissCount;

} DataCollectLink_Obj;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
