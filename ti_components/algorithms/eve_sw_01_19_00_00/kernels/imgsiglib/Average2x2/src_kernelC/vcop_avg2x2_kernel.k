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

/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_INTER     sizeof(*inter)
#define VECTORSZ_INTER   (VCOP_SIMD_WIDTH * ELEMSZ_INTER)

#define ELEMSZ_OUT       sizeof(*result)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define TRANSPOSE_WIDTH  8
#define WORD_SIZE        4

/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_uchar
(
    __vptr_uint8  in,                  //  Pointer to an input array of "type_input".
    __vptr_int16 result,               //  Pointer to output array of "type_output".
    int          w_input,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_blk,                //  The compute width over which avg2x2 values are found.
    int          h_blk,                //  The compute height for avg2x2 filter.
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int          type_output           //  0 - BYTE,  1 - SHORT
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;

        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2;

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}


/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_char
(
    __vptr_int8  in,                   //  Pointer to an input array of "type_input".
    __vptr_int16 result,               //  Pointer to output array of "type_output".
    int          w_input,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_blk,                //  The compute width over which avg2x2 values are found.
    int          h_blk,                //  The compute height for avg2x2 filter.
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int          type_output           //  0 - BYTE,  1 - SHORT
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;

        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2;

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}


/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_ushort
(
    __vptr_uint16  in,                 //  Pointer to an input array of "type_input".
    __vptr_int16 result,               //  Pointer to output array of "type_output".
    int          w_input,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_blk,                //  The compute width over which avg2x2 values are found.
    int          h_blk,                //  The compute height for avg2x2 filter.
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int          type_output           //  0 - BYTE,  1 - SHORT
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;

        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2;

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}

/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_short
(
    __vptr_int16  in,                  //  Pointer to an input array of "type_input".
    __vptr_int16 result,               //  Pointer to output array of "type_output".
    int          w_input,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_blk,                //  The compute width over which avg2x2 values are found.
    int          h_blk,                //  The compute height for avg2x2 filter.
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int          type_output           //  0 - BYTE,  1 - SHORT
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;

        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2;

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}

