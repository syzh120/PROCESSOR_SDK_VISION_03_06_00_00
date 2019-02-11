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

void vcop_vec_update_ewr_variance_s16
(
    __vptr_int16 currentVar,
    __vptr_int16 currentVar_out,
    __vptr_int16 currentMean,
    __vptr_uint8  newestData,
    __vptr_uint8  foreground,
    unsigned short weight,
    unsigned short weight2,
    unsigned int frameSize
)
{
     __vector R0,R2,R3,R1,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15,fg,R16;

    R13 = 7;
    R14 = -3;
    R15 = -15;
    R12 = weight2;
    R11 = 1;
    R16 = 0xFF;

    for(int I1 = 0; I1 < frameSize/VCOP_SIMD_WIDTH; I1++ )
    {

        __agen Addr1,Addr2,Addr3;

        Addr1 = I1*VECTORSZ;
        Addr2 = I1*VECTORSZ*2;
        Addr3 = I1;

        fg  = foreground  [Addr3];
        R8  = newestData  [Addr1];
        R9  = currentMean [Addr2];
        R10 = currentVar  [Addr2];

        R7 = R8  << R13;
        R3 = R10 << R14;

        R7 = R7 - R9;
        R5 = R16 ^ fg;

        R1 = R7 * R7;
        R4 = unpack(R5,R11);

        R2 = R1 << R15;

        R3 = R2 - R3;

        R2 = R3 * R12;

        R1 = R2 << R15;

        R6 = R10 + R1;

        R6 = abs(R6);

        currentVar[Addr2] = R6.predicate(R4);
     }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_variance_s16_kernel.k                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


