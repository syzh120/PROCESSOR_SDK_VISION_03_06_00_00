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

#ifndef _IMAGETRANSFORM_LINK_PRIV_H_
#define _IMAGETRANSFORM_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
 
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_imageTransform.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_que.h>
#include "./include/iImageTransformAlgo.h"
#include <src/rtos/utils_common/include/utils_link_stats_if.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
 
#define IMAGETRANSFORM_LINK_MAX_LOCALQUEUELENGTH (40)
#define IMAGETRANSFORM_LINK_MAX_NUM_OUTPUT (16)
/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
typedef struct {
    Utils_QueHandle    queHandle;
    /**< Handle to the queue for this channel */
    System_Buffer      *queMem[IMAGETRANSFORM_LINK_MAX_LOCALQUEUELENGTH];
    /**< Queue memory */
} ImageTransformLink_SysBufferQue;
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
    
    UInt32                      inputPitch[SYSTEM_MAX_PLANES];
    UInt32                      outputPitch[SYSTEM_MAX_PLANES];
    
    System_LinkChInfo           inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    System_LinkChInfo           outputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];

	////////////////////////////////////////////////////////////////////
    AlgorithmLink_ImageTransformCreateParams             algLinkCreateParams;
     
    RVP_ImageTransform_CreationParamsStruct               algCreateParams;
    
    RVP_ImageTransform_ControlParams                      controlParams;
    
    ////////////////////////////////////////////////////////////////////
     
    System_Buffer buffers[ALGLINK_IMAGETRANSFORM_OPQID_MAXOPQ][IMAGETRANSFORM_LINK_MAX_NUM_OUTPUT];

    System_VideoFrameBuffer videoFrames[IMAGETRANSFORM_LINK_MAX_NUM_OUTPUT];                                
	System_VideoFrameCompositeBuffer videoCompositeFrames[IMAGETRANSFORM_LINK_MAX_NUM_OUTPUT];                                
	
	ImageTransformLink_SysBufferQue localInputQ[ALGLINK_IMAGETRANSFORM_IPQID_MAXIPQ];
	
    AlgorithmLink_OutputQueueInfo outputQInfo[ALGLINK_IMAGETRANSFORM_OPQID_MAXOPQ]; 
    AlgorithmLink_InputQueueInfo  inputQInfo[ALGLINK_IMAGETRANSFORM_IPQID_MAXIPQ]; 


	System_Buffer                *sysBufferDisparity;
	Bool receivedDisparityFlag;
	////////////////////////////////////////////////////////////////////
	
    System_LinkStatistics   *linkStatsInfo;
	
    Bool isFirstFrameRecv;
    
    Bool isFirstOPGenerated;

	////////////////////////////////////////////////////////////////////

	float *pInputCalibParams;
	
	Byte imageTransformMode;
	
} AlgorithmLink_ImageTransformObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_ImageTransformCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_ImageTransformProcess(void * pObj);
Int32 AlgorithmLink_ImageTransformControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_ImageTransformStop(void * pObj);
Int32 AlgorithmLink_ImageTransformDelete(void * pObj);
Int32 AlgorithmLink_ImageTransformPrintStatistics(void *pObj,
                       AlgorithmLink_ImageTransformObj *pImageTransformObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
