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
 * \file sceneObstructionDetectLink_priv.h Scene Obstruction Detect Algorithm Link private
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

#ifndef _SCENE_OBSTRUCTION_DETECT_LINK_PRIV_H_
#define _SCENE_OBSTRUCTION_DETECT_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_sceneObstructionDetect.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include "iSceneObstructionDetect_ti.h"
#include <src/rtos/alg_plugins/common/include/alg_ivision.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *   \brief Max number of buffers
 *******************************************************************************
 */
#define SCENE_OBSTRUCTION_DETECT_LINK_MAX_NUM_OUTPUT    (3)


/**
 *******************************************************************************
 *   \brief Max number of input channels
 *******************************************************************************
 */
#define SCENE_OBSTRUCTION_DETECT_LINK_MAX_CH            (4)

/**
 *******************************************************************************
 *   \brief Max size of Scene obstruction detect results
 *******************************************************************************
 */
#define SCENE_OBSTRUCTION_DETECT_LINK_MAX_BUF_SIZE      (SystemUtils_align(4, 128))


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing scene detection algorithm link specific parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    Void         * algHandle;
    /**< Handle of the algorithm */
    UInt32                      numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo           inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    AlgorithmLink_SceneObstructionDetectCreateParams algLinkCreateParams;
    /**< Create params of the frame copy algorithm Link*/
    SCENE_OBSTRUCTION_DETECT_TI_CreateParams   createParams;
    /**< Create parameters for the algorithm */
    IVISION_InArgs                      inArgs;
    /**< inArgs for the algorithm */
    IVISION_OutArgs                   outArgs;
    /**< outArgs for the algorithm */
    IVISION_InBufs                      inBufs;
    /**< input buffers for the algorithm */
    IVISION_OutBufs                     outBufs;
    /**< output buffers for the algorithm */
    IVISION_BufDesc                     inBufDesc;
    /**< input buffer descriptor */
    IVISION_BufDesc                     outBufDesc;
    /**< output buffer descriptor */
    IVISION_BufDesc                     *inBufDescList[SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_IN_TOTAL];
    /**< list of input buffer descriptors */
    IVISION_BufDesc                 *outBufDescList[SCENE_OBSTRUCTION_DETECT_TI_BUFDESC_OUT_TOTAL];
    /**< list of input buffer descriptors */
    System_Buffer buffers[SCENE_OBSTRUCTION_DETECT_LINK_MAX_CH*SCENE_OBSTRUCTION_DETECT_LINK_MAX_NUM_OUTPUT];
    /**< System buffer data structure to exchange buffers between links */
    System_MetaDataBuffer metaDataBuffers[SCENE_OBSTRUCTION_DETECT_LINK_MAX_CH*SCENE_OBSTRUCTION_DETECT_LINK_MAX_NUM_OUTPUT];
    System_LinkQueInfo inQueInfo;
    /**< Payload for the meta buffers */
    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Q */
    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Q */
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
   Bool sceneObstructionState;
    /**< Flag to indicate whether the scene is currently obstructed 
        TRUE: scene is obstructed
        FALSE: scene is not obstructed
        */
} AlgorithmLink_SceneObstructionDetectObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_sceneObstructionDetectCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_sceneObstructionDetectProcess(void * pObj);
Int32 AlgorithmLink_sceneObstructionDetectControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_sceneObstructionDetectStop(void * pObj);
Int32 AlgorithmLink_sceneObstructionDetectDelete(void * pObj);
Int32 AlgorithmLink_sceneObstructionDetectPrintStatistics(void *pObj,
                       AlgorithmLink_SceneObstructionDetectObj *pSceneObstructionDetectObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
