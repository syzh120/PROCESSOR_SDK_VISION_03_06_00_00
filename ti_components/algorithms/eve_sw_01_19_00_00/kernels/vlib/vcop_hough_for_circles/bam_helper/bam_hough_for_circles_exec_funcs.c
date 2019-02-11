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
 *  @file       bam_hough_for_circles_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hough for
 *              circles kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_hough_for_circles_int.h"
#include "bam_hough_for_circles.h"
#include "vcop_hough_for_circles_kernel.h" /* compiler should take care of include path */

#define BAM_HOUGHFORCIRCLES_IMG_BUF_A_B_OFFSET (0x20000U)


/***********************************************************************************************/
/*                        Below are the helper  functions related to Hough Index Calculation kernels                                */
/***********************************************************************************************/
static BAM_Status Bam_HoughForCircles_initFrame(void *kernelContext);
static BAM_Status Bam_HoughForCircles_computeFrame(void *kernelContext);
static BAM_Status Bam_HoughForCircles_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_HoughForCircles_initFrame(void *kernelContext)
{
  BAM_HoughForCircles_Context *context = (BAM_HoughForCircles_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;

  context->currentRadiusPtr[0]       = (int8_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_RADIUS_PTR_IDX];

#if !VCOP_HOST_EMULATION
  /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
   /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
   /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
  context->currentRadiusPtr[1] = context->currentRadiusPtr[0] + BAM_HOUGHFORCIRCLES_IMG_BUF_A_B_OFFSET;
  /* RESET_MISRA("17.4")  -> Reset rule 17.4     */

#else
  context->currentRadiusPtr[1] = context->currentRadiusPtr[0] ;
#endif

#if (!VCOP_HOST_EMULATION)

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  We are derving internal memory pointers and as their size is not know during compile time we have to do the following*/
  context->paramBlockUpdatePblock = (uint16_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX] +
                                            vcop_hough_circle_compute_idx_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  vcop_hough_circle_compute_idx_init(
    context->pInBlock[BAM_HOUGH_FOR_CIRCLES_NORM_GRAD_PORT],
    context->pInBlock[BAM_HOUGH_FOR_CIRCLES_XY_LIST_PORT],
    context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX],
    context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_HOUGH_IDX_PORT],
    0,/*This field will get populated later using param block update */
    context->kernelCtrlArgs.radius[0],
    context->kernelInitArgs.houghSpaceDownShift,
    context->kernelCtrlArgs.houghSpaceSaturateX,
    context->kernelCtrlArgs.houghSpaceSaturateY,
    context->kernelCtrlArgs.houghSpacePitch,
    context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX]
  );

  vcop_hough_circle_compute_idx_param_block_update_init(
      context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX],
      context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX],
      context->pInBlock[BAM_HOUGH_FOR_CIRCLES_XY_LIST_SIZE_WBUF_PORT],
      /* CHECK_MISRA("-11.4")  -> Disable rule 11.4  */
      /*  MISRA.CAST.PTR :  Cast between a pointer to object type and a different pointer to object type */
      /*  This cast is required to remove compiler warning which is coming because an issue with compiler header files   */
      (char *)context->currentRadiusPtr[0],
      /*RESET_MISRA("11.4")  -> Reset rule 11.4 for MISRA.CAST.PTR */
      context->paramBlockUpdatePblock);

#endif
    context->radIdx = 0;

    /* This is to initialize the first value of radius, later all other values of radius should get update by ARP32 to point to the next value */
    context->pingPongFlag = 0;
    *(context->currentRadiusPtr[context->pingPongFlag]) = context->kernelCtrlArgs.radius[context->radIdx];


    context->pingPongFlag ^= 1U;
    return status;
}


static BAM_Status Bam_HoughForCircles_computeFrame(void *kernelContext)
{
    BAM_HoughForCircles_Context *context = (BAM_HoughForCircles_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_hough_circle_compute_idx(
    context->pInBlock[BAM_HOUGH_FOR_CIRCLES_NORM_GRAD_PORT],
    context->pInBlock[BAM_HOUGH_FOR_CIRCLES_XY_LIST_PORT],
    context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX],
    context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_HOUGH_IDX_PORT],
    *((uint16_t *)context->pInBlock[BAM_HOUGH_FOR_CIRCLES_XY_LIST_SIZE_WBUF_PORT]),/* For Host emulation no param block update required */
    context->kernelCtrlArgs.radius[context->radIdx],
    context->kernelInitArgs.houghSpaceDownShift,
    context->kernelCtrlArgs.houghSpaceSaturateX,
    context->kernelCtrlArgs.houghSpaceSaturateY,
    context->kernelCtrlArgs.houghSpacePitch
  );
