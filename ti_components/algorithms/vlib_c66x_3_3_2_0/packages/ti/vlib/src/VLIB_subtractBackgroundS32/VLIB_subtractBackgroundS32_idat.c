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
#include "VLIB_subtractBackgroundS32_idat.h"

#define CAMERA_NOISE_S32      0x00A00000    /* SQ16.15 */
#define THRESHOLD_FACTOR_S32  0x31fffff9    /* SQ4.27 */

static uint8_t    prevLuma32[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16,
    32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 0, 0
};

static uint32_t    sequential32packed[1] = { 0x03E0FFFF };

static subtractBackgroundS32_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInLuma, *staticInPrevLuma, *staticOutMask,
           thresholdGlobal, thresholdFactor, PixelCount
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL, prevLuma32, sequential32packed,
        CAMERA_NOISE_S32 / 32, THRESHOLD_FACTOR_S32 / 2, 32
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        CAMERA_NOISE_S32 / 32, THRESHOLD_FACTOR_S32 / 2, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        CAMERA_NOISE_S32 / 32, THRESHOLD_FACTOR_S32 / 2, 128
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        CAMERA_NOISE_S32 / 32, THRESHOLD_FACTOR_S32 / 2, 512
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        CAMERA_NOISE_S32 / 32, THRESHOLD_FACTOR_S32 / 2, 1024
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        CAMERA_NOISE_S32 / 32, THRESHOLD_FACTOR_S32 / 2, 4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void subtractBackgroundS32_getTestParams(subtractBackgroundS32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(subtractBackgroundS32_testParams_t);
}

