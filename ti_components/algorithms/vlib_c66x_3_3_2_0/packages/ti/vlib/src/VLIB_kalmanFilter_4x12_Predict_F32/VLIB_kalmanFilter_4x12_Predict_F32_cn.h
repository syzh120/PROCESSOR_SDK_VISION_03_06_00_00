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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#ifndef VLIB_KALMANFILTER4X12_PREDICT_F32_CN_H_
#define VLIB_KALMANFILTER4X12_PREDICT_F32_CN_H_ 1

#include "../common/VLIB_kalmanFilter.h"

/** @defgroup VLIB_kalmanFilter_4x12_Predict_F32_cn */
/** @ingroup  VLIB_kalmanFilter_4x12_Predict_F32_cn */
/* @{ */

/**
 * @par Description:
 *  The function VLIB_kalmanFilter_4x12_Predict_F32_cn() .
 *
 * @par
 *    @param    *KF    Input    Pointer to struct VLIB_kalmanFilter_4x12_F32
 *
 */

void VLIB_kalmanFilter_4x12_Predict_F32_cn(VLIB_kalmanFilter_4x12_F32 *KF);

/** @} */

#endif /* VLIB_KALMANFILTER4X12_PREDICT_F32_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x12_Predict_F32_cn.h                   */
/* ======================================================================== */

