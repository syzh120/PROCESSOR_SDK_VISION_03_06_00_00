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

#include "VLIB_histogram_1D_Init_U8.h"
#include "VLIB_histogram_1D_Init_U8_cn.h"
#include "VLIB_histogram_1D_Init_U8_idat.h"

/* VLIB_histogram_1D_Init_U8_d:  Test Driver Routine */
void VLIB_histogram_1D_Init_U8_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    histogram_1D_Init_U8_testParams_t   *prm;

    histogram_1D_Init_U8_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_histogram_1D_Init_U8");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint8_t   *binEdges       =  (uint8_t *) VLIB_malloc(prm[tpi].numBins * sizeof(uint8_t));
        uint8_t   *histArray      =  (uint8_t *) VLIB_malloc(prm[tpi].maxSize * sizeof(uint8_t));
        uint8_t   *histArray_cn   =  (uint8_t *) malloc(prm[tpi].maxSize * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( binEdges && histArray && histArray_cn ) {

            int32_t    fail, numIterations;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            binEdges, prm[tpi].staticIn,
                            prm[tpi].numBins, 1, prm[tpi].numBins,
                            sizeof(uint8_t), testPatternString);

            /* Clear the histArray output, as per fn requirement */
            memset(histArray, 0, prm[tpi].maxSize * sizeof(uint8_t));
            memset(histArray_cn, 0, prm[tpi].maxSize * sizeof(uint8_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_histogram_1D_Init_U8(binEdges, prm[tpi].numBins, histArray);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_histogram_1D_Init_U8_cn(binEdges, prm[tpi].numBins, histArray_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) histArray, (void *)histArray_cn, prm[tpi].maxSize * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)histArray_cn, prm[tpi].maxSize * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;
            numIterations = binEdges[prm[tpi].numBins - 1] - binEdges[0] + 1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | numBins=%d, maxSize=%d",
                    testPatternString, prm[tpi].numBins, prm[tpi].maxSize);
            VLIB_formula_add_test(numIterations, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numBins=%d, maxSize=%d",
                    prm[tpi].numBins, prm[tpi].maxSize);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(histArray_cn);
        VLIB_free(histArray);
        VLIB_free(binEdges);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = binEdges[numBins-1] - binEdges[0] + 1",
                              "binEdges[numBins-1] - binEdges[0] + 1");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_histogram_1D_Init_U8");
    } else {
        VLIB_histogram_1D_Init_U8_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_histogram_1D_Init_U8_d.c                            */
/* ======================================================================== */

