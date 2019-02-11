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

#ifndef VLIB_IMAGE_RESCALE_CN_H_
#define VLIB_IMAGE_RESCALE_CN_H_ 1

#include "../common/VLIB_types.h"
#include "VLIB_image_rescale_types.h"

void VLIB_luma_rescale(uint8_t *pIn,
                       uint16_t inRows,
                       uint16_t inCols,
                       uint8_t *pOut);

void VLIB_chroma_rescale(uint8_t *pIn,
                         uint16_t inRows,
                         uint16_t inCols,
                         uint8_t *pOut);

void VLIB_interleave_rescale(uint8_t *pout_y,
                             uint8_t *pout_uv,
                             uint16_t inRows,
                             uint16_t inCols,
                             uint8_t *pout_int);

void VLIB_deinterleave_rescale(uint8_t *pIn,
                               uint8_t *luma_comp,
                               uint8_t *chroma_comp,
                               uint16_t width, uint16_t height);

void VLIB_image_rescale_cn(uint8_t *pIn,
                           uint8_t *pOut,
                           uint16_t nFactor,
                           uint16_t width,
                           uint16_t height,
                           int32_t color_format);
#endif /* VLIB_IMAGE_RESCALE_CN_H_ */

/* ======================================================================== */
/*  End of file:  vlib_image_rescale_cn.h                                   */
/* ======================================================================== */

