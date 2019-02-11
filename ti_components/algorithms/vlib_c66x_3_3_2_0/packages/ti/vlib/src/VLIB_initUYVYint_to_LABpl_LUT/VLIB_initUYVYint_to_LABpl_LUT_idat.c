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
#include "VLIB_initUYVYint_to_LABpl_LUT_idat.h"

static int16_t     coeff[5] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };
static VLIB_F32    whitePoint[3] = { 0.950456, 1.0, 1.088754 }; /* D65 */

static initUYVYint_to_LABpl_LUT_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticOut, *coeff, *whitePoint, d
        },
    *********************************************/
    /* NOTE: LUT size for d values < 2 won't fit in the heap that we are using in the
     * test framework (8MB) */
    {
        STATIC,
        NULL, coeff, whitePoint, 4,
    },
    {
        STATIC,
        NULL, coeff, whitePoint, 3,
    },
#ifdef _HOST_BUILD
    {
        STATIC,
        NULL, coeff, whitePoint, 2,
    },
    {
        STATIC,
        NULL, coeff, whitePoint, 1,
    }
#endif
};

/*
 *  Sends the test parameter structure and number of tests
 */
void initUYVYint_to_LABpl_LUT_getTestParams(initUYVYint_to_LABpl_LUT_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(initUYVYint_to_LABpl_LUT_testParams_t);
}

