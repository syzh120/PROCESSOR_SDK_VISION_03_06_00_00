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
#include "VLIB_imagePyramid8_idat.h"

static uint8_t    staticRefIn[16 * 8] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255,
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

/* expected output calculated off-line in Matlab */
static uint8_t    staticRefOut[8 * 4 + 4 * 2 + 2 * 1] =
{
    95, 116, 120, 139, 141, 86, 74, 130,
    136, 35, 101, 145, 187, 92, 162, 180,
    95, 116, 120, 139, 141, 86, 74, 130,
    136, 35, 101, 145, 187, 92, 162, 180,
    95, 126, 126, 136,
    95, 126, 126, 136,
    110, 131
};

/* Expected interval image for constant array of 1s */
static uint8_t    staticRefOutOnes[16 * 4 + 8 * 2 + 4 * 1] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1
};

static imagePyramid8_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           inCols, inRows
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOut,
        16, 8
    },
    {
        CONSTANT,
        NULL, staticRefOutOnes,
        32, 8
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48
    },
    {
        RANDOM,
        NULL, NULL,
        104, 56
    },
    {
        RANDOM,
        NULL, NULL,
        112, 64
    },
    {
        RANDOM,
        NULL, NULL,
        320, 160
    },
    {
        RANDOM,
        NULL, NULL,
        640, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void imagePyramid8_getTestParams(imagePyramid8_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(imagePyramid8_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

