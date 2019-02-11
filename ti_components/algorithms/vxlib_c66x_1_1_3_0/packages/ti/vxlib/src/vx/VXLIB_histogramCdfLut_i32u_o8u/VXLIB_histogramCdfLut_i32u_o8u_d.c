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

#define USE_NATC_HISTSIMPLE

#include "../../common/TI_test.h"
#include "../../common/TI_memory.h"
#include "../../common/TI_profile.h"

#include "VXLIB_histogramCdfLut_i32u_o8u.h"
#include "VXLIB_histogramCdfLut_i32u_o8u_cn.h"
#include "VXLIB_histogramCdfLut_i32u_o8u_idat.h"

#ifdef USE_NATC_HISTSIMPLE
#include "../VXLIB_histogramSimple_i8u_o32u/VXLIB_histogramSimple_i8u_o32u_cn.h"
#else
#include "../VXLIB_histogramSimple_i8u_o32u/c66/VXLIB_histogramSimple_i8u_o32u.h"
#endif

/* VXLIB_histogramCdfLut_i32u_o8u_d:  Test Driver Routine */
void VXLIB_histogramCdfLut_i32u_o8u_d(uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    histogramCdfLut_i32u_o8u_testParams_t   *prm;

    histogramCdfLut_i32u_o8u_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    TI_profile_init(2, "VXLIB_histogramCdfLut_i32u_o8u");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t        status_nat_vs_opt_cdf = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t        status_nat_vs_opt_dst = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t        status_nat_vs_ref_cdf = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        int32_t        status_nat_vs_ref_dst = TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        VXLIB_STATUS    status_opt = VXLIB_SUCCESS;
        VXLIB_STATUS    status_nat = VXLIB_SUCCESS;

        /* Allocate buffers for each test vector */
        uint8_t   *img       =  (uint8_t *) malloc(prm[tpi].numPixels * sizeof(uint8_t));
        uint32_t  *scratch   =  (uint32_t *) malloc(1024 * sizeof(uint32_t));
        uint32_t  *src       =  (uint32_t *) TI_malloc(256 * sizeof(uint32_t));
        uint32_t  *cdf_cn    =  (uint32_t *) malloc(256 * sizeof(uint32_t));
        uint8_t   *dst_cn    =  (uint8_t *) malloc(256 * sizeof(uint8_t));

        uint32_t  *cdf = NULL;
        uint8_t   *dst = NULL;

        if((prm[tpi].mode & 1) == 1) {
            cdf       =  (uint32_t *) TI_malloc(256 * sizeof(uint32_t));
        }

        if((prm[tpi].mode & 2) == 2) {
            dst       =  (uint8_t *) TI_malloc(256 * sizeof(uint8_t));
        }

        /* Only run the test if the buffer allocations fit in the heap */
        if( img && scratch && src && cdf_cn && dst_cn &&
            (   ((prm[tpi].mode & 1) == 0) ||
                ((prm[tpi].mode & 1) == 1 && cdf)   ) &&
            (   ((prm[tpi].mode & 2) == 0) ||
                ((prm[tpi].mode & 2) == 2 && dst)   )
        ) {

            int32_t                          fail, mode;
            VXLIB_bufParams2D_t    src_addr;
            uint32_t minv = 0xffffffff;

            /* Fill input arrays according to desired test pattern */
            TI_fillBuffer(prm[tpi].testPattern,
                          (uint8_t)255,
                          img, prm[tpi].staticIn,
                          prm[tpi].numPixels, 1, prm[tpi].numPixels,
                          sizeof(uint8_t), testPatternString);

#ifdef USE_NATC_HISTSIMPLE
            /* src should be cleared if we are using natural c version of VXLIB_histogramSimple_i8u_o32u_cn */
            memset(src, 0, 256 * sizeof(uint32_t));
#else
            /* Scratch should be cleared if we are using optimized version of VXLIB_histogramSimple_i8u_o32u */
            memset(scratch, 0, 1024 * sizeof(uint32_t));
#endif

            src_addr.dim_x = prm[tpi].numPixels;
            src_addr.dim_y = 1;
            src_addr.stride_y = prm[tpi].numPixels;
            src_addr.data_type = VXLIB_UINT8;

#ifdef USE_NATC_HISTSIMPLE
            VXLIB_histogramSimple_i8u_o32u_cn(img, &src_addr, src, scratch, &minv);
#else
            VXLIB_histogramSimple_i8u_o32u(img, &src_addr, src, scratch, &minv, 1);
#endif

            /* Test optimized kernel */
            TI_profile_start(TI_PROFILE_KERNEL_OPT);
            status_opt = VXLIB_histogramCdfLut_i32u_o8u(src, cdf, dst, prm[tpi].numPixels, minv);
            TI_profile_stop();

            /* Test _cn kernel */
            TI_profile_start(TI_PROFILE_KERNEL_CN);
            status_nat = VXLIB_histogramCdfLut_i32u_o8u_cn(src, cdf_cn, dst_cn, prm[tpi].numPixels, minv);
            TI_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if(cdf) {
                status_nat_vs_opt_cdf = TI_compare_mem((void *) cdf, (void *)cdf_cn, 256 * sizeof(cdf[0]));
            }
            if(dst) {
                status_nat_vs_opt_dst = TI_compare_mem_2D((void *)dst, (void *)dst_cn, 1, 0, 256 * sizeof(dst[0]), 1, 256 * sizeof(dst[0]), sizeof(dst[0]));
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( (prm[tpi].staticOutCdf != NULL) && (cdf_cn != NULL)) {
                status_nat_vs_ref_cdf = TI_compare_mem((void *) prm[tpi].staticOutCdf, (void *)cdf_cn, 256 * sizeof(cdf_cn[0]));
            }
            if( (prm[tpi].staticOut != NULL) && (dst_cn != NULL)) {
                status_nat_vs_ref_dst = TI_compare_mem_2D((void *)prm[tpi].staticOut, (void *)dst_cn, 1, 0, 256 * sizeof(dst[0]), 1, 256 * sizeof(dst[0]), sizeof(dst_cn[0]));
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_opt_cdf == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_opt_dst == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref_cdf == TI_TEST_KERNEL_FAIL) ||
                    (status_nat_vs_ref_dst == TI_TEST_KERNEL_FAIL) ||
                    (status_opt != VXLIB_SUCCESS) ||
                    (status_nat != VXLIB_SUCCESS)) ? 1 : 0;

            est_test=1;

            mode = prm[tpi].mode;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | numPixels=%d, mode=%d",
                    testPatternString, prm[tpi].numPixels, mode);
            TI_profile_formula_add_test(256, NULL, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numPixels=%d",
                    prm[tpi].numPixels);
            TI_profile_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(dst_cn);
        TI_free(dst);
        free(cdf_cn);
        TI_free(cdf);
        TI_free(src);
        free(scratch);
        free(img);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    TI_profile_setMode(1, 2, "generate cdf output only", 0); /* Mode 1 */
    TI_profile_cycle_report(TI_PROFILE_RANGE,
                            NULL,
                            "256");

    TI_profile_setMode(2, 2, "generate lut output only", 0); /* Mode 2 */
    TI_profile_cycle_report(TI_PROFILE_RANGE,
                            NULL,
                            "256");

    TI_profile_setMode(3, 2, "generate cdf and lut outputs", 1); /* Mode 3 */
    TI_profile_cycle_report(TI_PROFILE_RANGE,
                            NULL,
                            "256");

    /* Provide memory requirements */
    TI_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( TI_cache_init()) {
        TI_memError("VXLIB_histogramCdfLut_i32u_o8u");
    } else {
        VXLIB_histogramCdfLut_i32u_o8u_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VXLIB_histogramCdfLut_i32u_o8u_d.c                                        */
/* ======================================================================== */

