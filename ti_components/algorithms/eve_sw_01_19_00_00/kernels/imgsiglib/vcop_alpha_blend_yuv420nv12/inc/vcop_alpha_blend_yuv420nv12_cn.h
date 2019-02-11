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
/*     @file : vcop_alpha_blend_yuv420nv12_cn.h                             */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for alpha blending of two YUV 420 NV12 images.          */
/*                                                                          */
/*     vcop_alpha_blend_yuv420nv12_cn                                       */
/*         This is the c-reference for the vcop_alpha_blend_yuv420nv12      */
/*         kernel. This routine accepts two YUV 420 NV12 input images and   */
/*         an 2D array containing alpha values and outputs alpha belended   */
/*         image.                                                           */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_alpha_blend_yuv420nv12_cn                                  */
/*     (                                                                    */
/*         unsigned char *img1,                                             */
/*         unsigned char *img2,                                             */
/*         unsigned char *alphaFrame,                                       */
/*         unsigned char *out,                                              */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short in_img1_stride,                                   */
/*         unsigned short in_img2_stride,                                   */
/*         unsigned short out_stride                                        */
/*     )                                                                    */
/*                                                                          */
/*     img1           : YUV 420 NV12 Image 1                                */
/*     img2           : YUV 420 NV12 Image 2                                */
/*     alphaFrame     : Alpha values for Y pixels, ranges from [0-16]       */
/*     out            : Alpha blended output image (YUV 420 NV12)           */
/*     width          : Width of the input/output images                    */
/*     height         : Height of the input/output images                   */
/*     in_img1_stride : Stride for the input image 1                        */
/*     in_img2_stride : Stride for the input image 2                        */
/*     out_stride    : Stride of the output image                           */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Oct 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_ALPHA_BLEND_YUV420NV12_CN
#define _VCOP_ALPHA_BLEND_YUV420NV12_CN  1


void vcop_alpha_blend_yuv420nv12_cn
(
    unsigned char *img1,
    unsigned char *img2,
    unsigned char *alphaFrame,
    unsigned char *out,
    unsigned short width,
    unsigned short height,
    unsigned short in_img1_stride,
    unsigned short in_img2_stride,
    unsigned short out_stride
);

#endif /* _VCOP_ALPHA_BLEND_YUV420NV12_CN */
