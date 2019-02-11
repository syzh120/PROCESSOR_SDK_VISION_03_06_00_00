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

#include "VLIB_goodFeaturestoTrack.h"
#include "VLIB_goodFeaturestoTrack_cn.h"
#include "VLIB_goodFeaturestoTrack_idat.h"

/* VLIB_goodFeaturestoTrack_d:  Test Driver Routine */
void VLIB_goodFeaturestoTrack_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    goodFeatures_testParams_t   *prm;

    goodFeatures_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_goodFeaturestoTrack");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size         =   prm[tpi].width  * prm[tpi].height;
        uint32_t    pixIndex_size    =   inp_size * 2 + 2;
        uint32_t    internalBuf_size =   inp_size + (2 * prm[tpi].patch);

        /* Allocate buffers for each test vector */
        uint16_t   *im          =  (uint16_t *) VLIB_malloc(inp_size * sizeof(uint16_t));
        uint8_t    *out_opt     =  (uint8_t *)  VLIB_malloc(inp_size * sizeof(uint8_t));
        uint8_t    *out_cn      =  (uint8_t *)  malloc(inp_size * sizeof(uint8_t));
        uint16_t   *outTemp     =  (uint16_t *) VLIB_malloc(inp_size * sizeof(uint16_t));
        int16_t    *pixIndex    =  (int16_t *)  VLIB_malloc(pixIndex_size * sizeof(int16_t));
        uint16_t   *internalBuf =  (uint16_t *) VLIB_malloc(internalBuf_size * sizeof(uint16_t));
        int32_t    *ind         =  (int32_t *)  VLIB_malloc(inp_size * sizeof(int32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( im && out_opt && out_cn && outTemp && pixIndex && internalBuf && ind ) {

            int32_t    fail;
            int32_t    good_points_number_opt, good_points_number_cn;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            im, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width * sizeof(uint16_t),
                            sizeof(uint16_t), testPatternString);

            /* Output should be initialized to zero for this API */
            memset(out_opt, 0, inp_size * sizeof(uint8_t));
            memset(outTemp, 0, inp_size * sizeof(uint16_t));

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_goodFeaturestoTrack(im, out_opt, prm[tpi].width, prm[tpi].height,
                                     prm[tpi].thresh, prm[tpi].patch, prm[tpi].qualitypar,
                                     prm[tpi].topNfeatures, prm[tpi].mindist,
                                     outTemp, &good_points_number_opt,
                                     pixIndex, internalBuf, ind);
            VLIB_profile_stop();

            /* Output should be initialized to zero for this API */
            memset(out_cn, 0, inp_size * sizeof(uint8_t));
            memset(outTemp, 0, inp_size * sizeof(uint16_t));

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_goodFeaturestoTrack_cn(im, out_cn, prm[tpi].width, prm[tpi].height,
                                        prm[tpi].thresh, prm[tpi].patch, prm[tpi].qualitypar,
                                        prm[tpi].topNfeatures, prm[tpi].mindist,
                                        outTemp, &good_points_number_cn,
                                        pixIndex, internalBuf, ind);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) out_opt, (void *)out_cn, inp_size * sizeof(uint8_t));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = VLIB_compare_mem((void *) prm[tpi].staticOut, (void *)out_cn, inp_size * sizeof(uint8_t));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;
            fail |= (good_points_number_opt != good_points_number_cn);
            if( prm[tpi].static_good_points_result != NULL ) {
                fail |= (prm[tpi].static_good_points_result[0] != good_points_number_cn);
            }

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, patch=%d, thresh=%d, mindist=%d, good_points_number=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height,
                    prm[tpi].patch, prm[tpi].thresh, prm[tpi].mindist, good_points_number_opt);
            VLIB_formula_add_test(inp_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, patch=%d, thresh=%d, mindist=%d",
                    prm[tpi].width, prm[tpi].height, prm[tpi].patch, prm[tpi].thresh, prm[tpi].mindist);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(ind);
        VLIB_free(internalBuf);
        VLIB_free(pixIndex);
        VLIB_free(outTemp);
        free(out_cn);
        VLIB_free(out_opt);
        VLIB_free(im);
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
        VLIB_memError("VLIB_goodFeaturestoTrack");
    } else {
        VLIB_goodFeaturestoTrack_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_goodFeaturestoTrack_d.c                              */
/* ======================================================================== */

