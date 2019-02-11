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

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

#define VCOP_2SIMD_WIDTH (2*VCOP_SIMD_WIDTH)

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define INPUT_ELEMSZ 1
#define TEMPLATE_ELEMSZ sizeof(*pTempImg)
#define SCRATCH_ELEMSZ sizeof(*pScratch)
#define SUM_ELEMSZ sizeof(*pSum)
#define OUT_ELEMSZ sizeof(*pOutNumCC)

#define invTemplateSize ((1<<sizeQshift) + ((tempImgWidth*tempImgHeight)/2)) / (tempImgWidth*tempImgHeight)
#define outputWidth     (orgImgWidth  - tempImgWidth  + 1)
#define outputHeight    (orgImgHeight - tempImgHeight + 1)
#define qShiftDiff       (sizeQshift - qShift)
#define qValDiffHalf     (1<<(qShiftDiff -1 ))

#define inputWidth (computeWidth + windowWidth - 1)
#define inputHeight (computeHeight + windowHeight - 1)

/*
 * Performance estimates:
 *  (ALIGN(inputWidth)*windowHeight)*2/16 + (ALIGN(inputWidth)*(computeHeight-1))*2/16 + (ALIGN(computeHeight)*windowWidth)*2/16 cycles + (ALIGN(computeHeight)*(computeWidth-1))*2/16
 *
 */
