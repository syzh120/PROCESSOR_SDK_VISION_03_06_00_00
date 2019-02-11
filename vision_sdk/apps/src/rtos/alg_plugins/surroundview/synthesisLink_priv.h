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
 * \file synthesisLink_priv.h Synthesis Algorithm Link private
 *                            API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef SYNTHESIS_LINK_PRIV_H_
#define SYNTHESIS_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_srvCommon.h>
#include <include/alglink_api/algorithmLink_synthesis.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_que.h>
#include "./include/iSynthesisAlgo.h"
#include "svAlgLink_priv.h"
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
 *   \brief Max number of video frames (Stiched output) / PA Stats needed for
 *          synthesis algorithm
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SYNTHESIS_LINK_MAX_NUM_OUTPUT (8)

/**
 *******************************************************************************
 *
 *   \brief Max number of elements for local queues
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SYNTHESIS_LINK_MAX_LOCALQUEUELENGTH (20)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the Que of system buffers.
 *          TBD: Can be made available to all alg links?
 *
 *   Que handle and the associated memory for queue elements are grouped.
 *
 *******************************************************************************
*/
typedef struct {
    Utils_QueHandle    queHandle;
    /**< Handle to the queue for this channel */
    System_Buffer      *queMem[SYNTHESIS_LINK_MAX_LOCALQUEUELENGTH];
    /**< Queue memory */
} SynthesisLink_SysBufferQue;

/**
 *******************************************************************************
 *
 *   \brief Structure containing synthesis algorithm link specific parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    void                      * algHandle;
    /**< Handle of the algorithm */
    UInt32                      inPitch[SYSTEM_MAX_PLANES];
    /**< Pitch of the input video buffer, This is kept same for all channels */
    UInt32                      outPitch[SYSTEM_MAX_PLANES];
    /**< Pitch of output video frames */
    UInt32                      dataFormat;
    /**< Data format of the video to operate on */
    UInt32                      numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo           inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    AlgorithmLink_SynthesisCreateParams algLinkCreateParams;
    /**< Create params of the synthesis algorithm Link*/
    SV_Synthesis_CreationParamsStruct   algCreateParams;
    /**< Create params of the synthesis algorithm */
    SV_Synthesis_ControlParams  controlParams;
    /**< Control params of the synthesis algorithm */
    System_Buffer buffers[ALGLINK_SYNTHESIS_OPQID_MAXOPQ]
                         [SYNTHESIS_LINK_MAX_NUM_OUTPUT];
    /**< System buffer data structure to exchange buffers between links */
    System_VideoFrameBuffer videoFrames[SYNTHESIS_LINK_MAX_NUM_OUTPUT];
    /**< Payload for System buffers */
    System_MetaDataBuffer   photoAlignStats[SYNTHESIS_LINK_MAX_NUM_OUTPUT];
    /**< Payload for System buffers */
    System_MetaDataBuffer   opSgxBlendLUT[SYNTHESIS_LINK_MAX_NUM_OUTPUT];
    /**< Payload for System buffers */
    AlgorithmLink_OutputQueueInfo outputQInfo[ALGLINK_SYNTHESIS_OPQID_MAXOPQ];
    /**< All the information about output Queues used */
    AlgorithmLink_InputQueueInfo  inputQInfo[ALGLINK_SYNTHESIS_IPQID_MAXIPQ];
    /**< All the information about input Queues used */
    SynthesisLink_SysBufferQue localInputQ[ALGLINK_SYNTHESIS_IPQID_MAXIPQ];
    /**< Local Qs to hold input */
    UInt32                        frameDropCounter;
    /**< Counter to keep track of number of frame drops */
    System_Buffer                *sysBufferGALUT;
    /**< Place holder for the GA LUT sysBuffer. Only one will be held
     * inside Synthesis link at any point in time.
     */
    System_Buffer                *sysBufferBlendLUT;
    /**< Place holder for the Blend LUT sysBuffer. Only one will be held
     * inside Synthesis link at any point in time.
     */
    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */
    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
    Bool receivedGALUTFlag;
    /**< Flag to indicate if GA LUT has been received. At any point in time
     *   Synthesis link keeps only one copy of GA LUT. So no queue is used.
     *   Just a bool is used for tracking.
     */
    Bool isFirstOPGenerated;
    /**< Flag to indicate if first synthesized frame is generated. This flag
     *   can be used to control any special processing for first output
     *   frame.
     */
    UInt8 *pLinkStaticPALUT;
    /**< Ptr to Static array for first frame PA LUT input.
     */
    Bool isSGXBlendLUTOPGenerated;
    /**< Flag to indicate if first blend LUT is generated. This output
     *   need to be generated only once, same will be reused later
     */

} AlgorithmLink_SynthesisObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_synthesisProcess(void * pObj);
Int32 AlgorithmLink_synthesisControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_synthesisStop(void * pObj);
Int32 AlgorithmLink_synthesisDelete(void * pObj);
Int32 AlgorithmLink_synthesisPrintStatistics(void *pObj,
                       AlgorithmLink_SynthesisObj *pSynthesisObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
