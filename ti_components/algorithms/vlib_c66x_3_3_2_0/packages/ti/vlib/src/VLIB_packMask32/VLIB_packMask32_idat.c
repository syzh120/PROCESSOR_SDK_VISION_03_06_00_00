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
#include "VLIB_packMask32_idat.h"

static uint8_t    staticRefIn[] =
{
    0, 0, 0, 0,  1, 1, 1, 1,  0, 0, 0, 0,  1, 0, 1, 0,  0, 0, 0, 0,  0, 1, 0, 1,  0, 0, 0, 0,  1, 1, 1, 1,
    1, 1, 1, 1,  0, 0, 0, 0,  1, 0, 1, 0,  0, 0, 0, 0,  0, 1, 0, 1,  0, 0, 0, 0,  1, 1, 1, 1,  0, 0, 0, 0
};

static uint32_t    staticRefOut[] =
{
    0x0F0A050F, 0xF0A050F0
};

static packMask32_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           pixelCount
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOut,
        64
    },
    {
        CONSTANT,
        NULL, NULL,
        128
    },
    {
        RANDOM,
        NULL, NULL,
        256
    },
    {
        RANDOM,
        NULL, NULL,
        480
    },
    {
        RANDOM,
        NULL, NULL,
        640
    },
    {
        RANDOM,
        NULL, NULL,
        1280
    },
    {
        RANDOM,
        NULL, NULL,
        2600
    },
    {
        RANDOM,
        NULL, NULL,
        4800
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void packMask32_getTestParams(packMask32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(packMask32_testParams_t);
}

