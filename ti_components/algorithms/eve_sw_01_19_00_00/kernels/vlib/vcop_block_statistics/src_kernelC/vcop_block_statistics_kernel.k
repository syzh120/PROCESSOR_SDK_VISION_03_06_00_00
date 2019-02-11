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
/*    vcop_block_statistics                                                 */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*             This routine accepts an 8-bit grayscale input image of size  */
/*     blockWidth by blockHeight with a stride of blockStride. The image is */
/*     divided into non-overlapping blocks of statBlockWidth by             */
/*     statBlockHeight. The kernel computes block statistics over these     */
/*     non-overlapping blocks. The following statistics are computed :      */
/*     Minima(min_B), Maxima(max_B), Mean(mean_B) and Variance(variance_A). */
/*     The kernel doesn't perform averaging during mean and variance        */
/*     computations. Hence mean output reported is actually N*mean and      */
/*     variance is N^2*variance where N is the number of samples within a   */
/*     block (N = statBlockWidth*statBlockHeight). User has to divide the   */
/*     outputs by N and N^2 respectively to arrive at mean and variance.    */
/*                                                                          */
/*     For storing intermediate results the kernel requires 4 scratch       */
/*     buffers - scratch_C, scratchSum_A, scratchSumSq_B, scratchSumSq_C.   */
/*     The buffers scratch_C and scratchSum_A require a stride of 36 bytes  */
/*     due to usage of transpose store but the active area in both buffers  */
/*     is only 16 bytes. Similarly the output buffers min_B, max_B and      */
/*     mean_B also require 36 bytes of stride for thier respective buffers  */
/*     whereas the active width is only 8 byte for min, 8 byte for max and  */
/*     16 byte for mean. Hence one can effectively place the three of them  */
/*     in a single buffer of 36 byte width to save intenal memory.          */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High, IMBUF */
/*     low or WMEM.                                                         */
/*                                                                          */
/* USAGE:                                                                   */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_block_statistics                                            */
/*    (                                                                     */
/*        __vptr_uint8       im_A,                                          */
/*        unsigned short     blockStride,                                   */
/*        unsigned short     blockWidth,                                    */
/*        unsigned short     blockHeight,                                   */
/*        unsigned short     statBlockWidth,                                */
/*        unsigned short     statBlockHeight,                               */
/*        __vptr_uint8       scratch_C,                                     */
/*        __vptr_uint16      scratchSum_A,                                  */
/*        __vptr_uint32      scratchSumSq_B,                                */
/*        __vptr_uint32      scratchSumSq_C,                                */
/*        __vptr_uint16      scratchSumSq_C_lo,                             */
/*        __vptr_uint16      scratchSumSq_C_hi,                             */
/*        __vptr_uint8       min_B,                                         */
/*        __vptr_uint8       max_B,                                         */
/*        __vptr_uint16      mean_B,                                        */
/*        __vptr_uint32      variance_A                                     */
/*    )                                                                     */
/*                                                                          */
/*    im_A            : 8-bit grayscale image block. This buffer should     */
/*                      contain atleast blockHeight*blockStride bytes.      */
/*    blockStride     : Stride of the input image block.                    */
/*    blockWidth      : Width of the input image block.                     */
/*    blockHeight     : Height of the input image block.                    */
/*    statBlockWidth  : Width over which block statistics needs to be       */
/*                      computed.                                           */
/*    statBlockHeight : Height over which block statistics needs to be      */
/*                      computed.                                           */
/*    scratch_C       : Scratch buffer for storing row-wise minima and      */
/*                      row-wise maxima. User need to allocate a minimum    */
/*                      of 8*ceil(blockWidth/8)*36 bytes. Only one half     */
/*                      of this buffer will be effectively used.            */
/*    scratchSum_A    : Scratch buffer for storing row-wise sum of image    */
/*                      pixels. User need to allocate a minimum of          */
/*                      8*ceil(blockWidth/8)*36 bytes. Only one half        */
/*                      of this buffer will be effectively used.            */
/*    scratchSumSq_B  : Scratch buffer for holding row-wise sum of squares  */
/*                      of image pixels. User need to allocate at least     */
/*                      8*ceil(blockWidth/8)*36 bytes.                      */
/*    scratchSumSq_C  : Scratch buffer for holding block sum of squares of  */
/*                      image pixels. User need to allocate at least 8*36   */
/*                      bytes.                                              */
/*    scratchSumSq_C_lo : Address of 16-bit LSB of scratchSumSq_C           */
/*    scratchSumSq_C_hi : Address of 16-bit MSB of scratchSumSq_C           */
/*    min_B           : Block minimum output. The buffer requires a minimum */
/*                      of 8*36 bytes. The output will be present in an 8*8 */
/*                      region with a stride of 36 bytes.                   */
/*    max_B           : Block maximum output. The buffer requires a minimum */
/*                      of 8*36 bytes. The output will be present in an 8*8 */
/*                      region with a stride of 36 bytes.                   */
/*    mean_B          : Block mean output. The kernel outputs N*mean where  */
/*                      N is the number of samples in the block. The buffer */
/*                      requires a minimum of 8*36 bytes. The output will   */
/*                      be present in an 8*8 region with a stride of 36     */
/*                      bytes.                                              */
/*    variance_A      : Block variance output. The kernel outputs           */
/*                      N^2*variance where N is the number of samples in    */
/*                      the block.The buffer requires a minimum of 8*36     */
/*                      bytes.                                              */
/*                                                                          */
/*    Returns    :  None or void.                                           */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*     Number of pixels in a block (blockWidth x blockHeight) <= 256        */
/*     Number of blocks vertically (blockHeight/statBlockHeight) is <= 8    */
/*     Number of blocks horizontally (blockWidth/statBlockWidth) is <= 8    */
/*                                                                          */
/* PERFORMANCE MEASUREMENT:                                                 */
/*                                                                          */
/*                                                                          */
/* AUTHOR:                                                                  */
/*             Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/* VERSION:                                                                 */
/*            1.0 (Sept 2013) : Base version.                               */
/*                                                                          */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*im_A)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

