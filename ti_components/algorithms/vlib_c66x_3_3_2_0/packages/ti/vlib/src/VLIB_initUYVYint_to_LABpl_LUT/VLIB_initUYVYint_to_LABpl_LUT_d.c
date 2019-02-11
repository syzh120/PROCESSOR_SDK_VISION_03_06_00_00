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

#include "VLIB_initUYVYint_to_LABpl_LUT.h"
#include "VLIB_initUYVYint_to_LABpl_LUT_cn.h"
#include "VLIB_initUYVYint_to_LABpl_LUT_idat.h"

/* VLIB_initUYVYint_to_LABpl_LUT_d:  Test Driver Routine */
void VLIB_initUYVYint_to_LABpl_LUT_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    initUYVYint_to_LABpl_LUT_testParams_t   *prm;

    initUYVYint_to_LABpl_LUT_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_initUYVYint_to_LABpl_LUT");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    lut_size   =  4 * 2 * ((256 >> prm[tpi].d) + 1) *
                                 ((256 >> prm[tpi].d) + 1) *
                                 ((256 >> prm[tpi].d) + 1);

        /* Allocate buffers for each test vector */
        int16_t    *coeff = (int16_t *) VLIB_malloc(5 * sizeof(int16_t));
        VLIB_F32   *whitePoint = (VLIB_F32 *) VLIB_malloc(3 * sizeof(VLIB_F32));
        uint16_t   *Lab =    (uint16_t *) malloc(lut_size); /* Should be 8 byte aligned, malloc aligns to 8 */
        uint16_t   *Lab_cn = (uint16_t *) malloc(lut_size); /* Should be 8 byte aligned, malloc aligns to 8 */

        /* Only run the test if the buffer allocations fit in the heap */
        if( coeff && whitePoint && Lab && Lab_cn ) {

            int32_t    fail, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            NULL, NULL,
                            NULL, NULL, NULL,
                            sizeof(uint16_t), testPatternString);

            for( i=0; i < 5; i++ ) {
                coeff[i] = prm[tpi].coeff[i];
            }

            for( i=0; i < 3; i++ ) {
                whitePoint[i] = prm[tpi].whitePoint[i];
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_initUYVYint_to_LABpl_LUT(prm[tpi].d, coeff, whitePoint, Lab);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_initUYVYint_to_LABpl_LUT_cn(prm[tpi].d, coeff, whitePoint, Lab_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) Lab, (void *)Lab_cn, lut_size);

            for( i=0; i < lut_size / 2; i++ ) {
                if( Lab[i] != Lab_cn[i] ) {
                    printf("[%d] O=%d C=%d\n", i, Lab[i], Lab_cn[i]);
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)Lab_cn, lut_size * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | d=%d, lut_size=%d bytes",
                    testPatternString, prm[tpi].d, lut_size);
            VLIB_formula_add_test(lut_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "d=%d, lut_size=%d bytes",
                    prm[tpi].d, lut_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(Lab_cn);
        free(Lab);
        VLIB_free(whitePoint);
        VLIB_free(coeff);
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
        VLIB_memError("VLIB_initUYVYint_to_LABpl_LUT");
    } else {
        VLIB_initUYVYint_to_LABpl_LUT_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_initUYVYint_to_LABpl_LUT_d.c                         */
/* ======================================================================== */

