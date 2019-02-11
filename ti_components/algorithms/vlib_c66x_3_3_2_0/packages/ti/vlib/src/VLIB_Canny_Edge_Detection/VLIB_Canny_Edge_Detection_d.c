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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#include "VLIB_Canny_Edge_Detection.h"
#include "VLIB_Canny_Edge_Detection_cn.h"
#include "VLIB_Canny_Edge_Detection_idat.h"

/* VLIB_Canny_Edge_Detection_d:  Test Driver Routine */
void VLIB_Canny_Edge_Detection_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;                      /* test parameter index */

    /* Test Parameters */
    canny_testParams_t   *prm;

    canny_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_Canny_Edge_Detection");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    bufferSize  = prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        uint8_t   *pInput      = (uint8_t *) VLIB_malloc(bufferSize * sizeof(uint8_t));
        int16_t   *pBufGradX   = (int16_t *) VLIB_malloc(bufferSize * sizeof(int16_t));
        int16_t   *pBufGradY   = (int16_t *) VLIB_malloc(bufferSize * sizeof(int16_t));
        int16_t   *pBufMag     = (int16_t *) VLIB_malloc(bufferSize * sizeof(int16_t));
        uint8_t   *pScratch    = (uint8_t *) VLIB_malloc(bufferSize * sizeof(uint8_t));
        uint8_t   *pBufOut     = (uint8_t *) VLIB_malloc(bufferSize * sizeof(uint8_t));
        uint8_t   *pBufOut_cn  = (uint8_t *) malloc(bufferSize * sizeof(uint8_t));
        int32_t    numItems;
        int32_t    numItems_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( pInput && pBufGradX && pBufGradY && pBufMag && pScratch && pBufOut && pBufOut_cn ) {
            uint32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)127,
                            pInput, prm[tpi].input,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            /* initialize memory */
            memset(pBufGradX,  0, bufferSize * sizeof(int16_t));
            memset(pBufGradY,  0, bufferSize * sizeof(int16_t));
            memset(pBufMag,    0, bufferSize * sizeof(int16_t));
            memset(pBufOut,    0, bufferSize * sizeof(uint8_t));
            memset(pScratch,   0, bufferSize * sizeof(uint8_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_Canny_Edge_Detection(pInput,
                                      pBufGradX,
                                      pBufGradY,
                                      pBufMag,
                                      pBufOut,
                                      pScratch,
                                      &numItems,
                                      prm[tpi].width,
                                      prm[tpi].height);
            VLIB_profile_stop();

            /* initialize memory */
            memset(pBufGradX,  0, bufferSize * sizeof(int16_t));
            memset(pBufGradY,  0, bufferSize * sizeof(int16_t));
            memset(pBufMag,    0, bufferSize * sizeof(int16_t));
            memset(pBufOut_cn, 0, bufferSize * sizeof(uint8_t));
            memset(pScratch,   0, bufferSize * sizeof(uint8_t));

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_Canny_Edge_Detection_cn(pInput,
                                         pBufGradX,
                                         pBufGradY,
                                         pBufMag,
                                         pBufOut_cn,
                                         pScratch,
                                         &numItems_cn,
                                         prm[tpi].width,
                                         prm[tpi].height);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pBufOut, (void *)pBufOut_cn, bufferSize * sizeof(uint8_t));
            if( numItems != numItems_cn ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].refOutput != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].refOutput, (void *)pBufOut_cn, bufferSize * sizeof(uint8_t));
                if( prm[tpi].refNumItems != numItems_cn ) {
                    status_nat_vs_ref = vlib_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height);
            VLIB_formula_add_test(bufferSize, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d",
                    prm[tpi].width, prm[tpi].height);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pBufOut_cn);
        VLIB_free(pBufOut);
        VLIB_free(pScratch);
        VLIB_free(pBufMag);
        VLIB_free(pBufGradY);
        VLIB_free(pBufGradX);
        VLIB_free(pInput);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_Canny_Edge_Detection");
    } else {
        VLIB_Canny_Edge_Detection_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_Canny_Edge_Detection_d.c                             */
/* ======================================================================== */

