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

void vcop_vec_bin_image_erode_cross
(
    __vptr_uint32 pIn,
    __vptr_uint32 out,
    unsigned short cols,
    unsigned short pitch,
    unsigned short height
)
{
     __vector  in00, in01, in10, in11, in20, in21, R6, R7,R12;
     __vector  R8, R9, R10, R11, R13, t1, t2,t3, t4;

    R10 =  31;
    R11 =  30;
    R12 = -2;
    R13 = -1;

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
    /*  The same register is used for accumulating for effectively         */
    /*  pipelining of 3 source instructions (SHFTOR and AND3).             */
    /*---------------------------------------------------------------------*/

            R6  = in00<<R13 ;
            R7  = in10<<R13 ;

            R6 |= in01 <<R10;
            R7 |= in11 <<R10;

            R8  = in10<<R12 ;
            R9  = in20<<R13 ;

            in10 &= R6 & R7 ;

            R8 |= in11 <<R11;
            R9 |= in21 <<R10;

            R8 &= in10 & R9 ;

            out[Addr1] = R8;
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_vec_bin_image_erode_cross_kernel.k                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


