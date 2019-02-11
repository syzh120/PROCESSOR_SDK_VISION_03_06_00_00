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

#include "VLIB_convertUYVYpl_to_YUVint.h"
#include "VLIB_convertUYVYpl_to_YUVint_cn.h"
#include "VLIB_convertUYVYpl_to_YUVint_idat.h"

/* VLIB_convertUYVYpl_to_YUVint_d:  Test Driver Routine */
void VLIB_convertUYVYpl_to_YUVint_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    UYVYpl_to_YUVint_testParams_t   *prm;

    UYVYpl_to_YUVint_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_convertUYVYpl_to_YUVint");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    in_luma    =  prm[tpi].pitch * prm[tpi].height;
        uint32_t    in_chroma  =  prm[tpi].pitch * prm[tpi].height / 2;
        uint32_t    out_size   =  prm[tpi].width * prm[tpi].height * 2;
        uint32_t    num_pts    =  prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        uint8_t   *y     = (uint8_t *) VLIB_memalign(8, in_luma);
        uint8_t   *cr    = (uint8_t *) VLIB_memalign(8, in_chroma);
        uint8_t   *cb    = (uint8_t *) VLIB_memalign(8, in_chroma);
        uint8_t   *yc    = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *yc_cn = (uint8_t *) malloc(out_size);

        /* Only run the test if the buffer allocations fit in the heap */
        if( y && cr && cb && yc && yc_cn ) {

            int32_t    fail, mode;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            y, prm[tpi].staticInY,
                            prm[tpi].width, prm[tpi].height, prm[tpi].pitch,
                            sizeof(uint8_t), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            cr, prm[tpi].staticInCr,
                            prm[tpi].width / 2, prm[tpi].height, prm[tpi].pitch / 2,
                            sizeof(uint8_t), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            cb, prm[tpi].staticInCb,
                            prm[tpi].width / 2, prm[tpi].height, prm[tpi].pitch / 2,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convertUYVYpl_to_YUVint(y, cr, cb, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, yc);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convertUYVYpl_to_YUVint_cn(y, cr, cb, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, yc_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) yc, (void *)yc_cn, out_size);

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutYC != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOutYC, (void *)yc_cn, out_size);
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, pitch=%d, height=%d, num_pts=%d",
                    testPatternString, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, num_pts);
            mode = (prm[tpi].pitch == prm[tpi].width) ? 1 : 2;
            VLIB_formula_add_test(num_pts, prm[tpi].height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, pitch=%d, height=%d, num_pts=%d",
                    prm[tpi].width, prm[tpi].pitch, prm[tpi].height, num_pts);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(yc_cn);
        VLIB_align_free(yc);
        VLIB_align_free(cb);
        VLIB_align_free(cr);
        VLIB_align_free(y);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 2, "pitch == width", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height",
                              "width * height");

    VLIB_profile_setMode(2, 3, "pitch > width", 1); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height; M = height",
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_convertUYVYpl_to_YUVint");
    } else {
        VLIB_convertUYVYpl_to_YUVint_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file: VLIB_convertUYVYpl_to_YUVint_d.c                        */
/* ======================================================================== */

