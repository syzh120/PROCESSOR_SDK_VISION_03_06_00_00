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
#include "VLIB_grayscale_morphology_idat.h"

static uint8_t    se_random[] =
{
    1,  1,  0,  1,  0,  1,  1,  0,  0,  1,  0,
    0,  0,  1,  1,  1,  0,  1,  1,  1,  0,  1,
    0,  1,  0,  0,  1,  1,  0,  1,  1,  0,  0,
    1,  0,  0,  1,  1,  1,  1,  0,  1,  1,  0,
    0,  1,  1,  1,  1,  1,  1,  0,  1,  0,  1,
    1,  0,  1,  1,  1,  1,  1,  0,  0,  1,  1,
    0,  1,  0,  0,  1,  1,  1,  0,  0,  0,  0,
    1,  0,  0,  1,  0,  1,  0,  1,  1,  1,  1,
    0,  1,  0,  1,  1,  1,  1,  1,  0,  0,  1,
    1,  1,  0,  1,  0,  1,  1,  0,  1,  0,  1,
    1,  1,  0,  0,  1,  1,  1,  1,  0,  0,  1,
};

static uint8_t    se_reflec_random[] =
{
    1,  0,  1,  1,  1,  1,  1,  0,  0,  1,  1,
    0,  1,  0,  0,  1,  1,  0,  1,  1,  0,  0,
    1,  0,  0,  1,  1,  1,  1,  0,  1,  1,  0,
    0,  1,  0,  0,  1,  1,  1,  0,  0,  0,  0,
    1,  1,  0,  0,  1,  1,  1,  1,  0,  0,  1,
    1,  0,  0,  1,  0,  1,  0,  1,  1,  1,  1,
    1,  1,  0,  1,  0,  1,  1,  0,  0,  1,  0,
    0,  1,  1,  1,  1,  1,  1,  0,  1,  0,  1,
    0,  0,  1,  1,  1,  0,  1,  1,  1,  0,  1,
    0,  1,  0,  1,  1,  1,  1,  1,  0,  0,  1,
    1,  1,  0,  1,  0,  1,  1,  0,  1,  0,  1,

};

static uint8_t    se_allOne[] =
{
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
};

static grayScaleMorph_testParams_t    testParams[]=
{
    /********************************************
        {
            testPattern,
            *staticIn, *staticOut;
            *se_ptr;
            *se_reflc_ptr;
            imageWidth, imageHeight, imagePitch,
            se_w, se_h,
            *desc
        },
    *********************************************/
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        64, 64, 64,
        3, 3,
        "Mask with all ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_random,
        se_reflec_random,
        64, 64, 64,
        5, 5,
        "Mask with random ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        64, 64, 64,
        3, 5,
        "Mask with all ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_random,
        se_reflec_random,
        64, 64, 64,
        5, 11,
        "Mask with random ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        128, 128, 128,
        1, 3,
        "Mask with all ones :: Special Optmization as  (blk_h-se_h+1)%se_h=0"
    },
    {
        RANDOM,
        NULL, NULL,
        se_random,
        se_reflec_random,
        128, 128, 128,
        3, 1,
        "Mask with random ones  "
    },
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        320, 240, 320,
        11, 11,
        "Mask with all ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_random,
        se_reflec_random,
        320, 240, 320,
        3, 3,
        "Mask with random ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        320, 240, 320,
        3, 3,
        "Mask with all ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_random,
        se_reflec_random,
        322, 241, 322,
        11, 7,
        "Mask with random ones"
    },
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        320, 240, 320,
        1, 13,
        "Mask with all ones"
    },
    /* height is choosen so that Gil-Werman flow can be choosen. performance
       number of this can be compared with previous test case to highlight the
       gain due to this flow*/
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        320, 246, 320,
        1, 13,
        "Mask with all ones : Special Optmization as  (blk_h-se_h+1)%se_h=0"
    },
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        320, 240, 320,
        1, 3,
        "Mask with all ones"
    },
    /* height is choosen so that Gil-Werman flow can be choosen. performance
       number of this can be compared with previous test case to highlight the
       gain due to this flow*/
    {
        RANDOM,
        NULL, NULL,
        se_allOne,
        se_allOne,
        320, 242, 320,
        1, 3,
        "Mask with all ones : Special Optmization as  (blk_h-se_h+1)%se_h=0"
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void grayScaleMorph_getTestParams(grayScaleMorph_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(grayScaleMorph_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

