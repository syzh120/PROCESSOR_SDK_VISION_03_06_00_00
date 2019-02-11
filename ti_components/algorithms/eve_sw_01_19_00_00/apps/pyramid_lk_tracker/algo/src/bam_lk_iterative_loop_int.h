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
 *  @file       bam_lk_iterative_loop_int.h
 *
 *  @brief      This header defines internal structures for kernel that computes
 *              relative location within the fetched input block along with updated
 *              source pointers using the new X, Y coordinates into BAM. It also
 *              incorporates the iterative LK loop to compute the flow vectors
 */
#ifndef BAM_LK_ITERATIVE_LOOP_INT_H_
#define BAM_LK_ITERATIVE_LOOP_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_lk_iterative_loop.h"

#define NUM_IN_BLOCKS (7U)
#define NUM_OUT_BLOCKS (3U)
#define NUM_INTERNAL_BLOCKS (3U)

#define PARAMS_IDX   (0U)
#define SCRATCH_IDX1 (1U)
#define SCRATCH_NUM_INVALID_PTS_WBUF (2U)

#define SCRATCH_IDX1_SIZE (5120U)

#define IN_IDX1 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_CURRIMG        )
#define IN_IDX2 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_PREVINTERP     )
#define IN_IDX3 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADXINTERP    )
#define IN_IDX4 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADYINTERP    )
#define IN_IDX5 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_INVMAT         )
#define IN_IDX6 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_LASCRATCH      )
#define IN_IDX7 (BAM_LK_ITERATIVE_LOOP_INPUT_PORT_HASCRATCH      )


#define OUT_IDX1 (BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_CURRXY     )
#define OUT_IDX2 (BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_ERRMEASURE )
#define OUT_IDX3 (BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_INVALIDPTS)

#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)
#define VCOP_LK_PATCH_WIDTH          (7) /* 7x7*/

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_LK_Iterative_Loop_Args kernelArgs;
    BAM_LK_Iterative_Loop_CtrlArgs ctrlArgs;
    uint16_t           *pBlkWgtAddrUpdate;
    uint16_t           *pBlkCurrBiLin;
    uint16_t           *pBlkWgtAddrForErrMeas;
    uint16_t           *pBlkCurrBiLinForErrMeas;
    uint16_t           *pBlkCalcIxIt;
    uint16_t           *pBlkIterCalcNewXY;
    uint16_t           *pBlkCopyNewXY;
    uint16_t           *pBlkCalcSADErrMeasure;
    uint16_t  (*prevXYAdrs[2])[2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*currXYAdrs[2])[2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*localXYAdrs[2])[2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*localXAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t  (*localYAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint8_t   (*currValidPointsAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint32_t  (*pValidInAddrListAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint32_t  (*pValidOutAddrListAdrs[2])[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    volatile uint32_t   pBaseInAddrListLocal[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    volatile uint32_t   pBaseOutAddrListLocal[VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t            localXCb[2][VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint16_t            localYCb[2][VCOP_LK_MAX_NUM_KEY_PER_CALL];
    uint8_t             listInDMAContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
    uint16_t          * numValidPoints;
    uint16_t            currIdx;
} BAM_LK_Iterative_Loop_Context;

#endif /* BAM_LK_ITERATIVE_LOOP_INT_H_ */
