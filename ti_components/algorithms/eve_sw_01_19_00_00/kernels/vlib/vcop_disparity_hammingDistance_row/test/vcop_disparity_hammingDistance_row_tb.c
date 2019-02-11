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

/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_disparity_hammingDistance_row_config.h"
#include "../inc/vcop_disparity_hammingDistance_row_cn.h"
#include "../inc/init_disparity_hammingDistance_row_params.h"

//#define _ONLY_NATC
#define _CIRCULAR_BUFFER

#if VCOP_HOST_EMULATION
// kernel source compiled directly by makefile to avoid conflicting macro defs
//#include "../src_kernelC/vcop_disparity_hammingDistance64_row_kernel.k"   
//#include "../src_kernelC/vcop_disparity_hammingDistance32_row_kernel.k"
//#include "../src_kernelC/vcop_disparity_postprocess_kernel.k"
#endif
#include "vcop_disparity_hammingDistance64_row_kernel.h"
#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_postprocess_kernel.h"

// #define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define VCOP_SIMD_WIDTH4 (4*VCOP_SIMD_WIDTH)

#define ALIGN_8(a)   (((a) + 7) & ~(7))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))

/*Define MAXIMUM values */
#define MAX_WIN_WIDTH      (15)
#define MAX_WIN_HEIGHT     (15)
#define EVE_MAX_WIDTH       (32)
#define MAX_NUM_DISPARITIES (64)
#define MAX_NUM_DISPARITIES_OUT (32)
#define MAX_WIDTH          (32)
#define MAX_NUM_ROWS       (2)
#define MAX_LEFT_STRIDE    (8*(MAX_WIDTH + MAX_WIN_WIDTH - 1))
#define MAX_RIGHT_STRIDE   (8*(MAX_WIDTH + MAX_NUM_DISPARITIES - 1 + MAX_WIN_WIDTH - 1))

#define NUM_ITER    (1)
#define COMPARE_REFERENCE (1)

#pragma DATA_SECTION (natC_dispOut, "DST_MEM");
unsigned char natC_dispOut[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_minCostOutput, "DST_MEM");
unsigned short natC_minCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_prevMinCostOutput, "DST_MEM");
unsigned short natC_prevMinCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_nextMinCostOutput, "DST_MEM");
unsigned short natC_nextMinCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_allCostOutput, "DST_MEM");
unsigned short natC_allCostOutput[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH];

#pragma DATA_SECTION (natC_dispOut, "DST_MEM");
unsigned char natC_RLdispOut[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_RLminCostOutput, "DST_MEM");
unsigned short natC_RLminCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (natC_RLallCostOutput, "DST_MEM");
unsigned short natC_RLallCostOutput[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH];
#pragma DATA_SECTION (natC_RLfromLRallCostOutput, "DST_MEM");
unsigned short natC_RLfromLRallCostOutput[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*(MAX_WIDTH + MAX_NUM_DISPARITIES)];

#pragma DATA_SECTION (allCostOutput, "DST_MEM");
unsigned short allCostOutput[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH];

#pragma DATA_SECTION (IMAGE_LEFT, "Adata");
unsigned char IMAGE_LEFT[(MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_LEFT_STRIDE] ;
#pragma DATA_SECTION (IMAGE_RIGHT, "Bdata");
unsigned char IMAGE_RIGHT[(MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_RIGHT_STRIDE] ;

//#pragma DATA_SECTION (dispOut, "Adata");
#pragma DATA_SECTION (dispOut, "Bdata");
unsigned char dispOut[MAX_NUM_ROWS*MAX_WIDTH];
//#pragma DATA_SECTION (minCostOutput, "Adata");
#pragma DATA_SECTION (minCostOutput, "Bdata");
unsigned short minCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (prevMinCostOutput, "Bdata");
unsigned short prevMinCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (nextMinCostOutput, "Bdata");
unsigned short nextMinCostOutput[MAX_NUM_ROWS*MAX_WIDTH];
#pragma DATA_SECTION (rlMinCostOutput, "Bdata");
unsigned short rlMinCostOutput[MAX_NUM_ROWS*ALIGN_SIMD2(MAX_WIDTH + MAX_NUM_DISPARITIES -1)];
#pragma DATA_SECTION (rlDispOut, "Bdata");
unsigned char rlDispOut[MAX_NUM_ROWS*ALIGN_SIMD2(MAX_WIDTH + MAX_NUM_DISPARITIES -1)];
/* The below buffers are only used when _PICK_HIGH_DISPARITY_WHEN_TIE is enabled in the *.k file */
#pragma DATA_SECTION (rlMinCostScratch, "Cdata");
unsigned short rlMinCostScratch[ALIGN_SIMD2(MAX_WIDTH + MAX_NUM_DISPARITIES -1)];
#pragma DATA_SECTION (rlDispScratch, "Cdata");
unsigned char rlDispScratch[ALIGN_SIMD2(MAX_WIDTH + MAX_NUM_DISPARITIES -1)];

#pragma DATA_SECTION (partialAllCostOutput, "Cdata");
#pragma DATA_ALIGN (partialAllCostOutput, 32);
unsigned short partialAllCostOutput[(MAX_NUM_DISPARITIES_OUT+2)*(MAX_WIDTH+4)];

#pragma DATA_SECTION (rlPartialAllCostOutput, "Cdata");
unsigned short rlPartialAllCostOutput[MAX_NUM_DISPARITIES_OUT*(MAX_WIDTH + MAX_NUM_DISPARITIES -1)];

#pragma DATA_SECTION (offset, "Cdata");
uint16_t offset[16];

#pragma DATA_SECTION (collateMask, "Cdata");
uint8_t collateMask[1];

//#pragma DATA_SECTION (scratch0, "Bdata");
#pragma DATA_SECTION (scratch0, "Cdata");
#pragma DATA_ALIGN (scratch0, 32);
int16_t scratch0[(MAX_NUM_DISPARITIES_OUT+2)*EVE_MAX_WIDTH];
#if 1
#pragma DATA_SECTION (scratch1, "Cdata");
#pragma DATA_ALIGN (scratch1, 32);
int16_t scratch1[(MAX_NUM_DISPARITIES_OUT+2)*EVE_MAX_WIDTH];
#endif
//#pragma DATA_SECTION (carryOverIn, "Cdata");
//#pragma DATA_SECTION (carryOverOut, "Cdata");
#pragma DATA_SECTION (carryOverIn, "Adata");
#pragma DATA_SECTION (carryOverOut, "Bdata");
int16_t carryOverIn[MAX_NUM_DISPARITIES_OUT];
int16_t carryOverOut[MAX_NUM_DISPARITIES_OUT];

#pragma DATA_SECTION (scratchIndex, "Adata");
uint16_t scratchIndex[EVE_MAX_WIDTH];

int16_t carryOverBackup[MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT];

#pragma DATA_SECTION (scratch2, "Adata");
int16_t scratch2[(MAX_NUM_DISPARITIES_OUT+2)*MAX_WIDTH];

void vcop_disparity_hammingDistance_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen
) {
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_row_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_row_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }

}

