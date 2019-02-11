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
#include "../common/VLIB_orb_utilities.h"

#include "VLIB_aFast_nonmaxSuppression.h"
#include "VLIB_aFast_nonmaxSuppression_cn.h"
#include "VLIB_aFast_nonmaxSuppression_idat.h"

void VLIB_aFast_nonmaxSuppression_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    aFast_nonmaxSuppression_testParams_t   *prm;

    aFast_nonmaxSuppression_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_aFast_nonmaxSuppression");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t     status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t     status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        uint16_t    nfeatures         = (prm[tpi].true_num_features) & 0xFFF8;
        uint32_t   *yxPkdOut          = (uint32_t *)VLIB_malloc((nfeatures) * sizeof(uint32_t));
        uint32_t   *yxPkdOut_cn       = (uint32_t *)malloc((nfeatures) * sizeof(uint32_t));
        uint8_t    *scoreOut          = (uint8_t *)VLIB_malloc((nfeatures) * sizeof(uint8_t));
        uint8_t    *scoreOut_cn       = (uint8_t *)malloc((nfeatures) * sizeof(uint8_t));
        uint32_t    orbScratchSize    = nfeatures * sizeof(uint16_t) + (prm[tpi].imageWidth * sizeof(uint32_t)) + 16;
        uint8_t    *scratch           = (uint8_t *)VLIB_memalign(8, (orbScratchSize) * sizeof(uint8_t));
        uint32_t   *featuresLoc       = (uint32_t *)VLIB_memalign(4, nfeatures * sizeof(uint32_t));
        uint8_t    *scoreIn           = (uint8_t *)VLIB_malloc((nfeatures) * sizeof(uint8_t));

        uint16_t    nfeaturesOut      = 0;
        uint16_t    nfeaturesOut_cn   = 0;

        /* Only run the test if the buffer allocations fit in the heap */
        if( yxPkdOut && nfeatures && yxPkdOut && yxPkdOut_cn && scoreOut && scratch ) {

            int32_t    fail;
            int32_t    i;

            /* Calling with null pointers will only set the testPatternString variable */
            VLIB_fillBuffer(prm[tpi].testPattern, 0, NULL, NULL,
                            0, 0, 0, sizeof(uint8_t), testPatternString);

            memset(scratch, 0, orbScratchSize);
            memcpy(featuresLoc, prm[tpi].staticInFeatures, nfeatures * sizeof(uint32_t));
            memcpy(scoreIn, prm[tpi].staticInFastResponse, nfeatures * sizeof(uint8_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            nfeaturesOut =
                VLIB_aFast_nonmaxSuppression(scoreIn,
                                             featuresLoc,
                                             scoreOut,
                                             yxPkdOut,
                                             nfeatures,
                                             prm[tpi].imageWidth,
                                             prm[tpi].imageHeight,
                                             scratch);
            VLIB_profile_stop();

            memset(scratch, 0, orbScratchSize);
            /* Test natural C code */
            VLIB_profile_start(vlib_KERNEL_CN);
            nfeaturesOut_cn =
                VLIB_aFast_nonmaxSuppression_cn(scoreIn,
                                                featuresLoc,
                                                scoreOut_cn,
                                                yxPkdOut_cn,
                                                nfeatures,
                                                prm[tpi].imageWidth,
                                                prm[tpi].imageHeight,
                                                scratch);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            if( nfeaturesOut != nfeaturesOut_cn ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
                if( LevelOfFeedback > 0 ) {
                    printf(" Mismatch in total feature out \n");
                }
            }

            for( i=0; i < nfeaturesOut_cn; i++ ) {
                if((yxPkdOut_cn[i] != yxPkdOut[i]) ||
                   (scoreOut_cn[i] != scoreOut[i])) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u, out = %x, expected = %x\n", i, yxPkdOut[i], yxPkdOut_cn[i]);
                    }
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if((prm[tpi].staticOut != NULL) && (prm[tpi].staticOutFastResponse != NULL)) {
                for( i=0; i < nfeaturesOut_cn; i++ ) {
                    if((yxPkdOut_cn[i] != ((uint32_t *)prm[tpi].staticOut)[i]) ||
                       (scoreOut_cn[i] != prm[tpi].staticOutFastResponse[i])) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch in Index = %u, out = %x, expected = %x\n", i, yxPkdOut_cn[i], ((uint32_t *)prm[tpi].staticOut)[i]);
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
            sprintf(desc, "%s generated input | Opt and NatC results compared | inNumScores = %d, output features= %d, %s",
                    testPatternString, prm[tpi].true_num_features, nfeaturesOut_cn, prm[tpi].desc);

            VLIB_formula_add_test(nfeatures, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inNumScores = %d",
                    prm[tpi].true_num_features);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(yxPkdOut);
        free(yxPkdOut_cn);
        VLIB_free(scoreOut);
        free(scoreOut_cn);
        VLIB_align_free(scratch);
        VLIB_free(scoreIn);
        VLIB_align_free(featuresLoc);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inNumScores",
                              "inNumScores");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_aFast_nonmaxSuppression");
    } else {
        VLIB_aFast_nonmaxSuppression_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_aFast_nonmaxSuppression_d.c                          */
/* ======================================================================== */

