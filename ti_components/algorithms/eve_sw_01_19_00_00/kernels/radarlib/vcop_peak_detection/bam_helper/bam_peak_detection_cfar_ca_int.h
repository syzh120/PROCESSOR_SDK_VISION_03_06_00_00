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
 *  @file       bam_peak_detection_cfar_ca_int.h
 *
 *  @brief      This header defines internal structures for CFAR CA kernels.
 */

#ifndef BAM_PEAK_DETECTION_CFAR_CA_INT_H_
#define BAM_PEAK_DETECTION_CFAR_CA_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_peak_detection_cfar_ca.h"

#define BAM_PEAK_DETECTION_CFAR_CA_NUM_TABLES (8U)


typedef enum
{
  PEAK_DETECTION_CFAR_CA_INTERNAL_PARAMS_IDX = 0,
  PEAK_DETECTION_CFAR_CA_CELL_SUM_IDX,
  PEAK_DETECTION_CFAR_CA_CELL_SUM_ONE_LINE_IDX,
  PEAK_DETECTION_CFAR_CA_BINARY_MASK_IDX,
  PEAK_DETECTION_CFAR_CA_INTERNAL_DOPPLER_INDEX_IDX,
  PEAK_DETECTION_CFAR_CA_CURR_DOPPLER_INDEX_IDX,
  PEAK_DETECTION_CFAR_CA_SCATTER_INDEX_IDX,
  PEAK_DETECTION_CFAR_CA_INTERNAL_NUM_BLOCKS
} eBAM_PEAK_DETECTION_CFAR_CA_INTERNAL_BLOCKS;

typedef void (*BAM_PeakDetectionCfarCa_KernelFuncType)(uint16_t pblock[]);
typedef uint16_t *BAM_PeakDetectionCfarCa_KernelContextType;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[PEAK_DETECTION_CFAR_CA_INTERNAL_NUM_BLOCKS];
    void *pInBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_PEAK_DETECTION_CFAR_CA_NUM_OUTPUT_BLOCKS];
    BAM_PeakDetectionCfarCa_Args     kernelInitArgs;
    BAM_PeakDetectionCfarCa_ctrlArgs kernelCtrlArgs;
    uint16_t *pBlockTranspose;
    uint16_t *pBlockCellSum;
    uint16_t *pBlockCfarCa;
    uint16_t  numHorzPoint;
    uint16_t  numVertPoint;
    uint16_t  inputDataPitch;
    uint16_t  cellSumPitch;
    uint16_t  vertCoordinateShift;
    uint32_t  offsetBwInBufs;
    int16_t   cfarCaThreshold;
    uint16_t  shiftAmount;
    uint16_t  horzIdxUpdateOffset;
    uint8_t   *idxBuf;
    uint16_t transposePitch;
    uint32_t numKernels;
    BAM_PeakDetectionCfarCa_KernelFuncType    execFunc[3];
    BAM_PeakDetectionCfarCa_KernelContextType kernelContext[3];
} BAM_PeakDetectionCfarCa_Context;

#endif /* BAM_PEAK_DETECTION_CFAR_CA_INT_H_*/