void vcop_disparity_hammingDistance_row_right_left_ref_cn(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen
) {
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_row_right_left_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_row_right_left_ref_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }

}


void vcop_disparity_hammingDistance_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen
){
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_first_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_first_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }

}

void vcop_disparity_hammingDistance_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen
){
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_nth_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                prevAllCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_nth_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                prevAllCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }

}

void vcop_disparity_hammingDistance_first_row_firstCall
(
        uint32_t *pLeft, /* In IBUFLA, Pointer to row from left image */
        uint32_t *pRight, /* In IBUFHA, Pointer to row from right image */
        unsigned short leftStride, /* Stride of the left row, need to be greater or equal to width + winWidth-1 */
        unsigned short rightStride, /* Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 */
        unsigned char winWidth, /* width of the support window used for cost calculation */
        unsigned char winHeight, /* height of the support window used for cost calculation */
        uint8_t *pDisparityOutput, /* In IBUFHA, pointer to disparity found for every pixels. Size is 'width' bytes */
        uint16_t *pMinCostOutput, /* In IBUFHA, pointer to minimum cost corresponding to the disparity found for every pixel. Size is 4*width bytes   */
        uint16_t *pAllCostOutput, /* In WBUF, Must be 32-bytes aligned.  size must be equal to the parameter allCostOutputBufferSize returned by init_disparity_hammingDistance64_row_params()   */
        unsigned short allCostOutputStride, /* Must be set to the parameter allCostOutputStride returned by init_disparity_hammingDistance64_row_params() */ 
        unsigned short width,   /* Must be multiple of 16, number of pixels in the row for which disparities are produced */
        unsigned char numDisparities, /* Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep which must be multiple of 8 */
        unsigned char disparityStep, /* Disparity step, for faster computation */
        uint8_t *pCollateMask, /* In WBUF, pointer to value equal to 0x80, set by init_disparity_hammingDistance64_row_params() */
        uint16_t *pOffset, /* In WBUF, is a constant memory of size 32 bytes, filled by init_disparity_hammingDistance64_row_params() */
        int16_t *pScratch0, /* In WBUF, must be 32 bytes aligned, size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance64_row_params()   */
        int16_t *pCarryOverOut, /* In WBUF, size is 2*disparity bytes */
        unsigned short scratchStride, /* Must be set to the parameter scratchBufferStride returned by init_disparity_hammingDistance64_row_params() */
        uint8_t codeWordLen 
){
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_first_row_firstCall
        (
                pLeft,
                pRight,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pCarryOverOut,
                scratchStride
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_first_row_firstCall
        (
                pLeft,
                pRight,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pCarryOverOut,
                scratchStride
        );
    }
}


void vcop_disparity_hammingDistance_first_row
(
        uint32_t *pLeft, /* In IBUFLA, Pointer to row from left image */
        uint32_t *pRight, /* In IBUFHA, Pointer to row from right image */
        unsigned short leftStride, /* Stride of the left row, need to be greater or equal to width + winWidth-1 */
        unsigned short rightStride, /* Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 */
        unsigned char winWidth, /* width of the support window used for cost calculation */
        unsigned char winHeight, /* height of the support window used for cost calculation */
        uint8_t *pDisparityOutput, /* In IBUFHA, pointer to disparity found for every pixels. Size is 'width' bytes */
        uint16_t *pMinCostOutput, /* In IBUFHA, pointer to minimum cost corresponding to the disparity found for every pixel. Size is 4*width bytes   */
        uint16_t *pAllCostOutput, /* In WBUF, Must be 32-bytes aligned.  size must be equal to the parameter allCostOutputBufferSize returned by init_disparity_hammingDistance64_row_params()   */
        unsigned short allCostOutputStride, /* Must be set to the parameter allCostOutputStride returned by init_disparity_hammingDistance64_row_params() */ 
        unsigned short width,   /* Must be multiple of 16, number of pixels in the row for which disparities are produced */
        unsigned char numDisparities, /* Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep which must be multiple of 8 */
        unsigned char disparityStep, /* Disparity step, for faster computation */
        uint8_t *pCollateMask, /* In WBUF, pointer to value equal to 0x80, set by init_disparity_hammingDistance64_row_params() */
        uint16_t *pOffset, /* In WBUF, is a constant memory of size 32 bytes, filled by init_disparity_hammingDistance64_row_params() */
        int16_t *pScratch0, /* In WBUF, must be 32 bytes aligned, size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance64_row_params()   */
        int16_t *pCarryOverIn, /* In WBUF, size is 2*disparity bytes */
        int16_t *pCarryOverOut, /* In WBUF, size is 2*disparity bytes */
        unsigned short scratchStride, /* Must be set to the parameter scratchBufferStride returned by init_disparity_hammingDistance64_row_params() */
        uint8_t codeWordLen 
){
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_first_row
        (
                pLeft,
                pRight,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pCarryOverIn,
                pCarryOverOut,
                scratchStride
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_first_row
        (
                pLeft,
                pRight,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pCarryOverIn,
                pCarryOverOut,
                scratchStride
        );
    }
}