#else
    /* Param block update to update the radius and current number of edge points */
    vcop_hough_circle_compute_idx_param_block_update_vloops(context->paramBlockUpdatePblock);

    vcop_hough_circle_compute_idx_vloops(
        context->pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX]);
#endif

  context->radIdx++;
  if ( context->radIdx == context->kernelCtrlArgs.numRadius )
  {
      context->radIdx = 0;
  }
  /* This is the radius which will get used in next trigger call */
  *(context->currentRadiusPtr[context->pingPongFlag]) = context->kernelCtrlArgs.radius[context->radIdx];

  context->pingPongFlag ^= 1U;

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_HoughForCircles_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_HoughForCircles_Context *context = (BAM_HoughForCircles_Context *) kernelContext;

  BAM_HoughForCircles_CtrlArgs * ctrlArgs = (BAM_HoughForCircles_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}


/***********************************************************************************************/
/*                        Below are the helper  functions related to Circle Detect kernels                                                */
/***********************************************************************************************/
static BAM_Status Bam_HoughForCirclesDetect_initFrame(void *kernelContext);
static BAM_Status Bam_HoughForCirclesDetect_computeFrame(void *kernelContext);
static BAM_Status Bam_HoughForCirclesDetect_control(void *kernelContext,
                                                  void * kernelCtlArg);

static BAM_Status Bam_HoughForCirclesDetect_initFrame(void *kernelContext)
{
  BAM_HoughForCirclesDetect_Context *context = (BAM_HoughForCirclesDetect_Context *) kernelContext;
  uint32_t i;
  BAM_Status status = BAM_S_SUCCESS;
  uint16_t *pXseq;
  uint16_t (*pUpperLeftXY)[2];
  uint16_t *pBlock;

  context->blkIdx = 0;
  context->numBlks = (context->kernelCtrlArgs.numEdgePoints +
      (context->kernelCtrlArgs.numEdgePointsChunk - 1U))/
      context->kernelCtrlArgs.numEdgePointsChunk;

  context->numElemsInLastBlk = context->kernelCtrlArgs.numEdgePoints -
      ((context->numBlks - 1U)*context->kernelCtrlArgs.numEdgePointsChunk);

  pXseq = (uint16_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX];

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the parameter outside this node which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  for(i = 0; i < context->kernelCtrlArgs.houghSpacePitch; i++) {
    pXseq[2U * i] = 0;
    pXseq[(2U * i) + 1U] = (uint16_t)((uint16_t)i << (uint16_t)context->kernelCtrlArgs.houghSpaceShift);
  }
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  pUpperLeftXY = (uint16_t (*)[2])context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX];

  (*pUpperLeftXY)[0] = context->kernelCtrlArgs.startY;
  (*pUpperLeftXY)[1] = context->kernelCtrlArgs.startX;

  context->pingPongFlag = 0;
  context->pingPongFlag ^= 1U;

#if (!VCOP_HOST_EMULATION)

  pBlock = (uint16_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_PARAMS_IDX];
  context->pBlockHoughSpaceInit = pBlock;
  vcop_hough_circle_init_hough_space_init(
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the parameter outside this node which at compile is unknown , hence we cannot check if we are accessing beyond*/
    (uint32_t*)(void *)((uint8_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX] + (context->kernelCtrlArgs.maxRadius *
            context->kernelCtrlArgs.houghSpacePitch)),
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    context->kernelCtrlArgs.houghSpacePitch,
    context->kernelCtrlArgs.houghSpaceHeight,
    context->pBlockHoughSpaceInit);

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  We are derving internal memory pointers and as their size is not know during compile time we have to do the following*/
  pBlock += vcop_hough_circle_init_hough_space_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  context->pBlockHoughSpaceVote = pBlock;
  vcop_hough_circle_vote_to_hough_space_init(
    context->pInBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_IDX_PORT],
    context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX],
    context->kernelCtrlArgs.numEdgePointsChunk,
    context->pBlockHoughSpaceVote);

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  We are derving internal memory pointers and as their size is not know during compile time we have to do the following*/
  pBlock += vcop_hough_circle_vote_to_hough_space_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */


  context->pBlockCircleDetect = pBlock;
  vcop_hough_for_circle_detect_init(
    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the parameter outside this node which at compile is unknown , hence we cannot check if we are accessing beyond*/
    (uint8_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX] +
            context->kernelCtrlArgs.maxRadius + (context->kernelCtrlArgs.maxRadius *
            context->kernelCtrlArgs.houghSpacePitch),
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX],
    context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX],
    context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_CIRCLES_PORT],
    context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_CENTER_XY_PORT],
    context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_SCORE_PORT],
    context->kernelCtrlArgs.houghScoreThreshold,
    context->kernelCtrlArgs.houghSpaceWidth,
    context->kernelCtrlArgs.houghSpaceHeight,
    context->kernelCtrlArgs.houghSpacePitch,
    context->kernelCtrlArgs.houghSpaceShift,
    context->pBlockCircleDetect);

  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  We are derving internal memory pointers and as their size is not know during compile time we have to do the following*/
  pBlock += vcop_hough_for_circle_detect_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  context->pBlockHoughSpaceVoteUpdateParams = pBlock;

  vcop_hough_circle_vote_to_hough_space_param_block_update_init(
    context->pBlockHoughSpaceVote,
    context->numElemsInLastBlk,
    context->pBlockHoughSpaceVoteUpdateParams);
