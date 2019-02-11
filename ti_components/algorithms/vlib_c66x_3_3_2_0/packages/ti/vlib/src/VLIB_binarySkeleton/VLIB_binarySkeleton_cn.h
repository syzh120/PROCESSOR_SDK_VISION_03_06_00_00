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

#ifndef VLIB_BINARY_SKELETON_CN_H_
#define VLIB_BINARY_SKELETON_CN_H_ 1

#include "../common/VLIB_types.h"

void VLIB_hitmiss_bin_cn(const uint32_t *restrict in_data,
                         uint32_t *restrict out_data,
                         const uint8_t *restrict mask,
                         const uint8_t *restrict mask_d,
                         int32_t rows,
                         int32_t cols);

void    VLIB_binarySkeleton_cn(const uint32_t * restrict in_data,
                               uint32_t * restrict out_data,
                               uint32_t * restrict scratch,
                               uint8_t mask[][VLIB_BINSKEL_MASK_SZ],
                               uint8_t mask_d[][VLIB_BINSKEL_MASK_SZ],
                               uint16_t width,
                               uint16_t height,
                               uint8_t num_st,
                               uint8_t * iters);


#endif /* VLIB_BINARY_SKELETON_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_binarySkeleton_cn.h                                  */
/* ======================================================================== */

