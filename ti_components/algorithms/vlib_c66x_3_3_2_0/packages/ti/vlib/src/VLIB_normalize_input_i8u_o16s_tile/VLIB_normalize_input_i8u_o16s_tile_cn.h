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
#ifndef VLIB_NORMALIZE_INPUT_I8U_O16S_TILE_CN_H_
#define VLIB_NORMALIZE_INPUT_I8U_O16S_TILE_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_tiler.h"

/** @defgroup VLIB_normalize_input_i8u_o16s_tile_cn */
/** @ingroup  VLIB_normalize_input_i8u_o16s_tile_cn */
/* @{ */

/**
 * @par Description:
 *  Performs normalization of N 8-bit inputs channels with bias producing N 16-bit outputs
 *  channels.
 *
 *  Each W x H 8-bit inputs in an input channel produce W x H 16-bit outputs.
 *
 * @par
 *   @param [in]   *pInChannel   Pointer to N 8-bit input channels
 *   @param [out]  *pOutChannel  Pointer to N 16-bit ouput channels
 *   @param [in]   bias          bias value
 *   @param [in]   shift         Shift value to adjust output to 16 bit
 *
 * @par Algorithm:
 * VLIB_normalize_input_i8u_o16s_tile_cn.c is the natural C equivalent of the optimized
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

void VLIB_normalize_input_i8u_o16s_tile_cn(sBuffer_t *pInChannel,
                                           sBuffer_t *pOutChannel,
                                           int16_t bias,
                                           uint8_t shift);
/** @} */

#endif /* VLIB_NORMALIZE_INPUT_I8U_O16S_TILE_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_normalize_input_i8u_o16s_tile_cn.h              */
/* ======================================================================== */

