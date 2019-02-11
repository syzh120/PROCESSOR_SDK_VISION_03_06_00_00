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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#ifndef VLIB_SIMPLEX_3D_IDAT_H

#define VLIB_SIMPLEX_3D_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t testPattern;    /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    int32_t (*func)(int16_t a[], const void *b);
    int16_t    *start;
    int16_t    *init_step;
    int32_t     MaxIteration;
    int32_t     EPSILON;
    const void *addtlArgs;
    int16_t    *refMinPoint;
    int32_t     refMinValue;
} simplex_3D_testParams_t;

void simplex_3D_getTestParams(simplex_3D_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_SIMPLEX_3D_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_simplex_3D_idat.h                                    */
/* ======================================================================== */

