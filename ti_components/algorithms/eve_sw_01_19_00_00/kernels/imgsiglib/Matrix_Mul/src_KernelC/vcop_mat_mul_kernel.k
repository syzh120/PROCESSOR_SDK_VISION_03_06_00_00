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

#define ELEMSZ_IN1        sizeof(*in1_ary)
#define VECTORSZ_IN1      (VCOP_SIMD_WIDTH * ELEMSZ_IN1)

#define ELEMSZ_IN2        sizeof(*in2_ary)
#define VECTORSZ_IN2     (VCOP_SIMD_WIDTH * ELEMSZ_IN2)

#define ELEMSZ_OUT       sizeof(*res)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define SAT_LO_CHAR           (-128)
#define SAT_HI_CHAR           (127)
#define SAT_LO_SHORT          (-32768)
#define SAT_HI_SHORT          (32767)

void vcop_mat_mul_uchar_uchar_short
(
    __vptr_uint8   in1_ary,      // Pointer to first input array.
    __vptr_uint8   in2_ary,      // Pointer to second input array.
    __vptr_int16   res,          // Pointer to output array.
    int            w_in1,        // Width of the first input array in pixels.
    int            h_in1,        // Height of the first input array in pixels.
    int            w_in2,        // Width of the second input array in pixels.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_in1, v_in2, v_sum;

    /*-------------------------------------------------------------------*/
    /* Actual matrix multiplication step.                                */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_in1; I1++)
    {
        v_sum = 0;

        for ( int I2 = 0; I2 < w_in2/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr = I1 * ELEMSZ_OUT * w_in1 + I2 * ELEMSZ_OUT * VCOP_SIMD_WIDTH;

            for ( int I3 = 0; I3 < w_in1; I3++)
            {
                    __agen in1_Addr, in2_Addr;

                    in1_Addr = I1 * ELEMSZ_IN1 * w_in1 + I3 * ELEMSZ_IN1;
                    in2_Addr = I2 * ELEMSZ_IN2 * VCOP_SIMD_WIDTH + I3 * ELEMSZ_IN2 * w_in2;

                    v_in1  =  in1_ary[in1_Addr].onept();
                    v_in2  =  in2_ary[in2_Addr].npt();

                    v_sum += (v_in1 * v_in2);
             }

             res[outAddr].npt() = v_sum.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}

/*-----------------------------------------------------------------*/
/* End of file : vcop_mat_mul_kernel.k                             */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                       */
/*=================================================================*/
