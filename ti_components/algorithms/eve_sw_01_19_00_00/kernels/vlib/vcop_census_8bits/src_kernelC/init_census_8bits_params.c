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


/**
 *******************************************************************************
 *  @func          init_census_8bits_params
 *  @brief         This function initializes some parameters passed to vcop_census_8bits()
 *  @param [in]    winWidth : width of the census transform support windows
 *  @param [in]    winHeight : height of the census transform support windows
 *  @param [in]    winHorzStep : horizontal step between each orientation in the support window. Typically 1 or 2.
 *  @param [in]    winVertStep : vertical step between each orientation in the support window. Typically 1 or 2.
 *  @param [in]    computeWidth : number of bit strings produced in each output row
 *  @param [in]    computeWidth : number of rows produced
 *  @param [in]    outStride : Horizontal stride of the output block in bytes
 *  @params[out]   pOffset: pointer to an array of 8 half-words, will be initialized by init_census_8bits_params(). Preferably in WBUF.
 *  @params[in]    sizeOffsetArray: size in bytes of the array pointed by pOffset. Should be 16.
 *  @params[out]   pCodeWordMask: pointer to an array which will be initialized by init_census_8bits_params(). Preferably in WBUF.
 *  @params[in]    sizeCodeWordMarkArray: size in bytes of the array pointed by pCodeWordMask. Should be (winWidth*winHeight+7)/8.
 *  @params[out]   pRowMask: pointer to an array which will be initialized by init_census_8bits_params(). Preferably in WBUF.
 *  @params[in]    sizeRowMaskArray: size in bytes of the array pointed by pCodeWordMask. Should be (computeHeight+7)/8.
 *  @return         •   0: no error
 *                  •   -1: Constraint outStride >= ((winWidth*winHeight+7)/8)*computeWidth not respected.
 *                  •   -2: Constraint outStride multiple of 4, not respected.
 *                  •   -3: Constraint outStride not multiple of 32, not respected.
 *                  •   -4: Constraint of sizeOffsetArray to be 16 bytes, not respected.
 *                  •   5: Constraint of sizeCodeWordMarkArray to be (winWidth*winHeight+7)/8 bytes, not respected.
 *                  •   6: Constraint of sizeRowMaskArray to be (computeHeight+7)/8 bytes, not respected.

 *******************************************************************************
 */
#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"
#include "vcop_census_8bits_cn.h"
#include "init_census_8bits_params.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

int32_t init_census_8bits_params
(
        uint8_t winWidth, /* windWidth * winHeight msut be > 8 */
        uint8_t winHeight,
        uint8_t winHorzStep,
        uint8_t winVertStep,
        uint16_t computeWidth,
        uint16_t computeHeight,
        uint16_t outStride, /* in bytes, must multiple of 4 but not multiple of 32 bytes*/
        uint16_t pOffset[], /* Point to an array of 8 bytes. Call init_census_8bits_params() to initialize content pointed by pOffset*/
        uint8_t sizeOffsetArray, /* Should be 32 */
        uint8_t  pCodeWordMask[], /* Point to an array of (winWidth*winHeight+7)/8 bytes. Call init_census_8bits_params() to initialize content pointed by pCodeWordMask */
        int32_t sizeCodeWordMarkArray, /* Should be (winWidth*winHeight+7)/8 */
        uint8_t  pRowMask[],/* Point to an array of (computeHeight+7)/8 bytes. Call init_census_8bits_params() to initialize content pointed by pRowMask */
        int32_t sizeRowMaskArray, /* Should be (computeHeight+7)/8 */
        uint16_t *scratchStride
) {
    int32_t i, j;
    uint8_t bank[8];
    uint16_t numCensusOrientations= (uint16_t)_CENSUS_WIN_SIZE((uint16_t)winWidth, (uint16_t)winHeight,(uint16_t) winHorzStep, (uint16_t)winVertStep);
    uint16_t numBytesPerCensus= (numCensusOrientations + 7u) / 8u;
    int32_t errorCode= 0;

    if (outStride < (numBytesPerCensus*computeWidth)) {
        errorCode= -1;
        goto exitFunc;
    }

    if (outStride & 3u) {/* If outStride not multiple of 4, return error */
        errorCode= -2;
        goto exitFunc;
    }

    if ((outStride & 31u)== 0) {/* If outStride multiple of 32, return error */
        errorCode= -3;
        goto exitFunc;
    }

    if (sizeOffsetArray < 32u) {
        errorCode= -4;
        goto exitFunc;
    }

    if (sizeCodeWordMarkArray < (int32_t)numBytesPerCensus) {
        errorCode= -5;
        goto exitFunc;
    }

    if (sizeRowMaskArray < (((int32_t)computeHeight+7)/8)) {
        errorCode= -6;
        goto exitFunc;
    }

#if 1
    /*Calculate size of one line used in the first p-scatter, need to be (n*8 + 1) banks or (n*8*4 + 4)=  n*32 + 4 bytes) wide to avoid p-scatter error*/
    *scratchStride= (uint16_t)(((computeHeight + (uint16_t)31u) & (uint16_t)(~(uint16_t)31u)) + (uint16_t)4u); /* Round up to next multiple of 32 and then add 4 bytes */

    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i]=(uint16_t)i*(*scratchStride);
    }

    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i+8]=(uint16_t)i*outStride;
    }
