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

#include "VLIB_haarDetectObjectsDense.h"
#include "VLIB_haarDetectObjectsDense_cn.h"
#include "VLIB_haarDetectObjectsDense_idat.h"

/* VLIB_haarDetectObjectsDense_d:  Test Driver Routine */
void VLIB_haarDetectObjectsDense_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    haarDetectObjectsDense_testParams_t   *prm;

    haarDetectObjectsDense_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_haarDetectObjectsDense");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
        int32_t    integralImgWidth          = prm[tpi].integralImgWidth;
        int32_t    integralImgHeight         = prm[tpi].integralImgHeight;
        int32_t    integralImgPitch          = prm[tpi].integralImgPitch;

        /* Allocate buffers for each test vector */
        /* Every track maximum length is assumed to be MAX_POINTS_IN_TRACK*/
        VLIB_HAARDETOBJ_sObjectList   *outObjList = (VLIB_HAARDETOBJ_sObjectList *)VLIB_malloc(sizeof(VLIB_HAARDETOBJ_sObjectList));
        uint8_t                       *scratch1   = VLIB_malloc(4 * (((prm[tpi].integralImgWidth + 3) & 0xFFFFFFCU) * sizeof(uint32_t)));
        uint8_t                       *scratch2   = VLIB_malloc((((prm[tpi].integralImgWidth + 7) >> 0x3U) * sizeof(uint32_t)));

        VLIB_HAARDETOBJ_sClassifier   *classifier    = (VLIB_HAARDETOBJ_sClassifier *)malloc(sizeof(VLIB_HAARDETOBJ_sClassifier));
        uint32_t                      *intImageA     = (uint32_t *) malloc(integralImgPitch * integralImgHeight * sizeof(uint32_t));
        uint32_t                      *intImageNA    = (uint32_t *) malloc((integralImgPitch * integralImgHeight + 1) * sizeof(uint32_t));
        VLIB_HAARDETOBJ_sClassifier   *classifier_cn = (VLIB_HAARDETOBJ_sClassifier *)malloc(sizeof(VLIB_HAARDETOBJ_sClassifier));
        VLIB_HAARDETOBJ_sObjectList   *outObjList_cn = (VLIB_HAARDETOBJ_sObjectList *)malloc(sizeof(VLIB_HAARDETOBJ_sObjectList));
        uint32_t                      *objectPos     = malloc(prm[tpi].maxObjects * sizeof(uint32_t));
        uint32_t                      *objectPos_cn  = malloc(prm[tpi].maxObjects * sizeof(uint32_t));

        int32_t     numPixels;
        int32_t     fail;
        int32_t     i, totTreeExec, totTreeExec_cn;
        uint32_t   *intImageNAL = intImageNA;

        /* Only run the test if the buffer allocations fit in the heap */
        if( intImageA && intImageNA && classifier && classifier_cn && outObjList &&
            outObjList_cn && objectPos && objectPos_cn && scratch1 && scratch2 ) {

            outObjList->objectPos     = objectPos;
            outObjList_cn->objectPos  = objectPos_cn;

            VLIB_fillBuffer(prm[tpi].testPattern, 0xFF, intImageA, prm[tpi].integralImg,
                            integralImgWidth, integralImgHeight, integralImgPitch * sizeof(uint32_t),
                            sizeof(uint32_t),
                            testPatternString);
            /* To make this pointer as non aligned*/
            intImageNA += 1;

            VLIB_fillBuffer(prm[tpi].testPattern, 0xFF, intImageNA, prm[tpi].integralImg,
                            integralImgWidth, integralImgHeight, integralImgPitch * sizeof(uint32_t),
                            sizeof(uint32_t), testPatternString);
            memcpy(classifier, prm[tpi].classifier, sizeof(VLIB_HAARDETOBJ_sClassifier));

            memcpy(classifier_cn, prm[tpi].classifier, sizeof(VLIB_HAARDETOBJ_sClassifier));


            numPixels = (prm[tpi].integralImgWidth - classifier->patchSize[1]) * (prm[tpi].integralImgHeight - classifier->patchSize[0]);


            if( prm[tpi].dualIntImgFlow == 0x0 ) {
                intImageNA = NULL;
            }


            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            totTreeExec =
                VLIB_haarDetectObjectsDense(intImageA,
                                            intImageNA,
                                            (prm[tpi].integralImgWidth - classifier->patchSize[1]),
                                            prm[tpi].integralImgPitch,
                                            (prm[tpi].integralImgHeight - classifier->patchSize[0]),
                                            prm[tpi].startStage,
                                            prm[tpi].endStage,
                                            prm[tpi].maxObjects,
                                            1,
                                            classifier,
                                            outObjList,
                                            scratch1,
                                            scratch2);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            totTreeExec_cn =
                VLIB_haarDetectObjectsDense_cn(intImageA,
                                               NULL,
                                               (prm[tpi].integralImgWidth - classifier->patchSize[1]),
                                               prm[tpi].integralImgPitch,
                                               prm[tpi].integralImgHeight - classifier->patchSize[0],
                                               prm[tpi].startStage,
                                               prm[tpi].endStage,
                                               prm[tpi].maxObjects,
                                               1,
                                               classifier_cn,
                                               outObjList_cn,
                                               NULL,
                                               NULL);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            if( totTreeExec != totTreeExec_cn ) {
                printf(" Mismatch With Number of Trees Executed totTreeExec = %d, totTreeExec_cn = %d \n", totTreeExec, totTreeExec_cn);
            }

            for( i = 0; i < outObjList_cn->numObjects; i++ ) {
                if( outObjList_cn->objectPos[i] != outObjList->objectPos[i] ) {
                    status_nat_vs_int = vlib_KERNEL_FAIL;
                    if( LevelOfFeedback > 0 ) {
                        printf(" Mismatch With Reference in Object Number = %u \n", i);
                    }
                    break;
                }
            }

            /* If static output is available, then additionally compares natural C output with static reference output data */
            if( prm[tpi].objectPos != NULL ) {
                for( i = 0; i < outObjList_cn->numObjects; i++ ) {
                    if( outObjList_cn->objectPos[i] != prm[tpi].objectPos[i] ) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf(" Mismatch With Static Reference in Object Number = %u \n", i);
                        }
                        break;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | numStages=%d%s",\
                    testPatternString, (prm[tpi].endStage - prm[tpi].startStage + 1), prm[tpi].desc);

            VLIB_formula_add_test(totTreeExec_cn, NULL, NULL, fail, desc, (prm[tpi].dualIntImgFlow + 1));

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numStages=%d, numPixels=%d", (prm[tpi].endStage - prm[tpi].startStage), numPixels);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */

        VLIB_free(outObjList);
        VLIB_free(scratch1);
        VLIB_free(scratch2);
        free(intImageA);
        free(intImageNAL);
        free(classifier);
        free(classifier_cn);
        free(outObjList_cn);
        free(objectPos);
        free(objectPos_cn);

    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_setMode(1, 2, "Only One Copy of Integral Image in Use", 0); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = Number of Trees Executed For all Points in Image",
                              "Number of Trees Executed For all Points in Image");

    VLIB_profile_setMode(2, 2, "Two Copy of Integral Image in Use", 1); /* Mode 1 */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = Number of Trees Executed For all Points in Image",
                              "Number of Trees Executed For all Points in Image");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_haarDetectObjectsDense");
    } else {
        VLIB_haarDetectObjectsDense_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsDense_d.c                           */
/* ======================================================================== */

