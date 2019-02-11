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

/*--------------------------------------------------------------------------*/
/* NAME: vcop_grayscale_morphology_kernel.k                                 */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernels for performing grayscale dilation and erosion  */
/* using flat structing elements (SE). Images are assumed to be 8-bit       */
/* grayscale. All other grayscale morphological operations can be relaized  */
/* as a combination of the vcop_grayscale_dilate, vcop_grayscale_erode and  */
/* vcop_grayscale_morp_diff kernels.                                        */
/*                                                                          */
/* Based on the shape of SE used, three variants of the dilation and        */
/* erosion kernels are provided.                                            */
/* 1. Generic structuring element                                           */
/*    vcop_grayscale_dilate_mask and vcop_grayscale_erode_mask allows user  */
/*    to provide a SE of any shape. The shape of the SE can be specified    */
/*    as a mask of 1's and 0's in "se_ptr" of width "se_w" and height       */
/*    "se_h".                                                               */
/* 2. Rectangular structuring element                                       */
/*    vcop_grayscale_dilate_rect and vcop_grayscale_erode_rect are          */
/*    optimized for the special case of a rectangular SE. User can specify  */
/*    the height and width of the rectangular SE using "se_w" and "se_h"    */
/* 3. Cross structuring element                                             */
/*    vcop_grayscale_dilate_cross and vcop_grayscale_erode_cross are        */
/*    optimized for the special case of a cross shared SE. The non-zero row */
/*    and column of the cross SE can be specified using "cross_se_row" and  */
/*    "cross_se_col".                                                       */
/*                                                                          */
/* All dilation and erosion kernels accepts input data in an array of       */
/* unsigned char in "data_ptr", of width "blk_w" and  height "blk_h" with   */
/* each line having a line pitch of "line_ofst" elements, the SE size -     */
/* width "se_w" and height of "se_h", filtering the input with  the SE      */
/* according to the variant and writing the result in an output array       */
/* output_ptr of width "blk_w" elements per line, where each line           */
/* has a line pitch of "line_ofst" and "blk_h" such lines.                  */
/*                                                                          */
/* The vcop_grayscale_morp_diff kernel performs image difference operation  */
/* between two 8-bit grayscale images at data_ptr and data2_ptr, both of    */
/* size blk_w by blk_h, and writes the output into output_ptr.              */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Grayscale images are of 8-bit                                       */
/*   2. "blk_w" should a multiple of 16                                     */
/*   3. vcop_grayscale_morp_diff assumes that the image pixel values in     */
/*      data_ptr is always greater than the corresponding pixel values at   */
/*      data2_ptr. This is always true for all grayscale morphology         */
/*      operations with flat SE.                                            */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_grayscale_dilate_mask     ~ blk_w*(blk_h-se_h+1)*se_w*se_h/8      */
/*   vcop_grayscale_erode_mask      ~ blk_w*(blk_h-se_h+1)*se_w*se_h/8      */
/*   vcop_grayscale_dilate_rect     ~ blk_w*(blk_h-se_h+1)*(se_w+se_h)/16   */
/*   vcop_grayscale_erode_rect      ~ blk_w*(blk_h-se_h+1)*(se_w+se_h)/16   */
/*   vcop_grayscale_dilate_cross    ~ blk_w*(blk_h-se_h+1)*(se_w+se_h)/16   */
/*   vcop_grayscale_erode_cross     ~ blk_w*(blk_h-se_h+1)*(se_w+se_h)/16   */
/*   vcop_grayscale_morp_diff       ~ blk_w*blk_h/16 cycles                 */
/*                                                                          */
/* AUTHOR:   Anoop K P(a-kp@ti.com)                                         */
/*                                                                          */
/* VERSION:  1.0 (February 2013) : Base version.                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if VCOP_HOST_EMULATION

#include <vcop.h>
#endif

#define ELEMSZ            sizeof(*data_ptr)
#define VCOP_2SIMD_WIDTH  (2 * VCOP_SIMD_WIDTH)
#define LINESZ            (line_ofst * ELEMSZ)
#define VECTORSZ          (VCOP_2SIMD_WIDTH * ELEMSZ)
#define SE_ELEMSZ         sizeof(*se_ptr)
#define SE_LINESZ         (se_w * SE_ELEMSZ)
#define OUTPUT_ELEMSZ     sizeof(*output_ptr)
#define OUTPUT_LINESZ     (line_ofst * OUTPUT_ELEMSZ)
#define OUTPUT_VECTORSZ   (VCOP_2SIMD_WIDTH * OUTPUT_ELEMSZ)


// Grayscale Dilation with a generic mask structuring element
void vcop_grayscale_dilate_mask
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    __vptr_uint8           se_ptr,       // structuring element data pointer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1, Vin2;                 // input data
    __vector   Vse;                        // structuring element
    __vector   Vmax1, Vmax2;
    __vector   Vsmall1, Vsmall2;

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A2;

            Vmax1 =  0;
            Vmax2 =  0;

            for (int I3 = 0; I3 < se_h; I3++)
            {
                for (int I4 = 0; I4 < se_w; I4++)
                {
                    __agen A0, A1;

                    Vsmall1 = 0;
                    Vsmall2 = 0;

                    A0  = I1*LINESZ + I2*VECTORSZ +
                          I3*LINESZ + I4*ELEMSZ;
                    A1  = I3*SE_LINESZ + I4*SE_ELEMSZ;

                    (Vin1, Vin2) = data_ptr[A0].deinterleave();
                    Vse = se_ptr[A1].onept();

                    Vsmall1 = select(Vse, Vin1, Vsmall1);
                    Vsmall2 = select(Vse, Vin2, Vsmall2);

                    Vmax1 = max(Vsmall1, Vmax1);
                    Vmax2 = max(Vsmall2, Vmax2);
                }
            }

            A2 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            output_ptr[A2].interleave() = (Vmax1, Vmax2);
        }
    }
}

// Grayscale Erosion with a generic mask structuring element
void vcop_grayscale_erode_mask
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    __vptr_uint8           se_ptr,       // structuring element data pointer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1,  Vin2;                // input data
    __vector   Vse;                        // structuring element
    __vector   Vmin1, Vmin2;
    __vector   Vlarge1, Vlarge2;

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A2;

            Vmin1 =  255;
            Vmin2 =  255;

            for (int I3 = 0; I3 < se_h; I3++)
            {
                for (int I4 = 0; I4 < se_w; I4++)
                {
                    __agen A0, A1;

                    Vlarge1 = 255;
                    Vlarge2 = 255;

                    A0  = I1*LINESZ + I2*VECTORSZ +
                          I3*LINESZ + I4*ELEMSZ;
                    A1  = I3*SE_LINESZ + I4*SE_ELEMSZ;

                    (Vin1, Vin2) = data_ptr[A0].deinterleave();
                    Vse = se_ptr[A1].onept();

                    Vlarge1 = select(Vse, Vin1, Vlarge1);
                    Vlarge2 = select(Vse, Vin2, Vlarge2);

                    Vmin1 = min(Vlarge1, Vmin1);
                    Vmin2 = min(Vlarge2, Vmin2);
                }
            }

            A2 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            output_ptr[A2].interleave() = (Vmin1, Vmin2);
        }
    }
}

// Grayscale Dilation with Rectangular Structuring Elements
void vcop_grayscale_dilate_rect
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input data pointer
    unsigned short         se_w,         // width of the rectangular structuring element block, in elements
    unsigned short         se_h,         // height of the rectangular structuring element block
    __vptr_uint8           scratch_ptr,  // pointer to scratch buffer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1, Vin2;                 // input data
    __vector   Vmax1, Vmax2;

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1, A2;

            A2 = I1*LINESZ + I2*VECTORSZ;

            (Vmax1, Vmax2) = data_ptr[A2].deinterleave();

            for (int I3 = 0; I3 < (se_h-1); I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*LINESZ;

                (Vin1, Vin2) = (data_ptr + LINESZ)[A0].deinterleave();

                Vmax1 = max(Vin1, Vmax1);
                Vmax2 = max(Vin2, Vmax2);
            }

            A1 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            scratch_ptr[A1].interleave() = (Vmax1, Vmax2);
        }
    }

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1, A2;

            A2 = I1*LINESZ + I2*VECTORSZ;

            (Vmax1, Vmax2) = scratch_ptr[A2].deinterleave();

            for (int I3 = 0; I3 < (se_w-1); I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*ELEMSZ;

                (Vin1, Vin2) = (scratch_ptr + ELEMSZ)[A0].deinterleave();

                Vmax1 = max(Vin1, Vmax1);
                Vmax2 = max(Vin2, Vmax2);
            }

            A1 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            output_ptr[A1].interleave() = (Vmax1, Vmax2);
        }
    }
}

// Grayscale Erosion with Rectangular Structuring Elements
void vcop_grayscale_erode_rect
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input data pointer
    unsigned short         se_w,         // width of the rectangular structuring element block, in elements
    unsigned short         se_h,         // height of the rectangular structuring element block
    __vptr_uint8           scratch_ptr,  // pointer to scratch buffer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1,  Vin2;                // input data
    __vector   Vmin1, Vmin2;

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w+VCOP_2SIMD_WIDTH-1)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1, A2;

            A2 = I1*LINESZ + I2*VECTORSZ;
            (Vmin1, Vmin2) = data_ptr[A2].deinterleave();

            for (int I3 = 0; I3 < (se_h-1); I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*LINESZ;

                (Vin1, Vin2) = (data_ptr + LINESZ)[A0].deinterleave();

                Vmin1 = min(Vin1, Vmin1);
                Vmin2 = min(Vin2, Vmin2);
            }

            A1 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            scratch_ptr[A1].interleave() = (Vmin1, Vmin2);
        }
    }

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1, A2;

            A2 = I1*LINESZ + I2*VECTORSZ;
            (Vmin1, Vmin2) = scratch_ptr[A2].deinterleave();

            for (int I3 = 0; I3 < (se_w-1); I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*ELEMSZ;

                (Vin1, Vin2) = (scratch_ptr + ELEMSZ)[A0].deinterleave();

                Vmin1 = min(Vin1, Vmin1);
                Vmin2 = min(Vin2, Vmin2);
            }

            A1 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            output_ptr[A1].interleave() = (Vmin1, Vmin2);
        }
    }
}

// Grayscale Dilation for Cross Structuring Elements
void vcop_grayscale_dilate_cross
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    unsigned short         cross_se_row, // row number of the cross structuring element
    unsigned short         cross_se_col, // column number of the cross structuring element
    __vptr_uint8           scratch_ptr,  // pointer to scratch buffer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1, Vin2;                 // input data
    __vector   Vmax1, Vmax2;

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1, A2;

            A1 = I1*LINESZ + I2*VECTORSZ;

            (Vmax1, Vmax2) =  (data_ptr  + cross_se_row*LINESZ)[A1].deinterleave();

            for (int I3 = 0; I3 < (se_w-1); I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*ELEMSZ;

                (Vin1, Vin2) = (data_ptr  + cross_se_row*LINESZ + ELEMSZ)[A0].deinterleave();

                Vmax1 = max(Vin1, Vmax1);
                Vmax2 = max(Vin2, Vmax2);
            }

            A2 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            scratch_ptr[A2].interleave() = (Vmax1, Vmax2);
        }
    }

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1;

            A1 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);

            (Vmax1, Vmax2) =  scratch_ptr[A1].deinterleave();

            for (int I3 = 0; I3 < se_h; I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*LINESZ;

                (Vin1, Vin2) = (data_ptr + cross_se_col*ELEMSZ)[A0].deinterleave();

                Vmax1 = max(Vin1, Vmax1);
                Vmax2 = max(Vin2, Vmax2);
            }

            output_ptr[A1].interleave() = (Vmax1, Vmax2);
        }
    }
}

// Grayscale Erosion for Cross Structuring Elements
void vcop_grayscale_erode_cross
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    unsigned short         cross_se_row, // row number of the cross structuring element
    unsigned short         cross_se_col, // column number of the cross structuring element
    __vptr_uint8           scratch_ptr,  // pointer to scratch buffer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1, Vin2;                // input data
    __vector   Vmin1, Vmin2;

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1, A2;

            A1 = I1*LINESZ + I2*VECTORSZ;

            (Vmin1, Vmin2) =  (data_ptr + cross_se_row*LINESZ)[A1].deinterleave();

            for (int I3 = 0; I3 < (se_w-1); I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*ELEMSZ;

                (Vin1, Vin2) = (data_ptr + cross_se_row*LINESZ + ELEMSZ)[A0].deinterleave();

                Vmin1 = min(Vin1, Vmin1);
                Vmin2 = min(Vin2, Vmin2);
            }

            A2 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);
            scratch_ptr[A2].interleave() = (Vmin1, Vmin2);
        }
    }

    for (int I1 = 0; I1 < blk_h-se_h+1; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w-se_w+VCOP_2SIMD_WIDTH)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A1;
            A1 = I1*(OUTPUT_LINESZ) + I2*(OUTPUT_VECTORSZ);

            (Vmin1, Vmin2) =  scratch_ptr[A1].deinterleave();

            for (int I3 = 0; I3 < se_h; I3++)
            {
                __agen A0;

                A0  = I1*LINESZ + I2*VECTORSZ +
                      I3*LINESZ;

                (Vin1, Vin2) = (data_ptr + cross_se_col*ELEMSZ)[A0].deinterleave();

                Vmin1 = min(Vin1, Vmin1);
                Vmin2 = min(Vin2, Vmin2);
            }

            output_ptr[A1].interleave() = (Vmin1, Vmin2);
        }
    }
}

// Image difference operation
void vcop_grayscale_morp_diff
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    __vptr_uint8           data_ptr,     // input 1 data pointer (data >= data2)
    __vptr_uint8           data2_ptr,    // input 2 data pointer
    __vptr_uint8           output_ptr    // output data pointer
)
{
    __vector   Vin1,  Vin2;                // input 1 data
    __vector   Vin3,  Vin4;                // input 2 data
    __vector   Vdiff1,  Vdiff2;            // output data

    for (int I1 = 0; I1 < blk_h; I1++)
    {
        for (int I2 = 0; I2 < ((blk_w+VCOP_2SIMD_WIDTH-1)/VCOP_2SIMD_WIDTH); I2++)
        {
            __agen A0, A1;

            A0  = I1*LINESZ + I2*VECTORSZ;
            A1  = I1*OUTPUT_LINESZ + I2*OUTPUT_VECTORSZ;

            (Vin1, Vin2) = data_ptr[A0].deinterleave();
            (Vin3, Vin4) = data2_ptr[A0].deinterleave();

            Vdiff1 = Vin1 - Vin3;
            Vdiff2 = Vin2 - Vin4;

            output_ptr[A1].interleave() = (Vdiff1, Vdiff2);
        }
    }
}

