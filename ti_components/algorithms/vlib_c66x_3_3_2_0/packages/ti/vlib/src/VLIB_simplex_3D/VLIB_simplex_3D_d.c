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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#include "VLIB_simplex_3D.h"
#include "VLIB_simplex_3D_cn.h"
#include "VLIB_simplex_3D_idat.h"

/* VLIB_simplex_3D_d:  Test Driver Routine */
void VLIB_simplex_3D_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    simplex_3D_testParams_t   *prm;

    simplex_3D_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_simplex_3D");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */

        /* Allocate buffers for each test vector */
        int16_t   *start       =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *init_step   =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *v           =  (int16_t *) VLIB_malloc(12 * sizeof(int16_t));
        int32_t   *f           =  (int32_t *) VLIB_malloc(4 * sizeof(int32_t));
        int16_t   *vr          =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *ve          =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *vc          =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *vm          =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *minPoint    =  (int16_t *) VLIB_malloc(3 * sizeof(int16_t));
        int16_t   *minPoint_cn =  (int16_t *) malloc(3 * sizeof(int16_t));
        int32_t    minValue;
        int32_t    minValue_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( start && init_step && v && f && vr && ve && vc && vm && minPoint && minPoint_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)255,
                            start, prm[tpi].start,
                            3, 1, 3 * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)255,
                            init_step, prm[tpi].init_step,
                            3, 1, 3 * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_simplex_3D(prm[tpi].func,
                            start, init_step,
                            prm[tpi].MaxIteration,
                            prm[tpi].EPSILON,
                            v, f, vr, ve, vc, vm,
                            prm[tpi].addtlArgs,
                            minPoint, &minValue);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_simplex_3D_cn(prm[tpi].func,
                               start, init_step,
                               prm[tpi].MaxIteration,
                               prm[tpi].EPSILON,
                               v, f, vr, ve, vc, vm,
                               (void *)prm[tpi].addtlArgs,
                               minPoint_cn, &minValue_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) minPoint, (void *)minPoint_cn, 3 * sizeof(int16_t));
            if( minValue != minValue_cn ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].refMinPoint != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].refMinPoint, (void *)minPoint_cn, 3 * sizeof(int16_t));
                if( prm[tpi].refMinValue != minValue_cn ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | MaxIteration=%d, EPSILON=%d",
                    testPatternString, prm[tpi].MaxIteration, prm[tpi].EPSILON);
            VLIB_formula_add_test(1, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "MaxIteration=%d, EPSILON=%d",
                    prm[tpi].MaxIteration, prm[tpi].EPSILON);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(minPoint_cn);
        VLIB_free(minPoint);
        VLIB_free(vm);
        VLIB_free(vc);
        VLIB_free(ve);
        VLIB_free(vr);
        VLIB_free(f);
        VLIB_free(v);
        VLIB_free(init_step);
        VLIB_free(start);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "Performance number includes iterations of cost function");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_simplex_3D");
    } else {
        VLIB_simplex_3D_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_simplex_3D_d.c                                       */
/* ======================================================================== */

