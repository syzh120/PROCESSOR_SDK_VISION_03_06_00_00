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
 * \defgroup ALGORITHM_LINK_SUBFRAME_COPY_API  Sub Frame Copy API
 *
 * \brief  This module has the interface for using subframe copy alg plugin
 *
 *         Subframe copy is a sample algorithm, which just copies subframe from
 *         input to output buffer. The input buffer is in OCMC region and
 *         allocated by M4 capture driver. The Plugin registers an interrupt
 *         on VIP for subframe and frame complete events.
 *         The Link has a single output queue and single channel support
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_subframeCopy.h
 *
 * \brief Algorithm Link API specific to subframe copy algorithm on EVE
 *
 * \version 0.0 (Jul 2014) : [VT] First version
 *
 *******************************************************************************
 */

#ifndef ALGLINK_SUBFRAME_COPY_H_
#define ALGLINK_SUBFRAME_COPY_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/captureLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 * \brief Max number of output queue
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SUBFRAME_COPY_LINK_MAX_NUM_OUT_QUE                                  (1)

/**
 *******************************************************************************
 *
 * \brief Max Channels per output queue
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SUBFRAME_COPY_LINK_MAX_CH_PER_OUT_QUE                               (1)


/**
 *******************************************************************************
 *
 * \brief Indicates number of output buffers to be set to default
 *         value by the Subframe Process link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SUBFRAME_COPY_LINK_NUM_BUFS_PER_CH_DEFAULT                          (4)


/* @} */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


/**
 *******************************************************************************
 * \brief Subframe Process link configuration parameters.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams      baseClassCreate;

    UInt32                          numBufs;
    /**< Number of buffers to be allocated for the Subframe Process link. Min
     *   number of buffers required is 4 for Subframe Process link to capture
     *   without frame drops
     */

    UInt32                          inChannelId;
    /**<This is the channel ID in input queue which this alg plugin processes */

    System_LinkOutQueParams         outQueParams;
    /**< Output queue information */

    System_LinkInQueParams          inQueParams;
    /**< link input queue information */

} AlgorithmLink_SubframeCopyCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for subframe copy algorithm
 *
 *          Ideally subframe copy should not have any control cmds in running
 *          state, as this will make the link process subframe slower leading
 *          to corruption.
 *          This data structure is added as Base class implementation of alg
 *          plugin expects it.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_SubframeCopyControlParams;

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
 *        register plugins of sub frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopy_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
