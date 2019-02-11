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

#ifndef VLIB_TRIANGULATE_POINTS_IDAT_H

#define VLIB_TRIANGULATE_POINTS_IDAT_H

#include "../common/VLIB_test.h"


typedef struct {
    uint8_t   testPattern;      /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    int32_t   numTracks;
    VLIB_F32 *ptrack[4];
    VLIB_F32 *camExtPrm;
    uint8_t   trackLength[4];
    uint32_t  maxIter;
    VLIB_F32 *outX[4];
    uint8_t   isHighPrecision;
    char     *desc;
} triangulatePoints_testParams_t;

void triangulatePoints_getTestParams(triangulatePoints_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_TRIANGULATE_POINTS_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_triangulatePoints_idat.h                 */
/* ======================================================================== */

