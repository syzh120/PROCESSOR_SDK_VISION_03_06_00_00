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

#include "vcop_remap_kernel.h"

/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for luma using nearest neighbor interpolation method */
void vcop_nnInterpolate8b(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scratch,             /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint16       stride_ptr,
        unsigned char       QShift,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{

/* Calculate the different indexes which will be used for TLU */
#define index_ptr (scratch)

    __vector  Vstride, VQShift, negVQShift;
    __agen Addr0=0;

    negVQShift= -QShift;
    VQShift= QShift;
    Vstride= stride_ptr[Addr0].onept();

    for (int I1 = 0; I1 < ALIGN_2SIMD(outputBlockSize)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2;

        __vector yFrac1, yFrac2, roundedYFrac1, roundedYFrac2;
        __vector tluIndex1, tluIndex2;
        __vector fracMap1, fracMap2;
        __vector Vmaskx;
        __vector Vshifty;

        Vmaskx = 0x000000000F;
        Vshifty = -4;

        Addr1 = I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);

        (tluIndex1, tluIndex2) = tluIndexArray[Addr2].deinterleave();
        (fracMap1, fracMap2) = fracArray[Addr1].deinterleave();

        yFrac1 = fracMap1 << Vshifty;
        yFrac2 = fracMap2 << Vshifty;

        roundedYFrac1= round(yFrac1, VQShift);
        roundedYFrac2= round(yFrac2, VQShift);

        tluIndex1+= roundedYFrac1*Vstride;
        tluIndex2+= roundedYFrac2*Vstride;

        index_ptr[Addr2].interleave() = (tluIndex1, tluIndex2);
    }

    /* Perform TLU */
    _LOOKUP(1,1);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*sizeof(*dst);
            Vindex = index_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            dst[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}
