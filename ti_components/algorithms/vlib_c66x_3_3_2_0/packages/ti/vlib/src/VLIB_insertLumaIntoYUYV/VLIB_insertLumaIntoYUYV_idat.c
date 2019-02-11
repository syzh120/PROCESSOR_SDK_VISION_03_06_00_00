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
#include "VLIB_insertLumaIntoYUYV_idat.h"

static uint8_t    staticRefIn[32] =
{
    151, 116,  9, 208, 150,  88,   4, 162, 31, 178, 135,  54, 193, 20, 137, 128,
    214,   9, 53,  98, 149, 231, 115, 177, 62,   3, 127, 135, 211,  9, 106, 249
};

static uint8_t    staticInYUYV[64] =
{
    140,  57, 132, 170,   3, 247, 224, 140, 130,  60,  68,  77,  12,   6, 140,   6,
    10, 143, 203,   3, 156,  91,  27, 154, 225, 161,  30, 162, 168, 150, 102, 224,
    250, 113,  16,  28,  46, 211,  85, 217, 124, 233, 252, 127, 104, 203, 175,  42,
    61, 155,   7, 103,  58,  16, 190, 131, 248, 158,  45,   2,  77, 227, 214, 255
};

static uint8_t    staticRefOut[64] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

static insertLumaIntoYUYV_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticInYUYV, *staticOut,
           inCols, inPitch, inRows
        },
    *********************************************/
    /* MODE 1: inPitch == inCols */
    {
        STATIC,
        staticRefIn, staticInYUYV, staticRefOut,
        16, 16, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 64, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128, 128, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 320, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 640, 480
    },
    /* MODE 2: inPitch > inCols */
    {
        RANDOM,
        NULL, NULL, NULL,
        16, 20, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 84, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128, 136, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 324, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 644, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void insertLumaIntoYUYV_getTestParams(insertLumaIntoYUYV_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(insertLumaIntoYUYV_testParams_t);
}

