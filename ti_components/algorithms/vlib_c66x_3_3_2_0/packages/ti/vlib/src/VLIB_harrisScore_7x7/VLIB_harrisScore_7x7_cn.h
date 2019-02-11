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

#ifndef VLIB_HARRISSCORE_7X7_CN_H_
#define VLIB_HARRISSCORE_7X7_CN_H_ 1

int32_t VLIB_harrisScore_7x7_cn(const int16_t *restrict gradX,
                                const int16_t *restrict gradY,
                                int32_t width,
                                int32_t height,
                                int16_t *restrict outm,
                                int16_t k,
                                uint8_t *buffer);

int32_t VLIB_harrisScore_7x7_f(const int16_t *restrict gradX,
                               const int16_t *restrict gradY,
                               int32_t width,
                               int32_t height,
                               VLIB_F32 *outm,
                               VLIB_F32 k,
                               VLIB_F32 *buffer);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_harrisScore_7x7_cn.h                              */
/* ======================================================================== */

