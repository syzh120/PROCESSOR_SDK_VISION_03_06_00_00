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

/*                                                                          */
/*     @file : vcop_sad_error_measure_lk_host.c                             */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for SAD Based Error Measure for LK: */
/*           vcop_sad_error_measure_lk_init - Copies arguments to           */
/*             parameter block memory                                       */
/*           vcop_sad_error_measure_lk_vloops - Invokes the API namely      */
/*             vcop_sad_error_measure_lk defined in kernel file by          */
/*             passing the arguments from parameter block memory            */
/*                                                                          */
/*  @version 1.0 (January 2014) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdint.h>
#include "vcop.h"

#include "vcop_sad_error_measure_lk_cn.h"

#if VCOP_HOST_EMULATION
void vcop_sad_error_measure_lk
(
   __vptr_uint8      pPrevBiLinImg_A   ,
   __vptr_uint8      pCurrBiLinImg_B   ,
   __vptr_uint16     pNewXYList_X      ,
   __vptr_uint16     pOutErrorMeasure_C,
   uint16_t          inputStride       ,
   uint16_t          frmWidth          ,
   uint16_t          frmHeight         ,
   uint16_t          blkWidth          ,
   uint16_t          blkHeight         ,
   uint16_t          numKeyPoints      ,
   uint16_t          shiftValue        ,
   __vptr_uint16     scratch_a         ,
   uint16_t          sadThreshold      ,
   __vptr_uint16     numValidPointsWbuf,
   __vptr_uint16     numValidPointsIbuf
);

typedef struct _vcop_sad_error_measure_lk_args
{
   uint16_t          inputStride ;
   uint16_t          frmWidth    ;
   uint16_t          frmHeight   ;
   uint16_t          blkWidth    ;
   uint16_t          blkHeight   ;
   uint16_t          numKeyPoints;
   uint16_t          shiftValue  ;
   uint16_t          sadThreshold;
} VCOP_SAD_ERROR_MEASURE_LK_Args;

typedef struct _vcop_sad_error_measure_lk_context
{
    void *pInBlock[3] ;
    void *pOutBlock[2];
    void *pInternalBlock[2];
    VCOP_SAD_ERROR_MEASURE_LK_Args kernelArgs;
} VCOP_SAD_ERROR_MEASURE_LK_Context;

unsigned short __pblock_vcop_sad_error_measure_lk[sizeof(VCOP_SAD_ERROR_MEASURE_LK_Context)/sizeof(uint16_t)];

unsigned int vcop_sad_error_measure_lk_init(
   __vptr_uint8      pPrevBiLinImg_A   ,
   __vptr_uint8      pCurrBiLinImg_B   ,
   __vptr_uint16     pNewXYList_X      ,
   __vptr_uint16     pOutErrorMeasure_C,
   uint16_t          inputStride       ,
   uint16_t          frmWidth          ,
   uint16_t          frmHeight         ,
   uint16_t          blkWidth          ,
   uint16_t          blkHeight         ,
   uint16_t          numKeyPoints      ,
   uint16_t          shiftValue        ,
   __vptr_uint16     scratch_a         ,
   uint16_t          sadThreshold      ,
   __vptr_uint16     numValidPointsWbuf,
   __vptr_uint16     numValidPointsIbuf,
   uint16_t          pblock[])
{
    int retVal = 0;

    VCOP_SAD_ERROR_MEASURE_LK_Context *sadErrorMeasureLKHostContext = (VCOP_SAD_ERROR_MEASURE_LK_Context *)pblock;

    sadErrorMeasureLKHostContext->pInBlock[0]                 = pPrevBiLinImg_A.addr   ;
    sadErrorMeasureLKHostContext->pInBlock[1]                 = pCurrBiLinImg_B.addr   ;
    sadErrorMeasureLKHostContext->pInBlock[2]                 = pNewXYList_X.addr      ;
    sadErrorMeasureLKHostContext->pOutBlock[0]                = pOutErrorMeasure_C.addr;
    sadErrorMeasureLKHostContext->pOutBlock[1]                = numValidPointsIbuf.addr;
    sadErrorMeasureLKHostContext->pInternalBlock[0]           = scratch_a.addr         ;
    sadErrorMeasureLKHostContext->pInternalBlock[1]           = numValidPointsWbuf.addr;
    sadErrorMeasureLKHostContext->kernelArgs.inputStride      = inputStride            ;
    sadErrorMeasureLKHostContext->kernelArgs.frmWidth         = frmWidth               ;
    sadErrorMeasureLKHostContext->kernelArgs.frmHeight        = frmHeight              ;
    sadErrorMeasureLKHostContext->kernelArgs.blkWidth         = blkWidth               ;
    sadErrorMeasureLKHostContext->kernelArgs.blkHeight        = blkHeight              ;
    sadErrorMeasureLKHostContext->kernelArgs.numKeyPoints     = numKeyPoints           ;
    sadErrorMeasureLKHostContext->kernelArgs.shiftValue       = shiftValue             ;
    sadErrorMeasureLKHostContext->kernelArgs.sadThreshold     = sadThreshold           ;

#ifdef NATC
{
/* Zero out the partial results for validPoints to closely match the behaviour of the kernel-C function*/
    int32_t i;
    for (i = 0U; i < VCOP_SIMD_WIDTH; i++ ) {
        numValidPointsIbuf.addr[i]= 0;
        numValidPointsWbuf.addr[i]= 0;
    }
}
#endif

    return retVal;
}

