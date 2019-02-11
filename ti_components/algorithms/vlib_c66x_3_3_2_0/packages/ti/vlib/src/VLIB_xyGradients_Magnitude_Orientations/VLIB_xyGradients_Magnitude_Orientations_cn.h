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
**+--------------------------------------------------------------------------+*/

#ifndef VLIB_XYGRADIENTS_MAGNITUDE_ORIENTATIONS_CN_H_
#define VLIB_XYGRADIENTS_MAGNITUDE_ORIENTATIONS_CN_H_ 1

#include "../common/VLIB_types.h"


void    VLIB_init_xyGradients_Magnitude_Orientations_cn(uint8_t table[],
                                                        uint8_t bins, int32_t max_btable[],
                                                        int32_t min_btable[]);

void    VLIB_xyGradients_Magnitude_Orientations_cn
(
    const uint8_t img[],
    uint16_t Width,
    uint16_t Height,
    uint8_t bins,
    uint32_t Mag[],
    uint32_t Orien[]);

#endif
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_xyGradients_Magnitude_Orientations_cn.h              */
/* ======================================================================== */

