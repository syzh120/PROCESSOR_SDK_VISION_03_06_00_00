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
 *  @file       bam_glcm_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating gray-level
 *              co-occurrence matrix computation into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_glcm_int.h"
#include "bam_glcm.h"
#include "vcop_glcm_kernel.h" /* compiler should take care of include path */

extern uint8_t GLCM_TI_maxGLCMLevels_1c[BAM_GLCM_MAX_NUM_DIRECTIONS];
extern uint8_t GLCM_TI_maxGLCMLevels_8c[BAM_GLCM_MAX_NUM_DIRECTIONS];

/* Function Prototypes */
static BAM_Status Bam_Glcm_initFrame(void *kernelContext);

static BAM_Status Bam_Glcm_initFrame(void *kernelContext)
{
    BAM_Glcm_Context *context = (BAM_Glcm_Context *) kernelContext;
    uint8_t numChannels;
    uint32_t n, rem;
    uint8_t rowStart[BAM_GLCM_MAX_NUM_DIRECTIONS], colStart[BAM_GLCM_MAX_NUM_DIRECTIONS];
    int8_t maxColOffset, minColOffset, maxRowOffset, minRowOffset;
    uint8_t numRows, numCols;
    uint16_t *scratch_idx_arr[BAM_GLCM_MAX_NUM_DIRECTIONS],
             *out_glcm_arr[BAM_GLCM_MAX_NUM_DIRECTIONS];
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied */
    if((context->kernelArgs.numOffsets > BAM_GLCM_MAX_NUM_DIRECTIONS) ||
       (context->kernelArgs.numLevels > GLCM_TI_maxGLCMLevels_1c[context->kernelArgs.numOffsets - 1U])) {
        status = 1;
    }

    if(status == 0) {
        numChannels = (context->kernelArgs.numLevels > GLCM_TI_maxGLCMLevels_8c[context->kernelArgs.numOffsets - 1U]) ? 1U : 8U;

        maxColOffset = 0;
        minColOffset = 0;
        maxRowOffset = 0;
        minRowOffset = 0;

        for(n = 0; n < context->kernelArgs.numOffsets; n++) {

          rowStart[n] = (context->kernelArgs.rowOffsets[n] > 0) ? 0 : -context->kernelArgs.rowOffsets[n];
          colStart[n] = (context->kernelArgs.colOffsets[n] > 0) ? 0 : -context->kernelArgs.colOffsets[n];

          maxColOffset = MAX(maxColOffset, context->kernelArgs.colOffsets[n]);
          minColOffset = MIN(minColOffset, context->kernelArgs.colOffsets[n]);
          maxRowOffset = MAX(maxRowOffset, context->kernelArgs.rowOffsets[n]);
          minRowOffset = MIN(minRowOffset, context->kernelArgs.rowOffsets[n]);
        }

        numRows = (uint8_t)(context->kernelArgs.blockHeight - (maxRowOffset - minRowOffset));
        numCols = (uint8_t)(context->kernelArgs.blockWidth  - (maxColOffset - minColOffset));

        vcop_initialize_glcm((uint16_t*)context->pInternalBlock[GLCM_BUFF_IDX],
                             context->kernelArgs.numLevels,
                             numChannels*context->kernelArgs.numOffsets);

        for(n = 0; n < context->kernelArgs.numOffsets; n++) {
            scratch_idx_arr[n] = (uint16_t*)(*((uint16_t (*)[])context->pInternalBlock[SCRATCH_IDX]) +
                                 (n*numRows*(((uint32_t)numCols+1U)/2U)*2U));
            out_glcm_arr[n]    = (uint16_t*)(*((uint16_t (*)[])context->pInternalBlock[GLCM_BUFF_IDX]) +
                                 (n*numChannels*context->kernelArgs.numLevels*context->kernelArgs.numLevels));
        }

        if(context->kernelArgs.numLevels > GLCM_TI_maxGLCMLevels_8c[context->kernelArgs.numOffsets - 1U]) {
#if (!VCOP_HOST_EMULATION)
            vcop_glcm_compute_1c_init((uint8_t*)context->pInBlock[IN_IDX],
                                 scratch_idx_arr, out_glcm_arr,
                                 context->kernelArgs.numLevels, context->kernelArgs.numOffsets, rowStart, colStart,
                                 (char *)context->kernelArgs.rowOffsets, (char *)context->kernelArgs.colOffsets, numRows, numCols,
                                 context->kernelArgs.blockWidth, context->kernelArgs.blockHeight, context->kernelArgs.blockStride,
                                 context->pInternalBlock[PARAMS_IDX]);

            gBAM_TI_glcmExecFunc.kernelCustom = &vcop_glcm_compute_1c_vloops;
#endif
        }
        else {
            rem = (uint32_t)numCols - (8U*(((uint32_t)numCols-1U)/8U));
            for(n = 0; n < 8U; n++) {
                (*(uint8_t (*)[])(context->pInternalBlock[WEIGHT_IDX]))[n] = (n < rem) ? 1U : 0;
#if (!VCOP_HOST_EMULATION)
                (*(uint8_t (*)[])(context->pInternalBlock[WEIGHT_IDX]) + 0x20000)[n] = (n < rem) ? 1U : 0;
#endif
            }

#if (!VCOP_HOST_EMULATION)
            vcop_glcm_compute_8c_init((uint8_t*)context->pInBlock[IN_IDX],
                scratch_idx_arr, out_glcm_arr,
                (uint8_t*)context->pInternalBlock[WEIGHT_IDX],
                context->kernelArgs.numLevels, context->kernelArgs.numOffsets, rowStart,
                colStart, (char *)context->kernelArgs.rowOffsets, (char *)context->kernelArgs.colOffsets,
                numRows, numCols, context->kernelArgs.blockWidth,
                context->kernelArgs.blockHeight, context->kernelArgs.blockStride,
                context->pInternalBlock[PARAMS_IDX]);
            gBAM_TI_glcmExecFunc.kernelCustom = &vcop_glcm_compute_8c_vloops;
#endif
        }
        (*(uint32_t *(*)[])context->pOutBlock[OUT_IDX])[0] = (uint32_t *)context->pInternalBlock[GLCM_BUFF_IDX];
    }

    return status;
}

