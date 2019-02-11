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

#include "VLIB_L1DistanceS16.h"
#include "VLIB_L1DistanceS16_cn.h"
#include "VLIB_L1DistanceS16_idat.h"

/* VLIB_L1DistanceS16_d:  Test Driver Routine */
void VLIB_L1DistanceS16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    L1DistanceS16_testParams_t   *prm;

    L1DistanceS16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_L1DistanceS16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        int16_t    *X          = (int16_t *) VLIB_malloc(prm[tpi].d * sizeof(int16_t));
        int16_t    *Y          = (int16_t *) VLIB_malloc(prm[tpi].d * sizeof(int16_t));
        uint32_t    L1D;
        uint32_t    L1D_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( X && Y ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)0,
                            X, prm[tpi].staticIn1,
                            prm[tpi].d, 1, prm[tpi].d * sizeof(X[0]),
                            sizeof(X[0]), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)1,
                            Y, prm[tpi].staticIn2,
                            prm[tpi].d, 1, prm[tpi].d * sizeof(Y[0]),
                            sizeof(Y[0]), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_L1DistanceS16(X, Y, prm[tpi].d, &L1D);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_L1DistanceS16_cn(X, Y, prm[tpi].d, &L1D_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            if( L1D != L1D_cn ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                if( prm[tpi].staticOut != L1D_cn ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | d=%d",
                    testPatternString, prm[tpi].d);
            VLIB_formula_add_test(prm[tpi].d, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "d=%d",
                    prm[tpi].d);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(Y);
        VLIB_free(X);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = d",
                              "d");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_L1DistanceS16");
    } else {
        VLIB_L1DistanceS16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_L1DistanceS16_d.c                                    */
/* ======================================================================== */

