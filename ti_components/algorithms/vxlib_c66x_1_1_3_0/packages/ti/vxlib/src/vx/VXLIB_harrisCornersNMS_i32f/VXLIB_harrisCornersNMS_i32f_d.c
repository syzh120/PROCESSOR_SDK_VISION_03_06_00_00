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

#include "VXLIB_harrisCornersNMS_i32f.h"
#include "VXLIB_harrisCornersNMS_i32f_cn.h"
#include "VXLIB_harrisCornersNMS_i32f_idat.h"

#include "../VXLIB_harrisCornersDetect_i32f/VXLIB_harrisCornersDetect_i32f_cn.h"

/* VXLIB_harrisCornersNMS_i32f_d:  Test Driver Routine */
void VXLIB_harrisCornersNMS_i32f_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    harrisCornersNMS_i32f_testParams_t   *prm;

    harrisCornersNMS_i32f_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_harrisCornersNMS_i32f");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Compute buffer sizes */
        uint32_t    inp_size =   prm[tpi].stride * prm[tpi].height;

        /* Allocate buffers for each test vector */
        VXLIB_F32  *src   =  (VXLIB_F32 *) TI_malloc(inp_size);
        uint32_t   num_corners;
        uint32_t   num_corners_out;
        uint32_t   num_corners_out_cn;
        int32_t    iterations    = 0;
        int32_t    iterations_cn = 0;
        uint32_t   *corners        =  (uint32_t *) TI_malloc(prm[tpi].corners_capacity * sizeof(uint32_t));
        VXLIB_F32   *strengths      =  (VXLIB_F32 *) TI_malloc(prm[tpi].corners_capacity * sizeof(VXLIB_F32));
        uint32_t   *corners_out    =  (uint32_t *) TI_malloc(prm[tpi].corners_capacity * sizeof(uint32_t));
        uint32_t   *corners_out_cn =  (uint32_t *) malloc(prm[tpi].corners_capacity * sizeof(uint32_t));
        VXLIB_F32   *strengths_out  =  (VXLIB_F32 *) TI_malloc(prm[tpi].corners_capacity * sizeof(VXLIB_F32));
        VXLIB_F32   *strengths_out_cn =  (VXLIB_F32 *) malloc(prm[tpi].corners_capacity * sizeof(VXLIB_F32));

        /* Only run the test if the buffer allocations fit in the heap */
        if( src && corners && strengths && corners_out && corners_out_cn && strengths_out && strengths_out_cn) {

            int32_t    i, fail;
            VXLIB_bufParams2D_t src_addr;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (int32_t)255,
                          src, prm[tpi].staticIn,
                          prm[tpi].width, prm[tpi].height, prm[tpi].stride,
                          sizeof(int32_t), testPatternString);

            if(prm[tpi].testPattern == RANDOM) {
                for(i=0; i<inp_size/4; i++) {
                    src[i] = (VXLIB_F32)_ftoi(src[i]);
                }
            }

            src_addr.dim_x = prm[tpi].width;
            src_addr.dim_y = prm[tpi].height;
            src_addr.stride_y = prm[tpi].stride;
            src_addr.data_type = VXLIB_FLOAT32;

            status_opt = VXLIB_harrisCornersDetect_i32f_cn(src, &src_addr, corners, strengths, prm[tpi].corners_capacity, &num_corners, prm[tpi].strength_thresh, 0, 0);

            {
                uint32_t   neighborhood_size = ((prm[tpi].min_distance+1.0f)*2)*((prm[tpi].min_distance+1.0f)*2)/9;
                uint32_t   scratch_size  = num_corners + 2*VXLIB_min(neighborhood_size, num_corners);
                int8_t     *scratch      =  (int8_t *) TI_malloc(scratch_size * sizeof(int8_t));

                /* Test optimized kernel */
                TI_profile_start(TI_PROFILE_KERNEL_OPT);num_corners_out=0;
                status_nat = VXLIB_harrisCornersNMS_i32f(corners, strengths, num_corners, corners_out, strengths_out, prm[tpi].corners_capacity, &num_corners_out, scratch, scratch_size, prm[tpi].min_distance, (uint8_t *)&iterations);
                TI_profile_stop();

                /* Test _cn kernel */
                TI_profile_start(TI_PROFILE_KERNEL_CN);
                status_nat = VXLIB_harrisCornersNMS_i32f_cn(corners, strengths, num_corners, corners_out_cn, strengths_out_cn, prm[tpi].corners_capacity, &num_corners_out_cn, scratch, scratch_size, prm[tpi].min_distance, (uint8_t *)&iterations_cn);
                TI_profile_stop();

                TI_free(scratch);
            }

            /* Compare natural C Output and Optimized Output */
            if( num_corners_out_cn == num_corners_out ) {
                status_nat_vs_opt = TI_compare_mem((void *) corners_out, (void *)corners_out_cn, num_corners_out * sizeof(uint32_t));
                if(status_nat_vs_opt == TI_TEST_KERNEL_PASS) {
                    status_nat_vs_opt = TI_compare_mem((void *) strengths_out, (void *)strengths_out_cn, num_corners_out * sizeof(VXLIB_F32));
                }
            } else {
                status_nat_vs_opt = TI_TEST_KERNEL_FAIL;
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticOut != NULL ) {
                status_nat_vs_ref = TI_compare_mem((void *) prm[tpi].staticOut, (void *)corners_out_cn, num_corners_out_cn * sizeof(uint32_t));
            }
            if( (status_nat_vs_ref == TI_TEST_KERNEL_PASS) && (prm[tpi].staticOutStr != NULL) ) {
                status_nat_vs_ref = TI_compare_mem((void *) prm[tpi].staticOutStr, (void *)strengths_out_cn, num_corners_out_cn * sizeof(uint8_t));
            }
            if( (status_nat_vs_ref == TI_TEST_KERNEL_PASS) && (prm[tpi].num_corners != NULL) ) {
                if( num_corners_out_cn == *prm[tpi].num_corners ) {
                    status_nat_vs_ref = TI_TEST_KERNEL_PASS;
                } else {
                    status_nat_vs_ref = TI_TEST_KERNEL_FAIL;
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | width=%d, height=%d, num_corners_in=%d, num_corners_out=%d, iterations=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height, num_corners, num_corners_out, iterations);
            TI_profile_formula_add_test(num_corners*iterations, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, buffer size=%d",
                    prm[tpi].width, prm[tpi].height, inp_size);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(strengths_out_cn);
        TI_free(strengths_out);
        free(corners_out_cn);
        TI_free(corners_out);
        TI_free(strengths);
        TI_free(corners);
        free(src);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    TI_profile_cycle_report(TI_PROFILE_RANGE,
                            NULL,
                            "num_corners_in*iterations");

    /* Provide memory requirements */
    TI_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( TI_cache_init()) {
        TI_memError("VXLIB_harrisCornersNMS_i32f");
    } else {
        VXLIB_harrisCornersNMS_i32f_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_harrisCornersNMS_i32f_d.c                                 */
/* ======================================================================== */
