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

#ifndef VLIB_UPDATEEWRVARIANCES32_CN_H_
#define VLIB_UPDATEEWRVARIANCES32_CN_H_ 1

#include "../common/VLIB_types.h"

int32_t VLIB_updateEWRVarianceS32_cn(int32_t *restrict runningVar,
                                     const int32_t *restrict runningMean,
                                     const uint8_t *restrict newLuma,
                                     const uint32_t *restrict mask32packed,
                                     const int32_t weight,
                                     const uint32_t pixelCount);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_updateEWRVarianceS32_cn.h                            */
/* ======================================================================== */

