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

#include "VLIB_extractLumaFromYUYV.h"
#include "VLIB_extractLumaFromYUYV_cn.h"
#include "VLIB_extractLumaFromYUYV_idat.h"

/* VLIB_extractLumaFromYUYV_d:  Test Driver Routine */
void VLIB_extractLumaFromYUYV_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    extractLumaFromYUYV_testParams_t   *prm;

    extractLumaFromYUYV_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_extractLumaFromYUYV");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].inPitch * prm[tpi].inRows * 2; /* 2 bytes per pixel in input */
        uint32_t    out_luma   =  prm[tpi].inCols  * prm[tpi].inRows;     /* 1 byte  per pixel in output */

        /* Allocate buffers for each test vector */
        uint8_t   *pInYUYV   = (uint8_t *) VLIB_memalign(8, inp_size);
        uint8_t   *pOutY     = (uint8_t *) VLIB_memalign(8, out_luma);
        uint8_t   *pOutY_cn  = (uint8_t *) malloc(out_luma);

        /* Only run the test if the buffer allocations fit in the heap */
        if( pInYUYV && pOutY && pOutY_cn ) {

            int32_t    fail, mode;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            pInYUYV, prm[tpi].staticIn,
                            prm[tpi].inCols, prm[tpi].inRows, prm[tpi].inPitch * 2,
                            sizeof(uint16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_extractLumaFromYUYV(pInYUYV, prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, pOutY);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_extractLumaFromYUYV_cn(pInYUYV, prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, pOutY_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pOutY, (void *)pOutY_cn, out_luma);

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutY != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOutY, (void *)pOutY_cn, out_luma);
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inPitch=%d, inRows=%d, num_pts=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, out_luma);
            mode = (prm[tpi].inPitch == prm[tpi].inCols) ? 1 : 2;
            VLIB_formula_add_test(out_luma, prm[tpi].inRows, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inPitch=%d, inRows=%d, num_pts=%d",
                    prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, out_luma);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pOutY_cn);
        VLIB_align_free(pOutY);
        VLIB_align_free(pInYUYV);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 2, "inPitch == inCols", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inCols * inRows",
                              "inCols * inRows");

    VLIB_profile_setMode(2, 3, "inPitch > inCols", 1); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inCols * inRows; M = inRows",
                              "inCols * inRows");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_extractLumaFromYUYV");
    } else {
        VLIB_extractLumaFromYUYV_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_extractLumaFromYUYV_d.c                              */
/* ======================================================================== */

