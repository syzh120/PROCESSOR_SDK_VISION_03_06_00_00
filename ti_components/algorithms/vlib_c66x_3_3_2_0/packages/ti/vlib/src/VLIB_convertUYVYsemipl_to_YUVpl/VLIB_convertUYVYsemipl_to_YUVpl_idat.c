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
#include "VLIB_convertUYVYsemipl_to_YUVpl_idat.h"

static uint8_t    staticRefIn[32] =
{
    1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
};

static uint8_t    staticRefOutCr[16] =
{
    1,  3,  5,  7,  9, 11, 13, 15,
    17, 19, 21, 23, 25, 27, 29, 31
};

static uint8_t    staticRefOutCb[16] =
{
    2,  4,  6,  8, 10, 12, 14, 16,
    18, 20, 22, 24, 26, 28, 30, 32
};

static UYVYsemipl_to_YUVpl_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOutCr, *staticOutCb
           width, pitch, height
        },
    *********************************************/
    /* pitch == width*/
    {
        STATIC,
        staticRefIn, staticRefOutCr, staticRefOutCb,
        16, 16, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 64, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128, 128, 54
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 320, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 640, 480
    },
    /* pitch > width*/
    {
        RANDOM,
        NULL, NULL, NULL,
        16, 24, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 72, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128, 136, 54
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 328, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 648, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void UYVYsemipl_to_YUVpl_getTestParams(UYVYsemipl_to_YUVpl_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(UYVYsemipl_to_YUVpl_testParams_t);
}

