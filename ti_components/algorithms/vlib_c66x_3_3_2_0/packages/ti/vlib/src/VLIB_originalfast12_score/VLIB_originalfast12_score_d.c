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
#include "../common/VLIB_orb_utilities.h"

#include "VLIB_originalfast12_score.h"
#include "VLIB_originalfast12_score_cn.h"
#include "VLIB_originalfast12_score_idat.h"

void VLIB_originalfast12_score_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    originalfast12_score_testParams_t   *prm;

    originalfast12_score_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_originalfast12_score");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* In this test, the number of features going into this function is already known in the test vector, so
         * it is being set here to the known size to minimize the memory usage for the test.  However, in an application,
         * the memory allocation for the number of features will be done before the features are found, so the memory
         * allocation should assume the MAX number of features supported by the feature detector : CORB_MAX_FEATURES */
        //uint32_t    nfeatures = CORB_MAX_FEATURES;           /* Typical in production */
        uint32_t    nfeatures = prm[tpi].true_num_features;   /* Used for the sake of this test for memory savings */

        /*  Initialization  */
        const CORBParameters    orbParams = getCORBParameters(prm[tpi].imageWidth, prm[tpi].imageHeight, 10, prm[tpi].fastDifferenceThreshold, nfeatures);

        /* Allocate buffers for each test vector */
        uint32_t     *dummyPtr      = (uint32_t *)1;
        CORBInput    *orbInput      = (CORBInput  *) malloc(sizeof(CORBInput));
        CORBOutput   *orbOutput     = (CORBOutput *) VLIB_malloc(sizeof(CORBOutput));
        CORBOutput   *orbOutput_cn  = (CORBOutput *) malloc(sizeof(CORBOutput));

        if( orbInput && orbOutput && orbOutput_cn ) {
            orbInput->prefimage         = (uint8_t *) VLIB_malloc(prm[tpi].imageWidth * prm[tpi].imageHeight * sizeof(uint8_t));

            orbOutput->n_features       = prm[tpi].true_num_features;
            orbOutput->features         = (CORBFeature *) VLIB_malloc((nfeatures) * sizeof(CORBFeature));

            orbOutput_cn->n_features    = prm[tpi].true_num_features;
            orbOutput_cn->features      = (CORBFeature *) malloc((nfeatures) * sizeof(CORBFeature));

        } else {
            dummyPtr = NULL;
        }

        /* Only run the test if the buffer allocations fit in the heap */
        if( dummyPtr && orbOutput->features && orbOutput_cn->features && orbInput->prefimage ) {

            int32_t    fail;
            int32_t    i;

            /* Fill input arrays according to desired test pattern */
            for( i=0; i < prm[tpi].true_num_features; i++ ) {
                orbOutput->features[i].x = prm[tpi].staticInFeatures[2 * i];
                orbOutput_cn->features[i].x = prm[tpi].staticInFeatures[2 * i];
                orbOutput->features[i].y = prm[tpi].staticInFeatures[2 * i + 1];
                orbOutput_cn->features[i].y = prm[tpi].staticInFeatures[2 * i + 1];
            }

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)128,
                            orbInput->prefimage, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imageWidth,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_originalfast12_score(orbInput->prefimage, orbParams.width, orbOutput->features, orbOutput->n_features, orbParams.fastDifferenceThreshold);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_originalfast12_score_cn(orbInput->prefimage, orbParams.width, orbOutput_cn->features, orbOutput_cn->n_features, orbParams.fastDifferenceThreshold);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if( orbOutput->n_features != orbOutput_cn->n_features ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            for( i=0; i < orbOutput->n_features; i++ ) {
                if( orbOutput->features[i].fastResponse != orbOutput_cn->features[i].fastResponse ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u \n", i);
                    }
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                for( i=0; i < orbOutput->n_features; i++ ) {
                    if( orbOutput_cn->features[i].fastResponse != prm[tpi].staticOut[i] ) {
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
            sprintf(desc, "%s generated input | Opt and NatC results compared | n_features_12= %d, fastDifferenceThreshold= %d, %s",
                    testPatternString, orbOutput->n_features, prm[tpi].fastDifferenceThreshold, prm[tpi].desc);

            VLIB_formula_add_test(prm[tpi].true_num_features, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "n_features_12= %d",
                    prm[tpi].true_num_features);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(orbInput->prefimage);
        free(orbOutput_cn->features);
        free(orbOutput->features);
        free(orbOutput_cn);
        VLIB_free(orbOutput);
        free(orbInput);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "n_features_12; Performance is data dependent.");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_originalfast12_score");
    } else {
        VLIB_originalfast12_score_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_originalfast12_score_d.c                             */
/* ======================================================================== */

