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

#include "VLIB_xyGradients_Magnitude_Orientations.h"
#include "VLIB_xyGradients_Magnitude_Orientations_cn.h"
#include "VLIB_xyGradients_Magnitude_Orientations_idat.h"

/* VLIB_xyGradients_Magnitude_Orientations_d:  Test Driver Routine */
void VLIB_xyGradients_Magnitude_Orientations_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    xyGradientsMagOrien_testParams_t   *prm;

    xyGradientsMagOrien_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_xyGradients_Magnitude_Orientations");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].Width * prm[tpi].Height;
        uint32_t    out_size =   (prm[tpi].Width - 2) * (prm[tpi].Height - 2);

        /* Allocate buffers for each test vector */
        uint8_t    *img      = (uint8_t *)  VLIB_malloc(inp_size);
        uint32_t   *Mag      = (uint32_t *) VLIB_malloc(out_size * sizeof(uint32_t));
        uint32_t   *Orien    = (uint32_t *) VLIB_malloc(out_size * sizeof(uint32_t));
        uint32_t   *Mag_cn   = (uint32_t *) malloc(out_size * sizeof(uint32_t));
        uint32_t   *Orien_cn = (uint32_t *) malloc(out_size * sizeof(uint32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( img && Mag && Orien && Mag_cn && Orien_cn ) {

            int32_t    fail, i;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            img, prm[tpi].staticIn,
                            prm[tpi].Width, prm[tpi].Height, prm[tpi].Width,
                            sizeof(uint8_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_xyGradients_Magnitude_Orientations(img, prm[tpi].Width, prm[tpi].Height, prm[tpi].bins, Mag, Orien);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_xyGradients_Magnitude_Orientations_cn(img, prm[tpi].Width, prm[tpi].Height, prm[tpi].bins, Mag_cn, Orien_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( i=0; i < out_size; i++ ) {
                if( Mag[i] != Mag_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    //printf("i=%d, Mag=%d, Magcn=%d\n", i, Mag[i], Mag_cn[i]);
                    break;
                }
                if( Orien[i] != Orien_cn[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    //printf("i=%d, Or=%d, Orcn=%d\n", i, Orien[i], Orien_cn[i]);
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutMag != NULL &&
                prm[tpi].staticOutOrien != NULL ) {
                for( i=0; i < out_size; i++ ) {
                    if( prm[tpi].staticOutMag[i] != Mag_cn[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        break;
                    }
                    if( prm[tpi].staticOutOrien[i] != Orien_cn[i] ) {
                        status_nat_vs_ref = vlib_KERNEL_FAIL;
                        break;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | Width=%d, Height=%d, bins=%d, out size=%d",
                    testPatternString, prm[tpi].Width, prm[tpi].Height, prm[tpi].bins, out_size);
            VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "Width=%d, Height=%d, bins=%d, out size=%d",
                    prm[tpi].Width, prm[tpi].Height, prm[tpi].bins, out_size);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(Orien_cn);
        free(Mag_cn);
        VLIB_free(Orien);
        VLIB_free(Mag);
        VLIB_free(img);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = (Width-2) * (Height-2)",
                              "(Width-2) * (Height-2)");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_xyGradients_Magnitude_Orientations");
    } else {
        VLIB_xyGradients_Magnitude_Orientations_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_xyGradients_Magnitude_Orientations_d.c               */
/* ======================================================================== */

