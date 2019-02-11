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
#include "VLIB_harrisScore_7x7_idat.h"

static harrisScore_7x7_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           width, height,
           k,
           *desc
        },
    *********************************************/
    {
        CUSTOM,
        NULL, NULL,
        64, 64,
        1310,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        48, 64,
        1310,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        32, 64,
        1310,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        32, 32,
        1310,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        320, 240,
        1310,
        NULL
    },
    {
        CUSTOM,
        NULL, NULL,
        320, 240,
        1600,
        NULL
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void harrisScore_7x7_getTestParams(harrisScore_7x7_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(harrisScore_7x7_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

