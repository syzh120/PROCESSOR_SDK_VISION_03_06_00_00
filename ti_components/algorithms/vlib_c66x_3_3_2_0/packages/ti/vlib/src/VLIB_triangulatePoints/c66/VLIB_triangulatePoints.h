/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2007 - 2016 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_TRIANGULATEPOINT_H_
#define VLIB_TRIANGULATEPOINT_H_ 1

#include "../../common/VLIB_types.h"
#include "../VLIB_triangulatePoints_types.h"

/** @defgroup VLIB_triangulatePoints */
/** @ingroup  VLIB_triangulatePoints */
/* @{ */

/**
 *
 * @par Description:
 *   This API takes set of tracked 2D feature points from which 3D points are estimated using Hartley's
 *   Iterative LS method described in the paper reference provided below.
 *
 * @par
 *   @param [in]  curTrack[]      : Current track data after multiplying with inverse of intrinsic parameters.
 *                                  i.e. [x,y,1] = K<SUP>-1</SUP> * [x',y',1];
 *                                  Format of intrinsic parameter is [f<SUB>x</SUB> 0 x<SUB>0</SUB> 0 f<SUB>y</SUB> y<SUB>0</SUB> 0 0 1.0]. Where f<SUB>x</SUB> and f<SUB>y</SUB> are
 *                                  focal length parameters in x and y direction. Whereas(x<SUB>0</SUB>, y<SUB>0</SUB>) is the principal
 *                                  point , where optic axis intersects the image plane.
 *                                  Two track data are clubbed together. x/y-coordinates of two tracks are
 *                                  placed together. Lets assume two tracks are
 *                                  {(x<SUB>0</SUB>,y<SUB>0</SUB>),(x<SUB>1</SUB>,y<SUB>1</SUB>),(x<SUB>2</SUB>,y<SUB>2</SUB>),(x<SUB>3</SUB>,y<SUB>3</SUB>),(x<SUB>4</SUB>,y<SUB>4</SUB>),(x<SUB>5</SUB>,y<SUB>5</SUB>)} &
 *                                  {(u<SUB>0</SUB>,v<SUB>0</SUB>),(u<SUB>1</SUB>,v<SUB>1</SUB>),(u<SUB>2</SUB>,v<SUB>2</SUB>),(u<SUB>3</SUB>,v<SUB>3</SUB>),(u<SUB>4</SUB>,v<SUB>4</SUB>),(u<SUB>5</SUB>,v<SUB>5</SUB>)}.
 *                                  where (x<SUB>i</SUB>,y<SUB>i</SUB>) is the feature point location in i<SUP>th</SUP> frame for particular track. (u<SUB>i</SUB>,v<SUB>i</SUB>) is the feature
 *                                  point location in i<SUP>th</SUP> frame for another track. Expected format for curTrack
 *                                  is curTrack[] = {x<SUB>0</SUB>, u<SUB>0</SUB>, y<SUB>0</SUB>, v<SUB>0</SUB>, x<SUB>1</SUB>, u<SUB>1</SUB>, y<SUB>1</SUB>, v<SUB>1</SUB>, .. so on}. Here (x<SUB>0</SUB>,y<SUB>0</SUB>) or
 *                                  (u<SUB>0</SUB>,v<SUB>0</SUB>) is oldest location , whereas (x<SUB>1</SUB>,y<SUB>1</SUB>) or (u<SUB>1</SUB>,v<SUB>1</SUB>) is
 *                                  second oldest frame location, and so on. If any frame location is not available for
 *                                  a track then its corresponding place in \c curTrack is don't care. Maximum 6 frames
 *                                  locations are allowed in a given track. For a given track pair total length will be
 *                                  6*2*2 = 24. Hence second pair of track will be filled from curTrack[24] to curTrack[47]
 *                                  and so on.
 *
 *   @param [in]  camExtPrm      : Camera extrinsic parameters. Base format of camera extrinsic parameters is P = [ r00 r01 r02 t0 r10 r11 r12 t1 r20 r21 r22 t2],
 *                                 where rij are the rotation parameter, and ti are the translation parameters. Base camera
 *                                 extrinsic parameters are of size 12, but for optimization purpose it is asked as 20 elements with some
 *                                 of the elements repeated. Refer to implementation notes below. Maximum 6 frames can be considered for a 3D
 *                                 point estimation using triangulation. Oldest camera extrinsic parameter is placed at '0' index,
 *                                 and latest camera parameter is placed at index '5'.
 *
 *   @param [in]  curTrackLength : Array of values for each track lengths.
 *                                 E.g. If curTrackLength[i]=2, will triangulate using points (x<SUB>4</SUB>,y<SUB>4</SUB>) and (x<SUB>5</SUB>,y<SUB>5</SUB>) of
 *                                 track i with extrinsic parameters camExtPrm[4] and camExtPrm[5]. If curTrackLength[i]=6, will triangulate using points
 *                                 (x<SUB>0</SUB>,y<SUB>0</SUB>),(x<SUB>1</SUB>,y<SUB>1</SUB>),..., (x<SUB>5</SUB>,y<SUB>5</SUB>) of track i, and
 *                                 extrinsic parameters camExtPrm[0],...,camExtPrm[5].
 *
 *   @param [in]  maxIter       : Maximum iteration of triangulation as described in Iterative LS Method.
 *
 *   @param [out] Xcam          : 3-D output generated after triangulation API. Two 3D outputs are
 *                                clubbed together. X(or Y or Z) co-ordinates are clubbed together.
 *                                e.g X1X0Y1Y0Z1Z0X3X2Y3Y2Z3Z2....so on. Here [X0, Y0, Z0] is one 3D
 *                                point form one track, whereas [X1, Y1, Z1] is another 3D point output
 *                                from another track.
 *
 *   @param [in]  scratch       : Scratch area to be used, size of this scratch area is (N/2)*1540, where 'N'
 *                                = totalTracks if totalTracks is even or =totalTracks+1 if totalTracks is odd..
 *                                E.g. If \c totalTracks is 5, then total scratch required will be ((5+1)/2)*1540.
 *                                Similarly if \c totalTracks is 20 then total scratch requirement is
 *                                (20/2)*1540.
 *
 *   @param [in]  totalTracks   : Total number of tracks to be processed.
 *
 *   @param [out] validOut      : Output flag for each track, whether a solution was found or not. '1' indicates
 *                                a solution was found, whereas '0' indicates solution could not be found.
 *
 *   @param [in]  flag          : Flag to enable or disable high precision triangulation. '1' will enable high
 *                                precision triangulation.
 *
 * @par Implementation Notes:
 * - This code is implemented for floating point DSP processor e.g. C6600
 * - Recommended value of \c maxIter is 10. However lower value of it will reduce the cycle consumption without
 *   affecting the quality of output much.
 * - Camera extrinsic parameters \c camExtPrm are expected in specific format. Original camera extrinsic ('P')parameter is
 *   of size [3x4]. Expected camera extrinsic parameter here is of size [20]. Format for this is as
 *   {P(8),P(0),P(4),P(9),P(1),P(5),P(10),P(11),P(2),P(6),P(3),P(7),P(8),P(8),P(9),P(9),P(10),P(10),P(11),P(11)}.
 *   Some of the data elements in array is replicated to avoid few overheads inside kernel.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
*/

int32_t    VLIB_triangulatePoints(VLIB_F32 curTrack[restrict],
                                  VLIB_F32 camExtPrm[restrict],
                                  uint8_t curTrackLength[restrict],
                                  int32_t maxIter,
                                  VLIB_F32 Xcam[restrict],
                                  VLIB_F32 scratch[restrict],
                                  int32_t totalTracks,
                                  uint8_t validOut[restrict],
                                  uint32_t flag);

#endif /* VLIB_TRIANGULATEPOINT_H_ */
/** @} */

/* ======================================================================== */
/*  End of file:  VLIB_triangulatePoints.h                                  */
/* ======================================================================== */

