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
 *  @file       bam_nonMaxSuppress_mxn_S16bitPack.h
 *
 *  @brief      This header defines interfaces for integrating non max suppression into BAM.
 */

#ifndef BAM_NONMAXSUPPRESS_MXN_S16BITPACK_H_
#define BAM_NONMAXSUPPRESS_MXN_S16BITPACK_H_

#include <stdint.h>

#define BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE (8100U)


typedef struct
{
  int16_t  threshold;
  uint16_t computeWidth;
  uint16_t computeHeight;
  uint16_t winW; /* NMS window width */
  uint16_t winH; /* NMS window height */
  uint16_t inStride;
  uint16_t outStride; /* Must be multiple of 8 */
} BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc;

extern BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S16bitPack_Kernel;

/* Macro symbols to initialize member ctlCmdId in BAM_NonMaxSuppress_mxn_S16bitPack_Args */
typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_CMD_GET_THRESHOLD = 0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_CMD_SET_THRESHOLD
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_CTRL_CMD;


typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORT   =   0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_NUM_INPUT_BLOCKS
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORTS;

typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT = 0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_NUM_OUTPUT_BLOCKS
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORTS;

typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_PARAMS_IDX   =    0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_NUM_BLOCK
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_BLOCKS;



#endif /* BAM_NONMAXSUPPRESS_MXN_S16BITPACK_H_ */

