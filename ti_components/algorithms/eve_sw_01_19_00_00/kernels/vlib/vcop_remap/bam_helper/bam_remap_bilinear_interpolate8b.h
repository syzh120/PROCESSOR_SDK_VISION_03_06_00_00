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
 *  @file       bam_remap_bilinear_interpolate8b.h
 *
 *  @brief      This header defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#ifndef BAM_REMAP_BILINEAR_INTERPOLATE8B_H_
#define BAM_REMAP_BILINEAR_INTERPOLATE8B_H_

typedef struct bam_remap_bilinear_interpolate8b_ctrlArgs
{
  uint32_t      maxInBlockSize;
  uint16_t      maxInputBlockStride;
  uint8_t       byPassInput;
} BAM_RemapBilinearInterpolate8b_ctrlArgs;


typedef struct bam_remap_bilinear_interpolate8b_args
{
  uint16_t      outBlockWidth;
  uint16_t      outBlockHeight;
  uint8_t       mnQShift;
  uint8_t       oQShift;
  uint16_t      qScale;
  uint8_t       mult;
  uint8_t       rightShift;
  int64_t       sat_high;
  int64_t       sat_high_set;
  int64_t       sat_low;
  int64_t       sat_low_set;
  BAM_RemapBilinearInterpolate8b_ctrlArgs ctrlArgs;
} BAM_RemapBilinearInterpolate8b_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_remapBilinearInterpolate8bHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_remapBilinearInterpolate8bExecFunc;

extern BAM_KernelInfo gBAM_TI_remapBilinearInterpolate8bKernel;

#define BAM_REMAP_BILINEAR_INTERPOLATE8B_INPUT_PORT   (0U)
#define BAM_REMAP_BILINEAR_INTERPOLATE8B_LUT_PORT     (1U)


#define BAM_REMAP_BILINEAR_INTERPOLATE8B_OUTPUT_PORT  (0U)


#endif /* BAM_REMAP_BILINEAR_INTERPOLATE8B_H_ */

