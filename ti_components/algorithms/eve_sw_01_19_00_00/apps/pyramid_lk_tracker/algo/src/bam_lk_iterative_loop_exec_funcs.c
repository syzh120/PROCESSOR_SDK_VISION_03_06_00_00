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
*  @file       bam_lk_iterative_loop_exec_funcs.c
*
*  @brief      This file defines interfaces for integrating for kernel that computes
*              relative location within the fetched input block along with updated
*              source pointers using the new X, Y coordinates into BAM. It also
 *              incorporates the iterative LK loop to compute the flow vectors
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>
#include <vcop_host.h>

#include "bam_lk_iterative_loop_int.h"
#include "bam_lk_iterative_loop.h"
#include "vcop_weight_address_bilinear_interpolation_kernel.h"
#include "vcop_sum_grad_cross_inter_frame_diff_7x7_kernel.h"
#include "vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel.h"
#include "vcop_calc_new_lk_xy_kernel.h"
#include "vcop_copy_new_lk_xy_kernel.h"
#include "vcop_sad_error_measure_lk_kernel.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"
#include "edma_utils_context_size.h"
#include "edma_utils.h"

#define ARP32_VCOP_SEQUENTIAL (0)

/* Function Prototypes */
static BAM_Status Bam_LK_Iterative_Loop_initFrame(void *kernelContext);

static BAM_Status Bam_LK_Iterative_Loop_computeFrame(void *kernelContext);

static BAM_Status Bam_LK_Iterative_Loop_control(void *kernelContext, void *kernelCtlArg);

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2     */
/* These is ia auto generated variable    */
extern uint16_t __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[1];
/* RESET_MISRA("20.2")  -> Reset rule 20.2     */

