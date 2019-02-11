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
 * \ingroup  ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_FRAMECOPY_API  Frame Copy API
 *
 * \brief  This module has the interface for using frame copy algorithm
 *
 *         Frame copy is a sample algorithm, which just copies a frame from
 *         input to output buffer.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_frameCopy.h
 *
 * \brief Algorithm Link API specific to frame copy algorithm on DSP
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_STITCHING_H_
#define ALGORITHM_LINK_STITCHING_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ALGORITHM_LINK_MAX_VIEWS      (3U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the algorithms supported on DSP.
 *
 *          Method of copying frame
 *
 *******************************************************************************
*/
typedef enum
{
    //ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW = 0,
    ALGLINK_STITCHING_IPQID_MULTIVIEW_RAW = 0,
	ALGLINK_STITCHING_IPQID_BLENDLUT = 1,
    /**< QueueId for multiview images */
    ALGLINK_STITCHING_IPQID_MAXIPQ = 2,
    /**< Maximum number of input queues */
    ALGLINK_STITCHING_IPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
} AlgorithmLink_StitchingInputQueId;

typedef enum
{

    /**< QueueId for disparity images */
    ALGLINK_STITCHING_OPQID_DISPARITY_TRANSFORMED = 0,
    /**< QueueId for multiview images */
    ALGLINK_STITCHING_OPQID_MAXOPQ = 1,
    /**< Maximum number of output queues */
    ALGLINK_STITCHING_OPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
}AlgorithmLink_StitchingOutputQueId;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Synthesis algorithm
 *
 *          This structure is a replica of create time parameters of synthesis
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    // Connects to chains_common
    AlgorithmLink_CreateParams  baseClassCreate;

    UInt32            maxInputHeight;
    UInt32            maxInputWidth;

    UInt32            maxOutputHeight;
    UInt32            maxOutputWidth;

    UInt32            numCameras;
    UInt32            dataFormat;
    UInt32            numOutBuffers;
    unsigned char     stitchingMode;

    System_LinkOutQueParams outQueParams[ALGLINK_STITCHING_OPQID_MAXOPQ];
    System_LinkInQueParams  inQueParams[ALGLINK_STITCHING_IPQID_MAXIPQ];

} AlgorithmLink_StitchingCreateParams;
/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Frame copy algorithm
 *
 *          This structure is a replica of control parameters of frame copy
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_StitchingControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_Stitching_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
