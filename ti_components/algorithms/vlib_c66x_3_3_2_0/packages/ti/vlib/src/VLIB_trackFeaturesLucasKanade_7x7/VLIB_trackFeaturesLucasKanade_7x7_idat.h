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

#ifndef VLIB_TRACK_FEATURES_LK_7X7_IDAT_H

#define VLIB_TRACK_FEATURES_LK_7X7_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;   /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint8_t  *staticIn1;      /* im1 */
    uint8_t  *staticIn2;      /* im2 */
    uint16_t  width;
    uint16_t  height;
    uint32_t  imgGradPitch;
    uint32_t  nfeatures;
    uint16_t *x;
    uint16_t *y;
    uint16_t *outx;
    uint16_t *outy;
    uint16_t *outError;
    uint32_t  max_iters;
    uint32_t  earlyExitTh;
    uint8_t   gradFlag;
    uint8_t   outEstFlag;
    char     *desc;
} trackFeaturesLK_7x7_testParams_t;

void trackFeaturesLK_7x7_getTestParams(trackFeaturesLK_7x7_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_TRACK_FEATURES_LK_7X7_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_trackFeaturesLucasKanade_7x7_idat.h                 */
/* ======================================================================== */

