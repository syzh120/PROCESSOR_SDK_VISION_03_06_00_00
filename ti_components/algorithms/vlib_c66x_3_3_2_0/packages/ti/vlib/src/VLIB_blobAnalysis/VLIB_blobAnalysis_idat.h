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

#ifndef  _VLIB_BLOB_ANALYSIS_IDAT_H_

#define  _VLIB_BLOB_ANALYSIS_IDAT_H_

#include "../common/VLIB_test.h"

typedef struct {
    int32_t  ccMapColor;
    int32_t  area;
    int32_t  perimeter;
    int32_t  xmin;
    int32_t  ymin;
    int32_t  xmax;
    int32_t  ymax;
    VLIB_F32 rect_center_x;
    VLIB_F32 rect_center_y;
    VLIB_F32 rect_sita;
    VLIB_F32 rect_width;
    VLIB_F32 rect_height;
    VLIB_F32 circle_x;
    VLIB_F32 circle_y;
    VLIB_F32 circle_r;
} blobAnalysis_resultParams_t;

typedef struct {
    uint8_t                      testPattern;   /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    int32_t                      imageWidth;
    int32_t                      imageHeight;
    uint8_t                     *staticIn;
    int32_t                      numBlobs;     /* [out] expected reference output */
    blobAnalysis_resultParams_t *staticOut; /* [out] expected reference output */
} blobAnalysis_testParams_t;

void blobAnalysis_getTestParams(blobAnalysis_testParams_t * *params, int32_t *numTests);

#endif /* define _VLIB_BLOB_ANALYSIS_IDAT_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_blobAnalysis_idat.h                                  */
/* ======================================================================== */

