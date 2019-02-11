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
 * \ingroup SUBFRAMECOPY_LINK_API
 * \defgroup SUBFRAMECOPY_LINK_IMPL subframe copy link Implementation
 *
 * @{
 */


 /**
  *******************************************************************************
  *
  * \file subframeCopyLink_priv.h SubFrame Copy Algorithm Link private
  *                            API/Data structures
  *
  * \brief  This link private header file has defined
  *         - Algorithm link instance/handle object
  *         - All the local data structures
  *         - Algorithm plug in function interfaces
  *
  * \version 0.0 (Jul 2014) : [VT] First version
  *
  *******************************************************************************
  */


#ifndef _SUBFRAMECOPY_LINK_PRIV_H_
#define _SUBFRAMECOPY_LINK_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <src/rtos/links_eve/system/system_priv_eve.h>
#include <include/link_api/algorithmLink.h>
#include <src/rtos/links_common/algorithm/algorithmLink_priv.h>
#include <include/alglink_api/algorithmLink_subframeCopy.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include "src/rtos/utils_common/include/utils_dma.h"
#include "src/rtos/utils_common/include/utils_vip_interrupt.h"


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Minimum number of frames (buffers) required for doing capture without
 *        dropping frames.
 *
 *        If application provides numBufs less than
 *        SUBFRAME_COPY_LINK_MIN_FRAMES it will be overridden to
 *        SUBFRAME_COPY_LINK_MIN_FRAMES
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SUBFRAME_COPY_LINK_MIN_FRAMES             (3)

/**
 *******************************************************************************
 *
 * \brief Maximum number of frames getting allocated for subframe capture link.
 *
 *        If application provides numBufs more than
 *        SUBFRAME_COPY_LINK_MAX_FRAMES it will be overridden to
 *        SUBFRAME_COPY_LINK_MAX_FRAMES
 *        This is to allocate frame container statically, which will point to
 *        actual frames. Frames will be allocated based on application requests
 *        but frame containers are always allocated at init time that is max
 *        of frames possible.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */

#define SUBFRAME_COPY_LINK_MAX_FRAMES           (SYSTEM_LINK_MAX_FRAMES_PER_CH)


/**
 *******************************************************************************
 *
 * \brief The link maintains a queue for storing new data - frame complete or
 * subframe complete commands. This parameter indicates the queu depth required
 *
 *
 *******************************************************************************
 */
#define SUBFRAME_COPY_LINK_CMDQ_DEPTH                                       (4)


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

typedef enum
{
    SUBFRAME_ALGLINK_NEWDATA_IS_INVALID = 0,
    SUBFRAME_ALGLINK_NEWDATA_IS_SUBFRAME,
    SUBFRAME_ALGLINK_NEWDATA_IS_FRAME
} Subframe_AlgLink_NewDataCmdType;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Structure for EDMA object
 *
 *******************************************************************************
*/
typedef struct
{
    unsigned int        edmaChId;
    /**< EDMA CH ID that is used for this EDMA */

    unsigned int        tccId;
    /**< EDMA TCC ID that is used for this EDMA */

    EDMA3_DRV_Handle    hEdma;
    /**< Handle to EDMA controller associated with this logical DMA channel */

    EDMA3_DRV_PaRAMRegs *pParamSet;
    /**< Pointer to physical area of PaRAM for this channel */

} AlgorithmLink_SubframeCopyEdma_Obj;


/**
 *******************************************************************************
 *
 *   \brief Structure containing subframe copy alg link specific parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    Utils_TskHndl *ptsk;
    /**< Handle to subframe copy link task */

    AlgorithmLink_SubframeCopyCreateParams createArgs;
    /**< Create params for subframe copy link */

    AlgorithmLink_SubframeCopyControlParams  controlParams;
    /**< Control params of the subframe copy link */

    UInt32 numBufs;
    /**< Number of buffers allocated for this instance */

    CaptureLink_Subframe_Info     captureLinkSubframeInfo;
    /**< OCMC buffer i.e. VIP output buffer info */

    System_Buffer buffers[SUBFRAME_COPY_LINK_MAX_FRAMES];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[SUBFRAME_COPY_LINK_MAX_FRAMES];
    /**< Payload for System buffers */

    FVID2_Frame frames[SUBFRAME_COPY_LINK_MAX_FRAMES];
    /**< FVID2_Frames to handle the frame buffers */

    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Q */

    System_Buffer *sysBufCurrentlyFilling;
    /** <System buffer currently getting filled with subframe data*/

    BspOsal_IntrHandle hwiHandle;
    /** < Hwi Handle corresponding to the VIP interrupts registered*/

    AlgorithmLink_SubframeCopyEdma_Obj EDMA_subframeToDDR;
    /** < EDMA object for subframe copy */

    #if 0
    Utils_LatencyStats  linkLatency;
    /**< Structure to find out min, max and average latency of the link */

    Utils_LatencyStats  srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */

    Utils_LinkStatistics    linkStats;
    /**< links statistics like frames captured, dropped etc */
    #endif
    System_LinkStatistics  *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    UInt32 subFrameNum;
    /**< Subframe number currently getting processsed*/

    UInt32 numLinesRemainInCurFrame;
    /**< Number of lines (vertical) remaining to be processed in current frome*/

    UInt32 numSubframesInEachFrame;
    /**< Total number of subframes in each frame for given width/height*/

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    Bool isFirstSubFrameRecv;
    /**< Flag to indicate if first subframe frame is received. Initially
     * dummy frame complete ISRs are triggerred which need to be ignored till a
     * valid subframe is recieved
     */

    Bool dropFrame;
    /**< Flag to indicate if cuurent frame needs to be dropped*/

    Utils_QueHandle newDataCmdQ;
    /**< Handle for the new data command queue - This queue is filled when ISR
    * is raised from VIP - the entries in queu indicate if subframe/frame
    * complete event is recieved.
    */

    UInt32 cmdQ[SUBFRAME_COPY_LINK_CMDQ_DEPTH];
    /**< Entries in the new data command queue*/
}AlgorithmLink_SubframeCopyObj;


