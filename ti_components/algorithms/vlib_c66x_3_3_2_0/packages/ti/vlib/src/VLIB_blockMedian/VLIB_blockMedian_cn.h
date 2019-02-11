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
**|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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

#ifndef VLIB_BLOCKMEDIAN_CN_H_
#define VLIB_BLOCKMEDIAN_CN_H_ 1


void VLIB_blockMedian_cn(const uint8_t  *restrict pInput,
                         uint8_t  *restrict pMedian,
                         uint16_t *restrict pScratch,
                         uint16_t imageWidth,
                         uint16_t imageHeight,
                         uint16_t imagePitch,
                         uint16_t blockWidth,
                         uint16_t blockHeight,
                         uint16_t stepSizeHorz,
                         uint16_t stepSizeVert);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_blockMedian_cn.h                                     */
/* ======================================================================== */

