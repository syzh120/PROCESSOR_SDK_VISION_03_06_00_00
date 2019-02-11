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
#include "VLIB_L2_norm_i32_idat.h"

static uint32_t    staticRefIn[] = { 1, 32, 64, 10, 22, 5, 45, 32, 99, 250 };

static L2_norm_i32_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, staticOut,
           len
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, 0.0,
        10
    },
    {
        CONSTANT,
        NULL, 0.0,
        32
    },
    {
        RANDOM,
        NULL, 0.0,
        64
    },
    {
        RANDOM,
        NULL, 0.0,
        128
    },
    {
        RANDOM,
        NULL, 0.0,
        256
    },
    {
        RANDOM,
        NULL, 0.0,
        1024
    },
    {
        RANDOM,
        NULL, 0.0,
        4096
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void L2_norm_i32_getTestParams(L2_norm_i32_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(L2_norm_i32_testParams_t);
}