#if VCOP_HOST_EMULATION
static BAM_Status Bam_Glcm_computeFrame(void *kernelContext)
{
    BAM_Glcm_Context *context = (BAM_Glcm_Context *) kernelContext;
    uint8_t numChannels;
    uint32_t n, rem;
    uint8_t rowStart[BAM_GLCM_MAX_NUM_DIRECTIONS], colStart[BAM_GLCM_MAX_NUM_DIRECTIONS];
    int8_t maxColOffset, minColOffset, maxRowOffset, minRowOffset;
    uint8_t numRows, numCols;
    uint16_t *scratch_idx_arr[BAM_GLCM_MAX_NUM_DIRECTIONS],
             *out_glcm_arr[BAM_GLCM_MAX_NUM_DIRECTIONS];

    numChannels = (context->kernelArgs.numLevels > GLCM_TI_maxGLCMLevels_8c[context->kernelArgs.numOffsets - 1U]) ? 1U : 8U;

    maxColOffset = 0;
    minColOffset = 0;
    maxRowOffset = 0;
    minRowOffset = 0;

    for(n = 0; n < context->kernelArgs.numOffsets; n++) {

      rowStart[n] = (context->kernelArgs.rowOffsets[n] > 0) ? 0 : -context->kernelArgs.rowOffsets[n];
      colStart[n] = (context->kernelArgs.colOffsets[n] > 0) ? 0 : -context->kernelArgs.colOffsets[n];

      maxColOffset = MAX(maxColOffset, context->kernelArgs.colOffsets[n]);
      minColOffset = MIN(minColOffset, context->kernelArgs.colOffsets[n]);
      maxRowOffset = MAX(maxRowOffset, context->kernelArgs.rowOffsets[n]);
      minRowOffset = MIN(minRowOffset, context->kernelArgs.rowOffsets[n]);
    }

    numRows = context->kernelArgs.blockHeight - (maxRowOffset - minRowOffset);
    numCols = context->kernelArgs.blockWidth - (maxColOffset - minColOffset);

    for(n = 0; n < context->kernelArgs.numOffsets; n++) {
        scratch_idx_arr[n] = (uint16_t*)(context->pInternalBlock[SCRATCH_IDX]) + n*numRows*2U*((numCols+1U)/2U);
        out_glcm_arr[n] = (uint16_t*)context->pInternalBlock[GLCM_BUFF_IDX] +
                           n*numChannels*context->kernelArgs.numLevels*context->kernelArgs.numLevels;
    }

    if(context->kernelArgs.numLevels > GLCM_TI_maxGLCMLevels_8c[context->kernelArgs.numOffsets - 1]) {
        vcop_glcm_compute_1c((uint8_t*)context->pInBlock[IN_IDX],
            scratch_idx_arr, out_glcm_arr, context->kernelArgs.numLevels,
            context->kernelArgs.numOffsets, (unsigned char *)rowStart,(unsigned char *) colStart,
            (char *)context->kernelArgs.rowOffsets, (char *)context->kernelArgs.colOffsets,
            numRows, numCols, context->kernelArgs.blockWidth,
            context->kernelArgs.blockHeight, context->kernelArgs.blockStride);
    }
    else {
        vcop_glcm_compute_8c((uint8_t*)context->pInBlock[IN_IDX],
            scratch_idx_arr, out_glcm_arr,
            (uint8_t*)context->pInternalBlock[WEIGHT_IDX],
            context->kernelArgs.numLevels, context->kernelArgs.numOffsets, (unsigned char *)rowStart,
            (unsigned char *)colStart, (char *)context->kernelArgs.rowOffsets,(char *) context->kernelArgs.colOffsets,
            numRows, numCols, context->kernelArgs.blockWidth,
            context->kernelArgs.blockHeight, context->kernelArgs.blockStride);
    }

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_glcmExecFunc =
#if VCOP_HOST_EMULATION
    { NULL, &Bam_Glcm_initFrame, &Bam_Glcm_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Glcm_initFrame, NULL, NULL, NULL, &vcop_glcm_compute_8c_vloops };
#endif
