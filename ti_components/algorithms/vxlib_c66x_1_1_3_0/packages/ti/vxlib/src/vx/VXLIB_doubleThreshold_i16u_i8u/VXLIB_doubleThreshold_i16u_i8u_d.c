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

#include "VXLIB_doubleThreshold_i16u_i8u.h"
#include "VXLIB_doubleThreshold_i16u_i8u_cn.h"
#include "VXLIB_doubleThreshold_i16u_i8u_idat.h"

/* VXLIB_doubleThreshold_i16u_i8u_d:  Test Driver Routine */
void VXLIB_doubleThreshold_i16u_i8u_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    doubleThreshold_i16u_i8u_testParams_t   *prm;

    doubleThreshold_i16u_i8u_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_doubleThreshold_i16u_i8u");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt      = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_opt_size = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_opt_list = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref = TI_TEST_KERNEL_PASS;      /* Test status : Natural c vs. Static Reference */
        int32_t         status_nat_vs_ref_size = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        int32_t         status_nat_vs_ref_list = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].stride_in * prm[tpi].height_in;
        uint32_t    out_size =   prm[tpi].stride_out * prm[tpi].height_out;
        uint32_t    valid_out_width  =   prm[tpi].width_out;
        uint32_t    valid_out_height =   prm[tpi].height_out;
        uint32_t    valid_out_img    =   valid_out_width * valid_out_height;
        uint32_t    edgeListCapacity =   out_size;
        uint32_t    numEdges;
        uint32_t    numEdges_cn;

        /* Allocate buffers for each test vector */
        uint16_t  *src_mag      =  (uint16_t *) TI_malloc(inp_size);
        uint8_t   *dst          =  (uint8_t *) TI_malloc(out_size);
        uint8_t   *dst_cn       =  (uint8_t *) malloc(out_size);
        uint32_t  *dstList      =  (uint32_t *) TI_malloc(edgeListCapacity*4);
        uint32_t  *dstList_cn   =  (uint32_t *) malloc(edgeListCapacity*4);

        /* Only run the test if the buffer allocations fit in the heap */
        if( src_mag && dst && dst_cn && dstList && dstList_cn) {

            int32_t               fail, mode, i;
            VXLIB_bufParams2D_t    src_mag_addr, dst_addr;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (int16_t)255,
                          src_mag, prm[tpi].staticInMag,
                          prm[tpi].width_in, prm[tpi].height_in, prm[tpi].stride_in,
                          sizeof(int16_t), testPatternString);

            /* Adjust for max value supported */
            for(i=0; i<(inp_size/2); i++) {
                if(src_mag[i] == 0xFFFF) {
                    src_mag[i] = 0xFFFE;
                }
            }

            /* Initialize in/out buffer */
            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          dst, prm[tpi].staticInEdge,
                          prm[tpi].width_out, prm[tpi].height_out, prm[tpi].stride_out,
                          sizeof(uint8_t), testPatternString);

            /* Correct to be either 0, or 127 values that are output from
             * non-max suppression stage */
            for(i=0; i<out_size; i++) {
                dst[i] = (dst[i] >= 127) ? 127 : 0;
            }

            /* Copy to natural c version of in/out buffer */
            for(i=0; i<out_size; i++) {
                dst_cn[i] = dst[i];
            }

            src_mag_addr.dim_x = prm[tpi].width_in;
            src_mag_addr.dim_y = prm[tpi].height_in;
            src_mag_addr.stride_y = prm[tpi].stride_in;
            src_mag_addr.data_type = VXLIB_UINT16;

            dst_addr.dim_x = prm[tpi].width_out;
            dst_addr.dim_y = prm[tpi].height_out;
            dst_addr.stride_y = prm[tpi].stride_out;
            dst_addr.data_type = VXLIB_UINT8;

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_opt = VXLIB_doubleThreshold_i16u_i8u(src_mag, &src_mag_addr, dst, &dst_addr, prm[tpi].stride_out, dstList, edgeListCapacity, &numEdges, 0, prm[tpi].loThreshold, prm[tpi].hiThreshold);
            TI_profile_stop();


            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_doubleThreshold_i16u_i8u_cn(src_mag, &src_mag_addr, dst_cn, &dst_addr, prm[tpi].stride_out, dstList_cn, edgeListCapacity, &numEdges_cn, 0, prm[tpi].loThreshold, prm[tpi].hiThreshold);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_opt = TI_compare_mem_2D((void *) dst, (void *)dst_cn, 0, 0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst[0]));
            status_nat_vs_opt_size = (numEdges == numEdges_cn) ? TI_TEST_KERNEL_PASS : TI_TEST_KERNEL_FAIL;
            if(status_nat_vs_opt_size == TI_TEST_KERNEL_PASS) {
                status_nat_vs_opt_list = TI_compare_mem_2D((void *) dstList, (void *)dstList_cn, 0, 0, numEdges, 1, numEdges*4, sizeof(dstList[0]));
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOutEdge != NULL ) {
                status_nat_vs_ref = TI_compare_mem_2D((void *) prm[tpi].staticOutEdge, (void *)dst_cn, 0, 0, valid_out_width, valid_out_height, prm[tpi].stride_out, sizeof(dst_cn[0]));
                status_nat_vs_ref_size = (prm[tpi].staticOutEdgeListNum == numEdges_cn) ? TI_TEST_KERNEL_PASS : TI_TEST_KERNEL_FAIL;
                if(status_nat_vs_ref_size == TI_TEST_KERNEL_PASS && prm[tpi].staticOutEdgeList != NULL) {
                    status_nat_vs_ref_list = TI_compare_mem_2D((void *) prm[tpi].staticOutEdgeList, (void *)dstList_cn, 0, 0, numEdges_cn, 1, numEdges_cn*4, sizeof(dstList_cn[0]));
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_opt_size == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_opt_list == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref_size == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref_list == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = ( (prm[tpi].width_in == prm[tpi].width_out) &&
                     (prm[tpi].stride_in == prm[tpi].stride_out*2) &&
                     (prm[tpi].width_in*2 == prm[tpi].stride_in)) ? 1 : 2;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | width_out=%d, height_out=%d, out size=%d, mode=%d",
                    testPatternString, prm[tpi].width_out, prm[tpi].height_out, valid_out_img, mode);
            TI_profile_formula_add_test(valid_out_img, valid_out_height, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width_out=%d, height_out=%d, buffer size=%d",
                    valid_out_width, valid_out_height, out_size);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(dstList_cn);
        TI_free(dstList);
        free(dst_cn);
        TI_free(dst);
        TI_free(src_mag);
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
        TI_memError("VXLIB_doubleThreshold_i16u_i8u");
    } else {
        VXLIB_doubleThreshold_i16u_i8u_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_doubleThreshold_i16u_i8u_d.c                     */
/* ======================================================================== */