void vcop_disparity_hammingDistance_nth_row_firstCall
(
        uint32_t *pLeft, /* In IBUFLA, Pointer to row from left image */
        uint32_t *pRight, /* In IBUFHA, Pointer to row from right image */
        unsigned short leftStride, /* Stride of the left row, need to be greater or equal to width + winWidth-1 */
        unsigned short rightStride, /* Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 */
        unsigned char winWidth, /* width of the support window used for SAD calculation */
        unsigned char winHeight, /* height of the support window used for SAD calculation */
        uint8_t *pDisparityOutput, /* In IBUFHA, pointer to disparity found for every pixels. Size is 'width' bytes */
        uint16_t *pMinCostOutput, /* In IBUFHA, pointer to minimum cost corresponding to the disparity found for every pixel. Size is '4*width' bytes   */
        uint16_t *pAllCostOutput, /* In WBUF, Must be 32-bytes aligned.  size must be equal to the parameter allCostOutputBufferSize returned by init_disparity_hammingDistance_row_params()   */
        unsigned short allCostOutputStride, /* Must be set to the parameter allCostOutputStride returned by init_disparity_hammingDistance_row_params() */ 
        unsigned short width,   /* Must be multiple of 16, number of pixels in the row for which disparities are produced */
        unsigned char numDisparities, /* Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep which must be multiple of 8 */
        unsigned char disparityStep, /* Disparity step, for faster computation */
        uint8_t *pCollateMask, /* In WBUF, pointer to value equal to 0x80, set by init_disparity_hammingDistance_row_params() */
        uint16_t *pOffset, /* In WBUF, is a constant memory of size 32 bytes, filled by init_disparity_hammingDistance_row_params() */
        int16_t *pScratch0, /* In WBUF, must be 32 bytes aligned, size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance_row_params()   */
        int16_t *pScratch1, /* In WBUF, size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance_row_params()   */
        int16_t *pScratch2, /* In IBUFLA, Must be 32-bytes aligned size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance_row_params()   */
        int16_t *pCarryOverOut, /* In WBUF, size is 2*disparity bytes */
        unsigned short scratchStride, /* Must be set to the parameter scratchBufferStride returned by init_disparity_hammingDistance_row_params() */
        uint8_t codeWordLen 
){
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_nth_row_firstCall
        (
#ifdef _CIRCULAR_BUFFER
                pLeft - (leftStride/4),
                pLeft + (leftStride/4)*(winHeight-1),
                pRight - (rightStride/4),
                pRight + (rightStride/4)*(winHeight-1),
#else
                pLeft,
                pRight,
#endif
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pScratch1,
                pScratch2,
                pCarryOverOut,
                scratchStride
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_nth_row_firstCall
        (
#ifdef _CIRCULAR_BUFFER
                pLeft - (leftStride/4),
                pLeft + (leftStride/4)*(winHeight-1),
                pRight - (rightStride/4),
                pRight + (rightStride/4)*(winHeight-1),
#else
                pLeft,
                pRight,
#endif
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pScratch1,
                pScratch2,
                pCarryOverOut,
                scratchStride
        );
    }
}

void vcop_disparity_hammingDistance_nth_row
(
        uint32_t *pLeft, /* In IBUFLA, Pointer to row from left image */
        uint32_t *pRight, /* In IBUFHA, Pointer to row from right image */
        unsigned short leftStride, /* Stride of the left row, need to be greater or equal to width + winWidth-1 */
        unsigned short rightStride, /* Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 */
        unsigned char winWidth, /* width of the support window used for SAD calculation */
        unsigned char winHeight, /* height of the support window used for SAD calculation */
        uint8_t *pDisparityOutput, /* In IBUFHA, pointer to disparity found for every pixels. Size is 'width' bytes */
        uint16_t *pMinCostOutput, /* In IBUFHA, pointer to minimum cost corresponding to the disparity found for every pixel. Size is '4*width' bytes   */
        uint16_t *pAllCostOutput, /* In WBUF, Must be 32-bytes aligned.  size must be equal to the parameter allCostOutputBufferSize returned by init_disparity_hammingDistance_row_params()   */
        unsigned short allCostOutputStride, /* Must be set to the parameter allCostOutputStride returned by init_disparity_hammingDistance_row_params() */ 
        unsigned short width,   /* Must be multiple of 16, number of pixels in the row for which disparities are produced */
        unsigned char numDisparities, /* Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep which must be multiple of 8 */
        unsigned char disparityStep, /* Disparity step, for faster computation */
        uint8_t *pCollateMask, /* In WBUF, pointer to value equal to 0x80, set by init_disparity_hammingDistance_row_params() */
        uint16_t *pOffset, /* In WBUF, is a constant memory of size 32 bytes, filled by init_disparity_hammingDistance_row_params() */
        int16_t *pScratch0, /* In WBUF, must be 32 bytes aligned, size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance_row_params()   */
        int16_t *pScratch1, /* In WBUF, size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance_row_params()   */
        int16_t *pScratch2, /* In IBUFLA, Must be 32-bytes aligned size must be equal to the parameter scratchBufferSize returned by init_disparity_hammingDistance_row_params()   */
        int16_t *pCarryOverIn, /* In WBUF, size is 2*disparity bytes */
        int16_t *pCarryOverOut, /* In WBUF, size is 2*disparity bytes */
        unsigned short scratchStride, /* Must be set to the parameter scratchBufferStride returned by init_disparity_hammingDistance_row_params() */
        uint8_t codeWordLen 
){
    if (codeWordLen== 4) {
        vcop_disparity_hammingDistance32_nth_row
        (
#ifdef _CIRCULAR_BUFFER
                pLeft - (leftStride/4),
                pLeft + (leftStride/4)*(winHeight-1),
                pRight - (rightStride/4),
                pRight + (rightStride/4)*(winHeight-1),
#else
                pLeft,
                pRight,
#endif
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pScratch1,
                pScratch2,
                pCarryOverIn,
                pCarryOverOut,
                scratchStride
        );
    }
    else if (codeWordLen== 8) {
        vcop_disparity_hammingDistance64_nth_row
        (
#ifdef _CIRCULAR_BUFFER
                pLeft - (leftStride/4),
                pLeft + (leftStride/4)*(winHeight-1),
                pRight - (rightStride/4),
                pRight + (rightStride/4)*(winHeight-1),
#else
                pLeft,
                pRight,
#endif
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                pDisparityOutput,
                pMinCostOutput,
                pAllCostOutput,
                allCostOutputStride,
                width,
                numDisparities,
                disparityStep,
                pCollateMask,
                pOffset,
                pScratch0,
                pScratch1,
                pScratch2,
                pCarryOverIn,
                pCarryOverOut,
                scratchStride
        );
    }
}

