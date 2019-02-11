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

/*==========================================================================*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_lk_iterative_loop.h
 *
 *  @brief      This header defines interfaces for integrating kernel that computes
 *              relative location within the fetched input block along with updated
 *              source pointers using the new X, Y coordinates into BAM. It also
 *              incorporates the iterative LK loop to compute the flow vectors
 */

#ifndef BAM_LK_ITERATIVE_LOOP_H_
#define BAM_LK_ITERATIVE_LOOP_H_

#include "bam_pyramid_lk_tracker_dma_node.h"

typedef struct
{
  uint16_t numKeyPointsPerCall;
  uint16_t keyPointsProcessedCnt;
  uint16_t *prevXYList;
  uint16_t *currXYList;
  uint16_t numKeyPoints;
  uint16_t  currBlkWidth;
  uint16_t  currBlkHeight;
  EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs;
} BAM_LK_Iterative_Loop_Args;

typedef struct
{
  uint16_t SADthreshold;
} BAM_LK_Iterative_Loop_CtrlArgs;


extern BAM_KernelHelperFuncDef gBAM_TI_lkIterativeLoopHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_lkIterativeLoopExecFunc;

extern BAM_KernelInfo gBAM_TI_lkIterativeLoopKernel;

/*Input port comes from the DMA node outputdatablock which allocates memory for */
/*holding pointers of current frame, previous frame along with scratch memories */
/*required by the iterative LK loop in IBUFLA and IBUFHA buffers                */
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_CURRIMG        (0)
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_PREVINTERP     (1)
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADXINTERP    (2)
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_GRADYINTERP    (3)
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_INVMAT         (4)
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_LASCRATCH      (5)
#define BAM_LK_ITERATIVE_LOOP_INPUT_PORT_HASCRATCH      (6)

#define BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_CURRXY        (0)
#define BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_ERRMEASURE    (1)
#define BAM_LK_ITERATIVE_LOOP_OUTPUT_PORT_INVALIDPTS    (2)

#define NUM_POINTS_IN_DMEM (96U)
#define NUM_POINT_BUFFS_IN_DMEM (2U)

#endif /* BAM_LK_ITERATIVE_LOOP_H_ */