#endif



  return status;
}





static BAM_Status Bam_HoughForCirclesDetect_computeFrame(void *kernelContext)
{
  BAM_HoughForCirclesDetect_Context *context = (BAM_HoughForCirclesDetect_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
  uint16_t numElemsPerBlock;

  if(context->blkIdx == 0) {
    vcop_hough_circle_init_hough_space(
      (uint8_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX] +
            (context->kernelCtrlArgs.maxRadius *
            context->kernelCtrlArgs.houghSpacePitch),
      context->kernelCtrlArgs.houghSpacePitch,
      context->kernelCtrlArgs.houghSpaceHeight);
  }

  numElemsPerBlock = (context->blkIdx == context->numBlks - 1U) ?
                     context->numElemsInLastBlk :
                     context->kernelCtrlArgs.numEdgePointsChunk;

  vcop_hough_circle_vote_to_hough_space(
    context->pInBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_IDX_PORT],
    context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX],
    numElemsPerBlock);

  if(context->blkIdx == context->numBlks - 1U) {
    vcop_hough_for_circle_detect(
      (uint8_t *)context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX] +
            context->kernelCtrlArgs.maxRadius + (context->kernelCtrlArgs.maxRadius *
            context->kernelCtrlArgs.houghSpacePitch),
      context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX],
      context->pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX],
      context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_CIRCLES_PORT],
      context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_CENTER_XY_PORT],
      context->pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_SCORE_PORT],
      context->kernelCtrlArgs.houghScoreThreshold,
      context->kernelCtrlArgs.houghSpaceWidth,
      context->kernelCtrlArgs.houghSpaceHeight,
      context->kernelCtrlArgs.houghSpacePitch,
      context->kernelCtrlArgs.houghSpaceShift);
  }
#else
  if(context->blkIdx == 0) {
    vcop_hough_circle_init_hough_space_vloops(context->pBlockHoughSpaceInit);
  }

  if(context->blkIdx == (context->numBlks - 1U)) {
  /* Update numEdgePoints parameter in pBlock with numElemsInLastBlk for last block */
  vcop_hough_circle_vote_to_hough_space_param_block_update_vloops(context->pBlockHoughSpaceVoteUpdateParams);

  }

  vcop_hough_circle_vote_to_hough_space_vloops(context->pBlockHoughSpaceVote);

  if(context->blkIdx == (context->numBlks - 1U)) {
    vcop_hough_for_circle_detect_vloops(context->pBlockCircleDetect);

    /* TODO: Revert back param block pBlockHoughSpaceVote if required */
  }
#endif

  context->blkIdx = (context->blkIdx + 1U) % context->numBlks;
  context->pingPongFlag ^= 1U;

  return BAM_S_SUCCESS;
}



static BAM_Status Bam_HoughForCirclesDetect_control(void *kernelContext,
                                                  void * kernelCtlArg)
{
  BAM_HoughForCirclesDetect_Context *context = (BAM_HoughForCirclesDetect_Context *) kernelContext;

  BAM_HoughForCirclesDetect_CtrlArgs * ctrlArgs = (BAM_HoughForCirclesDetect_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_houghForCirclesExecFunc =
{
  NULL,
  &Bam_HoughForCircles_initFrame,
  &Bam_HoughForCircles_computeFrame,
  NULL,
  &Bam_HoughForCircles_control,
  NULL
};

BAM_KernelExecFuncDef gBAM_TI_houghForCirclesDetectExecFunc =
{
  NULL,
  &Bam_HoughForCirclesDetect_initFrame,
  &Bam_HoughForCirclesDetect_computeFrame,
  NULL,
  &Bam_HoughForCirclesDetect_control,
  NULL
};

