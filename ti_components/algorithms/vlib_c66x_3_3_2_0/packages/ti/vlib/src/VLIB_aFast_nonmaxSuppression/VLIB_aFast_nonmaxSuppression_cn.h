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

#ifndef VLIB_AFAST_NONMAXSUPPRESSION_CN_H_
#define VLIB_AFAST_NONMAXSUPPRESSION_CN_H_ 1

#include "../common/VLIB_types.h"
#include "../common/VLIB_orb.h"

uint16_t VLIB_aFast_nonmaxSuppression_cn(uint8_t *score,
                                         uint32_t *posyxPkd,
                                         uint8_t *scoreOut,
                                         uint32_t *posyxPkdOut,
                                         uint16_t inNumScores,
                                         uint16_t imgWidth,
                                         uint16_t imgHeight,
                                         uint8_t *scratch);
#endif

/* ======================================================================== */
/*  End of file:  VLIB_aFast_nonmaxSuppression_cn.h                         */
/* ======================================================================== */

