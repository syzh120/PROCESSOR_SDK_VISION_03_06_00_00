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
/* Compute the chroma tlu index on the fly using the tlu */
/* index of luma when Chroma is going to be bilinearly interpolated */
void vcop_chromaTLUIndexCalcBilInterpolate(
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scatterStoreArray,
        unsigned short      numMappedPixels,
        unsigned short      inputStride,
        unsigned short      inputStrideInverseQ16,
        unsigned short      outputStride,
        unsigned short      outputStrideInverseQ16,
        __vptr_uint16       tluIndexArrayUV,
        __vptr_uint8        xfracArrayUV,
        __vptr_uint8        yfracArrayUV,
        __vptr_uint16       scatterStoreArrayUV,
        unsigned char       QShift
)
{
    __vector Q16_stride, U16_stride, Vshift, VQShift, VmaskFirstBit, Vmaskx, Vshifty, U16_outputStride, Q16_outputStride;
    __vector LumaIndx, Lumafrac, LumaScatterStore, ChromaColIndex, xFrac, yFrac;
    __vector LumaLineIndex, LumaLineOffset, ChromaLineIndex;

    U16_stride = inputStride;
    Q16_stride = inputStrideInverseQ16;
    U16_outputStride = outputStride;
    Q16_outputStride = outputStrideInverseQ16;
    Vshift = -1;
    VmaskFirstBit = 0x0000000001;
    Vmaskx = 0x000000000F;
    Vshifty = -4;
    VQShift = QShift;

    //LumaLineIndex    = Q16_stride*LumaIndx >> 16;
    //ChromaLineIndex = LumaLineindex >> 1;
    //LumaColIndex     = LumaIndx - LumaLineindex * U16_stride;
    //ChromaIndex      = ChromaLineIndex*U16_stride + LumaColIndex;
    for (int I1 = 0; I1 < ALIGN_SIMD(numMappedPixels)/(VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr1, Addr2, Addr3, Addr4;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2 = I1*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr3 = I1*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayUV);
        Addr4 = I1*VCOP_SIMD_WIDTH*sizeof(*xfracArrayUV);

        //Load the packed format luma index
        LumaIndx = tluIndexArray[Addr1].npt();

        //Load the packed format luma frac
        Lumafrac = fracArray[Addr2].npt();

        //Load the packed format Scatter Store offsets
        LumaScatterStore = scatterStoreArray[Addr1].npt();

        // Extract x and y frac
        xFrac = Lumafrac & Vmaskx;
        yFrac = Lumafrac << Vshifty;

        //Compute luma line index by dividing the luma index with block stride in Q16 format
        LumaLineIndex = (Q16_stride*LumaIndx).truncate(0x10);

        //Compute the luma line offset by scaling the luma line index with block stride
        LumaLineOffset = U16_stride*LumaLineIndex;

        //Compute the chroma line index i.e., half of luma line index since it is YUV 420 SP
        ChromaLineIndex = LumaLineIndex << Vshift;

        //Compute the column index which is same for both luma or chroma components
        ChromaColIndex = LumaIndx - LumaLineOffset;

        // x-Frac Calculation
        Lumafrac = ChromaColIndex & VmaskFirstBit;
        Lumafrac = Lumafrac << VQShift;
        xFrac = Lumafrac + xFrac;

        //Add the chroma line index to the chroma column index to obtain chroma index
        ChromaColIndex += ChromaLineIndex*U16_stride;

        //Ensure that the chroma index for UV component is even
        ChromaColIndex &= ~VmaskFirstBit;

        // y-Frac Calculation
        Lumafrac = LumaLineIndex & VmaskFirstBit;
        Lumafrac = Lumafrac << VQShift;
        yFrac = Lumafrac + yFrac;

        //Compute Output luma line index by dividing the luma index with block stride in Q16 format
        LumaLineIndex = (Q16_outputStride*LumaScatterStore).truncate(0x10);

        //Compute the output luma line offset by scaling the luma line index with block stride
        LumaLineOffset = U16_outputStride*LumaLineIndex;

        //Compute the chroma line index i.e., half of luma line index since it is YUV 420 SP
        ChromaLineIndex = LumaLineIndex << Vshift;

        //Compute the column index which is same for both luma or chroma components
        LumaScatterStore = LumaScatterStore - LumaLineOffset;

        //Add the chroma line index to the chroma column index to obtain chroma index
        LumaScatterStore += ChromaLineIndex*U16_outputStride;

        tluIndexArrayUV[Addr3]     = ChromaColIndex;
        scatterStoreArrayUV[Addr3] = LumaScatterStore;
        xfracArrayUV[Addr4] = xFrac.truncate(1);
        yfracArrayUV[Addr4] = yFrac.truncate(1);
    }
}


