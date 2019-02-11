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
#include "VLIB_updateEWRMeanS32_idat.h"

#define IIR_ALPHA_S32         0x00001000    /* SQ0.31 */

static uint32_t    mask32packed32[] = { 0x03E0FFFF };

static uint8_t    prevLuma32[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16,
    32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 0, 0
};

static int32_t    sequentialMean32[] =
{
    0x00000000, 0x00000010, 0x00000020, 0x00000030,
    0x00000040, 0x00000050, 0x00000000, 0x00000000,
    0x08000000, 0x08000000, 0x08000000, 0x07FFFFAF,
    0x07FFFFBF, 0x07FFFFCF, 0x07FFFFDF, 0x07FFFFEF,
    0x10000000, 0x10000000, 0x10000000, 0x10000000,
    0x10000000, 0x10000000, 0x10000000, 0x10000000,
    0x20000000, 0x20000000, 0x20000000, 0x20000000,
    0x20000000, 0x20000000, 0x00000000, 0x00000000
};

static updateEWRMeanS32_testParams_t    testParams[]=
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
        IIR_ALPHA_S32, 32
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S32, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S32, 72
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S32, 512
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S32, 1024
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S32, 4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void updateEWRMeanS32_getTestParams(updateEWRMeanS32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(updateEWRMeanS32_testParams_t);
}

