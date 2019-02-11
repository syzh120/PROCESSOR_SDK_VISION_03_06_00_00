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
 ********************************************************************************
 * @file:      bam_image_filter.h
 *
 * @brief:    This file defines functions for integrating filter kernels into BAM
 *
 * @author: Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version: 0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#ifndef BAM_IMAGE_FILTER_H_
#define BAM_IMAGE_FILTER_H_

#define INPUT_TYPE   0   /* 0 - uchar, 1 - char, 2 - ushort, 3 - short */
#define COEF_TYPE    0   /* 0 - uchar, 1 - char, 2 - ushort, 3 - short*/
#define OUTPUT_TYPE  0   /* 0 - char, 1 - short, 2 - word */

#define UCHAR_TYPE  0
#define CHAR_TYPE   1 
#define USHORT_TYPE 2
#define SHORT_TYPE  3
#define INT_TYPE    4

typedef struct _isp_bam_image_filter_args
{
  int input_blk_width;
  int coeff_blk_width;
  int coeff_blk_height;
  int compute_blk_width;
  int compute_blk_height;
  int dnSmple_vert;
  int dnSmple_horz;
  int rnd_shift;
  int input_type;
  int coeff_type;
  int output_type;
  char *filter_coefs;
}BAM_Image_filter_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_filterHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_filterExecFunc;

extern BAM_KernelInfo gBAM_TI_filterKernel;

#define BAM_IMAGE_FILTER_INPUT_PORT  0
#define BAM_IMAGE_FILTER_OUTPUT_PORT 0
#endif

