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

#include "VLIB_originalfast9_score.h"
#include "VLIB_originalfast9_score_cn.h"
#include "VLIB_originalfast9_score_idat.h"

void VLIB_originalfast9_score_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    originalfast9_score_testParams_t   *prm;

    originalfast9_score_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_originalfast9_score");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Now total feature points given to kernel API has to be multiple of 8 , so truncating the total number of
         * features to nearest multiple of 8.
         */
        uint32_t    nfeatures    = prm[tpi].true_num_features & 0xFFFFFFF8;
        /* Allocate buffers for each test vector */
        uint8_t   *scoreOut      = (uint8_t *) VLIB_memalign(4, nfeatures);
        uint8_t   *scoreOut_cn   = (uint8_t *) memalign(4, nfeatures);
        uint8_t   *img           = (uint8_t *) VLIB_malloc(prm[tpi].imageWidth * prm[tpi].imageHeight * sizeof(uint8_t));
        uint8_t   *scratch       = (uint8_t *) VLIB_memalign(8, 463);

        /* Only run the test if the buffer allocations fit in the heap */
        if( scoreOut && scoreOut_cn && img && scratch ) {

            int32_t    fail;
            int32_t    i;

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)128,
                            img, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imageWidth,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_originalfast9_score(img,
                                     prm[tpi].imageWidth,
                                     (uint32_t *)prm[tpi].staticInFeatures,
                                     nfeatures,
                                     prm[tpi].fastDifferenceThreshold,
                                     scoreOut,
                                     scratch);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_originalfast9_score_cn(img,
                                        prm[tpi].imageWidth,
                                        (uint32_t *)prm[tpi].staticInFeatures,
                                        nfeatures,
                                        prm[tpi].fastDifferenceThreshold,
                                        scoreOut_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i=0; i < nfeatures; i++ ) {
                if( scoreOut[i] != scoreOut_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u \n", i);
                        printf(" Value of score[%u] = %d, And it should be %d \n", i, scoreOut[i], scoreOut_cn[i]);
                    }
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                for( i=0; i < nfeatures; i++ ) {
                    if( scoreOut_cn[i] != prm[tpi].staticOut[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Value of scoreOut_cn[%u] = %d, And it should be %d \n", i, scoreOut_cn[i], prm[tpi].staticOut[i]);
                        }
                        break;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) ||
                    (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | n_features_9= %d, fastDifferenceThreshold= %d, %s",
                    testPatternString, nfeatures, prm[tpi].fastDifferenceThreshold, prm[tpi].desc);

            VLIB_formula_add_test(nfeatures, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "n_features_9= %d",
                    prm[tpi].true_num_features);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_align_free(scratch);
        VLIB_free(img);
        VLIB_align_free(scoreOut);
        align_free(scoreOut_cn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N=numFeatures",
                              "numFeatures");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_originalfast9_score");
    } else {
        VLIB_originalfast9_score_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_originalfast9_score_d.c                              */
/* ======================================================================== */

