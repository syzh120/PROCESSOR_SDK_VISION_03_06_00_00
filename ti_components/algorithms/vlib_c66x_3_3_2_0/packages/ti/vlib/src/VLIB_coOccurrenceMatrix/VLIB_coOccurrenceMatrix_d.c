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

#include "VLIB_coOccurrenceMatrix.h"
#include "VLIB_coOccurrenceMatrix_cn.h"
#include "VLIB_coOccurrenceMatrix_idat.h"


/* Returns if value is a positive power of 2 */
static int32_t ppwr2(int32_t n)
{
    return ((n > 0) && !(n & (n - 1)));
}

/* VLIB_coOccurrence_d:  Test Driver Routine */
void VLIB_coOccurrenceMatrix_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;                      /* test parameter index */

    /* Test Parameters */
    coOccurrence_testParams_t   *prm;

    coOccurrence_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(4, "VLIB_coOccurrenceMatrix");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        uint16_t    outWidth     = prm[tpi].numLevels;
        uint16_t    outHeight    = prm[tpi].numLevels;
        uint32_t    retVal;
        uint32_t    i, j, k, fail, mode;
        uint16_t   *outMatrix[MAX_OUT_MATRIX];
        uint16_t   *outMatrix_cn[MAX_OUT_MATRIX];
        uint8_t    *scratch;

        /* Initialize status flags */
        int32_t    status_nat_vs_int  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Allocate buffers for each test vector */
        uint8_t   *input        = (uint8_t *) VLIB_malloc(prm[tpi].imagePitch * prm[tpi].imageHeight);

        for( k=0; k < prm[tpi].numOffsets; k++ ) {
            outMatrix[k]    = (uint16_t *) VLIB_malloc(outWidth * outHeight * sizeof(uint16_t));
            outMatrix_cn[k] = (uint16_t *) malloc(outWidth * outHeight * sizeof(uint16_t));
        }

        if( prm[tpi].scratchFlow ) {
            /* Allocating scratch buffer from DDR, as sometimes it might not fit in L2.
               to avoid a condition check,scratch is always allocated from DDR.
               */
            scratch = (uint8_t *) malloc(outWidth * outHeight * 4 * sizeof(uint16_t));
        } else {
            scratch = NULL;
        }

        /* Only run the test if the buffer allocations fit in the heap */
        if( input && outMatrix[prm[tpi].numOffsets - 1] && outMatrix_cn[prm[tpi].numOffsets - 1] ) {

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            input, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            retVal =  VLIB_coOccurrenceMatrix(input,
                                              outMatrix,
                                              prm[tpi].imageWidth,
                                              prm[tpi].imageHeight,
                                              prm[tpi].imagePitch,
                                              prm[tpi].loPixelVal,
                                              prm[tpi].hiPixelVal,
                                              prm[tpi].numLevels,
                                              prm[tpi].numOffsets,
                                              prm[tpi].rowOffsets,
                                              prm[tpi].colOffsets,
                                              scratch);
            VLIB_profile_stop();

            if( retVal == 0x0 ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            retVal =  VLIB_coOccurrenceMatrix_cn(input,
                                                 outMatrix_cn,
                                                 prm[tpi].imageWidth,
                                                 prm[tpi].imageHeight,
                                                 prm[tpi].imagePitch,
                                                 prm[tpi].loPixelVal,
                                                 prm[tpi].hiPixelVal,
                                                 prm[tpi].numLevels,
                                                 prm[tpi].numOffsets,
                                                 prm[tpi].rowOffsets,
                                                 prm[tpi].colOffsets,
                                                 scratch);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( k=0; k < (prm[tpi].numOffsets); k++ ) {
                for( i=0; i < (outHeight); i++ ) {
                    for( j=0; j < (outWidth); j++ ) {
                        if((outMatrix_cn[k][i * outWidth + j] != outMatrix[k][i * outWidth + j])) {
                            status_nat_vs_int = vlib_KERNEL_FAIL;
                            printf("Matrix:%d, row:%d, col:%d, out:%u, EOut:%u \n", k, i, j,\
                                   outMatrix[k][i * outWidth + j], outMatrix_cn[k][i * outWidth + j]);
                            break;
                        }
                    }
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                for( k=0; k < prm[tpi].numOffsets; k++ ) {
                    for( i=0; i < (outHeight); i++ ) {
                        for( j=0; j < (outWidth); j++ ) {
                            if((prm[tpi].staticOut[k * outWidth * outHeight + i * outWidth + j] != outMatrix_cn[k][i * outWidth + j])) {
                                status_nat_vs_ref = vlib_KERNEL_FAIL;
                                printf("Matrix:%d, row:%d, col:%d, Eout:%u, Out:%u \n", k, i, j,\
                                       prm[tpi].staticOut[k * outWidth * outHeight + i * outWidth + j], outMatrix_cn[k][i * outWidth + j]);
                                break;
                            }
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            if( prm[tpi].scratchFlow ) {
                if( ppwr2((prm[tpi].hiPixelVal - prm[tpi].loPixelVal + 1) / prm[tpi].numLevels) && (prm[tpi].numLevels <= 64)) {
                    mode = 1;
                } else {
                    mode = 2;
                }
            } else {
                mode = 3;
            }

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | imageWidth= %d, imageHeight= %d, outWidth= %d, outHeight= %d mode =%d",
                    testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, outWidth, outHeight, mode);
            VLIB_formula_add_test(prm[tpi].imageWidth * prm[tpi].imageHeight * prm[tpi].numOffsets,
                                  prm[tpi].imageHeight * prm[tpi].numOffsets,
                                  prm[tpi].numOffsets, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "imageWidth= %d, imageHeight= %d, outWidth= %d, outHeight= %d ",
                    prm[tpi].imageWidth, prm[tpi].imageHeight, outWidth, outHeight);
            VLIB_skip_test(desc);
        }

        VLIB_free(input);

        for( k=0; k < prm[tpi].numOffsets; k++ ) {
            VLIB_free(outMatrix[k]);
            free(outMatrix_cn[k]);
        }

        if( scratch != NULL ) {
            free(scratch);
        }
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 4, "Scratch used; internal LUT not required", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "imageWidth*imageHeight*numOffsets");

    VLIB_profile_setMode(2, 4, "Scratch used; internal LUT required", 0);     /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "imageWidth*imageHeight*numOffsets");

    VLIB_profile_setMode(3, 4, "Scratch not used; internal LUT required", 1); /* Mode 3 */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "imageWidth*imageHeight*numOffsets");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_coOccurrenceMatrix");
    } else {
        VLIB_coOccurrenceMatrix_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_coOccurrence_d.c                                 */
/* ======================================================================== */

