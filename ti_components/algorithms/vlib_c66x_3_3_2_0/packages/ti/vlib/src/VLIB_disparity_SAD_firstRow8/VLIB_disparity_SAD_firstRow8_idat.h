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

#ifndef VLIB_DISPARITY_SAD_FIRSTROW_8_IDAT_H

#define VLIB_DISPARITY_SAD_FIRSTROW_8_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t  testPattern;    /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint8_t *staticInLeft;
    uint8_t *staticInRight;
    int8_t  *staticOut;
    uint32_t width;
    uint32_t height;
    int32_t  minDisp;
    int32_t  maxDisp;
    int32_t  windowSize;
} disparity_SAD_firstRow8_testParams_t;

void disparity_SAD_firstRow8_getTestParams(disparity_SAD_firstRow8_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_DISPARITY_SAD_FIRSTROW_8_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_disparity_SAD_firstRow8_idat.h                       */
/* ======================================================================== */

