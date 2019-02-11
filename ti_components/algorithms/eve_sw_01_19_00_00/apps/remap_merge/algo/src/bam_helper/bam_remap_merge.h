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
 *  @file       bam_remap_merge.h
 *
 *  @brief     This header defines interfaces for integrating the combination of
 *                Remap, Format Convert and Merge kernels into BAM.
 */

#ifndef BAM_REMAP_MERGE_H_
#define BAM_REMAP_MERGE_H_

#include "remap.h"
#include "remap_common.h"
#include "bam_remap.h"                        /* KERNEL NODE  */
#include "bam_memcpy.h"                       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv420nv12.h"       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv422i.h"          /* KERNEL NODE  */
#include "bam_yuv_420nv12_to_422uyvy.h"       /* KERNEL NODE  */
#include "bam_yuv_422uyvy_to_420nv12.h"       /* KERNEL NODE  */


/** ========================================================
 *  @name   BAM_Remap_Merge_Args
 *
 *  @desc   This structure specifies the properties needed for configuring DMA
 *
 *  @field remapKernelArgs
 *          parameters to configure Remap kernel
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  @field dstFormat
 *          Format of output
 *
 *  @field memcpyKernelArgs
 *          parameters to configure Memcpy kernel
 *
 *  @field formatConvertKernelArgs
 *          parameters to configure Format Convert kernel
 *
 *  @field alphaBlendKernelArgs
 *          parameters to configure Alpha Blend kernel
 *  ===============================================================
 */
typedef struct bam_remap_merge_args
{
    BAM_Remap_Args                    remapKernelArgs;
    uint8_t                           enableMerge;
    Format                            dstFormat;
    BAM_Memcpy_Args                   memcpyKernelArgs;
    BAM_Yuv_420nv12_to_422uyvy_Args   formatConvertKernelArgs;
    BAM_Alpha_Blend_YUV420nv12_Args   alphaBlendKernelArgs;
} BAM_Remap_Merge_Args;


extern BAM_KernelHelperFuncDef gBAM_TI_remapMergeHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_remapMergeExecFunc;

extern BAM_KernelInfo gBAM_TI_remapMergeKernel;

#define BAM_REMAP_MERGE_INPUT_PORT_IMAGE_BLOCK     (0U)
#define BAM_REMAP_MERGE_INPUT_PORT_LUT             (1U)
#define BAM_REMAP_MERGE_INPUT_PORT_MERGE_BLOCK     (2U)
#define BAM_REMAP_MERGE_INPUT_PORT_ALPHA_BLOCK     (3U)

#define BAM_REMAP_MERGE_OUTPUT_PORT                (0U)


#endif /* BAM_REMAP_MERGE_H_ */

