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
**|         Copyright (c) 2007-2016 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_FINDFUNDAMENTALMAT_H_
#define VLIB_FINDFUNDAMENTALMAT_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_findFundamentalMat */
/** @ingroup  VLIB_findFundamentalMat */
/* @{ */

/**
* @par Description:
*   This API finds the fundamental matrix, utilizing the list of matched
*   feature points. This method is based on 8 point algorithm of F matrix
*   estimation along with RANSAC.
*
* @par
*   @param [in]   pts1r    : (x,y) packed key points locations list from one frame.
*   @param [in]   pts2r    : (x,y) packed key points locations list from another frame.
*   @param [in]   numfeatures    : number of feature point in list \c pts1r & \c pts2r.
*   @param [in]   distThreshold  : Threshold in terms of pixel distance from epipolar
*                                  line to determine a feature point as inlier or
*                                  out lier.
*   @param [in]   degenThreshold : Threshold in terms of pixel distance between a point and the line
*                                  formed by any other two points, to decided all these three points
*                                  are co linear or not.
*   @param [in]   numItr4RANSAC  : Total number of RANSC iteration to be done.
*   @param [in]   method         : Bit field flag to choose a algorithm. Default value '7'
*   @param [out]  fFinal         : Total Nine elements of F matrix as output
*   @param [out]  numInliers     : Total number of inliers
*   @param [out]  inOrOutLier    : Flag for each correspondence point, '1' indicates outlier, '0' indicates inlier.
*   @param [in]   scratch1       : Scratch memory of size 2520 bytes. This is mandatory scratch buffer.
*   @param [in]   scratch2       : Scratch memory of size 9* \c numfeatures bytes. Required only when RANSAC is enabled.
*   @param [in]   scratch3       : Scratch memory of size 52* \c numfeatures bytes. Required only when least square solution is requested.
*
* @par Assumptions:
*    -   NA
*
* @par Implementation Notes:
*    -   Output fundamental matrix \c fFinal satisfies pts2r<SUP>T</SUP> * fFinal * pts1r = 0.
*    -   Output \c fFinal is in row major form. fFinal[0],fFinal[1],fFinal[2] is the first row of fundamental matrix.
*    -   If \c numItr4RANSAC is set to 0x7FFFFFFF, then algorithm decides maximum number of iteration.
*    -   List \c pts1, \c pts2 is one to one mapped. I.e. pts1[i] matching point is pts2[i].
*    -   Field \c method is bit packed information to algorithm.
*    -   In field \c method, if bit '0' is 1 then 8-Point algorithm is chosen, otherwise 7 point algorithm is chosen. Currently 7 point algorithm is not supported.
*    -   In field \c method, if bit '1' is 1 then RANSAC solution is found, otherwise single iteration is done. In RANSAC disabled case first 8 or 7 points from both list is chosen.
*    -   In field \c method  if bit '2' is '1' then at last least square solution for all the input points is found.
*    -   In field \c method  if bit '3' is '1' then rank (of 2) enforcement is done (by setting smallest eigen value to zero) on final solution otherwise it is not done.
*    -   In field \c method  if bit '4' is '1' and bit '3' is '1' then along with setting smallest eigen value zero, other two eigen values are set to the average of those two non zero eigne values.
*    -   In field \c method  if bit '5' is '1' then SVD is used for matrix solution otherwise reverse power iteration is used. Currently SVD based matrix solution is not supported.
*    -   Recommended value for \c method is 7.
*    -   If \c degenThreshold is provided as FLT_MAX then no degeneracy check is performed.
*    -   \c scratch1 in internal memory will improve the cycle consumption.
*/
int32_t    VLIB_findFundamentalMat(VLIB_F32 pts1r[restrict],
                                   VLIB_F32 pts2r[restrict],
                                   int16_t numfeatures,
                                   VLIB_F32 distThreshold,
                                   VLIB_F32 degenThreshold,
                                   int32_t numItr4RANSAC,
                                   int32_t method,
                                   VLIB_F32 fFinal[restrict],
                                   int16_t   * numInliers,
                                   uint8_t   * inOrOutLier,
                                   uint8_t   * scratch1,
                                   uint8_t   * scratch2,
                                   uint8_t   * scratch3);

/** @} */

#endif
/* ======================================================================== */
/*  End of file:  VLIB_findFundamentalMat.h                                 */
/* ======================================================================== */

