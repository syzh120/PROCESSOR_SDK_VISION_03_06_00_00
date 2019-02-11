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
#include "VLIB_trackFeaturesLucasKanade_7x7_idat.h"

static uint16_t    inFeaturePointX[8]     = { 15.3f * 16, 25.2f * 16, 49.0f * 16,
                                              20.2f * 16, 3.2f * 16,  3.2f * 16,
                                              0.0f  * 16, 16.0f  * 16, };
static uint16_t    inFeaturePointY[8]     = { 14.7f * 16, 32.9f * 16, 32.1f * 16,
                                              40.9f * 16, 3.2f * 16, 3.2f * 16,
                                              0.0f  * 16, 16.0f  * 16, };

static uint16_t    outFeaturePointX[8]     = { 16.25f * 16, 25.9375f * 16, 49.875f * 16,
                                               20.8125f * 16, 0xFFFF,  0xFFFF,
                                               0xFFFF, 16.875f * 16 };
static uint16_t    outFeaturePointY[8]     = { 15.6875f * 16, 33.8125f * 16, 32.875f * 16,
                                               41.9375f * 16, 0xFFFF, 0xFFFF,
                                               0xFFFF, 16.875f * 16 };

static uint16_t    estFeaturePointX[8]     = { 16.0f * 16, 25.5f * 16, 49.5f * 16,
                                               20.7f * 16, 3.1f * 16,  3.1f * 16,
                                               0.0f  * 16, 16.0f  * 16, };
static uint16_t    estFeaturePointY[8]     = { 15.7f * 16, 33.3f * 16, 32.8f * 16,
                                               41.5f * 16, 3.1f * 16, 3.2f * 16,
                                               0.0f  * 16, 16.0f  * 16, };

static uint16_t    outError[8]             = { 0x0, 0xa, 0x5, 0x6,
                                               0xffff, 0xffff, 0xffff, 0x3, };

static trackFeaturesLK_7x7_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn1, *staticIn2,
           width, height,pitch, nfeatures,
           *x, *y,
           *outx, *outy, *outError,
           max_iters,earlyExitTh,gradFlag, outEstFlag,
           desc
        },
    *********************************************/
    {
        CUSTOM,
        NULL, NULL,
        64, 64, 64, 8,
        inFeaturePointX, inFeaturePointY,
        outFeaturePointX, outFeaturePointY, outError,
        10, 0, 1, 0,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        64, 64, 64, 8,
        inFeaturePointX, inFeaturePointY,
        outFeaturePointX, outFeaturePointY, outError,
        10, 0, 0, 0,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        64, 64, 64, 8,
        inFeaturePointX, inFeaturePointY,
        outFeaturePointX, outFeaturePointY, outError,
        10, 1, 0, 0,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        64, 64, 64, 8,
        inFeaturePointX, inFeaturePointY,
        outFeaturePointX, outFeaturePointY, outError,
        10, 1, 1, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        64, 64, 64, 2,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        50, 0, 0, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        64, 64, 64, 2,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        50, 0, 1, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        176, 144, 176, 2,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        50, 1, 1, 0,
        NULL
    },
    {
        SEQUENTIAL,
        NULL, NULL,
        80, 80, 80, 8,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        50, 1, 0, 0,
        NULL
    },
    {
        CONSTANT,
        NULL, NULL,
        81, 81, 81, 8,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        20, 1, 0, 0,
        NULL
    },

    {
        RANDOM,
        NULL, NULL,
        181, 181, 181, 8,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        200, 0, 0, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        181, 181, 181, 8,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        20, 0, 1, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240, 320, 8,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        20, 0, 1, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240, 320, 8,
        inFeaturePointX, inFeaturePointY,
        NULL, NULL, NULL,
        20, 0, 1, 0,
        NULL
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240, 320, 8,
        inFeaturePointX, inFeaturePointY,
        estFeaturePointX, estFeaturePointY, NULL,
        20, 0, 1, 1,
        NULL
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void trackFeaturesLK_7x7_getTestParams(trackFeaturesLK_7x7_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(trackFeaturesLK_7x7_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