void vcop_slidingSum(
        __vptr_uint8 pInput, /* Pointer to the input image block. Each element of the block should be in unsigned 8-bits format. */
        unsigned short inputStride, /* stride of the input block, in number of elements. Must be greater or equal than computeWidth + windWidth – 1 */
        unsigned short windowWidth, /* width of the sliding window, that defines the neighborhood in which the summation is performed. */
        unsigned short windowHeight, /* height of the sliding window, that defines the neighborhood in which the summation is performed */
        unsigned short computeWidth, /* number of sum values produced in each output row. Must be multiple of 16. */
        unsigned short computeHeight, /* number of rows produced */
        __vptr_int32   pScratch, /* Pointer to 4 bytes aligned scratch memory of size ((4*computeHeight + 31) & (~31)) + 4) * (computeWidth + windowWidth – 1) bytes. */
        unsigned short scratchStride, /* initialized by init_slidingSum_params() which should set it to ((4*computeHeight + 31) & (~31)) + 4 bytes. */
        __vptr_uint32  pSum, /* points to the output block of 32-bits elements. In total computeWidth x computeHeight values are produced. */
        unsigned short sumStride, /* initialized by init_slidingSum_params() which should set it to ((4*computeWidth + 31) & (~31)) + 4 bytes. */
        __vptr_uint16 pOffset, /* pointer to an array of 32 bytes, initialized by init_slidingSum_params(). Preferably in WBUF. */
        __vptr_int32 pScratchLine /* Pointer to 4 bytes aligned scratch memory of size MAX(ALIGN_SIMD2(computeWidth + windowWidth - 1), ALIGN_SIMD2(computeHeight)) bytes */
){

    __vector  vOfst;

    __agen AddrOffset= 0;
    vOfst= pOffset[AddrOffset].npt();

    /* Compute sliding vertical sum */
    /* Compute the first row. Each element of the first row is the vertical sum of each column of input image up. We add up to windowHeight elements per column */
    /* Performance estimates: (ALIGN(inputWidth)*windowHeight)*2/16 cycles */
    for (int u=0; u < ALIGN_SIMD2(inputWidth)/VCOP_2SIMD_WIDTH; u++) {
        __vector vInput0, vInput1, vScratch0, vScratch1;
        __agen scratchAddr= u*VCOP_2SIMD_WIDTH*scratchStride;
        __agen scratchLineAddr= u*VCOP_2SIMD_WIDTH*SCRATCH_ELEMSZ;

        vScratch0 =0;
        vScratch1= 0;
        for (int v=0; v < windowHeight; v++) {
            __agen orgImgAddr= v*INPUT_ELEMSZ*inputStride + u*INPUT_ELEMSZ*VCOP_2SIMD_WIDTH;

            vInput0= pInput[orgImgAddr].npt();
            vInput1= (pInput + VCOP_SIMD_WIDTH*INPUT_ELEMSZ)[orgImgAddr].npt();

            vScratch0= vScratch0 + vInput0;
            vScratch1= vScratch1 + vInput1;
        }
        pScratch[scratchAddr].p_scatter(vOfst)= vScratch0;
        (pScratch + VCOP_SIMD_WIDTH*scratchStride)[scratchAddr].p_scatter(vOfst)= vScratch1;
        pScratchLine[scratchLineAddr].npt()= vScratch0;
        (pScratchLine +  VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ)[scratchLineAddr].npt()= vScratch1;
    }

    /* Compute remaining rows. For row 'v', each element is calculated by taking the previous row (v-1) value and subtracting the value in the input image corresponding to row (v-1) and adding the value of (v + windowHeight - 1)
     * We also use transpose store.
     * */
    /* Performance estimates: (ALIGN(inputWidth)*(computeHeight-1))*2/16 cycles */
    for (int u=0; u < ALIGN_SIMD2(inputWidth)/VCOP_2SIMD_WIDTH; u++) {
        __vector vScratch0, vScratch1;
        __agen scratchLineAddr= u*VCOP_2SIMD_WIDTH*SCRATCH_ELEMSZ;

        vScratch0= pScratchLine[scratchLineAddr].npt();
        vScratch1= (pScratchLine +  VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ)[scratchLineAddr].npt();

        for (int v=0; v < (computeHeight-1); v++) {
            __vector vNewInput0, vNewInput1, vOldInput0, vOldInput1;

            __agen orgImgAddr= v*INPUT_ELEMSZ*inputStride + u*INPUT_ELEMSZ*VCOP_2SIMD_WIDTH;
            __agen scratchWrAddr= v*SCRATCH_ELEMSZ + u*VCOP_2SIMD_WIDTH*scratchStride;

            vNewInput0= (pInput + INPUT_ELEMSZ*windowHeight*inputStride)[orgImgAddr].npt();
            vNewInput1= (pInput + VCOP_SIMD_WIDTH*INPUT_ELEMSZ + INPUT_ELEMSZ*windowHeight*inputStride)[orgImgAddr].npt();
            vOldInput0= pInput[orgImgAddr].npt();
            vOldInput1= (pInput + VCOP_SIMD_WIDTH*INPUT_ELEMSZ)[orgImgAddr].npt();

            /* scratch[u + v*inputWidth]= pInput[u + (v + windowHeight - 1)*inputWidth] + scratch[u + (v-1)*inputWidth] - pInput[u + (v-1)*inputWidth]; */
            vScratch0+= (vNewInput0 - vOldInput0);
            vScratch1+= (vNewInput1 - vOldInput1);

            (pScratch + SCRATCH_ELEMSZ)[scratchWrAddr].p_scatter(vOfst)= vScratch0;
            (pScratch + SCRATCH_ELEMSZ + VCOP_SIMD_WIDTH*scratchStride)[scratchWrAddr].p_scatter(vOfst)= vScratch1;

        }
    }

    /* Compute sliding horizontal sum. Since input is transposed, this is exactly the same as computing sliding vertical sum */

    /* Compute sliding vertical sum */
    /* Compute the first row. Each element of the first row is the vertical sum of each column of input image up. We add up to windowHeight elements per column */
    /* Performance estimates: (ALIGN(outputHeight)*windowWidth)*2/16 cycles */
    /*
    for (v=0; v < computeHeight; v++) {
        sum[v*computeWidth]= 0;
    }
    for (u=0; u < windowWidth; u++) {
        for (v=0; v < computeHeight; v++) {
            sum[v*computeWidth]+= scratch[u*computeHeight + v];
        }
    }
     */
    vOfst= (pOffset + 16)[AddrOffset].npt();

    for (int v=0; v < ALIGN_SIMD2(computeHeight)/VCOP_2SIMD_WIDTH; v++) {
        __vector vScratch0, vScratch1, vSum0, vSum1;
        __agen sumAddr= v*VCOP_2SIMD_WIDTH*sumStride;
        __agen scratchLineAddr= v*VCOP_2SIMD_WIDTH*SCRATCH_ELEMSZ;

        vSum0 =0;
        vSum1= 0;
        for (int u=0; u < windowWidth; u++) {
            __agen scratchAddr= u*scratchStride + v*SCRATCH_ELEMSZ*VCOP_2SIMD_WIDTH;

            vScratch0= pScratch[scratchAddr].npt();
            vScratch1= (pScratch + VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ)[scratchAddr].npt();

            vSum0= vSum0 + vScratch0;
            vSum1= vSum1 + vScratch1;
        }
        pSum[sumAddr].p_scatter(vOfst)= vSum0;
        (pSum + VCOP_SIMD_WIDTH*sumStride)[sumAddr].p_scatter(vOfst)= vSum1;
        pScratchLine[scratchLineAddr].npt()= vSum0;
        (pScratchLine +  VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ)[scratchLineAddr].npt()= vSum1;
    }

    /* Compute remaining rows. For row 'v', each element is calculated by taking the previous row (v-1) value and subtracting the value in the input image corresponding to row (v-1) and adding the value of (v + windowHeight - 1)
     * We also use transpose store.
     *
     * */
    /* Performance estimates: (ALIGN(computeHeight)*(computeWidth-1))*2/16 cycles */
    for (int v=0; v < ALIGN_SIMD2(computeHeight)/VCOP_2SIMD_WIDTH; v++) {
        __vector vSum0, vSum1;
        __agen scratchLineAddr= v*VCOP_2SIMD_WIDTH*SCRATCH_ELEMSZ;

        vSum0= pScratchLine[scratchLineAddr].npt();
        vSum1= (pScratchLine +  VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ)[scratchLineAddr].npt();

        for (int u=0; u < (computeWidth-1); u++) {
            __vector vNewInput0, vNewInput1, vOldInput0, vOldInput1;

            __agen scratchAddr= u*scratchStride + v*SCRATCH_ELEMSZ*VCOP_2SIMD_WIDTH;
            __agen sumWrAddr= u*SUM_ELEMSZ + v*VCOP_2SIMD_WIDTH*sumStride;

            vNewInput0= (pScratch + scratchStride*windowWidth)[scratchAddr].npt();
            vNewInput1= (pScratch + VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ + scratchStride*windowWidth)[scratchAddr].npt();
            vOldInput0= pScratch[scratchAddr].npt();
            vOldInput1= (pScratch + VCOP_SIMD_WIDTH*SCRATCH_ELEMSZ)[scratchAddr].npt();

            /* scratch[u + v*inputWidth]= pInput[u + (v + windowHeight - 1)*inputWidth] + scratch[u + (v-1)*inputWidth] - pInput[u + (v-1)*inputWidth]; */
            vSum0+= (vNewInput0 - vOldInput0);
            vSum1+= (vNewInput1 - vOldInput1);

            (pSum + SUM_ELEMSZ)[sumWrAddr].p_scatter(vOfst)= vSum0;
            (pSum + SUM_ELEMSZ + VCOP_SIMD_WIDTH*sumStride)[sumWrAddr].p_scatter(vOfst)= vSum1;

        }
    }
}

