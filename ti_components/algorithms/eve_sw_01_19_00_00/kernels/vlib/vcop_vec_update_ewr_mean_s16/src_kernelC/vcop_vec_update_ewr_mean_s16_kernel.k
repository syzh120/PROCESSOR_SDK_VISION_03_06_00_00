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

#define ELEMSZ          sizeof(*newestData)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define weight_neg1      (2^16- 1 - weight)

void vcop_vec_update_ewr_mean_s16
(
    __vptr_int16  currentMean,
    __vptr_uint8  newestData,
    __vptr_uint8  foreground,
    unsigned short weight,
    unsigned short weight_neg,
    unsigned int frameSize
)
{
    __vector R0,R2,R3,R1,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15;

    R12 = -9;
    R13 = -16;
    R4 = weight;
    R5 = weight_neg;
    R14 =1;
    R15 = 0xFF;

    for(int I1 = 0; I1 < frameSize/VCOP_SIMD_WIDTH; I1 ++ )
    {
         __agen Addr1,Addr2,Addr3;

        Addr1 = I1*VECTORSZ;
        Addr2 = I1*VECTORSZ*2;
        Addr3 = I1;

        R1 = foreground[Addr3];
        R2 = newestData[Addr1];
        R3 = currentMean[Addr2];

        R6 = R4 * R2  ;
        R7 = R5 * R3  ;

        R8 = R6 << R12;
        R9 = R7 << R13;

        R10 = R8 + R9 ;
        R6  = R1 ^ R15;

        R2 = unpack(R6,R14);

        currentMean[Addr2] = R10.predicate(R2);
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_mean_s16_kernel.k                     */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


