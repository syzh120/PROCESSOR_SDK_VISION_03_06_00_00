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

#include "VLIB_bhattacharyaDistance_F32.h"
#include "VLIB_bhattacharyaDistance_F32_cn.h"
#include "VLIB_bhattacharyaDistance_F32_idat.h"

#define EPSILON 0.001       /* Degree of accuracy */

/* VLIB_bhattacharyaDistance_F32_d:  Test Driver Routine */
void VLIB_bhattacharyaDistance_F32_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    bhattacharyaDistance_F32_testParams_t   *prm;

    bhattacharyaDistance_F32_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_bhattacharyaDistance_F32");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint16_t   *X_u16  = (uint16_t *) malloc(prm[tpi].N * sizeof(uint16_t));
        uint16_t   *Y_u16  = (uint16_t *) malloc(prm[tpi].N * sizeof(uint16_t));
        VLIB_F32   *X      = (VLIB_F32 *) VLIB_malloc(prm[tpi].N * sizeof(VLIB_F32));
        VLIB_F32   *Y      = (VLIB_F32 *) VLIB_malloc(prm[tpi].N * sizeof(VLIB_F32));
        VLIB_F32    D;
        VLIB_F32    D_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( X_u16 && Y_u16 && X && Y ) {

            int32_t     fail, i;
            uint32_t    sum=0;
            VLIB_F32    sum_inv;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)1,
                            X_u16, prm[tpi].staticIn1,
                            prm[tpi].N, 1, prm[tpi].N * sizeof(X_u16[0]),
                            sizeof(X_u16[0]), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)2,
                            Y_u16, prm[tpi].staticIn2,
                            prm[tpi].N, 1, prm[tpi].N * sizeof(Y_u16[0]),
                            sizeof(Y_u16[0]), testPatternString);

            /* sum all values in the first histogram */
            for( i=0; i < prm[tpi].N; i++ ) {
                sum += X_u16[i];
            }

            if( LevelOfFeedback > 0 ) {
                printf("Before normalization: sum=%u\n", sum);
            }

            VLIB_assert(sum > 0, "Invalid test vector ... sum of X array values should be > 0");

            /* normalize histograms to make sure they sum to 1 */
            for( i=0; i < prm[tpi].N; i++ ) {
                sum_inv=_rcpsp(sum);
                X[i] = (float)(X_u16[i] * sum_inv);
                Y[i] =(float)(Y_u16[i] * sum_inv);
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_bhattacharyaDistance_F32(X, Y, prm[tpi].N, &D);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_bhattacharyaDistance_F32_cn(X, Y, prm[tpi].N, &D_cn);
            VLIB_profile_stop();

            if( LevelOfFeedback > 0 ) {
                printf("OPT =%f\n", D);
                printf("CN  =%f\n", D_cn);
            }

            /* Compare natural C Output and Optimized Output */
            if( abs(D - D_cn) > EPSILON ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != 0x0 ) {
                if( abs(prm[tpi].staticOut - D_cn) > EPSILON ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | N=%d",
                    testPatternString, prm[tpi].N);
            VLIB_formula_add_test(prm[tpi].N, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "N=%d",
                    prm[tpi].N);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(Y);
        VLIB_free(X);
        free(Y_u16);
        free(X_u16);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = N",
                              "N");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_bhattacharyaDistance_F32");
    } else {
        VLIB_bhattacharyaDistance_F32_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_bhattacharyaDistance_F32_d.c                         */
/* ======================================================================== */

