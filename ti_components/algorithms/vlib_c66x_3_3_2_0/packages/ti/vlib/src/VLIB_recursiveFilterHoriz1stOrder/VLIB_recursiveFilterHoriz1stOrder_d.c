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

#include "VLIB_recursiveFilterHoriz1stOrder.h"
#include "VLIB_recursiveFilterHoriz1stOrder_cn.h"
#include "VLIB_recursiveFilterHoriz1stOrder_idat.h"

/* ///////////////////////////////////// */
/* Makes a w * h custom pattern          */
/* ///////////////////////////////////// */
static void CreatePattern1(uint8_t *p, int16_t w, int16_t h)
{
    int32_t    i;

    for( i = 0; i < w * h; i++ ) {
        int32_t    x = i % w;
        int32_t    y = i / w;

        p[i] = 12 * (x | y) + 127;
    }
}

/* VLIB_recursiveFilterHoriz1stOrder_d:  Test Driver Routine */
void VLIB_recursiveFilterHoriz1stOrder_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    recursiveFilterHoriz1stOrder_testParams_t   *prm;

    recursiveFilterHoriz1stOrder_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_recursiveFilterHoriz1stOrder");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint8_t   *in      = (uint8_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height * sizeof(uint8_t));
        uint8_t   *out     = (uint8_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height * sizeof(uint8_t));
        uint8_t   *out_cn  = (uint8_t *) malloc(prm[tpi].width * prm[tpi].height * sizeof(uint8_t));
        uint8_t   *scratch = (uint8_t *) VLIB_malloc(8 * prm[tpi].width * sizeof(uint8_t));
        uint8_t   *boundaryLeft  = (uint8_t *) VLIB_malloc(prm[tpi].height * sizeof(uint8_t));
        uint8_t   *boundaryRight = (uint8_t *) VLIB_malloc(prm[tpi].height * sizeof(uint8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( in && out && out_cn && scratch && boundaryLeft && boundaryRight ) {

            int32_t    fail;
            uint8_t   *pBoundaryLeft = NULL, *pBoundaryRight = NULL;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern, (uint8_t)255,
                            in, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(in[0]),
                            sizeof(in[0]), testPatternString);

            if( prm[tpi].testPattern == CUSTOM ) {
                /* Synthetic motion sequence */
                CreatePattern1(in, prm[tpi].width, prm[tpi].height);
            }

            if( prm[tpi].boundaryLeft ) {
                memcpy(boundaryLeft, prm[tpi].boundaryLeft, prm[tpi].height);
                pBoundaryLeft = boundaryLeft;
            }
            if( prm[tpi].boundaryRight ) {
                memcpy(boundaryRight, prm[tpi].boundaryRight, prm[tpi].height);
                pBoundaryRight = boundaryRight;
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_recursiveFilterHoriz1stOrder(out, in, prm[tpi].width, prm[tpi].height, prm[tpi].weight,
                                              pBoundaryLeft, pBoundaryRight, scratch);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_recursiveFilterHoriz1stOrder_cn(out_cn, in, prm[tpi].width, prm[tpi].height, prm[tpi].weight,
                                                 pBoundaryLeft, pBoundaryRight, scratch);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) out, (void *)out_cn, prm[tpi].width * prm[tpi].height * sizeof(out_cn[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)out_cn, prm[tpi].width * prm[tpi].height * sizeof(out_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height);
            VLIB_formula_add_test(prm[tpi].width * prm[tpi].height, prm[tpi].height, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d",
                    prm[tpi].width, prm[tpi].height);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(boundaryRight);
        VLIB_free(boundaryLeft);
        VLIB_free(scratch);
        free(out_cn);
        VLIB_free(out);
        VLIB_free(in);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height; M = height",
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_recursiveFilterHoriz1stOrder");
    } else {
        VLIB_recursiveFilterHoriz1stOrder_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_recursiveFilterHoriz1stOrder_d.c                     */
/* ======================================================================== */

