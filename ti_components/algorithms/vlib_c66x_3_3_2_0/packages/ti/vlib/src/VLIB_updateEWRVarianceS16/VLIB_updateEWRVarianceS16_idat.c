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
#include "VLIB_updateEWRVarianceS16_idat.h"

#define IIR_ALPHA_S16         0x10          /* SQ0.15 */
#define CAMERA_NOISE_S16      0x0A00        /* SQ12.3 */

static uint32_t    mask32packed32[] = { 0x03E0FFFF };

static uint8_t    prevLuma32[] =
{
    200, 200, 200, 200, 200, 200, 200, 200, 16, 16, 16, 16, 16, 16, 16, 16,
    32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64, 0, 0
};

static int16_t    sequentialVar32[] =
{
    0x0063, 0x0063, 0x0063, 0x0062, 0x0062, 0x0062, 0x0050, 0x0050,
    0x0050, 0x0050, 0x0050, 0x0050, 0x004F, 0x004F, 0x004F, 0x004F,
    0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050,
    0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050, 0x0050
};

static updateEWRVarianceS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInLuma, *staticInMask, *staticInPrevLuma, *staticOutMean,
           weight, constant, pixelCount
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL, mask32packed32, prevLuma32, sequentialVar32,
        IIR_ALPHA_S16, CAMERA_NOISE_S16 / 32, 32
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, CAMERA_NOISE_S16 / 32, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, CAMERA_NOISE_S16 / 32, 72
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, CAMERA_NOISE_S16 / 32, 512
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, CAMERA_NOISE_S16 / 32, 1024
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        IIR_ALPHA_S16, CAMERA_NOISE_S16 / 32, 4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void updateEWRVarianceS16_getTestParams(updateEWRVarianceS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(updateEWRVarianceS16_testParams_t);
}