char * moveToNextElement(char *in, char *LinePtr)
{
    LinePtr += strlen(in);
    while((LinePtr[0] == ' ') || (LinePtr[0] == '\t'))
    {
        LinePtr++;
    }
    return(LinePtr);
}

void fillDefaultConfig(sdisparity_hammingDistance_row_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->leftStride = MAX_LEFT_STRIDE;
    params->rightStride = MAX_RIGHT_STRIDE;
    params->width = MAX_WIDTH;
    params->numRows = MAX_NUM_ROWS;
    params->winWidth= MAX_WIN_WIDTH;
    params->winHeight= MAX_WIN_HEIGHT;
    params->numDisparities= MAX_NUM_DISPARITIES;
    params->disparityStep= 1;
    params->numIter        = NUM_ITER;
    params->offset= 0;
    params->writeOutput = 0;
    params->seedForRND    = 0;
    params->interpOutput= 0;
    params->rightLeftDisp= 0;
}


int writeOutputFile(unsigned char *dispOut, unsigned short *minCostOutput, unsigned short *allCostOutput, sdisparity_hammingDistance_row_Config * params, char * filename)
{
    FILE * fp;
    unsigned int i, j, k, actualNumDisparities;

    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for (k=0; k < params->numRows; k++) {

        for(i=0;i<params->width;i++)
        {

            fprintf(fp, "%3d,", dispOut[k*params->width + i]);
        }

        fprintf(fp, "\n\n");

        for(i=0;i<params->width;i++)
        {

            fprintf(fp, "%3d,", minCostOutput[k*params->width + i]);
        }

        fprintf(fp, "\n\n");

        actualNumDisparities= params->numDisparities/params->disparityStep;

        for(i=0;i<actualNumDisparities;i++)
        {
            for (j=0;j<params->width;j++) {
                fprintf(fp, "%3d,", allCostOutput[k*params->width*actualNumDisparities + i*params->width + j]);
            }
            fprintf(fp, "\n");
        }

        fprintf(fp, "\n ------------------------------------------------------------------------------------------ \n");
    }
    fclose(fp);

    return (0);
}


int readInputFile(void * input, unsigned short n, unsigned short w, unsigned short h, unsigned short stride, char * filename, int dataType)
{
    int i, j, k;
    FILE * fp;
    char * LinePtr;
    char * status;
    int value;
    char inputLine[MAX_INPUT_LINE_SIZE];
    char inputValue[MAX_INPUT_VALUE_SIZE];

    fp = fopen(filename, "r");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < h; i++)
        {
            memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
            status = fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
            if (status == NULL)
            {
                printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
                return(-1);
            }
            LinePtr = inputLine;
            for(j = 0; j < w; j++)
            {
                sscanf(LinePtr, "%d",&value);
                sscanf(LinePtr, "%s",inputValue);
                if(dataType == 5)
                {
                    int * ptr = (int * )input;
                    ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 4)
                {
                    unsigned int * ptr = (unsigned int * )input;
                    ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 3)
                {
                    short * ptr = (short * )input;
                    ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 2)
                {
                    unsigned short * ptr = (unsigned short * )input;
                    ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 1)
                {
                    char * ptr = (char * )input;
                    ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType ==0)
                {
                    unsigned char * ptr = (unsigned char * )input;
                    ptr[k*stride*h+i*stride+j] = value;
                }
                LinePtr = moveToNextElement(inputValue,LinePtr);
            }
        }
    }
    fclose(fp);
    return(0);
}

static void CreateRandPatternU8(unsigned char *p, unsigned short h, unsigned short stride)
{
    int i, j;

#ifdef __DEBUG
    printf("Input Block:\n");
#endif

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < stride; j++)
        {
            p[i*stride + j] = (rand() & 0xFF);
#ifdef __DEBUG
            printf("%4d, ",  p[i*stride + j]);
#endif
        }
#ifdef __DEBUG
        printf("\n");
#endif
    }
}

