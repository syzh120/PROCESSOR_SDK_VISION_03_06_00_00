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
#include "VLIB_integralImage16_idat.h"

static uint16_t    staticRefIn[16 * 4] =
{
    604, 228, 464, 680,  36, 988, 832, 560, 600, 240, 352, 308,  16,  24, 648,  24,
    124, 572, 712,  12, 540, 364, 216, 616, 772, 644,  80, 648, 548, 600, 512, 896,
    856, 452,  36, 112, 212, 844, 392, 868, 596, 932, 924, 508, 460, 812, 708, 168,
    248, 620,  12, 412, 508,  64, 540, 524, 844, 632,  36,   8, 424, 908, 996, 1020
};

/* expected output calculated off-line in Matlab */
static uint32_t    staticRefOut[16 * 4] =
{
    604,   832,  1296,  1976,  2012,  3000,  3832,  4392,  4992,  5232,  5584,  5892,  5908,  5932,  6580,  6604,
    728,  1528,  2704,  3396,  3972,  5324,  6372,  7548,  8920,  9804, 10236, 11192, 11756, 12380, 13540, 14460,
    1584,  2836,  4048,  4852,  5640,  7836,  9276, 11320, 13288, 15104, 16460, 17924, 18948, 20384, 22252, 23340,
    1832,  3704,  4928,  6144,  7440,  9700, 11680, 14248, 17060, 19508, 20900, 22372, 23820, 26164, 29028, 31136
};

/* Expected interval image for constant array of 1s */
static uint32_t    staticRefOutOnes[32 * 4] =
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64,
    3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96,
    4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128
};

static integralImage16_testParams_t    testParams[]=
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
void integralImage16_getTestParams(integralImage16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(integralImage16_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

