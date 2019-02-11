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

#include "VLIB_lbp.h"
#include "VLIB_lbp_cn.h"
#include "VLIB_lbp_idat.h"

/* VLIB_lbp_d:  Test Driver Routine */
void VLIB_lbp_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    lbp_testParams_t   *prm;

    lbp_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_lbp");

    /* Run each test case */
    for( tpi = 0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size          =   prm[tpi].imageWidth  * prm[tpi].imageHeight;
        uint32_t    scratch_size      =   prm[tpi].imageWidth  * prm[tpi].imageHeight * 6;
        uint32_t    pMapTbl_size      =   1 << prm[tpi].numNeighbours;

        /* Allocate buffers for each test vector */
        uint8_t    *pInput            =  (uint8_t *) VLIB_malloc(inp_size * sizeof(uint8_t));
        uint8_t    *pMapTbl           =  (uint8_t *) VLIB_malloc(pMapTbl_size * sizeof(uint8_t));
        uint8_t    *pScratch          =  (uint8_t *) VLIB_malloc(scratch_size * sizeof(uint8_t));
        uint32_t   *pOutHistogram;
        uint32_t   *pOutHistogram_cn;

        VLIB_assert(prm[tpi].numNeighbours == 8, "This release requires numNeighbors = 8");
        VLIB_assert(prm[tpi].radius == 1, "This release requires radius = 1");

        /* Only run the test if the buffer allocations fit in the heap */
        if( pInput && pMapTbl && pScratch ) {

            int32_t    fail, maxTbl = 0, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            pMapTbl, prm[tpi].lbpMapTbl,
                            pMapTbl_size, 1, pMapTbl_size * sizeof(pMapTbl[0]),
                            sizeof(pMapTbl[0]), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            pInput, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imageWidth * sizeof(pInput[0]),
                            sizeof(pInput[0]), testPatternString);

            /* Max value in pMapTbl determines the histogram output size */
            for( i=0; i < pMapTbl_size; i++ ) {
                if( maxTbl < pMapTbl[i] ) {
                    maxTbl = pMapTbl[i];
                }
            }

            pOutHistogram     =  (uint32_t *) VLIB_malloc((maxTbl + 1) * sizeof(uint32_t));
            pOutHistogram_cn  =  (uint32_t *) malloc((maxTbl + 1) * sizeof(uint32_t));

            /* Only run the test if the buffer allocations fit in the heap */
            if( pOutHistogram && pOutHistogram_cn ) {

                memset(pOutHistogram, 0, (maxTbl + 1) * sizeof(pOutHistogram[0]));
                memset(pOutHistogram_cn, 0, (maxTbl + 1) * sizeof(pOutHistogram_cn[0]));

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_lbp(pInput, pMapTbl, pScratch, pOutHistogram,
                         prm[tpi].imageWidth, prm[tpi].imageHeight,
                         prm[tpi].numNeighbours, prm[tpi].radius);
                VLIB_profile_stop();


                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_lbp_cn(pInput, pMapTbl, pOutHistogram_cn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight,
                            prm[tpi].numNeighbours, prm[tpi].radius);
                VLIB_profile_stop();


                /* Compare natural C Output and Optimized Output */
                status_nat_vs_int = VLIB_compare_mem((void *) pOutHistogram, (void *)pOutHistogram_cn, (maxTbl + 1) * sizeof(pOutHistogram_cn[0]));

                /* If static output is available, then additionally compares natural C output with static reference output data */
                if( prm[tpi].staticOut != NULL ) {
                    status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOutHistogram_cn, (maxTbl + 1) * sizeof(pOutHistogram_cn[0]));
                }

                /* Set the 'fail' flag based on test vector comparison results */
                fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;
                est_test=1;

                /* Profile display and preparation for cycle estimation */
                sprintf(desc, "%s generated input | Opt results compared to NatC results | imageWidth=%d, imageHeight=%d, out_size=%d",
                        testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, maxTbl + 1);
                VLIB_formula_add_test(inp_size, prm[tpi].imageHeight, NULL, fail, desc, NULL);
            } else {
                /* Display the error printout for this test vector before moving on to the next test vector */
                sprintf(desc, "imageWidth=%d, imageHeight=%d,  out size=%d",
                        prm[tpi].imageWidth, prm[tpi].imageHeight, maxTbl + 1);
                VLIB_skip_test(desc);
            }
        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "imageWidth=%d, imageHeight=%d",
                    prm[tpi].imageWidth, prm[tpi].imageHeight);
            VLIB_skip_test(desc);
        }
        free(pOutHistogram_cn);
        VLIB_free(pOutHistogram);
        VLIB_free(pScratch);
        VLIB_free(pMapTbl);
        VLIB_free(pInput);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = imageWidth * imageHeight; M = imageHeight",
                              "imageWidth * imageHeight");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_lbp");
    } else {
        VLIB_lbp_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_lbp_d.c                                              */
/* ======================================================================== */

