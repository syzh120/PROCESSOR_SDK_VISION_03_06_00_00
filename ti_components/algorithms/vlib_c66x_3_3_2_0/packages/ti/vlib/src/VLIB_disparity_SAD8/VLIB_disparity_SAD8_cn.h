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

#ifndef VLIB_DISPARITY_SAD8_CN_H_
#define VLIB_DISPARITY_SAD8_CN_H_ 1

int32_t VLIB_disparity_SAD8_cn(const uint8_t *restrict leftImage,
                               const uint8_t *restrict rightImage,
                               uint16_t *restrict currentCost,
                               uint16_t *restrict minCost,
                               int8_t *restrict disparity,
                               int32_t displacement,
                               uint32_t width,
                               int32_t pitch,
                               int32_t windowSize);



#endif

/* ======================================================================== */
/*  End of file:  VLIB_disparity_SAD8_cn.h                                  */
/* ======================================================================== */