int test_disparity_hammingDistance_row_vcop(sdisparity_hammingDistance_row_Config * params)
{
    unsigned int iter, r, d, i, segm;
    uint16_t numDisp, disparityStepShift;
    uint16_t segmWidth;
    uint16_t scratchBufferSize, scratchBufferStride, partialAllCostOutputStride, partialAllCostOutputSize;

    int ret=0, status;

    assert((MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_LEFT_STRIDE >= params->leftStride*(params->numRows + params->winHeight - 1));
    assert((MAX_NUM_ROWS + MAX_WIN_HEIGHT - 1)*MAX_RIGHT_STRIDE >= params->rightStride*(params->numRows + params->winHeight - 1));
    assert(MAX_NUM_ROWS*MAX_NUM_DISPARITIES_OUT*MAX_WIDTH >= (params->width*params->numRows*(params->numDisparities/params->disparityStep)));

    profiler_init();

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern generation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU8(IMAGE_LEFT, params->numRows + params->winHeight - 1, params->leftStride);
        CreateRandPatternU8(IMAGE_RIGHT, params->numRows + params->winHeight - 1, params->rightStride);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(IMAGE_LEFT, 1, params->leftStride, params->numRows + params->winHeight - 1, params->leftStride, params->inLeftFileName, 0);
        readInputFile(IMAGE_RIGHT, 1, params->rightStride, params->numRows + params->winHeight - 1, params->rightStride, params->inRightFileName, 0);
    }

    segmWidth= params->width/params->numRowSegments;
    numDisp= params->numDisparities/params->disparityStep;

    i=1;
    while (params->disparityStep>>i) {
        i++;
    }
    disparityStepShift= i-1;

    printf("Codeword length: %d bytes,  Num disparities: %d, Compute row width = %d, num rows= %d, num segm per row= %d\n", params->codeWordLen, params->numDisparities/params->disparityStep, segmWidth, params->numRows, params->numRowSegments);

    status= init_disparity_hammingDistance_row_params
            (
                    offset,
                    sizeof(offset),
                    collateMask,
                    &scratchBufferSize,
                    &scratchBufferStride,
                    &partialAllCostOutputStride,
                    &partialAllCostOutputSize,
                    segmWidth,
                    params->numDisparities,
                    params->disparityStep
            );

    if (status < 0 ) {
        if (status== -1) {
            printf ("Error: width not greater than 32\n");
        }
        else if (status== -2) {
            printf ("Error: width not multiple of 16\n");
        }
        else if (status== -4) {
            printf ("Error: size of offset array not greater than 32\n");
        }
        else if (status== -7) {
            printf ("Error: bank conflict in computed offset (this error should not happen)\n");
        }
        else if (status== -8) {
            printf ("Error: bank conflict in computed offset (this error should not happen)\n");
        }
        exit(-1);
    }

    assert(scratchBufferSize <= sizeof(scratch0));
    assert(partialAllCostOutputSize <= sizeof(partialAllCostOutput));

    for(iter = 0; iter < params->numIter; iter++)
    {
        memset(natC_dispOut, 0, sizeof(natC_dispOut));
        memset(dispOut, 0, sizeof(dispOut));
        memset(natC_minCostOutput, 0, sizeof(natC_minCostOutput));
        memset(minCostOutput, 0, sizeof(minCostOutput));
        memset(rlMinCostOutput, 0xFF, sizeof(rlMinCostOutput));
        memset(allCostOutput, 0, sizeof(allCostOutput));
        memset(natC_allCostOutput, 0, sizeof(natC_allCostOutput));
        memset(partialAllCostOutput, 0, sizeof(partialAllCostOutput));
        memset(rlPartialAllCostOutput, 0xFF, sizeof(rlPartialAllCostOutput));
        memset(scratch0, 0, sizeof(scratch0));
        memset(carryOverIn, 0, sizeof(carryOverIn));
        memset(carryOverOut, 0, sizeof(carryOverOut));

        /* Initialize first row and last row with 65535 
         * This is a requirement from vcop_disparity_genPrevAndNextMinCost()
         * */
        for(i=0;i<partialAllCostOutputStride/2;i++) {
            partialAllCostOutput[i]= ((int)1<<(8*sizeof(partialAllCostOutput[0]))) - 1; /* Should be 65535 */;
            partialAllCostOutput[(numDisp+1)*partialAllCostOutputStride/2 + i]= ((int)1<<(8*sizeof(partialAllCostOutput[0]))) - 1; /* Should be 65535 */;
        }

        for (segm=0; segm < params->numRowSegments; segm++) {

            r= 0;

#ifdef _ONLY_NATC
            vcop_disparity_hammingDistance_first_row_cn
            (
                    IMAGE_LEFT + params->offset + r*params->leftStride + segm*segmWidth*params->codeWordLen,
                    IMAGE_RIGHT + r*params->rightStride + segm*segmWidth*params->codeWordLen,
                    params->leftStride,
                    params->rightStride,
                    params->winWidth,
                    params->winHeight,
                    dispOut + r*params->width + segm*segmWidth,
                    minCostOutput + r*params->width + segm*segmWidth,
                    allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width + segm*segmWidth,
                    segmWidth,
                    params->width,
                    params->numDisparities,
                    params->disparityStep,
                    params->codeWordLen
            );
#else
            if (segm== 0) {
                vcop_disparity_hammingDistance_first_row_firstCall
                (
                        (uint32_t*)(IMAGE_LEFT + params->offset + r*params->leftStride  + segm*segmWidth*params->codeWordLen), 
                        (uint32_t*)(IMAGE_RIGHT+ r*params->rightStride + segm*segmWidth*params->codeWordLen),
                        params->leftStride,
                        params->rightStride,
                        params->winWidth,
                        params->winHeight,
                        dispOut + r*params->width + segm*segmWidth,
                        minCostOutput + r*params->width + segm*segmWidth,
                        partialAllCostOutput + partialAllCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                        partialAllCostOutputStride,
                        segmWidth,
                        params->numDisparities,
                        params->disparityStep,
                        collateMask,
                        offset,
                        scratch0,
                        carryOverOut,
                        scratchBufferStride,
                        params->codeWordLen
                );

                /* If rightLeftDisp is != 0 then it is an indication that we have to calculate the right-left disparities for validation purpose */
                if (params->rightLeftDisp == 1) {
                    vcop_disparity_hammingDistance_row_right_left_firstCall
                    (
                            partialAllCostOutput + partialAllCostOutputStride/2,
                            rlDispOut + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                            rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                            rlDispOut + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                            rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                            rlPartialAllCostOutput,
                            rlDispScratch,
                            rlMinCostScratch,
                            partialAllCostOutputStride, /* allCostStride in bytes */
                            2*(segmWidth + params->numDisparities - 1), /* stride of rlPartialAllCostOutput in bytes */
                            segmWidth, /* width */
                            params->numDisparities,
                            params->disparityStep
                    );
                }

            }
            else {
                /* Restore carryOver */
                for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                    carryOverIn[d]= carryOverBackup[r*(params->numDisparities/params->disparityStep) + d];
                }

                vcop_disparity_hammingDistance_first_row
                (
                        (uint32_t*)(IMAGE_LEFT + params->offset + r*params->leftStride  + segm*segmWidth*params->codeWordLen), 
                        (uint32_t*)(IMAGE_RIGHT+ r*params->rightStride + segm*segmWidth*params->codeWordLen),
                        params->leftStride,
                        params->rightStride,
                        params->winWidth,
                        params->winHeight,
                        dispOut + r*params->width + segm*segmWidth,
                        minCostOutput + r*params->width + segm*segmWidth,
                        partialAllCostOutput + partialAllCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                        partialAllCostOutputStride,
                        segmWidth,
                        params->numDisparities,
                        params->disparityStep,
                        collateMask,
                        offset,
                        scratch0,
                        carryOverIn,
                        carryOverOut,
                        scratchBufferStride,
                        params->codeWordLen
                );

                /* If offset is != 0 then it is an indication that we have to calculate the right-left disparities for validation purpose */
                if (params->rightLeftDisp == 1) {
                    vcop_disparity_hammingDistance_row_right_left
                    (
                            partialAllCostOutput + partialAllCostOutputStride/2,
                            rlDispOut + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                            rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                            rlDispOut + r*(params->width + params->numDisparities - 1)  + (segm-1)*segmWidth,
                            rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + (segm-1)*segmWidth,
                            rlPartialAllCostOutput,
                            rlDispScratch,
                            rlMinCostScratch,
                            partialAllCostOutputStride, /* allCostStride in bytes */
                            2*(segmWidth + params->numDisparities - 1), /* stride of rlPartialAllCostOutput in bytes */
                            segmWidth, /* width */
                            params->numDisparities,
                            params->disparityStep
                    );
                }

            }

            /* If params->interpOutput== 1, generate the prev and next mincost values, which are typically used for interpolation in post-processing stage */
            if (params->interpOutput== 1) {
                vcop_disparity_genPrevAndNextMinCost(
                        dispOut + r*params->width + segm*segmWidth,
                        partialAllCostOutput + partialAllCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                        prevMinCostOutput + r*params->width + segm*segmWidth,
                        nextMinCostOutput + r*params->width + segm*segmWidth,
                        scratchIndex,
                        segmWidth,
                        partialAllCostOutputStride,
                        params->numDisparities,
                        params->disparityStep,
                        disparityStepShift);
            }

            /* Save carryOver */
            for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                carryOverBackup[r*(params->numDisparities/params->disparityStep) + d]= carryOverOut[d];
            }

            /* For testing purpose, copy from partialAllCostOutput (used in VCOP version only) to allCostOutput */
            for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                for(i=0;i<segmWidth;i++) {
                    allCostOutput[d*params->width + segm*segmWidth +i]= (partialAllCostOutput + partialAllCostOutputStride/2)[d*(partialAllCostOutputStride/2)+i];
                }
            } 
