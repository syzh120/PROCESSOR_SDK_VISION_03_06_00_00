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

#ifndef VLIB_WEIGHTEDHISTOGRAM_1D_U16_CN_H_
#define VLIB_WEIGHTEDHISTOGRAM_1D_U16_CN_H_ 1

int32_t VLIB_weightedHistogram_1D_U16_cn(uint16_t *restrict X,
                                         const int32_t numX,
                                         const int32_t numBins,
                                         uint16_t *restrict binWeight,
                                         uint16_t *restrict histArray,
                                         uint16_t *restrict H1,
                                         uint16_t *restrict H);


#endif

/* ======================================================================== */
/*  End of file: VLIB_weightedHistogram_1D_U16_cn.h                         */
/* ======================================================================== */

