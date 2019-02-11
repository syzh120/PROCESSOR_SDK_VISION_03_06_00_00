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
/*    @file : vcop_yuv_420nv12_to_422uyvy_kernel.k                          */
/*                                                                          */
/*    @brief : This routine accepts an YUV 420 NV12 images of size width    */
/*             by height and with a stride of in_stride. The kernel         */
/*             performs format conversion and outputs a YUV 422 UYVY image. */
/*             The missing UV samples are filled up by upsampling by 2.     */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_yuv_420nv12_to_422uyvy                                      */
/*    (                                                                     */
/*        __vptr_uint8   in_img_A,                                          */
/*        __vptr_uint8   out_B,                                             */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short in_stride,                                         */
/*        unsigned short out_stride                                         */
/*    )                                                                     */
/*                                                                          */
/*     in_img_A      : YUV 420 NV12 Image                                   */
/*     out_B         : YUV 422 UYVY output image                            */
/*     width         : Width of the input/output images                     */
/*     height        : Height of the input/output images                    */
/*     in_stride     : Stride for the input image                           */
/*     out_stride    : Stride of the output image                           */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    ASSUMPTIONS:                                                          */
/*      The missing UV samples for odd rows in output are same as UV        */
/*      values in the previous even row of output.                          */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      0.140625 cycles/pixel + 56 cycle VCOP overheads                     */
/*                                                                          */
/*    @author  : Anoop K P(a-kp@ti.com)                                     */
/*                                                                          */
/*    @version : 1.0 (Oct 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH        (2 * VCOP_SIMD_WIDTH)

void vcop_yuv_420nv12_to_422uyvy
(
    __vptr_uint8   in_img_A,
    __vptr_uint8   out_B,
    unsigned short width,
    unsigned short height,
    unsigned short in_stride,
    unsigned short out_stride
)
{
    for(int I1 = 0; I1 < height/2; I1++) {
        for(int I2 = 0; I2 < (width + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I2++) {
            __vector Vy1, Vy2, Vuv, Vuv1, Vuv2;
            __agen Addr_in_y, Addr_in_uv, Addr_out;

            Addr_in_y = I1*2*in_stride + I2*VCOP_SIMD_WIDTH;
            Addr_in_uv = I1*in_stride + I2*VCOP_SIMD_WIDTH;
            Addr_out = I1*2*out_stride + I2*VCOP_2SIMD_WIDTH;

            Vy1 =  (in_img_A)[Addr_in_y];
            Vy2 =  (in_img_A + in_stride)[Addr_in_y];
            Vuv =  (in_img_A + height*in_stride)[Addr_in_uv];

            Vuv1 = Vuv;
            Vuv2 = Vuv;

            out_B[Addr_out].interleave() = (Vuv1, Vy1);
            (out_B + out_stride)[Addr_out].interleave() = (Vuv2, Vy2);
        }
    }
}
