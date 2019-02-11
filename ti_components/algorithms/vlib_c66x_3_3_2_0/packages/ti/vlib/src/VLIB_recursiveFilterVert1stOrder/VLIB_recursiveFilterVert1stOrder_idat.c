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
#include "VLIB_recursiveFilterVert1stOrder_idat.h"

static uint8_t    staticRefOut[] =
{
    128, 139, 152, 163, 176, 187, 200, 211,
    139, 141, 161, 163, 187, 188, 209, 211,
    151, 162, 153, 163, 198, 209, 200, 211,
    163, 164, 164, 166, 208, 209, 209, 211,
    175, 185, 197, 208, 178, 188, 200, 211,
    187, 188, 209, 211, 187, 189, 209, 211,
    199, 209, 200, 211, 199, 210, 200, 211,
    210, 211, 210, 211, 210, 211, 210, 211
};

static uint8_t    boundaryT[] =
{
    128, 139, 151, 163, 175, 187, 199, 210, 139, 141, 162, 164, 185, 188, 209, 211,
    128, 139, 151, 163, 175, 187, 199, 210, 139, 141, 162, 164, 185, 188, 209, 211
};

static uint8_t    boundaryB[] =
{
    152, 161, 153, 164, 197, 209, 200, 210, 163, 163, 163, 166, 208, 211, 211, 211,
    152, 161, 153, 164, 197, 209, 200, 210, 163, 163, 163, 166, 208, 211, 211, 211
};

static recursiveFilterVert1stOrder_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut, *boundaryTop, *boundaryBottom
           width, height, weight
        },
    *********************************************/
    {
        CUSTOM,
        NULL, staticRefOut, NULL, NULL,
        8, 8, 0x6fff
    },
    {
        RANDOM,
        NULL, NULL, boundaryT, boundaryB,
        32, 16, 0x6fff
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        16, 32, 0x6fff
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        64, 32, 0x7fff
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        48, 64, 0x7fff
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        64, 48, 0x7fff
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        160, 120, 0x0
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        320, 240, 0x80
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void recursiveFilterVert1stOrder_getTestParams(recursiveFilterVert1stOrder_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(recursiveFilterVert1stOrder_testParams_t);
}

