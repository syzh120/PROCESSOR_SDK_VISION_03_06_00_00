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
/* Down sample the luma tlu indices to compute chroma tlu indices for YUV 422 format */
/* This kernel is used when Chroma is to Bilinear Interpolated */
void vcop_dsTLUindexAndFracBilInterpolate(
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        unsigned short      numEvenMappedPixels,
        unsigned short      numOddMappedPixels,
        __vptr_uint8        xFracArrayU,
        __vptr_uint8        yFracArrayU,
        __vptr_uint16       tluIndexArrayU,
        __vptr_uint8        xFracArrayV,
        __vptr_uint8        yFracArrayV,
        __vptr_uint16       tluIndexArrayV,
        unsigned char       QShift
)
{
    for (int I1 = 0; I1 < ALIGN_2SIMD(numEvenMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1,Addr2,Addr3,Addr4;
        __vector tluIndexU_1, tluIndexU_2, xFracU_1, yFracU_1, xFracU_2, yFracU_2, fracMapU_1, fracMapU_2, tluIndexUOffset_1, tluIndexUOffset_2;
        __vector Vmaskx, VmaskEven;
        __vector Vshifty, VQShift;

        VmaskEven = 0x0000000001;
        Vmaskx = 0x000000000F;
        Vshifty = -4;
        VQShift = QShift;

        Addr1= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayU);
        Addr3= I1*2*VCOP_SIMD_WIDTH*sizeof(*xFracArrayU);
        Addr4= I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);

        tluIndexU_1 = tluIndexArray[Addr1].npt();
        tluIndexU_2 = (tluIndexArray+VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr1].npt();
        fracMapU_1 = fracArray[Addr4].npt();
        fracMapU_2 = (fracArray+VCOP_SIMD_WIDTH*sizeof(*fracArray))[Addr4].npt();

        /* Extract fractionals */
        xFracU_1 = fracMapU_1 & Vmaskx;
        xFracU_2 = fracMapU_2 & Vmaskx;

        yFracU_1 = fracMapU_1 << Vshifty;
        yFracU_2 = fracMapU_2 << Vshifty;

        /* tluIndex = i + j*stride, if 'i' is odd, tluIndex will also be odd as stride is always even.    */
        /* tluIndex_chroma should be (i/2) + j*(stride/2). If 'i' is odd, to compensate for the loss of 1 */
        /* on dividing by 2, we calculate the below offset and add it to x_frac.                          */
        tluIndexUOffset_1 = tluIndexU_1 & VmaskEven;
        tluIndexUOffset_2 = tluIndexU_2 & VmaskEven;

        tluIndexUOffset_1 = tluIndexUOffset_1 << VQShift;
        tluIndexUOffset_2 = tluIndexUOffset_2 << VQShift;

        xFracU_1 = tluIndexUOffset_1 + xFracU_1;
        xFracU_2 = tluIndexUOffset_2 + xFracU_2;

        /* There are half the number of U pixels as compared to Y along the x direction. Hence the indexes */
        /* and fractionals must be divided by 2. */
        tluIndexArrayU[Addr2].npt()= tluIndexU_1.truncate(1);
        (tluIndexArrayU+VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayU))[Addr2].npt()= tluIndexU_2.truncate(1);
        xFracArrayU[Addr3].npt()= xFracU_1.truncate(1);
        (xFracArrayU+VCOP_SIMD_WIDTH*sizeof(*xFracArrayU))[Addr3].npt()= xFracU_2.truncate(1);
        yFracArrayU[Addr3].npt()= yFracU_1;
        (yFracArrayU+VCOP_SIMD_WIDTH*sizeof(*yFracArrayU))[Addr3].npt()= yFracU_2;
    }

   for (int I1 = 0; I1 < ALIGN_2SIMD(numOddMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1,Addr2,Addr3,Addr4;
        __vector tluIndexV_1, tluIndexV_2, xFracV_1, yFracV_1, xFracV_2, yFracV_2, fracMapV_1, fracMapV_2, tluIndexVOffset_1, tluIndexVOffset_2;
        __vector Vmaskx, VmaskEven;
        __vector Vshifty, VQShift, Vone, maxTluIndexV_1, maxTluIndexV_2;

        VmaskEven = 0x0000000001;
        Vmaskx = 0x000000000F;
        Vshifty = -4;
        VQShift = QShift;
        Vone = 1;

        Addr1= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayV);
        Addr3= I1*2*VCOP_SIMD_WIDTH*sizeof(*xFracArrayV);
        Addr4= I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);

        tluIndexV_1 = (tluIndexArray+2*numEvenMappedPixels)[Addr1].npt();
        tluIndexV_2 = (tluIndexArray+2*numEvenMappedPixels+VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr1].npt();
        fracMapV_1 = (fracArray+numEvenMappedPixels)[Addr4].npt();
        fracMapV_2 = (fracArray+numEvenMappedPixels+VCOP_SIMD_WIDTH*sizeof(*fracArray))[Addr4].npt();

        xFracV_1 = fracMapV_1 & Vmaskx;
        xFracV_2 = fracMapV_2 & Vmaskx;

        yFracV_1 = fracMapV_1 << Vshifty;
        yFracV_2 = fracMapV_2 << Vshifty;

        /* As explained for U, the offset is calculated. */
        tluIndexVOffset_1 = tluIndexV_1 & VmaskEven;
        tluIndexVOffset_2 = tluIndexV_2 & VmaskEven;

        tluIndexVOffset_1 = tluIndexVOffset_1 << VQShift;
        tluIndexVOffset_2 = tluIndexVOffset_2 << VQShift;

        xFracV_1 = tluIndexVOffset_1 + xFracV_1;
        xFracV_2 = tluIndexVOffset_2 + xFracV_2;

        tluIndexArrayV[Addr2].npt()= tluIndexV_1.truncate(1);
        (tluIndexArrayV+VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayV))[Addr2].npt()= tluIndexV_2.truncate(1);
        xFracArrayV[Addr3].npt()= xFracV_1.truncate(1);
        (xFracArrayV+VCOP_SIMD_WIDTH*sizeof(*xFracArrayV))[Addr3].npt()= xFracV_2.truncate(1);
        yFracArrayV[Addr3].npt()= yFracV_1;
        (yFracArrayV+VCOP_SIMD_WIDTH*sizeof(*yFracArrayV))[Addr3].npt()= yFracV_2;
    }
}

