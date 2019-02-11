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
/*     @file : vcop_nonMaxSuppress_mxn_16s_c.h                              */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for non-maximum suppression using mxn window on 16 bit      */
/*     images.                                                              */
/*                                                                          */
/*     vcop_nonMaxSuppress_mxn_16s_cn                                       */
/*         This is the c-reference for the vcop_nonMaxSuppress_mxn_16s      */
/*         kernel. This routine accepts an 16-bit input image and outputs   */
/*         non-maxima suppressed image using a mxn window.                  */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nonMaxSuppress_mxn_16s_cn                                  */
/*     (                                                                    */
/*         unsigned short im [],                                            */
/*         unsigned char  out[],                                            */
/*         int            height,                                           */
/*         int            width,                                            */
/*         int            m,                                                */
/*         int            n,                                                */
/*         short          thresh                                            */
/*     )                                                                    */
/*                                                                          */
/*     im         :  16-bit input image                                     */
/*     out        :  8-bit binary output image                              */
/*     height     :  Height of the input image                              */
/*     width      :  Width of the input image                               */
/*     m          :  Height of the NMS window                               */
/*     n          :  Width of the NMS window                                */
/*     thresh     :  Threshold for pruning peaks                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/*     @version 1.0 (March 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_NONMAXSUPPRESS_MxN_16S_CN
#define _VCOP_NONMAXSUPPRESS_MxN_16S_CN  1

void vcop_nonMaxSuppress_mxn_16s_cn
(
    unsigned short im[],
    unsigned char  out[],
    int            height,
    int            width,
    int            m,
    int            n,
    short          thresh
);


void vcop_nonMaxSuppress_mxn_16sbitPack_cn
(
    short im[],
    unsigned char  out[],
    unsigned short width,
    unsigned short height,
    unsigned short inputStride,
    unsigned short outputSrtide,
    int            windowWidth,
    int            windowHeight,
    short          thresh
);


#endif /* _VCOP_NONMAXSUPPRESS_MxN_16S_CN */
