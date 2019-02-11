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

#ifndef VLIB_KALMANFILTER1X2_CORRECT_F32_CN_H_
#define VLIB_KALMANFILTER1X2_CORRECT_F32_CN_H_ 1

#include "../common/VLIB_kalmanFilter.h"

/** @defgroup VLIB_kalmanFilter_1x2_Correct_F32_cn */
/** @ingroup  VLIB_kalmanFilter_1x2_Correct_F32_cn */
/* @{ */

/**
 * @par Description:
 *  The function VLIB_kalmanFilter_1x2_Correct_F32_cn() .
 *
 * @par
 *  @param [in,out]  *KF        Pointer to struct VLIB_kalmanFilter_1x2_Correct_F32
 *  @param [in]      *Z         Pointer to array (dimension 4x1) containing measurement
 *  @param [out]     *Residual  Pointer to array to store the residual error
 *
 */

void VLIB_kalmanFilter_1x2_Correct_F32_cn(VLIB_kalmanFilter_1x2_F32 *KF,
                                          const VLIB_F32 *restrict Z,
                                          VLIB_F32 *restrict Residual);
/** @} */

#endif /* VLIB_KALMANFILTER1X2_CORRECT_F32_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_1x2_Correct_F32_cn.h                    */
/* ======================================================================== */