#endif

            if (params->numRowSegments== 1)
                profiler_start();

            for (r=1;r<params->numRows;r++) {
#ifdef _ONLY_NATC

                vcop_disparity_hammingDistance_nth_row_cn
                (
                        IMAGE_LEFT + params->offset + r*params->leftStride + segm*segmWidth*params->codeWordLen,
                        IMAGE_RIGHT + r*params->rightStride + segm*segmWidth*params->codeWordLen,
                        params->leftStride,
                        params->rightStride,
                        params->winWidth,
                        params->winHeight,
                        dispOut + r*params->width + segm*segmWidth,
                        minCostOutput + r*params->width + segm*segmWidth,
                        allCostOutput + (r-1)*(params->numDisparities/params->disparityStep)*params->width + segm*segmWidth,
                        allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width + segm*segmWidth,
                        segmWidth,
                        params->width,
                        params->numDisparities,
                        params->disparityStep,
                        params->codeWordLen
                );
#else

                if (params->numRowSegments!= 1)
                    profiler_start();

                if (segm== 0) {
                    vcop_disparity_hammingDistance_nth_row_firstCall
                    (
                            (uint32_t*)(IMAGE_LEFT + params->offset + r*params->leftStride), 
                            (uint32_t*)(IMAGE_RIGHT + r*params->rightStride), 
                            params->leftStride,
                            params->rightStride,
                            params->winWidth,
                            params->winHeight,
                            dispOut + r*params->width,
                            minCostOutput + r*params->width,
                            partialAllCostOutput + partialAllCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                            partialAllCostOutputStride,
                            segmWidth,
                            params->numDisparities,
                            params->disparityStep,
                            collateMask,
                            offset,
                            scratch0,
                            scratch1,
                            scratch2,
                            carryOverOut,
                            scratchBufferStride,
                            params->codeWordLen
                    );

                    /* If offset is != 0 then it is an indication that we have to calculate the right-left disparities for validation purpose */
                    if (params->rightLeftDisp == 1) {
                        vcop_disparity_hammingDistance_row_right_left_firstCall
                        (
                                partialAllCostOutput + partialAllCostOutputStride/2,
                                rlDispOut + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                                rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                                rlDispOut + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                                rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                                rlPartialAllCostOutput,
                                rlDispScratch,
                                rlMinCostScratch,
                                partialAllCostOutputStride, /* allCostStride in bytes */
                                2*(segmWidth + params->numDisparities - 1), /* rlAllCostStride in bytes */
                                segmWidth, /* width */
                                params->numDisparities,
                                params->disparityStep
                        );
                    }

                }
                else {
                    /* Restore carryOver */
                    for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                        carryOverIn[d]= carryOverBackup[r*(params->numDisparities/params->disparityStep) + d];
                    }

                    vcop_disparity_hammingDistance_nth_row
                    (
                            (uint32_t*)(IMAGE_LEFT + params->offset + r*params->leftStride  + segm*segmWidth*params->codeWordLen), 
                            (uint32_t*)(IMAGE_RIGHT + r*params->rightStride + segm*segmWidth*params->codeWordLen), 
                            params->leftStride,
                            params->rightStride,
                            params->winWidth,
                            params->winHeight,
                            dispOut + r*params->width + segm*segmWidth,
                            minCostOutput + r*params->width + segm*segmWidth,
                            partialAllCostOutput + partialAllCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                            partialAllCostOutputStride,
                            segmWidth,
                            params->numDisparities,
                            params->disparityStep,
                            collateMask,
                            offset,
                            scratch0,
                            scratch1,
                            scratch2,
                            carryOverIn,
                            carryOverOut,
                            scratchBufferStride,
                            params->codeWordLen
                    );

                    /* If offset is != 0 then it is an indication that we have to calculate the right-left disparities for validation purpose */
                    if (params->rightLeftDisp == 1) {
                        vcop_disparity_hammingDistance_row_right_left
                        (
                                partialAllCostOutput + partialAllCostOutputStride/2,
                                rlDispOut + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                                rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + segm*segmWidth,
                                rlDispOut + r*(params->width + params->numDisparities - 1)  + (segm-1)*segmWidth,
                                rlMinCostOutput + r*(params->width + params->numDisparities - 1)  + (segm-1)*segmWidth,
                                rlPartialAllCostOutput,
                                rlDispScratch,
                                rlMinCostScratch,
                                partialAllCostOutputStride, /* allCostStride in bytes */
                                2*(segmWidth + params->numDisparities - 1), /* rlAllCostStride in bytes */
                                segmWidth, /* width */
                                params->numDisparities,
                                params->disparityStep
                        );
                    }

                }

                /* If params->interpOutput== 1, generate the prev and next mincost values, which are typically used for interpolation in post-processing stage */
                if (params->interpOutput== 1) {
                    vcop_disparity_genPrevAndNextMinCost(
                            dispOut + r*params->width + segm*segmWidth,
                            partialAllCostOutput + partialAllCostOutputStride/2, /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                            prevMinCostOutput + r*params->width + segm*segmWidth,
                            nextMinCostOutput + r*params->width + segm*segmWidth,
                            scratchIndex,
                            segmWidth,
                            partialAllCostOutputStride,
                            params->numDisparities,
                            params->disparityStep,
                            disparityStepShift);
                }

                if (params->numRowSegments!= 1)
                    profiler_end();

                /* Save carryOver */
                for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                    carryOverBackup[r*(params->numDisparities/params->disparityStep) + d]= carryOverOut[d];
                }

                /* For testing purpose, copy from partialAllCostOutput (used in VCOP version only) to allCostOutput */
                for(d=0;d<params->numDisparities/params->disparityStep;d++) {
                    for(i=0;i<segmWidth;i++) {
                        allCostOutput[(r*(params->numDisparities/params->disparityStep) + d)*params->width + segm*segmWidth + i]= (partialAllCostOutput + partialAllCostOutputStride/2)[d*(partialAllCostOutputStride/2)+i];
                    }
                }
