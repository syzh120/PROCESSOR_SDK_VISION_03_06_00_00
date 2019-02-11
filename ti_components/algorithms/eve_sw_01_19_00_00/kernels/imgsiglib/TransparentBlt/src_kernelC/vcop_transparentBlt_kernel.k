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

#define VCOP_2SIMD_WIDTH        (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN1               sizeof( *inrgb555_ptr )
#define VECTORSZ_IN1             (VCOP_2SIMD_WIDTH * ELEMSZ_IN1)

#define ELEMSZ_IN2               sizeof( *backrgb555_ptr )
#define VECTORSZ_IN2             (VCOP_2SIMD_WIDTH * ELEMSZ_IN2)

#define ELEMSZ_OUT              sizeof( *outptr )
#define VECTORSZ_OUT            (VCOP_2SIMD_WIDTH * ELEMSZ_OUT)

/* * * * * * * * * * * * * * * * * * * * */


void vcop_transparentBlt_ushort_ushort
(
    __vptr_uint16    inrgb555_ptr,
    __vptr_uint16    backrgb555_ptr,
    unsigned short   transparentClr,
    unsigned short   in1_w,
    unsigned short   in1_h,
    unsigned short   in2_w,
    unsigned short   in2_h,
    unsigned short   comp_w,
    unsigned short   comp_h,
    unsigned short   out_w,
    unsigned short   out_h,
    __vptr_uint16    outptr
)
{
    __vector Vin0,  Vin1;          // foreground input
    __vector Vbk0,  Vbk1;          // background input
    __vector Vcomp0, Vcomp1;
    __vector VtranspClr;

    VtranspClr = transparentClr;

    for (int I1 = 0; I1 < comp_h; I1++)
    {
        for (int I2 = 0; I2 < comp_w/VCOP_2SIMD_WIDTH; I2++)
        {
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;

            Addr_in1   =  I1 * in1_w * ELEMSZ_IN1 + I2 * VECTORSZ_IN1;
            Addr_in2   =  I1 * in2_w * ELEMSZ_IN2 + I2 * VECTORSZ_IN2;
            Addr_out   =  I1 * out_w * ELEMSZ_OUT + I2 * VECTORSZ_OUT;

            (Vin0, Vin1)       =  inrgb555_ptr[Addr_in1].deinterleave();
            (Vbk0, Vbk1)       =  backrgb555_ptr[Addr_in2].deinterleave();

            /*-----------------------------------------------------------*/
            /* Compare the foreground color to the transparent color     */
            /* value transparentClr.                                     */
            /*-----------------------------------------------------------*/

            Vcomp0 = (Vin0 == VtranspClr);
            Vcomp1 = (Vin1 == VtranspClr);

            /*-----------------------------------------------------------*/
            /* Choose from either background or foreground (image to be  */
            /* overlayed).                                               */
            /*-----------------------------------------------------------*/

            Vin0  = select(Vcomp0, Vbk0, Vin0);
            Vin1  = select(Vcomp1, Vbk1, Vin1);

            outptr[Addr_out].interleave() = (Vin0, Vin1);
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * */
