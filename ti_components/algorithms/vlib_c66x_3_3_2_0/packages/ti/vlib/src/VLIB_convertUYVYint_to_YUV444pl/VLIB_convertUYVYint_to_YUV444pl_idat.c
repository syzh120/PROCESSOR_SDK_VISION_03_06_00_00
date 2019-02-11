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
#include "VLIB_convertUYVYint_to_YUV444pl_idat.h"

static uint8_t    staticRefIn[64] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

static uint8_t    staticRefOutY[32] =
{
    57, 170, 247, 140,  60,  77,   6,   6, 143,   3,  91, 154, 161, 162, 150, 224,
    113,  28, 211, 217, 233, 127, 203,  42, 155, 103,  16, 131, 158,   2, 227, 255
};

static uint8_t    staticRefOutCr[32] =
{
    116, 116, 208, 208, 88, 88, 162, 162, 178, 178, 54, 54, 20, 20, 128, 128,
    9, 9, 98, 98, 231, 231, 177, 177, 3, 3, 135, 135, 9, 9, 249, 249
};

static uint8_t    staticRefOutCb[32] =
{
    151, 151, 9, 9, 150, 150, 4, 4, 31, 31, 135, 135, 193, 193, 137, 137,
    214, 214, 53, 53, 149, 149, 115, 115, 62, 62, 127, 127, 211, 211, 106, 106
};

static UYVYint_to_YUV444pl_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOutY, *staticOutCr, *staticOutCb
           width, pitch, height
        },
    *********************************************/
    /* pitch == width*/
    {
        STATIC,
        staticRefIn, staticRefOutY, staticRefOutCr, staticRefOutCb,
        16, 16, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        64, 64, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        80, 80, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        320, 320, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        640, 640, 480
    },
    /* pitch > width*/
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        16, 20, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        64, 84, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        80, 84, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        320, 324, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        640, 644, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void UYVYint_to_YUV444pl_getTestParams(UYVYint_to_YUV444pl_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(UYVYint_to_YUV444pl_testParams_t);
}