#endif
            }

        }
        if (params->numRowSegments== 1)
            profiler_end();

#ifdef COMPARE_REFERENCE
#ifdef _USE_OPTIMIZED_RL
        memset(rlMinCostOutput, 0xFF, sizeof(rlMinCostOutput));
#endif
        for (r=0;r<params->numRows;r++) {
            vcop_disparity_hammingDistance_row_ref_cn
            (
                    IMAGE_LEFT + params->offset + r*params->leftStride,
                    IMAGE_RIGHT + r*params->rightStride,
                    params->leftStride,
                    params->rightStride,
                    params->winWidth,
                    params->winHeight,
                    natC_dispOut + r*params->width,
                    natC_minCostOutput + r*params->width,
                    natC_allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width,
                    params->width,
                    params->numDisparities,
                    params->disparityStep,
                    params->codeWordLen
            );

            vcop_disparity_hammingDistance_row_right_left_ref_cn
            (
                    IMAGE_LEFT + params->offset + r*params->leftStride, /* add a bias if disparity step is different than 1 */
                    IMAGE_RIGHT + params->offset + r*params->rightStride,
                    params->leftStride,
                    params->rightStride,
                    params->winWidth,
                    params->winHeight,
                    natC_RLdispOut + r*params->width,
                    natC_RLminCostOutput + r*params->width,
                    natC_RLallCostOutput + r*(params->numDisparities/params->disparityStep)*params->width,
                    params->width,
                    params->numDisparities,
                    params->disparityStep,
                    params->codeWordLen
            );
#ifdef _USE_OPTIMIZED_RL
            /* Derive the inverse cost map natC_RLfromLRallCostOutput */
            vcop_disparity_hammingDistance_row_right_left_cn
            (
                    natC_allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width,
                    rlDispOut + r*(params->width + params->numDisparities - 1),
                    rlMinCostOutput + r*(params->width + params->numDisparities - 1),
                    rlDispOut + r*(params->width + params->numDisparities - 1),
                    rlMinCostOutput + r*(params->width + params->numDisparities - 1),
                    natC_RLfromLRallCostOutput + r*(params->numDisparities/params->disparityStep)*(params->width + params->numDisparities - 1),
                    rlDispScratch,
                    rlMinCostScratch,
                    2*params->width,
                    2*(params->width + params->numDisparities - 1),
                    params->width,
                    params->numDisparities,
                    params->disparityStep
            );
#endif
            if (params->interpOutput== 1) {
                /* Produce prevMinCost and nextMinCost that can be used for interpolation */
                vcop_disparity_genPrevAndNextMinCost_cn(
                        natC_dispOut + r*params->width,
                        natC_allCostOutput + r*(params->numDisparities/params->disparityStep)*params->width,
                        natC_prevMinCostOutput+ r*params->width,
                        natC_nextMinCostOutput+ r*params->width,
                        params->width,
                        params->numDisparities,
                        params->disparityStep
                );
            }

        }

        ret = memcmp(dispOut, natC_dispOut, sizeof(dispOut));
        ret |= memcmp(minCostOutput, natC_minCostOutput, sizeof(minCostOutput));
        if (params->interpOutput== 1) {
            ret |= memcmp(prevMinCostOutput, natC_prevMinCostOutput, sizeof(prevMinCostOutput));
            ret |= memcmp(nextMinCostOutput, natC_nextMinCostOutput, sizeof(nextMinCostOutput));
        }
        ret |= memcmp(allCostOutput, natC_allCostOutput, sizeof(allCostOutput));

        /* If params->offset != 0 then it means we computed right-left disparities and we need now to compare natC_RLallCostOutput and natC_RLfromLRallCostOutput 
         * Only compare the middle block of params->width - 2*(params->numDisparities/params->disparityStep -1) pixels
         */

        if (params->rightLeftDisp != 0 && (params->width - 2*(numDisp -1))> 0) {
            for (r=0;r<params->numRows;r++) {

#if 0
                for(d=0;d<numDisp;d++) {
                    for(i=0;i<params->width - 2*(numDisp -1);i++) {
                        if (*(natC_RLallCostOutput + (r*numDisp + d)*params->width + i) !=  *(natC_RLfromLRallCostOutput + (r*numDisp + d)*(params->width + params->numDisparities - 1) + params->numDisparities -1 + i)){
                            ret|= 1;
                            break;
                        }
                    }
                }
#endif

                for(i=0;i<params->width - 2*(numDisp -1);i++) {
                    if (*(natC_RLdispOut + r*params->width + i) !=  *(rlDispOut + r*(params->width + params->numDisparities - 1) + params->numDisparities -1 + i)){
                        ret|= 1;
                        break;
                    }
                }

                for(i=0;i<params->width - 2*(numDisp -1);i++) {
                    if (*(natC_RLminCostOutput + r*params->width + i) !=  *(rlMinCostOutput + r*(params->width + params->numDisparities - 1) + params->numDisparities -1 + i)){
                        ret|= 1;
                        break;
                    }
                }
            }
        }



        if(ret !=0)
        {
            printf("Natural C & Kernel DIDN'T MATCH !!!!!!!!!!\n\n");
            exit(0);
        }
        else
        {
            printf("Natural C & Kernel MATCHED\n\n");
        }
