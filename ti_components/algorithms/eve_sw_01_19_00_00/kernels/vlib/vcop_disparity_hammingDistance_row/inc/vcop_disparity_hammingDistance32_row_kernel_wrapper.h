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
 *  @file       vcop_disparity_hammingDistance32_row_kernel_wrapper.c
 *
 *  @brief      This header file defines the prototype of wrapper functions that call the disparity kernel function corresponding
 *                 to the use case specified by rFlag.
 */

#ifndef _TI_vcop_disparity_hammingDistance32_row_kernel_wrapper_h_
#define _TI_vcop_disparity_hammingDistance32_row_kernel_wrapper_h_

#include <stdint.h>

#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_hammingDistance32_RL_row_kernel.h"

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_first_row_firstCall(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_first_row_firstCall_init(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_first_row(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_first_row_init(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_nth_row_firstCall(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_nth_row_firstCall_init(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_nth_row(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_nth_row_init(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/***********************************************************/
#endif

