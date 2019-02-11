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

#include "VLIB_harrisScore_7x7.h"
#include "VLIB_harrisScore_7x7_cn.h"
#include "VLIB_harrisScore_7x7_idat.h"

#include "../VLIB_xyGradients/VLIB_xyGradients_cn.h"

/* ///////////////////////////////////// */
/* Makes a w * h custom pattern          */
/* ///////////////////////////////////// */
static void CreatePattern1(uint8_t *p, int16_t w, int16_t h)
{
    int32_t    i;

    for( i = 0; i < w * h; i++ ) {
        int32_t    x = i % w;
        int32_t    y = i / w;

        p[i] = (x | y) / 2 + 127;
    }
}

/* VLIB_harrisScore_7x7_d:  Test Driver Routine */
void VLIB_harrisScore_7x7_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    harrisScore_7x7_testParams_t   *prm;

    harrisScore_7x7_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_harrisScore_7x7");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        /* Kernel does not write to last 3*width + 3 pixels */
        int32_t    out_size = prm[tpi].width * prm[tpi].height - (3 * prm[tpi].width + 3);

        /* Allocate buffers for each test vector */
        uint8_t   *input    =  (uint8_t *) malloc(prm[tpi].width * prm[tpi].height);
        int16_t   *gradX    =  (int16_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height * sizeof(int16_t));
        int16_t   *gradY    =  (int16_t *) VLIB_malloc(prm[tpi].width * prm[tpi].height * sizeof(int16_t));

        uint16_t   *outm     =  (uint16_t *) VLIB_malloc(out_size * sizeof(uint16_t));
        uint16_t   *outm_cn  =  (uint16_t *) malloc(out_size * sizeof(uint16_t));

#ifdef C64T
        uint8_t   *scratch    = (uint8_t *) VLIB_memalign(4, 108 * prm[tpi].width);
#else
        uint8_t   *scratch    = (uint8_t *) VLIB_memalign(4, 96 * prm[tpi].width);
#endif

        /* Only run the test if the buffer allocations fit in the heap */
        if( input && gradX && gradY && outm && outm_cn && scratch ) {

            int32_t    fail, x, y;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern, (uint8_t)255,
                            input, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            if( prm[tpi].testPattern == CUSTOM ) {
                /* Synthetic motion sequence */
                CreatePattern1(input, prm[tpi].width, prm[tpi].height);
            }

            /* Compute the gradient using the library function */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            VLIB_xyGradients_cn(input, gradX + prm[tpi].width + 1, gradY + prm[tpi].width + 1,
                                prm[tpi].width, prm[tpi].height);
            /* Pointer starts from the image one row and one column less */


            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_harrisScore_7x7(gradX, gradY, prm[tpi].width, prm[tpi].height,
                                 (int16_t *)outm, prm[tpi].k, scratch);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_harrisScore_7x7_cn(gradX, gradY, prm[tpi].width, prm[tpi].height,
                                    (int16_t *)outm_cn, prm[tpi].k, scratch);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            /* Only compare the valid region, skipping the border of 4 pixels = 7/2 + 1 (7/2 is border from harris, 1 is border from xyGrad)
             * This is done b/c natc only outputs values to this region, while opt outputs values (even invalid ones) in full region - last
             * three lines */
            for( y=4; y < prm[tpi].height - 4; y++ ) {
                for( x=4; x < prm[tpi].width - 4; x++ ) {
                    if( outm[y * prm[tpi].width + x] != outm_cn[y * prm[tpi].width + x] ) {
                        printf("(%d, %d) outm = %x\toutm_cn = %x\n", x, y, outm[y * prm[tpi].width + x], outm_cn[y * prm[tpi].width + x]);
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        break;
                    }
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                /* Only compare the valid region, skipping the border of 4 pixels = 7/2 + 1 (7/2 is border from harris, 1 is border from xyGrad) */
                for( y=4; y < prm[tpi].height - 4; y++ ) {
                    for( x=4; x < prm[tpi].width - 4; x++ ) {
                        if( prm[tpi].staticOut[y * prm[tpi].width + x] != outm_cn[y * prm[tpi].width + x] ) {
                            printf("(%d, %d) refOut = %x\toutm_cn = %x\n", x, y, prm[tpi].staticOut[y * prm[tpi].width + x], outm_cn[y * prm[tpi].width + x]);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                            break;
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, height=%d, k=%d, %s",
                    testPatternString, prm[tpi].width, prm[tpi].height, prm[tpi].k, prm[tpi].desc);
            VLIB_formula_add_test(prm[tpi].width * prm[tpi].height, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, k=%d",
                    prm[tpi].width, prm[tpi].height, prm[tpi].k);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_align_free(scratch);
        free(outm_cn);
        VLIB_free(outm);
        VLIB_free(gradY);
        VLIB_free(gradX);
        free(input);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height",
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_harrisScore_7x7");
    } else {
        VLIB_harrisScore_7x7_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_harrisScore_7x7_d.c                                  */
/* ======================================================================== */

