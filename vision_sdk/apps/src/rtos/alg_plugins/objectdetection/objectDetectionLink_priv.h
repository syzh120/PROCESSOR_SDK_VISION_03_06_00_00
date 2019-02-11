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
 * \file objectDetectionLink_priv.h Object Detection Algorithm Link
 *       private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef _OBJECTDETECTION_LINK_PRIV_H_
#define _OBJECTDETECTION_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_objectDetection.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/alg_plugins/common/include/alg_ivision.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include "iobjdet_ti.h"
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
 *   \brief Max number of buffers
 *
 *   Feature Plane Classification alg takes an input frame from feature plane
 *   computation link and generates an output buffer which is a meta data
 *   buffer. This macro defines the maximum number of such buffers this
 *   link can handle
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OBJECTDETECTION_LINK_MAX_NUM_OUTPUT    (8)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing feature plane Classification algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    Void *handle;
    /**< Handle to the algorithm */
    AlgorithmLink_ObjectDetectionCreateParams algLinkCreateParams;
    /**< Create params of feature plane Classification algorithm link */
    TI_OD_CreateParams algCreateParams;
    /**< Create parameters for the algorithm */
    TI_OD_InArgs inArgs;
    /**< inArgs for the algorithm */
    TI_OD_OutArgs   outArgs;
    /**< outArgs for the algorithm */
    IVISION_InBufs    inBufs;
    /**< input buffers for the algorithm */
    IVISION_OutBufs   outBufs;
    /**< output buffers for the algorithm */
    IVISION_BufDesc   inBufDesc;
    /**< input buffer descriptor */
    IVISION_BufDesc   outBufDesc[TI_OD_OUT_BUFDESC_TOTAL];
    /**< output buffer descriptor */
    IVISION_BufDesc   *inBufDescList[TI_OD_IN_BUFDESC_TOTAL];
    /**< list of input buffer descriptors */
    IVISION_BufDesc   *outBufDescList[TI_OD_OUT_BUFDESC_TOTAL];
    /**< list of input buffer descriptors */
    System_Buffer buffers[OBJECTDETECTION_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */
    System_MetaDataBuffer odOutput[OBJECTDETECTION_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers */
    UInt32  outBufferSize;
    /**< Size of each output buffer */
    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Queue*/
    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Queue*/
    UInt32                        frameDropCounter;
    /**< Counter to keep track of number of frame drops */
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
} AlgorithmLink_ObjectDetectionObj;


typedef struct {

    TI_OD_outputList  objectList;
    TI_OD_outputList  detectionList;

} AlgorithmLink_ObjectDetectionOutput;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_objectDetectionCreate(void * pObj,
                                              void * pCreateParams);
Int32 AlgorithmLink_objectDetectionProcess(void * pObj);
Int32 AlgorithmLink_objectDetectionControl(void * pObj,
                                               void * pControlParams);
Int32 AlgorithmLink_objectDetectionStop(void * pObj);
Int32 AlgorithmLink_objectDetectionDelete(void * pObj);
Int32 AlgorithmLink_objectDetectionPrintStatistics(void *pObj,
                AlgorithmLink_ObjectDetectionObj *pObjectDetectionObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
