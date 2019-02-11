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
 * \defgroup ALGORITHM_LINK_ADAPTIVEBOWL_API  Adaptive\
 * Bowl API
 *
 * \brief  This module has the interface for using Adaptive Bowl algorithm
 *
 *         Adaptive Bowl algorithm link -
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_adaptiveBowl.h
 *
 * \brief Algorithm Link API specific to adaptive bowl algorithm
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *          0.1 (Dec 2013) : [PS] Added support for Adaptive Bowl calibration support
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_ADAPTIVEBOWL_H_
#define ALGORITHM_LINK_ADAPTIVEBOWL_H_

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
    ALGLINK_ADAPTIVEBOWL_IPQID_MULTISENSOR = 0x0,
    /**< QueueId for multi-sensor images */

    ALGLINK_ADAPTIVEBOWL_IPQID_MAXIPQ = 0x1,
    /**< Maximum number of input queues */

    ALGLINK_ADAPTIVEBOWL_IPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_AdaptiveBowlInputQueId;

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
    ALGLINK_ADAPTIVEBOWL_OPQID_GASGXLUT = 0x0,
    /**< QueueId for SGX Adaptive Bowl LUT */

    ALGLINK_ADAPTIVEBOWL_OPQID_MAXOPQ = 0x1,
    /**< Maximum number of output queues */

    ALGLINK_ADAPTIVEBOWL_OPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_AdaptiveBowlOutputQueId;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Adaptive Bowl
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 calMatSize;
    /**< Size of calibaration matrix in bytes */
    void *                   calMatDDRPtr;
    /**< DDR pointer for calibration matrix */
} AlgorithmLink_AdaptiveBowlCalibrationParams;

/**
 *******************************************************************************
 * \brief Enum for input resolution mode
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_ADAPTIVE_INPUTRES_1MP = 0x0,
    /**< Input resolution is 1 MP */

    ALGLINK_ADAPTIVE_INPUTRES_2MP = 0x1,
    /**< Input resolution is 2 MP */

    ALGLINK_ADAPTIVE_INPUTRES_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_AdaptiveInputRes;

/**
 *******************************************************************************
 * \brief Enum for output resolution mode
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_ADAPTIVE_OUTPUTRES_1MP = 0x0,
    /**< Output resolution is 1 MP */

    ALGLINK_ADAPTIVE_OUTPUTRES_2MP = 0x1,
    /**< Output resolution is 2 MP */

    ALGLINK_ADAPTIVE_OUTPUTRES_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_AdaptiveOutputRes;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Adaptive Bowl
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    UInt32                   maxOutputHeight;
    /**< Max height of the output (stiched) frame */
    UInt32                   maxOutputWidth;
    /**< max width of the output (stiched) frame */
    UInt32                   maxInputHeight;
    /**< Max height of the input (captured) frame */
    UInt32                   maxInputWidth;
    /**< Max width of the input (captured) frame */
    UInt32                   numViews;
    /**< number of input views from which output will be synthesized */
    UInt32                   numOutputTables;
    /**< Number of output LUT tables. All the 3 LUT tables are considered
     * as one unit. numOutputTables defines number of such units.*/
    Int16                    carBoxWidth;
    /**< Width of the car box > */
    Int16                    carBoxHeight;
    /**< Height of the car box > */
    System_LinkOutQueParams  outQueParams[ALGLINK_ADAPTIVEBOWL_OPQID_MAXOPQ];
    /**< Output queue information */
    System_LinkInQueParams   inQueParams[ALGLINK_ADAPTIVEBOWL_IPQID_MAXIPQ];
    /**< Input queue information */
    AlgorithmLink_AdaptiveBowlCalibrationParams calParams;
    /**< Adaptive Bowl Calibration parameters */
    UInt32                  ignoreFirstNFrames;
    /**< The first set of frames received should be visible.
            In cases where Auto White balance is enabled and cannot grantee
            first good frame.
            Use this to configure the algorithm to skip, until valid frame is
            received. */
    UInt32                  defaultFocalLength;
    AlgorithmLink_AdaptiveOutputRes      inputRes;
    /**< Input resolution can be
         ALGLINK_ADAPTIVE_INPUTRES_1MP
         OR
         ALGLINK_ADAPTIVE_INPUTRES_2MP
     */
    AlgorithmLink_AdaptiveOutputRes     outputRes;
    /**< Input resolution can be
         ALGLINK_ADAPTIVE_OUTPUTRES_1MP
         OR
         ALGLINK_ADAPTIVE_OUTPUTRES_2MP
     */
    Int32 offsetXleft;
    /* left offset for adaptive bowl */
    Int32 offsetXright;
    /* right offset for adaptive bowl */
    Int32 offsetYfront;
    /* front offset for adaptive bowl */
    Int32 offsetYback;
    /* back offset for adaptive bowl */
    Void *pLensPrm;
    /**< Lens Parameters */
    Void *pLensPrm2D;
    /**< 2D Lens Parameters */
    /*<>*/
} AlgorithmLink_AdaptiveBowlCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Adaptive Bowl
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    Int32 offsetXleft;
    Int32 offsetXright;
    Int32 offsetYfront;
    Int32 offsetYback;
} AlgorithmLink_AdaptiveBowlControlParams;

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
 *        register plugins of Adaptive Bowl algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_adaptiveBowl_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
