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
 **|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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
#include "VLIB_blockStatistics_idat.h"

static uint8_t    minContStaticOut12x12[144] =
{
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
static uint8_t    maxContStaticOut12x12[144] =
{
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x0FF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
static uint16_t    meanContStaticOut12x12[144] =
{
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7,
    0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7, 0x18E7
};
static uint32_t    varContStaticOut12x12[144] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static blockStatistics_testParams_t    testParams[]=
{
    /********************************************
        {
          testPattern, *staticIn,
          *staticOutMin, *staticOutMax,
          *staticOutMean, *staticOutVar,
           mode,
           imageWidth, imageHeight, imagePitch,
           statBlockWidth, statBlockHeight
        },
    *********************************************/
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        64, 64, 70,
        1, 1,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        1,
        64, 64, 70,
        1, 1,
    },
    {
        SEQUENTIAL_NEGATIVE, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        64, 64, 64,
        5, 5,
    },
    {
        CONSTANT, NULL,
        minContStaticOut12x12, maxContStaticOut12x12,
        meanContStaticOut12x12, varContStaticOut12x12,
        1,
        64, 64, 72,
        5, 5,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        64, 64, 64,
        3, 5,
    },
    {
        RANDOM, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        64, 64, 64,
        5, 11,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        128, 128, 128,
        1, 3,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        128, 256, 128,
        3, 1,
    },
    {
        RANDOM, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        128, 256, 130,
        1, 32,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        1,
        128, 128, 128,
        1, 32,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        128, 256, 128,
        32, 1,
    },
    {
        RANDOM, NULL,
        NULL, NULL,
        NULL, NULL,
        1,
        128, 128, 128,
        32, 1,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        320, 240, 320,
        21, 11,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        1,
        320, 240, 320,
        21, 11,
    },
    {
        SEQUENTIAL_NEGATIVE, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        321, 241, 400,
        3, 3,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        322, 242, 322,
        3, 3,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        323, 243, 323,
        3, 3,
    },
    {
        RANDOM, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        324, 244, 324,
        3, 3,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        320, 240, 320,
        3, 3,
    },
    {
        SEQUENTIAL, NULL,
        NULL, NULL,
        NULL, NULL,
        1,
        320, 240, 320,
        3, 3,
    },

    {
        SEQUENTIAL_NEGATIVE, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        320, 240, 320,
        1, 18,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        320, 240, 320,
        18, 1,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        0,
        320, 240, 320,
        16, 16,
    },
    {
        CONSTANT, NULL,
        NULL, NULL,
        NULL, NULL,
        1,
        320, 240, 320,
        16, 16,
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void blockStatistics_getTestParams(blockStatistics_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(blockStatistics_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

