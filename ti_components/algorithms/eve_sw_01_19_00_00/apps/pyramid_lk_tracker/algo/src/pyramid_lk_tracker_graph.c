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
 *  @file      pyramid_lk_tracker_graph.c
 *
 *  @brief      This file defines the functions for pyramid_lk_tracker graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "pyramid_lk_tracker_graph_int.h"
#include "ipyramid_lk_tracker_ti.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"

static int32_t LK_TRACKER_TI_initKernelsArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);
static void assignDMAautoIncrementParams(
  EDMA_UTILS_autoIncrement_transferProperties * param,
  uint16_t    roiWidth,
  uint16_t    roiHeight,
  uint16_t    blkWidth,
  uint16_t    blkHeight,
  uint16_t    extBlkIncrementX,
  uint16_t    extBlkIncrementY,
  uint16_t    intBlkIncrementX,
  uint16_t    intBlkIncrementY,
  uint32_t    roiOffset,
  uint8_t     *extMemPtr,
  uint16_t    extMemPtrStride,
  uint8_t     *interMemPtr,
  uint16_t    interMemPtrStride,
  uint8_t     dmaQueNo
);

#define DMAREAD_SCATTERGATHER_NODE                      (0)
#define WEIGHT_COMPUTATION_NODE                         (1)
#define MULTIBLOCK_GRADIENT_XY_NODE                     (2)
#define MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE   (3)
#define MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE          (4)
#define TENSOR_MATRIX_7X7_S16_GRAD_NODE                 (5)
#define CALC_DETERMINANT_TENSOR_MATRIX_NODE             (6)
#define CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE          (7)
#define LK_ITERATIVE_LOOP_NODE                          (8)
#define DMAWRITE_AUTOINCREMENT_NODE                     (9)

#define MAX_KERNEL_ID 255

typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_DMAREAD_SCATTERGATHER,
    BAM_TI_KERNELID_WEIGHT_COMPUTATION,
    BAM_TI_KERNELID_MULTIBLOCK_GRADIENT_XY,
    BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16,
    BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_7X7_U8,
    BAM_TI_KERNELID_TENSOR_MATRIX_7X7_S16_GRAD,
    BAM_TI_KERNELID_CALC_DETERMINANT_TENSOR_MATRIX,
    BAM_TI_KERNELID_CALC_INVERSE_STRUCTURE_TENSOR_2X2,
    BAM_TI_KERNELID_LK_ITERATIVE_LOOP,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT
} BAM_TI_KernelID;

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamKernelHostDB[] =
{
    { &gBAM_TI_dmaPyramidLKTrackerReadKernel,                 &gBAM_TI_dmaReadPyramidLKTrackerKernelHelperFunc,             "ti_dma_read_scattergatherr",                   BAM_TI_KERNELID_DMAREAD_SCATTERGATHER},
    { &gBAM_TI_weightComputationKernel,                       &gBAM_TI_weightComputationHelperFunc,                         "ti_weight_computation",                        BAM_TI_KERNELID_WEIGHT_COMPUTATION },
    { &gBAM_TI_multiblockGradientXYKernel,                    &gBAM_TI_multiblockGradientXYHelperFunc,                      "ti_multiblock_gradient_xy",                    BAM_TI_KERNELID_MULTIBLOCK_GRADIENT_XY },
    { &gBAM_TI_multiblockBilinearInterpIntlv7x7S16Kernel,     &gBAM_TI_multiblockBilinearInterpIntlv7x7S16HelperFunc,       "ti_multiblock_bilinear_interp_intlv_7x7_s16",  BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16 },
    { &gBAM_TI_multiblockBilinearInterp7x7U8Kernel,           &gBAM_TI_multiblockBilinearInterp7x7U8HelperFunc,             "ti_multiblock_bilinear_interp_7x7_u8",         BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_7X7_U8 },
    { &gBAM_TI_tensorMatrix7x7S16GradKernel,                  &gBAM_TI_tensorMatrix7x7S16GradHelperFunc,                    "ti_tensor_matrix_7x7_s16_grad",                BAM_TI_KERNELID_TENSOR_MATRIX_7X7_S16_GRAD },
    { &gBAM_TI_calcDeterminantTensorMatrixKernel,             &gBAM_TI_calcDeterminantTensorMatrixHelperFunc,               "ti_calc_determinant_tensor_matrix",            BAM_TI_KERNELID_CALC_DETERMINANT_TENSOR_MATRIX },
    { &gBAM_TI_calcInverseStructureTensor2x2Kernel,           &gBAM_TI_calcInverseStructureTensor2x2HelperFunc,             "ti_calc_inverse_structure_tensor_2x2",         BAM_TI_KERNELID_CALC_INVERSE_STRUCTURE_TENSOR_2X2 },
    { &gBAM_TI_lkIterativeLoopKernel,                         &gBAM_TI_lkIterativeLoopHelperFunc,                           "ti_inner_loop_pyramid_lk_tracker",             BAM_TI_KERNELID_LK_ITERATIVE_LOOP },
    { &gBAM_TI_dmaPyramidLKTrackerWriteKernel,                &gBAM_TI_dmaWritePyramidLKTrackerKernelHelperFunc,            "ti_dma_write_autoincrement",                   BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaPyramidLKTrackerReadKernel,                 &gBAM_TI_dmaReadPyramidLKTrackerKernelExecFunc,               "ti_dma_read_scattergatherr",                       BAM_TI_KERNELID_DMAREAD_SCATTERGATHER},
    { &gBAM_TI_weightComputationKernel,                       &gBAM_TI_weightComputationExecFunc,                           "ti_weight_computation",                            BAM_TI_KERNELID_WEIGHT_COMPUTATION },
    { &gBAM_TI_multiblockGradientXYKernel,                    &gBAM_TI_multiblockGradientXYExecFunc,                        "ti_multiblock_gradient_xy",                        BAM_TI_KERNELID_MULTIBLOCK_GRADIENT_XY },
    { &gBAM_TI_multiblockBilinearInterpIntlv7x7S16Kernel,     &gBAM_TI_multiblockBilinearInterpIntlv7x7S16ExecFunc,         "ti_multiblock_bilinear_interp_intlv_7x7_s16",      BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16 },
    { &gBAM_TI_multiblockBilinearInterp7x7U8Kernel,           &gBAM_TI_multiblockBilinearInterp7x7U8ExecFunc,               "ti_multiblock_bilinear_interp_7x7_u8",             BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_7X7_U8 },
    { &gBAM_TI_tensorMatrix7x7S16GradKernel,                  &gBAM_TI_tensorMatrix7x7S16GradExecFunc,                      "ti_tensor_matrix_7x7_s16_grad",                    BAM_TI_KERNELID_TENSOR_MATRIX_7X7_S16_GRAD },
    { &gBAM_TI_calcDeterminantTensorMatrixKernel,             &gBAM_TI_calcDeterminantTensorMatrixExecFunc,                 "ti_calc_determinant_tensor_matrix",                BAM_TI_KERNELID_CALC_DETERMINANT_TENSOR_MATRIX },
    { &gBAM_TI_calcInverseStructureTensor2x2Kernel,           &gBAM_TI_calcInverseStructureTensor2x2ExecFunc,               "ti_calc_inverse_structure_tensor_2x2",             BAM_TI_KERNELID_CALC_INVERSE_STRUCTURE_TENSOR_2X2 },
    { &gBAM_TI_lkIterativeLoopKernel,                         &gBAM_TI_lkIterativeLoopExecFunc,                             "ti_inner_loop_pyramid_lk_tracker",                 BAM_TI_KERNELID_LK_ITERATIVE_LOOP },
    { &gBAM_TI_dmaPyramidLKTrackerWriteKernel,                &gBAM_TI_dmaWritePyramidLKTrackerKernelExecFunc,              "ti_dma_write_autoincrement",                       BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
};

BAM_KernelDBdef gBAM_TI_kernelDBdef =
{
    sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
    bamKernelHostDB,
    bamKernelExecFuncDB
};


int32_t LK_TRACKER_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = LK_TRACKER_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = LK_TRACKER_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = LK_TRACKER_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize     = sizeof(LK_TRACKER_TI_graphArgs) ;
  return 0;
}

