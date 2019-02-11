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
#include "VLIB_recursiveFilterHoriz1stOrderS16_idat.h"

static int16_t    staticRefOut[] =
{
    5128, 5139, 5151, 5163, 5175, 5187, 5199, 5210,
    5139, 5141, 5162, 5165, 5186, 5189, 5210, 5211,
    5152, 5162, 5153, 5165, 5197, 5210, 5201, 5211,
    5163, 5163, 5164, 5166, 5208, 5211, 5211, 5211,
    5176, 5187, 5199, 5208, 5178, 5188, 5199, 5210,
    5187, 5189, 5210, 5210, 5189, 5189, 5210, 5211,
    5200, 5210, 5200, 5210, 5200, 5210, 5201, 5211,
    5211, 5211, 5211, 5211, 5211, 5211, 5211, 5211
};

static int16_t    boundaryL[] =
{
    128, 139, 151, 163, 175, 187, 199, 210, 139, 141, 162, 164, 185, 188, 209, 211
};

static int16_t    boundaryR[] =
{
    152, 161, 153, 164, 197, 209, 200, 210, 163, 163, 163, 166, 208, 211, 211, 211
};

static recursiveFilterHoriz1stOrderS16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut, *boundaryLeft, *boundaryRight
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
        NULL, NULL, boundaryL, boundaryR,
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
void recursiveFilterHoriz1stOrderS16_getTestParams(recursiveFilterHoriz1stOrderS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(recursiveFilterHoriz1stOrderS16_testParams_t);
}

