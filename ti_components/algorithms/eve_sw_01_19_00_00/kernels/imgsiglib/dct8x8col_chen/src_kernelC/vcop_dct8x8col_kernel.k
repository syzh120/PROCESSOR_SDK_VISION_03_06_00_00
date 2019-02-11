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

#define ELEMSZ_IN      sizeof(*in)
#define VECTORSZ_IN   (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT      sizeof(*out)
#define VECTORSZ_OUT   (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define WORD_SIZE      (4)

#define SAT_LO   (-32768)
#define SAT_HI   (32767)

#define DCT_SIZE_8     (8)

/*-------------------------------------------------------------------------*/
/* We hard code the register allocation in case the compiler fails to      */
/* register allocate in optimized mode.                                    */
/*-------------------------------------------------------------------------*/

#define    x0     V0
#define    x1     V2
#define    x2     V4
#define    x3     V6
#define    x4     V8
#define    x5     V10
#define    x6     V12
#define    x7     V14

#define    c1     V1
#define    c2     V3
#define    c3     V5
#define    c4     V7
#define    c5     V9
#define    c6     V11
#define    c7     V13


void vcop_dct8x8col_int_int
(
    __vptr_int16   in,          // Pointer to an input array of "type_input".
    __vptr_int16   f_ignore,    // This pointer is ignored, in this implementation
                                // the DCT coeffs are implicitly defined within the kernel.
    __vptr_int16   out,         // Pointer to output array of "type_output".
    int            w_input,     // Width of the input image in pixels.
    int            h_input,     // Height of the input image in pixels.
    int            w_out,       // Width of the output in pixels.
    int            h_out,       // Height of the output coefficents in pixels.
    int            HBLKS,       // The number of 8x8 blocks of input in horz direction.
    int            VBLKS,       // The number of 8x8 blocks of input in vert direction.
    int            type_input,  // 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int            type_coeff,  // This is also ignored, coefficients are always 32-bit int
                                // and implicitly defined.
    int            type_output, // 0 - BYTE,  1 - SHORT
    int            rnd_shift    // round and shift amount may be specified.
)

{

    __vector  res_a, res_b, res_c, res_d, res_e, res_f, res_g, res_h;

    /*-------------------------------------------------------------------*/
    /* DCT column wise filtering. This is the part where the transform T */
    /* (8x8) is applied to image block A as T*A.                         */
    /*-------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < VBLKS; I1++)
    {
        for ( int I2 = 0; I2 < HBLKS; I2++)
        {
             __agen dataAddr0;
             __agen dataAddr1;

             dataAddr0 =  (I1 * DCT_SIZE_8 * w_input * ELEMSZ_IN ) + (I2 * VECTORSZ_IN );
             dataAddr1 =  (I1 * DCT_SIZE_8 * (w_out + HBLKS) * WORD_SIZE ) + (I2 * DCT_SIZE_8 * 9 * WORD_SIZE );

             x0 = (in + (0 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V0
             x1 = (in + (1 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V1
             x2 = (in + (2 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V2
             x3 = (in + (3 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V3
             x4 = (in + (4 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V4
             x5 = (in + (5 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V5
             x6 = (in + (6 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V6
             x7 = (in + (7 * w_input * ELEMSZ_IN ) )[dataAddr0];   // V7

             /*----------------------------------------------------------*/
             /* Coefficients are defined here in Q15 format. Please note */
             /* that these are read for each loop execution as some of   */
             /* these registers are reused due to register pressure      */
             /* further on in code execution.                            */
             /*----------------------------------------------------------*/

             c4 = 23173;                                       // V8

             c2 = 30271;                                       // V9
             c6 = 12537;                                       // V10

             c1 = 32138;                                       // V11
             c3 = 27243;                                       // V12
             c5 = 18205;                                       // V13
             c7 =  6389;                                       // V14

             /*----------------------------------------------------------*/
             /* First stage of butterfly -                               */
             /*----------------------------------------------------------*/

             (x0, x7).addsub();  // x0+x7, x0-x7
             (x1, x6).addsub();  // x1+x6, x1-x6
             (x2, x5).addsub();  // x2+x5, x2-x5
             (x3, x4).addsub();  // x3+x4, x3-x4

             /*----------------------------------------------------------*/
             /* Second stage of butterfly -                              */
             /*----------------------------------------------------------*/

             (x0, x3).addsub(); // x0+x7+x3+x4, x0+x7-x3-x4
             (x1, x2).addsub(); // x1+x6+x2+x5, x1+x6-x2-x5

             (x6, x5).addsub(); // x1-x6+x2-x5, x1-x6-x2+x5

             /*----------------------------------------------------------*/
             /* Third stage of butterfly -                               */
             /*----------------------------------------------------------*/

             (x0, x1).addsub(); // x0+x7+x3+x4+x1+x6+x2+x5
                                // x0+x7+x3+x4-x1-x6-x2-x5

             /*----------------------------------------------------------*/
             /* This step is merged into the next step to save a cycle   */
             /* and we truncate by 15, instead of 16.                    */
             /*   x5 = x5 << 1;                                          */
             /*   x6 = x6 << 1;                                          */
             /*----------------------------------------------------------*/

             x6 = (x6 * c4).truncate(15); // c4 * x1-x6+x2-x5
             x5 = (x5 * c4).truncate(15); // c4 * x1-x6-x2+x5

             /*----------------------------------------------------------*/
             /* Continue second stage of butterfly...                    */
             /*----------------------------------------------------------*/

             (x7, x6).addsub(); // x0-x7 + c4 X x1-x6+x2-x5; x0-x7 - c4 X x1-x6+x2-x5;
             (x4, x5).addsub(); // x3-x4 + c4 X x1-x6-x2-x5; x3-x4 - c4 X x1-x6-x2-x5;

             /*----------------------------------------------------------*/
             /* Transform coefficients multiplied with the input data    */
             /* reordered and manipulated using butterfly.               */
             /*----------------------------------------------------------*/

             res_a  =  c4 * x0;
             res_b  =  c4 * x1;

             res_c  = (c2 * x3);
             res_c += (c6 * x2);

             res_d  = (c6 * x3);
             res_d -= (c2 * x2);

             res_e  = (c1 * x7);
             res_e += (c7 * x4);

             res_f  = (c3 * x6);
             res_f -= (c5 * x5);

             res_g  = (c5 * x6);
             res_g += (c3 * x5);

             res_h  = (c7 * x7);
             res_h -= (c1 * x4);


             /*----------------------------------------------------------*/
             /* Output data is reordered to write to the correct         */
             /* location.                                                */
             /*----------------------------------------------------------*/

	         (out + (0 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_a.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V0
             (out + (1 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_e.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V8
             (out + (2 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_c.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V15
             (out + (3 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_f.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V9
             (out + (4 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_b.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V1
             (out + (5 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_g.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V10
             (out + (6 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_d.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V3
             (out + (7 * ELEMSZ_OUT))[dataAddr1].offset_np1() = res_h.round( rnd_shift ).saturate( SAT_LO, SAT_HI );  // V2

        }
    }
}



