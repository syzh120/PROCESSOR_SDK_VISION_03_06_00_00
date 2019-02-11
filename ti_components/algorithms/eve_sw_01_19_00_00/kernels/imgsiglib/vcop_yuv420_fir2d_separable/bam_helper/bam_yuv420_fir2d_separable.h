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
 *  @file       bam_yuv420_fir2d_separable.h
 *
 *  @brief      This header defines interfaces for integrating YUV420 2d FIR filter kernel
 *              into BAM.
 */

#ifndef BAM_YUV420_FIR2D_SEPARABLE_H_
#define BAM_YUV420_FIR2D_SEPARABLE_H_

#define BAM_YUV420_FIR2D_MAX_COEFF_WIDTH   (3U)
#define BAM_YUV420_FIR2D_MAX_COEFF_HEIGHT  (3U)
#define BAM_YUV420_FIR2D_MAX_COEFF_SIZE  (BAM_YUV420_FIR2D_MAX_COEFF_WIDTH * BAM_YUV420_FIR2D_MAX_COEFF_HEIGHT)


typedef struct bam_yuv420_fir2dseparable_args
{
  uint16_t blockWidth;         /* width of input block, in elements */
  uint16_t pitch;        /* offset between input lines, in elems*/
  uint16_t blockHeight;         /* height of input block*/
  uint8_t  coefWidth;     /* width of coef block, in elements*/
  uint8_t  coefHeight;     /* width of coef block, in elements*/
  uint8_t  (*coefPtr)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE];     /* width of coef block, in elements*/
  uint16_t rndBits;      /* bit position for rounding*/
} BAM_Yuv420_fir2dseparable_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_yuv420Fir2dSeparableYHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableYExecFunc;

extern BAM_KernelInfo gBAM_TI_yuv420Fir2dSeparableYKernel;


extern BAM_KernelHelperFuncDef gBAM_TI_yuv420Fir2dSeparableUvHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableUvExecFunc;

extern BAM_KernelInfo gBAM_TI_yuv420Fir2dSeparableUvKernel;

#define BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT     (0)

#define BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT    (0)


#endif /* BAM_YUV420_FIR2D_SEPARABLE_H_ */

