/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/*==========================================================================*/
/**
 *  @file:      block_statistics_graph_int.h
 *
 *  @brief:     This file defines the functions for block statistics graph
 *
 *  @version:   0.2 (Aug 2014) : Base version.
 */
/*==========================================================================*/

#ifndef BLOCK_STATS_GRAPH_INT_H
#define BLOCK_STATS_GRAPH_INT_H

#include <xdais_types.h>
#include <ivision.h>

#include "algframework.h"
#include "bam_common.h"

#include "iblock_statistics_ti.h"
#include "bam_block_statistics.h"
#include "edma_utils_autoincrement.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BLOCK_STATS_GRAPH_OBJ_SIZE             (3132U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BLOCK_STATS_GRAPH_SCRATCH_SIZE         (1040U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BLOCK_STATS_GRAPH_CONTEXT_SIZE         (4U)

/**
 * Additional BAM error codes specific to Block Statistics.
 */
#define BLOCK_STATS_BAM_E_CUSTOMFAILEND             (-1024)    /**< BLOCK STATISTICS BAM custom error code end */


/*--------------------------------------------------------------------*/
/**
  @struct BLOCK_STATS_TI_graphConstructParams
  @brief  This structure specifies the properties needed for constructing
          block statistics graph

  @param  imageWidth       Width in pixels of the input image
  @param  imageHeight      Height of the input image
  @param  statBlockWidth   Width of the block over which statistics is
                           computed
  @param  statBlockHeight  Height of the block over which statistics
                           is computed
 */
typedef struct
{
  uint16_t    imageWidth;
  uint16_t    imageHeight;
  uint16_t    statBlockWidth;
  uint16_t    statBlockHeight;
} BLOCK_STATS_TI_graphCreateParams;

/*--------------------------------------------------------------------*/
/**
  @struct BLOCK_STATS_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs      Parameters for DMA node
  @param  blockStatKernelArgs    Parameters for block statistics kernel
  @param  dmaWriteKernelArgs     Parameters for DMA SINK node
  @param  createParams           Creation time parameters
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
  BAM_Block_Statistics_Args          blockStatKernelArgs;
  EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
  BLOCK_STATS_TI_graphCreateParams *createParams;
} BLOCK_STATS_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 for graph
 *  @pre           BLOCK_STATS_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_graphCreate(const BAM_GraphMem * graphMem,
            BLOCK_STATS_TI_graphCreateParams* createParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BLOCK_STATS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs    : Pointer to graph memory structure
 *  @param [in]    outArgs   : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_execute(BAM_GraphMem *graphMem,
           const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_dmaControl
 *  @brief         This function can be called after the graph is created and
 *                 before BLOCK_STATS_TI_execute() to control the source and
 *                 sink node's parameters.
 *  @pre           BLOCK_STATS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem   : Pointer to graph memory structure
 *  @param [in]    inBufDesc  : Pointer to input buffer's descriptions
 *  @param [in]    outMinBufDesc  : Pointer to minimum buffer's descriptions
 *  @param [in]    outMaxBufDesc  : Pointer to maximum buffer's descriptions
 *  @param [in]    outMeanBufDesc : Pointer to mean buffer's descriptions
 *  @param [in]    outVarBufDesc  : Pointer to variance buffer's descriptions
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_dmaControl(const BAM_GraphMem *graphMem,
           const IVISION_BufDesc *inBufDesc,
           const IVISION_BufDesc *outMinBufDesc,
           const IVISION_BufDesc *outMaxBufDesc,
           const IVISION_BufDesc *outMeanBufDesc,
           const IVISION_BufDesc *outVarBufDesc);
#endif
