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
#include "VLIB_updateUWRVarianceS16_idat.h"

#define CAMERA_NOISE_S16      0x0A00        /* SQ12.3 */

static uint32_t    newestMask32packed32[] = { 0x1840F00F };
static uint32_t    oldestMask32packed32[] = { 0x03E0FFFF };

static uint8_t    oldestData[32] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static uint8_t    newestData[32] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};

static uint8_t    prevLuma32[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16,
    32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 0, 0
};

static updateUWRVarianceS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInPrevLuma, *staticOutVar,
           *newestData, *oldestData, *newestMask, *oldestMask
           constant, pixelCount, frameCount
        },
    *********************************************/
    {
        STATIC,
        prevLuma32, NULL,
        newestData, oldestData, newestMask32packed32, oldestMask32packed32,
        CAMERA_NOISE_S16 / 32, 32, 10
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        CAMERA_NOISE_S16 / 32, 64, 255
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        CAMERA_NOISE_S16 / 32, 72, 250
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        CAMERA_NOISE_S16 / 32, 512, 8
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        CAMERA_NOISE_S16 / 32, 1024, 128
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL, NULL,
        CAMERA_NOISE_S16 / 32, 4096, 127
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void updateUWRVarianceS16_getTestParams(updateUWRVarianceS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(updateUWRVarianceS16_testParams_t);
}

