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
#include "../common/VLIB_memory.h"
#include "VLIB_kalmanFilter_4x12_Predict_F32_idat.h"

static VLIB_kalmanFilter_4x12_Predict_F32_testParams_t    testParams[]=
{
    /********************************************
    {
      testPattern,
      *staticIn, *staticOut,
      numMeasurements
    },
    *********************************************/
    {
        RANDOM,
        NULL, NULL,
        20
    },
    {
        RANDOM,
        NULL, NULL,
        75
    },
    {
        RANDOM,
        NULL, NULL,
        100
    },
    {
        RANDOM,
        NULL, NULL,
        600
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void VLIB_kalmanFilter_4x12_Predict_F32_getTestParams(VLIB_kalmanFilter_4x12_Predict_F32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(VLIB_kalmanFilter_4x12_Predict_F32_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x8_Predict_F32_idat.c                  */
/* ======================================================================== */

