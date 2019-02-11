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

#ifndef VLIB_CONVERT_NV12_TO_RGBPL_TILE_CN_H_
#define VLIB_CONVERT_NV12_TO_RGBPL_TILE_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_tiler.h"

/** @defgroup VLIB_convert_NV12_to_RGBpl_tile_cn */
/** @ingroup  VLIB_convert_NV12_to_RGBpl_tile_cn */
/* @{ */

/**
 * @par Description:
 *   This function transforms the NV12 color format data into the RGB format and separates
 *   the three color channels into separate buffers, color planes.
 * @par
 *   The matrix coefficients specified by the array coeff are typically as shown in
 *   Equation (a) for the case of RGB levels that correspond the 219-level range
 *   of Y. Expected ranges are [16..235] for Y and [16..240] for Cb and Cr.
 *   - coeff[] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 }; (a)
 *
 * @par
 *   @param [in]   *yData      Interleaved luma/chroma                    (UQ8.0)
 *   @param [in]   *cbcrData   Interleaved CbCr data                      (UQ8.0)
 *   @param [in]    coeff      Matrix coefficients                        (SQ15.0)
 *   @param [out]  *rgbData    Base pointer to R, G and B plane (8-bit)   (UQ8.0)
 *
 * @par Algorithm:
 *   VLIB_convert_NV12_to_RGBpl_tile_cn.c is the natural C equivalent of the optimized
 *   intrinsics code.
 *
 * @par Assumptions
 *  - All arrays should be 8-byte aligned.
 *
 * @par References:
 *  -# <em> Digital Image Processing </em> by R.C.Gonzales and R.E.Woods, Prentice-Hall, 2007
 *
 */

int32_t VLIB_convert_NV12_to_RGBpl_tile_cn(sBuffer_t *yData,
                                           sBuffer_t *cbcrData,
                                           const int16_t coeff[5],
                                           sBuffer_t *rgbData);

/** @} */

#endif /* VLIB_CONVERT_NV12_TO_RGBPL_TILE_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_convert_NV12_to_RGBpl_tile_cn.h                      */
/* ======================================================================== */

