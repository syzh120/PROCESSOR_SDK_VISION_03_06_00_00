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
 *  @file       bam_nms_s16_to_list.h
 *
 *  @brief     This header defines interfaces for integrating the combination of
 *                NMS 16 bit signed kernel and bin to image list kernel  into BAM.
 */

#ifndef BAM_NMS_S16_TO_LIST_H_
#define BAM_NMS_S16_TO_LIST_H_

#include "bam_bin_image_to_list.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack.h"

#define NMS_16S_IMG_BUF_A_B_OFFSET (0x20000U)


/** ========================================================
 *  @name   BAM_Nms_16s_to_list_Args
 *
 *  @desc   This structure specifies the properties needed for configuring NMS 16 bit signed kernel
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
typedef struct bam_nms16s_to_list_ctrlargs
{
  BAM_Bin_image_to_list_ctrlArgs              binToImgListKernelArgs;
  BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs   nmsMxnS16bitPackKernelArgs;
} BAM_Nms_16s_to_list_CtrlArgs;


extern BAM_KernelHelperFuncDef gBAM_TI_nms16sToListHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_nms16sToListExecFunc;

extern BAM_KernelInfo gBAM_TI_nms16sToListKernel;

typedef enum
{
  BAM_NMS_MXN_S16_TO_LIST_INPUT_BLOCK_PORT   =   0,
  BAM_NMS_MXN_S16_TO_LIST_NUM_INPUT_BLOCKS
} eBAM_NMS_MXN_S16_TO_LIST_INPUT_PORTS;

typedef enum
{
  BAM_NMS_MXN_S16_TO_LIST_OUTPUT_XY_LIST_PORT = 0,
  BAM_NMS_MXN_S16_TO_LIST_OUTPUT_LIST_SIZE_PORT,
  BAM_NMS_MXN_S16_TO_LIST_NUM_OUTPUT_BLOCKS
} eBAM_NMS_MXN_S16_TO_LIST_OUTPUT_PORTS;


#endif /* BAM_NMS_S16_TO_LIST_H_ */

