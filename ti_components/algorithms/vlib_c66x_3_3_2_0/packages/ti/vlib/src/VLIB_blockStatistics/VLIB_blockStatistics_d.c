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

#include "VLIB_blockStatistics.h"
#include "VLIB_blockStatistics_cn.h"
#include "VLIB_blockStatistics_idat.h"

/* VLIB_blockStatistics_d:  Test Driver Routine */
void VLIB_blockStatistics_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;                      /* test parameter index */

    /* Test Parameters */
    blockStatistics_testParams_t   *prm;

    blockStatistics_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_blockStatistics");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint16_t    outWidth           = prm[tpi].imageWidth  / prm[tpi].statBlockWidth;
        uint16_t    outHeight          = prm[tpi].imageHeight / prm[tpi].statBlockHeight;
        uint8_t     mode               = prm[tpi].mode;
        int32_t     scratchBufSize;
        uint32_t    retVal;

        uint8_t   *scratch;

        /* Allocate buffers for each test vector */
        uint8_t   *input             = (uint8_t *) VLIB_memalign(8, prm[tpi].imagePitch * prm[tpi].imageHeight);

        uint8_t    *min_opt           = (uint8_t *)  VLIB_memalign(8, (outWidth * outHeight  + 7) * sizeof(uint8_t));
        uint8_t    *max_opt           = (uint8_t *)  VLIB_memalign(8, (outWidth * outHeight  + 7) * sizeof(uint8_t));
        uint16_t   *mean_opt          = (uint16_t *) VLIB_memalign(8, (outWidth * outHeight  + 7) * sizeof(uint16_t));
        uint32_t   *var_opt           = (uint32_t *) VLIB_memalign(8, (outWidth * outHeight  + 7) * sizeof(uint32_t));

        uint8_t    *min_cn            = (uint8_t *) memalign(8, outWidth * outHeight * sizeof(uint8_t));
        uint8_t    *max_cn            = (uint8_t *) memalign(8, outWidth * outHeight * sizeof(uint8_t));
        uint16_t   *mean_cn           = (uint16_t *)memalign(8, outWidth * outHeight * sizeof(uint16_t));
        uint32_t   *var_cn            = (uint32_t *)memalign(8, outWidth * outHeight * sizeof(uint32_t));

        /* ----------------------------------------------------------------------
         * Size of the scratch buffer
         * depends on value of 'mode'. If mode is zero then scratch buffer size
         * required is 64 bytes. If the mode is one then size of scratch buffer
         * required is (imageWidth*statBlockHeight + 64)
         *----------------------------------------------------------------------*/
        if( mode == 0x0 ) {
            scratchBufSize = 64;
        } else {
            scratchBufSize               = prm[tpi].imageWidth * prm[tpi].statBlockHeight + 64;
        }
        scratch           = (uint8_t *) VLIB_memalign(8, scratchBufSize);

        /* Only run the test if the buffer allocations fit in the heap */
        if( input && min_opt && max_opt && mean_opt && var_opt && scratch && min_cn && max_cn && mean_cn && var_cn ) {
            uint32_t    i, j, fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            input, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            retVal =  VLIB_blockStatistics(input,
                                           prm[tpi].imagePitch,
                                           prm[tpi].imageWidth,
                                           prm[tpi].imageHeight,
                                           prm[tpi].statBlockWidth,
                                           prm[tpi].statBlockHeight,
                                           min_opt,
                                           max_opt,
                                           mean_opt,
                                           var_opt,
                                           scratch,
                                           mode);
            VLIB_profile_stop();

            if( retVal == 0x0 ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            }

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_blockStatistics_cn(input,
                                    prm[tpi].imagePitch,
                                    prm[tpi].imageWidth,
                                    prm[tpi].imageHeight,
                                    prm[tpi].statBlockWidth,
                                    prm[tpi].statBlockHeight,
                                    min_cn,
                                    max_cn,
                                    mean_cn,
                                    var_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i=0; i < (outHeight); i++ ) {
                for( j=0; j < (outWidth); j++ ) {
                    if((min_opt[i * outWidth + j] != min_cn[i * outWidth + j])) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        printf("row:%d, col:%d, min_out:%u, min_EOut:%u \n", i, j, min_opt[i * outWidth + j], min_cn[i * outWidth + j]);
                        break;
                    }
                    if((max_opt[i * outWidth + j] != max_cn[i * outWidth + j])) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        printf("row:%d, col:%d, max_out:%u, max_EOut:%u \n", i, j, max_opt[i * outWidth + j], max_cn[i * outWidth + j]);
                        break;
                    }
                    if((mean_opt[i * outWidth + j] != mean_cn[i * outWidth + j])) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        printf("row:%d, col:%d, mean_out:%u, mean_EOut:%u \n", i, j, mean_opt[i * outWidth + j], mean_cn[i * outWidth + j]);
                        break;
                    }
                    if((var_opt[i * outWidth + j] != var_cn[i * outWidth + j])) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        printf("row:%d, col:%d, var_out:%u, var_EOut:%u \n", i, j, var_opt[i * outWidth + j], var_cn[i * outWidth + j]);
                        break;
                    }
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if((prm[tpi].staticOutMin != NULL) && (prm[tpi].staticOutMax != NULL) && (prm[tpi].staticOutMean != NULL) && (prm[tpi].staticOutVar != NULL)) {
                for( i=0; i < (outHeight); i++ ) {
                    for( j=0; j < (outWidth); j++ ) {
                        if((prm[tpi].staticOutMin[i * outWidth + j] != min_cn[i * outWidth + j])) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            printf("row:%d, col:%d, min_out:%u, min_EOut:%u \n", i, j, prm[tpi].staticOutMin[i * outWidth + j], min_cn[i * outWidth + j]);
                            break;
                        }
                        if((prm[tpi].staticOutMax[i * outWidth + j] != max_cn[i * outWidth + j])) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            printf("row:%d, col:%d, max_out:%u, max_EOut:%u \n", i, j, prm[tpi].staticOutMax[i * outWidth + j], max_cn[i * outWidth + j]);
                            break;
                        }
                        if((prm[tpi].staticOutMean[i * outWidth + j] != mean_cn[i * outWidth + j])) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            printf("row:%d, col:%d, mean_out:%u, mean_EOut:%u \n", i, j, prm[tpi].staticOutMean[i * outWidth + j], mean_cn[i * outWidth + j]);
                            break;
                        }
                        if((prm[tpi].staticOutVar[i * outWidth + j] != var_cn[i * outWidth + j])) {
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            printf("row:%d, col:%d, var_out:%u, var_EOut:%u \n", i, j, prm[tpi].staticOutVar[i * outWidth + j], var_cn[i * outWidth + j]);
                            break;
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | imageWidth= %d, imageHeight= %d, statBlockWidth= %d, statBlockHeight= %d, mode = %d",
                    testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].statBlockWidth, prm[tpi].statBlockHeight, mode);
            VLIB_formula_add_test((prm[tpi].imageWidth) * (prm[tpi].imageHeight), NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "imageWidth= %d, imageHeight= %d, statBlockWidth= %d, statBlockHeight= %d ",
                    prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].statBlockWidth, prm[tpi].statBlockHeight);
            VLIB_skip_test(desc);
        }

        VLIB_align_free(input);
        VLIB_align_free(min_opt);
        VLIB_align_free(max_opt);
        VLIB_align_free(mean_opt);
        VLIB_align_free(var_opt);
        VLIB_align_free(scratch);

        align_free(min_cn);
        align_free(max_cn);
        align_free(mean_cn);
        align_free(var_cn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "imageWidth*imageHeight");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_blockStatistics");
    } else {
        VLIB_blockStatistics_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_blockStatistics_d.c                                 */
/* ======================================================================== */

