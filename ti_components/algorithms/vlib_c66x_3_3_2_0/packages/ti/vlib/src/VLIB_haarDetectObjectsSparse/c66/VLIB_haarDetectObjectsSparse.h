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

#ifndef VLIB_HAARDETECTOBJECTSPARSE_H_
#define VLIB_HAARDETECTOBJECTSPARSE_H_ 1

#include "../../common/VLIB_haarDetectObjects_types.h"

/** @defgroup VLIB_haarDetectObjectsSparse */
/** @ingroup  VLIB_haarDetectObjectsSparse */
/* @{ */

/**
 * @par Description:
 *  This function implements object detection based on Haar features with
 *  Ada-boost classifier.
 *
 * @par
 *    @param [in]  integralImg        Pointer to 8 byte aligned integral image buffer                    (UQ32.0)
 *    @param [in]  integralImgPitch   Pitch of integral image                                            (UQ32.0)
 *    @param [in]  startStage         Classifier stage number to start sparse object search              (UQ32.0)
 *    @param [in]  endStage           Classifier stage number to end sparse object search                (UQ32.0)
 *    @param [in]  objListIn          Input object list holding the co-ordinates for objects
 *                                    in packed Y|X format where each co-ordinates are packed in 16 bit.  (VLIB_HAARDETOBJ_sObjectList)
 *    @param [in]  classifier         Classifier Data Structure                                           (VLIB_HAARDETOBJ_sClassifier)
 *    @param [in]  objListOut         Output List holding the co-ordinates for output objects
 *                                    in packed Y|X format where each co-ordinates are packed in 16 bit.  (VLIB_HAARDETOBJ_sObjectList)
 *    @param [in]  scratch1           Scratch buffer of 4*(number of input objects) bytes                 (UQ8.0)
 *    @param [in]  scratch2           Scratch buffer of 1*(number of input objects) bytes                 (UQ8.0)
 *
 * @par Assumptions:
 *    - Integral image is expected to be calculated outside this kernel.
 *    - All buffers should be non-aliased.
 *
 * @par Implementation Notes:
 *    - It is advised to keep all the input and output data in internal memory for better cycle performance.
 *    - If input object list is huge then it can be divided into smaller chunks to fit all input and output data into internal memory.
 *    - Another level input data splitting is possible if less number of classifier is executed in a single API call to fit input and output in internal memory.
 *
 */
int32_t    VLIB_haarDetectObjectsSparse(uint32_t integralImg[restrict],
                                        uint32_t integralImgPitch,
                                        uint32_t startStage,
                                        uint32_t endStage,
                                        VLIB_HAARDETOBJ_sObjectList objListIn[restrict],
                                        VLIB_HAARDETOBJ_sClassifier classifier[restrict],
                                        VLIB_HAARDETOBJ_sObjectList objListOut[restrict],
                                        uint8_t scratch1[restrict],
                                        uint8_t scratch2[restrict]);
/** @} */
#endif

/* ======================================================================== */
/*  End of file:  VLIB_haarDetectObjectsSparse.h                            */
/* ======================================================================== */

