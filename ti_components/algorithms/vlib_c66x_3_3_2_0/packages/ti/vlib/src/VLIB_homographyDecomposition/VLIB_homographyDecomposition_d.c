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

#include "VLIB_homographyDecomposition.h"
#include "VLIB_homographyDecomposition_cn.h"
#include "VLIB_homographyDecomposition_idat.h"

//#define   _TMS320C6600_CLK_MEASURE
#ifdef _TMS320C6600_CLK_MEASURE
#include <c6x.h>
#endif

/* VLIB_homographyDecomposition_d:  Test Driver Routine */
void VLIB_homographyDecomposition_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    homographyDecomposition_testParams_t   *prm;

    homographyDecomposition_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_homographyDecomposition");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        VLIB_D64   *pA       =  (VLIB_D64 *) VLIB_memalign(8, 3 * 3 * sizeof(VLIB_D64));
        VLIB_D64   *pRot     =  (VLIB_D64 *) VLIB_memalign(8, 3 * 3 * sizeof(VLIB_D64));
        VLIB_D64   *trans    =  (VLIB_D64 *) VLIB_memalign(8, 3 * sizeof(VLIB_D64));
        VLIB_D64   *proj     =  (VLIB_D64 *) VLIB_memalign(8, 3 * sizeof(VLIB_D64));
        VLIB_D64   *pRot_cn  =  (VLIB_D64 *) memalign(8, 3 * 3 * sizeof(VLIB_D64));
        VLIB_D64   *trans_cn =  (VLIB_D64 *) memalign(8, 3 * sizeof(VLIB_D64));
        VLIB_D64   *proj_cn  =  (VLIB_D64 *) memalign(8, 3 * sizeof(VLIB_D64));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pA && pRot && trans && proj && pRot_cn && trans_cn && proj_cn ) {

            int32_t    fail;
            int32_t    n;
            int32_t    err_cnt_c6x = 0;
            int32_t    err_cnt_cn  = 0;
            H3x3_t    *a = (H3x3_t *)pA;
            H3x3_t    *rot = (H3x3_t *)pRot;
            H3x3_t    *rot_cn = (H3x3_t *)pRot_cn;

            #if defined (_TMS320C6600_CLK_MEASURE)
            uint32_t    start_time, end_time;
            VLIB_D64    time_ave = 0.0;
            VLIB_D64    cycle_ave_c66 = 0.0;
            #endif

            for( n=0; n < prm[tpi].testIterations; n++ ) {

                int32_t    i, j;
                int32_t    err_flag = 0;

                /* Fill input arrays according to desired test pattern */
                if( prm[tpi].testPattern == STATIC ) {
                    a->H[0][0] = prm[tpi].staticInH[n * 9];
                    a->H[0][1] = prm[tpi].staticInH[n * 9 + 1];
                    a->H[0][2] = prm[tpi].staticInH[n * 9 + 2];
                    a->H[1][0] = prm[tpi].staticInH[n * 9 + 3];
                    a->H[1][1] = prm[tpi].staticInH[n * 9 + 4];
                    a->H[1][2] = prm[tpi].staticInH[n * 9 + 5];
                    a->H[2][0] = prm[tpi].staticInH[n * 9 + 6];
                    a->H[2][1] = prm[tpi].staticInH[n * 9 + 7];
                    a->H[2][2] = prm[tpi].staticInH[n * 9 + 8];
                    //printf_matrix(a, 3, 3);
                }

                /* Calling with null pointers will only set the testPatternString variable */
                VLIB_fillBuffer(prm[tpi].testPattern, 0, NULL, NULL,
                                0, 0, 0, sizeof(uint8_t), testPatternString);

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                #if defined (_TMS320C6600_CLK_MEASURE)
                TSCL = 0;
                start_time = TSCL;
                #endif
                VLIB_homographyDecomposition(a->H, rot->H, trans, proj);
                #if defined (_TMS320C6600_CLK_MEASURE)
                end_time = TSCL;
                #endif
                VLIB_profile_stop();

                #if defined (_TMS320C6600_CLK_MEASURE)
                printf("[%d][Faugeras] Number of cycles : %d cycles\n", n, end_time - start_time);
                printf("[%d][Faugeras] Time(ms) : %f ms\n", n, (VLIB_D64)(end_time - start_time) / (VLIB_D64)(700000));
                time_ave += (VLIB_D64)(end_time - start_time) / (VLIB_D64)(700000);
                cycle_ave_c66 += end_time - start_time;
                #endif

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_homographyDecomposition_cn(a->H, rot_cn->H, trans_cn, proj_cn);
                VLIB_profile_stop();

                /* Compare natural C Output and Optimized Output */
                for( i=0; i < 3; i++ ) {
                    for( j=0; j < 3; j++ ) {
                        if( fabs(rot->H[i][j] - rot_cn->H[i][j]) > prm[tpi].testErrorThreshold ) {
                            printf("#######[C66-CN][%d]Rotation Matrix FAILED\n", n);
                            printf("#######%.15g, %.15g\n", rot->H[i][j], rot_cn->H[i][j]);
                            status_nat_vs_int = vlib_KERNEL_FAIL;
                            err_flag = 1;
                        }
                    }
                }

                for( i=0; i < 3; i++ ) {
                    if( fabs(trans[i] - trans_cn[i]) > prm[tpi].testErrorThreshold ) {
                        printf("#######[C66-CN][%d]Translation Matrix FAILED\n", n);
                        printf("#######%.15g, %.15g\n", trans[i], trans_cn[i]);
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        err_flag = 1;
                    }
                }

                for( i=0; i < 3; i++ ) {
                    if( fabs(proj[i] - proj_cn[i]) > prm[tpi].testErrorThreshold ) {
                        printf("#######[C66-CN][%d]Projection Matrix FAILED\n", n);
                        printf("#######%.15g, %.15g\n", proj[i], proj_cn[i]);
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        err_flag = 1;
                    }
                }

                if( status_nat_vs_int == vlib_KERNEL_PASS ) {
                    #ifdef DEBUG_SVD_MESSAGE
                    printf("[C66-CN][%d]Faugeras Decomposition Passed\n", n);
                    #endif
                } else {
                    err_cnt_c6x++;
                    printf("[C66-CN][%d]Faugeras Decomposition Failed : [err:%d]\n", n, err_cnt_c6x);
                }

                /* If static output is available, then additionally compares natural C output with static reference output data */
                if((prm[tpi].staticOutRot != NULL) && (prm[tpi].staticOutTr != NULL) && (prm[tpi].staticOutPr != NULL)) {

                    int32_t    cnt = 0;

                    err_flag = 0;

                    for( i=0; i < 3; i++ ) {
                        for( j=0; j < 3; j++ ) {
                            if( fabs(rot_cn->H[i][j] - prm[tpi].staticOutRot[n * 9 + cnt]) > prm[tpi].testErrorThreshold ) {
                                printf("#######[CN-REF][%d]Rotation Matrix FAILED\n", n);
                                printf("#######%.15g, %.15g\n", rot_cn->H[i][j], prm[tpi].staticOutRot[n * 9 + cnt]);
                                status_nat_vs_ref = vlib_KERNEL_FAIL;
                                err_flag = 1;
                            }
                            cnt++;
                        }
                    }

                    for( i=0; i < 3; i++ ) {
                        if( fabs(trans_cn[i] - prm[tpi].staticOutTr[n * 3 + i]) > prm[tpi].testErrorThreshold ) {
                            printf("#######[CN-REF][%d]Translation Matrix FAILED\n", n);
                            printf("#######%.15g, %.15g\n", trans_cn[i], prm[tpi].staticOutTr[n * 3 + i]);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            err_flag = 1;
                        }
                    }

                    for( i=0; i < 3; i++ ) {
                        if( fabs(proj_cn[i] - prm[tpi].staticOutPr[n * 3 + i]) > prm[tpi].testErrorThreshold ) {
                            printf("#######[CN-REF][%d]Projection Matrix FAILED\n", n);
                            printf("#######%.15g, %.15g\n", proj_cn[i], prm[tpi].staticOutPr[n * 3 + i]);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            err_flag = 1;
                        }
                    }

                    if( err_flag == 0 ) {
                        #ifdef DEBUG_SVD_MESSAGE
                        printf("[CN-REF][%d]Faugeras Decomposition Passed\n", n);
                        #endif
                    } else {
                        err_cnt_cn++;
                        printf("[CN-REF][%d]Faugeras Decomposition Failed : [err:%d]\n", n, err_cnt_cn);
                    }
                }
            }

            #if defined (_TMS320C6600_CLK_MEASURE)
            printf("###########################\n");
            printf("[Faugeras] Average Time(ms) : %f ms\n", time_ave / prm[tpi].testIterations);
            printf("[Faugeras] Average Cycles) : %f ms\n", cycle_ave_c66 / prm[tpi].testIterations);
            printf("###########################\n");
            #endif
            if( LevelOfFeedback > 0 ) {
                printf("[Faugeras] [C66-CN] error # : %d\n", err_cnt_c6x);
                printf("[Faugeras] [CN-REF] error # : %d\n", err_cnt_cn);
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared to ref | \"Num pt\" value is actually the number of times the \
test was called, so that the value shown is the average cycle count per call", testPatternString);
            VLIB_formula_add_test(prm[tpi].testIterations, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "Test iterations= %d", prm[tpi].testIterations);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        align_free(proj_cn);
        align_free(trans_cn);
        align_free(pRot_cn);
        VLIB_align_free(proj);
        VLIB_align_free(trans);
        VLIB_align_free(pRot);
        VLIB_align_free(pA);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "1 homography matrix");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_homographyDecomposition");
    } else {
        VLIB_homographyDecomposition_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_homographyDecomposition_d.c                          */
/* ======================================================================== */