#endif

    }

    profiler_deinit();

    if(params->writeOutput)
    {
        writeOutputFile(natC_dispOut, natC_minCostOutput, natC_allCostOutput, params, params->outFileName);
    }

    return 0;
}

int main()
{
    FILE * fp;
    char * LinePtr;
    int lineNum = -1;
    sdisparity_hammingDistance_row_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    printf("\nvcop_disparity_hammingDistance_row test\n\n");

    params = (sdisparity_hammingDistance_row_Config *)(&gConfig_disparity_hammingDistance_row);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_disparity_hammingDistance_row_vcop(params);
        return(0);
    }

    while(1)
    {
	char * status;
        memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
        status = fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = params->configLine;
        if (status == NULL)
            break;
        lineNum++;
        sscanf(LinePtr, "%d",&config_cmd);
        sscanf(LinePtr, "%s",params->configParam);
        if(config_cmd == 0)
        {
            printf("End of config list found !\n");
            break;
        }
        else if(config_cmd == 2)
        {
            continue;
        }
        else if(config_cmd == 1)
        {
	    int status;
            LinePtr = moveToNextElement(params->configParam,LinePtr);
            status  = sscanf(LinePtr, "%s",configFileName);
            printf("Processing config file %s !\n", configFileName);
            fillDefaultConfig(params);
            status = readparamfile(configFileName, &gsTokenMap_disparity_hammingDistance_row[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_disparity_hammingDistance_row_vcop(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);
    exit(0);

}


/*--------------------------------------------------------------------------*/
/* End of file: vcop_disparity_hammingDistance_row_tb.c                     */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

