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

#include "VLIB_packMask32.h"
#include "VLIB_packMask32_cn.h"
#include "VLIB_packMask32_idat.h"

/* VLIB_packMask32_d:  Test Driver Routine */
void VLIB_packMask32_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    packMask32_testParams_t   *prm;

    packMask32_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_packMask32");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    out_size = prm[tpi].pixelCount / 32;

        /* Allocate buffers for each test vector */
        uint8_t    *maskImage         =  (uint8_t *) VLIB_malloc(prm[tpi].pixelCount);
        uint32_t   *mask32packed      =  (uint32_t *) VLIB_malloc(out_size * sizeof(uint32_t));
        uint32_t   *mask32packed_cn   =  (uint32_t *) malloc(out_size * sizeof(uint32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( maskImage && mask32packed && mask32packed_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            maskImage, prm[tpi].staticIn,
                            prm[tpi].pixelCount, 1, prm[tpi].pixelCount,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_packMask32(maskImage, mask32packed, prm[tpi].pixelCount);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_packMask32_cn(maskImage, mask32packed_cn, prm[tpi].pixelCount);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) mask32packed, (void *)mask32packed_cn, out_size * sizeof(uint32_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)mask32packed_cn, out_size * sizeof(uint32_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | pixelCount=%d",
                    testPatternString, prm[tpi].pixelCount);
            VLIB_formula_add_test(prm[tpi].pixelCount, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "pixelCount=%d",
                    prm[tpi].pixelCount);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(mask32packed_cn);
        VLIB_free(mask32packed);
        VLIB_free(maskImage);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = pixelCount",
                              "pixelCount");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_packMask32");
    } else {
        VLIB_packMask32_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_packMask32_d.c                                       */
/* ======================================================================== */

