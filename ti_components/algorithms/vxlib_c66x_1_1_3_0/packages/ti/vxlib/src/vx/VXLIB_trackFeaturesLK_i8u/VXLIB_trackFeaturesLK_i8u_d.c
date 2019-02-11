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

#include "VXLIB_trackFeaturesLK_i8u.h"
#include "VXLIB_trackFeaturesLK_i8u_cn.h"
#include "VXLIB_trackFeaturesLK_i8u_idat.h"

#include "../VXLIB_scharr_3x3_i8u_o16s_o16s/VXLIB_scharr_3x3_i8u_o16s_o16s_cn.h"

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

/* ////////////////////////////////////////// */
/* Warps a w * h custom pattern               */
/* ////////////////////////////////////////// */
static void CreatePattern2(uint8_t *p, int16_t w, int16_t h)
{
    int32_t    i;

    for( i = 0; i < w * h; i++ ) {
        VXLIB_F32    x = i % w;
        VXLIB_F32    y = i / w;

        int32_t    x1 = x - 1;
        int32_t    y1 = y - 1;

        p[i] = (x1 | y1) / 2 + 127;
    }
}

/* VXLIB_trackFeaturesLK_i8u_d:  Test Driver Routine */
void VXLIB_trackFeaturesLK_i8u_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    trackFeaturesLK_i8u_testParams_t   *prm;

    trackFeaturesLK_i8u_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(3, "VXLIB_trackFeaturesLK_i8u");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t         status_nat_vs_opt = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t         status_nat_vs_ref = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Allocate buffers for each test vector */
        uint8_t   *old_image           =  (uint8_t *) TI_malloc(prm[tpi].stride * prm[tpi].height);
        uint8_t   *new_image           =  (uint8_t *) TI_malloc(prm[tpi].stride * prm[tpi].height);
        int16_t   *gradX               =  (int16_t *) TI_malloc(prm[tpi].stride*2 * prm[tpi].height * sizeof(int16_t));
        int16_t   *gradY               =  (int16_t *) TI_malloc(prm[tpi].stride*2 * prm[tpi].height * sizeof(int16_t));

        __float2_t  *old_points         =  (__float2_t *) TI_malloc(prm[tpi].num_points * sizeof(__float2_t));
        __float2_t  *new_points         =  (__float2_t *) TI_malloc(prm[tpi].num_points * sizeof(__float2_t));
        __float2_t  *new_points_cn      =  (__float2_t *) malloc(prm[tpi].num_points * sizeof(__float2_t));
        uint8_t    *tracking_status    = (uint8_t *) TI_malloc(prm[tpi].num_points * sizeof(uint8_t));
        uint8_t    *tracking_status_cn = (uint8_t *) malloc(prm[tpi].num_points * sizeof(uint8_t));

        /* scratch buffer required :
         *    optimized = window_size*window_size*6 + 2 bytes.
         *    natural c = window_size*window_size*8
         */
        uint32_t   scratch_size = prm[tpi].window_size*prm[tpi].window_size*8 + 2;
        uint8_t    *scratch  = (uint8_t *) TI_malloc(scratch_size);

        /* Only run the test if the buffer allocations fit in the heap */
        if( old_image && new_image && gradX && gradY && old_points && new_points && new_points_cn && tracking_status && tracking_status_cn && scratch ) {

            int32_t    fail, i, mode;
            VXLIB_bufParams2D_t old_addr, new_addr, gradX_addr, gradY_addr;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          old_image, prm[tpi].staticInOld,
                          prm[tpi].width, prm[tpi].height, prm[tpi].stride,
                          sizeof(uint8_t), testPatternString);

            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          new_image, prm[tpi].staticInNew,
                          prm[tpi].width, prm[tpi].height, prm[tpi].stride,
                          sizeof(uint8_t), testPatternString);

            if( prm[tpi].testPattern == CUSTOM ) {
                /* Synthetic motion sequence */
                CreatePattern1(old_image, prm[tpi].width, prm[tpi].height);
                CreatePattern2(new_image, prm[tpi].width, prm[tpi].height);
            }

            /* Fill the feature points */
            for( i = 0; i < prm[tpi].num_points; i++ ) {
                if( prm[tpi].staticOldPoints ) {
                    __float2_t *ptr = (__float2_t *)&prm[tpi].staticOldPoints[i*2];
                    old_points[i] = ptr[0];
                } else {
                    old_points[i] = _ftof2((VXLIB_F32)i, (VXLIB_F32)i);
                }
            }

            /* Initial guesses for the feature points */
            for( i = 0; i < prm[tpi].num_points; i++ ) {
                if( prm[tpi].staticEstPoints ) {
                    __float2_t *ptr = (__float2_t *)&prm[tpi].staticEstPoints[i*2];
                    new_points[i] = new_points_cn[i] = ptr[0];
                } else {
                    new_points[i] = new_points_cn[i] = old_points[i];
                }
            }

            /* Initialize status for the features points */
            for( i = 0; i < prm[tpi].num_points; i++ ) {
                if( prm[tpi].staticOldStatus ) {
                    tracking_status[i] = tracking_status_cn[i] = prm[tpi].staticOldStatus[i];
                } else {
                    tracking_status[i] = tracking_status_cn[i] = 1;
                }
            }

            old_addr.dim_x = prm[tpi].width;
            old_addr.dim_y = prm[tpi].height;
            old_addr.stride_y = prm[tpi].stride;
            old_addr.data_type = VXLIB_UINT8;

            new_addr.dim_x = prm[tpi].width;
            new_addr.dim_y = prm[tpi].height;
            new_addr.stride_y = prm[tpi].stride;
            new_addr.data_type = VXLIB_UINT8;

            gradX_addr.dim_x = prm[tpi].width;
            gradX_addr.dim_y = prm[tpi].height-2;
            gradX_addr.stride_y = prm[tpi].stride*2;
            gradX_addr.data_type = VXLIB_INT16;

            gradY_addr.dim_x = prm[tpi].width;
            gradY_addr.dim_y = prm[tpi].height-2;
            gradY_addr.stride_y = prm[tpi].stride*2;
            gradY_addr.data_type = VXLIB_INT16;

            /* Clear the gradient buffers since the first and last part are not set by the gradient function */
            memset(gradX, 0, prm[tpi].stride*2 * prm[tpi].height * sizeof(int16_t));
            memset(gradY, 0, prm[tpi].stride*2 * prm[tpi].height * sizeof(int16_t));

            /* Compute the gradient using the library function */
            /* The natC version of this vlib function is used so that the code size doesn't get counted in this test */
            status_nat = VXLIB_scharr_3x3_i8u_o16s_o16s_cn(old_image, &old_addr,
                                                           gradX + prm[tpi].stride/2 + 1, &gradX_addr,
                                                           gradY + prm[tpi].stride/2 + 1, &gradY_addr);

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_nat = VXLIB_trackFeaturesLK_i8u(old_image, &old_addr, new_image, &new_addr, gradX, &gradX_addr, gradY, &gradY_addr,
                                                            old_points, new_points, tracking_status, prm[tpi].num_points, prm[tpi].max_iters, prm[tpi].epsilon,
                                                            prm[tpi].scale, prm[tpi].window_size, prm[tpi].level, prm[tpi].termination, scratch, scratch_size);
            TI_profile_stop();

            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_trackFeaturesLK_i8u_cn(old_image, &old_addr, new_image, &new_addr, gradX, &gradX_addr, gradY, &gradY_addr,
                                                               old_points, new_points_cn, tracking_status_cn, prm[tpi].num_points, prm[tpi].max_iters, prm[tpi].epsilon,
                                                               prm[tpi].scale, prm[tpi].window_size, prm[tpi].level, prm[tpi].termination, scratch, scratch_size);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_opt = TI_compare_mem_2D_float((void *) new_points, (void *)new_points_cn, 0, 1.0, prm[tpi].num_points * 2, 1, 1, sizeof(VXLIB_F32));
            if(status_nat_vs_opt == TI_TEST_KERNEL_PASS) {
                status_nat_vs_opt = TI_compare_mem((void *) tracking_status, (void *)tracking_status_cn, prm[tpi].num_points);
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].staticNewPoints != NULL ) {
                status_nat_vs_ref = TI_compare_mem_2D_float((void *) prm[tpi].staticNewPoints, (void *)new_points_cn, 0, 1.0, prm[tpi].num_points * 2, 1, 1, sizeof(VXLIB_F32));
            }
            if( (status_nat_vs_ref == TI_TEST_KERNEL_PASS) && (prm[tpi].staticNewStatus != NULL) ) {
                status_nat_vs_ref = TI_compare_mem((void *) prm[tpi].staticNewStatus, (void *)tracking_status_cn, prm[tpi].num_points);
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = (prm[tpi].window_size == 5) ? 1 : (prm[tpi].window_size == 7) ? 2 : 3;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | num_points=%d, max_iters=%d, window_size=%d, epsilon=%f",\
                    testPatternString, prm[tpi].num_points, prm[tpi].max_iters, prm[tpi].window_size,
                    prm[tpi].epsilon);
            TI_profile_formula_add_test(prm[tpi].max_iters*prm[tpi].num_points, prm[tpi].num_points, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, buffer size=%d",
                    prm[tpi].width, prm[tpi].height, prm[tpi].stride * prm[tpi].height * 10 + 9*prm[tpi].num_points);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        TI_free(scratch);
        free(tracking_status_cn);
        TI_free(tracking_status);
        free(new_points_cn);
        TI_free(new_points);
        TI_free(old_points);
        TI_free(gradY);
        TI_free(gradX);
        TI_free(new_image);
        TI_free(old_image);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    TI_profile_setMode(1, 3, "Window Size = 5x5", 0); /* Mode 1 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                            "N = num_points * max_iters; M = num_points",
                             "num_points * max_iters");

    TI_profile_setMode(2, 3, "Window Size = 7x7", 0); /* Mode 2 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                              "N = num_points * max_iters; M = num_points",
                              "nfeatures * max_iters");

    TI_profile_setMode(3, 3, "Window Size = 9x9", 1); /* Mode 3 */
    TI_profile_cycle_report(TI_PROFILE_FORMULA_RANGE,
                              "N = num_points * max_iters; M = num_points",
                              "nfeatures * max_iters");

    /* Provide memory requirements */
    TI_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( TI_cache_init()) {
        TI_memError("VXLIB_trackFeaturesLK_i8u");
    } else {
        VXLIB_trackFeaturesLK_i8u_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_trackFeaturesLK_i8u_d.c                                 */
/* ======================================================================== */