int32_t LK_TRACKER_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      const PYRAMID_LK_TRACKER_TI_CreateParams * createParams)
{
  BAM_CreateGraphParams graphCreateParams;
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  LK_TRACKER_TI_graphArgs * graphArgs = (LK_TRACKER_TI_graphArgs *)graphMem->graphArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  BAM_NodeParams NODELIST[]=
  {
    {DMAREAD_SCATTERGATHER_NODE                   ,             BAM_TI_KERNELID_DMAREAD_SCATTERGATHER,                              NULL},
    {WEIGHT_COMPUTATION_NODE                      ,             BAM_TI_KERNELID_WEIGHT_COMPUTATION,                                 NULL},
    {MULTIBLOCK_GRADIENT_XY_NODE                  ,             BAM_TI_KERNELID_MULTIBLOCK_GRADIENT_XY,                             NULL},
    {MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,             BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16,           NULL},
    {MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE       ,             BAM_TI_KERNELID_MULTIBLOCK_BILINEAR_INTERP_7X7_U8,                  NULL},
    {TENSOR_MATRIX_7X7_S16_GRAD_NODE              ,             BAM_TI_KERNELID_TENSOR_MATRIX_7X7_S16_GRAD,                         NULL},
    {CALC_DETERMINANT_TENSOR_MATRIX_NODE          ,             BAM_TI_KERNELID_CALC_DETERMINANT_TENSOR_MATRIX,                     NULL},
    {CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE       ,             BAM_TI_KERNELID_CALC_INVERSE_STRUCTURE_TENSOR_2X2,                  NULL},
    {LK_ITERATIVE_LOOP_NODE                       ,             BAM_TI_KERNELID_LK_ITERATIVE_LOOP,                                  NULL},
    {DMAWRITE_AUTOINCREMENT_NODE                  ,             BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,                             NULL},
    {BAM_END_NODE_MARKER                          ,             0,                                                                  NULL},
  };
  /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
  NODELIST[DMAREAD_SCATTERGATHER_NODE                    ].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs );
  NODELIST[WEIGHT_COMPUTATION_NODE                       ].kernelArgs = (void *)(&graphArgs->wgtCompArgs       );
  NODELIST[MULTIBLOCK_GRADIENT_XY_NODE                   ].kernelArgs = (void *)(&graphArgs->gradXYArgs        );
  NODELIST[MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE ].kernelArgs = (void *)(&graphArgs->biLinIntp16Args   );
  NODELIST[MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE        ].kernelArgs = (void *)(&graphArgs->biLinIntpU8Args   );
  NODELIST[TENSOR_MATRIX_7X7_S16_GRAD_NODE               ].kernelArgs = (void *)(&graphArgs->tensorMatArgs     );
  NODELIST[CALC_DETERMINANT_TENSOR_MATRIX_NODE           ].kernelArgs = (void *)(&graphArgs->detMatArgs        );
  NODELIST[CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE        ].kernelArgs = (void *)(&graphArgs->invMatArgs        );
  NODELIST[LK_ITERATIVE_LOOP_NODE                        ].kernelArgs = (void *)(&graphArgs->lkIterativeLoopArgs );
  NODELIST[DMAWRITE_AUTOINCREMENT_NODE                   ].kernelArgs = (void *)(&graphArgs->dmaWriteKernelArgs);

  BAM_EdgeParams EDGELIST[]=
  {
    {{DMAREAD_SCATTERGATHER_NODE,   BAM_SOURCE_NODE_PORT1},                                                                      {MULTIBLOCK_GRADIENT_XY_NODE,  BAM_MULTIBLOCK_GRADIENT_XY_INPUT_PORT}},
    {{DMAREAD_SCATTERGATHER_NODE,   BAM_SOURCE_NODE_PORT1},                                                                      {MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_IMAGE}},
    {{DMAREAD_SCATTERGATHER_NODE,   BAM_SOURCE_NODE_PORT2},                                                                      {LK_ITERATIVE_LOOP_NODE,  BAM_LK_ITERATIVE_LOOP_INPUT_PORT_CURRIMG}},
    {{DMAREAD_SCATTERGATHER_NODE,   BAM_SOURCE_NODE_PORT3},                                                                      {WEIGHT_COMPUTATION_NODE,   BAM_WEIGHT_COMPUTATION_INPUT_PORT}},
    {{DMAREAD_SCATTERGATHER_NODE,   BAM_SOURCE_NODE_PORT4},                                                                      {LK_ITERATIVE_LOOP_NODE,   BAM_LK_ITERATIVE_LOOP_INPUT_PORT_LASCRATCH}},
    {{DMAREAD_SCATTERGATHER_NODE,   BAM_SOURCE_NODE_PORT5},                                                                      {LK_ITERATIVE_LOOP_NODE,   BAM_LK_ITERATIVE_LOOP_INPUT_PORT_HASCRATCH}},
    {{LK_ITERATIVE_LOOP_NODE,       BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_CURRXY},                                                   {DMAWRITE_AUTOINCREMENT_NODE,  BAM_SINK_NODE_PORT1}},
    {{LK_ITERATIVE_LOOP_NODE,       BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_ERRMEASURE},                                               {DMAWRITE_AUTOINCREMENT_NODE,  BAM_SINK_NODE_PORT2}},
    {{LK_ITERATIVE_LOOP_NODE,       BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_INVALIDPTS},                                               {DMAWRITE_AUTOINCREMENT_NODE,  BAM_SINK_NODE_PORT3}},
    {{WEIGHT_COMPUTATION_NODE,      BAM_WEIGHT_COMPUTATION_OUTPUT_PORT},                                                         {MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_WGTS}},
    {{WEIGHT_COMPUTATION_NODE,      BAM_WEIGHT_COMPUTATION_OUTPUT_PORT},                                                         {MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_WGTS}},
    {{MULTIBLOCK_GRADIENT_XY_NODE,  BAM_MULTIBLOCK_GRADIENT_XY_OUTPUT_PORT},                                                     {MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_IMAGE}},
    {{MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADX},           {TENSOR_MATRIX_7X7_S16_GRAD_NODE,  BAM_TENSOR_MATRIX_7X7_S16_GRAD_INPUT_PORT_GRADX}},
    {{MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADX},           {LK_ITERATIVE_LOOP_NODE,  BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADXINTERP}},
    {{MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADY},           {LK_ITERATIVE_LOOP_NODE,  BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADYINTERP}},
    {{MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE,  BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADY},           {TENSOR_MATRIX_7X7_S16_GRAD_NODE,  BAM_TENSOR_MATRIX_7X7_S16_GRAD_INPUT_PORT_GRADY}},
    {{MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE,   BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_OUTPUT_PORT},                              {LK_ITERATIVE_LOOP_NODE,  BAM_LK_ITERATIVE_LOOP_INPUT_PORT_PREVINTERP}},
    {{TENSOR_MATRIX_7X7_S16_GRAD_NODE,  BAM_TENSOR_MATRIX_7X7_S16_GRAD_OUTPUT_TENSOR},                                           {CALC_DETERMINANT_TENSOR_MATRIX_NODE,  BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_XX}},
    {{TENSOR_MATRIX_7X7_S16_GRAD_NODE,  BAM_TENSOR_MATRIX_7X7_S16_GRAD_OUTPUT_TENSOR},                                           {CALC_DETERMINANT_TENSOR_MATRIX_NODE,  BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_YY}},
    {{TENSOR_MATRIX_7X7_S16_GRAD_NODE,  BAM_TENSOR_MATRIX_7X7_S16_GRAD_OUTPUT_TENSOR},                                           {CALC_DETERMINANT_TENSOR_MATRIX_NODE,  BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_XY}},
    {{TENSOR_MATRIX_7X7_S16_GRAD_NODE,  BAM_TENSOR_MATRIX_7X7_S16_GRAD_OUTPUT_TENSOR},                                           {CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE,  BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_TENSOR}},
    {{CALC_DETERMINANT_TENSOR_MATRIX_NODE,  BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NRSB},                                {CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE,  BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NRSB}},
    {{CALC_DETERMINANT_TENSOR_MATRIX_NODE,  BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NORM},                                {CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE,  BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NORM}},
    {{CALC_DETERMINANT_TENSOR_MATRIX_NODE,  BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NORM},                                {CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE,  BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NORM}},
    {{CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE,  BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_OUTPUT_PORT_OUT1},                          {LK_ITERATIVE_LOOP_NODE,  BAM_LK_ITERATIVE_LOOP_INPUT_PORT_INVMAT}},
    {{BAM_END_NODE_MARKER, 0},                                     {BAM_END_NODE_MARKER, 0}},
  };

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;
  graphCreateParams.blockDimParams.blockWidth  = 0;
  graphCreateParams.blockDimParams.blockHeight = 0;


  status= BAM_initKernelDB(&gBAM_TI_kernelDBdef);

  if(status != BAM_S_SUCCESS)
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.coreType             = BAM_EVE;
  graphCreateParams.kernelDB             = &gBAM_TI_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = LK_TRACKER_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = LK_TRACKER_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = LK_TRACKER_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = 1U;
  graphCreateParams.optimizeBlockDim     = 0;

  graphArgs->createParams = createParams;

   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &LK_TRACKER_TI_initKernelsArgs;
  graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

  /* Initialize the structure blockDimParams that lists the processing block
  * dimensions as well as the step increment sizes used during the block
  * dimension optimization if enabled
  */
  graphCreateParams.blockDimParams.blockWidth           = 8;
  graphCreateParams.blockDimParams.blockHeight          = 1;

  /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  status = BAM_createGraph(&graphCreateParams, &graphHandle);
  if(status != BAM_S_SUCCESS)
  {
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto Exit;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
  }

  /*-------------------------------------------------------------------------*/
  /* error message handling and return of error code                         */
  /*-------------------------------------------------------------------------*/
