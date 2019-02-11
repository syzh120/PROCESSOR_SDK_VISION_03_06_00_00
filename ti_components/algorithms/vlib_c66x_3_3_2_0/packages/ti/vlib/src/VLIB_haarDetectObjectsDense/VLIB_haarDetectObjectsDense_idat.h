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
**|         Copyright (c) 2015 Texas Instruments Incorporated                |**
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

#ifndef VLIB_HAAR_DETOBJ_DENSE_IDAT_H

#define VLIB_HAAR_DETOBJ_DENSE_IDAT_H

#include "../common/VLIB_test.h"
#include "../common/VLIB_haarDetectObjects_types.h"


typedef struct {
    uint8_t                      testPattern;       /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint32_t                    *integralImg;        /* Integral image prepared outside this kernel*/
    int32_t                      integralImgWidth;  /* Integral image width  */
    int32_t                      integralImgHeight; /* Integral image height */
    int32_t                      integralImgPitch;  /* Integral image pitch  */
    int32_t                      startStage;        /* Start stage of classifier */
    int32_t                      endStage;          /* End stage of classifier   */
    int32_t                      dualIntImgFlow;    /* To enable dual integral image flow*/
    int32_t                      maxObjects;
    VLIB_HAARDETOBJ_sClassifier *classifier;        /* Classifier data   */
    uint32_t                    *objectPos;         /* Output object list*/
    char                        *desc;
} haarDetectObjectsDense_testParams_t;

void haarDetectObjectsDense_getTestParams(haarDetectObjectsDense_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_HAAR_DETOBJ_DENSE_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsDense_idat.h                        */
/* ======================================================================== */

