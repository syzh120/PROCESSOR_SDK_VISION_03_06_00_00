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

#include "VLIB_trackFeaturesLucasKanade_7x7.h"
#include "VLIB_trackFeaturesLucasKanade_7x7_cn.h"
#include "VLIB_trackFeaturesLucasKanade_7x7_idat.h"

#include "../VLIB_xyGradients/VLIB_xyGradients_cn.h"

/* ///////////////////////////////////// */
/* Makes a w * h custom pattern          */
/* ///////////////////////////////////// */
static void CreatePattern1(uint8_t *p, int16_t w, int16_t h)
{
    int32_t    i;

    for( i = 0; i < w * h; i++ ) {
        int32_t    x = i % w;
        int32_t    y = i / w;

        p[i] = (x | y) / 2 + 127;
    }
}

/* ////////////////////////////////////////// */
/* Warps a w * h custom pattern               */
/* ////////////////////////////////////////// */
static void CreatePattern2(uint8_t *p, int16_t w, int16_t h)
{
    int32_t    i;

    for( i = 0; i < w * h; i++ ) {
        VLIB_F32    x = i % w;
        VLIB_F32    y = i / w;

        int32_t    x1 = x - 1;
        int32_t    y1 = y - 1;

        p[i] = (x1 | y1) / 2 + 127;
    }
}

