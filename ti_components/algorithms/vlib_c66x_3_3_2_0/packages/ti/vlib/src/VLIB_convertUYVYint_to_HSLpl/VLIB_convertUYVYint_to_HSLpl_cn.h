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

#ifndef VLIB_CONVERTUYVYINT_TO_HSLPL_CN_H_
#define VLIB_CONVERTUYVYINT_TO_HSLPL_CN_H_ 1
/** @defgroup VLIB_convertUYVYint_to_HSLpl_cn */
/** @ingroup  VLIB_convertUYVYint_to_HSLpl_cn */
/* @{ */

/**
* @par
* @param  *yc    Interleaved luma/chroma (UQ8.0)
*  @param  width    Width of input image (number of luma pixels) (in pixels)
*  @param pitch  Pitch of input image (number of luma pixels) (in pixels)
*  @param height  Height of input image(number of luma pixels) (in pixels)
* @param coeff  Matrix coefficients (SQ16.0)
* @param div_table Division table (UQ16.0)
* @param *H   Pointer to H plane (8-bit) (UQ8.0)
* @param *S   Pointer to S plane (8-bit) (UQ8.0)
* @param *L   Pointer to L plane (8-bit) (UQ8.0)
* @par Benchmarks:
*  See VLIB_Test_Report.html for cycle and memory information.
*
*/
int32_t VLIB_convertUYVYint_to_HSLpl_cn(const uint8_t *yc,        /* Interleaved luma/chroma          */
                                        uint32_t width, /* width (number of luma pixels)    */
                                        int32_t pitch,
                                        uint32_t height,
                                        const int16_t coeff[5], /* Matrix coefficients  */
                                        const uint16_t div_table[510],
                                        uint16_t *restrict H, /* pointer to H plane   */
                                        uint8_t  *restrict S, /* pointer to S plane   */
                                        uint8_t  *restrict L /* pointer to L plane   */
                                        );


#endif

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_HSLpl_cn.h                         */
/* ======================================================================== */

