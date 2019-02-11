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

#include "VLIB_L2_norm_i32.h"
#include "VLIB_L2_norm_i32_cn.h"
#include "VLIB_L2_norm_i32_idat.h"

#define EPSILON 0.001       /* Degree of accuracy */

/* VLIB_L2_norm_i32_d:  Test Driver Routine */
void VLIB_L2_norm_i32_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    L2_norm_i32_testParams_t   *prm;

    L2_norm_i32_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_L2_norm_i32");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint32_t   *pData  = (uint32_t *) VLIB_malloc(prm[tpi].len * sizeof(uint32_t));
        VLIB_F32    norm;
        VLIB_F32    norm_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( pData ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint32_t)1,
                            pData, prm[tpi].staticIn,
                            prm[tpi].len, 1, prm[tpi].len * sizeof(pData[0]),
                            sizeof(pData[0]), testPatternString);


            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            norm = VLIB_L2_norm_i32(pData, prm[tpi].len);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            norm_cn = VLIB_L2_norm_i32(pData, prm[tpi].len);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if( abs(norm - norm_cn) > EPSILON ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != 0x0 ) {
                if( abs(prm[tpi].staticOut - norm_cn) > EPSILON ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | len=%d",
                    testPatternString, prm[tpi].len);
            VLIB_formula_add_test(prm[tpi].len, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "len=%d",
                    prm[tpi].len);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(pData);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = len",
                              "len");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_L2_norm_i32");
    } else {
        VLIB_L2_norm_i32_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_L2_norm_i32_d.c                                      */
/* ======================================================================== */

