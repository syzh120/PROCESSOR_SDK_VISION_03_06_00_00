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
**|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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

#include "VLIB_houghLineFromList.h"
#include "VLIB_houghLineFromList_cn.h"
#include "VLIB_houghLineFromList_idat.h"


int32_t VLIB_InitializeTrigLUTs(int16_t *restrict pSin,
                                int16_t *restrict pCos,
                                VLIB_F32 ThetaMin,
                                VLIB_F32 ThetaMax,
                                VLIB_F32 NumThetaPoints)
{
    uint32_t    i;
    VLIB_F32    Theta;

    for( i = 0; i < NumThetaPoints; i++ ) {
        Theta = ThetaMin + i * (ThetaMax - ThetaMin) / (NumThetaPoints - 1);

        *(pSin + i) = (int16_t)(floor(256 * sin(Theta * 0.017453) + 0.5));
        *(pCos + i) = (int16_t)(floor(256 * cos(Theta * 0.017453) + 0.5));

        /* pTRIG[i] = (*(pCos + i)) | ((int32_t)(*(pSin + i)) << 16);; */

    }

    return (0);
}

/* VLIB_houghLineFromList_d:  Test Driver Routine */
void VLIB_houghLineFromList_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    houghLineFromList_testParams_t   *prm;

    houghLineFromList_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_houghLineFromList");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    out_size =   prm[tpi].thetaRange * prm[tpi].rhoMaxLength;

        /* Allocate buffers for each test vector */
        uint16_t   *pEdgeMapList       =  (uint16_t *) memalign(8, prm[tpi].listSize * 2 * sizeof(uint16_t));
        uint16_t   *pOutHoughSpace     =  (uint16_t *) malloc(out_size * sizeof(uint16_t));
        uint16_t   *pOutHoughSpace_cn  =  (uint16_t *) malloc(out_size * sizeof(uint16_t));

        uint16_t   *ping    = (uint16_t *) VLIB_memalign(8, (prm[tpi].rhoMaxLength + 4) * sizeof(uint16_t));
        uint16_t   *pong    = (uint16_t *) VLIB_memalign(8, (prm[tpi].rhoMaxLength + 4) * sizeof(uint16_t));
        uint16_t   *pang    = (uint16_t *) VLIB_memalign(8, (prm[tpi].rhoMaxLength + 4) * sizeof(uint16_t));
        uint16_t   *peng    = (uint16_t *) VLIB_memalign(8, (prm[tpi].rhoMaxLength + 4) * sizeof(uint16_t));

        int16_t   *SinLUT  =  (int16_t *) malloc(prm[tpi].thetaRange * sizeof(int16_t));
        int16_t   *CosLUT  =  (int16_t *) malloc(prm[tpi].thetaRange * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pEdgeMapList && pOutHoughSpace && pOutHoughSpace_cn && ping && pong && pang && peng && SinLUT && CosLUT ) {

            int32_t    fail = 0;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            pEdgeMapList, prm[tpi].staticIn,
                            prm[tpi].listSize * 2, 1, prm[tpi].listSize * 2,
                            sizeof(uint16_t), testPatternString);

            /* Clear output memory */
            VLIB_clear_memory(pOutHoughSpace, prm[tpi].thetaRange * prm[tpi].rhoMaxLength * sizeof(uint16_t));
            VLIB_clear_memory(pOutHoughSpace_cn, prm[tpi].thetaRange * prm[tpi].rhoMaxLength * sizeof(uint16_t));

            /* Initialize SIN & COS tables */
            VLIB_InitializeTrigLUTs(SinLUT, CosLUT, -80, 79.6, prm[tpi].thetaRange);

            if( vlib_KERNEL_FAIL == VLIB_compare_mem((void *) prm[tpi].ref_pSIN, (void *)SinLUT, prm[tpi].thetaRange * sizeof(uint16_t))) {
                printf("|  %d | FAIL - Error: Sin table initialization failed!\n", tpi);
                fail = 1;
            }
            if( vlib_KERNEL_FAIL == VLIB_compare_mem((void *) prm[tpi].ref_pCOS, (void *)CosLUT, prm[tpi].thetaRange * sizeof(uint16_t))) {
                printf("|  %d | FAIL - Error: Cos table initialization failed!\n", tpi);
                fail = 1;
            }

            if( fail == 0 ) {
                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_houghLineFromList(
                    pEdgeMapList,
                    pOutHoughSpace,
                    prm[tpi].outBlkWidth,
                    prm[tpi].outBlkHeight,
                    prm[tpi].listSize,
                    prm[tpi].thetaRange,
                    prm[tpi].rhoMaxLength,
                    SinLUT,
                    CosLUT,
                    ping,
                    pong,
                    pang,
                    peng);
                VLIB_profile_stop();

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_houghLineFromList_cn(
                    pEdgeMapList,
                    pOutHoughSpace_cn,
                    prm[tpi].outBlkWidth,
                    prm[tpi].outBlkHeight,
                    prm[tpi].listSize,
                    prm[tpi].thetaRange,
                    prm[tpi].rhoMaxLength,
                    SinLUT,
                    CosLUT,
                    ping,
                    pong,
                    pang,
                    peng);
                VLIB_profile_stop();


                /* Compare natural C Output and Optimized Output */
                status_nat_vs_int = VLIB_compare_mem((void *) pOutHoughSpace, (void *)pOutHoughSpace_cn, out_size * sizeof(uint16_t));

                /* If static output is available, then additionally compares natural C output with static reference output data */
                if( prm[tpi].staticOut != NULL ) {
                    status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOutHoughSpace_cn, out_size * sizeof(uint16_t));
                }

                /* Set the 'fail' flag based on test vector comparison results */
                fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

                est_test=1;

                /* Profile display and preparation for cycle estimation */
                sprintf(desc, "%s generated input | Opt results compared to NatC results | listSize=%d, thetaRange=%d, rhoMaxLength=%d",
                        testPatternString, prm[tpi].listSize, prm[tpi].thetaRange, prm[tpi].rhoMaxLength);
                VLIB_formula_add_test(prm[tpi].listSize * prm[tpi].thetaRange, NULL, NULL, fail, desc, NULL);
            }
        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "listSize=%d, thetaRange=%d, rhoMaxLength=%d",
                    prm[tpi].listSize, prm[tpi].thetaRange, prm[tpi].rhoMaxLength);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(CosLUT);
        free(SinLUT);
        VLIB_align_free(peng);
        VLIB_align_free(pang);
        VLIB_align_free(pong);
        VLIB_align_free(ping);
        free(pOutHoughSpace_cn);
        free(pOutHoughSpace);
        align_free(pEdgeMapList);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = listSize * thetaRange",
                              NULL);

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_houghLineFromList");
    } else {
        VLIB_houghLineFromList_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_houghLineFromList_d.c                                */
/* ======================================================================== */

