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

#ifndef VLIB_AFAST_NONMAX_SUPPRESSION_IDAT_H

#define VLIB_AFAST_NONMAX_SUPPRESSION_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;  /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint16_t *staticInFeatures;      /* Feature List */
    uint8_t  *staticInFastResponse;  /* Fast Response List */
    uint16_t *staticOut;             /* Final Expected Feature List */
    uint8_t  *staticOutFastResponse; /* Final Expected Fast Response List */
    int32_t   out_n_features;        /* Final Expected Number of Features */
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint32_t  true_num_features;
    char     *desc;
} aFast_nonmaxSuppression_testParams_t;

void aFast_nonmaxSuppression_getTestParams(aFast_nonmaxSuppression_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_AFAST_NONMAX_SUPPRESSION_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_afast_nonmaxSuppression_idat.h                       */
/* ======================================================================== */

