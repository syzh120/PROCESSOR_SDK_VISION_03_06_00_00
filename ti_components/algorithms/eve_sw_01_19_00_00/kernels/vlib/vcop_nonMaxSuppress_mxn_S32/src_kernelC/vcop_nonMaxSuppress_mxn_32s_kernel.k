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
/* NAME:                                                                    */
/*     vcop_nonMaxSuppress_mxn_32s_kernel                                   */
/*                                                                          */
/*                                                                          */
/* USAGE:                                                                   */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nonMaxSuppress_mxn_32s                                     */
/*     (                                                                    */
/*         __vptr_uint32 im_A,                                              */
/*         __vptr_uint8  out_B,                                             */
/*         __vptr_uint32 scratch_B,                                         */
/*         __vptr_uint32 scratch_C,                                         */
/*         int           height,                                            */
/*         int           width,                                             */
/*         int           m,                                                 */
/*         int           n,                                                 */
/*         int           thresh                                             */
/*     )                                                                    */
/*                                                                          */
/*     im_A       :  32-bit input image. This buffer should contain         */
/*                   height*width words.                                    */
/*     out_B      :  8-bit binary output image. The buffer width should be  */
/*                   equal to 'width' bytes and height should be atleast    */
/*                   2*ceil((height-m+1)/2). Valid output will be present   */
/*                   at the first (height-m+1) rows and first (width-n+1)   */
/*                   columns.                                               */
/*     scratch_B  :  Scratch buffer 1. User need to allocate at least       */
/*                   4*(height-m+1)*width + 64 bytes for scratch_B.         */
/*     scratch_C  :  Scratch buffer 2. User need to allocate at least       */
/*                   8*ceil((height-m+1)/2)*width bytes for scratch_C.      */
/*     height     :  Height of the input image.                             */
/*     width      :  Width of the input image. This should be a multiple    */
/*                   of 8.                                                  */
/*     m          :  Height of the NMS window.                              */
/*     n          :  Width of the NMS window.                               */
/*     thresh     :  Threshold for pruning peaks.                           */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*             This routine accepts an 32-bit input image and outputs non-  */
/*     maxima suppressed image using an mxn window. The recomended memory   */
/*     bank for each of the buffers is captured as A/B/C as part of the     */
/*     buffer pointer. A/B/C can either be IMBUF High, IMBUF low or WMEM.   */
/*     Further out_B and scratch_B can safely overlap without causing data  */
/*     corruption.                                                          */
/*             The kernel assumes that the NMS window is centered at        */
/*     [floor((m-1)/2), floor((n-1)/2)]. The NMS output starts at the       */
/*     top-left pixel in the output buffer. User is expected to take care   */
/*     of the resulting pixel shift in the output.                          */
/*                                                                          */
/* PERFORMANCE MEASUREMENT:                                                 */
/*             For an input block of width = 32, height = 32 and an NMS     */
/*     window of width = 3 and height = 7, the kernel took 1318 VCOP cycles */
/*     on CentEVE platform.                                                 */
/*                                                                          */
/* AUTHOR:                                                                  */
/*             Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/* VERSION:                                                                 */
/*            1.0 (March 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*im_A)
#define ELEMSZ1         sizeof(*out_B)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define VECTORSZ1       (VCOP_SIMD_WIDTH*ELEMSZ1)

void vcop_nonMaxSuppress_mxn_32s
(
    __vptr_int32 im_A,
    __vptr_uint8  out_B,
    __vptr_int32 scratch_B,
    __vptr_int32 scratch_C,
    int           width,
    int           height,
    int           input_stride,
    int           output_stride, /* must be multiple of 8 */
    int           m,
    int           n,
    int           thresh
)
{
  __vector K0   ;
  __vector K0p  ;
  __vector maxs ;
  __vector maxsp;
  __vector R0   ;
  __vector R1   ;
  __vector I0  ;
  __vector I1  ;
  __vector max0;
  __vector max1;
  __vector Rthr   ;
  __vector K255   ;
  __vector Ieqmax0;
  __vector Ieqmax1;
  __vector Igtthr0;
  __vector Igtthr1;
  __vector C0     ;
  __vector C1     ;

    K0 = 0;
    K0p = 0;
    for (int i = 0; i < height-m+1; i++)
    {
        for (int j = 0; j < (width + VCOP_SIMD_WIDTH*2 - 1)/(VCOP_SIMD_WIDTH*2); j++)
        {
            __agen Addr1, Addr2, Addr3;
            Addr1 = i*width*ELEMSZ + j*VECTORSZ*2;
            Addr2 = i*output_stride*ELEMSZ1 + j*VECTORSZ1*2;
            Addr3 = i*input_stride*ELEMSZ + j*VECTORSZ*2;

            maxs  = (im_A)[Addr3];
            maxsp = (im_A + VECTORSZ)[Addr3];

            for (int k = 0; k < (m-1); k++)
            {
                __agen Addr0;
                Addr0 = i*input_stride*ELEMSZ + j*VECTORSZ*2 + k*input_stride*ELEMSZ;

                R0 = (im_A + input_stride*ELEMSZ)[Addr0];
                R1 = (im_A + input_stride*ELEMSZ + VECTORSZ)[Addr0];

                maxs = max(R0, maxs);
                maxsp = max(R1, maxsp);
            }

            scratch_B[Addr1] = maxs;
            (scratch_B + VECTORSZ)[Addr1] = maxsp;
            out_B[Addr2].interleave() = (K0, K0p);
        }
    }

#define SCRATCH_C_STRIDE (((width-n+VCOP_SIMD_WIDTH)/VCOP_SIMD_WIDTH)*VCOP_SIMD_WIDTH)

    for (int i = 0; i < (height-m+2)/2; i++)
    {
        for (int j = 0; j < (width-n+VCOP_SIMD_WIDTH)/VCOP_SIMD_WIDTH; j++)
        {
            __agen Addr1, Addr2;
            Addr1 = i*2*width*ELEMSZ + j*VECTORSZ;
            Addr2 = i*2*SCRATCH_C_STRIDE*ELEMSZ + j*VECTORSZ;

            max0 = (scratch_B)[Addr1];
            max1 = (scratch_B+width*ELEMSZ)[Addr1];

            for (int k = 0; k < (n-1); k++)
            {
                __agen Addr0;
                Addr0 = i*2*width*ELEMSZ + j*VECTORSZ + k*ELEMSZ;

                I0 = (scratch_B + ELEMSZ)[Addr0];
                I1 = (scratch_B + width*ELEMSZ + ELEMSZ)[Addr0];

                max0 = max(I0, max0);
                max1 = max(I1, max1);
            }

            scratch_C[Addr2] = max0;
            (scratch_C+SCRATCH_C_STRIDE*ELEMSZ)[Addr2] = max1;
         }
    }

    Rthr = thresh;
    K255 = 255;

    for (int i = 0; i < (height-m+2)/2; i++)
    {
        for (int j = 0; j < (width-n+VCOP_SIMD_WIDTH)/VCOP_SIMD_WIDTH; j++)
        {
            __agen Addr1, Addr2, Addr3;

            Addr1 = i*2*SCRATCH_C_STRIDE*ELEMSZ  + j*VECTORSZ;
            Addr2 = i*2*output_stride*ELEMSZ1 + j*VECTORSZ1;
            Addr3 = i*2*input_stride*ELEMSZ  + j*VECTORSZ;

            I0 = (im_A+((m-1)/2)*input_stride*ELEMSZ+((n-1)/2)*ELEMSZ)[Addr3];
            I1 = (im_A+((m-1)/2)*input_stride*ELEMSZ+((n-1)/2)*ELEMSZ + input_stride*ELEMSZ)[Addr3];

            max0 = scratch_C[Addr1];
            max1 = (scratch_C + SCRATCH_C_STRIDE*ELEMSZ)[Addr1];

            Ieqmax0 = (I0 == max0);
            Ieqmax1 = (I1 == max1);

            Igtthr0 = (I0 > Rthr);
            Igtthr1 = (I1 > Rthr);

            C0 = Ieqmax0 & Igtthr0;
            C1 = Ieqmax1 & Igtthr1;

            out_B[Addr2] = K255.predicate(C0);
            (out_B + output_stride*ELEMSZ1)[Addr2] = K255.predicate(C1);
        }
    }
}


