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

#ifndef VLIB_HIST_ND_U16_IDAT_H

#define VLIB_HIST_ND_U16_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;    /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint16_t *staticIn;
    uint16_t *numBins;
    uint16_t *normVals;
    uint16_t *staticOut;
    int32_t   numX;
    int32_t   dimX;
    uint16_t  binWeight;
    int32_t   maxSize;   /* = max value of input array + 1, used to set the size of the histArray buffer */
} histogram_nD_U16_testParams_t;

void histogram_nD_U16_getTestParams(histogram_nD_U16_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_HIST_ND_U16_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_histogram_nD_U16_idat.h                              */
/* ======================================================================== */

