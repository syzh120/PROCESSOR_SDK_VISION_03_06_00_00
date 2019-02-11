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

#include "VLIB_grayscale_morphology.h"
#include "VLIB_grayscale_morphology_cn.h"
#include "VLIB_grayscale_morphology_idat.h"

void VLIB_grayscale_morphology_d(uint8_t LevelOfFeedback)
{
    int32_t                         tpi; /* test parameter index */
    GrayscaleMorphologyOperation    operation;

    /* Test Parameters */
    grayScaleMorph_testParams_t   *prm;

    grayScaleMorph_getTestParams(&prm, &test_cases);

    for( operation = GRAYSCALE_MORPH_DILATE; operation <= GRAYSCALE_MORPH_GRADIENT; operation++ ) {

        char    testName[32];

        switch( operation ) {
            case GRAYSCALE_MORPH_DILATE :
                strcpy(testName, "GRAYSCALE_MORPH_DILATE");
                break;

            case GRAYSCALE_MORPH_ERODE :
                strcpy(testName, "GRAYSCALE_MORPH_ERODE");
                break;

            case GRAYSCALE_MORPH_OPEN :
                strcpy(testName, "GRAYSCALE_MORPH_OPEN");
                break;

            case GRAYSCALE_MORPH_CLOSE :
                strcpy(testName, "GRAYSCALE_MORPH_CLOSE");
                break;

            case GRAYSCALE_MORPH_TOPHAT :
                strcpy(testName, "GRAYSCALE_MORPH_TOPHAT");
                break;

            case GRAYSCALE_MORPH_BOTHAT :
                strcpy(testName, "GRAYSCALE_MORPH_BOTHAT");
                break;

            case GRAYSCALE_MORPH_GRADIENT :
                strcpy(testName, "GRAYSCALE_MORPH_GRADIENT");
                break;
        }

        /* Initialize profiling */
        VLIB_profile_init(2, testName);

        /* Run each test case */
        for( tpi=0; tpi < test_cases; tpi++ ) {

            /* Initialize status flags */
            int32_t    status_nat_vs_int  = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */

            /* Allocate buffers for each test vector */
            uint8_t   *input             = (uint8_t *) VLIB_memalign(8, prm[tpi].imagePitch * prm[tpi].imageHeight);
            uint8_t   *output_opt        = (uint8_t *) VLIB_memalign(8, prm[tpi].imagePitch * prm[tpi].imageHeight);
            uint8_t   *output_cn         = (uint8_t *) memalign(8, prm[tpi].imagePitch * prm[tpi].imageHeight);
            uint8_t   *scratch1          = (uint8_t *) VLIB_memalign(8, prm[tpi].imagePitch * prm[tpi].imageHeight);
            uint8_t   *scratch2          = (uint8_t *) VLIB_memalign(8, prm[tpi].imagePitch * prm[tpi].imageHeight);
            uint8_t   *struct_elem       = (uint8_t *) VLIB_memalign(8, prm[tpi].se_w * prm[tpi].se_h);
            uint8_t   *struct_elem_refl  = (uint8_t *) VLIB_memalign(8, prm[tpi].se_w * prm[tpi].se_h);

            /* Only run the test if the buffer allocations fit in the heap */
            if( input && output_opt && output_cn && scratch1 && scratch2 && struct_elem && struct_elem_refl ) {

                int32_t    fail;
                int32_t    i, j;
                int32_t    outPadX = ((operation == GRAYSCALE_MORPH_DILATE) || (operation == GRAYSCALE_MORPH_ERODE) ||
                                      (operation == GRAYSCALE_MORPH_GRADIENT)) ? (prm[tpi].se_w - 1) : 2 * (prm[tpi].se_w - 1);
                int32_t    outPadY = ((operation == GRAYSCALE_MORPH_DILATE) || (operation == GRAYSCALE_MORPH_ERODE) ||
                                      (operation == GRAYSCALE_MORPH_GRADIENT)) ? (prm[tpi].se_h - 1) : 2 * (prm[tpi].se_h - 1);

                /* Fill input arrays according to desired test pattern */
                VLIB_fillBuffer(prm[tpi].testPattern,
                                (uint8_t)0,
                                input, prm[tpi].staticIn,
                                prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].imagePitch,
                                sizeof(uint8_t), testPatternString);

                copyRoi(struct_elem, prm[tpi].se_ptr, prm[tpi].se_w, prm[tpi].se_h, prm[tpi].se_w, sizeof (uint8_t));
                copyRoi(struct_elem_refl, prm[tpi].se_reflc_ptr, prm[tpi].se_w, prm[tpi].se_h, prm[tpi].se_w, sizeof (uint8_t));

                /* Clear output arrays to different values */
                memset(output_opt, 0, sizeof(output_opt));
                memset(output_cn, 0xff, sizeof(output_cn));

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_grayscale_morphology(prm[tpi].imageWidth, prm[tpi].imagePitch, prm[tpi].imageHeight,
                                          input, prm[tpi].se_w, prm[tpi].se_h, struct_elem, struct_elem_refl,
                                          scratch1, scratch2, output_opt, operation);
                VLIB_profile_stop();

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_grayscale_morphology_cn(prm[tpi].imageWidth, prm[tpi].imagePitch, prm[tpi].imageHeight,
                                             input, prm[tpi].se_w, prm[tpi].se_h, struct_elem, struct_elem_refl,
                                             scratch1, scratch2, output_cn, operation);
                VLIB_profile_stop();

                /* Compare natural C Output and Optimized Output */
                for( i=0; i < (prm[tpi].imageHeight - outPadY); i++ ) {
                    for( j=0; j < (prm[tpi].imageWidth - outPadX); j++ ) {
                        if( output_opt[i * prm[tpi].imageWidth + j] != output_cn[i * prm[tpi].imagePitch + j] ) {
                            status_nat_vs_int = vlib_KERNEL_FAIL;
                            printf("row:%d, col:%d, out:%u, EOut:%u \n", i, j, output_opt[i * prm[tpi].imageWidth + j], output_cn[i * prm[tpi].imageWidth + j]);
                            break;
                        }
                    }
                }

                /* Set the 'fail' flag based on test vector comparison results */
                fail = (status_nat_vs_int == vlib_KERNEL_FAIL) ? 1 : 0;

                est_test=1;

                /* Profile display and preparation for cycle estimation */
                sprintf(desc, "%s generated input | Opt and NatC results compared | blk_w= %d, blk_h= %d, se_w= %d, se_h= %d | %s",
                        testPatternString, prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].se_w, prm[tpi].se_h, prm[tpi].desc);
                /* Profile display and preparation for cycle estimation */
                VLIB_formula_add_test((prm[tpi].imageWidth - prm[tpi].se_w + 1) * (prm[tpi].imageHeight - prm[tpi].se_h + 1) *
                                      prm[tpi].se_w * prm[tpi].se_h, NULL, NULL, fail, desc, NULL);

            } else {
                /* Display the error printout for this test vector before moving on to the next test vector */
                sprintf(desc, "blk_w= %d, blk_h= %d, se_w= %d, se_h= %d | %s",
                        prm[tpi].imageWidth, prm[tpi].imageHeight, prm[tpi].se_w, prm[tpi].se_h, prm[tpi].desc);
                VLIB_skip_test(desc);
            }

            VLIB_align_free(struct_elem_refl);
            VLIB_align_free(struct_elem);
            VLIB_align_free(scratch2);
            VLIB_align_free(scratch1);
            align_free(output_cn);
            VLIB_align_free(output_opt);
            VLIB_align_free(input);
        }

        /* Calculate and display cycle formula and/or cycle range (and testing success) */
        VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                                  NULL,
                                  "((blk_w - se_w + 1) * (blk_h - se_h + 1) * se_w * se_h)");

        /* Provide memory requirements */
        VLIB_kernel_memory();
    }
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST
main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_grayscale_morphology");
    } else {
        VLIB_grayscale_morphology_d(0);
    }
}
#endif /* __ONESHOTTEST */


