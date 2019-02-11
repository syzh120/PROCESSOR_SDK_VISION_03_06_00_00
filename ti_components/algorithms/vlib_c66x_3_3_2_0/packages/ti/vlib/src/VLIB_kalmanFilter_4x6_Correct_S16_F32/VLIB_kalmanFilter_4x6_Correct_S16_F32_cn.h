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

#ifndef VLIB_KALMANFILTER4X6_CORRECT_S16_F32_CN_H_
#define VLIB_KALMANFILTER4X6_CORRECT_S16_F32_CN_H_ 1

#include "../common/VLIB_kalmanFilter.h"

void VLIB_kalmanFilter_4x6_Correct_S16_F32_cn(VLIB_kalmanFilter_4x6_S16_F32 *KF,
                                              const int16_t *restrict Z,
                                              VLIB_F32 *restrict Residual);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x6_Correct_S16_F32_cn.h                */
/* ======================================================================== */

