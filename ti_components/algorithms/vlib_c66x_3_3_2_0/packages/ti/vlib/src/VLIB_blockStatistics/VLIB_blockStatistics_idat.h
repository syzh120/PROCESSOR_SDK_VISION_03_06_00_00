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
**|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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

#ifndef VLIB_BLOCKSTATISTICS_IDAT_H

#define VLIB_BLOCKSTATISTICS_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;
    uint8_t  *staticIn;
    uint8_t  *staticOutMin;
    uint8_t  *staticOutMax;
    uint16_t *staticOutMean;
    uint32_t *staticOutVar;
    uint8_t   mode;
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint16_t  imagePitch;
    uint16_t  statBlockWidth;
    uint16_t  statBlockHeight;
} blockStatistics_testParams_t;

void blockStatistics_getTestParams(blockStatistics_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_BLOCK_STATISTICS_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_blockStatistics_idat.h                               */
/* ======================================================================== */

