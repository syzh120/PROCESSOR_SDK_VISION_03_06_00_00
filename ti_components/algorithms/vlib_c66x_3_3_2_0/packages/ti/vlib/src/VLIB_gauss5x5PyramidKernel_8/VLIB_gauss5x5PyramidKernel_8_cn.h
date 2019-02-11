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

#ifndef VLIB_GAUSS5X5PYRAMIDKERNEL_8_CN_H_
#define VLIB_GAUSS5X5PYRAMIDKERNEL_8_CN_H_ 1

uint8_t VLIB_gauss5x5PyramidKernel_8_cn(uint8_t *restrict pIn,
                                        uint16_t *restrict pB,
                                        uint16_t width,
                                        uint16_t pitch,
                                        uint16_t height,
                                        uint8_t *restrict pOut);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_gauss5x5PyramidKernel_8_cn.h                         */
/* ======================================================================== */

