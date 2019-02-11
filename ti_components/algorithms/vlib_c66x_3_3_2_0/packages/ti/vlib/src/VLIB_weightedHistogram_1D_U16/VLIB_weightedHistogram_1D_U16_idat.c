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
#include "VLIB_weightedHistogram_1D_U16_idat.h"

static uint16_t    binEdges0[] =
{
    0,  26,  52,  78, 104, 130, 156, 182, 208, 234
};
static uint16_t    binEdges1[] =
{
    0, 7, 16, 19
};

static uint16_t    binEdges2[] =
{
    0, 100, 250
};

static uint16_t    binEdges3[] =
{
    120, 129, 132, 139, 145, 150, 157, 166, 172, 177, 183, 187, 190
};

static uint16_t    binEdges4[] =
{
    0, 129, 221, 381, 405, 490, 510
};

static uint16_t    X0[] =
{
    148, 107, 131, 85, 110, 57, 147, 193, 135, 163, 53, 96, 199, 173, 117, 144, 202, 15, 153,
    12, 105, 77, 222,  3, 195, 247, 252, 201, 111, 127, 54, 164, 81, 244, 185, 105, 189,
    68, 112, 238, 174, 54, 214, 160, 34, 52, 154, 160, 94, 146, 115, 11,
    6, 79,  3, 97, 174, 23,  9, 156, 155,  4,  4, 48, 149, 14, 93, 161, 182, 176,
    21, 115, 112, 90, 39, 172, 178, 185, 121, 141, 30, 114, 182, 227, 69, 64, 220, 59, 205,
    231, 59, 61, 12, 19, 163, 48, 215, 44, 43, 253
};

static uint16_t    Href0[] = { 14, 7, 12, 8, 13, 11, 13, 11, 6, 0 };


static weightedHistogram_1D_U16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInEdges, *staticInImg, *staticOut,
           weightPattern, *staticInWeight,
           numX, numBins, maxSize
        },
    *********************************************/
    {
        STATIC,
        binEdges0, X0, Href0,
        CONSTANT, NULL,
        sizeof(X0) / sizeof(X0[0]),
        sizeof(binEdges0) / sizeof(binEdges0[0]), 254
    },
    {
        RANDOM,
        binEdges1, NULL, NULL,
        RANDOM, NULL,
        64, sizeof(binEdges1) / sizeof(binEdges1[0]), 25
    },
    {
        RANDOM,
        binEdges2, NULL, NULL,
        RANDOM, NULL,
        512, sizeof(binEdges2) / sizeof(binEdges2[0]), 253
    },
    {
        RANDOM,
        binEdges3, NULL, NULL,
        RANDOM, NULL,
        4096, sizeof(binEdges3) / sizeof(binEdges3[0]), 200
    },
    {
        RANDOM,
        binEdges4, NULL, NULL,
        RANDOM, NULL,
        4096, sizeof(binEdges4) / sizeof(binEdges4[0]), 512
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void weightedHistogram_1D_U16_getTestParams(weightedHistogram_1D_U16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(weightedHistogram_1D_U16_testParams_t);
}

