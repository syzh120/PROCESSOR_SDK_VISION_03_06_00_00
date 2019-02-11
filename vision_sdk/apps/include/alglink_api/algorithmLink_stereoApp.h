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
 * \defgroup ALGORITHM_LINK_SENSE_AVOID_API  Sense And Avoid \
 *           Algo APIs
 *
 * \brief  This module has the interface for using sense and avoid algorithm
 *
 *         Sense and Avoid algorithm link -
 *           -# Will take in 3D point cloud from multiple stereo pairs and generate
 *              occupancy grid and movement vector
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_stereoApp.h
 *
 * \brief Algorithm Link API specific to stereo application algorithm
 *
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_STEREOAPP_H_
#define ALGORITHM_LINK_STEREOAPP_H_

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
    ALGLINK_STEREOAPP_IPQID_DISPARITY = 0x0,
    /**< QueueId for multiview images */

    ALGLINK_STEREOAPP_IPQID_MAXIPQ = 0x1,
    /**< Maximum number of input queues */

    ALGLINK_STEREOAPP_IPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} AlgorithmLink_StereoAppInputQueId;

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
    ALGLINK_STEREOAPP_OPQID_PCL = 0x0,
    /**< QueueId for point cloud output */

    ALGLINK_STEREOAPP_OPQID_OGMAP = 0x1,
    /**< QueueId for occupancy grid output */

    ALGLINK_STEREOAPP_OPQID_MV = 0x2,
    /**< QueueId for Motion Vector output */

    ALGLINK_STEREOAPP_OPQID_MAXOPQ = 0x3,
    /**< Maximum number of output queues */

    ALGLINK_STEREOAPP_OPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_StereoAppOutputQueId;


/**
 *******************************************************************************
 * \brief Enum for mode of stereo app algorithm
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_STEREOAPP_DETECT_CLOSE_OBJECT = 0x0,
    /**< detect close object only */

    ALGLINK_STEREOAPP_DETECT_OBJECT_WITHOUT_MOTION_SEARCH = 0x1,
    /**< detect objects without motion search */

    ALGLINK_STEREOAPP_DETECT_OBJECT_WITH_MOTION_SEARCH = 0x2,
    /**< detect objects with motion search */

    ALGLINK_STEREOAPP_OBJECT_DETECT_MODE_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} AlgorithmLink_StereoAppObjectDetectMode;


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Stereo App algorithm
 *
 *
 *******************************************************************************
*/
typedef struct
{
    float baseline;
    float scale_x;
    float scale_y;
    float dc_x;
    float dc_y;
    float ofst_x;
    float ofst_y;
    float f;
    float calmat[12];
} AlgorithmLink_StereoAppParams;


/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Stereo App algorithm
 *
 *
 *******************************************************************************
*/
typedef struct
{
    UInt8                      useDispRoiForPCL;
    /**< whether ROI is used to generate PCL from disparity */
    Int16                      dispRoiStartX;
    /**< Disparity ROI start X */
    Int16                      dispRoiStartY;
    /**< Disparity ROI start Y */
    Int16                      dispRoiWidth;
    /**< Disparity ROI width */
    Int16                      dispRoiHeight;

} AlgorithmLink_StereoAppDispRoiParams;
/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Stereo App algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    UInt32                     maxInputHeight;
    /**< Max height of the input (captured) frame */
    UInt32                     maxInputWidth;
    /**< Max width of the input (captured) frame */
    UInt32                     numPairs;
    /**< number of input stereo pairs from which disparity map is provided */
    UInt32                     numOutputBuffers;
    /**< number of outputs buffer */
    UInt8                      bDataStreaming;
    /**< whether PCL and OGMap will be streaming into host */
    UInt8                      bSenseAvoid;
    /**< specify whether the algorithm link is used for SAA */
    UInt8                      objectDetectMode;
    /**< motion search method for sense and avoid */

    System_LinkOutQueParams    outQueParams[ALGLINK_STEREOAPP_OPQID_MAXOPQ];
    /**< Output queue information */
    System_LinkInQueParams     inQueParams[ALGLINK_STEREOAPP_IPQID_MAXIPQ];
    /**< Input queue information */

    AlgorithmLink_StereoAppParams saParams;
    /**< Stereo app parameters */
    AlgorithmLink_StereoAppDispRoiParams dispRoiParams;
    /**< Disparity ROI parameters */

} AlgorithmLink_StereoAppCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Stereo App algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_StereoAppControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_StereoApp_Init(
    AlgorithmLink_StereoAppCreateParams *pPrm)
{

}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of stereo app algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoApp_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
