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
 *  @file       bam_hough_for_lines_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hough for lines
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>
#include "math.h"
#include "bam_hough_for_lines_int.h"
#include "bam_hough_for_lines.h"
#include "vcop_hough_for_lines_kernel.h" /* compiler should take care of include path */

#define PI              (3.14159)

#define NUM_TOTAL_OFFSETS (8U)

static const int16_t sinLutQ8[360]=
{
0, 4, 8, 13, 17, 22, 26, 31,
35, 40, 44, 48, 53, 57, 61, 66,
70, 74, 79, 83, 87, 91, 95, 99,
104, 108, 112, 116, 120, 124, 127, 131,
135, 139, 143, 146, 150, 153, 157, 161,
164, 167, 171, 174, 177, 180, 184, 187,
190, 193, 196, 198, 201, 204, 207, 209,
212, 214, 217, 219, 221, 223, 225, 228,
230, 231, 233, 235, 237, 238, 240, 242,
243, 244, 246, 247, 248, 249, 250, 251,
252, 252, 253, 254, 254, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255,
254, 254, 253, 252, 252, 251, 250, 249,
248, 247, 246, 244, 243, 242, 240, 239,
237, 235, 233, 232, 230, 228, 226, 224,
221, 219, 217, 214, 212, 209, 207, 204,
201, 199, 196, 193, 190, 187, 184, 181,
178, 174, 171, 168, 164, 161, 157, 154,
150, 147, 143, 139, 135, 132, 128, 124,
120, 116, 112, 108, 104, 100, 96, 92,
87, 83, 79, 75, 70, 66, 62, 57,
53, 49, 44, 40, 36, 31, 27, 22,
18, 13, 9, 4, 0, -4, -8, -12,
-17, -21, -26, -30, -35, -39, -44, -48,
-52, -57, -61, -65, -70, -74, -78, -82,
-87, -91, -95, -99, -103, -107, -111, -115,
-119, -123, -127, -131, -135, -139, -142, -146,
-150, -153, -157, -160, -164, -167, -170, -174,
-177, -180, -183, -186, -189, -192, -195, -198,
-201, -204, -206, -209, -211, -214, -216, -219,
-221, -223, -225, -227, -229, -231, -233, -235,
-237, -238, -240, -241, -243, -244, -245, -247,
-248, -249, -250, -251, -252, -252, -253, -254,
-254, -254, -255, -255, -255, -255, -255, -255,
-255, -255, -255, -255, -254, -254, -253, -252,
-252, -251, -250, -249, -248, -247, -246, -245,
-243, -242, -240, -239, -237, -235, -234, -232,
-230, -228, -226, -224, -222, -219, -217, -215,
-212, -210, -207, -204, -202, -199, -196, -193,
-190, -187, -184, -181, -178, -175, -171, -168,
-165, -161, -158, -154, -151, -147, -143, -140,
-136, -132, -128, -124, -120, -116, -112, -108,
-104, -100, -96, -92, -88, -84, -79, -75,
-71, -67, -62, -58, -53, -49, -45, -40,
-36, -31, -27, -23, -18, -14, -9, -5};

