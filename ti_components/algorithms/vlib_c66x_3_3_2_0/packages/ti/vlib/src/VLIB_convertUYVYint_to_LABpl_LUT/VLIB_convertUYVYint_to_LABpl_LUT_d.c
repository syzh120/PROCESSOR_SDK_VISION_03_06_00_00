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

#include "VLIB_convertUYVYint_to_LABpl_LUT.h"
#include "VLIB_convertUYVYint_to_LABpl_LUT_cn.h"
#include "VLIB_convertUYVYint_to_LABpl_LUT_idat.h"

#include "../VLIB_initUYVYint_to_LABpl_LUT/VLIB_initUYVYint_to_LABpl_LUT_cn.h"

/* VLIB_convertUYVYint_to_LABpl_LUT_d:  Test Driver Routine */
void VLIB_convertUYVYint_to_LABpl_LUT_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    UYVYint_to_LABpl_LUT_testParams_t   *prm;

    UYVYint_to_LABpl_LUT_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_convertUYVYint_to_LABpl_LUT");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].pitch * prm[tpi].height * 2;
        uint32_t    out_size   =  prm[tpi].width * prm[tpi].height;
        uint32_t    lut_size   =  4 * 2 * ((256 >> prm[tpi].d) + 1) *
                                 ((256 >> prm[tpi].d) + 1) *
                                 ((256 >> prm[tpi].d) + 1);

        /* Allocate buffers for each test vector */
        uint8_t    *yc    =  (uint8_t *) VLIB_memalign(8, inp_size);
        uint16_t   *L     = (uint16_t *) VLIB_memalign(8, out_size * sizeof(uint16_t));
        uint16_t   *a     = (uint16_t *) VLIB_memalign(8, out_size * sizeof(uint16_t));
        uint16_t   *b     = (uint16_t *) VLIB_memalign(8, out_size * sizeof(uint16_t));
        uint16_t   *L_cn  = (uint16_t *) malloc(out_size * sizeof(uint16_t));
        uint16_t   *a_cn  = (uint16_t *) malloc(out_size * sizeof(uint16_t));
        uint16_t   *b_cn  = (uint16_t *) malloc(out_size * sizeof(uint16_t));
        int16_t    *coeff = (int16_t *) VLIB_malloc(5 * sizeof(int16_t));
        VLIB_F32   *whitePoint = (VLIB_F32 *) VLIB_malloc(3 * sizeof(VLIB_F32));
        uint16_t   *LabExt = (uint16_t *) malloc(lut_size); /* Should be 8 byte aligned, malloc aligns to 8 */

        /* Only run the test if the buffer allocations fit in the heap */
        if( yc && L && a && b && L_cn && a_cn && b_cn && coeff && whitePoint && LabExt ) {

            int32_t    fail, i, j;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            yc, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].pitch * 2,
                            sizeof(uint16_t), testPatternString);

            for( i=0; i < 5; i++ ) {
                coeff[i] = prm[tpi].coeff[i];
            }

            for( i=0; i < 3; i++ ) {
                whitePoint[i] = prm[tpi].whitePoint[i];
            }

            /* Using natural c version only so as to not skew the code size measurement from this test */
            VLIB_initUYVYint_to_LABpl_LUT_cn(prm[tpi].d, coeff, whitePoint, LabExt);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convertUYVYint_to_LABpl_LUT(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, prm[tpi].d, LabExt, L, a, b);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convertUYVYint_to_LABpl_LUT_cn(yc, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, prm[tpi].d, LabExt, L_cn, a_cn, b_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( j=0; j < prm[tpi].height; j++ ) {
                for( i=0; i < prm[tpi].width; i++ ) {
                    if( L[j * prm[tpi].width + i] != L_cn[j * prm[tpi].width + i] ||
                        a[j * prm[tpi].width + i] != a_cn[j * prm[tpi].width + i] ||
                        b[j * prm[tpi].width + i] != b_cn[j * prm[tpi].width + i] ) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf("L[%d,%d] O=%d C=%d\n", i, j, L[j * prm[tpi].width + i], L_cn[j * prm[tpi].width + i]);
                            printf("a[%d,%d] O=%d C=%d\n", i, j, a[j * prm[tpi].width + i], a_cn[j * prm[tpi].width + i]);
                            printf("b[%d,%d] O=%d C=%d\n", i, j, b[j * prm[tpi].width + i], b_cn[j * prm[tpi].width + i]);
                        }
                    }
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutL != NULL &&
                prm[tpi].staticOutA != NULL &&
                prm[tpi].staticOutB != NULL ) {

                for( j=0; j < prm[tpi].height; j++ ) {
                    for( i=0; i < prm[tpi].width; i++ ) {
                        if( prm[tpi].staticOutL[j * prm[tpi].width + i] != L_cn[j * prm[tpi].width + i] ||
                            prm[tpi].staticOutA[j * prm[tpi].width + i] != a_cn[j * prm[tpi].width + i] ||
                            prm[tpi].staticOutB[j * prm[tpi].width + i] != b_cn[j * prm[tpi].width + i] ) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            if( LevelOfFeedback > 0 ) {
                                printf("L[%d,%d] S=%d C=%d\n", i, j, prm[tpi].staticOutL[j * prm[tpi].width + i], L_cn[j * prm[tpi].width + i]);
                                printf("a[%d,%d] S=%d C=%d\n", i, j, prm[tpi].staticOutA[j * prm[tpi].width + i], a_cn[j * prm[tpi].width + i]);
                                printf("b[%d,%d] S=%d C=%d\n", i, j, prm[tpi].staticOutB[j * prm[tpi].width + i], b_cn[j * prm[tpi].width + i]);
                            }
                        }
                    }
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
        free(LabExt);
        VLIB_free(whitePoint);
        VLIB_free(coeff);
        free(b_cn);
        free(a_cn);
        free(L_cn);
        VLIB_align_free(b);
        VLIB_align_free(a);
        VLIB_align_free(L);
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
        VLIB_memError("VLIB_convertUYVYint_to_LABpl_LUT");
    } else {
        VLIB_convertUYVYint_to_LABpl_LUT_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_LABpl_LUT_d.c                      */
/* ======================================================================== */

