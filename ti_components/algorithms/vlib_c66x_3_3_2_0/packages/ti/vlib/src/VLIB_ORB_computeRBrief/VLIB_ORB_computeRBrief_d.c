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

#include "VLIB_ORB_computeRBrief.h"
#include "VLIB_ORB_computeRBrief_cn.h"
#include "VLIB_ORB_computeRBrief_idat.h"

void VLIB_ORB_computeRBrief_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    orb_computeRBrief_testParams_t   *prm;

    orb_computeRBrief_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_ORB_computeRBrief");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        VLIB_F32    scale;
        uint32_t    nfeatures = prm[tpi].true_num_features;

        uint8_t    *outDesc             = (uint8_t *)VLIB_malloc(nfeatures * 32);
        uint8_t    *outDesc_cn          = (uint8_t *)malloc(nfeatures * 32);
        uint8_t    *featWedges          = (uint8_t *)VLIB_malloc(nfeatures);
        uint32_t   *validFeaturePoints  = (uint32_t *)VLIB_malloc(nfeatures * sizeof(uint32_t));
        VLIB_F32   *validAngles         = (VLIB_F32 *)VLIB_malloc(nfeatures * sizeof(VLIB_F32));
        int32_t    *relative_patterns   = (int32_t *)memalign(8, CORB_NUM_ORIENTATIONS * CORB_NUM_PATTERNS * 2 * sizeof(int32_t));
        uint32_t   *intgrlImg           = (uint32_t *)VLIB_malloc(prm[tpi].imageWidth * prm[tpi].imageHeight * sizeof(uint32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( outDesc && outDesc_cn && featWedges && validFeaturePoints && validAngles && relative_patterns && intgrlImg ) {

            int32_t    fail;
            int32_t    i, cnt, k, j;

            /* Fill input arrays according to desired test pattern */
            for( i=0, cnt=0; i < prm[tpi].true_num_features; i++ ) {
                int    pointX = prm[tpi].staticInFeatures[2 * i];
                int    pointY = prm[tpi].staticInFeatures[2 * i + 1];
                int    range = round(CORB_HALF_PATCH_SIZE * 1.42);
                /* Kernel does not check for border features (to save cycles), so they should be filtered
                 * out before calling function */
                if(((pointX >= range) &&
                    (pointY >= range) &&
                    (prm[tpi].imageWidth - pointX >= range) &&
                    (prm[tpi].imageHeight - pointY >= range))) {
                    validFeaturePoints[cnt] = ((pointY << 0x10U) | pointX);
                    validAngles[cnt]        = prm[tpi].staticInAngle[i];
                    cnt++;
                }
            }

            for( i=0; i < cnt; i++ ) {
                scale = ((VLIB_F32)CORB_NUM_ORIENTATIONS) / 360.0f;
                featWedges[i] = MIN((int32_t)(floor((VLIB_D64)validAngles[i] *\
                                                    (VLIB_D64)scale)), CORB_NUM_ORIENTATIONS - 1);
            }

            for( i = 0; i < CORB_NUM_ORIENTATIONS; i++ ) {
                const RotationMatrix    rMat = getRotationMatrix(i);

                for( j = 0; j < CORB_NUM_PATTERNS; j++ ) {
                    const VLIB_D64    x1 = (VLIB_D64) prm[tpi].orbPattern[j * 4];
                    const VLIB_D64    y1 = (VLIB_D64) prm[tpi].orbPattern[j * 4 + 1];
                    const VLIB_D64    x2 = (VLIB_D64) prm[tpi].orbPattern[j * 4 + 2];
                    const VLIB_D64    y2 = (VLIB_D64) prm[tpi].orbPattern[j * 4 + 3];

                    const int32_t    x1p = ROUND_DOUBLE(rMat.val[0][0] * x1 + rMat.val[0][1] * y1);
                    const int32_t    y1p = ROUND_DOUBLE(rMat.val[1][0] * x1 + rMat.val[1][1] * y1);
                    const int32_t    x2p = ROUND_DOUBLE(rMat.val[0][0] * x2 + rMat.val[0][1] * y2);
                    const int32_t    y2p = ROUND_DOUBLE(rMat.val[1][0] * x2 + rMat.val[1][1] * y2);
                    const int32_t    nstep = (int)prm[tpi].imageWidth;
                    int32_t          center;

                    center  = (int32_t)(x1p + prm[tpi].imageWidth * y1p);

                    relative_patterns[i * CORB_NUM_PATTERNS * 2 + j * 2] =
                        4 * (center - CORB_PATCH_KERNEL_HALF_WIDTH - CORB_PATCH_KERNEL_HALF_WIDTH * nstep - 1 - nstep);


                    center  = (int32_t)(x2p + prm[tpi].imageWidth * y2p);

                    relative_patterns[i * CORB_NUM_PATTERNS * 2 + j * 2 + 1] =
                        4 * (center - CORB_PATCH_KERNEL_HALF_WIDTH - CORB_PATCH_KERNEL_HALF_WIDTH * nstep - 1 - nstep);
                }
            }

            /* Calling with null pointers will only set the testPatternString variable */
            VLIB_fillBuffer(prm[tpi].testPattern, 128, intgrlImg, prm[tpi].staticInIntegral,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, sizeof(uint32_t) * prm[tpi].imageWidth,
                            sizeof(uint32_t), testPatternString);


            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_ORB_computeRBrief(intgrlImg,
                                   prm[tpi].imageWidth,
                                   prm[tpi].imageWidth,
                                   prm[tpi].imageHeight,
                                   validFeaturePoints,
                                   featWedges,
                                   cnt,
                                   relative_patterns,
                                   outDesc);
            VLIB_profile_stop();
            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_ORB_computeRBrief_cn(intgrlImg,
                                      prm[tpi].imageWidth,
                                      prm[tpi].imageWidth,
                                      prm[tpi].imageHeight,
                                      validFeaturePoints,
                                      featWedges,
                                      cnt,
                                      relative_patterns,
                                      outDesc_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i=0; i < cnt; i++ ) {
                for( k=0; k < (CORB_NUM_PATTERNS / 8); k++ ) {
                    if((outDesc_cn[i * 32 + k] != outDesc[i * 32 + k])) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch in Index = %u %u \n", i, k);
                        }
                        break;
                    }
                }
            }

            /* If test sequence is STATIC then additionally compares natural C output with static reference output data */
            if((prm[tpi].testPattern == STATIC) && (prm[tpi].staticOut != NULL)) {
                for( i=0; i < cnt; i++ ) {
                    for( k=0; k < (CORB_NUM_PATTERNS / 8); k++ ) {
                        if((outDesc_cn[i * 32 + k] != prm[tpi].staticOut[i * 32 + k])) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            if( LevelOfFeedback > 0 ) {
                                printf(" Mismatch in Index = %u %u \n", i, k);
                            }
                            break;
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) ||
                    (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | output->n_features= %d, %s",
                    testPatternString, cnt, prm[tpi].desc);

            VLIB_formula_add_test(cnt, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "Total Features= %d", prm[tpi].true_num_features);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(outDesc_cn);
        VLIB_free(outDesc);
        VLIB_free(featWedges);
        VLIB_free(validFeaturePoints);
        VLIB_free(validAngles);
        align_free(relative_patterns);
        VLIB_free(intgrlImg);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "Total Number of Features(numFeatures)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_ORB_computeRBrief");
    } else {
        VLIB_ORB_computeRBrief_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_computeRBrief_d.c                                */
/* ======================================================================== */

