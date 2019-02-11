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

#include "VLIB_xyGradientsAndMagnitude.h"
#include "VLIB_xyGradientsAndMagnitude_cn.h"
#include "VLIB_xyGradientsAndMagnitude_idat.h"

/* VLIB_xyGradientsAndMagnitude_d:  Test Driver Routine */
void VLIB_xyGradientsAndMagnitude_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    xyGradientsAndMagnitude_testParams_t   *prm;

    xyGradientsAndMagnitude_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_xyGradientsAndMagnitude");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        /* The allocated buffer for the input should be at least 1 byte larger than the actual image since the
         * function reads one extra byte after the last byte in the image is read.  This precaution is done
         * to avoid a memory read fault in some situations */
        uint32_t    inp_size =   prm[tpi].width * prm[tpi].height + 1;
        uint32_t    out_size =   prm[tpi].width * (prm[tpi].height - 2);

        /* Allocate buffers for each test vector */
        uint8_t   *pIn        =  (uint8_t *) VLIB_malloc(inp_size);
        int16_t   *pGradX_opt =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *pGradY_opt =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *pMag_opt   =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t   *pGradX_cn  =  (int16_t *) malloc(out_size * sizeof(int16_t));
        int16_t   *pGradY_cn  =  (int16_t *) malloc(out_size * sizeof(int16_t));
        int16_t   *pMag_cn    =  (int16_t *) malloc(out_size * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pIn && pGradX_opt && pGradY_opt && pMag_opt && pGradX_cn && pGradY_cn && pMag_cn ) {

            int32_t    fail, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            pIn, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_xyGradientsAndMagnitude(pIn, pGradX_opt, pGradY_opt, pMag_opt,
                                         prm[tpi].width, prm[tpi].height);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_xyGradientsAndMagnitude_cn(pIn, pGradX_cn, pGradY_cn, pMag_cn,
                                            prm[tpi].width, prm[tpi].height);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            /* The output that is checked is the size of the output buffer minus 1, since the final value
             * in the output uses 'trash' data from beyond the input image (the 1 extra byte allocated above).
             * If the input size given the the function is a line smaller than the true data in the buffer, then
             * this subtraction of 1 is not needed as it uses actual image data. */
            for( i=0; i < out_size - 1; i++ ) {
                if( pGradX_opt[i] != pGradX_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    break;
                }
                if( pGradY_opt[i] != pGradY_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    break;
                }
                if( pMag_opt[i] != pMag_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutpGradX != NULL &&
                prm[tpi].staticOutpGradY != NULL &&
                prm[tpi].staticOutpMag != NULL ) {
                /* The output that is checked is the size of the output buffer minus 1, since the final value
                 * in the output uses 'trash' data from beyond the input image (the 1 extra byte allocated above).
                 * If the input size given the the function is a line smaller than the true data in the buffer, then
                 * this subtraction of 1 is not needed as it uses actual image data. */
                for( i=0; i < out_size - 1; i++ ) {
                    if( prm[tpi].staticOutpGradX[i] != pGradX_cn[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        break;
                    }
                    if( prm[tpi].staticOutpGradY[i] != pGradY_cn[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        break;
                    }
                    if( prm[tpi].staticOutpMag[i] != pMag_cn[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        break;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, out size=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height, out_size);
            VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, out size=%d",
                    prm[tpi].width, prm[tpi].height, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pMag_cn);
        free(pGradY_cn);
        free(pGradX_cn);
        VLIB_free(pMag_opt);
        VLIB_free(pGradY_opt);
        VLIB_free(pGradX_opt);
        VLIB_free(pIn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * (height-2)",
                              "width * (height-2)");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_xyGradientsAndMagnitude");
    } else {
        VLIB_xyGradientsAndMagnitude_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_xyGradientsAndMagnitude_d.c                          */
/* ======================================================================== */

