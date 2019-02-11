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

#define ELEMSZ          sizeof(*data1_ptr)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define ALIGN_32SIMD(a) ((a + 32*VCOP_SIMD_WIDTH-1) & ~(32*VCOP_SIMD_WIDTH-1))


void vcop_vec_bin_image_morph_diff
(
    unsigned short         blk_w,
    unsigned short         line_ofst,
    unsigned short         blk_h,
    __vptr_uint32          data1_ptr,
    unsigned short         data1_bit_shift,
    __vptr_uint32          data2_ptr,
    unsigned short         data2_bit_shift,
    __vptr_uint32          output_ptr
)
{
    __vector Vdata1, Vdata2, Vin1, Vin1_1, Vin2, Vin2_1, Vdiff;
    __vector Vdata1shift, Vdata1shift_opp, Vdata2shift, Vdata2shift_opp;

    Vdata1shift     =     -data1_bit_shift;
    Vdata1shift_opp = 32 - data1_bit_shift;
    Vdata2shift     =     -data2_bit_shift;
    Vdata2shift_opp = 32 - data2_bit_shift;

    for (int I1 = 0; I1 < blk_h; I1++)
    {
        for (int I2 = 0; I2 < ALIGN_32SIMD(blk_w)/(32*VCOP_SIMD_WIDTH); I2++)
        {
            __agen A0, A1;
            A0 = I1*(line_ofst/8) + I2*VECTORSZ;

            Vin1   =  data1_ptr       [A0];
            Vin1_1 = (data1_ptr + 1*4)[A0];
            Vin2   =  data2_ptr       [A0];
            Vin2_1 = (data2_ptr + 1*4)[A0];

            Vdata1   = Vin1   << Vdata1shift;
            Vdata1  |= Vin1_1 << Vdata1shift_opp;

            Vdata2   = Vin2   << Vdata2shift;
            Vdata2  |= Vin2_1 << Vdata2shift_opp;

            Vdiff = Vdata1 ^ Vdata2;

            output_ptr[A0] = Vdiff;
        }
    }
}