/*******************************************************************************
 *  Subframe copy algorithm Link Private Functions
 *******************************************************************************
 */

Int32 AlgorithmLink_SubframeCopyCreate
                                        (void * pObj, void * pCreateParams);
Int32 AlgorithmLink_SubframeCopyProcess(void * pObj);
Int32 AlgorithmLink_SubframeCopyControl
                                        (void * pObj, void * pControlParams);
Int32 AlgorithmLink_SubframeCopyStop(void * pObj);
Int32 AlgorithmLink_SubframeCopyDelete(void * pObj);
static void AlgorithmLink_SubframeCopyFrameCompleteCallback
                            (AlgorithmLink_SubframeCopyObj *pSubframeCopyObj);
static void AlgorithmLink_SubframeCopySubFrameCallback
                            (AlgorithmLink_SubframeCopyObj *pSubframeCopyObj);
void AlgorithmLink_SubframeCopyVip_Isr_Func (void *pPtr);
static Int32 AlgorithmLink_SubframeCopyInitSystemBuffer(void *pObj,
                                                FVID2_FrameList *pFrameList);
static Int32 AlgorithmLink_SubframeCopyAllocFrames(void *pObj);
static Int32 AlgorithmLink_SubframeCopyProcessSubframeData
                                                            (void * pObj);
static Int32 AlgorithmLink_SubframeCopyProcessFrameData(void * pObj);
static Int32 AlgorithmLink_SubframeCopyFreeFrames(void * pObj);
Int32 AlgorithmLink_SubframeCopyPrintStatistics(void *pObj,
                           AlgorithmLink_SubframeCopyObj *pSubframeCopyObj);
Int32 AlgorithmLink_SubframeCopyEDMACreate
                            (AlgorithmLink_SubframeCopyObj * pObj);
Int32 AlgorithmLink_SubframeCopyEDMACopy
        (AlgorithmLink_SubframeCopyObj * pObj,
        UInt32*inPtr[],UInt32*outPtr[],UInt32 width,UInt32 height,
        UInt32 inPitch[],UInt32 outPitch[],UInt32 dataFormat);
Int32 AlgorithmLink_SubframeCopyEDMADelete
                        (AlgorithmLink_SubframeCopyObj * pObj);

#endif

/* @} */
