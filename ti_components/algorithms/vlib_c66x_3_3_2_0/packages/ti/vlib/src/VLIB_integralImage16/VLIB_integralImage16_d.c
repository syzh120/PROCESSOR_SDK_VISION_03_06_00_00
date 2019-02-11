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

#include "VLIB_integralImage16.h"
#include "VLIB_integralImage16_cn.h"
#include "VLIB_integralImage16_idat.h"

/* VLIB_integralImage16_d:  Test Driver Routine */
void VLIB_integralImage16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    integralImage16_testParams_t   *prm;

    integralImage16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_integralImage16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    img_size =   prm[tpi].inCols * prm[tpi].inRows;

        /* Allocate buffers for each test vector */
        uint16_t   *pIn          = (uint16_t *) VLIB_malloc(img_size * sizeof(uint16_t));
        uint32_t   *pOut         = (uint32_t *) VLIB_malloc(img_size * sizeof(uint32_t));
        uint32_t   *pOut_cn      = (uint32_t *) malloc(img_size * sizeof(uint32_t));
        uint32_t   *pLastLine    = (uint32_t *) VLIB_malloc(prm[tpi].inCols * sizeof(uint32_t));
        uint32_t   *pLastLine_cn = (uint32_t *) malloc(prm[tpi].inCols * sizeof(uint32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pIn && pOut && pOut_cn && pLastLine && pLastLine_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint16_t)1,
                            pIn, prm[tpi].staticIn,
                            prm[tpi].inCols, prm[tpi].inRows, prm[tpi].inCols * sizeof(uint16_t),
                            sizeof(uint16_t), testPatternString);

            /* initialize the lastLine buffer */
            memset(pLastLine,    0, prm[tpi].inCols * sizeof(uint32_t));
            memset(pLastLine_cn, 0, prm[tpi].inCols * sizeof(uint32_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_integralImage16(pIn, prm[tpi].inCols, prm[tpi].inRows, pLastLine, pOut);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_integralImage16_cn(pIn, prm[tpi].inCols, prm[tpi].inRows, pLastLine_cn, pOut_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pOut, (void *)pOut_cn, img_size * sizeof(uint32_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOut_cn, img_size * sizeof(uint32_t));
            }
#if 0
            {
                int    i, j;

                for( i=0; i < prm[tpi].inRows; i++ ) {
                    for( j=0; j < prm[tpi].inCols; j++ ) {
                        printf("%d, ", pOut[i * prm[tpi].inCols + j]);
                    }

                    printf("\n");
                }
            }
#endif
            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inRows=%d, num_pt=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inRows, img_size);
            VLIB_formula_add_test(img_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inRows=%d, num_pt=%d",
                    prm[tpi].inCols, prm[tpi].inRows, img_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pLastLine_cn);
        VLIB_free(pLastLine);
        free(pOut_cn);
        VLIB_free(pOut);
        VLIB_free(pIn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = inCols * inRows",
                              "inCols * inRows");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_integralImage16");
    } else {
        VLIB_integralImage16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_integralImage16_d.c                                  */
/* ======================================================================== */

