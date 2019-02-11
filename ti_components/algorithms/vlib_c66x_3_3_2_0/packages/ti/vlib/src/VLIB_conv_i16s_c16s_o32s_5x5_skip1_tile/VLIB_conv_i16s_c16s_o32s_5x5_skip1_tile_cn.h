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
#ifndef VLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_TILE_CN_H_
#define VLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_TILE_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_tiler.h"

/** @defgroup VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn */
/** @ingroup  VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn */
/* @{ */

/**
 * @par Description:
 *  Performs 5x5 convolution of N 16-bit inputs with N x M 16-bit weights producing M
 *  32-bit outputs.<BR>
 *  Each W x H 16-bit inputs are convolved with corresponding K x K 16bit weights
 *  and accumulated N times to produce one (W - K) + 1 x (H - K) + 1 32-bit output.
 *  This output is then rounded and shifted down to a 32-bit range prior to storing
 *  in the output array. This process is repeated for M outputs.
 *
 * @par
 *   @param [in]      *pInChannel       Pointer to N 16-bit input channels
 *   @param [in]      *pWeights         Pointer to N x M 16-bit weights
 *   @param [in]      *pBias            Pointer to M 16-bit bias values
 *   @param [out]     *pOutChannel      Pointer to M 32-bit ouput channels
 *   @param [in]      *shiftQ           Q-factor to adjust shift value to get output in required range
 *   @param [in]      *coeffQ           Q-factor to adjust Coefficient value
 *
 * @par Algorithm:
 * VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn.c is the natural C equivalent of the optimized
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

void VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn(sBuffer_t *pInChannel,
                                                sBuffer_t *pWeights,
                                                sBuffer_t *pBias,
                                                sBuffer_t *pOutChannel,
                                                uint32_t shiftQ,
                                                uint32_t coeffQ);

/** @} */

#endif /* VLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_TILE_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn.h              */
/* ======================================================================== */

