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

#include "VLIB_triangulatePoints.h"
#include "VLIB_triangulatePoints_cn.h"
#include "VLIB_triangulatePoints_idat.h"

/* VLIB_triangulatePoints_d:  Test Driver Routine */
void VLIB_triangulatePoints_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    triangulatePoints_testParams_t   *prm;

    triangulatePoints_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_triangulatePoints");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        int32_t    numTrackPair      = ((prm[tpi].numTracks + 1) >> 0x1);

        /* Allocate buffers for each test vector */
        /* Every track maximum length is assumed to be MAX_POINTS_IN_TRACK*/
        VLIB_F32   *track      =  (VLIB_F32 *) VLIB_memalign(8, (numTrackPair * 2) * VLIB_TRIANG_MAX_POINTS_IN_TRACK * 2 * sizeof(VLIB_F32));
        VLIB_F32   *camExtPrm  =  (VLIB_F32 *) VLIB_memalign(8, VLIB_TRIANG_MAX_POINTS_IN_TRACK * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE * sizeof(VLIB_F32));
        VLIB_F32   *outX       =  (VLIB_F32 *) VLIB_memalign(8, (numTrackPair * 2) * 3 * sizeof(VLIB_F32));
        uint8_t    *scratch    =  (uint8_t *)  VLIB_memalign(8, numTrackPair * 1540);
        uint8_t    *validOut   =  (uint8_t *)  VLIB_malloc(numTrackPair*2);

        VLIB_F32   *track_cn      =  (VLIB_F32 *) malloc((numTrackPair * 2) * VLIB_TRIANG_MAX_POINTS_IN_TRACK * 2 * sizeof(VLIB_F32));
        VLIB_F32   *camExtPrm_cn  =  (VLIB_F32 *) malloc(VLIB_TRIANG_MAX_POINTS_IN_TRACK * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE * sizeof(VLIB_F32));
        VLIB_F32   *outX_cn       =  (VLIB_F32 *) malloc((numTrackPair * 2) * 3 * sizeof(VLIB_F32));
        uint8_t    *scratch_cn    =  (uint8_t *)  malloc(numTrackPair * 3176);
        uint8_t    *validOut_cn   =  (uint8_t *)  malloc(numTrackPair*2);
        uint8_t    *trackLength   =  (uint8_t *)  malloc(numTrackPair*2);


        /* Only run the test if the buffer allocations fit in the heap */
        if( track && camExtPrm && outX && scratch && track_cn && camExtPrm_cn && outX_cn && scratch_cn && validOut && validOut_cn ) {

            int32_t     fail;
            int32_t     i, j, k, l;
            VLIB_F32   *pf32temp1;
            VLIB_F32   *pf32temp2;
            int32_t     totalPoints = 0;

            /* This VLIB API is able to handle last 6 frames track, to do one triangulation.
               Below shuffling of data is required to have better SIMD optimization. And
               this shuffling is required to done once in a frame.
             */
            for( l = (VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1); l >= 0; l-- ) {
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 0]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 8];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 1]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 0];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 2]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 4];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 3]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 9];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 4]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 1];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 5]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 5];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 6]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 10];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 7]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 11];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 8]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 2];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 9]   =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 6];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 10]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 3];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 11]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 7];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 12]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 8];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 13]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 8];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 14]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 9];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 15]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 9];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 16]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 10];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 17]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 10];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 18]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 11];
                camExtPrm[l * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE + 19]  =  prm[tpi].camExtPrm[l * (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 4) + 11];
            }

            memcpy(camExtPrm_cn, camExtPrm, 6 * VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE * sizeof(VLIB_F32));

            pf32temp1 = track;
            pf32temp2 = track_cn;

            /*
             * To get good profile number , it is required that many trackes are worked togather
             * in single call of triangualtion API. To avoid create large input test vectors,
             * first 2 test vectors are repeated.
             */
            for(i = 0; i < prm[tpi].numTracks; i++){
              trackLength[i] = prm[tpi].trackLength[i%VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR];
            }

            /*
             * To take care of the scenario when total number of tracks are less than SIMD_WIDTH (VXLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR)
             */
            for(i = prm[tpi].numTracks; i < VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR; i++){
              trackLength[i] = 0;
            }

            for( i = 0, k = 0; i < prm[tpi].numTracks; i++ ) {
                for( j = (VLIB_TRIANG_MAX_POINTS_IN_TRACK - trackLength[i]), l=0; j < VLIB_TRIANG_MAX_POINTS_IN_TRACK; j++, l++ ) {

                    /* x- co-ordinate
                     */
                    pf32temp1[k + 2 * j * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]     = (prm[tpi].ptrack[i%VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])[2 * l];
                    pf32temp2[k + 2 * j * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]     = (prm[tpi].ptrack[i%VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])[2 * l];

                    /* y- co-ordinate
                     */
                    pf32temp1[k + (2 * j + 1) * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]     = (prm[tpi].ptrack[i%VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])[2 * l + 1];
                    pf32temp2[k + (2 * j + 1) * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]     = (prm[tpi].ptrack[i%VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])[2 * l + 1];

                }

                k++;
                if((i % VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR) == (VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR - 1)) {
                    pf32temp1    += VLIB_TRIANG_MAX_POINTS_IN_TRACK * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR * 2;
                    pf32temp2    += VLIB_TRIANG_MAX_POINTS_IN_TRACK * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR * 2;
                    k = 0;
                }
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_triangulatePoints(track,
                                   camExtPrm,
                                   trackLength,
                                   prm[tpi].maxIter,
                                   outX,
                                   (VLIB_F32 *)scratch,
                                   numTrackPair * 2,
                                   validOut,
                                   prm[tpi].isHighPrecision);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_triangulatePoints_cn(track_cn,
                                      camExtPrm_cn,
                                      trackLength,
                                      prm[tpi].maxIter,
                                      outX_cn,
                                      (VLIB_F32 *)scratch_cn,
                                      numTrackPair * 2,
                                      validOut_cn,
                                      prm[tpi].isHighPrecision);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            pf32temp1 = outX;
            pf32temp2 = outX_cn;

            for( i = 0, k = 0; i < prm[tpi].numTracks; i++ ) {
                if((_fabsf((pf32temp1[k + 0 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR] - pf32temp2[k + 0 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]) / (pf32temp2[k + 0 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])) > 0.05f) ||
                   (_fabsf((pf32temp1[k + 1 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR] - pf32temp2[k + 1 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]) / (pf32temp2[k + 1 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])) > 0.05f) ||
                   (_fabsf((pf32temp1[k + 2 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR] - pf32temp2[k + 2 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]) / (pf32temp2[k + 2 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])) > 0.05f)) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch With Natural C in Track Number = %u \n", i);
                    }
                    break;
                }
                if((i % VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR) == (VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR - 1)) {
                    k         = 0;
                    pf32temp1     += VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR * 3;
                    pf32temp2     += VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR * 3;
                } else {
                    k++;
                }
                totalPoints += trackLength[i];
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */

            for( i = 0, k = 0; i < prm[tpi].numTracks; i++ ) {

                pf32temp1 = prm[tpi].outX[i%VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR];

                if( pf32temp1 != NULL ) {

                    pf32temp2 = outX_cn;

                    if((_fabsf((pf32temp1[0] - pf32temp2[k + 0 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]) / (pf32temp2[k + 0 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])) > 0.05f) ||
                       (_fabsf((pf32temp1[1] - pf32temp2[k + 1 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]) / (pf32temp2[k + 1 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])) > 0.05f) ||
                       (_fabsf((pf32temp1[2] - pf32temp2[k + 2 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR]) / (pf32temp2[k + 2 * VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR])) > 0.05f)) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch With Reference in Track Number = %u \n", i);
                        }
                        break;
                    }
                    if((i % VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR) == (VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR - 1)) {
                        k         = 0;
                        pf32temp2     += VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR * 3;
                    } else {
                        k++;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%sgenerated input | Opt results compared to NatC results | numTracks=%d | maxIter=%d %s",\
                    testPatternString, prm[tpi].numTracks, prm[tpi].maxIter, prm[tpi].desc);

            VLIB_formula_add_test(totalPoints * prm[tpi].maxIter, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numTracks=%d, maxIter=%d",
                    prm[tpi].numTracks, prm[tpi].maxIter);
            VLIB_skip_test(desc);
        }
        /* Free buffers for each test vector */
        VLIB_align_free(track);
        VLIB_align_free(camExtPrm);
        VLIB_align_free(outX);
        VLIB_align_free(scratch);
        VLIB_free(validOut);

        free(track_cn);
        free(camExtPrm_cn);
        free(outX_cn);
        free(scratch_cn);
        free(validOut_cn);
        free(trackLength);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = trackLength*maxIter",
                              "trackLength*maxIter");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_triangulatePoints");
    } else {
        VLIB_triangulatePoints_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_triangulatePoints_d.c                     */
/* ======================================================================== */

