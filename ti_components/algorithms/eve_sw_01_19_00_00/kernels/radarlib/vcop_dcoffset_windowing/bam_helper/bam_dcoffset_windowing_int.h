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
 *  @file       bam_dcoffset_windowing_int.h
 *
 *  @brief      This header defines internal structures for DC offset, windowing kernels.
 */

#ifndef BAM_DCOFFSET_WINDOWING_INT_H_
#define BAM_DCOFFSET_WINDOWING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_dcoffset_windowing.h"

#define BAM_DCOFFSET_WINDOWING_MAX_NUM_LINES (65U)
#define BAM_DCOFFSET_WINDOWING_MAX_OUTPUT_BLOCK_SIZE (16384U)

typedef enum{
 BAM_DCOFFSET_WINDOWING_ENABLE_SIGNEXTENSION         = (uint32_t)1U << 0U,
 BAM_DCOFFSET_WINDOWING_ENABLE_INTERFERENCE_ZERO_OUT = (uint32_t)1U << 1U,
 BAM_DCOFFSET_WINDOWING_ENABLE_DCOFFSET              = (uint32_t)1U << 2U,
 BAM_DCOFFSET_WINDOWING_ENABLE_WINDOWING             = (uint32_t)1U << 3U,
 BAM_DCOFFSET_WINDOWING_ENABLE_ALL                   = 0xFFFFU
}eBAM_DCOFFSET_WINDOWING_CONFIG;


typedef enum
{
  DCOFFSET_WINDOWING_INTERNAL_PARAMS_IDX = 0,
  DCOFFSET_WINDOWING_INTERNAL_WINDOWING_COEFF_IDX,
  DCOFFSET_WINDOWING_INTERNAL_DCOFFSET_IDX,
  DCOFFSET_WINDOWING_INTERNAL_PSCATTER_IDX,
  DCOFFSET_WINDOWING_INTERNAL_TRANSPOSE_PSCATTER_IDX,
  DCOFFSET_WINDOWING_INTERNAL_SCRATCH_IDX,
  DCOFFSET_WINDOWING_INTERNAL_INTERFERENCE_OUTPUT_IDX,
  DCOFFSET_WINDOWING_INTERNAL_NUM_BLOCKS
} eBAM_DCOFFSET_WINDOWING_INTERNAL_BLOCKS;

typedef void (*BAM_DcoffsetWindowing_KernelFuncType)(uint16_t pblock[]);
typedef uint16_t *BAM_DcoffsetWindowing_KernelContextType;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[DCOFFSET_WINDOWING_INTERNAL_NUM_BLOCKS];
    void *pInBlock[BAM_DCOFFSET_WINDOWING_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_DCOFFSET_WINDOWING_NUM_OUTPUT_BLOCKS];
    BAM_DcoffsetWindowing_Args     kernelInitArgs;
    BAM_DcoffsetWindowing_CtrlArgs kernelCtrlArgs;
    uint16_t *                     pBlockInterferenceZeroOut;
    uint16_t *                     pBlockDcOffset;
    uint16_t *                     pBlockWindowing;
    uint16_t *                     pBlockSignExtension;
    uint16_t                       interimTransposeStride;
    uint8_t                        shift;
    uint8_t                        numKernels;
    uint32_t                       configMask;
    int16_t                       *pSignExtOutput;
    int16_t                       *pInterferenceIn;
    int16_t                       *pInterferenceOut;
    int16_t                       *pWindowingIn;
    uint16_t                      signExtInPitch;
    uint16_t                      signExtOutPitch;
    uint16_t                      interferenceInPitch;
    uint16_t                      interferenceOutPitch;
    uint16_t                      dcOffsetInPitch;
    uint16_t                      winInputPitch;
    uint16_t                      numAlignedPoints;
    uint16_t                      inputPitch;
    BAM_DcoffsetWindowing_KernelFuncType    execFunc[4];
    BAM_DcoffsetWindowing_KernelContextType kernelContext[4];
} BAM_DcoffsetWindowing_Context;

#endif /* BAM_DCOFFSET_WINDOWING_INT_H_*/

