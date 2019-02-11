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

#ifndef VLIB_HOUGHLINEFROMLIST_CN_H_
#define VLIB_HOUGHLINEFROMLIST_CN_H_ 1

int32_t VLIB_houghLineFromList_cn(uint16_t *restrict pEdgeMapList,
                                  uint16_t *restrict pOutHoughSpace,
                                  uint16_t outBlkWidth,
                                  uint16_t outBlkHeight,
                                  uint32_t listSize,
                                  uint16_t thetaRange,
                                  uint16_t rhoMaxLength,
                                  const int16_t *pSIN,
                                  const int16_t *pCOS,
                                  uint16_t *restrict ping,
                                  uint16_t *restrict pong,
                                  uint16_t *restrict pang,
                                  uint16_t *restrict peng);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_houghLineFromList_cn.h                               */
/* ======================================================================== */

