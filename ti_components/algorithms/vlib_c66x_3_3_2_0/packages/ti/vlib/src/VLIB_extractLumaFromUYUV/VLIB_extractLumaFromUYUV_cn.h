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

#ifndef VLIB_EXTRACTLUMAFROMUYUV_CN_H_
#define VLIB_EXTRACTLUMAFROMUYUV_CN_H_ 1

int32_t VLIB_extractLumaFromUYUV_cn(uint8_t *restrict pInxYxY,
                                    uint16_t inCols, uint16_t inPitch,
                                    uint16_t inRows,
                                    uint8_t *restrict pOutY);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_extractLumaFromUYUV_cn.h                             */
/* ======================================================================== */

