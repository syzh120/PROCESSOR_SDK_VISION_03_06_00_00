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

#ifndef VLIB_KALMANFILTER4X6_PREDICT_S16_F32_CN_H_
#define VLIB_KALMANFILTER4X6_PREDICT_S16_F32_CN_H_ 1

#include "../common/VLIB_kalmanFilter.h"

/** @defgroup VLIB_kalmanFilter_4x6_Predict_S16_F32 */
/** @ingroup  VLIB_kalmanFilter_4x6_Predict_S16_F32 */
/* @{ */

/**
 * @par Description:
 *  The function VLIB_kalmanFilter_4x6_Predict_S16_F32() .
 *
 * @par
 *    @param    *KF            Input    Pointer to struct VLIB_kalmanFilter_4x6_Predict_S16_F32
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

void VLIB_kalmanFilter_4x6_Predict_S16_F32_cn(VLIB_kalmanFilter_4x6_S16_F32 *KF);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x6_Predict_S16_F32_cn.h                */
/* ======================================================================== */

