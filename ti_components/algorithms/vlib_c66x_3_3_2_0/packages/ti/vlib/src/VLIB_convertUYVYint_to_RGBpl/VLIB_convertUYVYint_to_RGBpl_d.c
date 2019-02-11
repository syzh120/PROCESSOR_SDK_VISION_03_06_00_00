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

#include "VLIB_convertUYVYint_to_RGBpl.h"
#include "VLIB_convertUYVYint_to_RGBpl_cn.h"
#include "VLIB_convertUYVYint_to_RGBpl_idat.h"

/* VLIB_convertUYVYint_to_RGBpl_d:  Test Driver Routine */
void VLIB_convertUYVYint_to_RGBpl_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    UYVYint_to_RGBpl_testParams_t   *prm;

    UYVYint_to_RGBpl_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_convertUYVYint_to_RGBpl");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].pitch * prm[tpi].height * 2;
        uint32_t    out_size   =  prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        uint8_t   *yc    = (uint8_t *) VLIB_memalign(8, inp_size);
        uint8_t   *r     = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *g     = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *b     = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *r_cn  = (uint8_t *) malloc(out_size);
        uint8_t   *g_cn  = (uint8_t *) malloc(out_size);
        uint8_t   *b_cn  = (uint8_t *) malloc(out_size);
        int16_t   *coeff = (int16_t *) VLIB_malloc(5 * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( yc && r && g && b && r_cn && g_cn && b_cn && coeff ) {

            int32_t    fail, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            yc, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].pitch * 2,
                            sizeof(uint16_t), testPatternString);

            for( i=0; i < 5; i++ ) {
                coeff[i] = prm[tpi].coeff[i];
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convertUYVYint_to_RGBpl(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, coeff, r, g, b);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convertUYVYint_to_RGBpl_cn(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, coeff, r_cn, g_cn, b_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            if( VLIB_compare_mem((void *) r, (void *)r_cn, out_size) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) g, (void *)g_cn, out_size) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) b, (void *)b_cn, out_size) == vlib_KERNEL_FAIL ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            } else {
                status_nat_vs_int = vlib_KERNEL_PASS;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutR != NULL &&
                prm[tpi].staticOutG != NULL &&
                prm[tpi].staticOutB != NULL ) {

                if( VLIB_compare_mem((void *) prm[tpi].staticOutR, (void *)r_cn, out_size) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutG, (void *)g_cn, out_size) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutB, (void *)b_cn, out_size) == vlib_KERNEL_FAIL ) {
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
                    testPatternString, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_size);
            VLIB_formula_add_test(out_size, prm[tpi].height, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, pitch=%d, height=%d, num_pts=%d",
                    prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(coeff);
        free(b_cn);
        free(g_cn);
        free(r_cn);
        VLIB_align_free(b);
        VLIB_align_free(g);
        VLIB_align_free(r);
        VLIB_align_free(yc);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height; M=height",
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_convertUYVYint_to_RGBpl");
    } else {
        VLIB_convertUYVYint_to_RGBpl_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file: VLIB_convertUYVYint_to_RGBpl_d.c                           */
/* ======================================================================== */

