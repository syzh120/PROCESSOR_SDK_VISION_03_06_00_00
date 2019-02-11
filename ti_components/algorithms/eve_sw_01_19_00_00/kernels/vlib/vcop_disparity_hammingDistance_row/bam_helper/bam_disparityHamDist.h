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
 *  @file       bam_disparityHamDist.h
 *
 *  @brief      This header defines interfaces for integrating disparity calculation based on hamming distance kernel
 *              into BAM.
 */

#ifndef BAM_DISPARITY_HAMDIST_H_
#define BAM_DISPARITY_HAMDIST_H_

/*
 * Public kernel argument structure interface exposed to the kernel consumer/integrator
 */
/* CHECK_MISRA("-20.2")  -> Disable rule 20.2  */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed as name is not used for any language entiry */
typedef struct _bam_disparityHamDist_args
{
  uint8_t codeWordByteLen; /* Number of bytes per codeword, only 4 bytes (32-bits) hamming distance is currently supported. */
  uint16_t leftStride; /* Stride of the left row in bytes, need to be greater or equal to codeWordByteLen * (width + winWidth-1) */
  uint16_t rightStride; /* Stride of the right row in bytes , need to be greater or equal to codeWordByteLen * (width + numDisparities - 1 + winWidth - 1) */
  uint8_t winWidth; /* width of the support window used for cost calculation  */
  uint8_t winHeight; /* height of the support window used for cost calculation */
  uint16_t width; /* Must be multiple of 16, number of pixels in the row for which disparities are produced */
  uint8_t numDisparities; /* Number of disparities to inspect. Note that actual number of disparities produced is numDisparities/disparityStep which must be multiple of 8 */
  uint8_t disparityStep; /* Disparity step, for faster computation */
  uint16_t numRows; /* Number of rows in the input frames for which disparities will be produced */
  uint16_t allCostOutputStride; /* stride in bytes of the allCostOutput output, must be multiple of 4 but not be multiple of 32, in order to avoid bank conflict because of p-scatter usage */ 
  uint8_t direction; /* 0: left to right (default), 1: right to left */
  uint8_t adjacentCosts;
} BAM_DisparityHamDist_Args;
/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

typedef struct
{
    uint8_t ctlCmdId;
    uint16_t numRows;
} BAM_DisparityHamDist_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_disparityHamDist_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_disparityHamDist_ExecFunc;

extern BAM_KernelInfo gBAM_TI_disparityHamDist_Kernel;

#define BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT         0
#define BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT        1
#define BAM_DISPARITY_HAMDIST_INPUT_CARRYOVER_PORT    2

#define BAM_DISPARITY_HAMDIST_OUTPUT_DISP_PORT            0
#define BAM_DISPARITY_HAMDIST_OUTPUT_MINCOST_PORT         1
#define BAM_DISPARITY_HAMDIST_OUTPUT_CARRYOVER_PORT       2
#define BAM_DISPARITY_HAMDIST_OUTPUT_PREV_ADJ_COST_PORT   3
#define BAM_DISPARITY_HAMDIST_OUTPUT_NEXT_ADJ_COST_PORT   4
/* Don't support for now
#define BAM_DISPARITY_HAMDIST_OUTPUT_RL_DISP_PORT    5
#define BAM_DISPARITY_HAMDIST_OUTPUT_RL_MINCOST_PORT 6
*/

/* Macro symbols to initialize member ctlCmdId in BAM_DisparityHamDist_CtlArgs */
#define BAM_DISPARITY_HAMDIST_CMD_SET_NUMROWS 0

#endif /* BAM_DISPARITY_HAMDIST_H_ */

