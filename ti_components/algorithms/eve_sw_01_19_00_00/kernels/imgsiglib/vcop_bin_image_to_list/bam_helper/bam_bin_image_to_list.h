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
 *  @file       bam_bin_image_to_list.h
 *
 *  @brief      This header defines interfaces for integrating binary image to
 *              (X, Y) co-ordinate list creation into BAM.
 */

#ifndef BAM_BIN_IMAGE_TO_LIST_H_
#define BAM_BIN_IMAGE_TO_LIST_H_

#include "bam_kernel_interface.h"
/**
  Maximum number of pixels in a block. Output requires 4 bytes per pix. Reserving 32 bytes
  for VCOP malloc header and 32 byte for buffer alignment.
*/
#define BIN_IMAGE_TO_LIST_MAX_PIXELS                 (4080U)

#define BIN_IMAGE_TO_LIST_MAX_BLK_WIDTH               (1920U)

typedef struct bam_bin_image_to_list_ctrlArgs
{
    uint16_t frameStartX;
    uint16_t frameStartY;
    uint16_t blkWidth;
    uint16_t blkHeight;
    uint16_t blkStride;
    uint8_t  outputQformat;
    uint8_t  xyOrder;/* Refer BAM_BIN_IMAGE_TO_LIST_XY_ORDER for valid values of it */
} BAM_Bin_image_to_list_ctrlArgs;

typedef struct bam_bin_image_to_list_args
{
    uint16_t frameStartX;
    uint16_t frameStartY;
    uint16_t blkWidth;
    uint16_t blkHeight;
    uint16_t blkStride;
    uint8_t  outputQformat;
    uint8_t  xyOrder;/* Refer BAM_BIN_IMAGE_TO_LIST_XY_ORDER for valid values of it */
} BAM_Bin_image_to_list_Args;

typedef enum
{
  BAM_BIN_IMAGE_TO_LIST_XY,
  BAM_BIN_IMAGE_TO_LIST_YX
} BAM_BIN_IMAGE_TO_LIST_XY_ORDER;


extern BAM_KernelHelperFuncDef gBAM_TI_binImageToListHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_binImageToListExecFunc;

extern BAM_KernelInfo gBAM_TI_binImageToListKernel;

#define BAM_BIN_IMAGE_TO_LIST_INPUT_PORT_IMG       (0)

#define BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_XY       (0)
#define BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_SIZE     (1U)

#define BAM_BIN_IMAGE_TO_LIST_TEMP_PARAM           (0)
#define BAM_BIN_IMAGE_TO_LIST_TEMP_PORT_STARTXY    (1U)
#define BAM_BIN_IMAGE_TO_LIST_TEMP_XSEQ            (2U)

#endif /* BAM_BIN_IMAGE_TO_LIST_H_ */