/*
 * Performance estimates:
 *  (4/16 + 0.5*tempImgWidth*tempImgHeight)*ALIGN(output_width)*output_height
 *
 */
void vcop_ncc(
        __vptr_uint8 pOrgImg,
        unsigned short orgImgWidth,
        unsigned short orgImgHeight,
        unsigned short orgImgPitch,        /*original input image pitch*/
        __vptr_int16   pTempImg,           /*template image pointer*/
        unsigned short tempImgWidth,       /*template image width*/
        unsigned short tempImgHeight,      /*template image height*/
        unsigned short tempImgPitch,       /*template image pitch*/
        __vptr_uint32   pSum,
        __vptr_uint16   pSumL,
        __vptr_uint16   pSumH,
        unsigned short sumStride,
        unsigned char  sizeQshift,
        unsigned char  qShift,
        __vptr_int32   pOutNumCC,          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        __vptr_uint32  pOutDenomVar,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        unsigned short outPitch           /*Out Score buffer pitch*/
){

    /*
    for (v=0; v < outputHeight; v++) {
        for (u=0; u < outputWidth; u++) {
            sum[u + v*outputWidth]= sum[u + v*outputWidth]*invTemplateSize;
        }
    }
     */
    /* Performance estimates: 6/16 cycles */
    __vector vInvTemplateSize, v_16;
    vInvTemplateSize= invTemplateSize;
    v_16= 16;

    for (int v=0; v < outputHeight; v++) {
        for (int u=0; u < ALIGN_SIMD2(outputWidth)/VCOP_2SIMD_WIDTH; u++) {
            __vector vInput0, vInput1, vInput0_l, vInput1_l, vInput0_h, vInput1_h;
            __agen sumWrAddr= v*sumStride + u*VCOP_2SIMD_WIDTH*SUM_ELEMSZ;

            vInput0_h= pSumH[sumWrAddr].ds2();
            vInput0_l= pSumL[sumWrAddr].ds2();

            vInput1_h= (pSumH + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].ds2();
            vInput1_l= (pSumL + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].ds2();

            vInput0_h= vInput0_h*vInvTemplateSize;
            vInput1_h= vInput1_h*vInvTemplateSize;

            vInput0_l= vInput0_l*vInvTemplateSize;
            vInput1_l= vInput1_l*vInvTemplateSize;

            vInput0_h=  vInput0_h<<v_16;
            vInput1_h=  vInput1_h<<v_16;

            vInput0= vInput0_h + vInput0_l;
            vInput1= vInput1_h + vInput1_l;

            pSum[sumWrAddr].npt()= vInput0.round(qShiftDiff);
            (pSum + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].npt()= vInput1.round(qShiftDiff);

        }
    }

    __vector vqShift;

    vqShift= qShift;

    /*
     * Performance estimates:
     *  tempImgWidth*tempImgHeight*8/16= 0.5*tempImgWidth*tempImgHeight cyc/pixel
     */
    for (int v=0; v < outputHeight; v++) {
        for (int u=0; u < ALIGN_SIMD2(outputWidth)/VCOP_2SIMD_WIDTH; u++) {
            __vector vNumCC0, vNumCC1, vDenomVar0, vDenomVar1, vFavg0, vFavg1;
            __agen sumAddr= v*sumStride + u*VCOP_2SIMD_WIDTH*SUM_ELEMSZ;
            __agen outAddr= v*outPitch*OUT_ELEMSZ + u*VCOP_2SIMD_WIDTH*OUT_ELEMSZ;
            vNumCC0= 0;
            vNumCC1= 0;
            vDenomVar0= 0;
            vDenomVar1= 0;

            vFavg0= pSum[sumAddr].npt();
            vFavg1= (pSum + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumAddr].npt();

            for (int y=0; y < tempImgHeight; y++) {
                for (int x=0; x < tempImgWidth; x++) {
                    __vector vInput0, vInput1, vTemplate, vTemp10, vTemp11, vTemp20, vTemp21;
                    __agen orgImgAddr= x*INPUT_ELEMSZ + y*INPUT_ELEMSZ*orgImgPitch + u*VCOP_2SIMD_WIDTH*INPUT_ELEMSZ + v*INPUT_ELEMSZ*orgImgPitch;
                    __agen tempImgAddr=x*TEMPLATE_ELEMSZ + y*TEMPLATE_ELEMSZ*tempImgPitch;

                    vInput0= pOrgImg[orgImgAddr].npt();
                    vInput1= (pOrgImg + VCOP_SIMD_WIDTH*INPUT_ELEMSZ)[orgImgAddr].npt();
                    vTemplate= pTempImg[tempImgAddr].onept();

                    vInput0= vInput0 << vqShift;
                    vInput1= vInput1 << vqShift;
                    vInput0= vInput0 - vFavg0;
                    vInput1= vInput1 - vFavg1;

                    vTemp10= vInput0*vTemplate;
                    vTemp11= vInput1*vTemplate;
                    vTemp20= vInput0*vInput0;
                    vTemp21= vInput1*vInput1;

                    vTemp10= round(vTemp10, vqShift);
                    vTemp11= round(vTemp11, vqShift);
                    vTemp20= round(vTemp20, vqShift);
                    vTemp21= round(vTemp21, vqShift);

                    vNumCC0+= vTemp10;
                    vNumCC1+= vTemp11;
                    vDenomVar0+= vTemp20;
                    vDenomVar1+= vTemp21;

                }
            }

            pOutNumCC[outAddr].npt()= vNumCC0;
            (pOutNumCC + VCOP_SIMD_WIDTH*OUT_ELEMSZ)[outAddr].npt()= vNumCC1;
            pOutDenomVar[outAddr].npt()= vDenomVar0;
            (pOutDenomVar + VCOP_SIMD_WIDTH*OUT_ELEMSZ)[outAddr].npt()= vDenomVar1;
        }
    }

}

