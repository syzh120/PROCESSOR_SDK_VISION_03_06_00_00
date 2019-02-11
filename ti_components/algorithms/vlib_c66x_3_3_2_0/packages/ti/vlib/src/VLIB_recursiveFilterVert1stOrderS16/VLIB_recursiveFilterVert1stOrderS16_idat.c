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
#include "VLIB_recursiveFilterVert1stOrderS16_idat.h"

static int16_t    staticRefOut[] =
{
    5128, 5139, 5152, 5163, 5176, 5187, 5200, 5211,
    5139, 5141, 5162, 5163, 5187, 5189, 5210, 5211,
    5151, 5162, 5153, 5164, 5199, 5210, 5200, 5211,
    5163, 5165, 5165, 5166, 5208, 5210, 5210, 5211,
    5175, 5186, 5197, 5208, 5178, 5189, 5200, 5211,
    5187, 5189, 5210, 5211, 5188, 5189, 5210, 5211,
    5199, 5210, 5201, 5211, 5199, 5210, 5201, 5211,
    5210, 5211, 5211, 5211, 5210, 5211, 5211, 5211
};

static int16_t    randomRefIn[] =
{
    17767, 9158, -26519, 18547, -9135, 23807, -27574, 22764,
    7977, 31949, 22714, -10325, 16882, 7931, -22045, -7866,
    124, 25282, 2132, 10232, 8987, -5656, -12825, 17293,
    3958, 9562, -1746, 29283, -15821, -10337, -15159, 1946,
    -1178, 23858, 20493, -10313, -17871, -7080, 12451, -9894,
    24869, -30371, -20219, -23785, -22440, 23273, -31650, -22316,
    -16981, -29518, -12083, -7994, 30363, -24908, 9300, -31215,
    -15346, 7554, -1932, -31167, -2783, -17091, -29220, -3961
};

static int16_t    boundaryT[] =
{
    128, 139, 151, 163, 175, 187, 199, 210, 139, 141, 162, 164, 185, 188, 209, 211,
    128, 139, 151, 163, 175, 187, 199, 210, 139, 141, 162, 164, 185, 188, 209, 211
};

static int16_t    boundaryB[] =
{
    152, 161, 153, 164, 197, 209, 200, 210, 163, 163, 163, 166, 208, 211, 211, 211,
    152, 161, 153, 164, 197, 209, 200, 210, 163, 163, 163, 166, 208, 211, 211, 211
};

static recursiveFilterVert1stOrderS16_testParams_t    testParams[]=
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
        STATIC,
        randomRefIn, NULL, NULL, NULL,
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
void recursiveFilterVert1stOrderS16_getTestParams(recursiveFilterVert1stOrderS16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(recursiveFilterVert1stOrderS16_testParams_t);
}

