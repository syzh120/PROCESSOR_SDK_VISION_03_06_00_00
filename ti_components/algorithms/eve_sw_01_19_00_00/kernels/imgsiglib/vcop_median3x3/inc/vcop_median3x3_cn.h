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
/*  @file : vcop_median3x3_cn.h                                             */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for 3x3 median filtering kernel.                               */
/*                                                                          */
/*  vcop_median3x3_char_cn                                                  */
/*     This routine accepts pointers to a input region "in" of type         */
/*     unsigned char, and computes the median over 3x3 pixels of the        */
/*     image.                                                               */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*     While The C code does not have any assumptions on the size of        */
/*     the arrays, the kernel-C code assumes zero padding of last 2 rows    */
/*     and 2 columns of the input image. Intermediate scratch buffers are   */
/*     also used which have sizes of (3 * (width + 2) * height ).           */
/*                                                                          */
/*  USAGE:                                                                  */
/*     void vcop_median3x3_uchar_cn                                         */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *out,                                             */
/*          signed char   *scratch1,                                        */
/*          signed char   *scratch2,                                        */
/*          int           w_input,                                          */
/*          int           w_out,                                            */
/*          int           w_compute,                                        */
/*          int           h_compute                                         */
/*     )                                                                    */
/*                                                                          */
/*     *in        :  Pointer to an input array of uchar.                    */
/*     *out       :  Pointer to output array of uchar.                      */
/*     *scratch1  :  Pointer to intermediate array.                         */
/*     *scratch2  :  Pointer to intermediate array.                         */
/*     w_input    :  Width of the input image in pixels.                    */
/*     w_out      :  Width of the output image in pixels.                   */
/*     w_compute  :  The compute width over which median values are found.  */
/*     h_compute  :  The compute height for median filter.                  */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*  vcop_median3x3_char_cn                                                  */
/*     This routine accepts pointers to a input region "in" of type         */
/*     signed char, and computes the median over 3x3 pixels of the          */
/*     image.                                                               */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*     While The C code does not have any assumptions on the size of        */
/*     the arrays, the kernel-C code assumes zero padding of last 2 rows    */
/*     and 2 columns of the input image. Intermediate scratch buffers are   */
/*     also used which have sizes of (3 * (width + 2) * height ).           */
/*                                                                          */
/*  USAGE:                                                                  */
/*     void vcop_median3x3_char_cn                                          */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *out,                                             */
/*          signed char   *scratch1,                                        */
/*          signed char   *scratch2,                                        */
/*          int           w_input,                                          */
/*          int           w_out,                                            */
/*          int           w_compute,                                        */
/*          int           h_compute                                         */
/*     )                                                                    */
/*                                                                          */
/*     *in        :  Pointer to an input array of char.                     */
/*     *out       :  Pointer to output array of char.                       */
/*     *scratch1  :  Pointer to intermediate array.                         */
/*     *scratch2  :  Pointer to intermediate array.                         */
/*     w_input    :  Width of the input image in pixels.                    */
/*     w_out      :  Width of the output image in pixels.                   */
/*     w_compute  :  The compute width over which median values are found.  */
/*     h_compute  :  The compute height for median filter.                  */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*  @version 0.1 (July 2014) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

void vcop_median3x3_uchar_cn
(
    unsigned char *in, 
    unsigned char *out,
    unsigned char *scratch1,
    unsigned char *scratch2,
    int w_input, 
    int w_out,
    int w_compute,
    int h_compute
);

void vcop_median3x3_char_cn
(
    signed char *in, 
    signed char *out,
    signed char *scratch1,
    signed char *scratch2,
    int w_input, 
    int w_out,
    int w_compute,
    int h_compute
);