/*
 * Performance estimates:
 *   (4/16 + 0.25*tempImgWidth*tempImgHeight)*ALIGN(output_width)*output_height
 *
 */
void vcop_ncc_qShift8(
        __vptr_uint8 pOrgImg,
        unsigned short orgImgWidth,
        unsigned short orgImgHeight,
        unsigned short orgImgPitch,        /*original input image pitch*/
        __vptr_int16   pTempImg,           /*template image pointer*/
        unsigned short tempImgWidth,       /*template image width*/
        unsigned short tempImgHeight,      /*template image height*/
        unsigned short tempImgPitch,       /*template image pitch*/
        __vptr_uint32  pSum,
        __vptr_uint16  pSumL,
        __vptr_uint16  pSumH,
        unsigned short sumStride,
        unsigned char  sizeQshift,
        unsigned char  qShift,
        __vptr_int32   pOutNumCC,          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        __vptr_uint32  pOutDenomVar,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        unsigned short outPitch           /*Out Score buffer pitch*/
){

    /*
    for (v=0; v < outputHeight; v++) {
        for (u=0; u < outputWidth; u++) {
            sum[u + v*outputWidth]= sum[u + v*outputWidth]*invTemplateSize;
        }
    }
     */
    /* Performance estimates: 6/16 cycles */
    __vector vInvTemplateSize, v_16;
    vInvTemplateSize= invTemplateSize;
    v_16= 16;

    for (int v=0; v < outputHeight; v++) {
        for (int u=0; u < ALIGN_SIMD2(outputWidth)/VCOP_2SIMD_WIDTH; u++) {
            __vector vInput0, vInput1, vInput0_l, vInput1_l, vInput0_h, vInput1_h;
            __agen sumWrAddr= v*sumStride + u*VCOP_2SIMD_WIDTH*SUM_ELEMSZ;

            vInput0_h= pSumH[sumWrAddr].ds2();
            vInput0_l= pSumL[sumWrAddr].ds2();

            vInput1_h= (pSumH + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].ds2();
            vInput1_l= (pSumL + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].ds2();

            vInput0_h= vInput0_h*vInvTemplateSize;
            vInput1_h= vInput1_h*vInvTemplateSize;

            vInput0_l= vInput0_l*vInvTemplateSize;
            vInput1_l= vInput1_l*vInvTemplateSize;

            vInput0_h=  vInput0_h<<v_16;
            vInput1_h=  vInput1_h<<v_16;

            vInput0= vInput0_h + vInput0_l;
            vInput1= vInput1_h + vInput1_l;

            pSum[sumWrAddr].npt()= vInput0.round(qShiftDiff);
            (pSum + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].npt()= vInput1.round(qShiftDiff);

        }
    }

    __vector vqShift;

    vqShift= qShift;

    /*
     * Performance estimates:
     *  tempImgWidth*tempImgHeight*4/16= 0.25*tempImgWidth*tempImgHeight cyc/pixel
     */
    for (int v=0; v < outputHeight; v++) {
        for (int u=0; u < ALIGN_SIMD2(outputWidth)/VCOP_2SIMD_WIDTH; u++) {
            __vector vNumCC0, vNumCC1, vDenomVar0, vDenomVar1, vFavg0, vFavg1;
            __agen sumAddr= v*sumStride + u*VCOP_2SIMD_WIDTH*SUM_ELEMSZ;
            __agen outAddr= v*outPitch*OUT_ELEMSZ + u*VCOP_2SIMD_WIDTH*OUT_ELEMSZ;
            vNumCC0= 0;
            vNumCC1= 0;
            vDenomVar0= 0;
            vDenomVar1= 0;

            vFavg0= pSum[sumAddr].npt();
            vFavg1= (pSum + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumAddr].npt();

            for (int y=0; y < tempImgHeight; y++) {
                for (int x=0; x < tempImgWidth; x++) {
                    __vector vInput0, vInput1, vTemplate, vTemp10, vTemp11, vTemp20, vTemp21;
                    __agen orgImgAddr= x*INPUT_ELEMSZ + y*INPUT_ELEMSZ*orgImgPitch + u*VCOP_2SIMD_WIDTH*INPUT_ELEMSZ + v*INPUT_ELEMSZ*orgImgPitch;
                    __agen tempImgAddr=x*TEMPLATE_ELEMSZ + y*TEMPLATE_ELEMSZ*tempImgPitch;

                    vInput0= pOrgImg[orgImgAddr].npt();
                    vInput1= (pOrgImg + VCOP_SIMD_WIDTH*INPUT_ELEMSZ)[orgImgAddr].npt();
                    vTemplate= pTempImg[tempImgAddr].onept();

                    vInput0= vInput0 << vqShift;
                    vInput1= vInput1 << vqShift;
                    vInput0= vInput0 - vFavg0;
                    vInput1= vInput1 - vFavg1;

                    vNumCC0+= (vInput0*vTemplate).round(8);
                    vNumCC1+= (vInput1*vTemplate).round(8);
                    vDenomVar0+= (vInput0*vInput0).round(8);
                    vDenomVar1+= (vInput1*vInput1).round(8);

                }
            }

            pOutNumCC[outAddr].npt()= vNumCC0;
            (pOutNumCC + VCOP_SIMD_WIDTH*OUT_ELEMSZ)[outAddr].npt()= vNumCC1;
            pOutDenomVar[outAddr].npt()= vDenomVar0;
            (pOutDenomVar + VCOP_SIMD_WIDTH*OUT_ELEMSZ)[outAddr].npt()= vDenomVar1;
        }
    }


}

