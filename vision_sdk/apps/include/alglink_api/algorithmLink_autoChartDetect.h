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
 * \defgroup ALGORITHM_LINK_AUTO_CHART_DETECT_API  Auto Chart Detection \
 *           Algo APIs
 *
 * \brief  This module has the interface for using automatic chart detection algorithm
 *
 *         Automatic Chart Detect algorithm link -
 *           -# Will take in images from multiple views and generate
 *              feature points, which will get used by the pose estimation

 *           -# Will call the algorithm process function once in K frames.
 *              For the remaining (K-1) frames, the link shall immediately
 *              release back the input video buffers.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_autoChartDetect.h
 *
 * \brief Algorithm Link API specific to automatic chart detection algorithm
 *
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_AUTOCHARTDETECT_H_
#define ALGORITHM_LINK_AUTOCHARTDETECT_H_

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

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enum for the input Q IDs
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_ACDETECT_IPQID_MULTIVIEW = 0x0,
    /**< QueueId for multiview images */

    ALGLINK_ACDETECT_IPQID_MAXIPQ = 0x1,
    /**< Maximum number of input queues */

    ALGLINK_ACDETECT_IPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} AlgorithmLink_ACDetectInputQueId;

/**
 *******************************************************************************
 * \brief Enum for the output Q IDs
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_ACDETECT_OPQID_FEATURE = 0x0,
    /**< QueueId for feature points output */

    ALGLINK_ACDETECT_OPQID_MAXOPQ = 0x1,
    /**< Maximum number of output queues */

    ALGLINK_ACDETECT_OPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_ACDetectOutputQueId;

/**
 *******************************************************************************
 * \brief Enum for mode of automatic chart detection
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_ACDETECT_MODE_SKIP = 0x0,
    /**< skip automatic chart detection */

    ALGLINK_ACDETECT_MODE_ENABLE = 0x1,
    /**< use automatic chart detection  */

    ALGLINK_ACDETECT_MODE_DEFAULT = 0x2,
    /**< Use default feature locations */

    ALGLINK_ACDETECT_MODE_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_ACDetectMode;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Automatic Chart
 *          Detect algorithm
 *
 *******************************************************************************
*/
typedef struct
{
	AlgorithmLink_ACDetectMode  acDetectMode;
    /**< automatic chart detection mode to be used */

    void *                   featurePtDDRPtr;
    /**< DDR pointer for feature pts */
} AlgorithmLink_ACDetectParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Automatic Chart
 *          Detect algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    UInt32                   maxInputHeight;
    /**< Max height of the input (captured) frame */
    UInt32                   maxInputWidth;
    /**< Max width of the input (captured) frame */
    UInt32                   numViews;
    /**< number of input views from which feature points will be detected */
    UInt32                   numOutput;
    /**< Number of output feature points */
    System_LinkOutQueParams  outQueParams[ALGLINK_ACDETECT_OPQID_MAXOPQ];
    /**< Output queue information */
    System_LinkInQueParams   inQueParams[ALGLINK_ACDETECT_IPQID_MAXIPQ];
    /**< Input queue information */
    AlgorithmLink_ACDetectParams acDetectParams;
    /**< Automatic Chart Detect parameters */
    UInt32                  ignoreFirstNFrames;
    /**< The first set of frames received should be visible.
            In cases where Auto White balance is enabled and cannot grantee
            first good frame.
            Use this to configure the algorithm to skip, until valid frame is
            received. */
    UInt32                  defaultFocalLength;
    /**< Focal length of the lens used */

    Void *pLensPrm;
    /**< Lens Parameters */

    Bool is2mp;
    /**< Flag to show whether it is 2MP SRV or not */

} AlgorithmLink_ACDetectCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Automatic Chart Detect
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_ACDetectControlParams;

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
 *        register plugins of automatic chart detect algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_acDetect_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
