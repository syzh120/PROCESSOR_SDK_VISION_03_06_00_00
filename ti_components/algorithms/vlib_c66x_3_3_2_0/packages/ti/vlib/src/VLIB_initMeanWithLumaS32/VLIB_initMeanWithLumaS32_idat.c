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
#include "VLIB_initMeanWithLumaS32_idat.h"

static int32_t    sequentialMean32[] =
{
    0 << 23, 1 << 23, 2 << 23, 3 << 23, 4 << 23, 5 << 23, 6 << 23, 7 << 23,
    8 << 23, 9 << 23, 10 << 23, 11 << 23, 12 << 23, 13 << 23, 14 << 23, 15 << 23,
    16 << 23, 17 << 23, 18 << 23, 19 << 23, 20 << 23, 21 << 23, 22 << 23, 23 << 23,
    24 << 23, 25 << 23, 26 << 23, 27 << 23, 28 << 23, 29 << 23, 30 << 23, 31 << 23
};

static initMeanWithLumaS32_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut, pixelCount
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL, sequentialMean32, 32
    },
    {
        RANDOM,
        NULL, NULL, 64
    },
    {
        RANDOM,
        NULL, NULL, 128
    },
    {
        RANDOM,
        NULL, NULL, 512
    },
    {
        RANDOM,
        NULL, NULL, 1024
    },
    {
        RANDOM,
        NULL, NULL, 4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void initMeanWithLumaS32_getTestParams(initMeanWithLumaS32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(initMeanWithLumaS32_testParams_t);
}

