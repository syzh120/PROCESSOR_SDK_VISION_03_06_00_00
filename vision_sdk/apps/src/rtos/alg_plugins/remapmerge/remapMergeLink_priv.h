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
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file remapMergeLink_priv.h Remap Merge Algorithm Link
 *       private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.1 (Oct 2014) : [YM] First version
 *
 *******************************************************************************
 */

#ifndef _REMAPMERGE_LINK_PRIV_H_
#define _REMAPMERGE_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_remapMerge.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include "iremap_merge_ti.h"
#include <src/rtos/alg_plugins/common/include/alg_ivision.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Threshold size beyond which memory gets allocated in Shared area
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define REMAPMERGE_ALGLINK_SRMEM_THRESHOLD (ALGORITHMLINK_SRMEM_THRESHOLD)

/**
 *******************************************************************************
 *
 *   \brief Max number of buffers
 *
 *   Soft Isp alg takes an input frame and generates an output
 *   frame. This macro defines the maximum number of such buffers this
 *   link can handle
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define REMAPMERGE_LINK_MAX_NUM_OUTPUT    (6)

/**
 *******************************************************************************
 *
 *   \brief Max number of channels per output queue
 *
 *   Soft Isp alg works on Stereo sensors - so 2 channels data the link can
 *   handle
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define REMAPMERGE_MAX_CH_PER_OUT_QUE    (2)


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing feature plane computation algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkOutQueParams             outQueParams;
    /**< Output queue information */
    System_LinkInQueParams              inQueParams;
    /**< Input queue information */
    AlgorithmLink_InputQueueInfo        inputQInfo;
    /**< All the information about input Queue*/
    AlgorithmLink_OutputQueueInfo       outputQInfo;
    /**< All the information about output Queue*/
    UInt32                              numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo                   inputChInfo[REMAPMERGE_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    Void *                              handle[REMAPMERGE_MAX_CH_PER_OUT_QUE];
    /**< Handle to the algorithm */
    AlgorithmLink_RemapMergeCreateParams algLinkCreateParams;
    /**< Create params of remap merge algorithm link */
    REMAP_MERGE_TI_CreateParams         algCreateParams;
    /**< Create parameters for the algorithm */
    UInt8                            *  srcBlkMap[REMAPMERGE_MAX_CH_PER_OUT_QUE];
    /**< Source map for left and right channel */
    UInt32                              blockMapLen[REMAPMERGE_MAX_CH_PER_OUT_QUE];
    /**< Source map for left and right channel */
    IVISION_InArgs                      inArgs;
    /**< inArgs for the algorithm */
    IVISION_OutArgs                     outArgs;
    /**< outArgs for the algorithm */
    IVISION_InBufs                      inBufs;
    /**< input buffers for the algorithm */
    IVISION_OutBufs                     outBufs;
    /**< output buffers for the algorithm */
    IVISION_BufDesc                     inBufDesc;
    /**< input buffer descriptor */
    IVISION_BufDesc                     lutBufDesc;
    /**< input buffer descriptor */
    IVISION_BufDesc                     outBufDesc;
    /**< output buffer descriptor */
    IVISION_BufDesc                     *inBufDescList[REMAP_MERGE_TI_BUFDESC_IN_REMAP_TOTAL];
    /**< list of input buffer descriptors */
    IVISION_BufDesc                     *outBufDescList[REMAP_MERGE_TI_BUFDESC_OUT_TOTAL];
    /**< list of input buffer descriptors */
    System_Buffer
            buffers[REMAPMERGE_MAX_CH_PER_OUT_QUE][REMAPMERGE_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */
    System_VideoFrameBuffer
        videoFrames[REMAPMERGE_MAX_CH_PER_OUT_QUE][REMAPMERGE_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers */
    UInt32                              output_pitch;
    /**< Pitch of output video frames. This is kept same for all channels*/
    UInt32                              output_height;
    /**< Size of each output buffer */

    UInt8           *saveFrameBufAddr;
    /**< Frame buffer used for saving captured frame for both channels */
    UInt32           saveFrameBufSize;
    /**< Frame buffer used for saving captured frame */
    Uint32           pgmHeaderSize;
    /**< Size of pgm header appended to captured frame */
    volatile UInt32  saveFrame[REMAPMERGE_MAX_CH_PER_OUT_QUE];
    /**< Flag to indicate saving of the frame from process callback */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool                                isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
} AlgorithmLink_RemapMergeObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergeCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_RemapMergeProcess(void * pObj);
Int32 AlgorithmLink_RemapMergeControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_RemapMergeStop(void * pObj);
Int32 AlgorithmLink_RemapMergeDelete(void * pObj);
Int32 AlgorithmLink_RemapMergePrintStatistics
                        (void *pObj, AlgorithmLink_RemapMergeObj *pRemapMergeObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