#define INPUT_ELEMSZ    sizeof(*im_A)
#define INPUT_VECTORSZ  ( INPUT_ELEMSZ * VCOP_SIMD_WIDTH )

#define OUTPUT_ELEMSZ       (sizeof(*out_B))
#define OUTPUT_VECTORSZ       (OUTPUT_ELEMSZ)

#define VCOP_2SIMD_WIDTH  (2 * VCOP_SIMD_WIDTH)
#define ALIGN_2SIMD(a)    ((a + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))

/* ==================================================
 *  @kernel     vcop_nonMaxSuppress_mxn_32s_bitPack
 *
 *  @desc     This kernel nms of the given input data and outputs the data in packed format
 *
 *  @inputs   This kernel takes following Inputs
 *                  im_A :
 *                          Pointer to the input image buffer
 *                  width :
 *                          Width of the input block
 *                  height :
 *                          Height of the input block
 *                  input_stride :
 *                          Stride of the input block
 *                  output_stride :
 *                          Stride of the output block
 *                  windowWidth :
 *                          Window width for NMS
 *                  windowHeight :
 *                          Window Height for NMS
 *                  thresh :
 *                          Threshold to be used with NMS
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  scratch_B :
 *                          This is pointer  to an intermediate scratch buffer which contains maximum values
 *                           calculated in vertical direction. Size of this buffer should be (ALIGN_2SIMD(width) * height * sizeof(uint32_t))
 *                  scratch_C :
 *                          This is pointer  to an intermediate scratch buffer which contains maximum values
 *                          calculated in horizontal direction. Size of this buffer should be (ALIGN_SIMD(width - windowWidth + 1) *
 *                           height * sizeof(uint32_t))
 *
 *  @outputs   This kernel produce following outputs
 *                  out_B :
 *                          Pointer to the buffer which will store the binpacked output after NMS and thresholding
 *                          should be ALIGN_SIMD(width  - windowWidth + 1) * height * sizeof(uint32_t))
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          im_A -> VCOP_IBUFLA
 *                          scratch_B -> VCOP_WMEM
 *                          scratch_C -> VCOP_IBUFHA
 *                          out_B -> VCOP_IBUFHA
 *
 *  @constraints Following constraints
 *                          width should be multiple of 8
 *                           height should be multiple of 2
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_nonMaxSuppress_mxn_32s_bitPack
(
    __vptr_int32 im_A,
    __vptr_uint8  out_B,
    __vptr_int32 scratch_B,
    __vptr_int32 scratch_C,
    int           width,
    int           height,
    int           input_stride,
    int           output_stride, /* must be multiple of 8 */
    int           windowWidth,
    int           windowHeight,
    int           thresh
)
{
  __vector maxs ;
  __vector maxsp;
  __vector R0   ;
  __vector R1   ;
  __vector I0  ;
  __vector I1  ;
  __vector max0;
  __vector max1;
  __vector Rthr   ;
  __vector Ieqmax0;
  __vector Ieqmax1;
  __vector Igtthr0;
  __vector Igtthr1;
  __vector C0     ;
  __vector C1     ;
  __vector K1     ;

#if 0
    K0 = 0;
    K0p = 0;
#endif
    for (int i = 0; i < height - windowHeight + 1; i++)
    {
        for (int j = 0; j < ALIGN_2SIMD(width)/ VCOP_2SIMD_WIDTH; j++)
        {
            __agen addrIn, addrOut;

            addrIn  = i * input_stride * INPUT_ELEMSZ + j * INPUT_VECTORSZ * 2;
            addrOut = i * width * INPUT_ELEMSZ + j *  INPUT_VECTORSZ * 2;

            maxs  = (im_A)[addrIn];
            maxsp = (im_A + INPUT_VECTORSZ)[addrIn];

            /* Now find the maximum of all the elements in vertical direction for window Height*/
            for (int k = 0; k < (windowHeight - 1); k++)
            {
                __agen Addr0;
                Addr0 = i * input_stride * INPUT_ELEMSZ + j * INPUT_VECTORSZ * 2 + k * input_stride * INPUT_ELEMSZ;

                R0 = (im_A + input_stride * INPUT_ELEMSZ)[Addr0];
                R1 = (im_A + input_stride * INPUT_ELEMSZ + INPUT_VECTORSZ)[Addr0];

                maxs  = max(R0, maxs);
                maxsp = max(R1, maxsp);
            }

            scratch_B[addrOut] = maxs;
            (scratch_B + INPUT_VECTORSZ)[addrOut] = maxsp;
#if 0
            out_B[Addr2].interleave() = (K0, K0p);
#endif
        }
    }


    for (int i = 0; i < (height - windowHeight + 2)/2; i++)
    {
        for (int j = 0; j < ALIGN_SIMD(width - windowWidth + 1)/VCOP_SIMD_WIDTH; j++)
        {
             __agen addrInOut;
            /* Multiplication by 2 in i direction because we are working with two rows at a time */
            addrInOut = i * INPUT_ELEMSZ * width * 2 + j * INPUT_VECTORSZ;
#if 0
            __agen Addr1, Addr2;
            Addr1 = i*2*width*ELEMSZ + j*VECTORSZ;
            Addr2 = i*2*SCRATCH_C_STRIDE*ELEMSZ + j*VECTORSZ;
#endif

            max0 = (scratch_B)[addrInOut];
            max1 = (scratch_B + INPUT_ELEMSZ * width)[addrInOut];

            for (int k = 0; k < (windowWidth - 1); k++)
            {
                __agen Addr0;
                Addr0 = i * 2 * width * INPUT_ELEMSZ + j * INPUT_VECTORSZ + k * INPUT_ELEMSZ;

                I0 = (scratch_B + INPUT_ELEMSZ)[Addr0];
                I1 = (scratch_B + width * INPUT_ELEMSZ + INPUT_ELEMSZ)[Addr0];

                max0 = max(I0, max0);
                max1 = max(I1, max1);
            }

            scratch_C[addrInOut] = max0;
            (scratch_C + INPUT_ELEMSZ * width)[addrInOut] = max1;
         }
    }

    Rthr = thresh;
    K1 = 1;

    for (int i = 0; i < (height-windowHeight+2)/2; i++)
    {
        for (int j = 0; j < (width-windowWidth+VCOP_SIMD_WIDTH)/VCOP_SIMD_WIDTH; j++)
        {
          __agen addrInData, addrMaxVal, addrBinPack;
          __vector binaryMask1;
          __vector binaryMask2;


          addrInData = i * 2 * input_stride * INPUT_ELEMSZ  + j * INPUT_VECTORSZ;

          addrMaxVal = i * 2 * width * INPUT_ELEMSZ + j * INPUT_VECTORSZ;
          addrBinPack = i * 2 * output_stride * OUTPUT_ELEMSZ + j * OUTPUT_VECTORSZ;

          I0 = (im_A+((windowHeight-1)/2)*input_stride*INPUT_ELEMSZ+((windowWidth-1)/2)*ELEMSZ)[addrInData];
          I1 = (im_A+((windowHeight-1)/2)*input_stride*INPUT_ELEMSZ+((windowWidth-1)/2)*ELEMSZ + input_stride*ELEMSZ)[addrInData];

          max0 = scratch_C[addrMaxVal];
          max1 = (scratch_C + width * INPUT_ELEMSZ)[addrMaxVal];

          Ieqmax0 = (I0 == max0);
          Ieqmax1 = (I1 == max1);

          Igtthr0 = (I0 > Rthr);
          Igtthr1 = (I1 > Rthr);

          C0 = Ieqmax0 & Igtthr0;
          C1 = Ieqmax1 & Igtthr1;

          binaryMask1 = pack(C0 >= K1);
          binaryMask2 = pack(C1 >= K1);
          out_B[addrBinPack].onept() = binaryMask1;
          (out_B + output_stride * OUTPUT_ELEMSZ)[addrBinPack].onept() = binaryMask2;
        }
    }
}

