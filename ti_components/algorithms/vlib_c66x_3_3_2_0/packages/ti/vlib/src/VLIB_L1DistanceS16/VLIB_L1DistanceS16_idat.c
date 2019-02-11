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
#include "VLIB_L1DistanceS16_idat.h"

static int16_t    H1[] = { 100, 200, -100, 5, 23, 10, 4, 33 };
static int16_t    H2[] = { 28, -10, -100, 32767, -32757, 0, 1, -28 };

static L1DistanceS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn1, *staticIn2, *staticOut,
           d
        },
    *********************************************/
    {
        STATIC,
        H1, H2, 65885,
        8
    },
    {
        CONSTANT,
        NULL, NULL, NULL,
        32
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        256
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        1024
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void L1DistanceS16_getTestParams(L1DistanceS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(L1DistanceS16_testParams_t);
}

