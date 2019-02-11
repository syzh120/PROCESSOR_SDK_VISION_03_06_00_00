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
/* Tile Approach                                                                */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for chroma of YUV420 format using nearest neighbor interpolation method */
void vcop_nnInterpolate420SPchroma(
        __vptr_uint8        src,
        __vptr_uint16       dst,
        unsigned short      numMappedPixels,
        __vptr_uint16       tluIndexArray,
        __vptr_uint16       scatterStoreArray,
        __vptr_uint8        scratchHbuf8b,
        __vptr_uint16       scratchHbuf16b,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set,
        unsigned short      dst_end_offset
)
{
    /* Perform TLU */
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*scratchHbuf8b);
            Vindex = tluIndexArray[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            scratchHbuf8b[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }

    for (int I1 = 0; I1 < 1; I1++) {
        __vector Voffset;
        __agen Addr0;
        Addr0 = 0;
        Voffset = dst_end_offset;

        (scatterStoreArray + 2*numMappedPixels)[Addr0] = Voffset;
    }

    /* Copy src into scratchHbuf so it is interleaved */
    for (int I1 = 0; I1 < ALIGN_SIMD(numMappedPixels)/(VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2, Addr_out;
        __vector srcUV, scatterStore;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*scratchHbuf16b);
        Addr2 = I1*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray);
        Addr_out = 0;

        srcUV = scratchHbuf16b[Addr1].npt();
        scatterStore = scatterStoreArray[Addr2].npt();

        dst[Addr_out].s_scatter(scatterStore)= srcUV;
    }
}

/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for chroma of YUV420 format using nearest neighbor interpolation method */
void vcop_nnInterpolate420SPchromaBB(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
    /* Perform TLU */
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*dst);
            Vindex = tluIndexArray[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            dst[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}
