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

/*--------------------------------------------------------------------------*/
/* NAME: vcop_copy_new_lk_xy_kernel.k                                       */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for copying the xy points from internal scratch */
/* to output buffer                                                         */
/*                                                                          */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_copy_new_lk_xy:                                                   */
/*   - ~ (1/8)(numKeyPoints)                                                */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pInput_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pOutput_B)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)

#define OUT_ELEMSZ_VALID_PTS sizeof(*currValidPoints)
#define OUT_ELEMSZ_VALID_ADRS sizeof(*pBaseAddrList)


void vcop_copy_new_lk_xy
(
    __vptr_int16   pInput_A,
    __vptr_int16   pOutput_B,
    __vptr_uint8  currValidPoints,        
		__vptr_uint32 pBaseAddrList ,
		__vptr_uint32 pValidAddrList,
		__vptr_uint32 pOutAddrList     ,
		__vptr_uint32 pValidOutAddrList,
    __vptr_int16   pLocalX,
    __vptr_int16   pLocalY,
    __vptr_int16   pLocalXY,
    unsigned short  numKeyPoints
)
{
    __vector Veven, Vodd;
	__vector Vevenlocalxy, Voddlocalxy;
    __agen AddrIn, AddrOut, AddrXYLocal;              //Address generators for input and output buffers
    __vector Vconst1;
    __agen AddrValidPts, AddrValidAdrs;             
    __vector Vsrc1;
    __vector Vsrc2;

    Vconst1 = 1;
    for (int I1 = 0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I1++)
    {
       AddrIn  = I1*2*INP_VECTORSZ;
       AddrOut = I1*2*OUT_VECTORSZ;
	   AddrXYLocal = I1*OUT_VECTORSZ;
       AddrValidPts  = I1*OUT_ELEMSZ_VALID_PTS*VCOP_SIMD_WIDTH;
       AddrValidAdrs = I1*OUT_ELEMSZ_VALID_ADRS*VCOP_SIMD_WIDTH;
       //Deinterleaving loading of the (X,Y) coordinate pair list
       (Veven, Vodd) =  pInput_A[AddrIn].deinterleave();
       Vsrc1 = pBaseAddrList[AddrValidAdrs];
       Vsrc2 = pOutAddrList[AddrValidAdrs];
       //Deinterleaving loading of the local (X,Y) coordinate pair list
       (Vevenlocalxy, Voddlocalxy) =  pLocalXY[AddrIn].deinterleave();

       pValidAddrList[AddrValidAdrs]    = Vsrc1;
       pValidOutAddrList[AddrValidAdrs] = Vsrc2;
       currValidPoints[AddrValidPts]    = Vconst1;
	   pLocalX[AddrXYLocal] = Vevenlocalxy;
	   pLocalY[AddrXYLocal] = Voddlocalxy;
       //Store the bilinear weights for each key point
       pOutput_B[AddrOut].interleave() = (Veven, Vodd);
   }
}