void vcop_sad_error_measure_lk_vloops(unsigned short pblock[])
{
    VCOP_SAD_ERROR_MEASURE_LK_Context *sadErrorMeasureLKHostContext = (VCOP_SAD_ERROR_MEASURE_LK_Context *)pblock;

#ifdef NATC
    /* Iterate VCOP_SIMD_WIDTH/2 to capture the trailing 0s as the dma write node will add VCOP_SIMD_WIDTH numbers of uint16_t partial results since
            it is what the kernel-C function produces
       */
    int32_t i;
    for (i = 0U; i < VCOP_SIMD_WIDTH/2; i++ ) {
        *((uint32_t*)sadErrorMeasureLKHostContext->pOutBlock[1] + i)= *((uint32_t*)sadErrorMeasureLKHostContext->pInternalBlock[1] + i);
        }

    vcop_sad_error_measure_lk_cn((unsigned char *)sadErrorMeasureLKHostContext->pInBlock[0],
                              (unsigned char *)sadErrorMeasureLKHostContext->pInBlock[1],
                              (unsigned short *)sadErrorMeasureLKHostContext->pInBlock[2],
                              (unsigned short *)sadErrorMeasureLKHostContext->pOutBlock[0],
                              sadErrorMeasureLKHostContext->kernelArgs.inputStride,
                              sadErrorMeasureLKHostContext->kernelArgs.frmWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.frmHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.blkWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.blkHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.numKeyPoints,
                              sadErrorMeasureLKHostContext->kernelArgs.shiftValue,
                              sadErrorMeasureLKHostContext->kernelArgs.sadThreshold,
                              (unsigned short *)sadErrorMeasureLKHostContext->pOutBlock[1]);

    for (i = 0U; i < VCOP_SIMD_WIDTH/2; i++ ) {
        *((uint32_t*)sadErrorMeasureLKHostContext->pInternalBlock[1] + i)= *((uint32_t*)sadErrorMeasureLKHostContext->pOutBlock[1] + i);
        }
#else
    vcop_sad_error_measure_lk(sadErrorMeasureLKHostContext->pInBlock[0],
                              sadErrorMeasureLKHostContext->pInBlock[1],
                              sadErrorMeasureLKHostContext->pInBlock[2],
                              sadErrorMeasureLKHostContext->pOutBlock[0],
                              sadErrorMeasureLKHostContext->kernelArgs.inputStride,
                              sadErrorMeasureLKHostContext->kernelArgs.frmWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.frmHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.blkWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.blkHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.numKeyPoints,
                              sadErrorMeasureLKHostContext->kernelArgs.shiftValue,
                              sadErrorMeasureLKHostContext->pInternalBlock[0],
                              sadErrorMeasureLKHostContext->kernelArgs.sadThreshold,
                              sadErrorMeasureLKHostContext->pInternalBlock[1],
                              sadErrorMeasureLKHostContext->pOutBlock[1]);
#endif
}

unsigned int vcop_sad_error_measure_lk_param_count(void)
{
    return (sizeof(VCOP_SAD_ERROR_MEASURE_LK_Context));
}
#endif
