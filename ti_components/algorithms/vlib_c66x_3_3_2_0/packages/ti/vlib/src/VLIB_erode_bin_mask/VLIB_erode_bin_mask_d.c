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

#include "VLIB_erode_bin_mask.h"
#include "VLIB_erode_bin_mask_cn.h"
#include "VLIB_erode_bin_mask_idat.h"

#include "../VLIB_packMask32/VLIB_packMask32_cn.h"
#include "../VLIB_unpackMask32/VLIB_unpackMask32_cn.h"

/* VLIB_erode_bin_mask_d:  Test Driver Routine */
void VLIB_erode_bin_mask_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    erode_bin_mask_testParams_t   *prm;

    erode_bin_mask_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_erode_bin_mask");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes and function parameters */
        uint32_t    in_pack_size  = prm[tpi].in_width * prm[tpi].in_height / 8 + 4; /* bit packed binary input with zero padding */
        uint32_t    out_pack_size = prm[tpi].in_width * prm[tpi].in_height / 8;     /* bit packed binary output */
        uint32_t    cols          = prm[tpi].in_width * (prm[tpi].in_height - 2);   /* total processed cols is 2 rows less than input */
        uint32_t    pitch         = prm[tpi].in_width;

        /* Allocate buffers for each test vector */
        uint8_t   *input_unpk      =  (uint8_t *) malloc(prm[tpi].in_width * prm[tpi].in_height);
        uint8_t   *in_data         =  (uint8_t *) VLIB_memalign(8, in_pack_size);
        uint8_t   *out_data        =  (uint8_t *) VLIB_memalign(8, out_pack_size);
        uint8_t   *output_unpk     =  (uint8_t *) malloc(prm[tpi].in_width * prm[tpi].in_height);
        uint8_t   *output_unpk_cn  =  (uint8_t *) malloc(prm[tpi].in_width * prm[tpi].in_height);
        int8_t    *mask            =   (int8_t *) VLIB_malloc(9);

        /* Only run the test if the buffer allocations fit in the heap */
        if( input_unpk && in_data && out_data && output_unpk && output_unpk_cn && mask ) {

            int32_t    fail, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            input_unpk, prm[tpi].staticIn,
                            prm[tpi].in_width, prm[tpi].in_height, prm[tpi].in_width,
                            sizeof(uint8_t), testPatternString);

            /* In case input is not binary (rg. random input), mask out all bits except bit 0 */
            for( i=0; i < prm[tpi].in_width * prm[tpi].in_height; i++ ) {
                input_unpk[i] &= 1;
            }

            /* Zero pad the extra word added to the end of the packed input buffer */
            memset(&in_data[in_pack_size - 4], 0, 4);

            /* Fill mask array */
            for( i=0; i < 9; i++ ) {
                mask[i] = prm[tpi].mask[i];
            }

            /* Pack input image */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_packMask32_cn(input_unpk, (uint32_t *)in_data, prm[tpi].in_width * prm[tpi].in_height);

            /* Clear intermediate output buffer that is used for both opt and nat_c, since the first and last lines are not set */
            memset(out_data, 0, out_pack_size);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_erode_bin_mask(in_data, out_data + prm[tpi].in_width / 8, mask, cols, pitch); /* Center output vertically */
            VLIB_profile_stop();

            /* Unpack output image */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_unpackMask32_cn((uint32_t *)out_data, output_unpk, prm[tpi].in_width * prm[tpi].in_height);

            /* Clear intermediate output buffer that is used for both opt and nat_c, since the first and last lines are not set */
            memset(out_data, 0, out_pack_size);

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_erode_bin_mask_cn(in_data, out_data + prm[tpi].in_width / 8, mask, cols, pitch); /* Center output vertically */
            VLIB_profile_stop();

            /* Unpack output image */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_unpackMask32_cn((uint32_t *)out_data, output_unpk_cn, prm[tpi].in_width * prm[tpi].in_height);

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) output_unpk, (void *)output_unpk_cn, prm[tpi].in_width * prm[tpi].in_height * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)output_unpk_cn, prm[tpi].in_width * prm[tpi].in_height * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | in_width=%d, in_height=%d, cols=%d, pitch=%d",
                    testPatternString, prm[tpi].in_width, prm[tpi].in_height, cols, pitch);
            VLIB_formula_add_test(cols, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "in_width=%d, in_height=%d, cols=%d, pitch=%d",
                    prm[tpi].in_width, prm[tpi].in_height, cols, pitch);
            VLIB_skip_test(desc);
        }

#if 0
        /* Display input/output (for debug) */
        VLIB_display_image_bits(input_unpk,  prm[tpi].in_height, prm[tpi].in_width);
        VLIB_display_image_bits(output_unpk,  prm[tpi].in_height, prm[tpi].in_width);
        VLIB_display_image_bits(output_unpk_cn, prm[tpi].in_height, prm[tpi].in_width);
#endif

        /* Free buffers for each test vector */
        VLIB_free(mask);
        free(output_unpk_cn);
        free(output_unpk);
        VLIB_align_free(out_data);
        VLIB_align_free(in_data);
        free(input_unpk);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = cols = in_width * (in_height - 2)",
                              "cols = in_width * (in_height - 2)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_erode_bin_mask");
    } else {
        VLIB_erode_bin_mask_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_erode_bin_mask_d.c                                   */
/* ======================================================================== */

