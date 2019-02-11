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
/*    @file : vcop_alpha_blend_yuv420nv12_kernel.k                          */
/*                                                                          */
/*    @brief : This routine accepts two YUV 420 NV12 images of size width   */
/*             by height and with a stride of in_stride. An frame of alpha  */
/*             values for each Y pixel is also provided. The kernel outputs */
/*             a YUV 420 NV12 image that is an alpha belended version of    */
/*             the two input images.                                        */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM. In case of don't care it is marked as X.          */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_alpha_blend_yuv420nv12                                      */
/*    (                                                                     */
/*        __vptr_uint8   in_img1_X,                                         */
/*        __vptr_uint8   in_img2_X,                                         */
/*        __vptr_uint8   alphaFrame_X,                                      */
/*        __vptr_uint8   out_X,                                             */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short in_img1_stride,                                    */
/*        unsigned short in_img2_stride,                                    */
/*        unsigned short out_stride                                         */
/*    )                                                                     */
/*                                                                          */
/*    in_img1_X      : YUV 420 NV12 Image 1                                 */
/*    in_img2_X      : YUV 420 NV12 Image 2                                 */
/*    alphaFrame_X   : Alpha values for Y pixels, ranges from [0-16]        */
/*    out_X          : Alpha blended output image (YUV 420 NV12)            */
/*    width          : Width of the input/output images                     */
/*    height         : Height of the input/output images                    */
/*    in_img1_stride : Stride for the input image 1                         */
/*    in_img2_stride : Stride for the input image 2                         */
/*    out_stride     : Stride of the output image                           */
/*                                                                          */
/*    Returns        :  None or void.                                       */
/*                                                                          */
/*    ASSUMPTIONS:                                                          */
/*      Alpha value ranges from 0 to 16.                                    */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      0.375 cycle/pix execution time + 92 cycle VCOP overheads            */
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

void vcop_alpha_blend_yuv420nv12
(
    __vptr_uint8   in_img1_X,
    __vptr_uint8   in_img2_X,
    __vptr_uint8   alphaFrame_X,
    __vptr_uint8   out_X,
    unsigned short width,
    unsigned short height,
    unsigned short in_img1_stride,
    unsigned short in_img2_stride,
    unsigned short out_stride
)
{
    __vector V16;

    /*-----------------------------------------------------------*/
    /* Alpha blending of Y data.                                 */
    /*-----------------------------------------------------------*/

    V16 = 16;

    for(int I1 = 0; I1 < height; I1++) {
        for(int I2 = 0; I2 < (width + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH; I2++) {
            __vector Vy1_e, Vy1_o, Vy2_e, Vy2_o, Vy_e, Vy_o;
            __vector Valpha_e, Valpha_o;
            __vector dy_e, dy_o;
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;

            Addr_in1 = I1*in_img1_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_in2 = I1*in_img2_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_alpha = I1*width + I2*VCOP_2SIMD_WIDTH;
            Addr_out = I1*out_stride + I2*VCOP_2SIMD_WIDTH;

            (Vy1_e, Vy1_o) =  in_img1_X[Addr_in1].deinterleave();
            (Vy2_e, Vy2_o) =  in_img2_X[Addr_in2].deinterleave();
            (Valpha_e, Valpha_o) = alphaFrame_X[Addr_alpha].deinterleave();

            dy_e = Vy1_e - Vy2_e;
            dy_o = Vy1_o - Vy2_o;

            Vy_e = Valpha_e*dy_e;
            Vy_o = Valpha_o*dy_o;

            Vy_e += Vy2_e*V16;
            Vy_o += Vy2_o*V16;

            out_X[Addr_out].interleave() = (Vy_e, Vy_o).truncate(4);
        }
    }

    /*-----------------------------------------------------------*/
    /* Alpha blending of UV data.                                */
    /*-----------------------------------------------------------*/
    for(int I1 = 0; I1 < height/2; I1++) {
        for(int I2 = 0; I2 < (width + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH; I2++) {
            __vector Vuv1_e, Vuv1_o, Vuv2_e, Vuv2_o, Vuv_e, Vuv_o;
            __vector Valpha_e, Valpha_o;
            __vector dy_e, dy_o;
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;

            Addr_in1 = I1*in_img1_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_in2 = I1*in_img2_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_alpha = I1*2*width + I2*VCOP_2SIMD_WIDTH;
            Addr_out = I1*out_stride + I2*VCOP_2SIMD_WIDTH;

            (Vuv1_e, Vuv1_o) =  (in_img1_X + height*in_img1_stride)[Addr_in1].deinterleave();
            (Vuv2_e, Vuv2_o) =  (in_img2_X + height*in_img2_stride)[Addr_in2].deinterleave();
            (Valpha_e, Valpha_o) = alphaFrame_X[Addr_alpha].deinterleave();

            dy_e = Vuv1_e - Vuv2_e;
            dy_o = Vuv1_o - Vuv2_o;

            Vuv_e = Valpha_e*dy_e;
            Vuv_o = Valpha_o*dy_o;

            Vuv_e += Vuv2_e*V16;
            Vuv_o += Vuv2_o*V16;

            (out_X + height*out_stride)[Addr_out].interleave() = (Vuv_e, Vuv_o).truncate(4);
        }
    }
}
