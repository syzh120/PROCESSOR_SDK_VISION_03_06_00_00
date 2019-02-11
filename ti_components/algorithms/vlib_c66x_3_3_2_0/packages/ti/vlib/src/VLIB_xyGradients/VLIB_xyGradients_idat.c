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
#include "VLIB_xyGradients_idat.h"

/* When SEQUENTIAL is selected as input type for the first vector, the test
 * framework produces the following input array, shown here for easy reference
 *
 * static uint8_t    staticRefInput[]=
 * {
 *     1,  2,  3,  4,  5,  6,  7, 8,
 *     9, 10, 11, 12, 13, 14, 15, 16,
 *    17, 18, 19, 20, 21, 22, 23, 24,
 *    25, 26, 27, 28, 29, 30, 31, 32
 * };
 */

static int16_t    staticRefOutGradX[]=
{
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
};

static int16_t    staticRefOutGradY[]=
{
    16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 0
};

static xyGradients_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn,
           *staticOutpGradX, *staticOutpGradY,
           width, height
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL,
        staticRefOutGradX, staticRefOutGradY,
        8, 4
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        8, 4
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        16, 8
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        32, 16
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        64, 32 - 1
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        128, 64
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        320, 240
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        328, 233
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void xyGradients_getTestParams(xyGradients_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(xyGradients_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

