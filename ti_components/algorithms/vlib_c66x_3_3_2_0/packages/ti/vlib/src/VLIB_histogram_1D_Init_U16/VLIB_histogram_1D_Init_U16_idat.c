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
#include "VLIB_histogram_1D_Init_U16_idat.h"

static uint16_t    binEdges0[] =
{
    0,  26,  52,  78, 104, 130, 156, 182, 208, 234
};
static uint16_t    binEdges1[] =
{
    0, 7, 16, 19
};

static uint16_t    binEdges2[] =
{
    0, 100, 250
};

static uint16_t    binEdges3[] =
{
    120, 129, 132, 139, 145, 150, 157, 166, 172, 177, 183, 187, 190
};

static uint16_t    binEdges4[] =
{
    0, 129, 221, 381, 405, 490, 510
};

static uint16_t    histArray1[] =
{
    1, 1, 1, 1, 1, 1, 1, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 4, 0, 0, 0, 0, 0
};

static histogram_1D_Init_U16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           numBins, maxSize
        },
    *********************************************/
    {
        STATIC,
        binEdges0, NULL,
        sizeof(binEdges0) / sizeof(binEdges0[0]), 250
    },
    {
        STATIC,
        binEdges1, histArray1,
        sizeof(binEdges1) / sizeof(binEdges1[0]), 25
    },
    {
        STATIC,
        binEdges2, NULL,
        sizeof(binEdges2) / sizeof(binEdges2[0]), 256
    },
    {
        STATIC,
        binEdges3, NULL,
        sizeof(binEdges3) / sizeof(binEdges3[0]), 240
    },
    {
        STATIC,
        binEdges4, NULL,
        sizeof(binEdges4) / sizeof(binEdges4[0]), 512
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void histogram_1D_Init_U16_getTestParams(histogram_1D_Init_U16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(histogram_1D_Init_U16_testParams_t);
}

