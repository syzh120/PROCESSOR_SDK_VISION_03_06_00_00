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
#include "VLIB_gradientV5x5PyramidKernel_8_idat.h"

static uint8_t    staticRefIn[16 * 5] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255,
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6
};

/* expected output calculated off-line in Matlab */
static uint8_t    staticRefOut[] = { 137, 129, 126, 127 };

/* Expected image for constant array */
static uint8_t    staticRefOutConst[] = { 128, 128, 128, 128 };

static gradientV5x5Pyramid8_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           width, pitch, height
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOut,
        12, 16, 5
    },
    {
        CONSTANT,
        NULL, staticRefOutConst,
        12, 16, 5
    },
    {
        RANDOM,
        NULL, NULL,
        60, 64, 32
    },
    {
        RANDOM,
        NULL, NULL,
        156, 160, 121
    },
    {
        RANDOM,
        NULL, NULL,
        324, 328, 240
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void gradientV5x5Pyramid8_getTestParams(gradientV5x5Pyramid8_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(gradientV5x5Pyramid8_testParams_t);
}

