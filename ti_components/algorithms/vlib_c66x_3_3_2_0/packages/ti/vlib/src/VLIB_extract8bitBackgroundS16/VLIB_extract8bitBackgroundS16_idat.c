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
#include "VLIB_extract8bitBackgroundS16_idat.h"

static int16_t    sequentialMean32[] =
{
    0 << 7, 1 << 7, 2 << 7, 3 << 7, 4 << 7, 5 << 7, 6 << 7, 7 << 7,
    8 << 7, 9 << 7, 10 << 7, 11 << 7, 12 << 7, 13 << 7, 14 << 7, 15 << 7,
    16 << 7, 17 << 7, 18 << 7, 19 << 7, 20 << 7, 21 << 7, 22 << 7, 23 << 7,
    24 << 7, 25 << 7, 26 << 7, 27 << 7, 28 << 7, 29 << 7, 30 << 7, 31 << 7
};

static uint8_t    sequentialBGimage[] =
{
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31
};

static extract8bitBackgroundS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut, pixelCount
        },
    *********************************************/
    {
        STATIC,
        sequentialMean32, sequentialBGimage, 32
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
void extract8bitBackgroundS16_getTestParams(extract8bitBackgroundS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(extract8bitBackgroundS16_testParams_t);
}

