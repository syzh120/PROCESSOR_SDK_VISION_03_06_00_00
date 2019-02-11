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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#include "VLIB_legendreMoments.h"
#include "VLIB_legendreMoments_cn.h"
#include "VLIB_legendreMoments_idat.h"

#include "../VLIB_legendreMoments_Init/VLIB_legendreMoments_Init_cn.h"

/* VLIB_legendreMoments_d:  Test Driver Routine */
void VLIB_legendreMoments_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    legendreMoments_testParams_t   *prm;

    legendreMoments_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_legendreMoments");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size     =   prm[tpi].ImH  * prm[tpi].ImH;
        uint32_t    lpoly_size   =   (prm[tpi].Order + 1) * (prm[tpi].ImH);
        uint32_t    moments_size =   (prm[tpi].Order + 1) * (prm[tpi].Order + 1);

        /* Allocate buffers for each test vector */
        int16_t   *Im          =  (int16_t *) VLIB_malloc(inp_size * sizeof(int16_t));
        int16_t   *LPoly       =  (int16_t *) VLIB_malloc(lpoly_size * sizeof(int16_t));
        int16_t   *LMoments    =  (int16_t *) VLIB_malloc(moments_size * sizeof(int16_t));
        int16_t   *LMoments_cn =  (int16_t *) malloc(moments_size * sizeof(int16_t));
        int16_t    Factor1;

        /* Only run the test if the buffer allocations fit in the heap */
        if( Im && LPoly && LMoments && LMoments_cn ) {

            int32_t    fail, i, j;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (int16_t)255,
                            Im, prm[tpi].staticIn,
                            prm[tpi].ImH, prm[tpi].ImH, prm[tpi].ImH * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* normalize the image */
            for( i=0; i < prm[tpi].ImH; i++ ) {
                for( j=0; j < prm[tpi].ImH; j++ ) {
                    Im[i * prm[tpi].ImH + j] &= 0x7fff; // Remove the sign bit from random input
                    Im[i * prm[tpi].ImH + j] = (int16_t)((32767 / prm[tpi].maxValue) * Im[i * prm[tpi].ImH + j]);
                }
            }

            /* Set the moments and the polynomial to 0 */
            memset(LPoly, 0, lpoly_size * sizeof(int16_t));
            memset(LMoments, 0, moments_size * sizeof(int16_t));
            memset(LMoments_cn, 0, moments_size * sizeof(int16_t));

            if( LevelOfFeedback > 0 ) {
                printf("Order = %d\n", prm[tpi].Order);
                printf("ImH = %d\n", prm[tpi].ImH);
            }

            /* Test optimized kernel */
            VLIB_legendreMoments_Init_cn(LPoly, prm[tpi].Order, prm[tpi].ImH, &Factor1);

            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_legendreMoments(Im, LMoments, LPoly, prm[tpi].Order, prm[tpi].ImH, Factor1);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_legendreMoments_cn(Im, LMoments_cn, LPoly, prm[tpi].Order, prm[tpi].ImH, Factor1);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) LMoments, (void *)LMoments_cn, moments_size * sizeof(LMoments[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)LMoments_cn, moments_size * sizeof(LMoments_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | ImH=%d, Order=%d",
                    testPatternString, prm[tpi].ImH, prm[tpi].Order);
            VLIB_formula_add_test(moments_size * inp_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "ImH=%d, Order=%d",
                    prm[tpi].ImH, prm[tpi].Order);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(LMoments_cn);
        VLIB_free(LMoments);
        VLIB_free(LPoly);
        VLIB_free(Im);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = (Order+1)*(Order+1)*ImH*ImH",
                              "(Order+1)*(Order+1)*ImH*ImH");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_legendreMoments");
    } else {
        VLIB_legendreMoments_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_legendreMoments_d.c                                  */
/* ======================================================================== */

