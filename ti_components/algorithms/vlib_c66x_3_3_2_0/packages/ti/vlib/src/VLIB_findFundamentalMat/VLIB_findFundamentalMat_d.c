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

#include "../common/VLIB_test.h"
#include "../common/VLIB_memory.h"
#include "../common/VLIB_profile.h"

#include "VLIB_findFundamentalMat.h"
#include "VLIB_findFundamentalMat_cn.h"
#include "VLIB_findFundamentalMat_idat.h"

/* VLIB_findFundamentalMat_d:  Test Driver Routine */
void VLIB_findFundamentalMat_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    findFundamentalMat_testParams_t   *prm;

    findFundamentalMat_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_findFundamentalMat");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        int32_t    outNumInter       = 0;
        int32_t    outNumInter_cn    = 0;

        int16_t    outNumInliers      = 0;
        int16_t    outNumInliers_cn   = 0;

        int32_t    numPoints         = prm[tpi].numPoints;

        /* Allocate buffers for each test vector */
        /* Every track maximum length is assumed to be MAX_POINTS_IN_TRACK*/
        VLIB_F32   *points1       =  (VLIB_F32 *)  VLIB_memalign(8, numPoints * 2 * sizeof(VLIB_F32));
        VLIB_F32   *points2       =  (VLIB_F32 *)  VLIB_memalign(8, numPoints * 2 * sizeof(VLIB_F32));
        VLIB_F32   *fMat          =  (VLIB_F32 *) VLIB_memalign(8, 9 * sizeof(VLIB_F32));
        uint8_t    *scratch1      =  (uint8_t  *) VLIB_memalign(8, 2520);
        uint8_t    *inOrOutLier   =  (uint8_t *)  VLIB_memalign(8, numPoints * sizeof(uint16_t));

        VLIB_F32   *fMat_cn         =  (VLIB_F32 *) malloc(9 * sizeof(VLIB_F32));
        uint8_t    *scratch1_cn     =  (uint8_t  *) memalign(8, sizeof(VLIB_F32) * 200);
        uint8_t    *inOrOutLier_cn  =  (uint8_t *)  memalign(8, numPoints * sizeof(uint16_t));

        /* Below two scratch requirement is high, can not be allocated from internal memory*/
        uint8_t   *scratch2     =  (uint8_t  *) memalign(8, 9 * numPoints);
        uint8_t   *scratch3     =  (uint8_t  *) memalign(8, 52 * numPoints);
        int32_t    mode         =  (prm[tpi].method & 0x4) >> 0x2;
        int32_t    inNumRanSac  =  (prm[tpi].numItr4RANSAC == 0x7FFFFFFF) ? 200 : prm[tpi].numItr4RANSAC;

        /* Only run the test if the buffer allocations fit in the heap */
        if( points1 && points2 && fMat && scratch1 && scratch1_cn && fMat_cn && scratch2 && scratch3 ) {

            int32_t    fail;
            int32_t    i;

            VLIB_fillBuffer(prm[tpi].testPattern, (uint8_t)256,
                            points1, prm[tpi].points1,
                            2, numPoints, 2 * sizeof(VLIB_F32),
                            sizeof(VLIB_F32), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern, (uint8_t)256,
                            points2, prm[tpi].points2,
                            2, numPoints, 2 * sizeof(VLIB_F32),
                            sizeof(VLIB_F32), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);

            outNumInter =
                VLIB_findFundamentalMat(points1,
                                        points2,
                                        prm[tpi].numPoints,
                                        2.0,
                                        0.176,
                                        prm[tpi].numItr4RANSAC,
                                        prm[tpi].method,
                                        fMat,
                                        &outNumInliers,
                                        inOrOutLier,
                                        scratch1,
                                        scratch2,
                                        scratch3);

            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);

            outNumInter_cn =
                VLIB_findFundamentalMat_cn(points1,
                                           points2,
                                           prm[tpi].numPoints,
                                           2.0,
                                           0.176,
                                           prm[tpi].numItr4RANSAC,
                                           prm[tpi].method,
                                           fMat_cn,
                                           &outNumInliers_cn,
                                           inOrOutLier_cn,
                                           scratch1,
                                           scratch2,
                                           scratch3);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if( outNumInter != outNumInter_cn ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
                if( LevelOfFeedback > 0 ) {
                    printf(" Mismatch With Natural C for Number of Iteration, outNumInter = %d, outNumInter_cn = %d \n", outNumInter, outNumInter_cn);
                }
                break;
            }

            for( i = 0; i < 9; i++ ) {
                if( _fabs(fMat_cn[i] - fMat[i]) > 0.01f ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch With Natural C for F Matrix\n");
                    }
                    break;
                }
            }

            for( i = 0; i < prm[tpi].numPoints; i++ ) {
                if( inOrOutLier_cn[i] != inOrOutLier[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch With Natural C for inlier index \n");
                    }
                    break;
                }
            }

            /* Compare natural C Output and static reference Output */
            if( prm[tpi].outFMat != NULL ) {
                for( i = 0; i < 9; i++ ) {
                    if( _fabs(fMat_cn[i] - prm[tpi].outFMat[i]) > 0.001f ) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch With static reference for F matrix\n");
                        }
                        break;
                    }
                }
            }
            /* If static output is available, then additionally compares natural C output with static reference output data */

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "generated input | Opt results compared to NatC results | numRANSACIter=%d |numFeatures = %d | leastSqrSlEn = %d | outInliers = %d | %s", inNumRanSac, numPoints, mode, outNumInliers_cn, prm[tpi].desc);

            VLIB_formula_add_test(inNumRanSac * numPoints, NULL, NULL, fail, desc, (mode + 1));

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numRANSACIter=%d", prm[tpi].numItr4RANSAC);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */

        VLIB_align_free(points1);
        VLIB_align_free(points2);
        VLIB_align_free(fMat);
        VLIB_align_free(scratch1);
        VLIB_align_free(inOrOutLier);

        free(fMat_cn);
        align_free(scratch1_cn);
        align_free(inOrOutLier_cn);
        align_free(scratch2);
        align_free(scratch3);
    }

    VLIB_profile_setMode(1, 2, "Least Square Solution Is Not Found", 0);

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inNumInter * numPoints",
                              "inNumInter * numPoints");

    VLIB_profile_setMode(2, 2, "Least Square Solution Is Found", 1);

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inNumInter * numPoints",
                              "inNumInter * numPoints");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_findFundamentalMat");
    } else {
        VLIB_findFundamentalMat_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_findFundamentalMat_d.c                     */
/* ======================================================================== */

