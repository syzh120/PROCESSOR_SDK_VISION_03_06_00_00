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

#include "VLIB_haarDetectObjectsSparse.h"
#include "VLIB_haarDetectObjectsSparse_cn.h"
#include "VLIB_haarDetectObjectsSparse_idat.h"

/* VLIB_haarDetectObjectsSparse_d:  Test Driver Routine */
void VLIB_haarDetectObjectsSparse_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    haarDetectObjectsSparse_testParams_t   *prm;

    haarDetectObjectsSparse_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_haarDetectObjectsSparse");

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
        VLIB_HAARDETOBJ_sObjectList   *inObjList  = (VLIB_HAARDETOBJ_sObjectList *)VLIB_malloc(sizeof(VLIB_HAARDETOBJ_sObjectList));

        uint8_t   *scratch1   = VLIB_malloc(prm[tpi].numInPos * sizeof(uint32_t));
        uint8_t   *scratch2   = VLIB_malloc(prm[tpi].numInPos);

        VLIB_HAARDETOBJ_sClassifier   *classifier    = (VLIB_HAARDETOBJ_sClassifier *)malloc(sizeof(VLIB_HAARDETOBJ_sClassifier));
        uint32_t                      *intImageA     = (uint32_t *) malloc(integralImgPitch * integralImgHeight * sizeof(uint32_t));
        VLIB_HAARDETOBJ_sObjectList   *outObjList_cn = (VLIB_HAARDETOBJ_sObjectList *)malloc(sizeof(VLIB_HAARDETOBJ_sObjectList));
        uint32_t                      *inObjectPos   = malloc(prm[tpi].numInPos * sizeof(uint32_t));
        uint32_t                      *objectPos     = malloc(prm[tpi].numInPos * sizeof(uint32_t));
        uint32_t                      *objectPos_cn  = malloc(prm[tpi].numInPos * sizeof(uint32_t));
        int32_t                        fail;
        int32_t                        i;
        int32_t                        numTrees, stageId, numTreesExecuted, numTreesExecuted_cn;

        /* Only run the test if the buffer allocations fit in the heap */
        if( intImageA && classifier && outObjList && outObjList_cn && inObjList &&
            objectPos && objectPos_cn && inObjectPos && scratch1 && scratch2 ) {

            outObjList->objectPos     = objectPos;
            outObjList_cn->objectPos  = objectPos_cn;
            inObjList->numObjects     = prm[tpi].numInPos;
            inObjList->objectPos      = inObjectPos;


            VLIB_fillBuffer(prm[tpi].testPattern, 0xFF, intImageA, prm[tpi].integralImg,
                            integralImgWidth, integralImgHeight, integralImgPitch * sizeof(uint32_t),
                            sizeof(uint32_t),
                            testPatternString);

            memcpy(classifier, prm[tpi].classifier, sizeof(VLIB_HAARDETOBJ_sClassifier));

            memcpy(inObjectPos, prm[tpi].inObjectPos, prm[tpi].numInPos * sizeof(uint32_t));

            memset(scratch2, 0x0, prm[tpi].numInPos);

            numTrees = 0;

            for( stageId=prm[tpi].startStage; stageId <= prm[tpi].endStage; stageId++ ) {
                numTrees += classifier->numTrees[stageId];
            }

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            numTreesExecuted =
                VLIB_haarDetectObjectsSparse(intImageA,
                                             prm[tpi].integralImgPitch,
                                             prm[tpi].startStage,
                                             prm[tpi].endStage,
                                             inObjList,
                                             classifier,
                                             outObjList,
                                             scratch1,
                                             scratch2);
            VLIB_profile_stop();

            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            numTreesExecuted_cn =
                VLIB_haarDetectObjectsSparse_cn(intImageA,
                                                prm[tpi].integralImgPitch,
                                                prm[tpi].startStage,
                                                prm[tpi].endStage,
                                                inObjList,
                                                classifier,
                                                outObjList_cn,
                                                NULL,
                                                NULL);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */

            if( numTreesExecuted_cn != numTreesExecuted ) {
                printf(" Mismatch With Number of Trees Executed \n");
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
            if( prm[tpi].outObjectPos != NULL ) {
                for( i = 0; i < outObjList_cn->numObjects; i++ ) {
                    if( outObjList_cn->objectPos[i] != prm[tpi].outObjectPos[i] ) {
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
            sprintf(desc, "%s generated input | Opt results compared to NatC results | numStages=%d | %s",\
                    testPatternString, (prm[tpi].endStage - prm[tpi].startStage + 1), prm[tpi].desc);

            VLIB_formula_add_test(numTreesExecuted_cn, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "numStages=%d, numInObjPos=%d", (prm[tpi].endStage - prm[tpi].startStage), prm[tpi].numInPos);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        VLIB_free(outObjList);
        VLIB_free(scratch1);
        VLIB_free(scratch2);
        VLIB_free(inObjList);

        free(inObjectPos);
        free(intImageA);
        free(classifier);
        free(outObjList_cn);
        free(objectPos);
        free(objectPos_cn);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = Number of Trees Executed For all Objects For all Stages",
                              "Number of Trees Executed For all Objects For all Stages");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_haarDetectObjectsSparse");
    } else {
        VLIB_haarDetectObjectsSparse_d(1);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsSparse_d.c                     */
/* ======================================================================== */

