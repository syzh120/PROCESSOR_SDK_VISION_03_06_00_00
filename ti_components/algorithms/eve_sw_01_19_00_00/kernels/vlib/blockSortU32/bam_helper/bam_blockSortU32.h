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
 *  @file       bam_blockSortU32.h
 *
 *  @brief      This header defines interfaces for integrating blockSort into BAM.
 */

#ifndef BAM_BLOCKSORTU32_H_
#define BAM_BLOCKSORTU32_H_

typedef struct
{
    uint16_t numElmts; /* Number of unsigned long elements to sort, must be either 64, 128, 256, 512, 1024 or 2048 */
} BAM_BlockSortU32_Args;

/* This control structure is used in case single block processing must be enabled, in which the applet needs to override the value
 * of the input and output's block pointer that has been found by BAM, with its own value passed in inputPtr and outputPtr of the control structure.
 */ 
typedef struct
{
    uint8_t ctlCmdId; /* Can only be set to BAM_BLOCKSORT_U32_CMD_SET_PTR */
    void *inputPtr;
    void *outputPtr;
} BAM_BlockSortU32_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_blockSortU32HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_blockSortU32ExecFunc;

extern BAM_KernelInfo gBAM_TI_blockSortU32Kernel;

#define BAM_BLOCKSORTU32_INPUT_PORT      0
#define BAM_BLOCKSORTU32_OUTPUT_PORT     0

#define BAM_BLOCKSORT_U32_CMD_SET_PTR 0

#endif /* BAM_BLOCK_SORT_H_ */

