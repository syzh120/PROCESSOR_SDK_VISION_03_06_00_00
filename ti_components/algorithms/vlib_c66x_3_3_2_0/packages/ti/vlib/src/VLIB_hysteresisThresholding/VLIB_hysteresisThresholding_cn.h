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

#ifndef VLIB_HYSTERESISTHRESHOLDING_CN_H_
#define VLIB_HYSTERESISTHRESHOLDING_CN_H_ 1

#include "../common/VLIB_types.h"

int32_t VLIB_hysteresisThresholding_cn(int16_t *restrict pInMagBlk,
                                       uint8_t *edgeMap,
                                       uint8_t *restrict scratch4,
                                       uint16_t blkHeight,
                                       uint16_t blkWidth,
                                       uint16_t blkPitch,
                                       uint8_t loThresh,
                                       uint8_t hiThreshold);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_hysteresisThresholding_cn.h                          */
/* ======================================================================== */

