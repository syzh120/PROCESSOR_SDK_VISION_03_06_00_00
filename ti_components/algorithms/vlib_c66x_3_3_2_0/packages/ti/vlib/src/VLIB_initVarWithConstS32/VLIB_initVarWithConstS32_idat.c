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
#include "VLIB_initVarWithConstS32_idat.h"

static int32_t    refOut32[] =
{
    0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000,
    0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000,
    0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000,
    0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000, 0x0A000000
};

static initVarWithConstS32_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticOut, constVar, pixelCount
        },
    *********************************************/
    {
        STATIC,
        refOut32, 0x0A000000, 32
    },
    {
        STATIC,
        NULL, 0xAAAAAAAA, 64
    },
    {
        STATIC,
        NULL, 0, 128
    },
    {
        STATIC,
        NULL, 0x7FFFFFFF, 512
    },
    {
        STATIC,
        NULL, 0x12345678, 1024
    },
    {
        STATIC,
        NULL, 0xfffefeee, 4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void initVarWithConstS32_getTestParams(initVarWithConstS32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(initVarWithConstS32_testParams_t);
}

