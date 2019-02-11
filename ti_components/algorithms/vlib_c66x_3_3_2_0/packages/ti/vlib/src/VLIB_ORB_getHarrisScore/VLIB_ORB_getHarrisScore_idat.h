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

#ifndef VLIB_ORB_GET_HARRIS_SCORE_IDAT_H

#define VLIB_ORB_GET_HARRIS_SCORE_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;  /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint16_t *staticInFeatures;      /* Feature List */
    int16_t  *staticInHarris;        /* Harris Image */
    int16_t  *staticOut;             /* Harris Scores matching features */
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint32_t  true_num_features;
} orb_getHarrisScore_testParams_t;

void orb_getHarrisScore_getTestParams(orb_getHarrisScore_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_ORB_GET_HARRIS_SCORE_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_getHarrisScore_idat.h                            */
/* ======================================================================== */