Exit:
  if (status== BAM_E_INVALID_MEM_SIZE)
  {
    PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
      graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
  }
  else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
  {
    PRINTF("Graph construction failed!!! Decrease the value of blockWidth : %d or blockHeight : %d",
      graphCreateParams.blockDimParams.blockWidth,graphCreateParams.blockDimParams.blockHeight);
  }
  else if (status != BAM_S_SUCCESS)
  {
    PRINTF("Graph construction failed!!!");
  }
  else {
      /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
  }

  return (status);
}

/*-------------------------------------------------------------------------*/
/* Function to assign DMA parameters to EDMA utilitiy                      */
/*-------------------------------------------------------------------------*/
static void assignDMAautoIncrementParams(
  EDMA_UTILS_autoIncrement_transferProperties * param,
  uint16_t    roiWidth,
  uint16_t    roiHeight,
  uint16_t    blkWidth,
  uint16_t    blkHeight,
  uint16_t    extBlkIncrementX,
  uint16_t    extBlkIncrementY,
  uint16_t    intBlkIncrementX,
  uint16_t    intBlkIncrementY,
  uint32_t    roiOffset,
  uint8_t     *extMemPtr,
  uint16_t    extMemPtrStride,
  uint8_t     *interMemPtr,
  uint16_t    interMemPtrStride,
  uint8_t     dmaQueNo
)
{
  param->roiWidth             = roiWidth;
  param->roiHeight            = roiHeight;
  param->blkWidth             = blkWidth;
  param->blkHeight            = blkHeight;
  param->extBlkIncrementX     = extBlkIncrementX;
  param->extBlkIncrementY     = extBlkIncrementY;
  param->intBlkIncrementX     = intBlkIncrementX;
  param->intBlkIncrementY     = intBlkIncrementY;
  param->roiOffset            = roiOffset;
  param->extMemPtr            = extMemPtr;
  param->extMemPtrStride      = extMemPtrStride ;
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t LK_TRACKER_TI_initKernelsArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams)
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
{
  LK_TRACKER_TI_graphArgs *args= (LK_TRACKER_TI_graphArgs*)initKernelsArgs;
  uint16_t      prevImStride;
  uint16_t      prevBlkHeight;
  uint16_t      gradBlkWidth;
  uint16_t      gradBlkHeight;
  uint16_t      currImStride;
  uint16_t      currBlkWidth;
  uint16_t      currBlkHeight;

  uint16_t numKeyPointsPerCall;
  uint16_t numKeyPoints;

  uint8_t maxSearchRange = LK_TRACKER_TI_FindMaxSearchRange(args->createParams->searchRange, args->createParams->numLevels);
  uint8_t searchWidth  = maxSearchRange;
  uint8_t searchHeight = maxSearchRange;

  currBlkWidth            = ((searchWidth + (uint16_t)((uint16_t)VCOP_LK_PATCH_WIDTH/2U))*2U) + 1U;
  currBlkWidth            = (uint16_t)((uint16_t)(currBlkWidth + (uint16_t)1U) & (uint16_t)(~(uint16_t)1U));
  currBlkHeight           = ((searchHeight + (uint16_t)((uint16_t)VCOP_LK_PATCH_WIDTH/2U))*2U) + 1U;
  currImStride            = currBlkWidth;
  numKeyPointsPerCall     = LK_TRACKER_TI_FindNumKeyPointsPerCall(currBlkWidth,currBlkHeight);

  numKeyPoints = (((args->createParams->numKeyPoints + numKeyPointsPerCall) - 1U)/numKeyPointsPerCall)*numKeyPointsPerCall;

  gradBlkWidth  = ((uint16_t)VCOP_LK_PATCH_WIDTH + 1U);
  gradBlkHeight = ((uint16_t)VCOP_LK_PATCH_WIDTH + 1U);
  prevImStride  = numKeyPointsPerCall * (gradBlkWidth + 2U);
  prevBlkHeight = (gradBlkHeight + 2U);

  /*--------------------------------------------------------------------------*/
  /*Params Update for Pyramid LK Tracker Scatter Gather DMA Read Node         */
  /*--------------------------------------------------------------------------*/
  args->dmaReadKernelArgs.numKeyPointsProcessedPerCall          = numKeyPointsPerCall;
  args->dmaReadKernelArgs.totalKeyPointsCompute                 = numKeyPoints;
  args->dmaReadKernelArgs.numScatterGatherTransfers             = numKeyPointsPerCall*2U;
  args->dmaReadKernelArgs.prevFrmblkWidth                       = (gradBlkWidth + 2U);
  args->dmaReadKernelArgs.prevFrmblkHeight                      = prevBlkHeight;
  args->dmaReadKernelArgs.prevFrmsrcPtrStride                   = args->createParams->imWidth;
  args->dmaReadKernelArgs.prevFrmdstPtrStride                   = prevImStride;
  args->dmaReadKernelArgs.currFrmblkWidth                       = currBlkWidth;
  args->dmaReadKernelArgs.currFrmblkHeight                      = currBlkHeight;
  args->dmaReadKernelArgs.currFrmsrcPtrStride                   = args->createParams->imWidth;
  args->dmaReadKernelArgs.currFrmdstPtrStride                   = currImStride;
  args->dmaReadKernelArgs.ctrlArgs                              = (EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args *)(void*)args->dmaCtrlArgs;

  /*--------------------------------------------------------------------------*/
  /*Params Update for Pyramid LK Tracker Auto increment DMA Write Node        */
  /*--------------------------------------------------------------------------*/
  args->dmaWriteKernelArgs.transferType           = EDMA_UTILS_TRANSFER_INOUT;
  args->dmaWriteKernelArgs.numInTransfers         = 0;
  args->dmaWriteKernelArgs.numOutTransfers        = 2;
  assignDMAautoIncrementParams((EDMA_UTILS_autoIncrement_transferProperties *)(void*)&args->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
    (uint16_t    )(4U*numKeyPointsPerCall),              /*roiWidth,          */
    (uint16_t    )(numKeyPoints/numKeyPointsPerCall),   /*roiHeight,         */
    (uint16_t    )(4U*numKeyPointsPerCall),              /*blkWidth,          */
    (uint16_t    )1,                                  /*blkHeight,         */
    (uint16_t    )0,                                  /*extBlkIncrementX,  */
    (uint16_t    )1,                                  /*extBlkIncrementY,  */
    (uint16_t    )0,                                  /*intBlkIncrementX,  */
    (uint16_t    )0,                                  /*intBlkIncrementY,  */
    (uint32_t    )0,                                  /*roiOffset,         */
    (uint8_t    *)NULL,                               /*extMemPtr,         */
    (uint16_t    )(numKeyPointsPerCall*4U),              /*extMemPtrStride,   */
    (uint8_t    *)NULL,                               /*interMemPtr,       */
    (uint16_t    )(numKeyPointsPerCall*4U),              /*interMemPtrStride, */
    (uint8_t     )0                                   /*dmaQueNo           */
    );
  assignDMAautoIncrementParams((EDMA_UTILS_autoIncrement_transferProperties *)(void*)&args->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT2],
    (uint16_t    )(2U*numKeyPointsPerCall),              /*roiWidth,          */
    (uint16_t    )(numKeyPoints/numKeyPointsPerCall),   /*roiHeight,         */
    (uint16_t    )(2U*numKeyPointsPerCall),              /*blkWidth,          */
    (uint16_t    )1,                                  /*blkHeight,         */
    (uint16_t    )0,                                  /*extBlkIncrementX,  */
    (uint16_t    )1,                                  /*extBlkIncrementY,  */
    (uint16_t    )0,                                  /*intBlkIncrementX,  */
    (uint16_t    )0,                                  /*intBlkIncrementY,  */
    (uint32_t    )0,                                  /*roiOffset,         */
    (uint8_t    *)NULL,                               /*extMemPtr,         */
    (uint16_t    )(numKeyPointsPerCall*2U),              /*extMemPtrStride,   */
    (uint8_t    *)NULL,                               /*interMemPtr,       */
    (uint16_t    )(numKeyPointsPerCall*2U),              /*interMemPtrStride, */
    (uint8_t     )0                                   /*dmaQueNo           */
    );


  /*--------------------------------------------------------------------------*/
  /*Params Update for Pyramid LK Tracker kernels                              */
  /*--------------------------------------------------------------------------*/
  args->wgtCompArgs.numKeyPoints = numKeyPointsPerCall;
  args->wgtCompArgs.outputStride = numKeyPointsPerCall;

  args->gradXYArgs.inputStride    =  prevImStride;
  args->gradXYArgs.blkWidth       =  gradBlkWidth;
  args->gradXYArgs.blkHeight      =  gradBlkHeight;
  args->gradXYArgs.blkOffset      =  (gradBlkWidth + 2U);
  args->gradXYArgs.numBlocks      =  numKeyPointsPerCall;

  args->biLinIntp16Args.input1Stride   =   (VCOP_LK_PATCH_WIDTH+1)*2;
  args->biLinIntp16Args.input2Stride   =   numKeyPointsPerCall;
  args->biLinIntp16Args.outputStride   =   (VCOP_LK_PATCH_WIDTH+1);
  args->biLinIntp16Args.blkWidth       =   (VCOP_LK_PATCH_WIDTH+1);
  args->biLinIntp16Args.blkHeight      =   VCOP_LK_PATCH_WIDTH;
  args->biLinIntp16Args.blkOffset      =   (VCOP_LK_PATCH_WIDTH+1)*2*(VCOP_LK_PATCH_WIDTH+1);
  args->biLinIntp16Args.numKeyPoints   =   numKeyPointsPerCall;

  args->biLinIntpU8Args.input1Stride   =   prevImStride;
  args->biLinIntpU8Args.input2Stride   =   numKeyPointsPerCall;
  args->biLinIntpU8Args.outputStride   =   (VCOP_LK_PATCH_WIDTH+1);
  args->biLinIntpU8Args.blkWidth       =   (VCOP_LK_PATCH_WIDTH+1);
  args->biLinIntpU8Args.blkHeight      =   VCOP_LK_PATCH_WIDTH;
  args->biLinIntpU8Args.blkOffset      =   (gradBlkWidth+2U);
  args->biLinIntpU8Args.numKeyPoints   =   numKeyPointsPerCall;

  args->tensorMatArgs.stride    =   (VCOP_LK_PATCH_WIDTH+1);
  args->tensorMatArgs.n         =   numKeyPointsPerCall;

  args->detMatArgs.n            =   numKeyPointsPerCall;

  args->invMatArgs.inputStride     =   numKeyPointsPerCall;
  args->invMatArgs.outputStride    =   numKeyPointsPerCall*2U;
  args->invMatArgs.numKeyPoints    =   numKeyPointsPerCall;

  /*Initialize the iterative LK loop kernel arguments*/
  args->lkIterativeLoopArgs.numKeyPointsPerCall    = numKeyPointsPerCall;
  args->lkIterativeLoopArgs.keyPointsProcessedCnt  = 2U*numKeyPointsPerCall;
  args->lkIterativeLoopArgs.prevXYList             = args->prevXYList;
  args->lkIterativeLoopArgs.currXYList             = args->currXYList;
  args->lkIterativeLoopArgs.numKeyPoints           = numKeyPoints;
  args->lkIterativeLoopArgs.currBlkWidth           = currBlkWidth;
  args->lkIterativeLoopArgs.currBlkHeight          = currBlkHeight;

  args->lkIterativeLoopArgs.ctrlArgs               = (EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args *)(void*)args->dmaCtrlArgs;

  return (0);
}

