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
 *  @file       bam_nms_s16_to_list_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integratingfor integrating the combination of
 *                NMS 16 bit signed kernel and bin to image list kernel  into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nms_s16_to_list.h"
#include "bam_nms_s16_to_list_int.h"
#include "vcop_nonMaxSuppress_mxn_16s_kernel.h"

static int32_t get_nmsBinPackPtrParamBlockOffset(
        uint16_t pblock[],
        uint16_t    numParamCount,
        uint32_t    dstPtr1,
        uint32_t    dstPtr2,
        uint16_t    *dstPtrOffset1,
        uint16_t    *dstPtrOffset2
);

static int32_t get_nmsBinPackPtrParamBlockOffset(
        uint16_t pblock[],
        uint16_t    numParamCount,
        uint32_t    dstPtr1,
        uint32_t    dstPtr2,
        uint16_t    *dstPtrOffset1,
        uint16_t    *dstPtrOffset2
)
{
    uint16_t i;
    uint32_t *p;
    int32_t status= 0;
    uint16_t offsetFound1 = 0;
    uint16_t offsetFound2 = 0;

    p = (uint32_t*)(void *)pblock;

    for (i = 0; i < (numParamCount / 2U); i++)
    {
        /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
        /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
        /*  Apriory we cannot know the size of param block and hence cannot put a restriction here on pointer "p"   */
        if ( (p[i] == dstPtr1 ) && (offsetFound1 == 0)) {
            *dstPtrOffset1 = i;
            offsetFound1 = 1U;
        }
        if ( ( p[i]== dstPtr2 ) && (offsetFound2 == 0)) {
            *dstPtrOffset2= i;
            offsetFound2 = 1U;
        }
        /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
    }

    if ((offsetFound1 == 0) || (offsetFound2 == 0)) {
        status = -1;
    }

    return status;
}
/* Function Prototypes */
static BAM_Status BAM_Nms16sToList_initFrame(void *kernelContext);
static BAM_Status BAM_Nms16sToList_compute(void *kernelContext);

static BAM_Status BAM_Nms16sToList_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_Nms16sToList_control(void *kernelContext, void *kernelCtlArg){

    BAM_Nms_16s_to_list_Context  *context = (BAM_Nms_16s_to_list_Context *) kernelContext;
    BAM_Bin_image_to_list_Context  *binImgToListContext = &context->binImgToListContext;
    BAM_NonMaxSuppress_mxn_S16bitPack_Context  *nms16sbitPackContext= &context->nms16sbitPackContext;

    BAM_Nms_16s_to_list_CtrlArgs *ctrlArgs  = (BAM_Nms_16s_to_list_CtrlArgs *) kernelCtlArg;

    context->kernelArgs = *ctrlArgs;

    gBAM_TI_binImageToListExecFunc.kernelCtl(binImgToListContext, &ctrlArgs->binToImgListKernelArgs);

    gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc.kernelCtl(nms16sbitPackContext, &ctrlArgs->nmsMxnS16bitPackKernelArgs);

    context->blockCount = 0;
    context->numHorzBlocks  = (ctrlArgs->binToImgListKernelArgs.blkWidth +
                               (ctrlArgs->nmsMxnS16bitPackKernelArgs.computeWidth - 1)) /
                               ctrlArgs->nmsMxnS16bitPackKernelArgs.computeWidth;

    return BAM_S_SUCCESS;
}

static BAM_Status BAM_Nms16sToList_initFrame(void *kernelContext)
{
  BAM_Status status = BAM_S_SUCCESS;
  BAM_Nms_16s_to_list_Context            *context = (BAM_Nms_16s_to_list_Context *)kernelContext;
  BAM_Bin_image_to_list_Context  *binImgToListContext = &context->binImgToListContext;
  BAM_NonMaxSuppress_mxn_S16bitPack_Context  *nms16sbitPackContext= &context->nms16sbitPackContext;
  uint8_t * outBufPtr1;
  uint8_t * outBufPtr2;
  context->pingPongFlag = 0;

  gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc.kernelInitFrame(nms16sbitPackContext);
  gBAM_TI_binImageToListExecFunc.kernelInitFrame(binImgToListContext);

  context->pNmsBinPackDstOffset[0] = (uint16_t *)context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_DSTPTR_OFFSET_IDX];
#if !VCOP_HOST_EMULATION
  /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
  /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
  /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
  context->pNmsBinPackDstOffset[1] = context->pNmsBinPackDstOffset[0] + (NMS_16S_IMG_BUF_A_B_OFFSET / sizeof(uint16_t));
  /* RESET_MISRA("17.4")  -> Reset rule 17.4     */

#else
  context->pNmsBinPackDstOffset[1] = context->pNmsBinPackDstOffset[0];
