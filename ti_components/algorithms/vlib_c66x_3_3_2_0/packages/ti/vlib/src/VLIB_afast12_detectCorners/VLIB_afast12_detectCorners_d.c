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
#include "../common/VLIB_orb_utilities.h"

#include "VLIB_afast12_detectCorners.h"
#include "VLIB_afast12_detectCorners_cn.h"
#include "VLIB_afast12_detectCorners_idat.h"

void VLIB_afast12_detectCorners_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    afast12_detectCorners_testParams_t   *prm;

    afast12_detectCorners_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_afast12_detectCorners");

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
        uint32_t    nfeatures = prm[tpi].max_num_features;   /* Used for the sake of this test for memory savings */

        /*  Initialization  */
        const CORBParameters    orbParams = getCORBParameters(prm[tpi].imageWidth, prm[tpi].imageHeight, 10, 20, nfeatures);
        uint32_t                orbScratchSize;

        /* Allocate buffers for each test vector */
        uint32_t     *dummyPtr      = (uint32_t *)1;
        CORBInput    *orbInput      = (CORBInput  *) malloc(sizeof(CORBInput));
        CORBOutput   *orbOutput     = (CORBOutput *) VLIB_memalign(4, sizeof(CORBOutput));
        CORBOutput   *orbOutput_cn  = (CORBOutput *) malloc(sizeof(CORBOutput));

        if( orbInput && orbOutput && orbOutput_cn ) {
            orbInput->prefimage         = (uint8_t *) VLIB_malloc(prm[tpi].imagePitch * prm[tpi].imageHeight * sizeof(uint8_t));

            orbOutput->n_features       = prm[tpi].max_num_features;
            orbOutput->features         = (CORBFeature *) malloc((nfeatures) * sizeof(CORBFeature));

            orbOutput_cn->n_features    = prm[tpi].max_num_features;
            orbOutput_cn->features      = (CORBFeature *) malloc((nfeatures) * sizeof(CORBFeature));

            orbScratchSize = orbParams.width * sizeof(uint16_t);
            orbInput->scratchBuffer = (char *)VLIB_memalign(8, orbScratchSize);

        } else {
            dummyPtr = NULL;
        }

        /* Only run the test if the buffer allocations fit in the heap */
        if( dummyPtr && orbOutput->features && orbOutput_cn->features && orbInput->scratchBuffer && orbInput->prefimage ) {

            int32_t    fail;
            int32_t    i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)128,
                            orbInput->prefimage, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                            sizeof(uint8_t), testPatternString);
            if( prm[tpi].testPattern == CUSTOM ) {  /* Custom pattern of 3x3 blocks to generate most corners*/
                uint32_t    row, col;
                uint8_t     val = 128;

                for( row= 0; row < prm[tpi].imageHeight; row++ ) {
                    for( col=0; col < prm[tpi].imageWidth - 5; col+=6 ) {
                        orbInput->prefimage[row * prm[tpi].imagePitch + col] = 0;
                        orbInput->prefimage[row * prm[tpi].imagePitch + col + 1] = 0;
                        orbInput->prefimage[row * prm[tpi].imagePitch + col + 2] = 0;
                        if((row % 6) < 3 ) {
                            orbInput->prefimage[row * prm[tpi].imagePitch + col + 3] = 0;
                            orbInput->prefimage[row * prm[tpi].imagePitch + col + 4] = 0;
                            orbInput->prefimage[row * prm[tpi].imagePitch + col + 5] = 0;
                        } else {
                            orbInput->prefimage[row * prm[tpi].imagePitch + col + 3] = val;
                            orbInput->prefimage[row * prm[tpi].imagePitch + col + 4] = val;
                            orbInput->prefimage[row * prm[tpi].imagePitch + col + 5] = val;
                        }
                    }
                }
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            orbOutput->n_features = VLIB_afast12_detectCorners(orbInput->prefimage, orbParams.width, orbParams.height, prm[tpi].imagePitch, orbParams.marginPixels,
                                                               orbParams.fastDifferenceThreshold, prm[tpi].sortResults, orbOutput->features, (uint16_t *) orbInput->scratchBuffer);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            orbOutput_cn->n_features = VLIB_afast12_detectCorners_cn(orbInput->prefimage, orbParams.width, orbParams.height, prm[tpi].imagePitch, orbParams.marginPixels,
                                                                     orbParams.fastDifferenceThreshold, prm[tpi].sortResults, orbOutput_cn->features, (uint16_t *) orbInput->scratchBuffer);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if( orbOutput->n_features == orbOutput_cn->n_features ) {
                for( i=0; i < orbOutput->n_features; i++ ) {
                    if((orbOutput->features[i].x != orbOutput_cn->features[i].x) ||
                       (orbOutput->features[i].y != orbOutput_cn->features[i].y)) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch in Index = %u \n", i);
                        }
                        break;
                    }
                }
            } else {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                if( orbOutput_cn->n_features == prm[tpi].out_n_features ) {
                    for( i=0; i < orbOutput->n_features; i++ ) {
                        if((orbOutput_cn->features[i].x != prm[tpi].staticOut[2 * i]) ||
                           (orbOutput_cn->features[i].y != prm[tpi].staticOut[2 * i + 1])) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            if( LevelOfFeedback > 0 ) {
                                printf(" Mismatch in Index = %u \n", i);
                            }
                            break;
                        }
                    }
                } else {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) ||
                    (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | img_width= %d, img_height= %d, n_features found= %d, %s",
                    testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, orbOutput->n_features, prm[tpi].desc);

            VLIB_formula_add_test(prm[tpi].imageWidth * prm[tpi].imageHeight, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "img_width= %d, img_height= %d",
                    prm[tpi].imageWidth, prm[tpi].imageHeight);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(orbInput->prefimage);
        VLIB_align_free(orbInput->scratchBuffer);
        free(orbOutput_cn->features);
        free(orbOutput->features);
        free(orbOutput_cn);
        VLIB_align_free(orbOutput);
        free(orbInput);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "number of input pixels (img_width*img_height); Performance is data dependent.");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_afast12_detectCorners");
    } else {
        VLIB_afast12_detectCorners_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_afast12_detectCorners_d.c                            */
/* ======================================================================== */

