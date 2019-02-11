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

#include "../VLIB_disparity_SAD_firstRow8/VLIB_disparity_SAD_firstRow8_cn.h"

#include "VLIB_disparity_SAD8.h"
#include "VLIB_disparity_SAD8_cn.h"
#include "VLIB_disparity_SAD8_idat.h"

/* VLIB_disparity_SAD8_d:  Test Driver Routine */
void VLIB_disparity_SAD8_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    disparity_SAD8_testParams_t   *prm;

    disparity_SAD8_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_disparity_SAD8");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inSize       =   prm[tpi].width * prm[tpi].height;
        uint32_t    wsDiv2       =   prm[tpi].windowSize / 2;
        uint32_t    numDisp      =   prm[tpi].maxDisp - prm[tpi].minDisp + 1;
        uint32_t    maxDispIdx   =   (prm[tpi].maxDisp > 0) ? prm[tpi].maxDisp : 0;
        int32_t     maxWidth     =   prm[tpi].width - (numDisp - 1) - (prm[tpi].windowSize - 1);
        uint32_t    outHeight    =   prm[tpi].height - (prm[tpi].windowSize - 1);
        uint32_t    arrayPad     =   (8 - ((maxWidth - 1) & 7)) & 7;
        uint32_t    padWidth     =   maxWidth + arrayPad;
        uint32_t    costBuffSize =   padWidth * numDisp;
        uint32_t    scratchSize  =   (maxWidth + prm[tpi].windowSize + 7) & ~0x7;
        uint32_t    outSize      =   padWidth * outHeight;

        /* Allocate buffers for each test vector */
        uint8_t    *pLeft            = (uint8_t *)  VLIB_malloc(inSize * sizeof(uint8_t));
        uint8_t    *pRight           = (uint8_t *)  VLIB_malloc(inSize * sizeof(uint8_t));
        uint16_t   *pCost            = (uint16_t *) VLIB_malloc(costBuffSize * sizeof(uint16_t));
        uint16_t   *pMinCost         = (uint16_t *) VLIB_malloc(padWidth * sizeof(uint16_t));
        uint16_t   *pScratch         = (uint16_t *) VLIB_malloc(scratchSize * sizeof(uint16_t));
        int8_t     *pDisparity       = (int8_t *)   VLIB_malloc(outSize * sizeof(int8_t));
        int8_t     *pDisparity_cn    = (int8_t *)   malloc(outSize * sizeof(int8_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( pLeft && pRight && pCost && pMinCost && pScratch && pDisparity && pDisparity_cn && maxWidth > 0 ) {

            int32_t     fail, d, y, i, j;
            uint32_t    idxIn, idxOut;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)0,
                            pLeft, prm[tpi].staticInLeft,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(pLeft[0]),
                            sizeof(pLeft[0]), testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)0,
                            pRight, prm[tpi].staticInRight,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(pRight[0]),
                            sizeof(pRight[0]), testPatternString);

            /* Test optimized kernel */

            /* Initialize i/o buffers as per API header */
            memset(pDisparity, 0, outSize * sizeof(int8_t));

            for( i=0; i < padWidth; i++ ) {
                pMinCost[i] = 0x7FFF;
            }

            idxIn = wsDiv2 * prm[tpi].width + wsDiv2 + maxDispIdx; /* Initialize offset into the input images */

            /* First Line */
            for( d=prm[tpi].minDisp; d <= prm[tpi].maxDisp; d++ ) {
                /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
                VLIB_disparity_SAD_firstRow8_cn((uint8_t *)&pLeft[idxIn], (uint8_t *)&pRight[idxIn - d],
                                                (uint16_t *)&pCost[(d - prm[tpi].minDisp) * padWidth],
                                                pMinCost, pScratch, pDisparity,
                                                d,
                                                maxWidth,
                                                prm[tpi].width,
                                                prm[tpi].windowSize);
            }

            /* Remaining Lines */
            for( y=1; y < outHeight; y++ ) {
                idxIn  = (y + wsDiv2) * prm[tpi].width + wsDiv2 + maxDispIdx; /* Initialize offset into the input images */
                idxOut = y * padWidth;                                  /* Initialize offset into the output disparity */

                /* Reset the mincost buffer for each line */
                for( i=0; i < padWidth; i++ ) {
                    pMinCost[i] = 0x7FFF;
                }

                for( d=prm[tpi].minDisp; d <= prm[tpi].maxDisp; d++ ) {
                    VLIB_profile_start(vlib_KERNEL_OPT);
                    VLIB_disparity_SAD8((uint8_t *)&pLeft[idxIn], (uint8_t *)&pRight[idxIn - d],
                                        (uint16_t *)&pCost[(d - prm[tpi].minDisp) * padWidth],
                                        pMinCost, (int8_t *)&pDisparity[idxOut],
                                        d,
                                        maxWidth,
                                        prm[tpi].width,
                                        prm[tpi].windowSize);
                    VLIB_profile_stop();
                }
            }

            /* Test _cn kernel */

            /* Initialize i/o buffers as per API header */
            memset(pDisparity_cn, 0, outSize * sizeof(int8_t));

            for( i=0; i < padWidth; i++ ) {
                pMinCost[i] = 0x7FFF;
            }

            idxIn = wsDiv2 * prm[tpi].width + wsDiv2 + maxDispIdx; /* Initialize offset into the input images */

            /* First Line */
            for( d=prm[tpi].minDisp; d <= prm[tpi].maxDisp; d++ ) {
                /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
                VLIB_disparity_SAD_firstRow8_cn((uint8_t *)&pLeft[idxIn], (uint8_t *)&pRight[idxIn - d],
                                                (uint16_t *)&pCost[(d - prm[tpi].minDisp) * padWidth],
                                                pMinCost, pScratch, pDisparity_cn,
                                                d,
                                                maxWidth,
                                                prm[tpi].width,
                                                prm[tpi].windowSize);
            }

            /* Remaining Lines */
            for( y=1; y < outHeight; y++ ) {
                idxIn  = (y + wsDiv2) * prm[tpi].width + wsDiv2 + maxDispIdx; /* Initialize offset into the input images */
                idxOut = y * padWidth;                                  /* Initialize offset into the output disparity */

                /* Reset the mincost buffer for each line */
                for( i=0; i < padWidth; i++ ) {
                    pMinCost[i] = 0x7FFF;
                }

                for( d=prm[tpi].minDisp; d <= prm[tpi].maxDisp; d++ ) {
                    VLIB_profile_start(vlib_KERNEL_CN);
                    VLIB_disparity_SAD8_cn((uint8_t *)&pLeft[idxIn], (uint8_t *)&pRight[idxIn - d],
                                           (uint16_t *)&pCost[(d - prm[tpi].minDisp) * padWidth],
                                           pMinCost, (int8_t *)&pDisparity_cn[idxOut],
                                           d,
                                           maxWidth,
                                           prm[tpi].width,
                                           prm[tpi].windowSize);
                    VLIB_profile_stop();
                }
            }

            /* Compare natural C Output and Optimized Output */
            for( j=0; j < outHeight; j++ ) {
                for( i=0; i < maxWidth; i++ ) {
                    if( pDisparity[j * padWidth + i] != pDisparity_cn[j * padWidth + i] ) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                    }
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                for( j=0; j < outHeight; j++ ) {
                    for( i=0; i < maxWidth; i++ ) {
                        if( prm[tpi].staticOut[j * maxWidth + i] != pDisparity_cn[j * padWidth + i] ) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }
                }
            }


            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, windowSize=%d, numDisp=%d",
                    testPatternString, maxWidth, outHeight, prm[tpi].windowSize, numDisp);
            VLIB_formula_add_test(padWidth * numDisp * (outHeight - 1), numDisp * (outHeight - 1), NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, windowSize=%d",
                    maxWidth, outHeight, prm[tpi].windowSize);
            VLIB_skip_test(desc);
        }


        /* Free buffers for each test vector */
        free(pDisparity_cn);
        VLIB_free(pDisparity);
        VLIB_free(pScratch);
        VLIB_free(pMinCost);
        VLIB_free(pCost);
        VLIB_free(pRight);
        VLIB_free(pLeft);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = padWidth*(outHeight-1)*(disparitySearchRange); M = (outHeight-1)*(disparitySearchRange)",
                              "padWidth*(outHeight-1)*(disparitySearchRange)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_disparity_SAD8");
    } else {
        VLIB_disparity_SAD8_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_disparity_SAD8_d.c                                   */
/* ======================================================================== */

