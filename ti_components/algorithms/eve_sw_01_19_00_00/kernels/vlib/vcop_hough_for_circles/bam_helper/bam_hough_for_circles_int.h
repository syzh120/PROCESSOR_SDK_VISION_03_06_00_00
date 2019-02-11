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
 *  @file       bam_hough_for_circles_int.h
 *
 *  @brief      This header defines internal structures for Hough for
 *              circles kernel.
 */

#ifndef BAM_HOUGH_FOR_CIRCLES_INT_H_
#define BAM_HOUGH_FOR_CIRCLES_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_hough_for_circles.h"

/* For Compute Hough Space index BAM node */

typedef enum
{
  HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX = 0,
  HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX,
  HOUGH_FOR_CIRCLES_INTERNAL_RADIUS_PTR_IDX,
  HOUGH_FOR_CIRCLES_INTERNAL_NUM_BLOCK
} eBAM_HOUGH_FOR_CIRCLES_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_HOUGH_FOR_CIRCLES_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_HOUGH_FOR_CIRCLES_NUM_OUTPUT_BLOCKS];
    BAM_HoughForCircles_Args kernelInitArgs;
    BAM_HoughForCircles_CtrlArgs kernelCtrlArgs;
    uint16_t * paramBlockUpdatePblock;
    int8_t * currentRadiusPtr[2];/* Need two buffers to store Ping Pong Addresses */
    uint8_t radIdx;
    uint8_t pingPongFlag;
} BAM_HoughForCircles_Context;


/* For Circle Detect BAM node */

typedef enum
{
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_PARAMS_IDX = 0,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_NUM_BLOCK
} eBAM_HOUGH_FOR_CIRCLES_DETECT_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_OUTPUT_BLOCKS];
    BAM_HoughForCirclesDetect_Args kernelInitArgs;
    BAM_HoughForCirclesDetect_CtrlArgs kernelCtrlArgs;
    uint16_t *pBlockHoughSpaceInit;
    uint16_t *pBlockHoughSpaceVote;
    uint16_t *pBlockCircleDetect;
    uint16_t *pBlockHoughSpaceVoteUpdateParams;
    uint8_t numBlks;
    uint16_t numElemsInLastBlk;
    uint8_t blkIdx;
    uint8_t pingPongFlag;
} BAM_HoughForCirclesDetect_Context;

#endif /* BAM_HOUGH_FOR_CIRCLES_INT_H_*/
