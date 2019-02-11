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

#ifndef VLIB_UPDATEUWRVARIANCES16_CN_H_
#define VLIB_UPDATEUWRVARIANCES16_CN_H_ 1

#include "../common/VLIB_types.h"

int32_t VLIB_updateUWRVarianceS16_cn(int16_t *restrict updatedVar,
                                     const int16_t *restrict previousVar,
                                     int16_t *restrict updatedMean,
                                     const int16_t *restrict previousMean,
                                     const uint8_t *restrict newestData,
                                     const uint32_t *restrict newestMask32packed,
                                     const uint32_t *restrict oldestMask32packed,
                                     const uint32_t pixelCount,
                                     const uint8_t frameCount);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_updateUWRVarianceS16_cn.h                            */
/* ======================================================================== */

