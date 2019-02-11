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

#include "VXLIB_harrisCornersScore_i32s_i32s_o32f.h"
#include "VXLIB_harrisCornersScore_i32s_i32s_o32f_cn.h"
#include "VXLIB_harrisCornersScore_i32s_i32s_o32f_idat.h"

/* VXLIB_harrisCornersScore_i32s_i32s_o32f_d:  Test Driver Routine */
void VXLIB_harrisCornersScore_i32s_i32s_o32f_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    harrisCornersScore_i32s_i32s_o32f_testParams_t   *prm;

    harrisCornersScore_i32s_i32s_o32f_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_harrisCornersScore_i32s_i32s_o32f");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Compute buffer sizes */
        uint8_t     gs = prm[tpi].gradient_size;
        uint8_t     bs = prm[tpi].block_size;
        uint32_t    inp_size =   prm[tpi].stride_in * prm[tpi].height_in;
        uint32_t    out_size =   prm[tpi].stride_out * prm[tpi].height_out;
        uint32_t    valid_out_width  =   VXLIB_min(prm[tpi].width_out, prm[tpi].width_in-(bs-1));
        uint32_t    valid_out_height =   VXLIB_min(prm[tpi].height_out, prm[tpi].height_in-(bs-1));
        uint32_t    valid_in_width   =   VXLIB_min(prm[tpi].width_out + (bs-1), prm[tpi].width_in);
        uint32_t    valid_in_height  =   VXLIB_min(prm[tpi].height_out + (bs-1), prm[tpi].height_in);
        uint32_t    valid_in_size    =   valid_in_width * valid_in_height;

        /* Allocate buffers for each test vector */
        int32_t   *src_x   =  (int32_t *) TI_malloc(inp_size);
        int32_t   *src_y   =  (int32_t *) TI_malloc(inp_size);
        VXLIB_F32  *dst     =  (VXLIB_F32 *) TI_malloc(out_size);
        VXLIB_F32  *dst_cn  =  (VXLIB_F32 *) malloc(out_size);
        VXLIB_F32  *scratch =  (VXLIB_F32 *) TI_malloc(prm[tpi].width_in*12*(bs+1));

        /* Only run the test if the buffer allocations fit in the heap */
        if( src_x && src_y && dst && dst_cn && scratch ) {

            int32_t               fail, mode;
            VXLIB_bufParams2D_t    src_x_addr, src_y_addr, dst_addr;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (int32_t)255,
                          src_x, prm[tpi].staticInX,
                          prm[tpi].width_in, prm[tpi].height_in, prm[tpi].stride_in,
                          sizeof(int32_t), testPatternString);

            TI_fillBuffer(prm[tpi].testPattern,
                          (int32_t)255,
                          src_y, prm[tpi].staticInY,
                          prm[tpi].width_in, prm[tpi].height_in, prm[tpi].stride_in,
                          sizeof(int32_t), testPatternString);

            src_x_addr.dim_x = prm[tpi].width_in;
            src_x_addr.dim_y = prm[tpi].height_in;
            src_x_addr.stride_y = prm[tpi].stride_in;
            src_x_addr.data_type = VXLIB_INT32;

            src_y_addr.dim_x = prm[tpi].width_in;
            src_y_addr.dim_y = prm[tpi].height_in;
            src_y_addr.stride_y = prm[tpi].stride_in;
            src_y_addr.data_type = VXLIB_INT32;

            dst_addr.dim_x = prm[tpi].width_out;
            dst_addr.dim_y = prm[tpi].height_out;
            dst_addr.stride_y = prm[tpi].stride_out;
            dst_addr.data_type = VXLIB_FLOAT32;

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_opt = VXLIB_harrisCornersScore_i32s_i32s_o32f(src_x, &src_x_addr, src_y, &src_y_addr, dst, &dst_addr, scratch, prm[tpi].sensitivity, gs, bs);
            TI_profile_stop();


            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_harrisCornersScore_i32s_i32s_o32f_cn(src_x, &src_x_addr, src_y, &src_y_addr, dst_cn, &dst_addr, scratch, prm[tpi].sensitivity, gs, bs);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_opt = TI_compare_mem_2D_float((void *) dst, (void *)dst_cn, 1.1, 2.0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = TI_compare_mem_2D_float((void *) prm[tpi].staticOut, (void *)dst_cn, 1.1, 2.0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = ( (prm[tpi].width_in == prm[tpi].width_out) &&
                     (prm[tpi].stride_in == prm[tpi].stride_out) &&
                     (prm[tpi].width_in*4 == prm[tpi].stride_in)) ? 1 : 2;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | width_in=%d, height_in=%d, in size=%d, mode=%d",
                    testPatternString, valid_in_width, valid_in_height, valid_in_size, mode);
            TI_profile_formula_add_test(valid_in_size, valid_in_height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width_out=%d, height_out=%d, buffer size=%d",
                    valid_out_width, valid_out_height, out_size);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        TI_free(scratch);
        free(dst_cn);
        TI_free(dst);
        TI_free(src_x);
        TI_free(src_y);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    TI_profile_setMode(1, 2, "widths == strides", 0); /* Mode 1 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = width_in * height_in; M = height_in",
                            "width_in * height_in");

    TI_profile_setMode(2, 3, "widths != strides", 1); /* Mode 2 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = width_in * height_in; M = height_in",
                            "width_in * height_in");

    /* Provide memory requirements */
    TI_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( TI_cache_init()) {
        TI_memError("VXLIB_harrisCornersScore_i32s_i32s_o32f");
    } else {
        VXLIB_harrisCornersScore_i32s_i32s_o32f_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_harrisCornersScore_i32s_i32s_o32f_d.c                     */
/* ======================================================================== */

