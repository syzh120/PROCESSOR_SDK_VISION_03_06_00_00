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
#include "VLIB_integralImage8_idat.h"

static uint8_t    staticRefIn[16 * 4] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

/* expected output calculated off-line in Matlab */
static uint32_t    staticRefOut[16 * 4] =
{
    151, 208,  324,  494,  503,  750,  958, 1098, 1248, 1308, 1396, 1473, 1477, 1483, 1645, 1651,
    182, 382,  676,  849,  993, 1331, 1593, 1887, 2230, 2451, 2559, 2798, 2939, 3095, 3385, 3615,
    396, 709, 1012, 1213, 1410, 1959, 2319, 2830, 3322, 3776, 4115, 4481, 4737, 5096, 5563, 5835,
    458, 926, 1232, 1536, 1860, 2425, 2920, 3562, 4265, 4877, 5225, 5593, 5955, 6541, 7257, 7784
};

/* Expected interval image for constant array of 1s */
static uint32_t    staticRefOutOnes[32 * 4] =
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64,
    3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96,
    4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128
};

static integralImage8_testParams_t    testParams[]=
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
        staticRefIn, staticRefOut,
        16, 4
    },
    {
        CONSTANT,
        NULL, staticRefOutOnes,
        32, 4
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48
    },
    {
        RANDOM,
        NULL, NULL,
        104, 55
    },
    {
        RANDOM,
        NULL, NULL,
        112, 62
    },
    {
        RANDOM,
        NULL, NULL,
        320, 160
    },
    {
        RANDOM,
        NULL, NULL,
        640, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void integralImage8_getTestParams(integralImage8_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(integralImage8_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

