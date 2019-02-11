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
**|         Copyright (c) 2015 Texas Instruments Incorporated                |**
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
#include "float.h"

#include "VLIB_matchTemplate.h"
#include "VLIB_matchTemplate_cn.h"
#include "VLIB_matchTemplate_idat.h"

/* VLIB_matchTemplate_d:  Test Driver Routine */
void VLIB_matchTemplate_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    matchTemplate_testParams_t   *prm;

    matchTemplate_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_matchTemplate");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        int32_t    status_int        = vlib_KERNEL_PASS; /* Test status : Optimized return code */
        int32_t    status_nat        = vlib_KERNEL_PASS; /* Test status : Natural return code */

        int32_t    orgImgWidth          = prm[tpi].orgImgWidth;
        int32_t    orgImgHeight         = prm[tpi].orgImgHeight;
        int32_t    orgImgPitch          = prm[tpi].orgImgPitch;

        int32_t    tempImgWidth         = prm[tpi].tempImgWidth;
        int32_t    tempImgHeight        = prm[tpi].tempImgHeight;
        int32_t    tempImgPitch         = prm[tpi].tempImgPitch;

        int32_t    outScorePitch        = prm[tpi].outScorePitch;
        int32_t    outScoreWidth        = prm[tpi].orgImgWidth - (prm[tpi].tempImgWidth - 1);
        int32_t    outScoreHeight       = prm[tpi].orgImgHeight - (prm[tpi].tempImgHeight - 1);


        /* Allocate buffers for each test vector */
        uint8_t    *orgImg     = VLIB_malloc(orgImgPitch * orgImgHeight);
        uint8_t    *tempImgU08 = VLIB_malloc(tempImgPitch * tempImgHeight);
        int16_t    *tempImg    = VLIB_malloc(tempImgPitch * tempImgHeight * sizeof(int16_t));
        VLIB_F32   *outScore   = VLIB_malloc(outScorePitch * outScoreHeight * sizeof(VLIB_F32));
        VLIB_F32   *outScore_cn= malloc(outScorePitch * outScoreHeight * sizeof(VLIB_F32));
        uint8_t    *scratch1   = VLIB_malloc(((outScoreWidth * (outScoreHeight * 10)) + 20) * sizeof(uint16_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( orgImg && tempImgU08 && tempImg && outScore && scratch1 && outScore_cn ) {

            int32_t     fail;
            int32_t     i, j, tempImgAvg;
            int32_t     tempImgVar;
            VLIB_F32    tempImgVarF;
            int32_t     mode;


            VLIB_fillBuffer(prm[tpi].testPattern, 0xFF, orgImg, prm[tpi].orgImg,
                            orgImgWidth, orgImgHeight, orgImgPitch * sizeof(uint8_t),
                            sizeof(uint8_t),
                            testPatternString);

            VLIB_fillBuffer(prm[tpi].testPattern, 0xFF, tempImgU08, prm[tpi].tempImg,
                            tempImgWidth, tempImgHeight, tempImgPitch * sizeof(uint8_t),
                            sizeof(uint8_t),
                            testPatternString);


            tempImgAvg = 0;

            for( i = 0; i < tempImgHeight; i++ ) {
                for( j = 0; j < tempImgWidth; j++ ) {
                    tempImgAvg += tempImgU08[(tempImgPitch * i) + j];
                }
            }

            /*tempImgAvg in Q2 format. Totally maximum 16 bit*/
            tempImgAvg = (tempImgAvg * 4) / (tempImgWidth * tempImgHeight);

            tempImgVar = 0;

            for( i = 0; i < tempImgHeight; i++ ) {
                for( j = 0; j < tempImgWidth; j++ ) {

                    /*Q2 format. 1 bit sign + 13 bit Integer + 2 bit fraction*/
                    tempImg[(i * tempImgPitch) + j] = (tempImgU08[(i * tempImgPitch) + j] * 4) - tempImgAvg;

                    /* Q2*Q2 = Q4 format. 1 bit sign + 11 bit Integer + 4 bit fraction*/
                    tempImgVar += ((tempImgU08[(i * tempImgPitch) + j] * 4 - tempImgAvg) * (tempImgU08[(i * tempImgPitch) + j] * 4 - tempImgAvg));
                }
            }

            tempImgVarF = (1.0f / sqrt(((VLIB_F32)tempImgVar) / (4.0 * 4.0)));

            if( tempImgVar <= FLT_MIN ) {
                tempImgVarF = FLT_MAX;
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            status_int = VLIB_matchTemplate(orgImg,
                                            orgImgWidth,
                                            orgImgHeight,
                                            orgImgPitch,
                                            tempImg,
                                            tempImgWidth,
                                            tempImgHeight,
                                            tempImgPitch,
                                            tempImgVarF,
                                            prm[tpi].xDirJump,
                                            prm[tpi].yDirJump,
                                            0x0,
                                            outScorePitch,
                                            outScore,
                                            scratch1);
            VLIB_profile_stop();
            status_int = (status_int == 1) ? vlib_KERNEL_FAIL : vlib_KERNEL_PASS;

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            status_nat = VLIB_matchTemplate_cn(orgImg,
                                               orgImgWidth,
                                               orgImgHeight,
                                               orgImgPitch,
                                               tempImg,
                                               tempImgWidth,
                                               tempImgHeight,
                                               tempImgPitch,
                                               tempImgVarF,
                                               prm[tpi].xDirJump,
                                               prm[tpi].yDirJump,
                                               0x0,
                                               outScorePitch,
                                               outScore_cn,
                                               NULL);
            VLIB_profile_stop();
            status_nat = (status_nat == 1) ? vlib_KERNEL_FAIL : vlib_KERNEL_PASS;

            /* Compare natural C Output and Optimized Output */

            if((status_int == vlib_KERNEL_PASS) && (status_int == vlib_KERNEL_PASS)) {
                for( i = 0; i < outScoreHeight; i+=prm[tpi].yDirJump ) {
                    for( j = 0; j < outScoreWidth; j+=prm[tpi].xDirJump ) {
                        if( outScore_cn[(i * outScorePitch) + j] != outScore[(i * outScorePitch) + j] ) {
                            status_nat_vs_int = vlib_KERNEL_FAIL;
                            if( LevelOfFeedback > 0 ) {
                                printf(" Mismatch With Reference at location (%u,%u) \n", i, j);
                            }
                            break;
                        }
                    }
                }

                /* If static output is available, then additionally compares natural C output with static reference output data */
                if( prm[tpi].outScore != NULL ) {
                    for( i = 0; i < outScoreHeight; i+= prm[tpi].yDirJump ) {
                        for( j = 0; j < outScoreWidth; j+= prm[tpi].xDirJump ) {
                            if( outScore_cn[(i * outScorePitch) + j] != prm[tpi].outScore[(i * outScorePitch) + j] ) {
                                status_nat_vs_int = vlib_KERNEL_FAIL;
                                if( LevelOfFeedback > 0 ) {
                                    printf(" Mismatch With Static Reference at location (%u,%u) \n", i, j);
                                }
                                break;
                            }
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) ||
                    (status_nat_vs_ref == vlib_KERNEL_FAIL) ||
                    (status_int == vlib_KERNEL_FAIL) ||
                    (status_nat == vlib_KERNEL_FAIL)) ? 1 : 0;

            if( tempImgWidth * tempImgHeight > 2048 ) {
                mode = 5;
            } else {
                if((((uint32_t)tempImg & 0x7U) == 0x0) &&
                   ((tempImgPitch & 0x3U) == 0x0) &&
                   (((uint32_t)orgImg & 0x3U) == NULL) &&
                   ((orgImgPitch & 0x3U) == NULL)) {
                    if( tempImgWidth == 24 ) {
                        mode = 1;
                    } else if( tempImgWidth == 32 ) {
                        mode = 2;
                    } else {
                        mode = 3;
                    }
                } else {
                    mode = 4;
                }
            }

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | numOutPixels=%d | %s, mode = %d",\
                    testPatternString, ((outScoreWidth / prm[tpi].xDirJump) * (outScoreHeight / prm[tpi].yDirJump) * tempImgWidth * tempImgHeight), prm[tpi].desc, mode);

            VLIB_formula_add_test(((outScoreWidth / prm[tpi].xDirJump) * (outScoreHeight / prm[tpi].yDirJump) * tempImgWidth * tempImgHeight), NULL, NULL, fail, desc, mode);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numOutPixels=%d", outScoreWidth * outScoreHeight);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(orgImg);
        VLIB_free(tempImgU08);
        VLIB_free(tempImg);
        VLIB_free(outScore);
        VLIB_free(scratch1);

        free(outScore_cn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 2, "template size <= 2048, ptr and pitch aligned, tempImgWidth == 24", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = outScoreWidth * outScoreHeight",
                              "outScoreWidth * outScoreHeight");

    VLIB_profile_setMode(2, 2, "template size <= 2048, ptr and pitch aligned, tempImgWidth == 32", 0); /* Mode 2 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = outScoreWidth * outScoreHeight",
                              "outScoreWidth * outScoreHeight");

    VLIB_profile_setMode(3, 2, "template size <= 2048, ptr and pitch aligned, tempImgWidth != 24 or 32", 0); /* Mode 3 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = outScoreWidth * outScoreHeight",
                              "outScoreWidth * outScoreHeight");

    VLIB_profile_setMode(4, 2, "template size <= 2048, ptr or pitch non-aligned", 0); /* Mode 4 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = outScoreWidth * outScoreHeight",
                              "outScoreWidth * outScoreHeight");

    VLIB_profile_setMode(5, 2, "template size > 2048", 1); /* Mode 5 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = outScoreWidth * outScoreHeight",
                              "outScoreWidth * outScoreHeight");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_matchTemplate");
    } else {
        VLIB_matchTemplate_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_matchTemplate_d.c                                    */
/* ======================================================================== */

