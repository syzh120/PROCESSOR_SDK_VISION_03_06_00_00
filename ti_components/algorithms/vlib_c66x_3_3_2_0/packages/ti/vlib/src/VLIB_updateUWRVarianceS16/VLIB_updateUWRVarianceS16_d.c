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
#include "../VLIB_updateUWRMeanS16/VLIB_updateUWRMeanS16_cn.h"

#include "VLIB_updateUWRVarianceS16.h"
#include "VLIB_updateUWRVarianceS16_cn.h"
#include "VLIB_updateUWRVarianceS16_idat.h"

/* VLIB_updateUWRVarianceS16_d:  Test Driver Routine */
void VLIB_updateUWRVarianceS16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    updateUWRVarianceS16_testParams_t   *prm;

    updateUWRVarianceS16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_updateUWRVarianceS16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    packed_size =   (prm[tpi].pixelCount + 31) / 32;

        /* Allocate buffers for each test vector */
        uint8_t    *prevLuma            =  (uint8_t *) malloc(prm[tpi].pixelCount * sizeof(uint8_t));
        int16_t    *previousVar         =  (int16_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(int16_t));
        uint8_t    *oldestData          =  (uint8_t *) malloc(prm[tpi].pixelCount * sizeof(uint8_t));
        uint8_t    *newestData          =  (uint8_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(uint8_t));
        uint32_t   *newestMask32packed  =  (uint32_t *) VLIB_malloc(packed_size * 4);
        uint32_t   *oldestMask32packed  =  (uint32_t *) VLIB_malloc(packed_size * 4);
        int16_t    *previousMean        =  (int16_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(int16_t));
        int16_t    *updatedMean         =  (int16_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(int16_t));
        int16_t    *updatedVar          =  (int16_t *) VLIB_malloc(prm[tpi].pixelCount * sizeof(int16_t));
        int16_t    *updatedVar_cn       =  (int16_t *) malloc(prm[tpi].pixelCount * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( prevLuma && previousVar && oldestData && newestData && newestMask32packed && oldestMask32packed &&
            previousMean && updatedMean && updatedVar && updatedVar_cn ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            if( prm[tpi].newestMask ) {
                memcpy(newestMask32packed, prm[tpi].newestMask, packed_size * 4);
            } else {
                VLIB_fillBuffer(RANDOM,
                                (uint32_t)1,
                                newestMask32packed, prm[tpi].newestMask,
                                packed_size, 1, packed_size * sizeof(newestMask32packed[0]),
                                sizeof(newestMask32packed[0]), testPatternString);
            }

            if( prm[tpi].oldestMask ) {
                memcpy(oldestMask32packed, prm[tpi].oldestMask, packed_size * 4);
            } else {
                VLIB_fillBuffer(RANDOM,
                                (uint32_t)1,
                                oldestMask32packed, prm[tpi].oldestMask,
                                packed_size, 1, packed_size * sizeof(oldestMask32packed[0]),
                                sizeof(oldestMask32packed[0]), testPatternString);
            }

            if( prm[tpi].newestData ) {
                memcpy(newestData, prm[tpi].newestData, prm[tpi].pixelCount * sizeof(newestData[0]));
            } else {
                VLIB_fillBuffer(RANDOM,
                                (uint8_t)1,
                                newestData, prm[tpi].newestData,
                                prm[tpi].pixelCount, 1, prm[tpi].pixelCount * sizeof(newestData[0]),
                                sizeof(newestData[0]), testPatternString);
            }

            if( prm[tpi].oldestData ) {
                memcpy(oldestData, prm[tpi].oldestData, prm[tpi].pixelCount * sizeof(oldestData[0]));
            } else {
                VLIB_fillBuffer(RANDOM,
                                (uint16_t)1,
                                oldestData, prm[tpi].oldestData,
                                prm[tpi].pixelCount, 1, prm[tpi].pixelCount * sizeof(oldestData[0]),
                                sizeof(oldestData[0]), testPatternString);
            }

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            prevLuma, prm[tpi].staticInPrevLuma,
                            prm[tpi].pixelCount, 1, prm[tpi].pixelCount * sizeof(prevLuma[0]),
                            sizeof(prevLuma[0]), testPatternString);

            /* initialize the previous mean "image" */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_initMeanWithLumaS16_cn(previousMean, prevLuma, prm[tpi].pixelCount);

            /* initialize the previous variance "image" */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_initVarWithConstS16_cn(previousVar, prm[tpi].constant, prm[tpi].pixelCount);

            /* initialize the updatedMean "image" */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_updateUWRMeanS16_cn(updatedMean, previousMean, newestData, oldestData, newestMask32packed, oldestMask32packed,
                                     prm[tpi].pixelCount, prm[tpi].frameCount);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_updateUWRVarianceS16(updatedVar, previousVar, updatedMean, previousMean, newestData, newestMask32packed, oldestMask32packed,
                                      prm[tpi].pixelCount, prm[tpi].frameCount);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_updateUWRVarianceS16_cn(updatedVar_cn, previousVar, updatedMean, previousMean, newestData, newestMask32packed, oldestMask32packed,
                                         prm[tpi].pixelCount, prm[tpi].frameCount);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) updatedVar, (void *)updatedVar_cn, prm[tpi].pixelCount * sizeof(updatedVar_cn[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutVar != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOutVar, (void *)updatedVar_cn, prm[tpi].pixelCount * sizeof(updatedVar_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | pixelCount=%d",
                    testPatternString, prm[tpi].pixelCount);
            VLIB_formula_add_test(prm[tpi].pixelCount, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "pixelCount=%d",
                    prm[tpi].pixelCount);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(updatedVar_cn);
        VLIB_free(updatedVar);
        VLIB_free(updatedMean);
        VLIB_free(previousMean);
        VLIB_free(oldestMask32packed);
        VLIB_free(newestMask32packed);
        VLIB_free(newestData);
        free(oldestData);
        VLIB_free(previousVar);
        free(prevLuma);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = pixelCount",
                              "pixelCount");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_updateUWRVarianceS16");
    } else {
        VLIB_updateUWRVarianceS16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_updateUWRVarianceS16_d.c                             */
/* ======================================================================== */

