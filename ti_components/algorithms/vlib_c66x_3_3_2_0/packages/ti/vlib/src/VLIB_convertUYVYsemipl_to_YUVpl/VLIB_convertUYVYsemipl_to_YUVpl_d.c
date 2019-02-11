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

#include "VLIB_convertUYVYsemipl_to_YUVpl.h"
#include "VLIB_convertUYVYsemipl_to_YUVpl_cn.h"
#include "VLIB_convertUYVYsemipl_to_YUVpl_idat.h"

/* VLIB_convertUYVYsemipl_to_YUVpl_d:  Test Driver Routine */
void VLIB_convertUYVYsemipl_to_YUVpl_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    UYVYsemipl_to_YUVpl_testParams_t   *prm;

    UYVYsemipl_to_YUVpl_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_convertUYVYsemipl_to_YUVpl");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].pitch * prm[tpi].height;
        uint32_t    out_size   =  prm[tpi].width * prm[tpi].height / 2;
        uint32_t    num_pts    =  prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        uint8_t   *crcb  = (uint8_t *) VLIB_memalign(8, inp_size);
        uint8_t   *cr    = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *cb    = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *cr_cn = (uint8_t *) malloc(out_size);
        uint8_t   *cb_cn = (uint8_t *) malloc(out_size);

        /* Only run the test if the buffer allocations fit in the heap */
        if( crcb && cr && cb && cr_cn && cb_cn ) {

            int32_t    fail, mode;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            crcb, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].pitch,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convertUYVYsemipl_to_YUVpl(crcb, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, cr, cb);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convertUYVYsemipl_to_YUVpl_cn(crcb, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, cr_cn, cb_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            if( VLIB_compare_mem((void *) cr, (void *)cr_cn, out_size) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) cb, (void *)cb_cn, out_size) == vlib_KERNEL_FAIL ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            } else {
                status_nat_vs_int = vlib_KERNEL_PASS;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutCr != NULL &&
                prm[tpi].staticOutCb != NULL ) {

                if( VLIB_compare_mem((void *) prm[tpi].staticOutCr, (void *)cr_cn, out_size) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutCb, (void *)cb_cn, out_size) == vlib_KERNEL_FAIL ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                } else {
                    status_nat_vs_ref = vlib_KERNEL_PASS;
                }
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
        free(cb_cn);
        free(cr_cn);
        VLIB_align_free(cb);
        VLIB_align_free(cr);
        VLIB_align_free(crcb);
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
        VLIB_memError("VLIB_convertUYVYsemipl_to_YUVpl");
    } else {
        VLIB_convertUYVYsemipl_to_YUVpl_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYsemipl_to_YUVpl_d.c                       */
/* ======================================================================== */

