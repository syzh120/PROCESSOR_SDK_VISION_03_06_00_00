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

#include "VLIB_histogram_equal_8.h"
#include "VLIB_histogram_equal_8_cn.h"
#include "VLIB_histogram_equal_8_idat.h"

/* VLIB_histogram_equal_8_d:  Test Driver Routine */
void VLIB_histogram_equal_8_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    histogram_equal_8_testParams_t   *prm;

    histogram_equal_8_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_histogram_equal_8");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint8_t   *image            =  (uint8_t *) VLIB_malloc(prm[tpi].n * sizeof(uint8_t));
        int16_t   *t_hist           =  (int16_t *) VLIB_malloc(2048);
        uint8_t   *histeq_image     =  (uint8_t *) VLIB_malloc(prm[tpi].n * sizeof(uint8_t));
        uint8_t   *histeq_image_cn  =  (uint8_t *) malloc(prm[tpi].n * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( image && t_hist && histeq_image && histeq_image_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            image, prm[tpi].staticIn,
                            prm[tpi].n, 1, prm[tpi].n * sizeof(image[0]),
                            sizeof(image[0]), testPatternString);

            /* Clear the histArray output, as per fn requirement */
            memset(t_hist, 0, 2048);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_histogram_equal_8(image, prm[tpi].n, t_hist, histeq_image);
            VLIB_profile_stop();

            /* Clear the histArray output, as per fn requirement */
            memset(t_hist, 0, 2048);

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_histogram_equal_8_cn(image, prm[tpi].n, t_hist, histeq_image_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) histeq_image, (void *)histeq_image_cn, prm[tpi].n * sizeof(histeq_image_cn[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)histeq_image_cn, prm[tpi].n * sizeof(histeq_image_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | n=%d",
                    testPatternString, prm[tpi].n);
            VLIB_formula_add_test(prm[tpi].n, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "n=%d",
                    prm[tpi].n);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(histeq_image_cn);
        VLIB_free(histeq_image);
        VLIB_free(t_hist);
        VLIB_free(image);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = n",
                              "n");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_histogram_equal_8");
    } else {
        VLIB_histogram_equal_8_d(0);
    }
}
#endif /* __ONESHOTTEST */
/* ======================================================================== */
/*  End of file:  VLIB_histogram_equal_8_d.c                                */
/* ======================================================================== */

