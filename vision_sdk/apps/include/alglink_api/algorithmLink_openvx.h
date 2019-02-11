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
 * \defgroup ALGORITHM_LINK_OPENVX_API OpenVX API
 *
 * \brief  This module has the interface for using openvx algorithm
 *
 *         OpenVX is a sample algorithm, which just performs canny
 *         edge detection on input buffer
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_openvx.h
 *
 * \brief Algorithm Link API specific to openvx algorithm on DSP
 *
 * \version 0.0 (Feb 2017) : [BJ] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_OPENVX_H_
#define ALGORITHM_LINK_OPENVX_H_

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

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing harris corners parameters
 *
 *******************************************************************************
*/
typedef struct
{
    Float   strength_thr;
    /**< Threshold threshold for HC */
    Float   min_dist;
    /**< Minimum Distances for HC */
    Float   sensitivity;
    /**< Sensitivity for HC */
    UInt32  grad_size;
    /**< Gradient Size for HC */
    UInt32  block_size;
    /**< Maximum block size for HC */
    UInt32  max_corners;
    /**< Maxinum number of corners to be detected for HC */
} AlgorithmLink_OpenVxHcParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for OpenVx algorithm
 *
 *          This structure is a replica of create time parameters of openvx
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams      baseClassCreate;
    /**< Base class create params */
    UInt32                          numOutputFrames;
    /**< Number of output frames to be created for this link per channel*/
    System_LinkOutQueParams         outQueParams;
    /**< Output queue information */
    System_LinkInQueParams          inQueParams;
    /**< Input queue information */
    AlgorithmLink_OpenVxHcParams    hcPrms;
} AlgorithmLink_OpenVxCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for openvx algorithm
 *
 *          This structure is a replica of control parameters of openvx
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_openvxControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
 static inline void AlgorithmLink_OpenVx_Init(
                            AlgorithmLink_OpenVxCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_OpenVx_Init(
                            AlgorithmLink_OpenVxCreateParams *pPrm)
{
    memset(pPrm, 0, sizeof(AlgorithmLink_OpenVxCreateParams));
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of openvx algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_OpenVx_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
