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

#ifndef VLIB_FIND_FUNDAMENTAL_MAT_IDAT_H

#define VLIB_FIND_FUNDAMENTAL_MAT_IDAT_H

#include "../common/VLIB_test.h"


typedef struct {
    uint8_t   testPattern;      /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    VLIB_F32 *points1;
    VLIB_F32 *points2;
    int32_t   numPoints;
    int32_t   numItr4RANSAC;
    int32_t   method;
    VLIB_F32  param1;
    int32_t   leastSqrSolEn;
    VLIB_F32 *outFMat;
    char     *desc;
} findFundamentalMat_testParams_t;

void findFundamentalMat_getTestParams(findFundamentalMat_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_FIND_FUNDAMENTAL_MAT_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_findFundamentalMat_idat.h                 */
/* ======================================================================== */