static const int16_t cosLutQ8[360] =
{256, 255, 255, 255, 255, 255, 254, 254,
253, 252, 252, 251, 250, 249, 248, 247,
246, 244, 243, 242, 240, 239, 237, 235,
233, 232, 230, 228, 226, 223, 221, 219,
217, 214, 212, 209, 207, 204, 201, 199,
196, 193, 190, 187, 184, 181, 177, 174,
171, 168, 164, 161, 157, 154, 150, 146,
143, 139, 135, 131, 128, 124, 120, 116,
112, 108, 104, 100, 96, 91, 87, 83,
79, 75, 70, 66, 62, 57, 53, 49,
44, 40, 35, 31, 26, 22, 18, 13,
9, 4, 0, -4, -8, -13, -17, -22,
-26, -30, -35, -39, -44, -48, -52, -57,
-61, -66, -70, -74, -78, -83, -87, -91,
-95, -99, -103, -107, -111, -115, -119, -123,
-127, -131, -135, -139, -142, -146, -150, -153,
-157, -160, -164, -167, -171, -174, -177, -180,
-183, -187, -190, -192, -195, -198, -201, -204,
-206, -209, -212, -214, -216, -219, -221, -223,
-225, -227, -229, -231, -233, -235, -237, -238,
-240, -241, -243, -244, -245, -247, -248, -249,
-250, -251, -252, -252, -253, -254, -254, -254,
-255, -255, -255, -255, -255, -255, -255, -255,
-255, -255, -254, -254, -253, -252, -252, -251,
-250, -249, -248, -247, -246, -244, -243, -242,
-240, -239, -237, -235, -234, -232, -230, -228,
-226, -224, -221, -219, -217, -214, -212, -209,
-207, -204, -202, -199, -196, -193, -190, -187,
-184, -181, -178, -174, -171, -168, -164, -161,
-158, -154, -150, -147, -143, -139, -136, -132,
-128, -124, -120, -116, -112, -108, -104, -100,
-96, -92, -88, -83, -79, -75, -71, -66,
-62, -58, -53, -49, -45, -40, -36, -31,
-27, -22, -18, -14, -9, -5, 0, 3,
8, 12, 17, 21, 26, 30, 35, 39,
43, 48, 52, 56, 61, 65, 69, 74,
78, 82, 86, 91, 95, 99, 103, 107,
111, 115, 119, 123, 127, 131, 135, 138,
142, 146, 149, 153, 157, 160, 164, 167,
170, 174, 177, 180, 183, 186, 189, 192,
195, 198, 201, 204, 206, 209, 211, 214,
216, 219, 221, 223, 225, 227, 229, 231,
233, 235, 237, 238, 240, 241, 243, 244,
245, 247, 248, 249, 250, 251, 251, 252,
253, 253, 254, 254, 255, 255, 255, 255};


/* Function Prototypes */
static BAM_Status Bam_HoughForLines_initFrame(void *kernelContext);
static BAM_Status Bam_HoughForLines_computeFrame(void *kernelContext);
static BAM_Status Bam_HoughForLines_control(void *kernelContext,
                                                        void * kernelCtlArg);

static BAM_Status Bam_HoughForLines_initFrame(void *kernelContext)
{
  BAM_HoughForLines_Context *context = (BAM_HoughForLines_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;
  int16_t  (*pCosSinMulNorm)[2];
  int32_t    tempData;
  uint32_t  diameterQ8;
  uint32_t  interimTransposeStride;
  uint16_t  (*offsetPtr)[NUM_TOTAL_OFFSETS];
  uint32_t  i;

#if !(VCOP_HOST_EMULATION)
  context->paramBlockKernel1 = (uint16_t * ) context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_PARAMS_IDX];
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
    rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->paramBlockKernel2 = context->paramBlockKernel1 +  vcop_hough_for_lines_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */
#endif

  offsetPtr = (uint16_t (*)[NUM_TOTAL_OFFSETS])(void *)context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX];
  interimTransposeStride = ((( (ALIGN_2SIMD((uint32_t)context->kernelArgs.rhoMaxLength) *
                                          sizeof(uint16_t)) / 2U ) / 4U) + 1U ) * 4U;

  for ( i = 0; i < 8U ; i++)
  {
    (*offsetPtr)[i] = (uint16_t)(interimTransposeStride * i);
  }

  pCosSinMulNorm = (int16_t (*)[2])context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX];

  /*ping Buffer */
  context->pCosSinMulNorm[0] = *pCosSinMulNorm;
  /*pong Buffer */
  /* CHECK_MISRA("-17.4")  -> Disable rule 17.4  */
  /* MISRA.PTR.ARITH :   Array indexing shall be the only allowed form of pointer arithmetic */
  /* This is acceptable because of the hardware supported alias memory view and hence the same buffer is available at two different memory location   */
  context->pCosSinMulNorm[1] = context->pCosSinMulNorm[0] + (HOUGH_FOR_LINES_IMG_BUF_A_B_OFFSET / 2U);
  /* RESET_MISRA("17.4")  -> Reset rule 17.4     */

  context->pingPong = 0;


  context->currThetaIdx   = context->kernelArgs.thetaStart;

  diameterQ8 = SQRTof2_Q8 * max( context->kernelArgs.imgWidth,
                                    context->kernelArgs.imgHeight);

  context->normalizationFactorQ8 = ((uint32_t)context->kernelArgs.rhoMaxLength << 16) / (2U * diameterQ8);

  tempData = (int32_t)cosLutQ8[context->currThetaIdx] * context->normalizationFactorQ8;
  (*pCosSinMulNorm)[0] = (int16_t) (tempData / 2) ;

  tempData = (int32_t)sinLutQ8[context->currThetaIdx] * context->normalizationFactorQ8;
  (*pCosSinMulNorm)[1] = (int16_t)(tempData / 2);

  context->pingPong ^= 1U;

