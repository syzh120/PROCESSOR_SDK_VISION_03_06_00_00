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
#include "VLIB_blockMedian_idat.h"

static uint8_t    staticRefIn[] =
{
    1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20,  0,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  0,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50,  0,
    70, 70, 70, 70, 70, 70, 70, 70, 70, 70,  0,
    90, 90, 90, 90, 90, 90, 90, 90, 90, 90,  0
};

static uint8_t    staticRefOut[]=
{
    20, 20, 20, 20,
    50, 50, 50, 50
};

static blockMedian_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           imageWidth, imageHeight, imagePitch,
           blockWidth, blockHeight,
           stepSizeHorz, stepSizeVert
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOut,
        11, 6, 11,
        4, 4,
        2, 2
    },
    {   /* All even numbers, overlapping blocks */
        /* fill value 255, blockMedian = 255 */
        CONSTANT,
        NULL, NULL,
        640, 480, 640,
        66, 60,
        66 / 4, 66 / 4
    },
    {   /* Flow vector, odd block sizes and step sizes, overlapping blocks*/
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        640, 480, 640,
        121, 71,
        35, 35
    },
    {   /* Median of whole image, sizes greater than 256  */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        640, 480, 640,
        640, 480,
        100, 100    /* Could be any non-zero number */
    },
    {   /* Adjacent blocks, sizes greater than 256 */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        640, 480, 640,
        320, 320,
        320, 320
    },
    {   /* Sparsely spaced blocks, odd sizes */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        633, 477, 633,
        251, 19,
        311, 311
    },
    {   /* Smaller block width ~32 */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        633, 477, 633,
        32, 19,
        21, 21
    },
    {   /* Test vector that fits in 32k RAM */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        203, 101, 213,
        32, 32,
        64, 32
    },
    {   /* Test vector that fits in 32k RAM */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        203, 101, 213,
        203, 16,
        64, 32
    },
    {   /* Test vector that fits in 32k RAM */
        /* blockMedian = random */
        RANDOM,
        NULL, NULL,
        2000, 10, 2000,
        2000, 8,
        200, 32
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void blockMedian_getTestParams(blockMedian_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(blockMedian_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

