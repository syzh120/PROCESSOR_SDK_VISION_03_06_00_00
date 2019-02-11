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
 *  @file       bam_soft_isp.h
 *
 *  @brief      This header defines interfaces for integrating software
 *              Image Signal Processor (ISP) into BAM.
 */

#ifndef BAM_SOFT_ISP_H_
#define BAM_SOFT_ISP_H_

#define SOFT_ISP_MAX_BLOCK_WIDTH  (68U)
#define SOFT_ISP_MAX_BLOCK_HEIGHT (68U)
#define SOFT_ISP_MAX_BLOCK_STRIDE (68U)

typedef struct
{
    uint16_t  blockWidth;
    uint16_t  blockHeight;
    uint16_t  blockStride;

    uint8_t   rPosition;
    uint8_t   sensorBitDepth;

    /* Decompanding parameters */
    uint8_t   enableDecompand;
    uint16_t  p1;
    uint16_t  pk;
    uint8_t   r1;
    uint16_t  r1r2;

    /* Black clamp and C balance */
    uint16_t *blackClamp;
    uint16_t *cBalanceGain;
    uint8_t   cBalanceShift;

    /* Extract R pixels */
    uint8_t   enableExtractR;

    /* GBCE parameter */
    uint8_t   gbceMethod;
    uint32_t *gbceToneCurveAddr;

    /* Stats Collection parameters */
    uint8_t   enableStats;
    uint16_t  saturationLimit;
} BAM_SoftIsp_Args;

typedef struct
{
    uint8_t   rPosition;
    uint8_t   sensorBitDepth;

    /* Decompanding parameters */
    uint8_t   enableDecompand;
    uint16_t  p1;
    uint16_t  pk;
    uint8_t   r1;
    uint16_t  r1r2;

    /* Black clamp and C balance */
    uint16_t *blackClamp;
    uint16_t *cBalanceGain;
    uint8_t   cBalanceShift;

    /* Extract R pixels */
    uint8_t   enableExtractR;

    /* GBCE parameter */
    uint8_t   gbceMethod;
    uint32_t *gbceToneCurveAddr;

    /* Stats Collection parameters */
    uint8_t   enableStats;
    uint16_t  saturationLimit;
} BAM_SoftIsp_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_softIspHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_softIspExecFunc;

extern BAM_KernelInfo gBAM_TI_softIspKernel;

typedef enum
{
  BAM_SOFT_ISP_INPUT_RC_PORT   =   0,
  BAM_SOFT_ISP_INPUT_CC_PORT,
  BAM_SOFT_ISP_NUM_INPUT_BLOCKS
} eBAM_SOFT_ISP_INPUT_PORTS;

typedef enum
{
  BAM_SOFT_ISP_OUTPUT_RC_PORT    =  0,
  BAM_SOFT_ISP_OUTPUT_CC_PORT,
  BAM_SOFT_ISP_OUTPUT_R_PORT,
  BAM_SOFT_ISP_OUTPUT_STATS_PORT,
  BAM_SOFT_ISP_NUM_OUTPUT_BLOCKS
} eBAM_SOFT_ISP_OUTPUT_PORTS;

#endif /* BAM_SOFT_ISP_H_ */