/* Down sample the luma tlu indices to compute chroma tlu indices for YUV 422 format */
/* This kernel is used when Chroma is to NN Interpolated */
void vcop_dsTLUindexAndFracNNInterpolate(
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        unsigned short      numEvenMappedPixels,
        unsigned short      numOddMappedPixels,
        __vptr_uint16       tluIndexArrayU,
        __vptr_uint16       tluIndexArrayV,
        unsigned char       stride,
        unsigned char       QShift
)
{

    __vector  Vstride, VQShift, Vshifty, VmaskEven;
    Vstride= stride;
    VQShift= QShift;
    VmaskEven = 0x0000000001;
    Vshifty = -4;

    for (int I1 = 0; I1 < ALIGN_2SIMD(numEvenMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2, Addr3;
        __vector tluIndexU_1, tluIndexU_2, tluIndexUOffset_1, tluIndexUOffset_2;
        __vector fracMapU_1, fracMapU_2, yFracU_1, yFracU_2, roundedYFracU_1, roundedYFracU_2;

        Addr1= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayU);
        Addr3= I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);

        tluIndexU_1 = tluIndexArray[Addr1].npt();
        tluIndexU_2 = (tluIndexArray+VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr1].npt();
        fracMapU_1 = fracArray[Addr3].npt();
        fracMapU_2 = (fracArray+VCOP_SIMD_WIDTH*sizeof(*fracArray))[Addr3].npt();

        tluIndexUOffset_1 = tluIndexU_1 & VmaskEven;
        tluIndexUOffset_2 = tluIndexU_2 & VmaskEven;

        tluIndexU_1 += tluIndexUOffset_1;
        tluIndexU_2 += tluIndexUOffset_2;

        yFracU_1 = fracMapU_1 << Vshifty;
        yFracU_2 = fracMapU_2 << Vshifty;

        roundedYFracU_1= round(yFracU_1, VQShift);
        roundedYFracU_2= round(yFracU_2, VQShift);

        tluIndexU_1 += roundedYFracU_1*Vstride;
        tluIndexU_2 += roundedYFracU_2*Vstride;

        tluIndexArrayU[Addr2].npt()= tluIndexU_1.truncate(1);
        (tluIndexArrayU+VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayU))[Addr2].npt()= tluIndexU_2.truncate(1);
    }

    for (int I1 = 0; I1 < ALIGN_2SIMD(numOddMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2, Addr3;
        __vector tluIndexV_1, tluIndexV_2, tluIndexVOffset_1, tluIndexVOffset_2;
        __vector fracMapV_1, fracMapV_2, yFracV_1, yFracV_2, roundedYFracV_1, roundedYFracV_2;

        Addr1= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayV);
        Addr3= I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);

        tluIndexV_1 = (tluIndexArray+2*numEvenMappedPixels)[Addr1].npt();
        tluIndexV_2 = (tluIndexArray+2*numEvenMappedPixels+VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr1].npt();
        fracMapV_1 = (fracArray+numEvenMappedPixels)[Addr3].npt();
        fracMapV_2 = (fracArray+numEvenMappedPixels+VCOP_SIMD_WIDTH*sizeof(*fracArray))[Addr3].npt();

        tluIndexVOffset_1 = tluIndexV_1 & VmaskEven;
        tluIndexVOffset_2 = tluIndexV_2 & VmaskEven;

        tluIndexV_1 += tluIndexVOffset_1;
        tluIndexV_2 += tluIndexVOffset_2;

        yFracV_1 = fracMapV_1 << Vshifty;
        yFracV_2 = fracMapV_2 << Vshifty;

        roundedYFracV_1= round(yFracV_1, VQShift);
        roundedYFracV_2= round(yFracV_2, VQShift);

        tluIndexV_1 += roundedYFracV_1*Vstride;
        tluIndexV_2 += roundedYFracV_2*Vstride;

        tluIndexArrayV[Addr2].npt()= tluIndexV_1.truncate(1);
        (tluIndexArrayV+VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayV))[Addr2].npt()= tluIndexV_2.truncate(1);
    }
}