#if (!VCOP_HOST_EMULATION)
  vcop_hough_for_lines_init(
    context->pInBlock[BAM_HOUGH_FOR_LINES_EDGE_LIST_PORT],
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX],
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX],
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX],
    context->kernelArgs.listSize,
    context->kernelArgs.rhoMaxLength,
    context->paramBlockKernel1
  );

  vcop_merge_voted_rho_array_init(
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX],
    context->pInBlock[BAM_HOUGH_FOR_LINES_VOTED_RHO_THETA_IN_PORT],/* Output Pointer is same as Input pointer given */
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX],/* Reusing buffer from kernel 1 */
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX],
    context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX],
    context->kernelArgs.rhoMaxLength,
    context->paramBlockKernel2
    );

#endif


    return status;
}

static BAM_Status Bam_HoughForLines_computeFrame(void *kernelContext)
{
    BAM_HoughForLines_Context *context = (BAM_HoughForLines_Context *) kernelContext;
    int16_t  (*pCosSinMulNorm)[2];
    int32_t    tempData;

#if (VCOP_HOST_EMULATION)

    vcop_hough_for_lines(
      context->pInBlock[BAM_HOUGH_FOR_LINES_EDGE_LIST_PORT],
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX],
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX],
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX],
      context->kernelArgs.listSize,
      context->kernelArgs.rhoMaxLength
    );

    vcop_merge_voted_rho_array(
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX],
      context->pInBlock[BAM_HOUGH_FOR_LINES_VOTED_RHO_THETA_IN_PORT],/* Output Pointer is same as Input pointer given */
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX],/* Reusing buffer from kernel 1 */
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX],
      context->pInternalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX],
      context->kernelArgs.rhoMaxLength
      );

      /* For Host Emulation No ping pong buffering */
      context->pingPong = 0;

#else
    vcop_hough_for_lines_vloops(context->paramBlockKernel1);
    vcop_merge_voted_rho_array_vloops(context->paramBlockKernel2);
#endif

  context->currThetaIdx += context->kernelArgs.thetaStepSize;

  if ( context->currThetaIdx > context->kernelArgs.thetaEnd )
  {
    context->currThetaIdx = 0;
  }

  pCosSinMulNorm = (int16_t (*)[2])(void *)context->pCosSinMulNorm[context->pingPong];


  tempData = (int32_t)cosLutQ8[context->currThetaIdx] * context->normalizationFactorQ8;
  (*pCosSinMulNorm)[0] = (int16_t) (tempData / 2) ;

  tempData = (int32_t)sinLutQ8[context->currThetaIdx] * context->normalizationFactorQ8;
  (*pCosSinMulNorm)[1] = (int16_t)(tempData / 2);

  context->pingPong^= 1U;

  return BAM_S_SUCCESS;
}

static BAM_Status Bam_HoughForLines_control(void *kernelContext,
                                                        void * kernelCtlArg)
{
  BAM_HoughForLines_Context *context = (BAM_HoughForLines_Context *) kernelContext;

  BAM_HoughForLines_CtrlArgs * ctrlArgs = (BAM_HoughForLines_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelArgs = *ctrlArgs;

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_houghForLinesExecFunc =
{
  NULL,
  &Bam_HoughForLines_initFrame,
  &Bam_HoughForLines_computeFrame,
  NULL,
  &Bam_HoughForLines_control,
  NULL
};


