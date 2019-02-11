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
#include "VLIB_nonMaxSuppress_5x5_S16_idat.h"

/* Test Vector */
static int16_t    IMAGE[5 * 8] = { 2, 3, 4, 1, 1, 1, 1, 1,
                                   5, 1, 2, 1, 1, 1, 1, 1,
                                   3, 4, 8, 7, 5, 9, 5, 8,
                                   1, 3, 2, 1, 1, 1, 1, 1,
                                   4, 1, 5, 1, 1, 1, 1, 1 };

/* Ground truth */
static uint8_t    TRUTH[] = { 255,   0,   0, 255,   0,   0,   0,   0 };

static nonMaxSuppress_5x5_S16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, staticOut,
           width, height,
           threshold
        },
    *********************************************/
    {
        STATIC,
        IMAGE, TRUTH,
        8, 5,
        5
    },
    {
        RANDOM,
        NULL, NULL,
        20, 18,
        80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        -68
    },
    {
        RANDOM,
        NULL, NULL,
        160, 120,
        80
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240,
        80
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void nonMaxSuppress_5x5_S16_getTestParams(nonMaxSuppress_5x5_S16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(nonMaxSuppress_5x5_S16_testParams_t);
}

