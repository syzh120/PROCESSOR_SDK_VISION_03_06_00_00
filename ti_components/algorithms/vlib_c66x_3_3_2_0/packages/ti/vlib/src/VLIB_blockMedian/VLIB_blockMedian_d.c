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

#include "VLIB_blockMedian.h"
#include "VLIB_blockMedian_cn.h"
#include "VLIB_blockMedian_idat.h"

/* VLIB_blockMedian_d:  Test Driver Routine */
void VLIB_blockMedian_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    blockMedian_testParams_t   *prm;

    blockMedian_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_blockMedian");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].imagePitch  * prm[tpi].imageHeight;
        uint32_t    out_size = ((prm[tpi].imageHeight - prm[tpi].blockHeight) / prm[tpi].stepSizeVert + 1) *
                               ((prm[tpi].imageWidth  - prm[tpi].blockWidth)  / prm[tpi].stepSizeHorz + 1);
        uint32_t    num_pts =    prm[tpi].blockWidth  * prm[tpi].blockHeight  * out_size;

        /* Allocate buffers for each test vector */
        uint8_t    *input      =  (uint8_t *) VLIB_memalign(8, inp_size);
        uint8_t    *output_opt =  (uint8_t *) VLIB_malloc(out_size);
        uint8_t    *output_cn  =  (uint8_t *) malloc(out_size);
        uint16_t   *scratch    = (uint16_t *) VLIB_memalign(8, (256 * 4) * sizeof(uint16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( input && output_opt && output_cn && scratch ) {

            int32_t    fail;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            input, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_blockMedian(input, output_opt, scratch,
                             prm[tpi].imageWidth,   prm[tpi].imageHeight, prm[tpi].imagePitch,
                             prm[tpi].blockWidth,   prm[tpi].blockHeight,
                             prm[tpi].stepSizeHorz, prm[tpi].stepSizeVert);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_blockMedian_cn(input, output_cn, scratch,
                                prm[tpi].imageWidth,   prm[tpi].imageHeight, prm[tpi].imagePitch,
                                prm[tpi].blockWidth,   prm[tpi].blockHeight,
                                prm[tpi].stepSizeHorz, prm[tpi].stepSizeVert);
            VLIB_profile_stop();


            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) output_opt, (void *)output_cn, out_size * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)output_cn, out_size * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | imageWidth=%d, imageHeight=%d, blockWidth=%d, blockHeight=%d, stepSizeHorz=%d, stepSizeVert=%d, out size=%d",
                    testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight,
                    prm[tpi].blockWidth, prm[tpi].blockHeight,
                    prm[tpi].stepSizeHorz, prm[tpi].stepSizeVert, out_size);
            VLIB_formula_add_test(num_pts, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "imageWidth=%d, imageHeight=%d, blockWidth=%d, blockHeight=%d, stepSizeHorz=%d, stepSizeVert=%d, out size=%d",
                    prm[tpi].imageWidth, prm[tpi].imageHeight,
                    prm[tpi].blockWidth, prm[tpi].blockHeight,
                    prm[tpi].stepSizeHorz, prm[tpi].stepSizeVert, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_align_free(input);
        VLIB_free(output_opt);
        free(output_cn);
        VLIB_align_free(scratch);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = ((imageHeight - blockHeight)/stepSizeVert + 1) * ((imageWidth - blockWidth)/stepSizeHorz + 1) * blockHeight*blockWidth",
                              "((imageHeight - blockHeight)/stepSizeVert + 1) * ((imageWidth - blockWidth)/stepSizeHorz + 1) * blockHeight*blockWidth; Cycles/pt get smaller as the blockWidth gets larger.");

    /* Provide memory requirements */
    VLIB_kernel_memory();

    return;
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_blockMedian");
    } else {
        VLIB_blockMedian_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_blockMedian_d.c                                      */
/* ======================================================================== */