/*
 * Performance estimates:
 *  (6/16 + 0.25*tempImgWidth*tempImgHeight)*ALIGN(output_width)*output_height
 *
 */
void vcop_ncc_qShift0(
        __vptr_uint8 pOrgImg,
        unsigned short orgImgWidth,
        unsigned short orgImgHeight,
        unsigned short orgImgPitch,        /*original input image pitch*/
        __vptr_int16   pTempImg,           /*template image pointer*/
        unsigned short tempImgWidth,       /*template image width*/
        unsigned short tempImgHeight,      /*template image height*/
        unsigned short tempImgPitch,       /*template image pitch*/
        __vptr_uint32  pSum,
        __vptr_uint16  pSumL,
        __vptr_uint16  pSumH,
        unsigned short sumStride,
        unsigned char  sizeQshift,
        unsigned char  qShift,
        __vptr_int32   pOutNumCC,          /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        __vptr_uint32  pOutDenomVar,       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        unsigned short outPitch           /*Out Score buffer pitch*/
){

    /*
    for (v=0; v < outputHeight; v++) {
        for (u=0; u < outputWidth; u++) {
            sum[u + v*outputWidth]= sum[u + v*outputWidth]*invTemplateSize;
        }
    }
     */
    /* Performance estimates: 6/16 cycles */
    __vector vInvTemplateSize, v_16;
    vInvTemplateSize= invTemplateSize;
    v_16= 16;

    for (int v=0; v < outputHeight; v++) {
        for (int u=0; u < ALIGN_SIMD2(outputWidth)/VCOP_2SIMD_WIDTH; u++) {
            __vector vInput0, vInput1, vInput0_l, vInput1_l, vInput0_h, vInput1_h;
            __agen sumWrAddr= v*sumStride + u*VCOP_2SIMD_WIDTH*SUM_ELEMSZ;

            vInput0_h= pSumH[sumWrAddr].ds2();
            vInput0_l= pSumL[sumWrAddr].ds2();

            vInput1_h= (pSumH + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].ds2();
            vInput1_l= (pSumL + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].ds2();

            vInput0_h= vInput0_h*vInvTemplateSize;
            vInput1_h= vInput1_h*vInvTemplateSize;

            vInput0_l= vInput0_l*vInvTemplateSize;
            vInput1_l= vInput1_l*vInvTemplateSize;

            vInput0_h=  vInput0_h<<v_16;
            vInput1_h=  vInput1_h<<v_16;

            vInput0= vInput0_h + vInput0_l;
            vInput1= vInput1_h + vInput1_l;

            pSum[sumWrAddr].npt()= vInput0.round(qShiftDiff);
            (pSum + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumWrAddr].npt()= vInput1.round(qShiftDiff);

        }
    }

    __vector vqShift;

    vqShift= qShift;

    /*
     * Performance estimates:
     *  tempImgWidth*tempImgHeight*4/16= 0.25*tempImgWidth*tempImgHeight cyc/pixel
     */
    for (int v=0; v < outputHeight; v++) {
        for (int u=0; u < ALIGN_SIMD2(outputWidth)/VCOP_2SIMD_WIDTH; u++) {
            __vector vNumCC0, vNumCC1, vDenomVar0, vDenomVar1, vFavg0, vFavg1;
            __agen sumAddr= v*sumStride + u*VCOP_2SIMD_WIDTH*SUM_ELEMSZ;
            __agen outAddr= v*outPitch*OUT_ELEMSZ + u*VCOP_2SIMD_WIDTH*OUT_ELEMSZ;
            vNumCC0= 0;
            vNumCC1= 0;
            vDenomVar0= 0;
            vDenomVar1= 0;

            vFavg0= pSum[sumAddr].npt();
            vFavg1= (pSum + VCOP_SIMD_WIDTH*SUM_ELEMSZ)[sumAddr].npt();

            for (int y=0; y < tempImgHeight; y++) {
                for (int x=0; x < tempImgWidth; x++) {
                    __vector vInput0, vInput1, vTemplate, vTemp10, vTemp11, vTemp20, vTemp21;
                    __agen orgImgAddr= x*INPUT_ELEMSZ + y*INPUT_ELEMSZ*orgImgPitch + u*VCOP_2SIMD_WIDTH*INPUT_ELEMSZ + v*INPUT_ELEMSZ*orgImgPitch;
                    __agen tempImgAddr=x*TEMPLATE_ELEMSZ + y*TEMPLATE_ELEMSZ*tempImgPitch;

                    vInput0= pOrgImg[orgImgAddr].npt();
                    vInput1= (pOrgImg + VCOP_SIMD_WIDTH*INPUT_ELEMSZ)[orgImgAddr].npt();
                    vTemplate= pTempImg[tempImgAddr].onept();

                    vInput0= vInput0 << vqShift;
                    vInput1= vInput1 << vqShift;
                    vInput0= vInput0 - vFavg0;
                    vInput1= vInput1 - vFavg1;

                    vNumCC0+= vInput0*vTemplate;
                    vNumCC1+= vInput1*vTemplate;
                    vDenomVar0+= vInput0*vInput0;
                    vDenomVar1+= vInput1*vInput1;

                }
            }

            pOutNumCC[outAddr].npt()= vNumCC0;
            (pOutNumCC + VCOP_SIMD_WIDTH*OUT_ELEMSZ)[outAddr].npt()= vNumCC1;
            pOutDenomVar[outAddr].npt()= vDenomVar0;
            (pOutDenomVar + VCOP_SIMD_WIDTH*OUT_ELEMSZ)[outAddr].npt()= vDenomVar1;
        }
    }


}