#else
    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i]=i*outStride;
    }
#endif
    /* Verify that all offsets belong to a different bank, otherwise p-scatter will thrown an error */

    /* First calculate the bank */
    for(i=0;i<8;i++) {
        bank[i]= (uint8_t)((pOffset[i]%32U)/4U);
    }

    /* Verify bank constraints */
    for(i=0;i<8;i++) {
        for(j=i+1;j<8;j++) {
            if (bank[i]==bank[j]) {
                errorCode= -7; /* return error if bank conflict arises, normally should not happen it code runs up to here without returning previous error code */
                goto exitFunc;
            }
        }
    }

    /* First calculate the bank */
    for(i=0;i<8;i++) {
        bank[i]= (uint8_t)((pOffset[(uint32_t)i+8U]%32U)/4U);
    }

    /* Verify bank constraints */
    for(i=0;i<8;i++) {
        for(j=i+1;j<8;j++) {
            if (bank[i]==bank[j]) {
                errorCode= -8; /* return error if bank conflict arises, normally should not happen it code runs up to here without returning previous error code */
                goto exitFunc;
            }
        }
    }

    /* Initialize mask that will be used to zero-out bits that don't correspond to any valid orientation. Indeed alignment to byte boundary will produce extra
     * orientation bits to be ignored. */
    for(i=0;i<((int32_t)numBytesPerCensus-1);i++) {
        pCodeWordMask[i]= (uint8_t)0xFF;
    }

    /* If numCensusOrientations is not multiple of 8, last codeword mask is not 0xFF but has some bits masked to 0 */
    if (numCensusOrientations & 7u) {
        pCodeWordMask[numBytesPerCensus-1u]= (uint8_t)((uint16_t)((uint16_t)1u<<(numCensusOrientations & (uint16_t)7u)) - (uint16_t)1u);
    }
    else {
        pCodeWordMask[numBytesPerCensus-1u]= (uint8_t)0xFFu;
    }

    /* Initialize row mask. Will be used by predicated store to prevent extra values from being written out, due to usage of p-scatter. */
    for(i=0; i<(((int32_t)computeHeight+7)/8); i++) {
        pRowMask[i]=(uint8_t)0xFF;
    }

    if (computeHeight & 7u) {
        pRowMask[((computeHeight+7u)/8u) - 1u]= (uint8_t)((uint16_t)((uint16_t)1u<<(computeHeight & (uint16_t)7u))-(uint16_t)1u);
    }

    exitFunc:
    return errorCode;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */

