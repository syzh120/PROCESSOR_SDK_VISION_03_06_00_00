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
 *  @file       bam_multipoint_harrisScore_u16.h
 *
 *  @brief      This header defines interfaces for integrating multi-point
 *              16-bit Harris score kernel into BAM.
 */

#ifndef BAM_MULTIPOINT_HARRIS_SCORE_H_
#define BAM_MULTIPOINT_HARRIS_SCORE_H_

#define SPARSE_HARRIS_SCORE_TI_NUMPOINTSPERBLOCK (32)
#define SPARSE_HARRIS_SCORE_TI_BLKSTRIDE         (9)
#define SPARSE_HARRIS_SCORE_TI_BLKHEIGHT         (9)
#define SPARSE_HARRIS_SCORE_TI_INTERBLKOFFSET    ((SPARSE_HARRIS_SCORE_TI_BLKSTRIDE)*(SPARSE_HARRIS_SCORE_TI_BLKHEIGHT))

typedef struct
{
  uint8_t  level ;
  uint8_t  firstTimeFlag ;
  uint16_t numTotalPointsInThisLevel;
} BAM_Multipoint_Harris_Score_InArgs;

typedef struct bam_multipoint_harris_score_args
{
    uint16_t  numPoints;
    uint16_t  totalNumPoints;
    uint16_t  inputStride;
    uint16_t  interBlockOffset;
    uint16_t  sensitivityParam;
    int16_t   start_idx;
    uint32_t *pOutScoreBuffer;
} BAM_Multipoint_Harris_Score_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_multipointHarrisScoreHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_multipointHarrisScoreExecFunc;

extern BAM_KernelInfo gBAM_TI_multipointHarrisScoreKernel;

typedef enum
{
 BAM_MULTIPOINT_HARRIS_SCORE_INPUT_PORT_IMG   =    0,
 BAM_MULTIPOINT_HARRIS_SCORE_INPUT_PORT_INARGS ,
 BAM_MULTIPOINT_HARRIS_SCORE_NUM_INPUT_BLOCKS
} eBAM_MULTIPOINT_HARRIS_INPUT_PORTS ;

typedef enum
{
 BAM_MULTIPOINT_HARRIS_SCORE_OUTPUT_PORT   =    0,
 BAM_MULTIPOINT_HARRIS_SCORE_NUM_OUTPUT_BLOCKS
} eBAM_MULTIPOINT_HARRIS_OUTPUT_PORTS ;

#endif /* BAM_MULTIPOINT_HARRIS_SCORE_H_ */

