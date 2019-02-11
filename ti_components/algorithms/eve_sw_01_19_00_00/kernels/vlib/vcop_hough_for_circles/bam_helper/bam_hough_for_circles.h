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
 *  @file       bam_hough_for_circles.h
 *
 *  @brief      This header defines interfaces for integrating hough for
 *              circles into BAM.
 */

#ifndef BAM_HOUGH_FOR_CIRCLES_H_
#define BAM_HOUGH_FOR_CIRCLES_H_

#include "bam_common.h"

#define BAM_HOUGH_FOR_CIRCLES_MAX_NUM_RADIUS   (32U)

/* For Compute Hough Space index BAM node */

typedef struct
{
  uint16_t maxNumEdgePoints;
  uint8_t  circleType;
  uint8_t  houghSpaceDownShift;
} BAM_HoughForCircles_Args;

typedef struct
{
  uint8_t  numRadius;
  int8_t  radius[BAM_HOUGH_FOR_CIRCLES_MAX_NUM_RADIUS];
  uint16_t houghSpaceSaturateX;
  uint16_t houghSpaceSaturateY;
  uint16_t houghSpacePitch;
} BAM_HoughForCircles_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_houghForCirclesHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_houghForCirclesExecFunc;

extern BAM_KernelInfo gBAM_TI_houghForCirclesKernel;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_NORM_GRAD_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_XY_LIST_PORT,
  BAM_HOUGH_FOR_CIRCLES_XY_LIST_SIZE_WBUF_PORT,
  BAM_HOUGH_FOR_CIRCLES_NUM_INPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_INPUT_PORTS;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_HOUGH_IDX_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_NUM_OUTPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_OUTPUT_PORTS;

/* For Circle Detect BAM node */

typedef struct
{
  uint16_t numElemsPerBlock;
  uint16_t maxHoughSpacePitch;
  uint16_t maxHoughSpaceHeight;
} BAM_HoughForCirclesDetect_Args;

typedef struct
{
  uint8_t  maxRadius;
  uint32_t numEdgePoints;
  uint16_t numEdgePointsChunk;
  uint8_t  houghScoreThreshold;
  uint16_t houghSpaceWidth;
  uint16_t houghSpaceHeight;
  uint16_t houghSpacePitch;
  uint8_t  houghSpaceShift;
  uint16_t startX;/* In terms of non scaled coordinates */
  uint16_t startY;/* In terms of non scaled coordinates */
} BAM_HoughForCirclesDetect_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_houghForCirclesDetectHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_houghForCirclesDetectExecFunc;

extern BAM_KernelInfo gBAM_TI_houghForCirclesDetectKernel;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_IDX_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_INPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_DETECT_INPUT_PORTS;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_DETECT_CENTER_XY_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_SCORE_PORT,
  BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_CIRCLES_PORT,
  BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_OUTPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_DETECT_OUTPUT_PORTS;

#endif /* BAM_HOUGH_FOR_CIRCLES_H_ */

