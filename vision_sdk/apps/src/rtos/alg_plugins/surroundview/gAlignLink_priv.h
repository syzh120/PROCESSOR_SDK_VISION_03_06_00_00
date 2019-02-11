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
 * \file gAlignLink_priv.h Geometric Alignment Algorithm Link private
 *                            API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef _GALIGN_LINK_PRIV_H_
#define _GALIGN_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_geometricAlignment.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_que.h>
#include "./include/iGeometricAlignmentAlgo.h"
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
 *   \brief Max number of output LUT tables
 *
 *   GA generates three tables - Simple stitch LUT, Blend LUT1, Blend LUT2.
 *   All the three are considered together as one unit. This macro defines
 *   number of such units.
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GALIGN_LINK_MAX_NUM_OUTPUT (8)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing geometric alignment algorithm link parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    void                      * algHandle;
    /**< Handle of the algorithm */
    UInt32                      dataFormat;
    /**< Data format of the video to operate on */
    UInt32                      inPitch[SYSTEM_MAX_PLANES];
    /**< Pitch of the input video buffer, support only YUV420 Data format */
    UInt32                      numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo           inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    AlgorithmLink_GAlignCreateParams             algLinkCreateParams;
    /**< Create params of the geometric alignment algorithm Link*/
    SV_GAlign_CreationParamsStruct               algCreateParams;
    /**< Create params of the geometric alignment algorithm */
    SV_GAlign_ControlParams                      controlParams;
    /**< Control params of the geometric alignment algorithm */
    System_Buffer buffers[ALGLINK_GALIGN_OPQID_MAXOPQ]
                         [GALIGN_LINK_MAX_NUM_OUTPUT];
    /**< System buffer data structure to exchange buffers between links */
    System_MetaDataBuffer   gAlignLUT[ALGLINK_GALIGN_OPQID_MAXOPQ]
                                     [GALIGN_LINK_MAX_NUM_OUTPUT];

    System_VideoFrameCompositeBuffer gAlignCompLut[GALIGN_LINK_MAX_NUM_OUTPUT];
    /**< Composite output buffer for LDC Lut */

    /**< Payload for System buffers */
    AlgorithmLink_OutputQueueInfo outputQInfo[ALGLINK_GALIGN_OPQID_MAXOPQ];
    /**< All the information about output Queues used */
    AlgorithmLink_InputQueueInfo  inputQInfo[ALGLINK_GALIGN_IPQID_MAXIPQ];
    /**< All the information about input Queues used */
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
    Bool isFirstOPGenerated;
    /**< Flag to indicate if first output is generated. This flag
     *   can be used to control any special processing for first time
     */
} AlgorithmLink_GAlignObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_gAlignCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_gAlignProcess(void * pObj);
Int32 AlgorithmLink_gAlignControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_gAlignStop(void * pObj);
Int32 AlgorithmLink_gAlignDelete(void * pObj);
Int32 AlgorithmLink_gAlignPrintStatistics(void *pObj,
                       AlgorithmLink_GAlignObj *pGeometricAlignmentObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
