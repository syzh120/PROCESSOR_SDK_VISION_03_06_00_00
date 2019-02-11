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
 **|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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
#include "VLIB_hammingDistance_idat.h"

static uint8_t    staticRefIn[] = /* size = (32 * 4) = 128 */
{
    163, 223, 120,  35, 128,   6, 181,  87, 154, 188, 109, 193, 127, 161, 158, 213,  23,  54,  54, 226,  68,  68, 36, 253, 217,  94, 161, 174,  20,  97, 250, 182,
    238, 108, 108, 104, 226, 135, 170,  46, 151, 194,  23,  35,   4, 109, 113, 156,  98,  43, 141, 186, 249, 115, 42, 241, 186, 146, 148, 247, 172,   7, 135, 126,
    71,  105, 193,  94, 132,  37,  23,  64, 198, 108,  64,  70, 183, 163, 175, 211, 215, 173, 230,  30, 224,  61, 97, 209,  55,  41, 203, 240, 121, 214,  99,  14,
    94,  55,  232, 200,  85, 198, 155, 168,  67, 241,  98, 172, 147, 100,  71, 226, 199,  59,  42,  93,  58, 156, 67,  69, 240, 209,  23,   7, 200,  34,  75,  23
};

static uint32_t    staticRefOut0[] = /* size = 4 */
{
    0, 0, 0, 0
};

static uint32_t    staticRefOut1[] = /* size = 4 */
{
    0, 135, 125, 142
};

static hammingDistance_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn1, *staticIn2, *staticOut,
           xSize, ySize, mode, xPitch
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefIn, staticRefOut0,
        32, 4, 0, 32
    },
    {
        STATIC,
        staticRefIn, staticRefIn, staticRefOut1,
        32, 4, 1, 32
    },
    {
        CONSTANT,
        NULL, NULL, NULL,
        256, 4, 0, 256
    },
    {
        CONSTANT,
        NULL, NULL, NULL,
        256, 4, 1, 256
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128, 8, 0, 128
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        128, 7, 1, 128
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 16, 0, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 4, 1, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 8, 0, 32
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        16, 16, 1, 16
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        8, 32, 0, 8
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        4, 64, 1, 4
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void hammingDistance_getTestParams(hammingDistance_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(hammingDistance_testParams_t);
}