/* The following wrapper function is compiled into the VLIB library in a
 * separate file, but is only shown here to for documentation sake, to
 * demonstrate how library sub-functions are internally being called.
 */
#if 0 /* Do not compile since symbol is already in VLIB library */
void VLIB_grayscale_morphology(
    uint16_t blk_w,                /* width of input block, in elements */
    uint16_t line_ofst,            /* offset between input lines, in elements */
    uint16_t blk_h,                /* height of input block */
    const uint8_t data_ptr[],      /* input data pointer */
    uint16_t se_w,                 /* width of structuring element block, in elements */
    uint16_t se_h,                 /* height of structuring element block */
    const uint8_t se_ptr[],        /* structuring element data pointer */
    const uint8_t refl_se_ptr[],   /* Reflected structuring element data pointer */
    uint8_t scratch1_ptr[],        /* scratch 1 pointer */
    uint8_t scratch2_ptr[],        /* scratch 2 pointer */
    uint8_t output_ptr[],          /* output data pointer */
    GrayscaleMorphologyOperation operation  /* Grayscale Morphology Operation */
    )
{
    switch( operation ) {
        case GRAYSCALE_MORPH_DILATE :
            VLIB_grayscale_dilate_mask(blk_w, line_ofst, blk_h,
                                       data_ptr, se_w, se_h, refl_se_ptr, output_ptr);
            break;

        case GRAYSCALE_MORPH_ERODE :
            VLIB_grayscale_erode_mask(blk_w, line_ofst, blk_h,
                                      data_ptr, se_w, se_h, se_ptr, output_ptr);
            break;

        case GRAYSCALE_MORPH_OPEN :
            VLIB_grayscale_erode_mask(blk_w, line_ofst, blk_h,
                                      data_ptr, se_w, se_h, se_ptr, scratch1_ptr);

            VLIB_grayscale_dilate_mask(blk_w - (se_w - 1U), line_ofst, blk_h - (se_h - 1U),
                                       scratch1_ptr, se_w, se_h, refl_se_ptr, output_ptr);
            break;

        case GRAYSCALE_MORPH_CLOSE :
            VLIB_grayscale_dilate_mask(blk_w, line_ofst, blk_h,
                                       data_ptr, se_w, se_h, refl_se_ptr, scratch1_ptr);

            VLIB_grayscale_erode_mask(blk_w - (se_w - 1U), line_ofst, blk_h - (se_h - 1U),
                                      scratch1_ptr, se_w, se_h, se_ptr, output_ptr);
            break;

        case GRAYSCALE_MORPH_TOPHAT :
            VLIB_grayscale_erode_mask(blk_w, line_ofst, blk_h,
                                      data_ptr, se_w, se_h, se_ptr, output_ptr);

            VLIB_grayscale_dilate_mask(blk_w - (se_w - 1U), blk_w, blk_h - (se_h - 1U),
                                       output_ptr, se_w, se_h, refl_se_ptr, scratch1_ptr);

            VLIB_grayscale_morp_diff(blk_w - ((uint16_t)2 * (se_w - 1U)), blk_w, blk_h - ((uint16_t)2 * (se_h - 1U)),
                                     &data_ptr[((se_w - 1U) * blk_w) + (se_w - 1U)], scratch1_ptr, output_ptr);

            break;

        case GRAYSCALE_MORPH_BOTHAT :
            VLIB_grayscale_dilate_mask(blk_w, line_ofst, blk_h,
                                       data_ptr, se_w, se_h, refl_se_ptr, output_ptr);

            VLIB_grayscale_erode_mask(blk_w - (se_w - 1U), blk_w, blk_h - (se_h - 1U),
                                      output_ptr, se_w, se_h, se_ptr, scratch1_ptr);

            VLIB_grayscale_morp_diff(blk_w - ((uint16_t)2 * (se_w - 1U)), blk_w, blk_h - ((uint16_t)2 * (se_h - 1U)),
                                     scratch1_ptr, &data_ptr[((se_w - 1U) * blk_w) + (se_w - 1U)], output_ptr);

            break;

        case GRAYSCALE_MORPH_GRADIENT :
            VLIB_grayscale_dilate_mask(blk_w, line_ofst, blk_h,
                                       data_ptr, se_w, se_h, refl_se_ptr, scratch1_ptr);

            VLIB_grayscale_erode_mask(blk_w, line_ofst, blk_h,
                                      data_ptr, se_w, se_h, se_ptr, scratch2_ptr);

            VLIB_grayscale_morp_diff(blk_w - (se_w - 1U), blk_w, blk_h - (se_h - 1U),
                                     scratch1_ptr, scratch2_ptr, output_ptr);

            break;
        default :
            break;
    }
}

#endif


/* ======================================================================== */
/*  End of file:  VLIB_grayscale_morphology_d.c                             */
/* ======================================================================== */

