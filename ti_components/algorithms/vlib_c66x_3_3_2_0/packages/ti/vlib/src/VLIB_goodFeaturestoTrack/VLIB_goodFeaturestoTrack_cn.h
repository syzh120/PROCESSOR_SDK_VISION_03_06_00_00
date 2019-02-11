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
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
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

#ifndef VLIB_GOODFEATURESTOTRACK_CN_H_
#define VLIB_GOODFEATURESTOTRACK_CN_H_ 1

#include "../common/VLIB_types.h"

/** @ingroup  VLIB_goodFeaturestoTrack */
/* @{ */

/**
* @par
* @param   im          :  16-bit input image
*  @param   out         :  8-bit binary output image
*  @param width       :  Width of the input image
*  @param height      :  Height of the input image
*  @param thresh      :  NONMAX-SUPR Threshold for pruning peaks
*  @param patch       :  Size of neighborhood for each corner point
*  @param qualitypar  :  Quality threshold to keep stronger points
*  @param topNfeatures:  Number of output top stronger points
*  @param  mindist     :  Min. distance without two points(spatial diversity)
*  @param  outTemp     :  Auxiliar buffer for intermediate operations
*  @param  good_points_number: number of points resulting
*  in case not enough to guarantee topNfeatures
*/
void    VLIB_goodFeaturestoTrack_cn
(
    const uint16_t im [],
    uint8_t out[],
    int32_t width,
    int32_t height,
    int16_t thresh,
    uint8_t patch,
    uint8_t qualitypar,
    int16_t topNfeatures,
    uint8_t mindist,
    uint16_t outTemp[],
    int32_t * good_points_number,
    int16_t pixIndex_gft_cn[],
    uint16_t internalBuf_cn[],
    int32_t ind_cn[]
);

#endif /* VLIB_GOODFEATURESTOTRACK_CN_H_ */

/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_goodFeaturestoTrack_cn.h                             */
/* ======================================================================== */

