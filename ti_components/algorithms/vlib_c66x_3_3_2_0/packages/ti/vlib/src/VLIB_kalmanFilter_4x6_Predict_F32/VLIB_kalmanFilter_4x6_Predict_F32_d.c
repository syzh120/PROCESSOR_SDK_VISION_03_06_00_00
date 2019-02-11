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

#include "../VLIB_kalmanFilter_4x6_Correct_F32/VLIB_kalmanFilter_4x6_Correct_F32_cn.h"

#include "VLIB_kalmanFilter_4x6_Predict_F32.h"
#include "VLIB_kalmanFilter_4x6_Predict_F32_cn.h"
#include "VLIB_kalmanFilter_4x6_Predict_F32_idat.h"

/* VLIB_kalmanFilter_4x6_Predict_F32_d:  Test Driver Routine */
void VLIB_kalmanFilter_4x6_Predict_F32_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    kalmanFilter_4x6_Predict_F32_testParams_t   *prm;

    kalmanFilter_4x6_Predict_F32_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_kalmanFilter_4x6_Predict_F32");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        VLIB_F32                    *Z           = (VLIB_F32 *) VLIB_memalign(8, 4 * sizeof(VLIB_F32));
        VLIB_F32                    *Z_buffer    = (VLIB_F32 *) memalign(8, prm[tpi].numMeasurements * 4 * sizeof(VLIB_F32));
        VLIB_F32                    *Residual    = (VLIB_F32 *) VLIB_memalign(8, 4 * sizeof(VLIB_F32));
        VLIB_F32                    *Residual_cn = (VLIB_F32 *) memalign(8, 4 * sizeof(VLIB_F32));
        VLIB_kalmanFilter_4x6_F32   *KF          = (VLIB_kalmanFilter_4x6_F32 *) VLIB_memalign(8, sizeof(VLIB_kalmanFilter_4x6_F32));
        VLIB_kalmanFilter_4x6_F32   *KF_cn       = (VLIB_kalmanFilter_4x6_F32 *) memalign(8, sizeof(VLIB_kalmanFilter_4x6_F32));

        /* Only run the test if the buffer allocations fit in the heap */
        if( Z && Z_buffer && Residual && Residual_cn && KF && KF_cn ) {

            int32_t    fail, i, index;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (VLIB_F32)1,
                            Z_buffer, prm[tpi].staticIn,
                            prm[tpi].numMeasurements * 4, 1, prm[tpi].numMeasurements * 4 * sizeof(VLIB_F32),
                            sizeof(VLIB_F32), testPatternString);

            memset(KF, 0, sizeof(VLIB_kalmanFilter_4x6_F32));
            memset(KF_cn, 0, sizeof(VLIB_kalmanFilter_4x6_F32));

            KF->scaleFactor = KF_cn->scaleFactor = 5;

            /* initialize matrices for both optimized and natural c versions */
            for( i=0; i < sD_4x6; i++ ) {
                index = i * sD_4x6 + i;
                KF->errorCov[index]   = KF_cn->errorCov[index]   = 1000;
                KF->transition[index] = KF_cn->transition[index] = 1;
                if( i < mD_4x6 ) {
                    KF->measurement[index] = KF_cn->measurement[index] = 1;
                }
            }

            KF->transition[2]  = KF_cn->transition[2] = 1;
            KF->transition[4]  = KF_cn->transition[4] = 0.5;
            KF->transition[9]  = KF_cn->transition[9] = 1;
            KF->transition[11] = KF_cn->transition[11] = 0.5;
            KF->transition[16] = KF_cn->transition[16] = 1;
            KF->transition[23] = KF_cn->transition[23] = 1;

            KF->measurementNoiseCov[0] = KF_cn->measurementNoiseCov[0] = 2500;
            KF->measurementNoiseCov[5] = KF_cn->measurementNoiseCov[5] = 2500;
            KF->measurementNoiseCov[10] = KF_cn->measurementNoiseCov[10] = 100;
            KF->measurementNoiseCov[15] = KF_cn->measurementNoiseCov[15] = 100;

            KF->processNoiseCov[0] = KF_cn->processNoiseCov[0] = 0.25;
            KF->processNoiseCov[1] = KF_cn->processNoiseCov[1] = 0.25;
            KF->processNoiseCov[2] = KF_cn->processNoiseCov[2] = 0.25;
            KF->processNoiseCov[6] = KF_cn->processNoiseCov[6] = 0.25;
            KF->processNoiseCov[7] = KF_cn->processNoiseCov[7] = 0.2500;
            KF->processNoiseCov[8] = KF_cn->processNoiseCov[8] = 0.5000;
            KF->processNoiseCov[12] = KF_cn->processNoiseCov[12] = 0.25;
            KF->processNoiseCov[13] = KF_cn->processNoiseCov[13] = 0.5000;
            KF->processNoiseCov[14] = KF_cn->processNoiseCov[14] = 1.000;

            KF->processNoiseCov[21] = KF_cn->processNoiseCov[21] = 0.25;
            KF->processNoiseCov[22] = KF_cn->processNoiseCov[22] = 0.25;
            KF->processNoiseCov[23] = KF_cn->processNoiseCov[23] = 0.25;
            KF->processNoiseCov[27] = KF_cn->processNoiseCov[27] = 0.25;
            KF->processNoiseCov[28] = KF_cn->processNoiseCov[28] = 0.2500;
            KF->processNoiseCov[29] = KF_cn->processNoiseCov[29] = 0.5000;
            KF->processNoiseCov[33] = KF_cn->processNoiseCov[33] = 0.25;
            KF->processNoiseCov[34] = KF_cn->processNoiseCov[34] = 0.5000;
            KF->processNoiseCov[35] = KF_cn->processNoiseCov[35] = 1.000;

            KF->state[0] = KF_cn->state[0] = 190;
            KF->state[1] = KF_cn->state[1] = 190;
            KF->state[2] = KF_cn->state[2] = 0;
            KF->state[3] = KF_cn->state[3] = 0;
            KF->state[4] = KF_cn->state[4] = 0;
            KF->state[5] = KF_cn->state[5] = 0;

            for( i=0; i < prm[tpi].numMeasurements; i++ ) {

                int    j;

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_kalmanFilter_4x6_Predict_F32(KF);
                VLIB_profile_stop();

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_kalmanFilter_4x6_Predict_F32_cn(KF_cn);
                VLIB_profile_stop();

                /* get measurement */
                Z[0] = Z_buffer[i * mD_4x6 + 0];
                Z[1] = Z_buffer[i * mD_4x6 + 1];
                Z[2] = Z_buffer[i * mD_4x6 + 2];
                Z[3] = Z_buffer[i * mD_4x6 + 3];

                VLIB_kalmanFilter_4x6_Correct_F32_cn(KF, Z, Residual);  // The natC version is used so that the code size doesn't get counted
                VLIB_kalmanFilter_4x6_Correct_F32_cn(KF_cn, Z, Residual_cn);

                for( j=0; j < 6; j++ ) {

                    /* Compare natural C Output and Optimized Output */
                    if( fabs(KF->state[j] - KF_cn->state[j]) > (0.1)) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                    }

                    /* If static output is available, then additionally compares natural C output with static reference output data */
                    if( prm[tpi].staticOut != NULL ) {
                        if( fabs(KF_cn->state[j] - prm[tpi].staticOut[(i * 6) + j]) > (0.1)) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }
                }
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
        VLIB_memError("VLIB_kalmanFilter_4x6_Predict_F32");
    } else {
        VLIB_kalmanFilter_4x6_Predict_F32_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x6_predict_F32_d.c                     */
/* ======================================================================== */

