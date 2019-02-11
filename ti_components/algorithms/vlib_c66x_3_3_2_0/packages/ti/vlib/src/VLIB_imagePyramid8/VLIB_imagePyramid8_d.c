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

#include "VLIB_imagePyramid8.h"
#include "VLIB_imagePyramid8_cn.h"
#include "VLIB_imagePyramid8_idat.h"

/* VLIB_imagePyramid8_d:  Test Driver Routine */
void VLIB_imagePyramid8_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    imagePyramid8_testParams_t   *prm;

    imagePyramid8_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_imagePyramid8");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    in_size  =   prm[tpi].inCols * prm[tpi].inRows;
        uint32_t    out_size =   in_size / 4 + in_size / 16 + in_size / 64; // same as in_size*21/64

        /* Allocate buffers for each test vector */
        uint8_t   *pIn          = (uint8_t *) VLIB_memalign(8, in_size);
        uint8_t   *pOut         = (uint8_t *) VLIB_memalign(8, out_size * sizeof(uint8_t));
        uint8_t   *pOut_cn      = (uint8_t *) malloc(out_size * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pIn && pOut && pOut_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            pIn, prm[tpi].staticIn,
                            prm[tpi].inCols, prm[tpi].inRows, prm[tpi].inCols,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_imagePyramid8(pIn, prm[tpi].inCols, prm[tpi].inRows, pOut);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_imagePyramid8_cn(pIn, prm[tpi].inCols, prm[tpi].inRows, pOut_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pOut, (void *)pOut_cn, out_size * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOut_cn, out_size * sizeof(uint8_t));
            }

#if 0
            {
                int    i;

                for( i=0; i < out_size; i++ ) {
                    printf("%d, ", pOut[i]);
                }
            }
#endif
            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inRows=%d, num_output_pt=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inRows, out_size);
            VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inRows=%d, num_output_pt=%d",
                    prm[tpi].inCols, prm[tpi].inRows, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pOut_cn);
        VLIB_align_free(pOut);
        VLIB_align_free(pIn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inCols * inRows * 21 / 64",
                              "inCols * inRows * 21 / 64");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_imagePyramid8");
    } else {
        VLIB_imagePyramid8_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_imagePyramid8_d.c                                    */
/* ======================================================================== */

