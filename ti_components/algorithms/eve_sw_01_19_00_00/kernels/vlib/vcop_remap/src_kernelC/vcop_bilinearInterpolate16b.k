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

/* Compute the bilinear interpolated luma pixels for U16BIT format */
/*------------------------------------------------------------------------------*/
/* Tile and Bounding Box Approach                                               */
/*------------------------------------------------------------------------------*/
void vcop_bilinearInterpolate16b(
        __vptr_uint16       src,
        __vptr_uint16       dst,
        unsigned short      maxNumMappedPixels,
        unsigned short      numMappedPixels,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scatterStoreArray,
        __vptr_uint16       scratchLUT,                  /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint16       scratchPixel,
        __vptr_uint16       stride_ptr,
        unsigned char       mnQShift,
        unsigned char       oQShift,
        unsigned short      qScale,
        unsigned char       rightShift,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
/* Calculate the different indexes which will be used for TLU */
#define index00_ptr (scratchLUT)
#define index01_ptr (scratchLUT + sizeof(*scratchLUT)*ALIGN_2SIMD(maxNumMappedPixels))

    __vector Vstride;
    __agen Addr0=0;

    Vstride= stride_ptr[Addr0].onept();

    for (int I1 = 0; I1 < ALIGN_2SIMD(numMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr2;

        __vector index00_1,index00_2;               //Top-left pixel
        __vector index01_1,index01_2;               //Bottom-left pixel

        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);

        (index00_1, index00_2) = tluIndexArray[Addr2].deinterleave();

        index01_1= index00_1 + Vstride;
        index01_2= index00_2 + Vstride;

        index00_ptr[Addr2].interleave() = (index00_1, index00_2);
        index01_ptr[Addr2].interleave() = (index01_1, index01_2);
    }


/* Perform TLU for pix00, pix10 */
#define pix00_ptr scratchPixel
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*dst);
            Vindex = index00_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            pix00_ptr[out_agen].table_npt() = Vdata;
    }

/* Perform TLU for pix01, pix11 */
#define pix01_ptr (scratchPixel + sizeof(*dst)*2*maxNumMappedPixels)
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*dst);
            Vindex = index01_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            pix01_ptr[out_agen].table_npt() = Vdata;
    }

    __vector v_qScale;
    v_qScale= qScale;

    for (int I1 = 0; I1 < ALIGN_SIMD(numMappedPixels)/VCOP_SIMD_WIDTH; I1++) {
        __vector temp1, temp2, xFrac, yFrac, qScale_xFrac, qScale_yFrac, pix00, pix10, pix01, pix11, fracMap, scatterStore;
        __agen Addr1, Addr2, Addr3, Addr_out;
        __vector Vmaskx;
        __vector Vshifty;

        Vmaskx = 0x000000000F;
        Vshifty = -4;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*pix01_ptr);
        Addr3 = I1*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray);
        Addr_out = 0;

        fracMap = fracArray[Addr1].npt();
        scatterStore = scatterStoreArray[Addr3].npt();

        (pix00, pix10)= pix00_ptr[Addr2].deinterleave();
        (pix01, pix11)= pix01_ptr[Addr2].deinterleave();

        xFrac = fracMap & Vmaskx;
        yFrac = fracMap << Vshifty;

        temp1= xFrac*pix10;
        temp2= xFrac*pix11;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*pix00;
        temp2+= qScale_xFrac*pix01;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        temp1= temp1 + temp2;

        dst[Addr_out].s_scatter(scatterStore)= temp1.round(mnQShift+oQShift).saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}

