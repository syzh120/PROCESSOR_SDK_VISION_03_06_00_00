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
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_priv.h Algorithm Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_PRIV_H_
#define ALGORITHM_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include "algorithmLink_cfg.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max Number of algorithm link queues (I/P or O/P) per link
 *
 *    DES_ID: DOX_DES_TAG(DES_ALGLINK_001)
 *    REQ_ID: DOX_REQ_TAG(ADASVISION-1546)
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_MAX_NUMQUEUES                        (5U)

/**
 *******************************************************************************
 *
 *   \brief Max Number of channels per queue of algorithm link
 *
 *    DES_ID: DOX_DES_TAG(DES_ALGLINK_001)
 *    REQ_ID: DOX_REQ_TAG(ADASVISION-1547)
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_MAX_NUMCHPERQUEUE                     (5U)

/**
 *******************************************************************************
 *
 *   \brief Max Number of system buffers per link queue (I/P or O/P)
 *
 *    DES_ID: DOX_DES_TAG(DES_ALGLINK_001)
 *    REQ_ID: DOX_REQ_TAG(ADASVISION-1548)
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_MAX_QUEUELENGTH    (16U*ALGORITHM_LINK_MAX_NUMCHPERQUEUE)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the algorithm buffer release status
 *
 *******************************************************************************
*/
typedef enum
{
    ALGORITHM_LINK_RELSTATUS_NOTREADY = 0U,
    /**< Not yet ready to be released */
    ALGORITHM_LINK_RELSTATUS_READY = 1U,
    /**< Ready to be released */
    ALGORITHM_LINK_RELSTATUS_ERROR = 2U,
    /**< Error occurred in status update functionN */
    ALGORITHM_LINK_RELSTATUS_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmLink_ReleaseStatus;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the Algorithm link Buffer free status
 *
 *          In algorithm link a buffer can be freed up only after both the
 *          current link and the next link which uses this buffer, free it up.
 *          Below structure is defined to do this book keeping.
 *
 *******************************************************************************
*/
typedef struct
{
    System_Buffer *pBuff;
    /**<  Pointer of the system buffer */
} AlgorithmLink_BufferFreeStatus;

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the Que of system buffers
 *
 *    DES_ID: DOX_DES_TAG(DES_ALGLINK_001)
 *    REQ_ID: DOX_REQ_TAG(ADASVISION-1549)
 *
 *   Que handle and the associated memory for queue elements are grouped.
 *
 *******************************************************************************
*/
typedef struct {
    Utils_QueHandle    queHandle;
    /**< Handle to the queue for this channel */
    System_Buffer      *queMem[ALGORITHM_LINK_MAX_QUEUELENGTH];
    /**< Queue memory */
} AlgorithmLink_SysBufferQue;

/**
 *******************************************************************************
 *
 *   \brief Algorithm link instance object
 *
 *          This structure is defined as a common object for all algorithm
 *          links.
 *          There is a pointer "algorithmParams" which shall point to
 *          structure containing algorithm specific parameters. This specific
 *          structure will be defined as per algorithm in the corresponding link
 *          file.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 linkId;
    /**< placeholder to store the Algorithm link task Id */
    char name[32];
    /**< Link name */
    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */
    Utils_TskHndl tsk;
    /**< placeholder to store the Algorithm link task handler */
    UInt32 algId;
    /**< Id of the algorithm used in this link */
    AlgorithmLink_CreateParams createArgs;
    /**< placeholder to store the Algorithm link create parameters */
    void * algorithmParams;
    /**< pointer to structure which holds all algorithm specific parameters */
    System_LinkInfo linkInfo;
    /**< Specifies a place holder that describe the LINK information */
    Int32 numInputQUsed;
    /**< Number of input queues used by this algorithm link */
    Int32 numOutputQUsed;
    /**< Number of output queues used by this algorithm link */
    AlgorithmLink_InputQueueInfo inputQInfo[ALGORITHM_LINK_MAX_NUMQUEUES];
    /**< Information about the output queues */
    AlgorithmLink_OutputQueueInfo outputQInfo[ALGORITHM_LINK_MAX_NUMQUEUES];
    /**< Information about the output queues */
    AlgorithmLink_SysBufferQue emptyOutputQ[ALGORITHM_LINK_MAX_NUMQUEUES]
                                           [ALGORITHM_LINK_MAX_NUMCHPERQUEUE];
    /**< Queues to hold empty output buffers. Seperate Q for each channel */
    AlgorithmLink_SysBufferQue fullOutputQ[ALGORITHM_LINK_MAX_NUMQUEUES];
    /**< Queue to hold full output buffers. Single Q for all chanls of givenQ */
    AlgorithmLink_BufferFreeStatus inputQFreeStatus
                                         [ALGORITHM_LINK_MAX_NUMQUEUES]
                                         [ALGORITHM_LINK_MAX_QUEUELENGTH];
    /**< Needed for book keeping related to release (freeing up) of input
     * buffers
     */
    AlgorithmLink_BufferFreeStatus outputQFreeStatus
                                          [ALGORITHM_LINK_MAX_NUMQUEUES]
                                          [ALGORITHM_LINK_MAX_QUEUELENGTH];
    /**< Needed for book keeping related to release (freeing up) of output
     * buffers
     */
    BspOsal_SemHandle lock;
    /**< Link level lock, used while updates the link params */
    UInt32 totalTime;
    /**< Total time duration for link, used to calculate the FPS */
    UInt32 startTime;
    /**< Start time of link, used to calculate the link stats */
    UInt32 prevTime;
    /**< Time info used to calculate some of the link stats */
    UInt32 minCbTime;
    /**< Minimum call back time noticed over the run */
    UInt32 maxCbTime;
    /**< Maximum call back time identified over the run */
    UInt32 lastCbTime;
    /**< The last/latest call back time */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by this link */

    AlgorithmLink_AlgPluginPutEmptyBuffers callbackPutEmptyBuffers;
    /**< User specified callback to call before releasing buffers */

} AlgorithmLink_Obj;

/**
 *******************************************************************************
 *
 * \brief Extern gAlgorithmLinkFuncTable
 *
 *******************************************************************************
 */
extern AlgorithmLink_FuncTable
        gAlgorithmLinkFuncTable[ALGORITHM_LINK_ALG_MAXNUM];
extern UInt32 gAlgorithmLinkFFIMode[ALGORITHM_LINK_ALG_MAXNUM];

/**
 *******************************************************************************
 *
 * \brief Extern gAlgorithmLink_obj
 *
 *******************************************************************************
 */
extern AlgorithmLink_Obj gAlgorithmLink_obj[ALGORITHM_LINK_OBJ_MAX];

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_tskRun(AlgorithmLink_Obj * pObj,
                           Utils_TskHndl * pTsk);
Void AlgorithmLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl *pMsg);
Int32 AlgorithmLink_init(void);
Int32 AlgorithmLink_deInit(void);
Int32 AlgorithmLink_getInfo(Void * ptr, System_LinkInfo * info);
Int32 AlgorithmLink_getFullBuffers(Void              * ptr,
                                   UInt16              queId,
                                   System_BufferList * pBufList);
Int32 AlgorithmLink_putEmptyBuffers(Void              *ptr,
                                    UInt16             queId,
                                    System_BufferList *pBufList);
AlgorithmLink_ReleaseStatus AlgorithmLink_sysBufRelStatusUpdate(
                        System_Buffer                   *pSysBuffer,
                        AlgorithmLink_BufferFreeStatus  *pBufferFreeStatusBase);

Int32 AlgorithmLink_tskCreate(UInt32 instId);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
