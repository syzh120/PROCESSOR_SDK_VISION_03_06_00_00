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

#include "VLIB_insertLumaIntoYUYV.h"
#include "VLIB_insertLumaIntoYUYV_cn.h"
#include "VLIB_insertLumaIntoYUYV_idat.h"

/* VLIB_insertLumaIntoYUYV_d:  Test Driver Routine */
void VLIB_insertLumaIntoYUYV_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    insertLumaIntoYUYV_testParams_t   *prm;

    insertLumaIntoYUYV_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_insertLumaIntoYUYV");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size   =  prm[tpi].inCols * prm[tpi].inRows;      /* 1 byte  per pixel in input */
        uint32_t    out_size   =  prm[tpi].inPitch * prm[tpi].inRows * 2; /* 2 bytes per pixel in output */

        /* Allocate buffers for each test vector */
        uint8_t   *pInY        = (uint8_t *) VLIB_memalign(8, inp_size);
        uint8_t   *pOutYUYV    = (uint8_t *) VLIB_memalign(8, out_size);
        uint8_t   *pOutYUYV_cn = (uint8_t *) malloc(out_size);

        /* Only run the test if the buffer allocations fit in the heap */
        if( pInY && pOutYUYV && pOutYUYV_cn ) {

            int32_t    fail, mode;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)128,
                            pInY, prm[tpi].staticIn,
                            prm[tpi].inCols, prm[tpi].inRows, prm[tpi].inCols,
                            sizeof(uint8_t), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)0,
                            pOutYUYV, prm[tpi].staticInYUYV,
                            prm[tpi].inCols, prm[tpi].inRows, prm[tpi].inPitch * 2,
                            sizeof(uint16_t), testPatternString);

            memcpy(pOutYUYV_cn, pOutYUYV, prm[tpi].inPitch * 2 * prm[tpi].inRows);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_insertLumaIntoYUYV(pInY, prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, pOutYUYV);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_insertLumaIntoYUYV_cn(pInY, prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, pOutYUYV_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pOutYUYV, (void *)pOutYUYV_cn, out_size);

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOutYUYV_cn, out_size);
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inPitch=%d, inRows=%d, num_pts=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, inp_size);
            mode = (prm[tpi].inPitch == prm[tpi].inCols) ? 1 : 2;
            VLIB_formula_add_test(inp_size, prm[tpi].inRows, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inPitch=%d, inRows=%d, num_pts=%d",
                    prm[tpi].inCols, prm[tpi].inPitch, prm[tpi].inRows, inp_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pOutYUYV_cn);
        VLIB_align_free(pOutYUYV);
        VLIB_align_free(pInY);
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
        VLIB_memError("VLIB_insertLumaIntoYUYV");
    } else {
        VLIB_insertLumaIntoYUYV_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_insertLumaIntoYUYV_d.c                              */
/* ======================================================================== */

