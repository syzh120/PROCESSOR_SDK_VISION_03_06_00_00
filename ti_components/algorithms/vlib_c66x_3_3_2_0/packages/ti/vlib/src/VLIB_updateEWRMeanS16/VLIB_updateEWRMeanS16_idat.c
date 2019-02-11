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
#include "VLIB_updateEWRMeanS16_idat.h"

#define IIR_ALPHA_S16         0x10          /* SQ0.15 */

static uint32_t    mask32packed32[] = { 0x03E0FFFF };

static uint8_t    prevLuma32[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16,
    32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 0, 0
};

static int16_t    sequentialMean32[] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0800, 0x0800, 0x0800, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF,
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000
};

static updateEWRMeanS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInLuma, *staticInMask, *staticInPrevLuma, *staticOutMean,
           weight, pixelCount
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL, mask32packed32, prevLuma32, sequentialMean32,
        IIR_ALPHA_S16, 32
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, 72
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, 512
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, 1024
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, 4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void updateEWRMeanS16_getTestParams(updateEWRMeanS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(updateEWRMeanS16_testParams_t);
}

