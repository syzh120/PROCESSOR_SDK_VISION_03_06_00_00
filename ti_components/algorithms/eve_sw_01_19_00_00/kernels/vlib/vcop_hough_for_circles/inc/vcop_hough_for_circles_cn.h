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

/*                                                                          */
/*  @file : vcop_hough_for_circle_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Hough Transform computation for circles.                   */
/*                                                                          */
/*  vcop_hough_circle_compute_idx_cn                                        */
/*      This is the c-reference for the vcop_hough_circle_compute_idx       */
/*      kernel. This routine computes the indexes in Hough Space into       */
/*      which the edge point specified by xyList votes for a particular     */
/*      radius.                                                             */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/* int32_t vcop_hough_circle_compute_idx_cn                                 */
/* (                                                                        */
/*   int16   *gradUnitVecXY,                                                */
/*   uint16  *xyList,                                                       */
/*   uint16  *houghSpaceIndex,                                              */
/*   uint16_t numEdgePoints,                                                */
/*   int8_t   radius,                                                       */
/*   uint8_t  downShift,                                                    */
/*   uint16_t houghSpaceWidth                                               */
/* )                                                                        */
/*                                                                          */
/*  gradUnitVecXY   : [in] List of unit gradient vectors packed as (GradX,  */
/*                    GradY) in Q1.8 format                                 */
/*  xyList          : [in] List of corresponding X,Y co-ordidnates in       */
/*                    packed format                                         */
/*  houghSpaceIndex : [out] Pointer to output hough space indices           */
/*  numEdgePoints   : Number of edge points for which gradient infomation   */
/*                    is provided                                           */
/*  radius          : Radius for which indexes in Hough Space need to be    */
/*                    computed                                              */
/*  downShift       : Downsampling factor in Hough space                    */
/*  houghSpaceWidth : Width of the output downsampled Hough space. It is    */
/*                    assumed that houghSpaceHeight <= houghSpaceWidth.     */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*  @version 0.1 (Sept 2014) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_HOUGH_FOR_CIRCLES_CN_H_
#define VCOP_HOUGH_FOR_CIRCLES_CN_H_

int32_t vcop_hough_circle_compute_idx_cn
(
  int16_t  *gradUnitVecXY,
  uint16_t *xyList,
  uint16_t *houghSpaceIndex,
  uint16_t  numEdgePoints,
  int8_t    radius,
  uint8_t   downShift,
  uint16_t  houghSpaceSaturateX,
  uint16_t  houghSpaceSaturateY,
  uint16_t  houghSpacePitch
);

int32_t vcop_hough_circle_vote_to_hough_space_cn
(
  uint16_t  *houghSpaceIndex,
  uint8_t   *houghSpacePtr,
  unsigned short numEdgePoints
);

int32_t vcop_hough_for_circle_detect_cn
(
  uint8_t  *houghSpacePtr,
  uint32_t *pUpperLeftXY,
  uint32_t *xSequence,
  uint16_t *pNumCircles,
  uint32_t *pCenterListXY,
  uint8_t  *pHoughScoreList,
  uint8_t   houghScoreThreshold,
  uint16_t  houghSpaceWidth,
  uint16_t  houghSpaceHeight,
  uint16_t  houghSpacePitch,
  uint8_t   houghSpaceShift
);

#endif /* VCOP_HOUGH_FOR_CIRCLES_CN_H_ */

