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
 * \ingroup EP_LINK_API
 * \defgroup EP_LINK_IMPL EP Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file epLink_priv.h
 *
 * \brief Endpoint(EP) Link Private Header File
 *
 *        This file has the structures, enums, function prototypes
 *        for EP link, which are not exposed to the application
 *
 * \version 0.0 (May 2015) : [SM] First version
 *
 *******************************************************************************
 */

#ifndef _EP_LINK_PRIV_H_
#define _EP_LINK_PRIV_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/epLink.h>
#include <links_fw/src/hlos/osa/include/osa_buf.h>
#include <links_fw/src/hlos/osa/include/osa_tsk.h>
#include <links_fw/src/hlos/osa/include/osa_prf.h>
#include <vivi_plugin.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Maximum number of EP links to be used and stack sizes
 *          to be used.
 *
 *******************************************************************************
 */

#define EP_LINK_OBJ_MAX        (4)

/**
 *******************************************************************************
 * \brief size of EP link thread stack
 *******************************************************************************
 */
#define EP_LINK_TSK_STACK_SIZE (OSA_TSK_STACK_SIZE_DEFAULT)

/**
 *******************************************************************************
 * \brief size of EP link thread priority
 *******************************************************************************
 */
#define EP_LINK_TSK_PRI (OSA_THR_PRI_DEFAULT)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  EP Link Object
 *
 *******************************************************************************
*/
typedef struct {
    UInt32 linkId;
    /**< Link ID of this Link Obj */

    UInt32 instId;
    /**< Instance index of this link */

    OSA_TskHndl tsk;
    /**< Link task handle */

    char tskName[32];
    /**< Link task name */

    System_LinkInfo linkInfo;
    /**< Current Link channel info */

    EpLink_CreateParams  createArgs;
    /**< create time arguments */

    struct ep_plugin_ctx ep_ctx;
    /**< endpoint's plugin context */

    OSA_BufHndl outBufQue;
    /**< required for source eplink to store the buffers */

    int32_t (*post_buf) (struct ep_plugin_ctx*, System_Buffer*);
    /**< function pointer to post buffers to the vivi framework */

    OSA_LatencyStats  srcToEpSinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */
} EpLink_obj;

extern EpLink_obj gEpLink_obj[];

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/* Common across source and sink */
Int32 EpLink_getLinkInfo(Void *pTsk, System_LinkInfo *info);
Int32 EpLink_drvPutEmptyBuffers(EpLink_obj *pObj, System_BufferList *pBufList);
Int32 EpLink_drvGetFullBuffers(EpLink_obj *pObj, System_BufferList *pBufList);
Int32 EpLink_drvCreateQueHandle(EpLink_obj *pObj, OSA_MsgHndl *pMsg);
Int32 EpLink_drvCloseQueHandle(EpLink_obj *pObj);


/* Sink specific */
Int32 EpLink_drvSinkCreate(EpLink_obj *pObj);
Int32 EpLink_drvSinkStart(EpLink_obj *pObj);
Int32 EpLink_drvSinkStop(EpLink_obj *pObj);
Int32 EpLink_drvSinkDelete(EpLink_obj *pObj);
Int32 EpLink_drvSinkProcessBuffers(EpLink_obj *pObj);
Int32 EpLink_drvSinkPutEmptyBuffers(EpLink_obj *pObj, System_BufferList *pBufList);
/* Source specific */
Int32 EpLink_drvSourceCreate(EpLink_obj *pObj, EpLink_ConfigSource *srcCfg);
Int32 EpLink_drvSourceStart(EpLink_obj *pObj);
Int32 EpLink_drvSourceStop(EpLink_obj *pObj);
Int32 EpLink_drvSourceDelete(EpLink_obj *pObj);
Int32 EpLink_drvSourceGetFullBuffers(EpLink_obj *pObj, System_BufferList *pBufList);
Int32 EpLink_drvSourcePutEmptyBuffers(EpLink_obj *pObj, System_BufferList *pBufList);
Int32 EpLink_drvSourceProcessBuffers(EpLink_obj *pObj, System_Buffer *pBuf);

#endif

/* @} */
