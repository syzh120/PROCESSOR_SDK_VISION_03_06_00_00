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

#include "../VLIB_kalmanFilter_1x2_Correct_F32/VLIB_kalmanFilter_1x2_Correct_F32_cn.h"

#include "VLIB_kalmanFilter_1x2_Predict_F32.h"
#include "VLIB_kalmanFilter_1x2_Predict_F32_cn.h"
#include "VLIB_kalmanFilter_1x2_Predict_F32_idat.h"

/* VLIB_kalmanFilter_1x2_Predict_F32_d:  Test Driver Routine */
void VLIB_kalmanFilter_1x2_Predict_F32_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi; /* test parameter index */

    /* Test Parameters */
    VLIB_kalmanFilter_1x2_Predict_F32_testParams_t   *prm;

    VLIB_kalmanFilter_1x2_Predict_F32_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_kalmanFilter_1x2_Predict_F32");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */

        /* Allocate buffers for each test vector */
        VLIB_F32                    *Z           = (VLIB_F32 *) VLIB_memalign(8, 4 * sizeof(VLIB_F32));
        VLIB_F32                    *Z_buffer    = (VLIB_F32 *) malloc(prm[tpi].numMeasurements * 4 * sizeof(VLIB_F32));
        VLIB_F32                    *Residual    = (VLIB_F32 *) VLIB_memalign(8, 4 * sizeof(VLIB_F32));
        VLIB_F32                    *Residual_cn = (VLIB_F32 *) malloc(4 * sizeof(VLIB_F32));
        VLIB_kalmanFilter_1x2_F32   *KF          = (VLIB_kalmanFilter_1x2_F32 *) VLIB_memalign(8, sizeof(VLIB_kalmanFilter_1x2_F32));
        VLIB_kalmanFilter_1x2_F32   *KF_cn       = (VLIB_kalmanFilter_1x2_F32 *) malloc(sizeof(VLIB_kalmanFilter_1x2_F32));

        /* Only run the test if the buffer allocations fit in the heap */
        if( Z && Z_buffer && Residual && Residual_cn && KF && KF_cn ) {

            int32_t    fail, i, index;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            1,
                            Z_buffer, prm[tpi].staticIn,
                            prm[tpi].numMeasurements * 4, 1, prm[tpi].numMeasurements * 4 * sizeof(VLIB_F32),
                            sizeof(VLIB_F32), testPatternString);

            memset(KF, 0, sizeof(VLIB_kalmanFilter_1x2_F32));
            memset(KF_cn, 0, sizeof(VLIB_kalmanFilter_1x2_F32));

            KF->scaleFactor = KF_cn->scaleFactor = 5;

            /* initialize matrices for both optimized and natural c versions */
            for( i=0; i < sD_1x2; i++ ) {
                index = i * sD_1x2 + i;
                KF->errorCov[index]   = KF_cn->errorCov[index]   = 1000;
                KF->transition[index] = KF_cn->transition[index] = 1;
                if( i < mD_1x2 ) {
                    KF->measurement[index] = KF_cn->measurement[index] = 1;
                }
            }

            KF->transition[2]  = KF_cn->transition[2]  = 1;
            KF->measurementNoiseCov[0]  = KF_cn->measurementNoiseCov[0]  = 2500;

            KF->processNoiseCov[0]  = KF_cn->processNoiseCov[0]  = 0.25;
            KF->processNoiseCov[1]  = KF_cn->processNoiseCov[1]  = 0.25;
            KF->processNoiseCov[2]  = KF_cn->processNoiseCov[2]  = 0.25;

            KF->state[0] = KF_cn->state[0] = 190;
            KF->state[1] = KF_cn->state[1] = 190;

            for( i=0; i < prm[tpi].numMeasurements; i++ ) {

                int    j;

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_kalmanFilter_1x2_Predict_F32(KF);
                VLIB_profile_stop();

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_kalmanFilter_1x2_Predict_F32_cn(KF_cn);
                VLIB_profile_stop();

                /* get measurement */
                Z[0] = Z_buffer[i * mD_1x2 + 0];
                Z[1] = Z_buffer[i * mD_1x2 + 1];
                Z[2] = Z_buffer[i * mD_1x2 + 2];
                Z[3] = Z_buffer[i * mD_1x2 + 3];

                VLIB_kalmanFilter_1x2_Correct_F32_cn(KF, Z, Residual); // The natC version is used so that the code size doesn't get counted
                VLIB_kalmanFilter_1x2_Correct_F32_cn(KF_cn, Z, Residual_cn);

                for( j=0; j < 2; j++ ) {

                    /* Compare natural C Output and Optimized Output */
                    if( fabs(KF->state[j] - KF_cn->state[j]) > (0.1)) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = (status_nat_vs_int == vlib_KERNEL_FAIL) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | num_measurements=%d",
                    testPatternString, prm[tpi].numMeasurements);
            VLIB_formula_add_test(prm[tpi].numMeasurements, (int32_t)NULL, (int32_t)NULL, fail, desc, (int32_t)NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "num_measurements=%d",
                    prm[tpi].numMeasurements);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(KF_cn);
        VLIB_align_free(KF);
        free(Residual_cn);
        VLIB_align_free(Residual);
        free(Z_buffer);
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
        VLIB_memError("VLIB_kalmanFilter_1x2_Predict_F32");
    } else {
        VLIB_kalmanFilter_1x2_Predict_F32_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_1x2_predict_F32_d.c                     */
/* ======================================================================== */

