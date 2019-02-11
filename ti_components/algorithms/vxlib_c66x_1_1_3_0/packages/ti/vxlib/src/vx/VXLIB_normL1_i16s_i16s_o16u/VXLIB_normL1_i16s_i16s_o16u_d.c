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

#include "VXLIB_normL1_i16s_i16s_o16u.h"
#include "VXLIB_normL1_i16s_i16s_o16u_cn.h"
#include "VXLIB_normL1_i16s_i16s_o16u_idat.h"

/* VXLIB_normL1_i16s_i16s_o16u_d:  Test Driver Routine */
void VXLIB_normL1_i16s_i16s_o16u_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    normL1_i16s_i16s_o16u_testParams_t   *prm;

    normL1_i16s_i16s_o16u_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_normL1_i16s_i16s_o16u");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].stride * prm[tpi].height;
        uint32_t    img_size =   prm[tpi].width * prm[tpi].height;

        /* Allocate buffers for each test vector */
        int16_t   *src_x   =  (int16_t *) TI_malloc(inp_size);
        int16_t   *src_y   =  (int16_t *) TI_malloc(inp_size);
        uint16_t  *dst     =  (uint16_t *) TI_malloc(inp_size);
        uint16_t  *dst_cn  =  (uint16_t *) malloc(inp_size);

        /* Only run the test if the buffer allocations fit in the heap */
        if( src_x && src_y && dst && dst_cn ) {

            int32_t                          fail, mode;
            VXLIB_bufParams2D_t    src_x_addr, src_y_addr, dst_addr;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          src_x, prm[tpi].staticIn0,
                          prm[tpi].width, prm[tpi].height, prm[tpi].stride,
                          sizeof(int16_t), testPatternString);

            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          src_y, prm[tpi].staticIn1,
                          prm[tpi].width, prm[tpi].height, prm[tpi].stride,
                          sizeof(int16_t), testPatternString);

            src_x_addr.dim_x = prm[tpi].width;
            src_x_addr.dim_y = prm[tpi].height;
            src_x_addr.stride_y = prm[tpi].stride;
            src_x_addr.data_type = VXLIB_INT16;

            src_y_addr.dim_x = prm[tpi].width;
            src_y_addr.dim_y = prm[tpi].height;
            src_y_addr.stride_y = prm[tpi].stride;
            src_y_addr.data_type = VXLIB_INT16;

            dst_addr.dim_x = prm[tpi].width;
            dst_addr.dim_y = prm[tpi].height;
            dst_addr.stride_y = prm[tpi].stride;
            dst_addr.data_type = VXLIB_UINT16;

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_opt = VXLIB_normL1_i16s_i16s_o16u(src_x, &src_x_addr, src_y, &src_y_addr, dst, &dst_addr);
            TI_profile_stop();


            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_normL1_i16s_i16s_o16u_cn(src_x, &src_x_addr, src_y, &src_y_addr, dst_cn, &dst_addr);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_opt = TI_compare_mem_2D((void *) dst, (void *)dst_cn, 1, 0, prm[tpi].width, prm[tpi].height, prm[tpi].stride, sizeof(dst[0]));

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = TI_compare_mem_2D((void *) prm[tpi].staticOut, (void *)dst_cn, 0, 0, prm[tpi].width, prm[tpi].height, prm[tpi].stride, sizeof(dst_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = (2 * prm[tpi].width == prm[tpi].stride) ? 1 : 2;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | width=%d, height=%d, out size=%d, mode=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height, img_size, mode);
            TI_profile_formula_add_test(img_size, prm[tpi].height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, buffer size=%d",
                    prm[tpi].width, prm[tpi].height, inp_size);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(dst_cn);
        TI_free(dst);
        TI_free(src_x);
        TI_free(src_y);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    TI_profile_setMode(1, 2, "width == stride", 0); /* Mode 1 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = width * height",
                            "width * height");

    TI_profile_setMode(2, 3, "width < stride", 1); /* Mode 2 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = width * height; M = height",
                            "width * height");

    /* Provide memory requirements */
    TI_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( TI_cache_init()) {
        TI_memError("VXLIB_normL1_i16s_i16s_o16u");
    } else {
        VXLIB_normL1_i16s_i16s_o16u_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_normL1_i16s_i16s_o16u_d.c                           */
/* ======================================================================== */

