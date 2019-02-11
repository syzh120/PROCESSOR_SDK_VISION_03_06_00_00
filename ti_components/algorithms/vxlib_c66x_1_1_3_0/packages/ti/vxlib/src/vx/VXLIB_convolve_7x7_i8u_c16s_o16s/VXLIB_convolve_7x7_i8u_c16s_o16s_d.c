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

#include "VXLIB_convolve_7x7_i8u_c16s_o16s.h"
#include "VXLIB_convolve_7x7_i8u_c16s_o16s_cn.h"
#include "VXLIB_convolve_7x7_i8u_c16s_o16s_idat.h"

#define CONV_SIZE 7

/* VXLIB_convolve_7x7_i8u_c16s_o16s_d:  Test Driver Routine */
void VXLIB_convolve_7x7_i8u_c16s_o16s_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    convolve_7x7_i8u_c16s_o16s_testParams_t   *prm;

    convolve_7x7_i8u_c16s_o16s_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_convolve_7x7_i8u_c16s_o16s");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].stride_in * prm[tpi].height_in;
        uint32_t    out_size =   (prm[tpi].stride_out/2) * prm[tpi].height_out;
        uint32_t    valid_out_width  =   VXLIB_min(prm[tpi].width_out, prm[tpi].width_in-(CONV_SIZE-1));
        uint32_t    valid_out_height =   VXLIB_min(prm[tpi].height_out, prm[tpi].height_in-(CONV_SIZE-1));
        uint32_t    valid_out_img    =   valid_out_width * valid_out_height;

        /* Allocate buffers for each test vector */
        uint8_t   *src    =  (uint8_t *) TI_malloc(inp_size * sizeof(uint8_t));
        int16_t   *dst    =  (int16_t *) TI_malloc(out_size * sizeof(int16_t));
        int16_t   *dst_cn =  (int16_t *) malloc(out_size * sizeof(int16_t));
        int16_t   *conv_mat =  (int16_t *) TI_malloc((CONV_SIZE*CONV_SIZE) * sizeof(int16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( src && dst && dst_cn && conv_mat ) {

            int32_t                          fail, mode;
            VXLIB_bufParams2D_t    src_addr, dst_addr;
            uint32_t shift = prm[tpi].shift;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          src, prm[tpi].staticIn,
                          prm[tpi].width_in, prm[tpi].height_in, prm[tpi].stride_in,
                          sizeof(uint8_t), testPatternString);

            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          conv_mat, prm[tpi].staticConv,
                          CONV_SIZE, CONV_SIZE, CONV_SIZE*2,
                          sizeof(int16_t), testPatternString);

            /* Auto-calculate shift so that the output isn't all saturated  */
            if(prm[tpi].shift > 31) {
                int32_t i = 0;
                int32_t sum = 0;
                for(i=0; i<(CONV_SIZE*CONV_SIZE); i++) {
                    sum += conv_mat[i];
                }
                for(i=0; i<32; i++) {
                    if(sum < (1<<i)) {
                        break;
                    }
                }
                shift = i;
            }

            src_addr.dim_x = prm[tpi].width_in;
            src_addr.dim_y = prm[tpi].height_in;
            src_addr.stride_y = prm[tpi].stride_in;
            src_addr.data_type = VXLIB_UINT8;

            dst_addr.dim_x = prm[tpi].width_out;
            dst_addr.dim_y = prm[tpi].height_out;
            dst_addr.stride_y = prm[tpi].stride_out;
            dst_addr.data_type = VXLIB_INT16;

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_opt = VXLIB_convolve_7x7_i8u_c16s_o16s(src, &src_addr, dst, &dst_addr, conv_mat, shift);
            TI_profile_stop();

            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_convolve_7x7_i8u_c16s_o16s_cn(src, &src_addr, dst_cn, &dst_addr, conv_mat, shift);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_opt = TI_compare_mem_2D((void *) dst, (void *)dst_cn, 1, 65535, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = TI_compare_mem_2D((void *) prm[tpi].staticOut, (void *)dst_cn, 1, 65535, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = ( (prm[tpi].width_in == prm[tpi].width_out) &&
                     ((prm[tpi].stride_in*2) == prm[tpi].stride_out) &&
                     (prm[tpi].width_in == prm[tpi].stride_in)) ? 1 : 2;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | width_out=%d, height_out=%d, out size=%d, mode=%d, shift=%d",
                    testPatternString, valid_out_width, valid_out_height, valid_out_img, mode, shift);
            TI_profile_formula_add_test(valid_out_img, valid_out_height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width_out=%d, height_out=%d, buffer size=%d",
                    valid_out_width, valid_out_height, out_size);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        TI_free(conv_mat);
        free(dst_cn);
        TI_free(dst);
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
        TI_memError("VXLIB_convolve_7x7_i8u_c16s_o16s");
    } else {
        VXLIB_convolve_7x7_i8u_c16s_o16s_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_convolve_7x7_i8u_c16s_o16s_d.c                                      */
/* ======================================================================== */