/*-----------------------------------------------------------------
  Function to compute the source address of the next set of blocks
  that needs to be fetched using scatter gather transfer
  This function only updates the offset along the vertical direction
  This routine updates the pointers for the current frame blocks
-----------------------------------------------------------------*/
static inline void getSrcForCurrFrame1(
  const uint16_t frameXY[2*VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint16_t localY[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t *temp[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t  *base,
  uint16_t imageWidth,
  uint16_t imageHeight,
  uint8_t qFormatePel,
  uint8_t searchHeight,
  uint16_t numKeyPointsPerCall
  )
{
  uint16_t i;
  uint16_t fullPelY;
  uint16_t currImSrcY;
  uint16_t mask;
  uint16_t vcopLKLocalY =   ((uint16_t)searchHeight + (uint16_t)(VCOP_LK_PATCH_WIDTH/2));
  vcopLKLocalY <<=   qFormatePel;
  for( i = 0; i < numKeyPointsPerCall; i++)
  {
    fullPelY = frameXY[(2U*i)+1U];
    fullPelY >>=  qFormatePel;
    if(fullPelY < ((uint16_t)searchHeight + (uint16_t)(VCOP_LK_PATCH_WIDTH/2)))
    {
      localY[i]     = frameXY[(2U*i)+1U];
      currImSrcY    = 0;
    }
    else if((fullPelY + ((uint16_t)searchHeight + (uint16_t)(VCOP_LK_PATCH_WIDTH/2)) + (uint16_t)1U) >= imageHeight)
    {
      currImSrcY    = imageHeight - (((uint16_t)searchHeight + (uint16_t)(VCOP_LK_PATCH_WIDTH/2))*2U) - 1U;
      localY[i]     = frameXY[(2U*i)+1U] - (uint16_t)(currImSrcY << qFormatePel);
    }
    else
    {
      mask = (uint16_t)(((uint16_t)1U) << qFormatePel);
      mask--;
      localY[i]     = vcopLKLocalY + (frameXY[(2U*i)+1U] & mask);
      currImSrcY    = fullPelY -((uint16_t)searchHeight + (uint16_t)(VCOP_LK_PATCH_WIDTH/2));
    }
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    temp[i] = (uint8_t*)(base + ((uint32_t)currImSrcY*(uint32_t)imageWidth));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
  }
}

/*-----------------------------------------------------------------
  Function to compute the source address of the next set of blocks
  that needs to be fetched using scatter gather transfer
  This function only updates the offset along the horizontal direction
  This routine updates the pointers for the current frame blocks
-----------------------------------------------------------------*/
static inline void getSrcForCurrFrame2(
  const uint16_t frameXY[2*VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint16_t localX[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t *temp[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t *srcList[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint16_t imageWidth,
  uint8_t qFormatePel,
  uint8_t searchWidth,
  uint16_t numKeyPointsPerCall
  )
{
  uint16_t i;
  uint16_t fullPelX;
  uint16_t currImSrcX;
  uint16_t mask;
  uint16_t vcopLKLocalX =   (uint16_t)searchWidth + ((uint16_t)(VCOP_LK_PATCH_WIDTH/2));
  vcopLKLocalX = (uint16_t)(vcopLKLocalX << (uint16_t)qFormatePel);

  for( i = 0; i < numKeyPointsPerCall; i++)
  {
    fullPelX = ((uint16_t)frameXY[2U*i] >> qFormatePel);
    if(fullPelX < ((uint16_t)searchWidth + (uint16_t)(VCOP_LK_PATCH_WIDTH/2)))
    {
      localX[i]     = frameXY[2U*i];
      currImSrcX = 0;
    }
    else if((fullPelX + ((uint16_t)searchWidth) + ((uint16_t)(VCOP_LK_PATCH_WIDTH/2)) + ((uint16_t)1U)) >= imageWidth)
    {
      currImSrcX    = imageWidth - (((uint16_t)searchWidth + (uint16_t)(VCOP_LK_PATCH_WIDTH/2))*2U)  - 1U;
      localX[i]     = frameXY[2U*i] - (uint16_t)(currImSrcX << qFormatePel);
    }
    else
    {
      mask = (uint16_t)(((uint16_t)1U << qFormatePel));
      mask--;
      localX[i]     = vcopLKLocalX + ((uint16_t)frameXY[2U*i] & (uint16_t)mask);
      currImSrcX    = fullPelX -((uint16_t)searchWidth + (uint16_t)(VCOP_LK_PATCH_WIDTH/2));
    }
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    srcList[i] =  (uint8_t*)(temp[i] + currImSrcX);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
  }
}

/*-----------------------------------------------------------------
  Function to compute the source address of the next set of blocks
  that needs to be fetched using scatter gather transfer
  This function only updates the offset along the vertical direction
  This routine updates the pointers for the previous frame blocks
-----------------------------------------------------------------*/
static inline void getSrcForPrevFrame1(
  const uint16_t frameXY[2*VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint16_t localY[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t   *temp[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t  base[],
  uint16_t imageWidth,
  uint16_t imageHeight,
  uint8_t qFormatePel,
  uint16_t numKeyPointsPerCall
  )
{
  uint16_t i;
  uint16_t fullPelY;
  uint16_t prevImSrcY;

  for( i = 0; i < numKeyPointsPerCall; i++)
  {
    fullPelY = ((uint16_t)frameXY[(2U*i)+1U] >> qFormatePel);
    if((fullPelY <  ((uint16_t)(VCOP_LK_PATCH_WIDTH/2) + (uint16_t)1U))  || ((fullPelY + ((uint16_t)(VCOP_LK_PATCH_WIDTH/2) + (uint16_t)2U)) >= imageHeight))
    {
      localY[i]     = 0;
      prevImSrcY    = 0;
    }
    else
    {
      prevImSrcY    = (fullPelY - ((uint16_t)(VCOP_LK_PATCH_WIDTH/2) + (uint16_t)1U));
    }
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    temp[i] = (uint8_t*)(base + ((uint32_t)prevImSrcY*(uint32_t)imageWidth));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
  }

}

/*-----------------------------------------------------------------
  Function to compute the source address of the next set of blocks
  that needs to be fetched using scatter gather transfer
  This function only updates the offset along the vertical direction
  This routine updates the pointers for the previous frame blocks
-----------------------------------------------------------------*/
static inline void getSrcForPrevFrame2(
  const uint16_t frameXY[2*VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint16_t localX[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t *temp[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint8_t *srcList[VCOP_LK_MAX_NUM_KEY_PER_CALL],
  uint16_t imageWidth,
  uint8_t qFormatePel,
  uint16_t numKeyPointsPerCall
  )
{
  uint16_t i;
  uint16_t fullPelX;
  uint16_t prevImSrcX;

  for( i = 0; i < numKeyPointsPerCall; i++)
  {
    fullPelX = ((uint16_t)frameXY[2U*i] >> qFormatePel);
    if((fullPelX <  ((uint16_t)(VCOP_LK_PATCH_WIDTH/2) + (uint16_t)1U)) || ((fullPelX + ((uint16_t)(VCOP_LK_PATCH_WIDTH/2) + (uint16_t)2U)) >= imageWidth))
    {
      localX[i]  = 0;
      prevImSrcX = 0;
    }
    else
    {
      prevImSrcX = (fullPelX - ((uint16_t)(VCOP_LK_PATCH_WIDTH/2) + (uint16_t)1));
    }
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    srcList[i] =  (uint8_t*)(temp[i] + prevImSrcX);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
  }
}

/*-----------------------------------------------------------------
  Function to initialize the iterative loop kernels and initializing
  the scratches required by these iterative loop kernels. The kernels
  include Weight & Address Update for the current frame blocks,
  Compute Bilinear interpolated patch windows for the current frame
  blocks, Compute product of bilinear interpolated gradient and temporal
  difference between previous and current frame blocks and finally
  compute the flow vectors for the given pyramid level
-----------------------------------------------------------------*/
static BAM_Status Bam_LK_Iterative_Loop_initFrame(void *kernelContext)
{
  BAM_LK_Iterative_Loop_Context *context = (BAM_LK_Iterative_Loop_Context *) (void*)kernelContext;
  uint16_t * buff_a;
  uint16_t * buff_b;
  uint16_t * buff_c;
  uint8_t  * currImBlocks;
  uint16_t   currImStride;
  uint16_t   currBlkWidth;
  uint16_t   currBlkHeight;
  uint16_t * currXY;
  uint16_t * localXY;
  uint16_t * localX;
  uint16_t * localY;
  uint16_t * pOutWts;
  int16_t  * pGradXBilinearInterpImg;
  int16_t  * pGradYBilinearInterpImg;
  uint8_t  * pCurrBilinearInterpImg;
  uint8_t  * pOutBilinearInterpImg;
  int32_t  * zIx2_b;
  int32_t  * zIy2_b;
  int32_t  * zIxy_b;
  int32_t  * IxIt_c;
  int32_t  * IyIt_c;
  uint16_t * IxItL_c;
  uint16_t * IyItL_c;
  int16_t  * IxItH_c;
  int16_t  * IyItH_c;
  int32_t  * temp32_a;
  int32_t  * temp32_b;
  uint32_t * pValidInAddrList;
  uint32_t * pValidOutAddrList;
  uint32_t * pTempOutAddress;
  uint32_t * pTempOutAddressErrMeas;
  uint16_t * pParamBlkOffsetVec;
  uint16_t (*pParamBlkOffsetVecLocal)[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint16_t * pWeightAddress[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint16_t * numValidPoints;
  uint8_t  * currValidPoints;
  uint8_t  * TempMem1[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint8_t  * TempMem2[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint16_t * prevXYList;
  uint16_t * currXYList;
  uint32_t * pBaseInAddrList;
  uint32_t (*pBaseInAddrListLocal)[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint32_t * pBaseOutAddrList;
  uint32_t (*pBaseOutAddrListLocal)[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint16_t * prevXYForDma    ;
  uint16_t * currXYForDma    ;
  uint16_t (* prevXYForVcop)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL]   ;
  uint16_t (* currXYForVcop)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL]   ;

  int32_t   qFormatePel;
  uint16_t   maxQFactor;
  uint16_t   numKeyPointsPerCall;
  uint16_t   i,k;
  uint8_t   truncateBits;
  uint16_t qFormatlocal;

  EDMA_UTILS_autoIncrement1D_initParam listInDMAinitParam;

  /* Beloe two address list will be filled by
   * vcop_weight_address_bilinear_interpolation
   */
  uint8_t  *pOutBaseAddress[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint8_t  *pValidFinalOutAddress[VCOP_LK_MAX_NUM_KEY_PER_CALL];

  qFormatePel              = (VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlArgs->currLevel);
  maxQFactor               = (uint16_t)((uint16_t)1U << (uint16_t)qFormatePel);
  maxQFactor--;
  truncateBits             = qFormatePel <= 8 ? 0 : (2*(qFormatePel-8));
  numKeyPointsPerCall      = context->kernelArgs.numKeyPointsPerCall;
  currBlkWidth             = context->kernelArgs.currBlkWidth;
  currBlkHeight            = context->kernelArgs.currBlkHeight;
  currImStride             = currBlkWidth;

  buff_a                   = (uint16_t *)(void*)context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_LASCRATCH];
  buff_b                   = (uint16_t *)(void*)context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_HASCRATCH];
  buff_c                   = (uint16_t *)(void*)context->pInternalBlock[SCRATCH_IDX1];

  currImBlocks             = (uint8_t  *)(void*)(context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_CURRIMG]);
  pOutBilinearInterpImg    = (uint8_t  *)(void*)(context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_PREVINTERP]);
  pGradXBilinearInterpImg  = (int16_t  *)(void*)(context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADXINTERP]);
  pGradYBilinearInterpImg  = (int16_t  *)(void*)(context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADYINTERP]);
  zIx2_b                   = (int32_t  *)(void*)(context->pInBlock[BAM_LK_ITERATIVE_LOOP_INPUT_PORT_INVMAT]);

  prevXYList               = context->kernelArgs.prevXYList;
  currXYList               = context->kernelArgs.currXYList;

  qFormatlocal = ((uint16_t)qFormatePel*(uint16_t)2U);
  if(qFormatlocal > 16U)
  {
    qFormatlocal = 16U;
  }


  localXY                           = (uint16_t *)(void*)buff_a;
  currXY                            = (uint16_t *)(void*)buff_b ;
  pCurrBilinearInterpImg            = (uint8_t  *)(void*)(buff_c);

  /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
  /* Pointer is used in arithmetic or array index expression */
  /* Deviation allowed since, this same address needs to be accessed with an offset  */
  zIy2_b                            = (int32_t  *)(void *)(zIx2_b   + (uint32_t)numKeyPointsPerCall);
  zIxy_b                            = (int32_t  *)(void *)(zIy2_b   + (uint32_t)numKeyPointsPerCall);
  localX                            = (uint16_t *)(void *)(localXY  + ((uint32_t)2 * (uint32_t)numKeyPointsPerCall));
  localY                            = (uint16_t *)(void *)(localX   + (uint32_t)numKeyPointsPerCall);
  pValidInAddrList                  = (uint32_t *)(void *)(localY   + (uint32_t)numKeyPointsPerCall);
  pValidOutAddrList                 = (uint32_t *)(void *)(pValidInAddrList     + (uint32_t)numKeyPointsPerCall);
  currValidPoints                   = (uint8_t  *)(void *)(pValidOutAddrList    + (uint32_t)numKeyPointsPerCall);
  pOutWts                           = (uint16_t *)(void *)(currValidPoints      + (uint32_t)numKeyPointsPerCall);
  temp32_a                          = (int32_t  *)(void *)(pOutWts              + ((uint32_t)4*(uint32_t)numKeyPointsPerCall));
  temp32_b                          = (int32_t  *)(void *)(currXY               + ((uint32_t)2*(uint32_t)numKeyPointsPerCall));

  pParamBlkOffsetVec                = (uint16_t  *)(void *)(pCurrBilinearInterpImg + ((uint32_t)numKeyPointsPerCall*(((uint32_t)VCOP_SIMD_WIDTH*(uint32_t)VCOP_LK_PATCH_WIDTH))));
  IxIt_c                            = (int32_t   *)(void *)(pParamBlkOffsetVec               + (uint32_t)numKeyPointsPerCall);
  IyIt_c                            = (int32_t   *)(void *)(IxIt_c                           + (uint32_t)numKeyPointsPerCall);
  pBaseInAddrList                   = (uint32_t  *)(void *)(IyIt_c                           + (uint32_t)numKeyPointsPerCall);
  pBaseOutAddrList                  = (uint32_t  *)(void *)(pBaseInAddrList                  + (uint32_t)numKeyPointsPerCall);
  numValidPoints                    = (uint16_t  *)(void *)(pBaseOutAddrList                 + (uint32_t)numKeyPointsPerCall);
  context->pBlkWgtAddrUpdate        = (uint16_t  *)(void *)(numValidPoints                   + (uint32_t)numKeyPointsPerCall);
  context->pBlkCurrBiLin            = (uint16_t  *)(void *)(context->pBlkWgtAddrUpdate       +  vcop_weight_address_bilinear_interpolation_param_count());
  context->pBlkCalcIxIt             = (uint16_t  *)(void *)(context->pBlkCurrBiLin           +  vcop_foreach_multiblock_bilinear_interp_7x7_u8_param_count());
  context->pBlkIterCalcNewXY        = (uint16_t  *)(void *)(context->pBlkCalcIxIt            +  vcop_sum_grad_cross_inter_frame_diff_7x7_param_count());
  context->pBlkCopyNewXY            = (uint16_t  *)(void *)(context->pBlkIterCalcNewXY       +  vcop_calc_new_lk_xy_param_count());
  context->pBlkWgtAddrForErrMeas    = (uint16_t  *)(void *)(context->pBlkCopyNewXY           +  vcop_copy_new_lk_xy_param_count());
  context->pBlkCurrBiLinForErrMeas  = (uint16_t  *)(void *)(context->pBlkWgtAddrForErrMeas   +  vcop_weight_address_bilinear_interpolation_param_count());
  context->pBlkCalcSADErrMeasure    = (uint16_t  *)(void *)(context->pBlkCurrBiLinForErrMeas +  vcop_foreach_multiblock_bilinear_interp_7x7_u8_param_count());
  IxItH_c                           = ((int16_t   *)(void *)(IxIt_c)) + 1;
  IyItH_c                           = ((int16_t   *)(void *)(IyIt_c)) + 1;
  /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

  IxItL_c = (uint16_t *)(void*)(IxIt_c);
  IyItL_c = (uint16_t *)(void*)(IyIt_c);


  listInDMAinitParam.numInTransfers    = 2;
  listInDMAinitParam.numOutTransfers   = 0;
  listInDMAinitParam.transferType      = EDMA_UTILS_TRANSFER_IN;

  for(k =0; k < 2U; k++)
  {
    listInDMAinitParam.transferProp[k].totalLength          = 2U*((context->kernelArgs.ctrlArgs->numKeyPoints + (NUM_POINTS_IN_DMEM-1U))/NUM_POINTS_IN_DMEM)*NUM_POINTS_IN_DMEM * sizeof(int16_t);
    listInDMAinitParam.transferProp[k].numBytes             = 2U*NUM_POINTS_IN_DMEM * sizeof(int16_t);
    listInDMAinitParam.transferProp[k].extMemIncrement      = 2U*NUM_POINTS_IN_DMEM * sizeof(int16_t);
    listInDMAinitParam.transferProp[k].intMemIncrement      = 2U*NUM_POINTS_IN_DMEM * sizeof(int16_t);
    listInDMAinitParam.transferProp[k].numCircBuf           = NUM_POINT_BUFFS_IN_DMEM;
    listInDMAinitParam.transferProp[k].dmaQueNo             = 0;
  }

  listInDMAinitParam.transferProp[0].extMemPtr            = (uint8_t *)(void*)context->kernelArgs.ctrlArgs->cornerListInXY;
  listInDMAinitParam.transferProp[1].extMemPtr            = (uint8_t *)(void*)context->kernelArgs.ctrlArgs->cornerListOutXY;

  listInDMAinitParam.transferProp[0].interMemPtr          = (uint8_t *)(void*)prevXYList;
  listInDMAinitParam.transferProp[1].interMemPtr          = (uint8_t *)(void*)currXYList;

  EDMA_UTILS_autoIncrement1D_init(context->listInDMAContext,&listInDMAinitParam);
  EDMA_UTILS_autoIncrement1D_configure(context->listInDMAContext , EDMA_UTILS_TRANSFER_IN);

  EDMA_UTILS_autoIncrement1D_triggerInChannel(context->listInDMAContext);
  EDMA_UTILS_autoIncrement1D_waitInChannel(context->listInDMAContext);

  if((NUM_POINTS_IN_DMEM/numKeyPointsPerCall) >= (context->kernelArgs.ctrlArgs->numKeyPoints/numKeyPointsPerCall))
  {
    uint16_t currValidPtIdx = (context->kernelArgs.ctrlArgs->numValidKeyPoints % (uint16_t)NUM_POINTS_IN_DMEM);
    uint16_t totalPts       = ((currValidPtIdx + (numKeyPointsPerCall-1U)) / numKeyPointsPerCall) * numKeyPointsPerCall;
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    uint16_t * prevXYList_temp  = &(context->kernelArgs.prevXYList[0]);
    uint16_t * currXYList_temp  = &(context->kernelArgs.currXYList[0]);

    uint16_t loopCnt;

    for(loopCnt = currValidPtIdx; loopCnt < totalPts; loopCnt++)
    {
      prevXYList_temp[2U * loopCnt]    = prevXYList_temp[(2U*loopCnt) - 2U];
      prevXYList_temp[(2U * loopCnt) + 1U] = prevXYList_temp[(2U*loopCnt) - 1U];
      currXYList_temp[2U * loopCnt]    = currXYList_temp[(2U*loopCnt) - 2U];
      currXYList_temp[(2U * loopCnt) + 1U] = currXYList_temp[(2U*loopCnt) - 1U];
    }
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
  }


  context->prevXYAdrs[0]              =  (uint16_t  (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)context->kernelArgs.ctrlArgs->prevXYAddr[0];
  context->currXYAdrs[0]              =  (uint16_t  (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)currXY;
  context->localXYAdrs[0]             =  (uint16_t  (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)localXY;
  context->localXAdrs[0]              =  (uint16_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)localX;
  context->localYAdrs[0]              =  (uint16_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)localY;
  context->currValidPointsAdrs[0]     =  (uint8_t   (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)currValidPoints;
  context->pValidInAddrListAdrs[0]    =  (uint32_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)pValidInAddrList;
  context->pValidOutAddrListAdrs[0]   =  (uint32_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)pValidOutAddrList;

  /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
  /* Pointer is used in arithmetic or array index expression */
  /* Deviation allowed since, this same address needs to be accessed with an offset  */
  context->prevXYAdrs[1]              =   (uint16_t  (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void *)(((uint8_t*)(void *)context->prevXYAdrs[0]            )   + 0x20000U);
  context->currXYAdrs[1]              =   (uint16_t  (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void *)(((uint8_t*)(void *)context->currXYAdrs[0]            )   + 0x20000U);
  context->localXYAdrs[1]             =   (uint16_t  (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void *)(((uint8_t*)(void *)context->localXYAdrs[0]           )   + 0x20000U);
  context->localXAdrs[1]              =   (uint16_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])  (void *)(((uint8_t*)(void *)context->localXAdrs[0]            )   + 0x20000U);
  context->localYAdrs[1]              =   (uint16_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])  (void *)(((uint8_t*)(void *)context->localYAdrs[0]            )   + 0x20000U);
  context->currValidPointsAdrs[1]     =   (uint8_t   (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])  (void *)(((uint8_t*)(void *)context->currValidPointsAdrs[0]   )   + 0x20000U);
  context->pValidInAddrListAdrs[1]    =   (uint32_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])  (void *)(((uint8_t*)(void *)context->pValidInAddrListAdrs[0]  )   + 0x20000U);
  context->pValidOutAddrListAdrs[1]   =   (uint32_t  (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])  (void *)(((uint8_t*)(void *)context->pValidOutAddrListAdrs[0] )   + 0x20000U);
  /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

  context->numValidPoints = numValidPoints;

  VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
  pBaseInAddrListLocal    = (uint32_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)pBaseInAddrList;
  pBaseOutAddrListLocal   = (uint32_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)pBaseOutAddrList;
  pParamBlkOffsetVecLocal = (uint16_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)pParamBlkOffsetVec;
  for(i = 0;  i < numKeyPointsPerCall ; i++)
  {
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    context->pBaseInAddrListLocal[i]          = (uint32_t )(currImBlocks + ((uint32_t)currBlkWidth*(uint32_t)currBlkHeight * (uint32_t)i));
    (*pBaseInAddrListLocal)[i]                = (uint32_t )(currImBlocks + ((uint32_t)currBlkWidth*(uint32_t)currBlkHeight * (uint32_t)i));
    context->pBaseOutAddrListLocal[i]         = (uint32_t )(pCurrBilinearInterpImg + (i*((uint32_t)VCOP_SIMD_WIDTH*(uint32_t)VCOP_LK_PATCH_WIDTH)));
    (*pBaseOutAddrListLocal)[i]               = (uint32_t )(pCurrBilinearInterpImg + (i*((uint32_t)VCOP_SIMD_WIDTH*(uint32_t)VCOP_LK_PATCH_WIDTH)));
    pWeightAddress[i]                         = (uint16_t *)(pOutWts + (uint32_t)i);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    (*pParamBlkOffsetVecLocal)[i]            = i*(uint16_t)26U*(uint16_t)2U;
  }

  for(i = 0;  i < 2U; i++)
  {
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    prevXYForDma  = (uint16_t *)(prevXYList + ((uint32_t)2*((((uint32_t)i)*(uint32_t)numKeyPointsPerCall)%((uint32_t)2*(uint32_t)NUM_POINTS_IN_DMEM))));
    currXYForDma  = (uint16_t *)(currXYList + ((uint32_t)2*((((uint32_t)i)*(uint32_t)numKeyPointsPerCall)%((uint32_t)2*(uint32_t)NUM_POINTS_IN_DMEM))));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    getSrcForCurrFrame1(currXYForDma, context->localYCb[i],TempMem2, context->kernelArgs.ctrlArgs->currBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,(uint8_t)qFormatePel,context->kernelArgs.ctrlArgs->searchRange, numKeyPointsPerCall);
    getSrcForPrevFrame1(prevXYForDma, context->localYCb[i],TempMem1, context->kernelArgs.ctrlArgs->prevBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,(uint8_t)qFormatePel,numKeyPointsPerCall);
    getSrcForCurrFrame2(currXYForDma, context->localXCb[i],TempMem2, &context->kernelArgs.ctrlArgs->srcAddrList[i&1U][numKeyPointsPerCall],context->kernelArgs.ctrlArgs->imWidth,(uint8_t)qFormatePel,context->kernelArgs.ctrlArgs->searchRange, numKeyPointsPerCall);
    getSrcForPrevFrame2(prevXYForDma, context->localXCb[i],TempMem1, &context->kernelArgs.ctrlArgs->srcAddrList[i&1U][0], context->kernelArgs.ctrlArgs->imWidth,(uint8_t)qFormatePel,numKeyPointsPerCall);
  }

  *numValidPoints = numKeyPointsPerCall;

  prevXYForVcop = (uint16_t (* )[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)prevXYList;
  currXYForVcop = (uint16_t (* )[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)currXYList;

  for( k = 0; k < numKeyPointsPerCall; k++)
  {
    (*context->prevXYAdrs[0])[(2U*k)]           = (*prevXYForVcop)[(2U*k)];
    (*context->prevXYAdrs[0])[(2U*k)+1U]        = (*prevXYForVcop)[(2U*k)+1U];
    (*context->currXYAdrs[0])[(2U*k)]           = (*currXYForVcop)[(2U*k)];
    (*context->currXYAdrs[0])[(2U*k)+1U]        = (*currXYForVcop)[(2U*k)+1U];
    (*context->localXAdrs[0])[k]              = context->localXCb[0][k];
    (*context->localYAdrs[0])[k]              = context->localYCb[0][k];
    (*context->localXYAdrs[0])[(2U*k)]          = context->localXCb[0][k];
    (*context->localXYAdrs[0])[(2U*k)+1U]       = context->localYCb[0][k];
    (*context->currValidPointsAdrs[0])[k]     = 1U;
    (*context->pValidInAddrListAdrs[0])[k]    = context->pBaseInAddrListLocal[k];
    (*context->pValidOutAddrListAdrs[0])[k]   = context->pBaseOutAddrListLocal[k];
  }

#if !VCOP_HOST_EMULATION
  for( k = 0; k < numKeyPointsPerCall; k++)
  {
    (*context->currValidPointsAdrs[1])[k]    = 1U;
    (*context->pValidInAddrListAdrs[1])[k]   = context->pBaseInAddrListLocal[k];
    (*context->pValidOutAddrListAdrs[1])[k]  = context->pBaseOutAddrListLocal[k];
  }
#endif

  /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
  /* Pointer is used in arithmetic or array index expression */
  /* Deviation allowed since, this same address needs to be accessed with an offset  */
  pTempOutAddress = (uint32_t  *)(void*)((context->pBlkCurrBiLin) + 10U);
  pTempOutAddressErrMeas = (uint32_t  *)(void*)((context->pBlkCurrBiLinForErrMeas) + 10U);
  /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

  vcop_weight_address_bilinear_interpolation_init(
    localX,                  /* Pointer to X Coordinate list of key points                */
    localY,                  /* Pointer to X Coordinate list of key points                */
    pValidInAddrList ,
    pValidOutAddrList,
    pOutWts,                 /* Pointer to output weights for each key point32_t              */
    pTempOutAddress,         /* Pointer to updated base address output for each key point32_t */
    pParamBlkOffsetVec,
    numKeyPointsPerCall,    /* Number of key points                                      */
    maxQFactor,              /* Maximum scale factor for given Q format                   */
    (uint16_t)truncateBits,
    (uint16_t)qFormatePel,              /* Q_shift                  */
    currImStride,            /* Stride of the input block                                 */
    numKeyPointsPerCall,     /* Stride of the output buffer                               */
    context->pBlkWgtAddrUpdate /*__pblock_vcop_weight_address_bilinear_interpolation*/
    );

  vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(
    pOutBaseAddress,         /* List of Pointers to input image data                      */
    pWeightAddress,          /* Pointer to input weights for each key point32_t               */
    pValidFinalOutAddress,   /* output pointer                                            */
    currImStride,            /* Stride of the input block                                 */
    numKeyPointsPerCall,    /* Stride of the weights                                */
    VCOP_SIMD_WIDTH,         /* Stride of the output buffer, pCurrBilinearInterpImg       */
    (uint16_t)VCOP_LK_PATCH_WIDTH,     /* Width of the output block around each key point32_t           */
    (uint16_t)VCOP_LK_PATCH_WIDTH,     /* Height of the output block around each key point32_t          */
    qFormatlocal,
    numKeyPointsPerCall,     /* Stride of the output buffer                               */
    context->pBlkCurrBiLin /*__pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8*/
    );

  vcop_sum_grad_cross_inter_frame_diff_7x7_init(
    pGradXBilinearInterpImg,
    pGradYBilinearInterpImg,
    pOutBilinearInterpImg,
    pCurrBilinearInterpImg,
    VCOP_SIMD_WIDTH,          /* gradStride */
    VCOP_SIMD_WIDTH,          /* imStride */
    numKeyPointsPerCall,
    IxIt_c,
    IyIt_c,
    temp32_a,
    temp32_b,
    context->pBlkCalcIxIt /*__pblock_vcop_sum_grad_cross_inter_frame_diff_7x7*/
    );

  vcop_calc_new_lk_xy_init(
    IxItL_c,
    IyItL_c,
    IxItH_c,
    IyItH_c,
    (int16_t *)(void*)zIx2_b,
    (int16_t *)(void*)zIy2_b,
    (int16_t *)(void*)zIxy_b,
    (int16_t *)(void*)localX,
    (int16_t *)(void*)localY,
    (int16_t *)(void*)localXY,
    (int16_t *)(void*)context->currXYAdrs[0],
    numValidPoints,
    currValidPoints,
    pBaseInAddrList  ,
    pValidInAddrList ,
    pBaseOutAddrList,
    pValidOutAddrList,
    temp32_a,
    temp32_b,
    (uint16_t)qFormatePel,
    context->kernelArgs.ctrlArgs->minErrValue,
    context->kernelArgs.ctrlArgs->searchRange,
    numKeyPointsPerCall,
    context->pBlkIterCalcNewXY /*__pblock_vcop_calc_new_lk_xy*/
    );

  vcop_copy_new_lk_xy_init(
    (int16_t *)(void*)context->currXYAdrs[0],
    (int16_t  *)(void*)(context->pOutBlock[BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_CURRXY]),
    currValidPoints,
    pBaseInAddrList,
    pValidInAddrList,
    pBaseOutAddrList,
    pValidOutAddrList,
    (int16_t *)(void*)localX,
    (int16_t *)(void*)localY,
    (int16_t *)(void*)localXY,
    numKeyPointsPerCall,
    context->pBlkCopyNewXY /*__pblock_vcop_copy_new_lk_xy*/
    );

  vcop_weight_address_bilinear_interpolation_init(
    localX,                  /* Pointer to X Coordinate list of key points                */
    localY,                  /* Pointer to X Coordinate list of key points                */
    pValidInAddrList ,
    pValidOutAddrList,
    pOutWts,                 /* Pointer to output weights for each key point32_t              */
    pTempOutAddressErrMeas,         /* Pointer to updated base address output for each key point32_t */
    pParamBlkOffsetVec,
    numKeyPointsPerCall,    /* Number of key points                                      */
    maxQFactor,              /* Maximum scale factor for given Q format                   */
    (uint16_t)truncateBits,
    (uint16_t)qFormatePel,              /* Q_shift                  */
    currImStride,            /* Stride of the input block                                 */
    numKeyPointsPerCall,     /* Stride of the output buffer                               */
    context->pBlkWgtAddrForErrMeas /*__pblock_vcop_weight_address_bilinear_interpolation*/
    );

  vcop_foreach_multiblock_bilinear_interp_7x7_u8_init(
    pOutBaseAddress,         /* List of Pointers to input image data                      */
    pWeightAddress,          /* Pointer to input weights for each key point32_t               */
    pValidFinalOutAddress,   /* output pointer                                            */
    currImStride,            /* Stride of the input block                                 */
    numKeyPointsPerCall,    /* Stride of the weights                                */
    VCOP_SIMD_WIDTH,         /* Stride of the output buffer, pCurrBilinearInterpImg       */
    (uint16_t)VCOP_LK_PATCH_WIDTH,     /* Width of the output block around each key point32_t           */
    (uint16_t)VCOP_LK_PATCH_WIDTH,     /* Height of the output block around each key point32_t          */
    qFormatlocal,
    numKeyPointsPerCall,     /* Stride of the output buffer                               */
    context->pBlkCurrBiLinForErrMeas /*__pblock_vcop_foreach_multiblock_bilinear_interp_7x7_u8*/
    );


  memset (context->pInternalBlock[SCRATCH_NUM_INVALID_PTS_WBUF], 0, sizeof(uint16_t) * VCOP_SIMD_WIDTH);
  memset (context->pOutBlock[OUT_IDX3], 0, sizeof(uint16_t) * VCOP_SIMD_WIDTH);

  vcop_sad_error_measure_lk_init(
    pOutBilinearInterpImg,
    pCurrBilinearInterpImg,
    (uint16_t *)(void*)context->currXYAdrs[0],
    (uint16_t  *)(void*)(context->pOutBlock[BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_ERRMEASURE]),
    VCOP_SIMD_WIDTH,
    context->kernelArgs.ctrlArgs->imWidth,       /* Frame width for the current level                                       */
    context->kernelArgs.ctrlArgs->imHeight,      /* Frame Height for the current level                                     */
    (uint16_t)VCOP_LK_PATCH_WIDTH,                         /* Width of the output block around each key point32_t           */
    (uint16_t)VCOP_LK_PATCH_WIDTH,                         /* Height of the output block around each key point32_t          */
    numKeyPointsPerCall,
    (uint16_t)qFormatePel,
    (uint16_t  *)(void*)temp32_a,
    context->ctrlArgs.SADthreshold,
     context->pInternalBlock[SCRATCH_NUM_INVALID_PTS_WBUF],
     context->pOutBlock[OUT_IDX3],
    context->pBlkCalcSADErrMeasure /*__pblock_vcop_sad_error_measure_lk*/
    );

  context->currIdx = 0;

  return 0;
}

/*-----------------------------------------------------------------
  Following routines are introduced to copy the next set of frame
  level XY coordinates and corresponding block level relative XY
  coordinates to the Pong/Ping buffer so that VCOP can utilize
  for computation in next trigger
-----------------------------------------------------------------*/
static inline void copyFrameXY(const uint32_t src1[],volatile uint32_t dst1[], const uint32_t src2[], volatile uint32_t dst2[],uint8_t numKeyPointsPerCall)
{
  uint16_t k;
  for(k =0; k < numKeyPointsPerCall; k++)
  {
    dst1[k]   =  src1[k];
    dst2[k]   =  src2[k];
  }
}

static inline void copyLocalXY(const BAM_LK_Iterative_Loop_Context *context,uint16_t currImgBuf, uint16_t localXYIdx, uint8_t numKeyPointsPerCall)
{
  uint16_t (*dst3)[VCOP_LK_MAX_NUM_KEY_PER_CALL]    = (uint16_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL]  )(void*)(context->localXAdrs[currImgBuf]);
  uint16_t (*src3)[VCOP_LK_MAX_NUM_KEY_PER_CALL]    = (uint16_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL]  )(void*)(&context->localXCb[localXYIdx][0]);
  uint16_t (*dst4)[VCOP_LK_MAX_NUM_KEY_PER_CALL]    = (uint16_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL]  )(void*)(context->localYAdrs[currImgBuf]);
  uint16_t (*src4)[VCOP_LK_MAX_NUM_KEY_PER_CALL]    = (uint16_t (*)[VCOP_LK_MAX_NUM_KEY_PER_CALL]  )(void*)(&context->localYCb[localXYIdx][0]);
  uint16_t (*dst5)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL]  = (uint16_t (*)[2*VCOP_LK_MAX_NUM_KEY_PER_CALL])(void*)(context->localXYAdrs[currImgBuf]);
  uint16_t k;
  for(k =0; k < numKeyPointsPerCall; k++)
  {
    (*dst3)[k]         =  (*src3)[k];
    (*dst5)[2U*k]      =  (*src3)[k];
    (*dst4)[k]         =  (*src4)[k];
    (*dst5)[(2U*k)+1U] =  (*src4)[k];
  }
}

/*-----------------------------------------------------------------
  Function to execute the iterative loop kernels. The kernels
  include Weight & Address Update for the current frame blocks,
  Compute Bilinear interpolated patch windows for the current frame
  blocks, Compute product of bilinear interpolated gradient and temporal
  difference between previous and current frame blocks and finally
  compute the flow vectors for the given pyramid level
-----------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION || ARP32_VCOP_SEQUENTIAL)
static BAM_Status Bam_LK_Iterative_Loop_computeFrame(void *kernelContext)
{
  BAM_LK_Iterative_Loop_Context *context = (BAM_LK_Iterative_Loop_Context *) kernelContext;
  uint16_t numKeyPointsPerCall = context->kernelArgs.numKeyPointsPerCall;
  uint8_t * TempMem1[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint8_t * TempMem2[VCOP_LK_MAX_NUM_KEY_PER_CALL];

  uint16_t  *prevXYList  = context->kernelArgs.prevXYList;
  uint16_t  *currXYList  = context->kernelArgs.currXYList;
  int32_t    qFormatePel = (VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlArgs->currLevel);

  uint16_t * prevXYForDma    ;
  uint16_t * currXYForDma    ;
  uint32_t * prevXYForVcop   ;
  uint32_t * currXYForVcop   ;
  volatile uint32_t* dst1;
  volatile uint32_t* dst2;
  uint16_t* dst3;
  uint16_t* dst4;
  uint16_t* dst5;
  uint8_t*  dst6;

  uint32_t* src1;
  uint32_t* src2;
  uint16_t* src3;
  uint16_t* src4;
  uint16_t* src5;
  uint32_t j,k;
  uint16_t currNumValidPoints;
  uint16_t currImgBuf;
  uint16_t localXYIdx;
  uint16_t currSet;
  uint32_t i = context->currIdx ;
  uint16_t prevSet;
#if !VCOP_HOST_EMULATION
  uint32_t val;
  uint32_t val_w;
  volatile uint32_t * bufSwitchCtrl = (uint32_t *)(void*)(MEM_BUF_SWITCH);
  currImgBuf = ((i+1)&1);
  currSet    = 2*(((i+1)*numKeyPointsPerCall)%(2*NUM_POINTS_IN_DMEM));
  localXYIdx = ((i+1)&1);
#else
  currImgBuf = 0;
  currSet    = 2*(((i)*numKeyPointsPerCall)%(2*NUM_POINTS_IN_DMEM));
  localXYIdx = (i&1);
#endif
  prevSet   = 2*(((i+1)*numKeyPointsPerCall)%(2*NUM_POINTS_IN_DMEM));

  if(i%(NUM_POINTS_IN_DMEM/numKeyPointsPerCall) == 0)
  {
    EDMA_UTILS_autoIncrement1D_triggerInChannel(context->listInDMAContext);
  }

  prevXYForDma  = &prevXYList[2*(((i+2)*numKeyPointsPerCall)%(2*NUM_POINTS_IN_DMEM))];
  currXYForDma  = &currXYList[2*(((i+2)*numKeyPointsPerCall)%(2*NUM_POINTS_IN_DMEM))];
  prevXYForVcop = (uint32_t *)(void*)(&prevXYList[prevSet]);
  currXYForVcop = (uint32_t *)(void*)(&currXYList[currSet]);

  dst1 = (volatile uint32_t*)(context->prevXYAdrs[currImgBuf]);
  dst2 = (volatile uint32_t*)(context->currXYAdrs[currImgBuf]);

  __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = (numKeyPointsPerCall-1);
  copyFrameXY(prevXYForVcop, dst1, currXYForVcop, dst2, numKeyPointsPerCall);
  copyLocalXY(context,currImgBuf,localXYIdx, numKeyPointsPerCall);
  getSrcForCurrFrame1(currXYForDma, context->localYCb[i&1],TempMem2, context->kernelArgs.ctrlArgs->currBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,qFormatePel,context->kernelArgs.ctrlArgs->searchRange, numKeyPointsPerCall);
  getSrcForPrevFrame1(prevXYForDma, context->localYCb[i&1],TempMem1, context->kernelArgs.ctrlArgs->prevBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,qFormatePel,numKeyPointsPerCall);
  getSrcForCurrFrame2(currXYForDma, context->localXCb[i&1],TempMem2, &context->kernelArgs.ctrlArgs->srcAddrList[i&1][numKeyPointsPerCall],context->kernelArgs.ctrlArgs->imWidth,qFormatePel,context->kernelArgs.ctrlArgs->searchRange, numKeyPointsPerCall);
  getSrcForPrevFrame2(prevXYForDma, context->localXCb[i&1],TempMem1, &context->kernelArgs.ctrlArgs->srcAddrList[i&1][0], context->kernelArgs.ctrlArgs->imWidth,qFormatePel,numKeyPointsPerCall);

  for(j = 0; j < context->kernelArgs.ctrlArgs->maxItersLK; j++)
  {
    vcop_weight_address_bilinear_interpolation_vloops(context->pBlkWgtAddrUpdate);
    vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(context->pBlkCurrBiLin);
    vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(context->pBlkCalcIxIt);
    vcop_calc_new_lk_xy_vloops(context->pBlkIterCalcNewXY);
    _vcop_vloop_done();

#if !VCOP_HOST_EMULATION
    val = bufSwitchCtrl[0];
    val_w = ((val & 0x0000FFFF) | (WBUF_SYST << 16));
    bufSwitchCtrl[0] = val_w;
    val_w = bufSwitchCtrl[0];
    currNumValidPoints = *context->numValidPoints;
    bufSwitchCtrl[0] = val;
#else
    currNumValidPoints = *context->numValidPoints;
#endif
    if(currNumValidPoints > 0)
    {
      __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = (currNumValidPoints-1);
    }
    else
    {
      break;
    }
  }
  vcop_copy_new_lk_xy_vloops(context->pBlkCopyNewXY);
  if(context->kernelArgs.ctrlArgs->currLevel == 0)
  {
    *context->numValidPoints = numKeyPointsPerCall;
    __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = (numKeyPointsPerCall-1);
    vcop_weight_address_bilinear_interpolation_vloops(context->pBlkWgtAddrForErrMeas);
    vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(context->pBlkCurrBiLinForErrMeas);
    vcop_sad_error_measure_lk_vloops(context->pBlkCalcSADErrMeasure);
  }
  context->currIdx++;
  if(i%(NUM_POINTS_IN_DMEM/numKeyPointsPerCall) == 0)
  {
    EDMA_UTILS_autoIncrement1D_waitInChannel(context->listInDMAContext);

    /*-----------------------------------------------------------------
    The number of key points that needs to be processed (numKeyPoints)
    is not multiple of the number of key points process in (numKeyPointsPerCall)
    each LK tracker kernel, then the last point needs to be duplicated
    to avoid processing any uninitialized points  which may cause
    illegal memory access
    -----------------------------------------------------------------*/

    if((i +(NUM_POINTS_IN_DMEM/numKeyPointsPerCall)) >= (context->kernelArgs.ctrlArgs->numKeyPoints/numKeyPointsPerCall))
    {
      int16_t currValidPtIdx = (context->kernelArgs.ctrlArgs->numValidKeyPoints % NUM_POINTS_IN_DMEM);
      int16_t totalPts       = ((currValidPtIdx + (numKeyPointsPerCall-1)) / numKeyPointsPerCall) * numKeyPointsPerCall;
      uint16_t * prevXYList  = &(context->kernelArgs.prevXYList[(i +(NUM_POINTS_IN_DMEM/numKeyPointsPerCall))/NUM_POINTS_IN_DMEM]);
      uint16_t * currXYList  = &(context->kernelArgs.currXYList[(i +(NUM_POINTS_IN_DMEM/numKeyPointsPerCall))/NUM_POINTS_IN_DMEM]);
      uint16_t loopCnt;

      for(loopCnt = currValidPtIdx; loopCnt < totalPts; loopCnt++)
      {
        prevXYList[2*loopCnt]   = prevXYList[2*loopCnt-2];
        prevXYList[2*loopCnt+1] = prevXYList[2*loopCnt-1];
        currXYList[2*loopCnt]   = currXYList[2*loopCnt-2];
        currXYList[2*loopCnt+1] = currXYList[2*loopCnt-1];
      }
    }
  }
  return 0;
}
#else
static BAM_Status Bam_LK_Iterative_Loop_computeFrame(void *kernelContext)
{
  BAM_LK_Iterative_Loop_Context *context = (BAM_LK_Iterative_Loop_Context *) (void*)kernelContext;
  uint16_t numKeyPointsPerCall = context->kernelArgs.numKeyPointsPerCall;
  uint8_t * TempMem1[VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint8_t * TempMem2[VCOP_LK_MAX_NUM_KEY_PER_CALL];

  uint16_t  *prevXYList  = context->kernelArgs.prevXYList;
  uint16_t  *currXYList  = context->kernelArgs.currXYList;
  int32_t    qFormatePel = (VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlArgs->currLevel);

  uint16_t * prevXYForDma    ;
  uint16_t * currXYForDma    ;
  uint32_t * prevXYForVcop   ;
  uint32_t * currXYForVcop   ;
  volatile uint32_t * dst1;
  volatile uint32_t * dst2;
  uint32_t   j;
  uint16_t   currNumValidPoints;
  uint16_t   currImgBuf;
  uint16_t   localXYIdx;
  uint16_t   currSet;
  uint16_t   i = context->currIdx ;
  uint16_t   prevSet;
  uint32_t   val;
  uint32_t   val_w;
  volatile uint32_t * bufSwitchCtrl = (uint32_t *)(void*)(MEM_BUF_SWITCH);
  currImgBuf = ((uint16_t)(i+(uint16_t)1U)&(uint16_t)1U);
  currSet    = (uint16_t)2*(((i+(uint16_t)1)*numKeyPointsPerCall)%((uint16_t)2*(uint16_t)NUM_POINTS_IN_DMEM));
  localXYIdx = ((i+(uint16_t)1)&(uint16_t)1U);
  prevSet   = (uint16_t)2*(((i+(uint16_t)1)*numKeyPointsPerCall)%((uint16_t)2*(uint16_t)NUM_POINTS_IN_DMEM));

  if((i%((uint16_t)NUM_POINTS_IN_DMEM/numKeyPointsPerCall)) == 0)
  {
    EDMA_UTILS_autoIncrement1D_triggerInChannel(context->listInDMAContext);
  }


  /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
  /* Pointer is used in arithmetic or array index expression */
  /* Deviation allowed since, this same address needs to be accessed with an offset  */
  prevXYForDma  = (uint16_t *)(prevXYList + ((uint32_t)2U*(((i+(uint32_t)2U)*numKeyPointsPerCall)%((uint32_t)2U*(uint32_t)NUM_POINTS_IN_DMEM))));
  currXYForDma  = (uint16_t *)(currXYList + ((uint32_t)2U*(((i+(uint32_t)2U)*numKeyPointsPerCall)%((uint32_t)2U*(uint32_t)NUM_POINTS_IN_DMEM))));
  prevXYForVcop = (uint32_t *)(void *)(prevXYList + (uint32_t)prevSet);
  currXYForVcop = (uint32_t *)(void *)(currXYList + (uint32_t)currSet);
  /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/

  dst1 = (volatile uint32_t*)(volatile void*)(context->prevXYAdrs[currImgBuf]);
  dst2 = (volatile uint32_t*)(void*)(context->currXYAdrs[currImgBuf]);
  __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = (numKeyPointsPerCall-1U);
  for(j = 0; j < context->kernelArgs.ctrlArgs->maxItersLK; j++)
  {
    vcop_weight_address_bilinear_interpolation_vloops(context->pBlkWgtAddrUpdate);
    vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(context->pBlkCurrBiLin);
    vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(context->pBlkCalcIxIt);
    if(j ==0)
    {
      copyFrameXY(prevXYForVcop, dst1, currXYForVcop, dst2,(uint8_t)numKeyPointsPerCall);
    }
    else if(j ==1U)
    {
      copyLocalXY(context,currImgBuf,localXYIdx,(uint8_t)numKeyPointsPerCall);
    }
    else if(j ==2U)
    {
      getSrcForCurrFrame1(currXYForDma, context->localYCb[i&1U],TempMem2, context->kernelArgs.ctrlArgs->currBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,(uint8_t)qFormatePel,context->kernelArgs.ctrlArgs->searchRange,numKeyPointsPerCall);
    }
    else if(j ==3U)
    {
      getSrcForPrevFrame1(prevXYForDma, context->localYCb[i&1U],TempMem1, context->kernelArgs.ctrlArgs->prevBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,(uint8_t)qFormatePel,numKeyPointsPerCall);
    }
    else if(j ==4U)
    {
      getSrcForCurrFrame2(currXYForDma, context->localXCb[i&1U],TempMem2, &context->kernelArgs.ctrlArgs->srcAddrList[i&1U][numKeyPointsPerCall],context->kernelArgs.ctrlArgs->imWidth,(uint8_t)qFormatePel,context->kernelArgs.ctrlArgs->searchRange, numKeyPointsPerCall);
    }
    else
    {
      if(j ==5U)
      {
        getSrcForPrevFrame2(prevXYForDma, context->localXCb[i&1U],TempMem1, &context->kernelArgs.ctrlArgs->srcAddrList[i&1U][0], context->kernelArgs.ctrlArgs->imWidth,(uint8_t)qFormatePel,numKeyPointsPerCall);
      }
    }
    vcop_calc_new_lk_xy_vloops(context->pBlkIterCalcNewXY);

    _vcop_vloop_done();

    val = *bufSwitchCtrl;
    val_w = (uint32_t)((uint32_t)(val & 0x0000FFFFU) | (uint32_t)((uint32_t)WBUF_SYST << 16U));
    *bufSwitchCtrl = val_w;
    val_w = *bufSwitchCtrl;
    currNumValidPoints = *context->numValidPoints;
    *bufSwitchCtrl = val;

    if(currNumValidPoints > 0)
    {
      __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = (currNumValidPoints-1U);
    }
    else
    {
      break;
    }
  }
  j++;
  /*-----------------------------------------------------------------
    Optimization to hide the ARP32 execution in parallel to VLOOPS
    execution so as to parallelize the computation
  -----------------------------------------------------------------*/
  for(; j < context->kernelArgs.ctrlArgs->maxItersLK; j++)
  {
    if(j ==1U)
    {
      copyLocalXY(context,currImgBuf,localXYIdx,(uint8_t)numKeyPointsPerCall);
    }
    else if(j ==2U)
    {
      getSrcForCurrFrame1(currXYForDma, context->localYCb[i&1U],TempMem2, context->kernelArgs.ctrlArgs->currBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,(uint8_t)qFormatePel,context->kernelArgs.ctrlArgs->searchRange,numKeyPointsPerCall);
    }
    else if(j ==3U)
    {
      getSrcForPrevFrame1(prevXYForDma, context->localYCb[i&1U],TempMem1, context->kernelArgs.ctrlArgs->prevBaseAddr, context->kernelArgs.ctrlArgs->imPitch,context->kernelArgs.ctrlArgs->imHeight,(uint8_t)qFormatePel,numKeyPointsPerCall);
    }
    else if(j ==4U)
    {
      getSrcForCurrFrame2(currXYForDma, context->localXCb[i&1U],TempMem2, &context->kernelArgs.ctrlArgs->srcAddrList[i&1U][numKeyPointsPerCall],context->kernelArgs.ctrlArgs->imWidth,(uint8_t)qFormatePel,context->kernelArgs.ctrlArgs->searchRange, numKeyPointsPerCall);
    }
    else
    {
      if(j ==5U)
      {
        getSrcForPrevFrame2(prevXYForDma, context->localXCb[i&1U],TempMem1, &context->kernelArgs.ctrlArgs->srcAddrList[i&1U][0], context->kernelArgs.ctrlArgs->imWidth,(uint8_t)qFormatePel,numKeyPointsPerCall);
      }
    }
  }
  vcop_copy_new_lk_xy_vloops(context->pBlkCopyNewXY);
  if(context->kernelArgs.ctrlArgs->currLevel == 0)
  {
    *context->numValidPoints = numKeyPointsPerCall;
    __ctrl_vcop_foreach_multiblock_bilinear_interp_7x7_u8[0] = (numKeyPointsPerCall-1U);
    vcop_weight_address_bilinear_interpolation_vloops(context->pBlkWgtAddrForErrMeas);
    vcop_foreach_multiblock_bilinear_interp_7x7_u8_vloops(context->pBlkCurrBiLinForErrMeas);
    vcop_sad_error_measure_lk_vloops(context->pBlkCalcSADErrMeasure);

  }

  context->currIdx++;
  if((i%((uint16_t)NUM_POINTS_IN_DMEM/numKeyPointsPerCall)) == 0)
  {
    EDMA_UTILS_autoIncrement1D_waitInChannel(context->listInDMAContext);
    /*-----------------------------------------------------------------
    The number of key points that needs to be processed (numKeyPoints)
    is not multiple of the number of key points process in (numKeyPointsPerCall)
    each LK tracker kernel, then the last point needs to be duplicated
    to avoid processing any uninitialized points  which may cause
    illegal memory access
    -----------------------------------------------------------------*/
    if((i +((uint16_t)NUM_POINTS_IN_DMEM/numKeyPointsPerCall)) >= (context->kernelArgs.ctrlArgs->numKeyPoints/numKeyPointsPerCall))
    {
      uint16_t currValidPtIdx    = (context->kernelArgs.ctrlArgs->numValidKeyPoints % (uint16_t)NUM_POINTS_IN_DMEM);
      uint16_t totalPts          = ((currValidPtIdx + (numKeyPointsPerCall-1U)) / numKeyPointsPerCall) * numKeyPointsPerCall;

      /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
      /* Pointer is used in arithmetic or array index expression */
      /* Deviation allowed since, this same address needs to be accessed with an offset  */
      uint16_t (*prevXYListPtr)[NUM_POINTS_IN_DMEM]   = (uint16_t (*)[NUM_POINTS_IN_DMEM])(void *)(context->kernelArgs.prevXYList+ (((uint32_t)i +((uint32_t)NUM_POINTS_IN_DMEM/(uint32_t)numKeyPointsPerCall))/(uint32_t)NUM_POINTS_IN_DMEM));
      uint16_t (*currXYListPtr)[NUM_POINTS_IN_DMEM]   = (uint16_t (*)[NUM_POINTS_IN_DMEM])(void *)(context->kernelArgs.currXYList+ (((uint32_t)i +((uint32_t)NUM_POINTS_IN_DMEM/(uint32_t)numKeyPointsPerCall))/(uint32_t)NUM_POINTS_IN_DMEM));
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
      uint16_t loopCnt;

      for(loopCnt = currValidPtIdx; loopCnt < totalPts; loopCnt++)
      {
        (*prevXYListPtr)[(2U*loopCnt)]    = (*prevXYListPtr)[(2U*loopCnt)-2U];
        (*prevXYListPtr)[(2U*loopCnt)+1U] = (*prevXYListPtr)[(2U*loopCnt)-1U];
        (*currXYListPtr)[(2U*loopCnt)]    = (*currXYListPtr)[(2U*loopCnt)-2U];
        (*currXYListPtr)[(2U*loopCnt)+1U] = (*currXYListPtr)[(2u*loopCnt)-1U];
      }
    }
  }
  return 0;
}
#endif




static BAM_Status Bam_LK_Iterative_Loop_control(void *kernelContext, void *kernelCtlArg)
{
  BAM_LK_Iterative_Loop_Context *context = (BAM_LK_Iterative_Loop_Context *) (void*)kernelContext;
  BAM_LK_Iterative_Loop_CtrlArgs * args = (BAM_LK_Iterative_Loop_CtrlArgs *) kernelCtlArg;

  context->ctrlArgs = *args;

  return 0;
}

BAM_KernelExecFuncDef gBAM_TI_lkIterativeLoopExecFunc =
{
  NULL,
  &Bam_LK_Iterative_Loop_initFrame,
  &Bam_LK_Iterative_Loop_computeFrame,
  NULL,
  &Bam_LK_Iterative_Loop_control,
  NULL };


