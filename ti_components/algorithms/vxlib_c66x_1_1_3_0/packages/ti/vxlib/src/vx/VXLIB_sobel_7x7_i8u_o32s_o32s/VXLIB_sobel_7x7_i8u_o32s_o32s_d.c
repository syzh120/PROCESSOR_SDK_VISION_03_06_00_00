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
**|         Copyright (c) 2016 - 2017 Texas Instruments Incorporated         |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include "../../common/TI_test.h"
#include "../../common/TI_memory.h"
#include "../../common/TI_profile.h"

#include "VXLIB_sobel_7x7_i8u_o32s_o32s.h"
#include "VXLIB_sobel_7x7_i8u_o32s_o32s_cn.h"
#include "VXLIB_sobel_7x7_i8u_o32s_o32s_idat.h"

/* VXLIB_sobel_7x7_i8u_o32s_o32s_d:  Test Driver Routine */
void VXLIB_sobel_7x7_i8u_o32s_o32s_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    sobel_7x7_i8u_o32s_o32s_testParams_t   *prm;

    sobel_7x7_i8u_o32s_o32s_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_sobel_7x7_i8u_o32s_o32s");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt_x = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_opt_y = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref_x = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        int32_t         status_nat_vs_ref_y = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].stride_in * prm[tpi].height_in;
        uint32_t    out_size =   prm[tpi].stride_out/4 * prm[tpi].height_out;
        uint32_t    valid_out_width  =   VXLIB_min(prm[tpi].width_out, prm[tpi].width_in-6);
        uint32_t    valid_out_height =   VXLIB_min(prm[tpi].height_out, prm[tpi].height_in-6);
        uint32_t    valid_out_img    =   valid_out_width * valid_out_height;

        /* Allocate buffers for each test vector */
        uint8_t   *src      =  (uint8_t *) TI_malloc(inp_size * sizeof(uint8_t));
        int32_t   *dst_x    =  (int32_t *) TI_malloc(out_size * sizeof(int32_t));
        int32_t   *dst_y    =  (int32_t *) TI_malloc(out_size * sizeof(int32_t));
        int32_t   *dst_x_cn =  (int32_t *) malloc(out_size * sizeof(int32_t));
        int32_t   *dst_y_cn =  (int32_t *) malloc(out_size * sizeof(int32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( src && dst_x && dst_y && dst_x_cn && dst_y_cn ) {

            int32_t                          fail, mode;
            VXLIB_bufParams2D_t    src_addr, dst_addr_x, dst_addr_y;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          src, prm[tpi].staticIn,
                          prm[tpi].width_in, prm[tpi].height_in, prm[tpi].stride_in,
                          sizeof(uint8_t), testPatternString);

            src_addr.dim_x = prm[tpi].width_in;
            src_addr.dim_y = prm[tpi].height_in;
            src_addr.stride_y = prm[tpi].stride_in;
            src_addr.data_type = VXLIB_UINT8;

            dst_addr_x.dim_x = prm[tpi].width_out;
            dst_addr_x.dim_y = prm[tpi].height_out;
            dst_addr_x.stride_y = prm[tpi].stride_out;
            dst_addr_x.data_type = VXLIB_INT32;

            dst_addr_y.dim_x = prm[tpi].width_out;
            dst_addr_y.dim_y = prm[tpi].height_out;
            dst_addr_y.stride_y = prm[tpi].stride_out;
            dst_addr_y.data_type = VXLIB_INT32;

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_opt = VXLIB_sobel_7x7_i8u_o32s_o32s(src, &src_addr, dst_x, &dst_addr_x, dst_y, &dst_addr_y);
            TI_profile_stop();

            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_sobel_7x7_i8u_o32s_o32s_cn(src, &src_addr, dst_x_cn, &dst_addr_x, dst_y_cn, &dst_addr_y);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_opt_x = TI_compare_mem_2D((void *) dst_x, (void *)dst_x_cn, 0, 0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_x[0]));
            status_nat_vs_opt_y = TI_compare_mem_2D((void *) dst_y, (void *)dst_y_cn, 0, 0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_y[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutX != NULL ) {
                status_nat_vs_ref_x = TI_compare_mem_2D((void *) prm[tpi].staticOutX, (void *)dst_x_cn, 0, 0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_x[0]));
            }
            if( prm[tpi].staticOutY != NULL ) {
                status_nat_vs_ref_y = TI_compare_mem_2D((void *) prm[tpi].staticOutY, (void *)dst_y_cn, 0, 0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_y[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt_x == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_opt_y == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref_x == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref_y == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = ( (prm[tpi].width_in == prm[tpi].width_out) &&
                     (prm[tpi].stride_in*4 == prm[tpi].stride_out) &&
                     (prm[tpi].width_in == prm[tpi].stride_in)) ? 1 : 2;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | width_out=%d, height_out=%d, out size=%d, mode=%d",
                    testPatternString, valid_out_width, valid_out_height, valid_out_img, mode);
            TI_profile_formula_add_test(valid_out_img, valid_out_height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width_out=%d, height_out=%d, buffer size=%d",
                    valid_out_width, valid_out_height, out_size*sizeof(int32_t));
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(dst_y_cn);
        free(dst_x_cn);
        TI_free(dst_y);
        TI_free(dst_x);
        TI_free(src);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    TI_profile_setMode(1, 3, "widths == strides", 0); /* Mode 1 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = width_out * height_out; M = height_out",
                            "width_out * height_out");

    TI_profile_setMode(2, 3, "widths != strides", 1); /* Mode 2 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = width_out * height_out; M = height_out",
                            "width_out * height_out");

    /* Provide memory requirements */
    TI_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( TI_cache_init()) {
        TI_memError("VXLIB_sobel_7x7_i8u_o32s_o32s");
    } else {
        VXLIB_sobel_7x7_i8u_o32s_o32s_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_sobel_7x7_i8u_o32s_o32s_d.c                              */
/* ======================================================================== */