/* Compute the chroma tlu index on the fly using the tlu */
/* index of luma when Chroma is going to be NN interpolated */
void vcop_chromaTLUIndexCalcNNInterpolate(
        __vptr_uint16       tluIndexArray,
        __vptr_uint16       scatterStoreArray,
        unsigned short      numMappedPixels,
        unsigned short      inputStride,
        unsigned short      inputStrideInverseQ16,
        unsigned short      outputStride,
        unsigned short      outputStrideInverseQ16,
        __vptr_uint16       tluIndexArrayUV,
        __vptr_uint16       scatterStoreArrayUV
)
{
    __vector Q16_stride, U16_stride, Vshift, VmaskFirstBit;
    __vector LumaIndx1, LumaIndx2, LumaLineIndex_1, LumaLineIndex_2;
    __vector LumaLineOffset1, LumaLineOffset2, ChromaLineIndex_1, ChromaLineIndex_2, ChromaIndex_1, ChromaIndex_2;
    __vector yFracOffset1, yFracOffset2, xFracOffset1, xFracOffset2;
    __vector LumaScatterStore1, LumaScatterStore2, opLumaLineIndex1, opLumaLineIndex2, opLumaLineOffset1, opLumaLineOffset2;
    __vector U16_outputStride, Q16_outputStride, opChromaLineIndex1, opChromaLineIndex2, opChromaColIndex1, opChromaColIndex2;

    U16_stride = inputStride;
    Q16_stride = inputStrideInverseQ16;
    U16_outputStride = outputStride;
    Q16_outputStride = outputStrideInverseQ16;
    Vshift = -1;
    VmaskFirstBit = 0x0000000001;

    //LumaLineIndex    = Q16_stride*LumaIndx >> 16;
    //ChromaLineIndex = LumaLineindex >> 1;
    //LumaColIndex     = LumaIndx - LumaLineindex * U16_stride;
    //ChromaIndex      = ChromaLineIndex*U16_stride + LumaColIndex;
    for (int I1 = 0; I1 < ALIGN_2SIMD(numMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr1, Addr2, Addr3, Addr4;

        Addr1 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray);
        Addr3 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayUV);
        Addr4 = I1*2*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArrayUV);

        //Load the packed format luma index
        LumaIndx1 = tluIndexArray[Addr1].npt();
        LumaIndx2 = (tluIndexArray + VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr1].npt();

        LumaScatterStore1 = scatterStoreArray[Addr2].npt();
        LumaScatterStore2 = (scatterStoreArray + VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray))[Addr2].npt();

        //Compute luma line index by dividing the luma index with block stride in Q16 format
        LumaLineIndex_1 = (Q16_stride*LumaIndx1).truncate(0x10); //Q16_stride*LumaIndx
        LumaLineIndex_2 = (Q16_stride*LumaIndx2).truncate(0x10); //Q16_stride*LumaIndx

        //Compute the luma line offset by scaling the luma line index with block stride
        LumaLineOffset1= U16_stride*LumaLineIndex_1;
        LumaLineOffset2= U16_stride*LumaLineIndex_2;

        // If LumaLineIndex is odd, Offset of 1 should be considered when ChromaLineIndex = LumaLineIndex/2
        yFracOffset1 = LumaLineIndex_1 & VmaskFirstBit;
        yFracOffset2 = LumaLineIndex_2 & VmaskFirstBit;

        //Compute the chroma line index i.e., half of luma line index since it is YUV 420 SP
        ChromaLineIndex_1 = LumaLineIndex_1 << Vshift;
        ChromaLineIndex_2 = LumaLineIndex_2 << Vshift;

        // If LumaLineIndex is odd, increment ChromaLineIndex by 1
        ChromaLineIndex_1 += yFracOffset1;
        ChromaLineIndex_2 += yFracOffset2;

        //Compute the column index which is same for both luma or chroma components
        ChromaIndex_1 = LumaIndx1 - LumaLineOffset1;
        ChromaIndex_2 = LumaIndx2 - LumaLineOffset2;

        // Check if Luma Column Index is odd or even
        xFracOffset1 = ChromaIndex_1 & VmaskFirstBit;
        xFracOffset2 = ChromaIndex_2 & VmaskFirstBit;

        // If Luma Column Index is odd, make it next even number
        ChromaIndex_1 += xFracOffset1;
        ChromaIndex_2 += xFracOffset2;

        //Add the chroma line index to the chroma column index to obtain chroma index. Since U16_stride is even, ChromaIndex will be even.
        ChromaIndex_1 += ChromaLineIndex_1*U16_stride;
        ChromaIndex_2 += ChromaLineIndex_2*U16_stride;

        //Compute Output luma line index by dividing the luma index with block stride in Q16 format
        opLumaLineIndex1 = (Q16_outputStride*LumaScatterStore1).truncate(0x10);
        opLumaLineIndex2 = (Q16_outputStride*LumaScatterStore2).truncate(0x10);

        //Compute the output luma line offset by scaling the luma line index with block stride
        opLumaLineOffset1 = U16_outputStride*opLumaLineIndex1;
        opLumaLineOffset2 = U16_outputStride*opLumaLineIndex2;

        //Compute the chroma line index i.e., half of luma line index since it is YUV 420 SP
        opChromaLineIndex1 = opLumaLineIndex1 << Vshift;
        opChromaLineIndex2 = opLumaLineIndex2 << Vshift;

        //Compute the column index which is same for both luma or chroma components
        opChromaColIndex1 = LumaScatterStore1 - opLumaLineOffset1;
        opChromaColIndex2 = LumaScatterStore2 - opLumaLineOffset2;

        //Add the chroma line index to the chroma column index to obtain chroma index
        opChromaColIndex1 += opChromaLineIndex1*U16_outputStride;
        opChromaColIndex2 += opChromaLineIndex2*U16_outputStride;

        tluIndexArrayUV[Addr3] = ChromaIndex_1;
        (tluIndexArrayUV + VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr3] = ChromaIndex_2;
        scatterStoreArrayUV[Addr4] = opChromaColIndex1;
        (scatterStoreArrayUV + VCOP_SIMD_WIDTH*sizeof(*scatterStoreArrayUV))[Addr4] = opChromaColIndex2;
    }
}


