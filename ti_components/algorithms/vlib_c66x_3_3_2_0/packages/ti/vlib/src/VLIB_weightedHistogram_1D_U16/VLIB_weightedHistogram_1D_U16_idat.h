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

#ifndef VLIB_WEIGHTED_HIST_U16_IDAT_H

#define VLIB_WEIGHTED_HIST_U16_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;   /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint16_t *staticInEdges;
    uint16_t *staticInImg;
    uint16_t *staticOut;
    uint8_t   weightPattern;    /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint16_t *staticInWeight;
    int32_t   numX;
    int32_t   numBins;
    int32_t   maxSize;   /* = max value of input array + 1, used to set the size of the histArray buffer */
} weightedHistogram_1D_U16_testParams_t;

void weightedHistogram_1D_U16_getTestParams(weightedHistogram_1D_U16_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_WEIGHTED_HIST_U16_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_weightedHistogram_1D_U16_idat.h                      */
/* ======================================================================== */

