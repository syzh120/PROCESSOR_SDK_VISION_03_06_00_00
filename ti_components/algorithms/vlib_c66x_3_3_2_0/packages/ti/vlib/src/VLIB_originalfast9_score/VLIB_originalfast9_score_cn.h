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
**|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
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

#ifndef VLIB_ORIGINALFAST9_SCORE_CN_H_
#define VLIB_ORIGINALFAST9_SCORE_CN_H_ 1

#include "../common/VLIB_types.h"

void VLIB_originalfast9_score_cn(const uint8_t  *img,
                                 uint16_t stride,
                                 uint32_t *featuresLoc,
                                 uint32_t n_features,
                                 uint8_t b,
                                 uint8_t  *score);
#endif

/* ======================================================================== */
/*  End of file:  VLIB_originalfast9_score_cn.h                             */
/* ======================================================================== */

