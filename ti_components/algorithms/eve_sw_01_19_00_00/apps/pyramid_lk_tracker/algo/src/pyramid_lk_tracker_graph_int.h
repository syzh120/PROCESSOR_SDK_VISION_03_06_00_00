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


/**
 *  @file       pyramid_lk_tracker_graph_int.h
 *
 *  @brief      This file defines the interface for pyramid_lk_tracker graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef PYRAMID_LK_TRACKER_TI_GRAPH_INT_H
#define PYRAMID_LK_TRACKER_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "algframework.h"
#include "bam_common.h"
#include "bam_lk_iterative_loop.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"
#include "bam_pyramid_lk_tracker_dma_node.h"
#include "pyramid_lk_tracker_alg_int.h"
#include "bam_weight_computation.h"
#include "bam_multiblock_gradient_xy.h"
#include "bam_multiblock_bilinear_interp_intlv_7x7_s16.h"
#include "bam_multiblock_bilinear_interp_7x7_u8.h"
#include "bam_tensor_matrix_7x7_s16_grad.h"
#include "bam_calc_determinant_tensor_matrix.h"
#include "bam_calc_inverse_structure_tensor_2x2.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define LK_TRACKER_GRAPH_OBJ_SIZE             (9652)

/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define LK_TRACKER_GRAPH_SCRATCH_SIZE         (2028 )

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define LK_TRACKER_GRAPH_CONTEXT_SIZE         (9442)

#define LK_IMGBUFF_INPUT_MEM_SIZE             (16*1024)

#define VCOP_LK_PATCH_WIDTH                   (7)
/*--------------------------------------------------------------------*/
/**
  @struct LK_TRACKER_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  lkiterativeloopArgs        Parameters for lkiterativeloop kernel
  @param  createParams              Creation time parameters
*/
typedef struct
{
  EDMA_UTILS_pyramidlktracker_dmaReadInitParam             dmaReadKernelArgs ;
  EDMA_UTILS_autoIncrement_initParam                       dmaWriteKernelArgs;
  BAM_Weight_Computation_Args                              wgtCompArgs       ;
  BAM_Multiblock_Gradient_XY_Args                          gradXYArgs        ;
  BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args        biLinIntp16Args   ;
  BAM_Multiblock_Bilinear_Interp_7x7_U8_Args               biLinIntpU8Args   ;
  BAM_Tensor_Matrix_7x7_S16_Grad_Args                      tensorMatArgs     ;
  BAM_Calc_Determinant_Tensor_Matrix_Args                  detMatArgs        ;
  BAM_Calc_Inverse_Structure_Tensor_2x2_Args               invMatArgs        ;
  BAM_LK_Iterative_Loop_Args                               lkIterativeLoopArgs;
  const PYRAMID_LK_TRACKER_TI_CreateParams                      *createParams;
  uint16_t                                                *prevXYList;
  uint16_t                                                *currXYList;
  uint32_t                                                *dmaCtrlArgs;
  uint32_t                                                *kernelCtrlArgs;
} LK_TRACKER_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_pyramid_lk_tracker
 *  @func          LK_TRACKER_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t LK_TRACKER_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_pyramid_lk_tracker
 *  @func          LK_TRACKER_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           PYRAMID_LK_TRACKER_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t LK_TRACKER_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                            const PYRAMID_LK_TRACKER_TI_CreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_pyramid_lk_tracker
 *  @func          LK_TRACKER_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           PYRAMID_LK_TRACKER_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t LK_TRACKER_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

int32_t LK_TRACKER_TI_bamControl(const BAM_GraphMem *graphMem,
                                 EDMA_UTILS_pyramidlktracker_dma_ctrl_args *bam_ctrl_args);
uint8_t LK_TRACKER_TI_FindNumKeyPointsPerCall(
        uint16_t blkWidth,
        uint16_t blkHeight);

uint8_t LK_TRACKER_TI_FindMaxSearchRange(
        const uint8_t    searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS],
        uint8_t    numLevels);

#endif
