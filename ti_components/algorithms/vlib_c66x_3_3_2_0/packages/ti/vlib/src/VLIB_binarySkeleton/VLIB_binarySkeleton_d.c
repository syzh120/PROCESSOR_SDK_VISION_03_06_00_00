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

#include "VLIB_binarySkeleton.h"
#include "VLIB_binarySkeleton_cn.h"
#include "VLIB_binarySkeleton_idat.h"

/* VLIB_binarySkeleton_d:  Test Driver Routine */
void VLIB_binarySkeleton_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    binarySkeleton_testParams_t   *prm;

    binarySkeleton_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_binarySkeleton");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].imagePitch * prm[tpi].imageHeight;

        /* Allocate buffers for each test vector */
        uint8_t   *input      = (uint8_t *) malloc(inp_size);  /* Unpacked input */
        uint8_t   *output     = (uint8_t *) malloc(inp_size);  /* Unpacked output */
        uint8_t   *output_cn  = (uint8_t *) malloc(inp_size);  /* Unpacked output from cn */

        uint32_t   *in_data    = (uint32_t *) VLIB_malloc(inp_size / 8);
        uint32_t   *out_data   = (uint32_t *) VLIB_malloc(inp_size / 8);
        uint32_t   *scratch    = (uint32_t *) VLIB_malloc(inp_size / 8 + 2 * VLIB_BINSKEL_MASK_SZ * 4 * prm[tpi].se_num);

        uint8_t   *mask       = (uint8_t *) VLIB_malloc(VLIB_BINSKEL_MASK_SZ * prm[tpi].se_num);
        uint8_t   *mask_d     = (uint8_t *) VLIB_malloc(VLIB_BINSKEL_MASK_SZ * prm[tpi].se_num);

        uint8_t    iters = prm[tpi].iters;
        uint8_t    iters_cn = prm[tpi].iters;

        /* Only run the test if the buffer allocations fit in the heap */
        if( input && output && output_cn && in_data && out_data && scratch && mask && mask_d ) {

            int32_t    fail;
            int32_t    i, j;
            uint8_t    thresh = 1;

            /* Fill input array according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)1,
                            input, prm[tpi].staticIn,
                            prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                            sizeof(uint8_t), testPatternString);

            /* Initialize the mask and mask_d buffers appropriately */
            for( i=0; i < prm[tpi].se_num; i++ ) {
                for( j=0; j < VLIB_BINSKEL_MASK_SZ; j++ ) {
                    if( prm[tpi].se_ptr[i * VLIB_BINSKEL_MASK_SZ + j] == 1 ) {  /* foreground mask value = 1 */
                        mask[i * VLIB_BINSKEL_MASK_SZ + j] = 1;
                        mask_d[i * VLIB_BINSKEL_MASK_SZ + j] = 0;
                    } else if( prm[tpi].se_ptr[i * VLIB_BINSKEL_MASK_SZ + j] == 0 ) { /* background mask value = 0 */
                        mask[i * VLIB_BINSKEL_MASK_SZ + j] = 0;
                        mask_d[i * VLIB_BINSKEL_MASK_SZ + j] = 0;
                    } else { /* "don't care" bit should be set = 0 */
                        mask[i * VLIB_BINSKEL_MASK_SZ + j] = 0;
                        mask_d[i * VLIB_BINSKEL_MASK_SZ + j] = 1;
                    }
                }
            }

            /* Pack input memory */
            if( prm[tpi].testPattern == RANDOM ) {
                thresh = 100;
            }
            VLIB_create32BitPackedBinImage(input, prm[tpi].imageWidth, prm[tpi].imageHeight, (uint32_t *)in_data, thresh);
            VLIB_clear_memory(out_data, inp_size / 8);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_binarySkeleton(in_data, out_data, scratch,
                                (uint8_t(*)[VLIB_BINSKEL_MASK_SZ])mask, (uint8_t(*)[VLIB_BINSKEL_MASK_SZ])mask_d,
                                prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].se_num, &iters);
            VLIB_profile_stop();

            /* Unpack output memory */
            VLIB_unpack32BitPackedBinImage(out_data, prm[tpi].imageWidth, prm[tpi].imageHeight, output);


            VLIB_clear_memory(out_data, inp_size / 8);

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_binarySkeleton_cn(in_data, out_data, scratch,
                                   (uint8_t(*)[VLIB_BINSKEL_MASK_SZ])mask, (uint8_t(*)[VLIB_BINSKEL_MASK_SZ])mask_d,
                                   prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].se_num, &iters_cn);
            VLIB_profile_stop();

            /* Unpack output memory */
            VLIB_unpack32BitPackedBinImage(out_data, prm[tpi].imageWidth, prm[tpi].imageHeight, output_cn);

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) output, (void *) output_cn, inp_size);

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)output_cn, inp_size);
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) ||
                    (status_nat_vs_ref == vlib_KERNEL_FAIL) ||
                    iters != iters_cn) ? 1 : 0;

            est_test=1;

            if( LevelOfFeedback > 0 ) {
                for( i=0; i < prm[tpi].imageHeight; i++ ) {
                    for( j=0; j < prm[tpi].imageWidth; j++ ) {
                        printf("%d, ", output[i * prm[tpi].imageWidth + j]);
                    }

                    printf("\n");
                }

                printf("\n");
            }

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt and NatC results compared | width=%d, height=%d, num_st=%d, iters=%d",
                    testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].se_num, iters);
            VLIB_formula_add_test(prm[tpi].imageWidth * (prm[tpi].imageHeight - 2) * prm[tpi].se_num * iters, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, num_st=%d",
                    prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].se_num);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(mask_d);
        VLIB_free(mask);
        VLIB_free(scratch);
        VLIB_free(out_data);
        VLIB_free(in_data);
        free(output_cn);
        free(output);
        free(input);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * (height - 2) * num_st * iters",
                              "width * (height - 2) * num_st * iters");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_binarySkeleton");
    } else {
        VLIB_binarySkeleton_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_binarySkeleton_d.c                                   */
/* ======================================================================== */

