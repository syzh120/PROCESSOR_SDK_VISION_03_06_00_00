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
 *  @file       bam_yuv_420nv12_to_422uyvy_int.h
 *
 *  @brief      This header defines internal structures for YUV420 NV12
 *              to YUV422 UYVY format conversion into BAM.
 */

#ifndef BAM_YUV_420NV12_TO_422UYVY_INT_H
#define BAM_YUV_420NV12_TO_422UYVY_INT_H

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_yuv_420nv12_to_422uyvy.h"

#ifndef NATC
#define NATC 0
#endif

#define YUV_420NV12_TO_422UYVY_NUM_IN_BLOCKS       (1U)
#define YUV_420NV12_TO_422UYVY_NUM_OUT_BLOCKS      (1U)
#define YUV_420NV12_TO_422UYVY_NUM_INTERNAL_BLOCKS (1U)

#define YUV_420NV12_TO_422UYVY_IN_IMG_IDX (BAM_YUV_420NV12_TO_422UYVY_INPUT_PORT_IMG)      /* 0 */
#define YUV_420NV12_TO_422UYVY_OUT_IDX    (BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT)         /* 0 */
#define PARAMS_IDX (0U)                                            /* 0 */


typedef struct bam_yuv_420nv12_to_422uyvy_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[YUV_420NV12_TO_422UYVY_NUM_INTERNAL_BLOCKS];
    void *pInBlock[YUV_420NV12_TO_422UYVY_NUM_IN_BLOCKS];
    void *pOutBlock[YUV_420NV12_TO_422UYVY_NUM_OUT_BLOCKS];
    BAM_Yuv_420nv12_to_422uyvy_Args kernelArgs;
} BAM_Yuv_420nv12_to_422uyvy_Context;

#endif /* BAM_YUV_420NV12_TO_422UYVY_INT_H */