uint8_t LK_TRACKER_TI_FindNumKeyPointsPerCall(
        uint16_t blkWidth,
        uint16_t blkHeight)
{
  uint8_t numKeyPointsPerCall = (uint8_t)((uint16_t)LK_IMGBUFF_INPUT_MEM_SIZE / (blkWidth*blkHeight));


  numKeyPointsPerCall = (uint8_t)(numKeyPointsPerCall &(uint8_t)(~7U));
  if(numKeyPointsPerCall > (uint8_t)VCOP_LK_MAX_NUM_KEY_PER_CALL)
  {
    numKeyPointsPerCall = (uint8_t)VCOP_LK_MAX_NUM_KEY_PER_CALL;
  }

  return numKeyPointsPerCall;
}

uint8_t LK_TRACKER_TI_FindMaxSearchRange(
        const uint8_t    searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS],
        uint8_t    numLevels)
{
  uint8_t i;
  uint8_t maxSearchRange = searchRange[0];
  for(i = 1U; i < numLevels; i++)
  {
    if(maxSearchRange < searchRange[i])
    {
      maxSearchRange = searchRange[i];
    }
  }
  return maxSearchRange;
}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t LK_TRACKER_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  status = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;
}

int32_t LK_TRACKER_TI_bamControl(const BAM_GraphMem *graphMem,EDMA_UTILS_pyramidlktracker_dma_ctrl_args *bam_ctrl_args)
{
    int32_t status = BAM_S_SUCCESS;
    BAM_Weight_Computation_Ctrl_Args    Ctrl_Args;
    BAM_LK_Iterative_Loop_CtrlArgs      iterativeLoop_ctrlArgs;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    status= BAM_controlNode(graphHandle, DMAREAD_SCATTERGATHER_NODE, bam_ctrl_args);

    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    status= BAM_controlNode(graphHandle, (uint8_t)DMAWRITE_AUTOINCREMENT_NODE, bam_ctrl_args);
    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    Ctrl_Args.currLevel = bam_ctrl_args->currLevel;

    status= BAM_controlNode(graphHandle, (uint8_t)WEIGHT_COMPUTATION_NODE, &Ctrl_Args);
    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    status= BAM_controlNode(graphHandle, (uint8_t)MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_NODE, &Ctrl_Args);
    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    status= BAM_controlNode(graphHandle, (uint8_t)MULTIBLOCK_BILINEAR_INTERP_7X7_U8_NODE, &Ctrl_Args);
    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
    status= BAM_controlNode(graphHandle, (uint8_t)CALC_INVERSE_STRUCTURE_TENSOR_2X2_NODE, &Ctrl_Args);

    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    iterativeLoop_ctrlArgs.SADthreshold = bam_ctrl_args->SADthreshold;


    status= BAM_controlNode(graphHandle, (uint8_t)LK_ITERATIVE_LOOP_NODE, &iterativeLoop_ctrlArgs);

 Exit:
    return status;
}
