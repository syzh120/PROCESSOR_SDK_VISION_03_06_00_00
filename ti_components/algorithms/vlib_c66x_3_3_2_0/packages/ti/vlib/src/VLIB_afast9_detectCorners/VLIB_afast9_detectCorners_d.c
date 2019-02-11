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

#include "VLIB_afast9_detectCorners.h"
#include "VLIB_afast9_detectCorners_cn.h"
#include "VLIB_afast9_detectCorners_idat.h"

void VLIB_afast9_detectCorners_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    afast9_detectCorners_testParams_t   *prm;

    afast9_detectCorners_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_afast9_detectCorners");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /*  Initialization  */
        uint16_t    totalHalfWordsInRow    = ((prm[tpi].imageWidth  - 2 * 3) & 0xFFF0U) >> 0x4U;
        uint32_t    totalFeatureHalfWords  = totalHalfWordsInRow * (prm[tpi].imageHeight - 2 * 3);

        /* Allocate buffers for each test vector */
        uint8_t    *im1             =  (uint8_t *)  VLIB_malloc(prm[tpi].imagePitch * prm[tpi].imageHeight);
        uint16_t   *outFeatures     =  (uint16_t *) VLIB_malloc(totalFeatureHalfWords * sizeof(uint16_t));
        uint8_t    *scratch         =  (uint8_t *)  VLIB_memalign(8, 32 * 16);
        uint16_t   *outFeatures_cn  =  (uint16_t *) malloc(totalFeatureHalfWords * sizeof(uint16_t));
        uint32_t    numFeatures;
        uint32_t    numFeatures_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( im1 && scratch && outFeatures && outFeatures_cn ) {

            int32_t    fail;
            int32_t    i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)128,
                            im1, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                            sizeof(uint8_t), testPatternString);

            if( prm[tpi].testPattern == CUSTOM ) {  /* Custom pattern of 3x3 blocks to generate most corners*/
                uint32_t    row, col;
                uint8_t     val = 128;

                for( row= 0; row < prm[tpi].imageHeight; row++ ) {
                    for( col=0; col < prm[tpi].imageWidth - 5; col+=6 ) {
                        im1[row * prm[tpi].imagePitch + col] = 0;
                        im1[row * prm[tpi].imagePitch + col + 1] = 0;
                        im1[row * prm[tpi].imagePitch + col + 2] = 0;
                        if((row % 6) < 3 ) {
                            im1[row * prm[tpi].imagePitch + col + 3] = 0;
                            im1[row * prm[tpi].imagePitch + col + 4] = 0;
                            im1[row * prm[tpi].imagePitch + col + 5] = 0;
                        } else {
                            im1[row * prm[tpi].imagePitch + col + 3] = val;
                            im1[row * prm[tpi].imagePitch + col + 4] = val;
                            im1[row * prm[tpi].imagePitch + col + 5] = val;
                        }
                    }
                }
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);

            numFeatures = VLIB_afast9_detectCorners(im1,
                                                    prm[tpi].imageWidth,
                                                    prm[tpi].imageHeight,
                                                    prm[tpi].imagePitch,
                                                    prm[tpi].threshold,
                                                    outFeatures,
                                                    scratch);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            numFeatures_cn = VLIB_afast9_detectCorners_cn(im1,
                                                          prm[tpi].imageWidth,
                                                          prm[tpi].imageHeight,
                                                          prm[tpi].imagePitch,
                                                          prm[tpi].threshold,
                                                          outFeatures_cn,
                                                          scratch);
            VLIB_profile_stop();

            for( i=0; i < totalFeatureHalfWords; i++ ) {
                if( outFeatures_cn[i] != outFeatures[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u,%x,%x \n", i, outFeatures_cn[i], outFeatures[i]);
                    }
                    break;
                }
            }

            if( numFeatures != numFeatures_cn ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                if( numFeatures_cn == numFeatures ) {
                    for( i=0; i < totalFeatureHalfWords; i++ ) {
                        if( outFeatures_cn[i] != prm[tpi].staticOut[i] ) {
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
            sprintf(desc, "%s generated input | Opt and NatC results compared | width= %d, height= %d, n_features found= %d, %s",
                    testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, numFeatures, prm[tpi].desc);

            VLIB_formula_add_test(totalFeatureHalfWords * 16, prm[tpi].imageHeight - 6, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width= %d, height= %d",
                    prm[tpi].imageWidth, prm[tpi].imageHeight);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(im1);
        VLIB_free(outFeatures);
        VLIB_align_free(scratch);
        free(outFeatures_cn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = ((width-6)&0xFFF0) * (height-6), M=height-6",
                              "((width-6)&0xFFF0) * (height-6)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_afast9_detectCorners");
    } else {
        VLIB_afast9_detectCorners_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_afast9_detectCorners_d.c                             */
/* ======================================================================== */

