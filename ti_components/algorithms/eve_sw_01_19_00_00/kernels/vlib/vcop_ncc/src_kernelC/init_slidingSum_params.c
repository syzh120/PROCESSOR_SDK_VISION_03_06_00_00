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


#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"
#include "vcop_ncc_cn.h"
#include "init_slidingSum_params.h"


int32_t init_slidingSum_params
(
        uint16_t windowWidth,       /*sliding sum window width*/
        uint16_t windowHeight,      /*sliding sum window height*/
        uint16_t computeWidth,      /* width of the output block */
        uint16_t computeHeight,     /* height of the output block */
        uint16_t pOffset[], /* Point to an array of 8 bytes. Call init_slidingSum_params() to initialize content pointed by pOffset*/
        uint8_t sizeOffsetArray, /* Should be 32 */
        uint16_t *scratchStride,
        uint16_t *sizeOfScratch,
        uint16_t *sumStride,
        uint16_t *sizeOfSum
) {

    int32_t i, j;
    uint16_t orgImgWidth;
    uint8_t bank[8];
    int32_t errorCode= 0;

    orgImgWidth= (computeWidth + windowWidth) - (uint16_t)1;

    if (sizeOffsetArray < 32U) {
        errorCode= -4;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto exitFunc;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*Calculate size of one line used in the first p-scatter, need to be (n*8 + 1) banks or (n*8*4 + 4)=  n*32 + 4 bytes) wide to avoid p-scatter error*/
    *scratchStride= ((((uint16_t)4*computeHeight) + (uint16_t)31) & ((uint16_t)(~(uint16_t)31))) + (uint16_t)4 ; /* Round up to next multiple of 32 and then add 4 bytes */
    *sumStride= ((((uint16_t)4*computeWidth) + (uint16_t)31) & (uint16_t)(~(uint16_t)31)) + (uint16_t)4 ;

    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i]=(uint16_t)i*(*scratchStride);
    }

    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i+8]=(uint16_t)i*(*sumStride);
    }

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
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto exitFunc;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
            }
        }
    }

    /* First calculate the bank */
    for(i=0;i<8;i++) {
        bank[i]= (uint8_t)((pOffset[i+8]%32U)/4U);
    }

    /* Verify bank constraints */
    for(i=0;i<8;i++) {
        for(j=i+1;j<8;j++) {
            if (bank[i]==bank[j]) {
                errorCode= -8; /* return error if bank conflict arises, normally should not happen it code runs up to here without returning previous error code */
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto exitFunc;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
            }
        }
    }

    *sizeOfScratch= (*scratchStride)*orgImgWidth;
    *sizeOfSum= ((*sumStride) + (uint16_t)4)*computeHeight;

exitFunc:
    return errorCode;
}