/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Down sample the luma tlu indices to compute chroma tlu indices for YUV 422 format */
/* This kernel is used when Chroma is to Bilinear Interpolated */
void vcop_dsTLUindexAndFracBilInterpolateBB(
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint8        xFracArrayU,
        __vptr_uint8        yFracArrayU,
        __vptr_uint16       tluIndexArrayU,
        __vptr_uint8        xFracArrayV,
        __vptr_uint8        yFracArrayV,
        __vptr_uint16       tluIndexArrayV,
        unsigned char       QShift,
        unsigned short      outputBlockSize
)
{
    for (int I1 = 0; I1 < ALIGN_2SIMD(outputBlockSize)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1,Addr2,Addr3,Addr4;
        __vector tluIndexU, tluIndexV, xFracU, yFracU, xFracV, yFracV, fracMapU, fracMapV, tluIndexUOffset, tluIndexVOffset;
        __vector Vmaskx, VmaskEven;
        __vector Vshifty, VQShift, Vone, maxTluIndexV;

        VmaskEven = 0x0000000001;
        Vmaskx = 0x000000000F;
        Vshifty = -4;
        VQShift = QShift;
        Vone = 1;

        Addr1= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2= I1*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayU);
        Addr3= I1*VCOP_SIMD_WIDTH*sizeof(*xFracArrayU);
        Addr4= I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);

        (tluIndexU, tluIndexV) = tluIndexArray[Addr1].deinterleave();
        (fracMapU, fracMapV) = fracArray[Addr4].deinterleave();

        xFracU = fracMapU & Vmaskx;
        xFracV = fracMapV & Vmaskx;

        yFracU = fracMapU << Vshifty;
        yFracV = fracMapV << Vshifty;

        tluIndexUOffset = tluIndexU & VmaskEven;
        tluIndexVOffset = tluIndexV & VmaskEven;

        tluIndexUOffset = tluIndexUOffset << VQShift;
        tluIndexVOffset = tluIndexVOffset << VQShift;

        xFracU = tluIndexUOffset + xFracU;
        xFracV = tluIndexVOffset + xFracV;

        tluIndexArrayU[Addr2].npt()= tluIndexU.truncate(1);
        xFracArrayU[Addr3].npt()= xFracU.truncate(1);
        yFracArrayU[Addr3].npt()= yFracU;

        tluIndexArrayV[Addr2].npt()= tluIndexV.truncate(1);
        xFracArrayV[Addr3].npt()= xFracV.truncate(1);
        yFracArrayV[Addr3].npt()= yFracV;

    }
}

/* Down sample the luma tlu indices to compute chroma tlu indices for YUV 422 format */
/* This kernel is used when Chroma is to NN Interpolated */
void vcop_dsTLUindexAndFracNNInterpolateBB(
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       tluIndexArrayU,
        __vptr_uint16       tluIndexArrayV,
        __vptr_uint16       stride_ptr,
        unsigned char       QShift,
        unsigned short      outputBlockSize
)
{

    __vector  Vstride, VQShift, Vshifty, VmaskEven;
    __agen Addr0=0;
    Vstride= stride_ptr[Addr0].onept();
    VQShift= QShift;
    VmaskEven = 0x0000000001;
    Vshifty = -4;

    for (int I1 = 0; I1 < ALIGN_2SIMD(outputBlockSize)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2, Addr3;
        __vector tluIndexU, tluIndexV, tluIndexUOffset, tluIndexVOffset;
        __vector fracMapU, fracMapV, yFracU, yFracV, roundedYFracU, roundedYFracV;

        Addr1= I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2= I1*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayU);
        Addr3= I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);

        (tluIndexU, tluIndexV) = tluIndexArray[Addr1].deinterleave();
        (fracMapU, fracMapV) = fracArray[Addr3].deinterleave();

        tluIndexUOffset = tluIndexU & VmaskEven;
        tluIndexVOffset = tluIndexV & VmaskEven;

        tluIndexU += tluIndexUOffset;
        tluIndexV += tluIndexVOffset;

        yFracU = fracMapU << Vshifty;
        yFracV = fracMapV << Vshifty;

        roundedYFracU= round(yFracU, VQShift);
        roundedYFracV= round(yFracV, VQShift);

        tluIndexU += roundedYFracU*Vstride;
        tluIndexV += roundedYFracV*Vstride;

        tluIndexArrayU[Addr2].npt()= tluIndexU.truncate(1);
        tluIndexArrayV[Addr2].npt()= tluIndexV.truncate(1);
    }
}

