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
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
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

#include "../VLIB_kalmanFilter_2x4_Predict/VLIB_kalmanFilter_2x4_Predict_cn.h"

#include "VLIB_kalmanFilter_2x4_Correct.h"
#include "VLIB_kalmanFilter_2x4_Correct_cn.h"
#include "VLIB_kalmanFilter_2x4_Correct_idat.h"

/* VLIB_kalmanFilter_2x4_Correct_d:  Test Driver Routine */
void VLIB_kalmanFilter_2x4_Correct_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    kalmanFilter_2x4_Correct_testParams_t   *prm;

    kalmanFilter_2x4_Correct_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_kalmanFilter_2x4_Correct");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        int16_t                 *Z           = (int16_t *) VLIB_memalign(8, 2 * sizeof(int16_t));
        int16_t                 *Z_buffer    = (int16_t *) memalign(8, prm[tpi].numMeasurements * 2 * sizeof(int16_t));
        int16_t                 *Residual    = (int16_t *) VLIB_memalign(8, 2 * sizeof(int16_t));
        int16_t                 *Residual_cn = (int16_t *) memalign(8, 2 * sizeof(int16_t));
        VLIB_kalmanFilter_2x4   *KF          = (VLIB_kalmanFilter_2x4 *) VLIB_memalign(8, sizeof(VLIB_kalmanFilter_2x4));
        VLIB_kalmanFilter_2x4   *KF_cn       = (VLIB_kalmanFilter_2x4 *) memalign(8, sizeof(VLIB_kalmanFilter_2x4));

        /* Only run the test if the buffer allocations fit in the heap */
        if( Z && Z_buffer && Residual && Residual_cn && KF && KF_cn ) {

            int32_t    fail, i, index;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)1,
                            Z_buffer, prm[tpi].staticIn,
                            prm[tpi].numMeasurements * 2, 1, prm[tpi].numMeasurements * 2 * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            memset(KF, 0, sizeof(VLIB_kalmanFilter_2x4));
            memset(KF_cn, 0, sizeof(VLIB_kalmanFilter_2x4));

            /* initialize matrices for both optimized and natural c versions */
            for( i=0; i < sD_2x4; i++ ) {
                index = i * sD_2x4 + i;
                KF->errorCov[index]   = KF_cn->errorCov[index]   = 1000 * INT16_MAX / VLIB_MAX_13p2;
                KF->transition[index] = KF_cn->transition[index] = 1;
                if( i < mD_2x4 ) {
                    KF->measurement[index] = KF_cn->measurement[index] = 1;
                }
            }

            KF->measurementNoiseCov[0] = KF_cn->measurementNoiseCov[0] = 8100; /* * INT16_MAX / VLIB_MAX_13p2; */
            KF->measurementNoiseCov[3] = KF_cn->measurementNoiseCov[3] = 8100; /* * INT16_MAX / VLIB_MAX_13p2; */

            KF->transition[2] = KF_cn->transition[2] = 1;
            KF->transition[7] = KF_cn->transition[7] = 1;

            KF->processNoiseCov[0]  = KF_cn->processNoiseCov[0]  = 0.333 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[1]  = KF_cn->processNoiseCov[1]  = 0.50 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[4]  = KF_cn->processNoiseCov[4]  = 0.50 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[5]  = KF_cn->processNoiseCov[5]  = 1.0 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[10] = KF_cn->processNoiseCov[10] = 0.333 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[11] = KF_cn->processNoiseCov[11] = 0.50 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[14] = KF_cn->processNoiseCov[14] = 0.50 * INT16_MAX / VLIB_MAX_13p2;
            KF->processNoiseCov[15] = KF_cn->processNoiseCov[15] = 1.0 * INT16_MAX / VLIB_MAX_13p2;

            for( i=0; i < prm[tpi].numMeasurements; i++ ) {

                /* kalman predict */
                VLIB_kalmanFilter_2x4_Predict_cn(KF);  // The natC version is used so that the code size doesn't get counted
                VLIB_kalmanFilter_2x4_Predict_cn(KF_cn);

                /* get measurement */
                memcpy(Z, Z_buffer + 2 * i, sizeof(int16_t) * 2);
                Z[0] = Z[0] * INT16_MAX / VLIB_MAX_10p5;
                Z[1] = Z[1] * INT16_MAX / VLIB_MAX_10p5;

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_kalmanFilter_2x4_Correct(KF, Z, Residual);
                VLIB_profile_stop();

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_kalmanFilter_2x4_Correct_cn(KF_cn, Z, Residual_cn);
                VLIB_profile_stop();
            }

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) &KF->state[0], (void *) &KF_cn->state[0], 4 * sizeof(int16_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)&KF_cn->state[0], 4 * sizeof(int16_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | num_measurements=%d",
                    testPatternString, prm[tpi].numMeasurements);
            VLIB_formula_add_test(prm[tpi].numMeasurements, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "num_measurements=%d",
                    prm[tpi].numMeasurements);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        align_free(KF_cn);
        VLIB_align_free(KF);
        align_free(Residual_cn);
        VLIB_align_free(Residual);
        align_free(Z_buffer);
        VLIB_align_free(Z);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = number of measurements",
                              "number of measurements");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_kalmanFilter_2x4_Correct");
    } else {
        VLIB_kalmanFilter_2x4_Correct_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_2x4_Correct_d.c                         */
/* ======================================================================== */

