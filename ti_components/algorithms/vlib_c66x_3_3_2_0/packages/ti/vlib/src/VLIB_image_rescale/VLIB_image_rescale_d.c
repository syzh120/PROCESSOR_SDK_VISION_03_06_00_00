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

#include "VLIB_image_rescale.h"
#include "VLIB_image_rescale_cn.h"
#include "VLIB_image_rescale_idat.h"

/* Default mode is frame mode, enable below Macro for slice mode */
/*#define PROCESS_MODE_SLICE*/
#define NO_OF_SLICES 2

/* VLIB_image_rescale_d:  Test Driver Routine */
void VLIB_image_rescale_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    image_rescale_testParams_t   *prm;

    image_rescale_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_image_rescale");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Declare variables for buffer sizes and pointers */
        uint32_t    in_size, out_w, out_h, out_size, bytesperpixels;
        uint8_t    *pIn, *pOut, *pOut_cn;

        /* Compute buffer sizes */
        in_size  =   prm[tpi].inCols * prm[tpi].inRows;
        if( prm[tpi].color_format == COLOR_FORMAT_LUMA_ONLY ) {
            out_w = (uint16_t)(((uint32_t)(prm[tpi].inCols << 12)) / (prm[tpi].nFactor));
            out_h = (uint16_t)(((uint32_t)(prm[tpi].inRows << 12)) / (prm[tpi].nFactor));
            bytesperpixels = 1;
        } else {
            out_w = prm[tpi].inCols / 2;
            out_h = prm[tpi].inRows / 2;
            bytesperpixels = 2;
        }
        out_size = out_w * out_h;
        VLIB_assert(out_size > 0, "Output size is not greater than zero.");

        /* Allocate buffers for each test vector */
        pIn          = (uint8_t *) VLIB_malloc(in_size * bytesperpixels);
        pOut         = (uint8_t *) VLIB_malloc(out_size * bytesperpixels);
        pOut_cn      = (uint8_t *) malloc(out_size * bytesperpixels);

        /* Only run the test if the buffer allocations fit in the heap */
        if( pIn && pOut && pOut_cn ) {

            int32_t    fail, mode;
#ifdef PROCESS_MODE_SLICE
            int32_t    k, sliced_Insize=0, sliced_Oupsize=0;
#endif

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            pIn, prm[tpi].staticIn,
                            prm[tpi].inCols, prm[tpi].inRows, prm[tpi].inCols * bytesperpixels,
                            bytesperpixels, testPatternString);

#ifdef PROCESS_MODE_SLICE
            if( prm[tpi].color_format == COLOR_FORMAT_YUV_422_UYVY || prm[tpi].color_format == COLOR_FORMAT_YUV_422_YUYV ) {

                for( k=0; k < NO_OF_SLICES; k++ ) {
                    VLIB_profile_start(vlib_KERNEL_OPT);
                    VLIB_image_rescale(&pIn[k * sliced_Insize], &pOut[k * sliced_Oupsize], prm[tpi].nFactor, prm[tpi].inCols, prm[tpi].inRows / NO_OF_SLICES, prm[tpi].color_format);
                    VLIB_profile_stop();

                    VLIB_profile_start(vlib_KERNEL_CN);
                    VLIB_image_rescale_cn(&pIn[k * sliced_Insize], &pOut_cn[k * sliced_Oupsize], prm[tpi].nFactor, prm[tpi].inCols, prm[tpi].inRows / NO_OF_SLICES, prm[tpi].color_format);
                    VLIB_profile_stop();

                    sliced_Insize = prm[tpi].inCols * (prm[tpi].inRows / NO_OF_SLICES) * 2;
                    sliced_Oupsize = out_w * (out_h / NO_OF_SLICES) * 2;
                }
            } else if( prm[tpi].color_format == COLOR_FORMAT_LUMA_ONLY ) {

                for( k=0; k < NO_OF_SLICES; k++ ) {
                    VLIB_profile_start(vlib_KERNEL_OPT);
                    VLIB_image_rescale(&pIn[k * sliced_Insize], &pOut[k * sliced_Oupsize], prm[tpi].nFactor, prm[tpi].inCols, prm[tpi].inRows / NO_OF_SLICES, prm[tpi].color_format);
                    VLIB_profile_stop();

                    VLIB_profile_start(vlib_KERNEL_CN);
                    VLIB_image_rescale_cn(&pIn[k * sliced_Insize], &pOut_cn[k * sliced_Oupsize], prm[tpi].nFactor, prm[tpi].inCols, prm[tpi].inRows / NO_OF_SLICES, prm[tpi].color_format);
                    VLIB_profile_stop();

                    sliced_Insize = prm[tpi].inCols * (prm[tpi].inRows / NO_OF_SLICES);
                    sliced_Oupsize = out_w * (out_h / NO_OF_SLICES);
                }
            } else {

            }
#else /*PROCESS_MODE_SLICE*/
            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_image_rescale(pIn, pOut, prm[tpi].nFactor, prm[tpi].inCols, prm[tpi].inRows, prm[tpi].color_format);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_image_rescale_cn(pIn, pOut_cn, prm[tpi].nFactor, prm[tpi].inCols, prm[tpi].inRows, prm[tpi].color_format);
            VLIB_profile_stop();
#endif  /* PROCESS_MODE_SLICE*/

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) pOut, (void *)pOut_cn, out_size * bytesperpixels);

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)pOut_cn, out_size * bytesperpixels);
            }

#if 0
            {
                int    i;

                for( i=0; i < out_size; i++ ) {
                    printf("%d, ", pOut[i]);
                }
            }
#endif
            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            mode = (prm[tpi].color_format == COLOR_FORMAT_LUMA_ONLY) ? 1 : 2;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inRows=%d, num_output_pt=%d, mode=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inRows, out_size, mode);
            VLIB_formula_add_test(out_size, out_h, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inRows=%d, num_output_pt=%d",
                    prm[tpi].inCols, prm[tpi].inRows, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(pOut_cn);
        VLIB_free(pOut);
        VLIB_free(pIn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 3, "Luma scaling using nFactor", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = out width * out height; M = out height",
                              "out width * out height");

    VLIB_profile_setMode(2, 3, "YUYV or UYVY down-scaling by 2", 1); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = out width * out height; M = out height",
                              "out width * out height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_image_rescale");
    } else {
        VLIB_image_rescale_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_image_rescale_d.c                                    */
/* ======================================================================== */

