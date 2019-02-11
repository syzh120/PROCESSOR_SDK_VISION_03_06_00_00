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

#include "VLIB_gradientH5x5PyramidKernel_8.h"
#include "VLIB_gradientH5x5PyramidKernel_8_cn.h"
#include "VLIB_gradientH5x5PyramidKernel_8_idat.h"

/* VLIB_gradientH5x5PyramidKernel_8_d:  Test Driver Routine */
void VLIB_gradientH5x5PyramidKernel_8_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    gradientH5x5Pyramid8_testParams_t   *prm;

    gradientH5x5Pyramid8_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_gradientH5x5PyramidKernel_8");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    in_size  =   prm[tpi].pitch * prm[tpi].height;
        uint32_t    tmp_size =   5 * (prm[tpi].width - 4);
        uint32_t    out_width =  (prm[tpi].width - 4) / 2;
        uint32_t    out_height = (prm[tpi].height - 3) / 2;
        uint32_t    out_size =   out_width * out_height;

        /* Allocate buffers for each test vector */
        uint8_t   *pIn          = (uint8_t *) VLIB_malloc(in_size * sizeof(uint8_t));
        int16_t   *pB           = (int16_t *) VLIB_malloc(tmp_size * sizeof(int16_t));
        uint8_t   *pOut         = (uint8_t *) VLIB_malloc(out_size * sizeof(uint8_t));
        uint8_t   *pOut_cn      = (uint8_t *) malloc(out_size * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pIn && pB && pOut && pOut_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)8,
                            pIn, prm[tpi].staticIn,
                            prm[tpi].pitch, prm[tpi].height, prm[tpi].pitch,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_gradientH5x5PyramidKernel_8(pIn, pB, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, pOut);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_gradientH5x5PyramidKernel_8_cn(pIn, pB, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, pOut_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pOut, (void *)pOut_cn, out_size * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOut_cn, out_size * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, num_output_pt=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height, out_size);
            VLIB_formula_add_test(out_size, out_height, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, num_output_pt=%d",
                    prm[tpi].width, prm[tpi].height, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pOut_cn);
        VLIB_free(pOut);
        VLIB_free(pB);
        VLIB_free(pIn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = (width-4)/2) * ((height-3)/2); M = (height-3)/2",
                              "(width-4)/2) * ((height-3)/2)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_gradientH5x5PyramidKernel_8");
    } else {
        VLIB_gradientH5x5PyramidKernel_8_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_gradientH5x5PyramidKernel_8_d.c                      */
/* ======================================================================== */

