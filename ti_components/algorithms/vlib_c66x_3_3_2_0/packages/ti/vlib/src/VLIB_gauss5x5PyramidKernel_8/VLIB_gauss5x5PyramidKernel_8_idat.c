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
#include "VLIB_gauss5x5PyramidKernel_8_idat.h"

/* test input */
static uint8_t    staticRefIn[16 * 5] = { 151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
                                          31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
                                          214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
                                          62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255,
                                          151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6 };

/* expected output calculated off-line in Matlab */
static uint8_t    staticRefOut[6] = { 82, 92, 134, 165, 125, 124 }; /* 82.2891, 92.0078, 134.3516, 165.4766, 125.0469, 124.3438 */

static uint8_t    staticRefOutConst[28 * 6] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                                                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                                                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                                                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                                                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
                                                128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, };

static gauss5x5pyramid_8_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern, constant,
           *staticIn, *staticOut,
           width, pitch, height,
        },
    *********************************************/
    {
        STATIC, 0,
        staticRefIn, staticRefOut,
        16 - 4, 16, 5
    },
    {
        CONSTANT, 128,
        NULL, staticRefOutConst,
        64 - 4, 64, 16
    },
    {
        RANDOM, 0,
        NULL, NULL,
        64 - 4, 64, 64
    },
    {
        RANDOM, 0,
        NULL, NULL,
        64 - 4, 64, 128
    },
    {
        RANDOM, 0,
        NULL, NULL,
        128 - 4, 128, 32
    },
    {
        RANDOM, 0,
        NULL, NULL,
        128 - 4, 128, 64
    },
    {
        RANDOM, 0,
        NULL, NULL,
        128 - 4, 128, 128
    },
    {
        RANDOM, 0,
        NULL, NULL,
        128 - 4, 128, 240
    },
    {
        RANDOM, 0,
        NULL, NULL,
        320 - 4, 320, 240
    },
    {
        RANDOM, 0,
        NULL, NULL,
        640 - 4, 640, 480
    },
    {
        RANDOM, 0,
        NULL, NULL,
        240 - 4, 320, 320
    },
    {
        RANDOM, 0,
        NULL, NULL,
        480 - 4, 640, 640
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void gauss5x5pyramid_8_getTestParams(gauss5x5pyramid_8_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(gauss5x5pyramid_8_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

