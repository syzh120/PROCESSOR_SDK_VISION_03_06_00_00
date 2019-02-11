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
#include "VLIB_weightedHistogram_nD_U16_idat.h"

static uint16_t    numB0[4] = { 2, 3, 4, 2 };
static uint16_t    normVals0[4] = { 256, 256, 256, 256 }; /* 65536/256 */

static uint16_t    X0[] =
{
    148, 107, 131, 85, 110, 57, 147, 193, 135, 163, 53, 96, 199, 173, 117, 144, 202, 15, 153,
    12, 105, 77, 222,  3, 195, 247, 252, 201, 111, 127, 54, 164, 81, 244, 185, 105, 189,
    68, 112, 238, 174, 54, 214, 160, 34, 52, 154, 160, 94, 146, 115, 11,
    6, 79,  3, 97, 174, 23,  9, 156, 155,  4,  4, 48, 149, 14, 93, 161, 182, 176,
    21, 115, 112, 90, 39, 172, 178, 185, 121, 141, 30, 114, 182, 227, 69, 64, 220, 59, 205,
    231, 59, 61, 12, 19, 163, 48, 215, 44, 43, 253
};

static uint16_t    Href0[48] =
{
    1,     1,     0,     0,     0,     1,     1,     1,
    2,     1,     0,     0,     0,     0,     1,     2,
    1,     1,     0,     0,     0,
    0,     0,     0,     0,     1,     1,     2,     2,
    2,     0,     0,     1,     0,     0,     1,     1,
    0,     0,     0,     1,     0,
    0,     0,     0,     0,     0,     0
};

static uint16_t    numB1[12] = { 2, 3, 4, 2, 3, 6, 2, 2, 5, 3, 7, 2 };
static uint16_t    numB2[4] = { 2, 3, 4, 2 };
static uint16_t    numB3[4] = { 2, 3, 4, 2 };
static uint16_t    numB4[4] = { 2, 3, 4, 2 };
static uint16_t    numB5[3] = { 2, 62, 200 };
static uint16_t    numB6[2] = { 10, 18 };

static weightedHistogram_nD_U16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *numBins, *normVals, *staticOut,
           numX, dimX, maxSize
        },
    *********************************************/
    {
        STATIC,
        X0, numB0, normVals0, Href0,
        CONSTANT, NULL,
        25, sizeof(numB0) / sizeof(numB0[0]), 254
    },
    {
        RANDOM,
        NULL, numB1, NULL, NULL,
        RANDOM, NULL,
        4, sizeof(numB1) / sizeof(numB1[0]), 25
    },
    {
        RANDOM,
        NULL, numB2, NULL, NULL,
        RANDOM, NULL,
        32, sizeof(numB2) / sizeof(numB2[0]), 253
    },
    {
        RANDOM,
        NULL, numB3, NULL, NULL,
        RANDOM, NULL,
        64, sizeof(numB3) / sizeof(numB3[0]), 253
    },
    {
        RANDOM,
        NULL, numB4, NULL, NULL,
        RANDOM, NULL,
        512, sizeof(numB4) / sizeof(numB4[0]), 253
    },
    {
        RANDOM,
        NULL, numB5, NULL, NULL,
        RANDOM, NULL,
        4096, sizeof(numB5) / sizeof(numB5[0]), 200
    },
    {
        RANDOM,
        NULL, numB6, NULL, NULL,
        RANDOM, NULL,
        4096, sizeof(numB6) / sizeof(numB6[0]), 512
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void weightedHistogram_nD_U16_getTestParams(weightedHistogram_nD_U16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(weightedHistogram_nD_U16_testParams_t);
}

