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

#include "VLIB_weightedHistogram_nD_U16.h"
#include "VLIB_weightedHistogram_nD_U16_cn.h"
#include "VLIB_weightedHistogram_nD_U16_idat.h"

/* VLIB_weightedHistogram_nD_U16_d:  Test Driver Routine */
void VLIB_weightedHistogram_nD_U16_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    weightedHistogram_nD_U16_testParams_t   *prm;

    weightedHistogram_nD_U16_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(4, "VLIB_weightedHistogram_nD_U16");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Calculate buffer sizes */
        int32_t    inSize = prm[tpi].numX * prm[tpi].dimX;

        /* Allocate buffers for each test vector */
        uint16_t   *X              =  (uint16_t *) VLIB_malloc(inSize * sizeof(uint16_t));
        uint16_t   *binWeight      =  (uint16_t *) VLIB_malloc(prm[tpi].numX * sizeof(uint16_t));
        uint16_t   *numBins        =  (uint16_t *) VLIB_malloc(prm[tpi].dimX * sizeof(uint16_t));
        uint16_t   *normVals       =  (uint16_t *) VLIB_malloc(prm[tpi].dimX * sizeof(uint16_t));
        uint16_t   *scrap          =  (uint16_t *) VLIB_malloc(prm[tpi].numX * sizeof(uint16_t));
        uint16_t   *H;
        uint16_t   *H_cn;
        uint16_t   *H1;

        /* Only run the test if the buffer allocations fit in the heap */
        if( X && binWeight && numBins && normVals && scrap ) {

            int32_t    fail, i, outSize;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(STATIC,
                            (uint16_t)1,
                            numBins, prm[tpi].numBins,
                            prm[tpi].dimX, 1, prm[tpi].dimX * sizeof(numBins[0]),
                            sizeof(numBins[0]), testPatternString);

            if( prm[tpi].normVals ) {
                VLIB_fillBuffer(STATIC,
                                (uint16_t)1,
                                normVals, prm[tpi].normVals,
                                prm[tpi].dimX, 1, prm[tpi].dimX * sizeof(normVals[0]),
                                sizeof(normVals[0]), testPatternString);
            } else {
                for( i=0; i < prm[tpi].dimX; i++ ) {
                    /* normVals is equal to 65536/(max value in dimension + a delta, where delta is > 0) */
                    normVals[i] = 65536 / prm[tpi].maxSize;
                }
            }

            VLIB_fillBuffer(prm[tpi].weightPattern,
                            (uint16_t)1,
                            binWeight, prm[tpi].staticInWeight,
                            prm[tpi].numX, 1, prm[tpi].numX * sizeof(binWeight[0]),
                            sizeof(binWeight[0]), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint16_t)1,
                            X, prm[tpi].staticIn,
                            inSize, 1, inSize * sizeof(X[0]),
                            sizeof(X[0]), testPatternString);

            /* Ensure that all values in array are within maxSize-1 value (if randomly generated) */
            for( i=0; i < prm[tpi].numX * prm[tpi].dimX; i++ ) {
                if( X[i] > prm[tpi].maxSize - 1 ) {
                    X[i] = prm[tpi].maxSize - 1;
                }
            }

            outSize = 1;

            for( i=0; i < prm[tpi].dimX; i++ ) {
                outSize *= numBins[i];
            }

            H    =  (uint16_t *) VLIB_malloc(outSize * sizeof(uint16_t));
            H_cn =  (uint16_t *) malloc(outSize * sizeof(uint16_t));
            H1   =  (uint16_t *) VLIB_malloc(outSize * sizeof(uint16_t));

            if( H && H_cn && H1 ) {

                /* Clear the H arrays, as per fn requirement */
                memset(H, 0, outSize * sizeof(uint16_t));
                memset(H1, 0, outSize * sizeof(uint16_t));
                memset(scrap, 0, prm[tpi].numX * sizeof(uint16_t));

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_weightedHistogram_nD_U16(X, prm[tpi].numX, prm[tpi].dimX, binWeight, numBins, normVals, scrap, H1, H);
                VLIB_profile_stop();

                /* Clear the H arrays, as per fn requirement */
                memset(H_cn, 0, outSize * sizeof(uint16_t));
                memset(H1, 0, outSize * sizeof(uint16_t));
                memset(scrap, 0, prm[tpi].numX * sizeof(uint16_t));

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_weightedHistogram_nD_U16_cn(X, prm[tpi].numX, prm[tpi].dimX, binWeight, numBins, normVals, scrap, H1, H_cn);
                VLIB_profile_stop();


                /* Compare natural C Output and Optimized Output */
                status_nat_vs_int = VLIB_compare_mem((void *) H, (void *)H_cn, outSize * sizeof(uint16_t));

                /* If static output is available, then additionally compares natural C output with static reference output data */
                if( prm[tpi].staticOut != NULL ) {
                    status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)H_cn, outSize * sizeof(uint16_t));
                }

                /* Set the 'fail' flag based on test vector comparison results */
                fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

                est_test=1;

                /* Profile display and preparation for cycle estimation */
                sprintf(desc, "%s generated input | Opt results compared to NatC results | numX=%d, dimX=%d, maxSize=%d, outsize=%d",
                        testPatternString, prm[tpi].numX, prm[tpi].dimX, prm[tpi].maxSize, outSize);
                VLIB_formula_add_test(inSize, prm[tpi].numX, outSize, fail, desc, NULL);
            } else {
                /* Display the error printout for this test vector before moving on to the next test vector */
                sprintf(desc, "numX=%d, dimX=%d, maxSize=%d, outsize=%d",
                        prm[tpi].numX, prm[tpi].dimX, prm[tpi].maxSize, outSize);
                VLIB_skip_test(desc);
            }
        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numX=%d, dimX=%d, maxSize=%d",
                    prm[tpi].numX, prm[tpi].dimX, prm[tpi].maxSize);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(H1);
        free(H_cn);
        VLIB_free(H);
        VLIB_free(scrap);
        VLIB_free(normVals);
        VLIB_free(numBins);
        VLIB_free(binWeight);
        VLIB_free(X);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = numX*dimX; M = numX; L = outsize (product of num of bins in each dim)",
                              "numX*dimX");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_weightedHistogram_nD_U16");
    } else {
        VLIB_weightedHistogram_nD_U16_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_weightedHistogram_nD_U16_d.c                         */
/* ======================================================================== */