#define STAT_OUT_HEIGHT (blockHeight/statBlockHeight)
#define STAT_OUT_WIDTH (blockWidth/statBlockWidth)

void vcop_block_statistics
(
    __vptr_uint8       im_A,
    unsigned short     blockStride,
    unsigned short     blockWidth,
    unsigned short     blockHeight,
    unsigned short     statBlockWidth,
    unsigned short     statBlockHeight,
    __vptr_uint8       scratch_C,
    __vptr_uint16      scratchSum_A,
    __vptr_uint32      scratchSumSq_B,
    __vptr_uint32      scratchSumSq_C,
    __vptr_uint16      scratchSumSq_C_lo,
    __vptr_uint16      scratchSumSq_C_hi,
    __vptr_uint8       min_B,
    __vptr_uint8       max_B,
    __vptr_uint16      mean_B,
    __vptr_uint32      variance_A
)
{
    // LOOP 1: Find row-wise max, min, sum, sum of squares over statBlockHeight
    // rows at a time. Here the kernel assumes that number of blocks vertically
    // is <= 8. This is required for transpose store.
    for(int I1 = 0; I1 < STAT_OUT_HEIGHT; I1++)
    {
        for(int I2 = 0; I2 < ((blockWidth + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH); I2++)
        {
            __vector Vmin, Vmax, Vsum, VsumSq;
            __agen AddrOut, AddrOutSum, AddrOutSumSq;

            AddrOut = I1*ELEMSZ + I2*36*VCOP_SIMD_WIDTH;
            AddrOutSum = I1*2*ELEMSZ + I2*36*VCOP_SIMD_WIDTH;
            AddrOutSumSq = I1*4*ELEMSZ + I2*36*VCOP_SIMD_WIDTH;

            Vmin = 255;
            Vmax = 0;
            Vsum = 0;
            VsumSq = 0;


            for(int I3 = 0; I3 < statBlockHeight; I3++)
            {
                __vector Vin, VinSq;
                __agen AddrIn;

                AddrIn = I1*statBlockHeight*blockStride + I2*VECTORSZ + I3*blockStride;

                Vin = im_A[AddrIn];

                Vsum += Vin;
                VsumSq += Vin*Vin;

                Vmin = min(Vin, Vmin);
                Vmax  = max(Vin, Vmax);
            }

            scratch_C[AddrOut].offset_np1() = Vmin;
            (scratch_C + 8)[AddrOut].offset_np1() = Vmax;
            scratchSum_A[AddrOutSum].offset_np1() = Vsum;
            scratchSumSq_B[AddrOutSumSq].offset_np1() = VsumSq;
        }
    }

    // LOOP 2: Operate column-wise over statBlockWidth columns to find block max,
    // min, sum, sum of squares. Here the kernel assumes that number of blocks
    // horizontally is <= 8. This is required for transpose store.
    for(int I1 = 0; I1 < STAT_OUT_WIDTH; I1++)
    {
        __vector Vmin, Vmax, Vsum, VsumSq;
        __agen AddrOut, AddrOutSum, AddrOutSumSq;

        AddrOut = I1*ELEMSZ;
        AddrOutSum = I1*2*ELEMSZ;
        AddrOutSumSq = I1*4*ELEMSZ;

        Vmin = 255;
        Vmax = 0;
        Vsum = 0;
        VsumSq = 0;

        for(int I2 = 0; I2 < statBlockWidth; I2++)
        {
            __vector VrowMin, VrowMax, VrowSum, VrowSumSq;
            __agen AddrIn;

            AddrIn = I1*statBlockWidth*36  + I2*36;

            VrowMin = scratch_C[AddrIn];
            VrowSum = scratchSum_A[AddrIn];
            VrowMax = (scratch_C + 8)[AddrIn];
            VrowSumSq = scratchSumSq_B[AddrIn];

            Vsum += VrowSum;
            VsumSq += VrowSumSq;

            Vmin = min(VrowMin, Vmin);
            Vmax = max(VrowMax, Vmax);
        }

        min_B[AddrOut].offset_np1() = Vmin;
        max_B[AddrOut].offset_np1() = Vmax;
        mean_B[AddrOutSum].offset_np1() = Vsum;
        scratchSumSq_C[AddrOutSumSq].offset_np1() = VsumSq;
    }

    // LOOP 3: Compute Variance from block sum and sum of squares.
    for(int I1 = 0; I1 < STAT_OUT_HEIGHT; I1++)
    {
        __agen AddrIn, Addrout;
        __vector Vmean, Vmean2, Vvar;
        __vector Vn;
        __vector Vlo, Vhi;
        __vector Vt1, Vt2, Vt1L, Vt1H;

        AddrIn = I1*36;
        Addrout = I1*STAT_OUT_WIDTH*4;

        Vlo = scratchSumSq_C_lo[AddrIn].ds2();  // AS0
        Vhi = scratchSumSq_C_hi[AddrIn].ds2();  // BU0
        Vmean = mean_B[AddrIn];

        Vn = statBlockWidth*statBlockHeight;       // CS0

        Vmean2 = Vmean*Vmean;
        Vt1 = Vhi*Vn;

        Vt2 = Vlo*Vn;                     // lo * Vn
        (Vt1L, Vt1H) = jus16(Vt1);

        Vt2 += Vt1L;

        Vvar = Vt2 - Vmean2;

        variance_A[Addrout] = Vvar;
    }
}

