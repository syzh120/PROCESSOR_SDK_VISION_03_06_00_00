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
#include "../common/VLIB_orb_utilities.h"

#include "VLIB_ORB_computeOrientation.h"
#include "VLIB_ORB_computeOrientation_cn.h"
#include "VLIB_ORB_computeOrientation_idat.h"

void VLIB_ORB_computeOrientation_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    orb_computeOrientation_testParams_t   *prm;

    orb_computeOrientation_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_ORB_computeOrientation");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* In this test, the number of features going into this function is already known in the test vector, so
         * it is being set here to the known size to minimize the memory usage for the test.  However, in an application,
         * the memory allocation for the number of features will be done before the features are found, so the memory
         * allocation should assume the MAX number of features supported by the feature detector : CORB_MAX_FEATURES */
        uint32_t    nfeatures = prm[tpi].true_num_features;   /* Used for the sake of this test for memory savings */

        uint32_t   *featuresLoc   = (uint32_t *) VLIB_memalign(4, nfeatures * sizeof(uint32_t));
        uint8_t    *inImage       = (uint8_t  *) VLIB_memalign(4, prm[tpi].imageWidth * prm[tpi].imageHeight);

        int16_t   *outAngles      = (int16_t *) VLIB_memalign(4, nfeatures * sizeof(int16_t));

        int16_t   *outAngles_cn   = (int16_t *) malloc(nfeatures * sizeof(int16_t));

        uint8_t   *scratch           = (uint8_t *) VLIB_malloc(1991);

        if( featuresLoc && inImage && outAngles && outAngles_cn && scratch ) {

            int32_t    fail;
            int32_t    i, cnt;

            /* Fill input arrays according to desired test pattern */
            for( i=0, cnt=0; i < prm[tpi].true_num_features; i++ ) {
                int    pointX = prm[tpi].staticInFeatures[2 * i];
                int    pointY = prm[tpi].staticInFeatures[2 * i + 1];
                /* Kernel does not check for border features (to save cycles), so they should be filtered
                 * out before calling function */
                if(((pointX >= CORB_HALF_PATCH_SIZE) &&
                    (pointY >= CORB_HALF_PATCH_SIZE) &&
                    (prm[tpi].imageWidth - pointX >= CORB_HALF_PATCH_SIZE) &&
                    (prm[tpi].imageHeight - pointY >= CORB_HALF_PATCH_SIZE))) {
                    featuresLoc[cnt] = ((pointY << 0x10U) | pointX);
                    cnt++;
                }
            }

            VLIB_fillBuffer(prm[tpi].testPattern, 128, inImage, prm[tpi].staticInImage,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, sizeof(uint8_t) * prm[tpi].imageWidth,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_ORB_computeOrientation(inImage,
                                        prm[tpi].imageWidth,
                                        prm[tpi].imageHeight,
                                        prm[tpi].imageWidth,
                                        featuresLoc,
                                        cnt,
                                        outAngles,
                                        prm[tpi].momentPattern,
                                        scratch);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_ORB_computeOrientation_cn(inImage,
                                           prm[tpi].imageWidth,
                                           prm[tpi].imageHeight,
                                           prm[tpi].imageWidth,
                                           featuresLoc,
                                           cnt,
                                           outAngles_cn,
                                           prm[tpi].momentPattern,
                                           scratch);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i=0; i < cnt; i++ ) {
                if( outAngles[i] != outAngles_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u \n", i);
                    }
                    break;
                }
            }

            /* If test sequence is STATIC then additionally compares natural C output with static reference output data */
            if((prm[tpi].testPattern == STATIC) &&
               (prm[tpi].staticOut1 != NULL)) {
                for( i=0; i < cnt; i++ ) {
                    if( outAngles_cn[i] != prm[tpi].staticOut1[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch in Index = %u \n", i);
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
            sprintf(desc, "%s generated input | Opt and NatC results compared | numFeatures= %d, %s",
                    testPatternString, cnt, prm[tpi].desc);

            VLIB_formula_add_test(cnt, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numFeatures= %d",
                    prm[tpi].true_num_features);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(scratch);
        VLIB_align_free(outAngles);
        free(outAngles_cn);
        VLIB_align_free(inImage);
        VLIB_align_free(featuresLoc);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = numFeatures",
                              "numFeatures");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_ORB_computeOrientation");
    } else {
        VLIB_ORB_computeOrientation_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_computeOrientation_d.c                           */
/* ======================================================================== */

