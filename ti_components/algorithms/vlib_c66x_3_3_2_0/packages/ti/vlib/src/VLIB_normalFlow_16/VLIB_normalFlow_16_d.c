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

#include "../VLIB_xyGradientsAndMagnitude/VLIB_xyGradientsAndMagnitude_cn.h"

#include "VLIB_normalFlow_16.h"
#include "VLIB_normalFlow_16_cn.h"
#include "VLIB_normalFlow_16_idat.h"

/* VLIB_normalFlow_16_d:  Test Driver Routine */
void VLIB_normalFlow_16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    normalFlow_16_testParams_t   *prm;

    normalFlow_16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_normalFlow_16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        /* The allocated buffer for the input should be at least 1 byte larger than the actual image since the
         * xyGradientsAndMagnitudes function reads one extra byte after the last byte in the image is read.
         * This precaution is done to avoid a memory read fault in some situations */
        uint32_t    inp_size =   prm[tpi].width * prm[tpi].height + 1;
        uint32_t    out_size =   prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        uint8_t   *pIn            =  (uint8_t *) VLIB_malloc(inp_size);
        uint8_t   *pInold         =  (uint8_t *) VLIB_malloc(inp_size);
        int16_t   *imDiff         =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *Emag           =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *Ex             =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *Ey             =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *LUT;
        int16_t   *normalFlowU    =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *normalFlowV    =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *normalFlowU_cn =  (int16_t *) malloc(out_size * sizeof(int16_t));
        int16_t   *normalFlowV_cn =  (int16_t *) malloc(out_size * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pIn && pInold && imDiff && Emag && Ex && Ey && normalFlowU && normalFlowV && normalFlowU_cn && normalFlowV_cn ) {

            int32_t    fail, i, maxMag=0;

            /* Fill input arrays according to desired test pattern */
            if( prm[tpi].testPattern == STATIC ) {
                VLIB_fillBuffer(prm[tpi].testPattern,
                                (int16_t)255,
                                imDiff, prm[tpi].staticImDiff,
                                prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(imDiff[0]),
                                sizeof(imDiff[0]), testPatternString);

                VLIB_fillBuffer(prm[tpi].testPattern,
                                (int16_t)255,
                                Emag, prm[tpi].staticEmag,
                                prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(Emag[0]),
                                sizeof(Emag[0]), testPatternString);

                VLIB_fillBuffer(prm[tpi].testPattern,
                                (int16_t)255,
                                Ex, prm[tpi].staticEx,
                                prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(Ex[0]),
                                sizeof(Ex[0]), testPatternString);

                VLIB_fillBuffer(prm[tpi].testPattern,
                                (int16_t)255,
                                Ey, prm[tpi].staticEy,
                                prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(Ey[0]),
                                sizeof(Ey[0]), testPatternString);

            } else {
                /* The imDiff array should be computed between the 2 input images separated in time.  Since this condition
                 * is for autogenerating test vectors, I will simply generate a second RANDOM input for this before taking the
                 * pixelwise difference */
                VLIB_fillBuffer(RANDOM,
                                (uint8_t)255,
                                pInold, NULL,
                                prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(pInold[0]),
                                sizeof(pInold[0]), testPatternString);

                VLIB_fillBuffer(prm[tpi].testPattern,
                                (uint8_t)255,
                                pIn, NULL,
                                prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(pIn[0]),
                                sizeof(pIn[0]), testPatternString);

                for( i=0; i < out_size; i++ ) {
                    imDiff[i] = pIn[i] - pInold[i];
                }

                /* Instead of clearing full image output buffers, I only clear the first and last lines that
                 * will not be overwritten by the function */
                memset(Ex, 0, (prm[tpi].width + 1) * sizeof(Ex[0]));
                memset(&Ex[prm[tpi].width * (prm[tpi].height - 1) - 1], 0, (prm[tpi].width + 1) * sizeof(Ex[0]));
                memset(Ey, 0, (prm[tpi].width + 1) * sizeof(Ey[0]));
                memset(&Ey[prm[tpi].width * (prm[tpi].height - 1) - 1], 0, (prm[tpi].width + 1) * sizeof(Ey[0]));
                memset(Emag, 0, (prm[tpi].width + 1) * sizeof(Emag[0]));
                memset(&Emag[prm[tpi].width * (prm[tpi].height - 1) - 1], 0, (prm[tpi].width + 1) * sizeof(Emag[0]));

                /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
                VLIB_xyGradientsAndMagnitude_cn(pIn, &Ex[prm[tpi].width + 1], &Ey[prm[tpi].width + 1], &Emag[prm[tpi].width + 1],
                                                prm[tpi].width, prm[tpi].height);
            }

            /* Since the LUT only has to be sized to be as large as the max value of Emag array + 1,
             * I am sizing the LUT accordingly for testing purposes.  In production, this can be set to
             * a fixed size at initialization time which would be as large as the largest expected magnitude
             * plus 1 */
            for( i=0; i < out_size; i++ ) {
                if( maxMag < Emag[i] ) {
                    maxMag = Emag[i];
                }
            }

            LUT = (int16_t *) VLIB_malloc((maxMag + 1) * sizeof(int16_t));

            /* Only run the test if the buffer allocations fit in the heap */
            if( LUT ) {

                int32_t    statusU, statusV;

                if( prm[tpi].testPattern == STATIC ) {
                    VLIB_fillBuffer(prm[tpi].testPattern,
                                    (int16_t)255,
                                    LUT, prm[tpi].staticLUT,
                                    (maxMag + 1), 1, (maxMag + 1) * sizeof(LUT[0]),
                                    sizeof(LUT[0]), testPatternString);
                } else {
                    /* Auto-generating the LUT of the minimum size needed for the magnitude array in this test vector */
                    LUT[0] = 0;

                    for( i=1; i < (maxMag + 1); i++ ) {
                        LUT[i] = (int16_t)((float)32767 / i + 0.5f);
                    }
                }

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_normalFlow_16(imDiff, Emag, Ex, Ey, LUT, prm[tpi].T,
                                   prm[tpi].width * prm[tpi].height,
                                   normalFlowU, normalFlowV);
                VLIB_profile_stop();


                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_normalFlow_16_cn(imDiff, Emag, Ex, Ey, LUT, prm[tpi].T,
                                      prm[tpi].width * prm[tpi].height,
                                      normalFlowU_cn, normalFlowV_cn);
                VLIB_profile_stop();

                /* Compare natural C Output and Optimized Output */
                statusU = VLIB_compare_mem((void *) normalFlowU, (void *)normalFlowU_cn, prm[tpi].width * prm[tpi].height * sizeof(normalFlowU_cn[0]));
                statusV = VLIB_compare_mem((void *) normalFlowV, (void *)normalFlowV_cn, prm[tpi].width * prm[tpi].height * sizeof(normalFlowV_cn[0]));
                if( statusU == vlib_KERNEL_FAIL || statusV == vlib_KERNEL_FAIL ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                }

                /* If static output is available, then additionally compares natural C output with static reference output data */
                statusU = statusV = vlib_KERNEL_PASS;
                if( prm[tpi].staticOutU != NULL ) {
                    statusU = VLIB_compare_mem((void *) prm[tpi].staticOutU, (void *)normalFlowU_cn, prm[tpi].width * prm[tpi].height * sizeof(normalFlowU_cn[0]));
                }
                if( prm[tpi].staticOutU != NULL ) {
                    statusV = VLIB_compare_mem((void *) prm[tpi].staticOutV, (void *)normalFlowV_cn, prm[tpi].width * prm[tpi].height * sizeof(normalFlowV_cn[0]));
                }
                if( statusU == vlib_KERNEL_FAIL || statusV == vlib_KERNEL_FAIL ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }

                /* Set the 'fail' flag based on test vector comparison results */
                fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

                est_test=1;

                /* Profile display and preparation for cycle estimation */
                sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, numEls=%d",
                        testPatternString, prm[tpi].width, prm[tpi].height, out_size);
                VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);
            } else {
                /* Display the error printout for this test vector before moving on to the next test vector */
                sprintf(desc, "width=%d, height=%d, numEls=%d",
                        prm[tpi].width, prm[tpi].height, out_size);
                VLIB_skip_test(desc);
            }
        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, numEls=%d",
                    prm[tpi].width, prm[tpi].height, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(normalFlowV_cn);
        free(normalFlowU_cn);
        VLIB_free(normalFlowV);
        VLIB_free(normalFlowU);
        VLIB_free(LUT);
        VLIB_free(Ey);
        VLIB_free(Ex);
        VLIB_free(Emag);
        VLIB_free(imDiff);
        VLIB_free(pInold);
        VLIB_free(pIn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = numEls",
                              "numEls");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_normalFlow_16");
    } else {
        VLIB_normalFlow_16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_normalFlow_16_d.c                                    */
/* ======================================================================== */

