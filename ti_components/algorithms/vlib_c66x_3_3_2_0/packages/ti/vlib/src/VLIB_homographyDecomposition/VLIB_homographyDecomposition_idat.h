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

#ifndef VLIB_HOMOGRAPHY_DECOMPOSITION_IDAT_H

#define VLIB_HOMOGRAPHY_DECOMPOSITION_IDAT_H

#include "../common/VLIB_test.h"

/* Used so that malloc can point to this 3x3 contiguous array in the test */
typedef struct {
    VLIB_D64 H[3][3];
} H3x3_t;

typedef struct {
    uint8_t   testPattern;  /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    VLIB_D64 *staticInH;
    VLIB_D64 *staticOutRot;
    VLIB_D64 *staticOutTr;
    VLIB_D64 *staticOutPr;
    uint16_t  testIterations;
    VLIB_D64  testErrorThreshold;
} homographyDecomposition_testParams_t;

void homographyDecomposition_getTestParams(homographyDecomposition_testParams_t * *params, int32_t *numTests);

#endif /* defineVLIB_HOMOGRAPHY_DECOMPOSITION_IDAT_HVLIB_BLOCK_MEDIAN_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_homographyDecomposition_idat.h                       */
/* ======================================================================== */

