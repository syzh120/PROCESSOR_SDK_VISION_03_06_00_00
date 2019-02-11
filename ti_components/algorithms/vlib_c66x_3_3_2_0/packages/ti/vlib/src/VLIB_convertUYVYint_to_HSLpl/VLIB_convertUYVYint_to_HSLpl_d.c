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

#include "VLIB_convertUYVYint_to_HSLpl.h"
#include "VLIB_convertUYVYint_to_HSLpl_cn.h"
#include "VLIB_convertUYVYint_to_HSLpl_idat.h"

/* VLIB_convertUYVYint_to_HSLpl_d:  Test Driver Routine */
void VLIB_convertUYVYint_to_HSLpl_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    UYVYint_to_HSLpl_testParams_t   *prm;

    UYVYint_to_HSLpl_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_convertUYVYint_to_HSLpl");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].pitch * prm[tpi].height * 2;
        uint32_t    out_size   =  prm[tpi].width * prm[tpi].height;
        uint32_t    div_table_size = 510;

        /* Allocate buffers for each test vector */
        uint8_t    *yc    = (uint8_t *) VLIB_memalign(8, inp_size);
        uint16_t   *H     = (uint16_t *) VLIB_memalign(8, out_size * sizeof(uint16_t));
        uint8_t    *S     = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t    *L     = (uint8_t *) VLIB_memalign(8, out_size);
        uint16_t   *H_cn  = (uint16_t *) malloc(out_size * sizeof(uint16_t));
        uint8_t    *S_cn  = (uint8_t *) malloc(out_size);
        uint8_t    *L_cn  = (uint8_t *) malloc(out_size);
        int16_t    *coeff = (int16_t *) VLIB_malloc(5 * sizeof(int16_t));
        uint16_t   *div_table = (uint16_t *) VLIB_malloc(div_table_size * sizeof(uint16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( yc && H && S && L && H_cn && S_cn && L_cn && coeff && div_table ) {

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

            for( i=0; i < div_table_size; i++ ) {
                div_table[i] = prm[tpi].div_table[i];
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convertUYVYint_to_HSLpl(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, coeff, div_table, H, S, L);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convertUYVYint_to_HSLpl_cn(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, coeff, div_table, H_cn, S_cn, L_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            if( VLIB_compare_mem((void *) H, (void *)H_cn, out_size * sizeof(uint16_t)) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) S, (void *)S_cn, out_size) == vlib_KERNEL_FAIL ||
                VLIB_compare_mem((void *) L, (void *)L_cn, out_size) == vlib_KERNEL_FAIL ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            } else {
                status_nat_vs_int = vlib_KERNEL_PASS;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutH != NULL &&
                prm[tpi].staticOutS != NULL &&
                prm[tpi].staticOutL != NULL ) {

                if( VLIB_compare_mem((void *) prm[tpi].staticOutH, (void *)H_cn, out_size * sizeof(uint16_t)) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutS, (void *)S_cn, out_size) == vlib_KERNEL_FAIL ||
                    VLIB_compare_mem((void *) prm[tpi].staticOutL, (void *)L_cn, out_size) == vlib_KERNEL_FAIL ) {
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
            VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, pitch=%d, height=%d, num_pts=%d",
                    prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(div_table);
        VLIB_free(coeff);
        free(L_cn);
        free(S_cn);
        free(H_cn);
        VLIB_align_free(L);
        VLIB_align_free(S);
        VLIB_align_free(H);
        VLIB_align_free(yc);
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
        VLIB_memError("VLIB_convertUYVYint_to_HSLpl");
    } else {
        VLIB_convertUYVYint_to_HSLpl_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_HSLpl_d.c                          */
/* ======================================================================== */

