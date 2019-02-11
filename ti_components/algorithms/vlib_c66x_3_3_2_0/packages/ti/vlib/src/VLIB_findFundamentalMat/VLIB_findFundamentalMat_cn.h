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

#ifndef VLIB_FINDFUNDAMENTALMAT_CN_H_
#define VLIB_FINDFUNDAMENTALMAT_CN_H_ 1

int32_t    VLIB_findFundamentalMat_cn(VLIB_F32 pts1r[],
                                      VLIB_F32 pts2r[],
                                      int16_t numfeatures,
                                      VLIB_F32 distThreshold,
                                      VLIB_F32 degenThreshold,
                                      int32_t numItr4RANSAC,
                                      int32_t method,
                                      VLIB_F32 fFinal[],
                                      int16_t  * numInliers,
                                      uint8_t  * inOrOutLier,
                                      uint8_t  * scratch1,
                                      uint8_t  * scratch2,
                                      uint8_t  * scratch3);
#endif
/* ======================================================================== */
/*  End of file:  VLIB_findFundamentalMat_cn.h                    */
/* ======================================================================== */

