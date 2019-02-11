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
#include "../common/VLIB_memory.h"
#include "VLIB_kalmanFilter_2x4_Predict_idat.h"

/* 50 measurements (2 values per measurement) */
static int16_t    Y[] = { 1, 99, 2, 84, 3, 98, 4, 100, 5, 103, 6, 109, 7, 88, 8, 87, 9, 120, 10, 127,
                          11, 109, 12, 94, 13, 105, 14, 101, 15, 79, 16, 100, 17, 98, 18, 104, 19, 100, 20, 64,
                          21, 88, 22, 85, 23, 92, 24, 81, 25, 97, 26, 90, 27, 105, 28, 93, 29, 105, 30, 86,
                          31, 80, 32, 90, 33, 106, 34, 111, 35, 93, 36, 115, 37, 98, 38, 101, 39, 97, 40, 94,
                          41, 102, 42, 105, 43, 97, 44, 73, 45, 121, 46, 90, 47, 119, 48, 110, 49, 73, 50, 99 };

/* state after 50 iterations */
static int16_t    testResult[] = { 1425, 3250, 17, -3 };

static kalmanFilter_2x4_Predict_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           inCols, inRows
        },
    *********************************************/
    {
        STATIC,
        Y, testResult,
        50
    },
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
void kalmanFilter_2x4_Predict_getTestParams(kalmanFilter_2x4_Predict_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(kalmanFilter_2x4_Predict_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

