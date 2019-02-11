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

#include "VLIB_hammingDistance.h"
#include "VLIB_hammingDistance_cn.h"
#include "VLIB_hammingDistance_idat.h"

/* VLIB_hammingDistance_d:  Test Driver Routine */
void VLIB_hammingDistance_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    hammingDistance_testParams_t   *prm;

    hammingDistance_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_hammingDistance");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    mode0_inSize =   prm[tpi].xSize * prm[tpi].ySize;
        uint32_t    mode1_inSize =   prm[tpi].xSize;

        /* Allocate buffers for each test vector */
        uint8_t    *pString1            = (uint8_t *) VLIB_malloc(mode0_inSize * sizeof(uint8_t));
        uint8_t    *pString2;
        uint32_t   *pHammingDistance    = (uint32_t *) VLIB_malloc(prm[tpi].ySize * sizeof(uint32_t));
        uint32_t   *pHammingDistance_cn = (uint32_t *) malloc(prm[tpi].ySize * sizeof(uint32_t));

        if( prm[tpi].mode == 0 ) {
            pString2            = (uint8_t *) VLIB_malloc(mode0_inSize * sizeof(uint8_t));
        } else {
            pString2            = (uint8_t *) VLIB_malloc(mode1_inSize * sizeof(uint8_t));
        }

        /* Only run the test if the buffer allocations fit in the heap */
        if( pString1 && pString2 && pHammingDistance && pHammingDistance_cn ) {

            int32_t    fail, mode;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)0,
                            pString1, prm[tpi].staticIn1,
                            prm[tpi].xSize, prm[tpi].ySize, prm[tpi].xPitch * sizeof(pString1[0]),
                            sizeof(pString1[0]), testPatternString);

            if( prm[tpi].mode == 0 ) {
                VLIB_fillBuffer(prm[tpi].testPattern,
                                (uint8_t)1,
                                pString2, prm[tpi].staticIn2,
                                prm[tpi].xSize, prm[tpi].ySize, prm[tpi].xPitch * sizeof(pString2[0]),
                                sizeof(pString2[0]), testPatternString);
            } else {
                VLIB_fillBuffer(prm[tpi].testPattern,
                                (uint8_t)1,
                                pString2, prm[tpi].staticIn2,
                                prm[tpi].xSize, 1, prm[tpi].xPitch * sizeof(pString2[0]),
                                sizeof(pString2[0]), testPatternString);
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_hammingDistance(pString1, pString2, prm[tpi].xSize, prm[tpi].ySize, prm[tpi].mode, prm[tpi].xPitch, pHammingDistance);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_hammingDistance_cn(pString1, pString2, prm[tpi].xSize, prm[tpi].ySize, prm[tpi].mode, prm[tpi].xPitch, pHammingDistance_cn);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pHammingDistance, (void *)pHammingDistance_cn, prm[tpi].ySize * sizeof(pHammingDistance_cn[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pHammingDistance_cn, prm[tpi].ySize * sizeof(pHammingDistance_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            mode = (prm[tpi].mode) ? 2 : 1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | mode=%d, xSize=%d, ySize=%d",
                    testPatternString, prm[tpi].mode, prm[tpi].xSize, prm[tpi].ySize);
            VLIB_formula_add_test(mode0_inSize, prm[tpi].ySize, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "mode=%d, xSize=%d, ySize=%d",
                    prm[tpi].mode, prm[tpi].xSize, prm[tpi].ySize);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pHammingDistance_cn);
        VLIB_free(pHammingDistance);
        VLIB_free(pString2);
        VLIB_free(pString1);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 3, "mode=0, One-to-one", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = xSize * ySize; M = ySize",
                              "xSize * ySize");

    VLIB_profile_setMode(2, 3, "mode=1, Many-to-one", 1); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = xSize * ySize; M = ySize",
                              "xSize * ySize");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_hammingDistance");
    } else {
        VLIB_hammingDistance_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_hammingDistance_d.c                                  */
/* ======================================================================== */

