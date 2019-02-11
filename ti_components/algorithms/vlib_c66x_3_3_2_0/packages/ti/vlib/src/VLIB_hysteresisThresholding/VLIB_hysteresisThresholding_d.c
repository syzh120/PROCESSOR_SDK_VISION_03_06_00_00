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

#include "VLIB_hysteresisThresholding.h"
#include "VLIB_hysteresisThresholding_cn.h"
#include "VLIB_hysteresisThresholding_idat.h"

#include "../VLIB_Canny_Edge_Detection/VLIB_Canny_Edge_Detection_cn.h"
#include "../VLIB_xyGradientsAndMagnitude/VLIB_xyGradientsAndMagnitude_cn.h"

/* VLIB_hysteresisThresholding_d:  Test Driver Routine */
void VLIB_hysteresisThresholding_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;                      /* test parameter index */

    /* Test Parameters */
    hysteresis_testParams_t   *prm;

    hysteresis_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_hysteresisThresholding");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    bufferSize  = prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        uint8_t   *pInput      = (uint8_t *) VLIB_malloc(bufferSize * sizeof(uint8_t));
        int16_t   *pBufGradX   = (int16_t *) VLIB_malloc(bufferSize * sizeof(int16_t));
        int16_t   *pBufGradY   = (int16_t *) VLIB_malloc(bufferSize * sizeof(int16_t));
        int16_t   *pBufMag     = (int16_t *) VLIB_malloc(bufferSize * sizeof(int16_t));
        uint8_t   *pScratch    = (uint8_t *) VLIB_malloc(bufferSize * sizeof(uint8_t));
        uint8_t   *pBufOut     = (uint8_t *) VLIB_malloc(bufferSize * sizeof(uint8_t));
        uint8_t   *pBufOut_cn  = (uint8_t *) malloc(bufferSize * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pInput && pBufGradX && pBufGradY && pBufMag && pScratch && pBufOut && pBufOut_cn ) {
            uint32_t    fail, i, j;

            uint16_t             new_width;
            uint16_t             new_height;
            uint8_t             *listptr;
            uint16_t             conv_window_size=7;
            int16_t *restrict    pGx;
            int16_t *restrict    pGy;
            int16_t *restrict    pMag;
            uint8_t             *pOut;

            /* 3x3 Gaussian kernel with SQ0.8 coefficients */
            const int8_t    gaussian_7x7[49] =
            {
                0, 0,  0,  0,  0, 0, 0,
                0, 0,  0,  0,  0, 0, 0,
                0, 0, 16, 32, 16, 0, 0,
                0, 0, 32, 64, 32, 0, 0,
                0, 0, 16, 32, 16, 0, 0,
                0, 0,  0,  0,  0, 0, 0,
                0, 0,  0,  0,  0, 0, 0
            };

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)127,
                            pInput, prm[tpi].input,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            /* initialize memory */
            memset(pBufGradX,  0, bufferSize * sizeof(int16_t));
            memset(pBufGradY,  0, bufferSize * sizeof(int16_t));
            memset(pBufMag,    0, bufferSize * sizeof(int16_t));
            memset(pBufOut,    0, bufferSize * sizeof(uint8_t));
            memset(pScratch,   0, bufferSize * sizeof(uint8_t));

            if( LevelOfFeedback > 0 ) {
                /* Display image */
                printf("\nDisplay the original 8-bit input image:\n\n");

                for( i=0; i < prm[tpi].height; i++ ) {
                    for( j=0; j < prm[tpi].width; j++ ) {
                        printf("%3d", pInput[i * prm[tpi].width + j]);
                    }

                    printf("\n");
                }
            }

            new_height = prm[tpi].height - (conv_window_size - 1);  /* Output height of convolution */
            new_width = prm[tpi].width - (conv_window_size - 1);    /* Output width of convolution */

            VLIB_conv_7x7_i8_c8s_cn(pInput,
                                    pScratch,
                                    prm[tpi].width * (new_height) - 6,
                                    prm[tpi].width,
                                    gaussian_7x7,
                                    8);

            if( LevelOfFeedback > 0 ) {
                /* Display smoothed image */
                printf("\nDisplay the smoothed 8-bit input image:\n\n");

                for( i=0; i < prm[tpi].height; i++ ) {
                    for( j=0; j < prm[tpi].width; j++ ) {
                        printf("%3d", pScratch[i * prm[tpi].width + j]);
                    }

                    printf("\n");
                }
            }

            pGx  = pBufGradX +
                   prm[tpi].width * (conv_window_size - 1) / 2 + (conv_window_size - 1) / 2 + /* Convolution border */
                   (prm[tpi].width + 1); /* xyGradients border */
            pGy  = pBufGradY +
                   prm[tpi].width * (conv_window_size - 1) / 2 + (conv_window_size - 1) / 2 + /* Convolution border */
                   (prm[tpi].width + 1); /* xyGradients border */
            pMag = pBufMag   +
                   prm[tpi].width * (conv_window_size - 1) / 2 + (conv_window_size - 1) / 2 + /* Convolution border */
                   (prm[tpi].width + 1); /* xyGradients border */

            VLIB_xyGradientsAndMagnitude_cn(pScratch,
                                            pGx,
                                            pGy,
                                            pMag,
                                            prm[tpi].width,
                                            new_height);

            if( LevelOfFeedback > 0 ) {
                /* Display gradient magnitude "image" */
                printf("\nDisplay the 16-bit Gradient Magnitude image:\n\n");

                for( i=0; i < prm[tpi].height; i++ ) {
                    for( j=0; j < prm[tpi].width; j++ ) {
                        printf("%3d", pBufMag[i * prm[tpi].width + j]);
                    }

                    printf("\n");
                }
            }

            /* Valid output sizes of xyGradientsAndMagnitude */
            new_height -= 2;
            new_width  -= 2;
            pOut = pBufOut +
                   prm[tpi].width * (conv_window_size - 1) / 2 + (conv_window_size - 1) / 2 + /* Convolution border */
                   (2 * prm[tpi].width + 2); /* xyGradients and nonMaxSuppression border */

            VLIB_nonMaximumSuppressionCanny_cn(pMag,
                                               pGx,
                                               pGy,
                                               pOut,
                                               new_width,
                                               prm[tpi].width,
                                               new_height);

            if( LevelOfFeedback > 0 ) {
                /* Display edge map after non-maximum suppresion */
                printf("\nDisplay the edge map after Non-Maximum Suppression:\n\n");

                for( i=0; i < prm[tpi].height; i++ ) {
                    for( j=0; j < prm[tpi].width; j++ ) {
                        printf("%3d", pBufOut[i * prm[tpi].width + j]);
                    }

                    printf("\n");
                }
            }

            listptr   = (uint8_t *) pGx;
            pMag += (prm[tpi].width + 1); /* nonMaxSuppression border */
            new_height -= 2;
            new_width  -= 2;

            /* Copy the input to hysteresis threshold to _cn buffer since the hysteresis
             * threshold function modifies this buffer */
            memcpy(pBufOut_cn, pBufOut, bufferSize * sizeof(uint8_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_hysteresisThresholding(pMag,
                                        pOut,
                                        listptr,
                                        new_height,
                                        new_width,
                                        prm[tpi].width,
                                        prm[tpi].loThresh,
                                        prm[tpi].hiThreshold);
            VLIB_profile_stop();

#if 0       /* Normally, we would also do the following step in the application, but so that we verify the raw output of
               VLIB_hysteresisThresholding we need to compare before this step */

            /* Clean-Up: Set all the remaining 'possible edges' to non-edges */
            for( i=prm[tpi].width * 5; i < prm[tpi].width * (prm[tpi].height - 5); i++ ) {
                pBufOut[i] = (pBufOut[i] >> 7) * 255;
            }

#endif


            pOut = pBufOut_cn +
                   prm[tpi].width * (conv_window_size - 1) / 2 + (conv_window_size - 1) / 2 + /* Convolution border */
                   (2 * prm[tpi].width + 2); /* xyGradients and nonMaxSuppression border */

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_hysteresisThresholding_cn(pMag,
                                           pOut,
                                           listptr,
                                           new_height,
                                           new_width,
                                           prm[tpi].width,
                                           prm[tpi].loThresh,
                                           prm[tpi].hiThreshold);
            VLIB_profile_stop();

#if 0       /* Normally, we would also do the following step in the application, but so that we verify the raw output of
               VLIB_hysteresisThresholding we need to compare before this step */

            /* Clean-Up: Set all the remaining 'possible edges' to non-edges */
            for( i=prm[tpi].width * 5; i < prm[tpi].width * (prm[tpi].height - 5); i++ ) {
                pBufOut_cn[i] = (pBufOut_cn[i] >> 7) * 255;
            }

#endif

            /* Display edge map after hysteresis */
            if( LevelOfFeedback > 0 ) {
                printf("\nDisplay the final edge map after Hysteresis:\n\n");

                for( i=0; i < prm[tpi].height; i++ ) {
                    for( j=0; j < prm[tpi].width; j++ ) {
                        if( pBufOut[i * prm[tpi].width + j] == pBufOut_cn[i * prm[tpi].width + j] ) {
                            printf("%3d", pBufOut[i * prm[tpi].width + j]);
                        } else {
                            printf("***");
                        }
                    }

                    printf("\n");
                }
            }

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pBufOut, (void *)pBufOut_cn, bufferSize * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].refOutput != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].refOutput, (void *)pBufOut_cn, bufferSize * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d",
                    testPatternString, new_width, new_height);
            VLIB_formula_add_test(new_width * new_height, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d",
                    prm[tpi].width, prm[tpi].height);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pBufOut_cn);
        VLIB_free(pBufOut);
        VLIB_free(pScratch);
        VLIB_free(pBufMag);
        VLIB_free(pBufGradY);
        VLIB_free(pBufGradX);
        VLIB_free(pInput);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_hysteresisThresholding");
    } else {
        VLIB_hysteresisThresholding_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_hysteresisThresholding_d.c                           */
/* ======================================================================== */

