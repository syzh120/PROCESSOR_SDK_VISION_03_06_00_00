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
 *  @file       vcop_disparity_hammingDistance32_getPtr.h
 *
 *  @brief      This file defines interfaces for functions used for updating the param registers corresponding to pointers
 *              to some rows belonging to the left and right images. These functions are useful in case a line circular buffer
 *              is used to limit the amount of input data that needs to be brought in for every row calculation. When a line circular
 *              buffer is implemented, a sliding window mechanism is used and thus row pointers must be updated.
 */
#ifndef _VCOP_DISPARITY_HAMMING_DISTANCE32_COPY_GETPTR
#define _VCOP_DISPARITY_HAMMING_DISTANCE32_COPY_GETPTR

#include <stdint.h>

/*
 * vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr() returns the half-word offsets 
 * from the pblock pointer associated to vcop_disparity_hammingDistance32_nth_row_firstCall().
 * Each offset corresponds to the location where pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow are used. Each pointer is used 5 times and thus leftPrevRowOffset, 
 * leftLastRowOffset, rightPrevRowOffset, rightLastRowOffset are empty arrays of 5 elements that are filled
 * by the function. The parameter sizeOffsetArray should be >= 5.
 * winWidth input parmeter is used because pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow
 * are not used as raw values but instead get massaged with winWidth before being incorporated in the param registers
 * block.
 * If the function does not find anyone of the locations, -1 is returned instead of 0. 
 */
int32_t vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr(
        const uint16_t* pblock,
        const uint16_t    paramCount,
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint16_t    *leftPrevRowOffset,
        uint16_t    *leftLastRowOffset,
        uint16_t    *rightPrevRowOffset,
        uint16_t    *rightLastRowOffset,
        const uint8_t sizeOffsetArray,
        const uint8_t rlFlag
);

/*
 * vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr() take the input pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow and write them at locations specified in the arrays of 5 pointers leftPrevRowPtr,
 * leftLastRowPtr, rightPrevRowPtr, rightLastRowPtr. The function does not write the raw values of these pointers but
 * instead massage them with the parameter winWidth.
 */
void vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr(
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint32_t    **leftPrevRowPtr,
        uint32_t    **leftLastRowPtr,
        uint32_t    **rightPrevRowPtr,
        uint32_t    **rightLastRowPtr,
        const uint8_t rlFlag
);

/*
 * vcop_disparity_hammingDistance32_nth_row_getPtr() returns the half-word offsets 
 * from the pblock pointer associated to vcop_disparity_hammingDistance32_nth_row().
 * Each offset corresponds to the location where pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow are used. Each pointer is used 4 times and thus leftPrevRowOffset, 
 * leftLastRowOffset, rightPrevRowOffset, rightLastRowOffset are empty arrays of 4 elements that are filled
 * by the function. The parameter sizeOffsetArray should be >= 4.
 * winWidth input parmeter is used because pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow
 * are not used as raw values but instead get massaged with winWidth before being incorporated in the param registers
 * block.
 * If the function does not find anyone of the locations, -1 is returned instead of 0. 
 */
int32_t vcop_disparity_hammingDistance32_nth_row_getPtr(
        const uint16_t* pblock,
        const uint16_t    paramCount,
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint16_t    *leftPrevRowOffset,
        uint16_t    *leftLastRowOffset,
        uint16_t    *rightPrevRowOffset,
        uint16_t    *rightLastRowOffset,
        const uint8_t sizeOffsetArray,
        const uint8_t rlFlag
);

/*
 * vcop_disparity_hammingDistance32_nth_row_setPtr() take the input pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow and write them at locations specified in the arrays of 4 pointers leftPrevRowPtr,
 * leftLastRowPtr, rightPrevRowPtr, rightLastRowPtr. The function does not write the raw values of these pointers but
 * instead massage them with the parameter winWidth.
 */
void vcop_disparity_hammingDistance32_nth_row_setPtr(
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint32_t    **leftPrevRowPtr,
        uint32_t    **leftLastRowPtr,
        uint32_t    **rightPrevRowPtr,
        uint32_t    **rightLastRowPtr,
        const uint8_t rlFlag
);


#endif
