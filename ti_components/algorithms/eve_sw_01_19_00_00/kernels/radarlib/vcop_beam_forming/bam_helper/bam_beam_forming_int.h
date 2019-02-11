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
 *  @file       bam_beam_forming_int.h
 *
 *  @brief      This header defines internal structures for Beam forming kernels.
 */

#ifndef BAM_BEAM_FORMING_INT_H_
#define BAM_BEAM_FORMING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_beam_forming.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN(x,y)         (((x) + (y) - 1U)/(y))*(y)
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

typedef enum
{
  BEAM_FORMING_INTERNAL_PARAMS_IDX = 0,
  BEAM_FORMING_INTERNAL_STEERING_MATRIX_IDX,
  BEAM_FORMING_INTERNAL_OUT_ANGLE_IDX,
  BEAM_FORMING_INTERNAL_OUT_ENERGY_IDX,
  BEAM_FORMING_INTERNAL_PSCATTER_IDX,
  BEAM_FORMING_INTERNAL_NUM_BLOCKS
} eBAM_BEAM_FORMING_INTERNAL_BLOCKS;

typedef void (*BAM_BeamForming_KernelFuncType)(uint16_t pblock[]);
typedef uint16_t *BAM_BeamForming_KernelContextType;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[BEAM_FORMING_INTERNAL_NUM_BLOCKS];
    void *pInBlock[BAM_BEAM_FORMING_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_BEAM_FORMING_NUM_OUTPUT_BLOCKS];
    BAM_BeamForming_Args     kernelInitArgs;
    BAM_BeamForming_InCtrlArgs kernelCtrlArgs;
    BAM_BeamForming_Info     *pBeamFormingInfo[2];
    uint16_t  transposePitch;
    void     *pMatMulOutput;
    void     *pTransposeOut;
    void     *pEnergy;
    uint16_t *pBlockSteeringMatCopy;
    uint16_t *pBlockBeamForming;
    uint16_t *pBlockEnergyCal;
    uint16_t *pBlockAngleAssociation;
    uint16_t *pBlockTranspose;
    uint8_t   pingPongFlag;/* For tracking current buffer owned by ARP32 */
    uint8_t   enableSMCopy;
#if VCOP_HOST_EMULATION
    uint16_t  currDetectionIdx; /* This is only required for host emulation*/
#endif
} BAM_BeamForming_Context;

#endif /* BAM_BEAM_FORMING_INT_H_*/

