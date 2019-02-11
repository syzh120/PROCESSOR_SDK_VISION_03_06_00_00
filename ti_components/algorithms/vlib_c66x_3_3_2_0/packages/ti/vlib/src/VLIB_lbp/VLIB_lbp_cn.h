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

#ifndef VLIB_LBP_CN_H_
#define VLIB_LBP_CN_H_

void VLIB_lbp_cn(const uint8_t *pInput,
                 uint8_t *pMapTbl,
                 uint32_t *pOutHistogram,
                 int32_t imageWidth,
                 int32_t imageHeight,
                 int32_t numNeighbors,
                 int32_t radius);

#endif /* VLIB_LBP_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_lbp_cn.h                                             */
/* ======================================================================== */

