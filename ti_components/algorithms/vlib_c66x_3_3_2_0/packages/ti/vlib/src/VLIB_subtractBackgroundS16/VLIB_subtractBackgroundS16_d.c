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

#include "../VLIB_initMeanWithLumaS16/VLIB_initMeanWithLumaS16_cn.h"
#include "../VLIB_initVarWithConstS16/VLIB_initVarWithConstS16_cn.h"

#include "VLIB_subtractBackgroundS16.h"
#include "VLIB_subtractBackgroundS16_cn.h"
#include "VLIB_subtractBackgroundS16_idat.h"

/* VLIB_subtractBackgroundS16_d:  Test Driver Routine */
void VLIB_subtractBackgroundS16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    subtractBackgroundS16_testParams_t   *prm;

    subtractBackgroundS16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_subtractBackgroundS16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    packed_size =   (prm[tpi].PixelCount + 31) / 32;

        /* Allocate buffers for each test vector */
        uint8_t    *newLuma         =  (uint8_t *) VLIB_malloc(prm[tpi].PixelCount * sizeof(uint8_t));
        uint8_t    *prevLuma        =  (uint8_t *) malloc(prm[tpi].PixelCount * sizeof(uint8_t));
        int16_t    *runningMean     =  (int16_t *) VLIB_malloc(prm[tpi].PixelCount * sizeof(int16_t));
        int16_t    *runningVar      =  (int16_t *) VLIB_malloc(prm[tpi].PixelCount * sizeof(int16_t));
        uint32_t   *mask32packed    =  (uint32_t *) VLIB_malloc(packed_size * 4);
        uint32_t   *mask32packed_cn =  (uint32_t *) malloc(packed_size * 4);

        /* Only run the test if the buffer allocations fit in the heap */
        if( newLuma && prevLuma && runningMean && runningVar && mask32packed && mask32packed_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            if( prm[tpi].staticInPrevLuma ) {
                memcpy(prevLuma, prm[tpi].staticInPrevLuma, prm[tpi].PixelCount);
            } else {
                VLIB_fillBuffer(RANDOM,
                                (uint8_t)1,
                                prevLuma, prm[tpi].staticInPrevLuma,
                                prm[tpi].PixelCount, 1, prm[tpi].PixelCount * sizeof(prevLuma[0]),
                                sizeof(prevLuma[0]), testPatternString);
            }

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            newLuma, prm[tpi].staticInLuma,
                            prm[tpi].PixelCount, 1, prm[tpi].PixelCount * sizeof(newLuma[0]),
                            sizeof(newLuma[0]), testPatternString);

            /* initialize the running mean "image" */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_initMeanWithLumaS16_cn(runningMean, prevLuma, prm[tpi].PixelCount);

            /* initialize the running variance "image" */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_initVarWithConstS16_cn(runningVar, prm[tpi].thresholdGlobal, prm[tpi].PixelCount);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_subtractBackgroundS16(mask32packed, newLuma, runningMean, runningVar, prm[tpi].thresholdGlobal, prm[tpi].thresholdFactor, prm[tpi].PixelCount);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_subtractBackgroundS16_cn(mask32packed_cn, newLuma, runningMean, runningVar, prm[tpi].thresholdGlobal, prm[tpi].thresholdFactor, prm[tpi].PixelCount);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) mask32packed, (void *)mask32packed_cn, packed_size * sizeof(mask32packed_cn[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutMask != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOutMask, (void *)mask32packed_cn, packed_size * sizeof(mask32packed_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | PixelCount=%d",
                    testPatternString, prm[tpi].PixelCount);
            VLIB_formula_add_test(prm[tpi].PixelCount, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "PixelCount=%d",
                    prm[tpi].PixelCount);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(mask32packed_cn);
        VLIB_free(mask32packed);
        VLIB_free(runningVar);
        VLIB_free(runningMean);
        free(prevLuma);
        VLIB_free(newLuma);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = PixelCount",
                              "PixelCount");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_subtractBackgroundS16");
    } else {
        VLIB_subtractBackgroundS16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_subtractBackgroundS16_d.c                            */
/* ======================================================================== */

