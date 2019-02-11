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

#ifndef VLIB_MIXTUREOFGAUSSIANSS32_IDAT_H

#define VLIB_MIXTUREOFGAUSSIANSS32_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;  /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint8_t  *staticIn;
    uint32_t *staticOut;
    int32_t   im_size;
    int32_t   num_images;
    int16_t   alpha;
    int32_t   rho;
    int32_t   delta;
    int16_t   T;
    int16_t   ini_wt;
    int32_t   ini_var;
} mixtureOfGaussiansS32_testParams_t;

void mixtureOfGaussiansS32_getTestParams(mixtureOfGaussiansS32_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_MIXTUREOFGAUSSIANSS32_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_mixtureOfGaussiansS32_idat.h                         */
/* ======================================================================== */

