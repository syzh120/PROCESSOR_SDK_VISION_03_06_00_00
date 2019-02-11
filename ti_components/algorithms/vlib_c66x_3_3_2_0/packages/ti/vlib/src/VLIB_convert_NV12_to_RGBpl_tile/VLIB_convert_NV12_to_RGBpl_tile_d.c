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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#include "VLIB_convert_NV12_to_RGBpl_tile.h"
#include "VLIB_convert_NV12_to_RGBpl_tile_cn.h"
#include "VLIB_convert_NV12_to_RGBpl_tile_idat.h"

/* VLIB_convert_NV12_to_RGBpl_tile_d:  Test Driver Routine */
void VLIB_convert_NV12_to_RGBpl_tile_d (uint8_t LevelOfFeedback)
{
    int32_t      tpi; /* test parameter index */
    sBuffer_t    yInData, cbcrInData;
    sBuffer_t    rgbOutData, rgbOutData_cn;
    uint8_t     *r_OutData;
    uint8_t     *g_OutData;
    uint8_t     *b_OutData;
    uint8_t     *r_OutData_cn;
    uint8_t     *g_OutData_cn;
    uint8_t     *b_OutData_cn;

    /* Test Parameters */
    VLIB_convert_NV12_to_RGBpl_tile_testParams_t   *prm;

    VLIB_convert_NV12_to_RGBpl_tile_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_convert_NV12_to_RGBpl_tile");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */

        /* Compute buffer sizes */
        uint32_t    y_inp_size      =  prm[tpi].pitch * prm[tpi].height;
        uint32_t    cbcr_inp_size   =  prm[tpi].pitch * prm[tpi].height >> 1;
        uint32_t    out_size        =  prm[tpi].pitch * prm[tpi].height;

        /* Allocate buffers for each test vector */
        int16_t   *coeff      = (int16_t *) VLIB_malloc(5 * sizeof(int16_t));

        yInData.data          = (uint8_t *) VLIB_memalign(8, y_inp_size * sizeof(uint8_t));
        yInData.rows          = prm[tpi].height;
        yInData.cols          = prm[tpi].width;
        yInData.pitch         = prm[tpi].pitch;

        cbcrInData.data       = (uint8_t *) VLIB_memalign(8, cbcr_inp_size * sizeof(uint8_t));
        cbcrInData.rows       = prm[tpi].height >> 1;
        cbcrInData.cols       = prm[tpi].width;
        cbcrInData.pitch      = prm[tpi].pitch;

        rgbOutData.data       = (uint8_t *) VLIB_memalign(8, out_size * 3 * sizeof(uint8_t));
        rgbOutData.rows       = prm[tpi].height;
        rgbOutData.cols       = prm[tpi].width;
        rgbOutData.pitch      = prm[tpi].pitch;

        rgbOutData_cn.data    = (uint8_t *) malloc(out_size * 3 * sizeof(uint8_t));
        rgbOutData_cn.rows    = prm[tpi].height;
        rgbOutData_cn.cols    = prm[tpi].width;
        rgbOutData_cn.pitch   = prm[tpi].pitch;

        r_OutData = (uint8_t *)rgbOutData.data;
        g_OutData = (uint8_t *)rgbOutData.data + (rgbOutData.rows * rgbOutData.pitch);
        b_OutData = (uint8_t *)rgbOutData.data + (rgbOutData.rows * rgbOutData.pitch << 1);

        r_OutData_cn = (uint8_t *)rgbOutData_cn.data;
        g_OutData_cn = (uint8_t *)rgbOutData_cn.data + (rgbOutData_cn.rows * rgbOutData_cn.pitch);
        b_OutData_cn = (uint8_t *)rgbOutData_cn.data + (rgbOutData_cn.rows * rgbOutData_cn.pitch << 1);

        /* Only run the test if the buffer allocations fit in the heap */
        if( yInData.data && cbcrInData.data && rgbOutData.data && rgbOutData_cn.data ) {
            int32_t    fail, i;

            /* Fill input Luma arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            yInData.data, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height,
                            (uint8_t)(prm[tpi].pitch * sizeof(uint8_t)),
                            sizeof(uint8_t), testPatternString);

            /* Fill input Chroma arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            cbcrInData.data, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height >> 1,
                            (uint8_t)(prm[tpi].pitch * sizeof(uint8_t)),
                            sizeof(uint8_t), testPatternString);

            for( i=0; i < 5; i++ ) {
                coeff[i] = prm[tpi].coeff[i];
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_convert_NV12_to_RGBpl_tile(&yInData, &cbcrInData, coeff, &rgbOutData);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_convert_NV12_to_RGBpl_tile_cn(&yInData, &cbcrInData, coeff, &rgbOutData_cn);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if( compare((void *) r_OutData, (void *)r_OutData_cn,
                        rgbOutData.cols, rgbOutData.rows, rgbOutData.pitch) == 1 ||
                compare((void *) g_OutData, (void *)g_OutData_cn,
                        rgbOutData.cols, rgbOutData.rows, rgbOutData.pitch) == 1 ||
                compare((void *) b_OutData, (void *)b_OutData_cn,
                        rgbOutData.cols, rgbOutData.rows, rgbOutData.pitch) == 1 ) {
                status_nat_vs_int = vlib_KERNEL_FAIL;
            } else {
                status_nat_vs_int = vlib_KERNEL_PASS;
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = (status_nat_vs_int == vlib_KERNEL_FAIL) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | width=%d, pitch=%d, height=%d, num_pts=%d",
                    testPatternString, prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_size);
            VLIB_formula_add_test(out_size, (int32_t) prm[tpi].height, (int32_t) NULL, fail, desc, (int32_t)NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, pitch=%d, height=%d, num_pts=%d",
                    prm[tpi].width, prm[tpi].pitch, prm[tpi].height, out_size * 3);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(coeff);
        free(rgbOutData_cn.data);
        VLIB_align_free(rgbOutData.data);
        VLIB_align_free(yInData.data);
        VLIB_align_free(cbcrInData.data);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = width * height; M=height",
                              "width * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

int main()
{
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_convert_NV12_to_RGBpl_tile");
    } else {
        VLIB_convert_NV12_to_RGBpl_tile_d(0);
    }
    return (0);
}

#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file: VLIB_convert_NV12_to_RGBpl_tile_d.c                        */
/* ======================================================================== */

