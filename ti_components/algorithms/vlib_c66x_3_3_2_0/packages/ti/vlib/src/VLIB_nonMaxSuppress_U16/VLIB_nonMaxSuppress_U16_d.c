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

#include "VLIB_nonMaxSuppress_U16.h"
#include "VLIB_nonMaxSuppress_U16_cn.h"
#include "VLIB_nonMaxSuppress_U16_idat.h"

/* VLIB_nonMaxSuppress_U16_d:  Test Driver Routine */
void VLIB_nonMaxSuppress_U16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    nonMaxSuppressU16_testParams_t   *prm;

    nonMaxSuppressU16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_nonMaxSuppress_U16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].w * prm[tpi].h;
        uint32_t    buf_size =   2 * prm[tpi].filterWidth + prm[tpi].w * prm[tpi].h;
        uint32_t    out_size =   2 * prm[tpi].w * prm[tpi].h + 2;

        /* Allocate buffers for each test vector */
        uint16_t   *im           =  (uint16_t *) VLIB_malloc(inp_size * sizeof(uint16_t));
        uint16_t   *buffer       =  (uint16_t *) VLIB_malloc(buf_size * sizeof(uint16_t));
        int16_t    *pixIndex_opt =  (int16_t *) VLIB_malloc(out_size * sizeof(int16_t));
        int16_t    *pixIndex_cn  =  (int16_t *) malloc(out_size * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( im && buffer && pixIndex_opt && pixIndex_cn ) {

            int32_t    fail, mode;
            int16_t    no_of_pts_opt, no_of_pts_cn, no_of_pts_ref;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            im, prm[tpi].staticIn,
                            prm[tpi].w, prm[tpi].h, prm[tpi].w * sizeof(uint16_t),
                            sizeof(uint16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_nonMaxSuppress_U16(im, prm[tpi].w, prm[tpi].h,
                                    prm[tpi].filterWidth, prm[tpi].threshold,
                                    buffer, pixIndex_opt);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_nonMaxSuppress_U16_cn(im, prm[tpi].w, prm[tpi].h,
                                       prm[tpi].filterWidth, prm[tpi].threshold,
                                       buffer, pixIndex_cn);
            VLIB_profile_stop();

            no_of_pts_opt = pixIndex_opt[0];
            no_of_pts_cn  = pixIndex_cn[0];

            /* Compare natural C Output and Optimized Output */
            if( no_of_pts_opt == no_of_pts_cn ) {
#if 0
                int    i;

                for( i=0; i < 2 * no_of_pts_opt + 2; i+=2 ) {
                    if( i % 20 == 0 ) {
                        printf("\n");
                    }
                    printf("%d, %d, ", pixIndex_opt[i], pixIndex_opt[i + 1]);
                }

#endif
                status_nat_vs_int = VLIB_compare_mem((void *) pixIndex_opt, (void *)pixIndex_cn, (no_of_pts_opt * 2 + 2) * sizeof(uint16_t));
            } else {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {

                no_of_pts_ref = prm[tpi].staticOut[0];

                if( no_of_pts_ref == no_of_pts_cn ) {
                    status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pixIndex_cn, (no_of_pts_cn * 2 + 2) * sizeof(uint16_t));
                } else {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            mode = prm[tpi].filterWidth >> 1; /* 3= mode 1, 5= mode 2, 7= mode 3*/

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | w=%d, h=%d, filterWidth=%d, threshold=%d, in size=%d",
                    testPatternString, prm[tpi].w, prm[tpi].h, prm[tpi].filterWidth, prm[tpi].threshold, inp_size);
            VLIB_formula_add_test(inp_size, NULL, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "w=%d, h=%d, filterWidth=%d, threshold=%d, in size=%d",
                    prm[tpi].w, prm[tpi].h, prm[tpi].filterWidth, prm[tpi].threshold, inp_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pixIndex_cn);
        VLIB_free(pixIndex_opt);
        VLIB_free(buffer);
        VLIB_free(im);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 2, "filterWidth = 3", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = w * h",
                              "w * h");

    VLIB_profile_setMode(2, 2, "filterWidth = 5", 0); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = w * h",
                              "w * h");

    VLIB_profile_setMode(3, 2, "filterWidth = 7", 1); /* Mode 3 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = w * h",
                              "w * h");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_nonMaxSuppress_U16");
    } else {
        VLIB_nonMaxSuppress_U16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_nonMaxSuppress_U16_d.c                               */
/* ======================================================================== */