#endif
  if ( context->numHorzBlocks == 1 )
  {
    context->nmsBinPackblockJump =  0;
  }
  else
  {
    context->nmsBinPackblockJump =  context->kernelArgs.nmsMxnS16bitPackKernelArgs.computeWidth / 8;
  }

  *(context->pNmsBinPackDstOffset[context->pingPongFlag]) = context->nmsBinPackblockJump;
  context->pingPongFlag ^= 1U;

#if (!VCOP_HOST_EMULATION)
  outBufPtr1 = context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_BINPACK_BUF_IDX];
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  This operation is done to mimic the behavior in which param block enteries are calculated inside the _init call. Hence it can be waived    */
  outBufPtr2 = outBufPtr1 + ((context->kernelArgs.nmsMxnS16bitPackKernelArgs.outStride / 8) * sizeof(uint8_t));
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
       The address space is 32 bit and type casting to integer will not result into any loss because of TI's
     compiler teratment to integer.  Here outBufPtr1 and outBufPtr2 are stored in param block memory as addresses
     and hence we need to cast to int to get the address */

  status = get_nmsBinPackPtrParamBlockOffset(context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_NMSBINPACK_PARAM_IDX],
                                      context->numNms16sbitPackParamCnt,
                                      (uint32_t)(void *)outBufPtr1,
                                      (uint32_t)(void *)outBufPtr2,
                                      &context->nmsBinPackPrmBlockOffset1,
                                      &context->nmsBinPackPrmBlockOffset2);
  /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

  if ( status == 0 )
  {
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type*/
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
       The address space is 32 bit and type casting to integer will not result into any loss because of TI's
       compiler teratment to integer.  Here outBufPtr1 and outBufPtr2 are stored in param block memory as addresses
       and hence we need to cast to int to get the address */

    vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_init(
              context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_NMSBINPACK_PARAM_IDX],/*Param Block from which one entry needs to be updated */
              (uint32_t)(void *)outBufPtr1,/*Destination Pointer (pointer to binPackData) address */
              (uint32_t)(void *)outBufPtr2,/*Destination Pointer (pointer to binPackData) address */
              context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_DSTPTR_OFFSET_IDX],/*Offset that needs to be addted to destination pointer */
              context->nmsBinPackPrmBlockOffset1,/* Offset in param block where the destination address is actually stored */
              context->nmsBinPackPrmBlockOffset2,/* Offset in param block where the destination address is actually stored */
              context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_UPDATE_DST_PARAM_IDX]);/*Param Block of this kernel*/

    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

    status = BAM_S_SUCCESS;
  }
  else
  {
    status = BAM_E_FAIL;
  }

#endif

  return status;
}

static BAM_Status BAM_Nms16sToList_compute(void *kernelContext)
{
  BAM_Nms_16s_to_list_Context            *context =  (BAM_Nms_16s_to_list_Context *)kernelContext;
  BAM_Bin_image_to_list_Context  *binImgToListContext = &context->binImgToListContext;
  BAM_NonMaxSuppress_mxn_S16bitPack_Context  *nms16sbitPackContext= &context->nms16sbitPackContext;

#if (!VCOP_HOST_EMULATION)
  gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc.kernelCustom(nms16sbitPackContext->pInternalBlock[0]);
  vcop_nonMaxSuppress_mxn_16sUpdateDstPtr_vloops(context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_UPDATE_DST_PARAM_IDX]);
#else
  gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc.kernelCompute(nms16sbitPackContext);

  nms16sbitPackContext->pOutBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT] =
    (uint8_t*)((uint32_t)context->pInternalBlock[NMS_MXN_S16_TO_LIST_INTERNAL_BINPACK_BUF_IDX] +
              context->nmsBinPackblockJump);

#endif

  context->blockCount++;

  if ( context->blockCount == (context->numHorzBlocks - 1U))
  {
    context->nmsBinPackblockJump = 0;
  }
  else
  {
    if (  context->numHorzBlocks == 1 )
    {
      context->nmsBinPackblockJump = 0;
    }
    else
    {
      context->nmsBinPackblockJump += (context->kernelArgs.nmsMxnS16bitPackKernelArgs.computeWidth / 8 );
    }
  }

  *(context->pNmsBinPackDstOffset[context->pingPongFlag]) = context->nmsBinPackblockJump;
  context->pingPongFlag ^= 1U ;

  if ( context->blockCount == context->numHorzBlocks )
  {
#if (!VCOP_HOST_EMULATION)
    gBAM_TI_binImageToListExecFunc.kernelCustom(binImgToListContext->pInternalBlock[0]);
#else
    gBAM_TI_binImageToListExecFunc.kernelCompute(binImgToListContext);
#endif
    context->blockCount = 0;
  }

  return BAM_S_SUCCESS;
}

BAM_KernelExecFuncDef gBAM_TI_nms16sToListExecFunc =
{
  NULL,
  &BAM_Nms16sToList_initFrame,
  &BAM_Nms16sToList_compute,
  NULL,
  &BAM_Nms16sToList_control,
  NULL
};


