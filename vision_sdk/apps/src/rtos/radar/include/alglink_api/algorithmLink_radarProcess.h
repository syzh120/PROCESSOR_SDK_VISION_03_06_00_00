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
 * \defgroup ALGORITHM_LINK_RADARPROCESS_API  Radar Process Plugin API
 *
 * \brief  This module has the interface for using Radar Process Plugin algorithm
 *
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_radarRadarProcess.h
 *
 * \brief Algorithm Link API specific to radar process plugin algorithm
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_RADARPROCESS_H_
#define ALGORITHM_LINK_RADARPROCESS_H_

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
/**
 *  \brief Control Command for being able to call the algorithm control
 *         function.
 */
#define ALGORITHM_LINK_RADAR_PROCESS_CONTROL_CMD        (0x6677U)

/** \brief Algorithm Function Name Length */
#define ALGORITHM_LINK_RADAR_PROCESS_ALG_FXN_NAME_LEN   (256U)


/** \brief Dont performan any cache ops */
#define ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE     (0x0000U)

/** \brief Do write back cache ops */
#define ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB       (0x0001U)

/** \brief Do invalidate cache ops */
#define ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_INV      (0x0002U)

/** \brief Do writeback and invalidate cache ops */
#define ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB_INV   (0x0003U)

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
 *   \brief Structure containing create time parameters for Frame copy algorithm
 *
 *          This structure is a replica of create time parameters of frame copy
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params */
    System_LinkOutQueParams  outQueParams;
    /**< Output queue information */
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */
    UInt32 numOutputBuffers;
    /**< Number of output buffers that is required by this algorithm plugin */
    char algFxnName[ALGORITHM_LINK_RADAR_PROCESS_ALG_FXN_NAME_LEN];
    /**< Name of the Algorithm functions that is to be used by the alg plugin */
} AlgorithmLink_RadarProcessCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure populated by the algorithm plugin function during create
 *
 *          This structure is used by the radar process alg plugin to allocate
 *          output buffers.
 *
 *******************************************************************************
*/
typedef struct
{
    System_BufferType outputBufferType;
    /**< Type of the output buffer given out by the algorithm */
    System_LinkChInfo outputChannelInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Output Channel info describing the buffer type to be given out
     *   by the algorithm.
     */
    UInt32  outputBufferSize[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Output Buffer Size. The Alg Plugin allocates memory
     *   based on this size */
     UInt32  metaBufSize[SYSTEM_MAX_CH_PER_OUT_QUE][SYSTEM_MAX_META_DATA_PLANES];
    /**< Output Metadata Buffer Size per Plane. The Alg Plugin allocates memory
     *   based on this size. */

     UInt32 inputBufCacheOps;
     /**< Cache operation to perform on input buffer
      * Default is Invalidate
      * Bit mask of values ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_xxx
      */

     UInt32 outputBufCacheOps;
     /**< Cache operation to perform on output buffer
      * Default is Writeback
      * Bit mask of values ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_xxx
      */

     UInt32 numMetaDataPlanes;
     /**< Number of Data Planes in Output Metadata Buffer. The Alg Plugin
      *   allocates number of Metadata buffers based on this value.
      *   Maximum number of data planes is 4.*/
     UInt32 numOutputCh;
     /**< Number of output channels that the processing link would generate */
} AlgorithmLink_RadarProcessAlgCreateOpParams;

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
    UInt32 controlCmd;
    /**< Control Command */
} AlgorithmLink_RadarProcessControlParams;

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
static inline void AlgorithmLink_RadarProcess_Init(
    AlgorithmLink_RadarProcessCreateParams *pPrm)
{
    memset(pPrm, 0, sizeof(AlgorithmLink_RadarProcessCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmLink_RadarProcessCreateParams);
    /* This is a default algId provided. As a part of the automated usecase
     * generation flow the alg Id will be updated based on which processor the
     * alg is instantiated for.
     * This is done in the <usecase_name>_SetPrms autogenerated function.
     * Do not update this function for the algId.
     */
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_RADAR_PROCESS;
    pPrm->numOutputBuffers = 2U;
}
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
Int32 AlgorithmLink_RadarProcess_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */

