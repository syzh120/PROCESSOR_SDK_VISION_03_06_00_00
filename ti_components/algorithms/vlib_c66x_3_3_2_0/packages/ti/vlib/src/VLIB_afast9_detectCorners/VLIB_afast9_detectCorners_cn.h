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
**|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
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

#ifndef VLIB_AFAST9_DETECTCORNERS_CN_H_
#define VLIB_AFAST9_DETECTCORNERS_CN_H_ 1

#include "../common/VLIB_types.h"

int32_t VLIB_afast9_detectCorners_cn(const uint8_t *image,
                                     uint16_t width,
                                     uint16_t height,
                                     uint32_t pitch,
                                     uint8_t differenceThreshold,
                                     uint16_t *features,
                                     uint8_t *scratchBuffer);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_afast9_detectCorners_cn.h                            */
/* ======================================================================== */

