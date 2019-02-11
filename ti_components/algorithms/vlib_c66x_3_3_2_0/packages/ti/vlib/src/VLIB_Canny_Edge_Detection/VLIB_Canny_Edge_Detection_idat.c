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
 **|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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
#include "VLIB_Canny_Edge_Detection_idat.h"

extern uint8_t    gTITexasLogo[4096];
extern uint8_t    gTITexasLogoCannyRef[4096];

static canny_testParams_t    testParams[]=
{
    /********************************************
         testPattern,
        *input, *refOutput, refNumItems,
         width, height
    *********************************************/
    {
        STATIC,
        gTITexasLogo, gTITexasLogoCannyRef, 307,
        64, 64
    },
    {
        CONSTANT,
        NULL, NULL, 0,
        32, 15
    },
    {
        RANDOM,
        NULL, NULL, 0,
        18, 12
    },
    {
        RANDOM,
        NULL, NULL, 0,
        30, 12
    },
    {
        RANDOM,
        NULL, NULL, 0,
        36, 100
    },
    {
        RANDOM,
        NULL, NULL, 0,
        38, 110
    },
    {
        RANDOM,
        NULL, NULL, 0,
        160, 120
    },
    {
        RANDOM,
        NULL, NULL, 0,
        162, 241
    },
    {
        RANDOM,
        NULL, NULL, 0,
        320, 240
    },
    {
        RANDOM,
        NULL, NULL, 0,
        640, 480
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void canny_getTestParams(canny_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(canny_testParams_t);
}