/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the chroma tlu index on the fly using the tlu */
/* index of luma when Chroma is going to be bilinearly interpolated */
void vcop_chromaTLUIndexCalcBilInterpolateBB(
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       stride_ptr,
        __vptr_uint16       stride_inverse_q16_ptr,
        __vptr_uint16       tluIndexArrayUV,
        __vptr_uint8        xfracArrayUV,
        __vptr_uint8        yfracArrayUV,
        unsigned char       QShift,
        unsigned short      outputBlockWidth,
        unsigned short      outputBlockHeight
)
{
    __agen Addr0;
    __vector Q16_stride, U16_stride, Vshift, VQShift, Vq16shift, VmaskEven, VmaskFirstBit, Vmaskx, Vshifty;
    __vector LumaIndx, LumaLineIndex;
    __vector LumaLineOffset, ChromaLineIndex, ChromaColIndex, ChromaIndex;
    __vector Lumafrac, xFrac, yFrac, xFracOffset, yFracOffset;
    Addr0 = 0;
    U16_stride = stride_ptr[Addr0].onept();
    Q16_stride = (stride_ptr + 4)[Addr0].onept();
    VmaskEven = 0xFFFFFFFFFE;
    Vshift = -1;
    Vq16shift = -16;
    VmaskFirstBit = 0x0000000001;
    Vmaskx = 0x000000000F;
    Vshifty = -4;
    VQShift = QShift;

    //LumaLineIndex    = Q16_stride*LumaIndx >> 16;
    //ChromaLineIndex = LumaLineindex >> 1;
    //LumaColIndex     = LumaIndx - LumaLineindex * U16_stride;
    //ChromaIndex      = ChromaLineIndex*U16_stride + LumaColIndex;
    for (int I2 = 0; I2 < outputBlockHeight; I2++)
    {
        for (int I1 = 0; I1 < ALIGN_2SIMD(outputBlockWidth)/(2*VCOP_SIMD_WIDTH); I1++)
        {
            __agen Addr3, Addr4, Addr5, Addr6;

            Addr3 = I2*2*outputBlockWidth*sizeof(*tluIndexArray)+I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
            Addr4 = I2*2*outputBlockWidth*sizeof(*fracArray)+I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);
            Addr5 = I2*((outputBlockWidth+1)/2)*sizeof(*tluIndexArrayUV)+I1*VCOP_SIMD_WIDTH*sizeof(*tluIndexArrayUV);
            Addr6 = I2*((outputBlockWidth+1)/2)*sizeof(*xfracArrayUV)+I1*VCOP_SIMD_WIDTH*sizeof(*xfracArrayUV);

            //Load the packed format luma index
            LumaIndx = tluIndexArray[Addr3].ds2();

            //Load the packed format luma frac
            Lumafrac = fracArray[Addr4].ds2();

            // Extract x and y frac
            xFrac = Lumafrac & Vmaskx;
            yFrac = Lumafrac << Vshifty;

            //Compute luma line index by dividing the luma index with block stride in Q16 format
            LumaLineIndex = (Q16_stride*LumaIndx).truncate(0x10);

            //Compute the luma line offset by scaling the luma line index with block stride
            LumaLineOffset = U16_stride*LumaLineIndex;

            //Compute the chroma line index i.e., half of luma line index since it is YUV 420 SP
            ChromaLineIndex = LumaLineIndex << Vshift;

            //Compute the column index which is same for both luma or chroma components
            ChromaColIndex = LumaIndx - LumaLineOffset;

            // x-Frac Calculation
            xFracOffset = ChromaColIndex & VmaskFirstBit;
            xFracOffset = xFracOffset << VQShift;
            xFrac = xFracOffset + xFrac;

            //Add the chroma line index to the chroma column index to obtain chroma index
            ChromaColIndex += ChromaLineIndex*U16_stride;

            //Ensure that the chroma index for UV component is even
            ChromaIndex = ChromaColIndex & VmaskEven;

            // y-Frac Calculation
            yFracOffset = LumaLineIndex & VmaskFirstBit;
            yFracOffset = yFracOffset << VQShift;
            yFrac = yFracOffset + yFrac;

            tluIndexArrayUV[Addr5] = ChromaIndex;
            xfracArrayUV[Addr6] = xFrac.truncate(1);
            yfracArrayUV[Addr6] = yFrac.truncate(1);
        }
    }
}

