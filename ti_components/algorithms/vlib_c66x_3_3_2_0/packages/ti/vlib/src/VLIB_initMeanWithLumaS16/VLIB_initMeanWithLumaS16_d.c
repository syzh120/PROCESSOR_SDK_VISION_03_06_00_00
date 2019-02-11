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

#include "../common/VLIB_test.h"
#include "../common/VLIB_memory.h"
#include "../common/VLIB_profile.h"

#include "VLIB_initMeanWithLumaS16.h"
#include "VLIB_initMeanWithLumaS16_cn.h"
#include "VLIB_initMeanWithLumaS16_idat.h"

/* VLIB_updateEWRMeanS16_d:  Test Driver Routine */
void VLIB_initMeanWithLumaS16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    initMeanWithLumaS16_testParams_t   *prm;

    initMeanWithLumaS16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_initMeanWithLumaS16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint8_t   *lumaFrame       =  (uint8_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(uint8_t));
        int16_t   *runningMean     =  (int16_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(int16_t));
        int16_t   *runningMean_cn  =  (int16_t *) malloc(prm[tpi].pixelCount * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( lumaFrame && runningMean && runningMean_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint16_t)1,
                            lumaFrame, prm[tpi].staticIn,
                            prm[tpi].pixelCount, 1, prm[tpi].pixelCount * sizeof(lumaFrame[0]),
                            sizeof(lumaFrame[0]), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_initMeanWithLumaS16(runningMean, lumaFrame, prm[tpi].pixelCount);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_initMeanWithLumaS16_cn(runningMean_cn, lumaFrame, prm[tpi].pixelCount);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) runningMean, (void *)runningMean_cn, prm[tpi].pixelCount * sizeof(runningMean_cn[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)runningMean_cn, prm[tpi].pixelCount * sizeof(runningMean_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | pixelCount=%d",
                    testPatternString, prm[tpi].pixelCount);
            VLIB_formula_add_test(prm[tpi].pixelCount, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "pixelCount=%d",
                    prm[tpi].pixelCount);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(runningMean_cn);
        VLIB_free(runningMean);
        VLIB_free(lumaFrame);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = pixelCount",
                              "pixelCount");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_initMeanWithLumaS16");
    } else {
        VLIB_initMeanWithLumaS16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_initMeanWithLumaS16_d.c                              */
/* ======================================================================== */

