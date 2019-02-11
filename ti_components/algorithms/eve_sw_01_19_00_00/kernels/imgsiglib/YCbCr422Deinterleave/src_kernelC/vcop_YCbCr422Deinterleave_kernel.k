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


/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDeinterleave                                   */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDeinterleave" acceptsd 8 or 16-bit data */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 422 or */
/* 422 format, the output can be of 422, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCr422_Deinterleave422_char                         */
/* (                                                               */
/*     __vptr_uint32  YCbCr_char,                                  */
/*     __vptr_int8    YCbCrmask,                                   */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint8   Y_char,                                      */
/*     __vptr_uint8   Cb_char,                                     */
/*     __vptr_uint8   Cr_char                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop_YCbCr422_Deinterleave422_short                        */
/* (                                                               */
/*     __vptr_uint32  YCbCr_short,                                 */
/*     __vptr_int8    YCbCrmask,                                   */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  Y_short,                                     */
/*     __vptr_uint16  Cb_short,                                    */
/*     __vptr_uint16  Cr_short                                     */
/* );                                                              */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* YCbCr422_Deinterleave422_char: 1/8 cyc/pix                      */
/* YCbCr422_Deinterleave422_short: 1/8 cyc/pix                     */
/*                                                                 */
/*=================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH    (16)

#define ELEMSZ_IN_CHAR      sizeof( *YCbYCr_char )
#define VECTORSZ_IN_CHAR    (VCOP_2SIMD_WIDTH * ELEMSZ_IN_CHAR)

#define ELEMSZ_IN_SHORT     sizeof( *YCbYCr_short )
#define VECTORSZ_IN_SHORT   (VCOP_2SIMD_WIDTH * ELEMSZ_IN_SHORT)

#define ELEMSZ_Y_CHAR       sizeof( *Y_char )
#define VECTORSZ_Y_CHAR     (VCOP_SIMD_WIDTH * ELEMSZ_Y_CHAR)

#define ELEMSZ_Cb_CHAR       sizeof( *Cb_char )
#define VECTORSZ_Cb_CHAR     ((VCOP_SIMD_WIDTH - 4) * ELEMSZ_Cb_CHAR)

#define ELEMSZ_Y_SHORT       sizeof( *Y_short )
#define VECTORSZ_Y_SHORT    (VCOP_SIMD_WIDTH * ELEMSZ_Y_SHORT)

#define ELEMSZ_Cb_SHORT       sizeof( *Cb_short )
#define VECTORSZ_Cb_SHORT    ((VCOP_SIMD_WIDTH - 4) * ELEMSZ_Cb_SHORT)

#define K0                  0
#define K1                  1
#define K2                  2
#define K3                  3
#define K4                  4
#define K5                  5
#define K6                  6
#define K7                  7
#define K8                  8

/* * * * * * * * * * * * * * * * * * * * */


void vcop_YCbCr422_Deinterleave422_char
(
    __vptr_uint8   YCbYCr_char,
    unsigned int   npixels,
    __vptr_uint8   Y_char,
    __vptr_uint8   Cb_char,
    __vptr_uint8   Cr_char
)
{
    __vector VY, VCb, VCr;
    __vector VCbCr;
    __vector Vdummy;

    /*-----------------------------------------------------------*/
    /* YCbCr 422 pattern is:                                     */
    /* Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr                   */
    /*-----------------------------------------------------------*/

   Vdummy = 0;
   for (int I1 = 0; I1 < (npixels/VCOP_2SIMD_WIDTH); I1++)
   {
       __agen Addr_in;
       __agen Addr_Y_out;
       __agen Addr_Cb_out;

       Addr_in     = I1 * VECTORSZ_IN_CHAR;
       Addr_Y_out  = I1 * VECTORSZ_Y_CHAR;
       Addr_Cb_out = I1 * VECTORSZ_Cb_CHAR;

       (VY, VCbCr) = YCbYCr_char[Addr_in].deinterleave();

       (VCb, VCr) = (VCbCr, Vdummy).deinterleave();

       Y_char[Addr_Y_out]   = VY;
       Cb_char[Addr_Cb_out].npt()  = VCb;
       Cr_char[Addr_Cb_out].npt()  = VCr;

   }
}

void vcop_YCbCr422_Deinterleave422_short
(
    __vptr_uint16  YCbYCr_short,
    unsigned int   npixels,
    __vptr_uint16  Y_short,
    __vptr_uint16  Cb_short,
    __vptr_uint16  Cr_short
)
{
    __vector VY, VCb, VCr;
    __vector VCbCr;
    __vector Vdummy;

    /*-----------------------------------------------------------*/
    /* YCbCr 422 pattern is:                                     */
    /* Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr                   */
    /*-----------------------------------------------------------*/

   Vdummy = 0;
   for (int I1 = 0; I1 < (npixels/VCOP_2SIMD_WIDTH); I1++)
   {
       __agen Addr_in;
       __agen Addr_Y_out;
       __agen Addr_Cb_out;

       Addr_in     = I1 * VECTORSZ_IN_SHORT;
       Addr_Y_out  = I1 * VECTORSZ_Y_SHORT;
       Addr_Cb_out = I1 * VECTORSZ_Cb_SHORT;

       (VY, VCbCr) = YCbYCr_short[Addr_in].deinterleave();
       (VCb, VCr) = (VCbCr, Vdummy).deinterleave();

       Y_short[Addr_Y_out]   = VY;
       Cb_short[Addr_Cb_out].npt()  = VCb;
       Cr_short[Addr_Cb_out].npt()  = VCr;
   }
}


/* * * * * * * * * * * * * * * * * * * * */