/* VLIB_trackFeaturesLucasKanade_7x7_d:  Test Driver Routine */
void VLIB_trackFeaturesLucasKanade_7x7_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    trackFeaturesLK_7x7_testParams_t   *prm;

    trackFeaturesLK_7x7_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_trackFeaturesLucasKanade_7x7");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint8_t   *im1      =  (uint8_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height);
        uint8_t   *im2      =  (uint8_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height);
        int16_t   *gradX    =  (int16_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height * sizeof(int16_t));
        int16_t   *gradY    =  (int16_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height * sizeof(int16_t));

        uint16_t   *outx    =  (uint16_t *) VLIB_malloc(prm[tpi].nfeatures * sizeof(int16_t));
        uint16_t   *outy    =  (uint16_t *) VLIB_malloc(prm[tpi].nfeatures * sizeof(int16_t));
        uint16_t   *outx_cn =  (uint16_t *) malloc(prm[tpi].nfeatures * sizeof(int16_t));
        uint16_t   *outy_cn =  (uint16_t *) malloc(prm[tpi].nfeatures * sizeof(int16_t));
        uint16_t   *error    =  (uint16_t *) VLIB_malloc(prm[tpi].nfeatures * sizeof(uint16_t));
        uint16_t   *error_cn =  (uint16_t *) malloc(prm[tpi].nfeatures * sizeof(uint16_t));
        /* scratch buffer is required for original gradx(2*8*8), grady(2*8*8), and for interpolated
           template image(8x8) gradx(2*8*7) and grady(2*8*7) of two sets for two features.
           total = 2*8*8*2 + 2*8*7*4 + 8*8*2 + 7 bytes for alignment = 839.
          */
        uint8_t    *scratch  = (uint8_t *) VLIB_memalign(2, 839);
        uint32_t    numFeature_x_iters;

        /* Only run the test if the buffer allocations fit in the heap */
        if( im1 && im2 && gradX && gradY && outx && outy && outx_cn && outy_cn && error && error_cn && scratch ) {

            int32_t    fail, mode;
            int32_t    i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern, (uint8_t)255,
                            im1, prm[tpi].staticIn1,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern, (uint8_t)255,
                            im2, prm[tpi].staticIn2,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            if( prm[tpi].testPattern == CUSTOM ) {
                /* Synthetic motion sequence */
                CreatePattern1(im1, prm[tpi].width, prm[tpi].height);
                CreatePattern2(im2, prm[tpi].width, prm[tpi].height);
            }

            /* Initial guesses for the feature points */
            for( i = 0; i < prm[tpi].nfeatures; i++ ) {
                if( prm[tpi].outEstFlag == 0x0 ) {
                    outx[i] = outx_cn[i] = prm[tpi].x[i];
                    outy[i] = outy_cn[i] = prm[tpi].y[i];
                } else {
                    outx[i] = outx_cn[i] = prm[tpi].outx[i];
                    outy[i] = outy_cn[i] = prm[tpi].outy[i];
                }
            }

            /* Clear the gradient buffers since the first and last part are not set by the gradient function */
            memset(gradX, 0, prm[tpi].width * prm[tpi].height * sizeof(int16_t));
            memset(gradY, 0, prm[tpi].width * prm[tpi].height * sizeof(int16_t));

            /* Compute the gradient using the library function */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_xyGradients_cn(im1, gradX + prm[tpi].width + 1, gradY + prm[tpi].width + 1,
                                prm[tpi].width, prm[tpi].height);


            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            if( prm[tpi].gradFlag == 0x1 ) {
                numFeature_x_iters =
                    VLIB_trackFeaturesLucasKanade_7x7(im1, im2, gradX, gradY, prm[tpi].width, prm[tpi].height,
                                                      prm[tpi].nfeatures, prm[tpi].x, prm[tpi].y, outx, outy,
                                                      error, prm[tpi].max_iters, prm[tpi].earlyExitTh, scratch);
            } else {
                numFeature_x_iters =
                    VLIB_trackFeaturesLucasKanade_7x7(im1, im2, NULL, NULL, prm[tpi].width, prm[tpi].height,
                                                      prm[tpi].nfeatures, prm[tpi].x, prm[tpi].y, outx, outy,
                                                      error, prm[tpi].max_iters, prm[tpi].earlyExitTh, scratch);
            }
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_trackFeaturesLucasKanade_7x7_cn(im1, im2, gradX, gradY, prm[tpi].width, prm[tpi].height,
                                                 prm[tpi].nfeatures, prm[tpi].x, prm[tpi].y, outx_cn, outy_cn,
                                                 error_cn, prm[tpi].max_iters, prm[tpi].earlyExitTh, scratch);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i = 0; i < prm[tpi].nfeatures; i++ ) {
                if((outx[i] != outx_cn[i]) ||
                   (outy[i] != outy_cn[i]) ||
                   (error[i] != error_cn[i])
                   ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch in Index = %u \n", i);
                    }
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if((prm[tpi].outx != NULL) && (prm[tpi].outy != NULL) && (prm[tpi].outError != NULL)) {
                for( i = 0; i < prm[tpi].nfeatures; i++ ) {
                    if((prm[tpi].outx[i] != outx_cn[i]) ||
                       (prm[tpi].outy[i] != outy_cn[i]) ||
                       (prm[tpi].outError[i] != error_cn[i])
                       ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch in Index = %u \n", i);
                        }
                        break;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | nfeatures=%d | max_iters=%d | earlyExit=%d(1=en,0=dis) | gradCalculation=%d(1=external,0=internal)%s",\
                    testPatternString, prm[tpi].nfeatures, prm[tpi].max_iters, (prm[tpi].earlyExitTh != 0),\
                    prm[tpi].gradFlag, prm[tpi].desc);
            mode = (prm[tpi].gradFlag == 1) ? 1 : 2;
            VLIB_formula_add_test(numFeature_x_iters, prm[tpi].nfeatures, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "nfeatures=%d, max_iters=%d",
                    prm[tpi].nfeatures, prm[tpi].max_iters);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_align_free(scratch);
        free(error_cn);
        VLIB_free(error);
        free(outy_cn);
        free(outx_cn);
        VLIB_free(outy);
        VLIB_free(outx);
        VLIB_free(gradY);
        VLIB_free(gradX);
        VLIB_free(im2);
        VLIB_free(im1);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 3, "gradient is externally calculated and results passed to function", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = nfeatures * num_iters; M = nfeatures",
                              "nfeatures * num_iters");

    VLIB_profile_setMode(2, 3, "gradient is internally calculated", 1); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = nfeatures * num_iters; M = nfeatures",
                              "nfeatures * num_iters");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_trackFeaturesLucasKanade_7x7");
    } else {
        VLIB_trackFeaturesLucasKanade_7x7_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_trackFeaturesLucasKanade_7x7_d.c                     */
/* ======================================================================== */

