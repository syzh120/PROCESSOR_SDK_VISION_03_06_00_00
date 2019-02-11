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

#ifndef VLIB_RECURSIVEFILTERHORIZ1STORDERE_CN_H_
#define VLIB_RECURSIVEFILTERHORIZ1STORDERE_CN_H_ 1

int32_t VLIB_recursiveFilterHoriz1stOrder_cn(uint8_t *out,
                                             const uint8_t *in,
                                             const int32_t width,
                                             const int32_t height,
                                             const int16_t weight,
                                             const uint8_t *boundaryLeft,
                                             const uint8_t *boundaryRight,
                                             uint8_t *scratch);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_recursiveFilterHoriz1stOrder_cn.h                    */
/* ======================================================================== */

