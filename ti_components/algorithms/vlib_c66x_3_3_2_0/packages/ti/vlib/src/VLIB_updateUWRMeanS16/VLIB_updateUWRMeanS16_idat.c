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
#include "VLIB_updateUWRMeanS16_idat.h"

static uint32_t    newestMask32packed32[] = { 0x1840F00F };
static uint32_t    oldestMask32packed32[] = { 0x03E0FFFF };

static uint8_t    newestLuma[32] =
{
    0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};

static uint8_t    oldestLuma[32] =
{
    0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160,
    170, 180, 190, 200, 210, 220, 230, 240, 250, 6, 7, 8, 9, 0, 1
};

static uint8_t    prevLuma32[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16,
    32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 0, 0
};

static updateUWRMeanS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInPrevLuma, *staticOutMean,
           *newestData, *oldestData, *newestMask, *oldestMask
           pixelCount, frameCount
        },
    *********************************************/
    {
        STATIC,
        prevLuma32, NULL,
        newestLuma, oldestLuma, newestMask32packed32, oldestMask32packed32,
        32, 10
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        64, 255
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        72, 250
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        512, 2
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        1024, 128
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        4096, 127
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void updateUWRMeanS16_getTestParams(updateUWRMeanS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(updateUWRMeanS16_testParams_t);
}

