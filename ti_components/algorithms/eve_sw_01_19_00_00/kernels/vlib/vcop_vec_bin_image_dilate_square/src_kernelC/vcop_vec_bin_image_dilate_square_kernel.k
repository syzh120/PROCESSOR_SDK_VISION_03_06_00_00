/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define ALIGN_32SIMD(a) ((a + 32*VCOP_SIMD_WIDTH-1) & ~(32*VCOP_SIMD_WIDTH-1))

void vcop_vec_bin_image_dilate_square
(
    __vptr_uint32 pIn,
    __vptr_uint32 out,
    unsigned short cols,
    unsigned short pitch,
    unsigned short height
)
{

     __vector  R8, R9, R10, R11, t1, t2, t3, t4;
    __vector r,in00, in01, in10, in11, in20, in21;

    R8  =  31;
    R9  =  30;
    R10 = -2;
    R11 = -1;

    for(int I1 = 0; I1 < height; I1 ++ )
    {
        for (int I2 = 0; I2 < ALIGN_32SIMD(cols)/(32*VCOP_SIMD_WIDTH); I2++)
        {
            __agen Addr1;

            Addr1 = I1*(pitch/8) + I2*VECTORSZ;

            in00 = (pIn)                  [Addr1];
            in01 = (pIn + 1*4)            [Addr1];
            in10 = (pIn + pitch/8)        [Addr1];
            in11 = (pIn + pitch/8   + 1*4)[Addr1];
            in20 = (pIn + pitch*2/8)      [Addr1];
            in21 = (pIn + pitch*2/8 + 1*4)[Addr1];

    /*---------------------------------------------------------------------*/
    /*  As ORs and SHIFTs can be interchanged, we group the terms having   */
    /*  same shifts, we OR them first and then apply a single SHIFT.       */
    /*---------------------------------------------------------------------*/

            in00 |= in10 | in20;
            in11 |= in01 | in21;

            t1 = in00<<R11;
            t2 = in11<<R8 ;

            t1 |= t2 | in00;

            t3 = in00<<R10;
            t4 = in11<<R9 ;

            t1 |= t3 | t4;

            out[Addr1] = t1;
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_dilate_square_kernel.k                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


