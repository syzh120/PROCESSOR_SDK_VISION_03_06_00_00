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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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
#ifndef VLIB_RELU_MAXPOOLING_2x2_SKIP2_TILE_CN_H_
#define VLIB_RELU_MAXPOOLING_2x2_SKIP2_TILE_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_tiler.h"

/** @defgroup VLIB_ReLU_MaxPooling_2x2_skip2_tile_cn */
/** @ingroup  VLIB_ReLU_MaxPooling_2x2_skip2_tile_cn */
/* @{ */

/**
 * @par Description:
 *  Performs 2x2 ReLU and MaxPooling operations on N 32-bit input channels producing N 32-bit
 *  output channels.<BR>
 *
 *  After maxpooling operation, each W x H 32-bit inputs of a single input channel are skipped
 *  in alternate horizontal and vertical pixels, to produce one (W/2) x (H/2) 32-bit outputs.
 *  It is then fed to ReLU operation to remove negative values. This output is then rounded and
 *  shifted down to a 16-bit range prior to storing in the output array.
 *
 * @par
 *   @param [in]      *pInChannel       Pointer to N 32-bit input channels
 *   @param [out]     *pOutChannel      Pointer to N 16-bit ouput channels
 *   @param [in]      *shiftQ           Q-factor to adjust shift value to get output in required range
 *   @param [in]      *coeffQ           Q-factor to adjust Coefficient value
 *
 * @par Algorithm:
 * VLIB_ReLU_MaxPooling_2x2_skip2_tile_cn.c is the natural C equivalent of the optimized
 * intrinsics code.
 *
 * @par Assumptions:
 *   All buffer starting and each line starting addresses of input/output/weights
 *   are assumed to be aligned to 8-bytes.
 *
 * @par Implementation Notes:
 *      The code is interruptible. <BR>
 *
 */

void VLIB_ReLU_MaxPooling_2x2_skip2_tile_cn(sBuffer_t *pInChannel,
                                            sBuffer_t *pOutChannel,
                                            uint32_t shiftQ,
                                            uint32_t coeffQ);
/** @} */

#endif /* VLIB_RELU_MAXPOOLING_2x2_SKIP2_TILE_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_ReLU_MaxPooling_2x2_skip2_tile_cn.h                  */
/* ======================================================================== */

