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

#include "VLIB_nonMaxSuppress_3x3_S16.h"
#include "VLIB_nonMaxSuppress_3x3_S16_cn.h"
#include "VLIB_nonMaxSuppress_3x3_S16_idat.h"

/* VLIB_nonMaxSuppress_3x3_S16_d:  Test Driver Routine */
void VLIB_nonMaxSuppress_3x3_S16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    nonMaxSuppress_3x3_S16_testParams_t   *prm;

    nonMaxSuppress_3x3_S16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_nonMaxSuppress_3x3_S16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    in_size = prm[tpi].width * prm[tpi].height;
        uint32_t    out_size = prm[tpi].width * (prm[tpi].height - 2); /* Last 2 rows are not written to */

        /* Allocate buffers for each test vector */
        int16_t   *im       =  (int16_t *) VLIB_malloc(in_size * sizeof(int16_t));
        uint8_t   *out      =  (uint8_t *) VLIB_malloc(out_size * sizeof(uint8_t));
        uint8_t   *out_cn   =  (uint8_t *) malloc(out_size * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( im && out && out_cn ) {

            int32_t    fail, i, j;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            im, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_nonMaxSuppress_3x3_S16(im, prm[tpi].width, prm[tpi].height, prm[tpi].threshold, out);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_nonMaxSuppress_3x3_S16_cn(im, prm[tpi].width, prm[tpi].height, prm[tpi].threshold, out_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            /* Only valid region should be compared since the natc doesn't write to non-valid region, but opt version does */
            for( i = 0; i < prm[tpi].height - 2; i++ ) {
                for( j = 0; j < prm[tpi].width - 2; j++ ) {
                    if( out[prm[tpi].width * i + j] != out_cn[prm[tpi].width * i + j] ) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback ) {
                            printf("Error: pixel (row: %d, column: %d) is incorrect!\n", i, j);
                        }
                    }
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            /* Only valid region should be compared since the natc doesn't write to non-valid region, but opt version does */
            if( prm[tpi].staticOut != NULL ) {
                for( i = 0; i < prm[tpi].height - 2; i++ ) {
                    for( j = 0; j < prm[tpi].width - 2; j++ ) {
                        if( prm[tpi].staticOut[prm[tpi].width * i + j] != out_cn[prm[tpi].width * i + j] ) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            if( LevelOfFeedback ) {
                                printf("Error: pixel (row: %d, column: %d) is incorrect!\n", i, j);
                            }
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, out_size=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height, out_size);
            VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, out_size=%d",
                    prm[tpi].width, prm[tpi].height, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(out_cn);
        VLIB_free(out);
        VLIB_free(im);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * (height-2)",
                              "width * (height-2)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_nonMaxSuppress_3x3_S16");
    } else {
        VLIB_nonMaxSuppress_3x3_S16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_nonMaxSuppress_3x3_S16.c                             */
/* ======================================================================== */

