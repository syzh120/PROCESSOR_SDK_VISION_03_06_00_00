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

/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT       sizeof(*result)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_blockAverage2x2_uchar
(
    __vptr_uint8  in,                  //  Pointer to an input array of "type_input".
    __vptr_uint8 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute +(2*VCOP_SIMD_WIDTH-1)) / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;
            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}

void vcop_blockAverage2x2_char
(
    __vptr_int8  in,                  //  Pointer to an input array of "type_input".
    __vptr_int8 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute +(2*VCOP_SIMD_WIDTH-1))  / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;

            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}

void vcop_blockAverage2x2_ushort
(
    __vptr_uint16  in,                  //  Pointer to an input array of "type_input".
    __vptr_uint16 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute +(2*VCOP_SIMD_WIDTH-1))  / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;

            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}

void vcop_blockAverage2x2_short
(
    __vptr_int16  in,                  //  Pointer to an input array of "type_input".
    __vptr_int16 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute + (2*VCOP_SIMD_WIDTH-1))  / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;

            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}
