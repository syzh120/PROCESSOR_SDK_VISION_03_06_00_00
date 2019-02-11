/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2012 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ          sizeof(*Emag)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define NUM_TBLS    (8)
#define NUM_PTS_TLU (1)
#define IND_ELEMSZ (NUM_TBLS * sizeof(*Emag))
#define OUT_ELEMSZ (NUM_TBLS  * NUM_PTS_TLU * sizeof(*TLU_m_inv))

void vcop_normalFlow
(
    __vptr_int16   imDiff,
    __vptr_int16   Emag,
    __vptr_int16   LUT,
    __vptr_int16   E,
    __vptr_int16   TLU_m_inv,
             int   T,
           short   numEls,
    __vptr_int16   normalFlowU,
    __vptr_int16   normalFlowV
)
{
    __vector m, m_inv, ex, ey, d, Vdst;
    __vector R0, R1, R2, R3;
    __vector Ex_1, Ey_1, d_1, Ex_2, Ey_2;
    __vector im, im_1, exd, eyd;
    __vector Vpred;
    __vector Vindex, Vtabledata;

//  Look-up table kernel to compute the inverse of Emag

    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
    for (int I1 = 0; I1 < numEls/NUM_TBLS; I1++)
    {
        __agen index_addr = I1 * IND_ELEMSZ;
        __agen table_addr = 0;
        __agen out_addr   = I1 * OUT_ELEMSZ;

        Vindex     = Emag[index_addr];
        Vtabledata = LUT[table_addr].lookup(Vindex);
        TLU_m_inv[out_addr].table_npt() = Vtabledata;
    }

    R0 = -8;
    R2 = T;
    R3 = 0;

// Compute kernel to do the normal flow computations

    for (int I1 = 0; I1 < numEls/VCOP_SIMD_WIDTH; I1++)
    {
        __agen Addr, Addr1;

        Addr = I1*VECTORSZ;
        Addr1 = 2*I1*VECTORSZ;

        m = Emag[Addr];
        im = imDiff[Addr];
        m_inv = TLU_m_inv[Addr];

        (Ex_1,Ey_1) = E[Addr1].deinterleave();

        Ex_2 = (Ex_1 * m_inv).truncate(8);
        Ey_2 = (Ey_1 * m_inv).truncate(8);

        im_1 = R3 - im;
        d = (im_1 * m_inv).truncate(8);

        exd = (Ex_2 * d);
        eyd = (Ey_2 * d);

        Vpred = (m > R2);  // Check if the Emag value is greater than threshold T

        normalFlowU[Addr] = exd.truncate(7).predicate(Vpred);
        normalFlowV[Addr] = eyd.truncate(7).predicate(Vpred);
    }
}

/* ======================================================================== */
/*  End of file:  vcop_normalFlow_kernel.k                                  */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
