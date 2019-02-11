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
 * \ingroup SGXFRMCPY_LINK_API
 * \defgroup SGXFRMCPY_LINK_IMPL SgxFrmcpy Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file sgxFrmcpyLink_priv.h SgxFrmcpy Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - SgxFrmcpy link instance/handle object
 *         - All the local data structures
 *         - SgxFrmcpy driver interfaces
 *
 * \version 0.0 (Jun 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _SGXFRMCPY_LINK_PRIV_H_
#define _SGXFRMCPY_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <links_fw/src/hlos/system/system_priv_common.h>
#include <links_fw/src/hlos/system/system_gl_egl_utils.h>
#include <osa.h>
#include <osa_mutex.h>
#include <osa_que.h>
#include <osa_prf.h>
#include <osa_mem_shared.h>
#include <osa_mem.h>
#include <osa_buf.h>
#include <include/link_api/sgxFrmcpyLink.h>
#include "sgxRender1x1.h"
#include "sgxRender2x2.h"
#include "sgxRender2x4.h"
#include "sgxRender3x3.h"
#include "sgxRenderKmsCube.h"
#include <links_fw/src/hlos/system/system_pvrscope_if.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Max Number of sgxFrmcpy link instances supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SGXFRMCPY_LINK_OBJ_MAX                     (1)

/**
 *******************************************************************************
 *
 * \brief Task size for SGXFRMCPY link task
 *
 *******************************************************************************
 */
#define SGXFRMCPY_LINK_TSK_STACK_SIZE              (OSA_TSK_STACK_SIZE_DEFAULT)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief SgxFrmcpy link instance object
 *
 *          This structure contains
 *          - All the local data structures
 *          - VPS Data structures required for SgxFrmcpy driver interfaces
 *          - All fields to support the Link stats and status information
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 linkId;
    /**< placeholder to store the SgxFrmcpy link Id */

    OSA_TskHndl tsk;
    /**< placeholder to store the SgxFrmcpy link task handler */

    char tskName[32];
    /**< Link task name */

    SgxFrmcpyLink_CreateParams createArgs;
    /**< placeholder to store the SgxFrmcpy link create parameters */

    System_LinkInfo inTskInfo;
    /**< Specifies a place holder that describe the LINK information */

    System_LinkQueInfo inQueInfo;
    /**< place holder that describe the output information of the LINK */

    OSA_LatencyStats linkLatency;
    /**< Structure to find out min, max and average latency of the link */

    OSA_LatencyStats srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */

    OSA_LinkStatistics linkStats;
    /* link specific statistics */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    System_EglWindowObj eglWindowObj;
    /**< EGL object information */

    SgxRender1x1_Obj render1x1Obj;
    /**< 1x1 rendering prgram obj */

    SgxRender2x2_Obj render2x2Obj;
    /**< 2x2 rendering prgram obj */

    SgxRender2x4_Obj render2x4Obj;
    /**< 2x4 rendering prgram obj */

    SgxRender3x3_Obj render3x3Obj;
    /**< 3x3rendering prgram obj */

    SgxRenderKmsCube_Obj renderKmsCubeObj;
    /**< KMS Cube rendering prgram obj */

    System_LinkInfo tskInfo;
    /**< Link output queue info, the next link query & use this info */

    System_PvrScope_Obj pvrscopeObj;
    /**< object to hold the PVR SCOPE FIFO delails and profile Info */

} SgxFrmcpyLink_Obj;

/*******************************************************************************
 *  SgxFrmcpy Link Private Functions
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvCreate(SgxFrmcpyLink_Obj *pObj,
                               SgxFrmcpyLink_CreateParams *pPrm);
Int32 SgxFrmcpyLink_drvStart(SgxFrmcpyLink_Obj *pObj);
Int32 SgxFrmcpyLink_drvDoProcessFrames(SgxFrmcpyLink_Obj *pObj);
Int32 SgxFrmcpyLink_drvStop(SgxFrmcpyLink_Obj *pObj);
Int32 SgxFrmcpyLink_drvDelete(SgxFrmcpyLink_Obj *pObj);
Int32 SgxFrmcpyLink_drvPrintStatistics(SgxFrmcpyLink_Obj *pObj);
Int32 SgxFrmcpyLink_drvDoProcessEglInfo(SgxFrmcpyLink_Obj *pObj,
			       struct control_srv_egl_ctx *pPrm);
Int32 SgxFrmcpyLink_getLinkInfo(Void * ptr, System_LinkInfo * info);
Int32 SgxFrmcpyLink_getFullBuffers(Void * ptr, UInt16 queId,
                                    System_BufferList * pBufList);
Int32 SgxFrmcpyLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                     System_BufferList * pBufList);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
