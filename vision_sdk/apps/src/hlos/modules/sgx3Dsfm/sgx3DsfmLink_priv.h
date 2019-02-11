/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup SGX3DSFM_LINK_API
 * \defgroup SGX3DSFM_LINK_IMPL Sgx3DSFM Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file sgx3DsfmLink_priv.h Sgx3Dsfm Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Sgx3Dsfm link instance/handle object
 *         - All the local data structures
 *         - Sgx3Dsfm driver interfaces
 *
 * \version 0.0 (Dec 2015) : [MM] First version
 *
 *******************************************************************************
 */

#ifndef _SGX3DSFM_LINK_PRIV_H_
#define _SGX3DSFM_LINK_PRIV_H_

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
#include <include/link_api/sgx3DsfmLink.h>
#include <include/alglink_api/algorithmLink_sfmMain.h>
#include <include/alglink_api/algorithmLink_sfmMap.h>
#include <src/hlos/modules/sgxRenderUtils/vis3Dsfm/sgxRender3Dsfm.h>
#include <links_fw/src/hlos/system/system_pvrscope_if.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Max Number of SGX3DSFM link instances supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SGX3DSFM_LINK_OBJ_MAX                     (1)

/**
 *******************************************************************************
 *
 * \brief Task size for SGX3DSFM link task
 *
 *******************************************************************************
 */
#define SGX3DSFM_LINK_TSK_STACK_SIZE              (OSA_TSK_STACK_SIZE_DEFAULT)

/**
 *******************************************************************************
 *
 *   \brief Max number of elements for local queues
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SGX3DSFM_LINK_MAX_LOCALQUEUELENGTH        (16)


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the Que of system buffers.
 *
 *   Que handle and the associated memory for queue elements are grouped.
 *
 *******************************************************************************
*/
typedef struct {
    OSA_QueHndl     queHandle;
    /**< Handle to the queue for this channel */
} Sgx3DsfmLink_SysBufferQue;


/**
 *******************************************************************************
 *
 *   \brief Sgx3Dsfm link instance object
 *
 *          This structure contains
 *          - All the local data structures
 *          - VPS Data structures required for Sgx3Dsfm driver interfaces
 *          - All fields to support the Link stats and status information
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32  linkId;
    /**< placeholder to store the Sgx3Dsfm link Id */
    OSA_TskHndl  tsk;
    /**< placeholder to store the Sgx3Dsfm link task handler */
    char tskName[32];
    /**< Link task name */
    UInt32  inPitch[SYSTEM_MAX_PLANES];
    /**< Pitch of the input video buffer, This is kept same for all channels */
    UInt32  inDataFormat;
    /**< Data format of the video to operate on */
    UInt32  numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    Sgx3DsfmLink_CreateParams createArgs;
    /**< placeholder to store the Sgx3Dsfm link create parameters */
    System_LinkInfo inTskInfo[SGX3DSFM_LINK_IPQID_MAXIPQ];
    /**< Specifies a place holder that describe the LINK information */
    System_LinkQueInfo inQueInfo[SGX3DSFM_LINK_IPQID_MAXIPQ];
    /**< place holder that describe the output information of the LINK */
    /**< Payload for System buffers */
    System_LinkInfo tskInfo;
    /**< Output queue information of this link */
    Sgx3DsfmLink_SysBufferQue localInputQ[SGX3DSFM_LINK_IPQID_MAXIPQ];
    /**< Local Qs to hold input */
    /**< Counter to keep track of number of frame drops */
    System_Buffer  *sysBufferEGOPOSE;
    /**< Place holder for the last egopose sysBuffer. Only one will be held
     * inside Synthesis link at any point in time.
     */
    System_Buffer  *sysBufferBOXES;
    /**< Place holder for the last boxes sysBuffer. Only one will be held
     * inside Synthesis link at any point in time.
     */
    Bool receivedFirstEGOPOSEFlag;
    /**< Flag to check the availabilty of ego pose*/
    Bool receivedFirstBOXFlag;   
    /**< Flag to check the availabilty of boxes*/
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
    SgxRender3Dsfm_Obj render3DsfmObj;
    /**< 3D rendering prgram obj */

    System_PvrScope_Obj pvrscopeObj;
    /**< object to hold the PVR SCOPE FIFO delails and profile Info */

} Sgx3DsfmLink_Obj;

/*******************************************************************************
 *  Sgx3Dsfm Link Private Functions
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_drvCreate(Sgx3DsfmLink_Obj *pObj,
                               Sgx3DsfmLink_CreateParams *pPrm);
Int32 Sgx3DsfmLink_drvStart(Sgx3DsfmLink_Obj *pObj);
Int32 Sgx3DsfmLink_drvDoProcessFrames(Sgx3DsfmLink_Obj *pObj);
Int32 Sgx3DsfmLink_drvStop(Sgx3DsfmLink_Obj *pObj);
Int32 Sgx3DsfmLink_drvDelete(Sgx3DsfmLink_Obj *pObj);
Int32 Sgx3DsfmLink_drvPrintStatistics(Sgx3DsfmLink_Obj *pObj);
Int32 Sgx3DsfmLink_drvDoProcessEglInfo(Sgx3DsfmLink_Obj *pObj,
			       struct control_srv_egl_ctx *pPrm);
Int32 Sgx3DsfmLink_getLinkInfo(Void *pTsk, System_LinkInfo *info);
Int32 Sgx3DsfmLink_getFullBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 Sgx3DsfmLink_putEmptyBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