/* Compute the chroma tlu index on the fly using the tlu */
/* index of luma when Chroma is going to be NN interpolated */
void vcop_chromaTLUIndexCalcNNInterpolateBB(
        __vptr_uint16       tluIndexArray,
        __vptr_uint16       stride_ptr,
        __vptr_uint16       stride_inverse_q16_ptr,
        __vptr_uint16       tluIndexArrayUV,
        unsigned short      outputBlockWidth,
        unsigned short      outputBlockHeight
)
{
    __agen Addr0;
    __vector Q16_stride, U16_stride, Vshift, VmaskFirstBit;
    __vector LumaIndx1, LumaIndx2, LumaLineIndex_1, LumaLineIndex_2;
    __vector LumaLineOffset1, LumaLineOffset2, ChromaLineIndex_1, ChromaLineIndex_2, ChromaIndex_1, ChromaIndex_2;
    __vector yFracOffset1, yFracOffset2, xFracOffset1, xFracOffset2;
    Addr0 = 0;
    U16_stride = stride_ptr[Addr0].onept();
    Q16_stride = (stride_ptr + 4)[Addr0].onept();
    Vshift = -1;
    VmaskFirstBit = 0x0000000001;

    //LumaLineIndex    = Q16_stride*LumaIndx >> 16;
    //ChromaLineIndex = LumaLineindex >> 1;
    //LumaColIndex     = LumaIndx - LumaLineindex * U16_stride;
    //ChromaIndex      = ChromaLineIndex*U16_stride + LumaColIndex;
    for (int I2 = 0; I2 < outputBlockHeight; I2++)
    {
        for (int I1 = 0; I1 < ALIGN_4SIMD(outputBlockWidth)/(4*VCOP_SIMD_WIDTH); I1++)
        {
            __agen Addr3, Addr4, Addr5;

            Addr3 = I2*2*outputBlockWidth*sizeof(*tluIndexArray)+I1*4*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);
            Addr5 = I2*((outputBlockWidth+1)/2)*sizeof(*tluIndexArray)+I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);

            //Load the packed format luma index
            LumaIndx1 = tluIndexArray[Addr3].ds2();
            LumaIndx2 = (tluIndexArray + 2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr3].ds2();

            //Compute luma line index by dividing the luma index with block stride in Q16 format
            LumaLineIndex_1 = (Q16_stride*LumaIndx1).truncate(0x10); //Q16_stride*LumaIndx
            LumaLineIndex_2 = (Q16_stride*LumaIndx2).truncate(0x10); //Q16_stride*LumaIndx

            //Compute the luma line offset by scaling the luma line index with block stride
            LumaLineOffset1= U16_stride*LumaLineIndex_1;
            LumaLineOffset2= U16_stride*LumaLineIndex_2;

            // If LumaLineIndex is odd, Offset of 1 should be considered when ChromaLineIndex = LumaLineIndex/2
            yFracOffset1 = LumaLineIndex_1 & VmaskFirstBit;
            yFracOffset2 = LumaLineIndex_2 & VmaskFirstBit;

            //Compute the chroma line index i.e., half of luma line index since it is YUV 420 SP
            ChromaLineIndex_1 = LumaLineIndex_1 << Vshift;
            ChromaLineIndex_2 = LumaLineIndex_2 << Vshift;

            // If LumaLineIndex is odd, increment ChromaLineIndex by 1
            ChromaLineIndex_1 += yFracOffset1;
            ChromaLineIndex_2 += yFracOffset2;

            //Compute the column index which is same for both luma or chroma components
            ChromaIndex_1 = LumaIndx1 - LumaLineOffset1;
            ChromaIndex_2 = LumaIndx2 - LumaLineOffset2;

            // Check if Luma Column Index is odd or even
            xFracOffset1 = ChromaIndex_1 & VmaskFirstBit;
            xFracOffset2 = ChromaIndex_2 & VmaskFirstBit;

            // If Luma Column Index is odd, make it next even number
            ChromaIndex_1 += xFracOffset1;
            ChromaIndex_2 += xFracOffset2;

            //Add the chroma line index to the chroma column index to obtain chroma index. Since U16_stride is even, ChromaIndex will be even.
            ChromaIndex_1 += ChromaLineIndex_1*U16_stride;
            ChromaIndex_2 += ChromaLineIndex_2*U16_stride;

            tluIndexArrayUV[Addr5] = ChromaIndex_1;
            (tluIndexArrayUV + VCOP_SIMD_WIDTH*sizeof(*tluIndexArray))[Addr5] = ChromaIndex_2;
        }
    }
}
